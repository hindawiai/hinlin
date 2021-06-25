<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
*  sym53c500_cs.c	Bob Tracy (rct@frus.com)
*
*  A reग_लिखो of the pcmcia-cs add-on driver क्रम newer (circa 1997)
*  New Media Bus Toaster PCMCIA SCSI cards using the Symbios Logic
*  53c500 controller: पूर्णांकended क्रम use with 2.6 and later kernels.
*  The pcmcia-cs add-on version of this driver is not supported
*  beyond 2.4.  It consisted of three files with history/copyright
*  inक्रमmation as follows:
*
*  SYM53C500.h
*	Bob Tracy (rct@frus.com)
*	Original by Tom Corner (tcorner@via.at).
*	Adapted from NCR53c406a.h which is Copyrighted (C) 1994
*	Normunds Saumanis (normunds@rx.tech.swh.lv)
*
*  SYM53C500.c
*	Bob Tracy (rct@frus.com)
*	Original driver by Tom Corner (tcorner@via.at) was adapted
*	from NCR53c406a.c which is Copyrighted (C) 1994, 1995, 1996 
*	Normunds Saumanis (normunds@fi.ibm.com)
*
*  sym53c500.c
*	Bob Tracy (rct@frus.com)
*	Original by Tom Corner (tcorner@via.at) was adapted from a
*	driver क्रम the Qlogic SCSI card written by
*	David Hinds (dhinds@allegro.stanक्रमd.edu).
*/

#घोषणा SYM53C500_DEBUG 0
#घोषणा VERBOSE_SYM53C500_DEBUG 0

/*
*  Set this to 0 अगर you encounter kernel lockups जबतक transferring 
*  data in PIO mode.  Note this can be changed via "sysfs".
*/
#घोषणा USE_FAST_PIO 1

/* =============== End of user configurable parameters ============== */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/ioport.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/bitops.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/irq.h>

#समावेश <scsi/scsi_ioctl.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_host.h>

#समावेश <pcmcia/cistpl.h>
#समावेश <pcmcia/ds.h>
#समावेश <pcmcia/ciscode.h>


/* ================================================================== */

#घोषणा SYNC_MODE 0 		/* Synchronous transfer mode */

/* Default configuration */
#घोषणा C1_IMG   0x07		/* ID=7 */
#घोषणा C2_IMG   0x48		/* FE SCSI2 */
#घोषणा C3_IMG   0x20		/* CDB */
#घोषणा C4_IMG   0x04		/* ANE */
#घोषणा C5_IMG   0xa4		/* ? changed from b6= AA PI SIE POL */
#घोषणा C7_IMG   0x80		/* added क्रम SYM53C500 t. corner */

/* Hardware Registers: offsets from io_port (base) */

/* Control Register Set 0 */
#घोषणा TC_LSB		0x00		/* transfer counter lsb */
#घोषणा TC_MSB		0x01		/* transfer counter msb */
#घोषणा SCSI_FIFO	0x02		/* scsi fअगरo रेजिस्टर */
#घोषणा CMD_REG		0x03		/* command रेजिस्टर */
#घोषणा STAT_REG	0x04		/* status रेजिस्टर */
#घोषणा DEST_ID		0x04		/* selection/reselection bus id */
#घोषणा INT_REG		0x05		/* पूर्णांकerrupt status रेजिस्टर */
#घोषणा SRTIMOUT	0x05		/* select/reselect समयout reg */
#घोषणा SEQ_REG		0x06		/* sequence step रेजिस्टर */
#घोषणा SYNCPRD		0x06		/* synchronous transfer period */
#घोषणा FIFO_FLAGS	0x07		/* indicates # of bytes in fअगरo */
#घोषणा SYNCOFF		0x07		/* synchronous offset रेजिस्टर */
#घोषणा CONFIG1		0x08		/* configuration रेजिस्टर */
#घोषणा CLKCONV		0x09		/* घड़ी conversion रेजिस्टर */
/* #घोषणा TESTREG	0x0A */		/* test mode रेजिस्टर */
#घोषणा CONFIG2		0x0B		/* configuration 2 रेजिस्टर */
#घोषणा CONFIG3		0x0C		/* configuration 3 रेजिस्टर */
#घोषणा CONFIG4		0x0D		/* configuration 4 रेजिस्टर */
#घोषणा TC_HIGH		0x0E		/* transfer counter high */
/* #घोषणा FIFO_BOTTOM	0x0F */		/* reserve FIFO byte रेजिस्टर */

