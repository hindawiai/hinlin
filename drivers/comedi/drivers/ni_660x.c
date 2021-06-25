<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Hardware driver क्रम NI 660x devices
 */

/*
 * Driver: ni_660x
 * Description: National Instruments 660x counter/समयr boards
 * Devices: [National Instruments] PCI-6601 (ni_660x), PCI-6602, PXI-6602,
 *   PCI-6608, PXI-6608, PCI-6624, PXI-6624
 * Author: J.P. Mellor <jpmellor@rose-hulman.edu>,
 *   Herman.Bruyninckx@mech.kuleuven.ac.be,
 *   Wim.Meeussen@mech.kuleuven.ac.be,
 *   Klaas.Gadeyne@mech.kuleuven.ac.be,
 *   Frank Mori Hess <fmhess@users.sourceक्रमge.net>
 * Updated: Mon, 16 Jan 2017 14:00:43 +0000
 * Status: experimental
 *
 * Encoders work.  PulseGeneration (both single pulse and pulse train)
 * works.  Buffered commands work क्रम input but not output.
 *
 * References:
 * DAQ 660x Register-Level Programmer Manual  (NI 370505A-01)
 * DAQ 6601/6602 User Manual (NI 322137B-01)
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "../comedi_pci.h"

#समावेश "mite.h"
#समावेश "ni_tio.h"
#समावेश "ni_routes.h"

/* See Register-Level Programmer Manual page 3.1 */
क्रमागत ni_660x_रेजिस्टर अणु
	/* see क्रमागत ni_gpct_रेजिस्टर */
	NI660X_STC_DIO_PARALLEL_INPUT = NITIO_NUM_REGS,
	NI660X_STC_DIO_OUTPUT,
	NI660X_STC_DIO_CONTROL,
	NI660X_STC_DIO_SERIAL_INPUT,
	NI660X_DIO32_INPUT,
	NI660X_DIO32_OUTPUT,
	NI660X_CLK_CFG,
	NI660X_GLOBAL_INT_STATUS,
	NI660X_DMA_CFG,
	NI660X_GLOBAL_INT_CFG,
	NI660X_IO_CFG_0_1,
	NI660X_IO_CFG_2_3,
	NI660X_IO_CFG_4_5,
	NI660X_IO_CFG_6_7,
	NI660X_IO_CFG_8_9,
	NI660X_IO_CFG_10_11,
	NI660X_IO_CFG_12_13,
	NI660X_IO_CFG_14_15,
	NI660X_IO_CFG_16_17,
	NI660X_IO_CFG_18_19,
	NI660X_IO_CFG_20_21,
	NI660X_IO_CFG_22_23,
	NI660X_IO_CFG_24_25,
	NI660X_IO_CFG_26_27,
	NI660X_IO_CFG_28_29,
	NI660X_IO_CFG_30_31,
	NI660X_IO_CFG_32_33,
	NI660X_IO_CFG_34_35,
	NI660X_IO_CFG_36_37,
	NI660X_IO_CFG_38_39,
	NI660X_NUM_REGS,
पूर्ण;

#घोषणा NI660X_CLK_CFG_COUNTER_SWAP	BIT(21)

#घोषणा NI660X_GLOBAL_INT_COUNTER0	BIT(8)
#घोषणा NI660X_GLOBAL_INT_COUNTER1	BIT(9)
#घोषणा NI660X_GLOBAL_INT_COUNTER2	BIT(10)
#घोषणा NI660X_GLOBAL_INT_COUNTER3	BIT(11)
#घोषणा NI660X_GLOBAL_INT_CASCADE	BIT(29)
#घोषणा NI660X_GLOBAL_INT_GLOBAL_POL	BIT(30)
#घोषणा NI660X_GLOBAL_INT_GLOBAL	BIT(31)

#घोषणा NI660X_DMA_CFG_SEL(_c, _s)	(((_s) & 0x1f) << (8 * (_c)))
#घोषणा NI660X_DMA_CFG_SEL_MASK(_c)	NI660X_DMA_CFG_SEL((_c), 0x1f)
#घोषणा NI660X_DMA_CFG_SEL_NONE(_c)	NI660X_DMA_CFG_SEL((_c), 0x1f)
#घोषणा NI660X_DMA_CFG_RESET(_c)	NI660X_DMA_CFG_SEL((_c), 0x80)

#घोषणा NI660X_IO_CFG(x)		(NI660X_IO_CFG_0_1 + ((x) / 2))
#घोषणा NI660X_IO_CFG_OUT_SEL(_c, _s)	(((_s) & 0x3) << (((_c) % 2) ? 0 : 8))
#घोषणा NI660X_IO_CFG_OUT_SEL_MASK(_c)	NI660X_IO_CFG_OUT_SEL((_c), 0x3)
#घोषणा NI660X_IO_CFG_IN_SEL(_c, _s)	(((_s) & 0x7) << (((_c) % 2) ? 4 : 12))
#घोषणा NI660X_IO_CFG_IN_SEL_MASK(_c)	NI660X_IO_CFG_IN_SEL((_c), 0x7)

काष्ठा ni_660x_रेजिस्टर_data अणु
	पूर्णांक offset;		/*  Offset from base address from GPCT chip */
	अक्षर size;		/* 2 or 4 bytes */
पूर्ण;

