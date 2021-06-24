<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* imm.c   --  low level driver क्रम the IOMEGA MatchMaker
 * parallel port SCSI host adapter.
 * 
 * (The IMM is the embedded controller in the ZIP Plus drive.)
 * 
 * My unofficial company acronym list is 21 pages दीर्घ:
 *      FLA:    Four letter acronym with built in facility क्रम
 *              future expansion to five letters.
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/parport.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/पन.स>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>

/* The following #घोषणा is to aव्योम a clash with hosts.c */
#घोषणा IMM_PROBE_SPP   0x0001
#घोषणा IMM_PROBE_PS2   0x0002
#घोषणा IMM_PROBE_ECR   0x0010
#घोषणा IMM_PROBE_EPP17 0x0100
#घोषणा IMM_PROBE_EPP19 0x0200


प्रकार काष्ठा अणु
	काष्ठा pardevice *dev;	/* Parport device entry         */
	पूर्णांक base;		/* Actual port address          */
	पूर्णांक base_hi;		/* Hi Base address क्रम ECP-ISA chipset */
	पूर्णांक mode;		/* Transfer mode                */
	काष्ठा scsi_cmnd *cur_cmd;	/* Current queued command       */
	काष्ठा delayed_work imm_tq;	/* Polling पूर्णांकerrupt stuff       */
	अचिन्हित दीर्घ jstart;	/* Jअगरfies at start             */
	अचिन्हित failed:1;	/* Failure flag                 */
	अचिन्हित dp:1;		/* Data phase present           */
	अचिन्हित rd:1;		/* Read data in data phase      */
	अचिन्हित wanted:1;	/* Parport sharing busy flag    */
	अचिन्हित पूर्णांक dev_no;	/* Device number		*/
	रुको_queue_head_t *रुकोing;
	काष्ठा Scsi_Host *host;
	काष्ठा list_head list;
पूर्ण imm_काष्ठा;

अटल व्योम imm_reset_pulse(अचिन्हित पूर्णांक base);
अटल पूर्णांक device_check(imm_काष्ठा *dev);

#समावेश "imm.h"

अटल अंतरभूत imm_काष्ठा *imm_dev(काष्ठा Scsi_Host *host)
अणु
	वापस *(imm_काष्ठा **)&host->hostdata;
पूर्ण

अटल DEFINE_SPINLOCK(arbitration_lock);

अटल व्योम got_it(imm_काष्ठा *dev)
अणु
	dev->base = dev->dev->port->base;
	अगर (dev->cur_cmd)
		dev->cur_cmd->SCp.phase = 1;
	अन्यथा
		wake_up(dev->रुकोing);
पूर्ण

अटल व्योम imm_wakeup(व्योम *ref)
अणु
	imm_काष्ठा *dev = (imm_काष्ठा *) ref;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&arbitration_lock, flags);
	अगर (dev->wanted) अणु
		अगर (parport_claim(dev->dev) == 0) अणु
			got_it(dev);
			dev->wanted = 0;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&arbitration_lock, flags);
पूर्ण

अटल पूर्णांक imm_pb_claim(imm_काष्ठा *dev)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक res = 1;
	spin_lock_irqsave(&arbitration_lock, flags);
	अगर (parport_claim(dev->dev) == 0) अणु
		got_it(dev);
		res = 0;
	पूर्ण
	dev->wanted = res;
	spin_unlock_irqrestore(&arbitration_lock, flags);
	वापस res;
पूर्ण

अटल व्योम imm_pb_dismiss(imm_काष्ठा *dev)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक wanted;
	spin_lock_irqsave(&arbitration_lock, flags);
	wanted = dev->wanted;
	dev->wanted = 0;
	spin_unlock_irqrestore(&arbitration_lock, flags);
	अगर (!wanted)
		parport_release(dev->dev);
पूर्ण

अटल अंतरभूत व्योम imm_pb_release(imm_काष्ठा *dev)
अणु
	parport_release(dev->dev);
पूर्ण

/* This is to give the imm driver a way to modअगरy the timings (and other
 * parameters) by writing to the /proc/scsi/imm/0 file.
 * Very simple method really... (Too simple, no error checking :( )
 * Reason: Kernel hackers HATE having to unload and reload modules क्रम
 * testing...
 * Also gives a method to use a script to obtain optimum timings (TODO)
 */
अटल पूर्णांक imm_ग_लिखो_info(काष्ठा Scsi_Host *host, अक्षर *buffer, पूर्णांक length)
अणु
	imm_काष्ठा *dev = imm_dev(host);

	अगर ((length > 5) && (म_भेदन(buffer, "mode=", 5) == 0)) अणु
		dev->mode = simple_म_से_अदीर्घ(buffer + 5, शून्य, 0);
		वापस length;
	पूर्ण
	prपूर्णांकk("imm /proc: invalid variable\n");
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक imm_show_info(काष्ठा seq_file *m, काष्ठा Scsi_Host *host)
अणु
	imm_काष्ठा *dev = imm_dev(host);

	seq_म_लिखो(m, "Version : %s\n", IMM_VERSION);
	seq_म_लिखो(m, "Parport : %s\n", dev->dev->port->name);
	seq_म_लिखो(m, "Mode    : %s\n", IMM_MODE_STRING[dev->mode]);
	वापस 0;
पूर्ण

#अगर IMM_DEBUG > 0
#घोषणा imm_fail(x,y) prपूर्णांकk("imm: imm_fail(%i) from %s at line %d\n",\
	   y, __func__, __LINE__); imm_fail_func(x,y);
अटल अंतरभूत व्योम
imm_fail_func(imm_काष्ठा *dev, पूर्णांक error_code)
#अन्यथा
अटल अंतरभूत व्योम
imm_fail(imm_काष्ठा *dev, पूर्णांक error_code)
#पूर्ण_अगर
अणु
	/* If we fail a device then we trash status / message bytes */
	अगर (dev->cur_cmd) अणु
		dev->cur_cmd->result = error_code << 16;
		dev->failed = 1;
	पूर्ण
