<शैली गुरु>
// SPDX-License-Identअगरier: GPL-1.0+
/* r3964 linediscipline क्रम linux
 *
 * -----------------------------------------------------------
 * Copyright by 
 * Philips Automation Projects
 * Kassel (Germany)
 * -----------------------------------------------------------
 * Author:
 * L. Haag
 *
 * $Log: n_r3964.c,v $
 * Revision 1.10  2001/03/18 13:02:24  dwmw2
 * Fix समयr usage, use spinlocks properly.
 *
 * Revision 1.9  2001/03/18 12:52:14  dwmw2
 * Merge changes in 2.4.2
 *
 * Revision 1.8  2000/03/23 14:14:54  dwmw2
 * Fix race in sleeping in r3964_पढ़ो()
 *
 * Revision 1.7  1999/28/08 11:41:50  dwmw2
 * Port to 2.3 kernel
 *
 * Revision 1.6  1998/09/30 00:40:40  dwmw2
 * Fixed compilation on 2.0.x kernels
 * Updated to newly रेजिस्टरed tty-ldisc number 9
 *
 * Revision 1.5  1998/09/04 21:57:36  dwmw2
 * Signal handling bug fixes, port to 2.1.x.
 *
 * Revision 1.4  1998/04/02 20:26:59  lhaag
 * select, blocking, ...
 *
 * Revision 1.3  1998/02/12 18:58:43  root
 * fixed some memory leaks
 * calculation of checksum अक्षरacters
 *
 * Revision 1.2  1998/02/07 13:03:34  root
 * ioctl पढ़ो_telegram
 *
 * Revision 1.1  1998/02/06 19:21:03  root
 * Initial revision
 *
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/types.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/ioport.h>
#समावेश <linux/in.h>
#समावेश <linux/slab.h>
#समावेश <linux/tty.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>	/* used in new tty drivers */
#समावेश <linux/संकेत.स>	/* used in new tty drivers */
#समावेश <linux/ioctl.h>
#समावेश <linux/n_r3964.h>
#समावेश <linux/poll.h>
#समावेश <linux/init.h>
#समावेश <linux/uaccess.h>

/*#घोषणा DEBUG_QUEUE*/

/* Log successful handshake and protocol operations  */
/*#घोषणा DEBUG_PROTO_S*/

/* Log handshake and protocol errors: */
/*#घोषणा DEBUG_PROTO_E*/

/* Log Linediscipline operations (खोलो, बंद, पढ़ो, ग_लिखो...): */
/*#घोषणा DEBUG_LDISC*/

/* Log module and memory operations (init, cleanup; kदो_स्मृति, kमुक्त): */
/*#घोषणा DEBUG_MODUL*/

/* Macro helpers क्रम debug output: */
#घोषणा TRACE(क्रमmat, args...) prपूर्णांकk("r3964: " क्रमmat "\n" , ## args)

#अगर_घोषित DEBUG_MODUL
#घोषणा TRACE_M(क्रमmat, args...) prपूर्णांकk("r3964: " क्रमmat "\n" , ## args)
#अन्यथा
#घोषणा TRACE_M(fmt, arg...) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर
#अगर_घोषित DEBUG_PROTO_S
#घोषणा TRACE_PS(क्रमmat, args...) prपूर्णांकk("r3964: " क्रमmat "\n" , ## args)
#अन्यथा
#घोषणा TRACE_PS(fmt, arg...) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर
#अगर_घोषित DEBUG_PROTO_E
#घोषणा TRACE_PE(क्रमmat, args...) prपूर्णांकk("r3964: " क्रमmat "\n" , ## args)
#अन्यथा
#घोषणा TRACE_PE(fmt, arg...) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर
#अगर_घोषित DEBUG_LDISC
#घोषणा TRACE_L(क्रमmat, args...) prपूर्णांकk("r3964: " क्रमmat "\n" , ## args)
#अन्यथा
#घोषणा TRACE_L(fmt, arg...) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर
#अगर_घोषित DEBUG_QUEUE
#घोषणा TRACE_Q(क्रमmat, args...) prपूर्णांकk("r3964: " क्रमmat "\n" , ## args)
#अन्यथा
#घोषणा TRACE_Q(fmt, arg...) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर
अटल व्योम add_tx_queue(काष्ठा r3964_info *, काष्ठा r3964_block_header *);
अटल व्योम हटाओ_from_tx_queue(काष्ठा r3964_info *pInfo, पूर्णांक error_code);
अटल व्योम put_अक्षर(काष्ठा r3964_info *pInfo, अचिन्हित अक्षर ch);
अटल व्योम trigger_transmit(काष्ठा r3964_info *pInfo);
अटल व्योम retry_transmit(काष्ठा r3964_info *pInfo);
अटल व्योम transmit_block(काष्ठा r3964_info *pInfo);
अटल व्योम receive_अक्षर(काष्ठा r3964_info *pInfo, स्थिर अचिन्हित अक्षर c);
अटल व्योम receive_error(काष्ठा r3964_info *pInfo, स्थिर अक्षर flag);
अटल व्योम on_समयout(काष्ठा समयr_list *t);
अटल पूर्णांक enable_संकेतs(काष्ठा r3964_info *pInfo, काष्ठा pid *pid, पूर्णांक arg);
अटल पूर्णांक पढ़ो_telegram(काष्ठा r3964_info *pInfo, काष्ठा pid *pid,
		अचिन्हित अक्षर __user * buf);
अटल व्योम add_msg(काष्ठा r3964_client_info *pClient, पूर्णांक msg_id, पूर्णांक arg,
		पूर्णांक error_code, काष्ठा r3964_block_header *pBlock);
अटल काष्ठा r3964_message *हटाओ_msg(काष्ठा r3964_info *pInfo,
		काष्ठा r3964_client_info *pClient);
अटल व्योम हटाओ_client_block(काष्ठा r3964_info *pInfo,
		काष्ठा r3964_client_info *pClient);

अटल पूर्णांक r3964_खोलो(काष्ठा tty_काष्ठा *tty);
अटल व्योम r3964_बंद(काष्ठा tty_काष्ठा *tty);
अटल sमाप_प्रकार r3964_पढ़ो(काष्ठा tty_काष्ठा *tty, काष्ठा file *file,
		व्योम *cookie, अचिन्हित अक्षर *buf, माप_प्रकार nr);
