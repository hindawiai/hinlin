<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Comedi driver क्रम National Instruments PCI-DIO-32HS
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 1999,2002 David A. Schleef <ds@schleef.org>
 */

/*
 * Driver: ni_pcidio
 * Description: National Instruments PCI-DIO32HS, PCI-6533
 * Author: ds
 * Status: works
 * Devices: [National Instruments] PCI-DIO-32HS (ni_pcidio)
 *   [National Instruments] PXI-6533, PCI-6533 (pxi-6533)
 *   [National Instruments] PCI-6534 (pci-6534)
 * Updated: Mon, 09 Jan 2012 14:27:23 +0000
 *
 * The DIO32HS board appears as one subdevice, with 32 channels. Each
 * channel is inभागidually I/O configurable. The channel order is 0=A0,
 * 1=A1, 2=A2, ... 8=B0, 16=C0, 24=D0. The driver only supports simple
 * digital I/O; no handshaking is supported.
 *
 * DMA mostly works क्रम the PCI-DIO32HS, but only in समयd input mode.
 *
 * The PCI-DIO-32HS/PCI-6533 has a configurable बाह्यal trigger. Setting
 * scan_begin_arg to 0 or CR_EDGE triggers on the leading edge. Setting
 * scan_begin_arg to CR_INVERT or (CR_EDGE | CR_INVERT) triggers on the
 * trailing edge.
 *
 * This driver could be easily modअगरied to support AT-MIO32HS and AT-MIO96.
 *
 * The PCI-6534 requires a firmware upload after घातer-up to work, the
 * firmware data and inकाष्ठाions क्रम loading it with comedi_config
 * it are contained in the comedi_nonमुक्त_firmware tarball available from
 * https://www.comedi.org
 */

#घोषणा USE_DMA

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sched.h>

#समावेश "../comedi_pci.h"

#समावेश "mite.h"

/* defines क्रम the PCI-DIO-32HS */

#घोषणा WINDOW_ADDRESS			4	/* W */
#घोषणा INTERRUPT_AND_WINDOW_STATUS	4	/* R */
#घोषणा INT_STATUS_1				BIT(0)
#घोषणा INT_STATUS_2				BIT(1)
#घोषणा WINDOW_ADDRESS_STATUS_MASK		0x7c

#घोषणा MASTER_DMA_AND_INTERRUPT_CONTROL 5	/* W */
#घोषणा INTERRUPT_LINE(x)			((x) & 3)
#घोषणा OPEN_INT				BIT(2)
#घोषणा GROUP_STATUS			5	/* R */
#घोषणा DATA_LEFT				BIT(0)
#घोषणा REQ					BIT(2)
#घोषणा STOP_TRIG				BIT(3)

#घोषणा GROUP_1_FLAGS			6	/* R */
#घोषणा GROUP_2_FLAGS			7	/* R */
#घोषणा TRANSFER_READY				BIT(0)
#घोषणा COUNT_EXPIRED				BIT(1)
#घोषणा WAITED					BIT(5)
#घोषणा PRIMARY_TC				BIT(6)
#घोषणा SECONDARY_TC				BIT(7)
  /* #घोषणा SerialRose */
  /* #घोषणा ReqRose */
  /* #घोषणा Paused */

#घोषणा GROUP_1_FIRST_CLEAR		6	/* W */
#घोषणा GROUP_2_FIRST_CLEAR		7	/* W */
#घोषणा CLEAR_WAITED				BIT(3)
#घोषणा CLEAR_PRIMARY_TC			BIT(4)
#घोषणा CLEAR_SECONDARY_TC			BIT(5)
#घोषणा DMA_RESET				BIT(6)
#घोषणा FIFO_RESET				BIT(7)
#घोषणा CLEAR_ALL				0xf8

#घोषणा GROUP_1_FIFO			8	/* W */
#घोषणा GROUP_2_FIFO			12	/* W */

#घोषणा TRANSFER_COUNT			20
#घोषणा CHIP_ID_D			24
#घोषणा CHIP_ID_I			25
#घोषणा CHIP_ID_O			26
#घोषणा CHIP_VERSION			27
#घोषणा PORT_IO(x)			(28 + (x))
#घोषणा PORT_PIN_सूचीECTIONS(x)		(32 + (x))
#घोषणा PORT_PIN_MASK(x)		(36 + (x))
#घोषणा PORT_PIN_POLARITIES(x)		(40 + (x))

#घोषणा MASTER_CLOCK_ROUTING		45
#घोषणा RTSI_CLOCKING(x)			(((x) & 3) << 4)

#घोषणा GROUP_1_SECOND_CLEAR		46	/* W */
#घोषणा GROUP_2_SECOND_CLEAR		47	/* W */
#घोषणा CLEAR_EXPIRED				BIT(0)

#घोषणा PORT_PATTERN(x)			(48 + (x))

#घोषणा DATA_PATH			64
#घोषणा FIFO_ENABLE_A		BIT(0)
#घोषणा FIFO_ENABLE_B		BIT(1)
#घोषणा FIFO_ENABLE_C		BIT(2)
#घोषणा FIFO_ENABLE_D		BIT(3)
#घोषणा FUNNELING(x)		(((x) & 3) << 4)
#घोषणा GROUP_सूचीECTION		BIT(7)

