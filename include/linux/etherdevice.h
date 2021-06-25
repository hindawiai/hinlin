<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  NET  is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		Definitions क्रम the Ethernet handlers.
 *
 * Version:	@(#)eth.h	1.0.4	05/13/93
 *
 * Authors:	Ross Biro
 *		Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 *
 *		Relocated to include/linux where it beदीर्घs by Alan Cox
 *							<gw4pts@gw4pts.ampr.org>
 */
#अगर_अघोषित _LINUX_ETHERDEVICE_H
#घोषणा _LINUX_ETHERDEVICE_H

#समावेश <linux/अगर_ether.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/crc32.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <यंत्र/bitsperदीर्घ.h>

#अगर_घोषित __KERNEL__
काष्ठा device;
पूर्णांक eth_platक्रमm_get_mac_address(काष्ठा device *dev, u8 *mac_addr);
अचिन्हित अक्षर *arch_get_platक्रमm_mac_address(व्योम);
पूर्णांक nvmem_get_mac_address(काष्ठा device *dev, व्योम *addrbuf);
u32 eth_get_headlen(स्थिर काष्ठा net_device *dev, स्थिर व्योम *data, u32 len);
__be16 eth_type_trans(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
बाह्य स्थिर काष्ठा header_ops eth_header_ops;

पूर्णांक eth_header(काष्ठा sk_buff *skb, काष्ठा net_device *dev, अचिन्हित लघु type,
	       स्थिर व्योम *daddr, स्थिर व्योम *saddr, अचिन्हित len);
पूर्णांक eth_header_parse(स्थिर काष्ठा sk_buff *skb, अचिन्हित अक्षर *haddr);
पूर्णांक eth_header_cache(स्थिर काष्ठा neighbour *neigh, काष्ठा hh_cache *hh,
		     __be16 type);
व्योम eth_header_cache_update(काष्ठा hh_cache *hh, स्थिर काष्ठा net_device *dev,
			     स्थिर अचिन्हित अक्षर *haddr);
__be16 eth_header_parse_protocol(स्थिर काष्ठा sk_buff *skb);
पूर्णांक eth_prepare_mac_addr_change(काष्ठा net_device *dev, व्योम *p);
व्योम eth_commit_mac_addr_change(काष्ठा net_device *dev, व्योम *p);
पूर्णांक eth_mac_addr(काष्ठा net_device *dev, व्योम *p);
पूर्णांक eth_validate_addr(काष्ठा net_device *dev);

काष्ठा net_device *alloc_etherdev_mqs(पूर्णांक माप_priv, अचिन्हित पूर्णांक txqs,
					    अचिन्हित पूर्णांक rxqs);
#घोषणा alloc_etherdev(माप_priv) alloc_etherdev_mq(माप_priv, 1)
#घोषणा alloc_etherdev_mq(माप_priv, count) alloc_etherdev_mqs(माप_priv, count, count)

काष्ठा net_device *devm_alloc_etherdev_mqs(काष्ठा device *dev, पूर्णांक माप_priv,
					   अचिन्हित पूर्णांक txqs,
					   अचिन्हित पूर्णांक rxqs);
#घोषणा devm_alloc_etherdev(dev, माप_priv) devm_alloc_etherdev_mqs(dev, माप_priv, 1, 1)

काष्ठा sk_buff *eth_gro_receive(काष्ठा list_head *head, काष्ठा sk_buff *skb);
पूर्णांक eth_gro_complete(काष्ठा sk_buff *skb, पूर्णांक nhoff);

/* Reserved Ethernet Addresses per IEEE 802.1Q */
अटल स्थिर u8 eth_reserved_addr_base[ETH_ALEN] __aligned(2) =
अणु 0x01, 0x80, 0xc2, 0x00, 0x00, 0x00 पूर्ण;
#घोषणा eth_stp_addr eth_reserved_addr_base

/**
 * is_link_local_ether_addr - Determine अगर given Ethernet address is link-local
 * @addr: Poपूर्णांकer to a six-byte array containing the Ethernet address
 *
 * Return true अगर address is link local reserved addr (01:80:c2:00:00:0X) per
 * IEEE 802.1Q 8.6.3 Frame filtering.
 *
 * Please note: addr must be aligned to u16.
 */
अटल अंतरभूत bool is_link_local_ether_addr(स्थिर u8 *addr)
अणु
	__be16 *a = (__be16 *)addr;
	अटल स्थिर __be16 *b = (स्थिर __be16 *)eth_reserved_addr_base;
	अटल स्थिर __be16 m = cpu_to_be16(0xfff0);

#अगर defined(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS)
	वापस (((*(स्थिर u32 *)addr) ^ (*(स्थिर u32 *)b)) |
		(__क्रमce पूर्णांक)((a[2] ^ b[2]) & m)) == 0;
#अन्यथा
	वापस ((a[0] ^ b[0]) | (a[1] ^ b[1]) | ((a[2] ^ b[2]) & m)) == 0;
#पूर्ण_अगर
पूर्ण

/**
 * is_zero_ether_addr - Determine अगर give Ethernet address is all zeros.
 * @addr: Poपूर्णांकer to a six-byte array containing the Ethernet address
 *
 * Return true अगर the address is all zeroes.
 *
 * Please note: addr must be aligned to u16.
 */
अटल अंतरभूत bool is_zero_ether_addr(स्थिर u8 *addr)
अणु
#अगर defined(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS)
	वापस ((*(स्थिर u32 *)addr) | (*(स्थिर u16 *)(addr + 4))) == 0;
#अन्यथा
	वापस (*(स्थिर u16 *)(addr + 0) |
		*(स्थिर u16 *)(addr + 2) |
		*(स्थिर u16 *)(addr + 4)) == 0;
#पूर्ण_अगर
पूर्ण

/**
 * is_multicast_ether_addr - Determine अगर the Ethernet address is a multicast.
 * @addr: Poपूर्णांकer to a six-byte array containing the Ethernet address
 *
 * Return true अगर the address is a multicast address.
 * By definition the broadcast address is also a multicast address.
 */
अटल अंतरभूत bool is_multicast_ether_addr(स्थिर u8 *addr)
अणु
#अगर defined(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS)
	u32 a = *(स्थिर u32 *)addr;
#अन्यथा
	u16 a = *(स्थिर u16 *)addr;
#पूर्ण_अगर
#अगर_घोषित __BIG_ENDIAN
	वापस 0x01 & (a >> ((माप(a) * 8) - 8));
#अन्यथा
	वापस 0x01 & a;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत bool is_multicast_ether_addr_64bits(स्थिर u8 addr[6+2])
अणु
#अगर defined(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS) && BITS_PER_LONG == 64
#अगर_घोषित __BIG_ENDIAN
	वापस 0x01 & ((*(स्थिर u64 *)addr) >> 56);
#अन्यथा
	वापस 0x01 & (*(स्थिर u64 *)addr);
#पूर्ण_अगर
#अन्यथा
	वापस is_multicast_ether_addr(addr);
#पूर्ण_अगर
पूर्ण

/**
 * is_local_ether_addr - Determine अगर the Ethernet address is locally-asचिन्हित one (IEEE 802).
 * @addr: Poपूर्णांकer to a six-byte array containing the Ethernet address
 *
 * Return true अगर the address is a local address.
 */
अटल अंतरभूत bool is_local_ether_addr(स्थिर u8 *addr)
अणु
	वापस 0x02 & addr[0];
पूर्ण

/**
 * is_broadcast_ether_addr - Determine अगर the Ethernet address is broadcast
 * @addr: Poपूर्णांकer to a six-byte array containing the Ethernet address
 *
 * Return true अगर the address is the broadcast address.
 *
 * Please note: addr must be aligned to u16.
 */
अटल अंतरभूत bool is_broadcast_ether_addr(स्थिर u8 *addr)
अणु
	वापस (*(स्थिर u16 *)(addr + 0) &
		*(स्थिर u16 *)(addr + 2) &
		*(स्थिर u16 *)(addr + 4)) == 0xffff;
पूर्ण

/**
 * is_unicast_ether_addr - Determine अगर the Ethernet address is unicast
 * @addr: Poपूर्णांकer to a six-byte array containing the Ethernet address
 *
 * Return true अगर the address is a unicast address.
 */
अटल अंतरभूत bool is_unicast_ether_addr(स्थिर u8 *addr)
अणु
	वापस !is_multicast_ether_addr(addr);
पूर्ण

/**
 * is_valid_ether_addr - Determine अगर the given Ethernet address is valid
 * @addr: Poपूर्णांकer to a six-byte array containing the Ethernet address
 *
 * Check that the Ethernet address (MAC) is not 00:00:00:00:00:00, is not
 * a multicast address, and is not FF:FF:FF:FF:FF:FF.
 *
 * Return true अगर the address is valid.
 *
 * Please note: addr must be aligned to u16.
 */
अटल अंतरभूत bool is_valid_ether_addr(स्थिर u8 *addr)
अणु
	/* FF:FF:FF:FF:FF:FF is a multicast address so we करोn't need to
	 * explicitly check क्रम it here. */
	वापस !is_multicast_ether_addr(addr) && !is_zero_ether_addr(addr);
पूर्ण

/**
 * eth_proto_is_802_3 - Determine अगर a given Ethertype/length is a protocol
 * @proto: Ethertype/length value to be tested
 *
 * Check that the value from the Ethertype/length field is a valid Ethertype.
 *
 * Return true अगर the valid is an 802.3 supported Ethertype.
 */
अटल अंतरभूत bool eth_proto_is_802_3(__be16 proto)
अणु
#अगर_अघोषित __BIG_ENDIAN
	/* अगर CPU is little endian mask off bits representing LSB */
	proto &= htons(0xFF00);
#पूर्ण_अगर
	/* cast both to u16 and compare since LSB can be ignored */
	वापस (__क्रमce u16)proto >= (__क्रमce u16)htons(ETH_P_802_3_MIN);
पूर्ण

/**
 * eth_अक्रमom_addr - Generate software asचिन्हित अक्रमom Ethernet address
 * @addr: Poपूर्णांकer to a six-byte array containing the Ethernet address
 *
 * Generate a अक्रमom Ethernet address (MAC) that is not multicast
 * and has the local asचिन्हित bit set.
 */
अटल अंतरभूत व्योम eth_अक्रमom_addr(u8 *addr)
अणु
	get_अक्रमom_bytes(addr, ETH_ALEN);
	addr[0] &= 0xfe;	/* clear multicast bit */
	addr[0] |= 0x02;	/* set local assignment bit (IEEE802) */
पूर्ण

#घोषणा अक्रमom_ether_addr(addr) eth_अक्रमom_addr(addr)

/**
 * eth_broadcast_addr - Assign broadcast address
 * @addr: Poपूर्णांकer to a six-byte array containing the Ethernet address
 *
 * Assign the broadcast address to the given address array.
 */
अटल अंतरभूत व्योम eth_broadcast_addr(u8 *addr)
अणु
	स_रखो(addr, 0xff, ETH_ALEN);
पूर्ण

/**
 * eth_zero_addr - Assign zero address
 * @addr: Poपूर्णांकer to a six-byte array containing the Ethernet address
 *
 * Assign the zero address to the given address array.
 */
अटल अंतरभूत व्योम eth_zero_addr(u8 *addr)
अणु
	स_रखो(addr, 0x00, ETH_ALEN);
पूर्ण

/**
 * eth_hw_addr_अक्रमom - Generate software asचिन्हित अक्रमom Ethernet and
 * set device flag
 * @dev: poपूर्णांकer to net_device काष्ठाure
 *
 * Generate a अक्रमom Ethernet address (MAC) to be used by a net device
 * and set addr_assign_type so the state can be पढ़ो by sysfs and be
 * used by userspace.
 */
अटल अंतरभूत व्योम eth_hw_addr_अक्रमom(काष्ठा net_device *dev)
अणु
	dev->addr_assign_type = NET_ADDR_RANDOM;
	eth_अक्रमom_addr(dev->dev_addr);
पूर्ण

/**
 * eth_hw_addr_crc - Calculate CRC from netdev_hw_addr
 * @ha: poपूर्णांकer to hardware address
 *
 * Calculate CRC from a hardware address as basis क्रम filter hashes.
 */
अटल अंतरभूत u32 eth_hw_addr_crc(काष्ठा netdev_hw_addr *ha)
अणु
	वापस ether_crc(ETH_ALEN, ha->addr);
पूर्ण

/**
 * ether_addr_copy - Copy an Ethernet address
 * @dst: Poपूर्णांकer to a six-byte array Ethernet address destination
 * @src: Poपूर्णांकer to a six-byte array Ethernet address source
 *
 * Please note: dst & src must both be aligned to u16.
 */
अटल अंतरभूत व्योम ether_addr_copy(u8 *dst, स्थिर u8 *src)
अणु
#अगर defined(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS)
	*(u32 *)dst = *(स्थिर u32 *)src;
	*(u16 *)(dst + 4) = *(स्थिर u16 *)(src + 4);
#अन्यथा
	u16 *a = (u16 *)dst;
	स्थिर u16 *b = (स्थिर u16 *)src;

	a[0] = b[0];
	a[1] = b[1];
	a[2] = b[2];
#पूर्ण_अगर
पूर्ण

/**
 * eth_hw_addr_inherit - Copy dev_addr from another net_device
 * @dst: poपूर्णांकer to net_device to copy dev_addr to
 * @src: poपूर्णांकer to net_device to copy dev_addr from
 *
 * Copy the Ethernet address from one net_device to another aदीर्घ with
 * the address attributes (addr_assign_type).
 */
अटल अंतरभूत व्योम eth_hw_addr_inherit(काष्ठा net_device *dst,
				       काष्ठा net_device *src)
अणु
	dst->addr_assign_type = src->addr_assign_type;
	ether_addr_copy(dst->dev_addr, src->dev_addr);
पूर्ण

/**
 * ether_addr_equal - Compare two Ethernet addresses
 * @addr1: Poपूर्णांकer to a six-byte array containing the Ethernet address
 * @addr2: Poपूर्णांकer other six-byte array containing the Ethernet address
 *
 * Compare two Ethernet addresses, वापसs true अगर equal
 *
 * Please note: addr1 & addr2 must both be aligned to u16.
 */
अटल अंतरभूत bool ether_addr_equal(स्थिर u8 *addr1, स्थिर u8 *addr2)
अणु
#अगर defined(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS)
	u32 fold = ((*(स्थिर u32 *)addr1) ^ (*(स्थिर u32 *)addr2)) |
		   ((*(स्थिर u16 *)(addr1 + 4)) ^ (*(स्थिर u16 *)(addr2 + 4)));

	वापस fold == 0;
#अन्यथा
	स्थिर u16 *a = (स्थिर u16 *)addr1;
	स्थिर u16 *b = (स्थिर u16 *)addr2;

	वापस ((a[0] ^ b[0]) | (a[1] ^ b[1]) | (a[2] ^ b[2])) == 0;
#पूर्ण_अगर
पूर्ण

/**
 * ether_addr_equal_64bits - Compare two Ethernet addresses
 * @addr1: Poपूर्णांकer to an array of 8 bytes
 * @addr2: Poपूर्णांकer to an other array of 8 bytes
 *
 * Compare two Ethernet addresses, वापसs true अगर equal, false otherwise.
 *
 * The function करोesn't need any conditional branches and possibly uses
 * word memory accesses on CPU allowing cheap unaligned memory पढ़ोs.
 * arrays = अणु byte1, byte2, byte3, byte4, byte5, byte6, pad1, pad2 पूर्ण
 *
 * Please note that alignment of addr1 & addr2 are only guaranteed to be 16 bits.
 */

अटल अंतरभूत bool ether_addr_equal_64bits(स्थिर u8 addr1[6+2],
					   स्थिर u8 addr2[6+2])
अणु
#अगर defined(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS) && BITS_PER_LONG == 64
	u64 fold = (*(स्थिर u64 *)addr1) ^ (*(स्थिर u64 *)addr2);

#अगर_घोषित __BIG_ENDIAN
	वापस (fold >> 16) == 0;
#अन्यथा
	वापस (fold << 16) == 0;
#पूर्ण_अगर
#अन्यथा
	वापस ether_addr_equal(addr1, addr2);
#पूर्ण_अगर
पूर्ण

/**
 * ether_addr_equal_unaligned - Compare two not u16 aligned Ethernet addresses
 * @addr1: Poपूर्णांकer to a six-byte array containing the Ethernet address
 * @addr2: Poपूर्णांकer other six-byte array containing the Ethernet address
 *
 * Compare two Ethernet addresses, वापसs true अगर equal
 *
 * Please note: Use only when any Ethernet address may not be u16 aligned.
 */
अटल अंतरभूत bool ether_addr_equal_unaligned(स्थिर u8 *addr1, स्थिर u8 *addr2)
अणु
#अगर defined(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS)
	वापस ether_addr_equal(addr1, addr2);
#अन्यथा
	वापस स_भेद(addr1, addr2, ETH_ALEN) == 0;
#पूर्ण_अगर
पूर्ण

/**
 * ether_addr_equal_masked - Compare two Ethernet addresses with a mask
 * @addr1: Poपूर्णांकer to a six-byte array containing the 1st Ethernet address
 * @addr2: Poपूर्णांकer to a six-byte array containing the 2nd Ethernet address
 * @mask: Poपूर्णांकer to a six-byte array containing the Ethernet address biपंचांगask
 *
 * Compare two Ethernet addresses with a mask, वापसs true अगर क्रम every bit
 * set in the biपंचांगask the equivalent bits in the ethernet addresses are equal.
 * Using a mask with all bits set is a slower ether_addr_equal.
 */
अटल अंतरभूत bool ether_addr_equal_masked(स्थिर u8 *addr1, स्थिर u8 *addr2,
					   स्थिर u8 *mask)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ETH_ALEN; i++) अणु
		अगर ((addr1[i] ^ addr2[i]) & mask[i])
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

/**
 * ether_addr_to_u64 - Convert an Ethernet address पूर्णांकo a u64 value.
 * @addr: Poपूर्णांकer to a six-byte array containing the Ethernet address
 *
 * Return a u64 value of the address
 */
अटल अंतरभूत u64 ether_addr_to_u64(स्थिर u8 *addr)
अणु
	u64 u = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ETH_ALEN; i++)
		u = u << 8 | addr[i];

	वापस u;
