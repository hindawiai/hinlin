<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  linux/drivers/acorn/net/ether3.h
 *
 *  Copyright (C) 1995-2000 Russell King
 *
 *  network driver क्रम Acorn/ANT Ether3 cards
 */

#अगर_अघोषित _LINUX_ether3_H
#घोषणा _LINUX_ether3_H

/* use 0 क्रम production, 1 क्रम verअगरication, >2 क्रम debug. debug flags: */
#घोषणा DEBUG_TX	 2
#घोषणा DEBUG_RX	 4
#घोषणा DEBUG_INT	 8
#घोषणा DEBUG_IC	16
#अगर_अघोषित NET_DEBUG
#घोषणा NET_DEBUG 	0
#पूर्ण_अगर

#घोषणा priv(dev)	((काष्ठा dev_priv *)netdev_priv(dev))

/* Command रेजिस्टर definitions & bits */
#घोषणा REG_COMMAND		(priv(dev)->seeq + 0x0000)
#घोषणा CMD_ENINTDMA		0x0001
#घोषणा CMD_ENINTRX		0x0002
#घोषणा CMD_ENINTTX		0x0004
#घोषणा CMD_ENINTBUFWIN		0x0008
#घोषणा CMD_ACKINTDMA		0x0010
#घोषणा CMD_ACKINTRX		0x0020
#घोषणा CMD_ACKINTTX		0x0040
#घोषणा CMD_ACKINTBUFWIN	0x0080
#घोषणा CMD_DMAON		0x0100
#घोषणा CMD_RXON		0x0200
#घोषणा CMD_TXON		0x0400
#घोषणा CMD_DMAOFF		0x0800
#घोषणा CMD_RXOFF		0x1000
#घोषणा CMD_TXOFF		0x2000
#घोषणा CMD_FIFOREAD		0x4000
#घोषणा CMD_FIFOWRITE		0x8000

/* status रेजिस्टर */
#घोषणा REG_STATUS		(priv(dev)->seeq + 0x0000)
#घोषणा STAT_ENINTSTAT		0x0001
#घोषणा STAT_ENINTRX		0x0002
#घोषणा STAT_ENINTTX		0x0004
#घोषणा STAT_ENINTBUFWIN	0x0008
#घोषणा STAT_INTDMA		0x0010
#घोषणा STAT_INTRX		0x0020
#घोषणा STAT_INTTX		0x0040
#घोषणा STAT_INTBUFWIN		0x0080
#घोषणा STAT_DMAON		0x0100
#घोषणा STAT_RXON		0x0200
#घोषणा STAT_TXON		0x0400
#घोषणा STAT_FIFOFULL		0x2000
#घोषणा STAT_FIFOEMPTY		0x4000
#घोषणा STAT_FIFOसूची		0x8000

/* configuration रेजिस्टर 1 */
#घोषणा REG_CONFIG1		(priv(dev)->seeq + 0x0040)
#घोषणा CFG1_BUFSELSTAT0	0x0000
#घोषणा CFG1_BUFSELSTAT1	0x0001
#घोषणा CFG1_BUFSELSTAT2	0x0002
#घोषणा CFG1_BUFSELSTAT3	0x0003
#घोषणा CFG1_BUFSELSTAT4	0x0004
#घोषणा CFG1_BUFSELSTAT5	0x0005
#घोषणा CFG1_ADDRPROM		0x0006
#घोषणा CFG1_TRANSEND		0x0007
#घोषणा CFG1_LOCBUFMEM		0x0008
#घोषणा CFG1_INTVECTOR		0x0009
#घोषणा CFG1_RECVSPECONLY	0x0000
#घोषणा CFG1_RECVSPECBROAD	0x4000
#घोषणा CFG1_RECVSPECBRMULTI	0x8000
#घोषणा CFG1_RECVPROMISC	0xC000

/* The following aren't in 8004 */
#घोषणा CFG1_DMABURSTCONT	0x0000
#घोषणा CFG1_DMABURST800NS	0x0010
#घोषणा CFG1_DMABURST1600NS	0x0020
#घोषणा CFG1_DMABURST3200NS	0x0030
#घोषणा CFG1_DMABURST1		0x0000
#घोषणा CFG1_DMABURST4		0x0040
#घोषणा CFG1_DMABURST8		0x0080
#घोषणा CFG1_DMABURST16		0x00C0
#घोषणा CFG1_RECVCOMPSTAT0	0x0100
#घोषणा CFG1_RECVCOMPSTAT1	0x0200
#घोषणा CFG1_RECVCOMPSTAT2	0x0400
#घोषणा CFG1_RECVCOMPSTAT3	0x0800
#घोषणा CFG1_RECVCOMPSTAT4	0x1000
#घोषणा CFG1_RECVCOMPSTAT5	0x2000

