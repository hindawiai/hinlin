<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/drivers/misc/xillybus_core.c
 *
 * Copyright 2011 Xillybus Ltd, http://xillybus.com
 *
 * Driver क्रम the Xillybus FPGA/host framework.
 *
 * This driver पूर्णांकerfaces with a special IP core in an FPGA, setting up
 * a pipe between a hardware FIFO in the programmable logic and a device
 * file in the host. The number of such pipes and their attributes are
 * set up on the logic. This driver detects these स्वतःmatically and
 * creates the device files accordingly.
 */

#समावेश <linux/list.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sched.h>
#समावेश <linux/fs.h>
#समावेश <linux/cdev.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mutex.h>
#समावेश <linux/crc32.h>
#समावेश <linux/poll.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश "xillybus.h"

MODULE_DESCRIPTION("Xillybus core functions");
MODULE_AUTHOR("Eli Billauer, Xillybus Ltd.");
MODULE_VERSION("1.07");
MODULE_ALIAS("xillybus_core");
MODULE_LICENSE("GPL v2");

/* General समयout is 100 ms, rx समयout is 10 ms */
#घोषणा XILLY_RX_TIMEOUT (10*HZ/1000)
#घोषणा XILLY_TIMEOUT (100*HZ/1000)

#घोषणा fpga_msg_ctrl_reg              0x0008
#घोषणा fpga_dma_control_reg           0x0020
#घोषणा fpga_dma_bufno_reg             0x0024
#घोषणा fpga_dma_bufaddr_lowaddr_reg   0x0028
#घोषणा fpga_dma_bufaddr_highaddr_reg  0x002c
#घोषणा fpga_buf_ctrl_reg              0x0030
#घोषणा fpga_buf_offset_reg            0x0034
#घोषणा fpga_endian_reg                0x0040

#घोषणा XILLYMSG_OPCODE_RELEASEBUF 1
#घोषणा XILLYMSG_OPCODE_QUIESCEACK 2
#घोषणा XILLYMSG_OPCODE_FIFOखातापूर्ण 3
#घोषणा XILLYMSG_OPCODE_FATAL_ERROR 4
#घोषणा XILLYMSG_OPCODE_NONEMPTY 5

अटल स्थिर अक्षर xillyname[] = "xillybus";

अटल काष्ठा class *xillybus_class;

/*
 * ep_list_lock is the last lock to be taken; No other lock requests are
 * allowed जबतक holding it. It merely protects list_of_endpoपूर्णांकs, and not
 * the endpoपूर्णांकs listed in it.
 */

अटल LIST_HEAD(list_of_endpoपूर्णांकs);
अटल काष्ठा mutex ep_list_lock;
अटल काष्ठा workqueue_काष्ठा *xillybus_wq;

/*
 * Locking scheme: Mutexes protect invocations of अक्षरacter device methods.
 * If both locks are taken, wr_mutex is taken first, rd_mutex second.
 *
 * wr_spinlock protects wr_*_buf_idx, wr_empty, wr_sleepy, wr_पढ़ोy and the
 * buffers' end_offset fields against changes made by IRQ handler (and in
 * theory, other file request handlers, but the mutex handles that). Nothing
 * अन्यथा.
 * They are held क्रम लघु direct memory manipulations. Needless to say,
 * no mutex locking is allowed when a spinlock is held.
 *
 * rd_spinlock करोes the same with rd_*_buf_idx, rd_empty and end_offset.
 *
 * रेजिस्टर_mutex is endpoपूर्णांक-specअगरic, and is held when non-atomic
 * रेजिस्टर operations are perक्रमmed. wr_mutex and rd_mutex may be
 * held when रेजिस्टर_mutex is taken, but none of the spinlocks. Note that
 * रेजिस्टर_mutex करोesn't protect against sporadic buf_ctrl_reg ग_लिखोs
 * which are unrelated to buf_offset_reg, since they are harmless.
 *
 * Blocking on the रुको queues is allowed with mutexes held, but not with
 * spinlocks.
 *
 * Only पूर्णांकerruptible blocking is allowed on mutexes and रुको queues.
 *
 * All in all, the locking order goes (with skips allowed, of course):
 * wr_mutex -> rd_mutex -> रेजिस्टर_mutex -> wr_spinlock -> rd_spinlock
 */

अटल व्योम malक्रमmed_message(काष्ठा xilly_endpoपूर्णांक *endpoपूर्णांक, u32 *buf)
अणु
	पूर्णांक opcode;
	पूर्णांक msg_channel, msg_bufno, msg_data, msg_dir;

	opcode = (buf[0] >> 24) & 0xff;
	msg_dir = buf[0] & 1;
	msg_channel = (buf[0] >> 1) & 0x7ff;
	msg_bufno = (buf[0] >> 12) & 0x3ff;
	msg_data = buf[1] & 0xfffffff;

	dev_warn(endpoपूर्णांक->dev,
		 "Malformed message (skipping): opcode=%d, channel=%03x, dir=%d, bufno=%03x, data=%07x\n",
		 opcode, msg_channel, msg_dir, msg_bufno, msg_data);
पूर्ण

/*
 * xillybus_isr assumes the पूर्णांकerrupt is allocated exclusively to it,
 * which is the natural हाल MSI and several other hardware-oriented
 * पूर्णांकerrupts. Sharing is not allowed.
 */

irqवापस_t xillybus_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा xilly_endpoपूर्णांक *ep = data;
	u32 *buf;
	अचिन्हित पूर्णांक buf_size;
	पूर्णांक i;
	पूर्णांक opcode;
	अचिन्हित पूर्णांक msg_channel, msg_bufno, msg_data, msg_dir;
	काष्ठा xilly_channel *channel;

	buf = ep->msgbuf_addr;
	buf_size = ep->msg_buf_size/माप(u32);

	ep->ephw->hw_sync_sgl_क्रम_cpu(ep,
				      ep->msgbuf_dma_addr,
				      ep->msg_buf_size,
				      DMA_FROM_DEVICE);

	क्रम (i = 0; i < buf_size; i += 2) अणु
		अगर (((buf[i+1] >> 28) & 0xf) != ep->msg_counter) अणु
			malक्रमmed_message(ep, &buf[i]);
			dev_warn(ep->dev,
				 "Sending a NACK on counter %x (instead of %x) on entry %d\n",
				 ((buf[i+1] >> 28) & 0xf),
				 ep->msg_counter,
				 i/2);

			अगर (++ep->failed_messages > 10) अणु
				dev_err(ep->dev,
					"Lost sync with interrupt messages. Stopping.\n");
			पूर्ण अन्यथा अणु
				ep->ephw->hw_sync_sgl_क्रम_device(
					ep,
					ep->msgbuf_dma_addr,
					ep->msg_buf_size,
					DMA_FROM_DEVICE);

				ioग_लिखो32(0x01,  /* Message NACK */
					  ep->रेजिस्टरs + fpga_msg_ctrl_reg);
			पूर्ण
			वापस IRQ_HANDLED;
		पूर्ण अन्यथा अगर (buf[i] & (1 << 22)) /* Last message */
			अवरोध;
	पूर्ण

	अगर (i >= buf_size) अणु
		dev_err(ep->dev, "Bad interrupt message. Stopping.\n");
		वापस IRQ_HANDLED;
	पूर्ण

	buf_size = i + 2;

	क्रम (i = 0; i < buf_size; i += 2) अणु /* Scan through messages */
		opcode = (buf[i] >> 24) & 0xff;

		msg_dir = buf[i] & 1;
		msg_channel = (buf[i] >> 1) & 0x7ff;
		msg_bufno = (buf[i] >> 12) & 0x3ff;
		msg_data = buf[i+1] & 0xfffffff;

		चयन (opcode) अणु
		हाल XILLYMSG_OPCODE_RELEASEBUF:
			अगर ((msg_channel > ep->num_channels) ||
			    (msg_channel == 0)) अणु
				malक्रमmed_message(ep, &buf[i]);
				अवरोध;
			पूर्ण

			channel = ep->channels[msg_channel];

			अगर (msg_dir) अणु /* Write channel */
				अगर (msg_bufno >= channel->num_wr_buffers) अणु
					malक्रमmed_message(ep, &buf[i]);
					अवरोध;
				पूर्ण
				spin_lock(&channel->wr_spinlock);
				channel->wr_buffers[msg_bufno]->end_offset =
					msg_data;
				channel->wr_fpga_buf_idx = msg_bufno;
				channel->wr_empty = 0;
				channel->wr_sleepy = 0;
				spin_unlock(&channel->wr_spinlock);

				wake_up_पूर्णांकerruptible(&channel->wr_रुको);

			पूर्ण अन्यथा अणु
				/* Read channel */

				अगर (msg_bufno >= channel->num_rd_buffers) अणु
					malक्रमmed_message(ep, &buf[i]);
					अवरोध;
				पूर्ण

				spin_lock(&channel->rd_spinlock);
				channel->rd_fpga_buf_idx = msg_bufno;
				channel->rd_full = 0;
				spin_unlock(&channel->rd_spinlock);

				wake_up_पूर्णांकerruptible(&channel->rd_रुको);
				अगर (!channel->rd_synchronous)
					queue_delayed_work(
						xillybus_wq,
						&channel->rd_workitem,
						XILLY_RX_TIMEOUT);
			पूर्ण

			अवरोध;
		हाल XILLYMSG_OPCODE_NONEMPTY:
			अगर ((msg_channel > ep->num_channels) ||
			    (msg_channel == 0) || (!msg_dir) ||
			    !ep->channels[msg_channel]->wr_supports_nonempty) अणु
				malक्रमmed_message(ep, &buf[i]);
				अवरोध;
			पूर्ण

			channel = ep->channels[msg_channel];

			अगर (msg_bufno >= channel->num_wr_buffers) अणु
				malक्रमmed_message(ep, &buf[i]);
				अवरोध;
			पूर्ण
			spin_lock(&channel->wr_spinlock);
			अगर (msg_bufno == channel->wr_host_buf_idx)
				channel->wr_पढ़ोy = 1;
			spin_unlock(&channel->wr_spinlock);

			wake_up_पूर्णांकerruptible(&channel->wr_पढ़ोy_रुको);

			अवरोध;
		हाल XILLYMSG_OPCODE_QUIESCEACK:
			ep->idtlen = msg_data;
			wake_up_पूर्णांकerruptible(&ep->ep_रुको);

			अवरोध;
		हाल XILLYMSG_OPCODE_FIFOखातापूर्ण:
			अगर ((msg_channel > ep->num_channels) ||
			    (msg_channel == 0) || (!msg_dir) ||
			    !ep->channels[msg_channel]->num_wr_buffers) अणु
				malक्रमmed_message(ep, &buf[i]);
				अवरोध;
			पूर्ण
			channel = ep->channels[msg_channel];
			spin_lock(&channel->wr_spinlock);
			channel->wr_eof = msg_bufno;
			channel->wr_sleepy = 0;

			channel->wr_hangup = channel->wr_empty &&
				(channel->wr_host_buf_idx == msg_bufno);

			spin_unlock(&channel->wr_spinlock);

			wake_up_पूर्णांकerruptible(&channel->wr_रुको);

			अवरोध;
		हाल XILLYMSG_OPCODE_FATAL_ERROR:
			ep->fatal_error = 1;
			wake_up_पूर्णांकerruptible(&ep->ep_रुको); /* For select() */
			dev_err(ep->dev,
				"FPGA reported a fatal error. This means that the low-level communication with the device has failed. This hardware problem is most likely unrelated to Xillybus (neither kernel module nor FPGA core), but reports are still welcome. All I/O is aborted.\n");
			अवरोध;
		शेष:
			malक्रमmed_message(ep, &buf[i]);
			अवरोध;
		पूर्ण
	पूर्ण

	ep->ephw->hw_sync_sgl_क्रम_device(ep,
					 ep->msgbuf_dma_addr,
					 ep->msg_buf_size,
					 DMA_FROM_DEVICE);

	ep->msg_counter = (ep->msg_counter + 1) & 0xf;
	ep->failed_messages = 0;
	ioग_लिखो32(0x03, ep->रेजिस्टरs + fpga_msg_ctrl_reg); /* Message ACK */

	वापस IRQ_HANDLED;
