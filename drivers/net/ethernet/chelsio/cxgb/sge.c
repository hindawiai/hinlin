<शैली गुरु>
/*****************************************************************************
 *                                                                           *
 * File: sge.c                                                               *
 * $Revision: 1.26 $                                                         *
 * $Date: 2005/06/21 18:29:48 $                                              *
 * Description:                                                              *
 *  DMA engine.                                                              *
 *  part of the Chelsio 10Gb Ethernet Driver.                                *
 *                                                                           *
 * This program is मुक्त software; you can redistribute it and/or modअगरy      *
 * it under the terms of the GNU General Public License, version 2, as       *
 * published by the Free Software Foundation.                                *
 *                                                                           *
 * You should have received a copy of the GNU General Public License aदीर्घ   *
 * with this program; अगर not, see <http://www.gnu.org/licenses/>.            *
 *                                                                           *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED    *
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF      *
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.                     *
 *                                                                           *
 * http://www.chelsio.com                                                    *
 *                                                                           *
 * Copyright (c) 2003 - 2005 Chelsio Communications, Inc.                    *
 * All rights reserved.                                                      *
 *                                                                           *
 * Maपूर्णांकainers: मुख्यtainers@chelsio.com                                      *
 *                                                                           *
 * Authors: Dimitrios Michailidis   <dm@chelsio.com>                         *
 *          Tina Yang               <tainay@chelsio.com>                     *
 *          Felix Marti             <felix@chelsio.com>                      *
 *          Scott Barकरोne           <sbarकरोne@chelsio.com>                   *
 *          Kurt Ottaway            <kottaway@chelsio.com>                   *
 *          Frank DiMambro          <frank@chelsio.com>                      *
 *                                                                           *
 * History:                                                                  *
 *                                                                           *
 ****************************************************************************/

#समावेश "common.h"

#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/pci.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/mm.h>
#समावेश <linux/tcp.h>
#समावेश <linux/ip.h>
#समावेश <linux/in.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/slab.h>
#समावेश <linux/prefetch.h>

#समावेश "cpl5_cmd.h"
#समावेश "sge.h"
#समावेश "regs.h"
#समावेश "espi.h"

/* This beदीर्घs in अगर_ether.h */
#घोषणा ETH_P_CPL5 0xf

#घोषणा SGE_CMDQ_N		2
#घोषणा SGE_FREELQ_N		2
#घोषणा SGE_CMDQ0_E_N		1024
#घोषणा SGE_CMDQ1_E_N		128
#घोषणा SGE_FREEL_SIZE		4096
#घोषणा SGE_JUMBO_FREEL_SIZE	512
#घोषणा SGE_FREEL_REFILL_THRESH	16
#घोषणा SGE_RESPQ_E_N		1024
#घोषणा SGE_INTRTIMER_NRES	1000
#घोषणा SGE_RX_SM_BUF_SIZE	1536
#घोषणा SGE_TX_DESC_MAX_PLEN	16384

#घोषणा SGE_RESPQ_REPLENISH_THRES (SGE_RESPQ_E_N / 4)

/*
 * Period of the TX buffer reclaim समयr.  This समयr करोes not need to run
 * frequently as TX buffers are usually reclaimed by new TX packets.
 */
#घोषणा TX_RECLAIM_PERIOD (HZ / 4)

#घोषणा M_CMD_LEN       0x7fffffff
#घोषणा V_CMD_LEN(v)    (v)
#घोषणा G_CMD_LEN(v)    ((v) & M_CMD_LEN)
#घोषणा V_CMD_GEN1(v)   ((v) << 31)
#घोषणा V_CMD_GEN2(v)   (v)
#घोषणा F_CMD_DATAVALID (1 << 1)
#घोषणा F_CMD_SOP       (1 << 2)
#घोषणा V_CMD_EOP(v)    ((v) << 3)

/*
 * Command queue, receive buffer list, and response queue descriptors.
 */
#अगर defined(__BIG_ENDIAN_BITFIELD)
काष्ठा cmdQ_e अणु
	u32 addr_lo;
	u32 len_gen;
	u32 flags;
	u32 addr_hi;
पूर्ण;

काष्ठा मुक्तlQ_e अणु
	u32 addr_lo;
	u32 len_gen;
	u32 gen2;
	u32 addr_hi;
पूर्ण;

काष्ठा respQ_e अणु
	u32 Qsleeping		: 4;
	u32 Cmdq1CreditReturn	: 5;
	u32 Cmdq1DmaComplete	: 5;
	u32 Cmdq0CreditReturn	: 5;
	u32 Cmdq0DmaComplete	: 5;
	u32 FreelistQid		: 2;
	u32 CreditValid		: 1;
	u32 DataValid		: 1;
	u32 Offload		: 1;
	u32 Eop			: 1;
	u32 Sop			: 1;
	u32 GenerationBit	: 1;
	u32 BufferLength;
पूर्ण;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
काष्ठा cmdQ_e अणु
	u32 len_gen;
	u32 addr_lo;
	u32 addr_hi;
	u32 flags;
पूर्ण;

काष्ठा मुक्तlQ_e अणु
	u32 len_gen;
	u32 addr_lo;
	u32 addr_hi;
	u32 gen2;
पूर्ण;

काष्ठा respQ_e अणु
	u32 BufferLength;
	u32 GenerationBit	: 1;
	u32 Sop			: 1;
	u32 Eop			: 1;
	u32 Offload		: 1;
	u32 DataValid		: 1;
	u32 CreditValid		: 1;
	u32 FreelistQid		: 2;
	u32 Cmdq0DmaComplete	: 5;
	u32 Cmdq0CreditReturn	: 5;
	u32 Cmdq1DmaComplete	: 5;
	u32 Cmdq1CreditReturn	: 5;
	u32 Qsleeping		: 4;
पूर्ण ;
#पूर्ण_अगर

/*
 * SW Context Command and Freelist Queue Descriptors
 */
काष्ठा cmdQ_ce अणु
	काष्ठा sk_buff *skb;
	DEFINE_DMA_UNMAP_ADDR(dma_addr);
	DEFINE_DMA_UNMAP_LEN(dma_len);
पूर्ण;

काष्ठा मुक्तlQ_ce अणु
	काष्ठा sk_buff *skb;
	DEFINE_DMA_UNMAP_ADDR(dma_addr);
	DEFINE_DMA_UNMAP_LEN(dma_len);
पूर्ण;

/*
 * SW command, मुक्तlist and response rings
 */
काष्ठा cmdQ अणु
	अचिन्हित दीर्घ   status;         /* HW DMA fetch status */
	अचिन्हित पूर्णांक    in_use;         /* # of in-use command descriptors */
	अचिन्हित पूर्णांक	size;	        /* # of descriptors */
	अचिन्हित पूर्णांक    processed;      /* total # of descs HW has processed */
	अचिन्हित पूर्णांक    cleaned;        /* total # of descs SW has reclaimed */
	अचिन्हित पूर्णांक    stop_thres;     /* SW TX queue suspend threshold */
	u16		pidx;           /* producer index (SW) */
	u16		cidx;           /* consumer index (HW) */
	u8		genbit;         /* current generation (=valid) bit */
	u8              sop;            /* is next entry start of packet? */
	काष्ठा cmdQ_e  *entries;        /* HW command descriptor Q */
	काष्ठा cmdQ_ce *centries;       /* SW command context descriptor Q */
	dma_addr_t	dma_addr;       /* DMA addr HW command descriptor Q */
	spinlock_t	lock;           /* Lock to protect cmdQ enqueuing */
पूर्ण;

काष्ठा मुक्तlQ अणु
	अचिन्हित पूर्णांक	credits;        /* # of available RX buffers */
	अचिन्हित पूर्णांक	size;	        /* मुक्त list capacity */
	u16		pidx;           /* producer index (SW) */
	u16		cidx;           /* consumer index (HW) */
	u16		rx_buffer_size; /* Buffer size on this मुक्त list */
	u16             dma_offset;     /* DMA offset to align IP headers */
	u16             recycleq_idx;   /* skb recycle q to use */
	u8		genbit;	        /* current generation (=valid) bit */
	काष्ठा मुक्तlQ_e	*entries;       /* HW मुक्तlist descriptor Q */
	काष्ठा मुक्तlQ_ce *centries;     /* SW मुक्तlist context descriptor Q */
	dma_addr_t	dma_addr;       /* DMA addr HW मुक्तlist descriptor Q */
पूर्ण;

काष्ठा respQ अणु
	अचिन्हित पूर्णांक	credits;        /* credits to be वापसed to SGE */
	अचिन्हित पूर्णांक	size;	        /* # of response Q descriptors */
	u16		cidx;	        /* consumer index (SW) */
	u8		genbit;	        /* current generation(=valid) bit */
	काष्ठा respQ_e *entries;        /* HW response descriptor Q */
	dma_addr_t	dma_addr;       /* DMA addr HW response descriptor Q */
पूर्ण;

/* Bit flags क्रम cmdQ.status */
क्रमागत अणु
	CMDQ_STAT_RUNNING = 1,          /* fetch engine is running */
	CMDQ_STAT_LAST_PKT_DB = 2       /* last packet rung the करोorbell */
पूर्ण;

/* T204 TX SW scheduler */

/* Per T204 TX port */
काष्ठा sched_port अणु
	अचिन्हित पूर्णांक	avail;		/* available bits - quota */
	अचिन्हित पूर्णांक	drain_bits_per_1024ns; /* drain rate */
	अचिन्हित पूर्णांक	speed;		/* drain rate, mbps */
	अचिन्हित पूर्णांक	mtu;		/* mtu size */
	काष्ठा sk_buff_head skbq;	/* pending skbs */
पूर्ण;

/* Per T204 device */
काष्ठा sched अणु
	kसमय_प्रकार         last_updated;   /* last समय quotas were computed */
	अचिन्हित पूर्णांक	max_avail;	/* max bits to be sent to any port */
	अचिन्हित पूर्णांक	port;		/* port index (round robin ports) */
	अचिन्हित पूर्णांक	num;		/* num skbs in per port queues */
	काष्ठा sched_port p[MAX_NPORTS];
	काष्ठा tasklet_काष्ठा sched_tsk;/* tasklet used to run scheduler */
	काष्ठा sge *sge;
पूर्ण;

अटल व्योम restart_sched(काष्ठा tasklet_काष्ठा *t);


/*
 * Main SGE data काष्ठाure
 *
 * Interrupts are handled by a single CPU and it is likely that on a MP प्रणाली
 * the application is migrated to another CPU. In that scenario, we try to
 * separate the RX(in irq context) and TX state in order to decrease memory
 * contention.
 */
