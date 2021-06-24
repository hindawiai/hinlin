<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*                                              -*- linux-c -*-
 * dtlk.c - DoubleTalk PC driver क्रम Linux
 *
 * Original author: Chris Pallotta <chris@allmedia.com>
 * Current मुख्यtainer: Jim Van Zandt <jrv@vanzandt.mv.com>
 * 
 * 2000-03-18 Jim Van Zandt: Fix polling.
 *  Eliminate dtlk_समयr_active flag and separate dtlk_stop_समयr
 *  function.  Don't restart समयr in dtlk_समयr_tick.  Restart समयr
 *  in dtlk_poll after every poll.  dtlk_poll वापसs mask (duh).
 *  Eliminate unused function dtlk_ग_लिखो_byte.  Misc. code cleanups.
 */

/* This driver is क्रम the DoubleTalk PC, a speech synthesizer
   manufactured by RC Systems (http://www.rcsys.com/).  It was written
   based on करोcumentation in their User's Manual file and Developer's
   Tools disk.

   The DoubleTalk PC contains four voice synthesizers: text-to-speech
   (TTS), linear predictive coding (LPC), PCM/ADPCM, and CVSD.  It
   also has a tone generator.  Output data क्रम LPC are written to the
   LPC port, and output data क्रम the other modes are written to the
   TTS port.

   Two kinds of data can be पढ़ो from the DoubleTalk: status
   inक्रमmation (in response to the "\001?" पूर्णांकerrogation command) is
   पढ़ो from the TTS port, and index markers (which mark the progress
   of the speech) are पढ़ो from the LPC port.  Not all models of the
   DoubleTalk PC implement index markers.  Both the TTS and LPC ports
   can also display status flags.

   The DoubleTalk PC generates no पूर्णांकerrupts.

   These अक्षरacteristics are mapped पूर्णांकo the Unix stream I/O model as
   follows:

   "write" sends bytes to the TTS port.  It is the responsibility of
   the user program to चयन modes among TTS, PCM/ADPCM, and CVSD.
   This driver was written क्रम use with the text-to-speech
   synthesizer.  If LPC output is needed some day, other minor device
   numbers can be used to select among output modes.

   "read" माला_लो index markers from the LPC port.  If the device करोes
   not implement index markers, the पढ़ो will fail with error EINVAL.

   Status inक्रमmation is available using the DTLK_INTERROGATE ioctl.

 */

#समावेश <linux/module.h>

#घोषणा KERNEL
#समावेश <linux/types.h>
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/त्रुटिसं.स>	/* क्रम -EBUSY */
#समावेश <linux/ioport.h>	/* क्रम request_region */
#समावेश <linux/delay.h>	/* क्रम loops_per_jअगरfy */
#समावेश <linux/sched.h>
#समावेश <linux/mutex.h>
#समावेश <यंत्र/पन.स>		/* क्रम inb_p, outb_p, inb, outb, etc. */
#समावेश <linux/uaccess.h>	/* क्रम get_user, etc. */
#समावेश <linux/रुको.h>		/* क्रम रुको_queue */
#समावेश <linux/init.h>		/* क्रम __init, module_अणुinit,निकासपूर्ण */
#समावेश <linux/poll.h>		/* क्रम EPOLLIN, etc. */
#समावेश <linux/dtlk.h>		/* local header file क्रम DoubleTalk values */

#अगर_घोषित TRACING
#घोषणा TRACE_TEXT(str) prपूर्णांकk(str);
#घोषणा TRACE_RET prपूर्णांकk(")")
#अन्यथा				/* !TRACING */
#घोषणा TRACE_TEXT(str) ((व्योम) 0)
#घोषणा TRACE_RET ((व्योम) 0)
#पूर्ण_अगर				/* TRACING */

अटल DEFINE_MUTEX(dtlk_mutex);
अटल व्योम dtlk_समयr_tick(काष्ठा समयr_list *unused);

अटल पूर्णांक dtlk_major;
अटल पूर्णांक dtlk_port_lpc;
अटल पूर्णांक dtlk_port_tts;
अटल पूर्णांक dtlk_busy;
अटल पूर्णांक dtlk_has_indexing;
अटल अचिन्हित पूर्णांक dtlk_portlist[] =
अणु0x25e, 0x29e, 0x2de, 0x31e, 0x35e, 0x39e, 0पूर्ण;
अटल रुको_queue_head_t dtlk_process_list;
अटल DEFINE_TIMER(dtlk_समयr, dtlk_समयr_tick);

