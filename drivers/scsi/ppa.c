<शैली गुरु>
/* ppa.c   --  low level driver क्रम the IOMEGA PPA3 
 * parallel port SCSI host adapter.
 * 
 * (The PPA3 is the embedded controller in the ZIP drive.)
 * 
 * (c) 1995,1996 Grant R. Guenther, grant@torque.net,
 * under the terms of the GNU General Public License.
 * 
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/parport.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/delay.h>
#समावेश <linux/jअगरfies.h>
#समावेश <यंत्र/पन.स>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>


अटल व्योम ppa_reset_pulse(अचिन्हित पूर्णांक base);

प्रकार काष्ठा अणु
	काष्ठा pardevice *dev;	/* Parport device entry         */
	पूर्णांक base;		/* Actual port address          */
	पूर्णांक mode;		/* Transfer mode                */
	काष्ठा scsi_cmnd *cur_cmd;	/* Current queued command       */
	काष्ठा delayed_work ppa_tq;	/* Polling पूर्णांकerrupt stuff       */
	अचिन्हित दीर्घ jstart;	/* Jअगरfies at start             */
	अचिन्हित दीर्घ recon_पंचांगo;	/* How many usecs to रुको क्रम reconnection (6th bit) */
	अचिन्हित पूर्णांक failed:1;	/* Failure flag                 */
	अचिन्हित wanted:1;	/* Parport sharing busy flag    */
	अचिन्हित पूर्णांक dev_no;	/* Device number		*/
	रुको_queue_head_t *रुकोing;
	काष्ठा Scsi_Host *host;
	काष्ठा list_head list;
पूर्ण ppa_काष्ठा;

#समावेश  "ppa.h"

अटल अंतरभूत ppa_काष्ठा *ppa_dev(काष्ठा Scsi_Host *host)
अणु
	वापस *(ppa_काष्ठा **)&host->hostdata;
पूर्ण

अटल DEFINE_SPINLOCK(arbitration_lock);

अटल व्योम got_it(ppa_काष्ठा *dev)
अणु
	dev->base = dev->dev->port->base;
	अगर (dev->cur_cmd)
		dev->cur_cmd->SCp.phase = 1;
	अन्यथा
		wake_up(dev->रुकोing);
पूर्ण

अटल व्योम ppa_wakeup(व्योम *ref)
अणु
	ppa_काष्ठा *dev = (ppa_काष्ठा *) ref;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&arbitration_lock, flags);
	अगर (dev->wanted) अणु
		parport_claim(dev->dev);
		got_it(dev);
		dev->wanted = 0;
	पूर्ण
	spin_unlock_irqrestore(&arbitration_lock, flags);
	वापस;
पूर्ण

अटल पूर्णांक ppa_pb_claim(ppa_काष्ठा *dev)
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

अटल व्योम ppa_pb_dismiss(ppa_काष्ठा *dev)
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

अटल अंतरभूत व्योम ppa_pb_release(ppa_काष्ठा *dev)
अणु
	parport_release(dev->dev);
पूर्ण

/*
 * Start of Chipset kludges
 */

/* This is to give the ppa driver a way to modअगरy the timings (and other
 * parameters) by writing to the /proc/scsi/ppa/0 file.
 * Very simple method really... (To simple, no error checking :( )
 * Reason: Kernel hackers HATE having to unload and reload modules क्रम
 * testing...
 * Also gives a method to use a script to obtain optimum timings (TODO)
 */

अटल अंतरभूत पूर्णांक ppa_ग_लिखो_info(काष्ठा Scsi_Host *host, अक्षर *buffer, पूर्णांक length)
अणु
	ppa_काष्ठा *dev = ppa_dev(host);
	अचिन्हित दीर्घ x;

	अगर ((length > 5) && (म_भेदन(buffer, "mode=", 5) == 0)) अणु
		x = simple_म_से_अदीर्घ(buffer + 5, शून्य, 0);
		dev->mode = x;
		वापस length;
	पूर्ण
	अगर ((length > 10) && (म_भेदन(buffer, "recon_tmo=", 10) == 0)) अणु
		x = simple_म_से_अदीर्घ(buffer + 10, शून्य, 0);
		dev->recon_पंचांगo = x;
		prपूर्णांकk(KERN_INFO "ppa: recon_tmo set to %ld\n", x);
		वापस length;
	पूर्ण
	prपूर्णांकk(KERN_WARNING "ppa /proc: invalid variable\n");
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ppa_show_info(काष्ठा seq_file *m, काष्ठा Scsi_Host *host)
अणु
	ppa_काष्ठा *dev = ppa_dev(host);

	seq_म_लिखो(m, "Version : %s\n", PPA_VERSION);
	seq_म_लिखो(m, "Parport : %s\n", dev->dev->port->name);
	seq_म_लिखो(m, "Mode    : %s\n", PPA_MODE_STRING[dev->mode]);
