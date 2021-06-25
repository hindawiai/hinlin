<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * udbg debug output routine via GELIC UDP broadcasts
 *
 * Copyright (C) 2007 Sony Computer Entertainment Inc.
 * Copyright 2006, 2007 Sony Corporation
 * Copyright (C) 2010 Hector Martin <hector@marcansoft.com>
 * Copyright (C) 2011 Andre Heider <a.heider@gmail.com>
 */

#समावेश <linux/अगर_ether.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/ip.h>
#समावेश <linux/udp.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/lv1call.h>

#घोषणा GELIC_BUS_ID 1
#घोषणा GELIC_DEVICE_ID 0
#घोषणा GELIC_DEBUG_PORT 18194
#घोषणा GELIC_MAX_MESSAGE_SIZE 1000

#घोषणा GELIC_LV1_GET_MAC_ADDRESS 1
#घोषणा GELIC_LV1_GET_VLAN_ID 4
#घोषणा GELIC_LV1_VLAN_TX_ETHERNET_0 2

#घोषणा GELIC_DESCR_DMA_STAT_MASK 0xf0000000
#घोषणा GELIC_DESCR_DMA_CARDOWNED 0xa0000000

#घोषणा GELIC_DESCR_TX_DMA_IKE 0x00080000
#घोषणा GELIC_DESCR_TX_DMA_NO_CHKSUM 0x00000000
#घोषणा GELIC_DESCR_TX_DMA_FRAME_TAIL 0x00040000

#घोषणा GELIC_DESCR_DMA_CMD_NO_CHKSUM (GELIC_DESCR_DMA_CARDOWNED | \
				       GELIC_DESCR_TX_DMA_IKE | \
				       GELIC_DESCR_TX_DMA_NO_CHKSUM)

अटल u64 bus_addr;

काष्ठा gelic_descr अणु
	/* as defined by the hardware */
	__be32 buf_addr;
	__be32 buf_size;
	__be32 next_descr_addr;
	__be32 dmac_cmd_status;
	__be32 result_size;
	__be32 valid_size;	/* all zeroes क्रम tx */
	__be32 data_status;
	__be32 data_error;	/* all zeroes क्रम tx */
पूर्ण __attribute__((aligned(32)));

काष्ठा debug_block अणु
	काष्ठा gelic_descr descr;
	u8 pkt[1520];
पूर्ण __packed;

अटल __iomem काष्ठा ethhdr *h_eth;
अटल __iomem काष्ठा vlan_hdr *h_vlan;
अटल __iomem काष्ठा iphdr *h_ip;
अटल __iomem काष्ठा udphdr *h_udp;

अटल __iomem अक्षर *pmsg;
अटल __iomem अक्षर *pmsgc;

अटल __iomem काष्ठा debug_block dbg __attribute__((aligned(32)));

अटल पूर्णांक header_size;

अटल व्योम map_dma_mem(पूर्णांक bus_id, पूर्णांक dev_id, व्योम *start, माप_प्रकार len,
			u64 *real_bus_addr)
अणु
	s64 result;
	u64 real_addr = ((u64)start) & 0x0fffffffffffffffUL;
	u64 real_end = real_addr + len;
	u64 map_start = real_addr & ~0xfff;
	u64 map_end = (real_end + 0xfff) & ~0xfff;
	u64 bus_addr = 0;

	u64 flags = 0xf800000000000000UL;

	result = lv1_allocate_device_dma_region(bus_id, dev_id,
						map_end - map_start, 12, 0,
						&bus_addr);
	अगर (result)
		lv1_panic(0);

	result = lv1_map_device_dma_region(bus_id, dev_id, map_start,
					   bus_addr, map_end - map_start,
					   flags);
	अगर (result)
		lv1_panic(0);

	*real_bus_addr = bus_addr + real_addr - map_start;
पूर्ण

अटल पूर्णांक unmap_dma_mem(पूर्णांक bus_id, पूर्णांक dev_id, u64 bus_addr, माप_प्रकार len)
अणु
	s64 result;
	u64 real_bus_addr;

	real_bus_addr = bus_addr & ~0xfff;
	len += bus_addr - real_bus_addr;
	len = (len + 0xfff) & ~0xfff;

	result = lv1_unmap_device_dma_region(bus_id, dev_id, real_bus_addr,
					     len);
	अगर (result)
		वापस result;

	वापस lv1_मुक्त_device_dma_region(bus_id, dev_id, real_bus_addr);
पूर्ण