/* Control Register Set 1 */
/* #घोषणा JUMPER_SENSE	0x00 */		/* jumper sense port reg (r/w) */
/* #घोषणा SRAM_PTR	0x01 */		/* SRAM address poपूर्णांकer reg (r/w) */
/* #घोषणा SRAM_DATA	0x02 */		/* SRAM data रेजिस्टर (r/w) */
#घोषणा PIO_FIFO	0x04		/* PIO FIFO रेजिस्टरs (r/w) */
/* #घोषणा PIO_FIFO1	0x05 */		/*  */
/* #घोषणा PIO_FIFO2	0x06 */		/*  */
/* #घोषणा PIO_FIFO3	0x07 */		/*  */
#घोषणा PIO_STATUS	0x08		/* PIO status (r/w) */
/* #घोषणा ATA_CMD	0x09 */		/* ATA command/status reg (r/w) */
/* #घोषणा ATA_ERR	0x0A */		/* ATA features/error reg (r/w) */
#घोषणा PIO_FLAG	0x0B		/* PIO flag पूर्णांकerrupt enable (r/w) */
#घोषणा CONFIG5		0x09		/* configuration 5 रेजिस्टर */
/* #घोषणा SIGNATURE	0x0E */		/* signature रेजिस्टर (r) */
/* #घोषणा CONFIG6	0x0F */		/* configuration 6 रेजिस्टर (r) */
#घोषणा CONFIG7		0x0d

/* select रेजिस्टर set 0 */
#घोषणा REG0(x)		(outb(C4_IMG, (x) + CONFIG4))
/* select रेजिस्टर set 1 */
#घोषणा REG1(x)		outb(C7_IMG, (x) + CONFIG7); outb(C5_IMG, (x) + CONFIG5)

#अगर SYM53C500_DEBUG
#घोषणा DEB(x) x
#अन्यथा
#घोषणा DEB(x)
#पूर्ण_अगर

#अगर VERBOSE_SYM53C500_DEBUG
#घोषणा VDEB(x) x
#अन्यथा
#घोषणा VDEB(x)
#पूर्ण_अगर

#घोषणा LOAD_DMA_COUNT(x, count) \
  outb(count & 0xff, (x) + TC_LSB); \
  outb((count >> 8) & 0xff, (x) + TC_MSB); \
  outb((count >> 16) & 0xff, (x) + TC_HIGH);

/* Chip commands */
#घोषणा DMA_OP               0x80

#घोषणा SCSI_NOP             0x00
#घोषणा FLUSH_FIFO           0x01
#घोषणा CHIP_RESET           0x02
#घोषणा SCSI_RESET           0x03
#घोषणा RESELECT             0x40
#घोषणा SELECT_NO_ATN        0x41
#घोषणा SELECT_ATN           0x42
#घोषणा SELECT_ATN_STOP      0x43
#घोषणा ENABLE_SEL           0x44
#घोषणा DISABLE_SEL          0x45
#घोषणा SELECT_ATN3          0x46
#घोषणा RESELECT3            0x47
#घोषणा TRANSFER_INFO        0x10
#घोषणा INIT_CMD_COMPLETE    0x11
#घोषणा MSG_ACCEPT           0x12
#घोषणा TRANSFER_PAD         0x18
#घोषणा SET_ATN              0x1a
#घोषणा RESET_ATN            0x1b
#घोषणा SEND_MSG             0x20
#घोषणा SEND_STATUS          0x21
#घोषणा SEND_DATA            0x22
#घोषणा DISCONN_SEQ          0x23
#घोषणा TERMINATE_SEQ        0x24
#घोषणा TARG_CMD_COMPLETE    0x25
#घोषणा DISCONN              0x27
#घोषणा RECV_MSG             0x28
#घोषणा RECV_CMD             0x29
#घोषणा RECV_DATA            0x2a
#घोषणा RECV_CMD_SEQ         0x2b
#घोषणा TARGET_ABORT_DMA     0x04

/* ================================================================== */

काष्ठा scsi_info_t अणु
	काष्ठा pcmcia_device	*p_dev;
	काष्ठा Scsi_Host *host;
	अचिन्हित लघु manf_id;
पूर्ण;

/*
*  Repository क्रम per-instance host data.
*/
काष्ठा sym53c500_data अणु
	काष्ठा scsi_cmnd *current_SC;
	पूर्णांक fast_pio;
पूर्ण;

