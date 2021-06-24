<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LAPB_H
#घोषणा _LAPB_H 
#समावेश <linux/lapb.h>
#समावेश <linux/refcount.h>

#घोषणा	LAPB_HEADER_LEN	20		/* LAPB over Ethernet + a bit more */

#घोषणा	LAPB_ACK_PENDING_CONDITION	0x01
#घोषणा	LAPB_REJECT_CONDITION		0x02
#घोषणा	LAPB_PEER_RX_BUSY_CONDITION	0x04

/* Control field ढाँचाs */
#घोषणा	LAPB_I		0x00	/* Inक्रमmation frames */
#घोषणा	LAPB_S		0x01	/* Supervisory frames */
#घोषणा	LAPB_U		0x03	/* Unnumbered frames */

#घोषणा	LAPB_RR		0x01	/* Receiver पढ़ोy */
#घोषणा	LAPB_RNR	0x05	/* Receiver not पढ़ोy */
#घोषणा	LAPB_REJ	0x09	/* Reject */

#घोषणा	LAPB_SABM	0x2F	/* Set Asynchronous Balanced Mode */
#घोषणा	LAPB_SABME	0x6F	/* Set Asynchronous Balanced Mode Extended */
#घोषणा	LAPB_DISC	0x43	/* Disconnect */
#घोषणा	LAPB_DM		0x0F	/* Disconnected mode */
#घोषणा	LAPB_UA		0x63	/* Unnumbered acknowledge */
#घोषणा	LAPB_FRMR	0x87	/* Frame reject */

#घोषणा LAPB_ILLEGAL	0x100	/* Impossible to be a real frame type */

#घोषणा	LAPB_SPF	0x10	/* Poll/final bit क्रम standard LAPB */
#घोषणा	LAPB_EPF	0x01	/* Poll/final bit क्रम extended LAPB */

#घोषणा	LAPB_FRMR_W	0x01	/* Control field invalid	*/
#घोषणा	LAPB_FRMR_X	0x02	/* I field invalid		*/
#घोषणा	LAPB_FRMR_Y	0x04	/* I field too दीर्घ		*/
#घोषणा	LAPB_FRMR_Z	0x08	/* Invalid N(R)			*/

#घोषणा	LAPB_POLLOFF	0
#घोषणा	LAPB_POLLON	1

/* LAPB C-bit */
#घोषणा LAPB_COMMAND	1
#घोषणा LAPB_RESPONSE	2

#घोषणा	LAPB_ADDR_A	0x03
#घोषणा	LAPB_ADDR_B	0x01
#घोषणा	LAPB_ADDR_C	0x0F
#घोषणा	LAPB_ADDR_D	0x07

/* Define Link State स्थिरants. */
क्रमागत अणु
	LAPB_STATE_0,	/* Disconnected State		*/
	LAPB_STATE_1,	/* Aरुकोing Connection State	*/
	LAPB_STATE_2,	/* Aरुकोing Disconnection State	*/
	LAPB_STATE_3,	/* Data Transfer State		*/
	LAPB_STATE_4	/* Frame Reject State		*/
पूर्ण;

#घोषणा	LAPB_DEFAULT_MODE		(LAPB_STANDARD | LAPB_SLP | LAPB_DTE)
#घोषणा	LAPB_DEFAULT_WINDOW		7		/* Winकरोw=7 */
#घोषणा	LAPB_DEFAULT_T1			(5 * HZ)	/* T1=5s    */
#घोषणा	LAPB_DEFAULT_T2			(1 * HZ)	/* T2=1s    */
#घोषणा	LAPB_DEFAULT_N2			20		/* N2=20    */

#घोषणा	LAPB_SMODULUS	8
#घोषणा	LAPB_EMODULUS	128

/*
 *	Inक्रमmation about the current frame.
 */
काष्ठा lapb_frame अणु
	अचिन्हित लघु		type;		/* Parsed type		*/
	अचिन्हित लघु		nr, ns;		/* N(R), N(S)		*/
	अचिन्हित अक्षर		cr;		/* Command/Response	*/
	अचिन्हित अक्षर		pf;		/* Poll/Final		*/
	अचिन्हित अक्षर		control[2];	/* Original control data*/
पूर्ण;

/*
 *	The per LAPB connection control काष्ठाure.
 */
