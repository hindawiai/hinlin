<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * drivers/net/ethernet/ibm/emac/mal.c
 *
 * Memory Access Layer (MAL) support
 *
 * Copyright 2007 Benjamin Herrenschmidt, IBM Corp.
 *                <benh@kernel.crashing.org>
 *
 * Based on the arch/ppc version of the driver:
 *
 * Copyright (c) 2004, 2005 Zultys Technologies.
 * Eugene Surovegin <eugene.surovegin@zultys.com> or <ebs@ebshome.net>
 *
 * Based on original work by
 *      Benjamin Herrenschmidt <benh@kernel.crashing.org>,
 *      David Gibson <hermes@gibson.dropbear.id.au>,
 *
 *      Armin Kuster <akuster@mvista.com>
 *      Copyright 2002 MontaVista Softare Inc.
 */

#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/of_irq.h>

#समावेश "core.h"
#समावेश <यंत्र/dcr-regs.h>

अटल पूर्णांक mal_count;

पूर्णांक mal_रेजिस्टर_commac(काष्ठा mal_instance *mal, काष्ठा mal_commac *commac)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mal->lock, flags);

	MAL_DBG(mal, "reg(%08x, %08x)" NL,
		commac->tx_chan_mask, commac->rx_chan_mask);

	/* Don't let multiple commacs claim the same channel(s) */
	अगर ((mal->tx_chan_mask & commac->tx_chan_mask) ||
	    (mal->rx_chan_mask & commac->rx_chan_mask)) अणु
		spin_unlock_irqrestore(&mal->lock, flags);
		prपूर्णांकk(KERN_WARNING "mal%d: COMMAC channels conflict!\n",
		       mal->index);
		वापस -EBUSY;
	पूर्ण

	अगर (list_empty(&mal->list))
		napi_enable(&mal->napi);
	mal->tx_chan_mask |= commac->tx_chan_mask;
	mal->rx_chan_mask |= commac->rx_chan_mask;
	list_add(&commac->list, &mal->list);

	spin_unlock_irqrestore(&mal->lock, flags);

	वापस 0;
पूर्ण

व्योम mal_unरेजिस्टर_commac(काष्ठा mal_instance	*mal,
		काष्ठा mal_commac *commac)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mal->lock, flags);

	MAL_DBG(mal, "unreg(%08x, %08x)" NL,
		commac->tx_chan_mask, commac->rx_chan_mask);

	mal->tx_chan_mask &= ~commac->tx_chan_mask;
	mal->rx_chan_mask &= ~commac->rx_chan_mask;
	list_del_init(&commac->list);
	अगर (list_empty(&mal->list))
		napi_disable(&mal->napi);

	spin_unlock_irqrestore(&mal->lock, flags);
पूर्ण

पूर्णांक mal_set_rcbs(काष्ठा mal_instance *mal, पूर्णांक channel, अचिन्हित दीर्घ size)
अणु
	BUG_ON(channel < 0 || channel >= mal->num_rx_chans ||
	       size > MAL_MAX_RX_SIZE);

	MAL_DBG(mal, "set_rbcs(%d, %lu)" NL, channel, size);

	अगर (size & 0xf) अणु
		prपूर्णांकk(KERN_WARNING
		       "mal%d: incorrect RX size %lu for the channel %d\n",
		       mal->index, size, channel);
		वापस -EINVAL;
	पूर्ण

	set_mal_dcrn(mal, MAL_RCBS(channel), size >> 4);
	वापस 0;
पूर्ण

पूर्णांक mal_tx_bd_offset(काष्ठा mal_instance *mal, पूर्णांक channel)
अणु
	BUG_ON(channel < 0 || channel >= mal->num_tx_chans);

	वापस channel * NUM_TX_BUFF;
पूर्ण

पूर्णांक mal_rx_bd_offset(काष्ठा mal_instance *mal, पूर्णांक channel)
अणु
	BUG_ON(channel < 0 || channel >= mal->num_rx_chans);
	वापस mal->num_tx_chans * NUM_TX_BUFF + channel * NUM_RX_BUFF;
पूर्ण

व्योम mal_enable_tx_channel(काष्ठा mal_instance *mal, पूर्णांक channel)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mal->lock, flags);

	MAL_DBG(mal, "enable_tx(%d)" NL, channel);

	set_mal_dcrn(mal, MAL_TXCASR,
		     get_mal_dcrn(mal, MAL_TXCASR) | MAL_CHAN_MASK(channel));

	spin_unlock_irqrestore(&mal->lock, flags);
