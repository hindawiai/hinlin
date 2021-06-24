<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	Copyright IBM Corp. 2004, 2007
 *	Authors:	Belinda Thompson (belindat@us.ibm.com)
 *			Andy Richter (richtera@us.ibm.com)
 *			Peter Tiedemann (ptiedem@de.ibm.com)
 */

/*
	This module exports functions to be used by CCS:
	EXPORT_SYMBOL(ctc_mpc_alloc_channel);
	EXPORT_SYMBOL(ctc_mpc_establish_connectivity);
	EXPORT_SYMBOL(ctc_mpc_dealloc_ch);
	EXPORT_SYMBOL(ctc_mpc_flow_control);
*/

#अघोषित DEBUG
#अघोषित DEBUGDATA
#अघोषित DEBUGCCW

#घोषणा KMSG_COMPONENT "ctcm"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/समयr.h>
#समावेश <linux/sched.h>

#समावेश <linux/संकेत.स>
#समावेश <linux/माला.स>
#समावेश <linux/proc_fs.h>

#समावेश <linux/ip.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/tcp.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/netdevice.h>
#समावेश <net/dst.h>

#समावेश <linux/पन.स>		/* instead of <यंत्र/पन.स> ok ? */
#समावेश <यंत्र/ccwdev.h>
#समावेश <यंत्र/ccwgroup.h>
#समावेश <linux/bitops.h>	/* instead of <यंत्र/bitops.h> ok ? */
#समावेश <linux/uaccess.h>	/* instead of <यंत्र/uaccess.h> ok ? */
#समावेश <linux/रुको.h>
#समावेश <linux/moduleparam.h>
#समावेश <यंत्र/idals.h>

#समावेश "ctcm_main.h"
#समावेश "ctcm_mpc.h"
#समावेश "ctcm_fsms.h"

अटल स्थिर काष्ठा xid2 init_xid = अणु
	.xid2_type_id	=	XID_FM2,
	.xid2_len	=	0x45,
	.xid2_adj_id	=	0,
	.xid2_rlen	=	0x31,
	.xid2_resv1	=	0,
	.xid2_flag1	=	0,
	.xid2_fmtt	=	0,
	.xid2_flag4	=	0x80,
	.xid2_resv2	=	0,
	.xid2_tgnum	=	0,
	.xid2_sender_id	=	0,
	.xid2_flag2	=	0,
	.xid2_option	=	XID2_0,
	.xid2_resv3	=	"\x00",
	.xid2_resv4	=	0,
	.xid2_dlc_type	=	XID2_READ_SIDE,
	.xid2_resv5	=	0,
	.xid2_mpc_flag	=	0,
	.xid2_resv6	=	0,
	.xid2_buf_len	=	(MPC_बफ_मानE_DEFAULT - 35),
पूर्ण;

अटल स्थिर काष्ठा th_header thnorm = अणु
	.th_seg		=	0x00,
	.th_ch_flag	=	TH_IS_XID,
	.th_blk_flag	=	TH_DATA_IS_XID,
	.th_is_xid	=	0x01,
	.th_seq_num	=	0x00000000,
पूर्ण;

अटल स्थिर काष्ठा th_header thdummy = अणु
	.th_seg		=	0x00,
	.th_ch_flag	=	0x00,
	.th_blk_flag	=	TH_DATA_IS_XID,
	.th_is_xid	=	0x01,
	.th_seq_num	=	0x00000000,
पूर्ण;

/*
 * Definition of one MPC group
 */

/*
 * Compatibility macros क्रम busy handling
 * of network devices.
 */

अटल व्योम ctcmpc_unpack_skb(काष्ठा channel *ch, काष्ठा sk_buff *pskb);

/*
 * MPC Group state machine actions (अटल prototypes)
 */
अटल व्योम mpc_action_nop(fsm_instance *fsm, पूर्णांक event, व्योम *arg);
अटल व्योम mpc_action_go_पढ़ोy(fsm_instance *fsm, पूर्णांक event, व्योम *arg);
अटल व्योम mpc_action_go_inop(fsm_instance *fi, पूर्णांक event, व्योम *arg);
अटल व्योम mpc_action_समयout(fsm_instance *fi, पूर्णांक event, व्योम *arg);
अटल पूर्णांक  mpc_validate_xid(काष्ठा mpcg_info *mpcginfo);
अटल व्योम mpc_action_yside_xid(fsm_instance *fsm, पूर्णांक event, व्योम *arg);
अटल व्योम mpc_action_करोxid0(fsm_instance *fsm, पूर्णांक event, व्योम *arg);
अटल व्योम mpc_action_करोxid7(fsm_instance *fsm, पूर्णांक event, व्योम *arg);
अटल व्योम mpc_action_xside_xid(fsm_instance *fsm, पूर्णांक event, व्योम *arg);
अटल व्योम mpc_action_rcvd_xid0(fsm_instance *fsm, पूर्णांक event, व्योम *arg);
अटल व्योम mpc_action_rcvd_xid7(fsm_instance *fsm, पूर्णांक event, व्योम *arg);

#अगर_घोषित DEBUGDATA
/*-------------------------------------------------------------------*
* Dump buffer क्रमmat						     *
*								     *
*--------------------------------------------------------------------*/
व्योम ctcmpc_dumpit(अक्षर *buf, पूर्णांक len)
अणु
	__u32	ct, sw, rm, dup;
	अक्षर	*ptr, *rptr;
	अक्षर	tbuf[82], tdup[82];
	अक्षर	addr[22];
	अक्षर	boff[12];
	अक्षर	bhex[82], duphex[82];
	अक्षर	basc[40];

	sw  = 0;
	rptr = ptr = buf;
	rm  = 16;
	duphex[0] = 0x00;
	dup = 0;

	क्रम (ct = 0; ct < len; ct++, ptr++, rptr++) अणु
		अगर (sw == 0) अणु
			प्र_लिखो(addr, "%16.16llx", (__u64)rptr);

			प्र_लिखो(boff, "%4.4X", (__u32)ct);
			bhex[0] = '\0';
			basc[0] = '\0';
		पूर्ण
		अगर ((sw == 4) || (sw == 12))
			म_जोड़ो(bhex, " ");
		अगर (sw == 8)
			म_जोड़ो(bhex, "	");

		प्र_लिखो(tbuf, "%2.2llX", (__u64)*ptr);

		tbuf[2] = '\0';
		म_जोड़ो(bhex, tbuf);
		अगर ((0 != है_छाप(*ptr)) && (*ptr >= 0x20))
			basc[sw] = *ptr;
		अन्यथा
			basc[sw] = '.';

		basc[sw+1] = '\0';
		sw++;
		rm--;
		अगर (sw != 16)
			जारी;
		अगर ((म_भेद(duphex, bhex)) != 0) अणु
			अगर (dup != 0) अणु
				प्र_लिखो(tdup,
					"Duplicate as above to %s", addr);
				ctcm_pr_debug("		       --- %s ---\n",
						tdup);
			पूर्ण
			ctcm_pr_debug("   %s (+%s) : %s  [%s]\n",
					addr, boff, bhex, basc);
			dup = 0;
			म_नकल(duphex, bhex);
		पूर्ण अन्यथा
			dup++;

		sw = 0;
		rm = 16;
	पूर्ण  /* endक्रम */

	अगर (sw != 0) अणु
		क्रम ( ; rm > 0; rm--, sw++) अणु
			अगर ((sw == 4) || (sw == 12))
				म_जोड़ो(bhex, " ");
			अगर (sw == 8)
				म_जोड़ो(bhex, "	");
			म_जोड़ो(bhex, "	");
			म_जोड़ो(basc, " ");
		पूर्ण
		अगर (dup != 0) अणु
			प्र_लिखो(tdup, "Duplicate as above to %s", addr);
			ctcm_pr_debug("		       --- %s ---\n", tdup);
		पूर्ण
		ctcm_pr_debug("   %s (+%s) : %s  [%s]\n",
					addr, boff, bhex, basc);
	पूर्ण अन्यथा अणु
		अगर (dup >= 1) अणु
			प्र_लिखो(tdup, "Duplicate as above to %s", addr);
			ctcm_pr_debug("		       --- %s ---\n", tdup);
		पूर्ण
		अगर (dup != 0) अणु
			ctcm_pr_debug("   %s (+%s) : %s  [%s]\n",
				addr, boff, bhex, basc);
		पूर्ण
	पूर्ण

	वापस;

पूर्ण   /*	 end of ctcmpc_dumpit  */
#पूर्ण_अगर

#अगर_घोषित DEBUGDATA
/*
 * Dump header and first 16 bytes of an sk_buff क्रम debugging purposes.
 *
 * skb		The sk_buff to dump.
 * offset	Offset relative to skb-data, where to start the dump.
 */
व्योम ctcmpc_dump_skb(काष्ठा sk_buff *skb, पूर्णांक offset)
अणु
	__u8 *p = skb->data;
	काष्ठा th_header *header;
	काष्ठा pdu *pheader;
	पूर्णांक bl = skb->len;
	पूर्णांक i;

	अगर (p == शून्य)
		वापस;

	p += offset;
	header = (काष्ठा th_header *)p;

	ctcm_pr_debug("dump:\n");
	ctcm_pr_debug("skb len=%d \n", skb->len);
	अगर (skb->len > 2) अणु
		चयन (header->th_ch_flag) अणु
		हाल TH_HAS_PDU:
			अवरोध;
		हाल 0x00:
		हाल TH_IS_XID:
			अगर ((header->th_blk_flag == TH_DATA_IS_XID) &&
			   (header->th_is_xid == 0x01))
				जाओ dumpth;
		हाल TH_SWEEP_REQ:
				जाओ dumpth;
		हाल TH_SWEEP_RESP:
				जाओ dumpth;
		शेष:
			अवरोध;
		पूर्ण

		pheader = (काष्ठा pdu *)p;
		ctcm_pr_debug("pdu->offset: %d hex: %04x\n",
			       pheader->pdu_offset, pheader->pdu_offset);
		ctcm_pr_debug("pdu->flag  : %02x\n", pheader->pdu_flag);
		ctcm_pr_debug("pdu->proto : %02x\n", pheader->pdu_proto);
		ctcm_pr_debug("pdu->seq   : %02x\n", pheader->pdu_seq);
					जाओ dumpdata;

dumpth:
		ctcm_pr_debug("th->seg     : %02x\n", header->th_seg);
		ctcm_pr_debug("th->ch      : %02x\n", header->th_ch_flag);
		ctcm_pr_debug("th->blk_flag: %02x\n", header->th_blk_flag);
		ctcm_pr_debug("th->type    : %s\n",
			       (header->th_is_xid) ? "DATA" : "XID");
		ctcm_pr_debug("th->seqnum  : %04x\n", header->th_seq_num);

	पूर्ण
dumpdata:
	अगर (bl > 32)
		bl = 32;
	ctcm_pr_debug("data: ");
	क्रम (i = 0; i < bl; i++)
		ctcm_pr_debug("%02x%s", *p++, (i % 16) ? " " : "\n");
	ctcm_pr_debug("\n");
पूर्ण
#पूर्ण_अगर

अटल काष्ठा net_device *ctcmpc_get_dev(पूर्णांक port_num)
अणु
	अक्षर device[20];
	काष्ठा net_device *dev;
	काष्ठा ctcm_priv *priv;

	प्र_लिखो(device, "%s%i", MPC_DEVICE_NAME, port_num);

	dev = __dev_get_by_name(&init_net, device);

	अगर (dev == शून्य) अणु
		CTCM_DBF_TEXT_(MPC_ERROR, CTC_DBF_ERROR,
			"%s: Device not found by name: %s",
					CTCM_FUNTAIL, device);
		वापस शून्य;
	पूर्ण
	priv = dev->ml_priv;
	अगर (priv == शून्य) अणु
		CTCM_DBF_TEXT_(MPC_ERROR, CTC_DBF_ERROR,
			"%s(%s): dev->ml_priv is NULL",
					CTCM_FUNTAIL, device);
		वापस शून्य;
	पूर्ण
	अगर (priv->mpcg == शून्य) अणु
		CTCM_DBF_TEXT_(MPC_ERROR, CTC_DBF_ERROR,
			"%s(%s): priv->mpcg is NULL",
					CTCM_FUNTAIL, device);
		वापस शून्य;
	पूर्ण
	वापस dev;
