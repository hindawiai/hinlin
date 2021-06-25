<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * DMA driver header क्रम STMicroelectronics STi FDMA controller
 *
 * Copyright (C) 2014 STMicroelectronics
 *
 * Author: Luकरोvic Barre <Luकरोvic.barre@st.com>
 */
#अगर_अघोषित __DMA_ST_FDMA_H
#घोषणा __DMA_ST_FDMA_H

#समावेश <linux/dmaengine.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/पन.स>
#समावेश <linux/remoteproc/st_slim_rproc.h>
#समावेश "virt-dma.h"

#घोषणा ST_FDMA_NR_DREQS 32
#घोषणा FW_NAME_SIZE 30
#घोषणा DRIVER_NAME "st-fdma"

/**
 * काष्ठा st_fdma_generic_node - Free running/paced generic node
 *
 * @length: Length in bytes of a line in a 2D mem to mem
 * @sstride: Stride, in bytes, between source lines in a 2D data move
 * @dstride: Stride, in bytes, between destination lines in a 2D data move
 */
काष्ठा st_fdma_generic_node अणु
	u32 length;
	u32 sstride;
	u32 dstride;
पूर्ण;

/**
 * काष्ठा st_fdma_hw_node - Node काष्ठाure used by fdma hw
 *
 * @next: Poपूर्णांकer to next node
 * @control: Transfer Control Parameters
 * @nbytes: Number of Bytes to पढ़ो
 * @saddr: Source address
 * @daddr: Destination address
 *
 * @generic: generic node क्रम मुक्त running/paced transfert type
 * 2 others transfert type are possible, but not yet implemented
 *
 * The NODE काष्ठाures must be aligned to a 32 byte boundary
 */
काष्ठा st_fdma_hw_node अणु
	u32 next;
	u32 control;
	u32 nbytes;
	u32 saddr;
	u32 daddr;
	जोड़ अणु
		काष्ठा st_fdma_generic_node generic;
	पूर्ण;
पूर्ण __aligned(32);

/*
 * node control parameters
 */
#घोषणा FDMA_NODE_CTRL_REQ_MAP_MASK	GENMASK(4, 0)
#घोषणा FDMA_NODE_CTRL_REQ_MAP_FREE_RUN	0x0
#घोषणा FDMA_NODE_CTRL_REQ_MAP_DREQ(n)	((n)&FDMA_NODE_CTRL_REQ_MAP_MASK)
#घोषणा FDMA_NODE_CTRL_REQ_MAP_EXT		FDMA_NODE_CTRL_REQ_MAP_MASK
#घोषणा FDMA_NODE_CTRL_SRC_MASK		GENMASK(6, 5)
#घोषणा FDMA_NODE_CTRL_SRC_STATIC	BIT(5)
#घोषणा FDMA_NODE_CTRL_SRC_INCR		BIT(6)
#घोषणा FDMA_NODE_CTRL_DST_MASK		GENMASK(8, 7)
#घोषणा FDMA_NODE_CTRL_DST_STATIC	BIT(7)
#घोषणा FDMA_NODE_CTRL_DST_INCR		BIT(8)
#घोषणा FDMA_NODE_CTRL_SECURE		BIT(15)
#घोषणा FDMA_NODE_CTRL_PAUSE_EON	BIT(30)
#घोषणा FDMA_NODE_CTRL_INT_EON		BIT(31)

/**
 * काष्ठा st_fdma_sw_node - descriptor काष्ठाure क्रम link list
 *
 * @pdesc: Physical address of desc
 * @node: link used क्रम putting this पूर्णांकo a channel queue
 */
काष्ठा st_fdma_sw_node अणु
	dma_addr_t pdesc;
	काष्ठा st_fdma_hw_node *desc;
पूर्ण;

#घोषणा NAME_SZ 10

काष्ठा st_fdma_driverdata अणु
	u32 id;
	अक्षर name[NAME_SZ];
पूर्ण;

काष्ठा st_fdma_desc अणु
	काष्ठा virt_dma_desc vdesc;
	काष्ठा st_fdma_chan *fchan;
	bool iscyclic;
	अचिन्हित पूर्णांक n_nodes;
	काष्ठा st_fdma_sw_node node[];
