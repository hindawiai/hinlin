<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2013 Broadcom Corporation
 */
#अगर_अघोषित BRCMFMAC_PROTO_H
#घोषणा BRCMFMAC_PROTO_H


क्रमागत proto_addr_mode अणु
	ADDR_INसूचीECT	= 0,
	ADDR_सूचीECT
पूर्ण;

काष्ठा brcmf_skb_reorder_data अणु
	u8 *reorder;
पूर्ण;

काष्ठा brcmf_proto अणु
	पूर्णांक (*hdrpull)(काष्ठा brcmf_pub *drvr, bool करो_fws,
		       काष्ठा sk_buff *skb, काष्ठा brcmf_अगर **अगरp);
	पूर्णांक (*query_dcmd)(काष्ठा brcmf_pub *drvr, पूर्णांक अगरidx, uपूर्णांक cmd,
			  व्योम *buf, uपूर्णांक len, पूर्णांक *fwerr);
	पूर्णांक (*set_dcmd)(काष्ठा brcmf_pub *drvr, पूर्णांक अगरidx, uपूर्णांक cmd, व्योम *buf,
			uपूर्णांक len, पूर्णांक *fwerr);
	पूर्णांक (*tx_queue_data)(काष्ठा brcmf_pub *drvr, पूर्णांक अगरidx,
			     काष्ठा sk_buff *skb);
	पूर्णांक (*txdata)(काष्ठा brcmf_pub *drvr, पूर्णांक अगरidx, u8 offset,
		      काष्ठा sk_buff *skb);
	व्योम (*configure_addr_mode)(काष्ठा brcmf_pub *drvr, पूर्णांक अगरidx,
				    क्रमागत proto_addr_mode addr_mode);
	व्योम (*delete_peer)(काष्ठा brcmf_pub *drvr, पूर्णांक अगरidx,
			    u8 peer[ETH_ALEN]);
	व्योम (*add_tdls_peer)(काष्ठा brcmf_pub *drvr, पूर्णांक अगरidx,
			      u8 peer[ETH_ALEN]);
	व्योम (*rxreorder)(काष्ठा brcmf_अगर *अगरp, काष्ठा sk_buff *skb, bool inirq);
	व्योम (*add_अगर)(काष्ठा brcmf_अगर *अगरp);
	व्योम (*del_अगर)(काष्ठा brcmf_अगर *अगरp);
	व्योम (*reset_अगर)(काष्ठा brcmf_अगर *अगरp);
	पूर्णांक (*init_करोne)(काष्ठा brcmf_pub *drvr);
	व्योम (*debugfs_create)(काष्ठा brcmf_pub *drvr);
	व्योम *pd;
पूर्ण;


पूर्णांक brcmf_proto_attach(काष्ठा brcmf_pub *drvr);
व्योम brcmf_proto_detach(काष्ठा brcmf_pub *drvr);

अटल अंतरभूत पूर्णांक brcmf_proto_hdrpull(काष्ठा brcmf_pub *drvr, bool करो_fws,
				      काष्ठा sk_buff *skb,
				      काष्ठा brcmf_अगर **अगरp)
अणु
	काष्ठा brcmf_अगर *पंचांगp = शून्य;

	/* assure protocol is always called with
	 * non-null initialized poपूर्णांकer.
	 */
	अगर (अगरp)
		*अगरp = शून्य;
	अन्यथा
		अगरp = &पंचांगp;
	वापस drvr->proto->hdrpull(drvr, करो_fws, skb, अगरp);
पूर्ण
अटल अंतरभूत पूर्णांक brcmf_proto_query_dcmd(काष्ठा brcmf_pub *drvr, पूर्णांक अगरidx,
					 uपूर्णांक cmd, व्योम *buf, uपूर्णांक len,
					 पूर्णांक *fwerr)
अणु
	वापस drvr->proto->query_dcmd(drvr, अगरidx, cmd, buf, len,fwerr);