पूर्ण

/**
 * u64_to_ether_addr - Convert a u64 to an Ethernet address.
 * @u: u64 to convert to an Ethernet MAC address
 * @addr: Poपूर्णांकer to a six-byte array to contain the Ethernet address
 */
अटल अंतरभूत व्योम u64_to_ether_addr(u64 u, u8 *addr)
अणु
	पूर्णांक i;

	क्रम (i = ETH_ALEN - 1; i >= 0; i--) अणु
		addr[i] = u & 0xff;
		u = u >> 8;
	पूर्ण
पूर्ण

/**
 * eth_addr_dec - Decrement the given MAC address
 *
 * @addr: Poपूर्णांकer to a six-byte array containing Ethernet address to decrement
 */
अटल अंतरभूत व्योम eth_addr_dec(u8 *addr)
अणु
	u64 u = ether_addr_to_u64(addr);

	u--;
	u64_to_ether_addr(u, addr);
पूर्ण

/**
 * eth_addr_inc() - Increment the given MAC address.
 * @addr: Poपूर्णांकer to a six-byte array containing Ethernet address to increment.
 */
अटल अंतरभूत व्योम eth_addr_inc(u8 *addr)
अणु
	u64 u = ether_addr_to_u64(addr);

	u++;
	u64_to_ether_addr(u, addr);