पूर्ण

/*
 * Wait क्रम the high bit to be set.
 * 
 * In principle, this could be tied to an पूर्णांकerrupt, but the adapter
 * करोesn't appear to be deचिन्हित to support पूर्णांकerrupts.  We spin on
 * the 0x80 पढ़ोy bit. 
 */
अटल अचिन्हित अक्षर imm_रुको(imm_काष्ठा *dev)
अणु
	पूर्णांक k;
	अचिन्हित लघु ppb = dev->base;
	अचिन्हित अक्षर r;

	w_ctr(ppb, 0x0c);

	k = IMM_SPIN_TMO;
	करो अणु
		r = r_str(ppb);
		k--;
		udelay(1);
	पूर्ण
	जबतक (!(r & 0x80) && (k));

	/*
	 * STR रेजिस्टर (LPT base+1) to SCSI mapping:
	 *
	 * STR      imm     imm
	 * ===================================
	 * 0x80     S_REQ   S_REQ
	 * 0x40     !S_BSY  (????)
	 * 0x20     !S_CD   !S_CD
	 * 0x10     !S_IO   !S_IO
	 * 0x08     (????)  !S_BSY
	 *
	 * imm      imm     meaning
	 * ==================================
	 * 0xf0     0xb8    Bit mask
	 * 0xc0     0x88    ZIP wants more data
	 * 0xd0     0x98    ZIP wants to send more data
	 * 0xe0     0xa8    ZIP is expecting SCSI command data
	 * 0xf0     0xb8    end of transfer, ZIP is sending status
	 */
	w_ctr(ppb, 0x04);
	अगर (k)
		वापस (r & 0xb8);

	/* Counter expired - Time out occurred */
	imm_fail(dev, DID_TIME_OUT);
	prपूर्णांकk("imm timeout in imm_wait\n");
	वापस 0;		/* command समयd out */
पूर्ण

अटल पूर्णांक imm_negotiate(imm_काष्ठा * पंचांगp)
अणु
	/*
	 * The following is supposedly the IEEE 1284-1994 negotiate
	 * sequence. I have yet to obtain a copy of the above standard
	 * so this is a bit of a guess...
	 *
	 * A fair chunk of this is based on the Linux parport implementation
	 * of IEEE 1284.
	 *
	 * Return 0 अगर data available
	 *        1 अगर no data available
	 */

	अचिन्हित लघु base = पंचांगp->base;
	अचिन्हित अक्षर a, mode;

	चयन (पंचांगp->mode) अणु
	हाल IMM_NIBBLE:
		mode = 0x00;
		अवरोध;
	हाल IMM_PS2:
		mode = 0x01;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	w_ctr(base, 0x04);
	udelay(5);
	w_dtr(base, mode);
	udelay(100);
	w_ctr(base, 0x06);
	udelay(5);
	a = (r_str(base) & 0x20) ? 0 : 1;
	udelay(5);
	w_ctr(base, 0x07);
	udelay(5);
	w_ctr(base, 0x06);

	अगर (a) अणु
		prपूर्णांकk
		    ("IMM: IEEE1284 negotiate indicates no data available.\n");
		imm_fail(पंचांगp, DID_ERROR);
	पूर्ण
	वापस a;
पूर्ण

/* 
 * Clear EPP समयout bit. 
 */
अटल अंतरभूत व्योम epp_reset(अचिन्हित लघु ppb)
अणु
	पूर्णांक i;

	i = r_str(ppb);
	w_str(ppb, i);
	w_str(ppb, i & 0xfe);
पूर्ण

/* 
 * Wait क्रम empty ECP fअगरo (अगर we are in ECP fअगरo mode only)
 */
अटल अंतरभूत व्योम ecp_sync(imm_काष्ठा *dev)
अणु
	पूर्णांक i, ppb_hi = dev->base_hi;

	अगर (ppb_hi == 0)
		वापस;

	अगर ((r_ecr(ppb_hi) & 0xe0) == 0x60) अणु	/* mode 011 == ECP fअगरo mode */
		क्रम (i = 0; i < 100; i++) अणु
			अगर (r_ecr(ppb_hi) & 0x01)
				वापस;
			udelay(5);
		पूर्ण
		prपूर्णांकk("imm: ECP sync failed as data still present in FIFO.\n");
	पूर्ण
पूर्ण

अटल पूर्णांक imm_byte_out(अचिन्हित लघु base, स्थिर अक्षर *buffer, पूर्णांक len)
अणु
	पूर्णांक i;

	w_ctr(base, 0x4);	/* apparently a sane mode */
	क्रम (i = len >> 1; i; i--) अणु
		w_dtr(base, *buffer++);
		w_ctr(base, 0x5);	/* Drop STROBE low */
		w_dtr(base, *buffer++);
		w_ctr(base, 0x0);	/* STROBE high + INIT low */
	पूर्ण
	w_ctr(base, 0x4);	/* apparently a sane mode */
	वापस 1;		/* All went well - we hope! */
पूर्ण

अटल पूर्णांक imm_nibble_in(अचिन्हित लघु base, अक्षर *buffer, पूर्णांक len)
अणु
	अचिन्हित अक्षर l;
	पूर्णांक i;

	/*
	 * The following is based on करोcumented timing संकेतs
	 */
	w_ctr(base, 0x4);
	क्रम (i = len; i; i--) अणु
		w_ctr(base, 0x6);
		l = (r_str(base) & 0xf0) >> 4;
		w_ctr(base, 0x5);
		*buffer++ = (r_str(base) & 0xf0) | l;
		w_ctr(base, 0x4);
	पूर्ण
	वापस 1;		/* All went well - we hope! */
पूर्ण

