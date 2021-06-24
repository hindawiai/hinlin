<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2010 Broadcom Corporation
 */

/*******************************************************************************
 * Communicates with the करोngle by using dcmd codes.
 * For certain dcmd codes, the करोngle पूर्णांकerprets string data from the host.
 ******************************************************************************/

#समावेश <linux/types.h>
#समावेश <linux/netdevice.h>

#समावेश <brcmu_utils.h>
#समावेश <brcmu_wअगरi.h>

#समावेश "core.h"
#समावेश "bus.h"
#समावेश "fwsignal.h"
#समावेश "debug.h"
#समावेश "tracepoint.h"
#समावेश "proto.h"
#समावेश "bcdc.h"

काष्ठा brcmf_proto_bcdc_dcmd अणु
	__le32 cmd;	/* करोngle command value */
	__le32 len;	/* lower 16: output buflen;
			 * upper 16: input buflen (excludes header) */
	__le32 flags;	/* flag defns given below */
	__le32 status;	/* status code वापसed from the device */
पूर्ण;

/* BCDC flag definitions */
#घोषणा BCDC_DCMD_ERROR		0x01		/* 1=cmd failed */
#घोषणा BCDC_DCMD_SET		0x02		/* 0=get, 1=set cmd */
#घोषणा BCDC_DCMD_IF_MASK	0xF000		/* I/F index */
#घोषणा BCDC_DCMD_IF_SHIFT	12
#घोषणा BCDC_DCMD_ID_MASK	0xFFFF0000	/* id an cmd pairing */
#घोषणा BCDC_DCMD_ID_SHIFT	16		/* ID Mask shअगरt bits */
#घोषणा BCDC_DCMD_ID(flags)	\
	(((flags) & BCDC_DCMD_ID_MASK) >> BCDC_DCMD_ID_SHIFT)

/*
 * BCDC header - Broadcom specअगरic extension of CDC.
 * Used on data packets to convey priority across USB.
 */
#घोषणा	BCDC_HEADER_LEN		4
#घोषणा BCDC_PROTO_VER		2	/* Protocol version */
#घोषणा BCDC_FLAG_VER_MASK	0xf0	/* Protocol version mask */
#घोषणा BCDC_FLAG_VER_SHIFT	4	/* Protocol version shअगरt */
#घोषणा BCDC_FLAG_SUM_GOOD	0x04	/* Good RX checksums */
#घोषणा BCDC_FLAG_SUM_NEEDED	0x08	/* Dongle needs to करो TX checksums */
#घोषणा BCDC_PRIORITY_MASK	0x7
#घोषणा BCDC_FLAG2_IF_MASK	0x0f	/* packet rx पूर्णांकerface in APSTA */
#घोषणा BCDC_FLAG2_IF_SHIFT	0

#घोषणा BCDC_GET_IF_IDX(hdr) \
	((पूर्णांक)((((hdr)->flags2) & BCDC_FLAG2_IF_MASK) >> BCDC_FLAG2_IF_SHIFT))
#घोषणा BCDC_SET_IF_IDX(hdr, idx) \
	((hdr)->flags2 = (((hdr)->flags2 & ~BCDC_FLAG2_IF_MASK) | \
	((idx) << BCDC_FLAG2_IF_SHIFT)))

/**
 * काष्ठा brcmf_proto_bcdc_header - BCDC header क्रमmat
 *
 * @flags: flags contain protocol and checksum info.
 * @priority: 802.1d priority and USB flow control info (bit 4:7).
 * @flags2: additional flags containing करोngle पूर्णांकerface index.
 * @data_offset: start of packet data. header is following by firmware संकेतs.
 */
काष्ठा brcmf_proto_bcdc_header अणु
	u8 flags;
	u8 priority;
	u8 flags2;
	u8 data_offset;
पूर्ण;

/*
 * maximum length of firmware संकेत data between
 * the BCDC header and packet data in the tx path.
 */
#घोषणा BRCMF_PROT_FW_SIGNAL_MAX_TXBYTES	12

#घोषणा RETRIES 2 /* # of retries to retrieve matching dcmd response */
#घोषणा BUS_HEADER_LEN	(16+64)		/* Must be atleast SDPCM_RESERVE
					 * (amount of header tha might be added)
					 * plus any space that might be needed
					 * क्रम bus alignment padding.
					 */