#अगर PPA_DEBUG > 0
	seq_म_लिखो(m, "recon_tmo : %lu\n", dev->recon_पंचांगo);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक device_check(ppa_काष्ठा *dev);

#अगर PPA_DEBUG > 0
#घोषणा ppa_fail(x,y) prपूर्णांकk("ppa: ppa_fail(%i) from %s at line %d\n",\
	   y, __func__, __LINE__); ppa_fail_func(x,y);
अटल अंतरभूत व्योम ppa_fail_func(ppa_काष्ठा *dev, पूर्णांक error_code)
#अन्यथा
अटल अंतरभूत व्योम ppa_fail(ppa_काष्ठा *dev, पूर्णांक error_code)
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
अटल अचिन्हित अक्षर ppa_रुको(ppa_काष्ठा *dev)
अणु
	पूर्णांक k;
	अचिन्हित लघु ppb = dev->base;
	अचिन्हित अक्षर r;

	k = PPA_SPIN_TMO;
	/* Wait क्रम bit 6 and 7 - PJC */
	क्रम (r = r_str(ppb); ((r & 0xc0) != 0xc0) && (k); k--) अणु
		udelay(1);
		r = r_str(ppb);
	पूर्ण

	/*
	 * वापस some status inक्रमmation.
	 * Semantics: 0xc0 = ZIP wants more data
	 *            0xd0 = ZIP wants to send more data
	 *            0xe0 = ZIP is expecting SCSI command data
	 *            0xf0 = end of transfer, ZIP is sending status
	 */
	अगर (k)
		वापस (r & 0xf0);

	/* Counter expired - Time out occurred */
	ppa_fail(dev, DID_TIME_OUT);
	prपूर्णांकk(KERN_WARNING "ppa timeout in ppa_wait\n");
	वापस 0;		/* command समयd out */
पूर्ण

/*
 * Clear EPP Timeout Bit 
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
अटल अंतरभूत व्योम ecp_sync(ppa_काष्ठा *dev)
अणु
	पूर्णांक i, ppb_hi = dev->dev->port->base_hi;

	अगर (ppb_hi == 0)
		वापस;

	अगर ((r_ecr(ppb_hi) & 0xe0) == 0x60) अणु	/* mode 011 == ECP fअगरo mode */
		क्रम (i = 0; i < 100; i++) अणु
			अगर (r_ecr(ppb_hi) & 0x01)
				वापस;
			udelay(5);
		पूर्ण
		prपूर्णांकk(KERN_WARNING "ppa: ECP sync failed as data still present in FIFO.\n");
	पूर्ण
पूर्ण

अटल पूर्णांक ppa_byte_out(अचिन्हित लघु base, स्थिर अक्षर *buffer, पूर्णांक len)
अणु
	पूर्णांक i;

	क्रम (i = len; i; i--) अणु
		w_dtr(base, *buffer++);
		w_ctr(base, 0xe);
		w_ctr(base, 0xc);
	पूर्ण
	वापस 1;		/* All went well - we hope! */
पूर्ण

अटल पूर्णांक ppa_byte_in(अचिन्हित लघु base, अक्षर *buffer, पूर्णांक len)
अणु
	पूर्णांक i;

	क्रम (i = len; i; i--) अणु
		*buffer++ = r_dtr(base);
		w_ctr(base, 0x27);
		w_ctr(base, 0x25);
	पूर्ण
	वापस 1;		/* All went well - we hope! */
पूर्ण

अटल पूर्णांक ppa_nibble_in(अचिन्हित लघु base, अक्षर *buffer, पूर्णांक len)
अणु
	क्रम (; len; len--) अणु
		अचिन्हित अक्षर h;

		w_ctr(base, 0x4);
		h = r_str(base) & 0xf0;
		w_ctr(base, 0x6);
		*buffer++ = h | ((r_str(base) & 0xf0) >> 4);
	पूर्ण
	वापस 1;		/* All went well - we hope! */
पूर्ण

अटल पूर्णांक ppa_out(ppa_काष्ठा *dev, अक्षर *buffer, पूर्णांक len)
अणु
	पूर्णांक r;
	अचिन्हित लघु ppb = dev->base;

	r = ppa_रुको(dev);

	अगर ((r & 0x50) != 0x40) अणु
		ppa_fail(dev, DID_ERROR);
		वापस 0;
	पूर्ण
	चयन (dev->mode) अणु
	हाल PPA_NIBBLE:
	हाल PPA_PS2:
		/* 8 bit output, with a loop */
		r = ppa_byte_out(ppb, buffer, len);
		अवरोध;

	हाल PPA_EPP_32:
	हाल PPA_EPP_16:
	हाल PPA_EPP_8:
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

	शेष:
		prपूर्णांकk(KERN_ERR "PPA: bug in ppa_out()\n");
		r = 0;
	पूर्ण
	वापस r;