पूर्ण
EXPORT_SYMBOL(xillybus_isr);

/*
 * A few trivial memory management functions.
 * NOTE: These functions are used only on probe and हटाओ, and thereक्रमe
 * no locks are applied!
 */

अटल व्योम xillybus_स्वतःflush(काष्ठा work_काष्ठा *work);

काष्ठा xilly_alloc_state अणु
	व्योम *salami;
	पूर्णांक left_of_salami;
	पूर्णांक nbuffer;
	क्रमागत dma_data_direction direction;
	u32 regdirection;
पूर्ण;

अटल पूर्णांक xilly_get_dma_buffers(काष्ठा xilly_endpoपूर्णांक *ep,
				 काष्ठा xilly_alloc_state *s,
				 काष्ठा xilly_buffer **buffers,
				 पूर्णांक bufnum, पूर्णांक bytebufsize)
अणु
	पूर्णांक i, rc;
	dma_addr_t dma_addr;
	काष्ठा device *dev = ep->dev;
	काष्ठा xilly_buffer *this_buffer = शून्य; /* Init to silence warning */

	अगर (buffers) अणु /* Not the message buffer */
		this_buffer = devm_kसुस्मृति(dev, bufnum,
					   माप(काष्ठा xilly_buffer),
					   GFP_KERNEL);
		अगर (!this_buffer)
			वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < bufnum; i++) अणु
		/*
		 * Buffers are expected in descending size order, so there
		 * is either enough space क्रम this buffer or none at all.
		 */

		अगर ((s->left_of_salami < bytebufsize) &&
		    (s->left_of_salami > 0)) अणु
			dev_err(ep->dev,
				"Corrupt buffer allocation in IDT. Aborting.\n");
			वापस -ENODEV;
		पूर्ण

		अगर (s->left_of_salami == 0) अणु
			पूर्णांक allocorder, allocsize;

			allocsize = PAGE_SIZE;
			allocorder = 0;
			जबतक (bytebufsize > allocsize) अणु
				allocsize *= 2;
				allocorder++;
			पूर्ण

			s->salami = (व्योम *) devm_get_मुक्त_pages(
				dev,
				GFP_KERNEL | __GFP_DMA32 | __GFP_ZERO,
				allocorder);
			अगर (!s->salami)
				वापस -ENOMEM;

			s->left_of_salami = allocsize;
		पूर्ण

		rc = ep->ephw->map_single(ep, s->salami,
					  bytebufsize, s->direction,
					  &dma_addr);
		अगर (rc)
			वापस rc;

		ioग_लिखो32((u32) (dma_addr & 0xffffffff),
			  ep->रेजिस्टरs + fpga_dma_bufaddr_lowaddr_reg);
		ioग_लिखो32(((u32) ((((u64) dma_addr) >> 32) & 0xffffffff)),
			  ep->रेजिस्टरs + fpga_dma_bufaddr_highaddr_reg);

		अगर (buffers) अणु /* Not the message buffer */
			this_buffer->addr = s->salami;
			this_buffer->dma_addr = dma_addr;
			buffers[i] = this_buffer++;

			ioग_लिखो32(s->regdirection | s->nbuffer++,
				  ep->रेजिस्टरs + fpga_dma_bufno_reg);
		पूर्ण अन्यथा अणु
			ep->msgbuf_addr = s->salami;
			ep->msgbuf_dma_addr = dma_addr;
			ep->msg_buf_size = bytebufsize;

			ioग_लिखो32(s->regdirection,
				  ep->रेजिस्टरs + fpga_dma_bufno_reg);
		पूर्ण

		s->left_of_salami -= bytebufsize;
		s->salami += bytebufsize;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक xilly_setupchannels(काष्ठा xilly_endpoपूर्णांक *ep,
			       अचिन्हित अक्षर *chandesc,
			       पूर्णांक entries)
अणु
	काष्ठा device *dev = ep->dev;
	पूर्णांक i, entry, rc;
	काष्ठा xilly_channel *channel;
	पूर्णांक channelnum, bufnum, bufsize, क्रमmat, is_ग_लिखोbuf;
	पूर्णांक bytebufsize;
	पूर्णांक synchronous, allowpartial, exclusive_खोलो, seekable;
	पूर्णांक supports_nonempty;
	पूर्णांक msg_buf_करोne = 0;

	काष्ठा xilly_alloc_state rd_alloc = अणु
		.salami = शून्य,
		.left_of_salami = 0,
		.nbuffer = 1,
		.direction = DMA_TO_DEVICE,
		.regdirection = 0,
	पूर्ण;

	काष्ठा xilly_alloc_state wr_alloc = अणु
		.salami = शून्य,
		.left_of_salami = 0,
		.nbuffer = 1,
		.direction = DMA_FROM_DEVICE,
		.regdirection = 0x80000000,
	पूर्ण;

	channel = devm_kसुस्मृति(dev, ep->num_channels,
			       माप(काष्ठा xilly_channel), GFP_KERNEL);
	अगर (!channel)
		वापस -ENOMEM;

	ep->channels = devm_kसुस्मृति(dev, ep->num_channels + 1,
				    माप(काष्ठा xilly_channel *),
				    GFP_KERNEL);
	अगर (!ep->channels)
		वापस -ENOMEM;

	ep->channels[0] = शून्य; /* Channel 0 is message buf. */

	/* Initialize all channels with शेषs */

	क्रम (i = 1; i <= ep->num_channels; i++) अणु
		channel->wr_buffers = शून्य;
		channel->rd_buffers = शून्य;
		channel->num_wr_buffers = 0;
		channel->num_rd_buffers = 0;
		channel->wr_fpga_buf_idx = -1;
		channel->wr_host_buf_idx = 0;
		channel->wr_host_buf_pos = 0;
		channel->wr_empty = 1;
		channel->wr_पढ़ोy = 0;
		channel->wr_sleepy = 1;
		channel->rd_fpga_buf_idx = 0;
		channel->rd_host_buf_idx = 0;
		channel->rd_host_buf_pos = 0;
		channel->rd_full = 0;
		channel->wr_ref_count = 0;
		channel->rd_ref_count = 0;

		spin_lock_init(&channel->wr_spinlock);
		spin_lock_init(&channel->rd_spinlock);
		mutex_init(&channel->wr_mutex);
		mutex_init(&channel->rd_mutex);
		init_रुकोqueue_head(&channel->rd_रुको);
		init_रुकोqueue_head(&channel->wr_रुको);
		init_रुकोqueue_head(&channel->wr_पढ़ोy_रुको);

		INIT_DELAYED_WORK(&channel->rd_workitem, xillybus_स्वतःflush);

		channel->endpoपूर्णांक = ep;
		channel->chan_num = i;

		channel->log2_element_size = 0;

		ep->channels[i] = channel++;
	पूर्ण

	क्रम (entry = 0; entry < entries; entry++, chandesc += 4) अणु
		काष्ठा xilly_buffer **buffers = शून्य;

		is_ग_लिखोbuf = chandesc[0] & 0x01;
		channelnum = (chandesc[0] >> 1) | ((chandesc[1] & 0x0f) << 7);
		क्रमmat = (chandesc[1] >> 4) & 0x03;
		allowpartial = (chandesc[1] >> 6) & 0x01;
		synchronous = (chandesc[1] >> 7) & 0x01;
		bufsize = 1 << (chandesc[2] & 0x1f);
		bufnum = 1 << (chandesc[3] & 0x0f);
		exclusive_खोलो = (chandesc[2] >> 7) & 0x01;
		seekable = (chandesc[2] >> 6) & 0x01;
		supports_nonempty = (chandesc[2] >> 5) & 0x01;

		अगर ((channelnum > ep->num_channels) ||
		    ((channelnum == 0) && !is_ग_लिखोbuf)) अणु
			dev_err(ep->dev,
				"IDT requests channel out of range. Aborting.\n");
			वापस -ENODEV;
		पूर्ण

		channel = ep->channels[channelnum]; /* शून्य क्रम msg channel */

		अगर (!is_ग_लिखोbuf || channelnum > 0) अणु
			channel->log2_element_size = ((क्रमmat > 2) ?
						      2 : क्रमmat);

			bytebufsize = bufsize *
				(1 << channel->log2_element_size);

			buffers = devm_kसुस्मृति(dev, bufnum,
					       माप(काष्ठा xilly_buffer *),
					       GFP_KERNEL);
			अगर (!buffers)
				वापस -ENOMEM;
		पूर्ण अन्यथा अणु
			bytebufsize = bufsize << 2;
		पूर्ण

		अगर (!is_ग_लिखोbuf) अणु
			channel->num_rd_buffers = bufnum;
			channel->rd_buf_size = bytebufsize;
			channel->rd_allow_partial = allowpartial;
			channel->rd_synchronous = synchronous;
			channel->rd_exclusive_खोलो = exclusive_खोलो;
			channel->seekable = seekable;

			channel->rd_buffers = buffers;
			rc = xilly_get_dma_buffers(ep, &rd_alloc, buffers,
						   bufnum, bytebufsize);
		पूर्ण अन्यथा अगर (channelnum > 0) अणु
			channel->num_wr_buffers = bufnum;
			channel->wr_buf_size = bytebufsize;

			channel->seekable = seekable;
			channel->wr_supports_nonempty = supports_nonempty;

			channel->wr_allow_partial = allowpartial;
			channel->wr_synchronous = synchronous;
			channel->wr_exclusive_खोलो = exclusive_खोलो;

			channel->wr_buffers = buffers;
			rc = xilly_get_dma_buffers(ep, &wr_alloc, buffers,
						   bufnum, bytebufsize);
		पूर्ण अन्यथा अणु
			rc = xilly_get_dma_buffers(ep, &wr_alloc, शून्य,
						   bufnum, bytebufsize);
			msg_buf_करोne++;
		पूर्ण

		अगर (rc)
			वापस -ENOMEM;
	पूर्ण

	अगर (!msg_buf_करोne) अणु
		dev_err(ep->dev,
			"Corrupt IDT: No message buffer. Aborting.\n");
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक xilly_scan_idt(काष्ठा xilly_endpoपूर्णांक *endpoपूर्णांक,
			  काष्ठा xilly_idt_handle *idt_handle)
