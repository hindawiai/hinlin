<शैली गुरु>
/*
 * A driver क्रम the Omnikey PCMCIA smartcard पढ़ोer CardMan 4040
 *
 * (c) 2000-2004 Omnikey AG (http://www.omnikey.com/)
 *
 * (C) 2005-2006 Harald Welte <laक्रमge@gnumonks.org>
 * 	- add support क्रम poll()
 * 	- driver cleanup
 * 	- add रुकोqueues
 * 	- adhere to linux kernel coding style and policies
 * 	- support 2.6.13 "new style" pcmcia पूर्णांकerface
 * 	- add class पूर्णांकerface क्रम udev device creation
 *
 * The device basically is a USB CCID compliant device that has been
 * attached to an I/O-Mapped FIFO.
 *
 * All rights reserved, Dual BSD/GPL Licensed.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/fs.h>
#समावेश <linux/delay.h>
#समावेश <linux/poll.h>
#समावेश <linux/mutex.h>
#समावेश <linux/रुको.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पन.स>

#समावेश <pcmcia/cistpl.h>
#समावेश <pcmcia/cisreg.h>
#समावेश <pcmcia/ciscode.h>
#समावेश <pcmcia/ds.h>

#समावेश "cm4040_cs.h"


#घोषणा पढ़ोer_to_dev(x)	(&x->p_dev->dev)

/* n (debug level) is ignored */
/* additional debug output may be enabled by re-compiling with
 * CM4040_DEBUG set */
