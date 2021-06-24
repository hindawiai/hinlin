<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2013 - 2018 Intel Corporation. */

#अगर_अघोषित _FM10K_MBX_H_
#घोषणा _FM10K_MBX_H_

/* क्रमward declaration */
काष्ठा fm10k_mbx_info;

#समावेश "fm10k_type.h"
#समावेश "fm10k_tlv.h"

/* PF Mailbox Registers */
#घोषणा FM10K_MBMEM(_n)		((_n) + 0x18000)
#घोषणा FM10K_MBMEM_VF(_n, _m)	(((_n) * 0x10) + (_m) + 0x18000)
#घोषणा FM10K_MBMEM_SM(_n)	((_n) + 0x18400)
#घोषणा FM10K_MBMEM_PF(_n)	((_n) + 0x18600)
/* XOR provides means of चयनing from Tx to Rx FIFO */
#घोषणा FM10K_MBMEM_PF_XOR	(FM10K_MBMEM_SM(0) ^ FM10K_MBMEM_PF(0))
#घोषणा FM10K_MBX(_n)		((_n) + 0x18800)
#घोषणा FM10K_MBX_REQ				0x00000002
#घोषणा FM10K_MBX_ACK				0x00000004
#घोषणा FM10K_MBX_REQ_INTERRUPT			0x00000008
#घोषणा FM10K_MBX_ACK_INTERRUPT			0x00000010
#घोषणा FM10K_MBX_INTERRUPT_ENABLE		0x00000020
#घोषणा FM10K_MBX_INTERRUPT_DISABLE		0x00000040
#घोषणा FM10K_MBX_GLOBAL_REQ_INTERRUPT		0x00000200
#घोषणा FM10K_MBX_GLOBAL_ACK_INTERRUPT		0x00000400
#घोषणा FM10K_MBICR(_n)		((_n) + 0x18840)
#घोषणा FM10K_GMBX		0x18842

/* VF Mailbox Registers */
#घोषणा FM10K_VFMBX		0x00010
#घोषणा FM10K_VFMBMEM(_n)	((_n) + 0x00020)
#घोषणा FM10K_VFMBMEM_LEN	16
#घोषणा FM10K_VFMBMEM_VF_XOR	(FM10K_VFMBMEM_LEN / 2)

/* Delays/समयouts */
#घोषणा FM10K_MBX_DISCONNECT_TIMEOUT		500
#घोषणा FM10K_MBX_POLL_DELAY			19
#घोषणा FM10K_MBX_INT_DELAY			20

/* PF/VF Mailbox state machine
 *
 * +----------+	    connect()	+----------+
 * |  CLOSED  | --------------> |  CONNECT |
 * +----------+			+----------+
 *   ^				  ^	 |
 *   | rcv:	      rcv:	  |	 | rcv:
 *   |  Connect	       Disconnect |	 |  Connect
 *   |  Disconnect     Error	  |	 |  Data
 *   |				  |	 |
 *   |				  |	 V
 * +----------+   disconnect()	+----------+
 * |DISCONNECT| <-------------- |   OPEN   |
 * +----------+			+----------+
 *
 * The diagram above describes the PF/VF mailbox state machine.  There
 * are four मुख्य states to this machine.
 * Closed: This state represents a mailbox that is in a standby state
 *	   with पूर्णांकerrupts disabled.  In this state the mailbox should not
 *	   पढ़ो the mailbox or ग_लिखो any data.  The only means of निकासing
 *	   this state is क्रम the प्रणाली to make the connect() call क्रम the
 *	   mailbox, it will then transition to the connect state.
 * Connect: In this state the mailbox is seeking a connection.  It will
 *	    post a connect message with no specअगरied destination and will
 *	    रुको क्रम a reply from the other side of the mailbox.  This state
 *	    is निकासed when either a connect with the local mailbox as the
 *	    destination is received or when a data message is received with
 *	    a valid sequence number.
 * Open: In this state the mailbox is able to transfer data between the local
 *       entity and the remote.  It will fall back to connect in the event of
 *       receiving either an error message, or a disconnect message.  It will
 *       transition to disconnect on a call to disconnect();
 * Disconnect: In this state the mailbox is attempting to gracefully terminate
 *	       the connection.  It will करो so at the first poपूर्णांक where it knows
 *	       that the remote endpoपूर्णांक is either करोne sending, or when the
 *	       remote endpoपूर्णांक has fallen back पूर्णांकo connect.
 */
