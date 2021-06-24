<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/* Copyright 2019, 2020 Cloudflare */

#समावेश <stdbool.h>
#समावेश <मानकघोष.स>
#समावेश <मानक_निवेशt.h>
#समावेश <माला.स>

#समावेश <linux/अगर_ether.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/udp.h>

काष्ठा gre_base_hdr अणु
	uपूर्णांक16_t flags;
	uपूर्णांक16_t protocol;
पूर्ण __attribute__((packed));

काष्ठा guehdr अणु
#अगर __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	uपूर्णांक8_t hlen : 5, control : 1, variant : 2;
#अन्यथा
	uपूर्णांक8_t variant : 2, control : 1, hlen : 5;
#पूर्ण_अगर
	uपूर्णांक8_t proto_ctype;
	uपूर्णांक16_t flags;
पूर्ण;

काष्ठा unigue अणु
#अगर __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	uपूर्णांक8_t _r : 2, last_hop_gre : 1, क्रमward_syn : 1, version : 4;
#अन्यथा
	uपूर्णांक8_t version : 4, क्रमward_syn : 1, last_hop_gre : 1, _r : 2;
#पूर्ण_अगर
	uपूर्णांक8_t reserved;
	uपूर्णांक8_t next_hop;
	uपूर्णांक8_t hop_count;
	// Next hops go here
पूर्ण __attribute__((packed));

प्रकार काष्ठा अणु
	काष्ठा ethhdr eth;
	काष्ठा iphdr ip;
	काष्ठा gre_base_hdr gre;
पूर्ण __attribute__((packed)) encap_gre_t;

प्रकार काष्ठा अणु
	काष्ठा ethhdr eth;
	काष्ठा iphdr ip;
	काष्ठा udphdr udp;
	काष्ठा guehdr gue;
	काष्ठा unigue unigue;
पूर्ण __attribute__((packed)) encap_headers_t;