अटल sमाप_प्रकार r3964_ग_लिखो(काष्ठा tty_काष्ठा *tty, काष्ठा file *file,
		स्थिर अचिन्हित अक्षर *buf, माप_प्रकार nr);
अटल पूर्णांक r3964_ioctl(काष्ठा tty_काष्ठा *tty, काष्ठा file *file,
		अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
#अगर_घोषित CONFIG_COMPAT
अटल पूर्णांक r3964_compat_ioctl(काष्ठा tty_काष्ठा *tty, काष्ठा file *file,
		अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
#पूर्ण_अगर
अटल व्योम r3964_set_termios(काष्ठा tty_काष्ठा *tty, काष्ठा ktermios *old);
अटल __poll_t r3964_poll(काष्ठा tty_काष्ठा *tty, काष्ठा file *file,
		काष्ठा poll_table_काष्ठा *रुको);
अटल व्योम r3964_receive_buf(काष्ठा tty_काष्ठा *tty, स्थिर अचिन्हित अक्षर *cp,
		अक्षर *fp, पूर्णांक count);

अटल काष्ठा tty_ldisc_ops tty_ldisc_N_R3964 = अणु
	.owner = THIS_MODULE,
	.name = "R3964",
	.खोलो = r3964_खोलो,
	.बंद = r3964_बंद,
	.पढ़ो = r3964_पढ़ो,
	.ग_लिखो = r3964_ग_लिखो,
	.ioctl = r3964_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl = r3964_compat_ioctl,
#पूर्ण_अगर
	.set_termios = r3964_set_termios,
	.poll = r3964_poll,
	.receive_buf = r3964_receive_buf,
पूर्ण;

अटल व्योम dump_block(स्थिर अचिन्हित अक्षर *block, अचिन्हित पूर्णांक length)
अणु
	अचिन्हित पूर्णांक i, j;
	अक्षर linebuf[16 * 3 + 1];

	क्रम (i = 0; i < length; i += 16) अणु
		क्रम (j = 0; (j < 16) && (j + i < length); j++) अणु
			प्र_लिखो(linebuf + 3 * j, "%02x ", block[i + j]);
		पूर्ण
		linebuf[3 * j] = '\0';
		TRACE_PS("%s", linebuf);
	पूर्ण
पूर्ण

/*************************************************************
 * Driver initialisation
 *************************************************************/

/*************************************************************
 * Module support routines
 *************************************************************/

अटल व्योम __निकास r3964_निकास(व्योम)
अणु
	पूर्णांक status;

	TRACE_M("cleanup_module()");

	status = tty_unरेजिस्टर_ldisc(N_R3964);

	अगर (status != 0) अणु
		prपूर्णांकk(KERN_ERR "r3964: error unregistering linediscipline: "
				"%d\n", status);
	पूर्ण अन्यथा अणु
		TRACE_L("linediscipline successfully unregistered");
	पूर्ण
पूर्ण

अटल पूर्णांक __init r3964_init(व्योम)
अणु
	पूर्णांक status;

	prपूर्णांकk("r3964: Philips r3964 Driver $Revision: 1.10 $\n");

	/*
	 * Register the tty line discipline
	 */

	status = tty_रेजिस्टर_ldisc(N_R3964, &tty_ldisc_N_R3964);
	अगर (status == 0) अणु
		TRACE_L("line discipline %d registered", N_R3964);
		TRACE_L("flags=%x num=%x", tty_ldisc_N_R3964.flags,
			tty_ldisc_N_R3964.num);
		TRACE_L("open=%p", tty_ldisc_N_R3964.खोलो);
		TRACE_L("tty_ldisc_N_R3964 = %p", &tty_ldisc_N_R3964);
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "r3964: error registering line discipline: "
				"%d\n", status);
	पूर्ण
	वापस status;
पूर्ण

module_init(r3964_init);
module_निकास(r3964_निकास);

/*************************************************************
 * Protocol implementation routines
 *************************************************************/

अटल व्योम add_tx_queue(काष्ठा r3964_info *pInfo,
			 काष्ठा r3964_block_header *pHeader)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pInfo->lock, flags);

	pHeader->next = शून्य;

	अगर (pInfo->tx_last == शून्य) अणु
		pInfo->tx_first = pInfo->tx_last = pHeader;
	पूर्ण अन्यथा अणु
		pInfo->tx_last->next = pHeader;
		pInfo->tx_last = pHeader;
	पूर्ण

	spin_unlock_irqrestore(&pInfo->lock, flags);

	TRACE_Q("add_tx_queue %p, length %d, tx_first = %p",
		pHeader, pHeader->length, pInfo->tx_first);
पूर्ण

अटल व्योम हटाओ_from_tx_queue(काष्ठा r3964_info *pInfo, पूर्णांक error_code)
अणु
	काष्ठा r3964_block_header *pHeader;
	अचिन्हित दीर्घ flags;
#अगर_घोषित DEBUG_QUEUE
	काष्ठा r3964_block_header *pDump;
#पूर्ण_अगर

	pHeader = pInfo->tx_first;

	अगर (pHeader == शून्य)
		वापस;

#अगर_घोषित DEBUG_QUEUE
	prपूर्णांकk("r3964: remove_from_tx_queue: %p, length %u - ",
		pHeader, pHeader->length);
	क्रम (pDump = pHeader; pDump; pDump = pDump->next)
		prपूर्णांकk("%p ", pDump);
	prपूर्णांकk("\n");
#पूर्ण_अगर

	अगर (pHeader->owner) अणु
		अगर (error_code) अणु
			add_msg(pHeader->owner, R3964_MSG_ACK, 0,
				error_code, शून्य);
		पूर्ण अन्यथा अणु
			add_msg(pHeader->owner, R3964_MSG_ACK, pHeader->length,
				error_code, शून्य);
		पूर्ण
		wake_up_पूर्णांकerruptible(&pInfo->tty->पढ़ो_रुको);
	पूर्ण

	spin_lock_irqsave(&pInfo->lock, flags);

	pInfo->tx_first = pHeader->next;
	अगर (pInfo->tx_first == शून्य) अणु
		pInfo->tx_last = शून्य;
	पूर्ण

	spin_unlock_irqrestore(&pInfo->lock, flags);

	kमुक्त(pHeader);
	TRACE_M("remove_from_tx_queue - kfree %p", pHeader);

	TRACE_Q("remove_from_tx_queue: tx_first = %p, tx_last = %p",
		pInfo->tx_first, pInfo->tx_last);