/* prototypes क्रम file_operations काष्ठा */
अटल sमाप_प्रकार dtlk_पढ़ो(काष्ठा file *, अक्षर __user *,
			 माप_प्रकार nbytes, loff_t * ppos);
अटल sमाप_प्रकार dtlk_ग_लिखो(काष्ठा file *, स्थिर अक्षर __user *,
			  माप_प्रकार nbytes, loff_t * ppos);
अटल __poll_t dtlk_poll(काष्ठा file *, poll_table *);
अटल पूर्णांक dtlk_खोलो(काष्ठा inode *, काष्ठा file *);
अटल पूर्णांक dtlk_release(काष्ठा inode *, काष्ठा file *);
अटल दीर्घ dtlk_ioctl(काष्ठा file *file,
		       अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);

अटल स्थिर काष्ठा file_operations dtlk_fops =
अणु
	.owner		= THIS_MODULE,
	.पढ़ो		= dtlk_पढ़ो,
	.ग_लिखो		= dtlk_ग_लिखो,
	.poll		= dtlk_poll,
	.unlocked_ioctl	= dtlk_ioctl,
	.खोलो		= dtlk_खोलो,
	.release	= dtlk_release,
	.llseek		= no_llseek,
पूर्ण;

/* local prototypes */
अटल पूर्णांक dtlk_dev_probe(व्योम);
अटल काष्ठा dtlk_settings *dtlk_पूर्णांकerrogate(व्योम);
अटल पूर्णांक dtlk_पढ़ोable(व्योम);
अटल अक्षर dtlk_पढ़ो_lpc(व्योम);
अटल अक्षर dtlk_पढ़ो_tts(व्योम);
अटल पूर्णांक dtlk_ग_लिखोable(व्योम);
अटल अक्षर dtlk_ग_लिखो_bytes(स्थिर अक्षर *buf, पूर्णांक n);
अटल अक्षर dtlk_ग_लिखो_tts(अक्षर);
/*
   अटल व्योम dtlk_handle_error(अक्षर, अक्षर, अचिन्हित पूर्णांक);
 */

अटल sमाप_प्रकार dtlk_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			 माप_प्रकार count, loff_t * ppos)
अणु
	अचिन्हित पूर्णांक minor = iminor(file_inode(file));
	अक्षर ch;
	पूर्णांक i = 0, retries;

	TRACE_TEXT("(dtlk_read");
	/*  prपूर्णांकk("DoubleTalk PC - dtlk_read()\n"); */

	अगर (minor != DTLK_MINOR || !dtlk_has_indexing)
		वापस -EINVAL;

	क्रम (retries = 0; retries < loops_per_jअगरfy; retries++) अणु
		जबतक (i < count && dtlk_पढ़ोable()) अणु
			ch = dtlk_पढ़ो_lpc();
			/*        prपूर्णांकk("dtlk_read() reads 0x%02x\n", ch); */
			अगर (put_user(ch, buf++))
				वापस -EFAULT;
			i++;
		पूर्ण
		अगर (i)
			वापस i;
		अगर (file->f_flags & O_NONBLOCK)
			अवरोध;
		msleep_पूर्णांकerruptible(100);
	पूर्ण
	अगर (retries == loops_per_jअगरfy)
		prपूर्णांकk(KERN_ERR "dtlk_read times out\n");
	TRACE_RET;
	वापस -EAGAIN;
पूर्ण

अटल sमाप_प्रकार dtlk_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			  माप_प्रकार count, loff_t * ppos)
अणु
	पूर्णांक i = 0, retries = 0, ch;

	TRACE_TEXT("(dtlk_write");
#अगर_घोषित TRACING
	prपूर्णांकk(" \"");
	अणु
		पूर्णांक i, ch;
		क्रम (i = 0; i < count; i++) अणु
			अगर (get_user(ch, buf + i))
				वापस -EFAULT;
			अगर (' ' <= ch && ch <= '~')
				prपूर्णांकk("%c", ch);
			अन्यथा
				prपूर्णांकk("\\%03o", ch);
		पूर्ण
		prपूर्णांकk("\"");
	पूर्ण
