<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Xilinx ZynqMP DPDMA Engine driver
 *
 * Copyright (C) 2015 - 2020 Xilinx, Inc.
 *
 * Author: Hyun Woo Kwon <hyun.kwon@xilinx.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/bits.h>
#समावेश <linux/clk.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/रुको.h>

#समावेश <dt-bindings/dma/xlnx-zynqmp-dpdma.h>

#समावेश "../dmaengine.h"
#समावेश "../virt-dma.h"

/* DPDMA रेजिस्टरs */
#घोषणा XILINX_DPDMA_ERR_CTRL				0x000
#घोषणा XILINX_DPDMA_ISR				0x004
#घोषणा XILINX_DPDMA_IMR				0x008
#घोषणा XILINX_DPDMA_IEN				0x00c
#घोषणा XILINX_DPDMA_IDS				0x010
#घोषणा XILINX_DPDMA_INTR_DESC_DONE(n)			BIT((n) + 0)
#घोषणा XILINX_DPDMA_INTR_DESC_DONE_MASK		GENMASK(5, 0)
#घोषणा XILINX_DPDMA_INTR_NO_OSTAND(n)			BIT((n) + 6)
#घोषणा XILINX_DPDMA_INTR_NO_OSTAND_MASK		GENMASK(11, 6)
#घोषणा XILINX_DPDMA_INTR_AXI_ERR(n)			BIT((n) + 12)
#घोषणा XILINX_DPDMA_INTR_AXI_ERR_MASK			GENMASK(17, 12)
#घोषणा XILINX_DPDMA_INTR_DESC_ERR(n)			BIT((n) + 16)
#घोषणा XILINX_DPDMA_INTR_DESC_ERR_MASK			GENMASK(23, 18)
#घोषणा XILINX_DPDMA_INTR_WR_CMD_FIFO_FULL		BIT(24)
#घोषणा XILINX_DPDMA_INTR_WR_DATA_FIFO_FULL		BIT(25)
#घोषणा XILINX_DPDMA_INTR_AXI_4K_CROSS			BIT(26)
#घोषणा XILINX_DPDMA_INTR_VSYNC				BIT(27)
#घोषणा XILINX_DPDMA_INTR_CHAN_ERR_MASK			0x00041000
#घोषणा XILINX_DPDMA_INTR_CHAN_ERR			0x00fff000
#घोषणा XILINX_DPDMA_INTR_GLOBAL_ERR			0x07000000
#घोषणा XILINX_DPDMA_INTR_ERR_ALL			0x07fff000
#घोषणा XILINX_DPDMA_INTR_CHAN_MASK			0x00041041
#घोषणा XILINX_DPDMA_INTR_GLOBAL_MASK			0x0f000000
#घोषणा XILINX_DPDMA_INTR_ALL				0x0fffffff
#घोषणा XILINX_DPDMA_EISR				0x014
#घोषणा XILINX_DPDMA_EIMR				0x018
#घोषणा XILINX_DPDMA_EIEN				0x01c
#घोषणा XILINX_DPDMA_EIDS				0x020
#घोषणा XILINX_DPDMA_EINTR_INV_APB			BIT(0)
#घोषणा XILINX_DPDMA_EINTR_RD_AXI_ERR(n)		BIT((n) + 1)
#घोषणा XILINX_DPDMA_EINTR_RD_AXI_ERR_MASK		GENMASK(6, 1)
#घोषणा XILINX_DPDMA_EINTR_PRE_ERR(n)			BIT((n) + 7)
#घोषणा XILINX_DPDMA_EINTR_PRE_ERR_MASK			GENMASK(12, 7)
#घोषणा XILINX_DPDMA_EINTR_CRC_ERR(n)			BIT((n) + 13)
#घोषणा XILINX_DPDMA_EINTR_CRC_ERR_MASK			GENMASK(18, 13)
#घोषणा XILINX_DPDMA_EINTR_WR_AXI_ERR(n)		BIT((n) + 19)
#घोषणा XILINX_DPDMA_EINTR_WR_AXI_ERR_MASK		GENMASK(24, 19)
#घोषणा XILINX_DPDMA_EINTR_DESC_DONE_ERR(n)		BIT((n) + 25)
#घोषणा XILINX_DPDMA_EINTR_DESC_DONE_ERR_MASK		GENMASK(30, 25)
#घोषणा XILINX_DPDMA_EINTR_RD_CMD_FIFO_FULL		BIT(32)
#घोषणा XILINX_DPDMA_EINTR_CHAN_ERR_MASK		0x02082082
#घोषणा XILINX_DPDMA_EINTR_CHAN_ERR			0x7ffffffe
#घोषणा XILINX_DPDMA_EINTR_GLOBAL_ERR			0x80000001
#घोषणा XILINX_DPDMA_EINTR_ALL				0xffffffff
#घोषणा XILINX_DPDMA_CNTL				0x100
#घोषणा XILINX_DPDMA_GBL				0x104
#घोषणा XILINX_DPDMA_GBL_TRIG_MASK(n)			((n) << 0)
#घोषणा XILINX_DPDMA_GBL_RETRIG_MASK(n)			((n) << 6)
#घोषणा XILINX_DPDMA_ALC0_CNTL				0x108
#घोषणा XILINX_DPDMA_ALC0_STATUS			0x10c
#घोषणा XILINX_DPDMA_ALC0_MAX				0x110
#घोषणा XILINX_DPDMA_ALC0_MIN				0x114
#घोषणा XILINX_DPDMA_ALC0_ACC				0x118
#घोषणा XILINX_DPDMA_ALC0_ACC_TRAN			0x11c
#घोषणा XILINX_DPDMA_ALC1_CNTL				0x120
#घोषणा XILINX_DPDMA_ALC1_STATUS			0x124
#घोषणा XILINX_DPDMA_ALC1_MAX				0x128
#घोषणा XILINX_DPDMA_ALC1_MIN				0x12c
#घोषणा XILINX_DPDMA_ALC1_ACC				0x130
#घोषणा XILINX_DPDMA_ALC1_ACC_TRAN			0x134

/* Channel रेजिस्टर */
#घोषणा XILINX_DPDMA_CH_BASE				0x200
#घोषणा XILINX_DPDMA_CH_OFFSET				0x100
#घोषणा XILINX_DPDMA_CH_DESC_START_ADDRE		0x000
#घोषणा XILINX_DPDMA_CH_DESC_START_ADDRE_MASK		GENMASK(15, 0)
#घोषणा XILINX_DPDMA_CH_DESC_START_ADDR			0x004
#घोषणा XILINX_DPDMA_CH_DESC_NEXT_ADDRE			0x008
#घोषणा XILINX_DPDMA_CH_DESC_NEXT_ADDR			0x00c
#घोषणा XILINX_DPDMA_CH_PYLD_CUR_ADDRE			0x010
#घोषणा XILINX_DPDMA_CH_PYLD_CUR_ADDR			0x014
#घोषणा XILINX_DPDMA_CH_CNTL				0x018
#घोषणा XILINX_DPDMA_CH_CNTL_ENABLE			BIT(0)
#घोषणा XILINX_DPDMA_CH_CNTL_PAUSE			BIT(1)
#घोषणा XILINX_DPDMA_CH_CNTL_QOS_DSCR_WR_MASK		GENMASK(5, 2)
#घोषणा XILINX_DPDMA_CH_CNTL_QOS_DSCR_RD_MASK		GENMASK(9, 6)
#घोषणा XILINX_DPDMA_CH_CNTL_QOS_DATA_RD_MASK		GENMASK(13, 10)
#घोषणा XILINX_DPDMA_CH_CNTL_QOS_VID_CLASS		11
#घोषणा XILINX_DPDMA_CH_STATUS				0x01c
#घोषणा XILINX_DPDMA_CH_STATUS_OTRAN_CNT_MASK		GENMASK(24, 21)
#घोषणा XILINX_DPDMA_CH_VDO				0x020
#घोषणा XILINX_DPDMA_CH_PYLD_SZ				0x024
#घोषणा XILINX_DPDMA_CH_DESC_ID				0x028
#घोषणा XILINX_DPDMA_CH_DESC_ID_MASK			GENMASK(15, 0)

/* DPDMA descriptor fields */
#घोषणा XILINX_DPDMA_DESC_CONTROL_PREEMBLE		0xa5
#घोषणा XILINX_DPDMA_DESC_CONTROL_COMPLETE_INTR		BIT(8)
#घोषणा XILINX_DPDMA_DESC_CONTROL_DESC_UPDATE		BIT(9)
#घोषणा XILINX_DPDMA_DESC_CONTROL_IGNORE_DONE		BIT(10)
#घोषणा XILINX_DPDMA_DESC_CONTROL_FRAG_MODE		BIT(18)
#घोषणा XILINX_DPDMA_DESC_CONTROL_LAST			BIT(19)
#घोषणा XILINX_DPDMA_DESC_CONTROL_ENABLE_CRC		BIT(20)
#घोषणा XILINX_DPDMA_DESC_CONTROL_LAST_OF_FRAME		BIT(21)
#घोषणा XILINX_DPDMA_DESC_ID_MASK			GENMASK(15, 0)
#घोषणा XILINX_DPDMA_DESC_HSIZE_STRIDE_HSIZE_MASK	GENMASK(17, 0)
#घोषणा XILINX_DPDMA_DESC_HSIZE_STRIDE_STRIDE_MASK	GENMASK(31, 18)
#घोषणा XILINX_DPDMA_DESC_ADDR_EXT_NEXT_ADDR_MASK	GENMASK(15, 0)
#घोषणा XILINX_DPDMA_DESC_ADDR_EXT_SRC_ADDR_MASK	GENMASK(31, 16)

#घोषणा XILINX_DPDMA_ALIGN_BYTES			256
#घोषणा XILINX_DPDMA_LINESIZE_ALIGN_BITS		128

