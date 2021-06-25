<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * CAIF Framing Layer.
 *
 * Copyright (C) ST-Ericsson AB 2010
 * Author:	Sjur Brendeland
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ":%s(): " fmt, __func__

#समावेश <linux/मानकघोष.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/crc-ccitt.h>
#समावेश <linux/netdevice.h>
#समावेश <net/caअगर/caअगर_layer.h>
#समावेश <net/caअगर/cfpkt.h>
#समावेश <net/caअगर/cffrml.h>

#घोषणा container_obj(layr) container_of(layr, काष्ठा cffrml, layer)

काष्ठा cffrml अणु
	काष्ठा cflayer layer;
	bool करोfcs;		/* !< FCS active */
	पूर्णांक __percpu		*pcpu_refcnt;
पूर्ण;

अटल पूर्णांक cffrml_receive(काष्ठा cflayer *layr, काष्ठा cfpkt *pkt);
अटल पूर्णांक cffrml_transmit(काष्ठा cflayer *layr, काष्ठा cfpkt *pkt);
अटल व्योम cffrml_ctrlcmd(काष्ठा cflayer *layr, क्रमागत caअगर_ctrlcmd ctrl,
			   पूर्णांक phyid);

अटल u32 cffrml_rcv_error;
अटल u32 cffrml_rcv_checsum_error;
काष्ठा cflayer *cffrml_create(u16 phyid, bool use_fcs)
अणु
	काष्ठा cffrml *this = kzalloc(माप(काष्ठा cffrml), GFP_ATOMIC);
	अगर (!this)
		वापस शून्य;
	this->pcpu_refcnt = alloc_percpu(पूर्णांक);
	अगर (this->pcpu_refcnt == शून्य) अणु
		kमुक्त(this);
		वापस शून्य;
	पूर्ण

	caअगर_निश्चित(दुरत्व(काष्ठा cffrml, layer) == 0);

	this->layer.receive = cffrml_receive;
	this->layer.transmit = cffrml_transmit;
	this->layer.ctrlcmd = cffrml_ctrlcmd;
	snम_लिखो(this->layer.name, CAIF_LAYER_NAME_SZ, "frm%d", phyid);
	this->करोfcs = use_fcs;
	this->layer.id = phyid;
	वापस (काष्ठा cflayer *) this;
पूर्ण

व्योम cffrml_मुक्त(काष्ठा cflayer *layer)
अणु
	काष्ठा cffrml *this = container_obj(layer);
	मुक्त_percpu(this->pcpu_refcnt);
	kमुक्त(layer);
पूर्ण

व्योम cffrml_set_uplayer(काष्ठा cflayer *this, काष्ठा cflayer *up)
अणु
	this->up = up;
पूर्ण

व्योम cffrml_set_dnlayer(काष्ठा cflayer *this, काष्ठा cflayer *dn)
अणु
	this->dn = dn;
पूर्ण

अटल u16 cffrml_checksum(u16 chks, व्योम *buf, u16 len)
अणु
	/* FIXME: FCS should be moved to glue in order to use OS-Specअगरic
	 * solutions
	 */
	वापस crc_ccitt(chks, buf, len);
पूर्ण