पूर्ण

अटल पूर्णांक ppa_in(ppa_काष्ठा *dev, अक्षर *buffer, पूर्णांक len)
अणु
	पूर्णांक r;
	अचिन्हित लघु ppb = dev->base;

	r = ppa_रुको(dev);

	अगर ((r & 0x50) != 0x50) अणु
		ppa_fail(dev, DID_ERROR);
		वापस 0;
	पूर्ण
	चयन (dev->mode) अणु
	हाल PPA_NIBBLE:
		/* 4 bit input, with a loop */
		r = ppa_nibble_in(ppb, buffer, len);
		w_ctr(ppb, 0xc);
		अवरोध;

	हाल PPA_PS2:
		/* 8 bit input, with a loop */
		w_ctr(ppb, 0x25);
		r = ppa_byte_in(ppb, buffer, len);
		w_ctr(ppb, 0x4);
		w_ctr(ppb, 0xc);
		अवरोध;

	हाल PPA_EPP_32:
	हाल PPA_EPP_16:
	हाल PPA_EPP_8:
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
		prपूर्णांकk(KERN_ERR "PPA: bug in ppa_ins()\n");
		r = 0;
		अवरोध;
	पूर्ण
	वापस r;
पूर्ण

/* end of ppa_पन.स */
अटल अंतरभूत व्योम ppa_d_pulse(अचिन्हित लघु ppb, अचिन्हित अक्षर b)
अणु
	w_dtr(ppb, b);
	w_ctr(ppb, 0xc);
	w_ctr(ppb, 0xe);
	w_ctr(ppb, 0xc);
	w_ctr(ppb, 0x4);
	w_ctr(ppb, 0xc);
पूर्ण

अटल व्योम ppa_disconnect(ppa_काष्ठा *dev)
अणु
	अचिन्हित लघु ppb = dev->base;

	ppa_d_pulse(ppb, 0);
	ppa_d_pulse(ppb, 0x3c);
	ppa_d_pulse(ppb, 0x20);
	ppa_d_pulse(ppb, 0xf);
पूर्ण

अटल अंतरभूत व्योम ppa_c_pulse(अचिन्हित लघु ppb, अचिन्हित अक्षर b)
अणु
	w_dtr(ppb, b);
	w_ctr(ppb, 0x4);
	w_ctr(ppb, 0x6);
	w_ctr(ppb, 0x4);
	w_ctr(ppb, 0xc);
पूर्ण

अटल अंतरभूत व्योम ppa_connect(ppa_काष्ठा *dev, पूर्णांक flag)
अणु
	अचिन्हित लघु ppb = dev->base;

	ppa_c_pulse(ppb, 0);
	ppa_c_pulse(ppb, 0x3c);
	ppa_c_pulse(ppb, 0x20);
	अगर ((flag == CONNECT_EPP_MAYBE) && IN_EPP_MODE(dev->mode))
		ppa_c_pulse(ppb, 0xcf);
	अन्यथा
		ppa_c_pulse(ppb, 0x8f);
पूर्ण

अटल पूर्णांक ppa_select(ppa_काष्ठा *dev, पूर्णांक target)
अणु
	पूर्णांक k;
	अचिन्हित लघु ppb = dev->base;

	/*
	 * Bit 6 (0x40) is the device selected bit.
	 * First we must रुको till the current device goes off line...
	 */
	k = PPA_SELECT_TMO;
	करो अणु
		k--;
		udelay(1);
	पूर्ण जबतक ((r_str(ppb) & 0x40) && (k));
	अगर (!k)
		वापस 0;

	w_dtr(ppb, (1 << target));
	w_ctr(ppb, 0xe);
	w_ctr(ppb, 0xc);
	w_dtr(ppb, 0x80);	/* This is NOT the initator */
	w_ctr(ppb, 0x8);

	k = PPA_SELECT_TMO;
	करो अणु
		k--;
		udelay(1);
	पूर्ण
	जबतक (!(r_str(ppb) & 0x40) && (k));
	अगर (!k)
		वापस 0;

	वापस 1;
पूर्ण

/* 
 * This is based on a trace of what the Iomega DOS 'guest' driver करोes.
 * I've tried several dअगरferent kinds of parallel ports with guest and
 * coded this to react in the same ways that it करोes.
 * 
 * The वापस value from this function is just a hपूर्णांक about where the
 * handshaking failed.
 * 
 */
