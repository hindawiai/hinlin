<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* PTP classअगरier
 */

/* The below program is the bpf_यंत्र (tools/net/) representation of
 * the opcode array in the ptp_filter काष्ठाure.
 *
 * For convenience, this can easily be altered and reviewed with
 * bpf_यंत्र and bpf_dbg, e.g. `./bpf_यंत्र -c prog` where prog is a
 * simple file containing the below program:
 *
 * ldh [12]                        ; load ethertype
 *
 * ; PTP over UDP over IPv4 over Ethernet
 * test_ipv4:
 *   jneq #0x800, test_ipv6        ; ETH_P_IP ?
 *   ldb [23]                      ; load proto
 *   jneq #17, drop_ipv4           ; IPPROTO_UDP ?
 *   ldh [20]                      ; load frag offset field
 *   jset #0x1fff, drop_ipv4       ; करोn't allow fragments
 *   ldxb 4*([14]&0xf)             ; load IP header len
 *   ldh [x + 16]                  ; load UDP dst port
 *   jneq #319, drop_ipv4          ; is port PTP_EV_PORT ?
 *   ldh [x + 22]                  ; load payload
 *   and #0xf                      ; mask PTP_CLASS_VMASK
 *   or #0x10                      ; PTP_CLASS_IPV4
 *   ret a                         ; वापस PTP class
 *   drop_ipv4: ret #0x0           ; PTP_CLASS_NONE
 *
 * ; PTP over UDP over IPv6 over Ethernet
 * test_ipv6:
 *   jneq #0x86dd, test_8021q      ; ETH_P_IPV6 ?
 *   ldb [20]                      ; load proto
 *   jneq #17, drop_ipv6           ; IPPROTO_UDP ?
 *   ldh [56]                      ; load UDP dst port
 *   jneq #319, drop_ipv6          ; is port PTP_EV_PORT ?
 *   ldh [62]                      ; load payload
 *   and #0xf                      ; mask PTP_CLASS_VMASK
 *   or #0x20                      ; PTP_CLASS_IPV6
 *   ret a                         ; वापस PTP class
 *   drop_ipv6: ret #0x0           ; PTP_CLASS_NONE
 *
 * ; PTP over 802.1Q over Ethernet
 * test_8021q:
 *   jneq #0x8100, test_ieee1588   ; ETH_P_8021Q ?
 *   ldh [16]                      ; load inner type
 *   jneq #0x88f7, test_8021q_ipv4 ; ETH_P_1588 ?
 *   ldb [18]                      ; load payload
 *   and #0x8                      ; as we करोn't have ports here, test
 *   jneq #0x0, drop_ieee1588      ; क्रम PTP_GEN_BIT and drop these
 *   ldh [18]                      ; reload payload
 *   and #0xf                      ; mask PTP_CLASS_VMASK
 *   or #0xc0                      ; PTP_CLASS_VLAN|PTP_CLASS_L2
 *   ret a                         ; वापस PTP class
 *
 * ; PTP over UDP over IPv4 over 802.1Q over Ethernet
 * test_8021q_ipv4:
 *   jneq #0x800, test_8021q_ipv6  ; ETH_P_IP ?
 *   ldb [27]                      ; load proto
 *   jneq #17, drop_8021q_ipv4     ; IPPROTO_UDP ?
 *   ldh [24]                      ; load frag offset field
 *   jset #0x1fff, drop_8021q_ipv4; करोn't allow fragments
 *   ldxb 4*([18]&0xf)             ; load IP header len
 *   ldh [x + 20]                  ; load UDP dst port
 *   jneq #319, drop_8021q_ipv4    ; is port PTP_EV_PORT ?
 *   ldh [x + 26]                  ; load payload
 *   and #0xf                      ; mask PTP_CLASS_VMASK
 *   or #0x90                      ; PTP_CLASS_VLAN|PTP_CLASS_IPV4
 *   ret a                         ; वापस PTP class
 *   drop_8021q_ipv4: ret #0x0     ; PTP_CLASS_NONE
 *
 * ; PTP over UDP over IPv6 over 802.1Q over Ethernet
 * test_8021q_ipv6:
 *   jneq #0x86dd, drop_8021q_ipv6 ; ETH_P_IPV6 ?
 *   ldb [24]                      ; load proto
 *   jneq #17, drop_8021q_ipv6           ; IPPROTO_UDP ?
 *   ldh [60]                      ; load UDP dst port
 *   jneq #319, drop_8021q_ipv6          ; is port PTP_EV_PORT ?
 *   ldh [66]                      ; load payload
 *   and #0xf                      ; mask PTP_CLASS_VMASK
 *   or #0xa0                      ; PTP_CLASS_VLAN|PTP_CLASS_IPV6
 *   ret a                         ; वापस PTP class
 *   drop_8021q_ipv6: ret #0x0     ; PTP_CLASS_NONE
 *
 * ; PTP over Ethernet
 * test_ieee1588:
 *   jneq #0x88f7, drop_ieee1588   ; ETH_P_1588 ?
 *   ldb [14]                      ; load payload
 *   and #0x8                      ; as we करोn't have ports here, test
 *   jneq #0x0, drop_ieee1588      ; क्रम PTP_GEN_BIT and drop these
 *   ldh [14]                      ; reload payload
 *   and #0xf                      ; mask PTP_CLASS_VMASK
 *   or #0x40                      ; PTP_CLASS_L2
 *   ret a                         ; वापस PTP class
 *   drop_ieee1588: ret #0x0       ; PTP_CLASS_NONE
 */