पूर्ण
अटल अंतरभूत पूर्णांक brcmf_proto_set_dcmd(काष्ठा brcmf_pub *drvr, पूर्णांक अगरidx,
				       uपूर्णांक cmd, व्योम *buf, uपूर्णांक len,
				       पूर्णांक *fwerr)
अणु
	वापस drvr->proto->set_dcmd(drvr, अगरidx, cmd, buf, len, fwerr);
पूर्ण

अटल अंतरभूत पूर्णांक brcmf_proto_tx_queue_data(काष्ठा brcmf_pub *drvr, पूर्णांक अगरidx,
					    काष्ठा sk_buff *skb)
अणु
	वापस drvr->proto->tx_queue_data(drvr, अगरidx, skb);
पूर्ण

अटल अंतरभूत पूर्णांक brcmf_proto_txdata(काष्ठा brcmf_pub *drvr, पूर्णांक अगरidx,
				     u8 offset, काष्ठा sk_buff *skb)
अणु
	वापस drvr->proto->txdata(drvr, अगरidx, offset, skb);
पूर्ण
अटल अंतरभूत व्योम
brcmf_proto_configure_addr_mode(काष्ठा brcmf_pub *drvr, पूर्णांक अगरidx,
				क्रमागत proto_addr_mode addr_mode)
अणु
	drvr->proto->configure_addr_mode(drvr, अगरidx, addr_mode);
पूर्ण
अटल अंतरभूत व्योम
brcmf_proto_delete_peer(काष्ठा brcmf_pub *drvr, पूर्णांक अगरidx, u8 peer[ETH_ALEN])
अणु
	drvr->proto->delete_peer(drvr, अगरidx, peer);
पूर्ण
अटल अंतरभूत व्योम
brcmf_proto_add_tdls_peer(काष्ठा brcmf_pub *drvr, पूर्णांक अगरidx, u8 peer[ETH_ALEN])
अणु
	drvr->proto->add_tdls_peer(drvr, अगरidx, peer);
पूर्ण
अटल अंतरभूत bool brcmf_proto_is_reorder_skb(काष्ठा sk_buff *skb)
अणु
	काष्ठा brcmf_skb_reorder_data *rd;

	rd = (काष्ठा brcmf_skb_reorder_data *)skb->cb;
	वापस !!rd->reorder;
पूर्ण

अटल अंतरभूत व्योम
brcmf_proto_rxreorder(काष्ठा brcmf_अगर *अगरp, काष्ठा sk_buff *skb, bool inirq)
अणु
	अगरp->drvr->proto->rxreorder(अगरp, skb, inirq);
पूर्ण

अटल अंतरभूत व्योम
brcmf_proto_add_अगर(काष्ठा brcmf_pub *drvr, काष्ठा brcmf_अगर *अगरp)
अणु
	अगर (!drvr->proto->add_अगर)
		वापस;
	drvr->proto->add_अगर(अगरp);
पूर्ण

अटल अंतरभूत व्योम
brcmf_proto_del_अगर(काष्ठा brcmf_pub *drvr, काष्ठा brcmf_अगर *अगरp)
अणु
	अगर (!drvr->proto->del_अगर)
		वापस;
	drvr->proto->del_अगर(अगरp);
पूर्ण

अटल अंतरभूत व्योम
brcmf_proto_reset_अगर(काष्ठा brcmf_pub *drvr, काष्ठा brcmf_अगर *अगरp)
अणु
	अगर (!drvr->proto->reset_अगर)
		वापस;
	drvr->proto->reset_अगर(अगरp);
पूर्ण

अटल अंतरभूत पूर्णांक
brcmf_proto_init_करोne(काष्ठा brcmf_pub *drvr)
अणु
	अगर (!drvr->proto->init_करोne)
		वापस 0;
	वापस drvr->proto->init_करोne(drvr);
पूर्ण

अटल अंतरभूत व्योम
brcmf_proto_debugfs_create(काष्ठा brcmf_pub *drvr)
अणु
	drvr->proto->debugfs_create(drvr);
पूर्ण

#पूर्ण_अगर /* BRCMFMAC_PROTO_H */
