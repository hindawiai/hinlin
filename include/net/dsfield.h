<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* include/net/dsfield.h - Manipulation of the Dअगरferentiated Services field */

/* Written 1998-2000 by Werner Almesberger, EPFL ICA */


#अगर_अघोषित __NET_DSFIELD_H
#घोषणा __NET_DSFIELD_H

#समावेश <linux/types.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <यंत्र/byteorder.h>


अटल अंतरभूत __u8 ipv4_get_dsfield(स्थिर काष्ठा iphdr *iph)
अणु
	वापस iph->tos;
पूर्ण


अटल अंतरभूत __u8 ipv6_get_dsfield(स्थिर काष्ठा ipv6hdr *ipv6h)
अणु
	वापस ntohs(*(__क्रमce स्थिर __be16 *)ipv6h) >> 4;
पूर्ण


अटल अंतरभूत व्योम ipv4_change_dsfield(काष्ठा iphdr *iph,__u8 mask,
    __u8 value)
अणु
        __u32 check = ntohs((__क्रमce __be16)iph->check);
	__u8 dsfield;

	dsfield = (iph->tos & mask) | value;
	check += iph->tos;
	अगर ((check+1) >> 16) check = (check+1) & 0xffff;
	check -= dsfield;
	check += check >> 16; /* adjust carry */
	iph->check = (__क्रमce __sum16)htons(check);
	iph->tos = dsfield;
पूर्ण


अटल अंतरभूत व्योम ipv6_change_dsfield(काष्ठा ipv6hdr *ipv6h,__u8 mask,
    __u8 value)
अणु
	__be16 *p = (__क्रमce __be16 *)ipv6h;

	*p = (*p & htons((((u16)mask << 4) | 0xf00f))) | htons((u16)value << 4);
पूर्ण


#पूर्ण_अगर