अटल पूर्णांक ppa_init(ppa_काष्ठा *dev)
अणु
	पूर्णांक retv;
	अचिन्हित लघु ppb = dev->base;

	ppa_disconnect(dev);
	ppa_connect(dev, CONNECT_NORMAL);

	retv = 2;		/* Failed */

	w_ctr(ppb, 0xe);
	अगर ((r_str(ppb) & 0x08) == 0x08)
		retv--;

	w_ctr(ppb, 0xc);
	अगर ((r_str(ppb) & 0x08) == 0x00)
		retv--;

	अगर (!retv)
		ppa_reset_pulse(ppb);
	udelay(1000);		/* Allow devices to settle करोwn */
	ppa_disconnect(dev);
	udelay(1000);		/* Another delay to allow devices to settle */

	अगर (retv)
		वापस -EIO;

	वापस device_check(dev);
पूर्ण

अटल अंतरभूत पूर्णांक ppa_send_command(काष्ठा scsi_cmnd *cmd)
अणु
	ppa_काष्ठा *dev = ppa_dev(cmd->device->host);
	पूर्णांक k;

	w_ctr(dev->base, 0x0c);

	क्रम (k = 0; k < cmd->cmd_len; k++)
		अगर (!ppa_out(dev, &cmd->cmnd[k], 1))
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
अटल पूर्णांक ppa_completion(काष्ठा scsi_cmnd *cmd)
अणु
	/* Return codes:
	 * -1     Error
	 *  0     Told to schedule
	 *  1     Finished data transfer
	 */
	ppa_काष्ठा *dev = ppa_dev(cmd->device->host);
	अचिन्हित लघु ppb = dev->base;
	अचिन्हित दीर्घ start_jअगरfies = jअगरfies;

	अचिन्हित अक्षर r, v;
	पूर्णांक fast, bulk, status;

	v = cmd->cmnd[0];
	bulk = ((v == READ_6) ||
		(v == READ_10) || (v == WRITE_6) || (v == WRITE_10));

	/*
	 * We only get here अगर the drive is पढ़ोy to comunicate,
	 * hence no need क्रम a full ppa_रुको.
	 */
	r = (r_str(ppb) & 0xf0);

	जबतक (r != (अचिन्हित अक्षर) 0xf0) अणु
		/*
		 * If we have been running क्रम more than a full समयr tick
		 * then take a rest.
		 */
		अगर (समय_after(jअगरfies, start_jअगरfies + 1))
			वापस 0;

		अगर ((cmd->SCp.this_residual <= 0)) अणु
			ppa_fail(dev, DID_ERROR);
			वापस -1;	/* ERROR_RETURN */
		पूर्ण

		/* On some hardware we have SCSI disconnected (6th bit low)
		 * क्रम about 100usecs. It is too expensive to रुको a 
		 * tick on every loop so we busy रुको क्रम no more than
		 * 500usecs to give the drive a chance first. We करो not 
		 * change things क्रम "normal" hardware since generally 
		 * the 6th bit is always high.
		 * This makes the CPU load higher on some hardware 
		 * but otherwise we can not get more than 50K/secs 
		 * on this problem hardware.
		 */
		अगर ((r & 0xc0) != 0xc0) अणु
			/* Wait क्रम reconnection should be no more than 
			 * jअगरfy/2 = 5ms = 5000 loops
			 */
			अचिन्हित दीर्घ k = dev->recon_पंचांगo;
			क्रम (; k && ((r = (r_str(ppb) & 0xf0)) & 0xc0) != 0xc0;
			     k--)
				udelay(1);

			अगर (!k)
				वापस 0;
		पूर्ण

		/* determine अगर we should use burst I/O */
		fast = (bulk && (cmd->SCp.this_residual >= PPA_BURST_SIZE))
		    ? PPA_BURST_SIZE : 1;

		अगर (r == (अचिन्हित अक्षर) 0xc0)
			status = ppa_out(dev, cmd->SCp.ptr, fast);
		अन्यथा
			status = ppa_in(dev, cmd->SCp.ptr, fast);

		cmd->SCp.ptr += fast;
		cmd->SCp.this_residual -= fast;

		अगर (!status) अणु
			ppa_fail(dev, DID_BUS_BUSY);
			वापस -1;	/* ERROR_RETURN */
		पूर्ण
		अगर (cmd->SCp.buffer && !cmd->SCp.this_residual) अणु
			/* अगर scatter/gather, advance to the next segment */
			अगर (cmd->SCp.buffers_residual--) अणु
				cmd->SCp.buffer = sg_next(cmd->SCp.buffer);
				cmd->SCp.this_residual =
				    cmd->SCp.buffer->length;
				cmd->SCp.ptr = sg_virt(cmd->SCp.buffer);
			पूर्ण
		पूर्ण
		/* Now check to see अगर the drive is पढ़ोy to comunicate */
		r = (r_str(ppb) & 0xf0);
		/* If not, drop back करोwn to the scheduler and रुको a समयr tick */
		अगर (!(r & 0x80))
			वापस 0;
	पूर्ण
	वापस 1;		/* FINISH_RETURN */