अणु
	पूर्णांक count = 0;
	अचिन्हित अक्षर *idt = endpoपूर्णांक->channels[1]->wr_buffers[0]->addr;
	अचिन्हित अक्षर *end_of_idt = idt + endpoपूर्णांक->idtlen - 4;
	अचिन्हित अक्षर *scan;
	पूर्णांक len;

	scan = idt;
	idt_handle->idt = idt;

	scan++; /* Skip version number */

	जबतक ((scan <= end_of_idt) && *scan) अणु
		जबतक ((scan <= end_of_idt) && *scan++)
			/* Do nothing, just scan thru string */;
		count++;
	पूर्ण

	scan++;

	अगर (scan > end_of_idt) अणु
		dev_err(endpoपूर्णांक->dev,
			"IDT device name list overflow. Aborting.\n");
		वापस -ENODEV;
	पूर्ण
	idt_handle->chandesc = scan;

	len = endpoपूर्णांक->idtlen - (3 + ((पूर्णांक) (scan - idt)));

	अगर (len & 0x03) अणु
		dev_err(endpoपूर्णांक->dev,
			"Corrupt IDT device name list. Aborting.\n");
		वापस -ENODEV;
	पूर्ण

	idt_handle->entries = len >> 2;
	endpoपूर्णांक->num_channels = count;

	वापस 0;
पूर्ण

अटल पूर्णांक xilly_obtain_idt(काष्ठा xilly_endpoपूर्णांक *endpoपूर्णांक)
अणु
	काष्ठा xilly_channel *channel;
	अचिन्हित अक्षर *version;
	दीर्घ t;

	channel = endpoपूर्णांक->channels[1]; /* This should be generated ad-hoc */

	channel->wr_sleepy = 1;

	ioग_लिखो32(1 |
		  (3 << 24), /* Opcode 3 क्रम channel 0 = Send IDT */
		  endpoपूर्णांक->रेजिस्टरs + fpga_buf_ctrl_reg);

	t = रुको_event_पूर्णांकerruptible_समयout(channel->wr_रुको,
					     (!channel->wr_sleepy),
					     XILLY_TIMEOUT);

	अगर (t <= 0) अणु
		dev_err(endpoपूर्णांक->dev, "Failed to obtain IDT. Aborting.\n");

		अगर (endpoपूर्णांक->fatal_error)
			वापस -EIO;

		वापस -ENODEV;
	पूर्ण

	endpoपूर्णांक->ephw->hw_sync_sgl_क्रम_cpu(
		channel->endpoपूर्णांक,
		channel->wr_buffers[0]->dma_addr,
		channel->wr_buf_size,
		DMA_FROM_DEVICE);

	अगर (channel->wr_buffers[0]->end_offset != endpoपूर्णांक->idtlen) अणु
		dev_err(endpoपूर्णांक->dev,
			"IDT length mismatch (%d != %d). Aborting.\n",
			channel->wr_buffers[0]->end_offset, endpoपूर्णांक->idtlen);
		वापस -ENODEV;
	पूर्ण

	अगर (crc32_le(~0, channel->wr_buffers[0]->addr,
		     endpoपूर्णांक->idtlen+1) != 0) अणु
		dev_err(endpoपूर्णांक->dev, "IDT failed CRC check. Aborting.\n");
		वापस -ENODEV;
	पूर्ण

	version = channel->wr_buffers[0]->addr;

	/* Check version number. Reject anything above 0x82. */
	अगर (*version > 0x82) अणु
		dev_err(endpoपूर्णांक->dev,
			"No support for IDT version 0x%02x. Maybe the xillybus driver needs an upgrade. Aborting.\n",
			*version);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार xillybus_पढ़ो(काष्ठा file *filp, अक्षर __user *userbuf,
			     माप_प्रकार count, loff_t *f_pos)