/* configuration रेजिस्टर 2 */
#घोषणा REG_CONFIG2		(priv(dev)->seeq + 0x0080)
#घोषणा CFG2_BYTESWAP		0x0001
#घोषणा CFG2_ERRENCRC		0x0008
#घोषणा CFG2_ERRENDRIBBLE	0x0010
#घोषणा CFG2_ERRSHORTFRAME	0x0020
#घोषणा CFG2_SLOTSELECT		0x0040
#घोषणा CFG2_PREAMSELECT	0x0080
#घोषणा CFG2_ADDRLENGTH		0x0100
#घोषणा CFG2_RECVCRC		0x0200
#घोषणा CFG2_XMITNOCRC		0x0400
#घोषणा CFG2_LOOPBACK		0x0800
#घोषणा CFG2_CTRLO		0x1000
#घोषणा CFG2_RESET		0x8000

#घोषणा REG_RECVEND		(priv(dev)->seeq + 0x00c0)

#घोषणा REG_BUFWIN		(priv(dev)->seeq + 0x0100)

#घोषणा REG_RECVPTR		(priv(dev)->seeq + 0x0140)

#घोषणा REG_TRANSMITPTR		(priv(dev)->seeq + 0x0180)

#घोषणा REG_DMAADDR		(priv(dev)->seeq + 0x01c0)

/*
 * Cards transmit/receive headers
 */
#घोषणा TX_NEXT			(0xffff)
#घोषणा TXHDR_ENBABBLEINT	(1 << 16)
#घोषणा TXHDR_ENCOLLISIONINT	(1 << 17)
#घोषणा TXHDR_EN16COLLISION	(1 << 18)
#घोषणा TXHDR_ENSUCCESS		(1 << 19)
#घोषणा TXHDR_DATAFOLLOWS	(1 << 21)
#घोषणा TXHDR_CHAINCONTINUE	(1 << 22)
#घोषणा TXHDR_TRANSMIT		(1 << 23)
#घोषणा TXSTAT_BABBLED		(1 << 24)
#घोषणा TXSTAT_COLLISION	(1 << 25)
#घोषणा TXSTAT_16COLLISIONS	(1 << 26)
#घोषणा TXSTAT_DONE		(1 << 31)

#घोषणा RX_NEXT			(0xffff)
#घोषणा RXHDR_CHAINCONTINUE	(1 << 6)
#घोषणा RXHDR_RECEIVE		(1 << 7)
#घोषणा RXSTAT_OVERSIZE		(1 << 8)
#घोषणा RXSTAT_CRCERROR		(1 << 9)
#घोषणा RXSTAT_DRIBBLEERROR	(1 << 10)
#घोषणा RXSTAT_SHORTPACKET	(1 << 11)
#घोषणा RXSTAT_DONE		(1 << 15)


#घोषणा TX_START	0x0000
#घोषणा TX_END		0x6000
#घोषणा RX_START	0x6000
#घोषणा RX_LEN		0xA000
#घोषणा RX_END		0x10000
/* must be a घातer of 2 and greater than MAX_TX_BUFFERED */
#घोषणा MAX_TXED	16
#घोषणा MAX_TX_BUFFERED	10

काष्ठा dev_priv अणु
    व्योम __iomem *base;
    व्योम __iomem *seeq;
    काष्ठा अणु
	अचिन्हित पूर्णांक command;
	अचिन्हित पूर्णांक config1;
	अचिन्हित पूर्णांक config2;
    पूर्ण regs;
    अचिन्हित अक्षर tx_head;		/* buffer nr to insert next packet	 */
    अचिन्हित अक्षर tx_tail;		/* buffer nr of transmitting packet	 */
    अचिन्हित पूर्णांक rx_head;		/* address to fetch next packet from	 */
    काष्ठा समयr_list समयr;
    काष्ठा net_device *dev;
    पूर्णांक broken;				/* 0 = ok, 1 = something went wrong	 */
पूर्ण;

काष्ठा ether3_data अणु
	स्थिर अक्षर name[8];
	अचिन्हित दीर्घ base_offset;
पूर्ण;

#पूर्ण_अगर