#घोषणा PROTOCOL_REGISTER_1		65
#घोषणा OP_MODE			PROTOCOL_REGISTER_1
#घोषणा RUN_MODE(x)		((x) & 7)
#घोषणा NUMBERED		BIT(3)

#घोषणा PROTOCOL_REGISTER_2		66
#घोषणा CLOCK_REG			PROTOCOL_REGISTER_2
#घोषणा CLOCK_LINE(x)		(((x) & 3) << 5)
#घोषणा INVERT_STOP_TRIG		BIT(7)
#घोषणा DATA_LATCHING(x)       (((x) & 3) << 5)

#घोषणा PROTOCOL_REGISTER_3		67
#घोषणा SEQUENCE			PROTOCOL_REGISTER_3

#घोषणा PROTOCOL_REGISTER_14		68	/* 16 bit */
#घोषणा CLOCK_SPEED			PROTOCOL_REGISTER_14

#घोषणा PROTOCOL_REGISTER_4		70
#घोषणा REQ_REG			PROTOCOL_REGISTER_4
#घोषणा REQ_CONDITIONING(x)	(((x) & 7) << 3)

#घोषणा PROTOCOL_REGISTER_5		71
#घोषणा BLOCK_MODE			PROTOCOL_REGISTER_5

#घोषणा FIFO_Control			72
#घोषणा READY_LEVEL(x)		((x) & 7)

#घोषणा PROTOCOL_REGISTER_6		73
#घोषणा LINE_POLARITIES		PROTOCOL_REGISTER_6
#घोषणा INVERT_ACK		BIT(0)
#घोषणा INVERT_REQ		BIT(1)
#घोषणा INVERT_CLOCK		BIT(2)
#घोषणा INVERT_SERIAL		BIT(3)
#घोषणा OPEN_ACK		BIT(4)
#घोषणा OPEN_CLOCK		BIT(5)

#घोषणा PROTOCOL_REGISTER_7		74
#घोषणा ACK_SER			PROTOCOL_REGISTER_7
#घोषणा ACK_LINE(x)		(((x) & 3) << 2)
#घोषणा EXCHANGE_PINS		BIT(7)

#घोषणा INTERRUPT_CONTROL		75
/* bits same as flags */

#घोषणा DMA_LINE_CONTROL_GROUP1		76
#घोषणा DMA_LINE_CONTROL_GROUP2		108

/* channel zero is none */
अटल अंतरभूत अचिन्हित पूर्णांक primary_DMAChannel_bits(अचिन्हित पूर्णांक channel)
अणु
	वापस channel & 0x3;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक secondary_DMAChannel_bits(अचिन्हित पूर्णांक channel)
अणु
	वापस (channel << 2) & 0xc;
पूर्ण

#घोषणा TRANSFER_SIZE_CONTROL		77
#घोषणा TRANSFER_WIDTH(x)	((x) & 3)
#घोषणा TRANSFER_LENGTH(x)	(((x) & 3) << 3)
#घोषणा REQUIRE_R_LEVEL        BIT(5)

#घोषणा PROTOCOL_REGISTER_15		79
#घोषणा DAQ_OPTIONS			PROTOCOL_REGISTER_15
#घोषणा START_SOURCE(x)			((x) & 0x3)
#घोषणा INVERT_START				BIT(2)
#घोषणा STOP_SOURCE(x)				(((x) & 0x3) << 3)
#घोषणा REQ_START				BIT(6)
#घोषणा PRE_START				BIT(7)

#घोषणा PATTERN_DETECTION		81
#घोषणा DETECTION_METHOD			BIT(0)
#घोषणा INVERT_MATCH				BIT(1)
#घोषणा IE_PATTERN_DETECTION			BIT(2)

#घोषणा PROTOCOL_REGISTER_9		82
#घोषणा REQ_DELAY			PROTOCOL_REGISTER_9

#घोषणा PROTOCOL_REGISTER_10		83
#घोषणा REQ_NOT_DELAY			PROTOCOL_REGISTER_10

#घोषणा PROTOCOL_REGISTER_11		84
#घोषणा ACK_DELAY			PROTOCOL_REGISTER_11

#घोषणा PROTOCOL_REGISTER_12		85
#घोषणा ACK_NOT_DELAY			PROTOCOL_REGISTER_12

#घोषणा PROTOCOL_REGISTER_13		86
#घोषणा DATA_1_DELAY			PROTOCOL_REGISTER_13

#घोषणा PROTOCOL_REGISTER_8		88	/* 32 bit */
#घोषणा START_DELAY			PROTOCOL_REGISTER_8

/* Firmware files क्रम PCI-6524 */
#घोषणा FW_PCI_6534_MAIN		"ni6534a.bin"
#घोषणा FW_PCI_6534_SCARAB_DI		"niscrb01.bin"
#घोषणा FW_PCI_6534_SCARAB_DO		"niscrb02.bin"
MODULE_FIRMWARE(FW_PCI_6534_MAIN);
MODULE_FIRMWARE(FW_PCI_6534_SCARAB_DI);
MODULE_FIRMWARE(FW_PCI_6534_SCARAB_DO);