अणु
	sमाप_प्रकार rc;
	अचिन्हित दीर्घ flags;
	पूर्णांक bytes_करोne = 0;
	पूर्णांक no_समय_left = 0;
	दीर्घ deadline, left_to_sleep;
	काष्ठा xilly_channel *channel = filp->निजी_data;

	पूर्णांक empty, reached_eof, exhausted, पढ़ोy;
	/* Initializations are there only to silence warnings */

	पूर्णांक howmany = 0, bufpos = 0, bufidx = 0, bufferकरोne = 0;
	पूर्णांक रुकोing_bufidx;

	अगर (channel->endpoपूर्णांक->fatal_error)
		वापस -EIO;

	deadline = jअगरfies + 1 + XILLY_RX_TIMEOUT;

	rc = mutex_lock_पूर्णांकerruptible(&channel->wr_mutex);
	अगर (rc)
		वापस rc;

	जबतक (1) अणु /* Note that we may drop mutex within this loop */
		पूर्णांक bytes_to_करो = count - bytes_करोne;

		spin_lock_irqsave(&channel->wr_spinlock, flags);

		empty = channel->wr_empty;
		पढ़ोy = !empty || channel->wr_पढ़ोy;

		अगर (!empty) अणु
			bufidx = channel->wr_host_buf_idx;
			bufpos = channel->wr_host_buf_pos;
			howmany = ((channel->wr_buffers[bufidx]->end_offset
				    + 1) << channel->log2_element_size)
				- bufpos;

			/* Update wr_host_* to its post-operation state */
			अगर (howmany > bytes_to_करो) अणु
				bufferकरोne = 0;

				howmany = bytes_to_करो;
				channel->wr_host_buf_pos += howmany;
			पूर्ण अन्यथा अणु
				bufferकरोne = 1;

				channel->wr_host_buf_pos = 0;

				अगर (bufidx == channel->wr_fpga_buf_idx) अणु
					channel->wr_empty = 1;
					channel->wr_sleepy = 1;
					channel->wr_पढ़ोy = 0;
				पूर्ण

				अगर (bufidx >= (channel->num_wr_buffers - 1))
					channel->wr_host_buf_idx = 0;
				अन्यथा
					channel->wr_host_buf_idx++;
			पूर्ण
		पूर्ण

		/*
		 * Marking our situation after the possible changes above,
		 * क्रम use after releasing the spinlock.
		 *
		 * empty = empty beक्रमe change
		 * exhasted = empty after possible change
		 */

		reached_eof = channel->wr_empty &&
			(channel->wr_host_buf_idx == channel->wr_eof);
		channel->wr_hangup = reached_eof;
		exhausted = channel->wr_empty;
		रुकोing_bufidx = channel->wr_host_buf_idx;

		spin_unlock_irqrestore(&channel->wr_spinlock, flags);

		अगर (!empty) अणु /* Go on, now without the spinlock */

			अगर (bufpos == 0) /* Position zero means it's virgin */
				channel->endpoपूर्णांक->ephw->hw_sync_sgl_क्रम_cpu(
					channel->endpoपूर्णांक,
					channel->wr_buffers[bufidx]->dma_addr,
					channel->wr_buf_size,
					DMA_FROM_DEVICE);

			अगर (copy_to_user(
				    userbuf,
				    channel->wr_buffers[bufidx]->addr
				    + bufpos, howmany))
				rc = -EFAULT;

			userbuf += howmany;
			bytes_करोne += howmany;

			अगर (bufferकरोne) अणु
				channel->endpoपूर्णांक->ephw->hw_sync_sgl_क्रम_device(
					channel->endpoपूर्णांक,
					channel->wr_buffers[bufidx]->dma_addr,
					channel->wr_buf_size,
					DMA_FROM_DEVICE);

				/*
				 * Tell FPGA the buffer is करोne with. It's an
				 * atomic operation to the FPGA, so what
				 * happens with other channels करोesn't matter,
				 * and the certain channel is रक्षित with
				 * the channel-specअगरic mutex.
				 */

				ioग_लिखो32(1 | (channel->chan_num << 1) |
					  (bufidx << 12),
					  channel->endpoपूर्णांक->रेजिस्टरs +
					  fpga_buf_ctrl_reg);
			पूर्ण

			अगर (rc) अणु
				mutex_unlock(&channel->wr_mutex);
				वापस rc;
			पूर्ण
		पूर्ण

		/* This includes a zero-count वापस = खातापूर्ण */
		अगर ((bytes_करोne >= count) || reached_eof)
			अवरोध;

		अगर (!exhausted)
			जारी; /* More in RAM buffer(s)? Just go on. */

		अगर ((bytes_करोne > 0) &&
		    (no_समय_left ||
		     (channel->wr_synchronous && channel->wr_allow_partial)))
			अवरोध;

		/*
		 * Nonblocking पढ़ो: The "ready" flag tells us that the FPGA
		 * has data to send. In non-blocking mode, अगर it isn't on,
		 * just वापस. But अगर there is, we jump directly to the poपूर्णांक
		 * where we ask क्रम the FPGA to send all it has, and रुको
		 * until that data arrives. So in a sense, we *करो* block in
		 * nonblocking mode, but only क्रम a very लघु समय.
		 */

		अगर (!no_समय_left && (filp->f_flags & O_NONBLOCK)) अणु
			अगर (bytes_करोne > 0)
				अवरोध;

			अगर (पढ़ोy)
				जाओ desperate;

			rc = -EAGAIN;
			अवरोध;
		पूर्ण

		अगर (!no_समय_left || (bytes_करोne > 0)) अणु
			/*
			 * Note that in हाल of an element-misaligned पढ़ो
			 * request, offsetlimit will include the last element,
			 * which will be partially पढ़ो from.
			 */
			पूर्णांक offsetlimit = ((count - bytes_करोne) - 1) >>
				channel->log2_element_size;
			पूर्णांक buf_elements = channel->wr_buf_size >>
				channel->log2_element_size;

			/*
			 * In synchronous mode, always send an offset limit.
			 * Just करोn't send a value too big.
			 */

			अगर (channel->wr_synchronous) अणु
				/* Don't request more than one buffer */
				अगर (channel->wr_allow_partial &&
				    (offsetlimit >= buf_elements))
					offsetlimit = buf_elements - 1;

				/* Don't request more than all buffers */
				अगर (!channel->wr_allow_partial &&
				    (offsetlimit >=
				     (buf_elements * channel->num_wr_buffers)))
					offsetlimit = buf_elements *
						channel->num_wr_buffers - 1;
			पूर्ण

			/*
			 * In asynchronous mode, क्रमce early flush of a buffer
			 * only अगर that will allow वापसing a full count. The
			 * "offsetlimit < ( ... )" rather than "<=" excludes
			 * requesting a full buffer, which would obviously
			 * cause a buffer transmission anyhow
			 */

			अगर (channel->wr_synchronous ||
			    (offsetlimit < (buf_elements - 1))) अणु
				mutex_lock(&channel->endpoपूर्णांक->रेजिस्टर_mutex);

				ioग_लिखो32(offsetlimit,
					  channel->endpoपूर्णांक->रेजिस्टरs +
					  fpga_buf_offset_reg);

				ioग_लिखो32(1 | (channel->chan_num << 1) |
					  (2 << 24) |  /* 2 = offset limit */
					  (रुकोing_bufidx << 12),
					  channel->endpoपूर्णांक->रेजिस्टरs +
					  fpga_buf_ctrl_reg);

				mutex_unlock(&channel->endpoपूर्णांक->
					     रेजिस्टर_mutex);
			पूर्ण
		पूर्ण

		/*
		 * If partial completion is disallowed, there is no poपूर्णांक in
		 * समयout sleeping. Neither अगर no_समय_left is set and
		 * there's no data.
		 */

		अगर (!channel->wr_allow_partial ||
		    (no_समय_left && (bytes_करोne == 0))) अणु
			/*
			 * This करो-loop will run more than once अगर another
			 * thपढ़ो reनिश्चितed wr_sleepy beक्रमe we got the mutex
			 * back, so we try again.
			 */

			करो अणु
				mutex_unlock(&channel->wr_mutex);

				अगर (रुको_event_पूर्णांकerruptible(
					    channel->wr_रुको,
					    (!channel->wr_sleepy)))
					जाओ पूर्णांकerrupted;

				अगर (mutex_lock_पूर्णांकerruptible(
					    &channel->wr_mutex))
					जाओ पूर्णांकerrupted;
			पूर्ण जबतक (channel->wr_sleepy);

			जारी;

पूर्णांकerrupted: /* Mutex is not held अगर got here */
			अगर (channel->endpoपूर्णांक->fatal_error)
				वापस -EIO;
			अगर (bytes_करोne)
				वापस bytes_करोne;
			अगर (filp->f_flags & O_NONBLOCK)
				वापस -EAGAIN; /* Don't admit snoozing */
			वापस -EINTR;
		पूर्ण

		left_to_sleep = deadline - ((दीर्घ) jअगरfies);

		/*
		 * If our समय is out, skip the रुकोing. We may miss wr_sleepy
		 * being deनिश्चितed but hey, almost missing the train is like
		 * missing it.
		 */

		अगर (left_to_sleep > 0) अणु
			left_to_sleep =
				रुको_event_पूर्णांकerruptible_समयout(
					channel->wr_रुको,
					(!channel->wr_sleepy),
					left_to_sleep);

			अगर (left_to_sleep > 0) /* wr_sleepy deनिश्चितed */
				जारी;

			अगर (left_to_sleep < 0) अणु /* Interrupt */
				mutex_unlock(&channel->wr_mutex);
				अगर (channel->endpoपूर्णांक->fatal_error)
					वापस -EIO;
				अगर (bytes_करोne)
					वापस bytes_करोne;
				वापस -EINTR;
			पूर्ण
		पूर्ण

desperate:
		no_समय_left = 1; /* We're out of sleeping समय. Desperate! */

		अगर (bytes_करोne == 0) अणु
			/*
			 * Reaching here means that we allow partial वापस,
			 * that we've run out of समय, and that we have
			 * nothing to वापस.
			 * So tell the FPGA to send anything it has or माला_लो.
			 */

			ioग_लिखो32(1 | (channel->chan_num << 1) |
				  (3 << 24) |  /* Opcode 3, flush it all! */
				  (रुकोing_bufidx << 12),
				  channel->endpoपूर्णांक->रेजिस्टरs +
				  fpga_buf_ctrl_reg);
		पूर्ण

		/*
		 * Reaching here means that we *करो* have data in the buffer,
		 * but the "partial" flag disallows वापसing less than
		 * required. And we करोn't have as much. So loop again,
		 * which is likely to end up blocking indefinitely until
		 * enough data has arrived.
		 */
	पूर्ण

	mutex_unlock(&channel->wr_mutex);

	अगर (channel->endpoपूर्णांक->fatal_error)
		वापस -EIO;

	अगर (rc)
		वापस rc;

	वापस bytes_करोne;
पूर्ण

/*
 * The समयout argument takes values as follows:
 *  >0 : Flush with समयout
 * ==0 : Flush, and रुको idefinitely क्रम the flush to complete
 *  <0 : Autoflush: Flush only अगर there's a single buffer occupied
 */

