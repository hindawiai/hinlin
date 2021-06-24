<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ngene.c: nGene PCIe bridge driver
 *
 * Copyright (C) 2005-2007 Micronas
 *
 * Copyright (C) 2008-2009 Ralph Metzler <rjkm@metzlerbros.de>
 *                         Modअगरications क्रम new nGene firmware,
 *                         support क्रम EEPROM-copying,
 *                         support क्रम new dual DVB-S2 card prototype
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/poll.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/भाग64.h>
#समावेश <linux/pci.h>
#समावेश <linux/समयr.h>
#समावेश <linux/byteorder/generic.h>
#समावेश <linux/firmware.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश "ngene.h"

अटल पूर्णांक one_adapter;
module_param(one_adapter, पूर्णांक, 0444);
MODULE_PARM_DESC(one_adapter, "Use only one adapter.");

अटल पूर्णांक shutकरोwn_workaround;
module_param(shutकरोwn_workaround, पूर्णांक, 0644);
MODULE_PARM_DESC(shutकरोwn_workaround, "Activate workaround for shutdown problem with some chipsets.");

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0444);
MODULE_PARM_DESC(debug, "Print debugging information.");

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

#घोषणा ngग_लिखोb(dat, adr)         ग_लिखोb((dat), dev->iomem + (adr))
#घोषणा ngग_लिखोl(dat, adr)         ग_लिखोl((dat), dev->iomem + (adr))
#घोषणा ngग_लिखोb(dat, adr)         ग_लिखोb((dat), dev->iomem + (adr))
#घोषणा ngपढ़ोl(adr)               पढ़ोl(dev->iomem + (adr))
#घोषणा ngपढ़ोb(adr)               पढ़ोb(dev->iomem + (adr))
#घोषणा ngcpyto(adr, src, count)   स_नकल_toio(dev->iomem + (adr), (src), (count))
#घोषणा ngcpyfrom(dst, adr, count) स_नकल_fromio((dst), dev->iomem + (adr), (count))

/****************************************************************************/
/* nGene पूर्णांकerrupt handler **************************************************/
/****************************************************************************/

अटल व्योम event_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा ngene *dev = from_tasklet(dev, t, event_tasklet);

	जबतक (dev->EventQueueReadIndex != dev->EventQueueWriteIndex) अणु
		काष्ठा EVENT_BUFFER Event =
			dev->EventQueue[dev->EventQueueReadIndex];
		dev->EventQueueReadIndex =
			(dev->EventQueueReadIndex + 1) & (EVENT_QUEUE_SIZE - 1);

		अगर ((Event.UARTStatus & 0x01) && (dev->TxEventNotअगरy))
			dev->TxEventNotअगरy(dev, Event.TimeStamp);
		अगर ((Event.UARTStatus & 0x02) && (dev->RxEventNotअगरy))
			dev->RxEventNotअगरy(dev, Event.TimeStamp,
					   Event.RXCharacter);
	पूर्ण
पूर्ण

अटल व्योम demux_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा ngene_channel *chan = from_tasklet(chan, t, demux_tasklet);
	काष्ठा device *pdev = &chan->dev->pci_dev->dev;
	काष्ठा SBufferHeader *Cur = chan->nextBuffer;

	spin_lock_irq(&chan->state_lock);

	जबतक (Cur->ngeneBuffer.SR.Flags & 0x80) अणु
		अगर (chan->mode & NGENE_IO_TSOUT) अणु
			u32 Flags = chan->DataFormatFlags;
			अगर (Cur->ngeneBuffer.SR.Flags & 0x20)
				Flags |= BEF_OVERFLOW;
			अगर (chan->pBufferExchange) अणु
				अगर (!chan->pBufferExchange(chan,
							   Cur->Buffer1,
							   chan->Capture1Length,
							   Cur->ngeneBuffer.SR.
							   Clock, Flags)) अणु
					/*
					   We didn't get data
					   Clear in service flag to make sure we
					   get called on next पूर्णांकerrupt again.
					   leave fill/empty (0x80) flag alone
					   to aव्योम hardware running out of
					   buffers during startup, we hold only
					   in run state ( the source may be late
					   delivering data )
					*/

					अगर (chan->HWState == HWSTATE_RUN) अणु
						Cur->ngeneBuffer.SR.Flags &=
							~0x40;
						अवरोध;
						/* Stop processing stream */
					पूर्ण
				पूर्ण अन्यथा अणु
					/* We got a valid buffer,
					   so चयन to run state */
					chan->HWState = HWSTATE_RUN;
				पूर्ण
			पूर्ण अन्यथा अणु
				dev_err(pdev, "OOPS\n");
				अगर (chan->HWState == HWSTATE_RUN) अणु
					Cur->ngeneBuffer.SR.Flags &= ~0x40;
					अवरोध;	/* Stop processing stream */
				पूर्ण
			पूर्ण
			अगर (chan->AudioDTOUpdated) अणु
				dev_info(pdev, "Update AudioDTO = %d\n",
					 chan->AudioDTOValue);
				Cur->ngeneBuffer.SR.DTOUpdate =
					chan->AudioDTOValue;
				chan->AudioDTOUpdated = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (chan->HWState == HWSTATE_RUN) अणु
				u32 Flags = chan->DataFormatFlags;
				IBufferExchange *exch1 = chan->pBufferExchange;
				IBufferExchange *exch2 = chan->pBufferExchange2;
				अगर (Cur->ngeneBuffer.SR.Flags & 0x01)
					Flags |= BEF_EVEN_FIELD;
				अगर (Cur->ngeneBuffer.SR.Flags & 0x20)
					Flags |= BEF_OVERFLOW;
				spin_unlock_irq(&chan->state_lock);
				अगर (exch1)
					exch1(chan, Cur->Buffer1,
						chan->Capture1Length,
						Cur->ngeneBuffer.SR.Clock,
						Flags);
				अगर (exch2)
					exch2(chan, Cur->Buffer2,
						chan->Capture2Length,
						Cur->ngeneBuffer.SR.Clock,
						Flags);
				spin_lock_irq(&chan->state_lock);
			पूर्ण अन्यथा अगर (chan->HWState != HWSTATE_STOP)
				chan->HWState = HWSTATE_RUN;
		पूर्ण
		Cur->ngeneBuffer.SR.Flags = 0x00;
		Cur = Cur->Next;
	पूर्ण
	chan->nextBuffer = Cur;

	spin_unlock_irq(&chan->state_lock);
पूर्ण

अटल irqवापस_t irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ngene *dev = (काष्ठा ngene *)dev_id;
	काष्ठा device *pdev = &dev->pci_dev->dev;
	u32 icounts = 0;
	irqवापस_t rc = IRQ_NONE;
	u32 i = MAX_STREAM;
	u8 *पंचांगpCmdDoneByte;

	अगर (dev->BootFirmware) अणु
		icounts = ngपढ़ोl(NGENE_INT_COUNTS);
		अगर (icounts != dev->icounts) अणु
			ngग_लिखोl(0, FORCE_NMI);
			dev->cmd_करोne = 1;
			wake_up(&dev->cmd_wq);
			dev->icounts = icounts;
			rc = IRQ_HANDLED;
		पूर्ण
		वापस rc;
	पूर्ण

	ngग_लिखोl(0, FORCE_NMI);

	spin_lock(&dev->cmd_lock);
	पंचांगpCmdDoneByte = dev->CmdDoneByte;
	अगर (पंचांगpCmdDoneByte &&
	    (*पंचांगpCmdDoneByte ||
	    (dev->ngenetohost[0] == 1 && dev->ngenetohost[1] != 0))) अणु
		dev->CmdDoneByte = शून्य;
		dev->cmd_करोne = 1;
		wake_up(&dev->cmd_wq);
		rc = IRQ_HANDLED;
	पूर्ण
	spin_unlock(&dev->cmd_lock);

	अगर (dev->EventBuffer->EventStatus & 0x80) अणु
		u8 nextWriteIndex =
			(dev->EventQueueWriteIndex + 1) &
			(EVENT_QUEUE_SIZE - 1);
		अगर (nextWriteIndex != dev->EventQueueReadIndex) अणु
			dev->EventQueue[dev->EventQueueWriteIndex] =
				*(dev->EventBuffer);
			dev->EventQueueWriteIndex = nextWriteIndex;
		पूर्ण अन्यथा अणु
			dev_err(pdev, "event overflow\n");
			dev->EventQueueOverflowCount += 1;
			dev->EventQueueOverflowFlag = 1;
		पूर्ण
		dev->EventBuffer->EventStatus &= ~0x80;
		tasklet_schedule(&dev->event_tasklet);
		rc = IRQ_HANDLED;
	पूर्ण

	जबतक (i > 0) अणु
		i--;
		spin_lock(&dev->channel[i].state_lock);
		/* अगर (dev->channel[i].State>=KSSTATE_RUN) अणु */
		अगर (dev->channel[i].nextBuffer) अणु
			अगर ((dev->channel[i].nextBuffer->
			     ngeneBuffer.SR.Flags & 0xC0) == 0x80) अणु
				dev->channel[i].nextBuffer->
					ngeneBuffer.SR.Flags |= 0x40;
				tasklet_schedule(
					&dev->channel[i].demux_tasklet);
				rc = IRQ_HANDLED;
			पूर्ण
		पूर्ण
		spin_unlock(&dev->channel[i].state_lock);
	पूर्ण

	/* Request might have been processed by a previous call. */
	वापस IRQ_HANDLED;
