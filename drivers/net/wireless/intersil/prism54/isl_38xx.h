<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Copyright (C) 2002 Intersil Americas Inc.
 */

#अगर_अघोषित _ISL_38XX_H
#घोषणा _ISL_38XX_H

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/byteorder.h>

#घोषणा ISL38XX_CB_RX_QSIZE                     8
#घोषणा ISL38XX_CB_TX_QSIZE                     32

/* ISL38XX Access Poपूर्णांक Specअगरic definitions */
#घोषणा ISL38XX_MAX_WDS_LINKS                   8

/* ISL38xx Client Specअगरic definitions */
#घोषणा ISL38XX_PSM_ACTIVE_STATE                0
#घोषणा ISL38XX_PSM_POWERSAVE_STATE             1

/* ISL38XX Host Interface Definitions */
#घोषणा ISL38XX_PCI_MEM_SIZE                    0x02000
#घोषणा ISL38XX_MEMORY_WINDOW_SIZE              0x01000
#घोषणा ISL38XX_DEV_FIRMWARE_ADDRES             0x20000
#घोषणा ISL38XX_WRITEIO_DELAY                   10	/* in us */
#घोषणा ISL38XX_RESET_DELAY                     50	/* in ms */
#घोषणा ISL38XX_WAIT_CYCLE                      10	/* in 10ms */
#घोषणा ISL38XX_MAX_WAIT_CYCLES                 10

/* PCI Memory Area */
#घोषणा ISL38XX_HARDWARE_REG                    0x0000
#घोषणा ISL38XX_CARDBUS_CIS                     0x0800
#घोषणा ISL38XX_सूचीECT_MEM_WIN                  0x1000

/* Hardware रेजिस्टरs */
#घोषणा ISL38XX_DEV_INT_REG                     0x0000
#घोषणा ISL38XX_INT_IDENT_REG                   0x0010
#घोषणा ISL38XX_INT_ACK_REG                     0x0014
#घोषणा ISL38XX_INT_EN_REG                      0x0018
#घोषणा ISL38XX_GEN_PURP_COM_REG_1              0x0020
#घोषणा ISL38XX_GEN_PURP_COM_REG_2              0x0024
#घोषणा ISL38XX_CTRL_BLK_BASE_REG               ISL38XX_GEN_PURP_COM_REG_1
#घोषणा ISL38XX_सूची_MEM_BASE_REG                0x0030
#घोषणा ISL38XX_CTRL_STAT_REG                   0x0078

/* High end mobos queue up pci ग_लिखोs, the following
 * is used to "read" from after a ग_लिखो to क्रमce flush */
#घोषणा ISL38XX_PCI_POSTING_FLUSH		ISL38XX_INT_EN_REG

/**
 * isl38xx_w32_flush - PCI iomem ग_लिखो helper
 * @base: (host) memory base address of the device
 * @val: 32bit value (host order) to ग_लिखो
 * @offset: byte offset पूर्णांकo @base to ग_लिखो value to
 *
 *  This helper takes care of writing a 32bit datum to the
 *  specअगरied offset पूर्णांकo the device's pci memory space, and making sure
 *  the pci memory buffers get flushed by perक्रमming one harmless पढ़ो
 *  from the %ISL38XX_PCI_POSTING_FLUSH offset.
 */
अटल अंतरभूत व्योम
isl38xx_w32_flush(व्योम __iomem *base, u32 val, अचिन्हित दीर्घ offset)
अणु
	ग_लिखोl(val, base + offset);
	(व्योम) पढ़ोl(base + ISL38XX_PCI_POSTING_FLUSH);
पूर्ण

/* Device Interrupt रेजिस्टर bits */
#घोषणा ISL38XX_DEV_INT_RESET                   0x0001
#घोषणा ISL38XX_DEV_INT_UPDATE                  0x0002
#घोषणा ISL38XX_DEV_INT_WAKEUP                  0x0008
#घोषणा ISL38XX_DEV_INT_SLEEP                   0x0010

/* Interrupt Identअगरication/Acknowledge/Enable रेजिस्टर bits */
#घोषणा ISL38XX_INT_IDENT_UPDATE                0x0002
#घोषणा ISL38XX_INT_IDENT_INIT                  0x0004
#घोषणा ISL38XX_INT_IDENT_WAKEUP                0x0008
#घोषणा ISL38XX_INT_IDENT_SLEEP                 0x0010
#घोषणा ISL38XX_INT_SOURCES                     0x001E