काष्ठा brcmf_bcdc अणु
	u16 reqid;
	u8 bus_header[BUS_HEADER_LEN];
	काष्ठा brcmf_proto_bcdc_dcmd msg;
	अचिन्हित अक्षर buf[BRCMF_DCMD_MAXLEN];
	काष्ठा brcmf_fws_info *fws;
पूर्ण;


काष्ठा brcmf_fws_info *drvr_to_fws(काष्ठा brcmf_pub *drvr)
अणु
	काष्ठा brcmf_bcdc *bcdc = drvr->proto->pd;

	वापस bcdc->fws;
पूर्ण

अटल पूर्णांक
brcmf_proto_bcdc_msg(काष्ठा brcmf_pub *drvr, पूर्णांक अगरidx, uपूर्णांक cmd, व्योम *buf,
		     uपूर्णांक len, bool set)
अणु
	काष्ठा brcmf_bcdc *bcdc = (काष्ठा brcmf_bcdc *)drvr->proto->pd;
	काष्ठा brcmf_proto_bcdc_dcmd *msg = &bcdc->msg;
	u32 flags;

	brcmf_dbg(BCDC, "Enter\n");

	स_रखो(msg, 0, माप(काष्ठा brcmf_proto_bcdc_dcmd));

	msg->cmd = cpu_to_le32(cmd);
	msg->len = cpu_to_le32(len);
	flags = (++bcdc->reqid << BCDC_DCMD_ID_SHIFT);
	अगर (set)
		flags |= BCDC_DCMD_SET;
	flags = (flags & ~BCDC_DCMD_IF_MASK) |
		(अगरidx << BCDC_DCMD_IF_SHIFT);
	msg->flags = cpu_to_le32(flags);

	अगर (buf)
		स_नकल(bcdc->buf, buf, len);

	len += माप(*msg);
	अगर (len > BRCMF_TX_IOCTL_MAX_MSG_SIZE)
		len = BRCMF_TX_IOCTL_MAX_MSG_SIZE;

	/* Send request */
	वापस brcmf_bus_txctl(drvr->bus_अगर, (अचिन्हित अक्षर *)&bcdc->msg, len);
पूर्ण

अटल पूर्णांक brcmf_proto_bcdc_cmplt(काष्ठा brcmf_pub *drvr, u32 id, u32 len)
अणु
	पूर्णांक ret;
	काष्ठा brcmf_bcdc *bcdc = (काष्ठा brcmf_bcdc *)drvr->proto->pd;

	brcmf_dbg(BCDC, "Enter\n");
	len += माप(काष्ठा brcmf_proto_bcdc_dcmd);
	करो अणु
		ret = brcmf_bus_rxctl(drvr->bus_अगर, (अचिन्हित अक्षर *)&bcdc->msg,
				      len);
		अगर (ret < 0)
			अवरोध;
	पूर्ण जबतक (BCDC_DCMD_ID(le32_to_cpu(bcdc->msg.flags)) != id);

	वापस ret;
पूर्ण

अटल पूर्णांक
brcmf_proto_bcdc_query_dcmd(काष्ठा brcmf_pub *drvr, पूर्णांक अगरidx, uपूर्णांक cmd,
			    व्योम *buf, uपूर्णांक len, पूर्णांक *fwerr)
अणु
	काष्ठा brcmf_bcdc *bcdc = (काष्ठा brcmf_bcdc *)drvr->proto->pd;
	काष्ठा brcmf_proto_bcdc_dcmd *msg = &bcdc->msg;
	व्योम *info;
	पूर्णांक ret = 0, retries = 0;
	u32 id, flags;

	brcmf_dbg(BCDC, "Enter, cmd %d len %d\n", cmd, len);

	*fwerr = 0;
	ret = brcmf_proto_bcdc_msg(drvr, अगरidx, cmd, buf, len, false);
	अगर (ret < 0) अणु
		bphy_err(drvr, "brcmf_proto_bcdc_msg failed w/status %d\n",
			 ret);
		जाओ करोne;
	पूर्ण

retry:
	/* रुको क्रम पूर्णांकerrupt and get first fragment */
	ret = brcmf_proto_bcdc_cmplt(drvr, bcdc->reqid, len);
	अगर (ret < 0)
		जाओ करोne;

	flags = le32_to_cpu(msg->flags);
	id = (flags & BCDC_DCMD_ID_MASK) >> BCDC_DCMD_ID_SHIFT;

	अगर ((id < bcdc->reqid) && (++retries < RETRIES))
		जाओ retry;
	अगर (id != bcdc->reqid) अणु
		bphy_err(drvr, "%s: unexpected request id %d (expected %d)\n",
			 brcmf_अगरname(brcmf_get_अगरp(drvr, अगरidx)), id,
			 bcdc->reqid);
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	/* Check info buffer */
	info = (व्योम *)&bcdc->buf[0];

	/* Copy info buffer */
	अगर (buf) अणु
		अगर (ret < (पूर्णांक)len)
			len = ret;
		स_नकल(buf, info, len);
	पूर्ण

	ret = 0;

	/* Check the ERROR flag */
	अगर (flags & BCDC_DCMD_ERROR)
		*fwerr = le32_to_cpu(msg->status);
