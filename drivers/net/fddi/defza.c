<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*	FDDI network adapter driver क्रम DEC FDDIcontroller 700/700-C devices.
 *
 *	Copyright (c) 2018  Maciej W. Rozycki
 *
 *	This program is मुक्त software; you can redistribute it and/or
 *	modअगरy it under the terms of the GNU General Public License
 *	as published by the Free Software Foundation; either version
 *	2 of the License, or (at your option) any later version.
 *
 *	References:
 *
 *	Dave Sawyer & Phil Weeks & Frank Itkowsky,
 *	"DEC FDDIcontroller 700 Port Specification",
 *	Revision 1.1, Digital Equipment Corporation
 */

/* ------------------------------------------------------------------------- */
/* FZA configurable parameters.                                              */

/* The number of transmit ring descriptors; either 0 क्रम 512 or 1 क्रम 1024.  */
#घोषणा FZA_RING_TX_MODE 0

/* The number of receive ring descriptors; from 2 up to 256.  */
#घोषणा FZA_RING_RX_SIZE 256

/* End of FZA configurable parameters.  No need to change anything below.    */
/* ------------------------------------------------------------------------- */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/io-64-nonatomic-lo-hi.h>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/fddidevice.h>
#समावेश <linux/sched.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/tc.h>
#समावेश <linux/समयr.h>
#समावेश <linux/types.h>
#समावेश <linux/रुको.h>

#समावेश <यंत्र/barrier.h>

#समावेश "defza.h"

#घोषणा DRV_NAME "defza"
#घोषणा DRV_VERSION "v.1.1.4"
#घोषणा DRV_RELDATE "Oct  6 2018"

अटल स्थिर अक्षर version[] =
	DRV_NAME ": " DRV_VERSION "  " DRV_RELDATE "  Maciej W. Rozycki\n";

MODULE_AUTHOR("Maciej W. Rozycki <macro@orcam.me.uk>");
MODULE_DESCRIPTION("DEC FDDIcontroller 700 (DEFZA-xx) driver");
MODULE_LICENSE("GPL");

अटल पूर्णांक loopback;
module_param(loopback, पूर्णांक, 0644);

/* Ring Purger Multicast */
अटल u8 hw_addr_purger[8] = अणु 0x09, 0x00, 0x2b, 0x02, 0x01, 0x05 पूर्ण;
/* Directed Beacon Multicast */
अटल u8 hw_addr_beacon[8] = अणु 0x01, 0x80, 0xc2, 0x00, 0x01, 0x00 पूर्ण;

/* Shorthands क्रम MMIO accesses that we require to be strongly ordered
 * WRT preceding MMIO accesses.
 */
#घोषणा पढ़ोw_o पढ़ोw_relaxed
#घोषणा पढ़ोl_o पढ़ोl_relaxed

#घोषणा ग_लिखोw_o ग_लिखोw_relaxed
#घोषणा ग_लिखोl_o ग_लिखोl_relaxed

/* Shorthands क्रम MMIO accesses that we are happy with being weakly ordered
 * WRT preceding MMIO accesses.
 */
#घोषणा पढ़ोw_u पढ़ोw_relaxed
#घोषणा पढ़ोl_u पढ़ोl_relaxed
#घोषणा पढ़ोq_u पढ़ोq_relaxed

#घोषणा ग_लिखोw_u ग_लिखोw_relaxed
#घोषणा ग_लिखोl_u ग_लिखोl_relaxed
#घोषणा ग_लिखोq_u ग_लिखोq_relaxed

अटल अंतरभूत काष्ठा sk_buff *fza_alloc_skb_irq(काष्ठा net_device *dev,
						अचिन्हित पूर्णांक length)
अणु
	वापस __netdev_alloc_skb(dev, length, GFP_ATOMIC);
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *fza_alloc_skb(काष्ठा net_device *dev,
					    अचिन्हित पूर्णांक length)
अणु
	वापस __netdev_alloc_skb(dev, length, GFP_KERNEL);
पूर्ण

अटल अंतरभूत व्योम fza_skb_align(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक v)
अणु
	अचिन्हित दीर्घ x, y;

	x = (अचिन्हित दीर्घ)skb->data;
	y = ALIGN(x, v);

	skb_reserve(skb, y - x);
पूर्ण

अटल अंतरभूत व्योम fza_पढ़ोs(स्थिर व्योम __iomem *from, व्योम *to,
			     अचिन्हित दीर्घ size)
अणु
	अगर (माप(अचिन्हित दीर्घ) == 8) अणु
		स्थिर u64 __iomem *src = from;
		स्थिर u32 __iomem *src_trail;
		u64 *dst = to;
		u32 *dst_trail;

		क्रम (size = (size + 3) / 4; size > 1; size -= 2)
			*dst++ = पढ़ोq_u(src++);
		अगर (size) अणु
			src_trail = (u32 __iomem *)src;
			dst_trail = (u32 *)dst;
			*dst_trail = पढ़ोl_u(src_trail);
		पूर्ण
	पूर्ण अन्यथा अणु
		स्थिर u32 __iomem *src = from;
		u32 *dst = to;

		क्रम (size = (size + 3) / 4; size; size--)
			*dst++ = पढ़ोl_u(src++);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम fza_ग_लिखोs(स्थिर व्योम *from, व्योम __iomem *to,
			      अचिन्हित दीर्घ size)
अणु
	अगर (माप(अचिन्हित दीर्घ) == 8) अणु
		स्थिर u64 *src = from;
		स्थिर u32 *src_trail;
		u64 __iomem *dst = to;
		u32 __iomem *dst_trail;

		क्रम (size = (size + 3) / 4; size > 1; size -= 2)
			ग_लिखोq_u(*src++, dst++);
		अगर (size) अणु
			src_trail = (u32 *)src;
			dst_trail = (u32 __iomem *)dst;
			ग_लिखोl_u(*src_trail, dst_trail);
		पूर्ण
	पूर्ण अन्यथा अणु
		स्थिर u32 *src = from;
		u32 __iomem *dst = to;

		क्रम (size = (size + 3) / 4; size; size--)
			ग_लिखोl_u(*src++, dst++);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम fza_moves(स्थिर व्योम __iomem *from, व्योम __iomem *to,
			     अचिन्हित दीर्घ size)
अणु
	अगर (माप(अचिन्हित दीर्घ) == 8) अणु
		स्थिर u64 __iomem *src = from;
		स्थिर u32 __iomem *src_trail;
		u64 __iomem *dst = to;
		u32 __iomem *dst_trail;

		क्रम (size = (size + 3) / 4; size > 1; size -= 2)
			ग_लिखोq_u(पढ़ोq_u(src++), dst++);
		अगर (size) अणु
			src_trail = (u32 __iomem *)src;
			dst_trail = (u32 __iomem *)dst;
			ग_लिखोl_u(पढ़ोl_u(src_trail), dst_trail);
		पूर्ण
	पूर्ण अन्यथा अणु
		स्थिर u32 __iomem *src = from;
		u32 __iomem *dst = to;

		क्रम (size = (size + 3) / 4; size; size--)
			ग_लिखोl_u(पढ़ोl_u(src++), dst++);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम fza_zeros(व्योम __iomem *to, अचिन्हित दीर्घ size)
अणु
	अगर (माप(अचिन्हित दीर्घ) == 8) अणु
		u64 __iomem *dst = to;
		u32 __iomem *dst_trail;

		क्रम (size = (size + 3) / 4; size > 1; size -= 2)
			ग_लिखोq_u(0, dst++);
		अगर (size) अणु
			dst_trail = (u32 __iomem *)dst;
			ग_लिखोl_u(0, dst_trail);
		पूर्ण
	पूर्ण अन्यथा अणु
		u32 __iomem *dst = to;

		क्रम (size = (size + 3) / 4; size; size--)
			ग_लिखोl_u(0, dst++);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम fza_regs_dump(काष्ठा fza_निजी *fp)
अणु
	pr_debug("%s: iomem registers:\n", fp->name);
	pr_debug(" reset:           0x%04x\n", पढ़ोw_o(&fp->regs->reset));
	pr_debug(" interrupt event: 0x%04x\n", पढ़ोw_u(&fp->regs->पूर्णांक_event));
	pr_debug(" status:          0x%04x\n", पढ़ोw_u(&fp->regs->status));
	pr_debug(" interrupt mask:  0x%04x\n", पढ़ोw_u(&fp->regs->पूर्णांक_mask));
	pr_debug(" control A:       0x%04x\n", पढ़ोw_u(&fp->regs->control_a));
	pr_debug(" control B:       0x%04x\n", पढ़ोw_u(&fp->regs->control_b));
पूर्ण