पूर्ण

व्योम mal_disable_tx_channel(काष्ठा mal_instance *mal, पूर्णांक channel)
अणु
	set_mal_dcrn(mal, MAL_TXCARR, MAL_CHAN_MASK(channel));

	MAL_DBG(mal, "disable_tx(%d)" NL, channel);
पूर्ण

व्योम mal_enable_rx_channel(काष्ठा mal_instance *mal, पूर्णांक channel)
अणु
	अचिन्हित दीर्घ flags;

	/*
	 * On some 4xx PPC's (e.g. 460EX/GT), the rx channel is a multiple
	 * of 8, but enabling in MAL_RXCASR needs the भागided by 8 value
	 * क्रम the biपंचांगask
	 */
	अगर (!(channel % 8))
		channel >>= 3;

	spin_lock_irqsave(&mal->lock, flags);

	MAL_DBG(mal, "enable_rx(%d)" NL, channel);

	set_mal_dcrn(mal, MAL_RXCASR,
		     get_mal_dcrn(mal, MAL_RXCASR) | MAL_CHAN_MASK(channel));

	spin_unlock_irqrestore(&mal->lock, flags);
पूर्ण

व्योम mal_disable_rx_channel(काष्ठा mal_instance *mal, पूर्णांक channel)
अणु
	/*
	 * On some 4xx PPC's (e.g. 460EX/GT), the rx channel is a multiple
	 * of 8, but enabling in MAL_RXCASR needs the भागided by 8 value
	 * क्रम the biपंचांगask
	 */
	अगर (!(channel % 8))
		channel >>= 3;

	set_mal_dcrn(mal, MAL_RXCARR, MAL_CHAN_MASK(channel));

	MAL_DBG(mal, "disable_rx(%d)" NL, channel);
पूर्ण

व्योम mal_poll_add(काष्ठा mal_instance *mal, काष्ठा mal_commac *commac)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mal->lock, flags);

	MAL_DBG(mal, "poll_add(%p)" NL, commac);

	/* starts disabled */
	set_bit(MAL_COMMAC_POLL_DISABLED, &commac->flags);

	list_add_tail(&commac->poll_list, &mal->poll_list);

	spin_unlock_irqrestore(&mal->lock, flags);
पूर्ण

व्योम mal_poll_del(काष्ठा mal_instance *mal, काष्ठा mal_commac *commac)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mal->lock, flags);

	MAL_DBG(mal, "poll_del(%p)" NL, commac);

	list_del(&commac->poll_list);

	spin_unlock_irqrestore(&mal->lock, flags);
पूर्ण

/* synchronized by mal_poll() */
अटल अंतरभूत व्योम mal_enable_eob_irq(काष्ठा mal_instance *mal)
अणु
	MAL_DBG2(mal, "enable_irq" NL);

	// XXX might want to cache MAL_CFG as the DCR पढ़ो can be slooooow
	set_mal_dcrn(mal, MAL_CFG, get_mal_dcrn(mal, MAL_CFG) | MAL_CFG_EOPIE);
पूर्ण

/* synchronized by NAPI state */
अटल अंतरभूत व्योम mal_disable_eob_irq(काष्ठा mal_instance *mal)
अणु
	// XXX might want to cache MAL_CFG as the DCR पढ़ो can be slooooow
	set_mal_dcrn(mal, MAL_CFG, get_mal_dcrn(mal, MAL_CFG) & ~MAL_CFG_EOPIE);

	MAL_DBG2(mal, "disable_irq" NL);
पूर्ण

