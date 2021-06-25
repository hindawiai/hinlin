<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause)
/* isotp.c - ISO 15765-2 CAN transport protocol क्रम protocol family CAN
 *
 * This implementation करोes not provide ISO-TP specअगरic वापस values to the
 * userspace.
 *
 * - RX path समयout of data reception leads to -ETIMEDOUT
 * - RX path SN mismatch leads to -EILSEQ
 * - RX path data reception with wrong padding leads to -EBADMSG
 * - TX path flowcontrol reception समयout leads to -ECOMM
 * - TX path flowcontrol reception overflow leads to -EMSGSIZE
 * - TX path flowcontrol reception with wrong layout/padding leads to -EBADMSG
 * - when a transfer (tx) is on the run the next ग_लिखो() blocks until it's करोne
 * - use CAN_ISOTP_WAIT_TX_DONE flag to block the caller until the PDU is sent
 * - as we have अटल buffers the check whether the PDU fits पूर्णांकo the buffer
 *   is करोne at FF reception समय (no support क्रम sending 'wait frames')
 * - take care of the tx-queue-len as traffic shaping is still on the TODO list
 *
 * Copyright (c) 2020 Volkswagen Group Electronic Research
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. Neither the name of Volkswagen nor the names of its contributors
 *    may be used to enकरोrse or promote products derived from this software
 *    without specअगरic prior written permission.
 *
 * Alternatively, provided that this notice is retained in full, this
 * software may be distributed under the terms of the GNU General
 * Public License ("GPL") version 2, in which हाल the provisions of the
 * GPL apply INSTEAD OF those given above.
 *
 * The provided data काष्ठाures and बाह्यal पूर्णांकerfaces from this code
 * are not restricted to be used by modules with a GPL compatible license.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/रुको.h>
#समावेश <linux/uपन.स>
#समावेश <linux/net.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/socket.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/can.h>
#समावेश <linux/can/core.h>
#समावेश <linux/can/skb.h>
#समावेश <linux/can/isotp.h>
#समावेश <linux/slab.h>
#समावेश <net/sock.h>
#समावेश <net/net_namespace.h>

MODULE_DESCRIPTION("PF_CAN isotp 15765-2:2016 protocol");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Oliver Hartkopp <socketcan@hartkopp.net>");
MODULE_ALIAS("can-proto-6");

#घोषणा ISOTP_MIN_NAMELEN CAN_REQUIRED_SIZE(काष्ठा sockaddr_can, can_addr.tp)

#घोषणा SINGLE_MASK(id) (((id) & CAN_EFF_FLAG) ? \
			 (CAN_EFF_MASK | CAN_EFF_FLAG | CAN_RTR_FLAG) : \
			 (CAN_SFF_MASK | CAN_EFF_FLAG | CAN_RTR_FLAG))

/* ISO 15765-2:2016 supports more than 4095 byte per ISO PDU as the FF_DL can
 * take full 32 bit values (4 Gbyte). We would need some good concept to handle
 * this between user space and kernel space. For now increase the अटल buffer
 * to something about 8 kbyte to be able to test this new functionality.
 */
#घोषणा MAX_MSG_LENGTH 8200

/* N_PCI type values in bits 7-4 of N_PCI bytes */
#घोषणा N_PCI_SF 0x00	/* single frame */
#घोषणा N_PCI_FF 0x10	/* first frame */
#घोषणा N_PCI_CF 0x20	/* consecutive frame */
#घोषणा N_PCI_FC 0x30	/* flow control */

#घोषणा N_PCI_SZ 1	/* size of the PCI byte #1 */
#घोषणा SF_PCI_SZ4 1	/* size of SingleFrame PCI including 4 bit SF_DL */
#घोषणा SF_PCI_SZ8 2	/* size of SingleFrame PCI including 8 bit SF_DL */
#घोषणा FF_PCI_SZ12 2	/* size of FirstFrame PCI including 12 bit FF_DL */
#घोषणा FF_PCI_SZ32 6	/* size of FirstFrame PCI including 32 bit FF_DL */
#घोषणा FC_CONTENT_SZ 3	/* flow control content size in byte (FS/BS/STmin) */

#घोषणा ISOTP_CHECK_PADDING (CAN_ISOTP_CHK_PAD_LEN | CAN_ISOTP_CHK_PAD_DATA)

/* Flow Status given in FC frame */
#घोषणा ISOTP_FC_CTS 0		/* clear to send */
#घोषणा ISOTP_FC_WT 1		/* रुको */
#घोषणा ISOTP_FC_OVFLW 2	/* overflow */

क्रमागत अणु
	ISOTP_IDLE = 0,
	ISOTP_WAIT_FIRST_FC,
	ISOTP_WAIT_FC,
	ISOTP_WAIT_DATA,
	ISOTP_SENDING
पूर्ण;

काष्ठा tpcon अणु
	पूर्णांक idx;
	पूर्णांक len;
	u8 state;
	u8 bs;
	u8 sn;
	u8 ll_dl;
	u8 buf[MAX_MSG_LENGTH + 1];
पूर्ण;

काष्ठा isotp_sock अणु
	काष्ठा sock sk;
	पूर्णांक bound;
	पूर्णांक अगरindex;
	canid_t txid;
	canid_t rxid;
	kसमय_प्रकार tx_gap;
	kसमय_प्रकार lastrxcf_tstamp;
	काष्ठा hrसमयr rxसमयr, txसमयr;
	काष्ठा can_isotp_options opt;
	काष्ठा can_isotp_fc_options rxfc, txfc;
	काष्ठा can_isotp_ll_options ll;
	u32 क्रमce_tx_sपंचांगin;
	u32 क्रमce_rx_sपंचांगin;
	काष्ठा tpcon rx, tx;
	काष्ठा list_head notअगरier;
	रुको_queue_head_t रुको;
पूर्ण;

अटल LIST_HEAD(isotp_notअगरier_list);
अटल DEFINE_SPINLOCK(isotp_notअगरier_lock);
अटल काष्ठा isotp_sock *isotp_busy_notअगरier;

अटल अंतरभूत काष्ठा isotp_sock *isotp_sk(स्थिर काष्ठा sock *sk)
अणु
	वापस (काष्ठा isotp_sock *)sk;
पूर्ण

अटल क्रमागत hrसमयr_restart isotp_rx_समयr_handler(काष्ठा hrसमयr *hrसमयr)
अणु
	काष्ठा isotp_sock *so = container_of(hrसमयr, काष्ठा isotp_sock,
					     rxसमयr);
	काष्ठा sock *sk = &so->sk;

	अगर (so->rx.state == ISOTP_WAIT_DATA) अणु
		/* we did not get new data frames in समय */

		/* report 'connection timed out' */
		sk->sk_err = ETIMEDOUT;
		अगर (!sock_flag(sk, SOCK_DEAD))
			sk->sk_error_report(sk);

		/* reset rx state */
		so->rx.state = ISOTP_IDLE;
	पूर्ण

	वापस HRTIMER_NORESTART;
पूर्ण