#घोषणा XILINX_DPDMA_NUM_CHAN				6

काष्ठा xilinx_dpdma_chan;

/**
 * काष्ठा xilinx_dpdma_hw_desc - DPDMA hardware descriptor
 * @control: control configuration field
 * @desc_id: descriptor ID
 * @xfer_size: transfer size
 * @hsize_stride: horizontal size and stride
 * @बारtamp_lsb: LSB of समय stamp
 * @बारtamp_msb: MSB of समय stamp
 * @addr_ext: upper 16 bit of 48 bit address (next_desc and src_addr)
 * @next_desc: next descriptor 32 bit address
 * @src_addr: payload source address (1st page, 32 LSB)
 * @addr_ext_23: payload source address (3nd and 3rd pages, 16 LSBs)
 * @addr_ext_45: payload source address (4th and 5th pages, 16 LSBs)
 * @src_addr2: payload source address (2nd page, 32 LSB)
 * @src_addr3: payload source address (3rd page, 32 LSB)
 * @src_addr4: payload source address (4th page, 32 LSB)
 * @src_addr5: payload source address (5th page, 32 LSB)
 * @crc: descriptor CRC
 */
काष्ठा xilinx_dpdma_hw_desc अणु
	u32 control;
	u32 desc_id;
	u32 xfer_size;
	u32 hsize_stride;
	u32 बारtamp_lsb;
	u32 बारtamp_msb;
	u32 addr_ext;
	u32 next_desc;
	u32 src_addr;
	u32 addr_ext_23;
	u32 addr_ext_45;
	u32 src_addr2;
	u32 src_addr3;
	u32 src_addr4;
	u32 src_addr5;
	u32 crc;
पूर्ण __aligned(XILINX_DPDMA_ALIGN_BYTES);

/**
 * काष्ठा xilinx_dpdma_sw_desc - DPDMA software descriptor
 * @hw: DPDMA hardware descriptor
 * @node: list node क्रम software descriptors
 * @dma_addr: DMA address of the software descriptor
 */
काष्ठा xilinx_dpdma_sw_desc अणु
	काष्ठा xilinx_dpdma_hw_desc hw;
	काष्ठा list_head node;
	dma_addr_t dma_addr;
पूर्ण;

/**
 * काष्ठा xilinx_dpdma_tx_desc - DPDMA transaction descriptor
 * @vdesc: भव DMA descriptor
 * @chan: DMA channel
 * @descriptors: list of software descriptors
 * @error: an error has been detected with this descriptor
 */
काष्ठा xilinx_dpdma_tx_desc अणु
	काष्ठा virt_dma_desc vdesc;
	काष्ठा xilinx_dpdma_chan *chan;
	काष्ठा list_head descriptors;
	bool error;
पूर्ण;

#घोषणा to_dpdma_tx_desc(_desc) \
	container_of(_desc, काष्ठा xilinx_dpdma_tx_desc, vdesc)

/**
 * काष्ठा xilinx_dpdma_chan - DPDMA channel
 * @vchan: भव DMA channel
 * @reg: रेजिस्टर base address
 * @id: channel ID
 * @रुको_to_stop: queue to रुको क्रम outstanding transacitons beक्रमe stopping
 * @running: true अगर the channel is running
 * @first_frame: flag क्रम the first frame of stream
 * @video_group: flag अगर multi-channel operation is needed क्रम video channels
 * @lock: lock to access काष्ठा xilinx_dpdma_chan
 * @desc_pool: descriptor allocation pool
 * @err_task: error IRQ bottom half handler
 * @desc: References to descriptors being processed
 * @desc.pending: Descriptor schedule to the hardware, pending execution
 * @desc.active: Descriptor being executed by the hardware
 * @xdev: DPDMA device
 */
काष्ठा xilinx_dpdma_chan अणु
	काष्ठा virt_dma_chan vchan;
	व्योम __iomem *reg;
	अचिन्हित पूर्णांक id;

	रुको_queue_head_t रुको_to_stop;
	bool running;
	bool first_frame;
	bool video_group;

	spinlock_t lock; /* lock to access काष्ठा xilinx_dpdma_chan */
	काष्ठा dma_pool *desc_pool;
	काष्ठा tasklet_काष्ठा err_task;

	काष्ठा अणु
		काष्ठा xilinx_dpdma_tx_desc *pending;
		काष्ठा xilinx_dpdma_tx_desc *active;
	पूर्ण desc;

	काष्ठा xilinx_dpdma_device *xdev;
पूर्ण;

#घोषणा to_xilinx_chan(_chan) \
	container_of(_chan, काष्ठा xilinx_dpdma_chan, vchan.chan)

/**
 * काष्ठा xilinx_dpdma_device - DPDMA device
 * @common: generic dma device काष्ठाure
 * @reg: रेजिस्टर base address
 * @dev: generic device काष्ठाure
 * @irq: the पूर्णांकerrupt number
 * @axi_clk: axi घड़ी
 * @chan: DPDMA channels
 * @ext_addr: flag क्रम 64 bit प्रणाली (48 bit addressing)
 */
काष्ठा xilinx_dpdma_device अणु
	काष्ठा dma_device common;
	व्योम __iomem *reg;
	काष्ठा device *dev;
	पूर्णांक irq;

	काष्ठा clk *axi_clk;
	काष्ठा xilinx_dpdma_chan *chan[XILINX_DPDMA_NUM_CHAN];

	bool ext_addr;
पूर्ण;

/* -----------------------------------------------------------------------------
 * DebugFS
 */

#अगर_घोषित CONFIG_DEBUG_FS

#घोषणा XILINX_DPDMA_DEBUGFS_READ_MAX_SIZE	32
#घोषणा XILINX_DPDMA_DEBUGFS_UINT16_MAX_STR	"65535"

/* Match xilinx_dpdma_testहालs vs dpdma_debugfs_reqs[] entry */
क्रमागत xilinx_dpdma_testहालs अणु
	DPDMA_TC_INTR_DONE,
	DPDMA_TC_NONE
पूर्ण;

काष्ठा xilinx_dpdma_debugfs अणु
	क्रमागत xilinx_dpdma_testहालs testहाल;
	u16 xilinx_dpdma_irq_करोne_count;
	अचिन्हित पूर्णांक chan_id;
पूर्ण;

अटल काष्ठा xilinx_dpdma_debugfs dpdma_debugfs;
काष्ठा xilinx_dpdma_debugfs_request अणु
	स्थिर अक्षर *name;
	क्रमागत xilinx_dpdma_testहालs tc;
	sमाप_प्रकार (*पढ़ो)(अक्षर *buf);
	पूर्णांक (*ग_लिखो)(अक्षर *args);
पूर्ण;

अटल व्योम xilinx_dpdma_debugfs_desc_करोne_irq(काष्ठा xilinx_dpdma_chan *chan)
अणु
	अगर (chan->id == dpdma_debugfs.chan_id)
		dpdma_debugfs.xilinx_dpdma_irq_करोne_count++;
पूर्ण

अटल sमाप_प्रकार xilinx_dpdma_debugfs_desc_करोne_irq_पढ़ो(अक्षर *buf)
अणु
	माप_प्रकार out_str_len;

	dpdma_debugfs.testहाल = DPDMA_TC_NONE;

	out_str_len = म_माप(XILINX_DPDMA_DEBUGFS_UINT16_MAX_STR);
	out_str_len = min_t(माप_प्रकार, XILINX_DPDMA_DEBUGFS_READ_MAX_SIZE,
			    out_str_len);
	snम_लिखो(buf, out_str_len, "%d",
		 dpdma_debugfs.xilinx_dpdma_irq_करोne_count);

	वापस 0;
पूर्ण

अटल पूर्णांक xilinx_dpdma_debugfs_desc_करोne_irq_ग_लिखो(अक्षर *args)
अणु
	अक्षर *arg;
	पूर्णांक ret;
	u32 id;

	arg = strsep(&args, " ");
	अगर (!arg || strnहालcmp(arg, "start", 5))
		वापस -EINVAL;

	arg = strsep(&args, " ");
	अगर (!arg)
		वापस -EINVAL;

	ret = kstrtou32(arg, 0, &id);
	अगर (ret < 0)
		वापस ret;

	अगर (id < ZYNQMP_DPDMA_VIDEO0 || id > ZYNQMP_DPDMA_AUDIO1)
		वापस -EINVAL;

	dpdma_debugfs.testहाल = DPDMA_TC_INTR_DONE;
	dpdma_debugfs.xilinx_dpdma_irq_करोne_count = 0;
	dpdma_debugfs.chan_id = id;

	वापस 0;
पूर्ण

/* Match xilinx_dpdma_testहालs vs dpdma_debugfs_reqs[] entry */
अटल काष्ठा xilinx_dpdma_debugfs_request dpdma_debugfs_reqs[] = अणु
	अणु
		.name = "DESCRIPTOR_DONE_INTR",
		.tc = DPDMA_TC_INTR_DONE,
		.पढ़ो = xilinx_dpdma_debugfs_desc_करोne_irq_पढ़ो,
		.ग_लिखो = xilinx_dpdma_debugfs_desc_करोne_irq_ग_लिखो,
	पूर्ण,
पूर्ण;

अटल sमाप_प्रकार xilinx_dpdma_debugfs_पढ़ो(काष्ठा file *f, अक्षर __user *buf,
					 माप_प्रकार size, loff_t *pos)
