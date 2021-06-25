<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  scsi_netlink.c  - SCSI Transport Netlink Interface
 *
 *  Copyright (C) 2006   James Smart, Emulex Corporation
 */
#समावेश <linux/समय.स>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/security.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <net/sock.h>
#समावेश <net/netlink.h>

#समावेश <scsi/scsi_netlink.h>
#समावेश "scsi_priv.h"

काष्ठा sock *scsi_nl_sock = शून्य;
EXPORT_SYMBOL_GPL(scsi_nl_sock);

/**
 * scsi_nl_rcv_msg - Receive message handler.
 * @skb:		socket receive buffer
 *
 * Description: Extracts message from a receive buffer.
 *    Validates message header and calls appropriate transport message handler
 *
 *
 **/
अटल व्योम
scsi_nl_rcv_msg(काष्ठा sk_buff *skb)
अणु
	काष्ठा nlmsghdr *nlh;
	काष्ठा scsi_nl_hdr *hdr;
	u32 rlen;
	पूर्णांक err, tport;

	जबतक (skb->len >= NLMSG_HDRLEN) अणु
		err = 0;

		nlh = nlmsg_hdr(skb);
		अगर ((nlh->nlmsg_len < (माप(*nlh) + माप(*hdr))) ||
		    (skb->len < nlh->nlmsg_len)) अणु
			prपूर्णांकk(KERN_WARNING "%s: discarding partial skb\n",
				 __func__);
			वापस;
		पूर्ण

		rlen = NLMSG_ALIGN(nlh->nlmsg_len);
		अगर (rlen > skb->len)
			rlen = skb->len;

		अगर (nlh->nlmsg_type != SCSI_TRANSPORT_MSG) अणु
			err = -EBADMSG;
			जाओ next_msg;
		पूर्ण

		hdr = nlmsg_data(nlh);
		अगर ((hdr->version != SCSI_NL_VERSION) ||
		    (hdr->magic != SCSI_NL_MAGIC)) अणु
			err = -EPROTOTYPE;
			जाओ next_msg;
		पूर्ण

		अगर (!netlink_capable(skb, CAP_SYS_ADMIN)) अणु
			err = -EPERM;
			जाओ next_msg;
		पूर्ण

		अगर (nlh->nlmsg_len < (माप(*nlh) + hdr->msglen)) अणु
			prपूर्णांकk(KERN_WARNING "%s: discarding partial message\n",
				 __func__);
			जाओ next_msg;
		पूर्ण

		/*
		 * Deliver message to the appropriate transport
		 */
		tport = hdr->transport;
		अगर (tport == SCSI_NL_TRANSPORT) अणु
			चयन (hdr->msgtype) अणु
			हाल SCSI_NL_SHOST_VENDOR:
				/* Locate the driver that corresponds to the message */
				err = -ESRCH;
				अवरोध;
			शेष:
				err = -EBADR;
				अवरोध;
			पूर्ण
			अगर (err)
				prपूर्णांकk(KERN_WARNING "%s: Msgtype %d failed - err %d\n",
				       __func__, hdr->msgtype, err);
		पूर्ण
		अन्यथा
			err = -ENOENT;

next_msg:
		अगर ((err) || (nlh->nlmsg_flags & NLM_F_ACK))
			netlink_ack(skb, nlh, err, शून्य);

		skb_pull(skb, rlen);
	पूर्ण
पूर्ण

/**
 * scsi_netlink_init - Called by SCSI subप्रणाली to initialize
 * 	the SCSI transport netlink पूर्णांकerface
 *
 **/
व्योम
scsi_netlink_init(व्योम)
अणु
	काष्ठा netlink_kernel_cfg cfg = अणु
		.input	= scsi_nl_rcv_msg,
		.groups	= SCSI_NL_GRP_CNT,
	पूर्ण;

	scsi_nl_sock = netlink_kernel_create(&init_net, NETLINK_SCSITRANSPORT,
					     &cfg);
	अगर (!scsi_nl_sock) अणु
		prपूर्णांकk(KERN_ERR "%s: register of receive handler failed\n",
				__func__);
		वापस;
	पूर्ण

	वापस;
पूर्ण


/**
 * scsi_netlink_निकास - Called by SCSI subप्रणाली to disable the SCSI transport netlink पूर्णांकerface
 *
 **/
व्योम
scsi_netlink_निकास(व्योम)
अणु
	अगर (scsi_nl_sock) अणु
		netlink_kernel_release(scsi_nl_sock);
	पूर्ण

	वापस;
पूर्ण