पूर्ण

/****************************************************************************/
/* nGene command पूर्णांकerface **************************************************/
/****************************************************************************/

अटल व्योम dump_command_io(काष्ठा ngene *dev)
अणु
	काष्ठा device *pdev = &dev->pci_dev->dev;
	u8 buf[8], *b;

	ngcpyfrom(buf, HOST_TO_NGENE, 8);
	dev_err(pdev, "host_to_ngene (%04x): %*ph\n", HOST_TO_NGENE, 8, buf);

	ngcpyfrom(buf, NGENE_TO_HOST, 8);
	dev_err(pdev, "ngene_to_host (%04x): %*ph\n", NGENE_TO_HOST, 8, buf);

	b = dev->hosttongene;
	dev_err(pdev, "dev->hosttongene (%p): %*ph\n", b, 8, b);

	b = dev->ngenetohost;
	dev_err(pdev, "dev->ngenetohost (%p): %*ph\n", b, 8, b);
पूर्ण

अटल पूर्णांक ngene_command_mutex(काष्ठा ngene *dev, काष्ठा ngene_command *com)
अणु
	काष्ठा device *pdev = &dev->pci_dev->dev;
	पूर्णांक ret;
	u8 *पंचांगpCmdDoneByte;

	dev->cmd_करोne = 0;

	अगर (com->cmd.hdr.Opcode == CMD_FWLOAD_PREPARE) अणु
		dev->BootFirmware = 1;
		dev->icounts = ngपढ़ोl(NGENE_INT_COUNTS);
		ngग_लिखोl(0, NGENE_COMMAND);
		ngग_लिखोl(0, NGENE_COMMAND_HI);
		ngग_लिखोl(0, NGENE_STATUS);
		ngग_लिखोl(0, NGENE_STATUS_HI);
		ngग_लिखोl(0, NGENE_EVENT);
		ngग_लिखोl(0, NGENE_EVENT_HI);
	पूर्ण अन्यथा अगर (com->cmd.hdr.Opcode == CMD_FWLOAD_FINISH) अणु
		u64 fwio = dev->PAFWInterfaceBuffer;

		ngग_लिखोl(fwio & 0xffffffff, NGENE_COMMAND);
		ngग_लिखोl(fwio >> 32, NGENE_COMMAND_HI);
		ngग_लिखोl((fwio + 256) & 0xffffffff, NGENE_STATUS);
		ngग_लिखोl((fwio + 256) >> 32, NGENE_STATUS_HI);
		ngग_लिखोl((fwio + 512) & 0xffffffff, NGENE_EVENT);
		ngग_लिखोl((fwio + 512) >> 32, NGENE_EVENT_HI);
	पूर्ण

	स_नकल(dev->FWInterfaceBuffer, com->cmd.raw8, com->in_len + 2);

	अगर (dev->BootFirmware)
		ngcpyto(HOST_TO_NGENE, com->cmd.raw8, com->in_len + 2);

	spin_lock_irq(&dev->cmd_lock);
	पंचांगpCmdDoneByte = dev->ngenetohost + com->out_len;
	अगर (!com->out_len)
		पंचांगpCmdDoneByte++;
	*पंचांगpCmdDoneByte = 0;
	dev->ngenetohost[0] = 0;
	dev->ngenetohost[1] = 0;
	dev->CmdDoneByte = पंचांगpCmdDoneByte;
	spin_unlock_irq(&dev->cmd_lock);

	/* Notअगरy 8051. */
	ngग_लिखोl(1, FORCE_INT);

	ret = रुको_event_समयout(dev->cmd_wq, dev->cmd_करोne == 1, 2 * HZ);
	अगर (!ret) अणु
		/*ngग_लिखोl(0, FORCE_NMI);*/

		dev_err(pdev, "Command timeout cmd=%02x prev=%02x\n",
			com->cmd.hdr.Opcode, dev->prev_cmd);
		dump_command_io(dev);
		वापस -1;
	पूर्ण
	अगर (com->cmd.hdr.Opcode == CMD_FWLOAD_FINISH)
		dev->BootFirmware = 0;

	dev->prev_cmd = com->cmd.hdr.Opcode;

	अगर (!com->out_len)
		वापस 0;

	स_नकल(com->cmd.raw8, dev->ngenetohost, com->out_len);

	वापस 0;
पूर्ण

पूर्णांक ngene_command(काष्ठा ngene *dev, काष्ठा ngene_command *com)
अणु
	पूर्णांक result;

	mutex_lock(&dev->cmd_mutex);
	result = ngene_command_mutex(dev, com);
	mutex_unlock(&dev->cmd_mutex);
	वापस result;
पूर्ण


अटल पूर्णांक ngene_command_load_firmware(काष्ठा ngene *dev,
				       u8 *ngene_fw, u32 size)
अणु
#घोषणा FIRSTCHUNK (1024)
	u32 cleft;
	काष्ठा ngene_command com;

	com.cmd.hdr.Opcode = CMD_FWLOAD_PREPARE;
	com.cmd.hdr.Length = 0;
	com.in_len = 0;
	com.out_len = 0;

	ngene_command(dev, &com);

	cleft = (size + 3) & ~3;
	अगर (cleft > FIRSTCHUNK) अणु
		ngcpyto(PROGRAM_SRAM + FIRSTCHUNK, ngene_fw + FIRSTCHUNK,
			cleft - FIRSTCHUNK);
		cleft = FIRSTCHUNK;
	पूर्ण
	ngcpyto(DATA_FIFO_AREA, ngene_fw, cleft);

	स_रखो(&com, 0, माप(काष्ठा ngene_command));
	com.cmd.hdr.Opcode = CMD_FWLOAD_FINISH;
	com.cmd.hdr.Length = 4;
	com.cmd.FWLoadFinish.Address = DATA_FIFO_AREA;
	com.cmd.FWLoadFinish.Length = (अचिन्हित लघु)cleft;
	com.in_len = 4;
	com.out_len = 0;

	वापस ngene_command(dev, &com);
पूर्ण


अटल पूर्णांक ngene_command_config_buf(काष्ठा ngene *dev, u8 config)
अणु
	काष्ठा ngene_command com;

	com.cmd.hdr.Opcode = CMD_CONFIGURE_BUFFER;
	com.cmd.hdr.Length = 1;
	com.cmd.ConfigureBuffers.config = config;
	com.in_len = 1;
	com.out_len = 0;

	अगर (ngene_command(dev, &com) < 0)
		वापस -EIO;
	वापस 0;
पूर्ण

अटल पूर्णांक ngene_command_config_मुक्त_buf(काष्ठा ngene *dev, u8 *config)
अणु
	काष्ठा ngene_command com;

	com.cmd.hdr.Opcode = CMD_CONFIGURE_FREE_BUFFER;
	com.cmd.hdr.Length = 6;
	स_नकल(&com.cmd.ConfigureBuffers.config, config, 6);
	com.in_len = 6;
	com.out_len = 0;

	अगर (ngene_command(dev, &com) < 0)
		वापस -EIO;

	वापस 0;
पूर्ण

पूर्णांक ngene_command_gpio_set(काष्ठा ngene *dev, u8 select, u8 level)
अणु
	काष्ठा ngene_command com;

	com.cmd.hdr.Opcode = CMD_SET_GPIO_PIN;
	com.cmd.hdr.Length = 1;
	com.cmd.SetGpioPin.select = select | (level << 7);
	com.in_len = 1;
	com.out_len = 0;

	वापस ngene_command(dev, &com);
पूर्ण


