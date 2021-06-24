<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* $Id: cosa.h,v 1.6 1999/01/06 14:02:44 kas Exp $ */

/*
 *  Copyright (C) 1995-1997  Jan "Yenya" Kasprzak <kas@fi.muni.cz>
 */

#अगर_अघोषित COSA_H__
#घोषणा COSA_H__

#समावेश <linux/ioctl.h>

#अगर_घोषित __KERNEL__
/* status रेजिस्टर - output bits */
#घोषणा SR_RX_DMA_ENA   0x04    /* receiver DMA enable bit */
#घोषणा SR_TX_DMA_ENA   0x08    /* transmitter DMA enable bit */
#घोषणा SR_RST          0x10    /* SRP reset */
#घोषणा SR_USR_INT_ENA  0x20    /* user पूर्णांकerrupt enable bit */
#घोषणा SR_TX_INT_ENA   0x40    /* transmitter पूर्णांकerrupt enable bit */
#घोषणा SR_RX_INT_ENA   0x80    /* receiver पूर्णांकerrupt enable bit */

/* status रेजिस्टर - input bits */
#घोषणा SR_USR_RQ       0x20    /* user पूर्णांकerrupt request pending */
#घोषणा SR_TX_RDY       0x40    /* transmitter empty (पढ़ोy) */
#घोषणा SR_RX_RDY       0x80    /* receiver data पढ़ोy */

#घोषणा SR_UP_REQUEST   0x02    /* request from SRP to transfer data
                                   up to PC */
#घोषणा SR_DOWN_REQUEST 0x01    /* SRP is able to transfer data करोwn
                                   from PC to SRP */
#घोषणा SR_END_OF_TRANSFER      0x03    /* SRP संकेतize end of
                                           transfer (up or करोwn) */

#घोषणा SR_CMD_FROM_SRP_MASK    0x03    /* mask to get SRP command */

/* bits in driver status byte definitions : */
#घोषणा SR_RDY_RCV      0x01    /* पढ़ोy to receive packet */
#घोषणा SR_RDY_SND      0x02    /* पढ़ोy to send packet */
#घोषणा SR_CMD_PND      0x04    /* command pending */ /* not currently used */

/* ???? */
#घोषणा SR_PKT_UP       0x01    /* transfer of packet up in progress */
#घोषणा SR_PKT_DOWN     0x02    /* transfer of packet करोwn in progress */

#पूर्ण_अगर /* __KERNEL__ */

#घोषणा SR_LOAD_ADDR    0x4400  /* SRP microcode load address */
#घोषणा SR_START_ADDR   0x4400  /* SRP microcode start address */

#घोषणा COSA_LOAD_ADDR    0x400  /* SRP microcode load address */
#घोषणा COSA_MAX_FIRMWARE_SIZE	0x10000

/* ioctls */
काष्ठा cosa_करोwnload अणु
	पूर्णांक addr, len;
	अक्षर __user *code;
पूर्ण;

/* Reset the device */
#घोषणा COSAIORSET	_IO('C',0xf0)

/* Start microcode at given address */
#घोषणा COSAIOSTRT	_IOW('C',0xf1, पूर्णांक)

/* Read the block from the device memory */
#घोषणा COSAIORMEM	_IOWR('C',0xf2, काष्ठा cosa_करोwnload *)
	/* actually the काष्ठा cosa_करोwnload itself; this is to keep
	 * the ioctl number same as in 2.4 in order to keep the user-space
	 * utils compatible. */

/* Write the block to the device memory (i.e. करोwnload the microcode) */
#घोषणा COSAIODOWNLD	_IOW('C',0xf2, काष्ठा cosa_करोwnload *)
	/* actually the काष्ठा cosa_करोwnload itself; this is to keep
	 * the ioctl number same as in 2.4 in order to keep the user-space
	 * utils compatible. */

/* Read the device type (one of "srp", "cosa", and "cosa8" क्रम now) */
#घोषणा COSAIORTYPE	_IOR('C',0xf3, अक्षर *)

/* Read the device identअगरication string */
#घोषणा COSAIORIDSTR	_IOR('C',0xf4, अक्षर *)
/* Maximum length of the identअगरication string. */
#घोषणा COSA_MAX_ID_STRING 128

/* Increment/decrement the module usage count :-) */
/* #घोषणा COSAIOMINC	_IO('C',0xf5) */
/* #घोषणा COSAIOMDEC	_IO('C',0xf6) */

/* Get the total number of cards installed */
#घोषणा COSAIONRCARDS	_IO('C',0xf7)

/* Get the number of channels on this card */
#घोषणा COSAIONRCHANS	_IO('C',0xf8)

/* Set the driver क्रम the bus-master operations */
#घोषणा COSAIOBMSET	_IOW('C', 0xf9, अचिन्हित लघु)

#घोषणा COSA_BM_OFF	0	/* Bus-mastering off - use ISA DMA (शेष) */
#घोषणा COSA_BM_ON	1	/* Bus-mastering on - faster but untested */

/* Gets the busmaster status */
#घोषणा COSAIOBMGET	_IO('C', 0xfa)

#पूर्ण_अगर /* !COSA_H__ */
