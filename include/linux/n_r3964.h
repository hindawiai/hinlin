<शैली गुरु>
/* r3964 linediscipline क्रम linux
 *
 * -----------------------------------------------------------
 * Copyright by
 * Philips Automation Projects
 * Kassel (Germany)
 * -----------------------------------------------------------
 * This software may be used and distributed according to the terms of
 * the GNU General Public License, incorporated herein by reference.
 *
 * Author:
 * L. Haag
 *
 * $Log: r3964.h,v $
 * Revision 1.4  2005/12/21 19:54:24  Kurt Huwig <kurt huwig de>
 * Fixed HZ usage on 2.6 kernels
 * Removed unnecessary include
 *
 * Revision 1.3  2001/03/18 13:02:24  dwmw2
 * Fix समयr usage, use spinlocks properly.
 *
 * Revision 1.2  2001/03/18 12:53:15  dwmw2
 * Merge changes in 2.4.2
 *
 * Revision 1.1.1.1  1998/10/13 16:43:14  dwmw2
 * This'll screw the version control
 *
 * Revision 1.6  1998/09/30 00:40:38  dwmw2
 * Updated to use kernel's N_R3964 अगर available
 *
 * Revision 1.4  1998/04/02 20:29:44  lhaag
 * select, blocking, ...
 *
 * Revision 1.3  1998/02/12 18:58:43  root
 * fixed some memory leaks
 * calculation of checksum अक्षरacters
 *
 * Revision 1.2  1998/02/07 13:03:17  root
 * ioctl पढ़ो_telegram
 *
 * Revision 1.1  1998/02/06 19:19:43  root
 * Initial revision
 *
 *
 */
#अगर_अघोषित __LINUX_N_R3964_H__
#घोषणा __LINUX_N_R3964_H__


#समावेश <linux/param.h>
#समावेश <uapi/linux/n_r3964.h>

/*
 * Common ascii handshake अक्षरacters:
 */

#घोषणा STX 0x02
#घोषणा ETX 0x03
#घोषणा DLE 0x10
#घोषणा NAK 0x15

/*
 * Timeouts (from milliseconds to jअगरfies)
 */

#घोषणा R3964_TO_QVZ ((550)*HZ/1000)
#घोषणा R3964_TO_ZVZ ((220)*HZ/1000)
#घोषणा R3964_TO_NO_BUF ((400)*HZ/1000)
#घोषणा R3964_NO_TX_ROOM ((100)*HZ/1000)
#घोषणा R3964_TO_RX_PANIC ((4000)*HZ/1000)
#घोषणा R3964_MAX_RETRIES 5


क्रमागत अणु R3964_IDLE, 
	   R3964_TX_REQUEST, R3964_TRANSMITTING, 
	   R3964_WAIT_ZVZ_BEFORE_TX_RETRY, R3964_WAIT_FOR_TX_ACK,
	   R3964_WAIT_FOR_RX_BUF,
	   R3964_RECEIVING, R3964_WAIT_FOR_BCC, R3964_WAIT_FOR_RX_REPEAT
	   पूर्ण;

/*
 * All खोलो file-handles are 'clients' and are stored in a linked list:
 */

काष्ठा r3964_message;

काष्ठा r3964_client_info अणु
	spinlock_t     lock;
	काष्ठा pid    *pid;
	अचिन्हित पूर्णांक   sig_flags;

	काष्ठा r3964_client_info *next;

	काष्ठा r3964_message *first_msg;
	काष्ठा r3964_message *last_msg;
	काष्ठा r3964_block_header *next_block_to_पढ़ो;
	पूर्णांक            msg_count;
पूर्ण;



काष्ठा r3964_block_header;

/* पूर्णांकernal version of client_message: */
काष्ठा r3964_message अणु
	  पूर्णांक     msg_id;
	  पूर्णांक     arg;
	  पूर्णांक     error_code;
	  काष्ठा r3964_block_header *block;
	  काष्ठा r3964_message *next;
पूर्ण;

/*
 * Header of received block in rx_buf/tx_buf:
 */

काष्ठा r3964_block_header 
अणु
	अचिन्हित पूर्णांक length;             /* length in अक्षरs without header */
	अचिन्हित अक्षर *data;             /* usually data is located 
                                        immediately behind this काष्ठा */
	अचिन्हित पूर्णांक locks;              /* only used in rx_buffer */
	  
    काष्ठा r3964_block_header *next;
	काष्ठा r3964_client_info *owner;  /* =शून्य in rx_buffer */
पूर्ण;

/*
 * If rx_buf hasn't enough space to store R3964_MTU अक्षरs,
 * we will reject all incoming STX-requests by sending NAK.
 */

#घोषणा RX_BUF_SIZE    4000
#घोषणा TX_BUF_SIZE    4000
#घोषणा R3964_MAX_BLOCKS_IN_RX_QUEUE 100

#घोषणा R3964_PARITY 0x0001
#घोषणा R3964_FRAME  0x0002
#घोषणा R3964_OVERRUN 0x0004
#घोषणा R3964_UNKNOWN 0x0008
#घोषणा R3964_BREAK   0x0010
#घोषणा R3964_CHECKSUM 0x0020
#घोषणा R3964_ERROR  0x003f
#घोषणा R3964_BCC   0x4000
#घोषणा R3964_DEBUG 0x8000


काष्ठा r3964_info अणु
	spinlock_t     lock;
	काष्ठा tty_काष्ठा *tty;
	अचिन्हित अक्षर priority;
	अचिन्हित अक्षर *rx_buf;            /* ring buffer */
	अचिन्हित अक्षर *tx_buf;

	काष्ठा r3964_block_header *rx_first;
	काष्ठा r3964_block_header *rx_last;
	काष्ठा r3964_block_header *tx_first;
	काष्ठा r3964_block_header *tx_last;
	अचिन्हित पूर्णांक tx_position;
        अचिन्हित पूर्णांक rx_position;
	अचिन्हित अक्षर last_rx;
	अचिन्हित अक्षर bcc;
        अचिन्हित पूर्णांक  blocks_in_rx_queue;

	काष्ठा mutex पढ़ो_lock;		/* serialize r3964_पढ़ो */

	काष्ठा r3964_client_info *firstClient;
	अचिन्हित पूर्णांक state;
	अचिन्हित पूर्णांक flags;

	काष्ठा समयr_list पंचांगr;
	पूर्णांक nRetry;
पूर्ण;

#पूर्ण_अगर