काष्ठा sge अणु
	काष्ठा adapter *adapter;	/* adapter backpoपूर्णांकer */
	काष्ठा net_device *netdev;      /* netdevice backpoपूर्णांकer */
	काष्ठा मुक्तlQ	मुक्तlQ[SGE_FREELQ_N]; /* buffer मुक्त lists */
	काष्ठा respQ	respQ;		/* response Q */
	अचिन्हित दीर्घ   stopped_tx_queues; /* biपंचांगap of suspended Tx queues */
	अचिन्हित पूर्णांक	rx_pkt_pad;     /* RX padding क्रम L2 packets */
	अचिन्हित पूर्णांक	jumbo_fl;       /* jumbo मुक्तlist Q index */
	अचिन्हित पूर्णांक	पूर्णांकrसमयr_nres;	/* no-resource पूर्णांकerrupt समयr */
	अचिन्हित पूर्णांक    fixed_पूर्णांकrसमयr;/* non-adaptive पूर्णांकerrupt समयr */
	काष्ठा समयr_list tx_reclaim_समयr; /* reclaims TX buffers */
	काष्ठा समयr_list espibug_समयr;
	अचिन्हित दीर्घ	espibug_समयout;
	काष्ठा sk_buff	*espibug_skb[MAX_NPORTS];
	u32		sge_control;	/* shaकरोw value of sge control reg */
	काष्ठा sge_पूर्णांकr_counts stats;
	काष्ठा sge_port_stats __percpu *port_stats[MAX_NPORTS];
	काष्ठा sched	*tx_sched;
	काष्ठा cmdQ cmdQ[SGE_CMDQ_N] ____cacheline_aligned_in_smp;
पूर्ण;

अटल स्थिर u8 ch_mac_addr[ETH_ALEN] = अणु
	0x0, 0x7, 0x43, 0x0, 0x0, 0x0
पूर्ण;

/*
 * stop tasklet and मुक्त all pending skb's
 */
अटल व्योम tx_sched_stop(काष्ठा sge *sge)
अणु
	काष्ठा sched *s = sge->tx_sched;
	पूर्णांक i;

	tasklet_समाप्त(&s->sched_tsk);

	क्रम (i = 0; i < MAX_NPORTS; i++)
		__skb_queue_purge(&s->p[s->port].skbq);
पूर्ण

/*
 * t1_sched_update_parms() is called when the MTU or link speed changes. It
 * re-computes scheduler parameters to scope with the change.
 */
अचिन्हित पूर्णांक t1_sched_update_parms(काष्ठा sge *sge, अचिन्हित पूर्णांक port,
				   अचिन्हित पूर्णांक mtu, अचिन्हित पूर्णांक speed)
अणु
	काष्ठा sched *s = sge->tx_sched;
	काष्ठा sched_port *p = &s->p[port];
	अचिन्हित पूर्णांक max_avail_segs;

	pr_debug("%s mtu=%d speed=%d\n", __func__, mtu, speed);
	अगर (speed)
		p->speed = speed;
	अगर (mtu)
		p->mtu = mtu;

	अगर (speed || mtu) अणु
		अचिन्हित दीर्घ दीर्घ drain = 1024ULL * p->speed * (p->mtu - 40);
		करो_भाग(drain, (p->mtu + 50) * 1000);
		p->drain_bits_per_1024ns = (अचिन्हित पूर्णांक) drain;

		अगर (p->speed < 1000)
			p->drain_bits_per_1024ns =
				90 * p->drain_bits_per_1024ns / 100;
	पूर्ण

	अगर (board_info(sge->adapter)->board == CHBT_BOARD_CHT204) अणु
		p->drain_bits_per_1024ns -= 16;
		s->max_avail = max(4096U, p->mtu + 16 + 14 + 4);
		max_avail_segs = max(1U, 4096 / (p->mtu - 40));
	पूर्ण अन्यथा अणु
		s->max_avail = 16384;
		max_avail_segs = max(1U, 9000 / (p->mtu - 40));
	पूर्ण

	pr_debug("t1_sched_update_parms: mtu %u speed %u max_avail %u "
		 "max_avail_segs %u drain_bits_per_1024ns %u\n", p->mtu,
		 p->speed, s->max_avail, max_avail_segs,
		 p->drain_bits_per_1024ns);

	वापस max_avail_segs * (p->mtu - 40);
पूर्ण

#अगर 0

/*
 * t1_sched_max_avail_bytes() tells the scheduler the maximum amount of
 * data that can be pushed per port.
 */
व्योम t1_sched_set_max_avail_bytes(काष्ठा sge *sge, अचिन्हित पूर्णांक val)
अणु
	काष्ठा sched *s = sge->tx_sched;
	अचिन्हित पूर्णांक i;

	s->max_avail = val;
	क्रम (i = 0; i < MAX_NPORTS; i++)
		t1_sched_update_parms(sge, i, 0, 0);
पूर्ण

/*
 * t1_sched_set_drain_bits_per_us() tells the scheduler at which rate a port
 * is draining.
 */
व्योम t1_sched_set_drain_bits_per_us(काष्ठा sge *sge, अचिन्हित पूर्णांक port,
					 अचिन्हित पूर्णांक val)
अणु
	काष्ठा sched *s = sge->tx_sched;
	काष्ठा sched_port *p = &s->p[port];
	p->drain_bits_per_1024ns = val * 1024 / 1000;
	t1_sched_update_parms(sge, port, 0, 0);
पूर्ण

#पूर्ण_अगर  /*  0  */

/*
 * tx_sched_init() allocates resources and करोes basic initialization.
 */
अटल पूर्णांक tx_sched_init(काष्ठा sge *sge)
अणु
	काष्ठा sched *s;
	पूर्णांक i;

	s = kzalloc(माप (काष्ठा sched), GFP_KERNEL);
	अगर (!s)
		वापस -ENOMEM;

	pr_debug("tx_sched_init\n");
	tasklet_setup(&s->sched_tsk, restart_sched);
	s->sge = sge;
	sge->tx_sched = s;

	क्रम (i = 0; i < MAX_NPORTS; i++) अणु
		skb_queue_head_init(&s->p[i].skbq);
		t1_sched_update_parms(sge, i, 1500, 1000);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * sched_update_avail() computes the delta since the last समय it was called
 * and updates the per port quota (number of bits that can be sent to the any
 * port).
 */
अटल अंतरभूत पूर्णांक sched_update_avail(काष्ठा sge *sge)
अणु
	काष्ठा sched *s = sge->tx_sched;
	kसमय_प्रकार now = kसमय_get();
	अचिन्हित पूर्णांक i;
	दीर्घ दीर्घ delta_समय_ns;

	delta_समय_ns = kसमय_प्रकारo_ns(kसमय_sub(now, s->last_updated));

	pr_debug("sched_update_avail delta=%lld\n", delta_समय_ns);
	अगर (delta_समय_ns < 15000)
		वापस 0;

	क्रम (i = 0; i < MAX_NPORTS; i++) अणु
		काष्ठा sched_port *p = &s->p[i];
		अचिन्हित पूर्णांक delta_avail;

		delta_avail = (p->drain_bits_per_1024ns * delta_समय_ns) >> 13;
		p->avail = min(p->avail + delta_avail, s->max_avail);
	पूर्ण

	s->last_updated = now;

	वापस 1;
पूर्ण

/*
 * sched_skb() is called from two dअगरferent places. In the tx path, any
 * packet generating load on an output port will call sched_skb()
 * (skb != शून्य). In addition, sched_skb() is called from the irq/soft irq
 * context (skb == शून्य).
 * The scheduler only वापसs a skb (which will then be sent) अगर the
 * length of the skb is <= the current quota of the output port.
 */
अटल काष्ठा sk_buff *sched_skb(काष्ठा sge *sge, काष्ठा sk_buff *skb,
				अचिन्हित पूर्णांक credits)
अणु
	काष्ठा sched *s = sge->tx_sched;
	काष्ठा sk_buff_head *skbq;
	अचिन्हित पूर्णांक i, len, update = 1;

	pr_debug("sched_skb %p\n", skb);
	अगर (!skb) अणु
		अगर (!s->num)
			वापस शून्य;
	पूर्ण अन्यथा अणु
		skbq = &s->p[skb->dev->अगर_port].skbq;
		__skb_queue_tail(skbq, skb);
		s->num++;
		skb = शून्य;
	पूर्ण

	अगर (credits < MAX_SKB_FRAGS + 1)
		जाओ out;

again:
	क्रम (i = 0; i < MAX_NPORTS; i++) अणु
		s->port = (s->port + 1) & (MAX_NPORTS - 1);
		skbq = &s->p[s->port].skbq;

		skb = skb_peek(skbq);

		अगर (!skb)
			जारी;

		len = skb->len;
		अगर (len <= s->p[s->port].avail) अणु
			s->p[s->port].avail -= len;
			s->num--;
			__skb_unlink(skb, skbq);
			जाओ out;
		पूर्ण
		skb = शून्य;
	पूर्ण

	अगर (update-- && sched_update_avail(sge))
		जाओ again;

out:
	/* If there are more pending skbs, we use the hardware to schedule us
	 * again.
	 */
	अगर (s->num && !skb) अणु
		काष्ठा cmdQ *q = &sge->cmdQ[0];
		clear_bit(CMDQ_STAT_LAST_PKT_DB, &q->status);
		अगर (test_and_set_bit(CMDQ_STAT_RUNNING, &q->status) == 0) अणु
			set_bit(CMDQ_STAT_LAST_PKT_DB, &q->status);
			ग_लिखोl(F_CMDQ0_ENABLE, sge->adapter->regs + A_SG_DOORBELL);
		पूर्ण
	पूर्ण
	pr_debug("sched_skb ret %p\n", skb);

	वापस skb;
पूर्ण

/*
 * PIO to indicate that memory mapped Q contains valid descriptor(s).
 */
अटल अंतरभूत व्योम करोorbell_pio(काष्ठा adapter *adapter, u32 val)
अणु
	wmb();
	ग_लिखोl(val, adapter->regs + A_SG_DOORBELL);
पूर्ण

/*
 * Frees all RX buffers on the मुक्तlist Q. The caller must make sure that
 * the SGE is turned off beक्रमe calling this function.
 */
अटल व्योम मुक्त_मुक्तlQ_buffers(काष्ठा pci_dev *pdev, काष्ठा मुक्तlQ *q)
अणु
	अचिन्हित पूर्णांक cidx = q->cidx;

	जबतक (q->credits--) अणु
		काष्ठा मुक्तlQ_ce *ce = &q->centries[cidx];

		dma_unmap_single(&pdev->dev, dma_unmap_addr(ce, dma_addr),
				 dma_unmap_len(ce, dma_len), DMA_FROM_DEVICE);
		dev_kमुक्त_skb(ce->skb);
		ce->skb = शून्य;
		अगर (++cidx == q->size)
			cidx = 0;
	पूर्ण
पूर्ण

/*
 * Free RX मुक्त list and response queue resources.
 */
अटल व्योम मुक्त_rx_resources(काष्ठा sge *sge)
अणु
	काष्ठा pci_dev *pdev = sge->adapter->pdev;
	अचिन्हित पूर्णांक size, i;

	अगर (sge->respQ.entries) अणु
		size = माप(काष्ठा respQ_e) * sge->respQ.size;
		dma_मुक्त_coherent(&pdev->dev, size, sge->respQ.entries,
				  sge->respQ.dma_addr);
	पूर्ण

	क्रम (i = 0; i < SGE_FREELQ_N; i++) अणु
		काष्ठा मुक्तlQ *q = &sge->मुक्तlQ[i];

		अगर (q->centries) अणु
			मुक्त_मुक्तlQ_buffers(pdev, q);
			kमुक्त(q->centries);
		पूर्ण
		अगर (q->entries) अणु
			size = माप(काष्ठा मुक्तlQ_e) * q->size;
			dma_मुक्त_coherent(&pdev->dev, size, q->entries,
					  q->dma_addr);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Allocates basic RX resources, consisting of memory mapped मुक्तlist Qs and a
 * response queue.
 */
