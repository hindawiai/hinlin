<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Definitions क्रम ADB (Apple Desktop Bus) support.
 */
#अगर_अघोषित _UAPI__ADB_H
#घोषणा _UAPI__ADB_H

/* ADB commands */
#घोषणा ADB_BUSRESET		0
#घोषणा ADB_FLUSH(id)		(0x01 | ((id) << 4))
#घोषणा ADB_WRITEREG(id, reg)	(0x08 | (reg) | ((id) << 4))
#घोषणा ADB_READREG(id, reg)	(0x0C | (reg) | ((id) << 4))

/* ADB शेष device IDs (upper 4 bits of ADB command byte) */
#घोषणा ADB_DONGLE	1	/* "software execution control" devices */
#घोषणा ADB_KEYBOARD	2
#घोषणा ADB_MOUSE	3
#घोषणा ADB_TABLET	4
#घोषणा ADB_MODEM	5
#घोषणा ADB_MISC	7	/* maybe a monitor */

#घोषणा ADB_RET_OK	0
#घोषणा ADB_RET_TIMEOUT	3

/* The kind of ADB request. The controller may emulate some
   or all of those CUDA/PMU packet kinds */
#घोषणा ADB_PACKET	0
#घोषणा CUDA_PACKET	1
#घोषणा ERROR_PACKET	2
#घोषणा TIMER_PACKET	3
#घोषणा POWER_PACKET	4
#घोषणा MACIIC_PACKET	5
#घोषणा PMU_PACKET	6
#घोषणा ADB_QUERY	7

/* ADB queries */

/* ADB_QUERY_GETDEVINFO
 * Query ADB slot क्रम device presence
 * data[2] = id, rep[0] = orig addr, rep[1] = handler_id
 */
#घोषणा ADB_QUERY_GETDEVINFO	1


#पूर्ण_अगर /* _UAPI__ADB_H */
