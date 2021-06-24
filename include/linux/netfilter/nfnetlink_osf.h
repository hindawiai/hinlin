<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NFOSF_H
#घोषणा _NFOSF_H

#समावेश <uapi/linux/netfilter/nfnetlink_osf.h>

क्रमागत osf_fmatch_states अणु
	/* Packet करोes not match the fingerprपूर्णांक */
	FMATCH_WRONG = 0,
	/* Packet matches the fingerprपूर्णांक */
	FMATCH_OK,
	/* Options करो not match the fingerprपूर्णांक, but header करोes */
	FMATCH_OPT_WRONG,
पूर्ण;

बाह्य काष्ठा list_head nf_osf_fingers[2];

काष्ठा nf_osf_finger अणु
	काष्ठा rcu_head			rcu_head;
	काष्ठा list_head		finger_entry;
	काष्ठा nf_osf_user_finger	finger;
पूर्ण;

काष्ठा nf_osf_data अणु
	स्थिर अक्षर *genre;
	स्थिर अक्षर *version;
पूर्ण;

bool nf_osf_match(स्थिर काष्ठा sk_buff *skb, u_पूर्णांक8_t family,
		  पूर्णांक hooknum, काष्ठा net_device *in, काष्ठा net_device *out,
		  स्थिर काष्ठा nf_osf_info *info, काष्ठा net *net,
		  स्थिर काष्ठा list_head *nf_osf_fingers);

bool nf_osf_find(स्थिर काष्ठा sk_buff *skb,
		 स्थिर काष्ठा list_head *nf_osf_fingers,
		 स्थिर पूर्णांक ttl_check, काष्ठा nf_osf_data *data);

#पूर्ण_अगर /* _NFOSF_H */
