<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * An पूर्णांकerface between IEEE802.15.4 device and rest of the kernel.
 *
 * Copyright (C) 2007-2012 Siemens AG
 *
 * Written by:
 * Pavel Smolenskiy <pavel.smolenskiy@gmail.com>
 * Maxim Gorbachyov <maxim.gorbachev@siemens.com>
 * Maxim Osipov <maxim.osipov@siemens.com>
 * Dmitry Eremin-Solenikov <dbaryshkov@gmail.com>
 * Alexander Smirnov <alex.bluesman.smirnov@gmail.com>
 */

#अगर_अघोषित IEEE802154_NETDEVICE_H
#घोषणा IEEE802154_NETDEVICE_H

#समावेश <net/af_ieee802154.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ieee802154.h>

#समावेश <net/cfg802154.h>

काष्ठा ieee802154_sechdr अणु
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
	u8 level:3,
	   key_id_mode:2,
	   reserved:3;
#या_अगर defined(__BIG_ENDIAN_BITFIELD)
	u8 reserved:3,
	   key_id_mode:2,
	   level:3;
#अन्यथा
#त्रुटि	"Please fix <asm/byteorder.h>"
#पूर्ण_अगर
	u8 key_id;
	__le32 frame_counter;
	जोड़ अणु
		__le32 लघु_src;
		__le64 extended_src;
	पूर्ण;
पूर्ण;

काष्ठा ieee802154_hdr_fc अणु
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
	u16 type:3,
	    security_enabled:1,
	    frame_pending:1,
	    ack_request:1,
	    पूर्णांकra_pan:1,
	    reserved:3,
	    dest_addr_mode:2,
	    version:2,
	    source_addr_mode:2;
#या_अगर defined(__BIG_ENDIAN_BITFIELD)
	u16 reserved:1,
	    पूर्णांकra_pan:1,
	    ack_request:1,
	    frame_pending:1,
	    security_enabled:1,
	    type:3,
	    source_addr_mode:2,
	    version:2,
	    dest_addr_mode:2,
	    reserved2:2;
#अन्यथा
#त्रुटि	"Please fix <asm/byteorder.h>"
#पूर्ण_अगर
पूर्ण;

काष्ठा ieee802154_hdr अणु
	काष्ठा ieee802154_hdr_fc fc;
	u8 seq;
	काष्ठा ieee802154_addr source;
	काष्ठा ieee802154_addr dest;
	काष्ठा ieee802154_sechdr sec;
पूर्ण;

/* pushes hdr onto the skb. fields of hdr->fc that can be calculated from
 * the contents of hdr will be, and the actual value of those bits in
 * hdr->fc will be ignored. this includes the INTRA_PAN bit and the frame
 * version, अगर SECEN is set.
 */
पूर्णांक ieee802154_hdr_push(काष्ठा sk_buff *skb, काष्ठा ieee802154_hdr *hdr);

/* pulls the entire 802.15.4 header off of the skb, including the security
 * header, and perक्रमms pan id decompression
 */
पूर्णांक ieee802154_hdr_pull(काष्ठा sk_buff *skb, काष्ठा ieee802154_hdr *hdr);

/* parses the frame control, sequence number of address fields in a given skb
 * and stores them पूर्णांकo hdr, perक्रमming pan id decompression and length checks
 * to be suitable क्रम use in header_ops.parse
 */
पूर्णांक ieee802154_hdr_peek_addrs(स्थिर काष्ठा sk_buff *skb,
			      काष्ठा ieee802154_hdr *hdr);

/* parses the full 802.15.4 header a given skb and stores them पूर्णांकo hdr,
 * perक्रमming pan id decompression and length checks to be suitable क्रम use in
 * header_ops.parse
 */
पूर्णांक ieee802154_hdr_peek(स्थिर काष्ठा sk_buff *skb, काष्ठा ieee802154_hdr *hdr);

पूर्णांक ieee802154_max_payload(स्थिर काष्ठा ieee802154_hdr *hdr);