अटल पूर्णांक imm_byte_in(अचिन्हित लघु base, अक्षर *buffer, पूर्णांक len)
अणु
	पूर्णांक i;

	/*
	 * The following is based on करोcumented timing संकेतs
	 */
	w_ctr(base, 0x4);
	क्रम (i = len; i; i--) अणु
		w_ctr(base, 0x26);
		*buffer++ = r_dtr(base);
		w_ctr(base, 0x25);
	पूर्ण
	वापस 1;		/* All went well - we hope! */
पूर्ण

अटल पूर्णांक imm_out(imm_काष्ठा *dev, अक्षर *buffer, पूर्णांक len)
अणु
	अचिन्हित लघु ppb = dev->base;
	पूर्णांक r = imm_रुको(dev);

	/*
	 * Make sure that:
	 * a) the SCSI bus is BUSY (device still listening)
	 * b) the device is listening
	 */
	अगर ((r & 0x18) != 0x08) अणु
		imm_fail(dev, DID_ERROR);
		prपूर्णांकk("IMM: returned SCSI status %2x\n", r);
		वापस 0;
	पूर्ण
	चयन (dev->mode) अणु
	हाल IMM_EPP_32:
	हाल IMM_EPP_16:
	हाल IMM_EPP_8:
		epp_reset(ppb);
		w_ctr(ppb, 0x4);
#अगर_घोषित CONFIG_SCSI_IZIP_EPP16
		अगर (!(((दीर्घ) buffer | len) & 0x01))
			outsw(ppb + 4, buffer, len >> 1);
#अन्यथा
		अगर (!(((दीर्घ) buffer | len) & 0x03))
			outsl(ppb + 4, buffer, len >> 2);
#पूर्ण_अगर
		अन्यथा
			outsb(ppb + 4, buffer, len);
		w_ctr(ppb, 0xc);
		r = !(r_str(ppb) & 0x01);
		w_ctr(ppb, 0xc);
		ecp_sync(dev);
		अवरोध;

	हाल IMM_NIBBLE:
	हाल IMM_PS2:
		/* 8 bit output, with a loop */
		r = imm_byte_out(ppb, buffer, len);
		अवरोध;

	शेष:
		prपूर्णांकk("IMM: bug in imm_out()\n");
		r = 0;
	पूर्ण
	वापस r;
पूर्ण

अटल पूर्णांक imm_in(imm_काष्ठा *dev, अक्षर *buffer, पूर्णांक len)
अणु
	अचिन्हित लघु ppb = dev->base;
	पूर्णांक r = imm_रुको(dev);

	/*
	 * Make sure that:
	 * a) the SCSI bus is BUSY (device still listening)
	 * b) the device is sending data
	 */
	अगर ((r & 0x18) != 0x18) अणु
		imm_fail(dev, DID_ERROR);
		वापस 0;
	पूर्ण
	चयन (dev->mode) अणु
	हाल IMM_NIBBLE:
		/* 4 bit input, with a loop */
		r = imm_nibble_in(ppb, buffer, len);
		w_ctr(ppb, 0xc);
		अवरोध;

	हाल IMM_PS2:
		/* 8 bit input, with a loop */
		r = imm_byte_in(ppb, buffer, len);
		w_ctr(ppb, 0xc);
		अवरोध;

	हाल IMM_EPP_32:
	हाल IMM_EPP_16:
	हाल IMM_EPP_8:
		epp_reset(ppb);
		w_ctr(ppb, 0x24);
#अगर_घोषित CONFIG_SCSI_IZIP_EPP16
		अगर (!(((दीर्घ) buffer | len) & 0x01))
			insw(ppb + 4, buffer, len >> 1);
#अन्यथा
		अगर (!(((दीर्घ) buffer | len) & 0x03))
			insl(ppb + 4, buffer, len >> 2);
#पूर्ण_अगर
		अन्यथा
			insb(ppb + 4, buffer, len);
		w_ctr(ppb, 0x2c);
		r = !(r_str(ppb) & 0x01);
		w_ctr(ppb, 0x2c);
		ecp_sync(dev);
		अवरोध;

	शेष:
		prपूर्णांकk("IMM: bug in imm_ins()\n");
		r = 0;
		अवरोध;
	पूर्ण
	वापस r;
पूर्ण

अटल पूर्णांक imm_cpp(अचिन्हित लघु ppb, अचिन्हित अक्षर b)
अणु
	/*
	 * Comments on udelay values refer to the
	 * Command Packet Protocol (CPP) timing diagram.
	 */

	अचिन्हित अक्षर s1, s2, s3;
	w_ctr(ppb, 0x0c);
	udelay(2);		/* 1 usec - infinite */
	w_dtr(ppb, 0xaa);
	udelay(10);		/* 7 usec - infinite */
	w_dtr(ppb, 0x55);
	udelay(10);		/* 7 usec - infinite */
	w_dtr(ppb, 0x00);
	udelay(10);		/* 7 usec - infinite */
	w_dtr(ppb, 0xff);
	udelay(10);		/* 7 usec - infinite */
	s1 = r_str(ppb) & 0xb8;
	w_dtr(ppb, 0x87);
	udelay(10);		/* 7 usec - infinite */
	s2 = r_str(ppb) & 0xb8;
	w_dtr(ppb, 0x78);
	udelay(10);		/* 7 usec - infinite */
	s3 = r_str(ppb) & 0x38;
	/*
	 * Values क्रम b are:
	 * 0000 00aa    Assign address aa to current device
	 * 0010 00aa    Select device aa in EPP Winbond mode
	 * 0010 10aa    Select device aa in EPP mode
	 * 0011 xxxx    Deselect all devices
	 * 0110 00aa    Test device aa
	 * 1101 00aa    Select device aa in ECP mode
	 * 1110 00aa    Select device aa in Compatible mode
	 */
	w_dtr(ppb, b);
	udelay(2);		/* 1 usec - infinite */
	w_ctr(ppb, 0x0c);
	udelay(10);		/* 7 usec - infinite */
	w_ctr(ppb, 0x0d);
	udelay(2);		/* 1 usec - infinite */
	w_ctr(ppb, 0x0c);
	udelay(10);		/* 7 usec - infinite */
	w_dtr(ppb, 0xff);
	udelay(10);		/* 7 usec - infinite */

	/*
	 * The following table is electrical pin values.
	 * (BSY is inverted at the CTR रेजिस्टर)
	 *
	 *       BSY  ACK  POut SEL  Fault
	 * S1    0    X    1    1    1
	 * S2    1    X    0    1    1
	 * S3    L    X    1    1    S
	 *
	 * L => Last device in chain
	 * S => Selected
	 *
	 * Observered values क्रम S1,S2,S3 are:
	 * Disconnect => f8/58/78
	 * Connect    => f8/58/70
	 */
	अगर ((s1 == 0xb8) && (s2 == 0x18) && (s3 == 0x30))
		वापस 1;	/* Connected */
	अगर ((s1 == 0xb8) && (s2 == 0x18) && (s3 == 0x38))
		वापस 0;	/* Disconnected */

	वापस -1;		/* No device present */