अटल स्थिर काष्ठा ni_660x_रेजिस्टर_data ni_660x_reg_data[NI660X_NUM_REGS] = अणु
	[NITIO_G0_INT_ACK]		= अणु 0x004, 2 पूर्ण,	/* ग_लिखो */
	[NITIO_G0_STATUS]		= अणु 0x004, 2 पूर्ण,	/* पढ़ो */
	[NITIO_G1_INT_ACK]		= अणु 0x006, 2 पूर्ण,	/* ग_लिखो */
	[NITIO_G1_STATUS]		= अणु 0x006, 2 पूर्ण,	/* पढ़ो */
	[NITIO_G01_STATUS]		= अणु 0x008, 2 पूर्ण,	/* पढ़ो */
	[NITIO_G0_CMD]			= अणु 0x00c, 2 पूर्ण,	/* ग_लिखो */
	[NI660X_STC_DIO_PARALLEL_INPUT]	= अणु 0x00e, 2 पूर्ण,	/* पढ़ो */
	[NITIO_G1_CMD]			= अणु 0x00e, 2 पूर्ण,	/* ग_लिखो */
	[NITIO_G0_HW_SAVE]		= अणु 0x010, 4 पूर्ण,	/* पढ़ो */
	[NITIO_G1_HW_SAVE]		= अणु 0x014, 4 पूर्ण,	/* पढ़ो */
	[NI660X_STC_DIO_OUTPUT]		= अणु 0x014, 2 पूर्ण,	/* ग_लिखो */
	[NI660X_STC_DIO_CONTROL]	= अणु 0x016, 2 पूर्ण,	/* ग_लिखो */
	[NITIO_G0_SW_SAVE]		= अणु 0x018, 4 पूर्ण,	/* पढ़ो */
	[NITIO_G1_SW_SAVE]		= अणु 0x01c, 4 पूर्ण,	/* पढ़ो */
	[NITIO_G0_MODE]			= अणु 0x034, 2 पूर्ण,	/* ग_लिखो */
	[NITIO_G01_STATUS1]		= अणु 0x036, 2 पूर्ण,	/* पढ़ो */
	[NITIO_G1_MODE]			= अणु 0x036, 2 पूर्ण,	/* ग_लिखो */
	[NI660X_STC_DIO_SERIAL_INPUT]	= अणु 0x038, 2 पूर्ण,	/* पढ़ो */
	[NITIO_G0_LOADA]		= अणु 0x038, 4 पूर्ण,	/* ग_लिखो */
	[NITIO_G01_STATUS2]		= अणु 0x03a, 2 पूर्ण,	/* पढ़ो */
	[NITIO_G0_LOADB]		= अणु 0x03c, 4 पूर्ण,	/* ग_लिखो */
	[NITIO_G1_LOADA]		= अणु 0x040, 4 पूर्ण,	/* ग_लिखो */
	[NITIO_G1_LOADB]		= अणु 0x044, 4 पूर्ण,	/* ग_लिखो */
	[NITIO_G0_INPUT_SEL]		= अणु 0x048, 2 पूर्ण,	/* ग_लिखो */
	[NITIO_G1_INPUT_SEL]		= अणु 0x04a, 2 पूर्ण,	/* ग_लिखो */
	[NITIO_G0_AUTO_INC]		= अणु 0x088, 2 पूर्ण,	/* ग_लिखो */
	[NITIO_G1_AUTO_INC]		= अणु 0x08a, 2 पूर्ण,	/* ग_लिखो */
	[NITIO_G01_RESET]		= अणु 0x090, 2 पूर्ण,	/* ग_लिखो */
	[NITIO_G0_INT_ENA]		= अणु 0x092, 2 पूर्ण,	/* ग_लिखो */
	[NITIO_G1_INT_ENA]		= अणु 0x096, 2 पूर्ण,	/* ग_लिखो */
	[NITIO_G0_CNT_MODE]		= अणु 0x0b0, 2 पूर्ण,	/* ग_लिखो */
	[NITIO_G1_CNT_MODE]		= अणु 0x0b2, 2 पूर्ण,	/* ग_लिखो */
	[NITIO_G0_GATE2]		= अणु 0x0b4, 2 पूर्ण,	/* ग_लिखो */
	[NITIO_G1_GATE2]		= अणु 0x0b6, 2 पूर्ण,	/* ग_लिखो */
	[NITIO_G0_DMA_CFG]		= अणु 0x0b8, 2 पूर्ण,	/* ग_लिखो */
	[NITIO_G0_DMA_STATUS]		= अणु 0x0b8, 2 पूर्ण,	/* पढ़ो */
	[NITIO_G1_DMA_CFG]		= अणु 0x0ba, 2 पूर्ण,	/* ग_लिखो */
	[NITIO_G1_DMA_STATUS]		= अणु 0x0ba, 2 पूर्ण,	/* पढ़ो */
	[NITIO_G2_INT_ACK]		= अणु 0x104, 2 पूर्ण,	/* ग_लिखो */
	[NITIO_G2_STATUS]		= अणु 0x104, 2 पूर्ण,	/* पढ़ो */
	[NITIO_G3_INT_ACK]		= अणु 0x106, 2 पूर्ण,	/* ग_लिखो */
	[NITIO_G3_STATUS]		= अणु 0x106, 2 पूर्ण,	/* पढ़ो */
	[NITIO_G23_STATUS]		= अणु 0x108, 2 पूर्ण,	/* पढ़ो */
	[NITIO_G2_CMD]			= अणु 0x10c, 2 पूर्ण,	/* ग_लिखो */
	[NITIO_G3_CMD]			= अणु 0x10e, 2 पूर्ण,	/* ग_लिखो */
	[NITIO_G2_HW_SAVE]		= अणु 0x110, 4 पूर्ण,	/* पढ़ो */
	[NITIO_G3_HW_SAVE]		= अणु 0x114, 4 पूर्ण,	/* पढ़ो */
	[NITIO_G2_SW_SAVE]		= अणु 0x118, 4 पूर्ण,	/* पढ़ो */
	[NITIO_G3_SW_SAVE]		= अणु 0x11c, 4 पूर्ण,	/* पढ़ो */
	[NITIO_G2_MODE]			= अणु 0x134, 2 पूर्ण,	/* ग_लिखो */
	[NITIO_G23_STATUS1]		= अणु 0x136, 2 पूर्ण,	/* पढ़ो */
	[NITIO_G3_MODE]			= अणु 0x136, 2 पूर्ण,	/* ग_लिखो */
	[NITIO_G2_LOADA]		= अणु 0x138, 4 पूर्ण,	/* ग_लिखो */
	[NITIO_G23_STATUS2]		= अणु 0x13a, 2 पूर्ण,	/* पढ़ो */
	[NITIO_G2_LOADB]		= अणु 0x13c, 4 पूर्ण,	/* ग_लिखो */
	[NITIO_G3_LOADA]		= अणु 0x140, 4 पूर्ण,	/* ग_लिखो */
	[NITIO_G3_LOADB]		= अणु 0x144, 4 पूर्ण,	/* ग_लिखो */
	[NITIO_G2_INPUT_SEL]		= अणु 0x148, 2 पूर्ण,	/* ग_लिखो */
	[NITIO_G3_INPUT_SEL]		= अणु 0x14a, 2 पूर्ण,	/* ग_लिखो */
	[NITIO_G2_AUTO_INC]		= अणु 0x188, 2 पूर्ण,	/* ग_लिखो */
	[NITIO_G3_AUTO_INC]		= अणु 0x18a, 2 पूर्ण,	/* ग_लिखो */
	[NITIO_G23_RESET]		= अणु 0x190, 2 पूर्ण,	/* ग_लिखो */
	[NITIO_G2_INT_ENA]		= अणु 0x192, 2 पूर्ण,	/* ग_लिखो */
	[NITIO_G3_INT_ENA]		= अणु 0x196, 2 पूर्ण,	/* ग_लिखो */
	[NITIO_G2_CNT_MODE]		= अणु 0x1b0, 2 पूर्ण,	/* ग_लिखो */
	[NITIO_G3_CNT_MODE]		= अणु 0x1b2, 2 पूर्ण,	/* ग_लिखो */
	[NITIO_G2_GATE2]		= अणु 0x1b4, 2 पूर्ण,	/* ग_लिखो */
	[NITIO_G3_GATE2]		= अणु 0x1b6, 2 पूर्ण,	/* ग_लिखो */
	[NITIO_G2_DMA_CFG]		= अणु 0x1b8, 2 पूर्ण,	/* ग_लिखो */
	[NITIO_G2_DMA_STATUS]		= अणु 0x1b8, 2 पूर्ण,	/* पढ़ो */
	[NITIO_G3_DMA_CFG]		= अणु 0x1ba, 2 पूर्ण,	/* ग_लिखो */
	[NITIO_G3_DMA_STATUS]		= अणु 0x1ba, 2 पूर्ण,	/* पढ़ो */
	[NI660X_DIO32_INPUT]		= अणु 0x414, 4 पूर्ण,	/* पढ़ो */
	[NI660X_DIO32_OUTPUT]		= अणु 0x510, 4 पूर्ण,	/* ग_लिखो */
	[NI660X_CLK_CFG]		= अणु 0x73c, 4 पूर्ण,	/* ग_लिखो */
	[NI660X_GLOBAL_INT_STATUS]	= अणु 0x754, 4 पूर्ण,	/* पढ़ो */
	[NI660X_DMA_CFG]		= अणु 0x76c, 4 पूर्ण,	/* ग_लिखो */
	[NI660X_GLOBAL_INT_CFG]		= अणु 0x770, 4 पूर्ण,	/* ग_लिखो */
	[NI660X_IO_CFG_0_1]		= अणु 0x77c, 2 पूर्ण,	/* पढ़ो/ग_लिखो */
	[NI660X_IO_CFG_2_3]		= अणु 0x77e, 2 पूर्ण,	/* पढ़ो/ग_लिखो */
	[NI660X_IO_CFG_4_5]		= अणु 0x780, 2 पूर्ण,	/* पढ़ो/ग_लिखो */
	[NI660X_IO_CFG_6_7]		= अणु 0x782, 2 पूर्ण,	/* पढ़ो/ग_लिखो */
	[NI660X_IO_CFG_8_9]		= अणु 0x784, 2 पूर्ण,	/* पढ़ो/ग_लिखो */
	[NI660X_IO_CFG_10_11]		= अणु 0x786, 2 पूर्ण,	/* पढ़ो/ग_लिखो */
	[NI660X_IO_CFG_12_13]		= अणु 0x788, 2 पूर्ण,	/* पढ़ो/ग_लिखो */
	[NI660X_IO_CFG_14_15]		= अणु 0x78a, 2 पूर्ण,	/* पढ़ो/ग_लिखो */
	[NI660X_IO_CFG_16_17]		= अणु 0x78c, 2 पूर्ण,	/* पढ़ो/ग_लिखो */
	[NI660X_IO_CFG_18_19]		= अणु 0x78e, 2 पूर्ण,	/* पढ़ो/ग_लिखो */
	[NI660X_IO_CFG_20_21]		= अणु 0x790, 2 पूर्ण,	/* पढ़ो/ग_लिखो */
	[NI660X_IO_CFG_22_23]		= अणु 0x792, 2 पूर्ण,	/* पढ़ो/ग_लिखो */
	[NI660X_IO_CFG_24_25]		= अणु 0x794, 2 पूर्ण,	/* पढ़ो/ग_लिखो */
	[NI660X_IO_CFG_26_27]		= अणु 0x796, 2 पूर्ण,	/* पढ़ो/ग_लिखो */
	[NI660X_IO_CFG_28_29]		= अणु 0x798, 2 पूर्ण,	/* पढ़ो/ग_लिखो */
	[NI660X_IO_CFG_30_31]		= अणु 0x79a, 2 पूर्ण,	/* पढ़ो/ग_लिखो */
	[NI660X_IO_CFG_32_33]		= अणु 0x79c, 2 पूर्ण,	/* पढ़ो/ग_लिखो */
	[NI660X_IO_CFG_34_35]		= अणु 0x79e, 2 पूर्ण,	/* पढ़ो/ग_लिखो */
	[NI660X_IO_CFG_36_37]		= अणु 0x7a0, 2 पूर्ण,	/* पढ़ो/ग_लिखो */
	[NI660X_IO_CFG_38_39]		= अणु 0x7a2, 2 पूर्ण	/* पढ़ो/ग_लिखो */