क्रमागत fm10k_mbx_state अणु
	FM10K_STATE_CLOSED,
	FM10K_STATE_CONNECT,
	FM10K_STATE_OPEN,
	FM10K_STATE_DISCONNECT,
पूर्ण;

/* PF/VF Mailbox header क्रमmat
 *    3			  2		      1			  0
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |        Size/Err_no/CRC        | Rsvd0 | Head  | Tail  | Type  |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * The layout above describes the क्रमmat क्रम the header used in the PF/VF
 * mailbox.  The header is broken out पूर्णांकo the following fields:
 * Type: There are 4 supported message types
 *		0x8: Data header - used to transport message data
 *		0xC: Connect header - used to establish connection
 *		0xD: Disconnect header - used to tear करोwn a connection
 *		0xE: Error header - used to address message exceptions
 * Tail: Tail index क्रम local FIFO
 *		Tail index actually consists of two parts.  The MSB of
 *		the head is a loop tracker, it is 0 on an even numbered
 *		loop through the FIFO, and 1 on the odd numbered loops.
 *		To get the actual mailbox offset based on the tail it
 *		is necessary to add bit 3 to bit 0 and clear bit 3.  This
 *		gives us a valid range of 0x1 - 0xE.
 * Head: Head index क्रम remote FIFO
 *		Head index follows the same क्रमmat as the tail index.
 * Rsvd0: Reserved 0 portion of the mailbox header
 * CRC: Running CRC क्रम all data since connect plus current message header
 * Size: Maximum message size - Applies only to connect headers
 *		The maximum message size is provided during connect to aव्योम
 *		jamming the mailbox with messages that करो not fit.
 * Err_no: Error number - Applies only to error headers
 *		The error number provides an indication of the type of error
 *		experienced.
 */