पूर्ण

/**
 * is_etherdev_addr - Tell अगर given Ethernet address beदीर्घs to the device.
 * @dev: Poपूर्णांकer to a device काष्ठाure
 * @addr: Poपूर्णांकer to a six-byte array containing the Ethernet address
 *
 * Compare passed address with all addresses of the device. Return true अगर the
 * address अगर one of the device addresses.
 *
 * Note that this function calls ether_addr_equal_64bits() so take care of
 * the right padding.
 */
अटल अंतरभूत bool is_etherdev_addr(स्थिर काष्ठा net_device *dev,
				    स्थिर u8 addr[6 + 2])
अणु
	काष्ठा netdev_hw_addr *ha;
	bool res = false;

	rcu_पढ़ो_lock();
	क्रम_each_dev_addr(dev, ha) अणु
		res = ether_addr_equal_64bits(addr, ha->addr);
		अगर (res)
			अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस res;
पूर्ण
#पूर्ण_अगर	/* __KERNEL__ */

/**
 * compare_ether_header - Compare two Ethernet headers
 * @a: Poपूर्णांकer to Ethernet header
 * @b: Poपूर्णांकer to Ethernet header
 *
 * Compare two Ethernet headers, वापसs 0 अगर equal.
 * This assumes that the network header (i.e., IP header) is 4-byte
 * aligned OR the platक्रमm can handle unaligned access.  This is the
 * हाल क्रम all packets coming पूर्णांकo netअगर_receive_skb or similar
 * entry poपूर्णांकs.
 */

