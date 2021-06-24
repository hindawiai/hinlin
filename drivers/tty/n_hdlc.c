<शैली गुरु>
// SPDX-License-Identअगरier: GPL-1.0+
/* generic HDLC line discipline क्रम Linux
 *
 * Written by Paul Fulghum paulkf@microgate.com
 * क्रम Microgate Corporation
 *
 * Microgate and SyncLink are रेजिस्टरed trademarks of Microgate Corporation
 *
 * Adapted from ppp.c, written by Michael Callahan <callahan@maths.ox.ac.uk>,
 *	Al Longyear <दीर्घyear@netcom.com>,
 *	Paul Mackerras <Paul.Mackerras@cs.anu.edu.au>
 *
 * Original release 01/11/99
 *
 * This module implements the tty line discipline N_HDLC क्रम use with
 * tty device drivers that support bit-synchronous HDLC communications.
 *
 * All HDLC data is frame oriented which means:
 *
 * 1. tty ग_लिखो calls represent one complete transmit frame of data
 *    The device driver should accept the complete frame or none of
 *    the frame (busy) in the ग_लिखो method. Each ग_लिखो call should have
 *    a byte count in the range of 2-65535 bytes (2 is min HDLC frame
 *    with 1 addr byte and 1 ctrl byte). The max byte count of 65535
 *    should include any crc bytes required. For example, when using
 *    CCITT CRC32, 4 crc bytes are required, so the maximum size frame
 *    the application may transmit is limited to 65531 bytes. For CCITT
 *    CRC16, the maximum application frame size would be 65533.
 *
 *
 * 2. receive callbacks from the device driver represents
 *    one received frame. The device driver should bypass
 *    the tty flip buffer and call the line discipline receive
 *    callback directly to aव्योम fragmenting or concatenating
 *    multiple frames पूर्णांकo a single receive callback.
 *
 *    The HDLC line discipline queues the receive frames in separate
 *    buffers so complete receive frames can be वापसed by the
 *    tty पढ़ो calls.
 *
 * 3. tty पढ़ो calls वापसs an entire frame of data or nothing.
 *
 * 4. all send and receive data is considered raw. No processing
 *    or translation is perक्रमmed by the line discipline, regardless
 *    of the tty flags
 *
 * 5. When line discipline is queried क्रम the amount of receive
 *    data available (FIOC), 0 is वापसed अगर no data available,
 *    otherwise the count of the next available frame is वापसed.
 *    (instead of the sum of all received frame counts).
 *
 * These conventions allow the standard tty programming पूर्णांकerface
 * to be used क्रम synchronous HDLC applications when used with
 * this line discipline (or another line discipline that is frame
 * oriented such as N_PPP).
 *
 * The SyncLink driver (synclink.c) implements both asynchronous
 * (using standard line discipline N_TTY) and synchronous HDLC
 * (using N_HDLC) communications, with the latter using the above
 * conventions.
 *
 * This implementation is very basic and करोes not मुख्यtain
 * any statistics. The मुख्य poपूर्णांक is to enक्रमce the raw data
 * and frame orientation of HDLC communications.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY सूचीECT,
 * INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#घोषणा HDLC_MAGIC 0x239e

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/types.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ptrace.h>

#समावेश <linux/poll.h>
#समावेश <linux/in.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/slab.h>
#समावेश <linux/tty.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>	/* used in new tty drivers */
#समावेश <linux/संकेत.स>	/* used in new tty drivers */
#समावेश <linux/अगर.h>
#समावेश <linux/bitops.h>

#समावेश <यंत्र/termios.h>
#समावेश <linux/uaccess.h>
#समावेश "tty.h"

/*
 * Buffers क्रम inभागidual HDLC frames
 */
#घोषणा MAX_HDLC_FRAME_SIZE 65535
#घोषणा DEFAULT_RX_BUF_COUNT 10
#घोषणा MAX_RX_BUF_COUNT 60
#घोषणा DEFAULT_TX_BUF_COUNT 3

काष्ठा n_hdlc_buf अणु
	काष्ठा list_head  list_item;
	पूर्णांक		  count;
	अक्षर		  buf[];