#समावेश <linux/skbuff.h>
#समावेश <linux/filter.h>
#समावेश <linux/ptp_classअगरy.h>

अटल काष्ठा bpf_prog *ptp_insns __पढ़ो_mostly;

अचिन्हित पूर्णांक ptp_classअगरy_raw(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस BPF_PROG_RUN(ptp_insns, skb);
पूर्ण
EXPORT_SYMBOL_GPL(ptp_classअगरy_raw);

काष्ठा ptp_header *ptp_parse_header(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक type)
अणु
	u8 *ptr = skb_mac_header(skb);

	अगर (type & PTP_CLASS_VLAN)
		ptr += VLAN_HLEN;

	चयन (type & PTP_CLASS_PMASK) अणु
	हाल PTP_CLASS_IPV4:
		ptr += IPV4_HLEN(ptr) + UDP_HLEN;
		अवरोध;
	हाल PTP_CLASS_IPV6:
		ptr += IP6_HLEN + UDP_HLEN;
		अवरोध;
	हाल PTP_CLASS_L2:
		अवरोध;
	शेष:
		वापस शून्य;
	पूर्ण

	ptr += ETH_HLEN;

	/* Ensure that the entire header is present in this packet. */
	अगर (ptr + माप(काष्ठा ptp_header) > skb->data + skb->len)
		वापस शून्य;

	वापस (काष्ठा ptp_header *)ptr;
पूर्ण
EXPORT_SYMBOL_GPL(ptp_parse_header);

व्योम __init ptp_classअगरier_init(व्योम)
अणु
	अटल काष्ठा sock_filter ptp_filter[] __initdata = अणु
		अणु 0x28,  0,  0, 0x0000000c पूर्ण,
		अणु 0x15,  0, 12, 0x00000800 पूर्ण,
		अणु 0x30,  0,  0, 0x00000017 पूर्ण,
		अणु 0x15,  0,  9, 0x00000011 पूर्ण,
		अणु 0x28,  0,  0, 0x00000014 पूर्ण,
		अणु 0x45,  7,  0, 0x00001fff पूर्ण,
		अणु 0xb1,  0,  0, 0x0000000e पूर्ण,
		अणु 0x48,  0,  0, 0x00000010 पूर्ण,
		अणु 0x15,  0,  4, 0x0000013f पूर्ण,
		अणु 0x48,  0,  0, 0x00000016 पूर्ण,
		अणु 0x54,  0,  0, 0x0000000f पूर्ण,
		अणु 0x44,  0,  0, 0x00000010 पूर्ण,
		अणु 0x16,  0,  0, 0x00000000 पूर्ण,
		अणु 0x06,  0,  0, 0x00000000 पूर्ण,
		अणु 0x15,  0,  9, 0x000086dd पूर्ण,
		अणु 0x30,  0,  0, 0x00000014 पूर्ण,
		अणु 0x15,  0,  6, 0x00000011 पूर्ण,
		अणु 0x28,  0,  0, 0x00000038 पूर्ण,
		अणु 0x15,  0,  4, 0x0000013f पूर्ण,
		अणु 0x28,  0,  0, 0x0000003e पूर्ण,
		अणु 0x54,  0,  0, 0x0000000f पूर्ण,
		अणु 0x44,  0,  0, 0x00000020 पूर्ण,
		अणु 0x16,  0,  0, 0x00000000 पूर्ण,
		अणु 0x06,  0,  0, 0x00000000 पूर्ण,
		अणु 0x15,  0, 32, 0x00008100 पूर्ण,
		अणु 0x28,  0,  0, 0x00000010 पूर्ण,
		अणु 0x15,  0,  7, 0x000088f7 पूर्ण,
		अणु 0x30,  0,  0, 0x00000012 पूर्ण,
		अणु 0x54,  0,  0, 0x00000008 पूर्ण,
		अणु 0x15,  0, 35, 0x00000000 पूर्ण,
		अणु 0x28,  0,  0, 0x00000012 पूर्ण,
		अणु 0x54,  0,  0, 0x0000000f पूर्ण,
		अणु 0x44,  0,  0, 0x000000c0 पूर्ण,
		अणु 0x16,  0,  0, 0x00000000 पूर्ण,
		अणु 0x15,  0, 12, 0x00000800 पूर्ण,
		अणु 0x30,  0,  0, 0x0000001b पूर्ण,
		अणु 0x15,  0,  9, 0x00000011 पूर्ण,
		अणु 0x28,  0,  0, 0x00000018 पूर्ण,
		अणु 0x45,  7,  0, 0x00001fff पूर्ण,
		अणु 0xb1,  0,  0, 0x00000012 पूर्ण,
		अणु 0x48,  0,  0, 0x00000014 पूर्ण,
		अणु 0x15,  0,  4, 0x0000013f पूर्ण,
		अणु 0x48,  0,  0, 0x0000001a पूर्ण,
		अणु 0x54,  0,  0, 0x0000000f पूर्ण,
		अणु 0x44,  0,  0, 0x00000090 पूर्ण,
		अणु 0x16,  0,  0, 0x00000000 पूर्ण,
		अणु 0x06,  0,  0, 0x00000000 पूर्ण,
		अणु 0x15,  0,  8, 0x000086dd पूर्ण,
		अणु 0x30,  0,  0, 0x00000018 पूर्ण,
		अणु 0x15,  0,  6, 0x00000011 पूर्ण,
		अणु 0x28,  0,  0, 0x0000003c पूर्ण,
		अणु 0x15,  0,  4, 0x0000013f पूर्ण,
		अणु 0x28,  0,  0, 0x00000042 पूर्ण,
		अणु 0x54,  0,  0, 0x0000000f पूर्ण,
		अणु 0x44,  0,  0, 0x000000a0 पूर्ण,
		अणु 0x16,  0,  0, 0x00000000 पूर्ण,
		अणु 0x06,  0,  0, 0x00000000 पूर्ण,
		अणु 0x15,  0,  7, 0x000088f7 पूर्ण,
		अणु 0x30,  0,  0, 0x0000000e पूर्ण,
		अणु 0x54,  0,  0, 0x00000008 पूर्ण,
		अणु 0x15,  0,  4, 0x00000000 पूर्ण,
		अणु 0x28,  0,  0, 0x0000000e पूर्ण,
		अणु 0x54,  0,  0, 0x0000000f पूर्ण,
		अणु 0x44,  0,  0, 0x00000040 पूर्ण,
		अणु 0x16,  0,  0, 0x00000000 पूर्ण,
		अणु 0x06,  0,  0, 0x00000000 पूर्ण,
	पूर्ण;
	काष्ठा sock_fprog_kern ptp_prog;

	ptp_prog.len = ARRAY_SIZE(ptp_filter);
	ptp_prog.filter = ptp_filter;

	BUG_ON(bpf_prog_create(&ptp_insns, &ptp_prog));
पूर्ण