/*
 02000640 is sample on rising edge.
 02000740 is sample on falling edge.
 02000040 is ignore "valid" संकेत

 0: FD_CTL1 Bit 7,6 must be 0,1
    7   disable(fw controlled)
    6   0-AUX,1-TS
    5   0-par,1-ser
    4   0-lsb/1-msb
    3,2 reserved
    1,0 0-no sync, 1-use ext. start, 2-use 0x47, 3-both
 1: FD_CTL2 has 3-valid must be hi, 2-use valid, 1-edge
 2: FD_STA is पढ़ो-only. 0-sync
 3: FD_INSYNC is number of 47s to trigger "in sync".
 4: FD_OUTSYNC is number of 47s to trigger "out of sync".
 5: FD_MAXBYTE1 is low-order of bytes per packet.
 6: FD_MAXBYTE2 is high-order of bytes per packet.
 7: Top byte is unused.
*/

/****************************************************************************/

अटल u8 TSFeatureDecoderSetup[8 * 5] = अणु
	0x42, 0x00, 0x00, 0x02, 0x02, 0xbc, 0x00, 0x00,
	0x40, 0x06, 0x00, 0x02, 0x02, 0xbc, 0x00, 0x00,	/* DRXH */
	0x71, 0x07, 0x00, 0x02, 0x02, 0xbc, 0x00, 0x00,	/* DRXHser */
	0x72, 0x00, 0x00, 0x02, 0x02, 0xbc, 0x00, 0x00,	/* S2ser */
	0x40, 0x07, 0x00, 0x02, 0x02, 0xbc, 0x00, 0x00, /* LGDT3303 */
पूर्ण;

/* Set NGENE I2S Config to 16 bit packed */
अटल u8 I2SConfiguration[] = अणु
	0x00, 0x10, 0x00, 0x00,
	0x80, 0x10, 0x00, 0x00,
पूर्ण;

अटल u8 SPDIFConfiguration[10] = अणु
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
पूर्ण;

/* Set NGENE I2S Config to transport stream compatible mode */

अटल u8 TS_I2SConfiguration[4] = अणु 0x3E, 0x18, 0x00, 0x00 पूर्ण;

अटल u8 TS_I2SOutConfiguration[4] = अणु 0x80, 0x04, 0x00, 0x00 पूर्ण;

अटल u8 ITUDecoderSetup[4][16] = अणु
	अणु0x1c, 0x13, 0x01, 0x68, 0x3d, 0x90, 0x14, 0x20,  /* SDTV */
	 0x00, 0x00, 0x01, 0xb0, 0x9c, 0x00, 0x00, 0x00पूर्ण,
	अणु0x9c, 0x03, 0x23, 0xC0, 0x60, 0x0E, 0x13, 0x00,
	 0x00, 0x00, 0x00, 0x01, 0xB0, 0x00, 0x00, 0x00पूर्ण,
	अणु0x9f, 0x00, 0x23, 0xC0, 0x60, 0x0F, 0x13, 0x00,  /* HDTV 1080i50 */
	 0x00, 0x00, 0x00, 0x01, 0xB0, 0x00, 0x00, 0x00पूर्ण,
	अणु0x9c, 0x01, 0x23, 0xC0, 0x60, 0x0E, 0x13, 0x00,  /* HDTV 1080i60 */
	 0x00, 0x00, 0x00, 0x01, 0xB0, 0x00, 0x00, 0x00पूर्ण,
पूर्ण;

/*
 * 50 48 60 gleich
 * 27p50 9f 00 22 80 42 69 18 ...
 * 27p60 93 00 22 80 82 69 1c ...
 */

/* Maxbyte to 1144 (क्रम raw data) */
अटल u8 ITUFeatureDecoderSetup[8] = अणु
	0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x04, 0x00
पूर्ण;

व्योम FillTSBuffer(व्योम *Buffer, पूर्णांक Length, u32 Flags)
अणु
	u32 *ptr = Buffer;

	स_रखो(Buffer, TS_FILLER, Length);
	जबतक (Length > 0) अणु
		अगर (Flags & DF_SWAP32)
			*ptr = 0x471FFF10;
		अन्यथा
			*ptr = 0x10FF1F47;
		ptr += (188 / 4);
		Length -= 188;
	पूर्ण
पूर्ण


अटल व्योम flush_buffers(काष्ठा ngene_channel *chan)
अणु
	u8 val;

	करो अणु
		msleep(1);
		spin_lock_irq(&chan->state_lock);
		val = chan->nextBuffer->ngeneBuffer.SR.Flags & 0x80;
		spin_unlock_irq(&chan->state_lock);
	पूर्ण जबतक (val);
पूर्ण

अटल व्योम clear_buffers(काष्ठा ngene_channel *chan)
अणु
	काष्ठा SBufferHeader *Cur = chan->nextBuffer;

	करो अणु
		स_रखो(&Cur->ngeneBuffer.SR, 0, माप(Cur->ngeneBuffer.SR));
		अगर (chan->mode & NGENE_IO_TSOUT)
			FillTSBuffer(Cur->Buffer1,
				     chan->Capture1Length,
				     chan->DataFormatFlags);
		Cur = Cur->Next;
	पूर्ण जबतक (Cur != chan->nextBuffer);

	अगर (chan->mode & NGENE_IO_TSOUT) अणु
		chan->nextBuffer->ngeneBuffer.SR.DTOUpdate =
			chan->AudioDTOValue;
		chan->AudioDTOUpdated = 0;

		Cur = chan->TSIdleBuffer.Head;

		करो अणु
			स_रखो(&Cur->ngeneBuffer.SR, 0,
			       माप(Cur->ngeneBuffer.SR));
			FillTSBuffer(Cur->Buffer1,
				     chan->Capture1Length,
				     chan->DataFormatFlags);
			Cur = Cur->Next;
		पूर्ण जबतक (Cur != chan->TSIdleBuffer.Head);
	पूर्ण
पूर्ण

अटल पूर्णांक ngene_command_stream_control(काष्ठा ngene *dev, u8 stream,
					u8 control, u8 mode, u8 flags)