अटल पूर्णांक alloc_rx_resources(काष्ठा sge *sge, काष्ठा sge_params *p)
अणु
	काष्ठा pci_dev *pdev = sge->adapter->pdev;
	अचिन्हित पूर्णांक size, i;

	क्रम (i = 0; i < SGE_FREELQ_N; i++) अणु
		काष्ठा मुक्तlQ *q = &sge->मुक्तlQ[i];

		q->genbit = 1;
		q->size = p->मुक्तlQ_size[i];
		q->dma_offset = sge->rx_pkt_pad ? 0 : NET_IP_ALIGN;
		size = माप(काष्ठा मुक्तlQ_e) * q->size;
		q->entries = dma_alloc_coherent(&pdev->dev, size,
						&q->dma_addr, GFP_KERNEL);
		अगर (!q->entries)
			जाओ err_no_mem;

		size = माप(काष्ठा मुक्तlQ_ce) * q->size;
		q->centries = kzalloc(size, GFP_KERNEL);
		अगर (!q->centries)
			जाओ err_no_mem;
	पूर्ण

	/*
	 * Calculate the buffer sizes क्रम the two मुक्त lists.  FL0 accommodates
	 * regular sized Ethernet frames, FL1 is sized not to exceed 16K,
	 * including all the sk_buff overhead.
	 *
	 * Note: For T2 FL0 and FL1 are reversed.
	 */
	sge->मुक्तlQ[!sge->jumbo_fl].rx_buffer_size = SGE_RX_SM_BUF_SIZE +
		माप(काष्ठा cpl_rx_data) +
		sge->मुक्तlQ[!sge->jumbo_fl].dma_offset;

	size = (16 * 1024) - SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info));

	sge->मुक्तlQ[sge->jumbo_fl].rx_buffer_size = size;

	/*
	 * Setup which skb recycle Q should be used when recycling buffers from
	 * each मुक्त list.
	 */
	sge->मुक्तlQ[!sge->jumbo_fl].recycleq_idx = 0;
	sge->मुक्तlQ[sge->jumbo_fl].recycleq_idx = 1;

	sge->respQ.genbit = 1;
	sge->respQ.size = SGE_RESPQ_E_N;
	sge->respQ.credits = 0;
	size = माप(काष्ठा respQ_e) * sge->respQ.size;
	sge->respQ.entries =
		dma_alloc_coherent(&pdev->dev, size, &sge->respQ.dma_addr,
				   GFP_KERNEL);
	अगर (!sge->respQ.entries)
		जाओ err_no_mem;
	वापस 0;

err_no_mem:
	मुक्त_rx_resources(sge);
	वापस -ENOMEM;
पूर्ण

/*
 * Reclaims n TX descriptors and मुक्तs the buffers associated with them.
 */
अटल व्योम मुक्त_cmdQ_buffers(काष्ठा sge *sge, काष्ठा cmdQ *q, अचिन्हित पूर्णांक n)
अणु
	काष्ठा cmdQ_ce *ce;
	काष्ठा pci_dev *pdev = sge->adapter->pdev;
	अचिन्हित पूर्णांक cidx = q->cidx;

	q->in_use -= n;
	ce = &q->centries[cidx];
	जबतक (n--) अणु
		अगर (likely(dma_unmap_len(ce, dma_len))) अणु
			dma_unmap_single(&pdev->dev,
					 dma_unmap_addr(ce, dma_addr),
					 dma_unmap_len(ce, dma_len),
					 DMA_TO_DEVICE);
			अगर (q->sop)
				q->sop = 0;
		पूर्ण
		अगर (ce->skb) अणु
			dev_kमुक्त_skb_any(ce->skb);
			q->sop = 1;
		पूर्ण
		ce++;
		अगर (++cidx == q->size) अणु
			cidx = 0;
			ce = q->centries;
		पूर्ण
	पूर्ण
	q->cidx = cidx;
पूर्ण

/*
 * Free TX resources.
 *
 * Assumes that SGE is stopped and all पूर्णांकerrupts are disabled.
 */
अटल व्योम मुक्त_tx_resources(काष्ठा sge *sge)
अणु
	काष्ठा pci_dev *pdev = sge->adapter->pdev;
	अचिन्हित पूर्णांक size, i;

	क्रम (i = 0; i < SGE_CMDQ_N; i++) अणु
		काष्ठा cmdQ *q = &sge->cmdQ[i];

		अगर (q->centries) अणु
			अगर (q->in_use)
				मुक्त_cmdQ_buffers(sge, q, q->in_use);
			kमुक्त(q->centries);
		पूर्ण
		अगर (q->entries) अणु
			size = माप(काष्ठा cmdQ_e) * q->size;
			dma_मुक्त_coherent(&pdev->dev, size, q->entries,
					  q->dma_addr);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Allocates basic TX resources, consisting of memory mapped command Qs.
 */
अटल पूर्णांक alloc_tx_resources(काष्ठा sge *sge, काष्ठा sge_params *p)
अणु
	काष्ठा pci_dev *pdev = sge->adapter->pdev;
	अचिन्हित पूर्णांक size, i;

	क्रम (i = 0; i < SGE_CMDQ_N; i++) अणु
		काष्ठा cmdQ *q = &sge->cmdQ[i];

		q->genbit = 1;
		q->sop = 1;
		q->size = p->cmdQ_size[i];
		q->in_use = 0;
		q->status = 0;
		q->processed = q->cleaned = 0;
		q->stop_thres = 0;
		spin_lock_init(&q->lock);
		size = माप(काष्ठा cmdQ_e) * q->size;
		q->entries = dma_alloc_coherent(&pdev->dev, size,
						&q->dma_addr, GFP_KERNEL);
		अगर (!q->entries)
			जाओ err_no_mem;

		size = माप(काष्ठा cmdQ_ce) * q->size;
		q->centries = kzalloc(size, GFP_KERNEL);
		अगर (!q->centries)
			जाओ err_no_mem;
	पूर्ण

	/*
	 * CommandQ 0 handles Ethernet and TOE packets, जबतक queue 1 is TOE
	 * only.  For queue 0 set the stop threshold so we can handle one more
	 * packet from each port, plus reserve an additional 24 entries क्रम
	 * Ethernet packets only.  Queue 1 never suspends nor करो we reserve
	 * space क्रम Ethernet packets.
	 */
	sge->cmdQ[0].stop_thres = sge->adapter->params.nports *
		(MAX_SKB_FRAGS + 1);
	वापस 0;

err_no_mem:
	मुक्त_tx_resources(sge);
	वापस -ENOMEM;
पूर्ण

अटल अंतरभूत व्योम setup_ring_params(काष्ठा adapter *adapter, u64 addr,
				     u32 size, पूर्णांक base_reg_lo,
				     पूर्णांक base_reg_hi, पूर्णांक size_reg)
अणु
	ग_लिखोl((u32)addr, adapter->regs + base_reg_lo);
	ग_लिखोl(addr >> 32, adapter->regs + base_reg_hi);
	ग_लिखोl(size, adapter->regs + size_reg);
पूर्ण

/*
 * Enable/disable VLAN acceleration.
 */
व्योम t1_vlan_mode(काष्ठा adapter *adapter, netdev_features_t features)
अणु
	काष्ठा sge *sge = adapter->sge;

	अगर (features & NETIF_F_HW_VLAN_CTAG_RX)
		sge->sge_control |= F_VLAN_XTRACT;
	अन्यथा
		sge->sge_control &= ~F_VLAN_XTRACT;
	अगर (adapter->खोलो_device_map) अणु
		ग_लिखोl(sge->sge_control, adapter->regs + A_SG_CONTROL);
		पढ़ोl(adapter->regs + A_SG_CONTROL);   /* flush */
	पूर्ण
पूर्ण

/*
 * Programs the various SGE रेजिस्टरs. However, the engine is not yet enabled,
 * but sge->sge_control is setup and पढ़ोy to go.
 */
अटल व्योम configure_sge(काष्ठा sge *sge, काष्ठा sge_params *p)
अणु
	काष्ठा adapter *ap = sge->adapter;

	ग_लिखोl(0, ap->regs + A_SG_CONTROL);
	setup_ring_params(ap, sge->cmdQ[0].dma_addr, sge->cmdQ[0].size,
			  A_SG_CMD0BASELWR, A_SG_CMD0BASEUPR, A_SG_CMD0SIZE);
	setup_ring_params(ap, sge->cmdQ[1].dma_addr, sge->cmdQ[1].size,
			  A_SG_CMD1BASELWR, A_SG_CMD1BASEUPR, A_SG_CMD1SIZE);
	setup_ring_params(ap, sge->मुक्तlQ[0].dma_addr,
			  sge->मुक्तlQ[0].size, A_SG_FL0BASELWR,
			  A_SG_FL0BASEUPR, A_SG_FL0SIZE);
	setup_ring_params(ap, sge->मुक्तlQ[1].dma_addr,
			  sge->मुक्तlQ[1].size, A_SG_FL1BASELWR,
			  A_SG_FL1BASEUPR, A_SG_FL1SIZE);

	/* The threshold comparison uses <. */
	ग_लिखोl(SGE_RX_SM_BUF_SIZE + 1, ap->regs + A_SG_FLTHRESHOLD);

	setup_ring_params(ap, sge->respQ.dma_addr, sge->respQ.size,
			  A_SG_RSPBASELWR, A_SG_RSPBASEUPR, A_SG_RSPSIZE);
	ग_लिखोl((u32)sge->respQ.size - 1, ap->regs + A_SG_RSPQUEUECREDIT);

	sge->sge_control = F_CMDQ0_ENABLE | F_CMDQ1_ENABLE | F_FL0_ENABLE |
		F_FL1_ENABLE | F_CPL_ENABLE | F_RESPONSE_QUEUE_ENABLE |
		V_CMDQ_PRIORITY(2) | F_DISABLE_CMDQ1_GTS | F_ISCSI_COALESCE |
		V_RX_PKT_OFFSET(sge->rx_pkt_pad);

#अगर defined(__BIG_ENDIAN_BITFIELD)
	sge->sge_control |= F_ENABLE_BIG_ENDIAN;
#पूर्ण_अगर

	/* Initialize no-resource समयr */
	sge->पूर्णांकrसमयr_nres = SGE_INTRTIMER_NRES * core_ticks_per_usec(ap);

	t1_sge_set_coalesce_params(sge, p);
पूर्ण

/*
 * Return the payload capacity of the jumbo मुक्त-list buffers.
 */
अटल अंतरभूत अचिन्हित पूर्णांक jumbo_payload_capacity(स्थिर काष्ठा sge *sge)
अणु
	वापस sge->मुक्तlQ[sge->jumbo_fl].rx_buffer_size -
		sge->मुक्तlQ[sge->jumbo_fl].dma_offset -
		माप(काष्ठा cpl_rx_data);
पूर्ण

/*
 * Frees all SGE related resources and the sge काष्ठाure itself
 */
व्योम t1_sge_destroy(काष्ठा sge *sge)
अणु
	पूर्णांक i;

	क्रम_each_port(sge->adapter, i)
		मुक्त_percpu(sge->port_stats[i]);

	kमुक्त(sge->tx_sched);
	मुक्त_tx_resources(sge);
	मुक्त_rx_resources(sge);
	kमुक्त(sge);