पूर्ण

अटल व्योम add_rx_queue(काष्ठा r3964_info *pInfo,
			 काष्ठा r3964_block_header *pHeader)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pInfo->lock, flags);

	pHeader->next = शून्य;

	अगर (pInfo->rx_last == शून्य) अणु
		pInfo->rx_first = pInfo->rx_last = pHeader;
	पूर्ण अन्यथा अणु
		pInfo->rx_last->next = pHeader;
		pInfo->rx_last = pHeader;
	पूर्ण
	pInfo->blocks_in_rx_queue++;

	spin_unlock_irqrestore(&pInfo->lock, flags);

	TRACE_Q("add_rx_queue: %p, length = %d, rx_first = %p, count = %d",
		pHeader, pHeader->length,
		pInfo->rx_first, pInfo->blocks_in_rx_queue);
पूर्ण

अटल व्योम हटाओ_from_rx_queue(काष्ठा r3964_info *pInfo,
				 काष्ठा r3964_block_header *pHeader)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा r3964_block_header *pFind;

	अगर (pHeader == शून्य)
		वापस;

	TRACE_Q("remove_from_rx_queue: rx_first = %p, rx_last = %p, count = %d",
		pInfo->rx_first, pInfo->rx_last, pInfo->blocks_in_rx_queue);
	TRACE_Q("remove_from_rx_queue: %p, length %u",
		pHeader, pHeader->length);

	spin_lock_irqsave(&pInfo->lock, flags);

	अगर (pInfo->rx_first == pHeader) अणु
		/* Remove the first block in the linked list: */
		pInfo->rx_first = pHeader->next;

		अगर (pInfo->rx_first == शून्य) अणु
			pInfo->rx_last = शून्य;
		पूर्ण
		pInfo->blocks_in_rx_queue--;
	पूर्ण अन्यथा अणु
		/* Find block to हटाओ: */
		क्रम (pFind = pInfo->rx_first; pFind; pFind = pFind->next) अणु
			अगर (pFind->next == pHeader) अणु
				/* Got it. */
				pFind->next = pHeader->next;
				pInfo->blocks_in_rx_queue--;
				अगर (pFind->next == शून्य) अणु
					/* Oh, हटाओd the last one! */
					pInfo->rx_last = pFind;
				पूर्ण
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&pInfo->lock, flags);

	kमुक्त(pHeader);
	TRACE_M("remove_from_rx_queue - kfree %p", pHeader);

	TRACE_Q("remove_from_rx_queue: rx_first = %p, rx_last = %p, count = %d",
		pInfo->rx_first, pInfo->rx_last, pInfo->blocks_in_rx_queue);
पूर्ण

अटल व्योम put_अक्षर(काष्ठा r3964_info *pInfo, अचिन्हित अक्षर ch)
अणु
	काष्ठा tty_काष्ठा *tty = pInfo->tty;
	/* FIXME: put_अक्षर should not be called from an IRQ */
	tty_put_अक्षर(tty, ch);
	pInfo->bcc ^= ch;
पूर्ण

अटल व्योम flush(काष्ठा r3964_info *pInfo)
अणु
	काष्ठा tty_काष्ठा *tty = pInfo->tty;

	अगर (tty == शून्य || tty->ops->flush_अक्षरs == शून्य)
		वापस;
	tty->ops->flush_अक्षरs(tty);
पूर्ण

अटल व्योम trigger_transmit(काष्ठा r3964_info *pInfo)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pInfo->lock, flags);

	अगर ((pInfo->state == R3964_IDLE) && (pInfo->tx_first != शून्य)) अणु
		pInfo->state = R3964_TX_REQUEST;
		pInfo->nRetry = 0;
		pInfo->flags &= ~R3964_ERROR;
		mod_समयr(&pInfo->पंचांगr, jअगरfies + R3964_TO_QVZ);

		spin_unlock_irqrestore(&pInfo->lock, flags);

		TRACE_PS("trigger_transmit - sent STX");

		put_अक्षर(pInfo, STX);
		flush(pInfo);

		pInfo->bcc = 0;
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&pInfo->lock, flags);
	पूर्ण
पूर्ण

अटल व्योम retry_transmit(काष्ठा r3964_info *pInfo)
अणु
	अगर (pInfo->nRetry < R3964_MAX_RETRIES) अणु
		TRACE_PE("transmission failed. Retry #%d", pInfo->nRetry);
		pInfo->bcc = 0;
		put_अक्षर(pInfo, STX);
		flush(pInfo);
		pInfo->state = R3964_TX_REQUEST;
		pInfo->nRetry++;
		mod_समयr(&pInfo->पंचांगr, jअगरfies + R3964_TO_QVZ);
	पूर्ण अन्यथा अणु
		TRACE_PE("transmission failed after %d retries",
			 R3964_MAX_RETRIES);

		हटाओ_from_tx_queue(pInfo, R3964_TX_FAIL);

		put_अक्षर(pInfo, NAK);
		flush(pInfo);
		pInfo->state = R3964_IDLE;

		trigger_transmit(pInfo);
	पूर्ण
पूर्ण

अटल व्योम transmit_block(काष्ठा r3964_info *pInfo)
अणु
	काष्ठा tty_काष्ठा *tty = pInfo->tty;
	काष्ठा r3964_block_header *pBlock = pInfo->tx_first;
	पूर्णांक room = 0;

	अगर (tty == शून्य || pBlock == शून्य) अणु
		वापस;
	पूर्ण

	room = tty_ग_लिखो_room(tty);

	TRACE_PS("transmit_block %p, room %d, length %d",
		 pBlock, room, pBlock->length);

	जबतक (pInfo->tx_position < pBlock->length) अणु
		अगर (room < 2)
			अवरोध;

		अगर (pBlock->data[pInfo->tx_position] == DLE) अणु
			/* send additional DLE अक्षर: */
			put_अक्षर(pInfo, DLE);
		पूर्ण
		put_अक्षर(pInfo, pBlock->data[pInfo->tx_position++]);

		room--;
	पूर्ण

	अगर ((pInfo->tx_position == pBlock->length) && (room >= 3)) अणु
		put_अक्षर(pInfo, DLE);
		put_अक्षर(pInfo, ETX);
		अगर (pInfo->flags & R3964_BCC) अणु
			put_अक्षर(pInfo, pInfo->bcc);
		पूर्ण
		pInfo->state = R3964_WAIT_FOR_TX_ACK;
		mod_समयr(&pInfo->पंचांगr, jअगरfies + R3964_TO_QVZ);
	पूर्ण
	flush(pInfo);
