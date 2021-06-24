<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2004-2013 Synopsys, Inc. (www.synopsys.com)
 *
 * Registers and bits definitions of ARC EMAC
 */

#अगर_अघोषित ARC_EMAC_H
#घोषणा ARC_EMAC_H

#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/phy.h>
#समावेश <linux/clk.h>

/* STATUS and ENABLE Register bit masks */
#घोषणा TXINT_MASK	(1 << 0)	/* Transmit पूर्णांकerrupt */
#घोषणा RXINT_MASK	(1 << 1)	/* Receive पूर्णांकerrupt */
#घोषणा ERR_MASK	(1 << 2)	/* Error पूर्णांकerrupt */
#घोषणा TXCH_MASK	(1 << 3)	/* Transmit chaining error पूर्णांकerrupt */
#घोषणा MSER_MASK	(1 << 4)	/* Missed packet counter error */
#घोषणा RXCR_MASK	(1 << 8)	/* RXCRCERR counter rolled over  */
#घोषणा RXFR_MASK	(1 << 9)	/* RXFRAMEERR counter rolled over */
#घोषणा RXFL_MASK	(1 << 10)	/* RXOFLOWERR counter rolled over */
#घोषणा MDIO_MASK	(1 << 12)	/* MDIO complete पूर्णांकerrupt */
#घोषणा TXPL_MASK	(1 << 31)	/* Force polling of BD by EMAC */

/* CONTROL Register bit masks */
#घोषणा EN_MASK		(1 << 0)	/* VMAC enable */
#घोषणा TXRN_MASK	(1 << 3)	/* TX enable */
#घोषणा RXRN_MASK	(1 << 4)	/* RX enable */
#घोषणा DSBC_MASK	(1 << 8)	/* Disable receive broadcast */
#घोषणा ENFL_MASK	(1 << 10)	/* Enable Full-duplex */
#घोषणा PROM_MASK	(1 << 11)	/* Promiscuous mode */

/* Buffer descriptor INFO bit masks */
#घोषणा OWN_MASK	(1 << 31)	/* 0-CPU or 1-EMAC owns buffer */
#घोषणा FIRST_MASK	(1 << 16)	/* First buffer in chain */
#घोषणा LAST_MASK	(1 << 17)	/* Last buffer in chain */
#घोषणा LEN_MASK	0x000007FF	/* last 11 bits */
#घोषणा CRLS		(1 << 21)
#घोषणा DEFR		(1 << 22)
#घोषणा DROP		(1 << 23)
#घोषणा RTRY		(1 << 24)
#घोषणा LTCL		(1 << 28)
#घोषणा UFLO		(1 << 29)

#घोषणा FOR_EMAC	OWN_MASK
#घोषणा FOR_CPU		0

/* ARC EMAC रेजिस्टर set combines entries क्रम MAC and MDIO */
क्रमागत अणु
	R_ID = 0,
	R_STATUS,
	R_ENABLE,
	R_CTRL,
	R_POLLRATE,
	R_RXERR,
	R_MISS,
	R_TX_RING,
	R_RX_RING,
	R_ADDRL,
	R_ADDRH,
	R_LAFL,
	R_LAFH,
	R_MDIO,
पूर्ण;

#घोषणा TX_TIMEOUT		(400 * HZ / 1000) /* Transmission समयout */

#घोषणा ARC_EMAC_NAPI_WEIGHT	40		/* Workload क्रम NAPI */

#घोषणा EMAC_BUFFER_SIZE	1536		/* EMAC buffer size */

/**
 * काष्ठा arc_emac_bd - EMAC buffer descriptor (BD).
 *
 * @info:	Contains status inक्रमmation on the buffer itself.
 * @data:	32-bit byte addressable poपूर्णांकer to the packet data.
 */
काष्ठा arc_emac_bd अणु
	__le32 info;
	dma_addr_t data;
पूर्ण;

/* Number of Rx/Tx BD's */
#घोषणा RX_BD_NUM	128
#घोषणा TX_BD_NUM	128

#घोषणा RX_RING_SZ	(RX_BD_NUM * माप(काष्ठा arc_emac_bd))
#घोषणा TX_RING_SZ	(TX_BD_NUM * माप(काष्ठा arc_emac_bd))

/**
 * काष्ठा buffer_state - Stores Rx/Tx buffer state.
 * @sk_buff:	Poपूर्णांकer to socket buffer.
 * @addr:	Start address of DMA-mapped memory region.
 * @len:	Length of DMA-mapped memory region.
 */
काष्ठा buffer_state अणु
	काष्ठा sk_buff *skb;
	DEFINE_DMA_UNMAP_ADDR(addr);
	DEFINE_DMA_UNMAP_LEN(len);
पूर्ण;

काष्ठा arc_emac_mdio_bus_data अणु
	काष्ठा gpio_desc *reset_gpio;
	पूर्णांक msec;
पूर्ण;