#पूर्ण_अगर

	अगर (iminor(file_inode(file)) != DTLK_MINOR)
		वापस -EINVAL;

	जबतक (1) अणु
		जबतक (i < count && !get_user(ch, buf) &&
		       (ch == DTLK_CLEAR || dtlk_ग_लिखोable())) अणु
			dtlk_ग_लिखो_tts(ch);
			buf++;
			i++;
			अगर (i % 5 == 0)
				/* We yield our समय until scheduled
				   again.  This reduces the transfer
				   rate to 500 bytes/sec, but that's
				   still enough to keep up with the
				   speech synthesizer. */
				msleep_पूर्णांकerruptible(1);
			अन्यथा अणु
				/* the RDY bit goes zero 2-3 usec
				   after writing, and goes 1 again
				   180-190 usec later.  Here, we रुको
				   up to 250 usec क्रम the RDY bit to
				   go nonzero. */
				क्रम (retries = 0;
				     retries < loops_per_jअगरfy / (4000/HZ);
				     retries++)
					अगर (inb_p(dtlk_port_tts) &
					    TTS_WRITABLE)
						अवरोध;
			पूर्ण
			retries = 0;
		पूर्ण
		अगर (i == count)
			वापस i;
		अगर (file->f_flags & O_NONBLOCK)
			अवरोध;

		msleep_पूर्णांकerruptible(1);

		अगर (++retries > 10 * HZ) अणु /* रुको no more than 10 sec
					      from last ग_लिखो */
			prपूर्णांकk("dtlk: write timeout.  "
			       "inb_p(dtlk_port_tts) = 0x%02x\n",
			       inb_p(dtlk_port_tts));
			TRACE_RET;
			वापस -EBUSY;
		पूर्ण
	पूर्ण
	TRACE_RET;
	वापस -EAGAIN;
पूर्ण

अटल __poll_t dtlk_poll(काष्ठा file *file, poll_table * रुको)
अणु
	__poll_t mask = 0;
	अचिन्हित दीर्घ expires;

	TRACE_TEXT(" dtlk_poll");
	/*
	   अटल दीर्घ पूर्णांक j;
	   prपूर्णांकk(".");
	   prपूर्णांकk("<%ld>", jअगरfies-j);
	   j=jअगरfies;
	 */
	poll_रुको(file, &dtlk_process_list, रुको);

	अगर (dtlk_has_indexing && dtlk_पढ़ोable()) अणु
	        del_समयr(&dtlk_समयr);
		mask = EPOLLIN | EPOLLRDNORM;
	पूर्ण
	अगर (dtlk_ग_लिखोable()) अणु
	        del_समयr(&dtlk_समयr);
		mask |= EPOLLOUT | EPOLLWRNORM;
	पूर्ण
	/* there are no exception conditions */

	/* There won't be any पूर्णांकerrupts, so we set a समयr instead. */
	expires = jअगरfies + 3*HZ / 100;
	mod_समयr(&dtlk_समयr, expires);

	वापस mask;
पूर्ण

अटल व्योम dtlk_समयr_tick(काष्ठा समयr_list *unused)
अणु
	TRACE_TEXT(" dtlk_timer_tick");
	wake_up_पूर्णांकerruptible(&dtlk_process_list);
पूर्ण

अटल दीर्घ dtlk_ioctl(काष्ठा file *file,
		       अचिन्हित पूर्णांक cmd,
		       अचिन्हित दीर्घ arg)
अणु
	अक्षर __user *argp = (अक्षर __user *)arg;
	काष्ठा dtlk_settings *sp;
	अक्षर portval;
	TRACE_TEXT(" dtlk_ioctl");

	चयन (cmd) अणु

	हाल DTLK_INTERROGATE:
		mutex_lock(&dtlk_mutex);
		sp = dtlk_पूर्णांकerrogate();
		mutex_unlock(&dtlk_mutex);
		अगर (copy_to_user(argp, sp, माप(काष्ठा dtlk_settings)))
			वापस -EINVAL;
		वापस 0;

	हाल DTLK_STATUS:
		portval = inb_p(dtlk_port_tts);
		वापस put_user(portval, argp);

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/* Note that nobody ever sets dtlk_busy... */
अटल पूर्णांक dtlk_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	TRACE_TEXT("(dtlk_open");

	चयन (iminor(inode)) अणु
	हाल DTLK_MINOR:
		अगर (dtlk_busy)
			वापस -EBUSY;
		वापस stream_खोलो(inode, file);

	शेष:
		वापस -ENXIO;
	पूर्ण
पूर्ण

अटल पूर्णांक dtlk_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	TRACE_TEXT("(dtlk_release");

	चयन (iminor(inode)) अणु
	हाल DTLK_MINOR:
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
	TRACE_RET;
	
	del_समयr_sync(&dtlk_समयr);

	वापस 0;
पूर्ण