पूर्ण

अटल व्योम on_receive_block(काष्ठा r3964_info *pInfo)
अणु
	अचिन्हित पूर्णांक length;
	काष्ठा r3964_client_info *pClient;
	काष्ठा r3964_block_header *pBlock;

	length = pInfo->rx_position;

	/* compare byte checksum अक्षरacters: */
	अगर (pInfo->flags & R3964_BCC) अणु
		अगर (pInfo->bcc != pInfo->last_rx) अणु
			TRACE_PE("checksum error - got %x but expected %x",
				 pInfo->last_rx, pInfo->bcc);
			pInfo->flags |= R3964_CHECKSUM;
		पूर्ण
	पूर्ण

	/* check क्रम errors (parity, overrun,...): */
	अगर (pInfo->flags & R3964_ERROR) अणु
		TRACE_PE("on_receive_block - transmission failed error %x",
			 pInfo->flags & R3964_ERROR);

		put_अक्षर(pInfo, NAK);
		flush(pInfo);
		अगर (pInfo->nRetry < R3964_MAX_RETRIES) अणु
			pInfo->state = R3964_WAIT_FOR_RX_REPEAT;
			pInfo->nRetry++;
			mod_समयr(&pInfo->पंचांगr, jअगरfies + R3964_TO_RX_PANIC);
		पूर्ण अन्यथा अणु
			TRACE_PE("on_receive_block - failed after max retries");
			pInfo->state = R3964_IDLE;
		पूर्ण
		वापस;
	पूर्ण

	/* received block; submit DLE: */
	put_अक्षर(pInfo, DLE);
	flush(pInfo);
	del_समयr_sync(&pInfo->पंचांगr);
	TRACE_PS(" rx success: got %d chars", length);

	/* prepare काष्ठा r3964_block_header: */
	pBlock = kदो_स्मृति(length + माप(काष्ठा r3964_block_header),
			GFP_KERNEL);
	TRACE_M("on_receive_block - kmalloc %p", pBlock);

	अगर (pBlock == शून्य)
		वापस;

	pBlock->length = length;
	pBlock->data = ((अचिन्हित अक्षर *)pBlock) +
			माप(काष्ठा r3964_block_header);
	pBlock->locks = 0;
	pBlock->next = शून्य;
	pBlock->owner = शून्य;

	स_नकल(pBlock->data, pInfo->rx_buf, length);

	/* queue block पूर्णांकo rx_queue: */
	add_rx_queue(pInfo, pBlock);

	/* notअगरy attached client processes: */
	क्रम (pClient = pInfo->firstClient; pClient; pClient = pClient->next) अणु
		अगर (pClient->sig_flags & R3964_SIG_DATA) अणु
			add_msg(pClient, R3964_MSG_DATA, length, R3964_OK,
				pBlock);
		पूर्ण
	पूर्ण
	wake_up_पूर्णांकerruptible(&pInfo->tty->पढ़ो_रुको);

	pInfo->state = R3964_IDLE;

	trigger_transmit(pInfo);
पूर्ण

अटल व्योम receive_अक्षर(काष्ठा r3964_info *pInfo, स्थिर अचिन्हित अक्षर c)
अणु
	चयन (pInfo->state) अणु
	हाल R3964_TX_REQUEST:
		अगर (c == DLE) अणु
			TRACE_PS("TX_REQUEST - got DLE");

			pInfo->state = R3964_TRANSMITTING;
			pInfo->tx_position = 0;

			transmit_block(pInfo);
		पूर्ण अन्यथा अगर (c == STX) अणु
			अगर (pInfo->nRetry == 0) अणु
				TRACE_PE("TX_REQUEST - init conflict");
				अगर (pInfo->priority == R3964_SLAVE) अणु
					जाओ start_receiving;
				पूर्ण
			पूर्ण अन्यथा अणु
				TRACE_PE("TX_REQUEST - secondary init "
					"conflict!? Switching to SLAVE mode "
					"for next rx.");
				जाओ start_receiving;
			पूर्ण
		पूर्ण अन्यथा अणु
			TRACE_PE("TX_REQUEST - char != DLE: %x", c);
			retry_transmit(pInfo);
		पूर्ण
		अवरोध;
	हाल R3964_TRANSMITTING:
		अगर (c == NAK) अणु
			TRACE_PE("TRANSMITTING - got NAK");
			retry_transmit(pInfo);
		पूर्ण अन्यथा अणु
			TRACE_PE("TRANSMITTING - got invalid char");

			pInfo->state = R3964_WAIT_ZVZ_BEFORE_TX_RETRY;
			mod_समयr(&pInfo->पंचांगr, jअगरfies + R3964_TO_ZVZ);
		पूर्ण
		अवरोध;
	हाल R3964_WAIT_FOR_TX_ACK:
		अगर (c == DLE) अणु
			TRACE_PS("WAIT_FOR_TX_ACK - got DLE");
			हटाओ_from_tx_queue(pInfo, R3964_OK);

			pInfo->state = R3964_IDLE;
			trigger_transmit(pInfo);
		पूर्ण अन्यथा अणु
			retry_transmit(pInfo);
		पूर्ण
		अवरोध;
	हाल R3964_WAIT_FOR_RX_REPEAT:
	हाल R3964_IDLE:
		अगर (c == STX) अणु
			/* Prevent rx_queue from overflow: */
			अगर (pInfo->blocks_in_rx_queue >=
			    R3964_MAX_BLOCKS_IN_RX_QUEUE) अणु
				TRACE_PE("IDLE - got STX but no space in "
						"rx_queue!");
				pInfo->state = R3964_WAIT_FOR_RX_BUF;
				mod_समयr(&pInfo->पंचांगr,
					  jअगरfies + R3964_TO_NO_BUF);
				अवरोध;
			पूर्ण
