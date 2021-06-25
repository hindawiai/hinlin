<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __LINUX_BRIDGE_EBT_AMONG_H
#घोषणा __LINUX_BRIDGE_EBT_AMONG_H

#समावेश <linux/types.h>

#घोषणा EBT_AMONG_DST 0x01
#घोषणा EBT_AMONG_SRC 0x02

/* Grzegorz Borowiak <grzes@gnu.univ.gda.pl> 2003
 * 
 * Write-once-पढ़ो-many hash table, used क्रम checking अगर a given
 * MAC address beदीर्घs to a set or not and possibly क्रम checking
 * अगर it is related with a given IPv4 address.
 *
 * The hash value of an address is its last byte.
 * 
 * In real-world ethernet addresses, values of the last byte are
 * evenly distributed and there is no need to consider other bytes.
 * It would only slow the routines करोwn.
 *
 * For MAC address comparison speedup reasons, we पूर्णांकroduce a trick.
 * MAC address is mapped onto an array of two 32-bit पूर्णांकegers.
 * This pair of पूर्णांकegers is compared with MAC addresses in the
 * hash table, which are stored also in क्रमm of pairs of पूर्णांकegers
 * (in `cmp' array). This is quick as it requires only two elementary
 * number comparisons in worst हाल. Further, we take advantage of
 * fact that entropy of 3 last bytes of address is larger than entropy
 * of 3 first bytes. So first we compare 4 last bytes of addresses and
 * अगर they are the same we compare 2 first.
 *
 * Yes, it is a memory overhead, but in 2003 AD, who cares?
 */

काष्ठा ebt_mac_wormhash_tuple अणु
	__u32 cmp[2];
	__be32 ip;
पूर्ण;

काष्ठा ebt_mac_wormhash अणु
	पूर्णांक table[257];
	पूर्णांक poolsize;
	काष्ठा ebt_mac_wormhash_tuple pool[0];
पूर्ण;

#घोषणा ebt_mac_wormhash_size(x) ((x) ? माप(काष्ठा ebt_mac_wormhash) \
		+ (x)->poolsize * माप(काष्ठा ebt_mac_wormhash_tuple) : 0)

काष्ठा ebt_among_info अणु
	पूर्णांक wh_dst_ofs;
	पूर्णांक wh_src_ofs;
	पूर्णांक biपंचांगask;
पूर्ण;

#घोषणा EBT_AMONG_DST_NEG 0x1
#घोषणा EBT_AMONG_SRC_NEG 0x2

#घोषणा ebt_among_wh_dst(x) ((x)->wh_dst_ofs ? \
	(काष्ठा ebt_mac_wormhash*)((अक्षर*)(x) + (x)->wh_dst_ofs) : शून्य)
#घोषणा ebt_among_wh_src(x) ((x)->wh_src_ofs ? \
	(काष्ठा ebt_mac_wormhash*)((अक्षर*)(x) + (x)->wh_src_ofs) : शून्य)

#घोषणा EBT_AMONG_MATCH "among"

#पूर्ण_अगर
