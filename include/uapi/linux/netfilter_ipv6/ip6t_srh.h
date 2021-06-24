<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _IP6T_SRH_H
#घोषणा _IP6T_SRH_H

#समावेश <linux/types.h>
#समावेश <linux/netfilter.h>

/* Values क्रम "mt_flags" field in काष्ठा ip6t_srh */
#घोषणा IP6T_SRH_NEXTHDR        0x0001
#घोषणा IP6T_SRH_LEN_EQ         0x0002
#घोषणा IP6T_SRH_LEN_GT         0x0004
#घोषणा IP6T_SRH_LEN_LT         0x0008
#घोषणा IP6T_SRH_SEGS_EQ        0x0010
#घोषणा IP6T_SRH_SEGS_GT        0x0020
#घोषणा IP6T_SRH_SEGS_LT        0x0040
#घोषणा IP6T_SRH_LAST_EQ        0x0080
#घोषणा IP6T_SRH_LAST_GT        0x0100
#घोषणा IP6T_SRH_LAST_LT        0x0200
#घोषणा IP6T_SRH_TAG            0x0400
#घोषणा IP6T_SRH_PSID           0x0800
#घोषणा IP6T_SRH_NSID           0x1000
#घोषणा IP6T_SRH_LSID           0x2000
#घोषणा IP6T_SRH_MASK           0x3FFF

/* Values क्रम "mt_invflags" field in काष्ठा ip6t_srh */
#घोषणा IP6T_SRH_INV_NEXTHDR    0x0001
#घोषणा IP6T_SRH_INV_LEN_EQ     0x0002
#घोषणा IP6T_SRH_INV_LEN_GT     0x0004
#घोषणा IP6T_SRH_INV_LEN_LT     0x0008
#घोषणा IP6T_SRH_INV_SEGS_EQ    0x0010
#घोषणा IP6T_SRH_INV_SEGS_GT    0x0020
#घोषणा IP6T_SRH_INV_SEGS_LT    0x0040
#घोषणा IP6T_SRH_INV_LAST_EQ    0x0080
#घोषणा IP6T_SRH_INV_LAST_GT    0x0100
#घोषणा IP6T_SRH_INV_LAST_LT    0x0200
#घोषणा IP6T_SRH_INV_TAG        0x0400
#घोषणा IP6T_SRH_INV_PSID       0x0800
#घोषणा IP6T_SRH_INV_NSID       0x1000
#घोषणा IP6T_SRH_INV_LSID       0x2000
#घोषणा IP6T_SRH_INV_MASK       0x3FFF

/**
 *      काष्ठा ip6t_srh - SRH match options
 *      @ next_hdr: Next header field of SRH
 *      @ hdr_len: Extension header length field of SRH
 *      @ segs_left: Segments left field of SRH
 *      @ last_entry: Last entry field of SRH
 *      @ tag: Tag field of SRH
 *      @ mt_flags: match options
 *      @ mt_invflags: Invert the sense of match options
 */

काष्ठा ip6t_srh अणु
	__u8                    next_hdr;
	__u8                    hdr_len;
	__u8                    segs_left;
	__u8                    last_entry;
	__u16                   tag;
	__u16                   mt_flags;
	__u16                   mt_invflags;
पूर्ण;

/**
 *      काष्ठा ip6t_srh1 - SRH match options (revision 1)
 *      @ next_hdr: Next header field of SRH
 *      @ hdr_len: Extension header length field of SRH
 *      @ segs_left: Segments left field of SRH
 *      @ last_entry: Last entry field of SRH
 *      @ tag: Tag field of SRH
 *      @ psid_addr: Address of previous SID in SRH SID list
 *      @ nsid_addr: Address of NEXT SID in SRH SID list
 *      @ lsid_addr: Address of LAST SID in SRH SID list
 *      @ psid_msk: Mask of previous SID in SRH SID list
 *      @ nsid_msk: Mask of next SID in SRH SID list
 *      @ lsid_msk: MAsk of last SID in SRH SID list
 *      @ mt_flags: match options
 *      @ mt_invflags: Invert the sense of match options
 */

काष्ठा ip6t_srh1 अणु
	__u8                    next_hdr;
	__u8                    hdr_len;
	__u8                    segs_left;
	__u8                    last_entry;
	__u16                   tag;
	काष्ठा in6_addr         psid_addr;
	काष्ठा in6_addr         nsid_addr;
	काष्ठा in6_addr         lsid_addr;
	काष्ठा in6_addr         psid_msk;
	काष्ठा in6_addr         nsid_msk;
	काष्ठा in6_addr         lsid_msk;
	__u16                   mt_flags;
	__u16                   mt_invflags;
पूर्ण;

#पूर्ण_अगर /*_IP6T_SRH_H*/