अटल अंतरभूत व्योम fza_करो_reset(काष्ठा fza_निजी *fp)
अणु
	/* Reset the board. */
	ग_लिखोw_o(FZA_RESET_INIT, &fp->regs->reset);
	पढ़ोw_o(&fp->regs->reset);	/* Synchronize. */
	पढ़ोw_o(&fp->regs->reset);	/* Read it back क्रम a small delay. */
	ग_लिखोw_o(FZA_RESET_CLR, &fp->regs->reset);

	/* Enable all पूर्णांकerrupt events we handle. */
	ग_लिखोw_o(fp->पूर्णांक_mask, &fp->regs->पूर्णांक_mask);
	पढ़ोw_o(&fp->regs->पूर्णांक_mask);	/* Synchronize. */
पूर्ण

अटल अंतरभूत व्योम fza_करो_shutकरोwn(काष्ठा fza_निजी *fp)
अणु
	/* Disable the driver mode. */
	ग_लिखोw_o(FZA_CONTROL_B_IDLE, &fp->regs->control_b);

	/* And reset the board. */
	ग_लिखोw_o(FZA_RESET_INIT, &fp->regs->reset);
	पढ़ोw_o(&fp->regs->reset);	/* Synchronize. */
	ग_लिखोw_o(FZA_RESET_CLR, &fp->regs->reset);
	पढ़ोw_o(&fp->regs->reset);	/* Synchronize. */
पूर्ण

अटल पूर्णांक fza_reset(काष्ठा fza_निजी *fp)
अणु
	अचिन्हित दीर्घ flags;
	uपूर्णांक status, state;
	दीर्घ t;

	pr_info("%s: resetting the board...\n", fp->name);

	spin_lock_irqsave(&fp->lock, flags);
	fp->state_chg_flag = 0;
	fza_करो_reset(fp);
	spin_unlock_irqrestore(&fp->lock, flags);

	/* DEC says RESET needs up to 30 seconds to complete.  My DEFZA-AA
	 * rev. C03 happily finishes in 9.7 seconds. :-)  But we need to
	 * be on the safe side...
	 */
	t = रुको_event_समयout(fp->state_chg_रुको, fp->state_chg_flag,
			       45 * HZ);
	status = पढ़ोw_u(&fp->regs->status);
	state = FZA_STATUS_GET_STATE(status);
	अगर (fp->state_chg_flag == 0) अणु
		pr_err("%s: RESET timed out!, state %x\n", fp->name, state);
		वापस -EIO;
	पूर्ण
	अगर (state != FZA_STATE_UNINITIALIZED) अणु
		pr_err("%s: RESET failed!, state %x, failure ID %x\n",
		       fp->name, state, FZA_STATUS_GET_TEST(status));
		वापस -EIO;
	पूर्ण
	pr_info("%s: OK\n", fp->name);
	pr_debug("%s: RESET: %lums elapsed\n", fp->name,
		 (45 * HZ - t) * 1000 / HZ);

	वापस 0;
पूर्ण

अटल काष्ठा fza_ring_cmd __iomem *fza_cmd_send(काष्ठा net_device *dev,
						 पूर्णांक command)
अणु
	काष्ठा fza_निजी *fp = netdev_priv(dev);
	काष्ठा fza_ring_cmd __iomem *ring = fp->ring_cmd + fp->ring_cmd_index;
	अचिन्हित पूर्णांक old_mask, new_mask;
	जोड़ fza_cmd_buf __iomem *buf;
	काष्ठा netdev_hw_addr *ha;
	पूर्णांक i;

	old_mask = fp->पूर्णांक_mask;
	new_mask = old_mask & ~FZA_MASK_STATE_CHG;
	ग_लिखोw_u(new_mask, &fp->regs->पूर्णांक_mask);
	पढ़ोw_o(&fp->regs->पूर्णांक_mask);			/* Synchronize. */
	fp->पूर्णांक_mask = new_mask;

	buf = fp->mmio + पढ़ोl_u(&ring->buffer);

	अगर ((पढ़ोl_u(&ring->cmd_own) & FZA_RING_OWN_MASK) !=
	    FZA_RING_OWN_HOST) अणु
		pr_warn("%s: command buffer full, command: %u!\n", fp->name,
			command);
		वापस शून्य;
	पूर्ण

	चयन (command) अणु
	हाल FZA_RING_CMD_INIT:
		ग_लिखोl_u(FZA_RING_TX_MODE, &buf->init.tx_mode);
		ग_लिखोl_u(FZA_RING_RX_SIZE, &buf->init.hst_rx_size);
		fza_zeros(&buf->init.counters, माप(buf->init.counters));
		अवरोध;

	हाल FZA_RING_CMD_MODCAM:
		i = 0;
		fza_ग_लिखोs(&hw_addr_purger, &buf->cam.hw_addr[i++],
			   माप(*buf->cam.hw_addr));
		fza_ग_लिखोs(&hw_addr_beacon, &buf->cam.hw_addr[i++],
			   माप(*buf->cam.hw_addr));
		netdev_क्रम_each_mc_addr(ha, dev) अणु
			अगर (i >= FZA_CMD_CAM_SIZE)
				अवरोध;
			fza_ग_लिखोs(ha->addr, &buf->cam.hw_addr[i++],
				   माप(*buf->cam.hw_addr));
		पूर्ण
		जबतक (i < FZA_CMD_CAM_SIZE)
			fza_zeros(&buf->cam.hw_addr[i++],
				  माप(*buf->cam.hw_addr));
		अवरोध;

	हाल FZA_RING_CMD_PARAM:
		ग_लिखोl_u(loopback, &buf->param.loop_mode);
		ग_लिखोl_u(fp->t_max, &buf->param.t_max);
		ग_लिखोl_u(fp->t_req, &buf->param.t_req);
		ग_लिखोl_u(fp->tvx, &buf->param.tvx);
		ग_लिखोl_u(fp->lem_threshold, &buf->param.lem_threshold);
		fza_ग_लिखोs(&fp->station_id, &buf->param.station_id,
			   माप(buf->param.station_id));
		/* Convert to milliseconds due to buggy firmware. */
		ग_लिखोl_u(fp->rtoken_समयout / 12500,
			 &buf->param.rtoken_समयout);
		ग_लिखोl_u(fp->ring_purger, &buf->param.ring_purger);
		अवरोध;

	हाल FZA_RING_CMD_MODPROM:
		अगर (dev->flags & IFF_PROMISC) अणु
			ग_लिखोl_u(1, &buf->modprom.llc_prom);
			ग_लिखोl_u(1, &buf->modprom.smt_prom);
		पूर्ण अन्यथा अणु
			ग_लिखोl_u(0, &buf->modprom.llc_prom);
			ग_लिखोl_u(0, &buf->modprom.smt_prom);
		पूर्ण
		अगर (dev->flags & IFF_ALLMULTI ||
		    netdev_mc_count(dev) > FZA_CMD_CAM_SIZE - 2)
			ग_लिखोl_u(1, &buf->modprom.llc_multi);
		अन्यथा
			ग_लिखोl_u(0, &buf->modprom.llc_multi);
		ग_लिखोl_u(1, &buf->modprom.llc_bcast);
		अवरोध;
	पूर्ण

	/* Trigger the command. */
	ग_लिखोl_u(FZA_RING_OWN_FZA | command, &ring->cmd_own);
	ग_लिखोw_o(FZA_CONTROL_A_CMD_POLL, &fp->regs->control_a);

	fp->ring_cmd_index = (fp->ring_cmd_index + 1) % FZA_RING_CMD_SIZE;

	fp->पूर्णांक_mask = old_mask;
	ग_लिखोw_u(fp->पूर्णांक_mask, &fp->regs->पूर्णांक_mask);

	वापस ring;
पूर्ण

अटल पूर्णांक fza_init_send(काष्ठा net_device *dev,
			 काष्ठा fza_cmd_init *__iomem *init)