क्रमागत Phase अणु
    idle,
    data_out,
    data_in,
    command_ph,
    status_ph,
    message_out,
    message_in
पूर्ण;

/* ================================================================== */

अटल व्योम
chip_init(पूर्णांक io_port)
अणु
	REG1(io_port);
	outb(0x01, io_port + PIO_STATUS);
	outb(0x00, io_port + PIO_FLAG);

	outb(C4_IMG, io_port + CONFIG4);	/* REG0(io_port); */
	outb(C3_IMG, io_port + CONFIG3);
	outb(C2_IMG, io_port + CONFIG2);
	outb(C1_IMG, io_port + CONFIG1);

	outb(0x05, io_port + CLKCONV);	/* घड़ी conversion factor */
	outb(0x9C, io_port + SRTIMOUT);	/* Selection समयout */
	outb(0x05, io_port + SYNCPRD);	/* Synchronous transfer period */
	outb(SYNC_MODE, io_port + SYNCOFF);	/* synchronous mode */  
पूर्ण

अटल व्योम
SYM53C500_पूर्णांक_host_reset(पूर्णांक io_port)
अणु
	outb(C4_IMG, io_port + CONFIG4);	/* REG0(io_port); */
	outb(CHIP_RESET, io_port + CMD_REG);
	outb(SCSI_NOP, io_port + CMD_REG);	/* required after reset */
	outb(SCSI_RESET, io_port + CMD_REG);
	chip_init(io_port);
पूर्ण

अटल __अंतरभूत__ पूर्णांक
SYM53C500_pio_पढ़ो(पूर्णांक fast_pio, पूर्णांक base, अचिन्हित अक्षर *request, अचिन्हित पूर्णांक reqlen)
अणु
	पूर्णांक i;
	पूर्णांक len;	/* current scsi fअगरo size */

	REG1(base);
	जबतक (reqlen) अणु
		i = inb(base + PIO_STATUS);
		/* VDEB(prपूर्णांकk("pio_status=%x\n", i)); */
		अगर (i & 0x80) 
			वापस 0;

		चयन (i & 0x1e) अणु
		शेष:
		हाल 0x10:	/* fअगरo empty */
			len = 0;
			अवरोध;
		हाल 0x0:
			len = 1;
			अवरोध; 
		हाल 0x8:	/* fअगरo 1/3 full */
			len = 42;
			अवरोध;
		हाल 0xc:	/* fअगरo 2/3 full */
			len = 84;
			अवरोध;
		हाल 0xe:	/* fअगरo full */
			len = 128;
			अवरोध;
		पूर्ण

		अगर ((i & 0x40) && len == 0) अणु /* fअगरo empty and पूर्णांकerrupt occurred */
			वापस 0;
		पूर्ण

		अगर (len) अणु
			अगर (len > reqlen) 
				len = reqlen;

			अगर (fast_pio && len > 3) अणु
				insl(base + PIO_FIFO, request, len >> 2);
				request += len & 0xfc; 
				reqlen -= len & 0xfc; 
			पूर्ण अन्यथा अणु
				जबतक (len--) अणु
					*request++ = inb(base + PIO_FIFO);
					reqlen--;
				पूर्ण
			पूर्ण 
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल __अंतरभूत__ पूर्णांक
SYM53C500_pio_ग_लिखो(पूर्णांक fast_pio, पूर्णांक base, अचिन्हित अक्षर *request, अचिन्हित पूर्णांक reqlen)
अणु
	पूर्णांक i = 0;
	पूर्णांक len;	/* current scsi fअगरo size */

	REG1(base);
	जबतक (reqlen && !(i & 0x40)) अणु
		i = inb(base + PIO_STATUS);
		/* VDEB(prपूर्णांकk("pio_status=%x\n", i)); */
		अगर (i & 0x80)	/* error */
			वापस 0;

		चयन (i & 0x1e) अणु
		हाल 0x10:
			len = 128;
			अवरोध;
		हाल 0x0:
			len = 84;
			अवरोध;
		हाल 0x8:
			len = 42;
			अवरोध;
		हाल 0xc:
			len = 1;
			अवरोध;
		शेष:
		हाल 0xe:
			len = 0;
			अवरोध;
		पूर्ण

		अगर (len) अणु
			अगर (len > reqlen)
				len = reqlen;

			अगर (fast_pio && len > 3) अणु
				outsl(base + PIO_FIFO, request, len >> 2);
				request += len & 0xfc;
				reqlen -= len & 0xfc;
			पूर्ण अन्यथा अणु
				जबतक (len--) अणु
					outb(*request++, base + PIO_FIFO);
					reqlen--;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल irqवापस_t
