<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * drivers/net/ethernet/ibm/emac/mal.h
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
 *      Armin Kuster <akuster@mvista.com>
 *      Copyright 2002 MontaVista Softare Inc.
 */
#अगर_अघोषित __IBM_NEWEMAC_MAL_H
#घोषणा __IBM_NEWEMAC_MAL_H

/*
 * There are some variations on the MAL, we express them in this driver as
 * MAL Version 1 and 2 though that करोesn't match any IBM terminology.
 *
 * We call MAL 1 the version in 405GP, 405GPR, 405EP, 440EP, 440GR and
 * NP405H.
 *
 * We call MAL 2 the version in 440GP, 440GX, 440SP, 440SPE and Axon
 *
 * The driver expects a "version" property in the emac node containing
 * a number 1 or 2. New device-trees क्रम EMAC capable platक्रमms are thus
 * required to include that when porting to arch/घातerpc.
 */

/* MALx DCR रेजिस्टरs */
#घोषणा	MAL_CFG			0x00
#घोषणा	  MAL_CFG_SR		0x80000000
#घोषणा   MAL_CFG_PLBB		0x00004000
#घोषणा   MAL_CFG_OPBBL		0x00000080
#घोषणा   MAL_CFG_EOPIE		0x00000004
#घोषणा   MAL_CFG_LEA		0x00000002
#घोषणा   MAL_CFG_SD		0x00000001

/* MAL V1 CFG bits */
#घोषणा   MAL1_CFG_PLBP_MASK	0x00c00000
#घोषणा   MAL1_CFG_PLBP_10	0x00800000
#घोषणा   MAL1_CFG_GA		0x00200000
#घोषणा   MAL1_CFG_OA		0x00100000
#घोषणा   MAL1_CFG_PLBLE	0x00080000
#घोषणा   MAL1_CFG_PLBT_MASK	0x00078000
#घोषणा   MAL1_CFG_DEFAULT	(MAL1_CFG_PLBP_10 | MAL1_CFG_PLBT_MASK)

/* MAL V2 CFG bits */
#घोषणा   MAL2_CFG_RPP_MASK	0x00c00000
#घोषणा   MAL2_CFG_RPP_10	0x00800000
#घोषणा   MAL2_CFG_RMBS_MASK	0x00300000
#घोषणा   MAL2_CFG_WPP_MASK	0x000c0000
#घोषणा   MAL2_CFG_WPP_10	0x00080000
#घोषणा   MAL2_CFG_WMBS_MASK	0x00030000
#घोषणा   MAL2_CFG_PLBLE	0x00008000
#घोषणा   MAL2_CFG_DEFAULT	(MAL2_CFG_RMBS_MASK | MAL2_CFG_WMBS_MASK | \
				 MAL2_CFG_RPP_10 | MAL2_CFG_WPP_10)

#घोषणा MAL_ESR			0x01
#घोषणा   MAL_ESR_EVB		0x80000000
#घोषणा   MAL_ESR_CIDT		0x40000000
#घोषणा   MAL_ESR_CID_MASK	0x3e000000
#घोषणा   MAL_ESR_CID_SHIFT	25
#घोषणा   MAL_ESR_DE		0x00100000
#घोषणा   MAL_ESR_OTE		0x00040000
#घोषणा   MAL_ESR_OSE		0x00020000
#घोषणा   MAL_ESR_PEIN		0x00010000
#घोषणा   MAL_ESR_DEI		0x00000010
#घोषणा   MAL_ESR_OTEI		0x00000004
#घोषणा   MAL_ESR_OSEI		0x00000002
#घोषणा   MAL_ESR_PBEI		0x00000001

/* MAL V1 ESR bits */
#घोषणा   MAL1_ESR_ONE		0x00080000
#घोषणा   MAL1_ESR_ONEI		0x00000008

/* MAL V2 ESR bits */
#घोषणा   MAL2_ESR_PTE		0x00800000
#घोषणा   MAL2_ESR_PRE		0x00400000
#घोषणा   MAL2_ESR_PWE		0x00200000
#घोषणा   MAL2_ESR_PTEI		0x00000080
#घोषणा   MAL2_ESR_PREI		0x00000040
#घोषणा   MAL2_ESR_PWEI		0x00000020


#घोषणा MAL_IER			0x02
/* MAL IER bits */
#घोषणा   MAL_IER_DE		0x00000010
#घोषणा   MAL_IER_OTE		0x00000004
#घोषणा   MAL_IER_OE		0x00000002
#घोषणा   MAL_IER_PE		0x00000001

/* PLB पढ़ो/ग_लिखो/समयout errors */
#घोषणा   MAL_IER_PTE		0x00000080
#घोषणा   MAL_IER_PRE		0x00000040
#घोषणा   MAL_IER_PWE		0x00000020