काष्ठा lapb_cb अणु
	काष्ठा list_head	node;
	काष्ठा net_device	*dev;

	/* Link status fields */
	अचिन्हित पूर्णांक		mode;
	अचिन्हित अक्षर		state;
	अचिन्हित लघु		vs, vr, va;
	अचिन्हित अक्षर		condition;
	अचिन्हित लघु		n2, n2count;
	अचिन्हित लघु		t1, t2;
	काष्ठा समयr_list	t1समयr, t2समयr;
	bool			t1समयr_running, t2समयr_running;

	/* Internal control inक्रमmation */
	काष्ठा sk_buff_head	ग_लिखो_queue;
	काष्ठा sk_buff_head	ack_queue;
	अचिन्हित अक्षर		winकरोw;
	स्थिर काष्ठा lapb_रेजिस्टर_काष्ठा *callbacks;

	/* FRMR control inक्रमmation */
	काष्ठा lapb_frame	frmr_data;
	अचिन्हित अक्षर		frmr_type;

	spinlock_t		lock;
	refcount_t		refcnt;
पूर्ण;

/* lapb_अगरace.c */
व्योम lapb_connect_confirmation(काष्ठा lapb_cb *lapb, पूर्णांक);
व्योम lapb_connect_indication(काष्ठा lapb_cb *lapb, पूर्णांक);
व्योम lapb_disconnect_confirmation(काष्ठा lapb_cb *lapb, पूर्णांक);
व्योम lapb_disconnect_indication(काष्ठा lapb_cb *lapb, पूर्णांक);
पूर्णांक lapb_data_indication(काष्ठा lapb_cb *lapb, काष्ठा sk_buff *);
पूर्णांक lapb_data_transmit(काष्ठा lapb_cb *lapb, काष्ठा sk_buff *);

/* lapb_in.c */
व्योम lapb_data_input(काष्ठा lapb_cb *lapb, काष्ठा sk_buff *);

/* lapb_out.c */
व्योम lapb_kick(काष्ठा lapb_cb *lapb);
व्योम lapb_transmit_buffer(काष्ठा lapb_cb *lapb, काष्ठा sk_buff *, पूर्णांक);
व्योम lapb_establish_data_link(काष्ठा lapb_cb *lapb);
व्योम lapb_enquiry_response(काष्ठा lapb_cb *lapb);
व्योम lapb_समयout_response(काष्ठा lapb_cb *lapb);
व्योम lapb_check_अगरrames_acked(काष्ठा lapb_cb *lapb, अचिन्हित लघु);
व्योम lapb_check_need_response(काष्ठा lapb_cb *lapb, पूर्णांक, पूर्णांक);

/* lapb_subr.c */
व्योम lapb_clear_queues(काष्ठा lapb_cb *lapb);
व्योम lapb_frames_acked(काष्ठा lapb_cb *lapb, अचिन्हित लघु);
व्योम lapb_requeue_frames(काष्ठा lapb_cb *lapb);
पूर्णांक lapb_validate_nr(काष्ठा lapb_cb *lapb, अचिन्हित लघु);
पूर्णांक lapb_decode(काष्ठा lapb_cb *lapb, काष्ठा sk_buff *, काष्ठा lapb_frame *);
व्योम lapb_send_control(काष्ठा lapb_cb *lapb, पूर्णांक, पूर्णांक, पूर्णांक);
व्योम lapb_transmit_frmr(काष्ठा lapb_cb *lapb);

/* lapb_समयr.c */
व्योम lapb_start_t1समयr(काष्ठा lapb_cb *lapb);
व्योम lapb_start_t2समयr(काष्ठा lapb_cb *lapb);
व्योम lapb_stop_t1समयr(काष्ठा lapb_cb *lapb);
व्योम lapb_stop_t2समयr(काष्ठा lapb_cb *lapb);
पूर्णांक lapb_t1समयr_running(काष्ठा lapb_cb *lapb);

/*
 * Debug levels.
 *	0 = Off
 *	1 = State Changes
 *	2 = Packets I/O and State Changes
 *	3 = Hex dumps, Packets I/O and State Changes.
 */
#घोषणा	LAPB_DEBUG	0

#घोषणा lapb_dbg(level, fmt, ...)			\
करो अणु							\
	अगर (level < LAPB_DEBUG)				\
		pr_debug(fmt, ##__VA_ARGS__);		\
पूर्ण जबतक (0)

#पूर्ण_अगर