अणु
	काष्ठा fza_निजी *fp = netdev_priv(dev);
	काष्ठा fza_ring_cmd __iomem *ring;
	अचिन्हित दीर्घ flags;
	u32 stat;
	दीर्घ t;

	spin_lock_irqsave(&fp->lock, flags);
	fp->cmd_करोne_flag = 0;
	ring = fza_cmd_send(dev, FZA_RING_CMD_INIT);
	spin_unlock_irqrestore(&fp->lock, flags);
	अगर (!ring)
		/* This should never happen in the uninitialized state,
		 * so करो not try to recover and just consider it fatal.
		 */
		वापस -ENOBUFS;

	/* INIT may take quite a दीर्घ समय (160ms क्रम my C03). */
	t = रुको_event_समयout(fp->cmd_करोne_रुको, fp->cmd_करोne_flag, 3 * HZ);
	अगर (fp->cmd_करोne_flag == 0) अणु
		pr_err("%s: INIT command timed out!, state %x\n", fp->name,
		       FZA_STATUS_GET_STATE(पढ़ोw_u(&fp->regs->status)));
		वापस -EIO;
	पूर्ण
	stat = पढ़ोl_u(&ring->stat);
	अगर (stat != FZA_RING_STAT_SUCCESS) अणु
		pr_err("%s: INIT command failed!, status %02x, state %x\n",
		       fp->name, stat,
		       FZA_STATUS_GET_STATE(पढ़ोw_u(&fp->regs->status)));
		वापस -EIO;
	पूर्ण
	pr_debug("%s: INIT: %lums elapsed\n", fp->name,
		 (3 * HZ - t) * 1000 / HZ);

	अगर (init)
		*init = fp->mmio + पढ़ोl_u(&ring->buffer);
	वापस 0;
पूर्ण

अटल व्योम fza_rx_init(काष्ठा fza_निजी *fp)
अणु
	पूर्णांक i;

	/* Fill the host receive descriptor ring. */
	क्रम (i = 0; i < FZA_RING_RX_SIZE; i++) अणु
		ग_लिखोl_o(0, &fp->ring_hst_rx[i].rmc);
		ग_लिखोl_o((fp->rx_dma[i] + 0x1000) >> 9,
			 &fp->ring_hst_rx[i].buffer1);
		ग_लिखोl_o(fp->rx_dma[i] >> 9 | FZA_RING_OWN_FZA,
			 &fp->ring_hst_rx[i].buf0_own);
	पूर्ण
पूर्ण

अटल व्योम fza_set_rx_mode(काष्ठा net_device *dev)
अणु
	fza_cmd_send(dev, FZA_RING_CMD_MODCAM);
	fza_cmd_send(dev, FZA_RING_CMD_MODPROM);
पूर्ण

जोड़ fza_buffer_txp अणु
	काष्ठा fza_buffer_tx *data_ptr;
	काष्ठा fza_buffer_tx __iomem *mmio_ptr;
पूर्ण;

अटल पूर्णांक fza_करो_xmit(जोड़ fza_buffer_txp ub, पूर्णांक len,
		       काष्ठा net_device *dev, पूर्णांक smt)
अणु
	काष्ठा fza_निजी *fp = netdev_priv(dev);
	काष्ठा fza_buffer_tx __iomem *rmc_tx_ptr;
	पूर्णांक i, first, frag_len, left_len;
	u32 own, rmc;

	अगर (((((fp->ring_rmc_txd_index - 1 + fp->ring_rmc_tx_size) -
	       fp->ring_rmc_tx_index) % fp->ring_rmc_tx_size) *
	     FZA_TX_BUFFER_SIZE) < len)
		वापस 1;

	first = fp->ring_rmc_tx_index;

	left_len = len;
	frag_len = FZA_TX_BUFFER_SIZE;
	/* First descriptor is relinquished last. */
	own = FZA_RING_TX_OWN_HOST;
	/* First descriptor carries frame length; we करोn't use cut-through. */
	rmc = FZA_RING_TX_SOP | FZA_RING_TX_VBC | len;
	करो अणु
		i = fp->ring_rmc_tx_index;
		rmc_tx_ptr = &fp->buffer_tx[i];

		अगर (left_len < FZA_TX_BUFFER_SIZE)
			frag_len = left_len;
		left_len -= frag_len;

		/* Length must be a multiple of 4 as only word ग_लिखोs are
		 * permitted!
		 */
		frag_len = (frag_len + 3) & ~3;
		अगर (smt)
			fza_moves(ub.mmio_ptr, rmc_tx_ptr, frag_len);
		अन्यथा
			fza_ग_लिखोs(ub.data_ptr, rmc_tx_ptr, frag_len);

		अगर (left_len == 0)
			rmc |= FZA_RING_TX_EOP;		/* Mark last frag. */

		ग_लिखोl_o(rmc, &fp->ring_rmc_tx[i].rmc);
		ग_लिखोl_o(own, &fp->ring_rmc_tx[i].own);

		ub.data_ptr++;
		fp->ring_rmc_tx_index = (fp->ring_rmc_tx_index + 1) %
					fp->ring_rmc_tx_size;

		/* Settings क्रम पूर्णांकermediate frags. */
		own = FZA_RING_TX_OWN_RMC;
		rmc = 0;
	पूर्ण जबतक (left_len > 0);

	अगर (((((fp->ring_rmc_txd_index - 1 + fp->ring_rmc_tx_size) -
	       fp->ring_rmc_tx_index) % fp->ring_rmc_tx_size) *
	     FZA_TX_BUFFER_SIZE) < dev->mtu + dev->hard_header_len) अणु
		netअगर_stop_queue(dev);
		pr_debug("%s: queue stopped\n", fp->name);
	पूर्ण

	ग_लिखोl_o(FZA_RING_TX_OWN_RMC, &fp->ring_rmc_tx[first].own);

	/* Go, go, go! */
	ग_लिखोw_o(FZA_CONTROL_A_TX_POLL, &fp->regs->control_a);

	वापस 0;
पूर्ण

अटल पूर्णांक fza_करो_recv_smt(काष्ठा fza_buffer_tx *data_ptr, पूर्णांक len,
			   u32 rmc, काष्ठा net_device *dev)
अणु
	काष्ठा fza_निजी *fp = netdev_priv(dev);
	काष्ठा fza_buffer_tx __iomem *smt_rx_ptr;
	u32 own;
	पूर्णांक i;

	i = fp->ring_smt_rx_index;
	own = पढ़ोl_o(&fp->ring_smt_rx[i].own);
	अगर ((own & FZA_RING_OWN_MASK) == FZA_RING_OWN_FZA)
		वापस 1;

	smt_rx_ptr = fp->mmio + पढ़ोl_u(&fp->ring_smt_rx[i].buffer);

	/* Length must be a multiple of 4 as only word ग_लिखोs are permitted! */
	fza_ग_लिखोs(data_ptr, smt_rx_ptr, (len + 3) & ~3);

	ग_लिखोl_o(rmc, &fp->ring_smt_rx[i].rmc);
	ग_लिखोl_o(FZA_RING_OWN_FZA, &fp->ring_smt_rx[i].own);

	fp->ring_smt_rx_index =
		(fp->ring_smt_rx_index + 1) % fp->ring_smt_rx_size;

	/* Grab it! */
	ग_लिखोw_o(FZA_CONTROL_A_SMT_RX_POLL, &fp->regs->control_a);

	वापस 0;
पूर्ण

अटल व्योम fza_tx(काष्ठा net_device *dev)
अणु
	काष्ठा fza_निजी *fp = netdev_priv(dev);
	u32 own, rmc;
	पूर्णांक i;

	जबतक (1) अणु
		i = fp->ring_rmc_txd_index;
		अगर (i == fp->ring_rmc_tx_index)
			अवरोध;
		own = पढ़ोl_o(&fp->ring_rmc_tx[i].own);
		अगर ((own & FZA_RING_OWN_MASK) == FZA_RING_TX_OWN_RMC)
			अवरोध;

		rmc = पढ़ोl_u(&fp->ring_rmc_tx[i].rmc);
		/* Only process the first descriptor. */
		अगर ((rmc & FZA_RING_TX_SOP) != 0) अणु
			अगर ((rmc & FZA_RING_TX_DCC_MASK) ==
			    FZA_RING_TX_DCC_SUCCESS) अणु
				पूर्णांक pkt_len = (rmc & FZA_RING_PBC_MASK) - 3;
								/* Omit PRH. */

				fp->stats.tx_packets++;
				fp->stats.tx_bytes += pkt_len;
			पूर्ण अन्यथा अणु
				fp->stats.tx_errors++;
				चयन (rmc & FZA_RING_TX_DCC_MASK) अणु
				हाल FZA_RING_TX_DCC_DTP_SOP:
				हाल FZA_RING_TX_DCC_DTP:
				हाल FZA_RING_TX_DCC_ABORT:
					fp->stats.tx_पातed_errors++;
					अवरोध;
				हाल FZA_RING_TX_DCC_UNDRRUN:
					fp->stats.tx_fअगरo_errors++;
					अवरोध;
				हाल FZA_RING_TX_DCC_PARITY:
				शेष:
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण

		fp->ring_rmc_txd_index = (fp->ring_rmc_txd_index + 1) %
					 fp->ring_rmc_tx_size;
	पूर्ण

	अगर (((((fp->ring_rmc_txd_index - 1 + fp->ring_rmc_tx_size) -
	       fp->ring_rmc_tx_index) % fp->ring_rmc_tx_size) *
	     FZA_TX_BUFFER_SIZE) >= dev->mtu + dev->hard_header_len) अणु
		अगर (fp->queue_active) अणु
			netअगर_wake_queue(dev);
			pr_debug("%s: queue woken\n", fp->name);
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक fza_rx_err(काष्ठा fza_निजी *fp,
			     स्थिर u32 rmc, स्थिर u8 fc)
