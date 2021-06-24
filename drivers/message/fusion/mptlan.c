<शैली गुरु>
/*
 *  linux/drivers/message/fusion/mptlan.c
 *      IP Over Fibre Channel device driver.
 *      For use with LSI Fibre Channel PCI chip/adapters
 *      running LSI Fusion MPT (Message Passing Technology) firmware.
 *
 *  Copyright (c) 2000-2008 LSI Corporation
 *  (mailto:DL-MPTFusionLinux@lsi.com)
 *
 */
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
    This program is मुक्त software; you can redistribute it and/or modअगरy
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; version 2 of the License.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License क्रम more details.

    NO WARRANTY
    THE PROGRAM IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OR
    CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT
    LIMITATION, ANY WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT,
    MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. Each Recipient is
    solely responsible क्रम determining the appropriateness of using and
    distributing the Program and assumes all risks associated with its
    exercise of rights under this Agreement, including but not limited to
    the risks and costs of program errors, damage to or loss of data,
    programs or equipment, and unavailability or पूर्णांकerruption of operations.

    DISCLAIMER OF LIABILITY
    NEITHER RECIPIENT NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY
    सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
    DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
    TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
    USE OR DISTRIBUTION OF THE PROGRAM OR THE EXERCISE OF ANY RIGHTS GRANTED
    HEREUNDER, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES

    You should have received a copy of the GNU General Public License
    aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 * Define statements used क्रम debugging
 */
//#घोषणा MPT_LAN_IO_DEBUG

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

#समावेश "mptlan.h"
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>

#घोषणा my_VERSION	MPT_LINUX_VERSION_COMMON
#घोषणा MYNAM		"mptlan"

MODULE_LICENSE("GPL");
MODULE_VERSION(my_VERSION);

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 * MPT LAN message sizes without variable part.
 */
#घोषणा MPT_LAN_RECEIVE_POST_REQUEST_SIZE \
	(माप(LANReceivePostRequest_t) - माप(SGE_MPI_UNION))

/*
 *  Fusion MPT LAN निजी काष्ठाures
 */

काष्ठा BufferControl अणु
	काष्ठा sk_buff	*skb;
	dma_addr_t	dma;
	अचिन्हित पूर्णांक	len;
पूर्ण;

काष्ठा mpt_lan_priv अणु
	MPT_ADAPTER *mpt_dev;
	u8 pnum; /* Port number in the IOC. This is not a Unix network port! */

	atomic_t buckets_out;		/* number of unused buckets on IOC */
	पूर्णांक bucketthresh;		/* Send more when this many left */

	पूर्णांक *mpt_txfidx; /* Free Tx Context list */
	पूर्णांक mpt_txfidx_tail;
	spinlock_t txfidx_lock;

	पूर्णांक *mpt_rxfidx; /* Free Rx Context list */
	पूर्णांक mpt_rxfidx_tail;
	spinlock_t rxfidx_lock;

	काष्ठा BufferControl *RcvCtl;	/* Receive BufferControl काष्ठाs */
	काष्ठा BufferControl *SendCtl;	/* Send BufferControl काष्ठाs */

	पूर्णांक max_buckets_out;		/* Max buckets to send to IOC */
	पूर्णांक tx_max_out;			/* IOC's Tx queue len */

	u32 total_posted;
	u32 total_received;

	काष्ठा delayed_work post_buckets_task;
	काष्ठा net_device *dev;
	अचिन्हित दीर्घ post_buckets_active;
पूर्ण;

काष्ठा mpt_lan_ohdr अणु
	u16	dtype;
	u8	daddr[FC_ALEN];
	u16	stype;
	u8	saddr[FC_ALEN];
पूर्ण;

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

/*
 *  Forward protos...
 */
अटल पूर्णांक  lan_reply (MPT_ADAPTER *ioc, MPT_FRAME_HDR *mf,
		       MPT_FRAME_HDR *reply);
अटल पूर्णांक  mpt_lan_खोलो(काष्ठा net_device *dev);
अटल पूर्णांक  mpt_lan_reset(काष्ठा net_device *dev);
अटल पूर्णांक  mpt_lan_बंद(काष्ठा net_device *dev);
अटल व्योम mpt_lan_post_receive_buckets(काष्ठा mpt_lan_priv *priv);
अटल व्योम mpt_lan_wake_post_buckets_task(काष्ठा net_device *dev,
					   पूर्णांक priority);
अटल पूर्णांक  mpt_lan_receive_post_turbo(काष्ठा net_device *dev, u32 पंचांगsg);
अटल पूर्णांक  mpt_lan_receive_post_reply(काष्ठा net_device *dev,
				       LANReceivePostReply_t *pRecvRep);
अटल पूर्णांक  mpt_lan_send_turbo(काष्ठा net_device *dev, u32 पंचांगsg);
अटल पूर्णांक  mpt_lan_send_reply(काष्ठा net_device *dev,
			       LANSendReply_t *pSendRep);
अटल पूर्णांक  mpt_lan_ioc_reset(MPT_ADAPTER *ioc, पूर्णांक reset_phase);
अटल पूर्णांक  mpt_lan_event_process(MPT_ADAPTER *ioc, EventNotअगरicationReply_t *pEvReply);
अटल अचिन्हित लघु mpt_lan_type_trans(काष्ठा sk_buff *skb,
					 काष्ठा net_device *dev);

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *  Fusion MPT LAN निजी data
 */
अटल u8 LanCtx = MPT_MAX_PROTOCOL_DRIVERS;

अटल u32 max_buckets_out = 127;
अटल u32 tx_max_out_p = 127 - 16;

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	lan_reply - Handle all data sent from the hardware.
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *	@mf: Poपूर्णांकer to original MPT request frame (शून्य अगर TurboReply)
 *	@reply: Poपूर्णांकer to MPT reply frame
 *
 *	Returns 1 indicating original alloc'd request frame ptr
 *	should be मुक्तd, or 0 अगर it shouldn't.
 */
अटल पूर्णांक
lan_reply (MPT_ADAPTER *ioc, MPT_FRAME_HDR *mf, MPT_FRAME_HDR *reply)
अणु
	काष्ठा net_device *dev = ioc->netdev;
	पूर्णांक FreeReqFrame = 0;

	dioprपूर्णांकk((KERN_INFO MYNAM ": %s/%s: Got reply.\n",
		  IOC_AND_NETDEV_NAMES_s_s(dev)));

//	dioprपूर्णांकk((KERN_INFO MYNAM "@lan_reply: mf = %p, reply = %p\n",
//			mf, reply));

	अगर (mf == शून्य) अणु
		u32 पंचांगsg = CAST_PTR_TO_U32(reply);

		dioprपूर्णांकk((KERN_INFO MYNAM ": %s/%s: @lan_reply, tmsg %08x\n",
				IOC_AND_NETDEV_NAMES_s_s(dev),
				पंचांगsg));

		चयन (GET_LAN_FORM(पंचांगsg)) अणु

		// NOTE!  (Optimization) First हाल here is now caught in
		//  mptbase.c::mpt_पूर्णांकerrupt() routine and callcack here
		//  is now skipped क्रम this हाल!
#अगर 0
		हाल LAN_REPLY_FORM_MESSAGE_CONTEXT:
//			dioprपूर्णांकk((KERN_INFO MYNAM "/lan_reply: "
//				  "MessageContext turbo reply received\n"));
			FreeReqFrame = 1;
			अवरोध;
#पूर्ण_अगर

		हाल LAN_REPLY_FORM_SEND_SINGLE:
//			dioprपूर्णांकk((MYNAM "/lan_reply: "
//				  "calling mpt_lan_send_reply (turbo)\n"));

			// Potential BUG here?
			//	FreeReqFrame = mpt_lan_send_turbo(dev, पंचांगsg);
			//  If/when mpt_lan_send_turbo would वापस 1 here,
			//  calling routine (mptbase.c|mpt_पूर्णांकerrupt)
			//  would Oops because mf has alपढ़ोy been set
			//  to शून्य.  So after वापस from this func,
			//  mpt_पूर्णांकerrupt() will attempt to put (शून्य) mf ptr
			//  item back onto its adapter FreeQ - Oops!:-(
			//  It's Ok, since mpt_lan_send_turbo() *currently*
			//  always वापसs 0, but..., just in हाल:

			(व्योम) mpt_lan_send_turbo(dev, पंचांगsg);
			FreeReqFrame = 0;

			अवरोध;

		हाल LAN_REPLY_FORM_RECEIVE_SINGLE:
//			dioprपूर्णांकk((KERN_INFO MYNAM "@lan_reply: "
//				  "rcv-Turbo = %08x\n", पंचांगsg));
			mpt_lan_receive_post_turbo(dev, पंचांगsg);
			अवरोध;

		शेष:
			prपूर्णांकk (KERN_ERR MYNAM "/lan_reply: Got a turbo reply "
				"that I don't know what to do with\n");

			/* CHECKME!  Hmmm...  FreeReqFrame is 0 here; is that right? */

			अवरोध;
		पूर्ण

		वापस FreeReqFrame;
	पूर्ण

//	msg = (u32 *) reply;
//	dioprपूर्णांकk((KERN_INFO MYNAM "@lan_reply: msg = %08x %08x %08x %08x\n",
//		  le32_to_cpu(msg[0]), le32_to_cpu(msg[1]),
//		  le32_to_cpu(msg[2]), le32_to_cpu(msg[3])));
//	dioprपूर्णांकk((KERN_INFO MYNAM "@lan_reply: Function = %02xh\n",
//		  reply->u.hdr.Function));

	चयन (reply->u.hdr.Function) अणु

	हाल MPI_FUNCTION_LAN_SEND:
	अणु
		LANSendReply_t *pSendRep;

		pSendRep = (LANSendReply_t *) reply;
		FreeReqFrame = mpt_lan_send_reply(dev, pSendRep);
		अवरोध;
	पूर्ण

	हाल MPI_FUNCTION_LAN_RECEIVE:
	अणु
		LANReceivePostReply_t *pRecvRep;

		pRecvRep = (LANReceivePostReply_t *) reply;
		अगर (pRecvRep->NumberOfContexts) अणु
			mpt_lan_receive_post_reply(dev, pRecvRep);
			अगर (!(pRecvRep->MsgFlags & MPI_MSGFLAGS_CONTINUATION_REPLY))
				FreeReqFrame = 1;
		पूर्ण अन्यथा
			dioprपूर्णांकk((KERN_INFO MYNAM "@lan_reply: zero context "
				  "ReceivePostReply received.\n"));
		अवरोध;
	पूर्ण

	हाल MPI_FUNCTION_LAN_RESET:
		/* Just a शेष reply. Might want to check it to
		 * make sure that everything went ok.
		 */
		FreeReqFrame = 1;
		अवरोध;

	हाल MPI_FUNCTION_EVENT_NOTIFICATION:
	हाल MPI_FUNCTION_EVENT_ACK:
		/*  _EVENT_NOTIFICATION should NOT come करोwn this path any more.
		 *  Should be routed to mpt_lan_event_process(), but just in हाल...
		 */
		FreeReqFrame = 1;
		अवरोध;

	शेष:
		prपूर्णांकk (KERN_ERR MYNAM "/lan_reply: Got a non-turbo "
			"reply that I don't know what to do with\n");

		/* CHECKME!  Hmmm...  FreeReqFrame is 0 here; is that right? */
		FreeReqFrame = 1;

		अवरोध;
	पूर्ण

	वापस FreeReqFrame;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
अटल पूर्णांक
mpt_lan_ioc_reset(MPT_ADAPTER *ioc, पूर्णांक reset_phase)
अणु
	काष्ठा net_device *dev = ioc->netdev;
	काष्ठा mpt_lan_priv *priv;

	अगर (dev == शून्य)
		वापस(1);
	अन्यथा
		priv = netdev_priv(dev);

	dlprपूर्णांकk((KERN_INFO MYNAM ": IOC %s_reset routed to LAN driver!\n",
			reset_phase==MPT_IOC_SETUP_RESET ? "setup" : (
			reset_phase==MPT_IOC_PRE_RESET ? "pre" : "post")));

	अगर (priv->mpt_rxfidx == शून्य)
		वापस (1);

	अगर (reset_phase == MPT_IOC_SETUP_RESET) अणु
		;
	पूर्ण अन्यथा अगर (reset_phase == MPT_IOC_PRE_RESET) अणु
		पूर्णांक i;
		अचिन्हित दीर्घ flags;

		netअगर_stop_queue(dev);

		dlprपूर्णांकk ((KERN_INFO "mptlan/ioc_reset: called netif_stop_queue for %s.\n", dev->name));

		atomic_set(&priv->buckets_out, 0);

		/* Reset Rx Free Tail index and re-populate the queue. */
		spin_lock_irqsave(&priv->rxfidx_lock, flags);
		priv->mpt_rxfidx_tail = -1;
		क्रम (i = 0; i < priv->max_buckets_out; i++)
			priv->mpt_rxfidx[++priv->mpt_rxfidx_tail] = i;
		spin_unlock_irqrestore(&priv->rxfidx_lock, flags);
	पूर्ण अन्यथा अणु
		mpt_lan_post_receive_buckets(priv);
		netअगर_wake_queue(dev);
	पूर्ण

	वापस 1;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
अटल पूर्णांक
mpt_lan_event_process(MPT_ADAPTER *ioc, EventNotअगरicationReply_t *pEvReply)
अणु
	dlprपूर्णांकk((KERN_INFO MYNAM ": MPT event routed to LAN driver!\n"));

	चयन (le32_to_cpu(pEvReply->Event)) अणु
	हाल MPI_EVENT_NONE:				/* 00 */
	हाल MPI_EVENT_LOG_DATA:			/* 01 */
	हाल MPI_EVENT_STATE_CHANGE:			/* 02 */
	हाल MPI_EVENT_UNIT_ATTENTION:			/* 03 */
	हाल MPI_EVENT_IOC_BUS_RESET:			/* 04 */
	हाल MPI_EVENT_EXT_BUS_RESET:			/* 05 */
	हाल MPI_EVENT_RESCAN:				/* 06 */
		/* Ok, करो we need to करो anything here? As far as
		   I can tell, this is when a new device माला_लो added
		   to the loop. */
	हाल MPI_EVENT_LINK_STATUS_CHANGE:		/* 07 */
	हाल MPI_EVENT_LOOP_STATE_CHANGE:		/* 08 */
	हाल MPI_EVENT_LOGOUT:				/* 09 */
	हाल MPI_EVENT_EVENT_CHANGE:			/* 0A */
	शेष:
		अवरोध;
	पूर्ण

	/*
	 *  NOTE: pEvent->AckRequired handling now करोne in mptbase.c;
	 *  Do NOT करो it here now!
	 */

	वापस 1;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
अटल पूर्णांक
mpt_lan_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा mpt_lan_priv *priv = netdev_priv(dev);
	पूर्णांक i;

	अगर (mpt_lan_reset(dev) != 0) अणु
		MPT_ADAPTER *mpt_dev = priv->mpt_dev;

		prपूर्णांकk (KERN_WARNING MYNAM "/lan_open: lan_reset failed.");

		अगर (mpt_dev->active)
			prपूर्णांकk ("The ioc is active. Perhaps it needs to be"
				" reset?\n");
		अन्यथा
			prपूर्णांकk ("The ioc in inactive, most likely in the "
				"process of being reset. Please try again in "
				"a moment.\n");
	पूर्ण

	priv->mpt_txfidx = kदो_स्मृति_array(priv->tx_max_out, माप(पूर्णांक),
					 GFP_KERNEL);
	अगर (priv->mpt_txfidx == शून्य)
		जाओ out;
	priv->mpt_txfidx_tail = -1;

	priv->SendCtl = kसुस्मृति(priv->tx_max_out, माप(काष्ठा BufferControl),
				GFP_KERNEL);
	अगर (priv->SendCtl == शून्य)
		जाओ out_mpt_txfidx;
	क्रम (i = 0; i < priv->tx_max_out; i++)
		priv->mpt_txfidx[++priv->mpt_txfidx_tail] = i;

	dlprपूर्णांकk((KERN_INFO MYNAM "@lo: Finished initializing SendCtl\n"));

	priv->mpt_rxfidx = kदो_स्मृति_array(priv->max_buckets_out, माप(पूर्णांक),
					 GFP_KERNEL);
	अगर (priv->mpt_rxfidx == शून्य)
		जाओ out_SendCtl;
	priv->mpt_rxfidx_tail = -1;

	priv->RcvCtl = kसुस्मृति(priv->max_buckets_out,
			       माप(काष्ठा BufferControl),
			       GFP_KERNEL);
	अगर (priv->RcvCtl == शून्य)
		जाओ out_mpt_rxfidx;
	क्रम (i = 0; i < priv->max_buckets_out; i++)
		priv->mpt_rxfidx[++priv->mpt_rxfidx_tail] = i;