SYM53C500_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा Scsi_Host *dev = dev_id;
	DEB(अचिन्हित अक्षर fअगरo_size;)
	DEB(अचिन्हित अक्षर seq_reg;)
	अचिन्हित अक्षर status, पूर्णांक_reg;
	अचिन्हित अक्षर pio_status;
	पूर्णांक port_base = dev->io_port;
	काष्ठा sym53c500_data *data =
	    (काष्ठा sym53c500_data *)dev->hostdata;
	काष्ठा scsi_cmnd *curSC = data->current_SC;
	पूर्णांक fast_pio = data->fast_pio;

	spin_lock_irqsave(dev->host_lock, flags);

	VDEB(prपूर्णांकk("SYM53C500_intr called\n"));

	REG1(port_base);
	pio_status = inb(port_base + PIO_STATUS);
	REG0(port_base);
	status = inb(port_base + STAT_REG);
	DEB(seq_reg = inb(port_base + SEQ_REG));
	पूर्णांक_reg = inb(port_base + INT_REG);
	DEB(fअगरo_size = inb(port_base + FIFO_FLAGS) & 0x1f);

#अगर SYM53C500_DEBUG
	prपूर्णांकk("status=%02x, seq_reg=%02x, int_reg=%02x, fifo_size=%02x", 
	    status, seq_reg, पूर्णांक_reg, fअगरo_size);
	prपूर्णांकk(", pio=%02x\n", pio_status);