अणु
	पूर्णांक len, min_len, max_len;

	len = rmc & FZA_RING_PBC_MASK;

	अगर (unlikely((rmc & FZA_RING_RX_BAD) != 0)) अणु
		fp->stats.rx_errors++;

		/* Check special status codes. */
		अगर ((rmc & (FZA_RING_RX_CRC | FZA_RING_RX_RRR_MASK |
			    FZA_RING_RX_DA_MASK | FZA_RING_RX_SA_MASK)) ==
		     (FZA_RING_RX_CRC | FZA_RING_RX_RRR_DADDR |
		      FZA_RING_RX_DA_CAM | FZA_RING_RX_SA_ALIAS)) अणु
			अगर (len >= 8190)
				fp->stats.rx_length_errors++;
			वापस 1;
		पूर्ण
		अगर ((rmc & (FZA_RING_RX_CRC | FZA_RING_RX_RRR_MASK |
			    FZA_RING_RX_DA_MASK | FZA_RING_RX_SA_MASK)) ==
		     (FZA_RING_RX_CRC | FZA_RING_RX_RRR_DADDR |
		      FZA_RING_RX_DA_CAM | FZA_RING_RX_SA_CAM)) अणु
			/* Halt the पूर्णांकerface to trigger a reset. */
			ग_लिखोw_o(FZA_CONTROL_A_HALT, &fp->regs->control_a);
			पढ़ोw_o(&fp->regs->control_a);	/* Synchronize. */
			वापस 1;
		पूर्ण

		/* Check the MAC status. */
		चयन (rmc & FZA_RING_RX_RRR_MASK) अणु
		हाल FZA_RING_RX_RRR_OK:
			अगर ((rmc & FZA_RING_RX_CRC) != 0)
				fp->stats.rx_crc_errors++;
			अन्यथा अगर ((rmc & FZA_RING_RX_FSC_MASK) == 0 ||
				 (rmc & FZA_RING_RX_FSB_ERR) != 0)
				fp->stats.rx_frame_errors++;
			वापस 1;
		हाल FZA_RING_RX_RRR_SADDR:
		हाल FZA_RING_RX_RRR_DADDR:
		हाल FZA_RING_RX_RRR_ABORT:
			/* Halt the पूर्णांकerface to trigger a reset. */
			ग_लिखोw_o(FZA_CONTROL_A_HALT, &fp->regs->control_a);
			पढ़ोw_o(&fp->regs->control_a);	/* Synchronize. */
			वापस 1;
		हाल FZA_RING_RX_RRR_LENGTH:
			fp->stats.rx_frame_errors++;
			वापस 1;
		शेष:
			वापस 1;
		पूर्ण
	पूर्ण

	/* Packet received successfully; validate the length. */
	चयन (fc & FDDI_FC_K_FORMAT_MASK) अणु
	हाल FDDI_FC_K_FORMAT_MANAGEMENT:
		अगर ((fc & FDDI_FC_K_CLASS_MASK) == FDDI_FC_K_CLASS_ASYNC)
			min_len = 37;
		अन्यथा
			min_len = 17;
		अवरोध;
	हाल FDDI_FC_K_FORMAT_LLC:
		min_len = 20;
		अवरोध;
	शेष:
		min_len = 17;
		अवरोध;
	पूर्ण
	max_len = 4495;
	अगर (len < min_len || len > max_len) अणु
		fp->stats.rx_errors++;
		fp->stats.rx_length_errors++;
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम fza_rx(काष्ठा net_device *dev)
अणु
	काष्ठा fza_निजी *fp = netdev_priv(dev);
	काष्ठा sk_buff *skb, *newskb;
	काष्ठा fza_fddihdr *frame;
	dma_addr_t dma, newdma;
	u32 own, rmc, buf;
	पूर्णांक i, len;
	u8 fc;

	जबतक (1) अणु
		i = fp->ring_hst_rx_index;
		own = पढ़ोl_o(&fp->ring_hst_rx[i].buf0_own);
		अगर ((own & FZA_RING_OWN_MASK) == FZA_RING_OWN_FZA)
			अवरोध;

		rmc = पढ़ोl_u(&fp->ring_hst_rx[i].rmc);
		skb = fp->rx_skbuff[i];
		dma = fp->rx_dma[i];

		/* The RMC करोesn't count the preamble and the starting
		 * delimiter.  We fix it up here क्रम a total of 3 octets.
		 */
		dma_rmb();
		len = (rmc & FZA_RING_PBC_MASK) + 3;
		frame = (काष्ठा fza_fddihdr *)skb->data;

		/* We need to get at real FC. */
		dma_sync_single_क्रम_cpu(fp->bdev,
					dma +
					((u8 *)&frame->hdr.fc - (u8 *)frame),
					माप(frame->hdr.fc),
					DMA_FROM_DEVICE);
		fc = frame->hdr.fc;

		अगर (fza_rx_err(fp, rmc, fc))
			जाओ err_rx;

		/* We have to 512-byte-align RX buffers... */
		newskb = fza_alloc_skb_irq(dev, FZA_RX_BUFFER_SIZE + 511);
		अगर (newskb) अणु
			fza_skb_align(newskb, 512);
			newdma = dma_map_single(fp->bdev, newskb->data,
						FZA_RX_BUFFER_SIZE,
						DMA_FROM_DEVICE);
			अगर (dma_mapping_error(fp->bdev, newdma)) अणु
				dev_kमुक्त_skb_irq(newskb);
				newskb = शून्य;
			पूर्ण
		पूर्ण
		अगर (newskb) अणु
			पूर्णांक pkt_len = len - 7;	/* Omit P, SD and FCS. */
			पूर्णांक is_multi;
			पूर्णांक rx_stat;

			dma_unmap_single(fp->bdev, dma, FZA_RX_BUFFER_SIZE,
					 DMA_FROM_DEVICE);

			/* Queue SMT frames to the SMT receive ring. */
			अगर ((fc & (FDDI_FC_K_CLASS_MASK |
				   FDDI_FC_K_FORMAT_MASK)) ==
			     (FDDI_FC_K_CLASS_ASYNC |
			      FDDI_FC_K_FORMAT_MANAGEMENT) &&
			    (rmc & FZA_RING_RX_DA_MASK) !=
			     FZA_RING_RX_DA_PROM) अणु
				अगर (fza_करो_recv_smt((काष्ठा fza_buffer_tx *)
						    skb->data, len, rmc,
						    dev)) अणु
					ग_लिखोl_o(FZA_CONTROL_A_SMT_RX_OVFL,
						 &fp->regs->control_a);
				पूर्ण
			पूर्ण

			is_multi = ((frame->hdr.daddr[0] & 0x01) != 0);

			skb_reserve(skb, 3);	/* Skip over P and SD. */
			skb_put(skb, pkt_len);	/* And cut off FCS. */
			skb->protocol = fddi_type_trans(skb, dev);

			rx_stat = netअगर_rx(skb);
			अगर (rx_stat != NET_RX_DROP) अणु
				fp->stats.rx_packets++;
				fp->stats.rx_bytes += pkt_len;
				अगर (is_multi)
					fp->stats.multicast++;
			पूर्ण अन्यथा अणु
				fp->stats.rx_dropped++;
			पूर्ण

			skb = newskb;
			dma = newdma;
			fp->rx_skbuff[i] = skb;
			fp->rx_dma[i] = dma;
		पूर्ण अन्यथा अणु
			fp->stats.rx_dropped++;
			pr_notice("%s: memory squeeze, dropping packet\n",
				  fp->name);
		पूर्ण

err_rx:
		ग_लिखोl_o(0, &fp->ring_hst_rx[i].rmc);
		buf = (dma + 0x1000) >> 9;
		ग_लिखोl_o(buf, &fp->ring_hst_rx[i].buffer1);
		buf = dma >> 9 | FZA_RING_OWN_FZA;
		ग_लिखोl_o(buf, &fp->ring_hst_rx[i].buf0_own);
		fp->ring_hst_rx_index =
			(fp->ring_hst_rx_index + 1) % fp->ring_hst_rx_size;
	पूर्ण
पूर्ण