पूर्ण

/*
 * Since the PPA itself करोesn't generate पूर्णांकerrupts, we use
 * the scheduler's task queue to generate a stream of call-backs and
 * complete the request when the drive is पढ़ोy.
 */
अटल व्योम ppa_पूर्णांकerrupt(काष्ठा work_काष्ठा *work)
अणु
	ppa_काष्ठा *dev = container_of(work, ppa_काष्ठा, ppa_tq.work);
	काष्ठा scsi_cmnd *cmd = dev->cur_cmd;

	अगर (!cmd) अणु
		prपूर्णांकk(KERN_ERR "PPA: bug in ppa_interrupt\n");
		वापस;
	पूर्ण
	अगर (ppa_engine(dev, cmd)) अणु
		schedule_delayed_work(&dev->ppa_tq, 1);
		वापस;
	पूर्ण
	/* Command must of completed hence it is safe to let go... */
#अगर PPA_DEBUG > 0
	चयन ((cmd->result >> 16) & 0xff) अणु
	हाल DID_OK:
		अवरोध;
	हाल DID_NO_CONNECT:
		prपूर्णांकk(KERN_DEBUG "ppa: no device at SCSI ID %i\n", cmd->device->target);
		अवरोध;
	हाल DID_BUS_BUSY:
		prपूर्णांकk(KERN_DEBUG "ppa: BUS BUSY - EPP timeout detected\n");
		अवरोध;
	हाल DID_TIME_OUT:
		prपूर्णांकk(KERN_DEBUG "ppa: unknown timeout\n");
		अवरोध;
	हाल DID_ABORT:
		prपूर्णांकk(KERN_DEBUG "ppa: told to abort\n");
		अवरोध;
	हाल DID_PARITY:
		prपूर्णांकk(KERN_DEBUG "ppa: parity error (???)\n");
		अवरोध;
	हाल DID_ERROR:
		prपूर्णांकk(KERN_DEBUG "ppa: internal driver error\n");
		अवरोध;
	हाल DID_RESET:
		prपूर्णांकk(KERN_DEBUG "ppa: told to reset device\n");
		अवरोध;
	हाल DID_BAD_INTR:
		prपूर्णांकk(KERN_WARNING "ppa: bad interrupt (???)\n");
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_WARNING "ppa: bad return code (%02x)\n",
		       (cmd->result >> 16) & 0xff);
	पूर्ण
#पूर्ण_अगर

	अगर (cmd->SCp.phase > 1)
		ppa_disconnect(dev);

	ppa_pb_dismiss(dev);

	dev->cur_cmd = शून्य;

	cmd->scsi_करोne(cmd);
पूर्ण

