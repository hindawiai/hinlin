<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  cobalt driver पूर्णांकernal defines and काष्ठाures
 *
 *  Derived from cx18-driver.h
 *
 *  Copyright 2012-2015 Cisco Systems, Inc. and/or its affiliates.
 *  All rights reserved.
 */

#अगर_अघोषित COBALT_DRIVER_H
#घोषणा COBALT_DRIVER_H

#समावेश <linux/bitops.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/i2c.h>
#समावेश <linux/list.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/mutex.h>

#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/videobuf2-dma-sg.h>

#समावेश "m00233_video_measure_memmap_package.h"
#समावेश "m00235_fdma_packer_memmap_package.h"
#समावेश "m00389_cvi_memmap_package.h"
#समावेश "m00460_evcnt_memmap_package.h"
#समावेश "m00473_freewheel_memmap_package.h"
#समावेश "m00479_clk_loss_detector_memmap_package.h"
#समावेश "m00514_syncgen_flow_evcnt_memmap_package.h"

/* System device ID */
#घोषणा PCI_DEVICE_ID_COBALT	0x2732

/* Number of cobalt device nodes. */
#घोषणा COBALT_NUM_INPUTS	4
#घोषणा COBALT_NUM_NODES	6

/* Number of cobalt device streams. */
#घोषणा COBALT_NUM_STREAMS	12

#घोषणा COBALT_HSMA_IN_NODE	4
#घोषणा COBALT_HSMA_OUT_NODE	5

/* Cobalt audio streams */
#घोषणा COBALT_AUDIO_IN_STREAM	6
#घोषणा COBALT_AUDIO_OUT_STREAM 11

/* DMA stuff */
#घोषणा DMA_CHANNELS_MAX	16

/* i2c stuff */
#घोषणा I2C_CLIENTS_MAX		16
#घोषणा COBALT_NUM_ADAPTERS	5

#घोषणा COBALT_CLK		50000000

/* System status रेजिस्टर */
#घोषणा COBALT_SYSSTAT_DIP0_MSK			BIT(0)
#घोषणा COBALT_SYSSTAT_DIP1_MSK			BIT(1)
#घोषणा COBALT_SYSSTAT_HSMA_PRSNTN_MSK		BIT(2)
#घोषणा COBALT_SYSSTAT_FLASH_RDYBSYN_MSK	BIT(3)
#घोषणा COBALT_SYSSTAT_VI0_5V_MSK		BIT(4)
#घोषणा COBALT_SYSSTAT_VI0_INT1_MSK		BIT(5)
#घोषणा COBALT_SYSSTAT_VI0_INT2_MSK		BIT(6)
#घोषणा COBALT_SYSSTAT_VI0_LOST_DATA_MSK	BIT(7)
#घोषणा COBALT_SYSSTAT_VI1_5V_MSK		BIT(8)
#घोषणा COBALT_SYSSTAT_VI1_INT1_MSK		BIT(9)
#घोषणा COBALT_SYSSTAT_VI1_INT2_MSK		BIT(10)
#घोषणा COBALT_SYSSTAT_VI1_LOST_DATA_MSK	BIT(11)
#घोषणा COBALT_SYSSTAT_VI2_5V_MSK		BIT(12)
#घोषणा COBALT_SYSSTAT_VI2_INT1_MSK		BIT(13)
#घोषणा COBALT_SYSSTAT_VI2_INT2_MSK		BIT(14)
#घोषणा COBALT_SYSSTAT_VI2_LOST_DATA_MSK	BIT(15)
#घोषणा COBALT_SYSSTAT_VI3_5V_MSK		BIT(16)
#घोषणा COBALT_SYSSTAT_VI3_INT1_MSK		BIT(17)
#घोषणा COBALT_SYSSTAT_VI3_INT2_MSK		BIT(18)
#घोषणा COBALT_SYSSTAT_VI3_LOST_DATA_MSK	BIT(19)
#घोषणा COBALT_SYSSTAT_VIHSMA_5V_MSK		BIT(20)
#घोषणा COBALT_SYSSTAT_VIHSMA_INT1_MSK		BIT(21)
#घोषणा COBALT_SYSSTAT_VIHSMA_INT2_MSK		BIT(22)
#घोषणा COBALT_SYSSTAT_VIHSMA_LOST_DATA_MSK	BIT(23)
#घोषणा COBALT_SYSSTAT_VOHSMA_INT1_MSK		BIT(24)
#घोषणा COBALT_SYSSTAT_VOHSMA_PLL_LOCKED_MSK	BIT(25)
#घोषणा COBALT_SYSSTAT_VOHSMA_LOST_DATA_MSK	BIT(26)
#घोषणा COBALT_SYSSTAT_AUD_PLL_LOCKED_MSK	BIT(28)
#घोषणा COBALT_SYSSTAT_AUD_IN_LOST_DATA_MSK	BIT(29)
#घोषणा COBALT_SYSSTAT_AUD_OUT_LOST_DATA_MSK	BIT(30)
#घोषणा COBALT_SYSSTAT_PCIE_SMBCLK_MSK		BIT(31)