पूर्ण

/*
 * ctc_mpc_alloc_channel
 *	(exported पूर्णांकerface)
 *
 * Device Initialization :
 *	ACTPATH  driven IO operations
 */
पूर्णांक ctc_mpc_alloc_channel(पूर्णांक port_num, व्योम (*callback)(पूर्णांक, पूर्णांक))
अणु
	काष्ठा net_device *dev;
	काष्ठा mpc_group *grp;
	काष्ठा ctcm_priv *priv;

	dev = ctcmpc_get_dev(port_num);
	अगर (dev == शून्य)
		वापस 1;
	priv = dev->ml_priv;
	grp = priv->mpcg;

	grp->allochanfunc = callback;
	grp->port_num = port_num;
	grp->port_persist = 1;

	CTCM_DBF_TEXT_(MPC_SETUP, CTC_DBF_INFO,
			"%s(%s): state=%s",
			CTCM_FUNTAIL, dev->name, fsm_माला_लोtate_str(grp->fsm));

	चयन (fsm_माला_लोtate(grp->fsm)) अणु
	हाल MPCG_STATE_INOP:
		/* Group is in the process of terminating */
		grp->alloc_called = 1;
		अवरोध;
	हाल MPCG_STATE_RESET:
		/* MPC Group will transition to state		  */
		/* MPCG_STATE_XID2INITW अगरf the minimum number	  */
		/* of 1 पढ़ो and 1 ग_लिखो channel have successfully*/
		/* activated					  */
		/*fsm_newstate(grp->fsm, MPCG_STATE_XID2INITW);*/
		अगर (callback)
			grp->send_qllc_disc = 1;
		fallthrough;
	हाल MPCG_STATE_XID0IOWAIT:
		fsm_delसमयr(&grp->समयr);
		grp->outstanding_xid2 = 0;
		grp->outstanding_xid7 = 0;
		grp->outstanding_xid7_p2 = 0;
		grp->saved_xid2 = शून्य;
		अगर (callback)
			ctcm_खोलो(dev);
		fsm_event(priv->fsm, DEV_EVENT_START, dev);
		अवरोध;
	हाल MPCG_STATE_READY:
		/* XID exchanges completed after PORT was activated */
		/* Link station alपढ़ोy active			    */
		/* Maybe timing issue...retry callback		    */
		grp->allocchan_callback_retries++;
		अगर (grp->allocchan_callback_retries < 4) अणु
			अगर (grp->allochanfunc)
				grp->allochanfunc(grp->port_num,
						  grp->group_max_buflen);
		पूर्ण अन्यथा अणु
			/* there are problems...bail out	    */
			/* there may be a state mismatch so restart */
			fsm_event(grp->fsm, MPCG_EVENT_INOP, dev);
			grp->allocchan_callback_retries = 0;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ctc_mpc_alloc_channel);

/*
 * ctc_mpc_establish_connectivity
 *	(exported पूर्णांकerface)
 */
व्योम ctc_mpc_establish_connectivity(पूर्णांक port_num,
				व्योम (*callback)(पूर्णांक, पूर्णांक, पूर्णांक))
अणु
	काष्ठा net_device *dev;
	काष्ठा mpc_group *grp;
	काष्ठा ctcm_priv *priv;
	काष्ठा channel *rch, *wch;

	dev = ctcmpc_get_dev(port_num);
	अगर (dev == शून्य)
		वापस;
	priv = dev->ml_priv;
	grp = priv->mpcg;
	rch = priv->channel[CTCM_READ];
	wch = priv->channel[CTCM_WRITE];

	CTCM_DBF_TEXT_(MPC_SETUP, CTC_DBF_INFO,
			"%s(%s): state=%s",
			CTCM_FUNTAIL, dev->name, fsm_माला_लोtate_str(grp->fsm));

	grp->estconnfunc = callback;
	grp->port_num = port_num;

	चयन (fsm_माला_लोtate(grp->fsm)) अणु
	हाल MPCG_STATE_READY:
		/* XID exchanges completed after PORT was activated */
		/* Link station alपढ़ोy active			    */
		/* Maybe timing issue...retry callback		    */
		fsm_delसमयr(&grp->समयr);
		grp->estconn_callback_retries++;
		अगर (grp->estconn_callback_retries < 4) अणु
			अगर (grp->estconnfunc) अणु
				grp->estconnfunc(grp->port_num, 0,
						grp->group_max_buflen);
				grp->estconnfunc = शून्य;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* there are problems...bail out	 */
			fsm_event(grp->fsm, MPCG_EVENT_INOP, dev);
			grp->estconn_callback_retries = 0;
		पूर्ण
		अवरोध;
	हाल MPCG_STATE_INOP:
	हाल MPCG_STATE_RESET:
		/* MPC Group is not पढ़ोy to start XID - min num of */
		/* 1 पढ़ो and 1 ग_लिखो channel have not been acquired*/

		CTCM_DBF_TEXT_(MPC_ERROR, CTC_DBF_ERROR,
			"%s(%s): REJECTED - inactive channels",
					CTCM_FUNTAIL, dev->name);
		अगर (grp->estconnfunc) अणु
			grp->estconnfunc(grp->port_num, -1, 0);
			grp->estconnfunc = शून्य;
		पूर्ण
		अवरोध;
	हाल MPCG_STATE_XID2INITW:
		/* alloc channel was called but no XID exchange    */
		/* has occurred. initiate xside XID exchange	   */
		/* make sure yside XID0 processing has not started */

		अगर ((fsm_माला_लोtate(rch->fsm) > CH_XID0_PENDING) ||
			(fsm_माला_लोtate(wch->fsm) > CH_XID0_PENDING)) अणु
			CTCM_DBF_TEXT_(MPC_ERROR, CTC_DBF_ERROR,
				"%s(%s): ABORT - PASSIVE XID",
					CTCM_FUNTAIL, dev->name);
			अवरोध;
		पूर्ण
		grp->send_qllc_disc = 1;
		fsm_newstate(grp->fsm, MPCG_STATE_XID0IOWAIT);
		fsm_delसमयr(&grp->समयr);
		fsm_addसमयr(&grp->समयr, MPC_XID_TIMEOUT_VALUE,
						MPCG_EVENT_TIMER, dev);
		grp->outstanding_xid7 = 0;
		grp->outstanding_xid7_p2 = 0;
		grp->saved_xid2 = शून्य;
		अगर ((rch->in_mpcgroup) &&
				(fsm_माला_लोtate(rch->fsm) == CH_XID0_PENDING))
			fsm_event(grp->fsm, MPCG_EVENT_XID0DO, rch);
		अन्यथा अणु
			CTCM_DBF_TEXT_(MPC_ERROR, CTC_DBF_ERROR,
				"%s(%s): RX-%s not ready for ACTIVE XID0",
					CTCM_FUNTAIL, dev->name, rch->id);
			अगर (grp->estconnfunc) अणु
				grp->estconnfunc(grp->port_num, -1, 0);
				grp->estconnfunc = शून्य;
			पूर्ण
			fsm_delसमयr(&grp->समयr);
				जाओ करोne;
		पूर्ण
		अगर ((wch->in_mpcgroup) &&
				(fsm_माला_लोtate(wch->fsm) == CH_XID0_PENDING))
			fsm_event(grp->fsm, MPCG_EVENT_XID0DO, wch);
		अन्यथा अणु
			CTCM_DBF_TEXT_(MPC_ERROR, CTC_DBF_ERROR,
				"%s(%s): WX-%s not ready for ACTIVE XID0",
					CTCM_FUNTAIL, dev->name, wch->id);
			अगर (grp->estconnfunc) अणु
				grp->estconnfunc(grp->port_num, -1, 0);
				grp->estconnfunc = शून्य;
			पूर्ण
			fsm_delसमयr(&grp->समयr);
				जाओ करोne;
			पूर्ण
		अवरोध;
	हाल MPCG_STATE_XID0IOWAIT:
		/* alपढ़ोy in active XID negotiations */
	शेष:
		अवरोध;
	पूर्ण

करोne:
	CTCM_PR_DEBUG("Exit %s()\n", __func__);
	वापस;
पूर्ण
EXPORT_SYMBOL(ctc_mpc_establish_connectivity);

/*
 * ctc_mpc_dealloc_ch
 *	(exported पूर्णांकerface)
 */
व्योम ctc_mpc_dealloc_ch(पूर्णांक port_num)
अणु
	काष्ठा net_device *dev;
	काष्ठा ctcm_priv *priv;
	काष्ठा mpc_group *grp;

	dev = ctcmpc_get_dev(port_num);
	अगर (dev == शून्य)
		वापस;
	priv = dev->ml_priv;
	grp = priv->mpcg;

	CTCM_DBF_TEXT_(MPC_SETUP, CTC_DBF_DEBUG,
			"%s: %s: refcount = %d\n",
			CTCM_FUNTAIL, dev->name, netdev_refcnt_पढ़ो(dev));

	fsm_delसमयr(&priv->restart_समयr);
	grp->channels_terminating = 0;
	fsm_delसमयr(&grp->समयr);
	grp->allochanfunc = शून्य;
	grp->estconnfunc = शून्य;
	grp->port_persist = 0;
	grp->send_qllc_disc = 0;
	fsm_event(grp->fsm, MPCG_EVENT_INOP, dev);

	ctcm_बंद(dev);
	वापस;
पूर्ण
EXPORT_SYMBOL(ctc_mpc_dealloc_ch);

/*
 * ctc_mpc_flow_control
 *	(exported पूर्णांकerface)
 */
व्योम ctc_mpc_flow_control(पूर्णांक port_num, पूर्णांक flowc)
अणु
	काष्ठा ctcm_priv *priv;
	काष्ठा mpc_group *grp;
	काष्ठा net_device *dev;
	काष्ठा channel *rch;
	पूर्णांक mpcg_state;

	dev = ctcmpc_get_dev(port_num);
	अगर (dev == शून्य)
		वापस;
	priv = dev->ml_priv;
	grp = priv->mpcg;

	CTCM_DBF_TEXT_(MPC_TRACE, CTC_DBF_DEBUG,
			"%s: %s: flowc = %d",
				CTCM_FUNTAIL, dev->name, flowc);

	rch = priv->channel[CTCM_READ];

	mpcg_state = fsm_माला_लोtate(grp->fsm);
	चयन (flowc) अणु
	हाल 1:
		अगर (mpcg_state == MPCG_STATE_FLOWC)
			अवरोध;
		अगर (mpcg_state == MPCG_STATE_READY) अणु
			अगर (grp->flow_off_called == 1)
				grp->flow_off_called = 0;
			अन्यथा
				fsm_newstate(grp->fsm, MPCG_STATE_FLOWC);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 0:
		अगर (mpcg_state == MPCG_STATE_FLOWC) अणु
			fsm_newstate(grp->fsm, MPCG_STATE_READY);
			/* ensure any data that has accumulated */
			/* on the io_queue will now be sen t	*/
			tasklet_schedule(&rch->ch_tasklet);
		पूर्ण
		/* possible race condition			*/
		अगर (mpcg_state == MPCG_STATE_READY) अणु
			grp->flow_off_called = 1;
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

पूर्ण
EXPORT_SYMBOL(ctc_mpc_flow_control);

अटल पूर्णांक mpc_send_qllc_discontact(काष्ठा net_device *);

/*
 * helper function of ctcmpc_unpack_skb
*/
अटल व्योम mpc_rcvd_sweep_resp(काष्ठा mpcg_info *mpcginfo)
अणु
	काष्ठा channel	  *rch = mpcginfo->ch;
	काष्ठा net_device *dev = rch->netdev;
	काष्ठा ctcm_priv   *priv = dev->ml_priv;
	काष्ठा mpc_group  *grp = priv->mpcg;
	काष्ठा channel	  *ch = priv->channel[CTCM_WRITE];

	CTCM_PR_DEBUG("%s: ch=0x%p id=%s\n", __func__, ch, ch->id);
	CTCM_D3_DUMP((अक्षर *)mpcginfo->sweep, TH_SWEEP_LENGTH);

	grp->sweep_rsp_pend_num--;

	अगर ((grp->sweep_req_pend_num == 0) &&
			(grp->sweep_rsp_pend_num == 0)) अणु
		fsm_delसमयr(&ch->sweep_समयr);
		grp->in_sweep = 0;
		rch->th_seq_num = 0x00;
		ch->th_seq_num = 0x00;
		ctcm_clear_busy_करो(dev);
	पूर्ण

	kमुक्त(mpcginfo);

	वापस;