अटल पूर्णांक ppa_engine(ppa_काष्ठा *dev, काष्ठा scsi_cmnd *cmd)
अणु
	अचिन्हित लघु ppb = dev->base;
	अचिन्हित अक्षर l = 0, h = 0;
	पूर्णांक retv;

	/* First check क्रम any errors that may of occurred
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
			ppa_fail(dev, DID_BUS_BUSY);
			वापस 0;
		पूर्ण
		वापस 1;	/* रुको until ppa_wakeup claims parport */
	हाल 1:		/* Phase 1 - Connected */
		अणु		/* Perक्रमm a sanity check क्रम cable unplugged */
			पूर्णांक retv = 2;	/* Failed */

			ppa_connect(dev, CONNECT_EPP_MAYBE);

			w_ctr(ppb, 0xe);
			अगर ((r_str(ppb) & 0x08) == 0x08)
				retv--;

			w_ctr(ppb, 0xc);
			अगर ((r_str(ppb) & 0x08) == 0x00)
				retv--;

			अगर (retv) अणु
				अगर (समय_after(jअगरfies, dev->jstart + (1 * HZ))) अणु
					prपूर्णांकk(KERN_ERR "ppa: Parallel port cable is unplugged.\n");
					ppa_fail(dev, DID_BUS_BUSY);
					वापस 0;
				पूर्ण अन्यथा अणु
					ppa_disconnect(dev);
					वापस 1;	/* Try again in a jअगरfy */
				पूर्ण
			पूर्ण
			cmd->SCp.phase++;
		पूर्ण
		fallthrough;

	हाल 2:		/* Phase 2 - We are now talking to the scsi bus */
		अगर (!ppa_select(dev, scmd_id(cmd))) अणु
			ppa_fail(dev, DID_NO_CONNECT);
			वापस 0;
		पूर्ण
		cmd->SCp.phase++;
		fallthrough;

	हाल 3:		/* Phase 3 - Ready to accept a command */
		w_ctr(ppb, 0x0c);
		अगर (!(r_str(ppb) & 0x80))
			वापस 1;

		अगर (!ppa_send_command(cmd))
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
		fallthrough;

	हाल 5:		/* Phase 5 - Data transfer stage */
		w_ctr(ppb, 0x0c);
		अगर (!(r_str(ppb) & 0x80))
			वापस 1;

		retv = ppa_completion(cmd);
		अगर (retv == -1)
			वापस 0;
		अगर (retv == 0)
			वापस 1;
		cmd->SCp.phase++;
		fallthrough;

	हाल 6:		/* Phase 6 - Read status/message */
		cmd->result = DID_OK << 16;
		/* Check क्रम data overrun */
		अगर (ppa_रुको(dev) != (अचिन्हित अक्षर) 0xf0) अणु
			ppa_fail(dev, DID_ERROR);
			वापस 0;
		पूर्ण
		अगर (ppa_in(dev, &l, 1)) अणु	/* पढ़ो status byte */
			/* Check क्रम optional message byte */
			अगर (ppa_रुको(dev) == (अचिन्हित अक्षर) 0xf0)
				ppa_in(dev, &h, 1);
			cmd->result =
			    (DID_OK << 16) + (h << 8) + (l & STATUS_MASK);
		पूर्ण
		वापस 0;	/* Finished */

	शेष:
		prपूर्णांकk(KERN_ERR "ppa: Invalid scsi phase\n");
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ppa_queuecommand_lck(काष्ठा scsi_cmnd *cmd,
		व्योम (*करोne) (काष्ठा scsi_cmnd *))
अणु
	ppa_काष्ठा *dev = ppa_dev(cmd->device->host);

	अगर (dev->cur_cmd) अणु
		prपूर्णांकk(KERN_ERR "PPA: bug in ppa_queuecommand\n");
		वापस 0;
	पूर्ण
	dev->failed = 0;
	dev->jstart = jअगरfies;
	dev->cur_cmd = cmd;
	cmd->scsi_करोne = करोne;
	cmd->result = DID_ERROR << 16;	/* शेष वापस code */
	cmd->SCp.phase = 0;	/* bus मुक्त */

	schedule_delayed_work(&dev->ppa_tq, 0);

	ppa_pb_claim(dev);

	वापस 0;
पूर्ण

अटल DEF_SCSI_QCMD(ppa_queuecommand)

/*
 * Apparently the disk->capacity attribute is off by 1 sector 
 * क्रम all disk drives.  We add the one here, but it should really
 * be करोne in sd.c.  Even अगर it माला_लो fixed there, this will still
 * work.
 */
अटल पूर्णांक ppa_biosparam(काष्ठा scsi_device *sdev, काष्ठा block_device *dev,
	      sector_t capacity, पूर्णांक ip[])
अणु
	ip[0] = 0x40;
	ip[1] = 0x20;
	ip[2] = ((अचिन्हित दीर्घ) capacity + 1) / (ip[0] * ip[1]);
	अगर (ip[2] > 1024) अणु
		ip[0] = 0xff;
		ip[1] = 0x3f;
		ip[2] = ((अचिन्हित दीर्घ) capacity + 1) / (ip[0] * ip[1]);
		अगर (ip[2] > 1023)
			ip[2] = 1023;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ppa_पात(काष्ठा scsi_cmnd *cmd)
अणु
	ppa_काष्ठा *dev = ppa_dev(cmd->device->host);
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

अटल व्योम ppa_reset_pulse(अचिन्हित पूर्णांक base)
अणु
	w_dtr(base, 0x40);
	w_ctr(base, 0x8);
	udelay(30);
	w_ctr(base, 0xc);
पूर्ण

अटल पूर्णांक ppa_reset(काष्ठा scsi_cmnd *cmd)
अणु
	ppa_काष्ठा *dev = ppa_dev(cmd->device->host);

	अगर (cmd->SCp.phase)
		ppa_disconnect(dev);
	dev->cur_cmd = शून्य;	/* Forget the problem */

	ppa_connect(dev, CONNECT_NORMAL);
	ppa_reset_pulse(dev->base);
	mdelay(1);		/* device settle delay */
	ppa_disconnect(dev);
	mdelay(1);		/* device settle delay */
	वापस SUCCESS;
पूर्ण