अटल पूर्णांक cffrml_receive(काष्ठा cflayer *layr, काष्ठा cfpkt *pkt)
अणु
	u16 पंचांगp;
	u16 len;
	u16 hdrchks;
	पूर्णांक pktchks;
	काष्ठा cffrml *this;
	this = container_obj(layr);

	cfpkt_extr_head(pkt, &पंचांगp, 2);
	len = le16_to_cpu(पंचांगp);

	/* Subtract क्रम FCS on length अगर FCS is not used. */
	अगर (!this->करोfcs)
		len -= 2;

	अगर (cfpkt_setlen(pkt, len) < 0) अणु
		++cffrml_rcv_error;
		pr_err("Framing length error (%d)\n", len);
		cfpkt_destroy(pkt);
		वापस -EPROTO;
	पूर्ण
	/*
	 * Don't do extract if FCS is false, rather do setlen - then we don't
	 * get a cache-miss.
	 */
	अगर (this->करोfcs) अणु
		cfpkt_extr_trail(pkt, &पंचांगp, 2);
		hdrchks = le16_to_cpu(पंचांगp);
		pktchks = cfpkt_iterate(pkt, cffrml_checksum, 0xffff);
		अगर (pktchks != hdrchks) अणु
			cfpkt_add_trail(pkt, &पंचांगp, 2);
			++cffrml_rcv_error;
			++cffrml_rcv_checsum_error;
			pr_info("Frame checksum error (0x%x != 0x%x)\n",
				hdrchks, pktchks);
			वापस -EILSEQ;
		पूर्ण
	पूर्ण
	अगर (cfpkt_erroneous(pkt)) अणु
		++cffrml_rcv_error;
		pr_err("Packet is erroneous!\n");
		cfpkt_destroy(pkt);
		वापस -EPROTO;
	पूर्ण

	अगर (layr->up == शून्य) अणु
		pr_err("Layr up is missing!\n");
		cfpkt_destroy(pkt);
		वापस -EINVAL;
	पूर्ण

	वापस layr->up->receive(layr->up, pkt);
पूर्ण

अटल पूर्णांक cffrml_transmit(काष्ठा cflayer *layr, काष्ठा cfpkt *pkt)
अणु
	u16 chks;
	u16 len;
	__le16 data;

	काष्ठा cffrml *this = container_obj(layr);
	अगर (this->करोfcs) अणु
		chks = cfpkt_iterate(pkt, cffrml_checksum, 0xffff);
		data = cpu_to_le16(chks);
		cfpkt_add_trail(pkt, &data, 2);
	पूर्ण अन्यथा अणु
		cfpkt_pad_trail(pkt, 2);
	पूर्ण
	len = cfpkt_getlen(pkt);
	data = cpu_to_le16(len);
	cfpkt_add_head(pkt, &data, 2);
	cfpkt_info(pkt)->hdr_len += 2;
	अगर (cfpkt_erroneous(pkt)) अणु
		pr_err("Packet is erroneous!\n");
		cfpkt_destroy(pkt);
		वापस -EPROTO;
	पूर्ण

	अगर (layr->dn == शून्य) अणु
		cfpkt_destroy(pkt);
		वापस -ENODEV;

	पूर्ण
	वापस layr->dn->transmit(layr->dn, pkt);
पूर्ण

अटल व्योम cffrml_ctrlcmd(काष्ठा cflayer *layr, क्रमागत caअगर_ctrlcmd ctrl,
			   पूर्णांक phyid)
अणु
	अगर (layr->up && layr->up->ctrlcmd)
		layr->up->ctrlcmd(layr->up, ctrl, layr->id);
पूर्ण

व्योम cffrml_put(काष्ठा cflayer *layr)
अणु
	काष्ठा cffrml *this = container_obj(layr);
	अगर (layr != शून्य && this->pcpu_refcnt != शून्य)
		this_cpu_dec(*this->pcpu_refcnt);
पूर्ण

व्योम cffrml_hold(काष्ठा cflayer *layr)
अणु
	काष्ठा cffrml *this = container_obj(layr);
	अगर (layr != शून्य && this->pcpu_refcnt != शून्य)
		this_cpu_inc(*this->pcpu_refcnt);
पूर्ण

पूर्णांक cffrml_refcnt_पढ़ो(काष्ठा cflayer *layr)
अणु
	पूर्णांक i, refcnt = 0;
	काष्ठा cffrml *this = container_obj(layr);
	क्रम_each_possible_cpu(i)
		refcnt += *per_cpu_ptr(this->pcpu_refcnt, i);
	वापस refcnt;
पूर्ण