start_receiving:
			/* Ok, start receiving: */
			TRACE_PS("IDLE - got STX");
			pInfo->rx_position = 0;
			pInfo->last_rx = 0;
			pInfo->flags &= ~R3964_ERROR;
			pInfo->state = R3964_RECEIVING;
			mod_समयr(&pInfo->पंचांगr, jअगरfies + R3964_TO_ZVZ);
			pInfo->nRetry = 0;
			put_अक्षर(pInfo, DLE);
			flush(pInfo);
			pInfo->bcc = 0;
		पूर्ण
		अवरोध;
	हाल R3964_RECEIVING:
		अगर (pInfo->rx_position < RX_BUF_SIZE) अणु
			pInfo->bcc ^= c;

			अगर (c == DLE) अणु
				अगर (pInfo->last_rx == DLE) अणु
					pInfo->last_rx = 0;
					जाओ अक्षर_to_buf;
				पूर्ण
				pInfo->last_rx = DLE;
				अवरोध;
			पूर्ण अन्यथा अगर ((c == ETX) && (pInfo->last_rx == DLE)) अणु
				अगर (pInfo->flags & R3964_BCC) अणु
					pInfo->state = R3964_WAIT_FOR_BCC;
					mod_समयr(&pInfo->पंचांगr,
						  jअगरfies + R3964_TO_ZVZ);
				पूर्ण अन्यथा अणु
					on_receive_block(pInfo);
				पूर्ण
			पूर्ण अन्यथा अणु
				pInfo->last_rx = c;
अक्षर_to_buf:
				pInfo->rx_buf[pInfo->rx_position++] = c;
				mod_समयr(&pInfo->पंचांगr, jअगरfies + R3964_TO_ZVZ);
			पूर्ण
		पूर्ण
		/* अन्यथा: overflow-msg? BUF_SIZE>MTU; should not happen? */
		अवरोध;
	हाल R3964_WAIT_FOR_BCC:
		pInfo->last_rx = c;
		on_receive_block(pInfo);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम receive_error(काष्ठा r3964_info *pInfo, स्थिर अक्षर flag)
अणु
	चयन (flag) अणु
	हाल TTY_NORMAL:
		अवरोध;
	हाल TTY_BREAK:
		TRACE_PE("received break");
		pInfo->flags |= R3964_BREAK;
		अवरोध;
	हाल TTY_PARITY:
		TRACE_PE("parity error");
		pInfo->flags |= R3964_PARITY;
		अवरोध;
	हाल TTY_FRAME:
		TRACE_PE("frame error");
		pInfo->flags |= R3964_FRAME;
		अवरोध;
	हाल TTY_OVERRUN:
		TRACE_PE("frame overrun");
		pInfo->flags |= R3964_OVERRUN;
		अवरोध;
	शेष:
		TRACE_PE("receive_error - unknown flag %d", flag);
		pInfo->flags |= R3964_UNKNOWN;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम on_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा r3964_info *pInfo = from_समयr(pInfo, t, पंचांगr);

	चयन (pInfo->state) अणु
	हाल R3964_TX_REQUEST:
		TRACE_PE("TX_REQUEST - timeout");
		retry_transmit(pInfo);
		अवरोध;
	हाल R3964_WAIT_ZVZ_BEFORE_TX_RETRY:
		put_अक्षर(pInfo, NAK);
		flush(pInfo);
		retry_transmit(pInfo);
		अवरोध;
	हाल R3964_WAIT_FOR_TX_ACK:
		TRACE_PE("WAIT_FOR_TX_ACK - timeout");
		retry_transmit(pInfo);
		अवरोध;
	हाल R3964_WAIT_FOR_RX_BUF:
		TRACE_PE("WAIT_FOR_RX_BUF - timeout");
		put_अक्षर(pInfo, NAK);
		flush(pInfo);
		pInfo->state = R3964_IDLE;
		अवरोध;
	हाल R3964_RECEIVING:
		TRACE_PE("RECEIVING - timeout after %d chars",
			 pInfo->rx_position);
		put_अक्षर(pInfo, NAK);
		flush(pInfo);
		pInfo->state = R3964_IDLE;
		अवरोध;
	हाल R3964_WAIT_FOR_RX_REPEAT:
		TRACE_PE("WAIT_FOR_RX_REPEAT - timeout");
		pInfo->state = R3964_IDLE;
		अवरोध;
	हाल R3964_WAIT_FOR_BCC:
		TRACE_PE("WAIT_FOR_BCC - timeout");
		put_अक्षर(pInfo, NAK);
		flush(pInfo);
		pInfo->state = R3964_IDLE;
		अवरोध;
	पूर्ण
पूर्ण

अटल काष्ठा r3964_client_info *findClient(काष्ठा r3964_info *pInfo,
		काष्ठा pid *pid)
अणु
	काष्ठा r3964_client_info *pClient;

	क्रम (pClient = pInfo->firstClient; pClient; pClient = pClient->next) अणु
		अगर (pClient->pid == pid) अणु
			वापस pClient;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक enable_संकेतs(काष्ठा r3964_info *pInfo, काष्ठा pid *pid, पूर्णांक arg)
