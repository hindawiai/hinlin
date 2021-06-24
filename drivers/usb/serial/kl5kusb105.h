<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Definitions क्रम the KLSI KL5KUSB105 serial port adapter
 */

/* venकरोr/product pairs that are known to contain this chipset */
#घोषणा PALMCONNECT_VID		0x0830
#घोषणा PALMCONNECT_PID		0x0080

/* Venकरोr commands: */


/* port table -- the chip supports up to 4 channels */

/* baud rates */

क्रमागत अणु
	kl5kusb105a_sio_b115200 = 0,
	kl5kusb105a_sio_b57600  = 1,
	kl5kusb105a_sio_b38400  = 2,
	kl5kusb105a_sio_b19200  = 4,
	kl5kusb105a_sio_b14400  = 5,
	kl5kusb105a_sio_b9600   = 6,
	kl5kusb105a_sio_b4800   = 8,	/* unchecked */
	kl5kusb105a_sio_b2400   = 9,	/* unchecked */
	kl5kusb105a_sio_b1200   = 0xa,	/* unchecked */
	kl5kusb105a_sio_b600    = 0xb	/* unchecked */
पूर्ण;

/* data bits */
#घोषणा kl5kusb105a_dtb_7   7
#घोषणा kl5kusb105a_dtb_8   8



/* requests: */
#घोषणा KL5KUSB105A_SIO_SET_DATA  1
#घोषणा KL5KUSB105A_SIO_POLL      2
#घोषणा KL5KUSB105A_SIO_CONFIGURE      3
/* values used क्रम request KL5KUSB105A_SIO_CONFIGURE */
#घोषणा KL5KUSB105A_SIO_CONFIGURE_READ_ON      3
#घोषणा KL5KUSB105A_SIO_CONFIGURE_READ_OFF     2

/* Interpretation of modem status lines */
/* These need sorting out by inभागidually connecting pins and checking
 * results. FIXME!
 * When data is being sent we see 0x30 in the lower byte; this must
 * contain DSR and CTS ...
 */
#घोषणा KL5KUSB105A_DSR			((1<<4) | (1<<5))
#घोषणा KL5KUSB105A_CTS			((1<<5) | (1<<4))

#घोषणा KL5KUSB105A_WANTS_TO_SEND	0x30
#अगर 0
#घोषणा KL5KUSB105A_DTR			/* Data Terminal Ready */
#घोषणा KL5KUSB105A_CTS			/* Clear To Send */
#घोषणा KL5KUSB105A_CD			/* Carrier Detect */
#घोषणा KL5KUSB105A_DSR			/* Data Set Ready */
#घोषणा KL5KUSB105A_RxD			/* Receive pin */

#घोषणा KL5KUSB105A_LE
#घोषणा KL5KUSB105A_RTS
#घोषणा KL5KUSB105A_ST
#घोषणा KL5KUSB105A_SR
#घोषणा KL5KUSB105A_RI			/* Ring Indicator */
#पूर्ण_अगर