/**/	dlprपूर्णांकk((KERN_INFO MYNAM "/lo: txfidx contains - "));
/**/	क्रम (i = 0; i < priv->tx_max_out; i++)
/**/		dlprपूर्णांकk((" %xh", priv->mpt_txfidx[i]));
/**/	dlprपूर्णांकk(("\n"));

	dlprपूर्णांकk((KERN_INFO MYNAM "/lo: Finished initializing RcvCtl\n"));

	mpt_lan_post_receive_buckets(priv);
	prपूर्णांकk(KERN_INFO MYNAM ": %s/%s: interface up & active\n",
			IOC_AND_NETDEV_NAMES_s_s(dev));

	अगर (mpt_event_रेजिस्टर(LanCtx, mpt_lan_event_process) != 0) अणु
		prपूर्णांकk (KERN_WARNING MYNAM "/lo: Unable to register for Event"
			" Notifications. This is a bad thing! We're not going "
			"to go ahead, but I'd be leery of system stability at "
			"this point.\n");
	पूर्ण

	netअगर_start_queue(dev);
	dlprपूर्णांकk((KERN_INFO MYNAM "/lo: Done.\n"));

	वापस 0;
out_mpt_rxfidx:
	kमुक्त(priv->mpt_rxfidx);
	priv->mpt_rxfidx = शून्य;
out_SendCtl:
	kमुक्त(priv->SendCtl);
	priv->SendCtl = शून्य;
out_mpt_txfidx:
	kमुक्त(priv->mpt_txfidx);
	priv->mpt_txfidx = शून्य;
out:	वापस -ENOMEM;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/* Send a LanReset message to the FW. This should result in the FW वापसing
   any buckets it still has. */
अटल पूर्णांक
mpt_lan_reset(काष्ठा net_device *dev)
अणु
	MPT_FRAME_HDR *mf;
	LANResetRequest_t *pResetReq;
	काष्ठा mpt_lan_priv *priv = netdev_priv(dev);

	mf = mpt_get_msg_frame(LanCtx, priv->mpt_dev);

	अगर (mf == शून्य) अणु
/*		dlprपूर्णांकk((KERN_ERR MYNAM "/reset: Evil funkiness abounds! "
		"Unable to allocate a request frame.\n"));
*/
		वापस -1;
	पूर्ण

	pResetReq = (LANResetRequest_t *) mf;

	pResetReq->Function	= MPI_FUNCTION_LAN_RESET;
	pResetReq->ChainOffset	= 0;
	pResetReq->Reserved	= 0;
	pResetReq->PortNumber	= priv->pnum;
	pResetReq->MsgFlags	= 0;
	pResetReq->Reserved2	= 0;

	mpt_put_msg_frame(LanCtx, priv->mpt_dev, mf);

	वापस 0;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
अटल पूर्णांक
mpt_lan_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा mpt_lan_priv *priv = netdev_priv(dev);
	MPT_ADAPTER *mpt_dev = priv->mpt_dev;
	अचिन्हित दीर्घ समयout;
	पूर्णांक i;

	dlprपूर्णांकk((KERN_INFO MYNAM ": mpt_lan_close called\n"));

	mpt_event_deरेजिस्टर(LanCtx);

	dlprपूर्णांकk((KERN_INFO MYNAM ":lan_close: Posted %d buckets "
		  "since driver was loaded, %d still out\n",
		  priv->total_posted,atomic_पढ़ो(&priv->buckets_out)));

	netअगर_stop_queue(dev);

	mpt_lan_reset(dev);

	समयout = jअगरfies + 2 * HZ;
	जबतक (atomic_पढ़ो(&priv->buckets_out) && समय_beक्रमe(jअगरfies, समयout))
		schedule_समयout_पूर्णांकerruptible(1);

	क्रम (i = 0; i < priv->max_buckets_out; i++) अणु
		अगर (priv->RcvCtl[i].skb != शून्य) अणु
/**/			dlprपूर्णांकk((KERN_INFO MYNAM "/lan_close: bucket %05x "
/**/				  "is still out\n", i));
			pci_unmap_single(mpt_dev->pcidev, priv->RcvCtl[i].dma,
					 priv->RcvCtl[i].len,
					 PCI_DMA_FROMDEVICE);
			dev_kमुक्त_skb(priv->RcvCtl[i].skb);
		पूर्ण
	पूर्ण

	kमुक्त(priv->RcvCtl);
	kमुक्त(priv->mpt_rxfidx);

	क्रम (i = 0; i < priv->tx_max_out; i++) अणु
		अगर (priv->SendCtl[i].skb != शून्य) अणु
			pci_unmap_single(mpt_dev->pcidev, priv->SendCtl[i].dma,
					 priv->SendCtl[i].len,
					 PCI_DMA_TODEVICE);
			dev_kमुक्त_skb(priv->SendCtl[i].skb);
		पूर्ण
	पूर्ण

	kमुक्त(priv->SendCtl);
	kमुक्त(priv->mpt_txfidx);

	atomic_set(&priv->buckets_out, 0);

	prपूर्णांकk(KERN_INFO MYNAM ": %s/%s: interface down & inactive\n",
			IOC_AND_NETDEV_NAMES_s_s(dev));

	वापस 0;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/* Tx समयout handler. */
अटल व्योम
mpt_lan_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा mpt_lan_priv *priv = netdev_priv(dev);
	MPT_ADAPTER *mpt_dev = priv->mpt_dev;

	अगर (mpt_dev->active) अणु
		dlprपूर्णांकk (("mptlan/tx_timeout: calling netif_wake_queue for %s.\n", dev->name));
		netअगर_wake_queue(dev);
	पूर्ण
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
//अटल अंतरभूत पूर्णांक
अटल पूर्णांक
mpt_lan_send_turbo(काष्ठा net_device *dev, u32 पंचांगsg)
अणु
	काष्ठा mpt_lan_priv *priv = netdev_priv(dev);
	MPT_ADAPTER *mpt_dev = priv->mpt_dev;
	काष्ठा sk_buff *sent;
	अचिन्हित दीर्घ flags;
	u32 ctx;

	ctx = GET_LAN_BUFFER_CONTEXT(पंचांगsg);
	sent = priv->SendCtl[ctx].skb;

	dev->stats.tx_packets++;
	dev->stats.tx_bytes += sent->len;

	dioprपूर्णांकk((KERN_INFO MYNAM ": %s/%s: @%s, skb %p sent.\n",
			IOC_AND_NETDEV_NAMES_s_s(dev),
			__func__, sent));

	priv->SendCtl[ctx].skb = शून्य;
	pci_unmap_single(mpt_dev->pcidev, priv->SendCtl[ctx].dma,
			 priv->SendCtl[ctx].len, PCI_DMA_TODEVICE);
	dev_kमुक्त_skb_irq(sent);

	spin_lock_irqsave(&priv->txfidx_lock, flags);
	priv->mpt_txfidx[++priv->mpt_txfidx_tail] = ctx;
	spin_unlock_irqrestore(&priv->txfidx_lock, flags);

	netअगर_wake_queue(dev);
	वापस 0;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