अणु
	काष्ठा r3964_client_info *pClient;
	काष्ठा r3964_client_info **ppClient;
	काष्ठा r3964_message *pMsg;

	अगर ((arg & R3964_SIG_ALL) == 0) अणु
		/* Remove client from client list */
		क्रम (ppClient = &pInfo->firstClient; *ppClient;
		     ppClient = &(*ppClient)->next) अणु
			pClient = *ppClient;

			अगर (pClient->pid == pid) अणु
				TRACE_PS("removing client %d from client list",
					 pid_nr(pid));
				*ppClient = pClient->next;
				जबतक (pClient->msg_count) अणु
					pMsg = हटाओ_msg(pInfo, pClient);
					अगर (pMsg) अणु
						kमुक्त(pMsg);
						TRACE_M("enable_signals - msg "
							"kfree %p", pMsg);
					पूर्ण
				पूर्ण
				put_pid(pClient->pid);
				kमुक्त(pClient);
				TRACE_M("enable_signals - kfree %p", pClient);
				वापस 0;
			पूर्ण
		पूर्ण
		वापस -EINVAL;
	पूर्ण अन्यथा अणु
		pClient = findClient(pInfo, pid);
		अगर (pClient) अणु
			/* update संकेत options */
			pClient->sig_flags = arg;
		पूर्ण अन्यथा अणु
			/* add client to client list */
			pClient = kदो_स्मृति(माप(काष्ठा r3964_client_info),
					GFP_KERNEL);
			TRACE_M("enable_signals - kmalloc %p", pClient);
			अगर (pClient == शून्य)
				वापस -ENOMEM;

			TRACE_PS("add client %d to client list", pid_nr(pid));
			spin_lock_init(&pClient->lock);
			pClient->sig_flags = arg;
			pClient->pid = get_pid(pid);
			pClient->next = pInfo->firstClient;
			pClient->first_msg = शून्य;
			pClient->last_msg = शून्य;
			pClient->next_block_to_पढ़ो = शून्य;
			pClient->msg_count = 0;
			pInfo->firstClient = pClient;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_telegram(काष्ठा r3964_info *pInfo, काष्ठा pid *pid,
			 अचिन्हित अक्षर __user * buf)
अणु
	काष्ठा r3964_client_info *pClient;
	काष्ठा r3964_block_header *block;

	अगर (!buf) अणु
		वापस -EINVAL;
	पूर्ण

	pClient = findClient(pInfo, pid);
	अगर (pClient == शून्य) अणु
		वापस -EINVAL;
	पूर्ण

	block = pClient->next_block_to_पढ़ो;
	अगर (!block) अणु
		वापस 0;
	पूर्ण अन्यथा अणु
		अगर (copy_to_user(buf, block->data, block->length))
			वापस -EFAULT;

		हटाओ_client_block(pInfo, pClient);
		वापस block->length;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल व्योम add_msg(काष्ठा r3964_client_info *pClient, पूर्णांक msg_id, पूर्णांक arg,
		पूर्णांक error_code, काष्ठा r3964_block_header *pBlock)
अणु
	काष्ठा r3964_message *pMsg;
	अचिन्हित दीर्घ flags;

	अगर (pClient->msg_count < R3964_MAX_MSG_COUNT - 1) अणु
queue_the_message:

		pMsg = kदो_स्मृति(माप(काष्ठा r3964_message),
				error_code ? GFP_ATOMIC : GFP_KERNEL);
		TRACE_M("add_msg - kmalloc %p", pMsg);
		अगर (pMsg == शून्य) अणु
			वापस;
		पूर्ण

		spin_lock_irqsave(&pClient->lock, flags);

		pMsg->msg_id = msg_id;
		pMsg->arg = arg;
		pMsg->error_code = error_code;
		pMsg->block = pBlock;
		pMsg->next = शून्य;

		अगर (pClient->last_msg == शून्य) अणु
			pClient->first_msg = pClient->last_msg = pMsg;
		पूर्ण अन्यथा अणु
			pClient->last_msg->next = pMsg;
			pClient->last_msg = pMsg;
		पूर्ण

		pClient->msg_count++;

		अगर (pBlock != शून्य) अणु
			pBlock->locks++;
		पूर्ण
		spin_unlock_irqrestore(&pClient->lock, flags);
	पूर्ण अन्यथा अणु
		अगर ((pClient->last_msg->msg_id == R3964_MSG_ACK)
		    && (pClient->last_msg->error_code == R3964_OVERFLOW)) अणु
			pClient->last_msg->arg++;
			TRACE_PE("add_msg - inc prev OVERFLOW-msg");
		पूर्ण अन्यथा अणु
			msg_id = R3964_MSG_ACK;
			arg = 0;
			error_code = R3964_OVERFLOW;
			pBlock = शून्य;
			TRACE_PE("add_msg - queue OVERFLOW-msg");
			जाओ queue_the_message;
		पूर्ण
	पूर्ण
	/* Send SIGIO संकेत to client process: */
	अगर (pClient->sig_flags & R3964_USE_SIGIO) अणु
		समाप्त_pid(pClient->pid, SIGIO, 1);
	पूर्ण
पूर्ण

अटल काष्ठा r3964_message *हटाओ_msg(काष्ठा r3964_info *pInfo,
					काष्ठा r3964_client_info *pClient)
अणु
	काष्ठा r3964_message *pMsg = शून्य;
	अचिन्हित दीर्घ flags;

	अगर (pClient->first_msg) अणु
		spin_lock_irqsave(&pClient->lock, flags);

		pMsg = pClient->first_msg;
		pClient->first_msg = pMsg->next;
		अगर (pClient->first_msg == शून्य) अणु
			pClient->last_msg = शून्य;
		पूर्ण

		pClient->msg_count--;
		अगर (pMsg->block) अणु
			हटाओ_client_block(pInfo, pClient);
			pClient->next_block_to_पढ़ो = pMsg->block;
		पूर्ण
		spin_unlock_irqrestore(&pClient->lock, flags);
	पूर्ण
	वापस pMsg;
पूर्ण

अटल व्योम हटाओ_client_block(काष्ठा r3964_info *pInfo,
				काष्ठा r3964_client_info *pClient)
अणु
	काष्ठा r3964_block_header *block;

	TRACE_PS("remove_client_block PID %d", pid_nr(pClient->pid));

	block = pClient->next_block_to_पढ़ो;
	अगर (block) अणु
		block->locks--;
		अगर (block->locks == 0) अणु
			हटाओ_from_rx_queue(pInfo, block);
		पूर्ण
	पूर्ण
	pClient->next_block_to_पढ़ो = शून्य;
पूर्ण

/*************************************************************
 * Line discipline routines
 *************************************************************/