अणु
	काष्ठा device *pdev = &dev->pci_dev->dev;
	काष्ठा ngene_channel *chan = &dev->channel[stream];
	काष्ठा ngene_command com;
	u16 BsUVI = ((stream & 1) ? 0x9400 : 0x9300);
	u16 BsSDI = ((stream & 1) ? 0x9600 : 0x9500);
	u16 BsSPI = ((stream & 1) ? 0x9800 : 0x9700);
	u16 BsSDO = 0x9B00;

	स_रखो(&com, 0, माप(com));
	com.cmd.hdr.Opcode = CMD_CONTROL;
	com.cmd.hdr.Length = माप(काष्ठा FW_STREAM_CONTROL) - 2;
	com.cmd.StreamControl.Stream = stream | (control ? 8 : 0);
	अगर (chan->mode & NGENE_IO_TSOUT)
		com.cmd.StreamControl.Stream |= 0x07;
	com.cmd.StreamControl.Control = control |
		(flags & SFLAG_ORDER_LUMA_CHROMA);
	com.cmd.StreamControl.Mode = mode;
	com.in_len = माप(काष्ठा FW_STREAM_CONTROL);
	com.out_len = 0;

	dev_dbg(pdev, "Stream=%02x, Control=%02x, Mode=%02x\n",
		com.cmd.StreamControl.Stream, com.cmd.StreamControl.Control,
		com.cmd.StreamControl.Mode);

	chan->Mode = mode;

	अगर (!(control & 0x80)) अणु
		spin_lock_irq(&chan->state_lock);
		अगर (chan->State == KSSTATE_RUN) अणु
			chan->State = KSSTATE_ACQUIRE;
			chan->HWState = HWSTATE_STOP;
			spin_unlock_irq(&chan->state_lock);
			अगर (ngene_command(dev, &com) < 0)
				वापस -1;
			/* clear_buffers(chan); */
			flush_buffers(chan);
			वापस 0;
		पूर्ण
		spin_unlock_irq(&chan->state_lock);
		वापस 0;
	पूर्ण

	अगर (mode & SMODE_AUDIO_CAPTURE) अणु
		com.cmd.StreamControl.CaptureBlockCount =
			chan->Capture1Length / AUDIO_BLOCK_SIZE;
		com.cmd.StreamControl.Buffer_Address = chan->RingBuffer.PAHead;
	पूर्ण अन्यथा अगर (mode & SMODE_TRANSPORT_STREAM) अणु
		com.cmd.StreamControl.CaptureBlockCount =
			chan->Capture1Length / TS_BLOCK_SIZE;
		com.cmd.StreamControl.MaxLinesPerField =
			chan->Capture1Length / TS_BLOCK_SIZE;
		com.cmd.StreamControl.Buffer_Address =
			chan->TSRingBuffer.PAHead;
		अगर (chan->mode & NGENE_IO_TSOUT) अणु
			com.cmd.StreamControl.BytesPerVBILine =
				chan->Capture1Length / TS_BLOCK_SIZE;
			com.cmd.StreamControl.Stream |= 0x07;
		पूर्ण
	पूर्ण अन्यथा अणु
		com.cmd.StreamControl.BytesPerVideoLine = chan->nBytesPerLine;
		com.cmd.StreamControl.MaxLinesPerField = chan->nLines;
		com.cmd.StreamControl.MinLinesPerField = 100;
		com.cmd.StreamControl.Buffer_Address = chan->RingBuffer.PAHead;

		अगर (mode & SMODE_VBI_CAPTURE) अणु
			com.cmd.StreamControl.MaxVBILinesPerField =
				chan->nVBILines;
			com.cmd.StreamControl.MinVBILinesPerField = 0;
			com.cmd.StreamControl.BytesPerVBILine =
				chan->nBytesPerVBILine;
		पूर्ण
		अगर (flags & SFLAG_COLORBAR)
			com.cmd.StreamControl.Stream |= 0x04;
	पूर्ण

	spin_lock_irq(&chan->state_lock);
	अगर (mode & SMODE_AUDIO_CAPTURE) अणु
		chan->nextBuffer = chan->RingBuffer.Head;
		अगर (mode & SMODE_AUDIO_SPDIF) अणु
			com.cmd.StreamControl.SetupDataLen =
				माप(SPDIFConfiguration);
			com.cmd.StreamControl.SetupDataAddr = BsSPI;
			स_नकल(com.cmd.StreamControl.SetupData,
			       SPDIFConfiguration, माप(SPDIFConfiguration));
		पूर्ण अन्यथा अणु
			com.cmd.StreamControl.SetupDataLen = 4;
			com.cmd.StreamControl.SetupDataAddr = BsSDI;
			स_नकल(com.cmd.StreamControl.SetupData,
			       I2SConfiguration +
			       4 * dev->card_info->i2s[stream], 4);
		पूर्ण
	पूर्ण अन्यथा अगर (mode & SMODE_TRANSPORT_STREAM) अणु
		chan->nextBuffer = chan->TSRingBuffer.Head;
		अगर (stream >= STREAM_AUDIOIN1) अणु
			अगर (chan->mode & NGENE_IO_TSOUT) अणु
				com.cmd.StreamControl.SetupDataLen =
					माप(TS_I2SOutConfiguration);
				com.cmd.StreamControl.SetupDataAddr = BsSDO;
				स_नकल(com.cmd.StreamControl.SetupData,
				       TS_I2SOutConfiguration,
				       माप(TS_I2SOutConfiguration));
			पूर्ण अन्यथा अणु
				com.cmd.StreamControl.SetupDataLen =
					माप(TS_I2SConfiguration);
				com.cmd.StreamControl.SetupDataAddr = BsSDI;
				स_नकल(com.cmd.StreamControl.SetupData,
				       TS_I2SConfiguration,
				       माप(TS_I2SConfiguration));
			पूर्ण
		पूर्ण अन्यथा अणु
			com.cmd.StreamControl.SetupDataLen = 8;
			com.cmd.StreamControl.SetupDataAddr = BsUVI + 0x10;
			स_नकल(com.cmd.StreamControl.SetupData,
			       TSFeatureDecoderSetup +
			       8 * dev->card_info->tsf[stream], 8);
		पूर्ण
	पूर्ण अन्यथा अणु
		chan->nextBuffer = chan->RingBuffer.Head;
		com.cmd.StreamControl.SetupDataLen =
			16 + माप(ITUFeatureDecoderSetup);
		com.cmd.StreamControl.SetupDataAddr = BsUVI;
		स_नकल(com.cmd.StreamControl.SetupData,
		       ITUDecoderSetup[chan->itumode], 16);
		स_नकल(com.cmd.StreamControl.SetupData + 16,
		       ITUFeatureDecoderSetup, माप(ITUFeatureDecoderSetup));
	पूर्ण
	clear_buffers(chan);
	chan->State = KSSTATE_RUN;
	अगर (mode & SMODE_TRANSPORT_STREAM)
		chan->HWState = HWSTATE_RUN;
	अन्यथा
		chan->HWState = HWSTATE_STARTUP;
	spin_unlock_irq(&chan->state_lock);

	अगर (ngene_command(dev, &com) < 0)
		वापस -1;

	वापस 0;
पूर्ण

व्योम set_transfer(काष्ठा ngene_channel *chan, पूर्णांक state)
अणु
	काष्ठा device *pdev = &chan->dev->pci_dev->dev;
	u8 control = 0, mode = 0, flags = 0;
	काष्ठा ngene *dev = chan->dev;
	पूर्णांक ret;

	/*
	dev_info(pdev, "st %d\n", state);
	msleep(100);
	*/

	अगर (state) अणु
		अगर (chan->running) अणु
			dev_info(pdev, "already running\n");
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!chan->running) अणु
			dev_info(pdev, "already stopped\n");
			वापस;
		पूर्ण
	पूर्ण

	अगर (dev->card_info->चयन_ctrl)
		dev->card_info->चयन_ctrl(chan, 1, state ^ 1);

	अगर (state) अणु
		spin_lock_irq(&chan->state_lock);

		/* dev_info(pdev, "lock=%08x\n",
			  ngपढ़ोl(0x9310)); */
		dvb_ringbuffer_flush(&dev->tsout_rbuf);
		control = 0x80;
		अगर (chan->mode & (NGENE_IO_TSIN | NGENE_IO_TSOUT)) अणु
			chan->Capture1Length = 512 * 188;
			mode = SMODE_TRANSPORT_STREAM;
		पूर्ण
		अगर (chan->mode & NGENE_IO_TSOUT) अणु
			chan->pBufferExchange = tsout_exchange;
			/* 0x66666666 = 50MHz *2^33 /250MHz */
			chan->AudioDTOValue = 0x80000000;
			chan->AudioDTOUpdated = 1;
		पूर्ण
		अगर (chan->mode & NGENE_IO_TSIN)
			chan->pBufferExchange = tsin_exchange;
		spin_unlock_irq(&chan->state_lock);
	पूर्ण
		/* अन्यथा dev_info(pdev, "lock=%08x\n",
			   ngपढ़ोl(0x9310)); */

	mutex_lock(&dev->stream_mutex);
	ret = ngene_command_stream_control(dev, chan->number,
					   control, mode, flags);
	mutex_unlock(&dev->stream_mutex);

	अगर (!ret)
		chan->running = state;
	अन्यथा
		dev_err(pdev, "%s %d failed\n", __func__, state);
	अगर (!state) अणु
		spin_lock_irq(&chan->state_lock);
		chan->pBufferExchange = शून्य;
		dvb_ringbuffer_flush(&dev->tsout_rbuf);
		spin_unlock_irq(&chan->state_lock);
	पूर्ण
पूर्ण


/****************************************************************************/
/* nGene hardware init and release functions ********************************/
/****************************************************************************/

अटल व्योम मुक्त_ringbuffer(काष्ठा ngene *dev, काष्ठा SRingBufferDescriptor *rb)
अणु
	काष्ठा SBufferHeader *Cur = rb->Head;
	u32 j;

	अगर (!Cur)
		वापस;

	क्रम (j = 0; j < rb->NumBuffers; j++, Cur = Cur->Next) अणु
		अगर (Cur->Buffer1)
			dma_मुक्त_coherent(&dev->pci_dev->dev,
					  rb->Buffer1Length, Cur->Buffer1,
					  Cur->scList1->Address);

		अगर (Cur->Buffer2)
			dma_मुक्त_coherent(&dev->pci_dev->dev,
					  rb->Buffer2Length, Cur->Buffer2,
					  Cur->scList2->Address);
	पूर्ण

	अगर (rb->SCListMem)
		dma_मुक्त_coherent(&dev->pci_dev->dev, rb->SCListMemSize,
				  rb->SCListMem, rb->PASCListMem);

	dma_मुक्त_coherent(&dev->pci_dev->dev, rb->MemSize, rb->Head,
			  rb->PAHead);
पूर्ण

अटल व्योम मुक्त_idlebuffer(काष्ठा ngene *dev,
		     काष्ठा SRingBufferDescriptor *rb,
		     काष्ठा SRingBufferDescriptor *tb)
अणु
	पूर्णांक j;
	काष्ठा SBufferHeader *Cur = tb->Head;

	अगर (!rb->Head)
		वापस;
	मुक्त_ringbuffer(dev, rb);
	क्रम (j = 0; j < tb->NumBuffers; j++, Cur = Cur->Next) अणु
		Cur->Buffer2 = शून्य;
		Cur->scList2 = शून्य;
		Cur->ngeneBuffer.Address_of_first_entry_2 = 0;
		Cur->ngeneBuffer.Number_of_entries_2 = 0;
	पूर्ण