पूर्ण

अटल अंतरभूत पूर्णांक imm_connect(imm_काष्ठा *dev, पूर्णांक flag)
अणु
	अचिन्हित लघु ppb = dev->base;

	imm_cpp(ppb, 0xe0);	/* Select device 0 in compatible mode */
	imm_cpp(ppb, 0x30);	/* Disconnect all devices */

	अगर ((dev->mode == IMM_EPP_8) ||
	    (dev->mode == IMM_EPP_16) ||
	    (dev->mode == IMM_EPP_32))
		वापस imm_cpp(ppb, 0x28);	/* Select device 0 in EPP mode */
	वापस imm_cpp(ppb, 0xe0);	/* Select device 0 in compatible mode */
पूर्ण

अटल व्योम imm_disconnect(imm_काष्ठा *dev)
अणु
	imm_cpp(dev->base, 0x30);	/* Disconnect all devices */
पूर्ण

अटल पूर्णांक imm_select(imm_काष्ठा *dev, पूर्णांक target)
अणु
	पूर्णांक k;
	अचिन्हित लघु ppb = dev->base;

	/*
	 * Firstly we want to make sure there is nothing
	 * holding onto the SCSI bus.
	 */
	w_ctr(ppb, 0xc);

	k = IMM_SELECT_TMO;
	करो अणु
		k--;
	पूर्ण जबतक ((r_str(ppb) & 0x08) && (k));

	अगर (!k)
		वापस 0;

	/*
	 * Now निश्चित the SCSI ID (HOST and TARGET) on the data bus
	 */
	w_ctr(ppb, 0x4);
	w_dtr(ppb, 0x80 | (1 << target));
	udelay(1);

	/*
	 * Deनिश्चित SELIN first followed by STROBE
	 */
	w_ctr(ppb, 0xc);
	w_ctr(ppb, 0xd);

	/*
	 * ACK should drop low जबतक SELIN is deनिश्चितed.
	 * FAULT should drop low when the SCSI device latches the bus.
	 */
	k = IMM_SELECT_TMO;
	करो अणु
		k--;
	पूर्ण
	जबतक (!(r_str(ppb) & 0x08) && (k));

	/*
	 * Place the पूर्णांकerface back पूर्णांकo a sane state (status mode)
	 */
	w_ctr(ppb, 0xc);
	वापस (k) ? 1 : 0;
पूर्ण

अटल पूर्णांक imm_init(imm_काष्ठा *dev)
अणु
	अगर (imm_connect(dev, 0) != 1)
		वापस -EIO;
	imm_reset_pulse(dev->base);
	mdelay(1);	/* Delay to allow devices to settle */
	imm_disconnect(dev);
	mdelay(1);	/* Another delay to allow devices to settle */
	वापस device_check(dev);
पूर्ण

अटल अंतरभूत पूर्णांक imm_send_command(काष्ठा scsi_cmnd *cmd)
अणु
	imm_काष्ठा *dev = imm_dev(cmd->device->host);
	पूर्णांक k;

	/* NOTE: IMM uses byte pairs */
	क्रम (k = 0; k < cmd->cmd_len; k += 2)
		अगर (!imm_out(dev, &cmd->cmnd[k], 2))
			वापस 0;
	वापस 1;
पूर्ण

/*
 * The bulk flag enables some optimisations in the data transfer loops,
 * it should be true क्रम any command that transfers data in पूर्णांकegral
 * numbers of sectors.
 * 
 * The driver appears to reमुख्य stable अगर we speed up the parallel port
 * i/o in this function, but not अन्यथाwhere.
 */