/* #घोषणा CM4040_DEBUG */
#घोषणा DEBUGP(n, rdr, x, args...) करो अणु 		\
		dev_dbg(पढ़ोer_to_dev(rdr), "%s:" x, 	\
			   __func__ , ## args);		\
	पूर्ण जबतक (0)

अटल DEFINE_MUTEX(cm4040_mutex);

#घोषणा	CCID_DRIVER_BULK_DEFAULT_TIMEOUT  	(150*HZ)
#घोषणा	CCID_DRIVER_ASYNC_POWERUP_TIMEOUT 	(35*HZ)
#घोषणा	CCID_DRIVER_MINIMUM_TIMEOUT 		(3*HZ)
#घोषणा READ_WRITE_BUFFER_SIZE 512
#घोषणा POLL_LOOP_COUNT				1000

/* how often to poll क्रम fअगरo status change */
#घोषणा POLL_PERIOD 				msecs_to_jअगरfies(10)

अटल व्योम पढ़ोer_release(काष्ठा pcmcia_device *link);

अटल पूर्णांक major;
अटल काष्ठा class *cmx_class;

#घोषणा		BS_READABLE	0x01
#घोषणा		BS_WRITABLE	0x02

काष्ठा पढ़ोer_dev अणु
	काष्ठा pcmcia_device	*p_dev;
	रुको_queue_head_t	devq;
	रुको_queue_head_t	poll_रुको;
	रुको_queue_head_t	पढ़ो_रुको;
	रुको_queue_head_t	ग_लिखो_रुको;
	अचिन्हित दीर्घ 	  	buffer_status;
	अचिन्हित दीर्घ     	समयout;
	अचिन्हित अक्षर     	s_buf[READ_WRITE_BUFFER_SIZE];
	अचिन्हित अक्षर     	r_buf[READ_WRITE_BUFFER_SIZE];
	काष्ठा समयr_list 	poll_समयr;
पूर्ण;

अटल काष्ठा pcmcia_device *dev_table[CM_MAX_DEV];

#अगर_अघोषित CM4040_DEBUG
#घोषणा	xoutb	outb
#घोषणा	xinb	inb
#अन्यथा
अटल अंतरभूत व्योम xoutb(अचिन्हित अक्षर val, अचिन्हित लघु port)
अणु
	pr_debug("outb(val=%.2x,port=%.4x)\n", val, port);
	outb(val, port);
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर xinb(अचिन्हित लघु port)
अणु
	अचिन्हित अक्षर val;

	val = inb(port);
	pr_debug("%.2x=inb(%.4x)\n", val, port);
	वापस val;
पूर्ण
#पूर्ण_अगर

/* poll the device fअगरo status रेजिस्टर.  not to be confused with
 * the poll syscall. */
अटल व्योम cm4040_करो_poll(काष्ठा समयr_list *t)
अणु
	काष्ठा पढ़ोer_dev *dev = from_समयr(dev, t, poll_समयr);
	अचिन्हित पूर्णांक obs = xinb(dev->p_dev->resource[0]->start
				+ REG_OFFSET_BUFFER_STATUS);

	अगर ((obs & BSR_BULK_IN_FULL)) अणु
		set_bit(BS_READABLE, &dev->buffer_status);
		DEBUGP(4, dev, "waking up read_wait\n");
		wake_up_पूर्णांकerruptible(&dev->पढ़ो_रुको);
	पूर्ण अन्यथा
		clear_bit(BS_READABLE, &dev->buffer_status);

	अगर (!(obs & BSR_BULK_OUT_FULL)) अणु
		set_bit(BS_WRITABLE, &dev->buffer_status);
		DEBUGP(4, dev, "waking up write_wait\n");
		wake_up_पूर्णांकerruptible(&dev->ग_लिखो_रुको);
	पूर्ण अन्यथा
		clear_bit(BS_WRITABLE, &dev->buffer_status);

	अगर (dev->buffer_status)
		wake_up_पूर्णांकerruptible(&dev->poll_रुको);

	mod_समयr(&dev->poll_समयr, jअगरfies + POLL_PERIOD);
पूर्ण

अटल व्योम cm4040_stop_poll(काष्ठा पढ़ोer_dev *dev)
अणु
	del_समयr_sync(&dev->poll_समयr);
पूर्ण

अटल पूर्णांक रुको_क्रम_bulk_out_पढ़ोy(काष्ठा पढ़ोer_dev *dev)
अणु
	पूर्णांक i, rc;
	पूर्णांक iobase = dev->p_dev->resource[0]->start;

	क्रम (i = 0; i < POLL_LOOP_COUNT; i++) अणु
		अगर ((xinb(iobase + REG_OFFSET_BUFFER_STATUS)
		    & BSR_BULK_OUT_FULL) == 0) अणु
			DEBUGP(4, dev, "BulkOut empty (i=%d)\n", i);
			वापस 1;
		पूर्ण
	पूर्ण

	DEBUGP(4, dev, "wait_event_interruptible_timeout(timeout=%ld\n",
		dev->समयout);
	rc = रुको_event_पूर्णांकerruptible_समयout(dev->ग_लिखो_रुको,
					      test_and_clear_bit(BS_WRITABLE,
						       &dev->buffer_status),
					      dev->समयout);

	अगर (rc > 0)
		DEBUGP(4, dev, "woke up: BulkOut empty\n");
	अन्यथा अगर (rc == 0)
		DEBUGP(4, dev, "woke up: BulkOut full, returning 0 :(\n");
	अन्यथा अगर (rc < 0)
		DEBUGP(4, dev, "woke up: signal arrived\n");

	वापस rc;
पूर्ण

/* Write to Sync Control Register */
अटल पूर्णांक ग_लिखो_sync_reg(अचिन्हित अक्षर val, काष्ठा पढ़ोer_dev *dev)
अणु
	पूर्णांक iobase = dev->p_dev->resource[0]->start;
	पूर्णांक rc;

	rc = रुको_क्रम_bulk_out_पढ़ोy(dev);
	अगर (rc <= 0)
		वापस rc;

	xoutb(val, iobase + REG_OFFSET_SYNC_CONTROL);
	rc = रुको_क्रम_bulk_out_पढ़ोy(dev);
	अगर (rc <= 0)
		वापस rc;

	वापस 1;
पूर्ण

अटल पूर्णांक रुको_क्रम_bulk_in_पढ़ोy(काष्ठा पढ़ोer_dev *dev)
अणु
	पूर्णांक i, rc;
	पूर्णांक iobase = dev->p_dev->resource[0]->start;

	क्रम (i = 0; i < POLL_LOOP_COUNT; i++) अणु
		अगर ((xinb(iobase + REG_OFFSET_BUFFER_STATUS)
		    & BSR_BULK_IN_FULL) == BSR_BULK_IN_FULL) अणु
			DEBUGP(3, dev, "BulkIn full (i=%d)\n", i);
			वापस 1;
		पूर्ण
	पूर्ण

	DEBUGP(4, dev, "wait_event_interruptible_timeout(timeout=%ld\n",
		dev->समयout);
	rc = रुको_event_पूर्णांकerruptible_समयout(dev->पढ़ो_रुको,
					      test_and_clear_bit(BS_READABLE,
						 	&dev->buffer_status),
					      dev->समयout);
	अगर (rc > 0)
		DEBUGP(4, dev, "woke up: BulkIn full\n");
	अन्यथा अगर (rc == 0)
		DEBUGP(4, dev, "woke up: BulkIn not full, returning 0 :(\n");
	अन्यथा अगर (rc < 0)
		DEBUGP(4, dev, "woke up: signal arrived\n");

	वापस rc;
पूर्ण

अटल sमाप_प्रकार cm4040_पढ़ो(काष्ठा file *filp, अक्षर __user *buf,
			माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा पढ़ोer_dev *dev = filp->निजी_data;
	पूर्णांक iobase = dev->p_dev->resource[0]->start;
	माप_प्रकार bytes_to_पढ़ो;
	अचिन्हित दीर्घ i;
	माप_प्रकार min_bytes_to_पढ़ो;
	पूर्णांक rc;
	अचिन्हित अक्षर uc;

	DEBUGP(2, dev, "-> cm4040_read(%s,%d)\n", current->comm, current->pid);

	अगर (count == 0)
		वापस 0;

	अगर (count < 10)
		वापस -EFAULT;

	अगर (filp->f_flags & O_NONBLOCK) अणु
		DEBUGP(4, dev, "filep->f_flags O_NONBLOCK set\n");
		DEBUGP(2, dev, "<- cm4040_read (failure)\n");
		वापस -EAGAIN;
	पूर्ण

	अगर (!pcmcia_dev_present(dev->p_dev))
		वापस -ENODEV;

	क्रम (i = 0; i < 5; i++) अणु
		rc = रुको_क्रम_bulk_in_पढ़ोy(dev);
		अगर (rc <= 0) अणु
			DEBUGP(5, dev, "wait_for_bulk_in_ready rc=%.2x\n", rc);
			DEBUGP(2, dev, "<- cm4040_read (failed)\n");
			अगर (rc == -ERESTARTSYS)
				वापस rc;
			वापस -EIO;
		पूर्ण
	  	dev->r_buf[i] = xinb(iobase + REG_OFFSET_BULK_IN);
#अगर_घोषित CM4040_DEBUG
		pr_debug("%lu:%2x ", i, dev->r_buf[i]);
	पूर्ण
	pr_debug("\n");
#अन्यथा
	पूर्ण
#पूर्ण_अगर

	bytes_to_पढ़ो = 5 + le32_to_cpu(*(__le32 *)&dev->r_buf[1]);

	DEBUGP(6, dev, "BytesToRead=%zu\n", bytes_to_पढ़ो);

	min_bytes_to_पढ़ो = min(count, bytes_to_पढ़ो + 5);
	min_bytes_to_पढ़ो = min_t(माप_प्रकार, min_bytes_to_पढ़ो, READ_WRITE_BUFFER_SIZE);

	DEBUGP(6, dev, "Min=%zu\n", min_bytes_to_पढ़ो);

	क्रम (i = 0; i < (min_bytes_to_पढ़ो-5); i++) अणु
		rc = रुको_क्रम_bulk_in_पढ़ोy(dev);
		अगर (rc <= 0) अणु
			DEBUGP(5, dev, "wait_for_bulk_in_ready rc=%.2x\n", rc);
			DEBUGP(2, dev, "<- cm4040_read (failed)\n");
			अगर (rc == -ERESTARTSYS)
				वापस rc;
			वापस -EIO;
		पूर्ण
		dev->r_buf[i+5] = xinb(iobase + REG_OFFSET_BULK_IN);
#अगर_घोषित CM4040_DEBUG
		pr_debug("%lu:%2x ", i, dev->r_buf[i]);
	पूर्ण
	pr_debug("\n");
#अन्यथा
	पूर्ण
#पूर्ण_अगर

	*ppos = min_bytes_to_पढ़ो;
	अगर (copy_to_user(buf, dev->r_buf, min_bytes_to_पढ़ो))
		वापस -EFAULT;

	rc = रुको_क्रम_bulk_in_पढ़ोy(dev);
	अगर (rc <= 0) अणु
		DEBUGP(5, dev, "wait_for_bulk_in_ready rc=%.2x\n", rc);
		DEBUGP(2, dev, "<- cm4040_read (failed)\n");
		अगर (rc == -ERESTARTSYS)
			वापस rc;
		वापस -EIO;
	पूर्ण

	rc = ग_लिखो_sync_reg(SCR_READER_TO_HOST_DONE, dev);
	अगर (rc <= 0) अणु
		DEBUGP(5, dev, "write_sync_reg c=%.2x\n", rc);
		DEBUGP(2, dev, "<- cm4040_read (failed)\n");
		अगर (rc == -ERESTARTSYS)
			वापस rc;
		अन्यथा
			वापस -EIO;
	पूर्ण

	uc = xinb(iobase + REG_OFFSET_BULK_IN);

	DEBUGP(2, dev, "<- cm4040_read (successfully)\n");
	वापस min_bytes_to_पढ़ो;
पूर्ण

अटल sमाप_प्रकार cm4040_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buf,
			 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा पढ़ोer_dev *dev = filp->निजी_data;
	पूर्णांक iobase = dev->p_dev->resource[0]->start;
	sमाप_प्रकार rc;
	पूर्णांक i;
	अचिन्हित पूर्णांक bytes_to_ग_लिखो;

	DEBUGP(2, dev, "-> cm4040_write(%s,%d)\n", current->comm, current->pid);

	अगर (count == 0) अणु
		DEBUGP(2, dev, "<- cm4040_write empty read (successfully)\n");
		वापस 0;
	पूर्ण

	अगर ((count < 5) || (count > READ_WRITE_BUFFER_SIZE)) अणु
		DEBUGP(2, dev, "<- cm4040_write buffersize=%zd < 5\n", count);
		वापस -EIO;
	पूर्ण

	अगर (filp->f_flags & O_NONBLOCK) अणु
		DEBUGP(4, dev, "filep->f_flags O_NONBLOCK set\n");
		DEBUGP(4, dev, "<- cm4040_write (failure)\n");
		वापस -EAGAIN;
	पूर्ण

	अगर (!pcmcia_dev_present(dev->p_dev))
		वापस -ENODEV;

	bytes_to_ग_लिखो = count;
	अगर (copy_from_user(dev->s_buf, buf, bytes_to_ग_लिखो))
		वापस -EFAULT;

	चयन (dev->s_buf[0]) अणु
		हाल CMD_PC_TO_RDR_XFRBLOCK:
		हाल CMD_PC_TO_RDR_SECURE:
		हाल CMD_PC_TO_RDR_TEST_SECURE:
		हाल CMD_PC_TO_RDR_OK_SECURE:
			dev->समयout = CCID_DRIVER_BULK_DEFAULT_TIMEOUT;
			अवरोध;

		हाल CMD_PC_TO_RDR_ICCPOWERON:
			dev->समयout = CCID_DRIVER_ASYNC_POWERUP_TIMEOUT;
			अवरोध;

		हाल CMD_PC_TO_RDR_GETSLOTSTATUS:
		हाल CMD_PC_TO_RDR_ICCPOWEROFF:
		हाल CMD_PC_TO_RDR_GETPARAMETERS:
		हाल CMD_PC_TO_RDR_RESETPARAMETERS:
		हाल CMD_PC_TO_RDR_SETPARAMETERS:
		हाल CMD_PC_TO_RDR_ESCAPE:
		हाल CMD_PC_TO_RDR_ICCCLOCK:
		शेष:
			dev->समयout = CCID_DRIVER_MINIMUM_TIMEOUT;
			अवरोध;
	पूर्ण

	rc = ग_लिखो_sync_reg(SCR_HOST_TO_READER_START, dev);
	अगर (rc <= 0) अणु
		DEBUGP(5, dev, "write_sync_reg c=%.2zx\n", rc);
		DEBUGP(2, dev, "<- cm4040_write (failed)\n");
		अगर (rc == -ERESTARTSYS)
			वापस rc;
		अन्यथा
			वापस -EIO;
	पूर्ण

	DEBUGP(4, dev, "start \n");

	क्रम (i = 0; i < bytes_to_ग_लिखो; i++) अणु
		rc = रुको_क्रम_bulk_out_पढ़ोy(dev);
		अगर (rc <= 0) अणु
			DEBUGP(5, dev, "wait_for_bulk_out_ready rc=%.2zx\n",
			       rc);
			DEBUGP(2, dev, "<- cm4040_write (failed)\n");
			अगर (rc == -ERESTARTSYS)
				वापस rc;
			अन्यथा
				वापस -EIO;
		पूर्ण

		xoutb(dev->s_buf[i],iobase + REG_OFFSET_BULK_OUT);
	पूर्ण
	DEBUGP(4, dev, "end\n");

	rc = ग_लिखो_sync_reg(SCR_HOST_TO_READER_DONE, dev);

	अगर (rc <= 0) अणु
		DEBUGP(5, dev, "write_sync_reg c=%.2zx\n", rc);
		DEBUGP(2, dev, "<- cm4040_write (failed)\n");
		अगर (rc == -ERESTARTSYS)
			वापस rc;
		अन्यथा
			वापस -EIO;
	पूर्ण

	DEBUGP(2, dev, "<- cm4040_write (successfully)\n");
	वापस count;
पूर्ण

अटल __poll_t cm4040_poll(काष्ठा file *filp, poll_table *रुको)
अणु
	काष्ठा पढ़ोer_dev *dev = filp->निजी_data;
	__poll_t mask = 0;

	poll_रुको(filp, &dev->poll_रुको, रुको);

	अगर (test_and_clear_bit(BS_READABLE, &dev->buffer_status))
		mask |= EPOLLIN | EPOLLRDNORM;
	अगर (test_and_clear_bit(BS_WRITABLE, &dev->buffer_status))
		mask |= EPOLLOUT | EPOLLWRNORM;

	DEBUGP(2, dev, "<- cm4040_poll(%u)\n", mask);

	वापस mask;
पूर्ण

अटल पूर्णांक cm4040_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा पढ़ोer_dev *dev;
	काष्ठा pcmcia_device *link;
	पूर्णांक minor = iminor(inode);
	पूर्णांक ret;

	अगर (minor >= CM_MAX_DEV)
		वापस -ENODEV;

	mutex_lock(&cm4040_mutex);
	link = dev_table[minor];
	अगर (link == शून्य || !pcmcia_dev_present(link)) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	अगर (link->खोलो) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	dev = link->priv;
	filp->निजी_data = dev;

	अगर (filp->f_flags & O_NONBLOCK) अणु
		DEBUGP(4, dev, "filep->f_flags O_NONBLOCK set\n");
		ret = -EAGAIN;
		जाओ out;
	पूर्ण

	link->खोलो = 1;

	mod_समयr(&dev->poll_समयr, jअगरfies + POLL_PERIOD);

	DEBUGP(2, dev, "<- cm4040_open (successfully)\n");
	ret = nonseekable_खोलो(inode, filp);
out:
	mutex_unlock(&cm4040_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक cm4040_बंद(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा पढ़ोer_dev *dev = filp->निजी_data;
	काष्ठा pcmcia_device *link;
	पूर्णांक minor = iminor(inode);

	DEBUGP(2, dev, "-> cm4040_close(maj/min=%d.%d)\n", imajor(inode),
	      iminor(inode));

	अगर (minor >= CM_MAX_DEV)
		वापस -ENODEV;

	link = dev_table[minor];
	अगर (link == शून्य)
		वापस -ENODEV;

	cm4040_stop_poll(dev);

	link->खोलो = 0;
	wake_up(&dev->devq);

	DEBUGP(2, dev, "<- cm4040_close\n");
	वापस 0;
पूर्ण

अटल व्योम cm4040_पढ़ोer_release(काष्ठा pcmcia_device *link)
अणु
	काष्ठा पढ़ोer_dev *dev = link->priv;

	DEBUGP(3, dev, "-> cm4040_reader_release\n");
	जबतक (link->खोलो) अणु
		DEBUGP(3, dev, MODULE_NAME ": delaying release "
		       "until process has terminated\n");
 		रुको_event(dev->devq, (link->खोलो == 0));
	पूर्ण
	DEBUGP(3, dev, "<- cm4040_reader_release\n");
	वापस;
पूर्ण

अटल पूर्णांक cm4040_config_check(काष्ठा pcmcia_device *p_dev, व्योम *priv_data)
अणु
	वापस pcmcia_request_io(p_dev);
पूर्ण


अटल पूर्णांक पढ़ोer_config(काष्ठा pcmcia_device *link, पूर्णांक devno)
अणु
	काष्ठा पढ़ोer_dev *dev;
	पूर्णांक fail_rc;

	link->config_flags |= CONF_AUTO_SET_IO;

	अगर (pcmcia_loop_config(link, cm4040_config_check, शून्य))
		जाओ cs_release;

	fail_rc = pcmcia_enable_device(link);
	अगर (fail_rc != 0) अणु
		dev_info(&link->dev, "pcmcia_enable_device failed 0x%x\n",
			 fail_rc);
		जाओ cs_release;
	पूर्ण

	dev = link->priv;

	DEBUGP(2, dev, "device " DEVICE_NAME "%d at %pR\n", devno,
	      link->resource[0]);
	DEBUGP(2, dev, "<- reader_config (succ)\n");

	वापस 0;

cs_release:
	पढ़ोer_release(link);
	वापस -ENODEV;
पूर्ण

अटल व्योम पढ़ोer_release(काष्ठा pcmcia_device *link)
अणु
	cm4040_पढ़ोer_release(link);
	pcmcia_disable_device(link);
पूर्ण

अटल पूर्णांक पढ़ोer_probe(काष्ठा pcmcia_device *link)
अणु
	काष्ठा पढ़ोer_dev *dev;
	पूर्णांक i, ret;

	क्रम (i = 0; i < CM_MAX_DEV; i++) अणु
		अगर (dev_table[i] == शून्य)
			अवरोध;
	पूर्ण

	अगर (i == CM_MAX_DEV)
		वापस -ENODEV;

	dev = kzalloc(माप(काष्ठा पढ़ोer_dev), GFP_KERNEL);
	अगर (dev == शून्य)
		वापस -ENOMEM;

	dev->समयout = CCID_DRIVER_MINIMUM_TIMEOUT;
	dev->buffer_status = 0;

	link->priv = dev;
	dev->p_dev = link;

	dev_table[i] = link;

	init_रुकोqueue_head(&dev->devq);
	init_रुकोqueue_head(&dev->poll_रुको);
	init_रुकोqueue_head(&dev->पढ़ो_रुको);
	init_रुकोqueue_head(&dev->ग_लिखो_रुको);
	समयr_setup(&dev->poll_समयr, cm4040_करो_poll, 0);

	ret = पढ़ोer_config(link, i);
	अगर (ret) अणु
		dev_table[i] = शून्य;
		kमुक्त(dev);
		वापस ret;
	पूर्ण

	device_create(cmx_class, शून्य, MKDEV(major, i), शून्य, "cmx%d", i);

	वापस 0;
पूर्ण

अटल व्योम पढ़ोer_detach(काष्ठा pcmcia_device *link)
अणु
	काष्ठा पढ़ोer_dev *dev = link->priv;
	पूर्णांक devno;

	/* find device */
	क्रम (devno = 0; devno < CM_MAX_DEV; devno++) अणु
		अगर (dev_table[devno] == link)
			अवरोध;
	पूर्ण
	अगर (devno == CM_MAX_DEV)
		वापस;

	पढ़ोer_release(link);

	dev_table[devno] = शून्य;
	kमुक्त(dev);

	device_destroy(cmx_class, MKDEV(major, devno));

	वापस;
पूर्ण

अटल स्थिर काष्ठा file_operations पढ़ोer_fops = अणु
	.owner		= THIS_MODULE,
	.पढ़ो		= cm4040_पढ़ो,
	.ग_लिखो		= cm4040_ग_लिखो,
	.खोलो		= cm4040_खोलो,
	.release	= cm4040_बंद,
	.poll		= cm4040_poll,
	.llseek		= no_llseek,
पूर्ण;

अटल स्थिर काष्ठा pcmcia_device_id cm4040_ids[] = अणु
	PCMCIA_DEVICE_MANF_CARD(0x0223, 0x0200),
	PCMCIA_DEVICE_PROD_ID12("OMNIKEY", "CardMan 4040",
				0xE32CDD8C, 0x8F23318B),
	PCMCIA_DEVICE_शून्य,
पूर्ण;
MODULE_DEVICE_TABLE(pcmcia, cm4040_ids);

अटल काष्ठा pcmcia_driver पढ़ोer_driver = अणु
  	.owner		= THIS_MODULE,
	.name		= "cm4040_cs",
	.probe		= पढ़ोer_probe,
	.हटाओ		= पढ़ोer_detach,
	.id_table	= cm4040_ids,
पूर्ण;

अटल पूर्णांक __init cm4040_init(व्योम)
अणु
	पूर्णांक rc;

	cmx_class = class_create(THIS_MODULE, "cardman_4040");
	अगर (IS_ERR(cmx_class))
		वापस PTR_ERR(cmx_class);

	major = रेजिस्टर_chrdev(0, DEVICE_NAME, &पढ़ोer_fops);
	अगर (major < 0) अणु
		prपूर्णांकk(KERN_WARNING MODULE_NAME
			": could not get major number\n");
		class_destroy(cmx_class);
		वापस major;
	पूर्ण

	rc = pcmcia_रेजिस्टर_driver(&पढ़ोer_driver);
	अगर (rc < 0) अणु
		unरेजिस्टर_chrdev(major, DEVICE_NAME);
		class_destroy(cmx_class);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास cm4040_निकास(व्योम)
अणु
	pcmcia_unरेजिस्टर_driver(&पढ़ोer_driver);
	unरेजिस्टर_chrdev(major, DEVICE_NAME);
	class_destroy(cmx_class);
पूर्ण

module_init(cm4040_init);
module_निकास(cm4040_निकास);
MODULE_LICENSE("Dual BSD/GPL");