पूर्ण

अटल व्योम मुक्त_common_buffers(काष्ठा ngene *dev)
अणु
	u32 i;
	काष्ठा ngene_channel *chan;

	क्रम (i = STREAM_VIDEOIN1; i < MAX_STREAM; i++) अणु
		chan = &dev->channel[i];
		मुक्त_idlebuffer(dev, &chan->TSIdleBuffer, &chan->TSRingBuffer);
		मुक्त_ringbuffer(dev, &chan->RingBuffer);
		मुक्त_ringbuffer(dev, &chan->TSRingBuffer);
	पूर्ण

	अगर (dev->OverflowBuffer)
		dma_मुक्त_coherent(&dev->pci_dev->dev, OVERFLOW_BUFFER_SIZE,
				  dev->OverflowBuffer, dev->PAOverflowBuffer);

	अगर (dev->FWInterfaceBuffer)
		dma_मुक्त_coherent(&dev->pci_dev->dev, 4096,
				  dev->FWInterfaceBuffer,
				  dev->PAFWInterfaceBuffer);
पूर्ण

/****************************************************************************/
/* Ring buffer handling *****************************************************/
/****************************************************************************/

अटल पूर्णांक create_ring_buffer(काष्ठा pci_dev *pci_dev,
		       काष्ठा SRingBufferDescriptor *descr, u32 NumBuffers)
अणु
	dma_addr_t पंचांगp;
	काष्ठा SBufferHeader *Head;
	u32 i;
	u32 MemSize = SIZखातापूर्ण_SBufferHeader * NumBuffers;
	u64 PARingBufferHead;
	u64 PARingBufferCur;
	u64 PARingBufferNext;
	काष्ठा SBufferHeader *Cur, *Next;

	descr->Head = शून्य;
	descr->MemSize = 0;
	descr->PAHead = 0;
	descr->NumBuffers = 0;

	अगर (MemSize < 4096)
		MemSize = 4096;

	Head = dma_alloc_coherent(&pci_dev->dev, MemSize, &पंचांगp, GFP_KERNEL);
	PARingBufferHead = पंचांगp;

	अगर (!Head)
		वापस -ENOMEM;

	PARingBufferCur = PARingBufferHead;
	Cur = Head;

	क्रम (i = 0; i < NumBuffers - 1; i++) अणु
		Next = (काष्ठा SBufferHeader *)
			(((u8 *) Cur) + SIZखातापूर्ण_SBufferHeader);
		PARingBufferNext = PARingBufferCur + SIZखातापूर्ण_SBufferHeader;
		Cur->Next = Next;
		Cur->ngeneBuffer.Next = PARingBufferNext;
		Cur = Next;
		PARingBufferCur = PARingBufferNext;
	पूर्ण
	/* Last Buffer poपूर्णांकs back to first one */
	Cur->Next = Head;
	Cur->ngeneBuffer.Next = PARingBufferHead;

	descr->Head       = Head;
	descr->MemSize    = MemSize;
	descr->PAHead     = PARingBufferHead;
	descr->NumBuffers = NumBuffers;

	वापस 0;
पूर्ण

अटल पूर्णांक AllocateRingBuffers(काष्ठा pci_dev *pci_dev,
			       dma_addr_t of,
			       काष्ठा SRingBufferDescriptor *pRingBuffer,
			       u32 Buffer1Length, u32 Buffer2Length)
अणु
	dma_addr_t पंचांगp;
	u32 i, j;
	u32 SCListMemSize = pRingBuffer->NumBuffers
		* ((Buffer2Length != 0) ? (NUM_SCATTER_GATHER_ENTRIES * 2) :
		    NUM_SCATTER_GATHER_ENTRIES)
		* माप(काष्ठा HW_SCATTER_GATHER_ELEMENT);

	u64 PASCListMem;
	काष्ठा HW_SCATTER_GATHER_ELEMENT *SCListEntry;
	u64 PASCListEntry;
	काष्ठा SBufferHeader *Cur;
	व्योम *SCListMem;

	अगर (SCListMemSize < 4096)
		SCListMemSize = 4096;

	SCListMem = dma_alloc_coherent(&pci_dev->dev, SCListMemSize, &पंचांगp,
				       GFP_KERNEL);

	PASCListMem = पंचांगp;
	अगर (SCListMem == शून्य)
		वापस -ENOMEM;

	pRingBuffer->SCListMem = SCListMem;
	pRingBuffer->PASCListMem = PASCListMem;
	pRingBuffer->SCListMemSize = SCListMemSize;
	pRingBuffer->Buffer1Length = Buffer1Length;
	pRingBuffer->Buffer2Length = Buffer2Length;

	SCListEntry = SCListMem;
	PASCListEntry = PASCListMem;
	Cur = pRingBuffer->Head;

	क्रम (i = 0; i < pRingBuffer->NumBuffers; i += 1, Cur = Cur->Next) अणु
		u64 PABuffer;

		व्योम *Buffer = dma_alloc_coherent(&pci_dev->dev,
						  Buffer1Length, &पंचांगp, GFP_KERNEL);
		PABuffer = पंचांगp;

		अगर (Buffer == शून्य)
			वापस -ENOMEM;

		Cur->Buffer1 = Buffer;

		SCListEntry->Address = PABuffer;
		SCListEntry->Length  = Buffer1Length;

		Cur->scList1 = SCListEntry;
		Cur->ngeneBuffer.Address_of_first_entry_1 = PASCListEntry;
		Cur->ngeneBuffer.Number_of_entries_1 =
			NUM_SCATTER_GATHER_ENTRIES;

		SCListEntry += 1;
		PASCListEntry += माप(काष्ठा HW_SCATTER_GATHER_ELEMENT);

#अगर NUM_SCATTER_GATHER_ENTRIES > 1
		क्रम (j = 0; j < NUM_SCATTER_GATHER_ENTRIES - 1; j += 1) अणु
			SCListEntry->Address = of;
			SCListEntry->Length = OVERFLOW_BUFFER_SIZE;
			SCListEntry += 1;
			PASCListEntry +=
				माप(काष्ठा HW_SCATTER_GATHER_ELEMENT);
		पूर्ण
#पूर्ण_अगर

		अगर (!Buffer2Length)
			जारी;

		Buffer = dma_alloc_coherent(&pci_dev->dev, Buffer2Length,
					    &पंचांगp, GFP_KERNEL);
		PABuffer = पंचांगp;

		अगर (Buffer == शून्य)
			वापस -ENOMEM;

		Cur->Buffer2 = Buffer;

		SCListEntry->Address = PABuffer;
		SCListEntry->Length  = Buffer2Length;

		Cur->scList2 = SCListEntry;
		Cur->ngeneBuffer.Address_of_first_entry_2 = PASCListEntry;
		Cur->ngeneBuffer.Number_of_entries_2 =
			NUM_SCATTER_GATHER_ENTRIES;

		SCListEntry   += 1;
		PASCListEntry += माप(काष्ठा HW_SCATTER_GATHER_ELEMENT);

#अगर NUM_SCATTER_GATHER_ENTRIES > 1
		क्रम (j = 0; j < NUM_SCATTER_GATHER_ENTRIES - 1; j++) अणु
			SCListEntry->Address = of;
			SCListEntry->Length = OVERFLOW_BUFFER_SIZE;
			SCListEntry += 1;
			PASCListEntry +=
				माप(काष्ठा HW_SCATTER_GATHER_ELEMENT);
		पूर्ण
#पूर्ण_अगर

	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक FillTSIdleBuffer(काष्ठा SRingBufferDescriptor *pIdleBuffer,
			    काष्ठा SRingBufferDescriptor *pRingBuffer)
अणु
	/* Copy poपूर्णांकer to scatter gather list in TSRingbuffer
	   काष्ठाure क्रम buffer 2
	   Load number of buffer
	*/
	u32 n = pRingBuffer->NumBuffers;

	/* Poपूर्णांक to first buffer entry */
	काष्ठा SBufferHeader *Cur = pRingBuffer->Head;
	पूर्णांक i;
	/* Loop through all buffer and set Buffer 2 poपूर्णांकers to TSIdlebuffer */
	क्रम (i = 0; i < n; i++) अणु
		Cur->Buffer2 = pIdleBuffer->Head->Buffer1;
		Cur->scList2 = pIdleBuffer->Head->scList1;
		Cur->ngeneBuffer.Address_of_first_entry_2 =
			pIdleBuffer->Head->ngeneBuffer.
			Address_of_first_entry_1;
		Cur->ngeneBuffer.Number_of_entries_2 =
			pIdleBuffer->Head->ngeneBuffer.Number_of_entries_1;
		Cur = Cur->Next;
	पूर्ण
	वापस 0;
