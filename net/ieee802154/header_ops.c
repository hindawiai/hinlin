<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014 Fraunhofer ITWM
 *
 * Written by:
 * Phoebe Buckheister <phoebe.buckheister@itwm.fraunhofer.de>
 */

#समावेश <linux/ieee802154.h>

#समावेश <net/mac802154.h>
#समावेश <net/ieee802154_netdev.h>

अटल पूर्णांक
ieee802154_hdr_push_addr(u8 *buf, स्थिर काष्ठा ieee802154_addr *addr,
			 bool omit_pan)
अणु
	पूर्णांक pos = 0;

	अगर (addr->mode == IEEE802154_ADDR_NONE)
		वापस 0;

	अगर (!omit_pan) अणु
		स_नकल(buf + pos, &addr->pan_id, 2);
		pos += 2;
	पूर्ण

	चयन (addr->mode) अणु
	हाल IEEE802154_ADDR_SHORT:
		स_नकल(buf + pos, &addr->लघु_addr, 2);
		pos += 2;
		अवरोध;

	हाल IEEE802154_ADDR_LONG:
		स_नकल(buf + pos, &addr->extended_addr, IEEE802154_ADDR_LEN);
		pos += IEEE802154_ADDR_LEN;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस pos;
पूर्ण

अटल पूर्णांक
ieee802154_hdr_push_sechdr(u8 *buf, स्थिर काष्ठा ieee802154_sechdr *hdr)
अणु
	पूर्णांक pos = 5;

	स_नकल(buf, hdr, 1);
	स_नकल(buf + 1, &hdr->frame_counter, 4);

	चयन (hdr->key_id_mode) अणु
	हाल IEEE802154_SCF_KEY_IMPLICIT:
		वापस pos;

	हाल IEEE802154_SCF_KEY_INDEX:
		अवरोध;

	हाल IEEE802154_SCF_KEY_SHORT_INDEX:
		स_नकल(buf + pos, &hdr->लघु_src, 4);
		pos += 4;
		अवरोध;

	हाल IEEE802154_SCF_KEY_HW_INDEX:
		स_नकल(buf + pos, &hdr->extended_src, IEEE802154_ADDR_LEN);
		pos += IEEE802154_ADDR_LEN;
		अवरोध;
	पूर्ण

	buf[pos++] = hdr->key_id;

	वापस pos;
पूर्ण

पूर्णांक
ieee802154_hdr_push(काष्ठा sk_buff *skb, काष्ठा ieee802154_hdr *hdr)
अणु
	u8 buf[IEEE802154_MAX_HEADER_LEN];
	पूर्णांक pos = 2;
	पूर्णांक rc;
	काष्ठा ieee802154_hdr_fc *fc = &hdr->fc;

	buf[pos++] = hdr->seq;

	fc->dest_addr_mode = hdr->dest.mode;

	rc = ieee802154_hdr_push_addr(buf + pos, &hdr->dest, false);
	अगर (rc < 0)
		वापस -EINVAL;
	pos += rc;

	fc->source_addr_mode = hdr->source.mode;

	अगर (hdr->source.pan_id == hdr->dest.pan_id &&
	    hdr->dest.mode != IEEE802154_ADDR_NONE)
		fc->पूर्णांकra_pan = true;

	rc = ieee802154_hdr_push_addr(buf + pos, &hdr->source, fc->पूर्णांकra_pan);
	अगर (rc < 0)
		वापस -EINVAL;
	pos += rc;

	अगर (fc->security_enabled) अणु
		fc->version = 1;

		rc = ieee802154_hdr_push_sechdr(buf + pos, &hdr->sec);
		अगर (rc < 0)
			वापस -EINVAL;

		pos += rc;
	पूर्ण

	स_नकल(buf, fc, 2);

	स_नकल(skb_push(skb, pos), buf, pos);

	वापस pos;
पूर्ण
EXPORT_SYMBOL_GPL(ieee802154_hdr_push);