अणु
	क्रमागत xilinx_dpdma_testहालs testहाल;
	अक्षर *kern_buff;
	पूर्णांक ret = 0;

	अगर (*pos != 0 || size <= 0)
		वापस -EINVAL;

	kern_buff = kzalloc(XILINX_DPDMA_DEBUGFS_READ_MAX_SIZE, GFP_KERNEL);
	अगर (!kern_buff) अणु
		dpdma_debugfs.testहाल = DPDMA_TC_NONE;
		वापस -ENOMEM;
	पूर्ण

	testहाल = READ_ONCE(dpdma_debugfs.testहाल);
	अगर (testहाल != DPDMA_TC_NONE) अणु
		ret = dpdma_debugfs_reqs[testहाल].पढ़ो(kern_buff);
		अगर (ret < 0)
			जाओ करोne;
	पूर्ण अन्यथा अणु
		strlcpy(kern_buff, "No testcase executed",
			XILINX_DPDMA_DEBUGFS_READ_MAX_SIZE);
	पूर्ण

	size = min(size, म_माप(kern_buff));
	अगर (copy_to_user(buf, kern_buff, size))
		ret = -EFAULT;

करोne:
	kमुक्त(kern_buff);
	अगर (ret)
		वापस ret;

	*pos = size + 1;
	वापस size;
पूर्ण

अटल sमाप_प्रकार xilinx_dpdma_debugfs_ग_लिखो(काष्ठा file *f,
					  स्थिर अक्षर __user *buf, माप_प्रकार size,
					  loff_t *pos)
अणु
	अक्षर *kern_buff, *kern_buff_start;
	अक्षर *testहाल;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (*pos != 0 || size <= 0)
		वापस -EINVAL;

	/* Supporting single instance of test as of now. */
	अगर (dpdma_debugfs.testहाल != DPDMA_TC_NONE)
		वापस -EBUSY;

	kern_buff = kzalloc(size, GFP_KERNEL);
	अगर (!kern_buff)
		वापस -ENOMEM;
	kern_buff_start = kern_buff;

	ret = म_नकलन_from_user(kern_buff, buf, size);
	अगर (ret < 0)
		जाओ करोne;

	/* Read the testहाल name from a user request. */
	testहाल = strsep(&kern_buff, " ");

	क्रम (i = 0; i < ARRAY_SIZE(dpdma_debugfs_reqs); i++) अणु
		अगर (!strहालcmp(testहाल, dpdma_debugfs_reqs[i].name))
			अवरोध;
	पूर्ण

	अगर (i == ARRAY_SIZE(dpdma_debugfs_reqs)) अणु
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	ret = dpdma_debugfs_reqs[i].ग_लिखो(kern_buff);
	अगर (ret < 0)
		जाओ करोne;

	ret = size;

करोne:
	kमुक्त(kern_buff_start);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_xilinx_dpdma_dbgfs = अणु
	.owner = THIS_MODULE,
	.पढ़ो = xilinx_dpdma_debugfs_पढ़ो,
	.ग_लिखो = xilinx_dpdma_debugfs_ग_लिखो,
पूर्ण;

अटल व्योम xilinx_dpdma_debugfs_init(काष्ठा xilinx_dpdma_device *xdev)
अणु
	काष्ठा dentry *dent;

	dpdma_debugfs.testहाल = DPDMA_TC_NONE;

	dent = debugfs_create_file("testcase", 0444, xdev->common.dbg_dev_root,
				   शून्य, &fops_xilinx_dpdma_dbgfs);
	अगर (IS_ERR(dent))
		dev_err(xdev->dev, "Failed to create debugfs testcase file\n");
पूर्ण

#अन्यथा
अटल व्योम xilinx_dpdma_debugfs_init(काष्ठा xilinx_dpdma_device *xdev)
अणु
पूर्ण

अटल व्योम xilinx_dpdma_debugfs_desc_करोne_irq(काष्ठा xilinx_dpdma_chan *chan)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_DEBUG_FS */

/* -----------------------------------------------------------------------------
 * I/O Accessors
 */

अटल अंतरभूत u32 dpdma_पढ़ो(व्योम __iomem *base, u32 offset)
अणु
	वापस ioपढ़ो32(base + offset);
पूर्ण

अटल अंतरभूत व्योम dpdma_ग_लिखो(व्योम __iomem *base, u32 offset, u32 val)
अणु
	ioग_लिखो32(val, base + offset);
पूर्ण

अटल अंतरभूत व्योम dpdma_clr(व्योम __iomem *base, u32 offset, u32 clr)
अणु
	dpdma_ग_लिखो(base, offset, dpdma_पढ़ो(base, offset) & ~clr);
पूर्ण

अटल अंतरभूत व्योम dpdma_set(व्योम __iomem *base, u32 offset, u32 set)
अणु
	dpdma_ग_लिखो(base, offset, dpdma_पढ़ो(base, offset) | set);
पूर्ण

/* -----------------------------------------------------------------------------
 * Descriptor Operations
 */

/**
 * xilinx_dpdma_sw_desc_set_dma_addrs - Set DMA addresses in the descriptor
 * @xdev: DPDMA device
 * @sw_desc: The software descriptor in which to set DMA addresses
 * @prev: The previous descriptor
 * @dma_addr: array of dma addresses
 * @num_src_addr: number of addresses in @dma_addr
 *
 * Set all the DMA addresses in the hardware descriptor corresponding to @dev
 * from @dma_addr. If a previous descriptor is specअगरied in @prev, its next
 * descriptor DMA address is set to the DMA address of @sw_desc. @prev may be
 * identical to @sw_desc क्रम cyclic transfers.
 */
अटल व्योम xilinx_dpdma_sw_desc_set_dma_addrs(काष्ठा xilinx_dpdma_device *xdev,
					       काष्ठा xilinx_dpdma_sw_desc *sw_desc,
					       काष्ठा xilinx_dpdma_sw_desc *prev,
					       dma_addr_t dma_addr[],
					       अचिन्हित पूर्णांक num_src_addr)
अणु
	काष्ठा xilinx_dpdma_hw_desc *hw_desc = &sw_desc->hw;
	अचिन्हित पूर्णांक i;

	hw_desc->src_addr = lower_32_bits(dma_addr[0]);
	अगर (xdev->ext_addr)
		hw_desc->addr_ext |=
			FIELD_PREP(XILINX_DPDMA_DESC_ADDR_EXT_SRC_ADDR_MASK,
				   upper_32_bits(dma_addr[0]));

	क्रम (i = 1; i < num_src_addr; i++) अणु
		u32 *addr = &hw_desc->src_addr2;

		addr[i-1] = lower_32_bits(dma_addr[i]);

		अगर (xdev->ext_addr) अणु
			u32 *addr_ext = &hw_desc->addr_ext_23;
			u32 addr_msb;

			addr_msb = upper_32_bits(dma_addr[i]) & GENMASK(15, 0);
			addr_msb <<= 16 * ((i - 1) % 2);
			addr_ext[(i - 1) / 2] |= addr_msb;
		पूर्ण
	पूर्ण

	अगर (!prev)
		वापस;

	prev->hw.next_desc = lower_32_bits(sw_desc->dma_addr);
	अगर (xdev->ext_addr)
		prev->hw.addr_ext |=
			FIELD_PREP(XILINX_DPDMA_DESC_ADDR_EXT_NEXT_ADDR_MASK,
				   upper_32_bits(sw_desc->dma_addr));
पूर्ण

/**
 * xilinx_dpdma_chan_alloc_sw_desc - Allocate a software descriptor
 * @chan: DPDMA channel
 *
 * Allocate a software descriptor from the channel's descriptor pool.
 *
 * Return: a software descriptor or शून्य.
 */
अटल काष्ठा xilinx_dpdma_sw_desc *
xilinx_dpdma_chan_alloc_sw_desc(काष्ठा xilinx_dpdma_chan *chan)
अणु
	काष्ठा xilinx_dpdma_sw_desc *sw_desc;
	dma_addr_t dma_addr;

	sw_desc = dma_pool_zalloc(chan->desc_pool, GFP_ATOMIC, &dma_addr);
	अगर (!sw_desc)
		वापस शून्य;

	sw_desc->dma_addr = dma_addr;

	वापस sw_desc;
पूर्ण

/**
 * xilinx_dpdma_chan_मुक्त_sw_desc - Free a software descriptor
 * @chan: DPDMA channel
 * @sw_desc: software descriptor to मुक्त
 *
 * Free a software descriptor from the channel's descriptor pool.
 */
अटल व्योम
xilinx_dpdma_chan_मुक्त_sw_desc(काष्ठा xilinx_dpdma_chan *chan,
			       काष्ठा xilinx_dpdma_sw_desc *sw_desc)
अणु
	dma_pool_मुक्त(chan->desc_pool, sw_desc, sw_desc->dma_addr);
पूर्ण

/**
 * xilinx_dpdma_chan_dump_tx_desc - Dump a tx descriptor
 * @chan: DPDMA channel
 * @tx_desc: tx descriptor to dump
 *
 * Dump contents of a tx descriptor
 */
अटल व्योम xilinx_dpdma_chan_dump_tx_desc(काष्ठा xilinx_dpdma_chan *chan,
					   काष्ठा xilinx_dpdma_tx_desc *tx_desc)