अटल पूर्णांक device_check(ppa_काष्ठा *dev)
अणु
	/* This routine looks क्रम a device and then attempts to use EPP
	   to send a command. If all goes as planned then EPP is available. */

	अटल u8 cmd[6] = अणु 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 पूर्ण;
	पूर्णांक loop, old_mode, status, k, ppb = dev->base;
	अचिन्हित अक्षर l;

	old_mode = dev->mode;
	क्रम (loop = 0; loop < 8; loop++) अणु
		/* Attempt to use EPP क्रम Test Unit Ready */
		अगर ((ppb & 0x0007) == 0x0000)
			dev->mode = PPA_EPP_32;

second_pass:
		ppa_connect(dev, CONNECT_EPP_MAYBE);
		/* Select SCSI device */
		अगर (!ppa_select(dev, loop)) अणु
			ppa_disconnect(dev);
			जारी;
		पूर्ण
		prपूर्णांकk(KERN_INFO "ppa: Found device at ID %i, Attempting to use %s\n",
		       loop, PPA_MODE_STRING[dev->mode]);

		/* Send SCSI command */
		status = 1;
		w_ctr(ppb, 0x0c);
		क्रम (l = 0; (l < 6) && (status); l++)
			status = ppa_out(dev, cmd, 1);

		अगर (!status) अणु
			ppa_disconnect(dev);
			ppa_connect(dev, CONNECT_EPP_MAYBE);
			w_dtr(ppb, 0x40);
			w_ctr(ppb, 0x08);
			udelay(30);
			w_ctr(ppb, 0x0c);
			udelay(1000);
			ppa_disconnect(dev);
			udelay(1000);
			अगर (dev->mode == PPA_EPP_32) अणु
				dev->mode = old_mode;
				जाओ second_pass;
			पूर्ण
			वापस -EIO;
		पूर्ण
		w_ctr(ppb, 0x0c);
		k = 1000000;	/* 1 Second */
		करो अणु
			l = r_str(ppb);
			k--;
			udelay(1);
		पूर्ण जबतक (!(l & 0x80) && (k));

		l &= 0xf0;

		अगर (l != 0xf0) अणु
			ppa_disconnect(dev);
			ppa_connect(dev, CONNECT_EPP_MAYBE);
			ppa_reset_pulse(ppb);
			udelay(1000);
			ppa_disconnect(dev);
			udelay(1000);
			अगर (dev->mode == PPA_EPP_32) अणु
				dev->mode = old_mode;
				जाओ second_pass;
			पूर्ण
			वापस -EIO;
		पूर्ण
		ppa_disconnect(dev);
		prपूर्णांकk(KERN_INFO "ppa: Communication established with ID %i using %s\n",
		       loop, PPA_MODE_STRING[dev->mode]);
		ppa_connect(dev, CONNECT_EPP_MAYBE);
		ppa_reset_pulse(ppb);
		udelay(1000);
		ppa_disconnect(dev);
		udelay(1000);
		वापस 0;
	पूर्ण
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक ppa_adjust_queue(काष्ठा scsi_device *device)
अणु
	blk_queue_bounce_limit(device->request_queue, BLK_BOUNCE_HIGH);
	वापस 0;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा ppa_ढाँचा = अणु
	.module			= THIS_MODULE,
	.proc_name		= "ppa",
	.show_info		= ppa_show_info,
	.ग_लिखो_info		= ppa_ग_लिखो_info,
	.name			= "Iomega VPI0 (ppa) interface",
	.queuecommand		= ppa_queuecommand,
	.eh_पात_handler	= ppa_पात,
	.eh_host_reset_handler	= ppa_reset,
	.bios_param		= ppa_biosparam,
	.this_id		= -1,
	.sg_tablesize		= SG_ALL,
	.can_queue		= 1,
	.slave_alloc		= ppa_adjust_queue,
पूर्ण;

/***************************************************************************
 *                   Parallel port probing routines                        *
 ***************************************************************************/

अटल LIST_HEAD(ppa_hosts);

/*
 * Finds the first available device number that can be alloted to the
 * new ppa device and वापसs the address of the previous node so that
 * we can add to the tail and have a list in the ascending order.
 */

अटल अंतरभूत ppa_काष्ठा *find_parent(व्योम)
अणु
	ppa_काष्ठा *dev, *par = शून्य;
	अचिन्हित पूर्णांक cnt = 0;

	अगर (list_empty(&ppa_hosts))
		वापस शून्य;

	list_क्रम_each_entry(dev, &ppa_hosts, list) अणु
		अगर (dev->dev_no != cnt)
			वापस par;
		cnt++;
		par = dev;
	पूर्ण

	वापस par;
पूर्ण