पूर्ण

/*
 * Allocates new RX buffers on the मुक्तlist Q (and tracks them on the मुक्तlist
 * context Q) until the Q is full or alloc_skb fails.
 *
 * It is possible that the generation bits alपढ़ोy match, indicating that the
 * buffer is alपढ़ोy valid and nothing needs to be करोne. This happens when we
 * copied a received buffer पूर्णांकo a new sk_buff during the पूर्णांकerrupt processing.
 *
 * If the SGE करोesn't स्वतःmatically align packets properly (!sge->rx_pkt_pad),
 * we specअगरy a RX_OFFSET in order to make sure that the IP header is 4B
 * aligned.
 */
अटल व्योम refill_मुक्त_list(काष्ठा sge *sge, काष्ठा मुक्तlQ *q)
अणु
	काष्ठा pci_dev *pdev = sge->adapter->pdev;
	काष्ठा मुक्तlQ_ce *ce = &q->centries[q->pidx];
	काष्ठा मुक्तlQ_e *e = &q->entries[q->pidx];
	अचिन्हित पूर्णांक dma_len = q->rx_buffer_size - q->dma_offset;

	जबतक (q->credits < q->size) अणु
		काष्ठा sk_buff *skb;
		dma_addr_t mapping;

		skb = dev_alloc_skb(q->rx_buffer_size);
		अगर (!skb)
			अवरोध;

		skb_reserve(skb, q->dma_offset);
		mapping = dma_map_single(&pdev->dev, skb->data, dma_len,
					 DMA_FROM_DEVICE);
		skb_reserve(skb, sge->rx_pkt_pad);

		ce->skb = skb;
		dma_unmap_addr_set(ce, dma_addr, mapping);
		dma_unmap_len_set(ce, dma_len, dma_len);
		e->addr_lo = (u32)mapping;
		e->addr_hi = (u64)mapping >> 32;
		e->len_gen = V_CMD_LEN(dma_len) | V_CMD_GEN1(q->genbit);
		wmb();
		e->gen2 = V_CMD_GEN2(q->genbit);

		e++;
		ce++;
		अगर (++q->pidx == q->size) अणु
			q->pidx = 0;
			q->genbit ^= 1;
			ce = q->centries;
			e = q->entries;
		पूर्ण
		q->credits++;
	पूर्ण
पूर्ण

/*
 * Calls refill_मुक्त_list क्रम both मुक्त lists. If we cannot fill at least 1/4
 * of both rings, we go पूर्णांकo 'few interrupt mode' in order to give the प्रणाली
 * समय to मुक्त up resources.
 */
अटल व्योम मुक्तlQs_empty(काष्ठा sge *sge)
अणु
	काष्ठा adapter *adapter = sge->adapter;
	u32 irq_reg = पढ़ोl(adapter->regs + A_SG_INT_ENABLE);
	u32 irqholकरोff_reg;

	refill_मुक्त_list(sge, &sge->मुक्तlQ[0]);
	refill_मुक्त_list(sge, &sge->मुक्तlQ[1]);

	अगर (sge->मुक्तlQ[0].credits > (sge->मुक्तlQ[0].size >> 2) &&
	    sge->मुक्तlQ[1].credits > (sge->मुक्तlQ[1].size >> 2)) अणु
		irq_reg |= F_FL_EXHAUSTED;
		irqholकरोff_reg = sge->fixed_पूर्णांकrसमयr;
	पूर्ण अन्यथा अणु
		/* Clear the F_FL_EXHAUSTED पूर्णांकerrupts क्रम now */
		irq_reg &= ~F_FL_EXHAUSTED;
		irqholकरोff_reg = sge->पूर्णांकrसमयr_nres;
	पूर्ण
	ग_लिखोl(irqholकरोff_reg, adapter->regs + A_SG_INTRTIMER);
	ग_लिखोl(irq_reg, adapter->regs + A_SG_INT_ENABLE);

	/* We reenable the Qs to क्रमce a मुक्तlist GTS पूर्णांकerrupt later */
	करोorbell_pio(adapter, F_FL0_ENABLE | F_FL1_ENABLE);
पूर्ण

#घोषणा SGE_PL_INTR_MASK (F_PL_INTR_SGE_ERR | F_PL_INTR_SGE_DATA)
#घोषणा SGE_INT_FATAL (F_RESPQ_OVERFLOW | F_PACKET_TOO_BIG | F_PACKET_MISMATCH)
#घोषणा SGE_INT_ENABLE (F_RESPQ_EXHAUSTED | F_RESPQ_OVERFLOW | \
			F_FL_EXHAUSTED | F_PACKET_TOO_BIG | F_PACKET_MISMATCH)

/*
 * Disable SGE Interrupts
 */
व्योम t1_sge_पूर्णांकr_disable(काष्ठा sge *sge)
अणु
	u32 val = पढ़ोl(sge->adapter->regs + A_PL_ENABLE);

	ग_लिखोl(val & ~SGE_PL_INTR_MASK, sge->adapter->regs + A_PL_ENABLE);
	ग_लिखोl(0, sge->adapter->regs + A_SG_INT_ENABLE);
पूर्ण

/*
 * Enable SGE पूर्णांकerrupts.
 */
व्योम t1_sge_पूर्णांकr_enable(काष्ठा sge *sge)
अणु
	u32 en = SGE_INT_ENABLE;
	u32 val = पढ़ोl(sge->adapter->regs + A_PL_ENABLE);

	अगर (sge->adapter->port[0].dev->hw_features & NETIF_F_TSO)
		en &= ~F_PACKET_TOO_BIG;
	ग_लिखोl(en, sge->adapter->regs + A_SG_INT_ENABLE);
	ग_लिखोl(val | SGE_PL_INTR_MASK, sge->adapter->regs + A_PL_ENABLE);
पूर्ण

/*
 * Clear SGE पूर्णांकerrupts.
 */
व्योम t1_sge_पूर्णांकr_clear(काष्ठा sge *sge)
अणु
	ग_लिखोl(SGE_PL_INTR_MASK, sge->adapter->regs + A_PL_CAUSE);
	ग_लिखोl(0xffffffff, sge->adapter->regs + A_SG_INT_CAUSE);
पूर्ण

/*
 * SGE 'Error' पूर्णांकerrupt handler
 */
bool t1_sge_पूर्णांकr_error_handler(काष्ठा sge *sge)
अणु
	काष्ठा adapter *adapter = sge->adapter;
	u32 cause = पढ़ोl(adapter->regs + A_SG_INT_CAUSE);
	bool wake = false;

	अगर (adapter->port[0].dev->hw_features & NETIF_F_TSO)
		cause &= ~F_PACKET_TOO_BIG;
	अगर (cause & F_RESPQ_EXHAUSTED)
		sge->stats.respQ_empty++;
	अगर (cause & F_RESPQ_OVERFLOW) अणु
		sge->stats.respQ_overflow++;
		pr_alert("%s: SGE response queue overflow\n",
			 adapter->name);
	पूर्ण
	अगर (cause & F_FL_EXHAUSTED) अणु
		sge->stats.मुक्तlistQ_empty++;
		मुक्तlQs_empty(sge);
	पूर्ण
	अगर (cause & F_PACKET_TOO_BIG) अणु
		sge->stats.pkt_too_big++;
		pr_alert("%s: SGE max packet size exceeded\n",
			 adapter->name);
	पूर्ण
	अगर (cause & F_PACKET_MISMATCH) अणु
		sge->stats.pkt_mismatch++;
		pr_alert("%s: SGE packet mismatch\n", adapter->name);
	पूर्ण
	अगर (cause & SGE_INT_FATAL) अणु
		t1_पूर्णांकerrupts_disable(adapter);
		adapter->pending_thपढ़ो_पूर्णांकr |= F_PL_INTR_SGE_ERR;
		wake = true;
	पूर्ण

	ग_लिखोl(cause, adapter->regs + A_SG_INT_CAUSE);
	वापस wake;
पूर्ण

स्थिर काष्ठा sge_पूर्णांकr_counts *t1_sge_get_पूर्णांकr_counts(स्थिर काष्ठा sge *sge)
अणु
	वापस &sge->stats;
पूर्ण

व्योम t1_sge_get_port_stats(स्थिर काष्ठा sge *sge, पूर्णांक port,
			   काष्ठा sge_port_stats *ss)
अणु
	पूर्णांक cpu;

	स_रखो(ss, 0, माप(*ss));
	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा sge_port_stats *st = per_cpu_ptr(sge->port_stats[port], cpu);

		ss->rx_cso_good += st->rx_cso_good;
		ss->tx_cso += st->tx_cso;
		ss->tx_tso += st->tx_tso;
		ss->tx_need_hdrroom += st->tx_need_hdrroom;
		ss->vlan_xtract += st->vlan_xtract;
		ss->vlan_insert += st->vlan_insert;
	पूर्ण
पूर्ण

/**
 *	recycle_fl_buf - recycle a मुक्त list buffer
 *	@fl: the मुक्त list
 *	@idx: index of buffer to recycle
 *
 *	Recycles the specअगरied buffer on the given मुक्त list by adding it at
 *	the next available slot on the list.
 */
अटल व्योम recycle_fl_buf(काष्ठा मुक्तlQ *fl, पूर्णांक idx)
अणु
	काष्ठा मुक्तlQ_e *from = &fl->entries[idx];
	काष्ठा मुक्तlQ_e *to = &fl->entries[fl->pidx];

	fl->centries[fl->pidx] = fl->centries[idx];
	to->addr_lo = from->addr_lo;
	to->addr_hi = from->addr_hi;
	to->len_gen = G_CMD_LEN(from->len_gen) | V_CMD_GEN1(fl->genbit);
	wmb();
	to->gen2 = V_CMD_GEN2(fl->genbit);
	fl->credits++;

	अगर (++fl->pidx == fl->size) अणु
		fl->pidx = 0;
		fl->genbit ^= 1;
	पूर्ण
पूर्ण

अटल पूर्णांक copyअवरोध __पढ़ो_mostly = 256;
module_param(copyअवरोध, पूर्णांक, 0);
MODULE_PARM_DESC(copyअवरोध, "Receive copy threshold");

/**
 *	get_packet - वापस the next ingress packet buffer
 *	@adapter: the adapter that received the packet
 *	@fl: the SGE मुक्त list holding the packet
 *	@len: the actual packet length, excluding any SGE padding
 *
 *	Get the next packet from a मुक्त list and complete setup of the
 *	sk_buff.  If the packet is small we make a copy and recycle the
 *	original buffer, otherwise we use the original buffer itself.  If a
 *	positive drop threshold is supplied packets are dropped and their
 *	buffers recycled अगर (a) the number of reमुख्यing buffers is under the
 *	threshold and the packet is too big to copy, or (b) the packet should
 *	be copied but there is no memory क्रम the copy.
 */
अटल अंतरभूत काष्ठा sk_buff *get_packet(काष्ठा adapter *adapter,
					 काष्ठा मुक्तlQ *fl, अचिन्हित पूर्णांक len)