अटल पूर्णांक
ieee802154_hdr_get_addr(स्थिर u8 *buf, पूर्णांक mode, bool omit_pan,
			काष्ठा ieee802154_addr *addr)
अणु
	पूर्णांक pos = 0;

	addr->mode = mode;

	अगर (mode == IEEE802154_ADDR_NONE)
		वापस 0;

	अगर (!omit_pan) अणु
		स_नकल(&addr->pan_id, buf + pos, 2);
		pos += 2;
	पूर्ण

	अगर (mode == IEEE802154_ADDR_SHORT) अणु
		स_नकल(&addr->लघु_addr, buf + pos, 2);
		वापस pos + 2;
	पूर्ण अन्यथा अणु
		स_नकल(&addr->extended_addr, buf + pos, IEEE802154_ADDR_LEN);
		वापस pos + IEEE802154_ADDR_LEN;
	पूर्ण
पूर्ण

अटल पूर्णांक ieee802154_hdr_addr_len(पूर्णांक mode, bool omit_pan)
अणु
	पूर्णांक pan_len = omit_pan ? 0 : 2;

	चयन (mode) अणु
	हाल IEEE802154_ADDR_NONE: वापस 0;
	हाल IEEE802154_ADDR_SHORT: वापस 2 + pan_len;
	हाल IEEE802154_ADDR_LONG: वापस IEEE802154_ADDR_LEN + pan_len;
	शेष: वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक
ieee802154_hdr_get_sechdr(स्थिर u8 *buf, काष्ठा ieee802154_sechdr *hdr)
अणु
	पूर्णांक pos = 5;

	स_नकल(hdr, buf, 1);
	स_नकल(&hdr->frame_counter, buf + 1, 4);

	चयन (hdr->key_id_mode) अणु
	हाल IEEE802154_SCF_KEY_IMPLICIT:
		वापस pos;

	हाल IEEE802154_SCF_KEY_INDEX:
		अवरोध;

	हाल IEEE802154_SCF_KEY_SHORT_INDEX:
		स_नकल(&hdr->लघु_src, buf + pos, 4);
		pos += 4;
		अवरोध;

	हाल IEEE802154_SCF_KEY_HW_INDEX:
		स_नकल(&hdr->extended_src, buf + pos, IEEE802154_ADDR_LEN);
		pos += IEEE802154_ADDR_LEN;
		अवरोध;
	पूर्ण

	hdr->key_id = buf[pos++];

	वापस pos;
पूर्ण

अटल पूर्णांक ieee802154_sechdr_lengths[4] = अणु
	[IEEE802154_SCF_KEY_IMPLICIT] = 5,
	[IEEE802154_SCF_KEY_INDEX] = 6,
	[IEEE802154_SCF_KEY_SHORT_INDEX] = 10,
	[IEEE802154_SCF_KEY_HW_INDEX] = 14,
पूर्ण;

अटल पूर्णांक ieee802154_hdr_sechdr_len(u8 sc)
अणु
	वापस ieee802154_sechdr_lengths[IEEE802154_SCF_KEY_ID_MODE(sc)];
पूर्ण

अटल पूर्णांक ieee802154_hdr_minlen(स्थिर काष्ठा ieee802154_hdr *hdr)
अणु
	पूर्णांक dlen, slen;

	dlen = ieee802154_hdr_addr_len(hdr->fc.dest_addr_mode, false);
	slen = ieee802154_hdr_addr_len(hdr->fc.source_addr_mode,
				       hdr->fc.पूर्णांकra_pan);

	अगर (slen < 0 || dlen < 0)
		वापस -EINVAL;

	वापस 3 + dlen + slen + hdr->fc.security_enabled;
पूर्ण