अटल पूर्णांक __ppa_attach(काष्ठा parport *pb)
अणु
	काष्ठा Scsi_Host *host;
	DECLARE_WAIT_QUEUE_HEAD_ONSTACK(रुकोing);
	DEFINE_WAIT(रुको);
	ppa_काष्ठा *dev, *temp;
	पूर्णांक ports;
	पूर्णांक modes, ppb, ppb_hi;
	पूर्णांक err = -ENOMEM;
	काष्ठा pardev_cb ppa_cb;

	dev = kzalloc(माप(ppa_काष्ठा), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;
	dev->base = -1;
	dev->mode = PPA_AUTODETECT;
	dev->recon_पंचांगo = PPA_RECON_TMO;
	init_रुकोqueue_head(&रुकोing);
	temp = find_parent();
	अगर (temp)
		dev->dev_no = temp->dev_no + 1;

	स_रखो(&ppa_cb, 0, माप(ppa_cb));
	ppa_cb.निजी = dev;
	ppa_cb.wakeup = ppa_wakeup;

	dev->dev = parport_रेजिस्टर_dev_model(pb, "ppa", &ppa_cb, dev->dev_no);

	अगर (!dev->dev)
		जाओ out;

	/* Claim the bus so it remembers what we करो to the control
	 * रेजिस्टरs. [ CTR and ECP ]
	 */
	err = -EBUSY;
	dev->रुकोing = &रुकोing;
	prepare_to_रुको(&रुकोing, &रुको, TASK_UNINTERRUPTIBLE);
	अगर (ppa_pb_claim(dev))
		schedule_समयout(3 * HZ);
	अगर (dev->wanted) अणु
		prपूर्णांकk(KERN_ERR "ppa%d: failed to claim parport because "
				"a pardevice is owning the port for too long "
				"time!\n", pb->number);
		ppa_pb_dismiss(dev);
		dev->रुकोing = शून्य;
		finish_रुको(&रुकोing, &रुको);
		जाओ out1;
	पूर्ण
	dev->रुकोing = शून्य;
	finish_रुको(&रुकोing, &रुको);
	ppb = dev->base = dev->dev->port->base;
	ppb_hi = dev->dev->port->base_hi;
	w_ctr(ppb, 0x0c);
	modes = dev->dev->port->modes;

	/* Mode detection works up the chain of speed
	 * This aव्योमs a nasty अगर-then-अन्यथा-अगर-... tree
	 */
	dev->mode = PPA_NIBBLE;

	अगर (modes & PARPORT_MODE_TRISTATE)
		dev->mode = PPA_PS2;

	अगर (modes & PARPORT_MODE_ECP) अणु
		w_ecr(ppb_hi, 0x20);
		dev->mode = PPA_PS2;
	पूर्ण
	अगर ((modes & PARPORT_MODE_EPP) && (modes & PARPORT_MODE_ECP))
		w_ecr(ppb_hi, 0x80);

	/* Done configuration */

	err = ppa_init(dev);
	ppa_pb_release(dev);

	अगर (err)
		जाओ out1;

	/* now the glue ... */
	अगर (dev->mode == PPA_NIBBLE || dev->mode == PPA_PS2)
		ports = 3;
	अन्यथा
		ports = 8;

	INIT_DELAYED_WORK(&dev->ppa_tq, ppa_पूर्णांकerrupt);

	err = -ENOMEM;
	host = scsi_host_alloc(&ppa_ढाँचा, माप(ppa_काष्ठा *));
	अगर (!host)
		जाओ out1;
	host->io_port = pb->base;
	host->n_io_port = ports;
	host->dma_channel = -1;
	host->unique_id = pb->number;
	*(ppa_काष्ठा **)&host->hostdata = dev;
	dev->host = host;
	list_add_tail(&dev->list, &ppa_hosts);
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

अटल व्योम ppa_attach(काष्ठा parport *pb)
अणु
	__ppa_attach(pb);
पूर्ण

अटल व्योम ppa_detach(काष्ठा parport *pb)
अणु
	ppa_काष्ठा *dev;
	list_क्रम_each_entry(dev, &ppa_hosts, list) अणु
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

अटल काष्ठा parport_driver ppa_driver = अणु
	.name		= "ppa",
	.match_port	= ppa_attach,
	.detach		= ppa_detach,
	.devmodel	= true,
पूर्ण;

अटल पूर्णांक __init ppa_driver_init(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "ppa: Version %s\n", PPA_VERSION);
	वापस parport_रेजिस्टर_driver(&ppa_driver);
पूर्ण

अटल व्योम __निकास ppa_driver_निकास(व्योम)
अणु
	parport_unरेजिस्टर_driver(&ppa_driver);
पूर्ण

module_init(ppa_driver_init);
module_निकास(ppa_driver_निकास);
MODULE_LICENSE("GPL");
