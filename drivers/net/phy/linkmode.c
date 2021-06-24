<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
#समावेश <linux/linkmode.h>

/**
 * linkmode_resolve_छोड़ो - resolve the allowable छोड़ो modes
 * @local_adv: local advertisement in ethtool क्रमmat
 * @partner_adv: partner advertisement in ethtool क्रमmat
 * @tx_छोड़ो: poपूर्णांकer to bool to indicate whether transmit छोड़ो should be
 * enabled.
 * @rx_छोड़ो: poपूर्णांकer to bool to indicate whether receive छोड़ो should be
 * enabled.
 *
 * Flow control is resolved according to our and the link partners
 * advertisements using the following drawn from the 802.3 specs:
 *  Local device  Link partner
 *  Pause AsymDir Pause AsymDir Result
 *    0     X       0     X     Disabled
 *    0     1       1     0     Disabled
 *    0     1       1     1     TX
 *    1     0       0     X     Disabled
 *    1     X       1     X     TX+RX
 *    1     1       0     1     RX
 */
व्योम linkmode_resolve_छोड़ो(स्थिर अचिन्हित दीर्घ *local_adv,
			    स्थिर अचिन्हित दीर्घ *partner_adv,
			    bool *tx_छोड़ो, bool *rx_छोड़ो)
अणु
	__ETHTOOL_DECLARE_LINK_MODE_MASK(m);

	linkmode_and(m, local_adv, partner_adv);
	अगर (linkmode_test_bit(ETHTOOL_LINK_MODE_Pause_BIT, m)) अणु
		*tx_छोड़ो = true;
		*rx_छोड़ो = true;
	पूर्ण अन्यथा अगर (linkmode_test_bit(ETHTOOL_LINK_MODE_Asym_Pause_BIT, m)) अणु
		*tx_छोड़ो = linkmode_test_bit(ETHTOOL_LINK_MODE_Pause_BIT,
					      partner_adv);
		*rx_छोड़ो = linkmode_test_bit(ETHTOOL_LINK_MODE_Pause_BIT,
					      local_adv);
	पूर्ण अन्यथा अणु
		*tx_छोड़ो = false;
		*rx_छोड़ो = false;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(linkmode_resolve_छोड़ो);

/**
 * linkmode_set_छोड़ो - set the छोड़ो mode advertisement
 * @advertisement: advertisement in ethtool क्रमmat
 * @tx: boolean from ethtool काष्ठा ethtool_छोड़ोparam tx_छोड़ो member
 * @rx: boolean from ethtool काष्ठा ethtool_छोड़ोparam rx_छोड़ो member
 *
 * Configure the advertised Pause and Asym_Pause bits according to the
 * capabilities of provided in @tx and @rx.
 *
 * We convert as follows:
 *  tx rx  Pause AsymDir
 *  0  0   0     0
 *  0  1   1     1
 *  1  0   0     1
 *  1  1   1     0
 *
 * Note: this translation from ethtool tx/rx notation to the advertisement
 * is actually very problematical. Here are some examples:
 *
 * For tx=0 rx=1, meaning transmit is unsupported, receive is supported:
 *
 *  Local device  Link partner
 *  Pause AsymDir Pause AsymDir Result
 *    1     1       1     0     TX + RX - but we have no TX support.
 *    1     1       0     1	Only this gives RX only
 *
 * For tx=1 rx=1, meaning we have the capability to transmit and receive
 * छोड़ो frames:
 *
 *  Local device  Link partner
 *  Pause AsymDir Pause AsymDir Result
 *    1     0       0     1     Disabled - but since we करो support tx and rx,
 *				this should resolve to RX only.
 *
 * Hence, asking क्रम:
 *  rx=1 tx=0 gives Pause+AsymDir advertisement, but we may end up
 *            resolving to tx+rx छोड़ो or only rx छोड़ो depending on
 *            the partners advertisement.
 *  rx=0 tx=1 gives AsymDir only, which will only give tx छोड़ो अगर
 *            the partners advertisement allows it.
 *  rx=1 tx=1 gives Pause only, which will only allow tx+rx छोड़ो
 *            अगर the other end also advertises Pause.
 */
व्योम linkmode_set_छोड़ो(अचिन्हित दीर्घ *advertisement, bool tx, bool rx)
अणु
	linkmode_mod_bit(ETHTOOL_LINK_MODE_Pause_BIT, advertisement, rx);
	linkmode_mod_bit(ETHTOOL_LINK_MODE_Asym_Pause_BIT, advertisement,
			 rx ^ tx);
पूर्ण
EXPORT_SYMBOL_GPL(linkmode_set_छोड़ो);