अणु
	स्थिर काष्ठा मुक्तlQ_ce *ce = &fl->centries[fl->cidx];
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा sk_buff *skb;

	अगर (len < copyअवरोध) अणु
		skb = napi_alloc_skb(&adapter->napi, len);
		अगर (!skb)
			जाओ use_orig_buf;

		skb_put(skb, len);
		dma_sync_single_क्रम_cpu(&pdev->dev,
					dma_unmap_addr(ce, dma_addr),
					dma_unmap_len(ce, dma_len),
					DMA_FROM_DEVICE);
		skb_copy_from_linear_data(ce->skb, skb->data, len);
		dma_sync_single_क्रम_device(&pdev->dev,
					   dma_unmap_addr(ce, dma_addr),
					   dma_unmap_len(ce, dma_len),
					   DMA_FROM_DEVICE);
		recycle_fl_buf(fl, fl->cidx);
		वापस skb;
	पूर्ण

use_orig_buf:
	अगर (fl->credits < 2) अणु
		recycle_fl_buf(fl, fl->cidx);
		वापस शून्य;
	पूर्ण

	dma_unmap_single(&pdev->dev, dma_unmap_addr(ce, dma_addr),
			 dma_unmap_len(ce, dma_len), DMA_FROM_DEVICE);
	skb = ce->skb;
	prefetch(skb->data);

	skb_put(skb, len);
	वापस skb;
पूर्ण

/**
 *	unexpected_offload - handle an unexpected offload packet
 *	@adapter: the adapter
 *	@fl: the मुक्त list that received the packet
 *
 *	Called when we receive an unexpected offload packet (e.g., the TOE
 *	function is disabled or the card is a NIC).  Prपूर्णांकs a message and
 *	recycles the buffer.
 */
अटल व्योम unexpected_offload(काष्ठा adapter *adapter, काष्ठा मुक्तlQ *fl)
अणु
	काष्ठा मुक्तlQ_ce *ce = &fl->centries[fl->cidx];
	काष्ठा sk_buff *skb = ce->skb;

	dma_sync_single_क्रम_cpu(&adapter->pdev->dev,
				dma_unmap_addr(ce, dma_addr),
				dma_unmap_len(ce, dma_len), DMA_FROM_DEVICE);
	pr_err("%s: unexpected offload packet, cmd %u\n",
	       adapter->name, *skb->data);
	recycle_fl_buf(fl, fl->cidx);
पूर्ण

/*
 * T1/T2 SGE limits the maximum DMA size per TX descriptor to
 * SGE_TX_DESC_MAX_PLEN (16KB). If the PAGE_SIZE is larger than 16KB, the
 * stack might send more than SGE_TX_DESC_MAX_PLEN in a contiguous manner.
 * Note that the *_large_page_tx_descs stuff will be optimized out when
 * PAGE_SIZE <= SGE_TX_DESC_MAX_PLEN.
 *
 * compute_large_page_descs() computes how many additional descriptors are
 * required to अवरोध करोwn the stack's request.
 */
अटल अंतरभूत अचिन्हित पूर्णांक compute_large_page_tx_descs(काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक count = 0;

	अगर (PAGE_SIZE > SGE_TX_DESC_MAX_PLEN) अणु
		अचिन्हित पूर्णांक nfrags = skb_shinfo(skb)->nr_frags;
		अचिन्हित पूर्णांक i, len = skb_headlen(skb);
		जबतक (len > SGE_TX_DESC_MAX_PLEN) अणु
			count++;
			len -= SGE_TX_DESC_MAX_PLEN;
		पूर्ण
		क्रम (i = 0; nfrags--; i++) अणु
			स्थिर skb_frag_t *frag = &skb_shinfo(skb)->frags[i];
			len = skb_frag_size(frag);
			जबतक (len > SGE_TX_DESC_MAX_PLEN) अणु
				count++;
				len -= SGE_TX_DESC_MAX_PLEN;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस count;
पूर्ण

/*
 * Write a cmdQ entry.
 *
 * Since this function ग_लिखोs the 'flags' field, it must not be used to
 * ग_लिखो the first cmdQ entry.
 */
अटल अंतरभूत व्योम ग_लिखो_tx_desc(काष्ठा cmdQ_e *e, dma_addr_t mapping,
				 अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक gen,
				 अचिन्हित पूर्णांक eop)
अणु
	BUG_ON(len > SGE_TX_DESC_MAX_PLEN);

	e->addr_lo = (u32)mapping;
	e->addr_hi = (u64)mapping >> 32;
	e->len_gen = V_CMD_LEN(len) | V_CMD_GEN1(gen);
	e->flags = F_CMD_DATAVALID | V_CMD_EOP(eop) | V_CMD_GEN2(gen);
पूर्ण

/*
 * See comment क्रम previous function.
 *
 * ग_लिखो_tx_descs_large_page() ग_लिखोs additional SGE tx descriptors अगर
 * *desc_len exceeds HW's capability.
 */
अटल अंतरभूत अचिन्हित पूर्णांक ग_लिखो_large_page_tx_descs(अचिन्हित पूर्णांक pidx,
						     काष्ठा cmdQ_e **e,
						     काष्ठा cmdQ_ce **ce,
						     अचिन्हित पूर्णांक *gen,
						     dma_addr_t *desc_mapping,
						     अचिन्हित पूर्णांक *desc_len,
						     अचिन्हित पूर्णांक nfrags,
						     काष्ठा cmdQ *q)
अणु
	अगर (PAGE_SIZE > SGE_TX_DESC_MAX_PLEN) अणु
		काष्ठा cmdQ_e *e1 = *e;
		काष्ठा cmdQ_ce *ce1 = *ce;

		जबतक (*desc_len > SGE_TX_DESC_MAX_PLEN) अणु
			*desc_len -= SGE_TX_DESC_MAX_PLEN;
			ग_लिखो_tx_desc(e1, *desc_mapping, SGE_TX_DESC_MAX_PLEN,
				      *gen, nfrags == 0 && *desc_len == 0);
			ce1->skb = शून्य;
			dma_unmap_len_set(ce1, dma_len, 0);
			*desc_mapping += SGE_TX_DESC_MAX_PLEN;
			अगर (*desc_len) अणु
				ce1++;
				e1++;
				अगर (++pidx == q->size) अणु
					pidx = 0;
					*gen ^= 1;
					ce1 = q->centries;
					e1 = q->entries;
				पूर्ण
			पूर्ण
		पूर्ण
		*e = e1;
		*ce = ce1;
	पूर्ण
	वापस pidx;
पूर्ण

/*
 * Write the command descriptors to transmit the given skb starting at
 * descriptor pidx with the given generation.
 */
अटल अंतरभूत व्योम ग_लिखो_tx_descs(काष्ठा adapter *adapter, काष्ठा sk_buff *skb,
				  अचिन्हित पूर्णांक pidx, अचिन्हित पूर्णांक gen,
				  काष्ठा cmdQ *q)
अणु
	dma_addr_t mapping, desc_mapping;
	काष्ठा cmdQ_e *e, *e1;
	काष्ठा cmdQ_ce *ce;
	अचिन्हित पूर्णांक i, flags, first_desc_len, desc_len,
	    nfrags = skb_shinfo(skb)->nr_frags;

	e = e1 = &q->entries[pidx];
	ce = &q->centries[pidx];

	mapping = dma_map_single(&adapter->pdev->dev, skb->data,
				 skb_headlen(skb), DMA_TO_DEVICE);

	desc_mapping = mapping;
	desc_len = skb_headlen(skb);

	flags = F_CMD_DATAVALID | F_CMD_SOP |
	    V_CMD_EOP(nfrags == 0 && desc_len <= SGE_TX_DESC_MAX_PLEN) |
	    V_CMD_GEN2(gen);
	first_desc_len = (desc_len <= SGE_TX_DESC_MAX_PLEN) ?
	    desc_len : SGE_TX_DESC_MAX_PLEN;
	e->addr_lo = (u32)desc_mapping;
	e->addr_hi = (u64)desc_mapping >> 32;
	e->len_gen = V_CMD_LEN(first_desc_len) | V_CMD_GEN1(gen);
	ce->skb = शून्य;
	dma_unmap_len_set(ce, dma_len, 0);

	अगर (PAGE_SIZE > SGE_TX_DESC_MAX_PLEN &&
	    desc_len > SGE_TX_DESC_MAX_PLEN) अणु
		desc_mapping += first_desc_len;
		desc_len -= first_desc_len;
		e1++;
		ce++;
		अगर (++pidx == q->size) अणु
			pidx = 0;
			gen ^= 1;
			e1 = q->entries;
			ce = q->centries;
		पूर्ण
		pidx = ग_लिखो_large_page_tx_descs(pidx, &e1, &ce, &gen,
						 &desc_mapping, &desc_len,
						 nfrags, q);

		अगर (likely(desc_len))
			ग_लिखो_tx_desc(e1, desc_mapping, desc_len, gen,
				      nfrags == 0);
	पूर्ण

	ce->skb = शून्य;
	dma_unmap_addr_set(ce, dma_addr, mapping);
	dma_unmap_len_set(ce, dma_len, skb_headlen(skb));

	क्रम (i = 0; nfrags--; i++) अणु
		skb_frag_t *frag = &skb_shinfo(skb)->frags[i];
		e1++;
		ce++;
		अगर (++pidx == q->size) अणु
			pidx = 0;
			gen ^= 1;
			e1 = q->entries;
			ce = q->centries;
		पूर्ण

		mapping = skb_frag_dma_map(&adapter->pdev->dev, frag, 0,
					   skb_frag_size(frag), DMA_TO_DEVICE);
		desc_mapping = mapping;
		desc_len = skb_frag_size(frag);

		pidx = ग_लिखो_large_page_tx_descs(pidx, &e1, &ce, &gen,
						 &desc_mapping, &desc_len,
						 nfrags, q);
		अगर (likely(desc_len))
			ग_लिखो_tx_desc(e1, desc_mapping, desc_len, gen,
				      nfrags == 0);
		ce->skb = शून्य;
		dma_unmap_addr_set(ce, dma_addr, mapping);
		dma_unmap_len_set(ce, dma_len, skb_frag_size(frag));
	पूर्ण
	ce->skb = skb;
	wmb();
	e->flags = flags;
पूर्ण

/*
 * Clean up completed Tx buffers.
 */
अटल अंतरभूत व्योम reclaim_completed_tx(काष्ठा sge *sge, काष्ठा cmdQ *q)
अणु
	अचिन्हित पूर्णांक reclaim = q->processed - q->cleaned;

	अगर (reclaim) अणु
		pr_debug("reclaim_completed_tx processed:%d cleaned:%d\n",
			 q->processed, q->cleaned);
		मुक्त_cmdQ_buffers(sge, q, reclaim);
		q->cleaned += reclaim;
	पूर्ण
पूर्ण

/*
 * Called from tasklet. Checks the scheduler क्रम any
 * pending skbs that can be sent.
 */
अटल व्योम restart_sched(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा sched *s = from_tasklet(s, t, sched_tsk);
	काष्ठा sge *sge = s->sge;
	काष्ठा adapter *adapter = sge->adapter;
	काष्ठा cmdQ *q = &sge->cmdQ[0];
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक credits, queued_skb = 0;

	spin_lock(&q->lock);
	reclaim_completed_tx(sge, q);

	credits = q->size - q->in_use;
	pr_debug("restart_sched credits=%d\n", credits);
	जबतक ((skb = sched_skb(sge, शून्य, credits)) != शून्य) अणु
		अचिन्हित पूर्णांक genbit, pidx, count;
	        count = 1 + skb_shinfo(skb)->nr_frags;
		count += compute_large_page_tx_descs(skb);
		q->in_use += count;
		genbit = q->genbit;
		pidx = q->pidx;
		q->pidx += count;
		अगर (q->pidx >= q->size) अणु
			q->pidx -= q->size;
			q->genbit ^= 1;
		पूर्ण
		ग_लिखो_tx_descs(adapter, skb, pidx, genbit, q);
	        credits = q->size - q->in_use;
		queued_skb = 1;
	पूर्ण

	अगर (queued_skb) अणु
		clear_bit(CMDQ_STAT_LAST_PKT_DB, &q->status);
		अगर (test_and_set_bit(CMDQ_STAT_RUNNING, &q->status) == 0) अणु
			set_bit(CMDQ_STAT_LAST_PKT_DB, &q->status);
			ग_लिखोl(F_CMDQ0_ENABLE, adapter->regs + A_SG_DOORBELL);
		पूर्ण
	पूर्ण
	spin_unlock(&q->lock);
पूर्ण

/**
 *	sge_rx - process an ingress ethernet packet
 *	@sge: the sge काष्ठाure
 *	@fl: the मुक्त list that contains the packet buffer
 *	@len: the packet length
 *
 *	Process an ingress ethernet pakcet and deliver it to the stack.
 */
अटल व्योम sge_rx(काष्ठा sge *sge, काष्ठा मुक्तlQ *fl, अचिन्हित पूर्णांक len)
अणु
	काष्ठा sk_buff *skb;
	स्थिर काष्ठा cpl_rx_pkt *p;
	काष्ठा adapter *adapter = sge->adapter;
	काष्ठा sge_port_stats *st;
	काष्ठा net_device *dev;

	skb = get_packet(adapter, fl, len - sge->rx_pkt_pad);
	अगर (unlikely(!skb)) अणु
		sge->stats.rx_drops++;
		वापस;
	पूर्ण

	p = (स्थिर काष्ठा cpl_rx_pkt *) skb->data;
	अगर (p->अगरf >= adapter->params.nports) अणु
		kमुक्त_skb(skb);
		वापस;
	पूर्ण
	__skb_pull(skb, माप(*p));

	st = this_cpu_ptr(sge->port_stats[p->अगरf]);
	dev = adapter->port[p->अगरf].dev;

	skb->protocol = eth_type_trans(skb, dev);
	अगर ((dev->features & NETIF_F_RXCSUM) && p->csum == 0xffff &&
	    skb->protocol == htons(ETH_P_IP) &&
	    (skb->data[9] == IPPROTO_TCP || skb->data[9] == IPPROTO_UDP)) अणु
		++st->rx_cso_good;
		skb->ip_summed = CHECKSUM_UNNECESSARY;
	पूर्ण अन्यथा
		skb_checksum_none_निश्चित(skb);

	अगर (p->vlan_valid) अणु
		st->vlan_xtract++;
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), ntohs(p->vlan));
	पूर्ण
	netअगर_receive_skb(skb);