अणु
	काष्ठा xilinx_dpdma_sw_desc *sw_desc;
	काष्ठा device *dev = chan->xdev->dev;
	अचिन्हित पूर्णांक i = 0;

	dev_dbg(dev, "------- TX descriptor dump start -------\n");
	dev_dbg(dev, "------- channel ID = %d -------\n", chan->id);

	list_क्रम_each_entry(sw_desc, &tx_desc->descriptors, node) अणु
		काष्ठा xilinx_dpdma_hw_desc *hw_desc = &sw_desc->hw;

		dev_dbg(dev, "------- HW descriptor %d -------\n", i++);
		dev_dbg(dev, "descriptor DMA addr: %pad\n", &sw_desc->dma_addr);
		dev_dbg(dev, "control: 0x%08x\n", hw_desc->control);
		dev_dbg(dev, "desc_id: 0x%08x\n", hw_desc->desc_id);
		dev_dbg(dev, "xfer_size: 0x%08x\n", hw_desc->xfer_size);
		dev_dbg(dev, "hsize_stride: 0x%08x\n", hw_desc->hsize_stride);
		dev_dbg(dev, "timestamp_lsb: 0x%08x\n", hw_desc->बारtamp_lsb);
		dev_dbg(dev, "timestamp_msb: 0x%08x\n", hw_desc->बारtamp_msb);
		dev_dbg(dev, "addr_ext: 0x%08x\n", hw_desc->addr_ext);
		dev_dbg(dev, "next_desc: 0x%08x\n", hw_desc->next_desc);
		dev_dbg(dev, "src_addr: 0x%08x\n", hw_desc->src_addr);
		dev_dbg(dev, "addr_ext_23: 0x%08x\n", hw_desc->addr_ext_23);
		dev_dbg(dev, "addr_ext_45: 0x%08x\n", hw_desc->addr_ext_45);
		dev_dbg(dev, "src_addr2: 0x%08x\n", hw_desc->src_addr2);
		dev_dbg(dev, "src_addr3: 0x%08x\n", hw_desc->src_addr3);
		dev_dbg(dev, "src_addr4: 0x%08x\n", hw_desc->src_addr4);
		dev_dbg(dev, "src_addr5: 0x%08x\n", hw_desc->src_addr5);
		dev_dbg(dev, "crc: 0x%08x\n", hw_desc->crc);
	पूर्ण

	dev_dbg(dev, "------- TX descriptor dump end -------\n");
पूर्ण

/**
 * xilinx_dpdma_chan_alloc_tx_desc - Allocate a transaction descriptor
 * @chan: DPDMA channel
 *
 * Allocate a tx descriptor.
 *
 * Return: a tx descriptor or शून्य.
 */
अटल काष्ठा xilinx_dpdma_tx_desc *
xilinx_dpdma_chan_alloc_tx_desc(काष्ठा xilinx_dpdma_chan *chan)
अणु
	काष्ठा xilinx_dpdma_tx_desc *tx_desc;

	tx_desc = kzalloc(माप(*tx_desc), GFP_NOWAIT);
	अगर (!tx_desc)
		वापस शून्य;

	INIT_LIST_HEAD(&tx_desc->descriptors);
	tx_desc->chan = chan;
	tx_desc->error = false;

	वापस tx_desc;
पूर्ण

/**
 * xilinx_dpdma_chan_मुक्त_tx_desc - Free a भव DMA descriptor
 * @vdesc: भव DMA descriptor
 *
 * Free the भव DMA descriptor @vdesc including its software descriptors.
 */
अटल व्योम xilinx_dpdma_chan_मुक्त_tx_desc(काष्ठा virt_dma_desc *vdesc)
अणु
	काष्ठा xilinx_dpdma_sw_desc *sw_desc, *next;
	काष्ठा xilinx_dpdma_tx_desc *desc;

	अगर (!vdesc)
		वापस;

	desc = to_dpdma_tx_desc(vdesc);

	list_क्रम_each_entry_safe(sw_desc, next, &desc->descriptors, node) अणु
		list_del(&sw_desc->node);
		xilinx_dpdma_chan_मुक्त_sw_desc(desc->chan, sw_desc);
	पूर्ण

	kमुक्त(desc);
पूर्ण

/**
 * xilinx_dpdma_chan_prep_पूर्णांकerleaved_dma - Prepare an पूर्णांकerleaved dma
 *					    descriptor
 * @chan: DPDMA channel
 * @xt: dma पूर्णांकerleaved ढाँचा
 *
 * Prepare a tx descriptor including पूर्णांकernal software/hardware descriptors
 * based on @xt.
 *
 * Return: A DPDMA TX descriptor on success, or शून्य.
 */
अटल काष्ठा xilinx_dpdma_tx_desc *
xilinx_dpdma_chan_prep_पूर्णांकerleaved_dma(काष्ठा xilinx_dpdma_chan *chan,
				       काष्ठा dma_पूर्णांकerleaved_ढाँचा *xt)
अणु
	काष्ठा xilinx_dpdma_tx_desc *tx_desc;
	काष्ठा xilinx_dpdma_sw_desc *sw_desc;
	काष्ठा xilinx_dpdma_hw_desc *hw_desc;
	माप_प्रकार hsize = xt->sgl[0].size;
	माप_प्रकार stride = hsize + xt->sgl[0].icg;

	अगर (!IS_ALIGNED(xt->src_start, XILINX_DPDMA_ALIGN_BYTES)) अणु
		dev_err(chan->xdev->dev, "buffer should be aligned at %d B\n",
			XILINX_DPDMA_ALIGN_BYTES);
		वापस शून्य;
	पूर्ण

	tx_desc = xilinx_dpdma_chan_alloc_tx_desc(chan);
	अगर (!tx_desc)
		वापस शून्य;

	sw_desc = xilinx_dpdma_chan_alloc_sw_desc(chan);
	अगर (!sw_desc) अणु
		xilinx_dpdma_chan_मुक्त_tx_desc(&tx_desc->vdesc);
		वापस शून्य;
	पूर्ण

	xilinx_dpdma_sw_desc_set_dma_addrs(chan->xdev, sw_desc, sw_desc,
					   &xt->src_start, 1);

	hw_desc = &sw_desc->hw;
	hsize = ALIGN(hsize, XILINX_DPDMA_LINESIZE_ALIGN_BITS / 8);
	hw_desc->xfer_size = hsize * xt->numf;
	hw_desc->hsize_stride =
		FIELD_PREP(XILINX_DPDMA_DESC_HSIZE_STRIDE_HSIZE_MASK, hsize) |
		FIELD_PREP(XILINX_DPDMA_DESC_HSIZE_STRIDE_STRIDE_MASK,
			   stride / 16);
	hw_desc->control |= XILINX_DPDMA_DESC_CONTROL_PREEMBLE;
	hw_desc->control |= XILINX_DPDMA_DESC_CONTROL_COMPLETE_INTR;
	hw_desc->control |= XILINX_DPDMA_DESC_CONTROL_IGNORE_DONE;
	hw_desc->control |= XILINX_DPDMA_DESC_CONTROL_LAST_OF_FRAME;

	list_add_tail(&sw_desc->node, &tx_desc->descriptors);

	वापस tx_desc;
पूर्ण

/* -----------------------------------------------------------------------------
 * DPDMA Channel Operations
 */

/**
 * xilinx_dpdma_chan_enable - Enable the channel
 * @chan: DPDMA channel
 *
 * Enable the channel and its पूर्णांकerrupts. Set the QoS values क्रम video class.
 */
अटल व्योम xilinx_dpdma_chan_enable(काष्ठा xilinx_dpdma_chan *chan)
अणु
	u32 reg;

	reg = (XILINX_DPDMA_INTR_CHAN_MASK << chan->id)
	    | XILINX_DPDMA_INTR_GLOBAL_MASK;
	dpdma_ग_लिखो(chan->xdev->reg, XILINX_DPDMA_IEN, reg);
	reg = (XILINX_DPDMA_EINTR_CHAN_ERR_MASK << chan->id)
	    | XILINX_DPDMA_INTR_GLOBAL_ERR;
	dpdma_ग_लिखो(chan->xdev->reg, XILINX_DPDMA_EIEN, reg);

	reg = XILINX_DPDMA_CH_CNTL_ENABLE
	    | FIELD_PREP(XILINX_DPDMA_CH_CNTL_QOS_DSCR_WR_MASK,
			 XILINX_DPDMA_CH_CNTL_QOS_VID_CLASS)
	    | FIELD_PREP(XILINX_DPDMA_CH_CNTL_QOS_DSCR_RD_MASK,
			 XILINX_DPDMA_CH_CNTL_QOS_VID_CLASS)
	    | FIELD_PREP(XILINX_DPDMA_CH_CNTL_QOS_DATA_RD_MASK,
			 XILINX_DPDMA_CH_CNTL_QOS_VID_CLASS);
	dpdma_set(chan->reg, XILINX_DPDMA_CH_CNTL, reg);
पूर्ण

/**
 * xilinx_dpdma_chan_disable - Disable the channel
 * @chan: DPDMA channel
 *
 * Disable the channel and its पूर्णांकerrupts.
 */
अटल व्योम xilinx_dpdma_chan_disable(काष्ठा xilinx_dpdma_chan *chan)
अणु
	u32 reg;

	reg = XILINX_DPDMA_INTR_CHAN_MASK << chan->id;
	dpdma_ग_लिखो(chan->xdev->reg, XILINX_DPDMA_IEN, reg);
	reg = XILINX_DPDMA_EINTR_CHAN_ERR_MASK << chan->id;
	dpdma_ग_लिखो(chan->xdev->reg, XILINX_DPDMA_EIEN, reg);

	dpdma_clr(chan->reg, XILINX_DPDMA_CH_CNTL, XILINX_DPDMA_CH_CNTL_ENABLE);
पूर्ण

/**
 * xilinx_dpdma_chan_छोड़ो - Pause the channel
 * @chan: DPDMA channel
 *
 * Pause the channel.
 */
अटल व्योम xilinx_dpdma_chan_छोड़ो(काष्ठा xilinx_dpdma_chan *chan)
अणु
	dpdma_set(chan->reg, XILINX_DPDMA_CH_CNTL, XILINX_DPDMA_CH_CNTL_PAUSE);
पूर्ण

/**
 * xilinx_dpdma_chan_unछोड़ो - Unछोड़ो the channel
 * @chan: DPDMA channel
 *
 * Unछोड़ो the channel.
 */
अटल व्योम xilinx_dpdma_chan_unछोड़ो(काष्ठा xilinx_dpdma_chan *chan)
अणु
	dpdma_clr(chan->reg, XILINX_DPDMA_CH_CNTL, XILINX_DPDMA_CH_CNTL_PAUSE);