अटल पूर्णांक imm_completion(काष्ठा scsi_cmnd *cmd)
अणु
	/* Return codes:
	 * -1     Error
	 *  0     Told to schedule
	 *  1     Finished data transfer
	 */
	imm_काष्ठा *dev = imm_dev(cmd->device->host);
	अचिन्हित लघु ppb = dev->base;
	अचिन्हित दीर्घ start_jअगरfies = jअगरfies;

	अचिन्हित अक्षर r, v;
	पूर्णांक fast, bulk, status;

	v = cmd->cmnd[0];
	bulk = ((v == READ_6) ||
		(v == READ_10) || (v == WRITE_6) || (v == WRITE_10));

	/*
	 * We only get here अगर the drive is पढ़ोy to comunicate,
	 * hence no need क्रम a full imm_रुको.
	 */
	w_ctr(ppb, 0x0c);
	r = (r_str(ppb) & 0xb8);

	/*
	 * जबतक (device is not पढ़ोy to send status byte)
	 *     loop;
	 */
	जबतक (r != (अचिन्हित अक्षर) 0xb8) अणु
		/*
		 * If we have been running क्रम more than a full समयr tick
		 * then take a rest.
		 */
		अगर (समय_after(jअगरfies, start_jअगरfies + 1))
			वापस 0;

		/*
		 * FAIL अगर:
		 * a) Drive status is screwy (!पढ़ोy && !present)
		 * b) Drive is requesting/sending more data than expected
		 */
		अगर (((r & 0x88) != 0x88) || (cmd->SCp.this_residual <= 0)) अणु
			imm_fail(dev, DID_ERROR);
			वापस -1;	/* ERROR_RETURN */
		पूर्ण
		/* determine अगर we should use burst I/O */
		अगर (dev->rd == 0) अणु
			fast = (bulk
				&& (cmd->SCp.this_residual >=
				    IMM_BURST_SIZE)) ? IMM_BURST_SIZE : 2;
			status = imm_out(dev, cmd->SCp.ptr, fast);
		पूर्ण अन्यथा अणु
			fast = (bulk
				&& (cmd->SCp.this_residual >=
				    IMM_BURST_SIZE)) ? IMM_BURST_SIZE : 1;
			status = imm_in(dev, cmd->SCp.ptr, fast);
		पूर्ण

		cmd->SCp.ptr += fast;
		cmd->SCp.this_residual -= fast;

		अगर (!status) अणु
			imm_fail(dev, DID_BUS_BUSY);
			वापस -1;	/* ERROR_RETURN */
		पूर्ण
		अगर (cmd->SCp.buffer && !cmd->SCp.this_residual) अणु
			/* अगर scatter/gather, advance to the next segment */
			अगर (cmd->SCp.buffers_residual--) अणु
				cmd->SCp.buffer = sg_next(cmd->SCp.buffer);
				cmd->SCp.this_residual =
				    cmd->SCp.buffer->length;
				cmd->SCp.ptr = sg_virt(cmd->SCp.buffer);

				/*
				 * Make sure that we transfer even number of bytes
				 * otherwise it makes imm_byte_out() messy.
				 */
				अगर (cmd->SCp.this_residual & 0x01)
					cmd->SCp.this_residual++;
			पूर्ण
		पूर्ण
		/* Now check to see अगर the drive is पढ़ोy to comunicate */
		w_ctr(ppb, 0x0c);
		r = (r_str(ppb) & 0xb8);

		/* If not, drop back करोwn to the scheduler and रुको a समयr tick */
		अगर (!(r & 0x80))
			वापस 0;
	पूर्ण
	वापस 1;		/* FINISH_RETURN */
पूर्ण

/*
 * Since the IMM itself करोesn't generate पूर्णांकerrupts, we use
 * the scheduler's task queue to generate a stream of call-backs and
 * complete the request when the drive is पढ़ोy.
 */
अटल व्योम imm_पूर्णांकerrupt(काष्ठा work_काष्ठा *work)
अणु
	imm_काष्ठा *dev = container_of(work, imm_काष्ठा, imm_tq.work);
	काष्ठा scsi_cmnd *cmd = dev->cur_cmd;
	काष्ठा Scsi_Host *host = cmd->device->host;
	अचिन्हित दीर्घ flags;

	अगर (imm_engine(dev, cmd)) अणु
		schedule_delayed_work(&dev->imm_tq, 1);
		वापस;
	पूर्ण
	/* Command must of completed hence it is safe to let go... */
#अगर IMM_DEBUG > 0
	चयन ((cmd->result >> 16) & 0xff) अणु
	हाल DID_OK:
		अवरोध;
	हाल DID_NO_CONNECT:
		prपूर्णांकk("imm: no device at SCSI ID %i\n", cmd->device->id);
		अवरोध;
	हाल DID_BUS_BUSY:
		prपूर्णांकk("imm: BUS BUSY - EPP timeout detected\n");
		अवरोध;
	हाल DID_TIME_OUT:
		prपूर्णांकk("imm: unknown timeout\n");
		अवरोध;
	हाल DID_ABORT:
		prपूर्णांकk("imm: told to abort\n");
		अवरोध;
	हाल DID_PARITY:
		prपूर्णांकk("imm: parity error (???)\n");
		अवरोध;
	हाल DID_ERROR:
		prपूर्णांकk("imm: internal driver error\n");
		अवरोध;
	हाल DID_RESET:
		prपूर्णांकk("imm: told to reset device\n");
		अवरोध;
	हाल DID_BAD_INTR:
		prपूर्णांकk("imm: bad interrupt (???)\n");
		अवरोध;
	शेष:
		prपूर्णांकk("imm: bad return code (%02x)\n",
		       (cmd->result >> 16) & 0xff);
	पूर्ण
#पूर्ण_अगर

	अगर (cmd->SCp.phase > 1)
		imm_disconnect(dev);

	imm_pb_dismiss(dev);

	spin_lock_irqsave(host->host_lock, flags);
	dev->cur_cmd = शून्य;
	cmd->scsi_करोne(cmd);
	spin_unlock_irqrestore(host->host_lock, flags);
	वापस;
पूर्ण

