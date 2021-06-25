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
#समावेश <यंत्र/unaligned.h>
#समावेश <net/caअगर/caअगर_layer.h>
#समावेश <net/caअगर/cfsrvl.h>
#समावेश <net/caअगर/cfpkt.h>

#घोषणा container_obj(layr) container_of(layr, काष्ठा cfrfml, serv.layer)
#घोषणा RFM_SEGMENTATION_BIT 0x01
#घोषणा RFM_HEAD_SIZE 7

अटल पूर्णांक cfrfml_receive(काष्ठा cflayer *layr, काष्ठा cfpkt *pkt);
अटल पूर्णांक cfrfml_transmit(काष्ठा cflayer *layr, काष्ठा cfpkt *pkt);

काष्ठा cfrfml अणु
	काष्ठा cfsrvl serv;
	काष्ठा cfpkt *incomplete_frm;
	पूर्णांक fragment_size;
	u8  seghead[6];
	u16 pdu_size;
	/* Protects serialized processing of packets */
	spinlock_t sync;
पूर्ण;

अटल व्योम cfrfml_release(काष्ठा cflayer *layer)
अणु
	काष्ठा cfsrvl *srvl = container_of(layer, काष्ठा cfsrvl, layer);
	काष्ठा cfrfml *rfml = container_obj(&srvl->layer);

	अगर (rfml->incomplete_frm)
		cfpkt_destroy(rfml->incomplete_frm);

	kमुक्त(srvl);
पूर्ण

काष्ठा cflayer *cfrfml_create(u8 channel_id, काष्ठा dev_info *dev_info,
			      पूर्णांक mtu_size)
अणु
	पूर्णांक पंचांगp;
	काष्ठा cfrfml *this = kzalloc(माप(काष्ठा cfrfml), GFP_ATOMIC);

	अगर (!this)
		वापस शून्य;

	cfsrvl_init(&this->serv, channel_id, dev_info, false);
	this->serv.release = cfrfml_release;
	this->serv.layer.receive = cfrfml_receive;
	this->serv.layer.transmit = cfrfml_transmit;

	/* Round करोwn to बंदst multiple of 16 */
	पंचांगp = (mtu_size - RFM_HEAD_SIZE - 6) / 16;
	पंचांगp *= 16;

	this->fragment_size = पंचांगp;
	spin_lock_init(&this->sync);
	snम_लिखो(this->serv.layer.name, CAIF_LAYER_NAME_SZ,
		"rfm%d", channel_id);

	वापस &this->serv.layer;
पूर्ण

अटल काष्ठा cfpkt *rfm_append(काष्ठा cfrfml *rfml, अक्षर *seghead,
				काष्ठा cfpkt *pkt, पूर्णांक *err)
अणु
	काष्ठा cfpkt *पंचांगppkt;
	*err = -EPROTO;
	/* n-th but not last segment */

	अगर (cfpkt_extr_head(pkt, seghead, 6) < 0)
		वापस शून्य;

	/* Verअगरy correct header */
	अगर (स_भेद(seghead, rfml->seghead, 6) != 0)
		वापस शून्य;

	पंचांगppkt = cfpkt_append(rfml->incomplete_frm, pkt,
			rfml->pdu_size + RFM_HEAD_SIZE);

	/* If cfpkt_append failes input pkts are not मुक्तd */
	*err = -ENOMEM;
	अगर (पंचांगppkt == शून्य)
		वापस शून्य;

	*err = 0;
	वापस पंचांगppkt;
पूर्ण

अटल पूर्णांक cfrfml_receive(काष्ठा cflayer *layr, काष्ठा cfpkt *pkt)
अणु
	u8 पंचांगp;
	bool segmented;
	पूर्णांक err;
	u8 seghead[6];
	काष्ठा cfrfml *rfml;
	काष्ठा cfpkt *पंचांगppkt = शून्य;

	caअगर_निश्चित(layr->up != शून्य);
	caअगर_निश्चित(layr->receive != शून्य);
	rfml = container_obj(layr);
	spin_lock(&rfml->sync);

	err = -EPROTO;
	अगर (cfpkt_extr_head(pkt, &पंचांगp, 1) < 0)
		जाओ out;
	segmented = पंचांगp & RFM_SEGMENTATION_BIT;

	अगर (segmented) अणु
		अगर (rfml->incomplete_frm == शून्य) अणु
			/* Initial Segment */
			अगर (cfpkt_peek_head(pkt, rfml->seghead, 6) != 0)
				जाओ out;

			rfml->pdu_size = get_unaligned_le16(rfml->seghead+4);

			अगर (cfpkt_erroneous(pkt))
				जाओ out;
			rfml->incomplete_frm = pkt;
			pkt = शून्य;
		पूर्ण अन्यथा अणु

			पंचांगppkt = rfm_append(rfml, seghead, pkt, &err);
			अगर (पंचांगppkt == शून्य)
				जाओ out;

			अगर (cfpkt_erroneous(पंचांगppkt))
				जाओ out;

			rfml->incomplete_frm = पंचांगppkt;


			अगर (cfpkt_erroneous(पंचांगppkt))
				जाओ out;
		पूर्ण
		err = 0;
		जाओ out;
	पूर्ण

	अगर (rfml->incomplete_frm) अणु

		/* Last Segment */
		पंचांगppkt = rfm_append(rfml, seghead, pkt, &err);
		अगर (पंचांगppkt == शून्य)
			जाओ out;

		अगर (cfpkt_erroneous(पंचांगppkt))
			जाओ out;

		rfml->incomplete_frm = शून्य;
		pkt = पंचांगppkt;
		पंचांगppkt = शून्य;

		/* Verअगरy that length is correct */
		err = -EPROTO;
		अगर (rfml->pdu_size != cfpkt_getlen(pkt) - RFM_HEAD_SIZE + 1)
			जाओ out;
	पूर्ण

	err = rfml->serv.layer.up->receive(rfml->serv.layer.up, pkt);

