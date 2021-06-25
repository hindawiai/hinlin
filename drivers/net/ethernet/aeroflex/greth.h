<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित GRETH_H
#घोषणा GRETH_H

#समावेश <linux/phy.h>

/* Register bits and masks */
#घोषणा GRETH_RESET 0x40
#घोषणा GRETH_MII_BUSY 0x8
#घोषणा GRETH_MII_NVALID 0x10

#घोषणा GRETH_CTRL_FD         0x10
#घोषणा GRETH_CTRL_PR         0x20
#घोषणा GRETH_CTRL_SP         0x80
#घोषणा GRETH_CTRL_GB         0x100
#घोषणा GRETH_CTRL_PSTATIEN   0x400
#घोषणा GRETH_CTRL_MCEN       0x800
#घोषणा GRETH_CTRL_DISDUPLEX  0x1000
#घोषणा GRETH_STATUS_PHYSTAT  0x100

#घोषणा GRETH_BD_EN 0x800
#घोषणा GRETH_BD_WR 0x1000
#घोषणा GRETH_BD_IE 0x2000
#घोषणा GRETH_BD_LEN 0x7FF

#घोषणा GRETH_TXEN 0x1
#घोषणा GRETH_INT_TE 0x2
#घोषणा GRETH_INT_TX 0x8
#घोषणा GRETH_TXI 0x4
#घोषणा GRETH_TXBD_STATUS 0x0001C000
#घोषणा GRETH_TXBD_MORE 0x20000
#घोषणा GRETH_TXBD_IPCS 0x40000
#घोषणा GRETH_TXBD_TCPCS 0x80000
#घोषणा GRETH_TXBD_UDPCS 0x100000
#घोषणा GRETH_TXBD_CSALL (GRETH_TXBD_IPCS | GRETH_TXBD_TCPCS | GRETH_TXBD_UDPCS)
#घोषणा GRETH_TXBD_ERR_LC 0x10000
#घोषणा GRETH_TXBD_ERR_UE 0x4000
#घोषणा GRETH_TXBD_ERR_AL 0x8000

#घोषणा GRETH_INT_RE         0x1
#घोषणा GRETH_INT_RX         0x4
#घोषणा GRETH_RXEN           0x2
#घोषणा GRETH_RXI            0x8
#घोषणा GRETH_RXBD_STATUS    0xFFFFC000
#घोषणा GRETH_RXBD_ERR_AE    0x4000
#घोषणा GRETH_RXBD_ERR_FT    0x8000
#घोषणा GRETH_RXBD_ERR_CRC   0x10000
#घोषणा GRETH_RXBD_ERR_OE    0x20000
#घोषणा GRETH_RXBD_ERR_LE    0x40000
#घोषणा GRETH_RXBD_IP        0x80000
#घोषणा GRETH_RXBD_IP_CSERR  0x100000
#घोषणा GRETH_RXBD_UDP       0x200000
#घोषणा GRETH_RXBD_UDP_CSERR 0x400000
#घोषणा GRETH_RXBD_TCP       0x800000
#घोषणा GRETH_RXBD_TCP_CSERR 0x1000000
#घोषणा GRETH_RXBD_IP_FRAG   0x2000000
#घोषणा GRETH_RXBD_MCAST     0x4000000

/* Descriptor parameters */
#घोषणा GRETH_TXBD_NUM 128
#घोषणा GRETH_TXBD_NUM_MASK (GRETH_TXBD_NUM-1)
#घोषणा GRETH_TX_BUF_SIZE 2048
#घोषणा GRETH_RXBD_NUM 128
#घोषणा GRETH_RXBD_NUM_MASK (GRETH_RXBD_NUM-1)
#घोषणा GRETH_RX_BUF_SIZE 2048

/* Buffers per page */
#घोषणा GRETH_RX_BUF_PPGAE	(PAGE_SIZE/GRETH_RX_BUF_SIZE)
#घोषणा GRETH_TX_BUF_PPGAE	(PAGE_SIZE/GRETH_TX_BUF_SIZE)

/* How many pages are needed क्रम buffers */
#घोषणा GRETH_RX_BUF_PAGE_NUM	(GRETH_RXBD_NUM/GRETH_RX_BUF_PPGAE)
#घोषणा GRETH_TX_BUF_PAGE_NUM	(GRETH_TXBD_NUM/GRETH_TX_BUF_PPGAE)

/* Buffer size.
 * Gbit MAC uses tagged maximum frame size which is 1518 excluding CRC.
 * Set to 1520 to make all buffers word aligned क्रम non-gbit MAC.
 */
#घोषणा MAX_FRAME_SIZE		1520

/* GRETH APB रेजिस्टरs */
काष्ठा greth_regs अणु
	u32 control;
	u32 status;
	u32 esa_msb;
	u32 esa_lsb;
	u32 mdio;
	u32 tx_desc_p;
	u32 rx_desc_p;
	u32 edclip;
	u32 hash_msb;
	u32 hash_lsb;
पूर्ण;

/* GRETH buffer descriptor */
काष्ठा greth_bd अणु
	u32 stat;
	u32 addr;
पूर्ण;

काष्ठा greth_निजी अणु
	काष्ठा sk_buff *rx_skbuff[GRETH_RXBD_NUM];
	काष्ठा sk_buff *tx_skbuff[GRETH_TXBD_NUM];

	अचिन्हित अक्षर *tx_bufs[GRETH_TXBD_NUM];
	अचिन्हित अक्षर *rx_bufs[GRETH_RXBD_NUM];
	u16 tx_bufs_length[GRETH_TXBD_NUM];

	u16 tx_next;
	u16 tx_last;
	u16 tx_मुक्त; /* only used on 10/100Mbit */
	u16 rx_cur;

	काष्ठा greth_regs *regs;	/* Address of controller रेजिस्टरs. */
	काष्ठा greth_bd *rx_bd_base;	/* Address of Rx BDs. */
	काष्ठा greth_bd *tx_bd_base;	/* Address of Tx BDs. */
	dma_addr_t rx_bd_base_phys;
	dma_addr_t tx_bd_base_phys;

	पूर्णांक irq;

	काष्ठा device *dev;	        /* Poपूर्णांकer to platक्रमm_device->dev */
	काष्ठा net_device *netdev;
	काष्ठा napi_काष्ठा napi;
	spinlock_t devlock;

	काष्ठा mii_bus *mdio;
	अचिन्हित पूर्णांक link;
	अचिन्हित पूर्णांक speed;
	अचिन्हित पूर्णांक duplex;

	u32 msg_enable;

	u8 phyaddr;
	u8 multicast;
	u8 gbit_mac;
	u8 mdio_पूर्णांक_en;
	u8 edcl;
पूर्ण;

#पूर्ण_अगर
