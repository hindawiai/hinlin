<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NF_CONNTRACK_TFTP_H
#घोषणा _NF_CONNTRACK_TFTP_H

#घोषणा TFTP_PORT 69

#समावेश <linux/netfilter.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/types.h>
#समावेश <net/netfilter/nf_conntrack_expect.h>

काष्ठा tftphdr अणु
	__be16 opcode;
पूर्ण;

#घोषणा TFTP_OPCODE_READ	1
#घोषणा TFTP_OPCODE_WRITE	2
#घोषणा TFTP_OPCODE_DATA	3
#घोषणा TFTP_OPCODE_ACK		4
#घोषणा TFTP_OPCODE_ERROR	5

बाह्य अचिन्हित पूर्णांक (*nf_nat_tftp_hook)(काष्ठा sk_buff *skb,
				        क्रमागत ip_conntrack_info ctinfo,
				        काष्ठा nf_conntrack_expect *exp);

#पूर्ण_अगर /* _NF_CONNTRACK_TFTP_H */