अटल पूर्णांक isotp_send_fc(काष्ठा sock *sk, पूर्णांक ae, u8 flowstatus)
अणु
	काष्ठा net_device *dev;
	काष्ठा sk_buff *nskb;
	काष्ठा canfd_frame *ncf;
	काष्ठा isotp_sock *so = isotp_sk(sk);
	पूर्णांक can_send_ret;

	nskb = alloc_skb(so->ll.mtu + माप(काष्ठा can_skb_priv), gfp_any());
	अगर (!nskb)
		वापस 1;

	dev = dev_get_by_index(sock_net(sk), so->अगरindex);
	अगर (!dev) अणु
		kमुक्त_skb(nskb);
		वापस 1;
	पूर्ण

	can_skb_reserve(nskb);
	can_skb_prv(nskb)->अगरindex = dev->अगरindex;
	can_skb_prv(nskb)->skbcnt = 0;

	nskb->dev = dev;
	can_skb_set_owner(nskb, sk);
	ncf = (काष्ठा canfd_frame *)nskb->data;
	skb_put_zero(nskb, so->ll.mtu);

	/* create & send flow control reply */
	ncf->can_id = so->txid;

	अगर (so->opt.flags & CAN_ISOTP_TX_PADDING) अणु
		स_रखो(ncf->data, so->opt.txpad_content, CAN_MAX_DLEN);
		ncf->len = CAN_MAX_DLEN;
	पूर्ण अन्यथा अणु
		ncf->len = ae + FC_CONTENT_SZ;
	पूर्ण

	ncf->data[ae] = N_PCI_FC | flowstatus;
	ncf->data[ae + 1] = so->rxfc.bs;
	ncf->data[ae + 2] = so->rxfc.sपंचांगin;

	अगर (ae)
		ncf->data[0] = so->opt.ext_address;

	ncf->flags = so->ll.tx_flags;

	can_send_ret = can_send(nskb, 1);
	अगर (can_send_ret)
		pr_notice_once("can-isotp: %s: can_send_ret %d\n",
			       __func__, can_send_ret);

	dev_put(dev);

	/* reset blocksize counter */
	so->rx.bs = 0;

	/* reset last CF frame rx बारtamp क्रम rx sपंचांगin enक्रमcement */
	so->lastrxcf_tstamp = kसमय_set(0, 0);

	/* start rx समयout watchकरोg */
	hrसमयr_start(&so->rxसमयr, kसमय_set(1, 0), HRTIMER_MODE_REL_SOFT);
	वापस 0;
पूर्ण

अटल व्योम isotp_rcv_skb(काष्ठा sk_buff *skb, काष्ठा sock *sk)
अणु
	काष्ठा sockaddr_can *addr = (काष्ठा sockaddr_can *)skb->cb;

	BUILD_BUG_ON(माप(skb->cb) < माप(काष्ठा sockaddr_can));

	स_रखो(addr, 0, माप(*addr));
	addr->can_family = AF_CAN;
	addr->can_अगरindex = skb->dev->अगरindex;

	अगर (sock_queue_rcv_skb(sk, skb) < 0)
		kमुक्त_skb(skb);
पूर्ण

अटल u8 padlen(u8 datalen)
अणु
	अटल स्थिर u8 plen[] = अणु
		8, 8, 8, 8, 8, 8, 8, 8, 8,	/* 0 - 8 */
		12, 12, 12, 12,			/* 9 - 12 */
		16, 16, 16, 16,			/* 13 - 16 */
		20, 20, 20, 20,			/* 17 - 20 */
		24, 24, 24, 24,			/* 21 - 24 */
		32, 32, 32, 32, 32, 32, 32, 32,	/* 25 - 32 */
		48, 48, 48, 48, 48, 48, 48, 48,	/* 33 - 40 */
		48, 48, 48, 48, 48, 48, 48, 48	/* 41 - 48 */
	पूर्ण;

	अगर (datalen > 48)
		वापस 64;

	वापस plen[datalen];
पूर्ण

/* check क्रम length optimization and वापस 1/true when the check fails */
अटल पूर्णांक check_optimized(काष्ठा canfd_frame *cf, पूर्णांक start_index)
अणु
	/* क्रम CAN_DL <= 8 the start_index is equal to the CAN_DL as the
	 * padding would start at this poपूर्णांक. E.g. अगर the padding would
	 * start at cf.data[7] cf->len has to be 7 to be optimal.
	 * Note: The data[] index starts with zero.
	 */
	अगर (cf->len <= CAN_MAX_DLEN)
		वापस (cf->len != start_index);

	/* This relation is also valid in the non-linear DLC range, where
	 * we need to take care of the minimal next possible CAN_DL.
	 * The correct check would be (padlen(cf->len) != padlen(start_index)).
	 * But as cf->len can only take discrete values from 12, .., 64 at this
	 * poपूर्णांक the padlen(cf->len) is always equal to cf->len.
	 */
	वापस (cf->len != padlen(start_index));
पूर्ण

/* check padding and वापस 1/true when the check fails */
अटल पूर्णांक check_pad(काष्ठा isotp_sock *so, काष्ठा canfd_frame *cf,
		     पूर्णांक start_index, u8 content)
अणु
	पूर्णांक i;

	/* no RX_PADDING value => check length of optimized frame length */
	अगर (!(so->opt.flags & CAN_ISOTP_RX_PADDING)) अणु
		अगर (so->opt.flags & CAN_ISOTP_CHK_PAD_LEN)
			वापस check_optimized(cf, start_index);

		/* no valid test against empty value => ignore frame */
		वापस 1;
	पूर्ण

	/* check datalength of correctly padded CAN frame */
	अगर ((so->opt.flags & CAN_ISOTP_CHK_PAD_LEN) &&
	    cf->len != padlen(cf->len))
		वापस 1;

	/* check padding content */
	अगर (so->opt.flags & CAN_ISOTP_CHK_PAD_DATA) अणु
		क्रम (i = start_index; i < cf->len; i++)
			अगर (cf->data[i] != content)
				वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक isotp_rcv_fc(काष्ठा isotp_sock *so, काष्ठा canfd_frame *cf, पूर्णांक ae)