अटल पूर्णांक
ieee802154_hdr_get_addrs(स्थिर u8 *buf, काष्ठा ieee802154_hdr *hdr)
अणु
	पूर्णांक pos = 0;

	pos += ieee802154_hdr_get_addr(buf + pos, hdr->fc.dest_addr_mode,
				       false, &hdr->dest);
	pos += ieee802154_hdr_get_addr(buf + pos, hdr->fc.source_addr_mode,
				       hdr->fc.पूर्णांकra_pan, &hdr->source);

	अगर (hdr->fc.पूर्णांकra_pan)
		hdr->source.pan_id = hdr->dest.pan_id;

	वापस pos;
पूर्ण

पूर्णांक
ieee802154_hdr_pull(काष्ठा sk_buff *skb, काष्ठा ieee802154_hdr *hdr)
अणु
	पूर्णांक pos = 3, rc;

	अगर (!pskb_may_pull(skb, 3))
		वापस -EINVAL;

	स_नकल(hdr, skb->data, 3);

	rc = ieee802154_hdr_minlen(hdr);
	अगर (rc < 0 || !pskb_may_pull(skb, rc))
		वापस -EINVAL;

	pos += ieee802154_hdr_get_addrs(skb->data + pos, hdr);

	अगर (hdr->fc.security_enabled) अणु
		पूर्णांक want = pos + ieee802154_hdr_sechdr_len(skb->data[pos]);

		अगर (!pskb_may_pull(skb, want))
			वापस -EINVAL;

		pos += ieee802154_hdr_get_sechdr(skb->data + pos, &hdr->sec);
	पूर्ण

	skb_pull(skb, pos);
	वापस pos;
पूर्ण
EXPORT_SYMBOL_GPL(ieee802154_hdr_pull);

पूर्णांक
ieee802154_hdr_peek_addrs(स्थिर काष्ठा sk_buff *skb, काष्ठा ieee802154_hdr *hdr)
अणु
	स्थिर u8 *buf = skb_mac_header(skb);
	पूर्णांक pos = 3, rc;

	अगर (buf + 3 > skb_tail_poपूर्णांकer(skb))
		वापस -EINVAL;

	स_नकल(hdr, buf, 3);

	rc = ieee802154_hdr_minlen(hdr);
	अगर (rc < 0 || buf + rc > skb_tail_poपूर्णांकer(skb))
		वापस -EINVAL;

	pos += ieee802154_hdr_get_addrs(buf + pos, hdr);
	वापस pos;
पूर्ण
EXPORT_SYMBOL_GPL(ieee802154_hdr_peek_addrs);

पूर्णांक
ieee802154_hdr_peek(स्थिर काष्ठा sk_buff *skb, काष्ठा ieee802154_hdr *hdr)
अणु
	स्थिर u8 *buf = skb_mac_header(skb);
	पूर्णांक pos;

	pos = ieee802154_hdr_peek_addrs(skb, hdr);
	अगर (pos < 0)
		वापस -EINVAL;

	अगर (hdr->fc.security_enabled) अणु
		u8 key_id_mode = IEEE802154_SCF_KEY_ID_MODE(*(buf + pos));
		पूर्णांक want = pos + ieee802154_sechdr_lengths[key_id_mode];

		अगर (buf + want > skb_tail_poपूर्णांकer(skb))
			वापस -EINVAL;

		pos += ieee802154_hdr_get_sechdr(buf + pos, &hdr->sec);
	पूर्ण

	वापस pos;
पूर्ण
EXPORT_SYMBOL_GPL(ieee802154_hdr_peek);

पूर्णांक ieee802154_max_payload(स्थिर काष्ठा ieee802154_hdr *hdr)
अणु
	पूर्णांक hlen = ieee802154_hdr_minlen(hdr);

	अगर (hdr->fc.security_enabled) अणु
		hlen += ieee802154_sechdr_lengths[hdr->sec.key_id_mode] - 1;
		hlen += ieee802154_sechdr_authtag_len(&hdr->sec);
	पूर्ण

	वापस IEEE802154_MTU - hlen - IEEE802154_MFR_SIZE;
पूर्ण
EXPORT_SYMBOL_GPL(ieee802154_max_payload);
