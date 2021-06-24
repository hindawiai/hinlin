<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * hdlcdrv.h  -- HDLC packet radio network driver.
 * The Linux soundcard driver क्रम 1200 baud and 9600 baud packet radio
 * (C) 1996-1998 by Thomas Sailer, HB9JNX/AE4WA
 */

#अगर_अघोषित _UAPI_HDLCDRV_H
#घोषणा _UAPI_HDLCDRV_H

/* -------------------------------------------------------------------- */
/*
 * काष्ठाs क्रम the IOCTL commands
 */

काष्ठा hdlcdrv_params अणु
	पूर्णांक iobase;
	पूर्णांक irq;
	पूर्णांक dma;
	पूर्णांक dma2;
	पूर्णांक seriobase;
	पूर्णांक pariobase;
	पूर्णांक midiiobase;
पूर्ण;	

काष्ठा hdlcdrv_channel_params अणु
	पूर्णांक tx_delay;  /* the transmitter keyup delay in 10ms units */
	पूर्णांक tx_tail;   /* the transmitter keyoff delay in 10ms units */
	पूर्णांक slotसमय;  /* the slotसमय in 10ms; usually 10 = 100ms */
	पूर्णांक ppersist;  /* the p-persistence 0..255 */
	पूर्णांक fulldup;   /* some driver करो not support full duplex, setting */
	               /* this just makes them send even अगर DCD is on */
पूर्ण;	

काष्ठा hdlcdrv_old_channel_state अणु
  	पूर्णांक ptt;
  	पूर्णांक dcd;
  	पूर्णांक ptt_keyed;
पूर्ण;

काष्ठा hdlcdrv_channel_state अणु
 	पूर्णांक ptt;
 	पूर्णांक dcd;
 	पूर्णांक ptt_keyed;
 	अचिन्हित दीर्घ tx_packets;
 	अचिन्हित दीर्घ tx_errors;
 	अचिन्हित दीर्घ rx_packets;
 	अचिन्हित दीर्घ rx_errors;
पूर्ण;

काष्ठा hdlcdrv_ioctl अणु
	पूर्णांक cmd;
	जोड़ अणु
		काष्ठा hdlcdrv_params mp;
		काष्ठा hdlcdrv_channel_params cp;
		काष्ठा hdlcdrv_channel_state cs;
		काष्ठा hdlcdrv_old_channel_state ocs;
		अचिन्हित पूर्णांक calibrate;
		अचिन्हित अक्षर bits;
		अक्षर modename[128];
		अक्षर drivername[32];
	पूर्ण data;
पूर्ण;

/* -------------------------------------------------------------------- */

/*
 * ioctl values
 */
#घोषणा HDLCDRVCTL_GETMODEMPAR       0
#घोषणा HDLCDRVCTL_SETMODEMPAR       1
#घोषणा HDLCDRVCTL_MODEMPARMASK      2  /* not handled by hdlcdrv */
#घोषणा HDLCDRVCTL_GETCHANNELPAR    10
#घोषणा HDLCDRVCTL_SETCHANNELPAR    11
#घोषणा HDLCDRVCTL_OLDGETSTAT       20
#घोषणा HDLCDRVCTL_CALIBRATE        21
#घोषणा HDLCDRVCTL_GETSTAT          22

/*
 * these are मुख्यly क्रम debugging purposes
 */
#घोषणा HDLCDRVCTL_GETSAMPLES       30
#घोषणा HDLCDRVCTL_GETBITS          31

/*
 * not handled by hdlcdrv, but by its depending drivers
 */
#घोषणा HDLCDRVCTL_GETMODE          40
#घोषणा HDLCDRVCTL_SETMODE          41
#घोषणा HDLCDRVCTL_MODELIST         42
#घोषणा HDLCDRVCTL_DRIVERNAME       43

/*
 * mask of needed modem parameters, वापसed by HDLCDRVCTL_MODEMPARMASK
 */
#घोषणा HDLCDRV_PARMASK_IOBASE      (1<<0)
#घोषणा HDLCDRV_PARMASK_IRQ         (1<<1)
#घोषणा HDLCDRV_PARMASK_DMA         (1<<2)
#घोषणा HDLCDRV_PARMASK_DMA2        (1<<3)
#घोषणा HDLCDRV_PARMASK_SERIOBASE   (1<<4)
#घोषणा HDLCDRV_PARMASK_PARIOBASE   (1<<5)
#घोषणा HDLCDRV_PARMASK_MIDIIOBASE  (1<<6)

/* -------------------------------------------------------------------- */


/* -------------------------------------------------------------------- */

#पूर्ण_अगर /* _UAPI_HDLCDRV_H */

/* -------------------------------------------------------------------- */