अणु
	काष्ठा sock *sk = &so->sk;

	अगर (so->tx.state != ISOTP_WAIT_FC &&
	    so->tx.state != ISOTP_WAIT_FIRST_FC)
		वापस 0;

	hrसमयr_cancel(&so->txसमयr);

	अगर ((cf->len < ae + FC_CONTENT_SZ) ||
	    ((so->opt.flags & ISOTP_CHECK_PADDING) &&
	     check_pad(so, cf, ae + FC_CONTENT_SZ, so->opt.rxpad_content))) अणु
		/* malक्रमmed PDU - report 'not a data message' */
		sk->sk_err = EBADMSG;
		अगर (!sock_flag(sk, SOCK_DEAD))
			sk->sk_error_report(sk);

		so->tx.state = ISOTP_IDLE;
		wake_up_पूर्णांकerruptible(&so->रुको);
		वापस 1;
	पूर्ण

	/* get communication parameters only from the first FC frame */
	अगर (so->tx.state == ISOTP_WAIT_FIRST_FC) अणु
		so->txfc.bs = cf->data[ae + 1];
		so->txfc.sपंचांगin = cf->data[ae + 2];

		/* fix wrong STmin values according spec */
		अगर (so->txfc.sपंचांगin > 0x7F &&
		    (so->txfc.sपंचांगin < 0xF1 || so->txfc.sपंचांगin > 0xF9))
			so->txfc.sपंचांगin = 0x7F;

		so->tx_gap = kसमय_set(0, 0);
		/* add transmission समय क्रम CAN frame N_As */
		so->tx_gap = kसमय_add_ns(so->tx_gap, so->opt.frame_txसमय);
		/* add रुकोing समय क्रम consecutive frames N_Cs */
		अगर (so->opt.flags & CAN_ISOTP_FORCE_TXSTMIN)
			so->tx_gap = kसमय_add_ns(so->tx_gap,
						  so->क्रमce_tx_sपंचांगin);
		अन्यथा अगर (so->txfc.sपंचांगin < 0x80)
			so->tx_gap = kसमय_add_ns(so->tx_gap,
						  so->txfc.sपंचांगin * 1000000);
		अन्यथा
			so->tx_gap = kसमय_add_ns(so->tx_gap,
						  (so->txfc.sपंचांगin - 0xF0)
						  * 100000);
		so->tx.state = ISOTP_WAIT_FC;
	पूर्ण

	चयन (cf->data[ae] & 0x0F) अणु
	हाल ISOTP_FC_CTS:
		so->tx.bs = 0;
		so->tx.state = ISOTP_SENDING;
		/* start cyclic समयr क्रम sending CF frame */
		hrसमयr_start(&so->txसमयr, so->tx_gap,
			      HRTIMER_MODE_REL_SOFT);
		अवरोध;

	हाल ISOTP_FC_WT:
		/* start समयr to रुको क्रम next FC frame */
		hrसमयr_start(&so->txसमयr, kसमय_set(1, 0),
			      HRTIMER_MODE_REL_SOFT);
		अवरोध;

	हाल ISOTP_FC_OVFLW:
		/* overflow on receiver side - report 'message too long' */
		sk->sk_err = EMSGSIZE;
		अगर (!sock_flag(sk, SOCK_DEAD))
			sk->sk_error_report(sk);
		fallthrough;

	शेष:
		/* stop this tx job */
		so->tx.state = ISOTP_IDLE;
		wake_up_पूर्णांकerruptible(&so->रुको);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक isotp_rcv_sf(काष्ठा sock *sk, काष्ठा canfd_frame *cf, पूर्णांक pcilen,
			काष्ठा sk_buff *skb, पूर्णांक len)
अणु
	काष्ठा isotp_sock *so = isotp_sk(sk);
	काष्ठा sk_buff *nskb;

	hrसमयr_cancel(&so->rxसमयr);
	so->rx.state = ISOTP_IDLE;

	अगर (!len || len > cf->len - pcilen)
		वापस 1;

	अगर ((so->opt.flags & ISOTP_CHECK_PADDING) &&
	    check_pad(so, cf, pcilen + len, so->opt.rxpad_content)) अणु
		/* malक्रमmed PDU - report 'not a data message' */
		sk->sk_err = EBADMSG;
		अगर (!sock_flag(sk, SOCK_DEAD))
			sk->sk_error_report(sk);
		वापस 1;
	पूर्ण

	nskb = alloc_skb(len, gfp_any());
	अगर (!nskb)
		वापस 1;

	स_नकल(skb_put(nskb, len), &cf->data[pcilen], len);

	nskb->tstamp = skb->tstamp;
	nskb->dev = skb->dev;
	isotp_rcv_skb(nskb, sk);
	वापस 0;
पूर्ण

अटल पूर्णांक isotp_rcv_ff(काष्ठा sock *sk, काष्ठा canfd_frame *cf, पूर्णांक ae)
अणु
	काष्ठा isotp_sock *so = isotp_sk(sk);
	पूर्णांक i;
	पूर्णांक off;
	पूर्णांक ff_pci_sz;

	hrसमयr_cancel(&so->rxसमयr);
	so->rx.state = ISOTP_IDLE;

	/* get the used sender LL_DL from the (first) CAN frame data length */
	so->rx.ll_dl = padlen(cf->len);

	/* the first frame has to use the entire frame up to LL_DL length */
	अगर (cf->len != so->rx.ll_dl)
		वापस 1;

	/* get the FF_DL */
	so->rx.len = (cf->data[ae] & 0x0F) << 8;
	so->rx.len += cf->data[ae + 1];

	/* Check क्रम FF_DL escape sequence supporting 32 bit PDU length */
	अगर (so->rx.len) अणु
		ff_pci_sz = FF_PCI_SZ12;
	पूर्ण अन्यथा अणु
		/* FF_DL = 0 => get real length from next 4 bytes */
		so->rx.len = cf->data[ae + 2] << 24;
		so->rx.len += cf->data[ae + 3] << 16;
		so->rx.len += cf->data[ae + 4] << 8;
		so->rx.len += cf->data[ae + 5];
		ff_pci_sz = FF_PCI_SZ32;
	पूर्ण

	/* take care of a potential SF_DL ESC offset क्रम TX_DL > 8 */
	off = (so->rx.ll_dl > CAN_MAX_DLEN) ? 1 : 0;

	अगर (so->rx.len + ae + off + ff_pci_sz < so->rx.ll_dl)
		वापस 1;

	अगर (so->rx.len > MAX_MSG_LENGTH) अणु
		/* send FC frame with overflow status */
		isotp_send_fc(sk, ae, ISOTP_FC_OVFLW);
		वापस 1;
	पूर्ण

	/* copy the first received data bytes */
	so->rx.idx = 0;
	क्रम (i = ae + ff_pci_sz; i < so->rx.ll_dl; i++)
		so->rx.buf[so->rx.idx++] = cf->data[i];

	/* initial setup क्रम this pdu reception */
	so->rx.sn = 1;
	so->rx.state = ISOTP_WAIT_DATA;

	/* no creation of flow control frames */
	अगर (so->opt.flags & CAN_ISOTP_LISTEN_MODE)
		वापस 0;

	/* send our first FC frame */
	isotp_send_fc(sk, ae, ISOTP_FC_CTS);
	वापस 0;
पूर्ण

अटल पूर्णांक isotp_rcv_cf(काष्ठा sock *sk, काष्ठा canfd_frame *cf, पूर्णांक ae,
			काष्ठा sk_buff *skb)