अटल पूर्णांक xillybus_myflush(काष्ठा xilly_channel *channel, दीर्घ समयout)
अणु
	पूर्णांक rc;
	अचिन्हित दीर्घ flags;

	पूर्णांक end_offset_plus1;
	पूर्णांक bufidx, bufidx_minus1;
	पूर्णांक i;
	पूर्णांक empty;
	पूर्णांक new_rd_host_buf_pos;

	अगर (channel->endpoपूर्णांक->fatal_error)
		वापस -EIO;
	rc = mutex_lock_पूर्णांकerruptible(&channel->rd_mutex);
	अगर (rc)
		वापस rc;

	/*
	 * Don't flush a बंदd channel. This can happen when the work queued
	 * स्वतःflush thपढ़ो fires off after the file has बंदd. This is not
	 * an error, just something to dismiss.
	 */

	अगर (!channel->rd_ref_count)
		जाओ करोne;

	bufidx = channel->rd_host_buf_idx;

	bufidx_minus1 = (bufidx == 0) ?
		channel->num_rd_buffers - 1 :
		bufidx - 1;

	end_offset_plus1 = channel->rd_host_buf_pos >>
		channel->log2_element_size;

	new_rd_host_buf_pos = channel->rd_host_buf_pos -
		(end_offset_plus1 << channel->log2_element_size);

	/* Submit the current buffer अगर it's nonempty */
	अगर (end_offset_plus1) अणु
		अचिन्हित अक्षर *tail = channel->rd_buffers[bufidx]->addr +
			(end_offset_plus1 << channel->log2_element_size);

		/* Copy  unflushed data, so we can put it in next buffer */
		क्रम (i = 0; i < new_rd_host_buf_pos; i++)
			channel->rd_leftovers[i] = *tail++;

		spin_lock_irqsave(&channel->rd_spinlock, flags);

		/* Autoflush only अगर a single buffer is occupied */

		अगर ((समयout < 0) &&
		    (channel->rd_full ||
		     (bufidx_minus1 != channel->rd_fpga_buf_idx))) अणु
			spin_unlock_irqrestore(&channel->rd_spinlock, flags);
			/*
			 * A new work item may be queued by the ISR exactly
			 * now, since the execution of a work item allows the
			 * queuing of a new one जबतक it's running.
			 */
			जाओ करोne;
		पूर्ण

		/* The 4th element is never needed क्रम data, so it's a flag */
		channel->rd_leftovers[3] = (new_rd_host_buf_pos != 0);

		/* Set up rd_full to reflect a certain moment's state */

		अगर (bufidx == channel->rd_fpga_buf_idx)
			channel->rd_full = 1;
		spin_unlock_irqrestore(&channel->rd_spinlock, flags);

		अगर (bufidx >= (channel->num_rd_buffers - 1))
			channel->rd_host_buf_idx = 0;
		अन्यथा
			channel->rd_host_buf_idx++;

		channel->endpoपूर्णांक->ephw->hw_sync_sgl_क्रम_device(
			channel->endpoपूर्णांक,
			channel->rd_buffers[bufidx]->dma_addr,
			channel->rd_buf_size,
			DMA_TO_DEVICE);

		mutex_lock(&channel->endpoपूर्णांक->रेजिस्टर_mutex);

		ioग_लिखो32(end_offset_plus1 - 1,
			  channel->endpoपूर्णांक->रेजिस्टरs + fpga_buf_offset_reg);

		ioग_लिखो32((channel->chan_num << 1) | /* Channel ID */
			  (2 << 24) |  /* Opcode 2, submit buffer */
			  (bufidx << 12),
			  channel->endpoपूर्णांक->रेजिस्टरs + fpga_buf_ctrl_reg);

		mutex_unlock(&channel->endpoपूर्णांक->रेजिस्टर_mutex);
	पूर्ण अन्यथा अगर (bufidx == 0) अणु
		bufidx = channel->num_rd_buffers - 1;
	पूर्ण अन्यथा अणु
		bufidx--;
	पूर्ण

	channel->rd_host_buf_pos = new_rd_host_buf_pos;

	अगर (समयout < 0)
		जाओ करोne; /* Autoflush */

	/*
	 * bufidx is now the last buffer written to (or equal to
	 * rd_fpga_buf_idx अगर buffer was never written to), and
	 * channel->rd_host_buf_idx the one after it.
	 *
	 * If bufidx == channel->rd_fpga_buf_idx we're either empty or full.
	 */

	जबतक (1) अणु /* Loop रुकोing क्रम draining of buffers */
		spin_lock_irqsave(&channel->rd_spinlock, flags);

		अगर (bufidx != channel->rd_fpga_buf_idx)
			channel->rd_full = 1; /*
					       * Not really full,
					       * but needs रुकोing.
					       */

		empty = !channel->rd_full;

		spin_unlock_irqrestore(&channel->rd_spinlock, flags);

		अगर (empty)
			अवरोध;

		/*
		 * Indefinite sleep with mutex taken. With data रुकोing क्रम
		 * flushing user should not be surprised अगर खोलो() क्रम ग_लिखो
		 * sleeps.
		 */
		अगर (समयout == 0)
			रुको_event_पूर्णांकerruptible(channel->rd_रुको,
						 (!channel->rd_full));

		अन्यथा अगर (रुको_event_पूर्णांकerruptible_समयout(
				 channel->rd_रुको,
				 (!channel->rd_full),
				 समयout) == 0) अणु
			dev_warn(channel->endpoपूर्णांक->dev,
				 "Timed out while flushing. Output data may be lost.\n");

			rc = -ETIMEDOUT;
			अवरोध;
		पूर्ण

		अगर (channel->rd_full) अणु
			rc = -EINTR;
			अवरोध;
		पूर्ण
	पूर्ण

करोne:
	mutex_unlock(&channel->rd_mutex);

	अगर (channel->endpoपूर्णांक->fatal_error)
		वापस -EIO;

	वापस rc;
पूर्ण

अटल पूर्णांक xillybus_flush(काष्ठा file *filp, fl_owner_t id)
अणु
	अगर (!(filp->f_mode & FMODE_WRITE))
		वापस 0;

	वापस xillybus_myflush(filp->निजी_data, HZ); /* 1 second समयout */
पूर्ण

अटल व्योम xillybus_स्वतःflush(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *workitem = container_of(
		work, काष्ठा delayed_work, work);
	काष्ठा xilly_channel *channel = container_of(
		workitem, काष्ठा xilly_channel, rd_workitem);
	पूर्णांक rc;

	rc = xillybus_myflush(channel, -1);
	अगर (rc == -EINTR)
		dev_warn(channel->endpoपूर्णांक->dev,
			 "Autoflush failed because work queue thread got a signal.\n");
	अन्यथा अगर (rc)
		dev_err(channel->endpoपूर्णांक->dev,
			"Autoflush failed under weird circumstances.\n");
पूर्ण

अटल sमाप_प्रकार xillybus_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *userbuf,
			      माप_प्रकार count, loff_t *f_pos)
अणु
	sमाप_प्रकार rc;
	अचिन्हित दीर्घ flags;
	पूर्णांक bytes_करोne = 0;
	काष्ठा xilly_channel *channel = filp->निजी_data;

	पूर्णांक full, exhausted;
	/* Initializations are there only to silence warnings */

	पूर्णांक howmany = 0, bufpos = 0, bufidx = 0, bufferकरोne = 0;
	पूर्णांक end_offset_plus1 = 0;

	अगर (channel->endpoपूर्णांक->fatal_error)
		वापस -EIO;

	rc = mutex_lock_पूर्णांकerruptible(&channel->rd_mutex);
	अगर (rc)
		वापस rc;

	जबतक (1) अणु
		पूर्णांक bytes_to_करो = count - bytes_करोne;

		spin_lock_irqsave(&channel->rd_spinlock, flags);

		full = channel->rd_full;

		अगर (!full) अणु
			bufidx = channel->rd_host_buf_idx;
			bufpos = channel->rd_host_buf_pos;
			howmany = channel->rd_buf_size - bufpos;

			/*
			 * Update rd_host_* to its state after this operation.
			 * count=0 means committing the buffer immediately,
			 * which is like flushing, but not necessarily block.
			 */

			अगर ((howmany > bytes_to_करो) &&
			    (count ||
			     ((bufpos >> channel->log2_element_size) == 0))) अणु
				bufferकरोne = 0;

				howmany = bytes_to_करो;
				channel->rd_host_buf_pos += howmany;
			पूर्ण अन्यथा अणु
				bufferकरोne = 1;

				अगर (count) अणु
					end_offset_plus1 =
						channel->rd_buf_size >>
						channel->log2_element_size;
					channel->rd_host_buf_pos = 0;
				पूर्ण अन्यथा अणु
					अचिन्हित अक्षर *tail;
					पूर्णांक i;

					howmany = 0;

					end_offset_plus1 = bufpos >>
						channel->log2_element_size;

					channel->rd_host_buf_pos -=
						end_offset_plus1 <<
						channel->log2_element_size;

					tail = channel->
						rd_buffers[bufidx]->addr +
						(end_offset_plus1 <<
						 channel->log2_element_size);

					क्रम (i = 0;
					     i < channel->rd_host_buf_pos;
					     i++)
						channel->rd_leftovers[i] =
							*tail++;
				पूर्ण

				अगर (bufidx == channel->rd_fpga_buf_idx)
					channel->rd_full = 1;

				अगर (bufidx >= (channel->num_rd_buffers - 1))
					channel->rd_host_buf_idx = 0;
				अन्यथा
					channel->rd_host_buf_idx++;
			पूर्ण
		पूर्ण

		/*
		 * Marking our situation after the possible changes above,
		 * क्रम use  after releasing the spinlock.
		 *
		 * full = full beक्रमe change
		 * exhasted = full after possible change
		 */

		exhausted = channel->rd_full;

		spin_unlock_irqrestore(&channel->rd_spinlock, flags);

		अगर (!full) अणु /* Go on, now without the spinlock */
			अचिन्हित अक्षर *head =
				channel->rd_buffers[bufidx]->addr;
			पूर्णांक i;

			अगर ((bufpos == 0) || /* Zero means it's virgin */
			    (channel->rd_leftovers[3] != 0)) अणु
				channel->endpoपूर्णांक->ephw->hw_sync_sgl_क्रम_cpu(
					channel->endpoपूर्णांक,
					channel->rd_buffers[bufidx]->dma_addr,
					channel->rd_buf_size,
					DMA_TO_DEVICE);

				/* Virgin, but leftovers are due */
				क्रम (i = 0; i < bufpos; i++)
					*head++ = channel->rd_leftovers[i];

				channel->rd_leftovers[3] = 0; /* Clear flag */
			पूर्ण

			अगर (copy_from_user(
				    channel->rd_buffers[bufidx]->addr + bufpos,
				    userbuf, howmany))
				rc = -EFAULT;

			userbuf += howmany;
			bytes_करोne += howmany;

			अगर (bufferकरोne) अणु
				channel->endpoपूर्णांक->ephw->hw_sync_sgl_क्रम_device(
					channel->endpoपूर्णांक,
					channel->rd_buffers[bufidx]->dma_addr,
					channel->rd_buf_size,
					DMA_TO_DEVICE);

				mutex_lock(&channel->endpoपूर्णांक->रेजिस्टर_mutex);

				ioग_लिखो32(end_offset_plus1 - 1,
					  channel->endpoपूर्णांक->रेजिस्टरs +
					  fpga_buf_offset_reg);

				ioग_लिखो32((channel->chan_num << 1) |
					  (2 << 24) |  /* 2 = submit buffer */
					  (bufidx << 12),
					  channel->endpoपूर्णांक->रेजिस्टरs +
					  fpga_buf_ctrl_reg);

				mutex_unlock(&channel->endpoपूर्णांक->
					     रेजिस्टर_mutex);

				channel->rd_leftovers[3] =
					(channel->rd_host_buf_pos != 0);
			पूर्ण

			अगर (rc) अणु
				mutex_unlock(&channel->rd_mutex);

				अगर (channel->endpoपूर्णांक->fatal_error)
					वापस -EIO;

				अगर (!channel->rd_synchronous)
					queue_delayed_work(
						xillybus_wq,
						&channel->rd_workitem,
						XILLY_RX_TIMEOUT);

				वापस rc;
			पूर्ण
		पूर्ण

		अगर (bytes_करोne >= count)
			अवरोध;

		अगर (!exhausted)
			जारी; /* If there's more space, just go on */

		अगर ((bytes_करोne > 0) && channel->rd_allow_partial)
			अवरोध;

		/*
		 * Indefinite sleep with mutex taken. With data रुकोing क्रम
		 * flushing, user should not be surprised अगर खोलो() क्रम ग_लिखो
		 * sleeps.
		 */

		अगर (filp->f_flags & O_NONBLOCK) अणु
			rc = -EAGAIN;
			अवरोध;
		पूर्ण

		अगर (रुको_event_पूर्णांकerruptible(channel->rd_रुको,
					     (!channel->rd_full))) अणु
			mutex_unlock(&channel->rd_mutex);

			अगर (channel->endpoपूर्णांक->fatal_error)
				वापस -EIO;

			अगर (bytes_करोne)
				वापस bytes_करोne;
			वापस -EINTR;
		पूर्ण
	पूर्ण

	mutex_unlock(&channel->rd_mutex);

	अगर (!channel->rd_synchronous)
		queue_delayed_work(xillybus_wq,
				   &channel->rd_workitem,
				   XILLY_RX_TIMEOUT);

	अगर (channel->endpoपूर्णांक->fatal_error)
		वापस -EIO;

	अगर (rc)
		वापस rc;

	अगर ((channel->rd_synchronous) && (bytes_करोne > 0)) अणु
		rc = xillybus_myflush(filp->निजी_data, 0); /* No समयout */

		अगर (rc && (rc != -EINTR))
			वापस rc;
	पूर्ण

	वापस bytes_करोne;