पूर्ण

अटल u32 xilinx_dpdma_chan_video_group_पढ़ोy(काष्ठा xilinx_dpdma_chan *chan)
अणु
	काष्ठा xilinx_dpdma_device *xdev = chan->xdev;
	u32 channels = 0;
	अचिन्हित पूर्णांक i;

	क्रम (i = ZYNQMP_DPDMA_VIDEO0; i <= ZYNQMP_DPDMA_VIDEO2; i++) अणु
		अगर (xdev->chan[i]->video_group && !xdev->chan[i]->running)
			वापस 0;

		अगर (xdev->chan[i]->video_group)
			channels |= BIT(i);
	पूर्ण

	वापस channels;
पूर्ण

/**
 * xilinx_dpdma_chan_queue_transfer - Queue the next transfer
 * @chan: DPDMA channel
 *
 * Queue the next descriptor, अगर any, to the hardware. If the channel is
 * stopped, start it first. Otherwise retrigger it with the next descriptor.
 */
अटल व्योम xilinx_dpdma_chan_queue_transfer(काष्ठा xilinx_dpdma_chan *chan)
अणु
	काष्ठा xilinx_dpdma_device *xdev = chan->xdev;
	काष्ठा xilinx_dpdma_sw_desc *sw_desc;
	काष्ठा xilinx_dpdma_tx_desc *desc;
	काष्ठा virt_dma_desc *vdesc;
	u32 reg, channels;
	bool first_frame;

	lockdep_निश्चित_held(&chan->lock);

	अगर (chan->desc.pending)
		वापस;

	अगर (!chan->running) अणु
		xilinx_dpdma_chan_unछोड़ो(chan);
		xilinx_dpdma_chan_enable(chan);
		chan->first_frame = true;
		chan->running = true;
	पूर्ण

	vdesc = vchan_next_desc(&chan->vchan);
	अगर (!vdesc)
		वापस;

	desc = to_dpdma_tx_desc(vdesc);
	chan->desc.pending = desc;
	list_del(&desc->vdesc.node);

	/*
	 * Assign the cookie to descriptors in this transaction. Only 16 bit
	 * will be used, but it should be enough.
	 */
	list_क्रम_each_entry(sw_desc, &desc->descriptors, node)
		sw_desc->hw.desc_id = desc->vdesc.tx.cookie
				    & XILINX_DPDMA_CH_DESC_ID_MASK;

	sw_desc = list_first_entry(&desc->descriptors,
				   काष्ठा xilinx_dpdma_sw_desc, node);
	dpdma_ग_लिखो(chan->reg, XILINX_DPDMA_CH_DESC_START_ADDR,
		    lower_32_bits(sw_desc->dma_addr));
	अगर (xdev->ext_addr)
		dpdma_ग_लिखो(chan->reg, XILINX_DPDMA_CH_DESC_START_ADDRE,
			    FIELD_PREP(XILINX_DPDMA_CH_DESC_START_ADDRE_MASK,
				       upper_32_bits(sw_desc->dma_addr)));

	first_frame = chan->first_frame;
	chan->first_frame = false;

	अगर (chan->video_group) अणु
		channels = xilinx_dpdma_chan_video_group_पढ़ोy(chan);
		/*
		 * Trigger the transfer only when all channels in the group are
		 * पढ़ोy.
		 */
		अगर (!channels)
			वापस;
	पूर्ण अन्यथा अणु
		channels = BIT(chan->id);
	पूर्ण

	अगर (first_frame)
		reg = XILINX_DPDMA_GBL_TRIG_MASK(channels);
	अन्यथा
		reg = XILINX_DPDMA_GBL_RETRIG_MASK(channels);

	dpdma_ग_लिखो(xdev->reg, XILINX_DPDMA_GBL, reg);
पूर्ण

/**
 * xilinx_dpdma_chan_ostand - Number of outstanding transactions
 * @chan: DPDMA channel
 *
 * Read and वापस the number of outstanding transactions from रेजिस्टर.
 *
 * Return: Number of outstanding transactions from the status रेजिस्टर.
 */
अटल u32 xilinx_dpdma_chan_ostand(काष्ठा xilinx_dpdma_chan *chan)
अणु
	वापस FIELD_GET(XILINX_DPDMA_CH_STATUS_OTRAN_CNT_MASK,
			 dpdma_पढ़ो(chan->reg, XILINX_DPDMA_CH_STATUS));
पूर्ण

/**
 * xilinx_dpdma_chan_no_ostand - Notअगरy no outstanding transaction event
 * @chan: DPDMA channel
 *
 * Notअगरy रुकोers क्रम no outstanding event, so रुकोers can stop the channel
 * safely. This function is supposed to be called when 'no outstanding'
 * पूर्णांकerrupt is generated. The 'no outstanding' पूर्णांकerrupt is disabled and
 * should be re-enabled when this event is handled. If the channel status
 * रेजिस्टर still shows some number of outstanding transactions, the पूर्णांकerrupt
 * reमुख्यs enabled.
 *
 * Return: 0 on success. On failure, -EWOULDBLOCK अगर there's still outstanding
 * transaction(s).
 */
अटल पूर्णांक xilinx_dpdma_chan_notअगरy_no_ostand(काष्ठा xilinx_dpdma_chan *chan)
अणु
	u32 cnt;

	cnt = xilinx_dpdma_chan_ostand(chan);
	अगर (cnt) अणु
		dev_dbg(chan->xdev->dev, "%d outstanding transactions\n", cnt);
		वापस -EWOULDBLOCK;
	पूर्ण

	/* Disable 'no outstanding' पूर्णांकerrupt */
	dpdma_ग_लिखो(chan->xdev->reg, XILINX_DPDMA_IDS,
		    XILINX_DPDMA_INTR_NO_OSTAND(chan->id));
	wake_up(&chan->रुको_to_stop);

	वापस 0;
पूर्ण

/**
 * xilinx_dpdma_chan_रुको_no_ostand - Wait क्रम the no outstanding irq
 * @chan: DPDMA channel
 *
 * Wait क्रम the no outstanding transaction पूर्णांकerrupt. This functions can sleep
 * क्रम 50ms.
 *
 * Return: 0 on success. On failure, -ETIMEOUT क्रम समय out, or the error code
 * from रुको_event_पूर्णांकerruptible_समयout().
 */
अटल पूर्णांक xilinx_dpdma_chan_रुको_no_ostand(काष्ठा xilinx_dpdma_chan *chan)
अणु
	पूर्णांक ret;

	/* Wait क्रम a no outstanding transaction पूर्णांकerrupt upto 50msec */
	ret = रुको_event_पूर्णांकerruptible_समयout(chan->रुको_to_stop,
					       !xilinx_dpdma_chan_ostand(chan),
					       msecs_to_jअगरfies(50));
	अगर (ret > 0) अणु
		dpdma_ग_लिखो(chan->xdev->reg, XILINX_DPDMA_IEN,
			    XILINX_DPDMA_INTR_NO_OSTAND(chan->id));
		वापस 0;
	पूर्ण

	dev_err(chan->xdev->dev, "not ready to stop: %d trans\n",
		xilinx_dpdma_chan_ostand(chan));

	अगर (ret == 0)
		वापस -ETIMEDOUT;

	वापस ret;
पूर्ण

/**
 * xilinx_dpdma_chan_poll_no_ostand - Poll the outstanding transaction status
 * @chan: DPDMA channel
 *
 * Poll the outstanding transaction status, and वापस when there's no
 * outstanding transaction. This functions can be used in the पूर्णांकerrupt context
 * or where the atomicity is required. Calling thपढ़ो may रुको more than 50ms.
 *
 * Return: 0 on success, or -ETIMEDOUT.
 */
अटल पूर्णांक xilinx_dpdma_chan_poll_no_ostand(काष्ठा xilinx_dpdma_chan *chan)
अणु
	u32 cnt, loop = 50000;

	/* Poll at least क्रम 50ms (20 fps). */
	करो अणु
		cnt = xilinx_dpdma_chan_ostand(chan);
		udelay(1);
	पूर्ण जबतक (loop-- > 0 && cnt);

	अगर (loop) अणु
		dpdma_ग_लिखो(chan->xdev->reg, XILINX_DPDMA_IEN,
			    XILINX_DPDMA_INTR_NO_OSTAND(chan->id));
		वापस 0;
	पूर्ण

	dev_err(chan->xdev->dev, "not ready to stop: %d trans\n",
		xilinx_dpdma_chan_ostand(chan));

	वापस -ETIMEDOUT;
पूर्ण

/**
 * xilinx_dpdma_chan_stop - Stop the channel
 * @chan: DPDMA channel
 *
 * Stop a previously छोड़ोd channel by first रुकोing क्रम completion of all
 * outstanding transaction and then disabling the channel.
 *
 * Return: 0 on success, or -ETIMEDOUT अगर the channel failed to stop.
 */
अटल पूर्णांक xilinx_dpdma_chan_stop(काष्ठा xilinx_dpdma_chan *chan)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	ret = xilinx_dpdma_chan_रुको_no_ostand(chan);
	अगर (ret)
		वापस ret;

	spin_lock_irqsave(&chan->lock, flags);
	xilinx_dpdma_chan_disable(chan);
	chan->running = false;
	spin_unlock_irqrestore(&chan->lock, flags);

	वापस 0;
पूर्ण

/**
 * xilinx_dpdma_chan_करोne_irq - Handle hardware descriptor completion
 * @chan: DPDMA channel
 *
 * Handle completion of the currently active descriptor (@chan->desc.active). As
 * we currently support cyclic transfers only, this just invokes the cyclic
 * callback. The descriptor will be completed at the VSYNC पूर्णांकerrupt when a new
 * descriptor replaces it.
 */