अणु
	काष्ठा isotp_sock *so = isotp_sk(sk);
	काष्ठा sk_buff *nskb;
	पूर्णांक i;

	अगर (so->rx.state != ISOTP_WAIT_DATA)
		वापस 0;

	/* drop अगर बारtamp gap is less than क्रमce_rx_sपंचांगin nano secs */
	अगर (so->opt.flags & CAN_ISOTP_FORCE_RXSTMIN) अणु
		अगर (kसमय_प्रकारo_ns(kसमय_sub(skb->tstamp, so->lastrxcf_tstamp)) <
		    so->क्रमce_rx_sपंचांगin)
			वापस 0;

		so->lastrxcf_tstamp = skb->tstamp;
	पूर्ण

	hrसमयr_cancel(&so->rxसमयr);

	/* CFs are never दीर्घer than the FF */
	अगर (cf->len > so->rx.ll_dl)
		वापस 1;

	/* CFs have usually the LL_DL length */
	अगर (cf->len < so->rx.ll_dl) अणु
		/* this is only allowed क्रम the last CF */
		अगर (so->rx.len - so->rx.idx > so->rx.ll_dl - ae - N_PCI_SZ)
			वापस 1;
	पूर्ण

	अगर ((cf->data[ae] & 0x0F) != so->rx.sn) अणु
		/* wrong sn detected - report 'illegal byte sequence' */
		sk->sk_err = EILSEQ;
		अगर (!sock_flag(sk, SOCK_DEAD))
			sk->sk_error_report(sk);

		/* reset rx state */
		so->rx.state = ISOTP_IDLE;
		वापस 1;
	पूर्ण
	so->rx.sn++;
	so->rx.sn %= 16;

	क्रम (i = ae + N_PCI_SZ; i < cf->len; i++) अणु
		so->rx.buf[so->rx.idx++] = cf->data[i];
		अगर (so->rx.idx >= so->rx.len)
			अवरोध;
	पूर्ण

	अगर (so->rx.idx >= so->rx.len) अणु
		/* we are करोne */
		so->rx.state = ISOTP_IDLE;

		अगर ((so->opt.flags & ISOTP_CHECK_PADDING) &&
		    check_pad(so, cf, i + 1, so->opt.rxpad_content)) अणु
			/* malक्रमmed PDU - report 'not a data message' */
			sk->sk_err = EBADMSG;
			अगर (!sock_flag(sk, SOCK_DEAD))
				sk->sk_error_report(sk);
			वापस 1;
		पूर्ण

		nskb = alloc_skb(so->rx.len, gfp_any());
		अगर (!nskb)
			वापस 1;

		स_नकल(skb_put(nskb, so->rx.len), so->rx.buf,
		       so->rx.len);

		nskb->tstamp = skb->tstamp;
		nskb->dev = skb->dev;
		isotp_rcv_skb(nskb, sk);
		वापस 0;
	पूर्ण

	/* perक्रमm blocksize handling, अगर enabled */
	अगर (!so->rxfc.bs || ++so->rx.bs < so->rxfc.bs) अणु
		/* start rx समयout watchकरोg */
		hrसमयr_start(&so->rxसमयr, kसमय_set(1, 0),
			      HRTIMER_MODE_REL_SOFT);
		वापस 0;
	पूर्ण

	/* no creation of flow control frames */
	अगर (so->opt.flags & CAN_ISOTP_LISTEN_MODE)
		वापस 0;

	/* we reached the specअगरied blocksize so->rxfc.bs */
	isotp_send_fc(sk, ae, ISOTP_FC_CTS);
	वापस 0;
पूर्ण

अटल व्योम isotp_rcv(काष्ठा sk_buff *skb, व्योम *data)
अणु
	काष्ठा sock *sk = (काष्ठा sock *)data;
	काष्ठा isotp_sock *so = isotp_sk(sk);
	काष्ठा canfd_frame *cf;
	पूर्णांक ae = (so->opt.flags & CAN_ISOTP_EXTEND_ADDR) ? 1 : 0;
	u8 n_pci_type, sf_dl;

	/* Strictly receive only frames with the configured MTU size
	 * => clear separation of CAN2.0 / CAN FD transport channels
	 */
	अगर (skb->len != so->ll.mtu)
		वापस;

	cf = (काष्ठा canfd_frame *)skb->data;

	/* अगर enabled: check reception of my configured extended address */
	अगर (ae && cf->data[0] != so->opt.rx_ext_address)
		वापस;

	n_pci_type = cf->data[ae] & 0xF0;

	अगर (so->opt.flags & CAN_ISOTP_HALF_DUPLEX) अणु
		/* check rx/tx path half duplex expectations */
		अगर ((so->tx.state != ISOTP_IDLE && n_pci_type != N_PCI_FC) ||
		    (so->rx.state != ISOTP_IDLE && n_pci_type == N_PCI_FC))
			वापस;
	पूर्ण

	चयन (n_pci_type) अणु
	हाल N_PCI_FC:
		/* tx path: flow control frame containing the FC parameters */
		isotp_rcv_fc(so, cf, ae);
		अवरोध;

	हाल N_PCI_SF:
		/* rx path: single frame
		 *
		 * As we करो not have a rx.ll_dl configuration, we can only test
		 * अगर the CAN frames payload length matches the LL_DL == 8
		 * requirements - no matter अगर it's CAN 2.0 or CAN FD
		 */

		/* get the SF_DL from the N_PCI byte */
		sf_dl = cf->data[ae] & 0x0F;

		अगर (cf->len <= CAN_MAX_DLEN) अणु
			isotp_rcv_sf(sk, cf, SF_PCI_SZ4 + ae, skb, sf_dl);
		पूर्ण अन्यथा अणु
			अगर (skb->len == CANFD_MTU) अणु
				/* We have a CAN FD frame and CAN_DL is greater than 8:
				 * Only frames with the SF_DL == 0 ESC value are valid.
				 *
				 * If so take care of the increased SF PCI size
				 * (SF_PCI_SZ8) to poपूर्णांक to the message content behind
				 * the extended SF PCI info and get the real SF_DL
				 * length value from the क्रमmerly first data byte.
				 */
				अगर (sf_dl == 0)
					isotp_rcv_sf(sk, cf, SF_PCI_SZ8 + ae, skb,
						     cf->data[SF_PCI_SZ4 + ae]);
			पूर्ण
		पूर्ण
		अवरोध;

	हाल N_PCI_FF:
		/* rx path: first frame */
		isotp_rcv_ff(sk, cf, ae);
		अवरोध;

	हाल N_PCI_CF:
		/* rx path: consecutive frame */
		isotp_rcv_cf(sk, cf, ae, skb);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम isotp_fill_dataframe(काष्ठा canfd_frame *cf, काष्ठा isotp_sock *so,
				 पूर्णांक ae, पूर्णांक off)
अणु
	पूर्णांक pcilen = N_PCI_SZ + ae + off;
	पूर्णांक space = so->tx.ll_dl - pcilen;
	पूर्णांक num = min_t(पूर्णांक, so->tx.len - so->tx.idx, space);
	पूर्णांक i;

	cf->can_id = so->txid;
	cf->len = num + pcilen;

	अगर (num < space) अणु
		अगर (so->opt.flags & CAN_ISOTP_TX_PADDING) अणु
			/* user requested padding */
			cf->len = padlen(cf->len);
			स_रखो(cf->data, so->opt.txpad_content, cf->len);
		पूर्ण अन्यथा अगर (cf->len > CAN_MAX_DLEN) अणु
			/* mandatory padding क्रम CAN FD frames */
			cf->len = padlen(cf->len);
			स_रखो(cf->data, CAN_ISOTP_DEFAULT_PAD_CONTENT,
			       cf->len);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < num; i++)
		cf->data[pcilen + i] = so->tx.buf[so->tx.idx++];

	अगर (ae)
		cf->data[0] = so->opt.ext_address;
पूर्ण

अटल व्योम isotp_create_fframe(काष्ठा canfd_frame *cf, काष्ठा isotp_sock *so,
				पूर्णांक ae)