/* Cobalt memory map */
#घोषणा COBALT_I2C_0_BASE			0x0
#घोषणा COBALT_I2C_1_BASE			0x080
#घोषणा COBALT_I2C_2_BASE			0x100
#घोषणा COBALT_I2C_3_BASE			0x180
#घोषणा COBALT_I2C_HSMA_BASE			0x200

#घोषणा COBALT_SYS_CTRL_BASE			0x400
#घोषणा COBALT_SYS_CTRL_HSMA_TX_ENABLE_BIT	1
#घोषणा COBALT_SYS_CTRL_VIDEO_RX_RESETN_BIT(n)	(4 + 4 * (n))
#घोषणा COBALT_SYS_CTRL_NRESET_TO_HDMI_BIT(n)	(5 + 4 * (n))
#घोषणा COBALT_SYS_CTRL_HPD_TO_CONNECTOR_BIT(n)	(6 + 4 * (n))
#घोषणा COBALT_SYS_CTRL_AUDIO_IPP_RESETN_BIT(n)	(7 + 4 * (n))
#घोषणा COBALT_SYS_CTRL_PWRDN0_TO_HSMA_TX_BIT	24
#घोषणा COBALT_SYS_CTRL_VIDEO_TX_RESETN_BIT	25
#घोषणा COBALT_SYS_CTRL_AUDIO_OPP_RESETN_BIT	27

#घोषणा COBALT_SYS_STAT_BASE			0x500
#घोषणा COBALT_SYS_STAT_MASK			(COBALT_SYS_STAT_BASE + 0x08)
#घोषणा COBALT_SYS_STAT_EDGE			(COBALT_SYS_STAT_BASE + 0x0c)

#घोषणा COBALT_HDL_INFO_BASE			0x4800
#घोषणा COBALT_HDL_INFO_SIZE			0x200

#घोषणा COBALT_VID_BASE				0x10000
#घोषणा COBALT_VID_SIZE				0x1000

#घोषणा COBALT_CVI(cobalt, c) \
	(cobalt->bar1 + COBALT_VID_BASE + (c) * COBALT_VID_SIZE)
#घोषणा COBALT_CVI_VMR(cobalt, c) \
	(cobalt->bar1 + COBALT_VID_BASE + (c) * COBALT_VID_SIZE + 0x100)
#घोषणा COBALT_CVI_EVCNT(cobalt, c) \
	(cobalt->bar1 + COBALT_VID_BASE + (c) * COBALT_VID_SIZE + 0x200)
#घोषणा COBALT_CVI_FREEWHEEL(cobalt, c) \
	(cobalt->bar1 + COBALT_VID_BASE + (c) * COBALT_VID_SIZE + 0x300)
#घोषणा COBALT_CVI_CLK_LOSS(cobalt, c) \
	(cobalt->bar1 + COBALT_VID_BASE + (c) * COBALT_VID_SIZE + 0x400)
#घोषणा COBALT_CVI_PACKER(cobalt, c) \
	(cobalt->bar1 + COBALT_VID_BASE + (c) * COBALT_VID_SIZE + 0x500)

#घोषणा COBALT_TX_BASE(cobalt) (cobalt->bar1 + COBALT_VID_BASE + 0x5000)

#घोषणा DMA_INTERRUPT_STATUS_REG		0x08

#घोषणा COBALT_HDL_SEARCH_STR			"** HDL version info **"

/* Cobalt CPU bus पूर्णांकerface */
#घोषणा COBALT_BUS_BAR1_BASE			0x600
#घोषणा COBALT_BUS_SRAM_BASE			0x0
#घोषणा COBALT_BUS_CPLD_BASE			0x00600000
#घोषणा COBALT_BUS_FLASH_BASE			0x08000000

/* FDMA to PCIe packing */
#घोषणा COBALT_BYTES_PER_PIXEL_YUYV		2
#घोषणा COBALT_BYTES_PER_PIXEL_RGB24		3
#घोषणा COBALT_BYTES_PER_PIXEL_RGB32		4

