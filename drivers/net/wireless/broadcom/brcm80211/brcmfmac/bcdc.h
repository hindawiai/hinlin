<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2013 Broadcom Corporation
 */
#अगर_अघोषित BRCMFMAC_BCDC_H
#घोषणा BRCMFMAC_BCDC_H

#अगर_घोषित CONFIG_BRCMFMAC_PROTO_BCDC
पूर्णांक brcmf_proto_bcdc_attach(काष्ठा brcmf_pub *drvr);
व्योम brcmf_proto_bcdc_detach(काष्ठा brcmf_pub *drvr);
व्योम brcmf_proto_bcdc_txflowblock(काष्ठा device *dev, bool state);
व्योम brcmf_proto_bcdc_txcomplete(काष्ठा device *dev, काष्ठा sk_buff *txp,
				 bool success);
काष्ठा brcmf_fws_info *drvr_to_fws(काष्ठा brcmf_pub *drvr);
#अन्यथा
अटल अंतरभूत पूर्णांक brcmf_proto_bcdc_attach(काष्ठा brcmf_pub *drvr) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम brcmf_proto_bcdc_detach(काष्ठा brcmf_pub *drvr) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* BRCMFMAC_BCDC_H */