पूर्ण;

काष्ठा n_hdlc_buf_list अणु
	काष्ठा list_head  list;
	पूर्णांक		  count;
	spinlock_t	  spinlock;
पूर्ण;

/**
 * काष्ठा n_hdlc - per device instance data काष्ठाure
 * @magic: magic value क्रम काष्ठाure
 * @tbusy: reentrancy flag क्रम tx wakeup code
 * @woke_up: tx wakeup needs to be run again as it was called जबतक @tbusy
 * @tx_buf_list: list of pending transmit frame buffers
 * @rx_buf_list: list of received frame buffers
 * @tx_मुक्त_buf_list: list unused transmit frame buffers
 * @rx_मुक्त_buf_list: list unused received frame buffers
 */
काष्ठा n_hdlc अणु
	पूर्णांक			magic;
	bool			tbusy;
	bool			woke_up;
	काष्ठा n_hdlc_buf_list	tx_buf_list;
	काष्ठा n_hdlc_buf_list	rx_buf_list;
	काष्ठा n_hdlc_buf_list	tx_मुक्त_buf_list;
	काष्ठा n_hdlc_buf_list	rx_मुक्त_buf_list;
पूर्ण;

/*
 * HDLC buffer list manipulation functions
 */
अटल व्योम n_hdlc_buf_वापस(काष्ठा n_hdlc_buf_list *buf_list,
						काष्ठा n_hdlc_buf *buf);
अटल व्योम n_hdlc_buf_put(काष्ठा n_hdlc_buf_list *list,
			   काष्ठा n_hdlc_buf *buf);
अटल काष्ठा n_hdlc_buf *n_hdlc_buf_get(काष्ठा n_hdlc_buf_list *list);

/* Local functions */

अटल काष्ठा n_hdlc *n_hdlc_alloc(व्योम);

/* max frame size क्रम memory allocations */
अटल पूर्णांक maxframe = 4096;