अटल व्योम xilinx_dpdma_chan_करोne_irq(काष्ठा xilinx_dpdma_chan *chan)
अणु
	काष्ठा xilinx_dpdma_tx_desc *active;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chan->lock, flags);

	xilinx_dpdma_debugfs_desc_करोne_irq(chan);

	active = chan->desc.active;
	अगर (active)
		vchan_cyclic_callback(&active->vdesc);
	अन्यथा
		dev_warn(chan->xdev->dev,
			 "DONE IRQ with no active descriptor!\n");

	spin_unlock_irqrestore(&chan->lock, flags);
पूर्ण

/**
 * xilinx_dpdma_chan_vsync_irq - Handle hardware descriptor scheduling
 * @chan: DPDMA channel
 *
 * At VSYNC the active descriptor may have been replaced by the pending
 * descriptor. Detect this through the DESC_ID and perक्रमm appropriate
 * bookkeeping.
 */
अटल व्योम xilinx_dpdma_chan_vsync_irq(काष्ठा  xilinx_dpdma_chan *chan)
अणु
	काष्ठा xilinx_dpdma_tx_desc *pending;
	काष्ठा xilinx_dpdma_sw_desc *sw_desc;
	अचिन्हित दीर्घ flags;
	u32 desc_id;

	spin_lock_irqsave(&chan->lock, flags);

	pending = chan->desc.pending;
	अगर (!chan->running || !pending)
		जाओ out;

	desc_id = dpdma_पढ़ो(chan->reg, XILINX_DPDMA_CH_DESC_ID)
		& XILINX_DPDMA_CH_DESC_ID_MASK;

	/* If the retrigger raced with vsync, retry at the next frame. */
	sw_desc = list_first_entry(&pending->descriptors,
				   काष्ठा xilinx_dpdma_sw_desc, node);
	अगर (sw_desc->hw.desc_id != desc_id)
		जाओ out;

	/*
	 * Complete the active descriptor, अगर any, promote the pending
	 * descriptor to active, and queue the next transfer, अगर any.
	 */
	अगर (chan->desc.active)
		vchan_cookie_complete(&chan->desc.active->vdesc);
	chan->desc.active = pending;
	chan->desc.pending = शून्य;

	xilinx_dpdma_chan_queue_transfer(chan);

out:
	spin_unlock_irqrestore(&chan->lock, flags);
पूर्ण

/**
 * xilinx_dpdma_chan_err - Detect any channel error
 * @chan: DPDMA channel
 * @isr: masked Interrupt Status Register
 * @eisr: Error Interrupt Status Register
 *
 * Return: true अगर any channel error occurs, or false otherwise.
 */
अटल bool
xilinx_dpdma_chan_err(काष्ठा xilinx_dpdma_chan *chan, u32 isr, u32 eisr)
अणु
	अगर (!chan)
		वापस false;

	अगर (chan->running &&
	    ((isr & (XILINX_DPDMA_INTR_CHAN_ERR_MASK << chan->id)) ||
	    (eisr & (XILINX_DPDMA_EINTR_CHAN_ERR_MASK << chan->id))))
		वापस true;

	वापस false;
पूर्ण

/**
 * xilinx_dpdma_chan_handle_err - DPDMA channel error handling
 * @chan: DPDMA channel
 *
 * This function is called when any channel error or any global error occurs.
 * The function disables the छोड़ोd channel by errors and determines
 * अगर the current active descriptor can be rescheduled depending on
 * the descriptor status.
 */
अटल व्योम xilinx_dpdma_chan_handle_err(काष्ठा xilinx_dpdma_chan *chan)
अणु
	काष्ठा xilinx_dpdma_device *xdev = chan->xdev;
	काष्ठा xilinx_dpdma_tx_desc *active;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chan->lock, flags);

	dev_dbg(xdev->dev, "cur desc addr = 0x%04x%08x\n",
		dpdma_पढ़ो(chan->reg, XILINX_DPDMA_CH_DESC_START_ADDRE),
		dpdma_पढ़ो(chan->reg, XILINX_DPDMA_CH_DESC_START_ADDR));
	dev_dbg(xdev->dev, "cur payload addr = 0x%04x%08x\n",
		dpdma_पढ़ो(chan->reg, XILINX_DPDMA_CH_PYLD_CUR_ADDRE),
		dpdma_पढ़ो(chan->reg, XILINX_DPDMA_CH_PYLD_CUR_ADDR));

	xilinx_dpdma_chan_disable(chan);
	chan->running = false;

	अगर (!chan->desc.active)
		जाओ out_unlock;

	active = chan->desc.active;
	chan->desc.active = शून्य;

	xilinx_dpdma_chan_dump_tx_desc(chan, active);

	अगर (active->error)
		dev_dbg(xdev->dev, "repeated error on desc\n");

	/* Reschedule अगर there's no new descriptor */
	अगर (!chan->desc.pending &&
	    list_empty(&chan->vchan.desc_issued)) अणु
		active->error = true;
		list_add_tail(&active->vdesc.node,
			      &chan->vchan.desc_issued);
	पूर्ण अन्यथा अणु
		xilinx_dpdma_chan_मुक्त_tx_desc(&active->vdesc);
	पूर्ण

out_unlock:
	spin_unlock_irqrestore(&chan->lock, flags);
पूर्ण

/* -----------------------------------------------------------------------------
 * DMA Engine Operations
 */

अटल काष्ठा dma_async_tx_descriptor *
xilinx_dpdma_prep_पूर्णांकerleaved_dma(काष्ठा dma_chan *dchan,
				  काष्ठा dma_पूर्णांकerleaved_ढाँचा *xt,
				  अचिन्हित दीर्घ flags)
अणु
	काष्ठा xilinx_dpdma_chan *chan = to_xilinx_chan(dchan);
	काष्ठा xilinx_dpdma_tx_desc *desc;

	अगर (xt->dir != DMA_MEM_TO_DEV)
		वापस शून्य;

	अगर (!xt->numf || !xt->sgl[0].size)
		वापस शून्य;

	अगर (!(flags & DMA_PREP_REPEAT) || !(flags & DMA_PREP_LOAD_EOT))
		वापस शून्य;

	desc = xilinx_dpdma_chan_prep_पूर्णांकerleaved_dma(chan, xt);
	अगर (!desc)
		वापस शून्य;

	vchan_tx_prep(&chan->vchan, &desc->vdesc, flags | DMA_CTRL_ACK);

	वापस &desc->vdesc.tx;
पूर्ण

/**
 * xilinx_dpdma_alloc_chan_resources - Allocate resources क्रम the channel
 * @dchan: DMA channel
 *
 * Allocate a descriptor pool क्रम the channel.
 *
 * Return: 0 on success, or -ENOMEM अगर failed to allocate a pool.
 */
अटल पूर्णांक xilinx_dpdma_alloc_chan_resources(काष्ठा dma_chan *dchan)
अणु
	काष्ठा xilinx_dpdma_chan *chan = to_xilinx_chan(dchan);
	माप_प्रकार align = __alignof__(काष्ठा xilinx_dpdma_sw_desc);

	chan->desc_pool = dma_pool_create(dev_name(chan->xdev->dev),
					  chan->xdev->dev,
					  माप(काष्ठा xilinx_dpdma_sw_desc),
					  align, 0);
	अगर (!chan->desc_pool) अणु
		dev_err(chan->xdev->dev,
			"failed to allocate a descriptor pool\n");
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * xilinx_dpdma_मुक्त_chan_resources - Free all resources क्रम the channel
 * @dchan: DMA channel
 *
 * Free resources associated with the भव DMA channel, and destroy the
 * descriptor pool.
 */
अटल व्योम xilinx_dpdma_मुक्त_chan_resources(काष्ठा dma_chan *dchan)
अणु
	काष्ठा xilinx_dpdma_chan *chan = to_xilinx_chan(dchan);

	vchan_मुक्त_chan_resources(&chan->vchan);

	dma_pool_destroy(chan->desc_pool);
	chan->desc_pool = शून्य;
पूर्ण

अटल व्योम xilinx_dpdma_issue_pending(काष्ठा dma_chan *dchan)
अणु
	काष्ठा xilinx_dpdma_chan *chan = to_xilinx_chan(dchan);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chan->vchan.lock, flags);
	अगर (vchan_issue_pending(&chan->vchan))
		xilinx_dpdma_chan_queue_transfer(chan);
	spin_unlock_irqrestore(&chan->vchan.lock, flags);
पूर्ण

अटल पूर्णांक xilinx_dpdma_config(काष्ठा dma_chan *dchan,
			       काष्ठा dma_slave_config *config)