#पूर्ण_अगर /* SYM53C500_DEBUG */

	अगर (पूर्णांक_reg & 0x80) अणु	/* SCSI reset पूर्णांकr */
		DEB(prपूर्णांकk("SYM53C500: reset intr received\n"));
		curSC->result = DID_RESET << 16;
		जाओ idle_out;
	पूर्ण

	अगर (pio_status & 0x80) अणु
		prपूर्णांकk("SYM53C500: Warning: PIO error!\n");
		curSC->result = DID_ERROR << 16;
		जाओ idle_out;
	पूर्ण

	अगर (status & 0x20) अणु		/* Parity error */
		prपूर्णांकk("SYM53C500: Warning: parity error!\n");
		curSC->result = DID_PARITY << 16;
		जाओ idle_out;
	पूर्ण

	अगर (status & 0x40) अणु		/* Gross error */
		prपूर्णांकk("SYM53C500: Warning: gross error!\n");
		curSC->result = DID_ERROR << 16;
		जाओ idle_out;
	पूर्ण

	अगर (पूर्णांक_reg & 0x20) अणु		/* Disconnect */
		DEB(prपूर्णांकk("SYM53C500: disconnect intr received\n"));
		अगर (curSC->SCp.phase != message_in) अणु	/* Unexpected disconnect */
			curSC->result = DID_NO_CONNECT << 16;
		पूर्ण अन्यथा अणु	/* Command complete, वापस status and message */
			curSC->result = (curSC->SCp.Status & 0xff)
			    | ((curSC->SCp.Message & 0xff) << 8) | (DID_OK << 16);
		पूर्ण
		जाओ idle_out;
	पूर्ण

	चयन (status & 0x07) अणु	/* scsi phase */
	हाल 0x00:			/* DATA-OUT */
		अगर (पूर्णांक_reg & 0x10) अणु	/* Target requesting info transfer */
			काष्ठा scatterlist *sg;
			पूर्णांक i;

			curSC->SCp.phase = data_out;
			VDEB(prपूर्णांकk("SYM53C500: Data-Out phase\n"));
			outb(FLUSH_FIFO, port_base + CMD_REG);
			LOAD_DMA_COUNT(port_base, scsi_bufflen(curSC));	/* Max transfer size */
			outb(TRANSFER_INFO | DMA_OP, port_base + CMD_REG);

			scsi_क्रम_each_sg(curSC, sg, scsi_sg_count(curSC), i) अणु
				SYM53C500_pio_ग_लिखो(fast_pio, port_base,
				    sg_virt(sg), sg->length);
			पूर्ण
			REG0(port_base);
		पूर्ण
		अवरोध;

	हाल 0x01:		/* DATA-IN */
		अगर (पूर्णांक_reg & 0x10) अणु	/* Target requesting info transfer */
			काष्ठा scatterlist *sg;
			पूर्णांक i;

			curSC->SCp.phase = data_in;
			VDEB(prपूर्णांकk("SYM53C500: Data-In phase\n"));
			outb(FLUSH_FIFO, port_base + CMD_REG);
			LOAD_DMA_COUNT(port_base, scsi_bufflen(curSC));	/* Max transfer size */
			outb(TRANSFER_INFO | DMA_OP, port_base + CMD_REG);

			scsi_क्रम_each_sg(curSC, sg, scsi_sg_count(curSC), i) अणु
				SYM53C500_pio_पढ़ो(fast_pio, port_base,
					sg_virt(sg), sg->length);
			पूर्ण
			REG0(port_base);
		पूर्ण
		अवरोध;

	हाल 0x02:		/* COMMAND */
		curSC->SCp.phase = command_ph;
		prपूर्णांकk("SYM53C500: Warning: Unknown interrupt occurred in command phase!\n");
		अवरोध;

	हाल 0x03:		/* STATUS */
		curSC->SCp.phase = status_ph;
		VDEB(prपूर्णांकk("SYM53C500: Status phase\n"));
		outb(FLUSH_FIFO, port_base + CMD_REG);
		outb(INIT_CMD_COMPLETE, port_base + CMD_REG);
		अवरोध;

	हाल 0x04:		/* Reserved */
	हाल 0x05:		/* Reserved */
		prपूर्णांकk("SYM53C500: WARNING: Reserved phase!!!\n");
		अवरोध;

	हाल 0x06:		/* MESSAGE-OUT */
		DEB(prपूर्णांकk("SYM53C500: Message-Out phase\n"));
		curSC->SCp.phase = message_out;
		outb(SET_ATN, port_base + CMD_REG);	/* Reject the message */
		outb(MSG_ACCEPT, port_base + CMD_REG);
		अवरोध;

	हाल 0x07:		/* MESSAGE-IN */
		VDEB(prपूर्णांकk("SYM53C500: Message-In phase\n"));
		curSC->SCp.phase = message_in;

		curSC->SCp.Status = inb(port_base + SCSI_FIFO);
		curSC->SCp.Message = inb(port_base + SCSI_FIFO);

		VDEB(prपूर्णांकk("SCSI FIFO size=%d\n", inb(port_base + FIFO_FLAGS) & 0x1f));
		DEB(prपूर्णांकk("Status = %02x  Message = %02x\n", curSC->SCp.Status, curSC->SCp.Message));

		अगर (curSC->SCp.Message == SAVE_POINTERS || curSC->SCp.Message == DISCONNECT) अणु
			outb(SET_ATN, port_base + CMD_REG);	/* Reject message */
			DEB(prपूर्णांकk("Discarding SAVE_POINTERS message\n"));
		पूर्ण
		outb(MSG_ACCEPT, port_base + CMD_REG);
		अवरोध;
	पूर्ण
out:
	spin_unlock_irqrestore(dev->host_lock, flags);
	वापस IRQ_HANDLED;

idle_out:
	curSC->SCp.phase = idle;
	curSC->scsi_करोne(curSC);
	जाओ out;
पूर्ण

अटल व्योम
SYM53C500_release(काष्ठा pcmcia_device *link)
अणु
	काष्ठा scsi_info_t *info = link->priv;
	काष्ठा Scsi_Host *shost = info->host;

	dev_dbg(&link->dev, "SYM53C500_release\n");

	/*
	*  Do this beक्रमe releasing/मुक्तing resources.
	*/
	scsi_हटाओ_host(shost);

	/*
	*  Interrupts getting hosed on card removal.  Try
	*  the following code, mostly from qlogicfas.c.
	*/
	अगर (shost->irq)
		मुक्त_irq(shost->irq, shost);
	अगर (shost->io_port && shost->n_io_port)
		release_region(shost->io_port, shost->n_io_port);

	pcmcia_disable_device(link);

	scsi_host_put(shost);
पूर्ण /* SYM53C500_release */

अटल स्थिर अक्षर*
SYM53C500_info(काष्ठा Scsi_Host *SChost)
अणु
	अटल अक्षर info_msg[256];
	काष्ठा sym53c500_data *data =
	    (काष्ठा sym53c500_data *)SChost->hostdata;

	DEB(prपूर्णांकk("SYM53C500_info called\n"));
	(व्योम)snम_लिखो(info_msg, माप(info_msg),
	    "SYM53C500 at 0x%lx, IRQ %d, %s PIO mode.", 
	    SChost->io_port, SChost->irq, data->fast_pio ? "fast" : "slow");
	वापस (info_msg);