क्रमागत pci_6534_firmware_रेजिस्टरs अणु	/* 16 bit */
	Firmware_Control_Register = 0x100,
	Firmware_Status_Register = 0x104,
	Firmware_Data_Register = 0x108,
	Firmware_Mask_Register = 0x10c,
	Firmware_Debug_Register = 0x110,
पूर्ण;

/* मुख्य fpga रेजिस्टरs (32 bit)*/
क्रमागत pci_6534_fpga_रेजिस्टरs अणु
	FPGA_Control1_Register = 0x200,
	FPGA_Control2_Register = 0x204,
	FPGA_Irq_Mask_Register = 0x208,
	FPGA_Status_Register = 0x20c,
	FPGA_Signature_Register = 0x210,
	FPGA_SCALS_Counter_Register = 0x280,	/*ग_लिखो-clear */
	FPGA_SCAMS_Counter_Register = 0x284,	/*ग_लिखो-clear */
	FPGA_SCBLS_Counter_Register = 0x288,	/*ग_लिखो-clear */
	FPGA_SCBMS_Counter_Register = 0x28c,	/*ग_लिखो-clear */
	FPGA_Temp_Control_Register = 0x2a0,
	FPGA_DAR_Register = 0x2a8,
	FPGA_ELC_Read_Register = 0x2b8,
	FPGA_ELC_Write_Register = 0x2bc,
पूर्ण;

क्रमागत FPGA_Control_Bits अणु
	FPGA_Enable_Bit = 0x8000,
पूर्ण;

#घोषणा TIMER_BASE 50		/* nanoseconds */

#अगर_घोषित USE_DMA
#घोषणा INT_EN (COUNT_EXPIRED | WAITED | PRIMARY_TC | SECONDARY_TC)
#अन्यथा
#घोषणा INT_EN (TRANSFER_READY | COUNT_EXPIRED | WAITED \
		| PRIMARY_TC | SECONDARY_TC)
#पूर्ण_अगर

क्रमागत nidio_boardid अणु
	BOARD_PCIDIO_32HS,
	BOARD_PXI6533,
	BOARD_PCI6534,
पूर्ण;

काष्ठा nidio_board अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक uses_firmware:1;
	अचिन्हित पूर्णांक dio_speed;
पूर्ण;

अटल स्थिर काष्ठा nidio_board nidio_boards[] = अणु
	[BOARD_PCIDIO_32HS] = अणु
		.name		= "pci-dio-32hs",
		.dio_speed	= 50,
	पूर्ण,
	[BOARD_PXI6533] = अणु
		.name		= "pxi-6533",
		.dio_speed	= 50,
	पूर्ण,
	[BOARD_PCI6534] = अणु
		.name		= "pci-6534",
		.uses_firmware	= 1,
		.dio_speed	= 50,
	पूर्ण,
पूर्ण;

काष्ठा nidio96_निजी अणु
	काष्ठा mite *mite;
	पूर्णांक boardtype;
	पूर्णांक dio;
	अचिन्हित लघु OP_MODEBits;
	काष्ठा mite_channel *di_mite_chan;
	काष्ठा mite_ring *di_mite_ring;
	spinlock_t mite_channel_lock;
पूर्ण;

अटल पूर्णांक ni_pcidio_request_di_mite_channel(काष्ठा comedi_device *dev)
अणु
	काष्ठा nidio96_निजी *devpriv = dev->निजी;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&devpriv->mite_channel_lock, flags);
	BUG_ON(devpriv->di_mite_chan);
	devpriv->di_mite_chan =
	    mite_request_channel_in_range(devpriv->mite,
					  devpriv->di_mite_ring, 1, 2);
	अगर (!devpriv->di_mite_chan) अणु
		spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);
		dev_err(dev->class_dev, "failed to reserve mite dma channel\n");
		वापस -EBUSY;
	पूर्ण
	devpriv->di_mite_chan->dir = COMEDI_INPUT;
	ग_लिखोb(primary_DMAChannel_bits(devpriv->di_mite_chan->channel) |
	       secondary_DMAChannel_bits(devpriv->di_mite_chan->channel),
	       dev->mmio + DMA_LINE_CONTROL_GROUP1);
	spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);
	वापस 0;
पूर्ण

अटल व्योम ni_pcidio_release_di_mite_channel(काष्ठा comedi_device *dev)
अणु
	काष्ठा nidio96_निजी *devpriv = dev->निजी;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&devpriv->mite_channel_lock, flags);
	अगर (devpriv->di_mite_chan) अणु
		mite_release_channel(devpriv->di_mite_chan);
		devpriv->di_mite_chan = शून्य;
		ग_लिखोb(primary_DMAChannel_bits(0) |
		       secondary_DMAChannel_bits(0),
		       dev->mmio + DMA_LINE_CONTROL_GROUP1);
	पूर्ण
	spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);
पूर्ण

अटल पूर्णांक setup_mite_dma(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	काष्ठा nidio96_निजी *devpriv = dev->निजी;
	पूर्णांक retval;
	अचिन्हित दीर्घ flags;

	retval = ni_pcidio_request_di_mite_channel(dev);
	अगर (retval)
		वापस retval;

	/* ग_लिखो alloc the entire buffer */
	comedi_buf_ग_लिखो_alloc(s, s->async->pपुनः_स्मृति_bufsz);

	spin_lock_irqsave(&devpriv->mite_channel_lock, flags);
	अगर (devpriv->di_mite_chan) अणु
		mite_prep_dma(devpriv->di_mite_chan, 32, 32);
		mite_dma_arm(devpriv->di_mite_chan);
	पूर्ण अन्यथा अणु
		retval = -EIO;
	पूर्ण
	spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);

	वापस retval;