अणु
	काष्ठा xilinx_dpdma_chan *chan = to_xilinx_chan(dchan);
	अचिन्हित दीर्घ flags;

	/*
	 * The destination address करोesn't need to be specअगरied as the DPDMA is
	 * hardwired to the destination (the DP controller). The transfer
	 * width, burst size and port winकरोw size are thus meaningless, they're
	 * fixed both on the DPDMA side and on the DP controller side.
	 */

	spin_lock_irqsave(&chan->lock, flags);

	/*
	 * Abuse the slave_id to indicate that the channel is part of a video
	 * group.
	 */
	अगर (chan->id <= ZYNQMP_DPDMA_VIDEO2)
		chan->video_group = config->slave_id != 0;

	spin_unlock_irqrestore(&chan->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक xilinx_dpdma_छोड़ो(काष्ठा dma_chan *dchan)
अणु
	xilinx_dpdma_chan_छोड़ो(to_xilinx_chan(dchan));

	वापस 0;
पूर्ण

अटल पूर्णांक xilinx_dpdma_resume(काष्ठा dma_chan *dchan)
अणु
	xilinx_dpdma_chan_unछोड़ो(to_xilinx_chan(dchan));

	वापस 0;
पूर्ण

/**
 * xilinx_dpdma_terminate_all - Terminate the channel and descriptors
 * @dchan: DMA channel
 *
 * Pause the channel without रुकोing क्रम ongoing transfers to complete. Waiting
 * क्रम completion is perक्रमmed by xilinx_dpdma_synchronize() that will disable
 * the channel to complete the stop.
 *
 * All the descriptors associated with the channel that are guaranteed not to
 * be touched by the hardware. The pending and active descriptor are not
 * touched, and will be मुक्तd either upon completion, or by
 * xilinx_dpdma_synchronize().
 *
 * Return: 0 on success, or -ETIMEDOUT अगर the channel failed to stop.
 */
अटल पूर्णांक xilinx_dpdma_terminate_all(काष्ठा dma_chan *dchan)
अणु
	काष्ठा xilinx_dpdma_chan *chan = to_xilinx_chan(dchan);
	काष्ठा xilinx_dpdma_device *xdev = chan->xdev;
	LIST_HEAD(descriptors);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;

	/* Pause the channel (including the whole video group अगर applicable). */
	अगर (chan->video_group) अणु
		क्रम (i = ZYNQMP_DPDMA_VIDEO0; i <= ZYNQMP_DPDMA_VIDEO2; i++) अणु
			अगर (xdev->chan[i]->video_group &&
			    xdev->chan[i]->running) अणु
				xilinx_dpdma_chan_छोड़ो(xdev->chan[i]);
				xdev->chan[i]->video_group = false;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		xilinx_dpdma_chan_छोड़ो(chan);
	पूर्ण

	/* Gather all the descriptors we can मुक्त and मुक्त them. */
	spin_lock_irqsave(&chan->vchan.lock, flags);
	vchan_get_all_descriptors(&chan->vchan, &descriptors);
	spin_unlock_irqrestore(&chan->vchan.lock, flags);

	vchan_dma_desc_मुक्त_list(&chan->vchan, &descriptors);

	वापस 0;
पूर्ण

/**
 * xilinx_dpdma_synchronize - Synchronize callback execution
 * @dchan: DMA channel
 *
 * Synchronizing callback execution ensures that all previously issued
 * transfers have completed and all associated callbacks have been called and
 * have वापसed.
 *
 * This function रुकोs क्रम the DMA channel to stop. It assumes it has been
 * छोड़ोd by a previous call to dmaengine_terminate_async(), and that no new
 * pending descriptors have been issued with dma_async_issue_pending(). The
 * behaviour is undefined otherwise.
 */
अटल व्योम xilinx_dpdma_synchronize(काष्ठा dma_chan *dchan)
अणु
	काष्ठा xilinx_dpdma_chan *chan = to_xilinx_chan(dchan);
	अचिन्हित दीर्घ flags;

	xilinx_dpdma_chan_stop(chan);

	spin_lock_irqsave(&chan->vchan.lock, flags);
	अगर (chan->desc.pending) अणु
		vchan_terminate_vdesc(&chan->desc.pending->vdesc);
		chan->desc.pending = शून्य;
	पूर्ण
	अगर (chan->desc.active) अणु
		vchan_terminate_vdesc(&chan->desc.active->vdesc);
		chan->desc.active = शून्य;
	पूर्ण
	spin_unlock_irqrestore(&chan->vchan.lock, flags);

	vchan_synchronize(&chan->vchan);
पूर्ण

/* -----------------------------------------------------------------------------
 * Interrupt and Tasklet Handling
 */

/**
 * xilinx_dpdma_err - Detect any global error
 * @isr: Interrupt Status Register
 * @eisr: Error Interrupt Status Register
 *
 * Return: True अगर any global error occurs, or false otherwise.
 */
अटल bool xilinx_dpdma_err(u32 isr, u32 eisr)
अणु
	अगर (isr & XILINX_DPDMA_INTR_GLOBAL_ERR ||
	    eisr & XILINX_DPDMA_EINTR_GLOBAL_ERR)
		वापस true;

	वापस false;
पूर्ण

/**
 * xilinx_dpdma_handle_err_irq - Handle DPDMA error पूर्णांकerrupt
 * @xdev: DPDMA device
 * @isr: masked Interrupt Status Register
 * @eisr: Error Interrupt Status Register
 *
 * Handle अगर any error occurs based on @isr and @eisr. This function disables
 * corresponding error पूर्णांकerrupts, and those should be re-enabled once handling
 * is करोne.
 */
अटल व्योम xilinx_dpdma_handle_err_irq(काष्ठा xilinx_dpdma_device *xdev,
					u32 isr, u32 eisr)
अणु
	bool err = xilinx_dpdma_err(isr, eisr);
	अचिन्हित पूर्णांक i;

	dev_dbg_ratelimited(xdev->dev,
			    "error irq: isr = 0x%08x, eisr = 0x%08x\n",
			    isr, eisr);

	/* Disable channel error पूर्णांकerrupts until errors are handled. */
	dpdma_ग_लिखो(xdev->reg, XILINX_DPDMA_IDS,
		    isr & ~XILINX_DPDMA_INTR_GLOBAL_ERR);
	dpdma_ग_लिखो(xdev->reg, XILINX_DPDMA_EIDS,
		    eisr & ~XILINX_DPDMA_EINTR_GLOBAL_ERR);

	क्रम (i = 0; i < ARRAY_SIZE(xdev->chan); i++)
		अगर (err || xilinx_dpdma_chan_err(xdev->chan[i], isr, eisr))
			tasklet_schedule(&xdev->chan[i]->err_task);
पूर्ण

/**
 * xilinx_dpdma_enable_irq - Enable पूर्णांकerrupts
 * @xdev: DPDMA device
 *
 * Enable पूर्णांकerrupts.
 */
अटल व्योम xilinx_dpdma_enable_irq(काष्ठा xilinx_dpdma_device *xdev)
अणु
	dpdma_ग_लिखो(xdev->reg, XILINX_DPDMA_IEN, XILINX_DPDMA_INTR_ALL);
	dpdma_ग_लिखो(xdev->reg, XILINX_DPDMA_EIEN, XILINX_DPDMA_EINTR_ALL);
पूर्ण

/**
 * xilinx_dpdma_disable_irq - Disable पूर्णांकerrupts
 * @xdev: DPDMA device
 *
 * Disable पूर्णांकerrupts.
 */
अटल व्योम xilinx_dpdma_disable_irq(काष्ठा xilinx_dpdma_device *xdev)
अणु
	dpdma_ग_लिखो(xdev->reg, XILINX_DPDMA_IDS, XILINX_DPDMA_INTR_ALL);
	dpdma_ग_लिखो(xdev->reg, XILINX_DPDMA_EIDS, XILINX_DPDMA_EINTR_ALL);
पूर्ण

/**
 * xilinx_dpdma_chan_err_task - Per channel tasklet क्रम error handling
 * @t: poपूर्णांकer to the tasklet associated with this handler
 *
 * Per channel error handling tasklet. This function रुकोs क्रम the outstanding
 * transaction to complete and triggers error handling. After error handling,
 * re-enable channel error पूर्णांकerrupts, and restart the channel अगर needed.
 */
अटल व्योम xilinx_dpdma_chan_err_task(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा xilinx_dpdma_chan *chan = from_tasklet(chan, t, err_task);
	काष्ठा xilinx_dpdma_device *xdev = chan->xdev;
	अचिन्हित दीर्घ flags;

	/* Proceed error handling even when polling fails. */
	xilinx_dpdma_chan_poll_no_ostand(chan);

	xilinx_dpdma_chan_handle_err(chan);

	dpdma_ग_लिखो(xdev->reg, XILINX_DPDMA_IEN,
		    XILINX_DPDMA_INTR_CHAN_ERR_MASK << chan->id);
	dpdma_ग_लिखो(xdev->reg, XILINX_DPDMA_EIEN,
		    XILINX_DPDMA_EINTR_CHAN_ERR_MASK << chan->id);

	spin_lock_irqsave(&chan->lock, flags);
	xilinx_dpdma_chan_queue_transfer(chan);
	spin_unlock_irqrestore(&chan->lock, flags);
पूर्ण

अटल irqवापस_t xilinx_dpdma_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा xilinx_dpdma_device *xdev = data;
	अचिन्हित दीर्घ mask;
	अचिन्हित पूर्णांक i;
	u32 status;
	u32 error;

	status = dpdma_पढ़ो(xdev->reg, XILINX_DPDMA_ISR);
	error = dpdma_पढ़ो(xdev->reg, XILINX_DPDMA_EISR);
	अगर (!status && !error)
		वापस IRQ_NONE;

	dpdma_ग_लिखो(xdev->reg, XILINX_DPDMA_ISR, status);
	dpdma_ग_लिखो(xdev->reg, XILINX_DPDMA_EISR, error);

	अगर (status & XILINX_DPDMA_INTR_VSYNC) अणु
		/*
		 * There's a single VSYNC पूर्णांकerrupt that needs to be processed
		 * by each running channel to update the active descriptor.
		 */
		क्रम (i = 0; i < ARRAY_SIZE(xdev->chan); i++) अणु
			काष्ठा xilinx_dpdma_chan *chan = xdev->chan[i];

			अगर (chan)
				xilinx_dpdma_chan_vsync_irq(chan);
		पूर्ण
	पूर्ण

	mask = FIELD_GET(XILINX_DPDMA_INTR_DESC_DONE_MASK, status);
	अगर (mask) अणु
		क्रम_each_set_bit(i, &mask, ARRAY_SIZE(xdev->chan))
			xilinx_dpdma_chan_करोne_irq(xdev->chan[i]);
	पूर्ण

	mask = FIELD_GET(XILINX_DPDMA_INTR_NO_OSTAND_MASK, status);
	अगर (mask) अणु
		क्रम_each_set_bit(i, &mask, ARRAY_SIZE(xdev->chan))
			xilinx_dpdma_chan_notअगरy_no_ostand(xdev->chan[i]);
	पूर्ण

	mask = status & XILINX_DPDMA_INTR_ERR_ALL;
	अगर (mask || error)
		xilinx_dpdma_handle_err_irq(xdev, mask, error);

	वापस IRQ_HANDLED;
पूर्ण

/* -----------------------------------------------------------------------------
 * Initialization & Cleanup
 */

अटल पूर्णांक xilinx_dpdma_chan_init(काष्ठा xilinx_dpdma_device *xdev,
				  अचिन्हित पूर्णांक chan_id)
अणु
	काष्ठा xilinx_dpdma_chan *chan;

	chan = devm_kzalloc(xdev->dev, माप(*chan), GFP_KERNEL);
	अगर (!chan)
		वापस -ENOMEM;

	chan->id = chan_id;
	chan->reg = xdev->reg + XILINX_DPDMA_CH_BASE
		  + XILINX_DPDMA_CH_OFFSET * chan->id;
	chan->running = false;
	chan->xdev = xdev;

	spin_lock_init(&chan->lock);
	init_रुकोqueue_head(&chan->रुको_to_stop);

	tasklet_setup(&chan->err_task, xilinx_dpdma_chan_err_task);

	chan->vchan.desc_मुक्त = xilinx_dpdma_chan_मुक्त_tx_desc;
	vchan_init(&chan->vchan, &xdev->common);

	xdev->chan[chan->id] = chan;

	वापस 0;
पूर्ण

अटल व्योम xilinx_dpdma_chan_हटाओ(काष्ठा xilinx_dpdma_chan *chan)
अणु
	अगर (!chan)
		वापस;

	tasklet_समाप्त(&chan->err_task);
	list_del(&chan->vchan.chan.device_node);
पूर्ण

अटल काष्ठा dma_chan *of_dma_xilinx_xlate(काष्ठा of_phandle_args *dma_spec,
					    काष्ठा of_dma *ofdma)
अणु
	काष्ठा xilinx_dpdma_device *xdev = ofdma->of_dma_data;
	uपूर्णांक32_t chan_id = dma_spec->args[0];

	अगर (chan_id >= ARRAY_SIZE(xdev->chan))
		वापस शून्य;

	अगर (!xdev->chan[chan_id])
		वापस शून्य;

	वापस dma_get_slave_channel(&xdev->chan[chan_id]->vchan.chan);
पूर्ण

अटल व्योम dpdma_hw_init(काष्ठा xilinx_dpdma_device *xdev)
अणु
	अचिन्हित पूर्णांक i;
	व्योम __iomem *reg;

	/* Disable all पूर्णांकerrupts */
	xilinx_dpdma_disable_irq(xdev);

	/* Stop all channels */
	क्रम (i = 0; i < ARRAY_SIZE(xdev->chan); i++) अणु
		reg = xdev->reg + XILINX_DPDMA_CH_BASE
				+ XILINX_DPDMA_CH_OFFSET * i;
		dpdma_clr(reg, XILINX_DPDMA_CH_CNTL, XILINX_DPDMA_CH_CNTL_ENABLE);
	पूर्ण

	/* Clear the पूर्णांकerrupt status रेजिस्टरs */
	dpdma_ग_लिखो(xdev->reg, XILINX_DPDMA_ISR, XILINX_DPDMA_INTR_ALL);
	dpdma_ग_लिखो(xdev->reg, XILINX_DPDMA_EISR, XILINX_DPDMA_EINTR_ALL);
पूर्ण

अटल पूर्णांक xilinx_dpdma_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xilinx_dpdma_device *xdev;
	काष्ठा dma_device *ddev;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	xdev = devm_kzalloc(&pdev->dev, माप(*xdev), GFP_KERNEL);
	अगर (!xdev)
		वापस -ENOMEM;

	xdev->dev = &pdev->dev;
	xdev->ext_addr = माप(dma_addr_t) > 4;

	INIT_LIST_HEAD(&xdev->common.channels);

	platक्रमm_set_drvdata(pdev, xdev);

	xdev->axi_clk = devm_clk_get(xdev->dev, "axi_clk");
	अगर (IS_ERR(xdev->axi_clk))
		वापस PTR_ERR(xdev->axi_clk);

	xdev->reg = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(xdev->reg))
		वापस PTR_ERR(xdev->reg);

	dpdma_hw_init(xdev);

	xdev->irq = platक्रमm_get_irq(pdev, 0);
	अगर (xdev->irq < 0) अणु
		dev_err(xdev->dev, "failed to get platform irq\n");
		वापस xdev->irq;
	पूर्ण

	ret = request_irq(xdev->irq, xilinx_dpdma_irq_handler, IRQF_SHARED,
			  dev_name(xdev->dev), xdev);
	अगर (ret) अणु
		dev_err(xdev->dev, "failed to request IRQ\n");
		वापस ret;
	पूर्ण

	ddev = &xdev->common;
	ddev->dev = &pdev->dev;

	dma_cap_set(DMA_SLAVE, ddev->cap_mask);
	dma_cap_set(DMA_PRIVATE, ddev->cap_mask);
	dma_cap_set(DMA_INTERLEAVE, ddev->cap_mask);
	dma_cap_set(DMA_REPEAT, ddev->cap_mask);
	dma_cap_set(DMA_LOAD_EOT, ddev->cap_mask);
	ddev->copy_align = fls(XILINX_DPDMA_ALIGN_BYTES - 1);

	ddev->device_alloc_chan_resources = xilinx_dpdma_alloc_chan_resources;
	ddev->device_मुक्त_chan_resources = xilinx_dpdma_मुक्त_chan_resources;
	ddev->device_prep_पूर्णांकerleaved_dma = xilinx_dpdma_prep_पूर्णांकerleaved_dma;
	/* TODO: Can we achieve better granularity ? */
	ddev->device_tx_status = dma_cookie_status;
	ddev->device_issue_pending = xilinx_dpdma_issue_pending;
	ddev->device_config = xilinx_dpdma_config;
	ddev->device_छोड़ो = xilinx_dpdma_छोड़ो;
	ddev->device_resume = xilinx_dpdma_resume;
	ddev->device_terminate_all = xilinx_dpdma_terminate_all;
	ddev->device_synchronize = xilinx_dpdma_synchronize;
	ddev->src_addr_widths = BIT(DMA_SLAVE_BUSWIDTH_UNDEFINED);
	ddev->directions = BIT(DMA_MEM_TO_DEV);
	ddev->residue_granularity = DMA_RESIDUE_GRANULARITY_DESCRIPTOR;

	क्रम (i = 0; i < ARRAY_SIZE(xdev->chan); ++i) अणु
		ret = xilinx_dpdma_chan_init(xdev, i);
		अगर (ret < 0) अणु
			dev_err(xdev->dev, "failed to initialize channel %u\n",
				i);
			जाओ error;
		पूर्ण
	पूर्ण

	ret = clk_prepare_enable(xdev->axi_clk);
	अगर (ret) अणु
		dev_err(xdev->dev, "failed to enable the axi clock\n");
		जाओ error;
	पूर्ण

	ret = dma_async_device_रेजिस्टर(ddev);
	अगर (ret) अणु
		dev_err(xdev->dev, "failed to register the dma device\n");
		जाओ error_dma_async;
	पूर्ण

	ret = of_dma_controller_रेजिस्टर(xdev->dev->of_node,
					 of_dma_xilinx_xlate, ddev);
	अगर (ret) अणु
		dev_err(xdev->dev, "failed to register DMA to DT DMA helper\n");
		जाओ error_of_dma;
	पूर्ण

	xilinx_dpdma_enable_irq(xdev);

	xilinx_dpdma_debugfs_init(xdev);

	dev_info(&pdev->dev, "Xilinx DPDMA engine is probed\n");

	वापस 0;

error_of_dma:
	dma_async_device_unरेजिस्टर(ddev);
error_dma_async:
	clk_disable_unprepare(xdev->axi_clk);
error:
	क्रम (i = 0; i < ARRAY_SIZE(xdev->chan); i++)
		xilinx_dpdma_chan_हटाओ(xdev->chan[i]);

	मुक्त_irq(xdev->irq, xdev);

	वापस ret;
पूर्ण

अटल पूर्णांक xilinx_dpdma_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xilinx_dpdma_device *xdev = platक्रमm_get_drvdata(pdev);
	अचिन्हित पूर्णांक i;

	/* Start by disabling the IRQ to aव्योम races during cleanup. */
	मुक्त_irq(xdev->irq, xdev);

	xilinx_dpdma_disable_irq(xdev);
	of_dma_controller_मुक्त(pdev->dev.of_node);
	dma_async_device_unरेजिस्टर(&xdev->common);
	clk_disable_unprepare(xdev->axi_clk);

	क्रम (i = 0; i < ARRAY_SIZE(xdev->chan); i++)
		xilinx_dpdma_chan_हटाओ(xdev->chan[i]);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id xilinx_dpdma_of_match[] = अणु
	अणु .compatible = "xlnx,zynqmp-dpdma",पूर्ण,
	अणु /* end of table */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, xilinx_dpdma_of_match);

अटल काष्ठा platक्रमm_driver xilinx_dpdma_driver = अणु
	.probe			= xilinx_dpdma_probe,
	.हटाओ			= xilinx_dpdma_हटाओ,
	.driver			= अणु
		.name		= "xilinx-zynqmp-dpdma",
		.of_match_table	= xilinx_dpdma_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(xilinx_dpdma_driver);

MODULE_AUTHOR("Xilinx, Inc.");
MODULE_DESCRIPTION("Xilinx ZynqMP DPDMA driver");
MODULE_LICENSE("GPL v2");