/**
 * काष्ठा arc_emac_priv - Storage of EMAC's निजी inक्रमmation.
 * @dev:	Poपूर्णांकer to the current device.
 * @phy_dev:	Poपूर्णांकer to attached PHY device.
 * @bus:	Poपूर्णांकer to the current MII bus.
 * @regs:	Base address of EMAC memory-mapped control रेजिस्टरs.
 * @napi:	Structure क्रम NAPI.
 * @rxbd:	Poपूर्णांकer to Rx BD ring.
 * @txbd:	Poपूर्णांकer to Tx BD ring.
 * @rxbd_dma:	DMA handle क्रम Rx BD ring.
 * @txbd_dma:	DMA handle क्रम Tx BD ring.
 * @rx_buff:	Storage क्रम Rx buffers states.
 * @tx_buff:	Storage क्रम Tx buffers states.
 * @txbd_curr:	Index of Tx BD to use on the next "ndo_start_xmit".
 * @txbd_dirty:	Index of Tx BD to मुक्त on the next Tx पूर्णांकerrupt.
 * @last_rx_bd:	Index of the last Rx BD we've got from EMAC.
 * @link:	PHY's last seen link state.
 * @duplex:	PHY's last set duplex mode.
 * @speed:	PHY's last set speed.
 */
काष्ठा arc_emac_priv अणु
	स्थिर अक्षर *drv_name;
	व्योम (*set_mac_speed)(व्योम *priv, अचिन्हित पूर्णांक speed);

	/* Devices */
	काष्ठा device *dev;
	काष्ठा mii_bus *bus;
	काष्ठा arc_emac_mdio_bus_data bus_data;

	व्योम __iomem *regs;
	काष्ठा clk *clk;

	काष्ठा napi_काष्ठा napi;

	काष्ठा arc_emac_bd *rxbd;
	काष्ठा arc_emac_bd *txbd;

	dma_addr_t rxbd_dma;
	dma_addr_t txbd_dma;

	काष्ठा buffer_state rx_buff[RX_BD_NUM];
	काष्ठा buffer_state tx_buff[TX_BD_NUM];
	अचिन्हित पूर्णांक txbd_curr;
	अचिन्हित पूर्णांक txbd_dirty;

	अचिन्हित पूर्णांक last_rx_bd;

	अचिन्हित पूर्णांक link;
	अचिन्हित पूर्णांक duplex;
	अचिन्हित पूर्णांक speed;

	अचिन्हित पूर्णांक rx_missed_errors;
पूर्ण;

/**
 * arc_reg_set - Sets EMAC रेजिस्टर with provided value.
 * @priv:	Poपूर्णांकer to ARC EMAC निजी data काष्ठाure.
 * @reg:	Register offset from base address.
 * @value:	Value to set in रेजिस्टर.
 */
अटल अंतरभूत व्योम arc_reg_set(काष्ठा arc_emac_priv *priv, पूर्णांक reg, पूर्णांक value)
अणु
	ioग_लिखो32(value, priv->regs + reg * माप(पूर्णांक));
पूर्ण

/**
 * arc_reg_get - Gets value of specअगरied EMAC रेजिस्टर.
 * @priv:	Poपूर्णांकer to ARC EMAC निजी data काष्ठाure.
 * @reg:	Register offset from base address.
 *
 * वापसs:	Value of requested रेजिस्टर.
 */
अटल अंतरभूत अचिन्हित पूर्णांक arc_reg_get(काष्ठा arc_emac_priv *priv, पूर्णांक reg)
अणु
	वापस ioपढ़ो32(priv->regs + reg * माप(पूर्णांक));
पूर्ण

/**
 * arc_reg_or - Applies mask to specअगरied EMAC रेजिस्टर - ("reg" | "mask").
 * @priv:	Poपूर्णांकer to ARC EMAC निजी data काष्ठाure.
 * @reg:	Register offset from base address.
 * @mask:	Mask to apply to specअगरied रेजिस्टर.
 *
 * This function पढ़ोs initial रेजिस्टर value, then applies provided mask
 * to it and then ग_लिखोs रेजिस्टर back.
 */
अटल अंतरभूत व्योम arc_reg_or(काष्ठा arc_emac_priv *priv, पूर्णांक reg, पूर्णांक mask)
अणु
	अचिन्हित पूर्णांक value = arc_reg_get(priv, reg);

	arc_reg_set(priv, reg, value | mask);
पूर्ण

/**
 * arc_reg_clr - Applies mask to specअगरied EMAC रेजिस्टर - ("reg" & ~"mask").
 * @priv:	Poपूर्णांकer to ARC EMAC निजी data काष्ठाure.
 * @reg:	Register offset from base address.
 * @mask:	Mask to apply to specअगरied रेजिस्टर.
 *
 * This function पढ़ोs initial रेजिस्टर value, then applies provided mask
 * to it and then ग_लिखोs रेजिस्टर back.
 */
अटल अंतरभूत व्योम arc_reg_clr(काष्ठा arc_emac_priv *priv, पूर्णांक reg, पूर्णांक mask)
अणु
	अचिन्हित पूर्णांक value = arc_reg_get(priv, reg);

	arc_reg_set(priv, reg, value & ~mask);
पूर्ण

पूर्णांक arc_mdio_probe(काष्ठा arc_emac_priv *priv);
पूर्णांक arc_mdio_हटाओ(काष्ठा arc_emac_priv *priv);
पूर्णांक arc_emac_probe(काष्ठा net_device *ndev, पूर्णांक पूर्णांकerface);
पूर्णांक arc_emac_हटाओ(काष्ठा net_device *ndev);

#पूर्ण_अगर /* ARC_EMAC_H */