/* debugging */
बाह्य पूर्णांक cobalt_debug;
बाह्य पूर्णांक cobalt_ignore_err;

#घोषणा cobalt_err(fmt, arg...)  v4l2_err(&cobalt->v4l2_dev, fmt, ## arg)
#घोषणा cobalt_warn(fmt, arg...) v4l2_warn(&cobalt->v4l2_dev, fmt, ## arg)
#घोषणा cobalt_info(fmt, arg...) v4l2_info(&cobalt->v4l2_dev, fmt, ## arg)
#घोषणा cobalt_dbg(level, fmt, arg...) \
	v4l2_dbg(level, cobalt_debug, &cobalt->v4l2_dev, fmt, ## arg)

काष्ठा cobalt;
काष्ठा cobalt_i2c_regs;

/* Per I2C bus निजी algo callback data */
काष्ठा cobalt_i2c_data अणु
	काष्ठा cobalt *cobalt;
	काष्ठा cobalt_i2c_regs __iomem *regs;
पूर्ण;

काष्ठा pci_consistent_buffer अणु
	व्योम *virt;
	dma_addr_t bus;
	माप_प्रकार bytes;
पूर्ण;

काष्ठा sg_dma_desc_info अणु
	व्योम *virt;
	dma_addr_t bus;
	अचिन्हित size;
	व्योम *last_desc_virt;
	काष्ठा device *dev;
पूर्ण;

#घोषणा COBALT_MAX_WIDTH			1920
#घोषणा COBALT_MAX_HEIGHT			1200
#घोषणा COBALT_MAX_BPP				3
#घोषणा COBALT_MAX_FRAMESZ \
	(COBALT_MAX_WIDTH * COBALT_MAX_HEIGHT * COBALT_MAX_BPP)

#घोषणा NR_BUFS					VIDEO_MAX_FRAME

#घोषणा COBALT_STREAM_FL_DMA_IRQ		0
#घोषणा COBALT_STREAM_FL_ADV_IRQ		1

काष्ठा cobalt_buffer अणु
	काष्ठा vb2_v4l2_buffer vb;
	काष्ठा list_head list;
पूर्ण;

अटल अंतरभूत
काष्ठा cobalt_buffer *to_cobalt_buffer(काष्ठा vb2_v4l2_buffer *vb2)
अणु
	वापस container_of(vb2, काष्ठा cobalt_buffer, vb);
पूर्ण

काष्ठा cobalt_stream अणु
	काष्ठा video_device vdev;
	काष्ठा vb2_queue q;
	काष्ठा list_head bufs;
	काष्ठा i2c_adapter *i2c_adap;
	काष्ठा v4l2_subdev *sd;
	काष्ठा mutex lock;
	spinlock_t irqlock;
	काष्ठा v4l2_dv_timings timings;
	u32 input;
	u32 pad_source;
	u32 width, height, bpp;
	u32 stride;
	u32 pixfmt;
	u32 sequence;
	u32 colorspace;
	u32 xfer_func;
	u32 ycbcr_enc;
	u32 quantization;

	u8 dma_channel;
	पूर्णांक video_channel;
	अचिन्हित dma_fअगरo_mask;
	अचिन्हित adv_irq_mask;
	काष्ठा sg_dma_desc_info dma_desc_info[NR_BUFS];
	अचिन्हित दीर्घ flags;
	bool unstable_frame;
	bool enable_cvi;
	bool enable_मुक्तwheel;
	अचिन्हित skip_first_frames;
	bool is_output;
	bool is_audio;
	bool is_dummy;

	काष्ठा cobalt *cobalt;
	काष्ठा snd_cobalt_card *alsa;
पूर्ण;

काष्ठा snd_cobalt_card;

/* Struct to hold info about cobalt cards */
काष्ठा cobalt अणु
	पूर्णांक instance;
	काष्ठा pci_dev *pci_dev;
	काष्ठा v4l2_device v4l2_dev;

	व्योम __iomem *bar0, *bar1;

	u8 card_rev;
	u16 device_id;

	/* device nodes */
	काष्ठा cobalt_stream streams[DMA_CHANNELS_MAX];
	काष्ठा i2c_adapter i2c_adap[COBALT_NUM_ADAPTERS];
	काष्ठा cobalt_i2c_data i2c_data[COBALT_NUM_ADAPTERS];
	bool have_hsma_rx;
	bool have_hsma_tx;

	/* irq */
	काष्ठा workqueue_काष्ठा *irq_work_queues;
	काष्ठा work_काष्ठा irq_work_queue;              /* work entry */
	/* irq counters */
	u32 irq_adv1;
	u32 irq_adv2;
	u32 irq_advout;
	u32 irq_dma_tot;
	u32 irq_dma[COBALT_NUM_STREAMS];
	u32 irq_none;
	u32 irq_full_fअगरo;

	/* omnitek dma */
	पूर्णांक dma_channels;
	पूर्णांक first_fअगरo_channel;
	bool pci_32_bit;

	अक्षर hdl_info[COBALT_HDL_INFO_SIZE];

	/* NOR flash */
	काष्ठा mtd_info *mtd;
पूर्ण;

अटल अंतरभूत काष्ठा cobalt *to_cobalt(काष्ठा v4l2_device *v4l2_dev)
अणु
	वापस container_of(v4l2_dev, काष्ठा cobalt, v4l2_dev);
पूर्ण

अटल अंतरभूत व्योम cobalt_ग_लिखो_bar0(काष्ठा cobalt *cobalt, u32 reg, u32 val)
अणु
	ioग_लिखो32(val, cobalt->bar0 + reg);
पूर्ण

अटल अंतरभूत u32 cobalt_पढ़ो_bar0(काष्ठा cobalt *cobalt, u32 reg)
अणु
	वापस ioपढ़ो32(cobalt->bar0 + reg);
पूर्ण

अटल अंतरभूत व्योम cobalt_ग_लिखो_bar1(काष्ठा cobalt *cobalt, u32 reg, u32 val)
अणु
	ioग_लिखो32(val, cobalt->bar1 + reg);
पूर्ण

अटल अंतरभूत u32 cobalt_पढ़ो_bar1(काष्ठा cobalt *cobalt, u32 reg)
अणु
	वापस ioपढ़ो32(cobalt->bar1 + reg);
पूर्ण

अटल अंतरभूत u32 cobalt_g_sysctrl(काष्ठा cobalt *cobalt)
अणु
	वापस cobalt_पढ़ो_bar1(cobalt, COBALT_SYS_CTRL_BASE);
पूर्ण

अटल अंतरभूत व्योम cobalt_s_bit_sysctrl(काष्ठा cobalt *cobalt,
					पूर्णांक bit, पूर्णांक val)
अणु
	u32 ctrl = cobalt_पढ़ो_bar1(cobalt, COBALT_SYS_CTRL_BASE);

	cobalt_ग_लिखो_bar1(cobalt, COBALT_SYS_CTRL_BASE,
			(ctrl & ~(1UL << bit)) | (val << bit));
पूर्ण

अटल अंतरभूत u32 cobalt_g_sysstat(काष्ठा cobalt *cobalt)
अणु
	वापस cobalt_पढ़ो_bar1(cobalt, COBALT_SYS_STAT_BASE);
पूर्ण

#घोषणा ADRS_REG (bar1 + COBALT_BUS_BAR1_BASE + 0)
#घोषणा LOWER_DATA (bar1 + COBALT_BUS_BAR1_BASE + 4)
#घोषणा UPPER_DATA (bar1 + COBALT_BUS_BAR1_BASE + 6)

अटल अंतरभूत u32 cobalt_bus_पढ़ो32(व्योम __iomem *bar1, u32 bus_adrs)
अणु
	ioग_लिखो32(bus_adrs, ADRS_REG);
	वापस ioपढ़ो32(LOWER_DATA);
पूर्ण

अटल अंतरभूत व्योम cobalt_bus_ग_लिखो16(व्योम __iomem *bar1,
				      u32 bus_adrs, u16 data)
अणु
	ioग_लिखो32(bus_adrs, ADRS_REG);
	अगर (bus_adrs & 2)
		ioग_लिखो16(data, UPPER_DATA);
	अन्यथा
		ioग_लिखो16(data, LOWER_DATA);
पूर्ण

अटल अंतरभूत व्योम cobalt_bus_ग_लिखो32(व्योम __iomem *bar1,
				      u32 bus_adrs, u16 data)
अणु
	ioग_लिखो32(bus_adrs, ADRS_REG);
	अगर (bus_adrs & 2)
		ioग_लिखो32(data, UPPER_DATA);
	अन्यथा
		ioग_लिखो32(data, LOWER_DATA);
पूर्ण

/*==============Prototypes==================*/

व्योम cobalt_pcie_status_show(काष्ठा cobalt *cobalt);

#पूर्ण_अगर