अटल पूर्णांक imm_engine(imm_काष्ठा *dev, काष्ठा scsi_cmnd *cmd)
अणु
	अचिन्हित लघु ppb = dev->base;
	अचिन्हित अक्षर l = 0, h = 0;
	पूर्णांक retv, x;

	/* First check क्रम any errors that may have occurred
	 * Here we check क्रम पूर्णांकernal errors
	 */
	अगर (dev->failed)
		वापस 0;

	चयन (cmd->SCp.phase) अणु
	हाल 0:		/* Phase 0 - Waiting क्रम parport */
		अगर (समय_after(jअगरfies, dev->jstart + HZ)) अणु
			/*
			 * We रुकोed more than a second
			 * क्रम parport to call us
			 */
			imm_fail(dev, DID_BUS_BUSY);
			वापस 0;
		पूर्ण
		वापस 1;	/* रुको until imm_wakeup claims parport */

	हाल 1:		/* Phase 1 - Connected */
		imm_connect(dev, CONNECT_EPP_MAYBE);
		cmd->SCp.phase++;
		fallthrough;

	हाल 2:		/* Phase 2 - We are now talking to the scsi bus */
		अगर (!imm_select(dev, scmd_id(cmd))) अणु
			imm_fail(dev, DID_NO_CONNECT);
			वापस 0;
		पूर्ण
		cmd->SCp.phase++;
		fallthrough;

	हाल 3:		/* Phase 3 - Ready to accept a command */
		w_ctr(ppb, 0x0c);
		अगर (!(r_str(ppb) & 0x80))
			वापस 1;

		अगर (!imm_send_command(cmd))
			वापस 0;
		cmd->SCp.phase++;
		fallthrough;

	हाल 4:		/* Phase 4 - Setup scatter/gather buffers */
		अगर (scsi_bufflen(cmd)) अणु
			cmd->SCp.buffer = scsi_sglist(cmd);
			cmd->SCp.this_residual = cmd->SCp.buffer->length;
			cmd->SCp.ptr = sg_virt(cmd->SCp.buffer);
		पूर्ण अन्यथा अणु
			cmd->SCp.buffer = शून्य;
			cmd->SCp.this_residual = 0;
			cmd->SCp.ptr = शून्य;
		पूर्ण
		cmd->SCp.buffers_residual = scsi_sg_count(cmd) - 1;
		cmd->SCp.phase++;
		अगर (cmd->SCp.this_residual & 0x01)
			cmd->SCp.this_residual++;
		fallthrough;

	हाल 5:		/* Phase 5 - Pre-Data transfer stage */
		/* Spin lock क्रम BUSY */
		w_ctr(ppb, 0x0c);
		अगर (!(r_str(ppb) & 0x80))
			वापस 1;

		/* Require negotiation क्रम पढ़ो requests */
		x = (r_str(ppb) & 0xb8);
		dev->rd = (x & 0x10) ? 1 : 0;
		dev->dp = (x & 0x20) ? 0 : 1;

		अगर ((dev->dp) && (dev->rd))
			अगर (imm_negotiate(dev))
				वापस 0;
		cmd->SCp.phase++;
		fallthrough;

	हाल 6:		/* Phase 6 - Data transfer stage */
		/* Spin lock क्रम BUSY */
		w_ctr(ppb, 0x0c);
		अगर (!(r_str(ppb) & 0x80))
			वापस 1;

		अगर (dev->dp) अणु
			retv = imm_completion(cmd);
			अगर (retv == -1)
				वापस 0;
			अगर (retv == 0)
				वापस 1;
		पूर्ण
		cmd->SCp.phase++;
		fallthrough;

	हाल 7:		/* Phase 7 - Post data transfer stage */
		अगर ((dev->dp) && (dev->rd)) अणु
			अगर ((dev->mode == IMM_NIBBLE) || (dev->mode == IMM_PS2)) अणु
				w_ctr(ppb, 0x4);
				w_ctr(ppb, 0xc);
				w_ctr(ppb, 0xe);
				w_ctr(ppb, 0x4);
			पूर्ण
		पूर्ण
		cmd->SCp.phase++;
		fallthrough;

	हाल 8:		/* Phase 8 - Read status/message */
		/* Check क्रम data overrun */
		अगर (imm_रुको(dev) != (अचिन्हित अक्षर) 0xb8) अणु
			imm_fail(dev, DID_ERROR);
			वापस 0;
		पूर्ण
		अगर (imm_negotiate(dev))
			वापस 0;
		अगर (imm_in(dev, &l, 1)) अणु	/* पढ़ो status byte */
			/* Check क्रम optional message byte */
			अगर (imm_रुको(dev) == (अचिन्हित अक्षर) 0xb8)
				imm_in(dev, &h, 1);
			cmd->result = (DID_OK << 16) | (l & STATUS_MASK);
		पूर्ण
		अगर ((dev->mode == IMM_NIBBLE) || (dev->mode == IMM_PS2)) अणु
			w_ctr(ppb, 0x4);
			w_ctr(ppb, 0xc);
			w_ctr(ppb, 0xe);
			w_ctr(ppb, 0x4);
		पूर्ण
		वापस 0;	/* Finished */

	शेष:
		prपूर्णांकk("imm: Invalid scsi phase\n");
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक imm_queuecommand_lck(काष्ठा scsi_cmnd *cmd,
		व्योम (*करोne)(काष्ठा scsi_cmnd *))
अणु
	imm_काष्ठा *dev = imm_dev(cmd->device->host);

	अगर (dev->cur_cmd) अणु
		prपूर्णांकk("IMM: bug in imm_queuecommand\n");
		वापस 0;
	पूर्ण
	dev->failed = 0;
	dev->jstart = jअगरfies;
	dev->cur_cmd = cmd;
	cmd->scsi_करोne = करोne;
	cmd->result = DID_ERROR << 16;	/* शेष वापस code */
	cmd->SCp.phase = 0;	/* bus मुक्त */

	schedule_delayed_work(&dev->imm_tq, 0);

	imm_pb_claim(dev);

	वापस 0;
पूर्ण

अटल DEF_SCSI_QCMD(imm_queuecommand)

/*
 * Apparently the disk->capacity attribute is off by 1 sector 
 * क्रम all disk drives.  We add the one here, but it should really
 * be करोne in sd.c.  Even अगर it माला_लो fixed there, this will still
 * work.
 */
अटल पूर्णांक imm_biosparam(काष्ठा scsi_device *sdev, काष्ठा block_device *dev,
			 sector_t capacity, पूर्णांक ip[])
अणु
	ip[0] = 0x40;
	ip[1] = 0x20;
	ip[2] = ((अचिन्हित दीर्घ) capacity + 1) / (ip[0] * ip[1]);
	अगर (ip[2] > 1024) अणु
		ip[0] = 0xff;
		ip[1] = 0x3f;
		ip[2] = ((अचिन्हित दीर्घ) capacity + 1) / (ip[0] * ip[1]);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक imm_पात(काष्ठा scsi_cmnd *cmd)