अणु
	पूर्णांक i;
	पूर्णांक ff_pci_sz;

	cf->can_id = so->txid;
	cf->len = so->tx.ll_dl;
	अगर (ae)
		cf->data[0] = so->opt.ext_address;

	/* create N_PCI bytes with 12/32 bit FF_DL data length */
	अगर (so->tx.len > 4095) अणु
		/* use 32 bit FF_DL notation */
		cf->data[ae] = N_PCI_FF;
		cf->data[ae + 1] = 0;
		cf->data[ae + 2] = (u8)(so->tx.len >> 24) & 0xFFU;
		cf->data[ae + 3] = (u8)(so->tx.len >> 16) & 0xFFU;
		cf->data[ae + 4] = (u8)(so->tx.len >> 8) & 0xFFU;
		cf->data[ae + 5] = (u8)so->tx.len & 0xFFU;
		ff_pci_sz = FF_PCI_SZ32;
	पूर्ण अन्यथा अणु
		/* use 12 bit FF_DL notation */
		cf->data[ae] = (u8)(so->tx.len >> 8) | N_PCI_FF;
		cf->data[ae + 1] = (u8)so->tx.len & 0xFFU;
		ff_pci_sz = FF_PCI_SZ12;
	पूर्ण

	/* add first data bytes depending on ae */
	क्रम (i = ae + ff_pci_sz; i < so->tx.ll_dl; i++)
		cf->data[i] = so->tx.buf[so->tx.idx++];

	so->tx.sn = 1;
	so->tx.state = ISOTP_WAIT_FIRST_FC;
पूर्ण

अटल क्रमागत hrसमयr_restart isotp_tx_समयr_handler(काष्ठा hrसमयr *hrसमयr)
अणु
	काष्ठा isotp_sock *so = container_of(hrसमयr, काष्ठा isotp_sock,
					     txसमयr);
	काष्ठा sock *sk = &so->sk;
	काष्ठा sk_buff *skb;
	काष्ठा net_device *dev;
	काष्ठा canfd_frame *cf;
	क्रमागत hrसमयr_restart restart = HRTIMER_NORESTART;
	पूर्णांक can_send_ret;
	पूर्णांक ae = (so->opt.flags & CAN_ISOTP_EXTEND_ADDR) ? 1 : 0;

	चयन (so->tx.state) अणु
	हाल ISOTP_WAIT_FC:
	हाल ISOTP_WAIT_FIRST_FC:

		/* we did not get any flow control frame in समय */

		/* report 'communication error on send' */
		sk->sk_err = ECOMM;
		अगर (!sock_flag(sk, SOCK_DEAD))
			sk->sk_error_report(sk);

		/* reset tx state */
		so->tx.state = ISOTP_IDLE;
		wake_up_पूर्णांकerruptible(&so->रुको);
		अवरोध;

	हाल ISOTP_SENDING:

		/* push out the next segmented pdu */
		dev = dev_get_by_index(sock_net(sk), so->अगरindex);
		अगर (!dev)
			अवरोध;

isotp_tx_burst:
		skb = alloc_skb(so->ll.mtu + माप(काष्ठा can_skb_priv),
				GFP_ATOMIC);
		अगर (!skb) अणु
			dev_put(dev);
			अवरोध;
		पूर्ण

		can_skb_reserve(skb);
		can_skb_prv(skb)->अगरindex = dev->अगरindex;
		can_skb_prv(skb)->skbcnt = 0;

		cf = (काष्ठा canfd_frame *)skb->data;
		skb_put_zero(skb, so->ll.mtu);

		/* create consecutive frame */
		isotp_fill_dataframe(cf, so, ae, 0);

		/* place consecutive frame N_PCI in appropriate index */
		cf->data[ae] = N_PCI_CF | so->tx.sn++;
		so->tx.sn %= 16;
		so->tx.bs++;

		cf->flags = so->ll.tx_flags;

		skb->dev = dev;
		can_skb_set_owner(skb, sk);

		can_send_ret = can_send(skb, 1);
		अगर (can_send_ret)
			pr_notice_once("can-isotp: %s: can_send_ret %d\n",
				       __func__, can_send_ret);

		अगर (so->tx.idx >= so->tx.len) अणु
			/* we are करोne */
			so->tx.state = ISOTP_IDLE;
			dev_put(dev);
			wake_up_पूर्णांकerruptible(&so->रुको);
			अवरोध;
		पूर्ण

		अगर (so->txfc.bs && so->tx.bs >= so->txfc.bs) अणु
			/* stop and रुको क्रम FC */
			so->tx.state = ISOTP_WAIT_FC;
			dev_put(dev);
			hrसमयr_set_expires(&so->txसमयr,
					    kसमय_add(kसमय_get(),
						      kसमय_set(1, 0)));
			restart = HRTIMER_RESTART;
			अवरोध;
		पूर्ण

		/* no gap between data frames needed => use burst mode */
		अगर (!so->tx_gap)
			जाओ isotp_tx_burst;

		/* start समयr to send next data frame with correct delay */
		dev_put(dev);
		hrसमयr_set_expires(&so->txसमयr,
				    kसमय_add(kसमय_get(), so->tx_gap));
		restart = HRTIMER_RESTART;
		अवरोध;

	शेष:
		WARN_ON_ONCE(1);
	पूर्ण

	वापस restart;
पूर्ण