करोne:
	वापस ret;
पूर्ण

अटल पूर्णांक
brcmf_proto_bcdc_set_dcmd(काष्ठा brcmf_pub *drvr, पूर्णांक अगरidx, uपूर्णांक cmd,
			  व्योम *buf, uपूर्णांक len, पूर्णांक *fwerr)
अणु
	काष्ठा brcmf_bcdc *bcdc = (काष्ठा brcmf_bcdc *)drvr->proto->pd;
	काष्ठा brcmf_proto_bcdc_dcmd *msg = &bcdc->msg;
	पूर्णांक ret;
	u32 flags, id;

	brcmf_dbg(BCDC, "Enter, cmd %d len %d\n", cmd, len);

	*fwerr = 0;
	ret = brcmf_proto_bcdc_msg(drvr, अगरidx, cmd, buf, len, true);
	अगर (ret < 0)
		जाओ करोne;

	ret = brcmf_proto_bcdc_cmplt(drvr, bcdc->reqid, len);
	अगर (ret < 0)
		जाओ करोne;

	flags = le32_to_cpu(msg->flags);
	id = (flags & BCDC_DCMD_ID_MASK) >> BCDC_DCMD_ID_SHIFT;

	अगर (id != bcdc->reqid) अणु
		bphy_err(drvr, "%s: unexpected request id %d (expected %d)\n",
			 brcmf_अगरname(brcmf_get_अगरp(drvr, अगरidx)), id,
			 bcdc->reqid);
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	ret = 0;

	/* Check the ERROR flag */
	अगर (flags & BCDC_DCMD_ERROR)
		*fwerr = le32_to_cpu(msg->status);

करोne:
	वापस ret;
पूर्ण

अटल व्योम
brcmf_proto_bcdc_hdrpush(काष्ठा brcmf_pub *drvr, पूर्णांक अगरidx, u8 offset,
			 काष्ठा sk_buff *pktbuf)
अणु
	काष्ठा brcmf_proto_bcdc_header *h;

	brcmf_dbg(BCDC, "Enter\n");

	/* Push BDC header used to convey priority क्रम buses that करोn't */
	skb_push(pktbuf, BCDC_HEADER_LEN);

	h = (काष्ठा brcmf_proto_bcdc_header *)(pktbuf->data);

	h->flags = (BCDC_PROTO_VER << BCDC_FLAG_VER_SHIFT);
	अगर (pktbuf->ip_summed == CHECKSUM_PARTIAL)
		h->flags |= BCDC_FLAG_SUM_NEEDED;

	h->priority = (pktbuf->priority & BCDC_PRIORITY_MASK);
	h->flags2 = 0;
	h->data_offset = offset;
	BCDC_SET_IF_IDX(h, अगरidx);
	trace_brcmf_bcdchdr(pktbuf->data);
पूर्ण

अटल पूर्णांक
brcmf_proto_bcdc_hdrpull(काष्ठा brcmf_pub *drvr, bool करो_fws,
			 काष्ठा sk_buff *pktbuf, काष्ठा brcmf_अगर **अगरp)