अटल पूर्णांक __init dtlk_init(व्योम)
अणु
	पूर्णांक err;

	dtlk_port_lpc = 0;
	dtlk_port_tts = 0;
	dtlk_busy = 0;
	dtlk_major = रेजिस्टर_chrdev(0, "dtlk", &dtlk_fops);
	अगर (dtlk_major < 0) अणु
		prपूर्णांकk(KERN_ERR "DoubleTalk PC - cannot register device\n");
		वापस dtlk_major;
	पूर्ण
	err = dtlk_dev_probe();
	अगर (err) अणु
		unरेजिस्टर_chrdev(dtlk_major, "dtlk");
		वापस err;
	पूर्ण
	prपूर्णांकk(", MAJOR %d\n", dtlk_major);

	init_रुकोqueue_head(&dtlk_process_list);

	वापस 0;
पूर्ण

अटल व्योम __निकास dtlk_cleanup (व्योम)
अणु
	dtlk_ग_लिखो_bytes("goodbye", 8);
	msleep_पूर्णांकerruptible(500);		/* nap 0.50 sec but
						   could be awakened
						   earlier by
						   संकेतs... */

	dtlk_ग_लिखो_tts(DTLK_CLEAR);
	unरेजिस्टर_chrdev(dtlk_major, "dtlk");
	release_region(dtlk_port_lpc, DTLK_IO_EXTENT);
पूर्ण

module_init(dtlk_init);
module_निकास(dtlk_cleanup);

/* ------------------------------------------------------------------------ */

अटल पूर्णांक dtlk_पढ़ोable(व्योम)
अणु
#अगर_घोषित TRACING
	prपूर्णांकk(" dtlk_readable=%u@%u", inb_p(dtlk_port_lpc) != 0x7f, jअगरfies);
#पूर्ण_अगर
	वापस inb_p(dtlk_port_lpc) != 0x7f;
पूर्ण

अटल पूर्णांक dtlk_ग_लिखोable(व्योम)
अणु
	/* TRACE_TEXT(" dtlk_writeable"); */
#अगर_घोषित TRACINGMORE
	prपूर्णांकk(" dtlk_writeable=%u", (inb_p(dtlk_port_tts) & TTS_WRITABLE)!=0);
#पूर्ण_अगर
	वापस inb_p(dtlk_port_tts) & TTS_WRITABLE;
पूर्ण

अटल पूर्णांक __init dtlk_dev_probe(व्योम)
अणु
	अचिन्हित पूर्णांक testval = 0;
	पूर्णांक i = 0;
	काष्ठा dtlk_settings *sp;

	अगर (dtlk_port_lpc | dtlk_port_tts)
		वापस -EBUSY;

	क्रम (i = 0; dtlk_portlist[i]; i++) अणु
#अगर 0
		prपूर्णांकk("DoubleTalk PC - Port %03x = %04x\n",
		       dtlk_portlist[i], (testval = inw_p(dtlk_portlist[i])));
#पूर्ण_अगर

		अगर (!request_region(dtlk_portlist[i], DTLK_IO_EXTENT, 
			       "dtlk"))
			जारी;
		testval = inw_p(dtlk_portlist[i]);
		अगर ((testval &= 0xfbff) == 0x107f) अणु
			dtlk_port_lpc = dtlk_portlist[i];
			dtlk_port_tts = dtlk_port_lpc + 1;

			sp = dtlk_पूर्णांकerrogate();
			prपूर्णांकk("DoubleTalk PC at %03x-%03x, "
			       "ROM version %s, serial number %u",
			       dtlk_portlist[i], dtlk_portlist[i] +
			       DTLK_IO_EXTENT - 1,
			       sp->rom_version, sp->serial_number);

                        /* put LPC port पूर्णांकo known state, so
			   dtlk_पढ़ोable() gives valid result */
			outb_p(0xff, dtlk_port_lpc); 

                        /* INIT string and index marker */
			dtlk_ग_लिखो_bytes("\036\1@\0\0012I\r", 8);
			/* posting an index takes 18 msec.  Here, we
			   रुको up to 100 msec to see whether it
			   appears. */
			msleep_पूर्णांकerruptible(100);
			dtlk_has_indexing = dtlk_पढ़ोable();
#अगर_घोषित TRACING
			prपूर्णांकk(", indexing %d\n", dtlk_has_indexing);
#पूर्ण_अगर
#अगर_घोषित INSCOPE
			अणु
