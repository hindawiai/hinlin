<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*****************************************************************************/

/*
 *	yam.h  -- YAM radio modem driver.
 *
 *	Copyright (C) 1998 Frederic Rible F1OAT (frible@teaser.fr)
 *	Adapted from baycom.c driver written by Thomas Sailer (sailer@अगरe.ee.ethz.ch)
 *
 *  Please note that the GPL allows you to use the driver, NOT the radio.
 *  In order to use the radio, you need a license from the communications
 *  authority of your country.
 */

/*****************************************************************************/

#घोषणा SIOCYAMRESERVED	(0)
#घोषणा SIOCYAMSCFG 	(1)	/* Set configuration */
#घोषणा SIOCYAMGCFG 	(2)	/* Get configuration */
#घोषणा SIOCYAMSMCS 	(3)	/* Set mcs data */

#घोषणा YAM_IOBASE   (1 << 0)
#घोषणा YAM_IRQ      (1 << 1)
#घोषणा YAM_BITRATE  (1 << 2) /* Bit rate of radio port ->57600 */
#घोषणा YAM_MODE     (1 << 3) /* 0=simplex 1=duplex 2=duplex+tempo */
#घोषणा YAM_HOLDDLY  (1 << 4) /* duplex tempo (sec) */
#घोषणा YAM_TXDELAY  (1 << 5) /* Tx Delay (ms) */
#घोषणा YAM_TXTAIL   (1 << 6) /* Tx Tail  (ms) */
#घोषणा YAM_PERSIST  (1 << 7) /* Persist  (ms) */
#घोषणा YAM_SLOTTIME (1 << 8) /* Slotसमय (ms) */
#घोषणा YAM_BAUDRATE (1 << 9) /* Baud rate of rs232 port ->115200 */

#घोषणा YAM_MAXBITRATE  57600
#घोषणा YAM_MAXBAUDRATE 115200
#घोषणा YAM_MAXMODE     2
#घोषणा YAM_MAXHOLDDLY  99
#घोषणा YAM_MAXTXDELAY  999
#घोषणा YAM_MAXTXTAIL   999
#घोषणा YAM_MAXPERSIST  255
#घोषणा YAM_MAXSLOTTIME 999

#घोषणा YAM_FPGA_SIZE	5302

काष्ठा yamcfg अणु
	अचिन्हित पूर्णांक mask;		/* Mask of commands */
	अचिन्हित पूर्णांक iobase;	/* IO Base of COM port */
	अचिन्हित पूर्णांक irq;		/* IRQ of COM port */
	अचिन्हित पूर्णांक bitrate;	/* Bit rate of radio port */
	अचिन्हित पूर्णांक baudrate;	/* Baud rate of the RS232 port */
	अचिन्हित पूर्णांक txdelay;	/* TxDelay */
	अचिन्हित पूर्णांक txtail;	/* TxTail */
	अचिन्हित पूर्णांक persist;	/* Persistence */
	अचिन्हित पूर्णांक slotसमय;	/* Slotसमय */
	अचिन्हित पूर्णांक mode;		/* mode 0 (simp), 1(Dupl), 2(Dupl+delay) */
	अचिन्हित पूर्णांक holddly;	/* PTT delay in FullDuplex 2 mode */
पूर्ण;

काष्ठा yamdrv_ioctl_cfg अणु
	पूर्णांक cmd;
	काष्ठा yamcfg cfg;
पूर्ण;

काष्ठा yamdrv_ioctl_mcs अणु
	पूर्णांक cmd;
	अचिन्हित पूर्णांक bitrate;
	अचिन्हित अक्षर bits[YAM_FPGA_SIZE];
पूर्ण;