अटल पूर्णांक isotp_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार size)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा isotp_sock *so = isotp_sk(sk);
	काष्ठा sk_buff *skb;
	काष्ठा net_device *dev;
	काष्ठा canfd_frame *cf;
	पूर्णांक ae = (so->opt.flags & CAN_ISOTP_EXTEND_ADDR) ? 1 : 0;
	पूर्णांक रुको_tx_करोne = (so->opt.flags & CAN_ISOTP_WAIT_TX_DONE) ? 1 : 0;
	पूर्णांक off;
	पूर्णांक err;

	अगर (!so->bound)
		वापस -EADDRNOTAVAIL;

	/* we करो not support multiple buffers - क्रम now */
	अगर (so->tx.state != ISOTP_IDLE || wq_has_sleeper(&so->रुको)) अणु
		अगर (msg->msg_flags & MSG_DONTWAIT)
			वापस -EAGAIN;

		/* रुको क्रम complete transmission of current pdu */
		रुको_event_पूर्णांकerruptible(so->रुको, so->tx.state == ISOTP_IDLE);
	पूर्ण

	अगर (!size || size > MAX_MSG_LENGTH)
		वापस -EINVAL;

	/* take care of a potential SF_DL ESC offset क्रम TX_DL > 8 */
	off = (so->tx.ll_dl > CAN_MAX_DLEN) ? 1 : 0;

	/* करोes the given data fit पूर्णांकo a single frame क्रम SF_BROADCAST? */
	अगर ((so->opt.flags & CAN_ISOTP_SF_BROADCAST) &&
	    (size > so->tx.ll_dl - SF_PCI_SZ4 - ae - off))
		वापस -EINVAL;

	err = स_नकल_from_msg(so->tx.buf, msg, size);
	अगर (err < 0)
		वापस err;

	dev = dev_get_by_index(sock_net(sk), so->अगरindex);
	अगर (!dev)
		वापस -ENXIO;

	skb = sock_alloc_send_skb(sk, so->ll.mtu + माप(काष्ठा can_skb_priv),
				  msg->msg_flags & MSG_DONTWAIT, &err);
	अगर (!skb) अणु
		dev_put(dev);
		वापस err;
	पूर्ण

	can_skb_reserve(skb);
	can_skb_prv(skb)->अगरindex = dev->अगरindex;
	can_skb_prv(skb)->skbcnt = 0;

	so->tx.state = ISOTP_SENDING;
	so->tx.len = size;
	so->tx.idx = 0;

	cf = (काष्ठा canfd_frame *)skb->data;
	skb_put_zero(skb, so->ll.mtu);

	/* check क्रम single frame transmission depending on TX_DL */
	अगर (size <= so->tx.ll_dl - SF_PCI_SZ4 - ae - off) अणु
		/* The message size generally fits पूर्णांकo a SingleFrame - good.
		 *
		 * SF_DL ESC offset optimization:
		 *
		 * When TX_DL is greater 8 but the message would still fit
		 * पूर्णांकo a 8 byte CAN frame, we can omit the offset.
		 * This prevents a protocol caused length extension from
		 * CAN_DL = 8 to CAN_DL = 12 due to the SF_SL ESC handling.
		 */
		अगर (size <= CAN_MAX_DLEN - SF_PCI_SZ4 - ae)
			off = 0;

		isotp_fill_dataframe(cf, so, ae, off);

		/* place single frame N_PCI w/o length in appropriate index */
		cf->data[ae] = N_PCI_SF;

		/* place SF_DL size value depending on the SF_DL ESC offset */
		अगर (off)
			cf->data[SF_PCI_SZ4 + ae] = size;
		अन्यथा
			cf->data[ae] |= size;

		so->tx.state = ISOTP_IDLE;
		wake_up_पूर्णांकerruptible(&so->रुको);

		/* करोn't enable रुको queue क्रम a single frame transmission */
		रुको_tx_करोne = 0;
	पूर्ण अन्यथा अणु
		/* send first frame and रुको क्रम FC */

		isotp_create_fframe(cf, so, ae);

		/* start समयout क्रम FC */
		hrसमयr_start(&so->txसमयr, kसमय_set(1, 0), HRTIMER_MODE_REL_SOFT);
	पूर्ण

	/* send the first or only CAN frame */
	cf->flags = so->ll.tx_flags;

	skb->dev = dev;
	skb->sk = sk;
	err = can_send(skb, 1);
	dev_put(dev);
	अगर (err) अणु
		pr_notice_once("can-isotp: %s: can_send_ret %d\n",
			       __func__, err);
		वापस err;
	पूर्ण

	अगर (रुको_tx_करोne) अणु
		/* रुको क्रम complete transmission of current pdu */
		रुको_event_पूर्णांकerruptible(so->रुको, so->tx.state == ISOTP_IDLE);
	पूर्ण

	वापस size;
पूर्ण

अटल पूर्णांक isotp_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार size,
			 पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा sk_buff *skb;
	पूर्णांक err = 0;
	पूर्णांक noblock;

	noblock = flags & MSG_DONTWAIT;
	flags &= ~MSG_DONTWAIT;

	skb = skb_recv_datagram(sk, flags, noblock, &err);
	अगर (!skb)
		वापस err;

	अगर (size < skb->len)
		msg->msg_flags |= MSG_TRUNC;
	अन्यथा
		size = skb->len;

	err = स_नकल_to_msg(msg, skb->data, size);
	अगर (err < 0) अणु
		skb_मुक्त_datagram(sk, skb);
		वापस err;
	पूर्ण

	sock_recv_बारtamp(msg, sk, skb);

	अगर (msg->msg_name) अणु
		__sockaddr_check_size(ISOTP_MIN_NAMELEN);
		msg->msg_namelen = ISOTP_MIN_NAMELEN;
		स_नकल(msg->msg_name, skb->cb, msg->msg_namelen);
	पूर्ण

	skb_मुक्त_datagram(sk, skb);

	वापस size;
पूर्ण