पूर्ण

/*
 * helper function of mpc_rcvd_sweep_req
 * which is a helper of ctcmpc_unpack_skb
 */
अटल व्योम ctcmpc_send_sweep_resp(काष्ठा channel *rch)
अणु
	काष्ठा net_device *dev = rch->netdev;
	काष्ठा ctcm_priv *priv = dev->ml_priv;
	काष्ठा mpc_group *grp = priv->mpcg;
	काष्ठा th_sweep *header;
	काष्ठा sk_buff *sweep_skb;
	काष्ठा channel *ch  = priv->channel[CTCM_WRITE];

	CTCM_PR_DEBUG("%s: ch=0x%p id=%s\n", __func__, rch, rch->id);

	sweep_skb = __dev_alloc_skb(MPC_बफ_मानE_DEFAULT, GFP_ATOMIC | GFP_DMA);
	अगर (sweep_skb == शून्य) अणु
		CTCM_DBF_TEXT_(MPC_ERROR, CTC_DBF_ERROR,
			"%s(%s): sweep_skb allocation ERROR\n",
			CTCM_FUNTAIL, rch->id);
		जाओ करोne;
	पूर्ण

	header = skb_put_zero(sweep_skb, TH_SWEEP_LENGTH);
	header->th.th_ch_flag	= TH_SWEEP_RESP;
	header->sw.th_last_seq	= ch->th_seq_num;

	netअगर_trans_update(dev);
	skb_queue_tail(&ch->sweep_queue, sweep_skb);

	fsm_addसमयr(&ch->sweep_समयr, 100, CTC_EVENT_RSWEEP_TIMER, ch);

	वापस;

करोne:
	grp->in_sweep = 0;
	ctcm_clear_busy_करो(dev);
	fsm_event(grp->fsm, MPCG_EVENT_INOP, dev);

	वापस;
पूर्ण

/*
 * helper function of ctcmpc_unpack_skb
 */
अटल व्योम mpc_rcvd_sweep_req(काष्ठा mpcg_info *mpcginfo)
अणु
	काष्ठा channel	  *rch     = mpcginfo->ch;
	काष्ठा net_device *dev     = rch->netdev;
	काष्ठा ctcm_priv  *priv = dev->ml_priv;
	काष्ठा mpc_group  *grp  = priv->mpcg;
	काष्ठा channel	  *ch	   = priv->channel[CTCM_WRITE];

	अगर (करो_debug)
		CTCM_DBF_TEXT_(MPC_TRACE, CTC_DBF_DEBUG,
			" %s(): ch=0x%p id=%s\n", __func__, ch, ch->id);

	अगर (grp->in_sweep == 0) अणु
		grp->in_sweep = 1;
		ctcm_test_and_set_busy(dev);
		grp->sweep_req_pend_num = grp->active_channels[CTCM_READ];
		grp->sweep_rsp_pend_num = grp->active_channels[CTCM_READ];
	पूर्ण

	CTCM_D3_DUMP((अक्षर *)mpcginfo->sweep, TH_SWEEP_LENGTH);

	grp->sweep_req_pend_num--;
	ctcmpc_send_sweep_resp(ch);
	kमुक्त(mpcginfo);
	वापस;
पूर्ण

/*
  * MPC Group Station FSM definitions
 */
अटल स्थिर अक्षर *mpcg_event_names[] = अणु
	[MPCG_EVENT_INOP]	= "INOP Condition",
	[MPCG_EVENT_DISCONC]	= "Discontact Received",
	[MPCG_EVENT_XID0DO]	= "Channel Active - Start XID",
	[MPCG_EVENT_XID2]	= "XID2 Received",
	[MPCG_EVENT_XID2DONE]	= "XID0 Complete",
	[MPCG_EVENT_XID7DONE]	= "XID7 Complete",
	[MPCG_EVENT_TIMER]	= "XID Setup Timer",
	[MPCG_EVENT_DOIO]	= "XID DoIO",
पूर्ण;

अटल स्थिर अक्षर *mpcg_state_names[] = अणु
	[MPCG_STATE_RESET]	= "Reset",
	[MPCG_STATE_INOP]	= "INOP",
	[MPCG_STATE_XID2INITW]	= "Passive XID- XID0 Pending Start",
	[MPCG_STATE_XID2INITX]	= "Passive XID- XID0 Pending Complete",
	[MPCG_STATE_XID7INITW]	= "Passive XID- XID7 Pending P1 Start",
	[MPCG_STATE_XID7INITX]	= "Passive XID- XID7 Pending P2 Complete",
	[MPCG_STATE_XID0IOWAIT]	= "Active  XID- XID0 Pending Start",
	[MPCG_STATE_XID0IOWAIX]	= "Active  XID- XID0 Pending Complete",
	[MPCG_STATE_XID7INITI]	= "Active  XID- XID7 Pending Start",
	[MPCG_STATE_XID7INITZ]	= "Active  XID- XID7 Pending Complete ",
	[MPCG_STATE_XID7INITF]	= "XID        - XID7 Complete ",
	[MPCG_STATE_FLOWC]	= "FLOW CONTROL ON",
	[MPCG_STATE_READY]	= "READY",
पूर्ण;

/*
 * The MPC Group Station FSM
 *   22 events
 */
अटल स्थिर fsm_node mpcg_fsm[] = अणु
	अणु MPCG_STATE_RESET,	MPCG_EVENT_INOP,	mpc_action_go_inop    पूर्ण,
	अणु MPCG_STATE_INOP,	MPCG_EVENT_INOP,	mpc_action_nop        पूर्ण,
	अणु MPCG_STATE_FLOWC,	MPCG_EVENT_INOP,	mpc_action_go_inop    पूर्ण,

	अणु MPCG_STATE_READY,	MPCG_EVENT_DISCONC,	mpc_action_discontact पूर्ण,
	अणु MPCG_STATE_READY,	MPCG_EVENT_INOP,	mpc_action_go_inop    पूर्ण,

	अणु MPCG_STATE_XID2INITW,	MPCG_EVENT_XID0DO,	mpc_action_करोxid0     पूर्ण,
	अणु MPCG_STATE_XID2INITW,	MPCG_EVENT_XID2,	mpc_action_rcvd_xid0  पूर्ण,
	अणु MPCG_STATE_XID2INITW,	MPCG_EVENT_INOP,	mpc_action_go_inop    पूर्ण,
	अणु MPCG_STATE_XID2INITW,	MPCG_EVENT_TIMER,	mpc_action_समयout    पूर्ण,
	अणु MPCG_STATE_XID2INITW,	MPCG_EVENT_DOIO,	mpc_action_yside_xid  पूर्ण,

	अणु MPCG_STATE_XID2INITX,	MPCG_EVENT_XID0DO,	mpc_action_करोxid0     पूर्ण,
	अणु MPCG_STATE_XID2INITX,	MPCG_EVENT_XID2,	mpc_action_rcvd_xid0  पूर्ण,
	अणु MPCG_STATE_XID2INITX,	MPCG_EVENT_INOP,	mpc_action_go_inop    पूर्ण,
	अणु MPCG_STATE_XID2INITX,	MPCG_EVENT_TIMER,	mpc_action_समयout    पूर्ण,
	अणु MPCG_STATE_XID2INITX,	MPCG_EVENT_DOIO,	mpc_action_yside_xid  पूर्ण,

	अणु MPCG_STATE_XID7INITW,	MPCG_EVENT_XID2DONE,	mpc_action_करोxid7     पूर्ण,
	अणु MPCG_STATE_XID7INITW,	MPCG_EVENT_DISCONC,	mpc_action_discontact पूर्ण,
	अणु MPCG_STATE_XID7INITW,	MPCG_EVENT_XID2,	mpc_action_rcvd_xid7  पूर्ण,
	अणु MPCG_STATE_XID7INITW,	MPCG_EVENT_INOP,	mpc_action_go_inop    पूर्ण,
	अणु MPCG_STATE_XID7INITW,	MPCG_EVENT_TIMER,	mpc_action_समयout    पूर्ण,
	अणु MPCG_STATE_XID7INITW,	MPCG_EVENT_XID7DONE,	mpc_action_करोxid7     पूर्ण,
	अणु MPCG_STATE_XID7INITW,	MPCG_EVENT_DOIO,	mpc_action_yside_xid  पूर्ण,

	अणु MPCG_STATE_XID7INITX,	MPCG_EVENT_DISCONC,	mpc_action_discontact पूर्ण,
	अणु MPCG_STATE_XID7INITX,	MPCG_EVENT_XID2,	mpc_action_rcvd_xid7  पूर्ण,
	अणु MPCG_STATE_XID7INITX,	MPCG_EVENT_INOP,	mpc_action_go_inop    पूर्ण,
	अणु MPCG_STATE_XID7INITX,	MPCG_EVENT_XID7DONE,	mpc_action_करोxid7     पूर्ण,
	अणु MPCG_STATE_XID7INITX,	MPCG_EVENT_TIMER,	mpc_action_समयout    पूर्ण,
	अणु MPCG_STATE_XID7INITX,	MPCG_EVENT_DOIO,	mpc_action_yside_xid  पूर्ण,

	अणु MPCG_STATE_XID0IOWAIT, MPCG_EVENT_XID0DO,	mpc_action_करोxid0     पूर्ण,
	अणु MPCG_STATE_XID0IOWAIT, MPCG_EVENT_DISCONC,	mpc_action_discontact पूर्ण,
	अणु MPCG_STATE_XID0IOWAIT, MPCG_EVENT_XID2,	mpc_action_rcvd_xid0  पूर्ण,
	अणु MPCG_STATE_XID0IOWAIT, MPCG_EVENT_INOP,	mpc_action_go_inop    पूर्ण,
	अणु MPCG_STATE_XID0IOWAIT, MPCG_EVENT_TIMER,	mpc_action_समयout    पूर्ण,
	अणु MPCG_STATE_XID0IOWAIT, MPCG_EVENT_DOIO,	mpc_action_xside_xid  पूर्ण,

	अणु MPCG_STATE_XID0IOWAIX, MPCG_EVENT_XID0DO,	mpc_action_करोxid0     पूर्ण,
	अणु MPCG_STATE_XID0IOWAIX, MPCG_EVENT_DISCONC,	mpc_action_discontact पूर्ण,
	अणु MPCG_STATE_XID0IOWAIX, MPCG_EVENT_XID2,	mpc_action_rcvd_xid0  पूर्ण,
	अणु MPCG_STATE_XID0IOWAIX, MPCG_EVENT_INOP,	mpc_action_go_inop    पूर्ण,
	अणु MPCG_STATE_XID0IOWAIX, MPCG_EVENT_TIMER,	mpc_action_समयout    पूर्ण,
	अणु MPCG_STATE_XID0IOWAIX, MPCG_EVENT_DOIO,	mpc_action_xside_xid  पूर्ण,

	अणु MPCG_STATE_XID7INITI,	MPCG_EVENT_XID2DONE,	mpc_action_करोxid7     पूर्ण,
	अणु MPCG_STATE_XID7INITI,	MPCG_EVENT_XID2,	mpc_action_rcvd_xid7  पूर्ण,
	अणु MPCG_STATE_XID7INITI,	MPCG_EVENT_DISCONC,	mpc_action_discontact पूर्ण,
	अणु MPCG_STATE_XID7INITI,	MPCG_EVENT_INOP,	mpc_action_go_inop    पूर्ण,
	अणु MPCG_STATE_XID7INITI,	MPCG_EVENT_TIMER,	mpc_action_समयout    पूर्ण,
	अणु MPCG_STATE_XID7INITI,	MPCG_EVENT_XID7DONE,	mpc_action_करोxid7     पूर्ण,
	अणु MPCG_STATE_XID7INITI,	MPCG_EVENT_DOIO,	mpc_action_xside_xid  पूर्ण,

	अणु MPCG_STATE_XID7INITZ,	MPCG_EVENT_XID2,	mpc_action_rcvd_xid7  पूर्ण,
	अणु MPCG_STATE_XID7INITZ,	MPCG_EVENT_XID7DONE,	mpc_action_करोxid7     पूर्ण,
	अणु MPCG_STATE_XID7INITZ,	MPCG_EVENT_DISCONC,	mpc_action_discontact पूर्ण,
	अणु MPCG_STATE_XID7INITZ,	MPCG_EVENT_INOP,	mpc_action_go_inop    पूर्ण,
	अणु MPCG_STATE_XID7INITZ,	MPCG_EVENT_TIMER,	mpc_action_समयout    पूर्ण,
	अणु MPCG_STATE_XID7INITZ,	MPCG_EVENT_DOIO,	mpc_action_xside_xid  पूर्ण,

	अणु MPCG_STATE_XID7INITF,	MPCG_EVENT_INOP,	mpc_action_go_inop    पूर्ण,
	अणु MPCG_STATE_XID7INITF,	MPCG_EVENT_XID7DONE,	mpc_action_go_पढ़ोy   पूर्ण,