पूर्ण;

#घोषणा NI660X_CHIP_OFFSET		0x800

क्रमागत ni_660x_boardid अणु
	BOARD_PCI6601,
	BOARD_PCI6602,
	BOARD_PXI6602,
	BOARD_PCI6608,
	BOARD_PXI6608,
	BOARD_PCI6624,
	BOARD_PXI6624
पूर्ण;

काष्ठा ni_660x_board अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक n_chips;	/* total number of TIO chips */
पूर्ण;

अटल स्थिर काष्ठा ni_660x_board ni_660x_boards[] = अणु
	[BOARD_PCI6601] = अणु
		.name		= "PCI-6601",
		.n_chips	= 1,
	पूर्ण,
	[BOARD_PCI6602] = अणु
		.name		= "PCI-6602",
		.n_chips	= 2,
	पूर्ण,
	[BOARD_PXI6602] = अणु
		.name		= "PXI-6602",
		.n_chips	= 2,
	पूर्ण,
	[BOARD_PCI6608] = अणु
		.name		= "PCI-6608",
		.n_chips	= 2,
	पूर्ण,
	[BOARD_PXI6608] = अणु
		.name		= "PXI-6608",
		.n_chips	= 2,
	पूर्ण,
	[BOARD_PCI6624] = अणु
		.name		= "PCI-6624",
		.n_chips	= 2,
	पूर्ण,
	[BOARD_PXI6624] = अणु
		.name		= "PXI-6624",
		.n_chips	= 2,
	पूर्ण,
पूर्ण;

#घोषणा NI660X_NUM_PFI_CHANNELS		40

/* there are only up to 3 dma channels, but the रेजिस्टर layout allows क्रम 4 */
#घोषणा NI660X_MAX_DMA_CHANNEL		4

#घोषणा NI660X_COUNTERS_PER_CHIP	4
#घोषणा NI660X_MAX_CHIPS		2
#घोषणा NI660X_MAX_COUNTERS		(NI660X_MAX_CHIPS *	\
					 NI660X_COUNTERS_PER_CHIP)

काष्ठा ni_660x_निजी अणु
	काष्ठा mite *mite;
	काष्ठा ni_gpct_device *counter_dev;
	काष्ठा mite_ring *ring[NI660X_MAX_CHIPS][NI660X_COUNTERS_PER_CHIP];
	/* protects mite channel request/release */
	spinlock_t mite_channel_lock;
	/* prevents races between पूर्णांकerrupt and comedi_poll */
	spinlock_t पूर्णांकerrupt_lock;
	अचिन्हित पूर्णांक dma_cfg[NI660X_MAX_CHIPS];
	अचिन्हित पूर्णांक io_cfg[NI660X_NUM_PFI_CHANNELS];
	u64 io_dir;
	काष्ठा ni_route_tables routing_tables;
पूर्ण;

अटल व्योम ni_660x_ग_लिखो(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक chip,
			  अचिन्हित पूर्णांक bits, अचिन्हित पूर्णांक reg)
अणु
	अचिन्हित पूर्णांक addr = (chip * NI660X_CHIP_OFFSET) +
			    ni_660x_reg_data[reg].offset;

	अगर (ni_660x_reg_data[reg].size == 2)
		ग_लिखोw(bits, dev->mmio + addr);
	अन्यथा
		ग_लिखोl(bits, dev->mmio + addr);
पूर्ण

अटल अचिन्हित पूर्णांक ni_660x_पढ़ो(काष्ठा comedi_device *dev,
				 अचिन्हित पूर्णांक chip, अचिन्हित पूर्णांक reg)
अणु
	अचिन्हित पूर्णांक addr = (chip * NI660X_CHIP_OFFSET) +
			    ni_660x_reg_data[reg].offset;

	अगर (ni_660x_reg_data[reg].size == 2)
		वापस पढ़ोw(dev->mmio + addr);
	वापस पढ़ोl(dev->mmio + addr);
पूर्ण

अटल व्योम ni_660x_gpct_ग_लिखो(काष्ठा ni_gpct *counter, अचिन्हित पूर्णांक bits,
			       क्रमागत ni_gpct_रेजिस्टर reg)
अणु
	काष्ठा comedi_device *dev = counter->counter_dev->dev;

	ni_660x_ग_लिखो(dev, counter->chip_index, bits, reg);
पूर्ण

अटल अचिन्हित पूर्णांक ni_660x_gpct_पढ़ो(काष्ठा ni_gpct *counter,
				      क्रमागत ni_gpct_रेजिस्टर reg)
अणु
	काष्ठा comedi_device *dev = counter->counter_dev->dev;

	वापस ni_660x_पढ़ो(dev, counter->chip_index, reg);
पूर्ण

अटल अंतरभूत व्योम ni_660x_set_dma_channel(काष्ठा comedi_device *dev,
					   अचिन्हित पूर्णांक mite_channel,
					   काष्ठा ni_gpct *counter)