पूर्ण;

क्रमागत st_fdma_type अणु
	ST_FDMA_TYPE_FREE_RUN,
	ST_FDMA_TYPE_PACED,
पूर्ण;

काष्ठा st_fdma_cfg अणु
	काष्ठा device_node *of_node;
	क्रमागत st_fdma_type type;
	dma_addr_t dev_addr;
	क्रमागत dma_transfer_direction dir;
	पूर्णांक req_line; /* request line */
	दीर्घ req_ctrl; /* Request control */
पूर्ण;

काष्ठा st_fdma_chan अणु
	काष्ठा st_fdma_dev *fdev;
	काष्ठा dma_pool *node_pool;
	काष्ठा dma_slave_config scfg;
	काष्ठा st_fdma_cfg cfg;

	पूर्णांक dreq_line;

	काष्ठा virt_dma_chan vchan;
	काष्ठा st_fdma_desc *fdesc;
	क्रमागत dma_status	status;
पूर्ण;

काष्ठा st_fdma_dev अणु
	काष्ठा device *dev;
	स्थिर काष्ठा st_fdma_driverdata *drvdata;
	काष्ठा dma_device dma_device;

	काष्ठा st_slim_rproc *slim_rproc;

	पूर्णांक irq;

	काष्ठा st_fdma_chan *chans;

	spinlock_t dreq_lock;
	अचिन्हित दीर्घ dreq_mask;

	u32 nr_channels;
	अक्षर fw_name[FW_NAME_SIZE];
पूर्ण;

/* Peripheral Registers*/

#घोषणा FDMA_CMD_STA_OFST	0xFC0
#घोषणा FDMA_CMD_SET_OFST	0xFC4
#घोषणा FDMA_CMD_CLR_OFST	0xFC8
#घोषणा FDMA_CMD_MASK_OFST	0xFCC
#घोषणा FDMA_CMD_START(ch)		(0x1 << (ch << 1))
#घोषणा FDMA_CMD_PAUSE(ch)		(0x2 << (ch << 1))
#घोषणा FDMA_CMD_FLUSH(ch)		(0x3 << (ch << 1))

#घोषणा FDMA_INT_STA_OFST	0xFD0
#घोषणा FDMA_INT_STA_CH			0x1
#घोषणा FDMA_INT_STA_ERR		0x2

#घोषणा FDMA_INT_SET_OFST	0xFD4
#घोषणा FDMA_INT_CLR_OFST	0xFD8
#घोषणा FDMA_INT_MASK_OFST	0xFDC

#घोषणा fdma_पढ़ो(fdev, name) \
	पढ़ोl((fdev)->slim_rproc->peri + name)

#घोषणा fdma_ग_लिखो(fdev, val, name) \
	ग_लिखोl((val), (fdev)->slim_rproc->peri + name)

/* fchan पूर्णांकerface (dmem) */
#घोषणा FDMA_CH_CMD_OFST	0x200
#घोषणा FDMA_CH_CMD_STA_MASK		GENMASK(1, 0)
#घोषणा FDMA_CH_CMD_STA_IDLE		(0x0)
#घोषणा FDMA_CH_CMD_STA_START		(0x1)
#घोषणा FDMA_CH_CMD_STA_RUNNING		(0x2)
#घोषणा FDMA_CH_CMD_STA_PAUSED		(0x3)
#घोषणा FDMA_CH_CMD_ERR_MASK		GENMASK(4, 2)
#घोषणा FDMA_CH_CMD_ERR_INT		(0x0 << 2)
#घोषणा FDMA_CH_CMD_ERR_न_अंकD		(0x1 << 2)
#घोषणा FDMA_CH_CMD_ERR_MCHI		(0x2 << 2)
#घोषणा FDMA_CH_CMD_DATA_MASK		GENMASK(31, 5)
#घोषणा fchan_पढ़ो(fchan, name) \
	पढ़ोl((fchan)->fdev->slim_rproc->mem[ST_SLIM_DMEM].cpu_addr \
			+ (fchan)->vchan.chan.chan_id * 0x4 \
			+ name)