#घोषणा   MAL_IER_SOC_EVENTS	(MAL_IER_PTE | MAL_IER_PRE | MAL_IER_PWE)
#घोषणा   MAL_IER_EVENTS	(MAL_IER_SOC_EVENTS | MAL_IER_DE | \
				 MAL_IER_OTE | MAL_IER_OE | MAL_IER_PE)

#घोषणा MAL_TXCASR		0x04
#घोषणा MAL_TXCARR		0x05
#घोषणा MAL_TXEOBISR		0x06
#घोषणा MAL_TXDEIR		0x07
#घोषणा MAL_RXCASR		0x10
#घोषणा MAL_RXCARR		0x11
#घोषणा MAL_RXEOBISR		0x12
#घोषणा MAL_RXDEIR		0x13
#घोषणा MAL_TXCTPR(n)		((n) + 0x20)
#घोषणा MAL_RXCTPR(n)		((n) + 0x40)
#घोषणा MAL_RCBS(n)		((n) + 0x60)

/* In reality MAL can handle TX buffers up to 4095 bytes दीर्घ,
 * but this isn't a good round number :) 		 --ebs
 */
#घोषणा MAL_MAX_TX_SIZE		4080
#घोषणा MAL_MAX_RX_SIZE		4080

अटल अंतरभूत पूर्णांक mal_rx_size(पूर्णांक len)
अणु
	len = (len + 0xf) & ~0xf;
	वापस len > MAL_MAX_RX_SIZE ? MAL_MAX_RX_SIZE : len;
पूर्ण

अटल अंतरभूत पूर्णांक mal_tx_chunks(पूर्णांक len)
अणु
	वापस DIV_ROUND_UP(len, MAL_MAX_TX_SIZE);
पूर्ण

#घोषणा MAL_CHAN_MASK(n)	(0x80000000 >> (n))

/* MAL Buffer Descriptor काष्ठाure */
काष्ठा mal_descriptor अणु
	u16 ctrl;		/* MAL / Commac status control bits */
	u16 data_len;		/* Max length is 4K-1 (12 bits)     */
	u32 data_ptr;		/* poपूर्णांकer to actual data buffer    */
पूर्ण;

/* the following defines are क्रम the MadMAL status and control रेजिस्टरs. */
/* MADMAL transmit and receive status/control bits  */
#घोषणा MAL_RX_CTRL_EMPTY	0x8000
#घोषणा MAL_RX_CTRL_WRAP	0x4000
#घोषणा MAL_RX_CTRL_CM		0x2000
#घोषणा MAL_RX_CTRL_LAST	0x1000
#घोषणा MAL_RX_CTRL_FIRST	0x0800
#घोषणा MAL_RX_CTRL_INTR	0x0400
#घोषणा MAL_RX_CTRL_SINGLE	(MAL_RX_CTRL_LAST | MAL_RX_CTRL_FIRST)
#घोषणा MAL_IS_SINGLE_RX(ctrl)	(((ctrl) & MAL_RX_CTRL_SINGLE) == MAL_RX_CTRL_SINGLE)

#घोषणा MAL_TX_CTRL_READY	0x8000
#घोषणा MAL_TX_CTRL_WRAP	0x4000
#घोषणा MAL_TX_CTRL_CM		0x2000
#घोषणा MAL_TX_CTRL_LAST	0x1000
#घोषणा MAL_TX_CTRL_INTR	0x0400

काष्ठा mal_commac_ops अणु
	व्योम	(*poll_tx) (व्योम *dev);
	पूर्णांक	(*poll_rx) (व्योम *dev, पूर्णांक budget);
	पूर्णांक	(*peek_rx) (व्योम *dev);
	व्योम	(*rxde) (व्योम *dev);
पूर्ण;

काष्ठा mal_commac अणु
	काष्ठा mal_commac_ops	*ops;
	व्योम			*dev;
	काष्ठा list_head	poll_list;
	दीर्घ       		flags;
#घोषणा MAL_COMMAC_RX_STOPPED		0
#घोषणा MAL_COMMAC_POLL_DISABLED	1
	u32			tx_chan_mask;
	u32			rx_chan_mask;
	काष्ठा list_head	list;
पूर्ण;

काष्ठा mal_instance अणु
	पूर्णांक			version;
	dcr_host_t		dcr_host;

	पूर्णांक			num_tx_chans;	/* Number of TX channels */
	पूर्णांक			num_rx_chans;	/* Number of RX channels */
	पूर्णांक 			txeob_irq;	/* TX End Of Buffer IRQ  */
	पूर्णांक 			rxeob_irq;	/* RX End Of Buffer IRQ  */
	पूर्णांक			txde_irq;	/* TX Descriptor Error IRQ */
	पूर्णांक			rxde_irq;	/* RX Descriptor Error IRQ */
	पूर्णांक			serr_irq;	/* MAL System Error IRQ    */

	काष्ठा list_head	poll_list;
	काष्ठा napi_काष्ठा	napi;

	काष्ठा list_head	list;
	u32			tx_chan_mask;
	u32			rx_chan_mask;

	dma_addr_t		bd_dma;
	काष्ठा mal_descriptor	*bd_virt;

	काष्ठा platक्रमm_device	*ofdev;
	पूर्णांक			index;
	spinlock_t		lock;

	काष्ठा net_device	dummy_dev;

	अचिन्हित पूर्णांक features;