अणु
	imm_काष्ठा *dev = imm_dev(cmd->device->host);
	/*
	 * There is no method क्रम पातing commands since Iomega
	 * have tied the SCSI_MESSAGE line high in the पूर्णांकerface
	 */

	चयन (cmd->SCp.phase) अणु
	हाल 0:		/* Do not have access to parport */
	हाल 1:		/* Have not connected to पूर्णांकerface */
		dev->cur_cmd = शून्य;	/* Forget the problem */
		वापस SUCCESS;
	शेष:		/* SCSI command sent, can not पात */
		वापस FAILED;
	पूर्ण
पूर्ण

अटल व्योम imm_reset_pulse(अचिन्हित पूर्णांक base)
अणु
	w_ctr(base, 0x04);
	w_dtr(base, 0x40);
	udelay(1);
	w_ctr(base, 0x0c);
	w_ctr(base, 0x0d);
	udelay(50);
	w_ctr(base, 0x0c);
	w_ctr(base, 0x04);
पूर्ण

अटल पूर्णांक imm_reset(काष्ठा scsi_cmnd *cmd)
अणु
	imm_काष्ठा *dev = imm_dev(cmd->device->host);

	अगर (cmd->SCp.phase)
		imm_disconnect(dev);
	dev->cur_cmd = शून्य;	/* Forget the problem */

	imm_connect(dev, CONNECT_NORMAL);
	imm_reset_pulse(dev->base);
	mdelay(1);		/* device settle delay */
	imm_disconnect(dev);
	mdelay(1);		/* device settle delay */
	वापस SUCCESS;
पूर्ण

अटल पूर्णांक device_check(imm_काष्ठा *dev)
अणु
	/* This routine looks क्रम a device and then attempts to use EPP
	   to send a command. If all goes as planned then EPP is available. */

	अटल अक्षर cmd[6] = अणु 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 पूर्ण;
	पूर्णांक loop, old_mode, status, k, ppb = dev->base;
	अचिन्हित अक्षर l;

	old_mode = dev->mode;
	क्रम (loop = 0; loop < 8; loop++) अणु
		/* Attempt to use EPP क्रम Test Unit Ready */
		अगर ((ppb & 0x0007) == 0x0000)
			dev->mode = IMM_EPP_32;

	      second_pass:
		imm_connect(dev, CONNECT_EPP_MAYBE);
		/* Select SCSI device */
		अगर (!imm_select(dev, loop)) अणु
			imm_disconnect(dev);
			जारी;
		पूर्ण
		prपूर्णांकk("imm: Found device at ID %i, Attempting to use %s\n",
		       loop, IMM_MODE_STRING[dev->mode]);

		/* Send SCSI command */
		status = 1;
		w_ctr(ppb, 0x0c);
		क्रम (l = 0; (l < 3) && (status); l++)
			status = imm_out(dev, &cmd[l << 1], 2);

		अगर (!status) अणु
			imm_disconnect(dev);
			imm_connect(dev, CONNECT_EPP_MAYBE);
			imm_reset_pulse(dev->base);
			udelay(1000);
			imm_disconnect(dev);
			udelay(1000);
			अगर (dev->mode == IMM_EPP_32) अणु
				dev->mode = old_mode;
				जाओ second_pass;
			पूर्ण
			prपूर्णांकk("imm: Unable to establish communication\n");
			वापस -EIO;
		पूर्ण
		w_ctr(ppb, 0x0c);

		k = 1000000;	/* 1 Second */
		करो अणु
			l = r_str(ppb);
			k--;
			udelay(1);
		पूर्ण जबतक (!(l & 0x80) && (k));

		l &= 0xb8;

		अगर (l != 0xb8) अणु
			imm_disconnect(dev);
			imm_connect(dev, CONNECT_EPP_MAYBE);
			imm_reset_pulse(dev->base);
			udelay(1000);
			imm_disconnect(dev);
			udelay(1000);
			अगर (dev->mode == IMM_EPP_32) अणु
				dev->mode = old_mode;
				जाओ second_pass;
			पूर्ण
			prपूर्णांकk
			    ("imm: Unable to establish communication\n");
			वापस -EIO;
		पूर्ण
		imm_disconnect(dev);
		prपूर्णांकk
		    ("imm: Communication established at 0x%x with ID %i using %s\n",
		     ppb, loop, IMM_MODE_STRING[dev->mode]);
		imm_connect(dev, CONNECT_EPP_MAYBE);
		imm_reset_pulse(dev->base);
		udelay(1000);
		imm_disconnect(dev);
		udelay(1000);
		वापस 0;
	पूर्ण
	prपूर्णांकk("imm: No devices found\n");
	वापस -ENODEV;
पूर्ण

/*
 * imm cannot deal with highmem, so this causes all IO pages क्रम this host
 * to reside in low memory (hence mapped)
 */
अटल पूर्णांक imm_adjust_queue(काष्ठा scsi_device *device)
अणु
	blk_queue_bounce_limit(device->request_queue, BLK_BOUNCE_HIGH);
	वापस 0;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा imm_ढाँचा = अणु
	.module			= THIS_MODULE,
	.proc_name		= "imm",
	.show_info		= imm_show_info,
	.ग_लिखो_info		= imm_ग_लिखो_info,
	.name			= "Iomega VPI2 (imm) interface",
	.queuecommand		= imm_queuecommand,
	.eh_पात_handler	= imm_पात,
	.eh_host_reset_handler	= imm_reset,
	.bios_param		= imm_biosparam,
	.this_id		= 7,
	.sg_tablesize		= SG_ALL,
	.can_queue		= 1,
	.slave_alloc		= imm_adjust_queue,
पूर्ण;

