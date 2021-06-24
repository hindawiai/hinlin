<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) ST-Ericsson AB 2010
 * Author:	Sjur Brendeland
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ":%s(): " fmt, __func__

#समावेश <linux/मानकघोष.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <net/caअगर/caअगर_layer.h>
#समावेश <net/caअगर/cfpkt.h>
#समावेश <net/caअगर/cfserl.h>

#घोषणा container_obj(layr) ((काष्ठा cfserl *) layr)

#घोषणा CFSERL_STX 0x02
#घोषणा SERIAL_MINIUM_PACKET_SIZE 4
#घोषणा SERIAL_MAX_FRAMESIZE 4096
काष्ठा cfserl अणु
	काष्ठा cflayer layer;
	काष्ठा cfpkt *incomplete_frm;
	/* Protects parallel processing of incoming packets */
	spinlock_t sync;
	bool usestx;
पूर्ण;

अटल पूर्णांक cfserl_receive(काष्ठा cflayer *layr, काष्ठा cfpkt *pkt);
अटल पूर्णांक cfserl_transmit(काष्ठा cflayer *layr, काष्ठा cfpkt *pkt);
अटल व्योम cfserl_ctrlcmd(काष्ठा cflayer *layr, क्रमागत caअगर_ctrlcmd ctrl,
			   पूर्णांक phyid);

व्योम cfserl_release(काष्ठा cflayer *layer)
अणु
	kमुक्त(layer);
पूर्ण

काष्ठा cflayer *cfserl_create(पूर्णांक instance, bool use_stx)
अणु
	काष्ठा cfserl *this = kzalloc(माप(काष्ठा cfserl), GFP_ATOMIC);
	अगर (!this)
		वापस शून्य;
	caअगर_निश्चित(दुरत्व(काष्ठा cfserl, layer) == 0);
	this->layer.receive = cfserl_receive;
	this->layer.transmit = cfserl_transmit;
	this->layer.ctrlcmd = cfserl_ctrlcmd;
	this->usestx = use_stx;
	spin_lock_init(&this->sync);
	snम_लिखो(this->layer.name, CAIF_LAYER_NAME_SZ, "ser1");
	वापस &this->layer;
पूर्ण

अटल पूर्णांक cfserl_receive(काष्ठा cflayer *l, काष्ठा cfpkt *newpkt)
अणु
	काष्ठा cfserl *layr = container_obj(l);
	u16 pkt_len;
	काष्ठा cfpkt *pkt = शून्य;
	काष्ठा cfpkt *tail_pkt = शून्य;
	u8 पंचांगp8;
	u16 पंचांगp;
	u8 stx = CFSERL_STX;
	पूर्णांक ret;
	u16 expectlen = 0;

	caअगर_निश्चित(newpkt != शून्य);
	spin_lock(&layr->sync);

	अगर (layr->incomplete_frm != शून्य) अणु
		layr->incomplete_frm =
		    cfpkt_append(layr->incomplete_frm, newpkt, expectlen);
		pkt = layr->incomplete_frm;
		अगर (pkt == शून्य) अणु
			spin_unlock(&layr->sync);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण अन्यथा अणु
		pkt = newpkt;
	पूर्ण
	layr->incomplete_frm = शून्य;

	करो अणु
		/* Search क्रम STX at start of pkt अगर STX is used */
		अगर (layr->usestx) अणु
			cfpkt_extr_head(pkt, &पंचांगp8, 1);
			अगर (पंचांगp8 != CFSERL_STX) अणु
				जबतक (cfpkt_more(pkt)
				       && पंचांगp8 != CFSERL_STX) अणु
					cfpkt_extr_head(pkt, &पंचांगp8, 1);
				पूर्ण
				अगर (!cfpkt_more(pkt)) अणु
					cfpkt_destroy(pkt);
					layr->incomplete_frm = शून्य;
					spin_unlock(&layr->sync);
					वापस -EPROTO;
				पूर्ण
			पूर्ण
		पूर्ण

		pkt_len = cfpkt_getlen(pkt);

		/*
		 *  pkt_len is the accumulated length of the packet data
		 *  we have received so far.
		 *  Exit अगर frame करोesn't hold length.
		 */

		अगर (pkt_len < 2) अणु
			अगर (layr->usestx)
				cfpkt_add_head(pkt, &stx, 1);
			layr->incomplete_frm = pkt;
			spin_unlock(&layr->sync);
			वापस 0;
		पूर्ण

		/*
		 *  Find length of frame.
		 *  expectlen is the length we need क्रम a full frame.
		 */
		cfpkt_peek_head(pkt, &पंचांगp, 2);
		expectlen = le16_to_cpu(पंचांगp) + 2;
		/*
		 * Frame error handling
		 */
		अगर (expectlen < SERIAL_MINIUM_PACKET_SIZE
		    || expectlen > SERIAL_MAX_FRAMESIZE) अणु
			अगर (!layr->usestx) अणु
				अगर (pkt != शून्य)
					cfpkt_destroy(pkt);
				layr->incomplete_frm = शून्य;
				expectlen = 0;
				spin_unlock(&layr->sync);
				वापस -EPROTO;
			पूर्ण
			जारी;
		पूर्ण

		अगर (pkt_len < expectlen) अणु
			/* Too little received data */
			अगर (layr->usestx)
				cfpkt_add_head(pkt, &stx, 1);
			layr->incomplete_frm = pkt;
			spin_unlock(&layr->sync);
			वापस 0;
		पूर्ण

		/*
		 * Enough data क्रम at least one frame.
		 * Split the frame, अगर too दीर्घ
		 */
		अगर (pkt_len > expectlen)
			tail_pkt = cfpkt_split(pkt, expectlen);
		अन्यथा
			tail_pkt = शून्य;

		/* Send the first part of packet upwards.*/
		spin_unlock(&layr->sync);
		ret = layr->layer.up->receive(layr->layer.up, pkt);
		spin_lock(&layr->sync);
		अगर (ret == -EILSEQ) अणु
			अगर (layr->usestx) अणु
				अगर (tail_pkt != शून्य)
					pkt = cfpkt_append(pkt, tail_pkt, 0);
				/* Start search क्रम next STX अगर frame failed */
				जारी;
			पूर्ण अन्यथा अणु
				cfpkt_destroy(pkt);
				pkt = शून्य;
			पूर्ण
		पूर्ण

		pkt = tail_pkt;

	पूर्ण जबतक (pkt != शून्य);

	spin_unlock(&layr->sync);
	वापस 0;
पूर्ण

अटल पूर्णांक cfserl_transmit(काष्ठा cflayer *layer, काष्ठा cfpkt *newpkt)
अणु
	काष्ठा cfserl *layr = container_obj(layer);
	u8 पंचांगp8 = CFSERL_STX;
	अगर (layr->usestx)
		cfpkt_add_head(newpkt, &पंचांगp8, 1);
	वापस layer->dn->transmit(layer->dn, newpkt);
पूर्ण

अटल व्योम cfserl_ctrlcmd(काष्ठा cflayer *layr, क्रमागत caअगर_ctrlcmd ctrl,
			   पूर्णांक phyid)
अणु
	layr->up->ctrlcmd(layr->up, ctrl, phyid);
पूर्ण