पूर्ण;

अटल अंतरभूत u32 get_mal_dcrn(काष्ठा mal_instance *mal, पूर्णांक reg)
अणु
	वापस dcr_पढ़ो(mal->dcr_host, reg);
पूर्ण

अटल अंतरभूत व्योम set_mal_dcrn(काष्ठा mal_instance *mal, पूर्णांक reg, u32 val)
अणु
	dcr_ग_लिखो(mal->dcr_host, reg, val);
पूर्ण

/* Features of various MAL implementations */

/* Set अगर you have पूर्णांकerrupt coalescing and you have to clear the SDR
 * रेजिस्टर क्रम TXEOB and RXEOB पूर्णांकerrupts to work
 */
#घोषणा MAL_FTR_CLEAR_ICINTSTAT	0x00000001

/* Set अगर your MAL has SERR, TXDE, and RXDE OR'd पूर्णांकo a single UIC
 * पूर्णांकerrupt
 */
#घोषणा MAL_FTR_COMMON_ERR_INT	0x00000002

क्रमागत अणु
	MAL_FTRS_ALWAYS = 0,

	MAL_FTRS_POSSIBLE =
#अगर_घोषित CONFIG_IBM_EMAC_MAL_CLR_ICINTSTAT
		MAL_FTR_CLEAR_ICINTSTAT |
#पूर्ण_अगर
#अगर_घोषित CONFIG_IBM_EMAC_MAL_COMMON_ERR
		MAL_FTR_COMMON_ERR_INT |
#पूर्ण_अगर
		0,
पूर्ण;

अटल अंतरभूत पूर्णांक mal_has_feature(काष्ठा mal_instance *dev,
		अचिन्हित दीर्घ feature)
अणु
	वापस (MAL_FTRS_ALWAYS & feature) ||
		(MAL_FTRS_POSSIBLE & dev->features & feature);
पूर्ण

/* Register MAL devices */
पूर्णांक mal_init(व्योम);
व्योम mal_निकास(व्योम);

पूर्णांक mal_रेजिस्टर_commac(काष्ठा mal_instance *mal,
			काष्ठा mal_commac *commac);
व्योम mal_unरेजिस्टर_commac(काष्ठा mal_instance *mal,
			   काष्ठा mal_commac *commac);
पूर्णांक mal_set_rcbs(काष्ठा mal_instance *mal, पूर्णांक channel, अचिन्हित दीर्घ size);

/* Returns BD ring offset क्रम a particular channel
   (in 'struct mal_descriptor' elements)
*/
पूर्णांक mal_tx_bd_offset(काष्ठा mal_instance *mal, पूर्णांक channel);
पूर्णांक mal_rx_bd_offset(काष्ठा mal_instance *mal, पूर्णांक channel);

व्योम mal_enable_tx_channel(काष्ठा mal_instance *mal, पूर्णांक channel);
व्योम mal_disable_tx_channel(काष्ठा mal_instance *mal, पूर्णांक channel);
व्योम mal_enable_rx_channel(काष्ठा mal_instance *mal, पूर्णांक channel);
व्योम mal_disable_rx_channel(काष्ठा mal_instance *mal, पूर्णांक channel);

व्योम mal_poll_disable(काष्ठा mal_instance *mal, काष्ठा mal_commac *commac);
व्योम mal_poll_enable(काष्ठा mal_instance *mal, काष्ठा mal_commac *commac);

/* Add/हटाओ EMAC to/from MAL polling list */
व्योम mal_poll_add(काष्ठा mal_instance *mal, काष्ठा mal_commac *commac);
व्योम mal_poll_del(काष्ठा mal_instance *mal, काष्ठा mal_commac *commac);

/* Ethtool MAL रेजिस्टरs */
काष्ठा mal_regs अणु
	u32 tx_count;
	u32 rx_count;

	u32 cfg;
	u32 esr;
	u32 ier;
	u32 tx_casr;
	u32 tx_carr;
	u32 tx_eobisr;
	u32 tx_deir;
	u32 rx_casr;
	u32 rx_carr;
	u32 rx_eobisr;
	u32 rx_deir;
	u32 tx_ctpr[32];
	u32 rx_ctpr[32];
	u32 rcbs[32];
पूर्ण;

पूर्णांक mal_get_regs_len(काष्ठा mal_instance *mal);
व्योम *mal_dump_regs(काष्ठा mal_instance *mal, व्योम *buf);

#पूर्ण_अगर /* __IBM_NEWEMAC_MAL_H */