पूर्ण

अटल पूर्णांक ni_pcidio_poll(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	काष्ठा nidio96_निजी *devpriv = dev->निजी;
	अचिन्हित दीर्घ irq_flags;
	पूर्णांक count;

	spin_lock_irqsave(&dev->spinlock, irq_flags);
	spin_lock(&devpriv->mite_channel_lock);
	अगर (devpriv->di_mite_chan)
		mite_sync_dma(devpriv->di_mite_chan, s);
	spin_unlock(&devpriv->mite_channel_lock);
	count = comedi_buf_n_bytes_पढ़ोy(s);
	spin_unlock_irqrestore(&dev->spinlock, irq_flags);
	वापस count;
पूर्ण

अटल irqवापस_t nidio_पूर्णांकerrupt(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा comedi_device *dev = d;
	काष्ठा nidio96_निजी *devpriv = dev->निजी;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	काष्ठा comedi_async *async = s->async;
	अचिन्हित पूर्णांक auxdata;
	पूर्णांक flags;
	पूर्णांक status;
	पूर्णांक work = 0;

	/* पूर्णांकerrupcions parasites */
	अगर (!dev->attached) अणु
		/* assume it's from another card */
		वापस IRQ_NONE;
	पूर्ण

	/* Lock to aव्योम race with comedi_poll */
	spin_lock(&dev->spinlock);

	status = पढ़ोb(dev->mmio + INTERRUPT_AND_WINDOW_STATUS);
	flags = पढ़ोb(dev->mmio + GROUP_1_FLAGS);

	spin_lock(&devpriv->mite_channel_lock);
	अगर (devpriv->di_mite_chan) अणु
		mite_ack_linkc(devpriv->di_mite_chan, s, false);
		/* XXX need to byteswap sync'ed dma */
	पूर्ण
	spin_unlock(&devpriv->mite_channel_lock);

	जबतक (status & DATA_LEFT) अणु
		work++;
		अगर (work > 20) अणु
			dev_dbg(dev->class_dev, "too much work in interrupt\n");
			ग_लिखोb(0x00,
			       dev->mmio + MASTER_DMA_AND_INTERRUPT_CONTROL);
			अवरोध;
		पूर्ण

		flags &= INT_EN;

		अगर (flags & TRANSFER_READY) अणु
			जबतक (flags & TRANSFER_READY) अणु
				work++;
				अगर (work > 100) अणु
					dev_dbg(dev->class_dev,
						"too much work in interrupt\n");
					ग_लिखोb(0x00, dev->mmio +
					       MASTER_DMA_AND_INTERRUPT_CONTROL
					      );
					जाओ out;
				पूर्ण
				auxdata = पढ़ोl(dev->mmio + GROUP_1_FIFO);
				comedi_buf_ग_लिखो_samples(s, &auxdata, 1);
				flags = पढ़ोb(dev->mmio + GROUP_1_FLAGS);
			पूर्ण
		पूर्ण

		अगर (flags & COUNT_EXPIRED) अणु
			ग_लिखोb(CLEAR_EXPIRED, dev->mmio + GROUP_1_SECOND_CLEAR);
			async->events |= COMEDI_CB_EOA;

			ग_लिखोb(0x00, dev->mmio + OP_MODE);
			अवरोध;
		पूर्ण अन्यथा अगर (flags & WAITED) अणु
			ग_लिखोb(CLEAR_WAITED, dev->mmio + GROUP_1_FIRST_CLEAR);
			async->events |= COMEDI_CB_ERROR;
			अवरोध;
		पूर्ण अन्यथा अगर (flags & PRIMARY_TC) अणु
			ग_लिखोb(CLEAR_PRIMARY_TC,
			       dev->mmio + GROUP_1_FIRST_CLEAR);
			async->events |= COMEDI_CB_EOA;
		पूर्ण अन्यथा अगर (flags & SECONDARY_TC) अणु
			ग_लिखोb(CLEAR_SECONDARY_TC,
			       dev->mmio + GROUP_1_FIRST_CLEAR);
			async->events |= COMEDI_CB_EOA;
		पूर्ण

		flags = पढ़ोb(dev->mmio + GROUP_1_FLAGS);
		status = पढ़ोb(dev->mmio + INTERRUPT_AND_WINDOW_STATUS);
	पूर्ण

out:
	comedi_handle_events(dev, s);
#अगर 0
	अगर (!tag)
		ग_लिखोb(0x03, dev->mmio + MASTER_DMA_AND_INTERRUPT_CONTROL);
#पूर्ण_अगर

	spin_unlock(&dev->spinlock);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ni_pcidio_insn_config(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	पूर्णांक ret;

	अगर (data[0] == INSN_CONFIG_GET_CMD_TIMING_CONSTRAINTS) अणु
		स्थिर काष्ठा nidio_board *board = dev->board_ptr;

		/* we करोn't care about actual channels */
		data[1] = board->dio_speed;
		data[2] = 0;
		वापस 0;
	पूर्ण

	ret = comedi_dio_insn_config(dev, s, insn, data, 0);
	अगर (ret)
		वापस ret;

	ग_लिखोl(s->io_bits, dev->mmio + PORT_PIN_सूचीECTIONS(0));

	वापस insn->n;
पूर्ण

अटल पूर्णांक ni_pcidio_insn_bits(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	अगर (comedi_dio_update_state(s, data))
		ग_लिखोl(s->state, dev->mmio + PORT_IO(0));

	data[1] = पढ़ोl(dev->mmio + PORT_IO(0));

	वापस insn->n;
पूर्ण

अटल पूर्णांक ni_pcidio_ns_to_समयr(पूर्णांक *nanosec, अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक भागider, base;

	base = TIMER_BASE;

	चयन (flags & CMDF_ROUND_MASK) अणु
	हाल CMDF_ROUND_NEAREST:
	शेष:
		भागider = DIV_ROUND_CLOSEST(*nanosec, base);
		अवरोध;
	हाल CMDF_ROUND_DOWN:
		भागider = (*nanosec) / base;
		अवरोध;
	हाल CMDF_ROUND_UP:
		भागider = DIV_ROUND_UP(*nanosec, base);
		अवरोध;
	पूर्ण

	*nanosec = base * भागider;
	वापस भागider;
पूर्ण

अटल पूर्णांक ni_pcidio_cmdtest(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s, काष्ठा comedi_cmd *cmd)
अणु
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक arg;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_NOW | TRIG_INT);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src,
					TRIG_TIMER | TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->convert_src, TRIG_NOW);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src, TRIG_COUNT | TRIG_NONE);

	अगर (err)
		वापस 1;

	/* Step 2a : make sure trigger sources are unique */

	err |= comedi_check_trigger_is_unique(cmd->start_src);
	err |= comedi_check_trigger_is_unique(cmd->scan_begin_src);
	err |= comedi_check_trigger_is_unique(cmd->stop_src);

	/* Step 2b : and mutually compatible */

	अगर (err)
		वापस 2;

	/* Step 3: check अगर arguments are trivially valid */

	err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);

#घोषणा MAX_SPEED	(TIMER_BASE)	/* in nanoseconds */

	अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
		err |= comedi_check_trigger_arg_min(&cmd->scan_begin_arg,
						    MAX_SPEED);
		/* no minimum speed */
	पूर्ण अन्यथा अणु
		/* TRIG_EXT */
		/* should be level/edge, hi/lo specअगरication here */
		अगर ((cmd->scan_begin_arg & ~(CR_EDGE | CR_INVERT)) != 0) अणु
			cmd->scan_begin_arg &= (CR_EDGE | CR_INVERT);
			err |= -EINVAL;
		पूर्ण
	पूर्ण

	err |= comedi_check_trigger_arg_is(&cmd->convert_arg, 0);
	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);

	अगर (cmd->stop_src == TRIG_COUNT)
		err |= comedi_check_trigger_arg_min(&cmd->stop_arg, 1);
	अन्यथा	/* TRIG_NONE */
		err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);

	अगर (err)
		वापस 3;

	/* step 4: fix up any arguments */

	अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
		arg = cmd->scan_begin_arg;
		ni_pcidio_ns_to_समयr(&arg, cmd->flags);
		err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, arg);
	पूर्ण

	अगर (err)
		वापस 4;

	वापस 0;