अणु
	काष्ठा ni_660x_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chip = counter->chip_index;

	devpriv->dma_cfg[chip] &= ~NI660X_DMA_CFG_SEL_MASK(mite_channel);
	devpriv->dma_cfg[chip] |= NI660X_DMA_CFG_SEL(mite_channel,
						     counter->counter_index);
	ni_660x_ग_लिखो(dev, chip, devpriv->dma_cfg[chip] |
		      NI660X_DMA_CFG_RESET(mite_channel),
		      NI660X_DMA_CFG);
पूर्ण

अटल अंतरभूत व्योम ni_660x_unset_dma_channel(काष्ठा comedi_device *dev,
					     अचिन्हित पूर्णांक mite_channel,
					     काष्ठा ni_gpct *counter)
अणु
	काष्ठा ni_660x_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chip = counter->chip_index;

	devpriv->dma_cfg[chip] &= ~NI660X_DMA_CFG_SEL_MASK(mite_channel);
	devpriv->dma_cfg[chip] |= NI660X_DMA_CFG_SEL_NONE(mite_channel);
	ni_660x_ग_लिखो(dev, chip, devpriv->dma_cfg[chip], NI660X_DMA_CFG);
पूर्ण

अटल पूर्णांक ni_660x_request_mite_channel(काष्ठा comedi_device *dev,
					काष्ठा ni_gpct *counter,
					क्रमागत comedi_io_direction direction)
अणु
	काष्ठा ni_660x_निजी *devpriv = dev->निजी;
	काष्ठा mite_ring *ring;
	काष्ठा mite_channel *mite_chan;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&devpriv->mite_channel_lock, flags);
	ring = devpriv->ring[counter->chip_index][counter->counter_index];
	mite_chan = mite_request_channel(devpriv->mite, ring);
	अगर (!mite_chan) अणु
		spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);
		dev_err(dev->class_dev,
			"failed to reserve mite dma channel for counter\n");
		वापस -EBUSY;
	पूर्ण
	mite_chan->dir = direction;
	ni_tio_set_mite_channel(counter, mite_chan);
	ni_660x_set_dma_channel(dev, mite_chan->channel, counter);
	spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);
	वापस 0;
पूर्ण

अटल व्योम ni_660x_release_mite_channel(काष्ठा comedi_device *dev,
					 काष्ठा ni_gpct *counter)
अणु
	काष्ठा ni_660x_निजी *devpriv = dev->निजी;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&devpriv->mite_channel_lock, flags);
	अगर (counter->mite_chan) अणु
		काष्ठा mite_channel *mite_chan = counter->mite_chan;

		ni_660x_unset_dma_channel(dev, mite_chan->channel, counter);
		ni_tio_set_mite_channel(counter, शून्य);
		mite_release_channel(mite_chan);
	पूर्ण
	spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);
पूर्ण