अणु
	काष्ठा brcmf_proto_bcdc_header *h;
	काष्ठा brcmf_अगर *पंचांगp_अगर;

	brcmf_dbg(BCDC, "Enter\n");

	/* Pop BCDC header used to convey priority क्रम buses that करोn't */
	अगर (pktbuf->len <= BCDC_HEADER_LEN) अणु
		brcmf_dbg(INFO, "rx data too short (%d <= %d)\n",
			  pktbuf->len, BCDC_HEADER_LEN);
		वापस -EBADE;
	पूर्ण

	trace_brcmf_bcdchdr(pktbuf->data);
	h = (काष्ठा brcmf_proto_bcdc_header *)(pktbuf->data);

	पंचांगp_अगर = brcmf_get_अगरp(drvr, BCDC_GET_IF_IDX(h));
	अगर (!पंचांगp_अगर) अणु
		brcmf_dbg(INFO, "no matching ifp found\n");
		वापस -EBADE;
	पूर्ण
	अगर (((h->flags & BCDC_FLAG_VER_MASK) >> BCDC_FLAG_VER_SHIFT) !=
	    BCDC_PROTO_VER) अणु
		bphy_err(drvr, "%s: non-BCDC packet received, flags 0x%x\n",
			 brcmf_अगरname(पंचांगp_अगर), h->flags);
		वापस -EBADE;
	पूर्ण

	अगर (h->flags & BCDC_FLAG_SUM_GOOD) अणु
		brcmf_dbg(BCDC, "%s: BDC rcv, good checksum, flags 0x%x\n",
			  brcmf_अगरname(पंचांगp_अगर), h->flags);
		pktbuf->ip_summed = CHECKSUM_UNNECESSARY;
	पूर्ण

	pktbuf->priority = h->priority & BCDC_PRIORITY_MASK;

	skb_pull(pktbuf, BCDC_HEADER_LEN);
	अगर (करो_fws)
		brcmf_fws_hdrpull(पंचांगp_अगर, h->data_offset << 2, pktbuf);
	अन्यथा
		skb_pull(pktbuf, h->data_offset << 2);

	अगर (pktbuf->len == 0)
		वापस -ENODATA;

	अगर (अगरp != शून्य)
		*अगरp = पंचांगp_अगर;
	वापस 0;
पूर्ण

अटल पूर्णांक brcmf_proto_bcdc_tx_queue_data(काष्ठा brcmf_pub *drvr, पूर्णांक अगरidx,
					  काष्ठा sk_buff *skb)
अणु
	काष्ठा brcmf_अगर *अगरp = brcmf_get_अगरp(drvr, अगरidx);
	काष्ठा brcmf_bcdc *bcdc = drvr->proto->pd;

	अगर (!brcmf_fws_queue_skbs(bcdc->fws))
		वापस brcmf_proto_txdata(drvr, अगरidx, 0, skb);

	वापस brcmf_fws_process_skb(अगरp, skb);
पूर्ण

अटल पूर्णांक
brcmf_proto_bcdc_txdata(काष्ठा brcmf_pub *drvr, पूर्णांक अगरidx, u8 offset,
			काष्ठा sk_buff *pktbuf)
अणु
	brcmf_proto_bcdc_hdrpush(drvr, अगरidx, offset, pktbuf);
	वापस brcmf_bus_txdata(drvr->bus_अगर, pktbuf);
पूर्ण

व्योम brcmf_proto_bcdc_txflowblock(काष्ठा device *dev, bool state)
अणु
	काष्ठा brcmf_bus *bus_अगर = dev_get_drvdata(dev);
	काष्ठा brcmf_pub *drvr = bus_अगर->drvr;

	brcmf_dbg(TRACE, "Enter\n");

	brcmf_fws_bus_blocked(drvr, state);
पूर्ण

व्योम
brcmf_proto_bcdc_txcomplete(काष्ठा device *dev, काष्ठा sk_buff *txp,
			    bool success)
अणु
	काष्ठा brcmf_bus *bus_अगर = dev_get_drvdata(dev);
	काष्ठा brcmf_bcdc *bcdc = bus_अगर->drvr->proto->pd;
	काष्ठा brcmf_अगर *अगरp;

	/* aरुको txstatus संकेत क्रम firmware अगर active */
	अगर (brcmf_fws_fc_active(bcdc->fws)) अणु
		अगर (!success)
			brcmf_fws_bustxfail(bcdc->fws, txp);
	पूर्ण अन्यथा अणु
		अगर (brcmf_proto_bcdc_hdrpull(bus_अगर->drvr, false, txp, &अगरp))
			brcmu_pkt_buf_मुक्त_skb(txp);
		अन्यथा
			brcmf_txfinalize(अगरp, txp, success);
	पूर्ण
पूर्ण

अटल व्योम
brcmf_proto_bcdc_configure_addr_mode(काष्ठा brcmf_pub *drvr, पूर्णांक अगरidx,
				     क्रमागत proto_addr_mode addr_mode)
अणु
पूर्ण

अटल व्योम
brcmf_proto_bcdc_delete_peer(काष्ठा brcmf_pub *drvr, पूर्णांक अगरidx,
			     u8 peer[ETH_ALEN])
अणु
पूर्ण