पूर्ण

अटल पूर्णांक xillybus_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	पूर्णांक rc = 0;
	अचिन्हित दीर्घ flags;
	पूर्णांक minor = iminor(inode);
	पूर्णांक major = imajor(inode);
	काष्ठा xilly_endpoपूर्णांक *ep_iter, *endpoपूर्णांक = शून्य;
	काष्ठा xilly_channel *channel;

	mutex_lock(&ep_list_lock);

	list_क्रम_each_entry(ep_iter, &list_of_endpoपूर्णांकs, ep_list) अणु
		अगर ((ep_iter->major == major) &&
		    (minor >= ep_iter->lowest_minor) &&
		    (minor < (ep_iter->lowest_minor +
			      ep_iter->num_channels))) अणु
			endpoपूर्णांक = ep_iter;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&ep_list_lock);

	अगर (!endpoपूर्णांक) अणु
		pr_err("xillybus: open() failed to find a device for major=%d and minor=%d\n",
		       major, minor);
		वापस -ENODEV;
	पूर्ण

	अगर (endpoपूर्णांक->fatal_error)
		वापस -EIO;

	channel = endpoपूर्णांक->channels[1 + minor - endpoपूर्णांक->lowest_minor];
	filp->निजी_data = channel;

	/*
	 * It माला_लो complicated because:
	 * 1. We करोn't want to take a mutex we don't have to
	 * 2. We करोn't want to खोलो one direction अगर the other will fail.
	 */

	अगर ((filp->f_mode & FMODE_READ) && (!channel->num_wr_buffers))
		वापस -ENODEV;

	अगर ((filp->f_mode & FMODE_WRITE) && (!channel->num_rd_buffers))
		वापस -ENODEV;

	अगर ((filp->f_mode & FMODE_READ) && (filp->f_flags & O_NONBLOCK) &&
	    (channel->wr_synchronous || !channel->wr_allow_partial ||
	     !channel->wr_supports_nonempty)) अणु
		dev_err(endpoपूर्णांक->dev,
			"open() failed: O_NONBLOCK not allowed for read on this device\n");
		वापस -ENODEV;
	पूर्ण

	अगर ((filp->f_mode & FMODE_WRITE) && (filp->f_flags & O_NONBLOCK) &&
	    (channel->rd_synchronous || !channel->rd_allow_partial)) अणु
		dev_err(endpoपूर्णांक->dev,
			"open() failed: O_NONBLOCK not allowed for write on this device\n");
		वापस -ENODEV;
	पूर्ण

	/*
	 * Note: खोलो() may block on getting mutexes despite O_NONBLOCK.
	 * This shouldn't occur normally, since multiple खोलो of the same
	 * file descriptor is almost always prohibited anyhow
	 * (*_exclusive_खोलो is normally set in real-lअगरe प्रणालीs).
	 */

	अगर (filp->f_mode & FMODE_READ) अणु
		rc = mutex_lock_पूर्णांकerruptible(&channel->wr_mutex);
		अगर (rc)
			वापस rc;
	पूर्ण

	अगर (filp->f_mode & FMODE_WRITE) अणु
		rc = mutex_lock_पूर्णांकerruptible(&channel->rd_mutex);
		अगर (rc)
			जाओ unlock_wr;
	पूर्ण

	अगर ((filp->f_mode & FMODE_READ) &&
	    (channel->wr_ref_count != 0) &&
	    (channel->wr_exclusive_खोलो)) अणु
		rc = -EBUSY;
		जाओ unlock;
	पूर्ण

	अगर ((filp->f_mode & FMODE_WRITE) &&
	    (channel->rd_ref_count != 0) &&
	    (channel->rd_exclusive_खोलो)) अणु
		rc = -EBUSY;
		जाओ unlock;
	पूर्ण

	अगर (filp->f_mode & FMODE_READ) अणु
		अगर (channel->wr_ref_count == 0) अणु /* First खोलो of file */
			/* Move the host to first buffer */
			spin_lock_irqsave(&channel->wr_spinlock, flags);
			channel->wr_host_buf_idx = 0;
			channel->wr_host_buf_pos = 0;
			channel->wr_fpga_buf_idx = -1;
			channel->wr_empty = 1;
			channel->wr_पढ़ोy = 0;
			channel->wr_sleepy = 1;
			channel->wr_eof = -1;
			channel->wr_hangup = 0;

			spin_unlock_irqrestore(&channel->wr_spinlock, flags);

			ioग_लिखो32(1 | (channel->chan_num << 1) |
				  (4 << 24) |  /* Opcode 4, खोलो channel */
				  ((channel->wr_synchronous & 1) << 23),
				  channel->endpoपूर्णांक->रेजिस्टरs +
				  fpga_buf_ctrl_reg);
		पूर्ण

		channel->wr_ref_count++;
	पूर्ण

	अगर (filp->f_mode & FMODE_WRITE) अणु
		अगर (channel->rd_ref_count == 0) अणु /* First खोलो of file */
			/* Move the host to first buffer */
			spin_lock_irqsave(&channel->rd_spinlock, flags);
			channel->rd_host_buf_idx = 0;
			channel->rd_host_buf_pos = 0;
			channel->rd_leftovers[3] = 0; /* No leftovers. */
			channel->rd_fpga_buf_idx = channel->num_rd_buffers - 1;
			channel->rd_full = 0;

			spin_unlock_irqrestore(&channel->rd_spinlock, flags);

			ioग_लिखो32((channel->chan_num << 1) |
				  (4 << 24),   /* Opcode 4, खोलो channel */
				  channel->endpoपूर्णांक->रेजिस्टरs +
				  fpga_buf_ctrl_reg);
		पूर्ण

		channel->rd_ref_count++;
	पूर्ण

unlock:
	अगर (filp->f_mode & FMODE_WRITE)
		mutex_unlock(&channel->rd_mutex);
unlock_wr:
	अगर (filp->f_mode & FMODE_READ)
		mutex_unlock(&channel->wr_mutex);

	अगर (!rc && (!channel->seekable))
		वापस nonseekable_खोलो(inode, filp);

	वापस rc;
पूर्ण