अटल पूर्णांक ni_660x_cmd(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	काष्ठा ni_gpct *counter = s->निजी;
	पूर्णांक retval;

	retval = ni_660x_request_mite_channel(dev, counter, COMEDI_INPUT);
	अगर (retval) अणु
		dev_err(dev->class_dev,
			"no dma channel available for use by counter\n");
		वापस retval;
	पूर्ण
	ni_tio_acknowledge(counter);

	वापस ni_tio_cmd(dev, s);
पूर्ण

अटल पूर्णांक ni_660x_cancel(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	काष्ठा ni_gpct *counter = s->निजी;
	पूर्णांक retval;

	retval = ni_tio_cancel(counter);
	ni_660x_release_mite_channel(dev, counter);
	वापस retval;
पूर्ण

अटल व्योम set_tio_counterswap(काष्ठा comedi_device *dev, पूर्णांक chip)
अणु
	अचिन्हित पूर्णांक bits = 0;

	/*
	 * See P. 3.5 of the Register-Level Programming manual.
	 * The CounterSwap bit has to be set on the second chip,
	 * otherwise it will try to use the same pins as the
	 * first chip.
	 */
	अगर (chip)
		bits = NI660X_CLK_CFG_COUNTER_SWAP;

	ni_660x_ग_लिखो(dev, chip, bits, NI660X_CLK_CFG);
पूर्ण

अटल व्योम ni_660x_handle_gpct_पूर्णांकerrupt(काष्ठा comedi_device *dev,
					  काष्ठा comedi_subdevice *s)
अणु
	काष्ठा ni_gpct *counter = s->निजी;

	ni_tio_handle_पूर्णांकerrupt(counter, s);
	comedi_handle_events(dev, s);
पूर्ण

अटल irqवापस_t ni_660x_पूर्णांकerrupt(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा comedi_device *dev = d;
	काष्ठा ni_660x_निजी *devpriv = dev->निजी;
	काष्ठा comedi_subdevice *s;
	अचिन्हित पूर्णांक i;
	अचिन्हित दीर्घ flags;

	अगर (!dev->attached)
		वापस IRQ_NONE;
	/* make sure dev->attached is checked beक्रमe करोing anything अन्यथा */
	smp_mb();

	/* lock to aव्योम race with comedi_poll */
	spin_lock_irqsave(&devpriv->पूर्णांकerrupt_lock, flags);
	क्रम (i = 0; i < dev->n_subdevices; ++i) अणु
		s = &dev->subdevices[i];
		अगर (s->type == COMEDI_SUBD_COUNTER)
			ni_660x_handle_gpct_पूर्णांकerrupt(dev, s);
	पूर्ण
	spin_unlock_irqrestore(&devpriv->पूर्णांकerrupt_lock, flags);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ni_660x_input_poll(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s)
अणु
	काष्ठा ni_660x_निजी *devpriv = dev->निजी;
	काष्ठा ni_gpct *counter = s->निजी;
	अचिन्हित दीर्घ flags;

	/* lock to aव्योम race with comedi_poll */
	spin_lock_irqsave(&devpriv->पूर्णांकerrupt_lock, flags);
	mite_sync_dma(counter->mite_chan, s);
	spin_unlock_irqrestore(&devpriv->पूर्णांकerrupt_lock, flags);
	वापस comedi_buf_पढ़ो_n_available(s);
पूर्ण

अटल पूर्णांक ni_660x_buf_change(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s)
अणु
	काष्ठा ni_660x_निजी *devpriv = dev->निजी;
	काष्ठा ni_gpct *counter = s->निजी;
	काष्ठा mite_ring *ring;
	पूर्णांक ret;

	ring = devpriv->ring[counter->chip_index][counter->counter_index];
	ret = mite_buf_change(ring, s);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक ni_660x_allocate_निजी(काष्ठा comedi_device *dev)
अणु
	काष्ठा ni_660x_निजी *devpriv;
	अचिन्हित पूर्णांक i;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	spin_lock_init(&devpriv->mite_channel_lock);
	spin_lock_init(&devpriv->पूर्णांकerrupt_lock);
	क्रम (i = 0; i < NI660X_NUM_PFI_CHANNELS; ++i)
		devpriv->io_cfg[i] = NI_660X_PFI_OUTPUT_COUNTER;

	वापस 0;
पूर्ण

अटल पूर्णांक ni_660x_alloc_mite_rings(काष्ठा comedi_device *dev)
अणु
	स्थिर काष्ठा ni_660x_board *board = dev->board_ptr;
	काष्ठा ni_660x_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक j;

	क्रम (i = 0; i < board->n_chips; ++i) अणु
		क्रम (j = 0; j < NI660X_COUNTERS_PER_CHIP; ++j) अणु
			devpriv->ring[i][j] = mite_alloc_ring(devpriv->mite);
			अगर (!devpriv->ring[i][j])
				वापस -ENOMEM;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम ni_660x_मुक्त_mite_rings(काष्ठा comedi_device *dev)
अणु
	स्थिर काष्ठा ni_660x_board *board = dev->board_ptr;
	काष्ठा ni_660x_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक j;

	क्रम (i = 0; i < board->n_chips; ++i) अणु
		क्रम (j = 0; j < NI660X_COUNTERS_PER_CHIP; ++j)
			mite_मुक्त_ring(devpriv->ring[i][j]);
	पूर्ण
पूर्ण

अटल पूर्णांक ni_660x_dio_insn_bits(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक shअगरt = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक mask = data[0] << shअगरt;
	अचिन्हित पूर्णांक bits = data[1] << shअगरt;

	/*
	 * There are 40 channels in this subdevice but only 32 are usable
	 * as DIO. The shअगरt adjusts the mask/bits to account क्रम the base
	 * channel in insn->chanspec. The state update can then be handled
	 * normally क्रम the 32 usable channels.
	 */
	अगर (mask) अणु
		s->state &= ~mask;
		s->state |= (bits & mask);
		ni_660x_ग_लिखो(dev, 0, s->state, NI660X_DIO32_OUTPUT);
	पूर्ण

	/*
	 * Return the input channels, shअगरted back to account क्रम the base
	 * channel.
	 */
	data[1] = ni_660x_पढ़ो(dev, 0, NI660X_DIO32_INPUT) >> shअगरt;

	वापस insn->n;
पूर्ण

अटल व्योम ni_660x_select_pfi_output(काष्ठा comedi_device *dev,
				      अचिन्हित पूर्णांक chan, अचिन्हित पूर्णांक out_sel)
अणु
	स्थिर काष्ठा ni_660x_board *board = dev->board_ptr;
	अचिन्हित पूर्णांक active_chip = 0;
	अचिन्हित पूर्णांक idle_chip = 0;
	अचिन्हित पूर्णांक bits;

	अगर (chan >= NI_PFI(0))
		/* allow new and old names of pfi channels to work. */
		chan -= NI_PFI(0);

	अगर (board->n_chips > 1) अणु
		अगर (out_sel == NI_660X_PFI_OUTPUT_COUNTER &&
		    chan >= 8 && chan <= 23) अणु
			/* counters 4-7 pfi channels */
			active_chip = 1;
			idle_chip = 0;
		पूर्ण अन्यथा अणु
			/* counters 0-3 pfi channels */
			active_chip = 0;
			idle_chip = 1;
		पूर्ण
	पूर्ण

	अगर (idle_chip != active_chip) अणु
		/* set the pfi channel to high-z on the inactive chip */
		bits = ni_660x_पढ़ो(dev, idle_chip, NI660X_IO_CFG(chan));
		bits &= ~NI660X_IO_CFG_OUT_SEL_MASK(chan);
		bits |= NI660X_IO_CFG_OUT_SEL(chan, 0);		/* high-z */
		ni_660x_ग_लिखो(dev, idle_chip, bits, NI660X_IO_CFG(chan));
	पूर्ण

	/* set the pfi channel output on the active chip */
	bits = ni_660x_पढ़ो(dev, active_chip, NI660X_IO_CFG(chan));
	bits &= ~NI660X_IO_CFG_OUT_SEL_MASK(chan);
	bits |= NI660X_IO_CFG_OUT_SEL(chan, out_sel);
	ni_660x_ग_लिखो(dev, active_chip, bits, NI660X_IO_CFG(chan));
पूर्ण

अटल व्योम ni_660x_set_pfi_direction(काष्ठा comedi_device *dev,
				      अचिन्हित पूर्णांक chan,
				      अचिन्हित पूर्णांक direction)
अणु
	काष्ठा ni_660x_निजी *devpriv = dev->निजी;
	u64 bit;

	अगर (chan >= NI_PFI(0))
		/* allow new and old names of pfi channels to work. */
		chan -= NI_PFI(0);

	bit = 1ULL << chan;

	अगर (direction == COMEDI_OUTPUT) अणु
		devpriv->io_dir |= bit;
		/* reset the output to currently asचिन्हित output value */
		ni_660x_select_pfi_output(dev, chan, devpriv->io_cfg[chan]);
	पूर्ण अन्यथा अणु
		devpriv->io_dir &= ~bit;
		/* set pin to high-z; करो not change currently asचिन्हित route */
		ni_660x_select_pfi_output(dev, chan, 0);
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक ni_660x_get_pfi_direction(काष्ठा comedi_device *dev,
					      अचिन्हित पूर्णांक chan)
अणु
	काष्ठा ni_660x_निजी *devpriv = dev->निजी;
	u64 bit;

	अगर (chan >= NI_PFI(0))
		/* allow new and old names of pfi channels to work. */
		chan -= NI_PFI(0);

	bit = 1ULL << chan;

	वापस (devpriv->io_dir & bit) ? COMEDI_OUTPUT : COMEDI_INPUT;
पूर्ण

अटल पूर्णांक ni_660x_set_pfi_routing(काष्ठा comedi_device *dev,
				   अचिन्हित पूर्णांक chan, अचिन्हित पूर्णांक source)
अणु
	काष्ठा ni_660x_निजी *devpriv = dev->निजी;

	अगर (chan >= NI_PFI(0))
		/* allow new and old names of pfi channels to work. */
		chan -= NI_PFI(0);

	चयन (source) अणु
	हाल NI_660X_PFI_OUTPUT_COUNTER:
		अगर (chan < 8)
			वापस -EINVAL;
		अवरोध;
	हाल NI_660X_PFI_OUTPUT_DIO:
		अगर (chan > 31)
			वापस -EINVAL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	devpriv->io_cfg[chan] = source;
	अगर (ni_660x_get_pfi_direction(dev, chan) == COMEDI_OUTPUT)
		ni_660x_select_pfi_output(dev, chan, devpriv->io_cfg[chan]);
	वापस 0;
पूर्ण

अटल पूर्णांक ni_660x_get_pfi_routing(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक chan)
अणु
	काष्ठा ni_660x_निजी *devpriv = dev->निजी;

	अगर (chan >= NI_PFI(0))
		/* allow new and old names of pfi channels to work. */
		chan -= NI_PFI(0);

	वापस devpriv->io_cfg[chan];
पूर्ण

अटल व्योम ni_660x_set_pfi_filter(काष्ठा comedi_device *dev,
				   अचिन्हित पूर्णांक chan, अचिन्हित पूर्णांक value)
अणु
	अचिन्हित पूर्णांक val;

	अगर (chan >= NI_PFI(0))
		/* allow new and old names of pfi channels to work. */
		chan -= NI_PFI(0);

	val = ni_660x_पढ़ो(dev, 0, NI660X_IO_CFG(chan));
	val &= ~NI660X_IO_CFG_IN_SEL_MASK(chan);
	val |= NI660X_IO_CFG_IN_SEL(chan, value);
	ni_660x_ग_लिखो(dev, 0, val, NI660X_IO_CFG(chan));
पूर्ण

अटल पूर्णांक ni_660x_dio_insn_config(काष्ठा comedi_device *dev,
				   काष्ठा comedi_subdevice *s,
				   काष्ठा comedi_insn *insn,
				   अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	पूर्णांक ret;

	चयन (data[0]) अणु
	हाल INSN_CONFIG_DIO_OUTPUT:
		ni_660x_set_pfi_direction(dev, chan, COMEDI_OUTPUT);
		अवरोध;

	हाल INSN_CONFIG_DIO_INPUT:
		ni_660x_set_pfi_direction(dev, chan, COMEDI_INPUT);
		अवरोध;

	हाल INSN_CONFIG_DIO_QUERY:
		data[1] = ni_660x_get_pfi_direction(dev, chan);
		अवरोध;

	हाल INSN_CONFIG_SET_ROUTING:
		ret = ni_660x_set_pfi_routing(dev, chan, data[1]);
		अगर (ret)
			वापस ret;
		अवरोध;

	हाल INSN_CONFIG_GET_ROUTING:
		data[1] = ni_660x_get_pfi_routing(dev, chan);
		अवरोध;

	हाल INSN_CONFIG_FILTER:
		ni_660x_set_pfi_filter(dev, chan, data[1]);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस insn->n;
पूर्ण

अटल अचिन्हित पूर्णांक _ni_get_valid_routes(काष्ठा comedi_device *dev,
					 अचिन्हित पूर्णांक n_pairs,
					 अचिन्हित पूर्णांक *pair_data)
अणु
	काष्ठा ni_660x_निजी *devpriv = dev->निजी;

	वापस ni_get_valid_routes(&devpriv->routing_tables, n_pairs,
				   pair_data);
पूर्ण

/*
 * Retrieves the current source of the output selector क्रम the given
 * destination.  If the terminal क्रम the destination is not alपढ़ोy configured
 * as an output, this function वापसs -EINVAL as error.
 *
 * Return: The रेजिस्टर value of the destination output selector;
 *	   -EINVAL अगर terminal is not configured क्रम output.
 */
अटल अंतरभूत पूर्णांक get_output_select_source(पूर्णांक dest, काष्ठा comedi_device *dev)
अणु
	काष्ठा ni_660x_निजी *devpriv = dev->निजी;
	पूर्णांक reg = -1;

	अगर (channel_is_pfi(dest)) अणु
		अगर (ni_660x_get_pfi_direction(dev, dest) == COMEDI_OUTPUT)
			reg = ni_660x_get_pfi_routing(dev, dest);
	पूर्ण अन्यथा अगर (channel_is_rtsi(dest)) अणु
		dev_dbg(dev->class_dev,
			"%s: unhandled rtsi destination (%d) queried\n",
			__func__, dest);
		/*
		 * The following can be enabled when RTSI routing info is
		 * determined (not currently करोcumented):
		 * अगर (ni_get_rtsi_direction(dev, dest) == COMEDI_OUTPUT) अणु
		 *	reg = ni_get_rtsi_routing(dev, dest);

		 *	अगर (reg == NI_RTSI_OUTPUT_RGOUT0) अणु
		 *		dest = NI_RGOUT0; ** prepare क्रम lookup below **
		 *		reg = get_rgout0_reg(dev);
		 *	पूर्ण अन्यथा अगर (reg >= NI_RTSI_OUTPUT_RTSI_BRD(0) &&
		 *		   reg <= NI_RTSI_OUTPUT_RTSI_BRD(3)) अणु
		 *		स्थिर पूर्णांक i = reg - NI_RTSI_OUTPUT_RTSI_BRD(0);

		 *		dest = NI_RTSI_BRD(i); ** prepare क्रम lookup **
		 *		reg = get_ith_rtsi_brd_reg(i, dev);
		 *	पूर्ण
		 * पूर्ण
		 */
	पूर्ण अन्यथा अगर (channel_is_ctr(dest)) अणु
		reg = ni_tio_get_routing(devpriv->counter_dev, dest);
	पूर्ण अन्यथा अणु
		dev_dbg(dev->class_dev,
			"%s: unhandled destination (%d) queried\n",
			__func__, dest);
	पूर्ण

	अगर (reg >= 0)
		वापस ni_find_route_source(CR_CHAN(reg), dest,
					    &devpriv->routing_tables);
	वापस -EINVAL;
पूर्ण

/*
 * Test a route:
 *
 * Return: -1 अगर not connectible;
 *	    0 अगर connectible and not connected;
 *	    1 अगर connectible and connected.
 */
अटल अंतरभूत पूर्णांक test_route(अचिन्हित पूर्णांक src, अचिन्हित पूर्णांक dest,
			     काष्ठा comedi_device *dev)
अणु
	काष्ठा ni_660x_निजी *devpriv = dev->निजी;
	s8 reg = ni_route_to_रेजिस्टर(CR_CHAN(src), dest,
				      &devpriv->routing_tables);

	अगर (reg < 0)
		वापस -1;
	अगर (get_output_select_source(dest, dev) != CR_CHAN(src))
		वापस 0;
	वापस 1;
पूर्ण

/* Connect the actual route.  */
अटल अंतरभूत पूर्णांक connect_route(अचिन्हित पूर्णांक src, अचिन्हित पूर्णांक dest,
				काष्ठा comedi_device *dev)
अणु
	काष्ठा ni_660x_निजी *devpriv = dev->निजी;
	s8 reg = ni_route_to_रेजिस्टर(CR_CHAN(src), dest,
				      &devpriv->routing_tables);
	s8 current_src;

	अगर (reg < 0)
		/* route is not valid */
		वापस -EINVAL;

	current_src = get_output_select_source(dest, dev);
	अगर (current_src == CR_CHAN(src))
		वापस -EALREADY;
	अगर (current_src >= 0)
		/* destination mux is alपढ़ोy busy. complain, करोn't overग_लिखो */
		वापस -EBUSY;

	/* The route is valid and available. Now connect... */
	अगर (channel_is_pfi(CR_CHAN(dest))) अणु
		/*
		 * set routing and then direction so that the output करोes not
		 * first get generated with the wrong pin
		 */
		ni_660x_set_pfi_routing(dev, dest, reg);
		ni_660x_set_pfi_direction(dev, dest, COMEDI_OUTPUT);
	पूर्ण अन्यथा अगर (channel_is_rtsi(CR_CHAN(dest))) अणु
		dev_dbg(dev->class_dev, "%s: unhandled rtsi destination (%d)\n",
			__func__, dest);
		वापस -EINVAL;
		/*
		 * The following can be enabled when RTSI routing info is
		 * determined (not currently करोcumented):
		 * अगर (reg == NI_RTSI_OUTPUT_RGOUT0) अणु
		 *	पूर्णांक ret = incr_rgout0_src_use(src, dev);

		 *	अगर (ret < 0)
		 *		वापस ret;
		 * पूर्ण अन्यथा अगर (ni_rtsi_route_requires_mux(reg)) अणु
		 *	** Attempt to allocate and  route (src->brd) **
		 *	पूर्णांक brd = incr_rtsi_brd_src_use(src, dev);

		 *	अगर (brd < 0)
		 *		वापस brd;

		 *	** Now lookup the रेजिस्टर value क्रम (brd->dest) **
		 *	reg = ni_lookup_route_रेजिस्टर(brd, CR_CHAN(dest),
		 *				       &devpriv->routing_tables);
		 * पूर्ण

		 * ni_set_rtsi_direction(dev, dest, COMEDI_OUTPUT);
		 * ni_set_rtsi_routing(dev, dest, reg);
		 */
	पूर्ण अन्यथा अगर (channel_is_ctr(CR_CHAN(dest))) अणु
		/*
		 * we are adding back the channel modअगरier info to set
		 * invert/edge info passed by the user
		 */
		ni_tio_set_routing(devpriv->counter_dev, dest,
				   reg | (src & ~CR_CHAN(-1)));
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक disconnect_route(अचिन्हित पूर्णांक src, अचिन्हित पूर्णांक dest,
				   काष्ठा comedi_device *dev)
अणु
	काष्ठा ni_660x_निजी *devpriv = dev->निजी;
	s8 reg = ni_route_to_रेजिस्टर(CR_CHAN(src), CR_CHAN(dest),
				      &devpriv->routing_tables);

	अगर (reg < 0)
		/* route is not valid */
		वापस -EINVAL;
	अगर (get_output_select_source(dest, dev) != CR_CHAN(src))
		/* cannot disconnect something not connected */
		वापस -EINVAL;

	/* The route is valid and is connected.  Now disconnect... */
	अगर (channel_is_pfi(CR_CHAN(dest))) अणु
		अचिन्हित पूर्णांक source = ((CR_CHAN(dest) - NI_PFI(0)) < 8)
					? NI_660X_PFI_OUTPUT_DIO
					: NI_660X_PFI_OUTPUT_COUNTER;

		/* set the pfi to high impedance, and disconnect */
		ni_660x_set_pfi_direction(dev, dest, COMEDI_INPUT);
		ni_660x_set_pfi_routing(dev, dest, source);
	पूर्ण अन्यथा अगर (channel_is_rtsi(CR_CHAN(dest))) अणु
		dev_dbg(dev->class_dev, "%s: unhandled rtsi destination (%d)\n",
			__func__, dest);
		वापस -EINVAL;
		/*
		 * The following can be enabled when RTSI routing info is
		 * determined (not currently करोcumented):
		 * अगर (reg == NI_RTSI_OUTPUT_RGOUT0) अणु
		 *	पूर्णांक ret = decr_rgout0_src_use(src, dev);

		 *	अगर (ret < 0)
		 *		वापस ret;
		 * पूर्ण अन्यथा अगर (ni_rtsi_route_requires_mux(reg)) अणु
		 *	** find which RTSI_BRD line is source क्रम rtsi pin **
		 *	पूर्णांक brd = ni_find_route_source(
		 *		ni_get_rtsi_routing(dev, dest), CR_CHAN(dest),
		 *		&devpriv->routing_tables);

		 *	अगर (brd < 0)
		 *		वापस brd;

		 *	** decrement/disconnect RTSI_BRD line from source **
		 *	decr_rtsi_brd_src_use(src, brd, dev);
		 * पूर्ण

		 * ** set rtsi output selector to शेष state **
		 * reg = शेष_rtsi_routing[CR_CHAN(dest) - TRIGGER_LINE(0)];
		 * ni_set_rtsi_direction(dev, dest, COMEDI_INPUT);
		 * ni_set_rtsi_routing(dev, dest, reg);
		 */
	पूर्ण अन्यथा अगर (channel_is_ctr(CR_CHAN(dest))) अणु
		ni_tio_unset_routing(devpriv->counter_dev, dest);
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ni_global_insn_config(काष्ठा comedi_device *dev,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	चयन (data[0]) अणु
	हाल INSN_DEVICE_CONFIG_TEST_ROUTE:
		data[0] = test_route(data[1], data[2], dev);
		वापस 2;
	हाल INSN_DEVICE_CONFIG_CONNECT_ROUTE:
		वापस connect_route(data[1], data[2], dev);
	हाल INSN_DEVICE_CONFIG_DISCONNECT_ROUTE:
		वापस disconnect_route(data[1], data[2], dev);
	/*
	 * This हाल is alपढ़ोy handled one level up.
	 * हाल INSN_DEVICE_CONFIG_GET_ROUTES:
	 */
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 1;
पूर्ण

अटल व्योम ni_660x_init_tio_chips(काष्ठा comedi_device *dev,
				   अचिन्हित पूर्णांक n_chips)
अणु
	काष्ठा ni_660x_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chip;
	अचिन्हित पूर्णांक chan;

	/*
	 * We use the ioconfig रेजिस्टरs to control dio direction, so zero
	 * output enables in stc dio control reg.
	 */
	ni_660x_ग_लिखो(dev, 0, 0, NI660X_STC_DIO_CONTROL);

	क्रम (chip = 0; chip < n_chips; ++chip) अणु
		/* init dma configuration रेजिस्टर */
		devpriv->dma_cfg[chip] = 0;
		क्रम (chan = 0; chan < NI660X_MAX_DMA_CHANNEL; ++chan)
			devpriv->dma_cfg[chip] |= NI660X_DMA_CFG_SEL_NONE(chan);
		ni_660x_ग_लिखो(dev, chip, devpriv->dma_cfg[chip],
			      NI660X_DMA_CFG);

		/* init ioconfig रेजिस्टरs */
		क्रम (chan = 0; chan < NI660X_NUM_PFI_CHANNELS; ++chan)
			ni_660x_ग_लिखो(dev, chip, 0, NI660X_IO_CFG(chan));
	पूर्ण
पूर्ण

अटल पूर्णांक ni_660x_स्वतः_attach(काष्ठा comedi_device *dev,
			       अचिन्हित दीर्घ context)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	स्थिर काष्ठा ni_660x_board *board = शून्य;
	काष्ठा ni_660x_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	काष्ठा ni_gpct_device *gpct_dev;
	अचिन्हित पूर्णांक n_counters;
	पूर्णांक subdev;
	पूर्णांक ret;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक global_पूर्णांकerrupt_config_bits;

	अगर (context < ARRAY_SIZE(ni_660x_boards))
		board = &ni_660x_boards[context];
	अगर (!board)
		वापस -ENODEV;
	dev->board_ptr = board;
	dev->board_name = board->name;

	ret = comedi_pci_enable(dev);
	अगर (ret)
		वापस ret;

	ret = ni_660x_allocate_निजी(dev);
	अगर (ret < 0)
		वापस ret;
	devpriv = dev->निजी;

	devpriv->mite = mite_attach(dev, true);		/* use win1 */
	अगर (!devpriv->mite)
		वापस -ENOMEM;

	ret = ni_660x_alloc_mite_rings(dev);
	अगर (ret < 0)
		वापस ret;

	ni_660x_init_tio_chips(dev, board->n_chips);

	/* prepare the device क्रम globally-named routes. */
	अगर (ni_assign_device_routes("ni_660x", board->name, शून्य,
				    &devpriv->routing_tables) < 0) अणु
		dev_warn(dev->class_dev, "%s: %s device has no signal routing table.\n",
			 __func__, board->name);
		dev_warn(dev->class_dev, "%s: High level NI signal names will not be available for this %s board.\n",
			 __func__, board->name);
	पूर्ण अन्यथा अणु
		/*
		 * only(?) assign insn_device_config अगर we have global names क्रम
		 * this device.
		 */
		dev->insn_device_config = ni_global_insn_config;
		dev->get_valid_routes = _ni_get_valid_routes;
	पूर्ण

	n_counters = board->n_chips * NI660X_COUNTERS_PER_CHIP;
	gpct_dev = ni_gpct_device_स्थिरruct(dev,
					    ni_660x_gpct_ग_लिखो,
					    ni_660x_gpct_पढ़ो,
					    ni_gpct_variant_660x,
					    n_counters,
					    NI660X_COUNTERS_PER_CHIP,
					    &devpriv->routing_tables);
	अगर (!gpct_dev)
		वापस -ENOMEM;
	devpriv->counter_dev = gpct_dev;

	ret = comedi_alloc_subdevices(dev, 2 + NI660X_MAX_COUNTERS);
	अगर (ret)
		वापस ret;

	subdev = 0;

	s = &dev->subdevices[subdev++];
	/* Old GENERAL-PURPOSE COUNTER/TIME (GPCT) subdevice, no दीर्घer used */
	s->type = COMEDI_SUBD_UNUSED;

	/*
	 * Digital I/O subdevice
	 *
	 * There are 40 channels but only the first 32 can be digital I/Os.
	 * The last 8 are dedicated to counters 0 and 1.
	 *
	 * Counter 0-3 संकेतs are from the first TIO chip.
	 * Counter 4-7 संकेतs are from the second TIO chip.
	 *
	 * Comedi	External
	 * PFI Chan	DIO Chan        Counter Signal
	 * -------	--------	--------------
	 *     0	    0
	 *     1	    1
	 *     2	    2
	 *     3	    3
	 *     4	    4
	 *     5	    5
	 *     6	    6
	 *     7	    7
	 *     8	    8		CTR 7 OUT
	 *     9	    9		CTR 7 AUX
	 *    10	   10		CTR 7 GATE
	 *    11	   11		CTR 7 SOURCE
	 *    12	   12		CTR 6 OUT
	 *    13	   13		CTR 6 AUX
	 *    14	   14		CTR 6 GATE
	 *    15	   15		CTR 6 SOURCE
	 *    16	   16		CTR 5 OUT
	 *    17	   17		CTR 5 AUX
	 *    18	   18		CTR 5 GATE
	 *    19	   19		CTR 5 SOURCE
	 *    20	   20		CTR 4 OUT
	 *    21	   21		CTR 4 AUX
	 *    22	   22		CTR 4 GATE
	 *    23	   23		CTR 4 SOURCE
	 *    24	   24		CTR 3 OUT
	 *    25	   25		CTR 3 AUX
	 *    26	   26		CTR 3 GATE
	 *    27	   27		CTR 3 SOURCE
	 *    28	   28		CTR 2 OUT
	 *    29	   29		CTR 2 AUX
	 *    30	   30		CTR 2 GATE
	 *    31	   31		CTR 2 SOURCE
	 *    32			CTR 1 OUT
	 *    33			CTR 1 AUX
	 *    34			CTR 1 GATE
	 *    35			CTR 1 SOURCE
	 *    36			CTR 0 OUT
	 *    37			CTR 0 AUX
	 *    38			CTR 0 GATE
	 *    39			CTR 0 SOURCE
	 */
	s = &dev->subdevices[subdev++];
	s->type		= COMEDI_SUBD_DIO;
	s->subdev_flags	= SDF_READABLE | SDF_WRITABLE;
	s->n_chan	= NI660X_NUM_PFI_CHANNELS;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= ni_660x_dio_insn_bits;
	s->insn_config	= ni_660x_dio_insn_config;

	 /*
	  * Default the DIO channels as:
	  *   chan 0-7:  DIO inमाला_दो
	  *   chan 8-39: counter संकेत inमाला_दो
	  */
	क्रम (i = 0; i < s->n_chan; ++i) अणु
		अचिन्हित पूर्णांक source = (i < 8) ? NI_660X_PFI_OUTPUT_DIO
					      : NI_660X_PFI_OUTPUT_COUNTER;

		ni_660x_set_pfi_routing(dev, i, source);
		ni_660x_set_pfi_direction(dev, i, COMEDI_INPUT);/* high-z */
	पूर्ण

	/* Counter subdevices (4 NI TIO General Purpose Counters per chip) */
	क्रम (i = 0; i < NI660X_MAX_COUNTERS; ++i) अणु
		s = &dev->subdevices[subdev++];
		अगर (i < n_counters) अणु
			काष्ठा ni_gpct *counter = &gpct_dev->counters[i];

			s->type		= COMEDI_SUBD_COUNTER;
			s->subdev_flags	= SDF_READABLE | SDF_WRITABLE |
					  SDF_LSAMPL | SDF_CMD_READ;
			s->n_chan	= 3;
			s->maxdata	= 0xffffffff;
			s->insn_पढ़ो	= ni_tio_insn_पढ़ो;
			s->insn_ग_लिखो	= ni_tio_insn_ग_लिखो;
			s->insn_config	= ni_tio_insn_config;
			s->len_chanlist	= 1;
			s->करो_cmd	= ni_660x_cmd;
			s->करो_cmdtest	= ni_tio_cmdtest;
			s->cancel	= ni_660x_cancel;
			s->poll		= ni_660x_input_poll;
			s->buf_change	= ni_660x_buf_change;
			s->async_dma_dir = DMA_BIसूचीECTIONAL;
			s->निजी	= counter;

			ni_tio_init_counter(counter);
		पूर्ण अन्यथा अणु
			s->type		= COMEDI_SUBD_UNUSED;
		पूर्ण
	पूर्ण

	/*
	 * To be safe, set counterswap bits on tio chips after all the counter
	 * outमाला_दो have been set to high impedance mode.
	 */
	क्रम (i = 0; i < board->n_chips; ++i)
		set_tio_counterswap(dev, i);

	ret = request_irq(pcidev->irq, ni_660x_पूर्णांकerrupt, IRQF_SHARED,
			  dev->board_name, dev);
	अगर (ret < 0) अणु
		dev_warn(dev->class_dev, " irq not available\n");
		वापस ret;
	पूर्ण
	dev->irq = pcidev->irq;
	global_पूर्णांकerrupt_config_bits = NI660X_GLOBAL_INT_GLOBAL;
	अगर (board->n_chips > 1)
		global_पूर्णांकerrupt_config_bits |= NI660X_GLOBAL_INT_CASCADE;
	ni_660x_ग_लिखो(dev, 0, global_पूर्णांकerrupt_config_bits,
		      NI660X_GLOBAL_INT_CFG);

	वापस 0;
पूर्ण

अटल व्योम ni_660x_detach(काष्ठा comedi_device *dev)
अणु
	काष्ठा ni_660x_निजी *devpriv = dev->निजी;

	अगर (dev->irq) अणु
		ni_660x_ग_लिखो(dev, 0, 0, NI660X_GLOBAL_INT_CFG);
		मुक्त_irq(dev->irq, dev);
	पूर्ण
	अगर (devpriv) अणु
		ni_gpct_device_destroy(devpriv->counter_dev);
		ni_660x_मुक्त_mite_rings(dev);
		mite_detach(devpriv->mite);
	पूर्ण
	अगर (dev->mmio)
		iounmap(dev->mmio);
	comedi_pci_disable(dev);
पूर्ण

अटल काष्ठा comedi_driver ni_660x_driver = अणु
	.driver_name	= "ni_660x",
	.module		= THIS_MODULE,
	.स्वतः_attach	= ni_660x_स्वतः_attach,
	.detach		= ni_660x_detach,
पूर्ण;

अटल पूर्णांक ni_660x_pci_probe(काष्ठा pci_dev *dev,
			     स्थिर काष्ठा pci_device_id *id)
अणु
	वापस comedi_pci_स्वतः_config(dev, &ni_660x_driver, id->driver_data);
पूर्ण

अटल स्थिर काष्ठा pci_device_id ni_660x_pci_table[] = अणु
	अणु PCI_VDEVICE(NI, 0x1310), BOARD_PCI6602 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x1360), BOARD_PXI6602 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x2c60), BOARD_PCI6601 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x2db0), BOARD_PCI6608 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x2cc0), BOARD_PXI6608 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x1e30), BOARD_PCI6624 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x1e40), BOARD_PXI6624 पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, ni_660x_pci_table);

अटल काष्ठा pci_driver ni_660x_pci_driver = अणु
	.name		= "ni_660x",
	.id_table	= ni_660x_pci_table,
	.probe		= ni_660x_pci_probe,
	.हटाओ		= comedi_pci_स्वतः_unconfig,
पूर्ण;
module_comedi_pci_driver(ni_660x_driver, ni_660x_pci_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi driver for NI 660x counter/timer boards");
MODULE_LICENSE("GPL");