/* macros क्रम retrieving and setting header values */
#घोषणा FM10K_MSG_HDR_MASK(name) \
	((0x1u << FM10K_MSG_##name##_SIZE) - 1)
#घोषणा FM10K_MSG_HDR_FIELD_SET(value, name) \
	(((u32)(value) & FM10K_MSG_HDR_MASK(name)) << FM10K_MSG_##name##_SHIFT)
#घोषणा FM10K_MSG_HDR_FIELD_GET(value, name) \
	((u16)((value) >> FM10K_MSG_##name##_SHIFT) & FM10K_MSG_HDR_MASK(name))

/* offsets shared between all headers */
#घोषणा FM10K_MSG_TYPE_SHIFT			0
#घोषणा FM10K_MSG_TYPE_SIZE			4
#घोषणा FM10K_MSG_TAIL_SHIFT			4
#घोषणा FM10K_MSG_TAIL_SIZE			4
#घोषणा FM10K_MSG_HEAD_SHIFT			8
#घोषणा FM10K_MSG_HEAD_SIZE			4
#घोषणा FM10K_MSG_RSVD0_SHIFT			12
#घोषणा FM10K_MSG_RSVD0_SIZE			4

/* offsets क्रम data/disconnect headers */
#घोषणा FM10K_MSG_CRC_SHIFT			16
#घोषणा FM10K_MSG_CRC_SIZE			16

/* offsets क्रम connect headers */
#घोषणा FM10K_MSG_CONNECT_SIZE_SHIFT		16
#घोषणा FM10K_MSG_CONNECT_SIZE_SIZE		16

/* offsets क्रम error headers */
#घोषणा FM10K_MSG_ERR_NO_SHIFT			16
#घोषणा FM10K_MSG_ERR_NO_SIZE			16

क्रमागत fm10k_msg_type अणु
	FM10K_MSG_DATA			= 0x8,
	FM10K_MSG_CONNECT		= 0xC,
	FM10K_MSG_DISCONNECT		= 0xD,
	FM10K_MSG_ERROR			= 0xE,
पूर्ण;

/* HNI/SM Mailbox FIFO क्रमmat
 *    3                   2                   1                   0
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-------+-----------------------+-------+-----------------------+
 * | Error |      Remote Head      |Version|      Local Tail       |
 * +-------+-----------------------+-------+-----------------------+
 * |                                                               |
 * .                        Local FIFO Data                        .
 * .                                                               .
 * +-------+-----------------------+-------+-----------------------+
 *
 * The layout above describes the क्रमmat क्रम the FIFOs used by the host
 * network पूर्णांकerface and the चयन manager to communicate messages back
 * and क्रमth.  Both the HNI and the चयन मुख्यtain one such FIFO.  The
 * layout in memory has the चयन manager FIFO followed immediately by
 * the HNI FIFO.  For this reason I am using just the poपूर्णांकer to the
 * HNI FIFO in the mailbox ops as the offset between the two is fixed.
 *
 * The header क्रम the FIFO is broken out पूर्णांकo the following fields:
 * Local Tail:  Offset पूर्णांकo FIFO region क्रम next DWORD to ग_लिखो.
 * Version:  Version info क्रम mailbox, only values of 0/1 are supported.
 * Remote Head:  Offset पूर्णांकo remote FIFO to indicate how much we have पढ़ो.
 * Error: Error indication, values TBD.
 */

/* version number क्रम चयन manager mailboxes */
#घोषणा FM10K_SM_MBX_VERSION		1
#घोषणा FM10K_SM_MBX_FIFO_LEN		(FM10K_MBMEM_PF_XOR - 1)

/* offsets shared between all SM FIFO headers */
#घोषणा FM10K_MSG_SM_TAIL_SHIFT			0
#घोषणा FM10K_MSG_SM_TAIL_SIZE			12
#घोषणा FM10K_MSG_SM_VER_SHIFT			12
#घोषणा FM10K_MSG_SM_VER_SIZE			4
#घोषणा FM10K_MSG_SM_HEAD_SHIFT			16
#घोषणा FM10K_MSG_SM_HEAD_SIZE			12
#घोषणा FM10K_MSG_SM_ERR_SHIFT			28
#घोषणा FM10K_MSG_SM_ERR_SIZE			4

/* All error messages वापसed by mailbox functions
 * The value -511 is 0xFE01 in hex.  The idea is to order the errors
 * from 0xFE01 - 0xFEFF so error codes are easily visible in the mailbox
 * messages.  This also helps to aव्योम error number collisions as Linux
 * करोesn't appear to use error numbers 256 - 511.
 */
#घोषणा FM10K_MBX_ERR(_n) ((_n) - 512)
#घोषणा FM10K_MBX_ERR_NO_MBX		FM10K_MBX_ERR(0x01)
#घोषणा FM10K_MBX_ERR_NO_SPACE		FM10K_MBX_ERR(0x03)
#घोषणा FM10K_MBX_ERR_TAIL		FM10K_MBX_ERR(0x05)
#घोषणा FM10K_MBX_ERR_HEAD		FM10K_MBX_ERR(0x06)
#घोषणा FM10K_MBX_ERR_SRC		FM10K_MBX_ERR(0x08)
#घोषणा FM10K_MBX_ERR_TYPE		FM10K_MBX_ERR(0x09)
#घोषणा FM10K_MBX_ERR_SIZE		FM10K_MBX_ERR(0x0B)
#घोषणा FM10K_MBX_ERR_BUSY		FM10K_MBX_ERR(0x0C)
#घोषणा FM10K_MBX_ERR_RSVD0		FM10K_MBX_ERR(0x0E)
#घोषणा FM10K_MBX_ERR_CRC		FM10K_MBX_ERR(0x0F)

#घोषणा FM10K_MBX_CRC_SEED		0xFFFF

काष्ठा fm10k_mbx_ops अणु
	s32 (*connect)(काष्ठा fm10k_hw *, काष्ठा fm10k_mbx_info *);
	व्योम (*disconnect)(काष्ठा fm10k_hw *, काष्ठा fm10k_mbx_info *);
	bool (*rx_पढ़ोy)(काष्ठा fm10k_mbx_info *);
	bool (*tx_पढ़ोy)(काष्ठा fm10k_mbx_info *, u16);
	bool (*tx_complete)(काष्ठा fm10k_mbx_info *);
	s32 (*enqueue_tx)(काष्ठा fm10k_hw *, काष्ठा fm10k_mbx_info *,
			  स्थिर u32 *);
	s32 (*process)(काष्ठा fm10k_hw *, काष्ठा fm10k_mbx_info *);
	s32 (*रेजिस्टर_handlers)(काष्ठा fm10k_mbx_info *,
				 स्थिर काष्ठा fm10k_msg_data *);
पूर्ण;

काष्ठा fm10k_mbx_fअगरo अणु
	u32 *buffer;
	u16 head;
	u16 tail;
	u16 size;
पूर्ण;

/* size of buffer to be stored in mailbox क्रम FIFOs */
#घोषणा FM10K_MBX_TX_BUFFER_SIZE	512
#घोषणा FM10K_MBX_RX_BUFFER_SIZE	128
#घोषणा FM10K_MBX_BUFFER_SIZE \
	(FM10K_MBX_TX_BUFFER_SIZE + FM10K_MBX_RX_BUFFER_SIZE)

/* minimum and maximum message size in dwords */
#घोषणा FM10K_MBX_MSG_MAX_SIZE \
	((FM10K_MBX_TX_BUFFER_SIZE - 1) & (FM10K_MBX_RX_BUFFER_SIZE - 1))
#घोषणा FM10K_VFMBX_MSG_MTU	((FM10K_VFMBMEM_LEN / 2) - 1)

#घोषणा FM10K_MBX_INIT_TIMEOUT	2000 /* number of retries on mailbox */
#घोषणा FM10K_MBX_INIT_DELAY	500  /* microseconds between retries */

काष्ठा fm10k_mbx_info अणु
	/* function poपूर्णांकers क्रम mailbox operations */
	काष्ठा fm10k_mbx_ops ops;
	स्थिर काष्ठा fm10k_msg_data *msg_data;

	/* message FIFOs */
	काष्ठा fm10k_mbx_fअगरo rx;
	काष्ठा fm10k_mbx_fअगरo tx;

	/* delay क्रम handling समयouts */
	u32 समयout;
	u32 udelay;

	/* mailbox state info */
	u32 mbx_reg, mbmem_reg, mbx_lock, mbx_hdr;
	u16 max_size, mbmem_len;
	u16 tail, tail_len, pulled;
	u16 head, head_len, pushed;
	u16 local, remote;
	क्रमागत fm10k_mbx_state state;

	/* result of last mailbox test */
	s32 test_result;

	/* statistics */
	u64 tx_busy;
	u64 tx_dropped;
	u64 tx_messages;
	u64 tx_dwords;
	u64 tx_mbmem_pulled;
	u64 rx_messages;
	u64 rx_dwords;
	u64 rx_mbmem_pushed;
	u64 rx_parse_err;

	/* Buffer to store messages */
	u32 buffer[FM10K_MBX_BUFFER_SIZE];
पूर्ण;

s32 fm10k_pfvf_mbx_init(काष्ठा fm10k_hw *, काष्ठा fm10k_mbx_info *,
			स्थिर काष्ठा fm10k_msg_data *, u8);
s32 fm10k_sm_mbx_init(काष्ठा fm10k_hw *, काष्ठा fm10k_mbx_info *,
		      स्थिर काष्ठा fm10k_msg_data *);

#पूर्ण_अगर /* _FM10K_MBX_H_ */