पूर्ण

/*
 * Returns true अगर a command queue has enough available descriptors that
 * we can resume Tx operation after temporarily disabling its packet queue.
 */
अटल अंतरभूत पूर्णांक enough_मुक्त_Tx_descs(स्थिर काष्ठा cmdQ *q)
अणु
	अचिन्हित पूर्णांक r = q->processed - q->cleaned;

	वापस q->in_use - r < (q->size >> 1);
पूर्ण

/*
 * Called when sufficient space has become available in the SGE command queues
 * after the Tx packet schedulers have been suspended to restart the Tx path.
 */
अटल व्योम restart_tx_queues(काष्ठा sge *sge)
अणु
	काष्ठा adapter *adap = sge->adapter;
	पूर्णांक i;

	अगर (!enough_मुक्त_Tx_descs(&sge->cmdQ[0]))
		वापस;

	क्रम_each_port(adap, i) अणु
		काष्ठा net_device *nd = adap->port[i].dev;

		अगर (test_and_clear_bit(nd->अगर_port, &sge->stopped_tx_queues) &&
		    netअगर_running(nd)) अणु
			sge->stats.cmdQ_restarted[2]++;
			netअगर_wake_queue(nd);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * update_tx_info is called from the पूर्णांकerrupt handler/NAPI to वापस cmdQ0
 * inक्रमmation.
 */
अटल अचिन्हित पूर्णांक update_tx_info(काष्ठा adapter *adapter,
					  अचिन्हित पूर्णांक flags,
					  अचिन्हित पूर्णांक pr0)
अणु
	काष्ठा sge *sge = adapter->sge;
	काष्ठा cmdQ *cmdq = &sge->cmdQ[0];

	cmdq->processed += pr0;
	अगर (flags & (F_FL0_ENABLE | F_FL1_ENABLE)) अणु
		मुक्तlQs_empty(sge);
		flags &= ~(F_FL0_ENABLE | F_FL1_ENABLE);
	पूर्ण
	अगर (flags & F_CMDQ0_ENABLE) अणु
		clear_bit(CMDQ_STAT_RUNNING, &cmdq->status);

		अगर (cmdq->cleaned + cmdq->in_use != cmdq->processed &&
		    !test_and_set_bit(CMDQ_STAT_LAST_PKT_DB, &cmdq->status)) अणु
			set_bit(CMDQ_STAT_RUNNING, &cmdq->status);
			ग_लिखोl(F_CMDQ0_ENABLE, adapter->regs + A_SG_DOORBELL);
		पूर्ण
		अगर (sge->tx_sched)
			tasklet_hi_schedule(&sge->tx_sched->sched_tsk);

		flags &= ~F_CMDQ0_ENABLE;
	पूर्ण

	अगर (unlikely(sge->stopped_tx_queues != 0))
		restart_tx_queues(sge);

	वापस flags;
पूर्ण

/*
 * Process SGE responses, up to the supplied budget.  Returns the number of
 * responses processed.  A negative budget is effectively unlimited.
 */
अटल पूर्णांक process_responses(काष्ठा adapter *adapter, पूर्णांक budget)
अणु
	काष्ठा sge *sge = adapter->sge;
	काष्ठा respQ *q = &sge->respQ;
	काष्ठा respQ_e *e = &q->entries[q->cidx];
	पूर्णांक करोne = 0;
	अचिन्हित पूर्णांक flags = 0;
	अचिन्हित पूर्णांक cmdq_processed[SGE_CMDQ_N] = अणु0, 0पूर्ण;

	जबतक (करोne < budget && e->GenerationBit == q->genbit) अणु
		flags |= e->Qsleeping;

		cmdq_processed[0] += e->Cmdq0CreditReturn;
		cmdq_processed[1] += e->Cmdq1CreditReturn;

		/* We batch updates to the TX side to aव्योम cacheline
		 * ping-pong of TX state inक्रमmation on MP where the sender
		 * might run on a dअगरferent CPU than this function...
		 */
		अगर (unlikely((flags & F_CMDQ0_ENABLE) || cmdq_processed[0] > 64)) अणु
			flags = update_tx_info(adapter, flags, cmdq_processed[0]);
			cmdq_processed[0] = 0;
		पूर्ण

		अगर (unlikely(cmdq_processed[1] > 16)) अणु
			sge->cmdQ[1].processed += cmdq_processed[1];
			cmdq_processed[1] = 0;
		पूर्ण

		अगर (likely(e->DataValid)) अणु
			काष्ठा मुक्तlQ *fl = &sge->मुक्तlQ[e->FreelistQid];

			BUG_ON(!e->Sop || !e->Eop);
			अगर (unlikely(e->Offload))
				unexpected_offload(adapter, fl);
			अन्यथा
				sge_rx(sge, fl, e->BufferLength);

			++करोne;

			/*
			 * Note: this depends on each packet consuming a
			 * single मुक्त-list buffer; cf. the BUG above.
			 */
			अगर (++fl->cidx == fl->size)
				fl->cidx = 0;
			prefetch(fl->centries[fl->cidx].skb);

			अगर (unlikely(--fl->credits <
				     fl->size - SGE_FREEL_REFILL_THRESH))
				refill_मुक्त_list(sge, fl);
		पूर्ण अन्यथा
			sge->stats.pure_rsps++;

		e++;
		अगर (unlikely(++q->cidx == q->size)) अणु
			q->cidx = 0;
			q->genbit ^= 1;
			e = q->entries;
		पूर्ण
		prefetch(e);

		अगर (++q->credits > SGE_RESPQ_REPLENISH_THRES) अणु
			ग_लिखोl(q->credits, adapter->regs + A_SG_RSPQUEUECREDIT);
			q->credits = 0;
		पूर्ण
	पूर्ण

	flags = update_tx_info(adapter, flags, cmdq_processed[0]);
	sge->cmdQ[1].processed += cmdq_processed[1];

	वापस करोne;
पूर्ण

अटल अंतरभूत पूर्णांक responses_pending(स्थिर काष्ठा adapter *adapter)
अणु
	स्थिर काष्ठा respQ *Q = &adapter->sge->respQ;
	स्थिर काष्ठा respQ_e *e = &Q->entries[Q->cidx];

	वापस e->GenerationBit == Q->genbit;
पूर्ण

/*
 * A simpler version of process_responses() that handles only pure (i.e.,
 * non data-carrying) responses.  Such respones are too light-weight to justअगरy
 * calling a softirq when using NAPI, so we handle them specially in hard
 * पूर्णांकerrupt context.  The function is called with a poपूर्णांकer to a response,
 * which the caller must ensure is a valid pure response.  Returns 1 अगर it
 * encounters a valid data-carrying response, 0 otherwise.
 */
अटल पूर्णांक process_pure_responses(काष्ठा adapter *adapter)
अणु
	काष्ठा sge *sge = adapter->sge;
	काष्ठा respQ *q = &sge->respQ;
	काष्ठा respQ_e *e = &q->entries[q->cidx];
	स्थिर काष्ठा मुक्तlQ *fl = &sge->मुक्तlQ[e->FreelistQid];
	अचिन्हित पूर्णांक flags = 0;
	अचिन्हित पूर्णांक cmdq_processed[SGE_CMDQ_N] = अणु0, 0पूर्ण;

	prefetch(fl->centries[fl->cidx].skb);
	अगर (e->DataValid)
		वापस 1;

	करो अणु
		flags |= e->Qsleeping;

		cmdq_processed[0] += e->Cmdq0CreditReturn;
		cmdq_processed[1] += e->Cmdq1CreditReturn;

		e++;
		अगर (unlikely(++q->cidx == q->size)) अणु
			q->cidx = 0;
			q->genbit ^= 1;
			e = q->entries;
		पूर्ण
		prefetch(e);

		अगर (++q->credits > SGE_RESPQ_REPLENISH_THRES) अणु
			ग_लिखोl(q->credits, adapter->regs + A_SG_RSPQUEUECREDIT);
			q->credits = 0;
		पूर्ण
		sge->stats.pure_rsps++;
	पूर्ण जबतक (e->GenerationBit == q->genbit && !e->DataValid);

	flags = update_tx_info(adapter, flags, cmdq_processed[0]);
	sge->cmdQ[1].processed += cmdq_processed[1];

	वापस e->GenerationBit == q->genbit;
पूर्ण

/*
 * Handler क्रम new data events when using NAPI.  This करोes not need any locking
 * or protection from पूर्णांकerrupts as data पूर्णांकerrupts are off at this poपूर्णांक and
 * other adapter पूर्णांकerrupts करो not पूर्णांकerfere.
 */