अटल irqवापस_t mal_serr(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा mal_instance *mal = dev_instance;

	u32 esr = get_mal_dcrn(mal, MAL_ESR);

	/* Clear the error status रेजिस्टर */
	set_mal_dcrn(mal, MAL_ESR, esr);

	MAL_DBG(mal, "SERR %08x" NL, esr);

	अगर (esr & MAL_ESR_EVB) अणु
		अगर (esr & MAL_ESR_DE) अणु
			/* We ignore Descriptor error,
			 * TXDE or RXDE पूर्णांकerrupt will be generated anyway.
			 */
			वापस IRQ_HANDLED;
		पूर्ण

		अगर (esr & MAL_ESR_PEIN) अणु
			/* PLB error, it's probably buggy hardware or
			 * incorrect physical address in BD (i.e. bug)
			 */
			अगर (net_ratelimit())
				prपूर्णांकk(KERN_ERR
				       "mal%d: system error, "
				       "PLB (ESR = 0x%08x)\n",
				       mal->index, esr);
			वापस IRQ_HANDLED;
		पूर्ण

		/* OPB error, it's probably buggy hardware or incorrect
		 * EBC setup
		 */
		अगर (net_ratelimit())
			prपूर्णांकk(KERN_ERR
			       "mal%d: system error, OPB (ESR = 0x%08x)\n",
			       mal->index, esr);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल अंतरभूत व्योम mal_schedule_poll(काष्ठा mal_instance *mal)
अणु
	अगर (likely(napi_schedule_prep(&mal->napi))) अणु
		MAL_DBG2(mal, "schedule_poll" NL);
		spin_lock(&mal->lock);
		mal_disable_eob_irq(mal);
		spin_unlock(&mal->lock);
		__napi_schedule(&mal->napi);
	पूर्ण अन्यथा
		MAL_DBG2(mal, "already in poll" NL);
पूर्ण

अटल irqवापस_t mal_txeob(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा mal_instance *mal = dev_instance;

	u32 r = get_mal_dcrn(mal, MAL_TXEOBISR);

	MAL_DBG2(mal, "txeob %08x" NL, r);

	mal_schedule_poll(mal);
	set_mal_dcrn(mal, MAL_TXEOBISR, r);

#अगर_घोषित CONFIG_PPC_DCR_NATIVE
	अगर (mal_has_feature(mal, MAL_FTR_CLEAR_ICINTSTAT))
		mtdcri(SDR0, DCRN_SDR_ICINTSTAT,
				(mfdcri(SDR0, DCRN_SDR_ICINTSTAT) | ICINTSTAT_ICTX));
#पूर्ण_अगर

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t mal_rxeob(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा mal_instance *mal = dev_instance;

	u32 r = get_mal_dcrn(mal, MAL_RXEOBISR);

	MAL_DBG2(mal, "rxeob %08x" NL, r);

	mal_schedule_poll(mal);
	set_mal_dcrn(mal, MAL_RXEOBISR, r);

#अगर_घोषित CONFIG_PPC_DCR_NATIVE
	अगर (mal_has_feature(mal, MAL_FTR_CLEAR_ICINTSTAT))
		mtdcri(SDR0, DCRN_SDR_ICINTSTAT,
				(mfdcri(SDR0, DCRN_SDR_ICINTSTAT) | ICINTSTAT_ICRX));
#पूर्ण_अगर

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t mal_txde(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा mal_instance *mal = dev_instance;

	u32 deir = get_mal_dcrn(mal, MAL_TXDEIR);
	set_mal_dcrn(mal, MAL_TXDEIR, deir);

	MAL_DBG(mal, "txde %08x" NL, deir);

	अगर (net_ratelimit())
		prपूर्णांकk(KERN_ERR
		       "mal%d: TX descriptor error (TXDEIR = 0x%08x)\n",
		       mal->index, deir);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t mal_rxde(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा mal_instance *mal = dev_instance;
	काष्ठा list_head *l;

	u32 deir = get_mal_dcrn(mal, MAL_RXDEIR);

	MAL_DBG(mal, "rxde %08x" NL, deir);

	list_क्रम_each(l, &mal->list) अणु
		काष्ठा mal_commac *mc = list_entry(l, काष्ठा mal_commac, list);
		अगर (deir & mc->rx_chan_mask) अणु
			set_bit(MAL_COMMAC_RX_STOPPED, &mc->flags);
			mc->ops->rxde(mc->dev);
		पूर्ण
	पूर्ण

	mal_schedule_poll(mal);
	set_mal_dcrn(mal, MAL_RXDEIR, deir);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t mal_पूर्णांक(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा mal_instance *mal = dev_instance;
	u32 esr = get_mal_dcrn(mal, MAL_ESR);

	अगर (esr & MAL_ESR_EVB) अणु
		/* descriptor error */
		अगर (esr & MAL_ESR_DE) अणु
			अगर (esr & MAL_ESR_CIDT)
				वापस mal_rxde(irq, dev_instance);
			अन्यथा
				वापस mal_txde(irq, dev_instance);
		पूर्ण अन्यथा अणु /* SERR */
			वापस mal_serr(irq, dev_instance);
		पूर्ण
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

व्योम mal_poll_disable(काष्ठा mal_instance *mal, काष्ठा mal_commac *commac)
अणु
	/* Spinlock-type semantics: only one caller disable poll at a समय */
	जबतक (test_and_set_bit(MAL_COMMAC_POLL_DISABLED, &commac->flags))
		msleep(1);

	/* Synchronize with the MAL NAPI poller */
	napi_synchronize(&mal->napi);
पूर्ण

व्योम mal_poll_enable(काष्ठा mal_instance *mal, काष्ठा mal_commac *commac)
अणु
	smp_wmb();
	clear_bit(MAL_COMMAC_POLL_DISABLED, &commac->flags);

	/* Feels better to trigger a poll here to catch up with events that
	 * may have happened on this channel जबतक disabled. It will most
	 * probably be delayed until the next पूर्णांकerrupt but that's mostly a
	 * non-issue in the context where this is called.
	 */
	napi_schedule(&mal->napi);
पूर्ण

अटल पूर्णांक mal_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा mal_instance *mal = container_of(napi, काष्ठा mal_instance, napi);
	काष्ठा list_head *l;
	पूर्णांक received = 0;
	अचिन्हित दीर्घ flags;

	MAL_DBG2(mal, "poll(%d)" NL, budget);

	/* Process TX skbs */
	list_क्रम_each(l, &mal->poll_list) अणु
		काष्ठा mal_commac *mc =
			list_entry(l, काष्ठा mal_commac, poll_list);
		mc->ops->poll_tx(mc->dev);
	पूर्ण

	/* Process RX skbs.
	 *
	 * We _might_ need something more smart here to enक्रमce polling
	 * fairness.
	 */
	list_क्रम_each(l, &mal->poll_list) अणु
		काष्ठा mal_commac *mc =
			list_entry(l, काष्ठा mal_commac, poll_list);
		पूर्णांक n;
		अगर (unlikely(test_bit(MAL_COMMAC_POLL_DISABLED, &mc->flags)))
			जारी;
		n = mc->ops->poll_rx(mc->dev, budget - received);
		अगर (n) अणु
			received += n;
			अगर (received >= budget)
				वापस budget;
		पूर्ण
	पूर्ण

	अगर (napi_complete_करोne(napi, received)) अणु
		/* We need to disable IRQs to protect from RXDE IRQ here */
		spin_lock_irqsave(&mal->lock, flags);
		mal_enable_eob_irq(mal);
		spin_unlock_irqrestore(&mal->lock, flags);
	पूर्ण

	/* Check क्रम "rotting" packet(s) */
	list_क्रम_each(l, &mal->poll_list) अणु
		काष्ठा mal_commac *mc =
			list_entry(l, काष्ठा mal_commac, poll_list);
		अगर (unlikely(test_bit(MAL_COMMAC_POLL_DISABLED, &mc->flags)))
			जारी;
		अगर (unlikely(mc->ops->peek_rx(mc->dev) ||
			     test_bit(MAL_COMMAC_RX_STOPPED, &mc->flags))) अणु
			MAL_DBG2(mal, "rotting packet" NL);
			अगर (!napi_reschedule(napi))
				जाओ more_work;

			spin_lock_irqsave(&mal->lock, flags);
			mal_disable_eob_irq(mal);
			spin_unlock_irqrestore(&mal->lock, flags);
		पूर्ण
		mc->ops->poll_tx(mc->dev);
	पूर्ण

 more_work:
	MAL_DBG2(mal, "poll() %d <- %d" NL, budget, received);
	वापस received;
पूर्ण

अटल व्योम mal_reset(काष्ठा mal_instance *mal)
अणु
	पूर्णांक n = 10;

	MAL_DBG(mal, "reset" NL);

	set_mal_dcrn(mal, MAL_CFG, MAL_CFG_SR);

	/* Wait क्रम reset to complete (1 प्रणाली घड़ी) */
	जबतक ((get_mal_dcrn(mal, MAL_CFG) & MAL_CFG_SR) && n)
		--n;

	अगर (unlikely(!n))
		prपूर्णांकk(KERN_ERR "mal%d: reset timeout\n", mal->index);
पूर्ण

पूर्णांक mal_get_regs_len(काष्ठा mal_instance *mal)
अणु
	वापस माप(काष्ठा emac_ethtool_regs_subhdr) +
	    माप(काष्ठा mal_regs);
पूर्ण

व्योम *mal_dump_regs(काष्ठा mal_instance *mal, व्योम *buf)
अणु
	काष्ठा emac_ethtool_regs_subhdr *hdr = buf;
	काष्ठा mal_regs *regs = (काष्ठा mal_regs *)(hdr + 1);
	पूर्णांक i;

	hdr->version = mal->version;
	hdr->index = mal->index;

	regs->tx_count = mal->num_tx_chans;
	regs->rx_count = mal->num_rx_chans;

	regs->cfg = get_mal_dcrn(mal, MAL_CFG);
	regs->esr = get_mal_dcrn(mal, MAL_ESR);
	regs->ier = get_mal_dcrn(mal, MAL_IER);
	regs->tx_casr = get_mal_dcrn(mal, MAL_TXCASR);
	regs->tx_carr = get_mal_dcrn(mal, MAL_TXCARR);
	regs->tx_eobisr = get_mal_dcrn(mal, MAL_TXEOBISR);
	regs->tx_deir = get_mal_dcrn(mal, MAL_TXDEIR);
	regs->rx_casr = get_mal_dcrn(mal, MAL_RXCASR);
	regs->rx_carr = get_mal_dcrn(mal, MAL_RXCARR);
	regs->rx_eobisr = get_mal_dcrn(mal, MAL_RXEOBISR);
	regs->rx_deir = get_mal_dcrn(mal, MAL_RXDEIR);

	क्रम (i = 0; i < regs->tx_count; ++i)
		regs->tx_ctpr[i] = get_mal_dcrn(mal, MAL_TXCTPR(i));

	क्रम (i = 0; i < regs->rx_count; ++i) अणु
		regs->rx_ctpr[i] = get_mal_dcrn(mal, MAL_RXCTPR(i));
		regs->rcbs[i] = get_mal_dcrn(mal, MAL_RCBS(i));
	पूर्ण
	वापस regs + 1;
पूर्ण

अटल पूर्णांक mal_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा mal_instance *mal;
	पूर्णांक err = 0, i, bd_size;
	पूर्णांक index = mal_count++;
	अचिन्हित पूर्णांक dcr_base;
	स्थिर u32 *prop;
	u32 cfg;
	अचिन्हित दीर्घ irqflags;
	irq_handler_t hdlr_serr, hdlr_txde, hdlr_rxde;

	mal = kzalloc(माप(काष्ठा mal_instance), GFP_KERNEL);
	अगर (!mal)
		वापस -ENOMEM;

	mal->index = index;
	mal->ofdev = ofdev;
	mal->version = of_device_is_compatible(ofdev->dev.of_node, "ibm,mcmal2") ? 2 : 1;

	MAL_DBG(mal, "probe" NL);

	prop = of_get_property(ofdev->dev.of_node, "num-tx-chans", शून्य);
	अगर (prop == शून्य) अणु
		prपूर्णांकk(KERN_ERR
		       "mal%d: can't find MAL num-tx-chans property!\n",
		       index);
		err = -ENODEV;
		जाओ fail;
	पूर्ण
	mal->num_tx_chans = prop[0];

	prop = of_get_property(ofdev->dev.of_node, "num-rx-chans", शून्य);
	अगर (prop == शून्य) अणु
		prपूर्णांकk(KERN_ERR
		       "mal%d: can't find MAL num-rx-chans property!\n",
		       index);
		err = -ENODEV;
		जाओ fail;
	पूर्ण
	mal->num_rx_chans = prop[0];

	dcr_base = dcr_resource_start(ofdev->dev.of_node, 0);
	अगर (dcr_base == 0) अणु
		prपूर्णांकk(KERN_ERR
		       "mal%d: can't find DCR resource!\n", index);
		err = -ENODEV;
		जाओ fail;
	पूर्ण
	mal->dcr_host = dcr_map(ofdev->dev.of_node, dcr_base, 0x100);
	अगर (!DCR_MAP_OK(mal->dcr_host)) अणु
		prपूर्णांकk(KERN_ERR
		       "mal%d: failed to map DCRs !\n", index);
		err = -ENODEV;
		जाओ fail;
	पूर्ण

	अगर (of_device_is_compatible(ofdev->dev.of_node, "ibm,mcmal-405ez")) अणु
#अगर defined(CONFIG_IBM_EMAC_MAL_CLR_ICINTSTAT) && \
		defined(CONFIG_IBM_EMAC_MAL_COMMON_ERR)
		mal->features |= (MAL_FTR_CLEAR_ICINTSTAT |
				MAL_FTR_COMMON_ERR_INT);
#अन्यथा
		prपूर्णांकk(KERN_ERR "%pOF: Support for 405EZ not enabled!\n",
				ofdev->dev.of_node);
		err = -ENODEV;
		जाओ fail;
#पूर्ण_अगर
	पूर्ण

	mal->txeob_irq = irq_of_parse_and_map(ofdev->dev.of_node, 0);
	mal->rxeob_irq = irq_of_parse_and_map(ofdev->dev.of_node, 1);
	mal->serr_irq = irq_of_parse_and_map(ofdev->dev.of_node, 2);

	अगर (mal_has_feature(mal, MAL_FTR_COMMON_ERR_INT)) अणु
		mal->txde_irq = mal->rxde_irq = mal->serr_irq;
	पूर्ण अन्यथा अणु
		mal->txde_irq = irq_of_parse_and_map(ofdev->dev.of_node, 3);
		mal->rxde_irq = irq_of_parse_and_map(ofdev->dev.of_node, 4);
	पूर्ण

	अगर (!mal->txeob_irq || !mal->rxeob_irq || !mal->serr_irq ||
	    !mal->txde_irq  || !mal->rxde_irq) अणु
		prपूर्णांकk(KERN_ERR
		       "mal%d: failed to map interrupts !\n", index);
		err = -ENODEV;
		जाओ fail_unmap;
	पूर्ण

	INIT_LIST_HEAD(&mal->poll_list);
	INIT_LIST_HEAD(&mal->list);
	spin_lock_init(&mal->lock);

	init_dummy_netdev(&mal->dummy_dev);

	netअगर_napi_add(&mal->dummy_dev, &mal->napi, mal_poll,
		       CONFIG_IBM_EMAC_POLL_WEIGHT);

	/* Load घातer-on reset शेषs */
	mal_reset(mal);

	/* Set the MAL configuration रेजिस्टर */
	cfg = (mal->version == 2) ? MAL2_CFG_DEFAULT : MAL1_CFG_DEFAULT;
	cfg |= MAL_CFG_PLBB | MAL_CFG_OPBBL | MAL_CFG_LEA;

	/* Current Axon is not happy with priority being non-0, it can
	 * deadlock, fix it up here
	 */
	अगर (of_device_is_compatible(ofdev->dev.of_node, "ibm,mcmal-axon"))
		cfg &= ~(MAL2_CFG_RPP_10 | MAL2_CFG_WPP_10);

	/* Apply configuration */
	set_mal_dcrn(mal, MAL_CFG, cfg);

	/* Allocate space क्रम BD rings */
	BUG_ON(mal->num_tx_chans <= 0 || mal->num_tx_chans > 32);
	BUG_ON(mal->num_rx_chans <= 0 || mal->num_rx_chans > 32);

	bd_size = माप(काष्ठा mal_descriptor) *
		(NUM_TX_BUFF * mal->num_tx_chans +
		 NUM_RX_BUFF * mal->num_rx_chans);
	mal->bd_virt = dma_alloc_coherent(&ofdev->dev, bd_size, &mal->bd_dma,
					  GFP_KERNEL);
	अगर (mal->bd_virt == शून्य) अणु
		err = -ENOMEM;
		जाओ fail_unmap;
	पूर्ण

	क्रम (i = 0; i < mal->num_tx_chans; ++i)
		set_mal_dcrn(mal, MAL_TXCTPR(i), mal->bd_dma +
			     माप(काष्ठा mal_descriptor) *
			     mal_tx_bd_offset(mal, i));

	क्रम (i = 0; i < mal->num_rx_chans; ++i)
		set_mal_dcrn(mal, MAL_RXCTPR(i), mal->bd_dma +
			     माप(काष्ठा mal_descriptor) *
			     mal_rx_bd_offset(mal, i));

	अगर (mal_has_feature(mal, MAL_FTR_COMMON_ERR_INT)) अणु
		irqflags = IRQF_SHARED;
		hdlr_serr = hdlr_txde = hdlr_rxde = mal_पूर्णांक;
	पूर्ण अन्यथा अणु
		irqflags = 0;
		hdlr_serr = mal_serr;
		hdlr_txde = mal_txde;
		hdlr_rxde = mal_rxde;
	पूर्ण

	err = request_irq(mal->serr_irq, hdlr_serr, irqflags, "MAL SERR", mal);
	अगर (err)
		जाओ fail2;
	err = request_irq(mal->txde_irq, hdlr_txde, irqflags, "MAL TX DE", mal);
	अगर (err)
		जाओ fail3;
	err = request_irq(mal->txeob_irq, mal_txeob, 0, "MAL TX EOB", mal);
	अगर (err)
		जाओ fail4;
	err = request_irq(mal->rxde_irq, hdlr_rxde, irqflags, "MAL RX DE", mal);
	अगर (err)
		जाओ fail5;
	err = request_irq(mal->rxeob_irq, mal_rxeob, 0, "MAL RX EOB", mal);
	अगर (err)
		जाओ fail6;

	/* Enable all MAL SERR पूर्णांकerrupt sources */
	set_mal_dcrn(mal, MAL_IER, MAL_IER_EVENTS);

	/* Enable EOB पूर्णांकerrupt */
	mal_enable_eob_irq(mal);

	prपूर्णांकk(KERN_INFO
	       "MAL v%d %pOF, %d TX channels, %d RX channels\n",
	       mal->version, ofdev->dev.of_node,
	       mal->num_tx_chans, mal->num_rx_chans);

	/* Advertise this instance to the rest of the world */
	wmb();
	platक्रमm_set_drvdata(ofdev, mal);

	वापस 0;

 fail6:
	मुक्त_irq(mal->rxde_irq, mal);
 fail5:
	मुक्त_irq(mal->txeob_irq, mal);
 fail4:
	मुक्त_irq(mal->txde_irq, mal);
 fail3:
	मुक्त_irq(mal->serr_irq, mal);
 fail2:
	dma_मुक्त_coherent(&ofdev->dev, bd_size, mal->bd_virt, mal->bd_dma);
 fail_unmap:
	dcr_unmap(mal->dcr_host, 0x100);
 fail:
	kमुक्त(mal);

	वापस err;
पूर्ण

अटल पूर्णांक mal_हटाओ(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा mal_instance *mal = platक्रमm_get_drvdata(ofdev);

	MAL_DBG(mal, "remove" NL);

	/* Synchronize with scheduled polling */
	napi_disable(&mal->napi);

	अगर (!list_empty(&mal->list))
		/* This is *very* bad */
		WARN(1, KERN_EMERG
		       "mal%d: commac list is not empty on remove!\n",
		       mal->index);

	मुक्त_irq(mal->serr_irq, mal);
	मुक्त_irq(mal->txde_irq, mal);
	मुक्त_irq(mal->txeob_irq, mal);
	मुक्त_irq(mal->rxde_irq, mal);
	मुक्त_irq(mal->rxeob_irq, mal);

	mal_reset(mal);

	dma_मुक्त_coherent(&ofdev->dev,
			  माप(काष्ठा mal_descriptor) *
			  (NUM_TX_BUFF * mal->num_tx_chans +
			   NUM_RX_BUFF * mal->num_rx_chans), mal->bd_virt,
			  mal->bd_dma);
	kमुक्त(mal);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mal_platक्रमm_match[] =
अणु
	अणु
		.compatible	= "ibm,mcmal",
	पूर्ण,
	अणु
		.compatible	= "ibm,mcmal2",
	पूर्ण,
	/* Backward compat */
	अणु
		.type		= "mcmal-dma",
		.compatible	= "ibm,mcmal",
	पूर्ण,
	अणु
		.type		= "mcmal-dma",
		.compatible	= "ibm,mcmal2",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver mal_of_driver = अणु
	.driver = अणु
		.name = "mcmal",
		.of_match_table = mal_platक्रमm_match,
	पूर्ण,
	.probe = mal_probe,
	.हटाओ = mal_हटाओ,
पूर्ण;

पूर्णांक __init mal_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&mal_of_driver);
पूर्ण

व्योम mal_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&mal_of_driver);
पूर्ण
