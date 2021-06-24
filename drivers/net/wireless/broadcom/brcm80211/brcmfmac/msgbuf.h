<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2014 Broadcom Corporation
 */
#अगर_अघोषित BRCMFMAC_MSGBUF_H
#घोषणा BRCMFMAC_MSGBUF_H

#अगर_घोषित CONFIG_BRCMFMAC_PROTO_MSGBUF

#घोषणा BRCMF_H2D_MSGRING_CONTROL_SUBMIT_MAX_ITEM	64
#घोषणा BRCMF_H2D_MSGRING_RXPOST_SUBMIT_MAX_ITEM	512
#घोषणा BRCMF_D2H_MSGRING_CONTROL_COMPLETE_MAX_ITEM	64
#घोषणा BRCMF_D2H_MSGRING_TX_COMPLETE_MAX_ITEM		1024
#घोषणा BRCMF_D2H_MSGRING_RX_COMPLETE_MAX_ITEM		512
#घोषणा BRCMF_H2D_TXFLOWRING_MAX_ITEM			512

#घोषणा BRCMF_H2D_MSGRING_CONTROL_SUBMIT_ITEMSIZE	40
#घोषणा BRCMF_H2D_MSGRING_RXPOST_SUBMIT_ITEMSIZE	32
#घोषणा BRCMF_D2H_MSGRING_CONTROL_COMPLETE_ITEMSIZE	24
#घोषणा BRCMF_D2H_MSGRING_TX_COMPLETE_ITEMSIZE_PRE_V7	16
#घोषणा BRCMF_D2H_MSGRING_TX_COMPLETE_ITEMSIZE		24
#घोषणा BRCMF_D2H_MSGRING_RX_COMPLETE_ITEMSIZE_PRE_V7	32
#घोषणा BRCMF_D2H_MSGRING_RX_COMPLETE_ITEMSIZE		40
#घोषणा BRCMF_H2D_TXFLOWRING_ITEMSIZE			48

काष्ठा msgbuf_buf_addr अणु
	__le32		low_addr;
	__le32		high_addr;
पूर्ण;

पूर्णांक brcmf_proto_msgbuf_rx_trigger(काष्ठा device *dev);
व्योम brcmf_msgbuf_delete_flowring(काष्ठा brcmf_pub *drvr, u16 flowid);
पूर्णांक brcmf_proto_msgbuf_attach(काष्ठा brcmf_pub *drvr);
व्योम brcmf_proto_msgbuf_detach(काष्ठा brcmf_pub *drvr);
#अन्यथा
अटल अंतरभूत पूर्णांक brcmf_proto_msgbuf_attach(काष्ठा brcmf_pub *drvr)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम brcmf_proto_msgbuf_detach(काष्ठा brcmf_pub *drvr) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* BRCMFMAC_MSGBUF_H */