पूर्ण

अटल पूर्णांक ni_pcidio_पूर्णांकtrig(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s,
			     अचिन्हित पूर्णांक trig_num)
अणु
	काष्ठा nidio96_निजी *devpriv = dev->निजी;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;

	अगर (trig_num != cmd->start_arg)
		वापस -EINVAL;

	ग_लिखोb(devpriv->OP_MODEBits, dev->mmio + OP_MODE);
	s->async->पूर्णांकtrig = शून्य;

	वापस 1;
पूर्ण

अटल पूर्णांक ni_pcidio_cmd(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	काष्ठा nidio96_निजी *devpriv = dev->निजी;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;

	/* XXX configure ports क्रम input */
	ग_लिखोl(0x0000, dev->mmio + PORT_PIN_सूचीECTIONS(0));

	अगर (1) अणु
		/* enable fअगरos A B C D */
		ग_लिखोb(0x0f, dev->mmio + DATA_PATH);

		/* set transfer width a 32 bits */
		ग_लिखोb(TRANSFER_WIDTH(0) | TRANSFER_LENGTH(0),
		       dev->mmio + TRANSFER_SIZE_CONTROL);
	पूर्ण अन्यथा अणु
		ग_लिखोb(0x03, dev->mmio + DATA_PATH);
		ग_लिखोb(TRANSFER_WIDTH(3) | TRANSFER_LENGTH(0),
		       dev->mmio + TRANSFER_SIZE_CONTROL);
	पूर्ण

	/* protocol configuration */
	अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
		/* page 4-5, "input with internal REQs" */
		ग_लिखोb(0, dev->mmio + OP_MODE);
		ग_लिखोb(0x00, dev->mmio + CLOCK_REG);
		ग_लिखोb(1, dev->mmio + SEQUENCE);
		ग_लिखोb(0x04, dev->mmio + REQ_REG);
		ग_लिखोb(4, dev->mmio + BLOCK_MODE);
		ग_लिखोb(3, dev->mmio + LINE_POLARITIES);
		ग_लिखोb(0xc0, dev->mmio + ACK_SER);
		ग_लिखोl(ni_pcidio_ns_to_समयr(&cmd->scan_begin_arg,
					     CMDF_ROUND_NEAREST),
		       dev->mmio + START_DELAY);
		ग_लिखोb(1, dev->mmio + REQ_DELAY);
		ग_लिखोb(1, dev->mmio + REQ_NOT_DELAY);
		ग_लिखोb(1, dev->mmio + ACK_DELAY);
		ग_लिखोb(0x0b, dev->mmio + ACK_NOT_DELAY);
		ग_लिखोb(0x01, dev->mmio + DATA_1_DELAY);
		/*
		 * manual, page 4-5:
		 * CLOCK_SPEED comment is incorrectly listed on DAQ_OPTIONS
		 */
		ग_लिखोw(0, dev->mmio + CLOCK_SPEED);
		ग_लिखोb(0, dev->mmio + DAQ_OPTIONS);
	पूर्ण अन्यथा अणु
		/* TRIG_EXT */
		/* page 4-5, "input with external REQs" */
		ग_लिखोb(0, dev->mmio + OP_MODE);
		ग_लिखोb(0x00, dev->mmio + CLOCK_REG);
		ग_लिखोb(0, dev->mmio + SEQUENCE);
		ग_लिखोb(0x00, dev->mmio + REQ_REG);
		ग_लिखोb(4, dev->mmio + BLOCK_MODE);
		अगर (!(cmd->scan_begin_arg & CR_INVERT))	/* Leading Edge */
			ग_लिखोb(0, dev->mmio + LINE_POLARITIES);
		अन्यथा					/* Trailing Edge */
			ग_लिखोb(2, dev->mmio + LINE_POLARITIES);
		ग_लिखोb(0x00, dev->mmio + ACK_SER);
		ग_लिखोl(1, dev->mmio + START_DELAY);
		ग_लिखोb(1, dev->mmio + REQ_DELAY);
		ग_लिखोb(1, dev->mmio + REQ_NOT_DELAY);
		ग_लिखोb(1, dev->mmio + ACK_DELAY);
		ग_लिखोb(0x0C, dev->mmio + ACK_NOT_DELAY);
		ग_लिखोb(0x10, dev->mmio + DATA_1_DELAY);
		ग_लिखोw(0, dev->mmio + CLOCK_SPEED);
		ग_लिखोb(0x60, dev->mmio + DAQ_OPTIONS);
	पूर्ण

	अगर (cmd->stop_src == TRIG_COUNT) अणु
		ग_लिखोl(cmd->stop_arg,
		       dev->mmio + TRANSFER_COUNT);
	पूर्ण अन्यथा अणु
		/* XXX */
	पूर्ण

#अगर_घोषित USE_DMA
	ग_लिखोb(CLEAR_PRIMARY_TC | CLEAR_SECONDARY_TC,
	       dev->mmio + GROUP_1_FIRST_CLEAR);

	अणु
		पूर्णांक retval = setup_mite_dma(dev, s);

		अगर (retval)
			वापस retval;
	पूर्ण
#अन्यथा
	ग_लिखोb(0x00, dev->mmio + DMA_LINE_CONTROL_GROUP1);
#पूर्ण_अगर
	ग_लिखोb(0x00, dev->mmio + DMA_LINE_CONTROL_GROUP2);

	/* clear and enable पूर्णांकerrupts */
	ग_लिखोb(0xff, dev->mmio + GROUP_1_FIRST_CLEAR);
	/* ग_लिखोb(CLEAR_EXPIRED, dev->mmio+GROUP_1_SECOND_CLEAR); */

	ग_लिखोb(INT_EN, dev->mmio + INTERRUPT_CONTROL);
	ग_लिखोb(0x03, dev->mmio + MASTER_DMA_AND_INTERRUPT_CONTROL);

	अगर (cmd->stop_src == TRIG_NONE) अणु
		devpriv->OP_MODEBits = DATA_LATCHING(0) | RUN_MODE(7);
	पूर्ण अन्यथा अणु		/* TRIG_TIMER */
		devpriv->OP_MODEBits = NUMBERED | RUN_MODE(7);
	पूर्ण
	अगर (cmd->start_src == TRIG_NOW) अणु
		/* start */
		ग_लिखोb(devpriv->OP_MODEBits, dev->mmio + OP_MODE);
		s->async->पूर्णांकtrig = शून्य;
	पूर्ण अन्यथा अणु
		/* TRIG_INT */
		s->async->पूर्णांकtrig = ni_pcidio_पूर्णांकtrig;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ni_pcidio_cancel(काष्ठा comedi_device *dev,
			    काष्ठा comedi_subdevice *s)
अणु
	ग_लिखोb(0x00, dev->mmio + MASTER_DMA_AND_INTERRUPT_CONTROL);
	ni_pcidio_release_di_mite_channel(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक ni_pcidio_change(काष्ठा comedi_device *dev,
			    काष्ठा comedi_subdevice *s)
अणु
	काष्ठा nidio96_निजी *devpriv = dev->निजी;
	पूर्णांक ret;

	ret = mite_buf_change(devpriv->di_mite_ring, s);
	अगर (ret < 0)
		वापस ret;

	स_रखो(s->async->pपुनः_स्मृति_buf, 0xaa, s->async->pपुनः_स्मृति_bufsz);

	वापस 0;
पूर्ण

अटल पूर्णांक pci_6534_load_fpga(काष्ठा comedi_device *dev,
			      स्थिर u8 *data, माप_प्रकार data_len,
			      अचिन्हित दीर्घ context)
अणु
	अटल स्थिर पूर्णांक समयout = 1000;
	पूर्णांक fpga_index = context;
	पूर्णांक i;
	माप_प्रकार j;

	ग_लिखोw(0x80 | fpga_index, dev->mmio + Firmware_Control_Register);
	ग_लिखोw(0xc0 | fpga_index, dev->mmio + Firmware_Control_Register);
	क्रम (i = 0;
	     (पढ़ोw(dev->mmio + Firmware_Status_Register) & 0x2) == 0 &&
	     i < समयout; ++i) अणु
		udelay(1);
	पूर्ण
	अगर (i == समयout) अणु
		dev_warn(dev->class_dev,
			 "ni_pcidio: failed to load fpga %i, waiting for status 0x2\n",
			 fpga_index);
		वापस -EIO;
	पूर्ण
	ग_लिखोw(0x80 | fpga_index, dev->mmio + Firmware_Control_Register);
	क्रम (i = 0;
	     पढ़ोw(dev->mmio + Firmware_Status_Register) != 0x3 &&
	     i < समयout; ++i) अणु
		udelay(1);
	पूर्ण
	अगर (i == समयout) अणु
		dev_warn(dev->class_dev,
			 "ni_pcidio: failed to load fpga %i, waiting for status 0x3\n",
			 fpga_index);
		वापस -EIO;
	पूर्ण
	क्रम (j = 0; j + 1 < data_len;) अणु
		अचिन्हित पूर्णांक value = data[j++];

		value |= data[j++] << 8;
		ग_लिखोw(value, dev->mmio + Firmware_Data_Register);
		क्रम (i = 0;
		     (पढ़ोw(dev->mmio + Firmware_Status_Register) & 0x2) == 0
		     && i < समयout; ++i) अणु
			udelay(1);
		पूर्ण
		अगर (i == समयout) अणु
			dev_warn(dev->class_dev,
				 "ni_pcidio: failed to load word into fpga %i\n",
				 fpga_index);
			वापस -EIO;
		पूर्ण
		अगर (need_resched())
			schedule();
	पूर्ण
	ग_लिखोw(0x0, dev->mmio + Firmware_Control_Register);
	वापस 0;
पूर्ण

अटल पूर्णांक pci_6534_reset_fpga(काष्ठा comedi_device *dev, पूर्णांक fpga_index)
अणु
	वापस pci_6534_load_fpga(dev, शून्य, 0, fpga_index);
पूर्ण

अटल पूर्णांक pci_6534_reset_fpgas(काष्ठा comedi_device *dev)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	ग_लिखोw(0x0, dev->mmio + Firmware_Control_Register);
	क्रम (i = 0; i < 3; ++i) अणु
		ret = pci_6534_reset_fpga(dev, i);
		अगर (ret < 0)
			अवरोध;
	पूर्ण
	ग_लिखोw(0x0, dev->mmio + Firmware_Mask_Register);
	वापस ret;
पूर्ण

अटल व्योम pci_6534_init_मुख्य_fpga(काष्ठा comedi_device *dev)
अणु
	ग_लिखोl(0, dev->mmio + FPGA_Control1_Register);
	ग_लिखोl(0, dev->mmio + FPGA_Control2_Register);
	ग_लिखोl(0, dev->mmio + FPGA_SCALS_Counter_Register);
	ग_लिखोl(0, dev->mmio + FPGA_SCAMS_Counter_Register);
	ग_लिखोl(0, dev->mmio + FPGA_SCBLS_Counter_Register);
	ग_लिखोl(0, dev->mmio + FPGA_SCBMS_Counter_Register);
पूर्ण

अटल पूर्णांक pci_6534_upload_firmware(काष्ठा comedi_device *dev)
अणु
	काष्ठा nidio96_निजी *devpriv = dev->निजी;
	अटल स्थिर अक्षर *स्थिर fw_file[3] = अणु
		FW_PCI_6534_SCARAB_DI,	/* loaded पूर्णांकo scarab A क्रम DI */
		FW_PCI_6534_SCARAB_DO,	/* loaded पूर्णांकo scarab B क्रम DO */
		FW_PCI_6534_MAIN,	/* loaded पूर्णांकo मुख्य FPGA */
	पूर्ण;
	पूर्णांक ret;
	पूर्णांक n;

	ret = pci_6534_reset_fpgas(dev);
	अगर (ret < 0)
		वापस ret;
	/* load मुख्य FPGA first, then the two scarअसल */
	क्रम (n = 2; n >= 0; n--) अणु
		ret = comedi_load_firmware(dev, &devpriv->mite->pcidev->dev,
					   fw_file[n],
					   pci_6534_load_fpga, n);
		अगर (ret == 0 && n == 2)
			pci_6534_init_मुख्य_fpga(dev);
		अगर (ret < 0)
			अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम nidio_reset_board(काष्ठा comedi_device *dev)
अणु
	ग_लिखोl(0, dev->mmio + PORT_IO(0));
	ग_लिखोl(0, dev->mmio + PORT_PIN_सूचीECTIONS(0));
	ग_लिखोl(0, dev->mmio + PORT_PIN_MASK(0));

	/* disable पूर्णांकerrupts on board */
	ग_लिखोb(0, dev->mmio + MASTER_DMA_AND_INTERRUPT_CONTROL);
पूर्ण

अटल पूर्णांक nidio_स्वतः_attach(काष्ठा comedi_device *dev,
			     अचिन्हित दीर्घ context)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	स्थिर काष्ठा nidio_board *board = शून्य;
	काष्ठा nidio96_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;
	अचिन्हित पूर्णांक irq;

	अगर (context < ARRAY_SIZE(nidio_boards))
		board = &nidio_boards[context];
	अगर (!board)
		वापस -ENODEV;
	dev->board_ptr = board;
	dev->board_name = board->name;

	ret = comedi_pci_enable(dev);
	अगर (ret)
		वापस ret;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	spin_lock_init(&devpriv->mite_channel_lock);

	devpriv->mite = mite_attach(dev, false);	/* use win0 */
	अगर (!devpriv->mite)
		वापस -ENOMEM;

	devpriv->di_mite_ring = mite_alloc_ring(devpriv->mite);
	अगर (!devpriv->di_mite_ring)
		वापस -ENOMEM;

	अगर (board->uses_firmware) अणु
		ret = pci_6534_upload_firmware(dev);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	nidio_reset_board(dev);

	ret = comedi_alloc_subdevices(dev, 1);
	अगर (ret)
		वापस ret;

	dev_info(dev->class_dev, "%s rev=%d\n", dev->board_name,
		 पढ़ोb(dev->mmio + CHIP_VERSION));

	s = &dev->subdevices[0];

	dev->पढ़ो_subdev = s;
	s->type = COMEDI_SUBD_DIO;
	s->subdev_flags =
		SDF_READABLE | SDF_WRITABLE | SDF_LSAMPL | SDF_PACKED |
		SDF_CMD_READ;
	s->n_chan = 32;
	s->range_table = &range_digital;
	s->maxdata = 1;
	s->insn_config = &ni_pcidio_insn_config;
	s->insn_bits = &ni_pcidio_insn_bits;
	s->करो_cmd = &ni_pcidio_cmd;
	s->करो_cmdtest = &ni_pcidio_cmdtest;
	s->cancel = &ni_pcidio_cancel;
	s->len_chanlist = 32;	/* XXX */
	s->buf_change = &ni_pcidio_change;
	s->async_dma_dir = DMA_BIसूचीECTIONAL;
	s->poll = &ni_pcidio_poll;

	irq = pcidev->irq;
	अगर (irq) अणु
		ret = request_irq(irq, nidio_पूर्णांकerrupt, IRQF_SHARED,
				  dev->board_name, dev);
		अगर (ret == 0)
			dev->irq = irq;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम nidio_detach(काष्ठा comedi_device *dev)
अणु
	काष्ठा nidio96_निजी *devpriv = dev->निजी;

	अगर (dev->irq)
		मुक्त_irq(dev->irq, dev);
	अगर (devpriv) अणु
		अगर (devpriv->di_mite_ring) अणु
			mite_मुक्त_ring(devpriv->di_mite_ring);
			devpriv->di_mite_ring = शून्य;
		पूर्ण
		mite_detach(devpriv->mite);
	पूर्ण
	अगर (dev->mmio)
		iounmap(dev->mmio);
	comedi_pci_disable(dev);
पूर्ण

अटल काष्ठा comedi_driver ni_pcidio_driver = अणु
	.driver_name	= "ni_pcidio",
	.module		= THIS_MODULE,
	.स्वतः_attach	= nidio_स्वतः_attach,
	.detach		= nidio_detach,
पूर्ण;

अटल पूर्णांक ni_pcidio_pci_probe(काष्ठा pci_dev *dev,
			       स्थिर काष्ठा pci_device_id *id)
अणु
	वापस comedi_pci_स्वतः_config(dev, &ni_pcidio_driver, id->driver_data);
पूर्ण

अटल स्थिर काष्ठा pci_device_id ni_pcidio_pci_table[] = अणु
	अणु PCI_VDEVICE(NI, 0x1150), BOARD_PCIDIO_32HS पूर्ण,
	अणु PCI_VDEVICE(NI, 0x12b0), BOARD_PCI6534 पूर्ण,
	अणु PCI_VDEVICE(NI, 0x1320), BOARD_PXI6533 पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, ni_pcidio_pci_table);

अटल काष्ठा pci_driver ni_pcidio_pci_driver = अणु
	.name		= "ni_pcidio",
	.id_table	= ni_pcidio_pci_table,
	.probe		= ni_pcidio_pci_probe,
	.हटाओ		= comedi_pci_स्वतः_unconfig,
पूर्ण;
module_comedi_pci_driver(ni_pcidio_driver, ni_pcidio_pci_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi low-level driver");
MODULE_LICENSE("GPL");