out:

	अगर (err != 0) अणु
		अगर (पंचांगppkt)
			cfpkt_destroy(पंचांगppkt);
		अगर (pkt)
			cfpkt_destroy(pkt);
		अगर (rfml->incomplete_frm)
			cfpkt_destroy(rfml->incomplete_frm);
		rfml->incomplete_frm = शून्य;

		pr_info("Connection error %d triggered on RFM link\n", err);

		/* Trigger connection error upon failure.*/
		layr->up->ctrlcmd(layr->up, CAIF_CTRLCMD_REMOTE_SHUTDOWN_IND,
					rfml->serv.dev_info.id);
	पूर्ण
	spin_unlock(&rfml->sync);

	अगर (unlikely(err == -EAGAIN))
		/* It is not possible to recover after drop of a fragment */
		err = -EIO;

	वापस err;
पूर्ण


अटल पूर्णांक cfrfml_transmit_segment(काष्ठा cfrfml *rfml, काष्ठा cfpkt *pkt)
अणु
	caअगर_निश्चित(cfpkt_getlen(pkt) < rfml->fragment_size + RFM_HEAD_SIZE);

	/* Add info क्रम MUX-layer to route the packet out. */
	cfpkt_info(pkt)->channel_id = rfml->serv.layer.id;

	/*
	 * To optimize alignment, we add up the size of CAIF header beक्रमe
	 * payload.
	 */
	cfpkt_info(pkt)->hdr_len = RFM_HEAD_SIZE;
	cfpkt_info(pkt)->dev_info = &rfml->serv.dev_info;

	वापस rfml->serv.layer.dn->transmit(rfml->serv.layer.dn, pkt);
पूर्ण

अटल पूर्णांक cfrfml_transmit(काष्ठा cflayer *layr, काष्ठा cfpkt *pkt)
अणु
	पूर्णांक err;
	u8 seg;
	u8 head[6];
	काष्ठा cfpkt *rearpkt = शून्य;
	काष्ठा cfpkt *frontpkt = pkt;
	काष्ठा cfrfml *rfml = container_obj(layr);

	caअगर_निश्चित(layr->dn != शून्य);
	caअगर_निश्चित(layr->dn->transmit != शून्य);

	अगर (!cfsrvl_पढ़ोy(&rfml->serv, &err))
		जाओ out;

	err = -EPROTO;
	अगर (cfpkt_getlen(pkt) <= RFM_HEAD_SIZE-1)
		जाओ out;

	err = 0;
	अगर (cfpkt_getlen(pkt) > rfml->fragment_size + RFM_HEAD_SIZE)
		err = cfpkt_peek_head(pkt, head, 6);

	अगर (err != 0)
		जाओ out;

	जबतक (cfpkt_getlen(frontpkt) > rfml->fragment_size + RFM_HEAD_SIZE) अणु

		seg = 1;
		err = -EPROTO;

		अगर (cfpkt_add_head(frontpkt, &seg, 1) < 0)
			जाओ out;
		/*
		 * On OOM error cfpkt_split वापसs शून्य.
		 *
		 * NOTE: Segmented pdu is not correctly aligned.
		 * This has negative perक्रमmance impact.
		 */

		rearpkt = cfpkt_split(frontpkt, rfml->fragment_size);
		अगर (rearpkt == शून्य)
			जाओ out;

		err = cfrfml_transmit_segment(rfml, frontpkt);

		अगर (err != 0) अणु
			frontpkt = शून्य;
			जाओ out;
		पूर्ण

		frontpkt = rearpkt;
		rearpkt = शून्य;

		err = -EPROTO;
		अगर (cfpkt_add_head(frontpkt, head, 6) < 0)
			जाओ out;

	पूर्ण

	seg = 0;
	err = -EPROTO;

	अगर (cfpkt_add_head(frontpkt, &seg, 1) < 0)
		जाओ out;

	err = cfrfml_transmit_segment(rfml, frontpkt);

	frontpkt = शून्य;
out:

	अगर (err != 0) अणु
		pr_info("Connection error %d triggered on RFM link\n", err);
		/* Trigger connection error upon failure.*/

		layr->up->ctrlcmd(layr->up, CAIF_CTRLCMD_REMOTE_SHUTDOWN_IND,
					rfml->serv.dev_info.id);

		अगर (rearpkt)
			cfpkt_destroy(rearpkt);

		अगर (frontpkt)
			cfpkt_destroy(frontpkt);
	पूर्ण

	वापस err;
पूर्ण