अटल पूर्णांक r3964_खोलो(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा r3964_info *pInfo;

	TRACE_L("open");
	TRACE_L("tty=%p, PID=%d, disc_data=%p",
		tty, current->pid, tty->disc_data);

	pInfo = kदो_स्मृति(माप(काष्ठा r3964_info), GFP_KERNEL);
	TRACE_M("r3964_open - info kmalloc %p", pInfo);

	अगर (!pInfo) अणु
		prपूर्णांकk(KERN_ERR "r3964: failed to alloc info structure\n");
		वापस -ENOMEM;
	पूर्ण

	pInfo->rx_buf = kदो_स्मृति(RX_BUF_SIZE, GFP_KERNEL);
	TRACE_M("r3964_open - rx_buf kmalloc %p", pInfo->rx_buf);

	अगर (!pInfo->rx_buf) अणु
		prपूर्णांकk(KERN_ERR "r3964: failed to alloc receive buffer\n");
		kमुक्त(pInfo);
		TRACE_M("r3964_open - info kfree %p", pInfo);
		वापस -ENOMEM;
	पूर्ण

	pInfo->tx_buf = kदो_स्मृति(TX_BUF_SIZE, GFP_KERNEL);
	TRACE_M("r3964_open - tx_buf kmalloc %p", pInfo->tx_buf);

	अगर (!pInfo->tx_buf) अणु
		prपूर्णांकk(KERN_ERR "r3964: failed to alloc transmit buffer\n");
		kमुक्त(pInfo->rx_buf);
		TRACE_M("r3964_open - rx_buf kfree %p", pInfo->rx_buf);
		kमुक्त(pInfo);
		TRACE_M("r3964_open - info kfree %p", pInfo);
		वापस -ENOMEM;
	पूर्ण

	spin_lock_init(&pInfo->lock);
	mutex_init(&pInfo->पढ़ो_lock);
	pInfo->tty = tty;
	pInfo->priority = R3964_MASTER;
	pInfo->rx_first = pInfo->rx_last = शून्य;
	pInfo->tx_first = pInfo->tx_last = शून्य;
	pInfo->rx_position = 0;
	pInfo->tx_position = 0;
	pInfo->last_rx = 0;
	pInfo->blocks_in_rx_queue = 0;
	pInfo->firstClient = शून्य;
	pInfo->state = R3964_IDLE;
	pInfo->flags = R3964_DEBUG;
	pInfo->nRetry = 0;

	tty->disc_data = pInfo;
	tty->receive_room = 65536;

	समयr_setup(&pInfo->पंचांगr, on_समयout, 0);

	वापस 0;
पूर्ण

अटल व्योम r3964_बंद(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा r3964_info *pInfo = tty->disc_data;
	काष्ठा r3964_client_info *pClient, *pNext;
	काष्ठा r3964_message *pMsg;
	काष्ठा r3964_block_header *pHeader, *pNextHeader;
	अचिन्हित दीर्घ flags;

	TRACE_L("close");

	/*
	 * Make sure that our task queue isn't activated.  If it
	 * is, take it out of the linked list.
	 */
	del_समयr_sync(&pInfo->पंचांगr);

	/* Remove client-काष्ठाs and message queues: */
	pClient = pInfo->firstClient;
	जबतक (pClient) अणु
		pNext = pClient->next;
		जबतक (pClient->msg_count) अणु
			pMsg = हटाओ_msg(pInfo, pClient);
			अगर (pMsg) अणु
				kमुक्त(pMsg);
				TRACE_M("r3964_close - msg kfree %p", pMsg);
			पूर्ण
		पूर्ण
		put_pid(pClient->pid);
		kमुक्त(pClient);
		TRACE_M("r3964_close - client kfree %p", pClient);
		pClient = pNext;
	पूर्ण
	/* Remove jobs from tx_queue: */
	spin_lock_irqsave(&pInfo->lock, flags);
	pHeader = pInfo->tx_first;
	pInfo->tx_first = pInfo->tx_last = शून्य;
	spin_unlock_irqrestore(&pInfo->lock, flags);

	जबतक (pHeader) अणु
		pNextHeader = pHeader->next;
		kमुक्त(pHeader);
		pHeader = pNextHeader;
	पूर्ण

	/* Free buffers: */
	kमुक्त(pInfo->rx_buf);
	TRACE_M("r3964_close - rx_buf kfree %p", pInfo->rx_buf);
	kमुक्त(pInfo->tx_buf);
	TRACE_M("r3964_close - tx_buf kfree %p", pInfo->tx_buf);
	kमुक्त(pInfo);
	TRACE_M("r3964_close - info kfree %p", pInfo);
पूर्ण

अटल sमाप_प्रकार r3964_पढ़ो(काष्ठा tty_काष्ठा *tty, काष्ठा file *file,
			  अचिन्हित अक्षर *kbuf, माप_प्रकार nr,
			  व्योम **cookie, अचिन्हित दीर्घ offset)
अणु
	काष्ठा r3964_info *pInfo = tty->disc_data;
	काष्ठा r3964_client_info *pClient;
	काष्ठा r3964_message *pMsg;
	काष्ठा r3964_client_message theMsg;
	पूर्णांक ret;

	TRACE_L("read()");

	/*
	 *	Internal serialization of पढ़ोs.
	 */
	अगर (file->f_flags & O_NONBLOCK) अणु
		अगर (!mutex_trylock(&pInfo->पढ़ो_lock))
			वापस -EAGAIN;
	पूर्ण अन्यथा अणु
		अगर (mutex_lock_पूर्णांकerruptible(&pInfo->पढ़ो_lock))
			वापस -ERESTARTSYS;
	पूर्ण

	pClient = findClient(pInfo, task_pid(current));
	अगर (pClient) अणु
		pMsg = हटाओ_msg(pInfo, pClient);
		अगर (pMsg == शून्य) अणु
			/* no messages available. */
			अगर (tty_io_nonblock(tty, file)) अणु
				ret = -EAGAIN;
				जाओ unlock;
			पूर्ण
			/* block until there is a message: */
			रुको_event_पूर्णांकerruptible(tty->पढ़ो_रुको,
					(pMsg = हटाओ_msg(pInfo, pClient)));
		पूर्ण

		/* If we still haven't got a message, we must have been संकेतled */

		अगर (!pMsg) अणु
			ret = -EINTR;
			जाओ unlock;
		पूर्ण

		/* deliver msg to client process: */
		theMsg.msg_id = pMsg->msg_id;
		theMsg.arg = pMsg->arg;
		theMsg.error_code = pMsg->error_code;
		ret = माप(काष्ठा r3964_client_message);

		kमुक्त(pMsg);
		TRACE_M("r3964_read - msg kfree %p", pMsg);

		स_नकल(kbuf, &theMsg, ret);

		TRACE_PS("read - return %d", ret);
		जाओ unlock;
	पूर्ण
	ret = -EPERM;
unlock:
	mutex_unlock(&pInfo->पढ़ो_lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार r3964_ग_लिखो(काष्ठा tty_काष्ठा *tty, काष्ठा file *file,
			   स्थिर अचिन्हित अक्षर *data, माप_प्रकार count)
अणु
	काष्ठा r3964_info *pInfo = tty->disc_data;
	काष्ठा r3964_block_header *pHeader;
	काष्ठा r3964_client_info *pClient;
	अचिन्हित अक्षर *new_data;

	TRACE_L("write request, %d characters", count);
/* 
 * Verअगरy the poपूर्णांकers 
 */

	अगर (!pInfo)
		वापस -EIO;

/*
 * Ensure that the caller करोes not wish to send too much.
 */
	अगर (count > R3964_MTU) अणु
		अगर (pInfo->flags & R3964_DEBUG) अणु
			TRACE_L(KERN_WARNING "r3964_write: truncating user "
				"packet from %u to mtu %d", count, R3964_MTU);
		पूर्ण
		count = R3964_MTU;
	पूर्ण
/*
 * Allocate a buffer क्रम the data and copy it from the buffer with header prepended
 */
	new_data = kदो_स्मृति(count + माप(काष्ठा r3964_block_header),
			GFP_KERNEL);
	TRACE_M("r3964_write - kmalloc %p", new_data);
	अगर (new_data == शून्य) अणु
		अगर (pInfo->flags & R3964_DEBUG) अणु
			prपूर्णांकk(KERN_ERR "r3964_write: no memory\n");
		पूर्ण
		वापस -ENOSPC;
	पूर्ण

	pHeader = (काष्ठा r3964_block_header *)new_data;
	pHeader->data = new_data + माप(काष्ठा r3964_block_header);
	pHeader->length = count;
	pHeader->locks = 0;
	pHeader->owner = शून्य;

	pClient = findClient(pInfo, task_pid(current));
	अगर (pClient) अणु
		pHeader->owner = pClient;
	पूर्ण

	स_नकल(pHeader->data, data, count);	/* We alपढ़ोy verअगरied this */

	अगर (pInfo->flags & R3964_DEBUG) अणु
		dump_block(pHeader->data, count);
	पूर्ण

/*
 * Add buffer to transmit-queue:
 */
	add_tx_queue(pInfo, pHeader);
	trigger_transmit(pInfo);

	वापस 0;
पूर्ण

अटल पूर्णांक r3964_ioctl(काष्ठा tty_काष्ठा *tty, काष्ठा file *file,
		अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा r3964_info *pInfo = tty->disc_data;
	अगर (pInfo == शून्य)
		वापस -EINVAL;
	चयन (cmd) अणु
	हाल R3964_ENABLE_SIGNALS:
		वापस enable_संकेतs(pInfo, task_pid(current), arg);
	हाल R3964_SETPRIORITY:
		अगर (arg < R3964_MASTER || arg > R3964_SLAVE)
			वापस -EINVAL;
		pInfo->priority = arg & 0xff;
		वापस 0;
	हाल R3964_USE_BCC:
		अगर (arg)
			pInfo->flags |= R3964_BCC;
		अन्यथा
			pInfo->flags &= ~R3964_BCC;
		वापस 0;
	हाल R3964_READ_TELEGRAM:
		वापस पढ़ो_telegram(pInfo, task_pid(current),
				(अचिन्हित अक्षर __user *)arg);
	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल पूर्णांक r3964_compat_ioctl(काष्ठा tty_काष्ठा *tty, काष्ठा file *file,
		अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	चयन (cmd) अणु
	हाल R3964_ENABLE_SIGNALS:
	हाल R3964_SETPRIORITY:
	हाल R3964_USE_BCC:
		वापस r3964_ioctl(tty, file, cmd, arg);
	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल व्योम r3964_set_termios(काष्ठा tty_काष्ठा *tty, काष्ठा ktermios *old)
अणु
	TRACE_L("set_termios");
पूर्ण

/* Called without the kernel lock held - fine */
अटल __poll_t r3964_poll(काष्ठा tty_काष्ठा *tty, काष्ठा file *file,
			काष्ठा poll_table_काष्ठा *रुको)
अणु
	काष्ठा r3964_info *pInfo = tty->disc_data;
	काष्ठा r3964_client_info *pClient;
	काष्ठा r3964_message *pMsg = शून्य;
	अचिन्हित दीर्घ flags;
	__poll_t result = EPOLLOUT;

	TRACE_L("POLL");

	pClient = findClient(pInfo, task_pid(current));
	अगर (pClient) अणु
		poll_रुको(file, &tty->पढ़ो_रुको, रुको);
		spin_lock_irqsave(&pInfo->lock, flags);
		pMsg = pClient->first_msg;
		spin_unlock_irqrestore(&pInfo->lock, flags);
		अगर (pMsg)
			result |= EPOLLIN | EPOLLRDNORM;
	पूर्ण अन्यथा अणु
		result = -EINVAL;
	पूर्ण
	वापस result;
पूर्ण

अटल व्योम r3964_receive_buf(काष्ठा tty_काष्ठा *tty, स्थिर अचिन्हित अक्षर *cp,
			अक्षर *fp, पूर्णांक count)
अणु
	काष्ठा r3964_info *pInfo = tty->disc_data;
	स्थिर अचिन्हित अक्षर *p;
	अक्षर *f, flags = TTY_NORMAL;
	पूर्णांक i;

	क्रम (i = count, p = cp, f = fp; i; i--, p++) अणु
		अगर (f)
			flags = *f++;
		अगर (flags == TTY_NORMAL) अणु
			receive_अक्षर(pInfo, *p);
		पूर्ण अन्यथा अणु
			receive_error(pInfo, flags);
		पूर्ण

	पूर्ण
पूर्ण

MODULE_LICENSE("GPL");
MODULE_ALIAS_LDISC(N_R3964);
