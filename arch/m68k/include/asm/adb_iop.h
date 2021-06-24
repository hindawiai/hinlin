<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * ADB through the IOP
 * Written by Joshua M. Thompson
 */

/* IOP number and channel number क्रम ADB */

#घोषणा ADB_IOP		IOP_NUM_ISM
#घोषणा ADB_CHAN	2

/* From the A/UX headers...maybe important, maybe not */

#घोषणा ADB_IOP_LISTEN	0x01
#घोषणा ADB_IOP_TALK	0x02
#घोषणा ADB_IOP_EXISTS	0x04
#घोषणा ADB_IOP_FLUSH	0x08
#घोषणा ADB_IOP_RESET	0x10
#घोषणा ADB_IOP_INT	0x20
#घोषणा ADB_IOP_POLL	0x40
#घोषणा ADB_IOP_UNINT	0x80

#घोषणा AIF_RESET	0x00
#घोषणा AIF_FLUSH	0x01
#घोषणा AIF_LISTEN	0x08
#घोषणा AIF_TALK	0x0C

/* Flag bits in काष्ठा adb_iopmsg */

#घोषणा ADB_IOP_EXPLICIT	0x80	/* nonzero अगर explicit command */
#घोषणा ADB_IOP_AUTOPOLL	0x40	/* स्वतः/SRQ polling enabled    */
#घोषणा ADB_IOP_SET_AUTOPOLL	0x20	/* set स्वतःpoll device list    */
#घोषणा ADB_IOP_SRQ		0x04	/* SRQ detected                */
#घोषणा ADB_IOP_TIMEOUT		0x02	/* nonzero अगर समयout          */

#अगर_अघोषित __ASSEMBLY__

काष्ठा adb_iopmsg अणु
	__u8 flags;		/* ADB flags         */
	__u8 count;		/* no. of data bytes */
	__u8 cmd;		/* ADB command       */
	__u8 data[8];		/* ADB data          */
	__u8 spare[21];		/* spare             */
पूर्ण;

#पूर्ण_अगर /* __ASSEMBLY__ */