अटल पूर्णांक xillybus_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा xilly_channel *channel = filp->निजी_data;

	पूर्णांक buf_idx;
	पूर्णांक eof;

	अगर (channel->endpoपूर्णांक->fatal_error)
		वापस -EIO;

	अगर (filp->f_mode & FMODE_WRITE) अणु
		mutex_lock(&channel->rd_mutex);

		channel->rd_ref_count--;

		अगर (channel->rd_ref_count == 0) अणु
			/*
			 * We rely on the kernel calling flush()
			 * beक्रमe we get here.
			 */

			ioग_लिखो32((channel->chan_num << 1) | /* Channel ID */
				  (5 << 24),  /* Opcode 5, बंद channel */
				  channel->endpoपूर्णांक->रेजिस्टरs +
				  fpga_buf_ctrl_reg);
		पूर्ण
		mutex_unlock(&channel->rd_mutex);
	पूर्ण

	अगर (filp->f_mode & FMODE_READ) अणु
		mutex_lock(&channel->wr_mutex);

		channel->wr_ref_count--;

		अगर (channel->wr_ref_count == 0) अणु
			ioग_लिखो32(1 | (channel->chan_num << 1) |
				  (5 << 24),  /* Opcode 5, बंद channel */
				  channel->endpoपूर्णांक->रेजिस्टरs +
				  fpga_buf_ctrl_reg);

			/*
			 * This is crazily cautious: We make sure that not
			 * only that we got an खातापूर्ण (be it because we बंदd
			 * the channel or because of a user's खातापूर्ण), but verअगरy
			 * that it's one beyond the last buffer arrived, so
			 * we have no leftover buffers pending beक्रमe wrapping
			 * up (which can only happen in asynchronous channels,
			 * BTW)
			 */

			जबतक (1) अणु
				spin_lock_irqsave(&channel->wr_spinlock,
						  flags);
				buf_idx = channel->wr_fpga_buf_idx;
				eof = channel->wr_eof;
				channel->wr_sleepy = 1;
				spin_unlock_irqrestore(&channel->wr_spinlock,
						       flags);

				/*
				 * Check अगर eof poपूर्णांकs at the buffer after
				 * the last one the FPGA submitted. Note that
				 * no खातापूर्ण is marked by negative eof.
				 */

				buf_idx++;
				अगर (buf_idx == channel->num_wr_buffers)
					buf_idx = 0;

				अगर (buf_idx == eof)
					अवरोध;

				/*
				 * Steal extra 100 ms अगर awaken by पूर्णांकerrupt.
				 * This is a simple workaround क्रम an
				 * पूर्णांकerrupt pending when entering, which would
				 * otherwise result in declaring the hardware
				 * non-responsive.
				 */

				अगर (रुको_event_पूर्णांकerruptible(
					    channel->wr_रुको,
					    (!channel->wr_sleepy)))
					msleep(100);

				अगर (channel->wr_sleepy) अणु
					mutex_unlock(&channel->wr_mutex);
					dev_warn(channel->endpoपूर्णांक->dev,
						 "Hardware failed to respond to close command, therefore left in messy state.\n");
					वापस -EINTR;
				पूर्ण
			पूर्ण
		पूर्ण

		mutex_unlock(&channel->wr_mutex);
	पूर्ण

	वापस 0;
पूर्ण

अटल loff_t xillybus_llseek(काष्ठा file *filp, loff_t offset, पूर्णांक whence)
अणु
	काष्ठा xilly_channel *channel = filp->निजी_data;
	loff_t pos = filp->f_pos;
	पूर्णांक rc = 0;

	/*
	 * Take both mutexes not allowing पूर्णांकerrupts, since it seems like
	 * common applications करोn't expect an -EINTR here. Besides, multiple
	 * access to a single file descriptor on seekable devices is a mess
	 * anyhow.
	 */

	अगर (channel->endpoपूर्णांक->fatal_error)
		वापस -EIO;

	mutex_lock(&channel->wr_mutex);
	mutex_lock(&channel->rd_mutex);

	चयन (whence) अणु
	हाल शुरू_से:
		pos = offset;
		अवरोध;
	हाल प्रस्तुत_से:
		pos += offset;
		अवरोध;
	हाल अंत_से:
		pos = offset; /* Going to the end => to the beginning */
		अवरोध;
	शेष:
		rc = -EINVAL;
		जाओ end;
	पूर्ण

	/* In any हाल, we must finish on an element boundary */
	अगर (pos & ((1 << channel->log2_element_size) - 1)) अणु
		rc = -EINVAL;
		जाओ end;
	पूर्ण

	mutex_lock(&channel->endpoपूर्णांक->रेजिस्टर_mutex);

	ioग_लिखो32(pos >> channel->log2_element_size,
		  channel->endpoपूर्णांक->रेजिस्टरs + fpga_buf_offset_reg);

	ioग_लिखो32((channel->chan_num << 1) |
		  (6 << 24),  /* Opcode 6, set address */
		  channel->endpoपूर्णांक->रेजिस्टरs + fpga_buf_ctrl_reg);

	mutex_unlock(&channel->endpoपूर्णांक->रेजिस्टर_mutex);

end:
	mutex_unlock(&channel->rd_mutex);
	mutex_unlock(&channel->wr_mutex);

	अगर (rc) /* Return error after releasing mutexes */
		वापस rc;

	filp->f_pos = pos;

	/*
	 * Since seekable devices are allowed only when the channel is
	 * synchronous, we assume that there is no data pending in either
	 * direction (which holds true as दीर्घ as no concurrent access on the
	 * file descriptor takes place).
	 * The only thing we may need to throw away is leftovers from partial
	 * ग_लिखो() flush.
	 */

	channel->rd_leftovers[3] = 0;

	वापस pos;
पूर्ण

अटल __poll_t xillybus_poll(काष्ठा file *filp, poll_table *रुको)
अणु
	काष्ठा xilly_channel *channel = filp->निजी_data;
	__poll_t mask = 0;
	अचिन्हित दीर्घ flags;

	poll_रुको(filp, &channel->endpoपूर्णांक->ep_रुको, रुको);

	/*
	 * poll() won't play ball regarding पढ़ो() channels which
	 * aren't asynchronous and support the nonempty message. Allowing
	 * that will create situations where data has been delivered at
	 * the FPGA, and users expecting select() to wake up, which it may
	 * not.
	 */

	अगर (!channel->wr_synchronous && channel->wr_supports_nonempty) अणु
		poll_रुको(filp, &channel->wr_रुको, रुको);
		poll_रुको(filp, &channel->wr_पढ़ोy_रुको, रुको);

		spin_lock_irqsave(&channel->wr_spinlock, flags);
		अगर (!channel->wr_empty || channel->wr_पढ़ोy)
			mask |= EPOLLIN | EPOLLRDNORM;

		अगर (channel->wr_hangup)
			/*
			 * Not EPOLLHUP, because its behavior is in the
			 * mist, and EPOLLIN करोes what we want: Wake up
			 * the पढ़ो file descriptor so it sees खातापूर्ण.
			 */
			mask |=  EPOLLIN | EPOLLRDNORM;
		spin_unlock_irqrestore(&channel->wr_spinlock, flags);
	पूर्ण

	/*
	 * If partial data ग_लिखो is disallowed on a ग_लिखो() channel,
	 * it's poपूर्णांकless to ever संकेत OK to ग_लिखो, because is could
	 * block despite some space being available.
	 */

	अगर (channel->rd_allow_partial) अणु
		poll_रुको(filp, &channel->rd_रुको, रुको);

		spin_lock_irqsave(&channel->rd_spinlock, flags);
		अगर (!channel->rd_full)
			mask |= EPOLLOUT | EPOLLWRNORM;
		spin_unlock_irqrestore(&channel->rd_spinlock, flags);
	पूर्ण

	अगर (channel->endpoपूर्णांक->fatal_error)
		mask |= EPOLLERR;

	वापस mask;
पूर्ण

अटल स्थिर काष्ठा file_operations xillybus_fops = अणु
	.owner      = THIS_MODULE,
	.पढ़ो       = xillybus_पढ़ो,
	.ग_लिखो      = xillybus_ग_लिखो,
	.खोलो       = xillybus_खोलो,
	.flush      = xillybus_flush,
	.release    = xillybus_release,
	.llseek     = xillybus_llseek,
	.poll       = xillybus_poll,
पूर्ण;

अटल पूर्णांक xillybus_init_chrdev(काष्ठा xilly_endpoपूर्णांक *endpoपूर्णांक,
				स्थिर अचिन्हित अक्षर *idt)
अणु
	पूर्णांक rc;
	dev_t dev;
	पूर्णांक devnum, i, minor, major;
	अक्षर devname[48];
	काष्ठा device *device;

	rc = alloc_chrdev_region(&dev, 0, /* minor start */
				 endpoपूर्णांक->num_channels,
				 xillyname);
	अगर (rc) अणु
		dev_warn(endpoपूर्णांक->dev, "Failed to obtain major/minors");
		वापस rc;
	पूर्ण

	endpoपूर्णांक->major = major = MAJOR(dev);
	endpoपूर्णांक->lowest_minor = minor = MINOR(dev);

	cdev_init(&endpoपूर्णांक->cdev, &xillybus_fops);
	endpoपूर्णांक->cdev.owner = endpoपूर्णांक->ephw->owner;
	rc = cdev_add(&endpoपूर्णांक->cdev, MKDEV(major, minor),
		      endpoपूर्णांक->num_channels);
	अगर (rc) अणु
		dev_warn(endpoपूर्णांक->dev, "Failed to add cdev. Aborting.\n");
		जाओ unरेजिस्टर_chrdev;
	पूर्ण

	idt++;

	क्रम (i = minor, devnum = 0;
	     devnum < endpoपूर्णांक->num_channels;
	     devnum++, i++) अणु
		snम_लिखो(devname, माप(devname)-1, "xillybus_%s", idt);

		devname[माप(devname)-1] = 0; /* Should never matter */

		जबतक (*idt++)
			/* Skip to next */;

		device = device_create(xillybus_class,
				       शून्य,
				       MKDEV(major, i),
				       शून्य,
				       "%s", devname);

		अगर (IS_ERR(device)) अणु
			dev_warn(endpoपूर्णांक->dev,
				 "Failed to create %s device. Aborting.\n",
				 devname);
			rc = -ENODEV;
			जाओ unroll_device_create;
		पूर्ण
	पूर्ण

	dev_info(endpoपूर्णांक->dev, "Created %d device files.\n",
		 endpoपूर्णांक->num_channels);
	वापस 0; /* succeed */