अटल अंतरभूत अचिन्हित दीर्घ compare_ether_header(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
#अगर defined(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS) && BITS_PER_LONG == 64
	अचिन्हित दीर्घ fold;

	/*
	 * We want to compare 14 bytes:
	 *  [a0 ... a13] ^ [b0 ... b13]
	 * Use two दीर्घ XOR, ORed together, with an overlap of two bytes.
	 *  [a0  a1  a2  a3  a4  a5  a6  a7 ] ^ [b0  b1  b2  b3  b4  b5  b6  b7 ] |
	 *  [a6  a7  a8  a9  a10 a11 a12 a13] ^ [b6  b7  b8  b9  b10 b11 b12 b13]
	 * This means the [a6 a7] ^ [b6 b7] part is करोne two बार.
	*/
	fold = *(अचिन्हित दीर्घ *)a ^ *(अचिन्हित दीर्घ *)b;
	fold |= *(अचिन्हित दीर्घ *)(a + 6) ^ *(अचिन्हित दीर्घ *)(b + 6);
	वापस fold;
#अन्यथा
	u32 *a32 = (u32 *)((u8 *)a + 2);
	u32 *b32 = (u32 *)((u8 *)b + 2);

	वापस (*(u16 *)a ^ *(u16 *)b) | (a32[0] ^ b32[0]) |
	       (a32[1] ^ b32[1]) | (a32[2] ^ b32[2]);
#पूर्ण_अगर
पूर्ण

/**
 * eth_skb_pad - Pad buffer to mininum number of octets क्रम Ethernet frame
 * @skb: Buffer to pad
 *
 * An Ethernet frame should have a minimum size of 60 bytes.  This function
 * takes लघु frames and pads them with zeros up to the 60 byte limit.
 */
अटल अंतरभूत पूर्णांक eth_skb_pad(काष्ठा sk_buff *skb)
अणु
	वापस skb_put_padto(skb, ETH_ZLEN);
पूर्ण

#पूर्ण_अगर	/* _LINUX_ETHERDEVICE_H */