पूर्ण;

अटल पूर्णांक mpcg_fsm_len = ARRAY_SIZE(mpcg_fsm);

/*
 * MPC Group Station FSM action
 * CTCM_PROTO_MPC only
 */
अटल व्योम mpc_action_go_पढ़ोy(fsm_instance *fsm, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा net_device *dev = arg;
	काष्ठा ctcm_priv *priv = dev->ml_priv;
	काष्ठा mpc_group *grp = priv->mpcg;

	अगर (grp == शून्य) अणु
		CTCM_DBF_TEXT_(MPC_ERROR, CTC_DBF_ERROR,
			"%s(%s): No MPC group",
				CTCM_FUNTAIL, dev->name);
		वापस;
	पूर्ण

	fsm_delसमयr(&grp->समयr);

	अगर (grp->saved_xid2->xid2_flag2 == 0x40) अणु
		priv->xid->xid2_flag2 = 0x00;
		अगर (grp->estconnfunc) अणु
			grp->estconnfunc(grp->port_num, 1,
					grp->group_max_buflen);
			grp->estconnfunc = शून्य;
		पूर्ण अन्यथा अगर (grp->allochanfunc)
			grp->send_qllc_disc = 1;

		fsm_event(grp->fsm, MPCG_EVENT_INOP, dev);
		CTCM_DBF_TEXT_(MPC_ERROR, CTC_DBF_ERROR,
				"%s(%s): fails",
					CTCM_FUNTAIL, dev->name);
		वापस;
	पूर्ण

	grp->port_persist = 1;
	grp->out_of_sequence = 0;
	grp->estconn_called = 0;

	tasklet_hi_schedule(&grp->mpc_tasklet2);

	वापस;
पूर्ण

/*
 * helper of ctcm_init_netdevice
 * CTCM_PROTO_MPC only
 */
व्योम mpc_group_पढ़ोy(अचिन्हित दीर्घ adev)
अणु
	काष्ठा net_device *dev = (काष्ठा net_device *)adev;
	काष्ठा ctcm_priv *priv = dev->ml_priv;
	काष्ठा mpc_group *grp = priv->mpcg;
	काष्ठा channel *ch = शून्य;

	अगर (grp == शून्य) अणु
		CTCM_DBF_TEXT_(MPC_ERROR, CTC_DBF_ERROR,
			"%s(%s): No MPC group",
				CTCM_FUNTAIL, dev->name);
		वापस;
	पूर्ण

	CTCM_DBF_TEXT_(MPC_SETUP, CTC_DBF_NOTICE,
		"%s: %s: GROUP TRANSITIONED TO READY, maxbuf = %d\n",
			CTCM_FUNTAIL, dev->name, grp->group_max_buflen);

	fsm_newstate(grp->fsm, MPCG_STATE_READY);

	/* Put up a पढ़ो on the channel */
	ch = priv->channel[CTCM_READ];
	ch->pdu_seq = 0;
	CTCM_PR_DBGDATA("ctcmpc: %s() ToDCM_pdu_seq= %08x\n" ,
			__func__, ch->pdu_seq);

	ctcmpc_chx_rxidle(ch->fsm, CTC_EVENT_START, ch);
	/* Put the ग_लिखो channel in idle state */
	ch = priv->channel[CTCM_WRITE];
	अगर (ch->collect_len > 0) अणु
		spin_lock(&ch->collect_lock);
		ctcm_purge_skb_queue(&ch->collect_queue);
		ch->collect_len = 0;
		spin_unlock(&ch->collect_lock);
	पूर्ण
	ctcm_chx_txidle(ch->fsm, CTC_EVENT_START, ch);
	ctcm_clear_busy(dev);

	अगर (grp->estconnfunc) अणु
		grp->estconnfunc(grp->port_num, 0,
				    grp->group_max_buflen);
		grp->estconnfunc = शून्य;
	पूर्ण अन्यथा 	अगर (grp->allochanfunc)
		grp->allochanfunc(grp->port_num, grp->group_max_buflen);

	grp->send_qllc_disc = 1;
	grp->changed_side = 0;

	वापस;

पूर्ण

/*
 * Increment the MPC Group Active Channel Counts
 * helper of dev_action (called from channel fsm)
 */
व्योम mpc_channel_action(काष्ठा channel *ch, पूर्णांक direction, पूर्णांक action)
अणु
	काष्ठा net_device  *dev  = ch->netdev;
	काष्ठा ctcm_priv   *priv = dev->ml_priv;
	काष्ठा mpc_group   *grp  = priv->mpcg;

	अगर (grp == शून्य) अणु
		CTCM_DBF_TEXT_(MPC_ERROR, CTC_DBF_ERROR,
			"%s(%s): No MPC group",
				CTCM_FUNTAIL, dev->name);
		वापस;
	पूर्ण

	CTCM_PR_DEBUG("enter %s: ch=0x%p id=%s\n", __func__, ch, ch->id);

	CTCM_DBF_TEXT_(MPC_TRACE, CTC_DBF_NOTICE,
		"%s: %i / Grp:%s total_channels=%i, active_channels: "
		"read=%i, write=%i\n", __func__, action,
		fsm_माला_लोtate_str(grp->fsm), grp->num_channel_paths,
		grp->active_channels[CTCM_READ],
		grp->active_channels[CTCM_WRITE]);

	अगर ((action == MPC_CHANNEL_ADD) && (ch->in_mpcgroup == 0)) अणु
		grp->num_channel_paths++;
		grp->active_channels[direction]++;
		grp->outstanding_xid2++;
		ch->in_mpcgroup = 1;

		अगर (ch->xid_skb != शून्य)
			dev_kमुक्त_skb_any(ch->xid_skb);

		ch->xid_skb = __dev_alloc_skb(MPC_बफ_मानE_DEFAULT,
					GFP_ATOMIC | GFP_DMA);
		अगर (ch->xid_skb == शून्य) अणु
			CTCM_DBF_TEXT_(MPC_ERROR, CTC_DBF_ERROR,
				"%s(%s): Couldn't alloc ch xid_skb\n",
				CTCM_FUNTAIL, dev->name);
			fsm_event(grp->fsm, MPCG_EVENT_INOP, dev);
			वापस;
		पूर्ण
		ch->xid_skb_data = ch->xid_skb->data;
		ch->xid_th = (काष्ठा th_header *)ch->xid_skb->data;
		skb_put(ch->xid_skb, TH_HEADER_LENGTH);
		ch->xid = (काष्ठा xid2 *)skb_tail_poपूर्णांकer(ch->xid_skb);
		skb_put(ch->xid_skb, XID2_LENGTH);
		ch->xid_id = skb_tail_poपूर्णांकer(ch->xid_skb);
		ch->xid_skb->data = ch->xid_skb_data;
		skb_reset_tail_poपूर्णांकer(ch->xid_skb);
		ch->xid_skb->len = 0;

		skb_put_data(ch->xid_skb, grp->xid_skb->data,
			     grp->xid_skb->len);

		ch->xid->xid2_dlc_type =
			((CHANNEL_सूचीECTION(ch->flags) == CTCM_READ)
				? XID2_READ_SIDE : XID2_WRITE_SIDE);

		अगर (CHANNEL_सूचीECTION(ch->flags) == CTCM_WRITE)
			ch->xid->xid2_buf_len = 0x00;

		ch->xid_skb->data = ch->xid_skb_data;
		skb_reset_tail_poपूर्णांकer(ch->xid_skb);
		ch->xid_skb->len = 0;

		fsm_newstate(ch->fsm, CH_XID0_PENDING);

		अगर ((grp->active_channels[CTCM_READ] > 0) &&
		    (grp->active_channels[CTCM_WRITE] > 0) &&
			(fsm_माला_लोtate(grp->fsm) < MPCG_STATE_XID2INITW)) अणु
			fsm_newstate(grp->fsm, MPCG_STATE_XID2INITW);
			CTCM_DBF_TEXT_(MPC_SETUP, CTC_DBF_NOTICE,
				"%s: %s: MPC GROUP CHANNELS ACTIVE\n",
						__func__, dev->name);
		पूर्ण
	पूर्ण अन्यथा अगर ((action == MPC_CHANNEL_REMOVE) &&
			(ch->in_mpcgroup == 1)) अणु
		ch->in_mpcgroup = 0;
		grp->num_channel_paths--;
		grp->active_channels[direction]--;

		अगर (ch->xid_skb != शून्य)
			dev_kमुक्त_skb_any(ch->xid_skb);
		ch->xid_skb = शून्य;

		अगर (grp->channels_terminating)
					जाओ करोne;

		अगर (((grp->active_channels[CTCM_READ] == 0) &&
					(grp->active_channels[CTCM_WRITE] > 0))
			|| ((grp->active_channels[CTCM_WRITE] == 0) &&
					(grp->active_channels[CTCM_READ] > 0)))
			fsm_event(grp->fsm, MPCG_EVENT_INOP, dev);
	पूर्ण
करोne:
	CTCM_DBF_TEXT_(MPC_TRACE, CTC_DBF_DEBUG,
		"exit %s: %i / Grp:%s total_channels=%i, active_channels: "
		"read=%i, write=%i\n", __func__, action,
		fsm_माला_लोtate_str(grp->fsm), grp->num_channel_paths,
		grp->active_channels[CTCM_READ],
		grp->active_channels[CTCM_WRITE]);

	CTCM_PR_DEBUG("exit %s: ch=0x%p id=%s\n", __func__, ch, ch->id);
पूर्ण

/**
 * Unpack a just received skb and hand it over to
 * upper layers.
 * special MPC version of unpack_skb.
 *
 * ch		The channel where this skb has been received.
 * pskb		The received skb.
 */
अटल व्योम ctcmpc_unpack_skb(काष्ठा channel *ch, काष्ठा sk_buff *pskb)
अणु
	काष्ठा net_device *dev	= ch->netdev;
	काष्ठा ctcm_priv *priv = dev->ml_priv;
	काष्ठा mpc_group *grp = priv->mpcg;
	काष्ठा pdu *curr_pdu;
	काष्ठा mpcg_info *mpcginfo;
	काष्ठा th_header *header = शून्य;
	काष्ठा th_sweep *sweep = शून्य;
	पूर्णांक pdu_last_seen = 0;
	__u32 new_len;
	काष्ठा sk_buff *skb;
	पूर्णांक skblen;
	पूर्णांक sendrc = 0;

	CTCM_PR_DEBUG("ctcmpc enter: %s() %s cp:%i ch:%s\n",
			__func__, dev->name, smp_processor_id(), ch->id);

	header = (काष्ठा th_header *)pskb->data;
	अगर ((header->th_seg == 0) &&
		(header->th_ch_flag == 0) &&
		(header->th_blk_flag == 0) &&
		(header->th_seq_num == 0))
		/* nothing क्रम us */	जाओ करोne;

	CTCM_PR_DBGDATA("%s: th_header\n", __func__);
	CTCM_D3_DUMP((अक्षर *)header, TH_HEADER_LENGTH);
	CTCM_PR_DBGDATA("%s: pskb len: %04x \n", __func__, pskb->len);

	pskb->dev = dev;
	pskb->ip_summed = CHECKSUM_UNNECESSARY;
	skb_pull(pskb, TH_HEADER_LENGTH);

	अगर (likely(header->th_ch_flag == TH_HAS_PDU)) अणु
		CTCM_PR_DBGDATA("%s: came into th_has_pdu\n", __func__);
		अगर ((fsm_माला_लोtate(grp->fsm) == MPCG_STATE_FLOWC) ||
		   ((fsm_माला_लोtate(grp->fsm) == MPCG_STATE_READY) &&
		    (header->th_seq_num != ch->th_seq_num + 1) &&
		    (ch->th_seq_num != 0))) अणु
			/* This is NOT the next segment		*
			 * we are not the correct race winner	*
			 * go away and let someone अन्यथा win	*
			 * BUT..this only applies अगर xid negot	*
			 * is करोne				*
			*/
			grp->out_of_sequence += 1;
			__skb_push(pskb, TH_HEADER_LENGTH);
			skb_queue_tail(&ch->io_queue, pskb);
			CTCM_PR_DBGDATA("%s: th_seq_num expect:%08x "
					"got:%08x\n", __func__,
				ch->th_seq_num + 1, header->th_seq_num);

			वापस;
		पूर्ण
		grp->out_of_sequence = 0;
		ch->th_seq_num = header->th_seq_num;

		CTCM_PR_DBGDATA("ctcmpc: %s() FromVTAM_th_seq=%08x\n",
					__func__, ch->th_seq_num);

		अगर (unlikely(fsm_माला_लोtate(grp->fsm) != MPCG_STATE_READY))
					जाओ करोne;
		जबतक ((pskb->len > 0) && !pdu_last_seen) अणु
			curr_pdu = (काष्ठा pdu *)pskb->data;

			CTCM_PR_DBGDATA("%s: pdu_header\n", __func__);
			CTCM_D3_DUMP((अक्षर *)pskb->data, PDU_HEADER_LENGTH);
			CTCM_PR_DBGDATA("%s: pskb len: %04x \n",
						__func__, pskb->len);

			skb_pull(pskb, PDU_HEADER_LENGTH);

			अगर (curr_pdu->pdu_flag & PDU_LAST)
				pdu_last_seen = 1;
			अगर (curr_pdu->pdu_flag & PDU_CNTL)
				pskb->protocol = htons(ETH_P_SNAP);
			अन्यथा
				pskb->protocol = htons(ETH_P_SNA_DIX);

			अगर ((pskb->len <= 0) || (pskb->len > ch->max_bufsize)) अणु
				CTCM_DBF_TEXT_(MPC_ERROR, CTC_DBF_ERROR,
					"%s(%s): Dropping packet with "
					"illegal siize %d",
					CTCM_FUNTAIL, dev->name, pskb->len);

				priv->stats.rx_dropped++;
				priv->stats.rx_length_errors++;
					जाओ करोne;
			पूर्ण
			skb_reset_mac_header(pskb);
			new_len = curr_pdu->pdu_offset;
			CTCM_PR_DBGDATA("%s: new_len: %04x \n",
						__func__, new_len);
			अगर ((new_len == 0) || (new_len > pskb->len)) अणु
				/* should never happen		    */
				/* pskb len must be hosed...bail out */
				CTCM_DBF_TEXT_(MPC_ERROR, CTC_DBF_ERROR,
					"%s(%s): non valid pdu_offset: %04x",
					/* "data may be lost", */
					CTCM_FUNTAIL, dev->name, new_len);
				जाओ करोne;
			पूर्ण
			skb = __dev_alloc_skb(new_len+4, GFP_ATOMIC);

			अगर (!skb) अणु
				CTCM_DBF_TEXT_(MPC_ERROR, CTC_DBF_ERROR,
					"%s(%s): MEMORY allocation error",
						CTCM_FUNTAIL, dev->name);
				priv->stats.rx_dropped++;
				fsm_event(grp->fsm, MPCG_EVENT_INOP, dev);
						जाओ करोne;
			पूर्ण
			skb_put_data(skb, pskb->data, new_len);

			skb_reset_mac_header(skb);
			skb->dev = pskb->dev;
			skb->protocol = pskb->protocol;
			skb->ip_summed = CHECKSUM_UNNECESSARY;
			*((__u32 *) skb_push(skb, 4)) = ch->pdu_seq;
			ch->pdu_seq++;

			अगर (करो_debug_data) अणु
				ctcm_pr_debug("%s: ToDCM_pdu_seq= %08x\n",
						__func__, ch->pdu_seq);
				ctcm_pr_debug("%s: skb:%0lx "
					"skb len: %d \n", __func__,
					(अचिन्हित दीर्घ)skb, skb->len);
				ctcm_pr_debug("%s: up to 32 bytes "
					"of pdu_data sent\n", __func__);
				ctcmpc_dump32((अक्षर *)skb->data, skb->len);
			पूर्ण

			skblen = skb->len;
			sendrc = netअगर_rx(skb);
			priv->stats.rx_packets++;
			priv->stats.rx_bytes += skblen;
			skb_pull(pskb, new_len); /* poपूर्णांक to next PDU */
		पूर्ण
	पूर्ण अन्यथा अणु
		mpcginfo = kदो_स्मृति(माप(काष्ठा mpcg_info), GFP_ATOMIC);
		अगर (mpcginfo == शून्य)
					जाओ करोne;

		mpcginfo->ch = ch;
		mpcginfo->th = header;
		mpcginfo->skb = pskb;
		CTCM_PR_DEBUG("%s: Not PDU - may be control pkt\n",
					__func__);
		/*  it's a sweep?   */
		sweep = (काष्ठा th_sweep *)pskb->data;
		mpcginfo->sweep = sweep;
		अगर (header->th_ch_flag == TH_SWEEP_REQ)
			mpc_rcvd_sweep_req(mpcginfo);
		अन्यथा अगर (header->th_ch_flag == TH_SWEEP_RESP)
			mpc_rcvd_sweep_resp(mpcginfo);
		अन्यथा अगर (header->th_blk_flag == TH_DATA_IS_XID) अणु
			काष्ठा xid2 *thisxid = (काष्ठा xid2 *)pskb->data;
			skb_pull(pskb, XID2_LENGTH);
			mpcginfo->xid = thisxid;
			fsm_event(grp->fsm, MPCG_EVENT_XID2, mpcginfo);
		पूर्ण अन्यथा अगर (header->th_blk_flag == TH_DISCONTACT)
			fsm_event(grp->fsm, MPCG_EVENT_DISCONC, mpcginfo);
		अन्यथा अगर (header->th_seq_num != 0) अणु
			CTCM_DBF_TEXT_(MPC_ERROR, CTC_DBF_ERROR,
				"%s(%s): control pkt expected\n",
						CTCM_FUNTAIL, dev->name);
			priv->stats.rx_dropped++;
			/* mpcginfo only used क्रम non-data transfers */
			kमुक्त(mpcginfo);
			अगर (करो_debug_data)
				ctcmpc_dump_skb(pskb, -8);
		पूर्ण
	पूर्ण
करोne:

	dev_kमुक्त_skb_any(pskb);
	अगर (sendrc == NET_RX_DROP) अणु
		dev_warn(&dev->dev,
			"The network backlog for %s is exceeded, "
			"package dropped\n", __func__);
		fsm_event(grp->fsm, MPCG_EVENT_INOP, dev);
	पूर्ण

	CTCM_PR_DEBUG("exit %s: %s: ch=0x%p id=%s\n",
			__func__, dev->name, ch, ch->id);
पूर्ण

/**
 * tasklet helper क्रम mpc's skb unpacking.
 *
 * ch		The channel to work on.
 * Allow flow control back pressure to occur here.
 * Throttling back channel can result in excessive
 * channel inactivity and प्रणाली deact of channel
 */
व्योम ctcmpc_bh(अचिन्हित दीर्घ thischan)
अणु
	काष्ठा channel	  *ch	= (काष्ठा channel *)thischan;
	काष्ठा sk_buff	  *skb;
	काष्ठा net_device *dev	= ch->netdev;
	काष्ठा ctcm_priv  *priv	= dev->ml_priv;
	काष्ठा mpc_group  *grp	= priv->mpcg;

	CTCM_PR_DEBUG("%s cp:%i enter:  %s() %s\n",
	       dev->name, smp_processor_id(), __func__, ch->id);
	/* caller has requested driver to throttle back */
	जबतक ((fsm_माला_लोtate(grp->fsm) != MPCG_STATE_FLOWC) &&
			(skb = skb_dequeue(&ch->io_queue))) अणु
		ctcmpc_unpack_skb(ch, skb);
		अगर (grp->out_of_sequence > 20) अणु
			/* assume data loss has occurred अगर */
			/* missing seq_num क्रम extended     */
			/* period of समय		    */
			grp->out_of_sequence = 0;
			fsm_event(grp->fsm, MPCG_EVENT_INOP, dev);
			अवरोध;
		पूर्ण
		अगर (skb == skb_peek(&ch->io_queue))
			अवरोध;
	पूर्ण
	CTCM_PR_DEBUG("exit %s: %s: ch=0x%p id=%s\n",
			__func__, dev->name, ch, ch->id);
	वापस;
पूर्ण

/*
 *  MPC Group Initializations
 */
काष्ठा mpc_group *ctcmpc_init_mpc_group(काष्ठा ctcm_priv *priv)
अणु
	काष्ठा mpc_group *grp;

	CTCM_DBF_TEXT_(MPC_SETUP, CTC_DBF_INFO,
			"Enter %s(%p)", CTCM_FUNTAIL, priv);

	grp = kzalloc(माप(काष्ठा mpc_group), GFP_KERNEL);
	अगर (grp == शून्य)
		वापस शून्य;

	grp->fsm = init_fsm("mpcg", mpcg_state_names, mpcg_event_names,
			MPCG_NR_STATES, MPCG_NR_EVENTS, mpcg_fsm,
			mpcg_fsm_len, GFP_KERNEL);
	अगर (grp->fsm == शून्य) अणु
		kमुक्त(grp);
		वापस शून्य;
	पूर्ण

	fsm_newstate(grp->fsm, MPCG_STATE_RESET);
	fsm_समय_रखोr(grp->fsm, &grp->समयr);

	grp->xid_skb =
		 __dev_alloc_skb(MPC_बफ_मानE_DEFAULT, GFP_ATOMIC | GFP_DMA);
	अगर (grp->xid_skb == शून्य) अणु
		kमुक्त_fsm(grp->fsm);
		kमुक्त(grp);
		वापस शून्य;
	पूर्ण
	/*  base xid क्रम all channels in group  */
	grp->xid_skb_data = grp->xid_skb->data;
	grp->xid_th = (काष्ठा th_header *)grp->xid_skb->data;
	skb_put_data(grp->xid_skb, &thnorm, TH_HEADER_LENGTH);

	grp->xid = (काष्ठा xid2 *)skb_tail_poपूर्णांकer(grp->xid_skb);
	skb_put_data(grp->xid_skb, &init_xid, XID2_LENGTH);
	grp->xid->xid2_adj_id = jअगरfies | 0xfff00000;
	grp->xid->xid2_sender_id = jअगरfies;

	grp->xid_id = skb_tail_poपूर्णांकer(grp->xid_skb);
	skb_put_data(grp->xid_skb, "VTAM", 4);

	grp->rcvd_xid_skb =
		__dev_alloc_skb(MPC_बफ_मानE_DEFAULT, GFP_ATOMIC|GFP_DMA);
	अगर (grp->rcvd_xid_skb == शून्य) अणु
		kमुक्त_fsm(grp->fsm);
		dev_kमुक्त_skb(grp->xid_skb);
		kमुक्त(grp);
		वापस शून्य;
	पूर्ण
	grp->rcvd_xid_data = grp->rcvd_xid_skb->data;
	grp->rcvd_xid_th = (काष्ठा th_header *)grp->rcvd_xid_skb->data;
	skb_put_data(grp->rcvd_xid_skb, &thnorm, TH_HEADER_LENGTH);
	grp->saved_xid2 = शून्य;
	priv->xid = grp->xid;
	priv->mpcg = grp;
	वापस grp;
पूर्ण

/*
 * The MPC Group Station FSM
 */

/*
 * MPC Group Station FSM actions
 * CTCM_PROTO_MPC only
 */

/**
 * NOP action क्रम statemachines
 */
अटल व्योम mpc_action_nop(fsm_instance *fi, पूर्णांक event, व्योम *arg)
अणु
पूर्ण

/*
 * invoked when the device transitions to dev_stopped
 * MPC will stop each inभागidual channel अगर a single XID failure
 * occurs, or will पूर्णांकitiate all channels be stopped अगर a GROUP
 * level failure occurs.
 */
अटल व्योम mpc_action_go_inop(fsm_instance *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा net_device  *dev = arg;
	काष्ठा ctcm_priv    *priv;
	काष्ठा mpc_group *grp;
	काष्ठा channel *wch;

	CTCM_PR_DEBUG("Enter %s: %s\n",	__func__, dev->name);

	priv  = dev->ml_priv;
	grp =  priv->mpcg;
	grp->flow_off_called = 0;
	fsm_delसमयr(&grp->समयr);
	अगर (grp->channels_terminating)
			वापस;

	grp->channels_terminating = 1;
	grp->saved_state = fsm_माला_लोtate(grp->fsm);
	fsm_newstate(grp->fsm, MPCG_STATE_INOP);
	अगर (grp->saved_state > MPCG_STATE_XID7INITF)
		CTCM_DBF_TEXT_(MPC_TRACE, CTC_DBF_NOTICE,
			"%s(%s): MPC GROUP INOPERATIVE",
				CTCM_FUNTAIL, dev->name);
	अगर ((grp->saved_state != MPCG_STATE_RESET) ||
		/* dealloc_channel has been called */
		(grp->port_persist == 0))
		fsm_delसमयr(&priv->restart_समयr);

	wch = priv->channel[CTCM_WRITE];

	चयन (grp->saved_state) अणु
	हाल MPCG_STATE_RESET:
	हाल MPCG_STATE_INOP:
	हाल MPCG_STATE_XID2INITW:
	हाल MPCG_STATE_XID0IOWAIT:
	हाल MPCG_STATE_XID2INITX:
	हाल MPCG_STATE_XID7INITW:
	हाल MPCG_STATE_XID7INITX:
	हाल MPCG_STATE_XID0IOWAIX:
	हाल MPCG_STATE_XID7INITI:
	हाल MPCG_STATE_XID7INITZ:
	हाल MPCG_STATE_XID7INITF:
		अवरोध;
	हाल MPCG_STATE_FLOWC:
	हाल MPCG_STATE_READY:
	शेष:
		tasklet_hi_schedule(&wch->ch_disc_tasklet);
	पूर्ण

	grp->xid2_tgnum = 0;
	grp->group_max_buflen = 0;  /*min of all received */
	grp->outstanding_xid2 = 0;
	grp->outstanding_xid7 = 0;
	grp->outstanding_xid7_p2 = 0;
	grp->saved_xid2 = शून्य;
	grp->xidnogood = 0;
	grp->changed_side = 0;

	grp->rcvd_xid_skb->data = grp->rcvd_xid_data;
	skb_reset_tail_poपूर्णांकer(grp->rcvd_xid_skb);
	grp->rcvd_xid_skb->len = 0;
	grp->rcvd_xid_th = (काष्ठा th_header *)grp->rcvd_xid_skb->data;
	skb_put_data(grp->rcvd_xid_skb, &thnorm, TH_HEADER_LENGTH);

	अगर (grp->send_qllc_disc == 1) अणु
		grp->send_qllc_disc = 0;
		mpc_send_qllc_discontact(dev);
	पूर्ण

	/* DO NOT issue DEV_EVENT_STOP directly out of this code */
	/* This can result in INOP of VTAM PU due to halting of  */
	/* outstanding IO which causes a sense to be वापसed	 */
	/* Only about 3 senses are allowed and then IOS/VTAM will*/
	/* become unreachable without manual पूर्णांकervention	 */
	अगर ((grp->port_persist == 1) || (grp->alloc_called)) अणु
		grp->alloc_called = 0;
		fsm_delसमयr(&priv->restart_समयr);
		fsm_addसमयr(&priv->restart_समयr, 500, DEV_EVENT_RESTART, dev);
		fsm_newstate(grp->fsm, MPCG_STATE_RESET);
		अगर (grp->saved_state > MPCG_STATE_XID7INITF)
			CTCM_DBF_TEXT_(MPC_TRACE, CTC_DBF_ALWAYS,
				"%s(%s): MPC GROUP RECOVERY SCHEDULED",
					CTCM_FUNTAIL, dev->name);
	पूर्ण अन्यथा अणु
		fsm_delसमयr(&priv->restart_समयr);
		fsm_addसमयr(&priv->restart_समयr, 500, DEV_EVENT_STOP, dev);
		fsm_newstate(grp->fsm, MPCG_STATE_RESET);
		CTCM_DBF_TEXT_(MPC_TRACE, CTC_DBF_ALWAYS,
			"%s(%s): NO MPC GROUP RECOVERY ATTEMPTED",
						CTCM_FUNTAIL, dev->name);
	पूर्ण
पूर्ण

/**
 * Handle mpc group  action समयout.
 * MPC Group Station FSM action
 * CTCM_PROTO_MPC only
 *
 * fi		An instance of an mpc_group fsm.
 * event	The event, just happened.
 * arg		Generic poपूर्णांकer, casted from net_device * upon call.
 */
अटल व्योम mpc_action_समयout(fsm_instance *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा net_device *dev = arg;
	काष्ठा ctcm_priv *priv;
	काष्ठा mpc_group *grp;
	काष्ठा channel *wch;
	काष्ठा channel *rch;

	priv = dev->ml_priv;
	grp = priv->mpcg;
	wch = priv->channel[CTCM_WRITE];
	rch = priv->channel[CTCM_READ];

	चयन (fsm_माला_लोtate(grp->fsm)) अणु
	हाल MPCG_STATE_XID2INITW:
		/* Unless there is outstanding IO on the  */
		/* channel just वापस and रुको क्रम ATTN  */
		/* पूर्णांकerrupt to begin XID negotiations	  */
		अगर ((fsm_माला_लोtate(rch->fsm) == CH_XID0_PENDING) &&
		   (fsm_माला_लोtate(wch->fsm) == CH_XID0_PENDING))
			अवरोध;
		fallthrough;
	शेष:
		fsm_event(grp->fsm, MPCG_EVENT_INOP, dev);
	पूर्ण

	CTCM_DBF_TEXT_(MPC_TRACE, CTC_DBF_DEBUG,
			"%s: dev=%s exit",
			CTCM_FUNTAIL, dev->name);
	वापस;
पूर्ण

/*
 * MPC Group Station FSM action
 * CTCM_PROTO_MPC only
 */
व्योम mpc_action_discontact(fsm_instance *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा mpcg_info   *mpcginfo   = arg;
	काष्ठा channel	   *ch	       = mpcginfo->ch;
	काष्ठा net_device  *dev;
	काष्ठा ctcm_priv   *priv;
	काष्ठा mpc_group   *grp;

	अगर (ch) अणु
		dev = ch->netdev;
		अगर (dev) अणु
			priv = dev->ml_priv;
			अगर (priv) अणु
				CTCM_DBF_TEXT_(MPC_TRACE, CTC_DBF_NOTICE,
					"%s: %s: %s\n",
					CTCM_FUNTAIL, dev->name, ch->id);
				grp = priv->mpcg;
				grp->send_qllc_disc = 1;
				fsm_event(grp->fsm, MPCG_EVENT_INOP, dev);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस;
पूर्ण

/*
 * MPC Group Station - not part of FSM
 * CTCM_PROTO_MPC only
 * called from add_channel in ctcm_मुख्य.c
 */
व्योम mpc_action_send_discontact(अचिन्हित दीर्घ thischan)
अणु
	पूर्णांक rc;
	काष्ठा channel	*ch = (काष्ठा channel *)thischan;
	अचिन्हित दीर्घ	saveflags = 0;

	spin_lock_irqsave(get_ccwdev_lock(ch->cdev), saveflags);
	rc = ccw_device_start(ch->cdev, &ch->ccw[15], 0, 0xff, 0);
	spin_unlock_irqrestore(get_ccwdev_lock(ch->cdev), saveflags);

	अगर (rc != 0) अणु
		ctcm_ccw_check_rc(ch, rc, (अक्षर *)__func__);
	पूर्ण

	वापस;
पूर्ण


/*
 * helper function of mpc FSM
 * CTCM_PROTO_MPC only
 * mpc_action_rcvd_xid7
*/
अटल पूर्णांक mpc_validate_xid(काष्ठा mpcg_info *mpcginfo)
अणु
	काष्ठा channel	   *ch	 = mpcginfo->ch;
	काष्ठा net_device  *dev  = ch->netdev;
	काष्ठा ctcm_priv   *priv = dev->ml_priv;
	काष्ठा mpc_group   *grp  = priv->mpcg;
	काष्ठा xid2	   *xid  = mpcginfo->xid;
	पूर्णांक	rc	 = 0;
	__u64	our_id   = 0;
	__u64   their_id = 0;
	पूर्णांक	len = TH_HEADER_LENGTH + PDU_HEADER_LENGTH;

	CTCM_PR_DEBUG("Enter %s: xid=%p\n", __func__, xid);

	अगर (xid == शून्य) अणु
		rc = 1;
		/* XID REJECTED: xid == शून्य */
		CTCM_DBF_TEXT_(MPC_ERROR, CTC_DBF_ERROR,
			"%s(%s): xid = NULL",
				CTCM_FUNTAIL, ch->id);
			जाओ करोne;
	पूर्ण

	CTCM_D3_DUMP((अक्षर *)xid, XID2_LENGTH);

	/*the received direction should be the opposite of ours  */
	अगर (((CHANNEL_सूचीECTION(ch->flags) == CTCM_READ) ? XID2_WRITE_SIDE :
				XID2_READ_SIDE) != xid->xid2_dlc_type) अणु
		rc = 2;
		/* XID REJECTED: r/w channel pairing mismatch */
		CTCM_DBF_TEXT_(MPC_ERROR, CTC_DBF_ERROR,
			"%s(%s): r/w channel pairing mismatch",
				CTCM_FUNTAIL, ch->id);
			जाओ करोne;
	पूर्ण

	अगर (xid->xid2_dlc_type == XID2_READ_SIDE) अणु
		CTCM_PR_DEBUG("%s: grpmaxbuf:%d xid2buflen:%d\n", __func__,
				grp->group_max_buflen, xid->xid2_buf_len);

		अगर (grp->group_max_buflen == 0 || grp->group_max_buflen >
						xid->xid2_buf_len - len)
			grp->group_max_buflen = xid->xid2_buf_len - len;
	पूर्ण

	अगर (grp->saved_xid2 == शून्य) अणु
		grp->saved_xid2 =
			(काष्ठा xid2 *)skb_tail_poपूर्णांकer(grp->rcvd_xid_skb);

		skb_put_data(grp->rcvd_xid_skb, xid, XID2_LENGTH);
		grp->rcvd_xid_skb->data = grp->rcvd_xid_data;

		skb_reset_tail_poपूर्णांकer(grp->rcvd_xid_skb);
		grp->rcvd_xid_skb->len = 0;

		/* convert two 32 bit numbers पूर्णांकo 1 64 bit क्रम id compare */
		our_id = (__u64)priv->xid->xid2_adj_id;
		our_id = our_id << 32;
		our_id = our_id + priv->xid->xid2_sender_id;
		their_id = (__u64)xid->xid2_adj_id;
		their_id = their_id << 32;
		their_id = their_id + xid->xid2_sender_id;
		/* lower id assume the xside role */
		अगर (our_id < their_id) अणु
			grp->roll = XSIDE;
			CTCM_DBF_TEXT_(MPC_TRACE, CTC_DBF_NOTICE,
				"%s(%s): WE HAVE LOW ID - TAKE XSIDE",
					CTCM_FUNTAIL, ch->id);
		पूर्ण अन्यथा अणु
			grp->roll = YSIDE;
			CTCM_DBF_TEXT_(MPC_TRACE, CTC_DBF_NOTICE,
				"%s(%s): WE HAVE HIGH ID - TAKE YSIDE",
					CTCM_FUNTAIL, ch->id);
		पूर्ण

	पूर्ण अन्यथा अणु
		अगर (xid->xid2_flag4 != grp->saved_xid2->xid2_flag4) अणु
			rc = 3;
			/* XID REJECTED: xid flag byte4 mismatch */
			CTCM_DBF_TEXT_(MPC_ERROR, CTC_DBF_ERROR,
				"%s(%s): xid flag byte4 mismatch",
					CTCM_FUNTAIL, ch->id);
		पूर्ण
		अगर (xid->xid2_flag2 == 0x40) अणु
			rc = 4;
			/* XID REJECTED - xid NOGOOD */
			CTCM_DBF_TEXT_(MPC_ERROR, CTC_DBF_ERROR,
				"%s(%s): xid NOGOOD",
					CTCM_FUNTAIL, ch->id);
		पूर्ण
		अगर (xid->xid2_adj_id != grp->saved_xid2->xid2_adj_id) अणु
			rc = 5;
			/* XID REJECTED - Adjacent Station ID Mismatch */
			CTCM_DBF_TEXT_(MPC_ERROR, CTC_DBF_ERROR,
				"%s(%s): Adjacent Station ID Mismatch",
					CTCM_FUNTAIL, ch->id);
		पूर्ण
		अगर (xid->xid2_sender_id != grp->saved_xid2->xid2_sender_id) अणु
			rc = 6;
			/* XID REJECTED - Sender Address Mismatch */
			CTCM_DBF_TEXT_(MPC_ERROR, CTC_DBF_ERROR,
				"%s(%s): Sender Address Mismatch",
					CTCM_FUNTAIL, ch->id);
		पूर्ण
	पूर्ण
करोne:
	अगर (rc) अणु
		dev_warn(&dev->dev,
			"The XID used in the MPC protocol is not valid, "
			"rc = %d\n", rc);
		priv->xid->xid2_flag2 = 0x40;
		grp->saved_xid2->xid2_flag2 = 0x40;
	पूर्ण

	वापस rc;
पूर्ण

/*
 * MPC Group Station FSM action
 * CTCM_PROTO_MPC only
 */
अटल व्योम mpc_action_side_xid(fsm_instance *fsm, व्योम *arg, पूर्णांक side)
अणु
	काष्ठा channel *ch = arg;
	पूर्णांक rc = 0;
	पूर्णांक gotlock = 0;
	अचिन्हित दीर्घ saveflags = 0;	/* aव्योमs compiler warning with
					   spin_unlock_irqrestore */

	CTCM_PR_DEBUG("Enter %s: cp=%i ch=0x%p id=%s\n",
			__func__, smp_processor_id(), ch, ch->id);

	अगर (ctcm_checkalloc_buffer(ch))
					जाओ करोne;

	/*
	 * skb data-buffer referencing:
	 */
	ch->trans_skb->data = ch->trans_skb_data;
	skb_reset_tail_poपूर्णांकer(ch->trans_skb);
	ch->trans_skb->len = 0;
	/* result of the previous 3 statements is NOT always
	 * alपढ़ोy set after ctcm_checkalloc_buffer
	 * because of possible reuse of the trans_skb
	 */
	स_रखो(ch->trans_skb->data, 0, 16);
	ch->rcvd_xid_th =  (काष्ठा th_header *)ch->trans_skb_data;
	/* check is मुख्य purpose here: */
	skb_put(ch->trans_skb, TH_HEADER_LENGTH);
	ch->rcvd_xid = (काष्ठा xid2 *)skb_tail_poपूर्णांकer(ch->trans_skb);
	/* check is मुख्य purpose here: */
	skb_put(ch->trans_skb, XID2_LENGTH);
	ch->rcvd_xid_id = skb_tail_poपूर्णांकer(ch->trans_skb);
	/* cleanup back to startpoपूर्णांक */
	ch->trans_skb->data = ch->trans_skb_data;
	skb_reset_tail_poपूर्णांकer(ch->trans_skb);
	ch->trans_skb->len = 0;

	/* non-checking reग_लिखो of above skb data-buffer referencing: */
	/*
	स_रखो(ch->trans_skb->data, 0, 16);
	ch->rcvd_xid_th =  (काष्ठा th_header *)ch->trans_skb_data;
	ch->rcvd_xid = (काष्ठा xid2 *)(ch->trans_skb_data + TH_HEADER_LENGTH);
	ch->rcvd_xid_id = ch->trans_skb_data + TH_HEADER_LENGTH + XID2_LENGTH;
	 */

	ch->ccw[8].flags	= CCW_FLAG_SLI | CCW_FLAG_CC;
	ch->ccw[8].count	= 0;
	ch->ccw[8].cda		= 0x00;

	अगर (!(ch->xid_th && ch->xid && ch->xid_id))
		CTCM_DBF_TEXT_(MPC_TRACE, CTC_DBF_INFO,
			"%s(%s): xid_th=%p, xid=%p, xid_id=%p",
			CTCM_FUNTAIL, ch->id, ch->xid_th, ch->xid, ch->xid_id);

	अगर (side == XSIDE) अणु
		/* mpc_action_xside_xid */
		अगर (ch->xid_th == शून्य)
				जाओ करोne;
		ch->ccw[9].cmd_code	= CCW_CMD_WRITE;
		ch->ccw[9].flags	= CCW_FLAG_SLI | CCW_FLAG_CC;
		ch->ccw[9].count	= TH_HEADER_LENGTH;
		ch->ccw[9].cda		= virt_to_phys(ch->xid_th);

		अगर (ch->xid == शून्य)
				जाओ करोne;
		ch->ccw[10].cmd_code	= CCW_CMD_WRITE;
		ch->ccw[10].flags	= CCW_FLAG_SLI | CCW_FLAG_CC;
		ch->ccw[10].count	= XID2_LENGTH;
		ch->ccw[10].cda		= virt_to_phys(ch->xid);

		ch->ccw[11].cmd_code	= CCW_CMD_READ;
		ch->ccw[11].flags	= CCW_FLAG_SLI | CCW_FLAG_CC;
		ch->ccw[11].count	= TH_HEADER_LENGTH;
		ch->ccw[11].cda		= virt_to_phys(ch->rcvd_xid_th);

		ch->ccw[12].cmd_code	= CCW_CMD_READ;
		ch->ccw[12].flags	= CCW_FLAG_SLI | CCW_FLAG_CC;
		ch->ccw[12].count	= XID2_LENGTH;
		ch->ccw[12].cda		= virt_to_phys(ch->rcvd_xid);

		ch->ccw[13].cmd_code	= CCW_CMD_READ;
		ch->ccw[13].cda		= virt_to_phys(ch->rcvd_xid_id);

	पूर्ण अन्यथा अणु /* side == YSIDE : mpc_action_yside_xid */
		ch->ccw[9].cmd_code	= CCW_CMD_READ;
		ch->ccw[9].flags	= CCW_FLAG_SLI | CCW_FLAG_CC;
		ch->ccw[9].count	= TH_HEADER_LENGTH;
		ch->ccw[9].cda		= virt_to_phys(ch->rcvd_xid_th);

		ch->ccw[10].cmd_code	= CCW_CMD_READ;
		ch->ccw[10].flags	= CCW_FLAG_SLI | CCW_FLAG_CC;
		ch->ccw[10].count	= XID2_LENGTH;
		ch->ccw[10].cda		= virt_to_phys(ch->rcvd_xid);

		अगर (ch->xid_th == शून्य)
				जाओ करोne;
		ch->ccw[11].cmd_code	= CCW_CMD_WRITE;
		ch->ccw[11].flags	= CCW_FLAG_SLI | CCW_FLAG_CC;
		ch->ccw[11].count	= TH_HEADER_LENGTH;
		ch->ccw[11].cda		= virt_to_phys(ch->xid_th);

		अगर (ch->xid == शून्य)
				जाओ करोne;
		ch->ccw[12].cmd_code	= CCW_CMD_WRITE;
		ch->ccw[12].flags	= CCW_FLAG_SLI | CCW_FLAG_CC;
		ch->ccw[12].count	= XID2_LENGTH;
		ch->ccw[12].cda		= virt_to_phys(ch->xid);

		अगर (ch->xid_id == शून्य)
				जाओ करोne;
		ch->ccw[13].cmd_code	= CCW_CMD_WRITE;
		ch->ccw[13].cda		= virt_to_phys(ch->xid_id);

	पूर्ण
	ch->ccw[13].flags	= CCW_FLAG_SLI | CCW_FLAG_CC;
	ch->ccw[13].count	= 4;

	ch->ccw[14].cmd_code	= CCW_CMD_NOOP;
	ch->ccw[14].flags	= CCW_FLAG_SLI;
	ch->ccw[14].count	= 0;
	ch->ccw[14].cda		= 0;

	CTCM_CCW_DUMP((अक्षर *)&ch->ccw[8], माप(काष्ठा ccw1) * 7);
	CTCM_D3_DUMP((अक्षर *)ch->xid_th, TH_HEADER_LENGTH);
	CTCM_D3_DUMP((अक्षर *)ch->xid, XID2_LENGTH);
	CTCM_D3_DUMP((अक्षर *)ch->xid_id, 4);

	अगर (!in_irq()) अणु
			 /* Such conditional locking is a known problem क्रम
			  * sparse because its अटल undeterministic.
			  * Warnings should be ignored here. */
		spin_lock_irqsave(get_ccwdev_lock(ch->cdev), saveflags);
		gotlock = 1;
	पूर्ण

	fsm_addसमयr(&ch->समयr, 5000 , CTC_EVENT_TIMER, ch);
	rc = ccw_device_start(ch->cdev, &ch->ccw[8], 0, 0xff, 0);

	अगर (gotlock)	/* see remark above about conditional locking */
		spin_unlock_irqrestore(get_ccwdev_lock(ch->cdev), saveflags);

	अगर (rc != 0) अणु
		ctcm_ccw_check_rc(ch, rc,
				(side == XSIDE) ? "x-side XID" : "y-side XID");
	पूर्ण

करोne:
	CTCM_PR_DEBUG("Exit %s: ch=0x%p id=%s\n",
				__func__, ch, ch->id);
	वापस;

पूर्ण

/*
 * MPC Group Station FSM action
 * CTCM_PROTO_MPC only
 */
अटल व्योम mpc_action_xside_xid(fsm_instance *fsm, पूर्णांक event, व्योम *arg)
अणु
	mpc_action_side_xid(fsm, arg, XSIDE);
पूर्ण

/*
 * MPC Group Station FSM action
 * CTCM_PROTO_MPC only
 */
अटल व्योम mpc_action_yside_xid(fsm_instance *fsm, पूर्णांक event, व्योम *arg)
अणु
	mpc_action_side_xid(fsm, arg, YSIDE);
पूर्ण

/*
 * MPC Group Station FSM action
 * CTCM_PROTO_MPC only
 */
अटल व्योम mpc_action_करोxid0(fsm_instance *fsm, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा channel	   *ch   = arg;
	काष्ठा net_device  *dev  = ch->netdev;
	काष्ठा ctcm_priv   *priv = dev->ml_priv;
	काष्ठा mpc_group   *grp  = priv->mpcg;

	CTCM_PR_DEBUG("Enter %s: cp=%i ch=0x%p id=%s\n",
			__func__, smp_processor_id(), ch, ch->id);

	अगर (ch->xid == शून्य) अणु
		CTCM_DBF_TEXT_(MPC_ERROR, CTC_DBF_ERROR,
			"%s(%s): ch->xid == NULL",
				CTCM_FUNTAIL, dev->name);
		वापस;
	पूर्ण

	fsm_newstate(ch->fsm, CH_XID0_INPROGRESS);

	ch->xid->xid2_option =	XID2_0;

	चयन (fsm_माला_लोtate(grp->fsm)) अणु
	हाल MPCG_STATE_XID2INITW:
	हाल MPCG_STATE_XID2INITX:
		ch->ccw[8].cmd_code = CCW_CMD_SENSE_CMD;
		अवरोध;
	हाल MPCG_STATE_XID0IOWAIT:
	हाल MPCG_STATE_XID0IOWAIX:
		ch->ccw[8].cmd_code = CCW_CMD_WRITE_CTL;
		अवरोध;
	पूर्ण

	fsm_event(grp->fsm, MPCG_EVENT_DOIO, ch);

	वापस;
पूर्ण

/*
 * MPC Group Station FSM action
 * CTCM_PROTO_MPC only
*/
अटल व्योम mpc_action_करोxid7(fsm_instance *fsm, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा net_device *dev = arg;
	काष्ठा ctcm_priv  *priv = dev->ml_priv;
	काष्ठा mpc_group  *grp  = शून्य;
	पूर्णांक direction;
	पूर्णांक send = 0;

	अगर (priv)
		grp = priv->mpcg;
	अगर (grp == शून्य)
		वापस;

	क्रम (direction = CTCM_READ; direction <= CTCM_WRITE; direction++) अणु
		काष्ठा channel *ch = priv->channel[direction];
		काष्ठा xid2 *thisxid = ch->xid;
		ch->xid_skb->data = ch->xid_skb_data;
		skb_reset_tail_poपूर्णांकer(ch->xid_skb);
		ch->xid_skb->len = 0;
		thisxid->xid2_option = XID2_7;
		send = 0;

		/* xid7 phase 1 */
		अगर (grp->outstanding_xid7_p2 > 0) अणु
			अगर (grp->roll == YSIDE) अणु
				अगर (fsm_माला_लोtate(ch->fsm) == CH_XID7_PENDING1) अणु
					fsm_newstate(ch->fsm, CH_XID7_PENDING2);
					ch->ccw[8].cmd_code = CCW_CMD_SENSE_CMD;
					skb_put_data(ch->xid_skb, &thdummy,
						     TH_HEADER_LENGTH);
					send = 1;
				पूर्ण
			पूर्ण अन्यथा अगर (fsm_माला_लोtate(ch->fsm) < CH_XID7_PENDING2) अणु
					fsm_newstate(ch->fsm, CH_XID7_PENDING2);
					ch->ccw[8].cmd_code = CCW_CMD_WRITE_CTL;
					skb_put_data(ch->xid_skb, &thnorm,
						     TH_HEADER_LENGTH);
					send = 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* xid7 phase 2 */
			अगर (grp->roll == YSIDE) अणु
				अगर (fsm_माला_लोtate(ch->fsm) < CH_XID7_PENDING4) अणु
					fsm_newstate(ch->fsm, CH_XID7_PENDING4);
					skb_put_data(ch->xid_skb, &thnorm,
						     TH_HEADER_LENGTH);
					ch->ccw[8].cmd_code = CCW_CMD_WRITE_CTL;
					send = 1;
				पूर्ण
			पूर्ण अन्यथा अगर (fsm_माला_लोtate(ch->fsm) == CH_XID7_PENDING3) अणु
				fsm_newstate(ch->fsm, CH_XID7_PENDING4);
				ch->ccw[8].cmd_code = CCW_CMD_SENSE_CMD;
				skb_put_data(ch->xid_skb, &thdummy,
					     TH_HEADER_LENGTH);
				send = 1;
			पूर्ण
		पूर्ण

		अगर (send)
			fsm_event(grp->fsm, MPCG_EVENT_DOIO, ch);
	पूर्ण

	वापस;
पूर्ण

/*
 * MPC Group Station FSM action
 * CTCM_PROTO_MPC only
 */
अटल व्योम mpc_action_rcvd_xid0(fsm_instance *fsm, पूर्णांक event, व्योम *arg)
अणु

	काष्ठा mpcg_info   *mpcginfo  = arg;
	काष्ठा channel	   *ch   = mpcginfo->ch;
	काष्ठा net_device  *dev  = ch->netdev;
	काष्ठा ctcm_priv   *priv = dev->ml_priv;
	काष्ठा mpc_group   *grp  = priv->mpcg;

	CTCM_PR_DEBUG("%s: ch-id:%s xid2:%i xid7:%i xidt_p2:%i \n",
			__func__, ch->id, grp->outstanding_xid2,
			grp->outstanding_xid7, grp->outstanding_xid7_p2);

	अगर (fsm_माला_लोtate(ch->fsm) < CH_XID7_PENDING)
		fsm_newstate(ch->fsm, CH_XID7_PENDING);

	grp->outstanding_xid2--;
	grp->outstanding_xid7++;
	grp->outstanding_xid7_p2++;

	/* must change state beक्रमe validating xid to */
	/* properly handle पूर्णांकerim पूर्णांकerrupts received*/
	चयन (fsm_माला_लोtate(grp->fsm)) अणु
	हाल MPCG_STATE_XID2INITW:
		fsm_newstate(grp->fsm, MPCG_STATE_XID2INITX);
		mpc_validate_xid(mpcginfo);
		अवरोध;
	हाल MPCG_STATE_XID0IOWAIT:
		fsm_newstate(grp->fsm, MPCG_STATE_XID0IOWAIX);
		mpc_validate_xid(mpcginfo);
		अवरोध;
	हाल MPCG_STATE_XID2INITX:
		अगर (grp->outstanding_xid2 == 0) अणु
			fsm_newstate(grp->fsm, MPCG_STATE_XID7INITW);
			mpc_validate_xid(mpcginfo);
			fsm_event(grp->fsm, MPCG_EVENT_XID2DONE, dev);
		पूर्ण
		अवरोध;
	हाल MPCG_STATE_XID0IOWAIX:
		अगर (grp->outstanding_xid2 == 0) अणु
			fsm_newstate(grp->fsm, MPCG_STATE_XID7INITI);
			mpc_validate_xid(mpcginfo);
			fsm_event(grp->fsm, MPCG_EVENT_XID2DONE, dev);
		पूर्ण
		अवरोध;
	पूर्ण
	kमुक्त(mpcginfo);

	CTCM_PR_DEBUG("ctcmpc:%s() %s xid2:%i xid7:%i xidt_p2:%i \n",
		__func__, ch->id, grp->outstanding_xid2,
		grp->outstanding_xid7, grp->outstanding_xid7_p2);
	CTCM_PR_DEBUG("ctcmpc:%s() %s grpstate: %s chanstate: %s \n",
		__func__, ch->id,
		fsm_माला_लोtate_str(grp->fsm), fsm_माला_लोtate_str(ch->fsm));
	वापस;

पूर्ण


/*
 * MPC Group Station FSM action
 * CTCM_PROTO_MPC only
 */
अटल व्योम mpc_action_rcvd_xid7(fsm_instance *fsm, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा mpcg_info   *mpcginfo   = arg;
	काष्ठा channel	   *ch	       = mpcginfo->ch;
	काष्ठा net_device  *dev        = ch->netdev;
	काष्ठा ctcm_priv   *priv    = dev->ml_priv;
	काष्ठा mpc_group   *grp     = priv->mpcg;

	CTCM_PR_DEBUG("Enter %s: cp=%i ch=0x%p id=%s\n",
		__func__, smp_processor_id(), ch, ch->id);
	CTCM_PR_DEBUG("%s: outstanding_xid7: %i, outstanding_xid7_p2: %i\n",
		__func__, grp->outstanding_xid7, grp->outstanding_xid7_p2);

	grp->outstanding_xid7--;
	ch->xid_skb->data = ch->xid_skb_data;
	skb_reset_tail_poपूर्णांकer(ch->xid_skb);
	ch->xid_skb->len = 0;

	चयन (fsm_माला_लोtate(grp->fsm)) अणु
	हाल MPCG_STATE_XID7INITI:
		fsm_newstate(grp->fsm, MPCG_STATE_XID7INITZ);
		mpc_validate_xid(mpcginfo);
		अवरोध;
	हाल MPCG_STATE_XID7INITW:
		fsm_newstate(grp->fsm, MPCG_STATE_XID7INITX);
		mpc_validate_xid(mpcginfo);
		अवरोध;
	हाल MPCG_STATE_XID7INITZ:
	हाल MPCG_STATE_XID7INITX:
		अगर (grp->outstanding_xid7 == 0) अणु
			अगर (grp->outstanding_xid7_p2 > 0) अणु
				grp->outstanding_xid7 =
					grp->outstanding_xid7_p2;
				grp->outstanding_xid7_p2 = 0;
			पूर्ण अन्यथा
				fsm_newstate(grp->fsm, MPCG_STATE_XID7INITF);

			mpc_validate_xid(mpcginfo);
			fsm_event(grp->fsm, MPCG_EVENT_XID7DONE, dev);
			अवरोध;
		पूर्ण
		mpc_validate_xid(mpcginfo);
		अवरोध;
	पूर्ण
	kमुक्त(mpcginfo);
	वापस;
पूर्ण

/*
 * mpc_action helper of an MPC Group Station FSM action
 * CTCM_PROTO_MPC only
 */
अटल पूर्णांक mpc_send_qllc_discontact(काष्ठा net_device *dev)
अणु
	काष्ठा sk_buff   *skb;
	काष्ठा qllc      *qllcptr;
	काष्ठा ctcm_priv *priv = dev->ml_priv;
	काष्ठा mpc_group *grp = priv->mpcg;

	CTCM_PR_DEBUG("%s: GROUP STATE: %s\n",
		__func__, mpcg_state_names[grp->saved_state]);

	चयन (grp->saved_state) अणु
	/*
	 * establish conn callback function is
	 * preferred method to report failure
	 */
	हाल MPCG_STATE_XID0IOWAIT:
	हाल MPCG_STATE_XID0IOWAIX:
	हाल MPCG_STATE_XID7INITI:
	हाल MPCG_STATE_XID7INITZ:
	हाल MPCG_STATE_XID2INITW:
	हाल MPCG_STATE_XID2INITX:
	हाल MPCG_STATE_XID7INITW:
	हाल MPCG_STATE_XID7INITX:
		अगर (grp->estconnfunc) अणु
			grp->estconnfunc(grp->port_num, -1, 0);
			grp->estconnfunc = शून्य;
			अवरोध;
		पूर्ण
		fallthrough;
	हाल MPCG_STATE_FLOWC:
	हाल MPCG_STATE_READY:
		grp->send_qllc_disc = 2;

		skb = __dev_alloc_skb(माप(काष्ठा qllc), GFP_ATOMIC);
		अगर (skb == शून्य) अणु
			CTCM_DBF_TEXT_(MPC_ERROR, CTC_DBF_ERROR,
				"%s(%s): skb allocation error",
						CTCM_FUNTAIL, dev->name);
			priv->stats.rx_dropped++;
			वापस -ENOMEM;
		पूर्ण

		qllcptr = skb_put(skb, माप(काष्ठा qllc));
		qllcptr->qllc_address = 0xcc;
		qllcptr->qllc_commands = 0x03;

		अगर (skb_headroom(skb) < 4) अणु
			CTCM_DBF_TEXT_(MPC_ERROR, CTC_DBF_ERROR,
				"%s(%s): skb_headroom error",
						CTCM_FUNTAIL, dev->name);
			dev_kमुक्त_skb_any(skb);
			वापस -ENOMEM;
		पूर्ण

		*((__u32 *)skb_push(skb, 4)) =
			priv->channel[CTCM_READ]->pdu_seq;
		priv->channel[CTCM_READ]->pdu_seq++;
		CTCM_PR_DBGDATA("ctcmpc: %s ToDCM_pdu_seq= %08x\n",
				__func__, priv->channel[CTCM_READ]->pdu_seq);

		/* receipt of CC03 resets anticipated sequence number on
		      receiving side */
		priv->channel[CTCM_READ]->pdu_seq = 0x00;
		skb_reset_mac_header(skb);
		skb->dev = dev;
		skb->protocol = htons(ETH_P_SNAP);
		skb->ip_summed = CHECKSUM_UNNECESSARY;

		CTCM_D3_DUMP(skb->data, (माप(काष्ठा qllc) + 4));

		netअगर_rx(skb);
		अवरोध;
	शेष:
		अवरोध;

	पूर्ण

	वापस 0;
पूर्ण
/* --- This is the END my मित्र --- */