पूर्ण

अटल u32 RingBufferSizes[MAX_STREAM] = अणु
	RING_SIZE_VIDEO,
	RING_SIZE_VIDEO,
	RING_SIZE_AUDIO,
	RING_SIZE_AUDIO,
	RING_SIZE_AUDIO,
पूर्ण;

अटल u32 Buffer1Sizes[MAX_STREAM] = अणु
	MAX_VIDEO_BUFFER_SIZE,
	MAX_VIDEO_BUFFER_SIZE,
	MAX_AUDIO_BUFFER_SIZE,
	MAX_AUDIO_BUFFER_SIZE,
	MAX_AUDIO_BUFFER_SIZE
पूर्ण;

अटल u32 Buffer2Sizes[MAX_STREAM] = अणु
	MAX_VBI_BUFFER_SIZE,
	MAX_VBI_BUFFER_SIZE,
	0,
	0,
	0
पूर्ण;


अटल पूर्णांक AllocCommonBuffers(काष्ठा ngene *dev)
अणु
	पूर्णांक status = 0, i;

	dev->FWInterfaceBuffer = dma_alloc_coherent(&dev->pci_dev->dev, 4096,
						    &dev->PAFWInterfaceBuffer,
						    GFP_KERNEL);
	अगर (!dev->FWInterfaceBuffer)
		वापस -ENOMEM;
	dev->hosttongene = dev->FWInterfaceBuffer;
	dev->ngenetohost = dev->FWInterfaceBuffer + 256;
	dev->EventBuffer = dev->FWInterfaceBuffer + 512;

	dev->OverflowBuffer = dma_alloc_coherent(&dev->pci_dev->dev,
						 OVERFLOW_BUFFER_SIZE,
						 &dev->PAOverflowBuffer, GFP_KERNEL);
	अगर (!dev->OverflowBuffer)
		वापस -ENOMEM;

	क्रम (i = STREAM_VIDEOIN1; i < MAX_STREAM; i++) अणु
		पूर्णांक type = dev->card_info->io_type[i];

		dev->channel[i].State = KSSTATE_STOP;

		अगर (type & (NGENE_IO_TV | NGENE_IO_HDTV | NGENE_IO_AIN)) अणु
			status = create_ring_buffer(dev->pci_dev,
						    &dev->channel[i].RingBuffer,
						    RingBufferSizes[i]);
			अगर (status < 0)
				अवरोध;

			अगर (type & (NGENE_IO_TV | NGENE_IO_AIN)) अणु
				status = AllocateRingBuffers(dev->pci_dev,
							     dev->
							     PAOverflowBuffer,
							     &dev->channel[i].
							     RingBuffer,
							     Buffer1Sizes[i],
							     Buffer2Sizes[i]);
				अगर (status < 0)
					अवरोध;
			पूर्ण अन्यथा अगर (type & NGENE_IO_HDTV) अणु
				status = AllocateRingBuffers(dev->pci_dev,
							     dev->
							     PAOverflowBuffer,
							     &dev->channel[i].
							     RingBuffer,
							   MAX_HDTV_BUFFER_SIZE,
							     0);
				अगर (status < 0)
					अवरोध;
			पूर्ण
		पूर्ण

		अगर (type & (NGENE_IO_TSIN | NGENE_IO_TSOUT)) अणु

			status = create_ring_buffer(dev->pci_dev,
						    &dev->channel[i].
						    TSRingBuffer, RING_SIZE_TS);
			अगर (status < 0)
				अवरोध;

			status = AllocateRingBuffers(dev->pci_dev,
						     dev->PAOverflowBuffer,
						     &dev->channel[i].
						     TSRingBuffer,
						     MAX_TS_BUFFER_SIZE, 0);
			अगर (status)
				अवरोध;
		पूर्ण

		अगर (type & NGENE_IO_TSOUT) अणु
			status = create_ring_buffer(dev->pci_dev,
						    &dev->channel[i].
						    TSIdleBuffer, 1);
			अगर (status < 0)
				अवरोध;
			status = AllocateRingBuffers(dev->pci_dev,
						     dev->PAOverflowBuffer,
						     &dev->channel[i].
						     TSIdleBuffer,
						     MAX_TS_BUFFER_SIZE, 0);
			अगर (status)
				अवरोध;
			FillTSIdleBuffer(&dev->channel[i].TSIdleBuffer,
					 &dev->channel[i].TSRingBuffer);
		पूर्ण
	पूर्ण
	वापस status;
पूर्ण

अटल व्योम ngene_release_buffers(काष्ठा ngene *dev)
अणु
	अगर (dev->iomem)
		iounmap(dev->iomem);
	मुक्त_common_buffers(dev);
	vमुक्त(dev->tsout_buf);
	vमुक्त(dev->tsin_buf);
	vमुक्त(dev->ain_buf);
	vमुक्त(dev->vin_buf);
	vमुक्त(dev);
पूर्ण

अटल पूर्णांक ngene_get_buffers(काष्ठा ngene *dev)
अणु
	अगर (AllocCommonBuffers(dev))
		वापस -ENOMEM;
	अगर (dev->card_info->io_type[4] & NGENE_IO_TSOUT) अणु
		dev->tsout_buf = vदो_स्मृति(TSOUT_BUF_SIZE);
		अगर (!dev->tsout_buf)
			वापस -ENOMEM;
		dvb_ringbuffer_init(&dev->tsout_rbuf,
				    dev->tsout_buf, TSOUT_BUF_SIZE);
	पूर्ण
	अगर (dev->card_info->io_type[2]&NGENE_IO_TSIN) अणु
		dev->tsin_buf = vदो_स्मृति(TSIN_BUF_SIZE);
		अगर (!dev->tsin_buf)
			वापस -ENOMEM;
		dvb_ringbuffer_init(&dev->tsin_rbuf,
				    dev->tsin_buf, TSIN_BUF_SIZE);
	पूर्ण
	अगर (dev->card_info->io_type[2] & NGENE_IO_AIN) अणु
		dev->ain_buf = vदो_स्मृति(AIN_BUF_SIZE);
		अगर (!dev->ain_buf)
			वापस -ENOMEM;
		dvb_ringbuffer_init(&dev->ain_rbuf, dev->ain_buf, AIN_BUF_SIZE);
	पूर्ण
	अगर (dev->card_info->io_type[0] & NGENE_IO_HDTV) अणु
		dev->vin_buf = vदो_स्मृति(VIN_BUF_SIZE);
		अगर (!dev->vin_buf)
			वापस -ENOMEM;
		dvb_ringbuffer_init(&dev->vin_rbuf, dev->vin_buf, VIN_BUF_SIZE);
	पूर्ण
	dev->iomem = ioremap(pci_resource_start(dev->pci_dev, 0),
			     pci_resource_len(dev->pci_dev, 0));
	अगर (!dev->iomem)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम ngene_init(काष्ठा ngene *dev)
अणु
	काष्ठा device *pdev = &dev->pci_dev->dev;
	पूर्णांक i;

	tasklet_setup(&dev->event_tasklet, event_tasklet);

	स_रखो_io(dev->iomem + 0xc000, 0x00, 0x220);
	स_रखो_io(dev->iomem + 0xc400, 0x00, 0x100);

	क्रम (i = 0; i < MAX_STREAM; i++) अणु
		dev->channel[i].dev = dev;
		dev->channel[i].number = i;
	पूर्ण

	dev->fw_पूर्णांकerface_version = 0;

	ngग_लिखोl(0, NGENE_INT_ENABLE);

	dev->icounts = ngपढ़ोl(NGENE_INT_COUNTS);

	dev->device_version = ngपढ़ोl(DEV_VER) & 0x0f;
	dev_info(pdev, "Device version %d\n", dev->device_version);
पूर्ण

