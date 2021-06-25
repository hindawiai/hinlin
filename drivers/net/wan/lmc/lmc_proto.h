<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LMC_PROTO_H_
#घोषणा _LMC_PROTO_H_

#समावेश <linux/hdlc.h>

व्योम lmc_proto_attach(lmc_softc_t *sc);
पूर्णांक lmc_proto_ioctl(lmc_softc_t *sc, काष्ठा अगरreq *अगरr, पूर्णांक cmd);
पूर्णांक lmc_proto_खोलो(lmc_softc_t *sc);
व्योम lmc_proto_बंद(lmc_softc_t *sc);
__be16 lmc_proto_type(lmc_softc_t *sc, काष्ठा sk_buff *skb);
व्योम lmc_proto_netअगर(lmc_softc_t *sc, काष्ठा sk_buff *skb);

अटल अंतरभूत lmc_softc_t* dev_to_sc(काष्ठा net_device *dev)
अणु
	वापस (lmc_softc_t *)dev_to_hdlc(dev)->priv;
पूर्ण

#पूर्ण_अगर