/* This macro records ten samples पढ़ो from the LPC port, क्रम later display */
#घोषणा LOOK					\
क्रम (i = 0; i < 10; i++)			\
  अणु						\
    buffer[b++] = inb_p(dtlk_port_lpc);		\
    __delay(loops_per_jअगरfy/(1000000/HZ));             \
  पूर्ण
				अक्षर buffer[1000];
				पूर्णांक b = 0, i, j;

				LOOK
				outb_p(0xff, dtlk_port_lpc);
				buffer[b++] = 0;
				LOOK
				dtlk_ग_लिखो_bytes("\0012I\r", 4);
				buffer[b++] = 0;
				__delay(50 * loops_per_jअगरfy / (1000/HZ));
				outb_p(0xff, dtlk_port_lpc);
				buffer[b++] = 0;
				LOOK

				prपूर्णांकk("\n");
				क्रम (j = 0; j < b; j++)
					prपूर्णांकk(" %02x", buffer[j]);
				prपूर्णांकk("\n");
			पूर्ण
#पूर्ण_अगर				/* INSCOPE */

#अगर_घोषित OUTSCOPE
			अणु
/* This macro records ten samples पढ़ो from the TTS port, क्रम later display */
#घोषणा LOOK					\
क्रम (i = 0; i < 10; i++)			\
  अणु						\
    buffer[b++] = inb_p(dtlk_port_tts);		\
    __delay(loops_per_jअगरfy/(1000000/HZ));  /* 1 us */ \
  पूर्ण
				अक्षर buffer[1000];
				पूर्णांक b = 0, i, j;

				mdelay(10);	/* 10 ms */
				LOOK
				outb_p(0x03, dtlk_port_tts);
				buffer[b++] = 0;
				LOOK
				LOOK

				prपूर्णांकk("\n");
				क्रम (j = 0; j < b; j++)
					prपूर्णांकk(" %02x", buffer[j]);
				prपूर्णांकk("\n");
			पूर्ण
#पूर्ण_अगर				/* OUTSCOPE */

			dtlk_ग_लिखो_bytes("Double Talk found", 18);

			वापस 0;
		पूर्ण
		release_region(dtlk_portlist[i], DTLK_IO_EXTENT);
	पूर्ण

	prपूर्णांकk(KERN_INFO "DoubleTalk PC - not found\n");
	वापस -ENODEV;
पूर्ण

/*
   अटल व्योम dtlk_handle_error(अक्षर op, अक्षर rc, अचिन्हित पूर्णांक minor)
   अणु
   prपूर्णांकk(KERN_INFO"\nDoubleTalk PC - MINOR: %d, OPCODE: %d, ERROR: %d\n", 
   minor, op, rc);
   वापस;
   पूर्ण
 */

/* पूर्णांकerrogate the DoubleTalk PC and वापस its settings */
अटल काष्ठा dtlk_settings *dtlk_पूर्णांकerrogate(व्योम)
अणु
	अचिन्हित अक्षर *t;
	अटल अक्षर buf[माप(काष्ठा dtlk_settings) + 1];
	पूर्णांक total, i;
	अटल काष्ठा dtlk_settings status;
	TRACE_TEXT("(dtlk_interrogate");
	dtlk_ग_लिखो_bytes("\030\001?", 3);
	क्रम (total = 0, i = 0; i < 50; i++) अणु
		buf[total] = dtlk_पढ़ो_tts();
		अगर (total > 2 && buf[total] == 0x7f)
			अवरोध;
		अगर (total < माप(काष्ठा dtlk_settings))
			total++;
	पूर्ण
	/*
	   अगर (i==50) prपूर्णांकk("interrogate() read overrun\n");
	   क्रम (i=0; i<माप(buf); i++)
	   prपूर्णांकk(" %02x", buf[i]);
	   prपूर्णांकk("\n");
	 */
	t = buf;
	status.serial_number = t[0] + t[1] * 256; /* serial number is
						     little endian */
	t += 2;

	i = 0;
	जबतक (*t != '\r') अणु
		status.rom_version[i] = *t;
		अगर (i < माप(status.rom_version) - 1)
			i++;
		t++;
	पूर्ण
	status.rom_version[i] = 0;
	t++;

	status.mode = *t++;
	status.punc_level = *t++;
	status.क्रमmant_freq = *t++;
	status.pitch = *t++;
	status.speed = *t++;
	status.volume = *t++;
	status.tone = *t++;
	status.expression = *t++;
	status.ext_dict_loaded = *t++;
	status.ext_dict_status = *t++;
	status.मुक्त_ram = *t++;
	status.articulation = *t++;
	status.reverb = *t++;
	status.eob = *t++;
	status.has_indexing = dtlk_has_indexing;
	TRACE_RET;
	वापस &status;