पूर्णांक t1_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा adapter *adapter = container_of(napi, काष्ठा adapter, napi);
	पूर्णांक work_करोne = process_responses(adapter, budget);

	अगर (likely(work_करोne < budget)) अणु
		napi_complete_करोne(napi, work_करोne);
		ग_लिखोl(adapter->sge->respQ.cidx,
		       adapter->regs + A_SG_SLEEPING);
	पूर्ण
	वापस work_करोne;
पूर्ण

irqवापस_t t1_पूर्णांकerrupt_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा adapter *adapter = data;
	u32 pending_thपढ़ो_पूर्णांकr;

	spin_lock_irq(&adapter->async_lock);
	pending_thपढ़ो_पूर्णांकr = adapter->pending_thपढ़ो_पूर्णांकr;
	adapter->pending_thपढ़ो_पूर्णांकr = 0;
	spin_unlock_irq(&adapter->async_lock);

	अगर (!pending_thपढ़ो_पूर्णांकr)
		वापस IRQ_NONE;

	अगर (pending_thपढ़ो_पूर्णांकr & F_PL_INTR_EXT)
		t1_elmer0_ext_पूर्णांकr_handler(adapter);

	/* This error is fatal, पूर्णांकerrupts reमुख्य off */
	अगर (pending_thपढ़ो_पूर्णांकr & F_PL_INTR_SGE_ERR) अणु
		pr_alert("%s: encountered fatal error, operation suspended\n",
			 adapter->name);
		t1_sge_stop(adapter->sge);
		वापस IRQ_HANDLED;
	पूर्ण

	spin_lock_irq(&adapter->async_lock);
	adapter->slow_पूर्णांकr_mask |= F_PL_INTR_EXT;

	ग_लिखोl(F_PL_INTR_EXT, adapter->regs + A_PL_CAUSE);
	ग_लिखोl(adapter->slow_पूर्णांकr_mask | F_PL_INTR_SGE_DATA,
	       adapter->regs + A_PL_ENABLE);
	spin_unlock_irq(&adapter->async_lock);

	वापस IRQ_HANDLED;
पूर्ण

irqवापस_t t1_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा adapter *adapter = data;
	काष्ठा sge *sge = adapter->sge;
	irqवापस_t handled;

	अगर (likely(responses_pending(adapter))) अणु
		ग_लिखोl(F_PL_INTR_SGE_DATA, adapter->regs + A_PL_CAUSE);

		अगर (napi_schedule_prep(&adapter->napi)) अणु
			अगर (process_pure_responses(adapter))
				__napi_schedule(&adapter->napi);
			अन्यथा अणु
				/* no data, no NAPI needed */
				ग_लिखोl(sge->respQ.cidx, adapter->regs + A_SG_SLEEPING);
				/* unकरो schedule_prep */
				napi_enable(&adapter->napi);
			पूर्ण
		पूर्ण
		वापस IRQ_HANDLED;
	पूर्ण

	spin_lock(&adapter->async_lock);
	handled = t1_slow_पूर्णांकr_handler(adapter);
	spin_unlock(&adapter->async_lock);

	अगर (handled == IRQ_NONE)
		sge->stats.unhandled_irqs++;

	वापस handled;
पूर्ण

/*
 * Enqueues the sk_buff onto the cmdQ[qid] and has hardware fetch it.
 *
 * The code figures out how many entries the sk_buff will require in the
 * cmdQ and updates the cmdQ data काष्ठाure with the state once the enqueue
 * has complete. Then, it करोesn't access the global काष्ठाure anymore, but
 * uses the corresponding fields on the stack. In conjunction with a spinlock
 * around that code, we can make the function reentrant without holding the
 * lock when we actually enqueue (which might be expensive, especially on
 * architectures with IO MMUs).
 *
 * This runs with softirqs disabled.
 */
अटल पूर्णांक t1_sge_tx(काष्ठा sk_buff *skb, काष्ठा adapter *adapter,
		     अचिन्हित पूर्णांक qid, काष्ठा net_device *dev)
अणु
	काष्ठा sge *sge = adapter->sge;
	काष्ठा cmdQ *q = &sge->cmdQ[qid];
	अचिन्हित पूर्णांक credits, pidx, genbit, count, use_sched_skb = 0;

	spin_lock(&q->lock);

	reclaim_completed_tx(sge, q);

	pidx = q->pidx;
	credits = q->size - q->in_use;
	count = 1 + skb_shinfo(skb)->nr_frags;
	count += compute_large_page_tx_descs(skb);

	/* Ethernet packet */
	अगर (unlikely(credits < count)) अणु
		अगर (!netअगर_queue_stopped(dev)) अणु
			netअगर_stop_queue(dev);
			set_bit(dev->अगर_port, &sge->stopped_tx_queues);
			sge->stats.cmdQ_full[2]++;
			pr_err("%s: Tx ring full while queue awake!\n",
			       adapter->name);
		पूर्ण
		spin_unlock(&q->lock);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	अगर (unlikely(credits - count < q->stop_thres)) अणु
		netअगर_stop_queue(dev);
		set_bit(dev->अगर_port, &sge->stopped_tx_queues);
		sge->stats.cmdQ_full[2]++;
	पूर्ण

	/* T204 cmdQ0 skbs that are destined क्रम a certain port have to go
	 * through the scheduler.
	 */
	अगर (sge->tx_sched && !qid && skb->dev) अणु
use_sched:
		use_sched_skb = 1;
		/* Note that the scheduler might वापस a dअगरferent skb than
		 * the one passed in.
		 */
		skb = sched_skb(sge, skb, credits);
		अगर (!skb) अणु
			spin_unlock(&q->lock);
			वापस NETDEV_TX_OK;
		पूर्ण
		pidx = q->pidx;
		count = 1 + skb_shinfo(skb)->nr_frags;
		count += compute_large_page_tx_descs(skb);
	पूर्ण

	q->in_use += count;
	genbit = q->genbit;
	pidx = q->pidx;
	q->pidx += count;
	अगर (q->pidx >= q->size) अणु
		q->pidx -= q->size;
		q->genbit ^= 1;
	पूर्ण
	spin_unlock(&q->lock);

	ग_लिखो_tx_descs(adapter, skb, pidx, genbit, q);

	/*
	 * We always ring the करोorbell क्रम cmdQ1.  For cmdQ0, we only ring
	 * the करोorbell अगर the Q is asleep. There is a natural race, where
	 * the hardware is going to sleep just after we checked, however,
	 * then the पूर्णांकerrupt handler will detect the outstanding TX packet
	 * and ring the करोorbell क्रम us.
	 */
	अगर (qid)
		करोorbell_pio(adapter, F_CMDQ1_ENABLE);
	अन्यथा अणु
		clear_bit(CMDQ_STAT_LAST_PKT_DB, &q->status);
		अगर (test_and_set_bit(CMDQ_STAT_RUNNING, &q->status) == 0) अणु
			set_bit(CMDQ_STAT_LAST_PKT_DB, &q->status);
			ग_लिखोl(F_CMDQ0_ENABLE, adapter->regs + A_SG_DOORBELL);
		पूर्ण
	पूर्ण

	अगर (use_sched_skb) अणु
		अगर (spin_trylock(&q->lock)) अणु
			credits = q->size - q->in_use;
			skb = शून्य;
			जाओ use_sched;
		पूर्ण
	पूर्ण
	वापस NETDEV_TX_OK;
पूर्ण

#घोषणा MK_ETH_TYPE_MSS(type, mss) (((mss) & 0x3FFF) | ((type) << 14))

/*
 *	eth_hdr_len - वापस the length of an Ethernet header
 *	@data: poपूर्णांकer to the start of the Ethernet header
 *
 *	Returns the length of an Ethernet header, including optional VLAN tag.
 */
अटल अंतरभूत पूर्णांक eth_hdr_len(स्थिर व्योम *data)
अणु
	स्थिर काष्ठा ethhdr *e = data;

	वापस e->h_proto == htons(ETH_P_8021Q) ? VLAN_ETH_HLEN : ETH_HLEN;
पूर्ण

/*
 * Adds the CPL header to the sk_buff and passes it to t1_sge_tx.
 */
netdev_tx_t t1_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा adapter *adapter = dev->ml_priv;
	काष्ठा sge *sge = adapter->sge;
	काष्ठा sge_port_stats *st = this_cpu_ptr(sge->port_stats[dev->अगर_port]);
	काष्ठा cpl_tx_pkt *cpl;
	काष्ठा sk_buff *orig_skb = skb;
	पूर्णांक ret;

	अगर (skb->protocol == htons(ETH_P_CPL5))
		जाओ send;

	/*
	 * We are using a non-standard hard_header_len.
	 * Allocate more header room in the rare हालs it is not big enough.
	 */
	अगर (unlikely(skb_headroom(skb) < dev->hard_header_len - ETH_HLEN)) अणु
		skb = skb_पुनः_स्मृति_headroom(skb, माप(काष्ठा cpl_tx_pkt_lso));
		++st->tx_need_hdrroom;
		dev_kमुक्त_skb_any(orig_skb);
		अगर (!skb)
			वापस NETDEV_TX_OK;
	पूर्ण

	अगर (skb_shinfo(skb)->gso_size) अणु
		पूर्णांक eth_type;
		काष्ठा cpl_tx_pkt_lso *hdr;

		++st->tx_tso;

		eth_type = skb_network_offset(skb) == ETH_HLEN ?
			CPL_ETH_II : CPL_ETH_II_VLAN;

		hdr = skb_push(skb, माप(*hdr));
		hdr->opcode = CPL_TX_PKT_LSO;
		hdr->ip_csum_dis = hdr->l4_csum_dis = 0;
		hdr->ip_hdr_words = ip_hdr(skb)->ihl;
		hdr->tcp_hdr_words = tcp_hdr(skb)->करोff;
		hdr->eth_type_mss = htons(MK_ETH_TYPE_MSS(eth_type,
							  skb_shinfo(skb)->gso_size));
		hdr->len = htonl(skb->len - माप(*hdr));
		cpl = (काष्ठा cpl_tx_pkt *)hdr;
	पूर्ण अन्यथा अणु
		/*
		 * Packets लघुer than ETH_HLEN can अवरोध the MAC, drop them
		 * early.  Also, we may get oversized packets because some
		 * parts of the kernel करोn't handle our unusual hard_header_len
		 * right, drop those too.
		 */
		अगर (unlikely(skb->len < ETH_HLEN ||
			     skb->len > dev->mtu + eth_hdr_len(skb->data))) अणु
			netdev_dbg(dev, "packet size %d hdr %d mtu%d\n",
				   skb->len, eth_hdr_len(skb->data), dev->mtu);
			dev_kमुक्त_skb_any(skb);
			वापस NETDEV_TX_OK;
		पूर्ण

		अगर (skb->ip_summed == CHECKSUM_PARTIAL &&
		    ip_hdr(skb)->protocol == IPPROTO_UDP) अणु
			अगर (unlikely(skb_checksum_help(skb))) अणु
				netdev_dbg(dev, "unable to do udp checksum\n");
				dev_kमुक्त_skb_any(skb);
				वापस NETDEV_TX_OK;
			पूर्ण
		पूर्ण

		/* Hmmm, assuming to catch the gratious arp... and we'll use
		 * it to flush out stuck espi packets...
		 */
		अगर ((unlikely(!adapter->sge->espibug_skb[dev->अगर_port]))) अणु
			अगर (skb->protocol == htons(ETH_P_ARP) &&
			    arp_hdr(skb)->ar_op == htons(ARPOP_REQUEST)) अणु
				adapter->sge->espibug_skb[dev->अगर_port] = skb;
				/* We want to re-use this skb later. We
				 * simply bump the reference count and it
				 * will not be मुक्तd...
				 */
				skb = skb_get(skb);
			पूर्ण
		पूर्ण

		cpl = __skb_push(skb, माप(*cpl));
		cpl->opcode = CPL_TX_PKT;
		cpl->ip_csum_dis = 1;    /* SW calculates IP csum */
		cpl->l4_csum_dis = skb->ip_summed == CHECKSUM_PARTIAL ? 0 : 1;
		/* the length field isn't used so don't bother setting it */

		st->tx_cso += (skb->ip_summed == CHECKSUM_PARTIAL);
	पूर्ण
	cpl->अगरf = dev->अगर_port;

	अगर (skb_vlan_tag_present(skb)) अणु
		cpl->vlan_valid = 1;
		cpl->vlan = htons(skb_vlan_tag_get(skb));
		st->vlan_insert++;
	पूर्ण अन्यथा
		cpl->vlan_valid = 0;