अटल व्योम
brcmf_proto_bcdc_add_tdls_peer(काष्ठा brcmf_pub *drvr, पूर्णांक अगरidx,
			       u8 peer[ETH_ALEN])
अणु
पूर्ण

अटल व्योम brcmf_proto_bcdc_rxreorder(काष्ठा brcmf_अगर *अगरp,
				       काष्ठा sk_buff *skb, bool inirq)
अणु
	brcmf_fws_rxreorder(अगरp, skb, inirq);
पूर्ण

अटल व्योम
brcmf_proto_bcdc_add_अगर(काष्ठा brcmf_अगर *अगरp)
अणु
	brcmf_fws_add_पूर्णांकerface(अगरp);
पूर्ण

अटल व्योम
brcmf_proto_bcdc_del_अगर(काष्ठा brcmf_अगर *अगरp)
अणु
	brcmf_fws_del_पूर्णांकerface(अगरp);
पूर्ण

अटल व्योम
brcmf_proto_bcdc_reset_अगर(काष्ठा brcmf_अगर *अगरp)
अणु
	brcmf_fws_reset_पूर्णांकerface(अगरp);
पूर्ण

अटल पूर्णांक
brcmf_proto_bcdc_init_करोne(काष्ठा brcmf_pub *drvr)
अणु
	काष्ठा brcmf_bcdc *bcdc = drvr->proto->pd;
	काष्ठा brcmf_fws_info *fws;

	fws = brcmf_fws_attach(drvr);
	अगर (IS_ERR(fws))
		वापस PTR_ERR(fws);

	bcdc->fws = fws;
	वापस 0;
पूर्ण

अटल व्योम brcmf_proto_bcdc_debugfs_create(काष्ठा brcmf_pub *drvr)
अणु
	brcmf_fws_debugfs_create(drvr);
पूर्ण

पूर्णांक brcmf_proto_bcdc_attach(काष्ठा brcmf_pub *drvr)
अणु
	काष्ठा brcmf_bcdc *bcdc;

	bcdc = kzalloc(माप(*bcdc), GFP_ATOMIC);
	अगर (!bcdc)
		जाओ fail;

	/* ensure that the msg buf directly follows the cdc msg काष्ठा */
	अगर ((अचिन्हित दीर्घ)(&bcdc->msg + 1) != (अचिन्हित दीर्घ)bcdc->buf) अणु
		bphy_err(drvr, "struct brcmf_proto_bcdc is not correctly defined\n");
		जाओ fail;
	पूर्ण

	drvr->proto->hdrpull = brcmf_proto_bcdc_hdrpull;
	drvr->proto->query_dcmd = brcmf_proto_bcdc_query_dcmd;
	drvr->proto->set_dcmd = brcmf_proto_bcdc_set_dcmd;
	drvr->proto->tx_queue_data = brcmf_proto_bcdc_tx_queue_data;
	drvr->proto->txdata = brcmf_proto_bcdc_txdata;
	drvr->proto->configure_addr_mode = brcmf_proto_bcdc_configure_addr_mode;
	drvr->proto->delete_peer = brcmf_proto_bcdc_delete_peer;
	drvr->proto->add_tdls_peer = brcmf_proto_bcdc_add_tdls_peer;
	drvr->proto->rxreorder = brcmf_proto_bcdc_rxreorder;
	drvr->proto->add_अगर = brcmf_proto_bcdc_add_अगर;
	drvr->proto->del_अगर = brcmf_proto_bcdc_del_अगर;
	drvr->proto->reset_अगर = brcmf_proto_bcdc_reset_अगर;
	drvr->proto->init_करोne = brcmf_proto_bcdc_init_करोne;
	drvr->proto->debugfs_create = brcmf_proto_bcdc_debugfs_create;
	drvr->proto->pd = bcdc;

	drvr->hdrlen += BCDC_HEADER_LEN + BRCMF_PROT_FW_SIGNAL_MAX_TXBYTES;
	drvr->bus_अगर->maxctl = BRCMF_DCMD_MAXLEN +
			माप(काष्ठा brcmf_proto_bcdc_dcmd);
	वापस 0;

fail:
	kमुक्त(bcdc);
	वापस -ENOMEM;
पूर्ण

व्योम brcmf_proto_bcdc_detach(काष्ठा brcmf_pub *drvr)
अणु
	काष्ठा brcmf_bcdc *bcdc = drvr->proto->pd;

	drvr->proto->pd = शून्य;
	brcmf_fws_detach(bcdc->fws);
	kमुक्त(bcdc);
पूर्ण