अटल व्योम gelic_debug_init(व्योम)
अणु
	s64 result;
	u64 v2;
	u64 mac;
	u64 vlan_id;

	result = lv1_खोलो_device(GELIC_BUS_ID, GELIC_DEVICE_ID, 0);
	अगर (result)
		lv1_panic(0);

	map_dma_mem(GELIC_BUS_ID, GELIC_DEVICE_ID, &dbg, माप(dbg),
		    &bus_addr);

	स_रखो(&dbg, 0, माप(dbg));

	dbg.descr.buf_addr = bus_addr + दुरत्व(काष्ठा debug_block, pkt);

	wmb();

	result = lv1_net_control(GELIC_BUS_ID, GELIC_DEVICE_ID,
				 GELIC_LV1_GET_MAC_ADDRESS, 0, 0, 0,
				 &mac, &v2);
	अगर (result)
		lv1_panic(0);

	mac <<= 16;

	h_eth = (काष्ठा ethhdr *)dbg.pkt;

	eth_broadcast_addr(h_eth->h_dest);
	स_नकल(&h_eth->h_source, &mac, ETH_ALEN);

	header_size = माप(काष्ठा ethhdr);

	result = lv1_net_control(GELIC_BUS_ID, GELIC_DEVICE_ID,
				 GELIC_LV1_GET_VLAN_ID,
				 GELIC_LV1_VLAN_TX_ETHERNET_0, 0, 0,
				 &vlan_id, &v2);
	अगर (!result) अणु
		h_eth->h_proto= ETH_P_8021Q;

		header_size += माप(काष्ठा vlan_hdr);
		h_vlan = (काष्ठा vlan_hdr *)(h_eth + 1);
		h_vlan->h_vlan_TCI = vlan_id;
		h_vlan->h_vlan_encapsulated_proto = ETH_P_IP;
		h_ip = (काष्ठा iphdr *)(h_vlan + 1);
	पूर्ण अन्यथा अणु
		h_eth->h_proto= 0x0800;
		h_ip = (काष्ठा iphdr *)(h_eth + 1);
	पूर्ण

	header_size += माप(काष्ठा iphdr);
	h_ip->version = 4;
	h_ip->ihl = 5;
	h_ip->ttl = 10;
	h_ip->protocol = 0x11;
	h_ip->saddr = 0x00000000;
	h_ip->daddr = 0xffffffff;

	header_size += माप(काष्ठा udphdr);
	h_udp = (काष्ठा udphdr *)(h_ip + 1);
	h_udp->source = GELIC_DEBUG_PORT;
	h_udp->dest = GELIC_DEBUG_PORT;

	pmsgc = pmsg = (अक्षर *)(h_udp + 1);
पूर्ण

अटल व्योम gelic_debug_shutकरोwn(व्योम)
अणु
	अगर (bus_addr)
		unmap_dma_mem(GELIC_BUS_ID, GELIC_DEVICE_ID,
			      bus_addr, माप(dbg));
	lv1_बंद_device(GELIC_BUS_ID, GELIC_DEVICE_ID);
पूर्ण

अटल व्योम gelic_sendbuf(पूर्णांक msgsize)
अणु
	u16 *p;
	u32 sum;
	पूर्णांक i;

	dbg.descr.buf_size = header_size + msgsize;
	h_ip->tot_len = msgsize + माप(काष्ठा udphdr) +
			     माप(काष्ठा iphdr);
	h_udp->len = msgsize + माप(काष्ठा udphdr);

	h_ip->check = 0;
	sum = 0;
	p = (u16 *)h_ip;
	क्रम (i = 0; i < 5; i++)
		sum += *p++;
	h_ip->check = ~(sum + (sum >> 16));

	dbg.descr.dmac_cmd_status = GELIC_DESCR_DMA_CMD_NO_CHKSUM |
				    GELIC_DESCR_TX_DMA_FRAME_TAIL;
	dbg.descr.result_size = 0;
	dbg.descr.data_status = 0;

	wmb();

	lv1_net_start_tx_dma(GELIC_BUS_ID, GELIC_DEVICE_ID, bus_addr, 0);

	जबतक ((dbg.descr.dmac_cmd_status & GELIC_DESCR_DMA_STAT_MASK) ==
	       GELIC_DESCR_DMA_CARDOWNED)
		cpu_relax();
पूर्ण

अटल व्योम ps3gelic_udbg_अ_दो(अक्षर ch)
अणु
	*pmsgc++ = ch;
	अगर (ch == '\n' || (pmsgc-pmsg) >= GELIC_MAX_MESSAGE_SIZE) अणु
		gelic_sendbuf(pmsgc-pmsg);
		pmsgc = pmsg;
	पूर्ण
पूर्ण

व्योम __init udbg_init_ps3gelic(व्योम)
अणु
	gelic_debug_init();
	udbg_अ_दो = ps3gelic_udbg_अ_दो;
पूर्ण

व्योम udbg_shutकरोwn_ps3gelic(व्योम)
अणु
	udbg_अ_दो = शून्य;
	gelic_debug_shutकरोwn();
पूर्ण
EXPORT_SYMBOL(udbg_shutकरोwn_ps3gelic);