/***************************************************************************
 *                   Parallel port probing routines                        *
 ***************************************************************************/

अटल LIST_HEAD(imm_hosts);

/*
 * Finds the first available device number that can be alloted to the
 * new imm device and वापसs the address of the previous node so that
 * we can add to the tail and have a list in the ascending order.
 */

अटल अंतरभूत imm_काष्ठा *find_parent(व्योम)
अणु
	imm_काष्ठा *dev, *par = शून्य;
	अचिन्हित पूर्णांक cnt = 0;

	अगर (list_empty(&imm_hosts))
		वापस शून्य;

	list_क्रम_each_entry(dev, &imm_hosts, list) अणु
		अगर (dev->dev_no != cnt)
			वापस par;
		cnt++;
		par = dev;
	पूर्ण

	वापस par;
पूर्ण

अटल पूर्णांक __imm_attach(काष्ठा parport *pb)
अणु
	काष्ठा Scsi_Host *host;
	imm_काष्ठा *dev, *temp;
	DECLARE_WAIT_QUEUE_HEAD_ONSTACK(रुकोing);
	DEFINE_WAIT(रुको);
	पूर्णांक ports;
	पूर्णांक modes, ppb;
	पूर्णांक err = -ENOMEM;
	काष्ठा pardev_cb imm_cb;

	init_रुकोqueue_head(&रुकोing);

	dev = kzalloc(माप(imm_काष्ठा), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;


	dev->base = -1;
	dev->mode = IMM_AUTODETECT;
	INIT_LIST_HEAD(&dev->list);

	temp = find_parent();
	अगर (temp)
		dev->dev_no = temp->dev_no + 1;

	स_रखो(&imm_cb, 0, माप(imm_cb));
	imm_cb.निजी = dev;
	imm_cb.wakeup = imm_wakeup;

	dev->dev = parport_रेजिस्टर_dev_model(pb, "imm", &imm_cb, dev->dev_no);
	अगर (!dev->dev)
		जाओ out;


	/* Claim the bus so it remembers what we करो to the control
	 * रेजिस्टरs. [ CTR and ECP ]
	 */
	err = -EBUSY;
	dev->रुकोing = &रुकोing;
	prepare_to_रुको(&रुकोing, &रुको, TASK_UNINTERRUPTIBLE);
	अगर (imm_pb_claim(dev))
		schedule_समयout(3 * HZ);
	अगर (dev->wanted) अणु
		prपूर्णांकk(KERN_ERR "imm%d: failed to claim parport because "
			"a pardevice is owning the port for too long "
			"time!\n", pb->number);
		imm_pb_dismiss(dev);
		dev->रुकोing = शून्य;
		finish_रुको(&रुकोing, &रुको);
		जाओ out1;
	पूर्ण
	dev->रुकोing = शून्य;
	finish_रुको(&रुकोing, &रुको);
	ppb = dev->base = dev->dev->port->base;
	dev->base_hi = dev->dev->port->base_hi;
	w_ctr(ppb, 0x0c);
	modes = dev->dev->port->modes;

	/* Mode detection works up the chain of speed
	 * This aव्योमs a nasty अगर-then-अन्यथा-अगर-... tree
	 */
	dev->mode = IMM_NIBBLE;

	अगर (modes & PARPORT_MODE_TRISTATE)
		dev->mode = IMM_PS2;

	/* Done configuration */

	err = imm_init(dev);

	imm_pb_release(dev);

	अगर (err)
		जाओ out1;

	/* now the glue ... */
	अगर (dev->mode == IMM_NIBBLE || dev->mode == IMM_PS2)
		ports = 3;
	अन्यथा
		ports = 8;

	INIT_DELAYED_WORK(&dev->imm_tq, imm_पूर्णांकerrupt);

	err = -ENOMEM;
	host = scsi_host_alloc(&imm_ढाँचा, माप(imm_काष्ठा *));
	अगर (!host)
		जाओ out1;
	host->io_port = pb->base;
	host->n_io_port = ports;
	host->dma_channel = -1;
	host->unique_id = pb->number;
	*(imm_काष्ठा **)&host->hostdata = dev;
	dev->host = host;
	अगर (!temp)
		list_add_tail(&dev->list, &imm_hosts);
	अन्यथा
		list_add_tail(&dev->list, &temp->list);
	err = scsi_add_host(host, शून्य);
	अगर (err)
		जाओ out2;
	scsi_scan_host(host);
	वापस 0;

out2:
	list_del_init(&dev->list);
	scsi_host_put(host);
out1:
	parport_unरेजिस्टर_device(dev->dev);
out:
	kमुक्त(dev);
	वापस err;
पूर्ण

अटल व्योम imm_attach(काष्ठा parport *pb)
अणु
	__imm_attach(pb);
पूर्ण

अटल व्योम imm_detach(काष्ठा parport *pb)
अणु
	imm_काष्ठा *dev;
	list_क्रम_each_entry(dev, &imm_hosts, list) अणु
		अगर (dev->dev->port == pb) अणु
			list_del_init(&dev->list);
			scsi_हटाओ_host(dev->host);
			scsi_host_put(dev->host);
			parport_unरेजिस्टर_device(dev->dev);
			kमुक्त(dev);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा parport_driver imm_driver = अणु
	.name		= "imm",
	.match_port	= imm_attach,
	.detach		= imm_detach,
	.devmodel	= true,
पूर्ण;

अटल पूर्णांक __init imm_driver_init(व्योम)
अणु
	prपूर्णांकk("imm: Version %s\n", IMM_VERSION);
	वापस parport_रेजिस्टर_driver(&imm_driver);
पूर्ण

अटल व्योम __निकास imm_driver_निकास(व्योम)
अणु
	parport_unरेजिस्टर_driver(&imm_driver);
पूर्ण

module_init(imm_driver_init);
module_निकास(imm_driver_निकास);

MODULE_LICENSE("GPL");