अटल पूर्णांक
mpt_lan_send_reply(काष्ठा net_device *dev, LANSendReply_t *pSendRep)
अणु
	काष्ठा mpt_lan_priv *priv = netdev_priv(dev);
	MPT_ADAPTER *mpt_dev = priv->mpt_dev;
	काष्ठा sk_buff *sent;
	अचिन्हित दीर्घ flags;
	पूर्णांक FreeReqFrame = 0;
	u32 *pContext;
	u32 ctx;
	u8 count;

	count = pSendRep->NumberOfContexts;

	dioprपूर्णांकk((KERN_INFO MYNAM ": send_reply: IOCStatus: %04x\n",
		 le16_to_cpu(pSendRep->IOCStatus)));

	/* Add check क्रम Loginfo Flag in IOCStatus */

	चयन (le16_to_cpu(pSendRep->IOCStatus) & MPI_IOCSTATUS_MASK) अणु
	हाल MPI_IOCSTATUS_SUCCESS:
		dev->stats.tx_packets += count;
		अवरोध;

	हाल MPI_IOCSTATUS_LAN_CANCELED:
	हाल MPI_IOCSTATUS_LAN_TRANSMIT_ABORTED:
		अवरोध;

	हाल MPI_IOCSTATUS_INVALID_SGL:
		dev->stats.tx_errors += count;
		prपूर्णांकk (KERN_ERR MYNAM ": %s/%s: ERROR - Invalid SGL sent to IOC!\n",
				IOC_AND_NETDEV_NAMES_s_s(dev));
		जाओ out;

	शेष:
		dev->stats.tx_errors += count;
		अवरोध;
	पूर्ण

	pContext = &pSendRep->BufferContext;

	spin_lock_irqsave(&priv->txfidx_lock, flags);
	जबतक (count > 0) अणु
		ctx = GET_LAN_BUFFER_CONTEXT(le32_to_cpu(*pContext));

		sent = priv->SendCtl[ctx].skb;
		dev->stats.tx_bytes += sent->len;

		dioprपूर्णांकk((KERN_INFO MYNAM ": %s/%s: @%s, skb %p sent.\n",
				IOC_AND_NETDEV_NAMES_s_s(dev),
				__func__, sent));

		priv->SendCtl[ctx].skb = शून्य;
		pci_unmap_single(mpt_dev->pcidev, priv->SendCtl[ctx].dma,
				 priv->SendCtl[ctx].len, PCI_DMA_TODEVICE);
		dev_kमुक्त_skb_irq(sent);

		priv->mpt_txfidx[++priv->mpt_txfidx_tail] = ctx;

		pContext++;
		count--;
	पूर्ण
	spin_unlock_irqrestore(&priv->txfidx_lock, flags);

out:
	अगर (!(pSendRep->MsgFlags & MPI_MSGFLAGS_CONTINUATION_REPLY))
		FreeReqFrame = 1;

	netअगर_wake_queue(dev);
	वापस FreeReqFrame;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