अटल व्योम flush_rx_queue(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा n_hdlc *n_hdlc = tty->disc_data;
	काष्ठा n_hdlc_buf *buf;

	जबतक ((buf = n_hdlc_buf_get(&n_hdlc->rx_buf_list)))
		n_hdlc_buf_put(&n_hdlc->rx_मुक्त_buf_list, buf);
पूर्ण

अटल व्योम flush_tx_queue(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा n_hdlc *n_hdlc = tty->disc_data;
	काष्ठा n_hdlc_buf *buf;

	जबतक ((buf = n_hdlc_buf_get(&n_hdlc->tx_buf_list)))
		n_hdlc_buf_put(&n_hdlc->tx_मुक्त_buf_list, buf);
पूर्ण

अटल व्योम n_hdlc_मुक्त_buf_list(काष्ठा n_hdlc_buf_list *list)
अणु
	काष्ठा n_hdlc_buf *buf;

	करो अणु
		buf = n_hdlc_buf_get(list);
		kमुक्त(buf);
	पूर्ण जबतक (buf);
पूर्ण

/**
 * n_hdlc_tty_बंद - line discipline बंद
 * @tty: poपूर्णांकer to tty info काष्ठाure
 *
 * Called when the line discipline is changed to something
 * अन्यथा, the tty is बंदd, or the tty detects a hangup.
 */
अटल व्योम n_hdlc_tty_बंद(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा n_hdlc *n_hdlc = tty->disc_data;

	अगर (n_hdlc->magic != HDLC_MAGIC) अणु
		pr_warn("n_hdlc: trying to close unopened tty!\n");
		वापस;
	पूर्ण
#अगर defined(TTY_NO_WRITE_SPLIT)
	clear_bit(TTY_NO_WRITE_SPLIT, &tty->flags);
#पूर्ण_अगर
	tty->disc_data = शून्य;

	/* Ensure that the n_hdlcd process is not hanging on select()/poll() */
	wake_up_पूर्णांकerruptible(&tty->पढ़ो_रुको);
	wake_up_पूर्णांकerruptible(&tty->ग_लिखो_रुको);

	n_hdlc_मुक्त_buf_list(&n_hdlc->rx_मुक्त_buf_list);
	n_hdlc_मुक्त_buf_list(&n_hdlc->tx_मुक्त_buf_list);
	n_hdlc_मुक्त_buf_list(&n_hdlc->rx_buf_list);
	n_hdlc_मुक्त_buf_list(&n_hdlc->tx_buf_list);
	kमुक्त(n_hdlc);
पूर्ण	/* end of n_hdlc_tty_बंद() */

/**
 * n_hdlc_tty_खोलो - called when line discipline changed to n_hdlc
 * @tty: poपूर्णांकer to tty info काष्ठाure
 *
 * Returns 0 अगर success, otherwise error code
 */
अटल पूर्णांक n_hdlc_tty_खोलो(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा n_hdlc *n_hdlc = tty->disc_data;

	pr_debug("%s() called (device=%s)\n", __func__, tty->name);

	/* There should not be an existing table क्रम this slot. */
	अगर (n_hdlc) अणु
		pr_err("%s: tty already associated!\n", __func__);
		वापस -EEXIST;
	पूर्ण

	n_hdlc = n_hdlc_alloc();
	अगर (!n_hdlc) अणु
		pr_err("%s: n_hdlc_alloc failed\n", __func__);
		वापस -ENखाता;
	पूर्ण

	tty->disc_data = n_hdlc;
	tty->receive_room = 65536;

	/* change tty_io ग_लिखो() to not split large ग_लिखोs पूर्णांकo 8K chunks */
	set_bit(TTY_NO_WRITE_SPLIT, &tty->flags);

	/* flush receive data from driver */
	tty_driver_flush_buffer(tty);

	वापस 0;

पूर्ण	/* end of n_tty_hdlc_खोलो() */

/**
 * n_hdlc_send_frames - send frames on pending send buffer list
 * @n_hdlc: poपूर्णांकer to ldisc instance data
 * @tty: poपूर्णांकer to tty instance data
 *
 * Send frames on pending send buffer list until the driver करोes not accept a
 * frame (busy) this function is called after adding a frame to the send buffer
 * list and by the tty wakeup callback.
 */
अटल व्योम n_hdlc_send_frames(काष्ठा n_hdlc *n_hdlc, काष्ठा tty_काष्ठा *tty)
अणु
	रेजिस्टर पूर्णांक actual;
	अचिन्हित दीर्घ flags;
	काष्ठा n_hdlc_buf *tbuf;

check_again:

	spin_lock_irqsave(&n_hdlc->tx_buf_list.spinlock, flags);
	अगर (n_hdlc->tbusy) अणु
		n_hdlc->woke_up = true;
		spin_unlock_irqrestore(&n_hdlc->tx_buf_list.spinlock, flags);
		वापस;
	पूर्ण
	n_hdlc->tbusy = true;
	n_hdlc->woke_up = false;
	spin_unlock_irqrestore(&n_hdlc->tx_buf_list.spinlock, flags);

	tbuf = n_hdlc_buf_get(&n_hdlc->tx_buf_list);
	जबतक (tbuf) अणु
		pr_debug("sending frame %p, count=%d\n", tbuf, tbuf->count);

		/* Send the next block of data to device */
		set_bit(TTY_DO_WRITE_WAKEUP, &tty->flags);
		actual = tty->ops->ग_लिखो(tty, tbuf->buf, tbuf->count);

		/* rollback was possible and has been करोne */
		अगर (actual == -ERESTARTSYS) अणु
			n_hdlc_buf_वापस(&n_hdlc->tx_buf_list, tbuf);
			अवरोध;
		पूर्ण
		/* अगर transmit error, throw frame away by */
		/* pretending it was accepted by driver */
		अगर (actual < 0)
			actual = tbuf->count;

		अगर (actual == tbuf->count) अणु
			pr_debug("frame %p completed\n", tbuf);

			/* मुक्त current transmit buffer */
			n_hdlc_buf_put(&n_hdlc->tx_मुक्त_buf_list, tbuf);

			/* रुको up sleeping ग_लिखोrs */
			wake_up_पूर्णांकerruptible(&tty->ग_लिखो_रुको);

			/* get next pending transmit buffer */
			tbuf = n_hdlc_buf_get(&n_hdlc->tx_buf_list);
		पूर्ण अन्यथा अणु
			pr_debug("frame %p pending\n", tbuf);

			/*
			 * the buffer was not accepted by driver,
			 * वापस it back पूर्णांकo tx queue
			 */
			n_hdlc_buf_वापस(&n_hdlc->tx_buf_list, tbuf);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!tbuf)
		clear_bit(TTY_DO_WRITE_WAKEUP, &tty->flags);

	/* Clear the re-entry flag */
	spin_lock_irqsave(&n_hdlc->tx_buf_list.spinlock, flags);
	n_hdlc->tbusy = false;
	spin_unlock_irqrestore(&n_hdlc->tx_buf_list.spinlock, flags);

	अगर (n_hdlc->woke_up)
		जाओ check_again;
पूर्ण	/* end of n_hdlc_send_frames() */

/**
 * n_hdlc_tty_wakeup - Callback क्रम transmit wakeup
 * @tty: poपूर्णांकer to associated tty instance data
 *
 * Called when low level device driver can accept more send data.
 */
अटल व्योम n_hdlc_tty_wakeup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा n_hdlc *n_hdlc = tty->disc_data;

	n_hdlc_send_frames(n_hdlc, tty);
पूर्ण	/* end of n_hdlc_tty_wakeup() */

/**
 * n_hdlc_tty_receive - Called by tty driver when receive data is available
 * @tty: poपूर्णांकer to tty instance data
 * @data: poपूर्णांकer to received data
 * @flags: poपूर्णांकer to flags क्रम data
 * @count: count of received data in bytes
 *
 * Called by tty low level driver when receive data is available. Data is
 * पूर्णांकerpreted as one HDLC frame.
 */
अटल व्योम n_hdlc_tty_receive(काष्ठा tty_काष्ठा *tty, स्थिर __u8 *data,
			       अक्षर *flags, पूर्णांक count)
अणु
	रेजिस्टर काष्ठा n_hdlc *n_hdlc = tty->disc_data;
	रेजिस्टर काष्ठा n_hdlc_buf *buf;

	pr_debug("%s() called count=%d\n", __func__, count);

	/* verअगरy line is using HDLC discipline */
	अगर (n_hdlc->magic != HDLC_MAGIC) अणु
		pr_err("line not using HDLC discipline\n");
		वापस;
	पूर्ण

	अगर (count > maxframe) अणु
		pr_debug("rx count>maxframesize, data discarded\n");
		वापस;
	पूर्ण

	/* get a मुक्त HDLC buffer */
	buf = n_hdlc_buf_get(&n_hdlc->rx_मुक्त_buf_list);
	अगर (!buf) अणु
		/*
		 * no buffers in मुक्त list, attempt to allocate another rx
		 * buffer unless the maximum count has been reached
		 */
		अगर (n_hdlc->rx_buf_list.count < MAX_RX_BUF_COUNT)
			buf = kदो_स्मृति(काष्ठा_size(buf, buf, maxframe),
				      GFP_ATOMIC);
	पूर्ण

	अगर (!buf) अणु
		pr_debug("no more rx buffers, data discarded\n");
		वापस;
	पूर्ण

	/* copy received data to HDLC buffer */
	स_नकल(buf->buf, data, count);
	buf->count = count;

	/* add HDLC buffer to list of received frames */
	n_hdlc_buf_put(&n_hdlc->rx_buf_list, buf);

	/* wake up any blocked पढ़ोs and perक्रमm async संकेतling */
	wake_up_पूर्णांकerruptible(&tty->पढ़ो_रुको);
	अगर (tty->fasync != शून्य)
		समाप्त_fasync(&tty->fasync, SIGIO, POLL_IN);

पूर्ण	/* end of n_hdlc_tty_receive() */

/**
 * n_hdlc_tty_पढ़ो - Called to retrieve one frame of data (अगर available)
 * @tty: poपूर्णांकer to tty instance data
 * @file: poपूर्णांकer to खोलो file object
 * @buf: poपूर्णांकer to वापसed data buffer
 * @nr: size of वापसed data buffer
 *
 * Returns the number of bytes वापसed or error code.
 */
अटल sमाप_प्रकार n_hdlc_tty_पढ़ो(काष्ठा tty_काष्ठा *tty, काष्ठा file *file,
			   __u8 *kbuf, माप_प्रकार nr,
			   व्योम **cookie, अचिन्हित दीर्घ offset)
अणु
	काष्ठा n_hdlc *n_hdlc = tty->disc_data;
	पूर्णांक ret = 0;
	काष्ठा n_hdlc_buf *rbuf;
	DECLARE_WAITQUEUE(रुको, current);

	/* Is this a repeated call क्रम an rbuf we alपढ़ोy found earlier? */
	rbuf = *cookie;
	अगर (rbuf)
		जाओ have_rbuf;

	add_रुको_queue(&tty->पढ़ो_रुको, &रुको);

	क्रम (;;) अणु
		अगर (test_bit(TTY_OTHER_CLOSED, &tty->flags)) अणु
			ret = -EIO;
			अवरोध;
		पूर्ण
		अगर (tty_hung_up_p(file))
			अवरोध;

		set_current_state(TASK_INTERRUPTIBLE);

		rbuf = n_hdlc_buf_get(&n_hdlc->rx_buf_list);
		अगर (rbuf)
			अवरोध;

		/* no data */
		अगर (tty_io_nonblock(tty, file)) अणु
			ret = -EAGAIN;
			अवरोध;
		पूर्ण

		schedule();

		अगर (संकेत_pending(current)) अणु
			ret = -EINTR;
			अवरोध;
		पूर्ण
	पूर्ण

	हटाओ_रुको_queue(&tty->पढ़ो_रुको, &रुको);
	__set_current_state(TASK_RUNNING);

	अगर (!rbuf)
		वापस ret;
	*cookie = rbuf;

have_rbuf:
	/* Have we used it up entirely? */
	अगर (offset >= rbuf->count)
		जाओ करोne_with_rbuf;

	/* More data to go, but can't copy any more? EOVERFLOW */
	ret = -EOVERFLOW;
	अगर (!nr)
		जाओ करोne_with_rbuf;

	/* Copy as much data as possible */
	ret = rbuf->count - offset;
	अगर (ret > nr)
		ret = nr;
	स_नकल(kbuf, rbuf->buf+offset, ret);
	offset += ret;

	/* If we still have data left, we leave the rbuf in the cookie */
	अगर (offset < rbuf->count)
		वापस ret;

करोne_with_rbuf:
	*cookie = शून्य;

	अगर (n_hdlc->rx_मुक्त_buf_list.count > DEFAULT_RX_BUF_COUNT)
		kमुक्त(rbuf);
	अन्यथा
		n_hdlc_buf_put(&n_hdlc->rx_मुक्त_buf_list, rbuf);

	वापस ret;

पूर्ण	/* end of n_hdlc_tty_पढ़ो() */

/**
 * n_hdlc_tty_ग_लिखो - ग_लिखो a single frame of data to device
 * @tty: poपूर्णांकer to associated tty device instance data
 * @file: poपूर्णांकer to file object data
 * @data: poपूर्णांकer to transmit data (one frame)
 * @count: size of transmit frame in bytes
 *
 * Returns the number of bytes written (or error code).
 */
अटल sमाप_प्रकार n_hdlc_tty_ग_लिखो(काष्ठा tty_काष्ठा *tty, काष्ठा file *file,
			    स्थिर अचिन्हित अक्षर *data, माप_प्रकार count)
अणु
	काष्ठा n_hdlc *n_hdlc = tty->disc_data;
	पूर्णांक error = 0;
	DECLARE_WAITQUEUE(रुको, current);
	काष्ठा n_hdlc_buf *tbuf;

	pr_debug("%s() called count=%zd\n", __func__, count);

	अगर (n_hdlc->magic != HDLC_MAGIC)
		वापस -EIO;

	/* verअगरy frame size */
	अगर (count > maxframe) अणु
		pr_debug("%s: truncating user packet from %zu to %d\n",
				__func__, count, maxframe);
		count = maxframe;
	पूर्ण

	add_रुको_queue(&tty->ग_लिखो_रुको, &रुको);

	क्रम (;;) अणु
		set_current_state(TASK_INTERRUPTIBLE);

		tbuf = n_hdlc_buf_get(&n_hdlc->tx_मुक्त_buf_list);
		अगर (tbuf)
			अवरोध;

		अगर (tty_io_nonblock(tty, file)) अणु
			error = -EAGAIN;
			अवरोध;
		पूर्ण
		schedule();

		अगर (संकेत_pending(current)) अणु
			error = -EINTR;
			अवरोध;
		पूर्ण
	पूर्ण

	__set_current_state(TASK_RUNNING);
	हटाओ_रुको_queue(&tty->ग_लिखो_रुको, &रुको);

	अगर (!error) अणु
		/* Retrieve the user's buffer */
		स_नकल(tbuf->buf, data, count);

		/* Send the data */
		tbuf->count = error = count;
		n_hdlc_buf_put(&n_hdlc->tx_buf_list, tbuf);
		n_hdlc_send_frames(n_hdlc, tty);
	पूर्ण

	वापस error;

पूर्ण	/* end of n_hdlc_tty_ग_लिखो() */

/**
 * n_hdlc_tty_ioctl - process IOCTL प्रणाली call क्रम the tty device.
 * @tty: poपूर्णांकer to tty instance data
 * @file: poपूर्णांकer to खोलो file object क्रम device
 * @cmd: IOCTL command code
 * @arg: argument क्रम IOCTL call (cmd dependent)
 *
 * Returns command dependent result.
 */
अटल पूर्णांक n_hdlc_tty_ioctl(काष्ठा tty_काष्ठा *tty, काष्ठा file *file,
			    अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा n_hdlc *n_hdlc = tty->disc_data;
	पूर्णांक error = 0;
	पूर्णांक count;
	अचिन्हित दीर्घ flags;
	काष्ठा n_hdlc_buf *buf = शून्य;

	pr_debug("%s() called %d\n", __func__, cmd);

	/* Verअगरy the status of the device */
	अगर (n_hdlc->magic != HDLC_MAGIC)
		वापस -EBADF;

	चयन (cmd) अणु
	हाल FIONREAD:
		/* report count of पढ़ो data available */
		/* in next available frame (अगर any) */
		spin_lock_irqsave(&n_hdlc->rx_buf_list.spinlock, flags);
		buf = list_first_entry_or_null(&n_hdlc->rx_buf_list.list,
						काष्ठा n_hdlc_buf, list_item);
		अगर (buf)
			count = buf->count;
		अन्यथा
			count = 0;
		spin_unlock_irqrestore(&n_hdlc->rx_buf_list.spinlock, flags);
		error = put_user(count, (पूर्णांक __user *)arg);
		अवरोध;

	हाल TIOCOUTQ:
		/* get the pending tx byte count in the driver */
		count = tty_अक्षरs_in_buffer(tty);
		/* add size of next output frame in queue */
		spin_lock_irqsave(&n_hdlc->tx_buf_list.spinlock, flags);
		buf = list_first_entry_or_null(&n_hdlc->tx_buf_list.list,
						काष्ठा n_hdlc_buf, list_item);
		अगर (buf)
			count += buf->count;
		spin_unlock_irqrestore(&n_hdlc->tx_buf_list.spinlock, flags);
		error = put_user(count, (पूर्णांक __user *)arg);
		अवरोध;

	हाल TCFLSH:
		चयन (arg) अणु
		हाल TCIOFLUSH:
		हाल TCOFLUSH:
			flush_tx_queue(tty);
		पूर्ण
		fallthrough;	/* to शेष */

	शेष:
		error = n_tty_ioctl_helper(tty, file, cmd, arg);
		अवरोध;
	पूर्ण
	वापस error;

पूर्ण	/* end of n_hdlc_tty_ioctl() */

/**
 * n_hdlc_tty_poll - TTY callback क्रम poll प्रणाली call
 * @tty: poपूर्णांकer to tty instance data
 * @filp: poपूर्णांकer to खोलो file object क्रम device
 * @रुको: रुको queue क्रम operations
 *
 * Determine which operations (पढ़ो/ग_लिखो) will not block and वापस info
 * to caller.
 * Returns a bit mask containing info on which ops will not block.
 */
अटल __poll_t n_hdlc_tty_poll(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp,
				    poll_table *रुको)
अणु
	काष्ठा n_hdlc *n_hdlc = tty->disc_data;
	__poll_t mask = 0;

	अगर (n_hdlc->magic != HDLC_MAGIC)
		वापस 0;

	/*
	 * queue the current process पूर्णांकo any रुको queue that may awaken in the
	 * future (पढ़ो and ग_लिखो)
	 */
	poll_रुको(filp, &tty->पढ़ो_रुको, रुको);
	poll_रुको(filp, &tty->ग_लिखो_रुको, रुको);

	/* set bits क्रम operations that won't block */
	अगर (!list_empty(&n_hdlc->rx_buf_list.list))
		mask |= EPOLLIN | EPOLLRDNORM;	/* पढ़ोable */
	अगर (test_bit(TTY_OTHER_CLOSED, &tty->flags))
		mask |= EPOLLHUP;
	अगर (tty_hung_up_p(filp))
		mask |= EPOLLHUP;
	अगर (!tty_is_ग_लिखोlocked(tty) &&
			!list_empty(&n_hdlc->tx_मुक्त_buf_list.list))
		mask |= EPOLLOUT | EPOLLWRNORM;	/* writable */

	वापस mask;
पूर्ण	/* end of n_hdlc_tty_poll() */

अटल व्योम n_hdlc_alloc_buf(काष्ठा n_hdlc_buf_list *list, अचिन्हित पूर्णांक count,
		स्थिर अक्षर *name)
अणु
	काष्ठा n_hdlc_buf *buf;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < count; i++) अणु
		buf = kदो_स्मृति(काष्ठा_size(buf, buf, maxframe), GFP_KERNEL);
		अगर (!buf) अणु
			pr_debug("%s(), kmalloc() failed for %s buffer %u\n",
					__func__, name, i);
			वापस;
		पूर्ण
		n_hdlc_buf_put(list, buf);
	पूर्ण
पूर्ण

/**
 * n_hdlc_alloc - allocate an n_hdlc instance data काष्ठाure
 *
 * Returns a poपूर्णांकer to newly created काष्ठाure अगर success, otherwise %शून्य
 */
अटल काष्ठा n_hdlc *n_hdlc_alloc(व्योम)
अणु
	काष्ठा n_hdlc *n_hdlc = kzalloc(माप(*n_hdlc), GFP_KERNEL);

	अगर (!n_hdlc)
		वापस शून्य;

	spin_lock_init(&n_hdlc->rx_मुक्त_buf_list.spinlock);
	spin_lock_init(&n_hdlc->tx_मुक्त_buf_list.spinlock);
	spin_lock_init(&n_hdlc->rx_buf_list.spinlock);
	spin_lock_init(&n_hdlc->tx_buf_list.spinlock);

	INIT_LIST_HEAD(&n_hdlc->rx_मुक्त_buf_list.list);
	INIT_LIST_HEAD(&n_hdlc->tx_मुक्त_buf_list.list);
	INIT_LIST_HEAD(&n_hdlc->rx_buf_list.list);
	INIT_LIST_HEAD(&n_hdlc->tx_buf_list.list);

	n_hdlc_alloc_buf(&n_hdlc->rx_मुक्त_buf_list, DEFAULT_RX_BUF_COUNT, "rx");
	n_hdlc_alloc_buf(&n_hdlc->tx_मुक्त_buf_list, DEFAULT_TX_BUF_COUNT, "tx");

	/* Initialize the control block */
	n_hdlc->magic  = HDLC_MAGIC;

	वापस n_hdlc;

पूर्ण	/* end of n_hdlc_alloc() */

/**
 * n_hdlc_buf_वापस - put the HDLC buffer after the head of the specअगरied list
 * @buf_list: poपूर्णांकer to the buffer list
 * @buf: poपूर्णांकer to the buffer
 */
अटल व्योम n_hdlc_buf_वापस(काष्ठा n_hdlc_buf_list *buf_list,
						काष्ठा n_hdlc_buf *buf)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&buf_list->spinlock, flags);

	list_add(&buf->list_item, &buf_list->list);
	buf_list->count++;

	spin_unlock_irqrestore(&buf_list->spinlock, flags);
पूर्ण

/**
 * n_hdlc_buf_put - add specअगरied HDLC buffer to tail of specअगरied list
 * @buf_list: poपूर्णांकer to buffer list
 * @buf: poपूर्णांकer to buffer
 */
अटल व्योम n_hdlc_buf_put(काष्ठा n_hdlc_buf_list *buf_list,
			   काष्ठा n_hdlc_buf *buf)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&buf_list->spinlock, flags);

	list_add_tail(&buf->list_item, &buf_list->list);
	buf_list->count++;

	spin_unlock_irqrestore(&buf_list->spinlock, flags);
पूर्ण	/* end of n_hdlc_buf_put() */

/**
 * n_hdlc_buf_get - हटाओ and वापस an HDLC buffer from list
 * @buf_list: poपूर्णांकer to HDLC buffer list
 *
 * Remove and वापस an HDLC buffer from the head of the specअगरied HDLC buffer
 * list.
 * Returns a poपूर्णांकer to HDLC buffer अगर available, otherwise %शून्य.
 */
अटल काष्ठा n_hdlc_buf *n_hdlc_buf_get(काष्ठा n_hdlc_buf_list *buf_list)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा n_hdlc_buf *buf;

	spin_lock_irqsave(&buf_list->spinlock, flags);

	buf = list_first_entry_or_null(&buf_list->list,
						काष्ठा n_hdlc_buf, list_item);
	अगर (buf) अणु
		list_del(&buf->list_item);
		buf_list->count--;
	पूर्ण

	spin_unlock_irqrestore(&buf_list->spinlock, flags);
	वापस buf;
पूर्ण	/* end of n_hdlc_buf_get() */

अटल काष्ठा tty_ldisc_ops n_hdlc_ldisc = अणु
	.owner		= THIS_MODULE,
	.name		= "hdlc",
	.खोलो		= n_hdlc_tty_खोलो,
	.बंद		= n_hdlc_tty_बंद,
	.पढ़ो		= n_hdlc_tty_पढ़ो,
	.ग_लिखो		= n_hdlc_tty_ग_लिखो,
	.ioctl		= n_hdlc_tty_ioctl,
	.poll		= n_hdlc_tty_poll,
	.receive_buf	= n_hdlc_tty_receive,
	.ग_लिखो_wakeup	= n_hdlc_tty_wakeup,
	.flush_buffer   = flush_rx_queue,
पूर्ण;

अटल पूर्णांक __init n_hdlc_init(व्योम)
अणु
	पूर्णांक status;

	/* range check maxframe arg */
	maxframe = clamp(maxframe, 4096, MAX_HDLC_FRAME_SIZE);

	status = tty_रेजिस्टर_ldisc(N_HDLC, &n_hdlc_ldisc);
	अगर (!status)
		pr_info("N_HDLC line discipline registered with maxframe=%d\n",
				maxframe);
	अन्यथा
		pr_err("N_HDLC: error registering line discipline: %d\n",
				status);

	वापस status;

पूर्ण	/* end of init_module() */

अटल व्योम __निकास n_hdlc_निकास(व्योम)
अणु
	/* Release tty registration of line discipline */
	पूर्णांक status = tty_unरेजिस्टर_ldisc(N_HDLC);

	अगर (status)
		pr_err("N_HDLC: can't unregister line discipline (err = %d)\n",
				status);
	अन्यथा
		pr_info("N_HDLC: line discipline unregistered\n");
पूर्ण

module_init(n_hdlc_init);
module_निकास(n_hdlc_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Paul Fulghum paulkf@microgate.com");
module_param(maxframe, पूर्णांक, 0);
MODULE_ALIAS_LDISC(N_HDLC);