अटल पूर्णांक ngene_load_firm(काष्ठा ngene *dev)
अणु
	काष्ठा device *pdev = &dev->pci_dev->dev;
	u32 size;
	स्थिर काष्ठा firmware *fw = शून्य;
	u8 *ngene_fw;
	अक्षर *fw_name;
	पूर्णांक err, version;

	version = dev->card_info->fw_version;

	चयन (version) अणु
	शेष:
	हाल 15:
		version = 15;
		size = 23466;
		fw_name = "ngene_15.fw";
		dev->cmd_समयout_workaround = true;
		अवरोध;
	हाल 16:
		size = 23498;
		fw_name = "ngene_16.fw";
		dev->cmd_समयout_workaround = true;
		अवरोध;
	हाल 17:
		size = 24446;
		fw_name = "ngene_17.fw";
		dev->cmd_समयout_workaround = true;
		अवरोध;
	हाल 18:
		size = 0;
		fw_name = "ngene_18.fw";
		अवरोध;
	पूर्ण

	अगर (request_firmware(&fw, fw_name, &dev->pci_dev->dev) < 0) अणु
		dev_err(pdev, "Could not load firmware file %s.\n", fw_name);
		dev_info(pdev, "Copy %s to your hotplug directory!\n",
			 fw_name);
		वापस -1;
	पूर्ण
	अगर (size == 0)
		size = fw->size;
	अगर (size != fw->size) अणु
		dev_err(pdev, "Firmware %s has invalid size!", fw_name);
		err = -1;
	पूर्ण अन्यथा अणु
		dev_info(pdev, "Loading firmware file %s.\n", fw_name);
		ngene_fw = (u8 *) fw->data;
		err = ngene_command_load_firmware(dev, ngene_fw, size);
	पूर्ण

	release_firmware(fw);

	वापस err;
पूर्ण

अटल व्योम ngene_stop(काष्ठा ngene *dev)
अणु
	mutex_destroy(&dev->cmd_mutex);
	i2c_del_adapter(&(dev->channel[0].i2c_adapter));
	i2c_del_adapter(&(dev->channel[1].i2c_adapter));
	ngग_लिखोl(0, NGENE_INT_ENABLE);
	ngग_लिखोl(0, NGENE_COMMAND);
	ngग_लिखोl(0, NGENE_COMMAND_HI);
	ngग_लिखोl(0, NGENE_STATUS);
	ngग_लिखोl(0, NGENE_STATUS_HI);
	ngग_लिखोl(0, NGENE_EVENT);
	ngग_लिखोl(0, NGENE_EVENT_HI);
	मुक्त_irq(dev->pci_dev->irq, dev);
#अगर_घोषित CONFIG_PCI_MSI
	अगर (dev->msi_enabled)
		pci_disable_msi(dev->pci_dev);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक ngene_buffer_config(काष्ठा ngene *dev)
अणु
	पूर्णांक stat;

	अगर (dev->card_info->fw_version >= 17) अणु
		u8 tsin12_config[6]   = अणु 0x60, 0x60, 0x00, 0x00, 0x00, 0x00 पूर्ण;
		u8 tsin1234_config[6] = अणु 0x30, 0x30, 0x00, 0x30, 0x30, 0x00 पूर्ण;
		u8 tsio1235_config[6] = अणु 0x30, 0x30, 0x00, 0x28, 0x00, 0x38 पूर्ण;
		u8 *bconf = tsin12_config;

		अगर (dev->card_info->io_type[2]&NGENE_IO_TSIN &&
		    dev->card_info->io_type[3]&NGENE_IO_TSIN) अणु
			bconf = tsin1234_config;
			अगर (dev->card_info->io_type[4]&NGENE_IO_TSOUT &&
			    dev->ci.en)
				bconf = tsio1235_config;
		पूर्ण
		stat = ngene_command_config_मुक्त_buf(dev, bconf);
	पूर्ण अन्यथा अणु
		पूर्णांक bconf = BUFFER_CONFIG_4422;

		अगर (dev->card_info->io_type[3] == NGENE_IO_TSIN)
			bconf = BUFFER_CONFIG_3333;
		stat = ngene_command_config_buf(dev, bconf);
	पूर्ण
	वापस stat;
पूर्ण


अटल पूर्णांक ngene_start(काष्ठा ngene *dev)
अणु
	पूर्णांक stat;
	पूर्णांक i;

	pci_set_master(dev->pci_dev);
	ngene_init(dev);

	stat = request_irq(dev->pci_dev->irq, irq_handler,
			   IRQF_SHARED, "nGene",
			   (व्योम *)dev);
	अगर (stat < 0)
		वापस stat;

	init_रुकोqueue_head(&dev->cmd_wq);
	init_रुकोqueue_head(&dev->tx_wq);
	init_रुकोqueue_head(&dev->rx_wq);
	mutex_init(&dev->cmd_mutex);
	mutex_init(&dev->stream_mutex);
	sema_init(&dev->pll_mutex, 1);
	mutex_init(&dev->i2c_चयन_mutex);
	spin_lock_init(&dev->cmd_lock);
	क्रम (i = 0; i < MAX_STREAM; i++)
		spin_lock_init(&dev->channel[i].state_lock);
	ngग_लिखोl(1, TIMESTAMPS);

	ngग_लिखोl(1, NGENE_INT_ENABLE);

	stat = ngene_load_firm(dev);
	अगर (stat < 0)
		जाओ fail;

#अगर_घोषित CONFIG_PCI_MSI
	/* enable MSI अगर kernel and card support it */
	अगर (pci_msi_enabled() && dev->card_info->msi_supported) अणु
		काष्ठा device *pdev = &dev->pci_dev->dev;
		अचिन्हित दीर्घ flags;

		ngग_लिखोl(0, NGENE_INT_ENABLE);
		मुक्त_irq(dev->pci_dev->irq, dev);
		stat = pci_enable_msi(dev->pci_dev);
		अगर (stat) अणु
			dev_info(pdev, "MSI not available\n");
			flags = IRQF_SHARED;
		पूर्ण अन्यथा अणु
			flags = 0;
			dev->msi_enabled = true;
		पूर्ण
		stat = request_irq(dev->pci_dev->irq, irq_handler,
					flags, "nGene", dev);
		अगर (stat < 0)
			जाओ fail2;
		ngग_लिखोl(1, NGENE_INT_ENABLE);
	पूर्ण
#पूर्ण_अगर

	stat = ngene_i2c_init(dev, 0);
	अगर (stat < 0)
		जाओ fail;

	stat = ngene_i2c_init(dev, 1);
	अगर (stat < 0)
		जाओ fail;

	वापस 0;

fail:
	ngग_लिखोl(0, NGENE_INT_ENABLE);
	मुक्त_irq(dev->pci_dev->irq, dev);
#अगर_घोषित CONFIG_PCI_MSI
fail2:
	अगर (dev->msi_enabled)
		pci_disable_msi(dev->pci_dev);
#पूर्ण_अगर
	वापस stat;
पूर्ण

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

अटल व्योम release_channel(काष्ठा ngene_channel *chan)
अणु
	काष्ठा dvb_demux *dvbdemux = &chan->demux;
	काष्ठा ngene *dev = chan->dev;

	अगर (chan->running)
		set_transfer(chan, 0);

	tasklet_समाप्त(&chan->demux_tasklet);

	अगर (chan->ci_dev) अणु
		dvb_unरेजिस्टर_device(chan->ci_dev);
		chan->ci_dev = शून्य;
	पूर्ण

	अगर (chan->fe2)
		dvb_unरेजिस्टर_frontend(chan->fe2);

	अगर (chan->fe) अणु
		dvb_unरेजिस्टर_frontend(chan->fe);

		/* release I2C client (tuner) अगर needed */
		अगर (chan->i2c_client_fe) अणु
			dvb_module_release(chan->i2c_client[0]);
			chan->i2c_client[0] = शून्य;
		पूर्ण

		dvb_frontend_detach(chan->fe);
		chan->fe = शून्य;
	पूर्ण

	अगर (chan->has_demux) अणु
		dvb_net_release(&chan->dvbnet);
		dvbdemux->dmx.बंद(&dvbdemux->dmx);
		dvbdemux->dmx.हटाओ_frontend(&dvbdemux->dmx,
					      &chan->hw_frontend);
		dvbdemux->dmx.हटाओ_frontend(&dvbdemux->dmx,
					      &chan->mem_frontend);
		dvb_dmxdev_release(&chan->dmxdev);
		dvb_dmx_release(&chan->demux);
		chan->has_demux = false;
	पूर्ण

	अगर (chan->has_adapter) अणु
		dvb_unरेजिस्टर_adapter(&dev->adapter[chan->number]);
		chan->has_adapter = false;
	पूर्ण
पूर्ण