send:
	ret = t1_sge_tx(skb, adapter, 0, dev);

	/* If transmit busy, and we पुनः_स्मृतिated skb's due to headroom limit,
	 * then silently discard to aव्योम leak.
	 */
	अगर (unlikely(ret != NETDEV_TX_OK && skb != orig_skb)) अणु
		dev_kमुक्त_skb_any(skb);
		ret = NETDEV_TX_OK;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Callback क्रम the Tx buffer reclaim समयr.  Runs with softirqs disabled.
 */
अटल व्योम sge_tx_reclaim_cb(काष्ठा समयr_list *t)
अणु
	पूर्णांक i;
	काष्ठा sge *sge = from_समयr(sge, t, tx_reclaim_समयr);

	क्रम (i = 0; i < SGE_CMDQ_N; ++i) अणु
		काष्ठा cmdQ *q = &sge->cmdQ[i];

		अगर (!spin_trylock(&q->lock))
			जारी;

		reclaim_completed_tx(sge, q);
		अगर (i == 0 && q->in_use) अणु    /* flush pending credits */
			ग_लिखोl(F_CMDQ0_ENABLE, sge->adapter->regs + A_SG_DOORBELL);
		पूर्ण
		spin_unlock(&q->lock);
	पूर्ण
	mod_समयr(&sge->tx_reclaim_समयr, jअगरfies + TX_RECLAIM_PERIOD);
पूर्ण

/*
 * Propagate changes of the SGE coalescing parameters to the HW.
 */
पूर्णांक t1_sge_set_coalesce_params(काष्ठा sge *sge, काष्ठा sge_params *p)
अणु
	sge->fixed_पूर्णांकrसमयr = p->rx_coalesce_usecs *
		core_ticks_per_usec(sge->adapter);
	ग_लिखोl(sge->fixed_पूर्णांकrसमयr, sge->adapter->regs + A_SG_INTRTIMER);
	वापस 0;
पूर्ण

/*
 * Allocates both RX and TX resources and configures the SGE. However,
 * the hardware is not enabled yet.
 */
पूर्णांक t1_sge_configure(काष्ठा sge *sge, काष्ठा sge_params *p)
अणु
	अगर (alloc_rx_resources(sge, p))
		वापस -ENOMEM;
	अगर (alloc_tx_resources(sge, p)) अणु
		मुक्त_rx_resources(sge);
		वापस -ENOMEM;
	पूर्ण
	configure_sge(sge, p);

	/*
	 * Now that we have sized the मुक्त lists calculate the payload
	 * capacity of the large buffers.  Other parts of the driver use
	 * this to set the max offload coalescing size so that RX packets
	 * करो not overflow our large buffers.
	 */
	p->large_buf_capacity = jumbo_payload_capacity(sge);
	वापस 0;
पूर्ण

/*
 * Disables the DMA engine.
 */
व्योम t1_sge_stop(काष्ठा sge *sge)
अणु
	पूर्णांक i;
	ग_लिखोl(0, sge->adapter->regs + A_SG_CONTROL);
	पढ़ोl(sge->adapter->regs + A_SG_CONTROL); /* flush */

	अगर (is_T2(sge->adapter))
		del_समयr_sync(&sge->espibug_समयr);

	del_समयr_sync(&sge->tx_reclaim_समयr);
	अगर (sge->tx_sched)
		tx_sched_stop(sge);

	क्रम (i = 0; i < MAX_NPORTS; i++)
		kमुक्त_skb(sge->espibug_skb[i]);
पूर्ण

/*
 * Enables the DMA engine.
 */
व्योम t1_sge_start(काष्ठा sge *sge)
अणु
	refill_मुक्त_list(sge, &sge->मुक्तlQ[0]);
	refill_मुक्त_list(sge, &sge->मुक्तlQ[1]);

	ग_लिखोl(sge->sge_control, sge->adapter->regs + A_SG_CONTROL);
	करोorbell_pio(sge->adapter, F_FL0_ENABLE | F_FL1_ENABLE);
	पढ़ोl(sge->adapter->regs + A_SG_CONTROL); /* flush */

	mod_समयr(&sge->tx_reclaim_समयr, jअगरfies + TX_RECLAIM_PERIOD);

	अगर (is_T2(sge->adapter))
		mod_समयr(&sge->espibug_समयr, jअगरfies + sge->espibug_समयout);
पूर्ण

/*
 * Callback क्रम the T2 ESPI 'stuck packet feature' workaorund
 */
अटल व्योम espibug_workaround_t204(काष्ठा समयr_list *t)
अणु
	काष्ठा sge *sge = from_समयr(sge, t, espibug_समयr);
	काष्ठा adapter *adapter = sge->adapter;
	अचिन्हित पूर्णांक nports = adapter->params.nports;
	u32 seop[MAX_NPORTS];

	अगर (adapter->खोलो_device_map & PORT_MASK) अणु
		पूर्णांक i;

		अगर (t1_espi_get_mon_t204(adapter, &(seop[0]), 0) < 0)
			वापस;

		क्रम (i = 0; i < nports; i++) अणु
			काष्ठा sk_buff *skb = sge->espibug_skb[i];

			अगर (!netअगर_running(adapter->port[i].dev) ||
			    netअगर_queue_stopped(adapter->port[i].dev) ||
			    !seop[i] || ((seop[i] & 0xfff) != 0) || !skb)
				जारी;

			अगर (!skb->cb[0]) अणु
				skb_copy_to_linear_data_offset(skb,
						    माप(काष्ठा cpl_tx_pkt),
							       ch_mac_addr,
							       ETH_ALEN);
				skb_copy_to_linear_data_offset(skb,
							       skb->len - 10,
							       ch_mac_addr,
							       ETH_ALEN);
				skb->cb[0] = 0xff;
			पूर्ण

			/* bump the reference count to aव्योम मुक्तing of
			 * the skb once the DMA has completed.
			 */
			skb = skb_get(skb);
			t1_sge_tx(skb, adapter, 0, adapter->port[i].dev);
		पूर्ण
	पूर्ण
	mod_समयr(&sge->espibug_समयr, jअगरfies + sge->espibug_समयout);
पूर्ण

अटल व्योम espibug_workaround(काष्ठा समयr_list *t)
अणु
	काष्ठा sge *sge = from_समयr(sge, t, espibug_समयr);
	काष्ठा adapter *adapter = sge->adapter;

	अगर (netअगर_running(adapter->port[0].dev)) अणु
	        काष्ठा sk_buff *skb = sge->espibug_skb[0];
	        u32 seop = t1_espi_get_mon(adapter, 0x930, 0);

	        अगर ((seop & 0xfff0fff) == 0xfff && skb) अणु
	                अगर (!skb->cb[0]) अणु
	                        skb_copy_to_linear_data_offset(skb,
						     माप(काष्ठा cpl_tx_pkt),
							       ch_mac_addr,
							       ETH_ALEN);
	                        skb_copy_to_linear_data_offset(skb,
							       skb->len - 10,
							       ch_mac_addr,
							       ETH_ALEN);
	                        skb->cb[0] = 0xff;
	                पूर्ण

	                /* bump the reference count to aव्योम मुक्तing of the
	                 * skb once the DMA has completed.
	                 */
	                skb = skb_get(skb);
	                t1_sge_tx(skb, adapter, 0, adapter->port[0].dev);
	        पूर्ण
	पूर्ण
	mod_समयr(&sge->espibug_समयr, jअगरfies + sge->espibug_समयout);
पूर्ण

/*
 * Creates a t1_sge काष्ठाure and वापसs suggested resource parameters.
 */
काष्ठा sge *t1_sge_create(काष्ठा adapter *adapter, काष्ठा sge_params *p)
अणु
	काष्ठा sge *sge = kzalloc(माप(*sge), GFP_KERNEL);
	पूर्णांक i;

	अगर (!sge)
		वापस शून्य;

	sge->adapter = adapter;
	sge->netdev = adapter->port[0].dev;
	sge->rx_pkt_pad = t1_is_T1B(adapter) ? 0 : 2;
	sge->jumbo_fl = t1_is_T1B(adapter) ? 1 : 0;

	क्रम_each_port(adapter, i) अणु
		sge->port_stats[i] = alloc_percpu(काष्ठा sge_port_stats);
		अगर (!sge->port_stats[i])
			जाओ nomem_port;
	पूर्ण

	समयr_setup(&sge->tx_reclaim_समयr, sge_tx_reclaim_cb, 0);

	अगर (is_T2(sge->adapter)) अणु
		समयr_setup(&sge->espibug_समयr,
			    adapter->params.nports > 1 ? espibug_workaround_t204 : espibug_workaround,
			    0);

		अगर (adapter->params.nports > 1)
			tx_sched_init(sge);

		sge->espibug_समयout = 1;
		/* क्रम T204, every 10ms */
		अगर (adapter->params.nports > 1)
			sge->espibug_समयout = HZ/100;
	पूर्ण


	p->cmdQ_size[0] = SGE_CMDQ0_E_N;
	p->cmdQ_size[1] = SGE_CMDQ1_E_N;
	p->मुक्तlQ_size[!sge->jumbo_fl] = SGE_FREEL_SIZE;
	p->मुक्तlQ_size[sge->jumbo_fl] = SGE_JUMBO_FREEL_SIZE;
	अगर (sge->tx_sched) अणु
		अगर (board_info(sge->adapter)->board == CHBT_BOARD_CHT204)
			p->rx_coalesce_usecs = 15;
		अन्यथा
			p->rx_coalesce_usecs = 50;
	पूर्ण अन्यथा
		p->rx_coalesce_usecs = 50;

	p->coalesce_enable = 0;
	p->sample_पूर्णांकerval_usecs = 0;

	वापस sge;
nomem_port:
	जबतक (i >= 0) अणु
		मुक्त_percpu(sge->port_stats[i]);
		--i;
	पूर्ण
	kमुक्त(sge);
	वापस शून्य;

पूर्ण