अटल अंतरभूत पूर्णांक
ieee802154_sechdr_authtag_len(स्थिर काष्ठा ieee802154_sechdr *sec)
अणु
	चयन (sec->level) अणु
	हाल IEEE802154_SCF_SECLEVEL_MIC32:
	हाल IEEE802154_SCF_SECLEVEL_ENC_MIC32:
		वापस 4;
	हाल IEEE802154_SCF_SECLEVEL_MIC64:
	हाल IEEE802154_SCF_SECLEVEL_ENC_MIC64:
		वापस 8;
	हाल IEEE802154_SCF_SECLEVEL_MIC128:
	हाल IEEE802154_SCF_SECLEVEL_ENC_MIC128:
		वापस 16;
	हाल IEEE802154_SCF_SECLEVEL_NONE:
	हाल IEEE802154_SCF_SECLEVEL_ENC:
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक ieee802154_hdr_length(काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee802154_hdr hdr;
	पूर्णांक len = ieee802154_hdr_pull(skb, &hdr);

	अगर (len > 0)
		skb_push(skb, len);

	वापस len;
पूर्ण

अटल अंतरभूत bool ieee802154_addr_equal(स्थिर काष्ठा ieee802154_addr *a1,
					 स्थिर काष्ठा ieee802154_addr *a2)
अणु
	अगर (a1->pan_id != a2->pan_id || a1->mode != a2->mode)
		वापस false;

	अगर ((a1->mode == IEEE802154_ADDR_LONG &&
	     a1->extended_addr != a2->extended_addr) ||
	    (a1->mode == IEEE802154_ADDR_SHORT &&
	     a1->लघु_addr != a2->लघु_addr))
		वापस false;

	वापस true;
पूर्ण

अटल अंतरभूत __le64 ieee802154_devaddr_from_raw(स्थिर व्योम *raw)
अणु
	u64 temp;

	स_नकल(&temp, raw, IEEE802154_ADDR_LEN);
	वापस (__क्रमce __le64)swab64(temp);
पूर्ण

अटल अंतरभूत व्योम ieee802154_devaddr_to_raw(व्योम *raw, __le64 addr)
अणु
	u64 temp = swab64((__क्रमce u64)addr);

	स_नकल(raw, &temp, IEEE802154_ADDR_LEN);
पूर्ण

अटल अंतरभूत व्योम ieee802154_addr_from_sa(काष्ठा ieee802154_addr *a,
					   स्थिर काष्ठा ieee802154_addr_sa *sa)
अणु
	a->mode = sa->addr_type;
	a->pan_id = cpu_to_le16(sa->pan_id);

	चयन (a->mode) अणु
	हाल IEEE802154_ADDR_SHORT:
		a->लघु_addr = cpu_to_le16(sa->लघु_addr);
		अवरोध;
	हाल IEEE802154_ADDR_LONG:
		a->extended_addr = ieee802154_devaddr_from_raw(sa->hwaddr);
		अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम ieee802154_addr_to_sa(काष्ठा ieee802154_addr_sa *sa,
					 स्थिर काष्ठा ieee802154_addr *a)
अणु
	sa->addr_type = a->mode;
	sa->pan_id = le16_to_cpu(a->pan_id);

	चयन (a->mode) अणु
	हाल IEEE802154_ADDR_SHORT:
		sa->लघु_addr = le16_to_cpu(a->लघु_addr);
		अवरोध;
	हाल IEEE802154_ADDR_LONG:
		ieee802154_devaddr_to_raw(sa->hwaddr, a->extended_addr);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * A control block of skb passed between the ARPHRD_IEEE802154 device
 * and other stack parts.
 */
काष्ठा ieee802154_mac_cb अणु
	u8 lqi;
	u8 type;
	bool ackreq;
	bool secen;
	bool secen_override;
	u8 seclevel;
	bool seclevel_override;
	काष्ठा ieee802154_addr source;
	काष्ठा ieee802154_addr dest;
पूर्ण;

अटल अंतरभूत काष्ठा ieee802154_mac_cb *mac_cb(काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा ieee802154_mac_cb *)skb->cb;
पूर्ण

अटल अंतरभूत काष्ठा ieee802154_mac_cb *mac_cb_init(काष्ठा sk_buff *skb)
अणु
	BUILD_BUG_ON(माप(काष्ठा ieee802154_mac_cb) > माप(skb->cb));

	स_रखो(skb->cb, 0, माप(काष्ठा ieee802154_mac_cb));
	वापस mac_cb(skb);
पूर्ण

क्रमागत अणु
	IEEE802154_LLSEC_DEVKEY_IGNORE,
	IEEE802154_LLSEC_DEVKEY_RESTRICT,
	IEEE802154_LLSEC_DEVKEY_RECORD,

	__IEEE802154_LLSEC_DEVKEY_MAX,
पूर्ण;

#घोषणा IEEE802154_MAC_SCAN_ED		0
#घोषणा IEEE802154_MAC_SCAN_ACTIVE	1
#घोषणा IEEE802154_MAC_SCAN_PASSIVE	2
#घोषणा IEEE802154_MAC_SCAN_ORPHAN	3

काष्ठा ieee802154_mac_params अणु
	s8 transmit_घातer;
	u8 min_be;
	u8 max_be;
	u8 csma_retries;
	s8 frame_retries;

	bool lbt;
	काष्ठा wpan_phy_cca cca;
	s32 cca_ed_level;
पूर्ण;

काष्ठा wpan_phy;

क्रमागत अणु
	IEEE802154_LLSEC_PARAM_ENABLED		= BIT(0),
	IEEE802154_LLSEC_PARAM_FRAME_COUNTER	= BIT(1),
	IEEE802154_LLSEC_PARAM_OUT_LEVEL	= BIT(2),
	IEEE802154_LLSEC_PARAM_OUT_KEY		= BIT(3),
	IEEE802154_LLSEC_PARAM_KEY_SOURCE	= BIT(4),
	IEEE802154_LLSEC_PARAM_PAN_ID		= BIT(5),
	IEEE802154_LLSEC_PARAM_HWADDR		= BIT(6),
	IEEE802154_LLSEC_PARAM_COORD_HWADDR	= BIT(7),
	IEEE802154_LLSEC_PARAM_COORD_SHORTADDR	= BIT(8),
पूर्ण;

काष्ठा ieee802154_llsec_ops अणु
	पूर्णांक (*get_params)(काष्ठा net_device *dev,
			  काष्ठा ieee802154_llsec_params *params);
	पूर्णांक (*set_params)(काष्ठा net_device *dev,
			  स्थिर काष्ठा ieee802154_llsec_params *params,
			  पूर्णांक changed);

	पूर्णांक (*add_key)(काष्ठा net_device *dev,
		       स्थिर काष्ठा ieee802154_llsec_key_id *id,
		       स्थिर काष्ठा ieee802154_llsec_key *key);
	पूर्णांक (*del_key)(काष्ठा net_device *dev,
		       स्थिर काष्ठा ieee802154_llsec_key_id *id);

	पूर्णांक (*add_dev)(काष्ठा net_device *dev,
		       स्थिर काष्ठा ieee802154_llsec_device *llsec_dev);
	पूर्णांक (*del_dev)(काष्ठा net_device *dev, __le64 dev_addr);

	पूर्णांक (*add_devkey)(काष्ठा net_device *dev,
			  __le64 device_addr,
			  स्थिर काष्ठा ieee802154_llsec_device_key *key);
	पूर्णांक (*del_devkey)(काष्ठा net_device *dev,
			  __le64 device_addr,
			  स्थिर काष्ठा ieee802154_llsec_device_key *key);

	पूर्णांक (*add_seclevel)(काष्ठा net_device *dev,
			    स्थिर काष्ठा ieee802154_llsec_seclevel *sl);
	पूर्णांक (*del_seclevel)(काष्ठा net_device *dev,
			    स्थिर काष्ठा ieee802154_llsec_seclevel *sl);

	व्योम (*lock_table)(काष्ठा net_device *dev);
	व्योम (*get_table)(काष्ठा net_device *dev,
			  काष्ठा ieee802154_llsec_table **t);
	व्योम (*unlock_table)(काष्ठा net_device *dev);
पूर्ण;
/*
 * This should be located at net_device->ml_priv
 *
 * get_phy should increment the reference counting on वापसed phy.
 * Use wpan_wpy_put to put that reference.
 */
काष्ठा ieee802154_mlme_ops अणु
	/* The following fields are optional (can be शून्य). */

	पूर्णांक (*assoc_req)(काष्ठा net_device *dev,
			काष्ठा ieee802154_addr *addr,
			u8 channel, u8 page, u8 cap);
	पूर्णांक (*assoc_resp)(काष्ठा net_device *dev,
			काष्ठा ieee802154_addr *addr,
			__le16 लघु_addr, u8 status);
	पूर्णांक (*disassoc_req)(काष्ठा net_device *dev,
			काष्ठा ieee802154_addr *addr,
			u8 reason);
	पूर्णांक (*start_req)(काष्ठा net_device *dev,
			काष्ठा ieee802154_addr *addr,
			u8 channel, u8 page, u8 bcn_ord, u8 sf_ord,
			u8 pan_coord, u8 blx, u8 coord_realign);
	पूर्णांक (*scan_req)(काष्ठा net_device *dev,
			u8 type, u32 channels, u8 page, u8 duration);

	पूर्णांक (*set_mac_params)(काष्ठा net_device *dev,
			      स्थिर काष्ठा ieee802154_mac_params *params);
	व्योम (*get_mac_params)(काष्ठा net_device *dev,
			       काष्ठा ieee802154_mac_params *params);

	स्थिर काष्ठा ieee802154_llsec_ops *llsec;
पूर्ण;

अटल अंतरभूत काष्ठा ieee802154_mlme_ops *
ieee802154_mlme_ops(स्थिर काष्ठा net_device *dev)
अणु
	वापस dev->ml_priv;
पूर्ण

#पूर्ण_अगर