अटल व्योम fza_tx_smt(काष्ठा net_device *dev)
अणु
	काष्ठा fza_निजी *fp = netdev_priv(dev);
	काष्ठा fza_buffer_tx __iomem *smt_tx_ptr;
	पूर्णांक i, len;
	u32 own;

	जबतक (1) अणु
		i = fp->ring_smt_tx_index;
		own = पढ़ोl_o(&fp->ring_smt_tx[i].own);
		अगर ((own & FZA_RING_OWN_MASK) == FZA_RING_OWN_FZA)
			अवरोध;

		smt_tx_ptr = fp->mmio + पढ़ोl_u(&fp->ring_smt_tx[i].buffer);
		len = पढ़ोl_u(&fp->ring_smt_tx[i].rmc) & FZA_RING_PBC_MASK;

		अगर (!netअगर_queue_stopped(dev)) अणु
			अगर (dev_nit_active(dev)) अणु
				काष्ठा fza_buffer_tx *skb_data_ptr;
				काष्ठा sk_buff *skb;

				/* Length must be a multiple of 4 as only word
				 * पढ़ोs are permitted!
				 */
				skb = fza_alloc_skb_irq(dev, (len + 3) & ~3);
				अगर (!skb)
					जाओ err_no_skb;	/* Drop. */

				skb_data_ptr = (काष्ठा fza_buffer_tx *)
					       skb->data;

				fza_पढ़ोs(smt_tx_ptr, skb_data_ptr,
					  (len + 3) & ~3);
				skb->dev = dev;
				skb_reserve(skb, 3);	/* Skip over PRH. */
				skb_put(skb, len - 3);
				skb_reset_network_header(skb);

				dev_queue_xmit_nit(skb, dev);

				dev_kमुक्त_skb_irq(skb);

err_no_skb:
				;
			पूर्ण

			/* Queue the frame to the RMC transmit ring. */
			fza_करो_xmit((जोड़ fza_buffer_txp)
				    अणु .mmio_ptr = smt_tx_ptr पूर्ण,
				    len, dev, 1);
		पूर्ण

		ग_लिखोl_o(FZA_RING_OWN_FZA, &fp->ring_smt_tx[i].own);
		fp->ring_smt_tx_index =
			(fp->ring_smt_tx_index + 1) % fp->ring_smt_tx_size;
	पूर्ण
पूर्ण

अटल व्योम fza_uns(काष्ठा net_device *dev)
अणु
	काष्ठा fza_निजी *fp = netdev_priv(dev);
	u32 own;
	पूर्णांक i;

	जबतक (1) अणु
		i = fp->ring_uns_index;
		own = पढ़ोl_o(&fp->ring_uns[i].own);
		अगर ((own & FZA_RING_OWN_MASK) == FZA_RING_OWN_FZA)
			अवरोध;

		अगर (पढ़ोl_u(&fp->ring_uns[i].id) == FZA_RING_UNS_RX_OVER) अणु
			fp->stats.rx_errors++;
			fp->stats.rx_over_errors++;
		पूर्ण

		ग_लिखोl_o(FZA_RING_OWN_FZA, &fp->ring_uns[i].own);
		fp->ring_uns_index =
			(fp->ring_uns_index + 1) % FZA_RING_UNS_SIZE;
	पूर्ण
पूर्ण

अटल व्योम fza_tx_flush(काष्ठा net_device *dev)
अणु
	काष्ठा fza_निजी *fp = netdev_priv(dev);
	u32 own;
	पूर्णांक i;

	/* Clean up the SMT TX ring. */
	i = fp->ring_smt_tx_index;
	करो अणु
		ग_लिखोl_o(FZA_RING_OWN_FZA, &fp->ring_smt_tx[i].own);
		fp->ring_smt_tx_index =
			(fp->ring_smt_tx_index + 1) % fp->ring_smt_tx_size;

	पूर्ण जबतक (i != fp->ring_smt_tx_index);

	/* Clean up the RMC TX ring. */
	i = fp->ring_rmc_tx_index;
	करो अणु
		own = पढ़ोl_o(&fp->ring_rmc_tx[i].own);
		अगर ((own & FZA_RING_OWN_MASK) == FZA_RING_TX_OWN_RMC) अणु
			u32 rmc = पढ़ोl_u(&fp->ring_rmc_tx[i].rmc);

			ग_लिखोl_u(rmc | FZA_RING_TX_DTP,
				 &fp->ring_rmc_tx[i].rmc);
		पूर्ण
		fp->ring_rmc_tx_index =
			(fp->ring_rmc_tx_index + 1) % fp->ring_rmc_tx_size;

	पूर्ण जबतक (i != fp->ring_rmc_tx_index);

	/* Done. */
	ग_लिखोw_o(FZA_CONTROL_A_FLUSH_DONE, &fp->regs->control_a);
पूर्ण

अटल irqवापस_t fza_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा fza_निजी *fp = netdev_priv(dev);
	uपूर्णांक पूर्णांक_event;

	/* Get पूर्णांकerrupt events. */
	पूर्णांक_event = पढ़ोw_o(&fp->regs->पूर्णांक_event) & fp->पूर्णांक_mask;
	अगर (पूर्णांक_event == 0)
		वापस IRQ_NONE;

	/* Clear the events. */
	ग_लिखोw_u(पूर्णांक_event, &fp->regs->पूर्णांक_event);

	/* Now handle the events.  The order matters. */

	/* Command finished पूर्णांकerrupt. */
	अगर ((पूर्णांक_event & FZA_EVENT_CMD_DONE) != 0) अणु
		fp->irq_count_cmd_करोne++;

		spin_lock(&fp->lock);
		fp->cmd_करोne_flag = 1;
		wake_up(&fp->cmd_करोne_रुको);
		spin_unlock(&fp->lock);
	पूर्ण

	/* Transmit finished पूर्णांकerrupt. */
	अगर ((पूर्णांक_event & FZA_EVENT_TX_DONE) != 0) अणु
		fp->irq_count_tx_करोne++;
		fza_tx(dev);
	पूर्ण

	/* Host receive पूर्णांकerrupt. */
	अगर ((पूर्णांक_event & FZA_EVENT_RX_POLL) != 0) अणु
		fp->irq_count_rx_poll++;
		fza_rx(dev);
	पूर्ण

	/* SMT transmit पूर्णांकerrupt. */
	अगर ((पूर्णांक_event & FZA_EVENT_SMT_TX_POLL) != 0) अणु
		fp->irq_count_smt_tx_poll++;
		fza_tx_smt(dev);
	पूर्ण

	/* Transmit ring flush request. */
	अगर ((पूर्णांक_event & FZA_EVENT_FLUSH_TX) != 0) अणु
		fp->irq_count_flush_tx++;
		fza_tx_flush(dev);
	पूर्ण

	/* Link status change पूर्णांकerrupt. */
	अगर ((पूर्णांक_event & FZA_EVENT_LINK_ST_CHG) != 0) अणु
		uपूर्णांक status;

		fp->irq_count_link_st_chg++;
		status = पढ़ोw_u(&fp->regs->status);
		अगर (FZA_STATUS_GET_LINK(status) == FZA_LINK_ON) अणु
			netअगर_carrier_on(dev);
			pr_info("%s: link available\n", fp->name);
		पूर्ण अन्यथा अणु
			netअगर_carrier_off(dev);
			pr_info("%s: link unavailable\n", fp->name);
		पूर्ण
	पूर्ण

	/* Unsolicited event पूर्णांकerrupt. */
	अगर ((पूर्णांक_event & FZA_EVENT_UNS_POLL) != 0) अणु
		fp->irq_count_uns_poll++;
		fza_uns(dev);
	पूर्ण

	/* State change पूर्णांकerrupt. */
	अगर ((पूर्णांक_event & FZA_EVENT_STATE_CHG) != 0) अणु
		uपूर्णांक status, state;

		fp->irq_count_state_chg++;

		status = पढ़ोw_u(&fp->regs->status);
		state = FZA_STATUS_GET_STATE(status);
		pr_debug("%s: state change: %x\n", fp->name, state);
		चयन (state) अणु
		हाल FZA_STATE_RESET:
			अवरोध;

		हाल FZA_STATE_UNINITIALIZED:
			netअगर_carrier_off(dev);
			del_समयr_sync(&fp->reset_समयr);
			fp->ring_cmd_index = 0;
			fp->ring_uns_index = 0;
			fp->ring_rmc_tx_index = 0;
			fp->ring_rmc_txd_index = 0;
			fp->ring_hst_rx_index = 0;
			fp->ring_smt_tx_index = 0;
			fp->ring_smt_rx_index = 0;
			अगर (fp->state > state) अणु
				pr_info("%s: OK\n", fp->name);
				fza_cmd_send(dev, FZA_RING_CMD_INIT);
			पूर्ण
			अवरोध;

		हाल FZA_STATE_INITIALIZED:
			अगर (fp->state > state) अणु
				fza_set_rx_mode(dev);
				fza_cmd_send(dev, FZA_RING_CMD_PARAM);
			पूर्ण
			अवरोध;

		हाल FZA_STATE_RUNNING:
		हाल FZA_STATE_MAINTEन_अंकCE:
			fp->state = state;
			fza_rx_init(fp);
			fp->queue_active = 1;
			netअगर_wake_queue(dev);
			pr_debug("%s: queue woken\n", fp->name);
			अवरोध;

		हाल FZA_STATE_HALTED:
			fp->queue_active = 0;
			netअगर_stop_queue(dev);
			pr_debug("%s: queue stopped\n", fp->name);
			del_समयr_sync(&fp->reset_समयr);
			pr_warn("%s: halted, reason: %x\n", fp->name,
				FZA_STATUS_GET_HALT(status));
			fza_regs_dump(fp);
			pr_info("%s: resetting the board...\n", fp->name);
			fza_करो_reset(fp);
			fp->समयr_state = 0;
			fp->reset_समयr.expires = jअगरfies + 45 * HZ;
			add_समयr(&fp->reset_समयr);
			अवरोध;

		शेष:
			pr_warn("%s: undefined state: %x\n", fp->name, state);
			अवरोध;
		पूर्ण

		spin_lock(&fp->lock);
		fp->state_chg_flag = 1;
		wake_up(&fp->state_chg_रुको);
		spin_unlock(&fp->lock);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम fza_reset_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा fza_निजी *fp = from_समयr(fp, t, reset_समयr);

	अगर (!fp->समयr_state) अणु
		pr_err("%s: RESET timed out!\n", fp->name);
		pr_info("%s: trying harder...\n", fp->name);

		/* Assert the board reset. */
		ग_लिखोw_o(FZA_RESET_INIT, &fp->regs->reset);
		पढ़ोw_o(&fp->regs->reset);		/* Synchronize. */

		fp->समयr_state = 1;
		fp->reset_समयr.expires = jअगरfies + HZ;
	पूर्ण अन्यथा अणु
		/* Clear the board reset. */
		ग_लिखोw_u(FZA_RESET_CLR, &fp->regs->reset);

		/* Enable all पूर्णांकerrupt events we handle. */
		ग_लिखोw_o(fp->पूर्णांक_mask, &fp->regs->पूर्णांक_mask);
		पढ़ोw_o(&fp->regs->पूर्णांक_mask);		/* Synchronize. */

		fp->समयr_state = 0;
		fp->reset_समयr.expires = jअगरfies + 45 * HZ;
	पूर्ण
	add_समयr(&fp->reset_समयr);