पूर्ण

अटल पूर्णांक 
SYM53C500_queue_lck(काष्ठा scsi_cmnd *SCpnt, व्योम (*करोne)(काष्ठा scsi_cmnd *))
अणु
	पूर्णांक i;
	पूर्णांक port_base = SCpnt->device->host->io_port;
	काष्ठा sym53c500_data *data =
	    (काष्ठा sym53c500_data *)SCpnt->device->host->hostdata;

	VDEB(prपूर्णांकk("SYM53C500_queue called\n"));

	DEB(prपूर्णांकk("cmd=%02x, cmd_len=%02x, target=%02x, lun=%02x, bufflen=%d\n", 
	    SCpnt->cmnd[0], SCpnt->cmd_len, SCpnt->device->id, 
		   (u8)SCpnt->device->lun,  scsi_bufflen(SCpnt)));

	VDEB(क्रम (i = 0; i < SCpnt->cmd_len; i++)
	    prपूर्णांकk("cmd[%d]=%02x  ", i, SCpnt->cmnd[i]));
	VDEB(prपूर्णांकk("\n"));

	data->current_SC = SCpnt;
	data->current_SC->scsi_करोne = करोne;
	data->current_SC->SCp.phase = command_ph;
	data->current_SC->SCp.Status = 0;
	data->current_SC->SCp.Message = 0;

	/* We are locked here alपढ़ोy by the mid layer */
	REG0(port_base);
	outb(scmd_id(SCpnt), port_base + DEST_ID);	/* set destination */
	outb(FLUSH_FIFO, port_base + CMD_REG);	/* reset the fअगरos */

	क्रम (i = 0; i < SCpnt->cmd_len; i++) अणु
		outb(SCpnt->cmnd[i], port_base + SCSI_FIFO);
	पूर्ण
	outb(SELECT_NO_ATN, port_base + CMD_REG);

	वापस 0;
पूर्ण

अटल DEF_SCSI_QCMD(SYM53C500_queue)

अटल पूर्णांक 
SYM53C500_host_reset(काष्ठा scsi_cmnd *SCpnt)
अणु
	पूर्णांक port_base = SCpnt->device->host->io_port;

	DEB(prपूर्णांकk("SYM53C500_host_reset called\n"));
	spin_lock_irq(SCpnt->device->host->host_lock);
	SYM53C500_पूर्णांक_host_reset(port_base);
	spin_unlock_irq(SCpnt->device->host->host_lock);

	वापस SUCCESS;
पूर्ण

अटल पूर्णांक 
SYM53C500_biosparm(काष्ठा scsi_device *disk,
    काष्ठा block_device *dev,
    sector_t capacity, पूर्णांक *info_array)
अणु
	पूर्णांक size;

	DEB(prपूर्णांकk("SYM53C500_biosparm called\n"));

	size = capacity;
	info_array[0] = 64;		/* heads */
	info_array[1] = 32;		/* sectors */
	info_array[2] = size >> 11;	/* cylinders */
	अगर (info_array[2] > 1024) अणु	/* big disk */
		info_array[0] = 255;
		info_array[1] = 63;
		info_array[2] = size / (255 * 63);
	पूर्ण
	वापस 0;
पूर्ण

अटल sमाप_प्रकार
SYM53C500_show_pio(काष्ठा device *dev, काष्ठा device_attribute *attr,
		   अक्षर *buf)
अणु
	काष्ठा Scsi_Host *SHp = class_to_shost(dev);
	काष्ठा sym53c500_data *data =
	    (काष्ठा sym53c500_data *)SHp->hostdata;

	वापस snम_लिखो(buf, 4, "%d\n", data->fast_pio);
पूर्ण

