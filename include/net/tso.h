<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _TSO_H
#घोषणा _TSO_H

#समावेश <net/ip.h>

#घोषणा TSO_HEADER_SIZE		256

काष्ठा tso_t अणु
	पूर्णांक	next_frag_idx;
	पूर्णांक	size;
	व्योम	*data;
	u16	ip_id;
	u8	tlen; /* transport header len */
	bool	ipv6;
	u32	tcp_seq;
पूर्ण;

पूर्णांक tso_count_descs(स्थिर काष्ठा sk_buff *skb);
व्योम tso_build_hdr(स्थिर काष्ठा sk_buff *skb, अक्षर *hdr, काष्ठा tso_t *tso,
		   पूर्णांक size, bool is_last);
व्योम tso_build_data(स्थिर काष्ठा sk_buff *skb, काष्ठा tso_t *tso, पूर्णांक size);
पूर्णांक tso_start(काष्ठा sk_buff *skb, काष्ठा tso_t *tso);

#पूर्ण_अगर	/* _TSO_H */