/* Control/Status रेजिस्टर bits */
/* Looks like there are other meaningful bits
    0x20004400 seen in normal operation,
    0x200044db at 'timeout waiting for mgmt response'
*/
#घोषणा ISL38XX_CTRL_STAT_SLEEPMODE             0x00000200
#घोषणा	ISL38XX_CTRL_STAT_CLKRUN		0x00800000
#घोषणा ISL38XX_CTRL_STAT_RESET                 0x10000000
#घोषणा ISL38XX_CTRL_STAT_RAMBOOT               0x20000000
#घोषणा ISL38XX_CTRL_STAT_STARTHALTED           0x40000000
#घोषणा ISL38XX_CTRL_STAT_HOST_OVERRIDE         0x80000000

/* Control Block definitions */
#घोषणा ISL38XX_CB_RX_DATA_LQ                   0
#घोषणा ISL38XX_CB_TX_DATA_LQ                   1
#घोषणा ISL38XX_CB_RX_DATA_HQ                   2
#घोषणा ISL38XX_CB_TX_DATA_HQ                   3
#घोषणा ISL38XX_CB_RX_MGMTQ                     4
#घोषणा ISL38XX_CB_TX_MGMTQ                     5
#घोषणा ISL38XX_CB_QCOUNT                       6
#घोषणा ISL38XX_CB_MGMT_QSIZE                   4
#घोषणा ISL38XX_MIN_QTHRESHOLD                  4	/* fragments */

/* Memory Manager definitions */
#घोषणा MGMT_FRAME_SIZE                         1500	/* >= size काष्ठा obj_bsslist */
#घोषणा MGMT_TX_FRAME_COUNT                     24	/* max 4 + spare 4 + 8 init */
#घोषणा MGMT_RX_FRAME_COUNT                     24	/* 4*4 + spare 8 */
#घोषणा MGMT_FRAME_COUNT                        (MGMT_TX_FRAME_COUNT + MGMT_RX_FRAME_COUNT)
#घोषणा CONTROL_BLOCK_SIZE                      1024	/* should be enough */
#घोषणा PSM_FRAME_SIZE                          1536
#घोषणा PSM_MINIMAL_STATION_COUNT               64
#घोषणा PSM_FRAME_COUNT                         PSM_MINIMAL_STATION_COUNT
#घोषणा PSM_BUFFER_SIZE                         PSM_FRAME_SIZE * PSM_FRAME_COUNT
#घोषणा MAX_TRAP_RX_QUEUE                       4
#घोषणा HOST_MEM_BLOCK                          CONTROL_BLOCK_SIZE + PSM_BUFFER_SIZE

/* Fragment package definitions */
#घोषणा FRAGMENT_FLAG_MF                        0x0001
#घोषणा MAX_FRAGMENT_SIZE                       1536

/* In monitor mode frames have a header. I करोn't know exactly how big those
 * frame can be but I've never seen any frame bigger than 1584... :
 */
#घोषणा MAX_FRAGMENT_SIZE_RX	                1600

प्रकार काष्ठा अणु
	__le32 address;		/* physical address on host */
	__le16 size;		/* packet size */
	__le16 flags;		/* set of bit-wise flags */
पूर्ण isl38xx_fragment;

काष्ठा isl38xx_cb अणु
	__le32 driver_curr_frag[ISL38XX_CB_QCOUNT];
	__le32 device_curr_frag[ISL38XX_CB_QCOUNT];
	isl38xx_fragment rx_data_low[ISL38XX_CB_RX_QSIZE];
	isl38xx_fragment tx_data_low[ISL38XX_CB_TX_QSIZE];
	isl38xx_fragment rx_data_high[ISL38XX_CB_RX_QSIZE];
	isl38xx_fragment tx_data_high[ISL38XX_CB_TX_QSIZE];
	isl38xx_fragment rx_data_mgmt[ISL38XX_CB_MGMT_QSIZE];
	isl38xx_fragment tx_data_mgmt[ISL38XX_CB_MGMT_QSIZE];
पूर्ण;

प्रकार काष्ठा isl38xx_cb isl38xx_control_block;

/* determine number of entries currently in queue */
पूर्णांक isl38xx_in_queue(isl38xx_control_block *cb, पूर्णांक queue);

व्योम isl38xx_disable_पूर्णांकerrupts(व्योम __iomem *);
व्योम isl38xx_enable_common_पूर्णांकerrupts(व्योम __iomem *);

व्योम isl38xx_handle_sleep_request(isl38xx_control_block *, पूर्णांक *,
				  व्योम __iomem *);
व्योम isl38xx_handle_wakeup(isl38xx_control_block *, पूर्णांक *, व्योम __iomem *);
व्योम isl38xx_trigger_device(पूर्णांक, व्योम __iomem *);
व्योम isl38xx_पूर्णांकerface_reset(व्योम __iomem *, dma_addr_t);

#पूर्ण_अगर				/* _ISL_38XX_H */