पूर्ण

अटल पूर्णांक fza_set_mac_address(काष्ठा net_device *dev, व्योम *addr)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल netdev_tx_t fza_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा fza_निजी *fp = netdev_priv(dev);
	अचिन्हित पूर्णांक old_mask, new_mask;
	पूर्णांक ret;
	u8 fc;

	skb_push(skb, 3);			/* Make room क्रम PRH. */

	/* Decode FC to set PRH. */
	fc = skb->data[3];
	skb->data[0] = 0;
	skb->data[1] = 0;
	skb->data[2] = FZA_PRH2_NORMAL;
	अगर ((fc & FDDI_FC_K_CLASS_MASK) == FDDI_FC_K_CLASS_SYNC)
		skb->data[0] |= FZA_PRH0_FRAME_SYNC;
	चयन (fc & FDDI_FC_K_FORMAT_MASK) अणु
	हाल FDDI_FC_K_FORMAT_MANAGEMENT:
		अगर ((fc & FDDI_FC_K_CONTROL_MASK) == 0) अणु
			/* Token. */
			skb->data[0] |= FZA_PRH0_TKN_TYPE_IMM;
			skb->data[1] |= FZA_PRH1_TKN_SEND_NONE;
		पूर्ण अन्यथा अणु
			/* SMT or MAC. */
			skb->data[0] |= FZA_PRH0_TKN_TYPE_UNR;
			skb->data[1] |= FZA_PRH1_TKN_SEND_UNR;
		पूर्ण
		skb->data[1] |= FZA_PRH1_CRC_NORMAL;
		अवरोध;
	हाल FDDI_FC_K_FORMAT_LLC:
	हाल FDDI_FC_K_FORMAT_FUTURE:
		skb->data[0] |= FZA_PRH0_TKN_TYPE_UNR;
		skb->data[1] |= FZA_PRH1_CRC_NORMAL | FZA_PRH1_TKN_SEND_UNR;
		अवरोध;
	हाल FDDI_FC_K_FORMAT_IMPLEMENTOR:
		skb->data[0] |= FZA_PRH0_TKN_TYPE_UNR;
		skb->data[1] |= FZA_PRH1_TKN_SEND_ORIG;
		अवरोध;
	पूर्ण

	/* SMT transmit पूर्णांकerrupts may sneak frames पूर्णांकo the RMC
	 * transmit ring.  We disable them जबतक queueing a frame
	 * to मुख्यtain consistency.
	 */
	old_mask = fp->पूर्णांक_mask;
	new_mask = old_mask & ~FZA_MASK_SMT_TX_POLL;
	ग_लिखोw_u(new_mask, &fp->regs->पूर्णांक_mask);
	पढ़ोw_o(&fp->regs->पूर्णांक_mask);			/* Synchronize. */
	fp->पूर्णांक_mask = new_mask;
	ret = fza_करो_xmit((जोड़ fza_buffer_txp)
			  अणु .data_ptr = (काष्ठा fza_buffer_tx *)skb->data पूर्ण,
			  skb->len, dev, 0);
	fp->पूर्णांक_mask = old_mask;
	ग_लिखोw_u(fp->पूर्णांक_mask, &fp->regs->पूर्णांक_mask);

	अगर (ret) अणु
		/* Probably an SMT packet filled the reमुख्यing space,
		 * so just stop the queue, but करोn't report it as an error.
		 */
		netअगर_stop_queue(dev);
		pr_debug("%s: queue stopped\n", fp->name);
		fp->stats.tx_dropped++;
	पूर्ण

	dev_kमुक्त_skb(skb);

	वापस ret;
पूर्ण

अटल पूर्णांक fza_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा fza_निजी *fp = netdev_priv(dev);
	काष्ठा fza_ring_cmd __iomem *ring;
	काष्ठा sk_buff *skb;
	अचिन्हित दीर्घ flags;
	dma_addr_t dma;
	पूर्णांक ret, i;
	u32 stat;
	दीर्घ t;

	क्रम (i = 0; i < FZA_RING_RX_SIZE; i++) अणु
		/* We have to 512-byte-align RX buffers... */
		skb = fza_alloc_skb(dev, FZA_RX_BUFFER_SIZE + 511);
		अगर (skb) अणु
			fza_skb_align(skb, 512);
			dma = dma_map_single(fp->bdev, skb->data,
					     FZA_RX_BUFFER_SIZE,
					     DMA_FROM_DEVICE);
			अगर (dma_mapping_error(fp->bdev, dma)) अणु
				dev_kमुक्त_skb(skb);
				skb = शून्य;
			पूर्ण
		पूर्ण
		अगर (!skb) अणु
			क्रम (--i; i >= 0; i--) अणु
				dma_unmap_single(fp->bdev, fp->rx_dma[i],
						 FZA_RX_BUFFER_SIZE,
						 DMA_FROM_DEVICE);
				dev_kमुक्त_skb(fp->rx_skbuff[i]);
				fp->rx_dma[i] = 0;
				fp->rx_skbuff[i] = शून्य;
			पूर्ण
			वापस -ENOMEM;
		पूर्ण
		fp->rx_skbuff[i] = skb;
		fp->rx_dma[i] = dma;
	पूर्ण

	ret = fza_init_send(dev, शून्य);
	अगर (ret != 0)
		वापस ret;

	/* Purger and Beacon multicasts need to be supplied beक्रमe PARAM. */
	fza_set_rx_mode(dev);

	spin_lock_irqsave(&fp->lock, flags);
	fp->cmd_करोne_flag = 0;
	ring = fza_cmd_send(dev, FZA_RING_CMD_PARAM);
	spin_unlock_irqrestore(&fp->lock, flags);
	अगर (!ring)
		वापस -ENOBUFS;

	t = रुको_event_समयout(fp->cmd_करोne_रुको, fp->cmd_करोne_flag, 3 * HZ);
	अगर (fp->cmd_करोne_flag == 0) अणु
		pr_err("%s: PARAM command timed out!, state %x\n", fp->name,
		       FZA_STATUS_GET_STATE(पढ़ोw_u(&fp->regs->status)));
		वापस -EIO;
	पूर्ण
	stat = पढ़ोl_u(&ring->stat);
	अगर (stat != FZA_RING_STAT_SUCCESS) अणु
		pr_err("%s: PARAM command failed!, status %02x, state %x\n",
		       fp->name, stat,
		       FZA_STATUS_GET_STATE(पढ़ोw_u(&fp->regs->status)));
		वापस -EIO;
	पूर्ण
	pr_debug("%s: PARAM: %lums elapsed\n", fp->name,
		 (3 * HZ - t) * 1000 / HZ);

	वापस 0;