अटल netdev_tx_t
mpt_lan_sdu_send (काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा mpt_lan_priv *priv = netdev_priv(dev);
	MPT_ADAPTER *mpt_dev = priv->mpt_dev;
	MPT_FRAME_HDR *mf;
	LANSendRequest_t *pSendReq;
	SGETransaction32_t *pTrans;
	SGESimple64_t *pSimple;
	स्थिर अचिन्हित अक्षर *mac;
	dma_addr_t dma;
	अचिन्हित दीर्घ flags;
	पूर्णांक ctx;
	u16 cur_naa = 0x1000;

	dioprपूर्णांकk((KERN_INFO MYNAM ": %s called, skb_addr = %p\n",
			__func__, skb));

	spin_lock_irqsave(&priv->txfidx_lock, flags);
	अगर (priv->mpt_txfidx_tail < 0) अणु
		netअगर_stop_queue(dev);
		spin_unlock_irqrestore(&priv->txfidx_lock, flags);

		prपूर्णांकk (KERN_ERR "%s: no tx context available: %u\n",
			__func__, priv->mpt_txfidx_tail);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	mf = mpt_get_msg_frame(LanCtx, mpt_dev);
	अगर (mf == शून्य) अणु
		netअगर_stop_queue(dev);
		spin_unlock_irqrestore(&priv->txfidx_lock, flags);

		prपूर्णांकk (KERN_ERR "%s: Unable to alloc request frame\n",
			__func__);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	ctx = priv->mpt_txfidx[priv->mpt_txfidx_tail--];
	spin_unlock_irqrestore(&priv->txfidx_lock, flags);

//	dioprपूर्णांकk((KERN_INFO MYNAM ": %s/%s: Creating new msg frame (send).\n",
//			IOC_AND_NETDEV_NAMES_s_s(dev)));

	pSendReq = (LANSendRequest_t *) mf;

	/* Set the mac.raw poपूर्णांकer, since this apparently isn't getting
	 * करोne beक्रमe we get the skb. Pull the data poपूर्णांकer past the mac data.
	 */
	skb_reset_mac_header(skb);
	skb_pull(skb, 12);

        dma = pci_map_single(mpt_dev->pcidev, skb->data, skb->len,
			     PCI_DMA_TODEVICE);

	priv->SendCtl[ctx].skb = skb;
	priv->SendCtl[ctx].dma = dma;
	priv->SendCtl[ctx].len = skb->len;

	/* Message Header */
	pSendReq->Reserved    = 0;
	pSendReq->Function    = MPI_FUNCTION_LAN_SEND;
	pSendReq->ChainOffset = 0;
	pSendReq->Reserved2   = 0;
	pSendReq->MsgFlags    = 0;
	pSendReq->PortNumber  = priv->pnum;

	/* Transaction Context Element */
	pTrans = (SGETransaction32_t *) pSendReq->SG_List;

	/* No Flags, 8 bytes of Details, 32bit Context (bloody turbo replies) */
	pTrans->ContextSize   = माप(u32);
	pTrans->DetailsLength = 2 * माप(u32);
	pTrans->Flags         = 0;
	pTrans->TransactionContext = cpu_to_le32(ctx);

//	dioprपूर्णांकk((KERN_INFO MYNAM ": %s/%s: BC = %08x, skb = %p, buff = %p\n",
//			IOC_AND_NETDEV_NAMES_s_s(dev),
//			ctx, skb, skb->data));

	mac = skb_mac_header(skb);

	pTrans->TransactionDetails[0] = cpu_to_le32((cur_naa         << 16) |
						    (mac[0] <<  8) |
						    (mac[1] <<  0));
	pTrans->TransactionDetails[1] = cpu_to_le32((mac[2] << 24) |
						    (mac[3] << 16) |
						    (mac[4] <<  8) |
						    (mac[5] <<  0));

	pSimple = (SGESimple64_t *) &pTrans->TransactionDetails[2];

	/* If we ever decide to send more than one Simple SGE per LANSend, then
	   we will need to make sure that LAST_ELEMENT only माला_लो set on the
	   last one. Otherwise, bad vooकरोo and evil funkiness will commence. */
	pSimple->FlagsLength = cpu_to_le32(
			((MPI_SGE_FLAGS_LAST_ELEMENT |
			  MPI_SGE_FLAGS_END_OF_BUFFER |
			  MPI_SGE_FLAGS_SIMPLE_ELEMENT |
			  MPI_SGE_FLAGS_SYSTEM_ADDRESS |
			  MPI_SGE_FLAGS_HOST_TO_IOC |
			  MPI_SGE_FLAGS_64_BIT_ADDRESSING |
			  MPI_SGE_FLAGS_END_OF_LIST) << MPI_SGE_FLAGS_SHIFT) |
			skb->len);
	pSimple->Address.Low = cpu_to_le32((u32) dma);
	अगर (माप(dma_addr_t) > माप(u32))
		pSimple->Address.High = cpu_to_le32((u32) ((u64) dma >> 32));
	अन्यथा
		pSimple->Address.High = 0;

	mpt_put_msg_frame (LanCtx, mpt_dev, mf);
	netअगर_trans_update(dev);

	dioprपूर्णांकk((KERN_INFO MYNAM ": %s/%s: Sending packet. FlagsLength = %08x.\n",
			IOC_AND_NETDEV_NAMES_s_s(dev),
			le32_to_cpu(pSimple->FlagsLength)));

	वापस NETDEV_TX_OK;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
अटल व्योम
mpt_lan_wake_post_buckets_task(काष्ठा net_device *dev, पूर्णांक priority)
/*
 * @priority: 0 = put it on the समयr queue, 1 = put it on the immediate queue
 */
अणु
	काष्ठा mpt_lan_priv *priv = netdev_priv(dev);
	
	अगर (test_and_set_bit(0, &priv->post_buckets_active) == 0) अणु
		अगर (priority) अणु
			schedule_delayed_work(&priv->post_buckets_task, 0);
		पूर्ण अन्यथा अणु
			schedule_delayed_work(&priv->post_buckets_task, 1);
			dioprपूर्णांकk((KERN_INFO MYNAM ": post_buckets queued on "
				   "timer.\n"));
		पूर्ण
	        dioprपूर्णांकk((KERN_INFO MYNAM ": %s/%s: Queued post_buckets task.\n",
			   IOC_AND_NETDEV_NAMES_s_s(dev) ));
	पूर्ण
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
अटल पूर्णांक
mpt_lan_receive_skb(काष्ठा net_device *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा mpt_lan_priv *priv = netdev_priv(dev);

	skb->protocol = mpt_lan_type_trans(skb, dev);

	dioprपूर्णांकk((KERN_INFO MYNAM ": %s/%s: Incoming packet (%d bytes) "
		 "delivered to upper level.\n",
			IOC_AND_NETDEV_NAMES_s_s(dev), skb->len));

	dev->stats.rx_bytes += skb->len;
	dev->stats.rx_packets++;

	skb->dev = dev;
	netअगर_rx(skb);

	dioprपूर्णांकk((MYNAM "/receive_skb: %d buckets remaining\n",
		 atomic_पढ़ो(&priv->buckets_out)));

	अगर (atomic_पढ़ो(&priv->buckets_out) < priv->bucketthresh)
		mpt_lan_wake_post_buckets_task(dev, 1);

	dioprपूर्णांकk((KERN_INFO MYNAM "/receive_post_reply: %d buckets "
		  "remaining, %d received back since sod\n",
		  atomic_पढ़ो(&priv->buckets_out), priv->total_received));

	वापस 0;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
//अटल अंतरभूत पूर्णांक
अटल पूर्णांक
mpt_lan_receive_post_turbo(काष्ठा net_device *dev, u32 पंचांगsg)
अणु
	काष्ठा mpt_lan_priv *priv = netdev_priv(dev);
	MPT_ADAPTER *mpt_dev = priv->mpt_dev;
	काष्ठा sk_buff *skb, *old_skb;
	अचिन्हित दीर्घ flags;
	u32 ctx, len;

	ctx = GET_LAN_BUCKET_CONTEXT(पंचांगsg);
	skb = priv->RcvCtl[ctx].skb;

	len = GET_LAN_PACKET_LENGTH(पंचांगsg);

	अगर (len < MPT_LAN_RX_COPYBREAK) अणु
		old_skb = skb;

		skb = (काष्ठा sk_buff *)dev_alloc_skb(len);
		अगर (!skb) अणु
			prपूर्णांकk (KERN_ERR MYNAM ": %s/%s: ERROR - Can't allocate skb! (%s@%d)\n",
					IOC_AND_NETDEV_NAMES_s_s(dev),
					__खाता__, __LINE__);
			वापस -ENOMEM;
		पूर्ण

		pci_dma_sync_single_क्रम_cpu(mpt_dev->pcidev, priv->RcvCtl[ctx].dma,
					    priv->RcvCtl[ctx].len, PCI_DMA_FROMDEVICE);

		skb_copy_from_linear_data(old_skb, skb_put(skb, len), len);

		pci_dma_sync_single_क्रम_device(mpt_dev->pcidev, priv->RcvCtl[ctx].dma,
					       priv->RcvCtl[ctx].len, PCI_DMA_FROMDEVICE);
		जाओ out;
	पूर्ण

	skb_put(skb, len);

	priv->RcvCtl[ctx].skb = शून्य;

	pci_unmap_single(mpt_dev->pcidev, priv->RcvCtl[ctx].dma,
			 priv->RcvCtl[ctx].len, PCI_DMA_FROMDEVICE);

out:
	spin_lock_irqsave(&priv->rxfidx_lock, flags);
	priv->mpt_rxfidx[++priv->mpt_rxfidx_tail] = ctx;
	spin_unlock_irqrestore(&priv->rxfidx_lock, flags);

	atomic_dec(&priv->buckets_out);
	priv->total_received++;

	वापस mpt_lan_receive_skb(dev, skb);
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
अटल पूर्णांक
mpt_lan_receive_post_मुक्त(काष्ठा net_device *dev,
			  LANReceivePostReply_t *pRecvRep)
अणु
	काष्ठा mpt_lan_priv *priv = netdev_priv(dev);
	MPT_ADAPTER *mpt_dev = priv->mpt_dev;
	अचिन्हित दीर्घ flags;
	काष्ठा sk_buff *skb;
	u32 ctx;
	पूर्णांक count;
	पूर्णांक i;

	count = pRecvRep->NumberOfContexts;

/**/	dlprपूर्णांकk((KERN_INFO MYNAM "/receive_post_reply: "
		  "IOC returned %d buckets, freeing them...\n", count));

	spin_lock_irqsave(&priv->rxfidx_lock, flags);
	क्रम (i = 0; i < count; i++) अणु
		ctx = le32_to_cpu(pRecvRep->BucketContext[i]);

		skb = priv->RcvCtl[ctx].skb;

//		dlprपूर्णांकk((KERN_INFO MYNAM ": %s: dev_name = %s\n",
//				IOC_AND_NETDEV_NAMES_s_s(dev)));
//		dlprपूर्णांकk((KERN_INFO MYNAM "@rpr[2], priv = %p, buckets_out addr = %p",
//				priv, &(priv->buckets_out)));
//		dlprपूर्णांकk((KERN_INFO MYNAM "@rpr[2] TC + 3\n"));

		priv->RcvCtl[ctx].skb = शून्य;
		pci_unmap_single(mpt_dev->pcidev, priv->RcvCtl[ctx].dma,
				 priv->RcvCtl[ctx].len, PCI_DMA_FROMDEVICE);
		dev_kमुक्त_skb_any(skb);

		priv->mpt_rxfidx[++priv->mpt_rxfidx_tail] = ctx;
	पूर्ण
	spin_unlock_irqrestore(&priv->rxfidx_lock, flags);

	atomic_sub(count, &priv->buckets_out);

//	क्रम (i = 0; i < priv->max_buckets_out; i++)
//		अगर (priv->RcvCtl[i].skb != शून्य)
//			dlprपूर्णांकk((KERN_INFO MYNAM "@rpr: bucket %03x "
//				  "is still out\n", i));

/*	dlprपूर्णांकk((KERN_INFO MYNAM "/receive_post_reply: freed %d buckets\n",
		  count));
*/
/**/	dlprपूर्णांकk((KERN_INFO MYNAM "@receive_post_reply: %d buckets "
/**/		  "remaining, %d received back since sod.\n",
/**/		  atomic_पढ़ो(&priv->buckets_out), priv->total_received));
	वापस 0;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
अटल पूर्णांक
mpt_lan_receive_post_reply(काष्ठा net_device *dev,
			   LANReceivePostReply_t *pRecvRep)
अणु
	काष्ठा mpt_lan_priv *priv = netdev_priv(dev);
	MPT_ADAPTER *mpt_dev = priv->mpt_dev;
	काष्ठा sk_buff *skb, *old_skb;
	अचिन्हित दीर्घ flags;
	u32 len, ctx, offset;
	u32 reमुख्यing = le32_to_cpu(pRecvRep->BucketsReमुख्यing);
	पूर्णांक count;
	पूर्णांक i, l;

	dioprपूर्णांकk((KERN_INFO MYNAM ": mpt_lan_receive_post_reply called\n"));
	dioprपूर्णांकk((KERN_INFO MYNAM ": receive_post_reply: IOCStatus: %04x\n",
		 le16_to_cpu(pRecvRep->IOCStatus)));

	अगर ((le16_to_cpu(pRecvRep->IOCStatus) & MPI_IOCSTATUS_MASK) ==
						MPI_IOCSTATUS_LAN_CANCELED)
		वापस mpt_lan_receive_post_मुक्त(dev, pRecvRep);

	len = le32_to_cpu(pRecvRep->PacketLength);
	अगर (len == 0) अणु
		prपूर्णांकk (KERN_ERR MYNAM ": %s/%s: ERROR - Got a non-TURBO "
			"ReceivePostReply w/ PacketLength zero!\n",
				IOC_AND_NETDEV_NAMES_s_s(dev));
		prपूर्णांकk (KERN_ERR MYNAM ": MsgFlags = %02x, IOCStatus = %04x\n",
				pRecvRep->MsgFlags, le16_to_cpu(pRecvRep->IOCStatus));
		वापस -1;
	पूर्ण

	ctx    = le32_to_cpu(pRecvRep->BucketContext[0]);
	count  = pRecvRep->NumberOfContexts;
	skb    = priv->RcvCtl[ctx].skb;

	offset = le32_to_cpu(pRecvRep->PacketOffset);
//	अगर (offset != 0) अणु
//		prपूर्णांकk (KERN_INFO MYNAM ": %s/%s: Got a ReceivePostReply "
//			"w/ PacketOffset %u\n",
//				IOC_AND_NETDEV_NAMES_s_s(dev),
//				offset);
//	पूर्ण

	dioprपूर्णांकk((KERN_INFO MYNAM ": %s/%s: @rpr, offset = %d, len = %d\n",
			IOC_AND_NETDEV_NAMES_s_s(dev),
			offset, len));

	अगर (count > 1) अणु
		पूर्णांक szrem = len;

//		dioprपूर्णांकk((KERN_INFO MYNAM ": %s/%s: Multiple buckets returned "
//			"for single packet, concatenating...\n",
//				IOC_AND_NETDEV_NAMES_s_s(dev)));

		skb = (काष्ठा sk_buff *)dev_alloc_skb(len);
		अगर (!skb) अणु
			prपूर्णांकk (KERN_ERR MYNAM ": %s/%s: ERROR - Can't allocate skb! (%s@%d)\n",
					IOC_AND_NETDEV_NAMES_s_s(dev),
					__खाता__, __LINE__);
			वापस -ENOMEM;
		पूर्ण

		spin_lock_irqsave(&priv->rxfidx_lock, flags);
		क्रम (i = 0; i < count; i++) अणु

			ctx = le32_to_cpu(pRecvRep->BucketContext[i]);
			old_skb = priv->RcvCtl[ctx].skb;

			l = priv->RcvCtl[ctx].len;
			अगर (szrem < l)
				l = szrem;

//			dioprपूर्णांकk((KERN_INFO MYNAM ": %s/%s: Buckets = %d, len = %u\n",
//					IOC_AND_NETDEV_NAMES_s_s(dev),
//					i, l));

			pci_dma_sync_single_क्रम_cpu(mpt_dev->pcidev,
						    priv->RcvCtl[ctx].dma,
						    priv->RcvCtl[ctx].len,
						    PCI_DMA_FROMDEVICE);
			skb_copy_from_linear_data(old_skb, skb_put(skb, l), l);

			pci_dma_sync_single_क्रम_device(mpt_dev->pcidev,
						       priv->RcvCtl[ctx].dma,
						       priv->RcvCtl[ctx].len,
						       PCI_DMA_FROMDEVICE);

			priv->mpt_rxfidx[++priv->mpt_rxfidx_tail] = ctx;
			szrem -= l;
		पूर्ण
		spin_unlock_irqrestore(&priv->rxfidx_lock, flags);

	पूर्ण अन्यथा अगर (len < MPT_LAN_RX_COPYBREAK) अणु

		old_skb = skb;

		skb = (काष्ठा sk_buff *)dev_alloc_skb(len);
		अगर (!skb) अणु
			prपूर्णांकk (KERN_ERR MYNAM ": %s/%s: ERROR - Can't allocate skb! (%s@%d)\n",
					IOC_AND_NETDEV_NAMES_s_s(dev),
					__खाता__, __LINE__);
			वापस -ENOMEM;
		पूर्ण

		pci_dma_sync_single_क्रम_cpu(mpt_dev->pcidev,
					    priv->RcvCtl[ctx].dma,
					    priv->RcvCtl[ctx].len,
					    PCI_DMA_FROMDEVICE);

		skb_copy_from_linear_data(old_skb, skb_put(skb, len), len);

		pci_dma_sync_single_क्रम_device(mpt_dev->pcidev,
					       priv->RcvCtl[ctx].dma,
					       priv->RcvCtl[ctx].len,
					       PCI_DMA_FROMDEVICE);

		spin_lock_irqsave(&priv->rxfidx_lock, flags);
		priv->mpt_rxfidx[++priv->mpt_rxfidx_tail] = ctx;
		spin_unlock_irqrestore(&priv->rxfidx_lock, flags);

	पूर्ण अन्यथा अणु
		spin_lock_irqsave(&priv->rxfidx_lock, flags);

		priv->RcvCtl[ctx].skb = शून्य;

		pci_unmap_single(mpt_dev->pcidev, priv->RcvCtl[ctx].dma,
				 priv->RcvCtl[ctx].len, PCI_DMA_FROMDEVICE);
		priv->RcvCtl[ctx].dma = 0;

		priv->mpt_rxfidx[++priv->mpt_rxfidx_tail] = ctx;
		spin_unlock_irqrestore(&priv->rxfidx_lock, flags);

		skb_put(skb,len);
	पूर्ण

	atomic_sub(count, &priv->buckets_out);
	priv->total_received += count;

	अगर (priv->mpt_rxfidx_tail >= MPT_LAN_MAX_BUCKETS_OUT) अणु
		prपूर्णांकk (KERN_ERR MYNAM ": %s/%s: Yoohoo! mpt_rxfidx_tail = %d, "
			"MPT_LAN_MAX_BUCKETS_OUT = %d\n",
				IOC_AND_NETDEV_NAMES_s_s(dev),
				priv->mpt_rxfidx_tail,
				MPT_LAN_MAX_BUCKETS_OUT);

		वापस -1;
	पूर्ण

	अगर (reमुख्यing == 0)
		prपूर्णांकk (KERN_WARNING MYNAM ": %s/%s: WARNING - IOC out of buckets! "
			"(priv->buckets_out = %d)\n",
			IOC_AND_NETDEV_NAMES_s_s(dev),
			atomic_पढ़ो(&priv->buckets_out));
	अन्यथा अगर (reमुख्यing < 10)
		prपूर्णांकk (KERN_INFO MYNAM ": %s/%s: IOC says %d buckets left. "
			"(priv->buckets_out = %d)\n",
			IOC_AND_NETDEV_NAMES_s_s(dev),
			reमुख्यing, atomic_पढ़ो(&priv->buckets_out));
	
	अगर ((reमुख्यing < priv->bucketthresh) &&
	    ((atomic_पढ़ो(&priv->buckets_out) - reमुख्यing) >
	     MPT_LAN_BUCKETS_REMAIN_MISMATCH_THRESH)) अणु
		
		prपूर्णांकk (KERN_WARNING MYNAM " Mismatch between driver's "
			"buckets_out count and fw's BucketsRemaining "
			"count has crossed the threshold, issuing a "
			"LanReset to clear the fw's hashtable. You may "
			"want to check your /var/log/messages for \"CRC "
			"error\" event notifications.\n");
		
		mpt_lan_reset(dev);
		mpt_lan_wake_post_buckets_task(dev, 0);
	पूर्ण
	
	वापस mpt_lan_receive_skb(dev, skb);
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/* Simple SGE's only at the moment */

अटल व्योम
mpt_lan_post_receive_buckets(काष्ठा mpt_lan_priv *priv)
अणु
	काष्ठा net_device *dev = priv->dev;
	MPT_ADAPTER *mpt_dev = priv->mpt_dev;
	MPT_FRAME_HDR *mf;
	LANReceivePostRequest_t *pRecvReq;
	SGETransaction32_t *pTrans;
	SGESimple64_t *pSimple;
	काष्ठा sk_buff *skb;
	dma_addr_t dma;
	u32 curr, buckets, count, max;
	u32 len = (dev->mtu + dev->hard_header_len + 4);
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	curr = atomic_पढ़ो(&priv->buckets_out);
	buckets = (priv->max_buckets_out - curr);

	dioprपूर्णांकk((KERN_INFO MYNAM ": %s/%s: @%s, Start_buckets = %u, buckets_out = %u\n",
			IOC_AND_NETDEV_NAMES_s_s(dev),
			__func__, buckets, curr));

	max = (mpt_dev->req_sz - MPT_LAN_RECEIVE_POST_REQUEST_SIZE) /
			(माप(SGETransaction32_t) + माप(SGESimple64_t));

	जबतक (buckets) अणु
		mf = mpt_get_msg_frame(LanCtx, mpt_dev);
		अगर (mf == शून्य) अणु
			prपूर्णांकk (KERN_ERR "%s: Unable to alloc request frame\n",
				__func__);
			dioprपूर्णांकk((KERN_ERR "%s: %u buckets remaining\n",
				 __func__, buckets));
			जाओ out;
		पूर्ण
		pRecvReq = (LANReceivePostRequest_t *) mf;

		i = le16_to_cpu(mf->u.frame.hwhdr.msgctxu.fld.req_idx);
		mpt_dev->RequestNB[i] = 0;
		count = buckets;
		अगर (count > max)
			count = max;

		pRecvReq->Function    = MPI_FUNCTION_LAN_RECEIVE;
		pRecvReq->ChainOffset = 0;
		pRecvReq->MsgFlags    = 0;
		pRecvReq->PortNumber  = priv->pnum;

		pTrans = (SGETransaction32_t *) pRecvReq->SG_List;
		pSimple = शून्य;

		क्रम (i = 0; i < count; i++) अणु
			पूर्णांक ctx;

			spin_lock_irqsave(&priv->rxfidx_lock, flags);
			अगर (priv->mpt_rxfidx_tail < 0) अणु
				prपूर्णांकk (KERN_ERR "%s: Can't alloc context\n",
					__func__);
				spin_unlock_irqrestore(&priv->rxfidx_lock,
						       flags);
				अवरोध;
			पूर्ण

			ctx = priv->mpt_rxfidx[priv->mpt_rxfidx_tail--];

			skb = priv->RcvCtl[ctx].skb;
			अगर (skb && (priv->RcvCtl[ctx].len != len)) अणु
				pci_unmap_single(mpt_dev->pcidev,
						 priv->RcvCtl[ctx].dma,
						 priv->RcvCtl[ctx].len,
						 PCI_DMA_FROMDEVICE);
				dev_kमुक्त_skb(priv->RcvCtl[ctx].skb);
				skb = priv->RcvCtl[ctx].skb = शून्य;
			पूर्ण

			अगर (skb == शून्य) अणु
				skb = dev_alloc_skb(len);
				अगर (skb == शून्य) अणु
					prपूर्णांकk (KERN_WARNING
						MYNAM "/%s: Can't alloc skb\n",
						__func__);
					priv->mpt_rxfidx[++priv->mpt_rxfidx_tail] = ctx;
					spin_unlock_irqrestore(&priv->rxfidx_lock, flags);
					अवरोध;
				पूर्ण

				dma = pci_map_single(mpt_dev->pcidev, skb->data,
						     len, PCI_DMA_FROMDEVICE);

				priv->RcvCtl[ctx].skb = skb;
				priv->RcvCtl[ctx].dma = dma;
				priv->RcvCtl[ctx].len = len;
			पूर्ण

			spin_unlock_irqrestore(&priv->rxfidx_lock, flags);

			pTrans->ContextSize   = माप(u32);
			pTrans->DetailsLength = 0;
			pTrans->Flags         = 0;
			pTrans->TransactionContext = cpu_to_le32(ctx);

			pSimple = (SGESimple64_t *) pTrans->TransactionDetails;

			pSimple->FlagsLength = cpu_to_le32(
				((MPI_SGE_FLAGS_END_OF_BUFFER |
				  MPI_SGE_FLAGS_SIMPLE_ELEMENT |
				  MPI_SGE_FLAGS_64_BIT_ADDRESSING) << MPI_SGE_FLAGS_SHIFT) | len);
			pSimple->Address.Low = cpu_to_le32((u32) priv->RcvCtl[ctx].dma);
			अगर (माप(dma_addr_t) > माप(u32))
				pSimple->Address.High = cpu_to_le32((u32) ((u64) priv->RcvCtl[ctx].dma >> 32));
			अन्यथा
				pSimple->Address.High = 0;

			pTrans = (SGETransaction32_t *) (pSimple + 1);
		पूर्ण

		अगर (pSimple == शून्य) अणु
/**/			prपूर्णांकk (KERN_WARNING MYNAM "/%s: No buckets posted\n",
/**/				__func__);
			mpt_मुक्त_msg_frame(mpt_dev, mf);
			जाओ out;
		पूर्ण

		pSimple->FlagsLength |= cpu_to_le32(MPI_SGE_FLAGS_END_OF_LIST << MPI_SGE_FLAGS_SHIFT);

		pRecvReq->BucketCount = cpu_to_le32(i);

/*	prपूर्णांकk(KERN_INFO MYNAM ": posting buckets\n   ");
 *	क्रम (i = 0; i < j + 2; i ++)
 *	    prपूर्णांकk (" %08x", le32_to_cpu(msg[i]));
 *	prपूर्णांकk ("\n");
 */

		mpt_put_msg_frame(LanCtx, mpt_dev, mf);

		priv->total_posted += i;
		buckets -= i;
		atomic_add(i, &priv->buckets_out);
	पूर्ण

out:
	dioprपूर्णांकk((KERN_INFO MYNAM "/%s: End_buckets = %u, priv->buckets_out = %u\n",
		  __func__, buckets, atomic_पढ़ो(&priv->buckets_out)));
	dioprपूर्णांकk((KERN_INFO MYNAM "/%s: Posted %u buckets and received %u back\n",
	__func__, priv->total_posted, priv->total_received));

	clear_bit(0, &priv->post_buckets_active);
पूर्ण

अटल व्योम
mpt_lan_post_receive_buckets_work(काष्ठा work_काष्ठा *work)
अणु
	mpt_lan_post_receive_buckets(container_of(work, काष्ठा mpt_lan_priv,
						  post_buckets_task.work));
पूर्ण

अटल स्थिर काष्ठा net_device_ops mpt_netdev_ops = अणु
	.nकरो_खोलो       = mpt_lan_खोलो,
	.nकरो_stop       = mpt_lan_बंद,
	.nकरो_start_xmit = mpt_lan_sdu_send,
	.nकरो_tx_समयout = mpt_lan_tx_समयout,
पूर्ण;

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
अटल काष्ठा net_device *
mpt_रेजिस्टर_lan_device (MPT_ADAPTER *mpt_dev, पूर्णांक pnum)
अणु
	काष्ठा net_device *dev;
	काष्ठा mpt_lan_priv *priv;
	u8 HWaddr[FC_ALEN], *a;

	dev = alloc_fcdev(माप(काष्ठा mpt_lan_priv));
	अगर (!dev)
		वापस शून्य;

	dev->mtu = MPT_LAN_MTU;

	priv = netdev_priv(dev);

	priv->dev = dev;
	priv->mpt_dev = mpt_dev;
	priv->pnum = pnum;

	INIT_DELAYED_WORK(&priv->post_buckets_task,
			  mpt_lan_post_receive_buckets_work);
	priv->post_buckets_active = 0;

	dlprपूर्णांकk((KERN_INFO MYNAM "@%d: bucketlen = %d\n",
			__LINE__, dev->mtu + dev->hard_header_len + 4));

	atomic_set(&priv->buckets_out, 0);
	priv->total_posted = 0;
	priv->total_received = 0;
	priv->max_buckets_out = max_buckets_out;
	अगर (mpt_dev->pfacts[0].MaxLanBuckets < max_buckets_out)
		priv->max_buckets_out = mpt_dev->pfacts[0].MaxLanBuckets;

	dlprपूर्णांकk((KERN_INFO MYNAM "@%d: MaxLanBuckets=%d, max_buckets_out/priv=%d/%d\n",
			__LINE__,
			mpt_dev->pfacts[0].MaxLanBuckets,
			max_buckets_out,
			priv->max_buckets_out));

	priv->bucketthresh = priv->max_buckets_out * 2 / 3;
	spin_lock_init(&priv->txfidx_lock);
	spin_lock_init(&priv->rxfidx_lock);

	/*  Grab pre-fetched LANPage1 stuff. :-) */
	a = (u8 *) &mpt_dev->lan_cnfg_page1.HardwareAddressLow;

	HWaddr[0] = a[5];
	HWaddr[1] = a[4];
	HWaddr[2] = a[3];
	HWaddr[3] = a[2];
	HWaddr[4] = a[1];
	HWaddr[5] = a[0];

	dev->addr_len = FC_ALEN;
	स_नकल(dev->dev_addr, HWaddr, FC_ALEN);
	स_रखो(dev->broadcast, 0xff, FC_ALEN);

	/* The Tx queue is 127 deep on the 909.
	 * Give ourselves some breathing room.
	 */
	priv->tx_max_out = (tx_max_out_p <= MPT_TX_MAX_OUT_LIM) ?
			    tx_max_out_p : MPT_TX_MAX_OUT_LIM;

	dev->netdev_ops = &mpt_netdev_ops;
	dev->watchकरोg_समयo = MPT_LAN_TX_TIMEOUT;

	/* MTU range: 96 - 65280 */
	dev->min_mtu = MPT_LAN_MIN_MTU;
	dev->max_mtu = MPT_LAN_MAX_MTU;

	dlprपूर्णांकk((KERN_INFO MYNAM ": Finished registering dev "
		"and setting initial values\n"));

	अगर (रेजिस्टर_netdev(dev) != 0) अणु
		मुक्त_netdev(dev);
		dev = शून्य;
	पूर्ण
	वापस dev;
पूर्ण

अटल पूर्णांक
mptlan_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	MPT_ADAPTER 		*ioc = pci_get_drvdata(pdev);
	काष्ठा net_device	*dev;
	पूर्णांक			i;

	क्रम (i = 0; i < ioc->facts.NumberOfPorts; i++) अणु
		prपूर्णांकk(KERN_INFO MYNAM ": %s: PortNum=%x, "
		       "ProtocolFlags=%02Xh (%c%c%c%c)\n",
		       ioc->name, ioc->pfacts[i].PortNumber,
		       ioc->pfacts[i].ProtocolFlags,
		       MPT_PROTOCOL_FLAGS_c_c_c_c(
			       ioc->pfacts[i].ProtocolFlags));

		अगर (!(ioc->pfacts[i].ProtocolFlags &
					MPI_PORTFACTS_PROTOCOL_LAN)) अणु
			prपूर्णांकk(KERN_INFO MYNAM ": %s: Hmmm... LAN protocol "
			       "seems to be disabled on this adapter port!\n",
			       ioc->name);
			जारी;
		पूर्ण

		dev = mpt_रेजिस्टर_lan_device(ioc, i);
		अगर (!dev) अणु
			prपूर्णांकk(KERN_ERR MYNAM ": %s: Unable to register "
			       "port%d as a LAN device\n", ioc->name,
			       ioc->pfacts[i].PortNumber);
			जारी;
		पूर्ण
		
		prपूर्णांकk(KERN_INFO MYNAM ": %s: Fusion MPT LAN device "
		       "registered as '%s'\n", ioc->name, dev->name);
		prपूर्णांकk(KERN_INFO MYNAM ": %s/%s: "
		       "LanAddr = %pM\n",
		       IOC_AND_NETDEV_NAMES_s_s(dev),
		       dev->dev_addr);
	
		ioc->netdev = dev;

		वापस 0;
	पूर्ण

	वापस -ENODEV;
पूर्ण

अटल व्योम
mptlan_हटाओ(काष्ठा pci_dev *pdev)
अणु
	MPT_ADAPTER 		*ioc = pci_get_drvdata(pdev);
	काष्ठा net_device	*dev = ioc->netdev;

	अगर(dev != शून्य) अणु
		unरेजिस्टर_netdev(dev);
		मुक्त_netdev(dev);
	पूर्ण
पूर्ण

अटल काष्ठा mpt_pci_driver mptlan_driver = अणु
	.probe		= mptlan_probe,
	.हटाओ		= mptlan_हटाओ,
पूर्ण;

अटल पूर्णांक __init mpt_lan_init (व्योम)
अणु
	show_mpपंचांगod_ver(LANAME, LANVER);

	LanCtx = mpt_रेजिस्टर(lan_reply, MPTLAN_DRIVER,
				"lan_reply");
	अगर (LanCtx <= 0) अणु
		prपूर्णांकk (KERN_ERR MYNAM ": Failed to register with MPT base driver\n");
		वापस -EBUSY;
	पूर्ण

	dlprपूर्णांकk((KERN_INFO MYNAM ": assigned context of %d\n", LanCtx));

	अगर (mpt_reset_रेजिस्टर(LanCtx, mpt_lan_ioc_reset)) अणु
		prपूर्णांकk(KERN_ERR MYNAM ": Eieee! unable to register a reset "
		       "handler with mptbase! The world is at an end! "
		       "Everything is fading to black! Goodbye.\n");
		वापस -EBUSY;
	पूर्ण

	dlprपूर्णांकk((KERN_INFO MYNAM ": Registered for IOC reset notifications\n"));
	
	mpt_device_driver_रेजिस्टर(&mptlan_driver, MPTLAN_DRIVER);
	वापस 0;
पूर्ण

अटल व्योम __निकास mpt_lan_निकास(व्योम)
अणु
	mpt_device_driver_deरेजिस्टर(MPTLAN_DRIVER);
	mpt_reset_deरेजिस्टर(LanCtx);

	अगर (LanCtx) अणु
		mpt_deरेजिस्टर(LanCtx);
		LanCtx = MPT_MAX_PROTOCOL_DRIVERS;
	पूर्ण
पूर्ण

module_init(mpt_lan_init);
module_निकास(mpt_lan_निकास);

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
अटल अचिन्हित लघु
mpt_lan_type_trans(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा mpt_lan_ohdr *fch = (काष्ठा mpt_lan_ohdr *)skb->data;
	काष्ठा fcllc *fcllc;

	skb_reset_mac_header(skb);
	skb_pull(skb, माप(काष्ठा mpt_lan_ohdr));

	अगर (fch->dtype == htons(0xffff)) अणु
		u32 *p = (u32 *) fch;

		swab32s(p + 0);
		swab32s(p + 1);
		swab32s(p + 2);
		swab32s(p + 3);

		prपूर्णांकk (KERN_WARNING MYNAM ": %s: WARNING - Broadcast swap F/W bug detected!\n",
				NETDEV_PTR_TO_IOC_NAME_s(dev));
		prपूर्णांकk (KERN_WARNING MYNAM ": Please update sender @ MAC_addr = %pM\n",
				fch->saddr);
	पूर्ण

	अगर (*fch->daddr & 1) अणु
		अगर (!स_भेद(fch->daddr, dev->broadcast, FC_ALEN)) अणु
			skb->pkt_type = PACKET_BROADCAST;
		पूर्ण अन्यथा अणु
			skb->pkt_type = PACKET_MULTICAST;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (स_भेद(fch->daddr, dev->dev_addr, FC_ALEN)) अणु
			skb->pkt_type = PACKET_OTHERHOST;
		पूर्ण अन्यथा अणु
			skb->pkt_type = PACKET_HOST;
		पूर्ण
	पूर्ण

	fcllc = (काष्ठा fcllc *)skb->data;

	/* Strip the SNAP header from ARP packets since we करोn't
	 * pass them through to the 802.2/SNAP layers.
	 */
	अगर (fcllc->dsap == EXTENDED_SAP &&
		(fcllc->ethertype == htons(ETH_P_IP) ||
		 fcllc->ethertype == htons(ETH_P_ARP))) अणु
		skb_pull(skb, माप(काष्ठा fcllc));
		वापस fcllc->ethertype;
	पूर्ण

	वापस htons(ETH_P_802_2);
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