अटल पूर्णांक init_channel(काष्ठा ngene_channel *chan)
अणु
	पूर्णांक ret = 0, nr = chan->number;
	काष्ठा dvb_adapter *adapter = शून्य;
	काष्ठा dvb_demux *dvbdemux = &chan->demux;
	काष्ठा ngene *dev = chan->dev;
	काष्ठा ngene_info *ni = dev->card_info;
	पूर्णांक io = ni->io_type[nr];

	tasklet_setup(&chan->demux_tasklet, demux_tasklet);
	chan->users = 0;
	chan->type = io;
	chan->mode = chan->type;	/* क्रम now only one mode */
	chan->i2c_client_fe = 0;	/* be sure this is set to zero */

	अगर (io & NGENE_IO_TSIN) अणु
		chan->fe = शून्य;
		अगर (ni->demod_attach[nr]) अणु
			ret = ni->demod_attach[nr](chan);
			अगर (ret < 0)
				जाओ err;
		पूर्ण
		अगर (chan->fe && ni->tuner_attach[nr]) अणु
			ret = ni->tuner_attach[nr](chan);
			अगर (ret < 0)
				जाओ err;
		पूर्ण
	पूर्ण

	अगर (!dev->ci.en && (io & NGENE_IO_TSOUT))
		वापस 0;

	अगर (io & (NGENE_IO_TSIN | NGENE_IO_TSOUT)) अणु
		अगर (nr >= STREAM_AUDIOIN1)
			chan->DataFormatFlags = DF_SWAP32;

		अगर (nr == 0 || !one_adapter || dev->first_adapter == शून्य) अणु
			adapter = &dev->adapter[nr];
			ret = dvb_रेजिस्टर_adapter(adapter, "nGene",
						   THIS_MODULE,
						   &chan->dev->pci_dev->dev,
						   adapter_nr);
			अगर (ret < 0)
				जाओ err;
			अगर (dev->first_adapter == शून्य)
				dev->first_adapter = adapter;
			chan->has_adapter = true;
		पूर्ण अन्यथा
			adapter = dev->first_adapter;
	पूर्ण

	अगर (dev->ci.en && (io & NGENE_IO_TSOUT)) अणु
		dvb_ca_en50221_init(adapter, dev->ci.en, 0, 1);
		set_transfer(chan, 1);
		chan->dev->channel[2].DataFormatFlags = DF_SWAP32;
		set_transfer(&chan->dev->channel[2], 1);
		dvb_रेजिस्टर_device(adapter, &chan->ci_dev,
				    &ngene_dvbdev_ci, (व्योम *) chan,
				    DVB_DEVICE_SEC, 0);
		अगर (!chan->ci_dev)
			जाओ err;
	पूर्ण

	अगर (chan->fe) अणु
		अगर (dvb_रेजिस्टर_frontend(adapter, chan->fe) < 0)
			जाओ err;
		chan->has_demux = true;
	पूर्ण
	अगर (chan->fe2) अणु
		अगर (dvb_रेजिस्टर_frontend(adapter, chan->fe2) < 0)
			जाओ err;
		अगर (chan->fe) अणु
			chan->fe2->tuner_priv = chan->fe->tuner_priv;
			स_नकल(&chan->fe2->ops.tuner_ops,
			       &chan->fe->ops.tuner_ops,
			       माप(काष्ठा dvb_tuner_ops));
		पूर्ण
	पूर्ण

	अगर (chan->has_demux) अणु
		ret = my_dvb_dmx_ts_card_init(dvbdemux, "SW demux",
					      ngene_start_feed,
					      ngene_stop_feed, chan);
		ret = my_dvb_dmxdev_ts_card_init(&chan->dmxdev, &chan->demux,
						 &chan->hw_frontend,
						 &chan->mem_frontend, adapter);
		ret = dvb_net_init(adapter, &chan->dvbnet, &chan->demux.dmx);
	पूर्ण

	वापस ret;

err:
	अगर (chan->fe) अणु
		dvb_frontend_detach(chan->fe);
		chan->fe = शून्य;
	पूर्ण
	release_channel(chan);
	वापस 0;
पूर्ण

अटल पूर्णांक init_channels(काष्ठा ngene *dev)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < MAX_STREAM; i++) अणु
		dev->channel[i].number = i;
		अगर (init_channel(&dev->channel[i]) < 0) अणु
			क्रम (j = i - 1; j >= 0; j--)
				release_channel(&dev->channel[j]);
			वापस -1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा cxd2099_cfg cxd_cfgपंचांगpl = अणु
	.bitrate = 62000,
	.polarity = 0,
	.घड़ी_mode = 0,
पूर्ण;

अटल व्योम cxd_attach(काष्ठा ngene *dev)
अणु
	काष्ठा device *pdev = &dev->pci_dev->dev;
	काष्ठा ngene_ci *ci = &dev->ci;
	काष्ठा cxd2099_cfg cxd_cfg = cxd_cfgपंचांगpl;
	काष्ठा i2c_client *client;
	पूर्णांक ret;
	u8 type;

	/* check क्रम CXD2099AR presence beक्रमe attaching */
	ret = ngene_port_has_cxd2099(&dev->channel[0].i2c_adapter, &type);
	अगर (!ret) अणु
		dev_dbg(pdev, "No CXD2099AR found\n");
		वापस;
	पूर्ण

	अगर (type != 1) अणु
		dev_warn(pdev, "CXD2099AR is uninitialized!\n");
		वापस;
	पूर्ण

	cxd_cfg.en = &ci->en;
	client = dvb_module_probe("cxd2099", शून्य,
				  &dev->channel[0].i2c_adapter,
				  0x40, &cxd_cfg);
	अगर (!client)
		जाओ err;

	ci->dev = dev;
	dev->channel[0].i2c_client[0] = client;
	वापस;

err:
	dev_err(pdev, "CXD2099AR attach failed\n");
	वापस;
पूर्ण

अटल व्योम cxd_detach(काष्ठा ngene *dev)
अणु
	काष्ठा ngene_ci *ci = &dev->ci;

	dvb_ca_en50221_release(ci->en);

	dvb_module_release(dev->channel[0].i2c_client[0]);
	dev->channel[0].i2c_client[0] = शून्य;
	ci->en = शून्य;
पूर्ण

/***********************************/
/* workaround क्रम shutकरोwn failure */
/***********************************/

अटल व्योम ngene_unlink(काष्ठा ngene *dev)
अणु
	काष्ठा ngene_command com;

	com.cmd.hdr.Opcode = CMD_MEM_WRITE;
	com.cmd.hdr.Length = 3;
	com.cmd.MemoryWrite.address = 0x910c;
	com.cmd.MemoryWrite.data = 0xff;
	com.in_len = 3;
	com.out_len = 1;

	mutex_lock(&dev->cmd_mutex);
	ngग_लिखोl(0, NGENE_INT_ENABLE);
	ngene_command_mutex(dev, &com);
	mutex_unlock(&dev->cmd_mutex);
पूर्ण

व्योम ngene_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ngene *dev = pci_get_drvdata(pdev);

	अगर (!dev || !shutकरोwn_workaround)
		वापस;

	dev_info(&pdev->dev, "shutdown workaround...\n");
	ngene_unlink(dev);
	pci_disable_device(pdev);
पूर्ण

/****************************************************************************/
/* device probe/हटाओ calls ************************************************/
/****************************************************************************/

व्योम ngene_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ngene *dev = pci_get_drvdata(pdev);
	पूर्णांक i;

	tasklet_समाप्त(&dev->event_tasklet);
	क्रम (i = MAX_STREAM - 1; i >= 0; i--)
		release_channel(&dev->channel[i]);
	अगर (dev->ci.en)
		cxd_detach(dev);
	ngene_stop(dev);
	ngene_release_buffers(dev);
	pci_disable_device(pdev);
पूर्ण

पूर्णांक ngene_probe(काष्ठा pci_dev *pci_dev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा ngene *dev;
	पूर्णांक stat = 0;

	अगर (pci_enable_device(pci_dev) < 0)
		वापस -ENODEV;

	dev = vzalloc(माप(काष्ठा ngene));
	अगर (dev == शून्य) अणु
		stat = -ENOMEM;
		जाओ fail0;
	पूर्ण

	dev->pci_dev = pci_dev;
	dev->card_info = (काष्ठा ngene_info *)id->driver_data;
	dev_info(&pci_dev->dev, "Found %s\n", dev->card_info->name);

	pci_set_drvdata(pci_dev, dev);

	/* Alloc buffers and start nGene */
	stat = ngene_get_buffers(dev);
	अगर (stat < 0)
		जाओ fail1;
	stat = ngene_start(dev);
	अगर (stat < 0)
		जाओ fail1;

	cxd_attach(dev);

	stat = ngene_buffer_config(dev);
	अगर (stat < 0)
		जाओ fail1;


	dev->i2c_current_bus = -1;

	/* Register DVB adapters and devices क्रम both channels */
	stat = init_channels(dev);
	अगर (stat < 0)
		जाओ fail2;

	वापस 0;

fail2:
	ngene_stop(dev);
fail1:
	ngene_release_buffers(dev);
fail0:
	pci_disable_device(pci_dev);
	वापस stat;
पूर्ण
