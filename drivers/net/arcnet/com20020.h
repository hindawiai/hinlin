<शैली गुरु>
/*
 * Linux ARCnet driver - COM20020 chipset support - function declarations
 *
 * Written 1997 by David Woodhouse.
 * Written 1994-1999 by Avery Pennarun.
 * Derived from skeleton.c by Donald Becker.
 *
 * Special thanks to Contemporary Controls, Inc. (www.ccontrols.com)
 *  क्रम sponsoring the further development of this driver.
 *
 * **********************
 *
 * The original copyright of skeleton.c was as follows:
 *
 * skeleton.c Written 1993 by Donald Becker.
 * Copyright 1993 United States Government as represented by the
 * Director, National Security Agency.  This software may only be used
 * and distributed according to the terms of the GNU General Public License as
 * modअगरied by SRC, incorporated herein by reference.
 *
 * **********************
 *
 * For more details, see drivers/net/arcnet.c
 *
 * **********************
 */
#अगर_अघोषित __COM20020_H
#घोषणा __COM20020_H
#समावेश <linux/leds.h>

पूर्णांक com20020_check(काष्ठा net_device *dev);
पूर्णांक com20020_found(काष्ठा net_device *dev, पूर्णांक shared);
बाह्य स्थिर काष्ठा net_device_ops com20020_netdev_ops;

/* The number of low I/O ports used by the card. */
#घोषणा ARCNET_TOTAL_SIZE 8

#घोषणा PLX_PCI_MAX_CARDS 2

काष्ठा leकरोffsets अणु
	पूर्णांक green;
	पूर्णांक red;
पूर्ण;

काष्ठा com20020_pci_channel_map अणु
	u32 bar;
	u32 offset;
	u32 size;               /* 0x00 - स्वतः, e.g. length of entire bar */
पूर्ण;

काष्ठा com20020_pci_card_info अणु
	स्थिर अक्षर *name;
	पूर्णांक devcount;

	काष्ठा com20020_pci_channel_map chan_map_tbl[PLX_PCI_MAX_CARDS];
	काष्ठा com20020_pci_channel_map misc_map;

	काष्ठा leकरोffsets leds[PLX_PCI_MAX_CARDS];
	पूर्णांक rotary;

	अचिन्हित पूर्णांक flags;
पूर्ण;

काष्ठा com20020_priv अणु
	काष्ठा com20020_pci_card_info *ci;
	काष्ठा list_head list_dev;
	resource_माप_प्रकार misc;
पूर्ण;

काष्ठा com20020_dev अणु
	काष्ठा list_head list;
	काष्ठा net_device *dev;

	काष्ठा led_classdev tx_led;
	काष्ठा led_classdev recon_led;

	काष्ठा com20020_priv *pci_priv;
	पूर्णांक index;
पूर्ण;

#घोषणा COM20020_REG_W_INTMASK	0	/* writable */
#घोषणा COM20020_REG_R_STATUS	0	/* पढ़ोable */
#घोषणा COM20020_REG_W_COMMAND	1	/* standard arcnet commands */
#घोषणा COM20020_REG_R_DIAGSTAT	1	/* diagnostic status */
#घोषणा COM20020_REG_W_ADDR_HI	2	/* control क्रम IO-mapped memory */
#घोषणा COM20020_REG_W_ADDR_LO	3
#घोषणा COM20020_REG_RW_MEMDATA	4	/* data port क्रम IO-mapped memory */
#घोषणा COM20020_REG_W_SUBADR	5	/* the extended port _XREG refers to */
#घोषणा COM20020_REG_W_CONFIG	6	/* configuration */
#घोषणा COM20020_REG_W_XREG	7	/* extra
					 * (indexed by _CONFIG or _SUBADDR)
					 */

/* in the ADDR_HI रेजिस्टर */
#घोषणा RDDATAflag	0x80	/* next access is a पढ़ो (not a ग_लिखो) */

/* in the DIAGSTAT रेजिस्टर */
#घोषणा NEWNXTIDflag	0x02	/* ID to which token is passed has changed */

/* in the CONFIG रेजिस्टर */
#घोषणा RESETcfg	0x80	/* put card in reset state */
#घोषणा TXENcfg		0x20	/* enable TX */
#घोषणा XTOcfg(x)	((x) << 3)	/* extended समयout */

/* in SETUP रेजिस्टर */
#घोषणा PROMISCset	0x10	/* enable RCV_ALL */
#घोषणा P1MODE		0x80    /* enable P1-MODE क्रम Backplane */
#घोषणा SLOWARB		0x01    /* enable Slow Arbitration क्रम >=5Mbps */

/* COM2002x */
#घोषणा SUB_TENTATIVE	0	/* tentative node ID */
#घोषणा SUB_NODE	1	/* node ID */
#घोषणा SUB_SETUP1	2	/* various options */
#घोषणा SUB_TEST	3	/* test/diag रेजिस्टर */

/* COM20022 only */
#घोषणा SUB_SETUP2	4	/* sundry options */
#घोषणा SUB_BUSCTL	5	/* bus control options */
#घोषणा SUB_DMACOUNT	6	/* DMA count options */

अटल अंतरभूत व्योम com20020_set_subaddress(काष्ठा arcnet_local *lp,
					   पूर्णांक ioaddr, पूर्णांक val)
अणु
	अगर (val < 4) अणु
		lp->config = (lp->config & ~0x03) | val;
		arcnet_outb(lp->config, ioaddr, COM20020_REG_W_CONFIG);
	पूर्ण अन्यथा अणु
		arcnet_outb(val, ioaddr, COM20020_REG_W_SUBADR);
	पूर्ण
पूर्ण

#पूर्ण_अगर /* __COM20020_H */