अटल पूर्णांक isotp_release(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा isotp_sock *so;
	काष्ठा net *net;

	अगर (!sk)
		वापस 0;

	so = isotp_sk(sk);
	net = sock_net(sk);

	/* रुको क्रम complete transmission of current pdu */
	रुको_event_पूर्णांकerruptible(so->रुको, so->tx.state == ISOTP_IDLE);

	spin_lock(&isotp_notअगरier_lock);
	जबतक (isotp_busy_notअगरier == so) अणु
		spin_unlock(&isotp_notअगरier_lock);
		schedule_समयout_unपूर्णांकerruptible(1);
		spin_lock(&isotp_notअगरier_lock);
	पूर्ण
	list_del(&so->notअगरier);
	spin_unlock(&isotp_notअगरier_lock);

	lock_sock(sk);

	hrसमयr_cancel(&so->txसमयr);
	hrसमयr_cancel(&so->rxसमयr);

	/* हटाओ current filters & unरेजिस्टर */
	अगर (so->bound && (!(so->opt.flags & CAN_ISOTP_SF_BROADCAST))) अणु
		अगर (so->अगरindex) अणु
			काष्ठा net_device *dev;

			dev = dev_get_by_index(net, so->अगरindex);
			अगर (dev) अणु
				can_rx_unरेजिस्टर(net, dev, so->rxid,
						  SINGLE_MASK(so->rxid),
						  isotp_rcv, sk);
				dev_put(dev);
			पूर्ण
		पूर्ण
	पूर्ण

	so->अगरindex = 0;
	so->bound = 0;

	sock_orphan(sk);
	sock->sk = शून्य;

	release_sock(sk);
	sock_put(sk);

	वापस 0;
पूर्ण

अटल पूर्णांक isotp_bind(काष्ठा socket *sock, काष्ठा sockaddr *uaddr, पूर्णांक len)
अणु
	काष्ठा sockaddr_can *addr = (काष्ठा sockaddr_can *)uaddr;
	काष्ठा sock *sk = sock->sk;
	काष्ठा isotp_sock *so = isotp_sk(sk);
	काष्ठा net *net = sock_net(sk);
	पूर्णांक अगरindex;
	काष्ठा net_device *dev;
	पूर्णांक err = 0;
	पूर्णांक notअगरy_enetकरोwn = 0;
	पूर्णांक करो_rx_reg = 1;

	अगर (len < ISOTP_MIN_NAMELEN)
		वापस -EINVAL;

	अगर (addr->can_addr.tp.tx_id & (CAN_ERR_FLAG | CAN_RTR_FLAG))
		वापस -EADDRNOTAVAIL;

	अगर (!addr->can_अगरindex)
		वापस -ENODEV;

	lock_sock(sk);

	/* करो not रेजिस्टर frame reception क्रम functional addressing */
	अगर (so->opt.flags & CAN_ISOTP_SF_BROADCAST)
		करो_rx_reg = 0;

	/* करो not validate rx address क्रम functional addressing */
	अगर (करो_rx_reg) अणु
		अगर (addr->can_addr.tp.rx_id == addr->can_addr.tp.tx_id) अणु
			err = -EADDRNOTAVAIL;
			जाओ out;
		पूर्ण

		अगर (addr->can_addr.tp.rx_id & (CAN_ERR_FLAG | CAN_RTR_FLAG)) अणु
			err = -EADDRNOTAVAIL;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (so->bound && addr->can_अगरindex == so->अगरindex &&
	    addr->can_addr.tp.rx_id == so->rxid &&
	    addr->can_addr.tp.tx_id == so->txid)
		जाओ out;

	dev = dev_get_by_index(net, addr->can_अगरindex);
	अगर (!dev) अणु
		err = -ENODEV;
		जाओ out;
	पूर्ण
	अगर (dev->type != ARPHRD_CAN) अणु
		dev_put(dev);
		err = -ENODEV;
		जाओ out;
	पूर्ण
	अगर (dev->mtu < so->ll.mtu) अणु
		dev_put(dev);
		err = -EINVAL;
		जाओ out;
	पूर्ण
	अगर (!(dev->flags & IFF_UP))
		notअगरy_enetकरोwn = 1;

	अगरindex = dev->अगरindex;

	अगर (करो_rx_reg)
		can_rx_रेजिस्टर(net, dev, addr->can_addr.tp.rx_id,
				SINGLE_MASK(addr->can_addr.tp.rx_id),
				isotp_rcv, sk, "isotp", sk);

	dev_put(dev);

	अगर (so->bound && करो_rx_reg) अणु
		/* unरेजिस्टर old filter */
		अगर (so->अगरindex) अणु
			dev = dev_get_by_index(net, so->अगरindex);
			अगर (dev) अणु
				can_rx_unरेजिस्टर(net, dev, so->rxid,
						  SINGLE_MASK(so->rxid),
						  isotp_rcv, sk);
				dev_put(dev);
			पूर्ण
		पूर्ण
	पूर्ण

	/* चयन to new settings */
	so->अगरindex = अगरindex;
	so->rxid = addr->can_addr.tp.rx_id;
	so->txid = addr->can_addr.tp.tx_id;
	so->bound = 1;

out:
	release_sock(sk);

	अगर (notअगरy_enetकरोwn) अणु
		sk->sk_err = ENETDOWN;
		अगर (!sock_flag(sk, SOCK_DEAD))
			sk->sk_error_report(sk);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक isotp_getname(काष्ठा socket *sock, काष्ठा sockaddr *uaddr, पूर्णांक peer)
अणु
	काष्ठा sockaddr_can *addr = (काष्ठा sockaddr_can *)uaddr;
	काष्ठा sock *sk = sock->sk;
	काष्ठा isotp_sock *so = isotp_sk(sk);

	अगर (peer)
		वापस -EOPNOTSUPP;

	स_रखो(addr, 0, ISOTP_MIN_NAMELEN);
	addr->can_family = AF_CAN;
	addr->can_अगरindex = so->अगरindex;
	addr->can_addr.tp.rx_id = so->rxid;
	addr->can_addr.tp.tx_id = so->txid;

	वापस ISOTP_MIN_NAMELEN;
पूर्ण

अटल पूर्णांक isotp_setsockopt_locked(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
			    sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा isotp_sock *so = isotp_sk(sk);
	पूर्णांक ret = 0;

	अगर (so->bound)
		वापस -EISCONN;

	चयन (optname) अणु
	हाल CAN_ISOTP_OPTS:
		अगर (optlen != माप(काष्ठा can_isotp_options))
			वापस -EINVAL;

		अगर (copy_from_sockptr(&so->opt, optval, optlen))
			वापस -EFAULT;

		/* no separate rx_ext_address is given => use ext_address */
		अगर (!(so->opt.flags & CAN_ISOTP_RX_EXT_ADDR))
			so->opt.rx_ext_address = so->opt.ext_address;
		अवरोध;

	हाल CAN_ISOTP_RECV_FC:
		अगर (optlen != माप(काष्ठा can_isotp_fc_options))
			वापस -EINVAL;

		अगर (copy_from_sockptr(&so->rxfc, optval, optlen))
			वापस -EFAULT;
		अवरोध;

	हाल CAN_ISOTP_TX_STMIN:
		अगर (optlen != माप(u32))
			वापस -EINVAL;

		अगर (copy_from_sockptr(&so->क्रमce_tx_sपंचांगin, optval, optlen))
			वापस -EFAULT;
		अवरोध;

	हाल CAN_ISOTP_RX_STMIN:
		अगर (optlen != माप(u32))
			वापस -EINVAL;

		अगर (copy_from_sockptr(&so->क्रमce_rx_sपंचांगin, optval, optlen))
			वापस -EFAULT;
		अवरोध;

	हाल CAN_ISOTP_LL_OPTS:
		अगर (optlen == माप(काष्ठा can_isotp_ll_options)) अणु
			काष्ठा can_isotp_ll_options ll;

			अगर (copy_from_sockptr(&ll, optval, optlen))
				वापस -EFAULT;

			/* check क्रम correct ISO 11898-1 DLC data length */
			अगर (ll.tx_dl != padlen(ll.tx_dl))
				वापस -EINVAL;

			अगर (ll.mtu != CAN_MTU && ll.mtu != CANFD_MTU)
				वापस -EINVAL;

			अगर (ll.mtu == CAN_MTU &&
			    (ll.tx_dl > CAN_MAX_DLEN || ll.tx_flags != 0))
				वापस -EINVAL;

			स_नकल(&so->ll, &ll, माप(ll));

			/* set ll_dl क्रम tx path to similar place as क्रम rx */
			so->tx.ll_dl = ll.tx_dl;
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण
		अवरोध;

	शेष:
		ret = -ENOPROTOOPT;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक isotp_setsockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
			    sockptr_t optval, अचिन्हित पूर्णांक optlen)

अणु
	काष्ठा sock *sk = sock->sk;
	पूर्णांक ret;

	अगर (level != SOL_CAN_ISOTP)
		वापस -EINVAL;

	lock_sock(sk);
	ret = isotp_setsockopt_locked(sock, level, optname, optval, optlen);
	release_sock(sk);
	वापस ret;
पूर्ण

अटल पूर्णांक isotp_माला_लोockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
			    अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा isotp_sock *so = isotp_sk(sk);
	पूर्णांक len;
	व्योम *val;

	अगर (level != SOL_CAN_ISOTP)
		वापस -EINVAL;
	अगर (get_user(len, optlen))
		वापस -EFAULT;
	अगर (len < 0)
		वापस -EINVAL;

	चयन (optname) अणु
	हाल CAN_ISOTP_OPTS:
		len = min_t(पूर्णांक, len, माप(काष्ठा can_isotp_options));
		val = &so->opt;
		अवरोध;

	हाल CAN_ISOTP_RECV_FC:
		len = min_t(पूर्णांक, len, माप(काष्ठा can_isotp_fc_options));
		val = &so->rxfc;
		अवरोध;

	हाल CAN_ISOTP_TX_STMIN:
		len = min_t(पूर्णांक, len, माप(u32));
		val = &so->क्रमce_tx_sपंचांगin;
		अवरोध;

	हाल CAN_ISOTP_RX_STMIN:
		len = min_t(पूर्णांक, len, माप(u32));
		val = &so->क्रमce_rx_sपंचांगin;
		अवरोध;

	हाल CAN_ISOTP_LL_OPTS:
		len = min_t(पूर्णांक, len, माप(काष्ठा can_isotp_ll_options));
		val = &so->ll;
		अवरोध;

	शेष:
		वापस -ENOPROTOOPT;
	पूर्ण

	अगर (put_user(len, optlen))
		वापस -EFAULT;
	अगर (copy_to_user(optval, val, len))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल व्योम isotp_notअगरy(काष्ठा isotp_sock *so, अचिन्हित दीर्घ msg,
			 काष्ठा net_device *dev)
अणु
	काष्ठा sock *sk = &so->sk;

	अगर (!net_eq(dev_net(dev), sock_net(sk)))
		वापस;

	अगर (so->अगरindex != dev->अगरindex)
		वापस;

	चयन (msg) अणु
	हाल NETDEV_UNREGISTER:
		lock_sock(sk);
		/* हटाओ current filters & unरेजिस्टर */
		अगर (so->bound && (!(so->opt.flags & CAN_ISOTP_SF_BROADCAST)))
			can_rx_unरेजिस्टर(dev_net(dev), dev, so->rxid,
					  SINGLE_MASK(so->rxid),
					  isotp_rcv, sk);

		so->अगरindex = 0;
		so->bound  = 0;
		release_sock(sk);

		sk->sk_err = ENODEV;
		अगर (!sock_flag(sk, SOCK_DEAD))
			sk->sk_error_report(sk);
		अवरोध;

	हाल NETDEV_DOWN:
		sk->sk_err = ENETDOWN;
		अगर (!sock_flag(sk, SOCK_DEAD))
			sk->sk_error_report(sk);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक isotp_notअगरier(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ msg,
			  व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);

	अगर (dev->type != ARPHRD_CAN)
		वापस NOTIFY_DONE;
	अगर (msg != NETDEV_UNREGISTER && msg != NETDEV_DOWN)
		वापस NOTIFY_DONE;
	अगर (unlikely(isotp_busy_notअगरier)) /* Check क्रम reentrant bug. */
		वापस NOTIFY_DONE;

	spin_lock(&isotp_notअगरier_lock);
	list_क्रम_each_entry(isotp_busy_notअगरier, &isotp_notअगरier_list, notअगरier) अणु
		spin_unlock(&isotp_notअगरier_lock);
		isotp_notअगरy(isotp_busy_notअगरier, msg, dev);
		spin_lock(&isotp_notअगरier_lock);
	पूर्ण
	isotp_busy_notअगरier = शून्य;
	spin_unlock(&isotp_notअगरier_lock);
	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक isotp_init(काष्ठा sock *sk)
अणु
	काष्ठा isotp_sock *so = isotp_sk(sk);

	so->अगरindex = 0;
	so->bound = 0;

	so->opt.flags = CAN_ISOTP_DEFAULT_FLAGS;
	so->opt.ext_address = CAN_ISOTP_DEFAULT_EXT_ADDRESS;
	so->opt.rx_ext_address = CAN_ISOTP_DEFAULT_EXT_ADDRESS;
	so->opt.rxpad_content = CAN_ISOTP_DEFAULT_PAD_CONTENT;
	so->opt.txpad_content = CAN_ISOTP_DEFAULT_PAD_CONTENT;
	so->opt.frame_txसमय = CAN_ISOTP_DEFAULT_FRAME_TXTIME;
	so->rxfc.bs = CAN_ISOTP_DEFAULT_RECV_BS;
	so->rxfc.sपंचांगin = CAN_ISOTP_DEFAULT_RECV_STMIN;
	so->rxfc.wfपंचांगax = CAN_ISOTP_DEFAULT_RECV_WFTMAX;
	so->ll.mtu = CAN_ISOTP_DEFAULT_LL_MTU;
	so->ll.tx_dl = CAN_ISOTP_DEFAULT_LL_TX_DL;
	so->ll.tx_flags = CAN_ISOTP_DEFAULT_LL_TX_FLAGS;

	/* set ll_dl क्रम tx path to similar place as क्रम rx */
	so->tx.ll_dl = so->ll.tx_dl;

	so->rx.state = ISOTP_IDLE;
	so->tx.state = ISOTP_IDLE;

	hrसमयr_init(&so->rxसमयr, CLOCK_MONOTONIC, HRTIMER_MODE_REL_SOFT);
	so->rxसमयr.function = isotp_rx_समयr_handler;
	hrसमयr_init(&so->txसमयr, CLOCK_MONOTONIC, HRTIMER_MODE_REL_SOFT);
	so->txसमयr.function = isotp_tx_समयr_handler;

	init_रुकोqueue_head(&so->रुको);

	spin_lock(&isotp_notअगरier_lock);
	list_add_tail(&so->notअगरier, &isotp_notअगरier_list);
	spin_unlock(&isotp_notअगरier_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक isotp_sock_no_ioctlcmd(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd,
				  अचिन्हित दीर्घ arg)
अणु
	/* no ioctls क्रम socket layer -> hand it करोwn to NIC layer */
	वापस -ENOIOCTLCMD;
पूर्ण

अटल स्थिर काष्ठा proto_ops isotp_ops = अणु
	.family = PF_CAN,
	.release = isotp_release,
	.bind = isotp_bind,
	.connect = sock_no_connect,
	.socketpair = sock_no_socketpair,
	.accept = sock_no_accept,
	.getname = isotp_getname,
	.poll = datagram_poll,
	.ioctl = isotp_sock_no_ioctlcmd,
	.gettstamp = sock_gettstamp,
	.listen = sock_no_listen,
	.shutकरोwn = sock_no_shutकरोwn,
	.setsockopt = isotp_setsockopt,
	.माला_लोockopt = isotp_माला_लोockopt,
	.sendmsg = isotp_sendmsg,
	.recvmsg = isotp_recvmsg,
	.mmap = sock_no_mmap,
	.sendpage = sock_no_sendpage,
पूर्ण;

अटल काष्ठा proto isotp_proto __पढ़ो_mostly = अणु
	.name = "CAN_ISOTP",
	.owner = THIS_MODULE,
	.obj_size = माप(काष्ठा isotp_sock),
	.init = isotp_init,
पूर्ण;

अटल स्थिर काष्ठा can_proto isotp_can_proto = अणु
	.type = SOCK_DGRAM,
	.protocol = CAN_ISOTP,
	.ops = &isotp_ops,
	.prot = &isotp_proto,
पूर्ण;

अटल काष्ठा notअगरier_block canisotp_notअगरier = अणु
	.notअगरier_call = isotp_notअगरier
पूर्ण;

अटल __init पूर्णांक isotp_module_init(व्योम)
अणु
	पूर्णांक err;

	pr_info("can: isotp protocol\n");

	err = can_proto_रेजिस्टर(&isotp_can_proto);
	अगर (err < 0)
		pr_err("can: registration of isotp protocol failed\n");
	अन्यथा
		रेजिस्टर_netdevice_notअगरier(&canisotp_notअगरier);

	वापस err;
पूर्ण

अटल __निकास व्योम isotp_module_निकास(व्योम)
अणु
	can_proto_unरेजिस्टर(&isotp_can_proto);
	unरेजिस्टर_netdevice_notअगरier(&canisotp_notअगरier);
पूर्ण

module_init(isotp_module_init);
module_निकास(isotp_module_निकास);