#घोषणा fchan_ग_लिखो(fchan, val, name) \
	ग_लिखोl((val), (fchan)->fdev->slim_rproc->mem[ST_SLIM_DMEM].cpu_addr \
			+ (fchan)->vchan.chan.chan_id * 0x4 \
			+ name)

/* req पूर्णांकerface */
#घोषणा FDMA_REQ_CTRL_OFST	0x240
#घोषणा dreq_ग_लिखो(fchan, val, name) \
	ग_लिखोl((val), (fchan)->fdev->slim_rproc->mem[ST_SLIM_DMEM].cpu_addr \
			+ fchan->dreq_line * 0x04 \
			+ name)
/* node पूर्णांकerface */
#घोषणा FDMA_NODE_SZ 128
#घोषणा FDMA_PTRN_OFST		0x800
#घोषणा FDMA_CNTN_OFST		0x808
#घोषणा FDMA_SADDRN_OFST	0x80c
#घोषणा FDMA_DADDRN_OFST	0x810
#घोषणा fnode_पढ़ो(fchan, name) \
	पढ़ोl((fchan)->fdev->slim_rproc->mem[ST_SLIM_DMEM].cpu_addr \
			+ (fchan)->vchan.chan.chan_id * FDMA_NODE_SZ \
			+ name)

#घोषणा fnode_ग_लिखो(fchan, val, name) \
	ग_लिखोl((val), (fchan)->fdev->slim_rproc->mem[ST_SLIM_DMEM].cpu_addr \
			+ (fchan)->vchan.chan.chan_id * FDMA_NODE_SZ \
			+ name)

/*
 * request control bits
 */
#घोषणा FDMA_REQ_CTRL_NUM_OPS_MASK	GENMASK(31, 24)
#घोषणा FDMA_REQ_CTRL_NUM_OPS(n)	(FDMA_REQ_CTRL_NUM_OPS_MASK & \
					((n) << 24))
#घोषणा FDMA_REQ_CTRL_INITIATOR_MASK	BIT(22)
#घोषणा FDMA_REQ_CTRL_INIT0		(0x0 << 22)
#घोषणा FDMA_REQ_CTRL_INIT1		(0x1 << 22)
#घोषणा FDMA_REQ_CTRL_INC_ADDR_ON	BIT(21)
#घोषणा FDMA_REQ_CTRL_DATA_SWAP_ON	BIT(17)
#घोषणा FDMA_REQ_CTRL_WNR		BIT(14)
#घोषणा FDMA_REQ_CTRL_OPCODE_MASK	GENMASK(7, 4)
#घोषणा FDMA_REQ_CTRL_OPCODE_LD_ST1	(0x0 << 4)
#घोषणा FDMA_REQ_CTRL_OPCODE_LD_ST2	(0x1 << 4)
#घोषणा FDMA_REQ_CTRL_OPCODE_LD_ST4	(0x2 << 4)
#घोषणा FDMA_REQ_CTRL_OPCODE_LD_ST8	(0x3 << 4)
#घोषणा FDMA_REQ_CTRL_OPCODE_LD_ST16	(0x4 << 4)
#घोषणा FDMA_REQ_CTRL_OPCODE_LD_ST32	(0x5 << 4)
#घोषणा FDMA_REQ_CTRL_OPCODE_LD_ST64	(0x6 << 4)
#घोषणा FDMA_REQ_CTRL_HOLDOFF_MASK	GENMASK(2, 0)
#घोषणा FDMA_REQ_CTRL_HOLDOFF(n)	((n) & FDMA_REQ_CTRL_HOLDOFF_MASK)

/* bits used by client to configure request control */
#घोषणा FDMA_REQ_CTRL_CFG_MASK (FDMA_REQ_CTRL_HOLDOFF_MASK | \
				FDMA_REQ_CTRL_DATA_SWAP_ON | \
				FDMA_REQ_CTRL_INC_ADDR_ON | \
				FDMA_REQ_CTRL_INITIATOR_MASK)

#पूर्ण_अगर	/* __DMA_ST_FDMA_H */