पूर्ण

अटल पूर्णांक fza_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा fza_निजी *fp = netdev_priv(dev);
	अचिन्हित दीर्घ flags;
	uपूर्णांक state;
	दीर्घ t;
	पूर्णांक i;

	netअगर_stop_queue(dev);
	pr_debug("%s: queue stopped\n", fp->name);

	del_समयr_sync(&fp->reset_समयr);
	spin_lock_irqsave(&fp->lock, flags);
	fp->state = FZA_STATE_UNINITIALIZED;
	fp->state_chg_flag = 0;
	/* Shut the पूर्णांकerface करोwn. */
	ग_लिखोw_o(FZA_CONTROL_A_SHUT, &fp->regs->control_a);
	पढ़ोw_o(&fp->regs->control_a);			/* Synchronize. */
	spin_unlock_irqrestore(&fp->lock, flags);

	/* DEC says SHUT needs up to 10 seconds to complete. */
	t = रुको_event_समयout(fp->state_chg_रुको, fp->state_chg_flag,
			       15 * HZ);
	state = FZA_STATUS_GET_STATE(पढ़ोw_o(&fp->regs->status));
	अगर (fp->state_chg_flag == 0) अणु
		pr_err("%s: SHUT timed out!, state %x\n", fp->name, state);
		वापस -EIO;
	पूर्ण
	अगर (state != FZA_STATE_UNINITIALIZED) अणु
		pr_err("%s: SHUT failed!, state %x\n", fp->name, state);
		वापस -EIO;
	पूर्ण
	pr_debug("%s: SHUT: %lums elapsed\n", fp->name,
		 (15 * HZ - t) * 1000 / HZ);

	क्रम (i = 0; i < FZA_RING_RX_SIZE; i++)
		अगर (fp->rx_skbuff[i]) अणु
			dma_unmap_single(fp->bdev, fp->rx_dma[i],
					 FZA_RX_BUFFER_SIZE, DMA_FROM_DEVICE);
			dev_kमुक्त_skb(fp->rx_skbuff[i]);
			fp->rx_dma[i] = 0;
			fp->rx_skbuff[i] = शून्य;
		पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा net_device_stats *fza_get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा fza_निजी *fp = netdev_priv(dev);

	वापस &fp->stats;
पूर्ण