अटल sमाप_प्रकार
SYM53C500_store_pio(काष्ठा device *dev, काष्ठा device_attribute *attr,
		    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक pio;
	काष्ठा Scsi_Host *SHp = class_to_shost(dev);
	काष्ठा sym53c500_data *data =
	    (काष्ठा sym53c500_data *)SHp->hostdata;

	pio = simple_म_से_अदीर्घ(buf, शून्य, 0);
	अगर (pio == 0 || pio == 1) अणु
		data->fast_pio = pio;
		वापस count;
	पूर्ण
	अन्यथा
		वापस -EINVAL;
पूर्ण

/*
*  SCSI HBA device attributes we want to
*  make available via sysfs.
*/
अटल काष्ठा device_attribute SYM53C500_pio_attr = अणु
	.attr = अणु
		.name = "fast_pio",
		.mode = (S_IRUGO | S_IWUSR),
	पूर्ण,
	.show = SYM53C500_show_pio,
	.store = SYM53C500_store_pio,
पूर्ण;

अटल काष्ठा device_attribute *SYM53C500_shost_attrs[] = अणु
	&SYM53C500_pio_attr,
	शून्य,
पूर्ण;

/*
*  scsi_host_ढाँचा initializer
*/
अटल काष्ठा scsi_host_ढाँचा sym53c500_driver_ढाँचा = अणु
     .module			= THIS_MODULE,
     .name			= "SYM53C500",
     .info			= SYM53C500_info,
     .queuecommand		= SYM53C500_queue,
     .eh_host_reset_handler	= SYM53C500_host_reset,
     .bios_param		= SYM53C500_biosparm,
     .proc_name			= "SYM53C500",
     .can_queue			= 1,
     .this_id			= 7,
     .sg_tablesize		= 32,
     .shost_attrs		= SYM53C500_shost_attrs
पूर्ण;

अटल पूर्णांक SYM53C500_config_check(काष्ठा pcmcia_device *p_dev, व्योम *priv_data)
अणु
	p_dev->io_lines = 10;
	p_dev->resource[0]->flags &= ~IO_DATA_PATH_WIDTH;
	p_dev->resource[0]->flags |= IO_DATA_PATH_WIDTH_AUTO;

	अगर (p_dev->resource[0]->start == 0)
		वापस -ENODEV;

	वापस pcmcia_request_io(p_dev);
पूर्ण

अटल पूर्णांक
SYM53C500_config(काष्ठा pcmcia_device *link)
अणु
	काष्ठा scsi_info_t *info = link->priv;
	पूर्णांक ret;
	पूर्णांक irq_level, port_base;
	काष्ठा Scsi_Host *host;
	काष्ठा scsi_host_ढाँचा *tpnt = &sym53c500_driver_ढाँचा;
	काष्ठा sym53c500_data *data;

	dev_dbg(&link->dev, "SYM53C500_config\n");

	info->manf_id = link->manf_id;

	ret = pcmcia_loop_config(link, SYM53C500_config_check, शून्य);
	अगर (ret)
		जाओ failed;

	अगर (!link->irq)
		जाओ failed;

	ret = pcmcia_enable_device(link);
	अगर (ret)
		जाओ failed;

	/*
	*  That's the trouble with copying liberally from another driver.
	*  Some things probably aren't relevant, and I suspect this entire
	*  section dealing with manufacturer IDs can be scrapped.	--rct
	*/
	अगर ((info->manf_id == MANFID_MACNICA) ||
	    (info->manf_id == MANFID_PIONEER) ||
	    (info->manf_id == 0x0098)) अणु
		/* set ATAcmd */
		outb(0xb4, link->resource[0]->start + 0xd);
		outb(0x24, link->resource[0]->start + 0x9);
		outb(0x04, link->resource[0]->start + 0xd);
	पूर्ण

	/*
	*  irq_level == 0 implies tpnt->can_queue == 0, which
	*  is not supported in 2.6.  Thus, only irq_level > 0
	*  will be allowed.
	*
	*  Possible port_base values are as follows:
	*
	*	0x130, 0x230, 0x280, 0x290,
	*	0x320, 0x330, 0x340, 0x350
	*/
	port_base = link->resource[0]->start;
	irq_level = link->irq;

	DEB(prपूर्णांकk("SYM53C500: port_base=0x%x, irq=%d, fast_pio=%d\n",
	    port_base, irq_level, USE_FAST_PIO);)

	chip_init(port_base);

	host = scsi_host_alloc(tpnt, माप(काष्ठा sym53c500_data));
	अगर (!host) अणु
		prपूर्णांकk("SYM53C500: Unable to register host, giving up.\n");
		जाओ err_release;
	पूर्ण

	data = (काष्ठा sym53c500_data *)host->hostdata;

	अगर (irq_level > 0) अणु
		अगर (request_irq(irq_level, SYM53C500_पूर्णांकr, IRQF_SHARED, "SYM53C500", host)) अणु
			prपूर्णांकk("SYM53C500: unable to allocate IRQ %d\n", irq_level);
			जाओ err_मुक्त_scsi;
		पूर्ण
		DEB(prपूर्णांकk("SYM53C500: allocated IRQ %d\n", irq_level));
	पूर्ण अन्यथा अगर (irq_level == 0) अणु
		DEB(prपूर्णांकk("SYM53C500: No interrupts detected\n"));
		जाओ err_मुक्त_scsi;
	पूर्ण अन्यथा अणु
		DEB(prपूर्णांकk("SYM53C500: Shouldn't get here!\n"));
		जाओ err_मुक्त_scsi;
	पूर्ण

	host->unique_id = port_base;
	host->irq = irq_level;
	host->io_port = port_base;
	host->n_io_port = 0x10;
	host->dma_channel = -1;

	/*
	*  Note fast_pio is set to USE_FAST_PIO by
	*  शेष, but can be changed via "sysfs".
	*/
	data->fast_pio = USE_FAST_PIO;

	info->host = host;

	अगर (scsi_add_host(host, शून्य))
		जाओ err_मुक्त_irq;

	scsi_scan_host(host);

	वापस 0;

err_मुक्त_irq:
	मुक्त_irq(irq_level, host);
err_मुक्त_scsi:
	scsi_host_put(host);
err_release:
	release_region(port_base, 0x10);
	prपूर्णांकk(KERN_INFO "sym53c500_cs: no SCSI devices found\n");
	वापस -ENODEV;

failed:
	SYM53C500_release(link);
	वापस -ENODEV;
पूर्ण /* SYM53C500_config */

अटल पूर्णांक sym53c500_resume(काष्ठा pcmcia_device *link)
अणु
	काष्ठा scsi_info_t *info = link->priv;

	/* See earlier comment about manufacturer IDs. */
	अगर ((info->manf_id == MANFID_MACNICA) ||
	    (info->manf_id == MANFID_PIONEER) ||
	    (info->manf_id == 0x0098)) अणु
		outb(0x80, link->resource[0]->start + 0xd);
		outb(0x24, link->resource[0]->start + 0x9);
		outb(0x04, link->resource[0]->start + 0xd);
	पूर्ण
	/*
	 *  If things करोn't work after a "resume",
	 *  this is a good place to start looking.
	 */
	SYM53C500_पूर्णांक_host_reset(link->resource[0]->start);

	वापस 0;
पूर्ण

अटल व्योम
SYM53C500_detach(काष्ठा pcmcia_device *link)
अणु
	dev_dbg(&link->dev, "SYM53C500_detach\n");

	SYM53C500_release(link);

	kमुक्त(link->priv);
	link->priv = शून्य;
पूर्ण /* SYM53C500_detach */

अटल पूर्णांक
SYM53C500_probe(काष्ठा pcmcia_device *link)
अणु
	काष्ठा scsi_info_t *info;

	dev_dbg(&link->dev, "SYM53C500_attach()\n");

	/* Create new SCSI device */
	info = kzalloc(माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;
	info->p_dev = link;
	link->priv = info;
	link->config_flags |= CONF_ENABLE_IRQ | CONF_AUTO_SET_IO;

	वापस SYM53C500_config(link);
पूर्ण /* SYM53C500_attach */

MODULE_AUTHOR("Bob Tracy <rct@frus.com>");
MODULE_DESCRIPTION("SYM53C500 PCMCIA SCSI driver");
MODULE_LICENSE("GPL");

अटल स्थिर काष्ठा pcmcia_device_id sym53c500_ids[] = अणु
	PCMCIA_DEVICE_PROD_ID12("BASICS by New Media Corporation", "SCSI Sym53C500", 0x23c78a9d, 0x0099e7f7),
	PCMCIA_DEVICE_PROD_ID12("New Media Corporation", "SCSI Bus Toaster Sym53C500", 0x085a850b, 0x45432eb8),
	PCMCIA_DEVICE_PROD_ID2("SCSI9000", 0x21648f44),
	PCMCIA_DEVICE_शून्य,
पूर्ण;
MODULE_DEVICE_TABLE(pcmcia, sym53c500_ids);

अटल काष्ठा pcmcia_driver sym53c500_cs_driver = अणु
	.owner		= THIS_MODULE,
	.name		= "sym53c500_cs",
	.probe		= SYM53C500_probe,
	.हटाओ		= SYM53C500_detach,
	.id_table       = sym53c500_ids,
	.resume		= sym53c500_resume,
पूर्ण;
module_pcmcia_driver(sym53c500_cs_driver);