पूर्ण

अटल अक्षर dtlk_पढ़ो_tts(व्योम)
अणु
	पूर्णांक portval, retries = 0;
	अक्षर ch;
	TRACE_TEXT("(dtlk_read_tts");

	/* verअगरy DT is पढ़ोy, पढ़ो अक्षर, रुको क्रम ACK */
	करो अणु
		portval = inb_p(dtlk_port_tts);
	पूर्ण जबतक ((portval & TTS_READABLE) == 0 &&
		 retries++ < DTLK_MAX_RETRIES);
	अगर (retries > DTLK_MAX_RETRIES)
		prपूर्णांकk(KERN_ERR "dtlk_read_tts() timeout\n");

	ch = inb_p(dtlk_port_tts);	/* input from TTS port */
	ch &= 0x7f;
	outb_p(ch, dtlk_port_tts);

	retries = 0;
	करो अणु
		portval = inb_p(dtlk_port_tts);
	पूर्ण जबतक ((portval & TTS_READABLE) != 0 &&
		 retries++ < DTLK_MAX_RETRIES);
	अगर (retries > DTLK_MAX_RETRIES)
		prपूर्णांकk(KERN_ERR "dtlk_read_tts() timeout\n");

	TRACE_RET;
	वापस ch;
पूर्ण

अटल अक्षर dtlk_पढ़ो_lpc(व्योम)
अणु
	पूर्णांक retries = 0;
	अक्षर ch;
	TRACE_TEXT("(dtlk_read_lpc");

	/* no need to test -- this is only called when the port is पढ़ोable */

	ch = inb_p(dtlk_port_lpc);	/* input from LPC port */

	outb_p(0xff, dtlk_port_lpc);

	/* acknowledging a पढ़ो takes 3-4
	   usec.  Here, we रुको up to 20 usec
	   क्रम the acknowledgement */
	retries = (loops_per_jअगरfy * 20) / (1000000/HZ);
	जबतक (inb_p(dtlk_port_lpc) != 0x7f && --retries > 0);
	अगर (retries == 0)
		prपूर्णांकk(KERN_ERR "dtlk_read_lpc() timeout\n");

	TRACE_RET;
	वापस ch;
पूर्ण

/* ग_लिखो n bytes to tts port */
अटल अक्षर dtlk_ग_लिखो_bytes(स्थिर अक्षर *buf, पूर्णांक n)
अणु
	अक्षर val = 0;
	/*  prपूर्णांकk("dtlk_write_bytes(\"%-*s\", %d)\n", n, buf, n); */
	TRACE_TEXT("(dtlk_write_bytes");
	जबतक (n-- > 0)
		val = dtlk_ग_लिखो_tts(*buf++);
	TRACE_RET;
	वापस val;
पूर्ण

अटल अक्षर dtlk_ग_लिखो_tts(अक्षर ch)
अणु
	पूर्णांक retries = 0;
#अगर_घोषित TRACINGMORE
	prपूर्णांकk("  dtlk_write_tts(");
	अगर (' ' <= ch && ch <= '~')
		prपूर्णांकk("'%c'", ch);
	अन्यथा
		prपूर्णांकk("0x%02x", ch);
#पूर्ण_अगर
	अगर (ch != DTLK_CLEAR)	/* no flow control क्रम CLEAR command */
		जबतक ((inb_p(dtlk_port_tts) & TTS_WRITABLE) == 0 &&
		       retries++ < DTLK_MAX_RETRIES)	/* DT पढ़ोy? */
			;
	अगर (retries > DTLK_MAX_RETRIES)
		prपूर्णांकk(KERN_ERR "dtlk_write_tts() timeout\n");

	outb_p(ch, dtlk_port_tts);	/* output to TTS port */
	/* the RDY bit goes zero 2-3 usec after writing, and goes
	   1 again 180-190 usec later.  Here, we रुको up to 10
	   usec क्रम the RDY bit to go zero. */
	क्रम (retries = 0; retries < loops_per_jअगरfy / (100000/HZ); retries++)
		अगर ((inb_p(dtlk_port_tts) & TTS_WRITABLE) == 0)
			अवरोध;

#अगर_घोषित TRACINGMORE
	prपूर्णांकk(")\n");
#पूर्ण_अगर
	वापस 0;
पूर्ण

MODULE_LICENSE("GPL");