अटल पूर्णांक fza_probe(काष्ठा device *bdev)
अणु
	अटल स्थिर काष्ठा net_device_ops netdev_ops = अणु
		.nकरो_खोलो = fza_खोलो,
		.nकरो_stop = fza_बंद,
		.nकरो_start_xmit = fza_start_xmit,
		.nकरो_set_rx_mode = fza_set_rx_mode,
		.nकरो_set_mac_address = fza_set_mac_address,
		.nकरो_get_stats = fza_get_stats,
	पूर्ण;
	अटल पूर्णांक version_prपूर्णांकed;
	अक्षर rom_rev[4], fw_rev[4], rmc_rev[4];
	काष्ठा tc_dev *tdev = to_tc_dev(bdev);
	काष्ठा fza_cmd_init __iomem *init;
	resource_माप_प्रकार start, len;
	काष्ठा net_device *dev;
	काष्ठा fza_निजी *fp;
	uपूर्णांक smt_ver, pmd_type;
	व्योम __iomem *mmio;
	uपूर्णांक hw_addr[2];
	पूर्णांक ret, i;

	अगर (!version_prपूर्णांकed) अणु
		pr_info("%s", version);
		version_prपूर्णांकed = 1;
	पूर्ण

	dev = alloc_fddidev(माप(*fp));
	अगर (!dev)
		वापस -ENOMEM;
	SET_NETDEV_DEV(dev, bdev);

	fp = netdev_priv(dev);
	dev_set_drvdata(bdev, dev);

	fp->bdev = bdev;
	fp->name = dev_name(bdev);

	/* Request the I/O MEM resource. */
	start = tdev->resource.start;
	len = tdev->resource.end - start + 1;
	अगर (!request_mem_region(start, len, dev_name(bdev))) अणु
		pr_err("%s: cannot reserve MMIO region\n", fp->name);
		ret = -EBUSY;
		जाओ err_out_kमुक्त;
	पूर्ण

	/* MMIO mapping setup. */
	mmio = ioremap(start, len);
	अगर (!mmio) अणु
		pr_err("%s: cannot map MMIO\n", fp->name);
		ret = -ENOMEM;
		जाओ err_out_resource;
	पूर्ण

	/* Initialize the new device काष्ठाure. */
	चयन (loopback) अणु
	हाल FZA_LOOP_NORMAL:
	हाल FZA_LOOP_INTERN:
	हाल FZA_LOOP_EXTERN:
		अवरोध;
	शेष:
		loopback = FZA_LOOP_NORMAL;
	पूर्ण

	fp->mmio = mmio;
	dev->irq = tdev->पूर्णांकerrupt;

	pr_info("%s: DEC FDDIcontroller 700 or 700-C at 0x%08llx, irq %d\n",
		fp->name, (दीर्घ दीर्घ)tdev->resource.start, dev->irq);
	pr_debug("%s: mapped at: 0x%p\n", fp->name, mmio);

	fp->regs = mmio + FZA_REG_BASE;
	fp->ring_cmd = mmio + FZA_RING_CMD;
	fp->ring_uns = mmio + FZA_RING_UNS;

	init_रुकोqueue_head(&fp->state_chg_रुको);
	init_रुकोqueue_head(&fp->cmd_करोne_रुको);
	spin_lock_init(&fp->lock);
	fp->पूर्णांक_mask = FZA_MASK_NORMAL;

	समयr_setup(&fp->reset_समयr, fza_reset_समयr, 0);

	/* Sanitize the board. */
	fza_regs_dump(fp);
	fza_करो_shutकरोwn(fp);

	ret = request_irq(dev->irq, fza_पूर्णांकerrupt, IRQF_SHARED, fp->name, dev);
	अगर (ret != 0) अणु
		pr_err("%s: unable to get IRQ %d!\n", fp->name, dev->irq);
		जाओ err_out_map;
	पूर्ण

	/* Enable the driver mode. */
	ग_लिखोw_o(FZA_CONTROL_B_DRIVER, &fp->regs->control_b);

	/* For some reason transmit करोne पूर्णांकerrupts can trigger during
	 * reset.  This aव्योमs a भागision error in the handler.
	 */
	fp->ring_rmc_tx_size = FZA_RING_TX_SIZE;

	ret = fza_reset(fp);
	अगर (ret != 0)
		जाओ err_out_irq;

	ret = fza_init_send(dev, &init);
	अगर (ret != 0)
		जाओ err_out_irq;

	fza_पढ़ोs(&init->hw_addr, &hw_addr, माप(hw_addr));
	स_नकल(dev->dev_addr, &hw_addr, FDDI_K_ALEN);

	fza_पढ़ोs(&init->rom_rev, &rom_rev, माप(rom_rev));
	fza_पढ़ोs(&init->fw_rev, &fw_rev, माप(fw_rev));
	fza_पढ़ोs(&init->rmc_rev, &rmc_rev, माप(rmc_rev));
	क्रम (i = 3; i >= 0 && rom_rev[i] == ' '; i--)
		rom_rev[i] = 0;
	क्रम (i = 3; i >= 0 && fw_rev[i] == ' '; i--)
		fw_rev[i] = 0;
	क्रम (i = 3; i >= 0 && rmc_rev[i] == ' '; i--)
		rmc_rev[i] = 0;

	fp->ring_rmc_tx = mmio + पढ़ोl_u(&init->rmc_tx);
	fp->ring_rmc_tx_size = पढ़ोl_u(&init->rmc_tx_size);
	fp->ring_hst_rx = mmio + पढ़ोl_u(&init->hst_rx);
	fp->ring_hst_rx_size = पढ़ोl_u(&init->hst_rx_size);
	fp->ring_smt_tx = mmio + पढ़ोl_u(&init->smt_tx);
	fp->ring_smt_tx_size = पढ़ोl_u(&init->smt_tx_size);
	fp->ring_smt_rx = mmio + पढ़ोl_u(&init->smt_rx);
	fp->ring_smt_rx_size = पढ़ोl_u(&init->smt_rx_size);

	fp->buffer_tx = mmio + FZA_TX_BUFFER_ADDR(पढ़ोl_u(&init->rmc_tx));

	fp->t_max = पढ़ोl_u(&init->def_t_max);
	fp->t_req = पढ़ोl_u(&init->def_t_req);
	fp->tvx = पढ़ोl_u(&init->def_tvx);
	fp->lem_threshold = पढ़ोl_u(&init->lem_threshold);
	fza_पढ़ोs(&init->def_station_id, &fp->station_id,
		  माप(fp->station_id));
	fp->rtoken_समयout = पढ़ोl_u(&init->rtoken_समयout);
	fp->ring_purger = पढ़ोl_u(&init->ring_purger);

	smt_ver = पढ़ोl_u(&init->smt_ver);
	pmd_type = पढ़ोl_u(&init->pmd_type);

	pr_debug("%s: INIT parameters:\n", fp->name);
	pr_debug("        tx_mode: %u\n", पढ़ोl_u(&init->tx_mode));
	pr_debug("    hst_rx_size: %u\n", पढ़ोl_u(&init->hst_rx_size));
	pr_debug("        rmc_rev: %.4s\n", rmc_rev);
	pr_debug("        rom_rev: %.4s\n", rom_rev);
	pr_debug("         fw_rev: %.4s\n", fw_rev);
	pr_debug("       mop_type: %u\n", पढ़ोl_u(&init->mop_type));
	pr_debug("         hst_rx: 0x%08x\n", पढ़ोl_u(&init->hst_rx));
	pr_debug("         rmc_tx: 0x%08x\n", पढ़ोl_u(&init->rmc_tx));
	pr_debug("    rmc_tx_size: %u\n", पढ़ोl_u(&init->rmc_tx_size));
	pr_debug("         smt_tx: 0x%08x\n", पढ़ोl_u(&init->smt_tx));
	pr_debug("    smt_tx_size: %u\n", पढ़ोl_u(&init->smt_tx_size));
	pr_debug("         smt_rx: 0x%08x\n", पढ़ोl_u(&init->smt_rx));
	pr_debug("    smt_rx_size: %u\n", पढ़ोl_u(&init->smt_rx_size));
	/* TC प्रणालीs are always LE, so करोn't bother swapping. */
	pr_debug("        hw_addr: 0x%02x%02x%02x%02x%02x%02x%02x%02x\n",
		 (पढ़ोl_u(&init->hw_addr[0]) >> 0) & 0xff,
		 (पढ़ोl_u(&init->hw_addr[0]) >> 8) & 0xff,
		 (पढ़ोl_u(&init->hw_addr[0]) >> 16) & 0xff,
		 (पढ़ोl_u(&init->hw_addr[0]) >> 24) & 0xff,
		 (पढ़ोl_u(&init->hw_addr[1]) >> 0) & 0xff,
		 (पढ़ोl_u(&init->hw_addr[1]) >> 8) & 0xff,
		 (पढ़ोl_u(&init->hw_addr[1]) >> 16) & 0xff,
		 (पढ़ोl_u(&init->hw_addr[1]) >> 24) & 0xff);
	pr_debug("      def_t_req: %u\n", पढ़ोl_u(&init->def_t_req));
	pr_debug("        def_tvx: %u\n", पढ़ोl_u(&init->def_tvx));
	pr_debug("      def_t_max: %u\n", पढ़ोl_u(&init->def_t_max));
	pr_debug("  lem_threshold: %u\n", पढ़ोl_u(&init->lem_threshold));
	/* Don't bother swapping, see above. */
	pr_debug(" def_station_id: 0x%02x%02x%02x%02x%02x%02x%02x%02x\n",
		 (पढ़ोl_u(&init->def_station_id[0]) >> 0) & 0xff,
		 (पढ़ोl_u(&init->def_station_id[0]) >> 8) & 0xff,
		 (पढ़ोl_u(&init->def_station_id[0]) >> 16) & 0xff,
		 (पढ़ोl_u(&init->def_station_id[0]) >> 24) & 0xff,
		 (पढ़ोl_u(&init->def_station_id[1]) >> 0) & 0xff,
		 (पढ़ोl_u(&init->def_station_id[1]) >> 8) & 0xff,
		 (पढ़ोl_u(&init->def_station_id[1]) >> 16) & 0xff,
		 (पढ़ोl_u(&init->def_station_id[1]) >> 24) & 0xff);
	pr_debug("   pmd_type_alt: %u\n", पढ़ोl_u(&init->pmd_type_alt));
	pr_debug("        smt_ver: %u\n", पढ़ोl_u(&init->smt_ver));
	pr_debug(" rtoken_timeout: %u\n", पढ़ोl_u(&init->rtoken_समयout));
	pr_debug("    ring_purger: %u\n", पढ़ोl_u(&init->ring_purger));
	pr_debug("    smt_ver_max: %u\n", पढ़ोl_u(&init->smt_ver_max));
	pr_debug("    smt_ver_min: %u\n", पढ़ोl_u(&init->smt_ver_min));
	pr_debug("       pmd_type: %u\n", पढ़ोl_u(&init->pmd_type));

	pr_info("%s: model %s, address %pMF\n",
		fp->name,
		pmd_type == FZA_PMD_TYPE_TW ?
			"700-C (DEFZA-CA), ThinWire PMD selected" :
			pmd_type == FZA_PMD_TYPE_STP ?
				"700-C (DEFZA-CA), STP PMD selected" :
				"700 (DEFZA-AA), MMF PMD",
		dev->dev_addr);
	pr_info("%s: ROM rev. %.4s, firmware rev. %.4s, RMC rev. %.4s, "
		"SMT ver. %u\n", fp->name, rom_rev, fw_rev, rmc_rev, smt_ver);

	/* Now that we fetched initial parameters just shut the पूर्णांकerface
	 * until खोलोed.
	 */
	ret = fza_बंद(dev);
	अगर (ret != 0)
		जाओ err_out_irq;

	/* The FZA-specअगरic entries in the device काष्ठाure. */
	dev->netdev_ops = &netdev_ops;

	ret = रेजिस्टर_netdev(dev);
	अगर (ret != 0)
		जाओ err_out_irq;

	pr_info("%s: registered as %s\n", fp->name, dev->name);
	fp->name = (स्थिर अक्षर *)dev->name;

	get_device(bdev);
	वापस 0;

err_out_irq:
	del_समयr_sync(&fp->reset_समयr);
	fza_करो_shutकरोwn(fp);
	मुक्त_irq(dev->irq, dev);

err_out_map:
	iounmap(mmio);

err_out_resource:
	release_mem_region(start, len);

err_out_kमुक्त:
	मुक्त_netdev(dev);

	pr_err("%s: initialization failure, aborting!\n", fp->name);
	वापस ret;
पूर्ण

अटल पूर्णांक fza_हटाओ(काष्ठा device *bdev)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(bdev);
	काष्ठा fza_निजी *fp = netdev_priv(dev);
	काष्ठा tc_dev *tdev = to_tc_dev(bdev);
	resource_माप_प्रकार start, len;

	put_device(bdev);

	unरेजिस्टर_netdev(dev);

	del_समयr_sync(&fp->reset_समयr);
	fza_करो_shutकरोwn(fp);
	मुक्त_irq(dev->irq, dev);

	iounmap(fp->mmio);

	start = tdev->resource.start;
	len = tdev->resource.end - start + 1;
	release_mem_region(start, len);

	मुक्त_netdev(dev);

	वापस 0;
पूर्ण

अटल काष्ठा tc_device_id स्थिर fza_tc_table[] = अणु
	अणु "DEC     ", "PMAF-AA " पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(tc, fza_tc_table);

अटल काष्ठा tc_driver fza_driver = अणु
	.id_table	= fza_tc_table,
	.driver		= अणु
		.name	= "defza",
		.bus	= &tc_bus_type,
		.probe	= fza_probe,
		.हटाओ	= fza_हटाओ,
	पूर्ण,
पूर्ण;

अटल पूर्णांक fza_init(व्योम)
अणु
	वापस tc_रेजिस्टर_driver(&fza_driver);
पूर्ण

अटल व्योम fza_निकास(व्योम)
अणु
	tc_unरेजिस्टर_driver(&fza_driver);
पूर्ण

module_init(fza_init);
module_निकास(fza_निकास);