unroll_device_create:
	devnum--; i--;
	क्रम (; devnum >= 0; devnum--, i--)
		device_destroy(xillybus_class, MKDEV(major, i));

	cdev_del(&endpoपूर्णांक->cdev);
unरेजिस्टर_chrdev:
	unरेजिस्टर_chrdev_region(MKDEV(major, minor), endpoपूर्णांक->num_channels);

	वापस rc;
पूर्ण

अटल व्योम xillybus_cleanup_chrdev(काष्ठा xilly_endpoपूर्णांक *endpoपूर्णांक)
अणु
	पूर्णांक minor;

	क्रम (minor = endpoपूर्णांक->lowest_minor;
	     minor < (endpoपूर्णांक->lowest_minor + endpoपूर्णांक->num_channels);
	     minor++)
		device_destroy(xillybus_class, MKDEV(endpoपूर्णांक->major, minor));
	cdev_del(&endpoपूर्णांक->cdev);
	unरेजिस्टर_chrdev_region(MKDEV(endpoपूर्णांक->major,
				       endpoपूर्णांक->lowest_minor),
				 endpoपूर्णांक->num_channels);

	dev_info(endpoपूर्णांक->dev, "Removed %d device files.\n",
		 endpoपूर्णांक->num_channels);
पूर्ण

काष्ठा xilly_endpoपूर्णांक *xillybus_init_endpoपूर्णांक(काष्ठा pci_dev *pdev,
					      काष्ठा device *dev,
					      काष्ठा xilly_endpoपूर्णांक_hardware
					      *ephw)
अणु
	काष्ठा xilly_endpoपूर्णांक *endpoपूर्णांक;

	endpoपूर्णांक = devm_kzalloc(dev, माप(*endpoपूर्णांक), GFP_KERNEL);
	अगर (!endpoपूर्णांक)
		वापस शून्य;

	endpoपूर्णांक->pdev = pdev;
	endpoपूर्णांक->dev = dev;
	endpoपूर्णांक->ephw = ephw;
	endpoपूर्णांक->msg_counter = 0x0b;
	endpoपूर्णांक->failed_messages = 0;
	endpoपूर्णांक->fatal_error = 0;

	init_रुकोqueue_head(&endpoपूर्णांक->ep_रुको);
	mutex_init(&endpoपूर्णांक->रेजिस्टर_mutex);

	वापस endpoपूर्णांक;
पूर्ण
EXPORT_SYMBOL(xillybus_init_endpoपूर्णांक);

अटल पूर्णांक xilly_quiesce(काष्ठा xilly_endpoपूर्णांक *endpoपूर्णांक)
अणु
	दीर्घ t;

	endpoपूर्णांक->idtlen = -1;

	ioग_लिखो32((u32) (endpoपूर्णांक->dma_using_dac & 0x0001),
		  endpoपूर्णांक->रेजिस्टरs + fpga_dma_control_reg);

	t = रुको_event_पूर्णांकerruptible_समयout(endpoपूर्णांक->ep_रुको,
					     (endpoपूर्णांक->idtlen >= 0),
					     XILLY_TIMEOUT);
	अगर (t <= 0) अणु
		dev_err(endpoपूर्णांक->dev,
			"Failed to quiesce the device on exit.\n");
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक xillybus_endpoपूर्णांक_discovery(काष्ठा xilly_endpoपूर्णांक *endpoपूर्णांक)
अणु
	पूर्णांक rc;
	दीर्घ t;

	व्योम *bootstrap_resources;
	पूर्णांक idtbuffersize = (1 << PAGE_SHIFT);
	काष्ठा device *dev = endpoपूर्णांक->dev;

	/*
	 * The bogus IDT is used during bootstrap क्रम allocating the initial
	 * message buffer, and then the message buffer and space क्रम the IDT
	 * itself. The initial message buffer is of a single page's size, but
	 * it's soon replaced with a more modest one (and memory is मुक्तd).
	 */

	अचिन्हित अक्षर bogus_idt[8] = अणु 1, 224, (PAGE_SHIFT)-2, 0,
				       3, 192, PAGE_SHIFT, 0 पूर्ण;
	काष्ठा xilly_idt_handle idt_handle;

	/*
	 * Writing the value 0x00000001 to Endianness रेजिस्टर संकेतs which
	 * endianness this processor is using, so the FPGA can swap words as
	 * necessary.
	 */

	ioग_लिखो32(1, endpoपूर्णांक->रेजिस्टरs + fpga_endian_reg);

	/* Bootstrap phase I: Allocate temporary message buffer */

	bootstrap_resources = devres_खोलो_group(dev, शून्य, GFP_KERNEL);
	अगर (!bootstrap_resources)
		वापस -ENOMEM;

	endpoपूर्णांक->num_channels = 0;

	rc = xilly_setupchannels(endpoपूर्णांक, bogus_idt, 1);
	अगर (rc)
		वापस rc;

	/* Clear the message subप्रणाली (and counter in particular) */
	ioग_लिखो32(0x04, endpoपूर्णांक->रेजिस्टरs + fpga_msg_ctrl_reg);

	endpoपूर्णांक->idtlen = -1;

	/*
	 * Set DMA 32/64 bit mode, quiesce the device (?!) and get IDT
	 * buffer size.
	 */
	ioग_लिखो32((u32) (endpoपूर्णांक->dma_using_dac & 0x0001),
		  endpoपूर्णांक->रेजिस्टरs + fpga_dma_control_reg);

	t = रुको_event_पूर्णांकerruptible_समयout(endpoपूर्णांक->ep_रुको,
					     (endpoपूर्णांक->idtlen >= 0),
					     XILLY_TIMEOUT);
	अगर (t <= 0) अणु
		dev_err(endpoपूर्णांक->dev, "No response from FPGA. Aborting.\n");
		वापस -ENODEV;
	पूर्ण

	/* Enable DMA */
	ioग_लिखो32((u32) (0x0002 | (endpoपूर्णांक->dma_using_dac & 0x0001)),
		  endpoपूर्णांक->रेजिस्टरs + fpga_dma_control_reg);

	/* Bootstrap phase II: Allocate buffer क्रम IDT and obtain it */
	जबतक (endpoपूर्णांक->idtlen >= idtbuffersize) अणु
		idtbuffersize *= 2;
		bogus_idt[6]++;
	पूर्ण

	endpoपूर्णांक->num_channels = 1;

	rc = xilly_setupchannels(endpoपूर्णांक, bogus_idt, 2);
	अगर (rc)
		जाओ failed_idt;

	rc = xilly_obtain_idt(endpoपूर्णांक);
	अगर (rc)
		जाओ failed_idt;

	rc = xilly_scan_idt(endpoपूर्णांक, &idt_handle);
	अगर (rc)
		जाओ failed_idt;

	devres_बंद_group(dev, bootstrap_resources);

	/* Bootstrap phase III: Allocate buffers according to IDT */

	rc = xilly_setupchannels(endpoपूर्णांक,
				 idt_handle.chandesc,
				 idt_handle.entries);
	अगर (rc)
		जाओ failed_idt;

	/*
	 * endpoपूर्णांक is now completely configured. We put it on the list
	 * available to खोलो() beक्रमe रेजिस्टरing the अक्षर device(s)
	 */

	mutex_lock(&ep_list_lock);
	list_add_tail(&endpoपूर्णांक->ep_list, &list_of_endpoपूर्णांकs);
	mutex_unlock(&ep_list_lock);

	rc = xillybus_init_chrdev(endpoपूर्णांक, idt_handle.idt);
	अगर (rc)
		जाओ failed_chrdevs;

	devres_release_group(dev, bootstrap_resources);

	वापस 0;

failed_chrdevs:
	mutex_lock(&ep_list_lock);
	list_del(&endpoपूर्णांक->ep_list);
	mutex_unlock(&ep_list_lock);

failed_idt:
	xilly_quiesce(endpoपूर्णांक);
	flush_workqueue(xillybus_wq);

	वापस rc;
पूर्ण
EXPORT_SYMBOL(xillybus_endpoपूर्णांक_discovery);

व्योम xillybus_endpoपूर्णांक_हटाओ(काष्ठा xilly_endpoपूर्णांक *endpoपूर्णांक)
अणु
	xillybus_cleanup_chrdev(endpoपूर्णांक);

	mutex_lock(&ep_list_lock);
	list_del(&endpoपूर्णांक->ep_list);
	mutex_unlock(&ep_list_lock);

	xilly_quiesce(endpoपूर्णांक);

	/*
	 * Flushing is करोne upon endpoपूर्णांक release to prevent access to memory
	 * just about to be released. This makes the quiesce complete.
	 */
	flush_workqueue(xillybus_wq);
पूर्ण
EXPORT_SYMBOL(xillybus_endpoपूर्णांक_हटाओ);

अटल पूर्णांक __init xillybus_init(व्योम)
अणु
	mutex_init(&ep_list_lock);

	xillybus_class = class_create(THIS_MODULE, xillyname);
	अगर (IS_ERR(xillybus_class))
		वापस PTR_ERR(xillybus_class);

	xillybus_wq = alloc_workqueue(xillyname, 0, 0);
	अगर (!xillybus_wq) अणु
		class_destroy(xillybus_class);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास xillybus_निकास(व्योम)
अणु
	/* flush_workqueue() was called क्रम each endpoपूर्णांक released */
	destroy_workqueue(xillybus_wq);

	class_destroy(xillybus_class);
पूर्ण

module_init(xillybus_init);
module_निकास(xillybus_निकास);
