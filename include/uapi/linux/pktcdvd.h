<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Copyright (C) 2000 Jens Axboe <axboe@suse.de>
 * Copyright (C) 2001-2004 Peter Osterlund <petero2@telia.com>
 *
 * May be copied or modअगरied under the terms of the GNU General Public
 * License.  See linux/COPYING क्रम more inक्रमmation.
 *
 * Packet writing layer क्रम ATAPI and SCSI CD-R, CD-RW, DVD-R, and
 * DVD-RW devices.
 *
 */
#अगर_अघोषित _UAPI__PKTCDVD_H
#घोषणा _UAPI__PKTCDVD_H

#समावेश <linux/types.h>

/*
 * 1 क्रम normal debug messages, 2 is very verbose. 0 to turn it off.
 */
#घोषणा PACKET_DEBUG		1

#घोषणा	MAX_WRITERS		8

#घोषणा PKT_RB_POOL_SIZE	512

/*
 * How दीर्घ we should hold a non-full packet beक्रमe starting data gathering.
 */
#घोषणा PACKET_WAIT_TIME	(HZ * 5 / 1000)

/*
 * use drive ग_लिखो caching -- we need deferred error handling to be
 * able to successfully recover with this option (drive will वापस good
 * status as soon as the cdb is validated).
 */
#अगर defined(CONFIG_CDROM_PKTCDVD_WCACHE)
#घोषणा USE_WCACHING		1
#अन्यथा
#घोषणा USE_WCACHING		0
#पूर्ण_अगर

/*
 * No user-servicable parts beyond this poपूर्णांक ->
 */

/*
 * device types
 */
#घोषणा PACKET_CDR		1
#घोषणा	PACKET_CDRW		2
#घोषणा PACKET_DVDR		3
#घोषणा PACKET_DVDRW		4

/*
 * flags
 */
#घोषणा PACKET_WRITABLE		1	/* pd is writable */
#घोषणा PACKET_NWA_VALID	2	/* next writable address valid */
#घोषणा PACKET_LRA_VALID	3	/* last recorded address valid */
#घोषणा PACKET_MERGE_SEGS	4	/* perक्रमm segment merging to keep */
					/* underlying cdrom device happy */

/*
 * Disc status -- from READ_DISC_INFO
 */
#घोषणा PACKET_DISC_EMPTY	0
#घोषणा PACKET_DISC_INCOMPLETE	1
#घोषणा PACKET_DISC_COMPLETE	2
#घोषणा PACKET_DISC_OTHER	3

/*
 * ग_लिखो type, and corresponding data block type
 */
#घोषणा PACKET_MODE1		1
#घोषणा PACKET_MODE2		2
#घोषणा PACKET_BLOCK_MODE1	8
#घोषणा PACKET_BLOCK_MODE2	10

/*
 * Last session/border status
 */
#घोषणा PACKET_SESSION_EMPTY		0
#घोषणा PACKET_SESSION_INCOMPLETE	1
#घोषणा PACKET_SESSION_RESERVED		2
#घोषणा PACKET_SESSION_COMPLETE		3

#घोषणा PACKET_MCN			"4a656e734178626f65323030300000"

#अघोषित PACKET_USE_LS

#घोषणा PKT_CTRL_CMD_SETUP	0
#घोषणा PKT_CTRL_CMD_TEARDOWN	1
#घोषणा PKT_CTRL_CMD_STATUS	2

काष्ठा pkt_ctrl_command अणु
	__u32 command;				/* in: Setup, tearकरोwn, status */
	__u32 dev_index;			/* in/out: Device index */
	__u32 dev;				/* in/out: Device nr क्रम cdrw device */
	__u32 pkt_dev;				/* in/out: Device nr क्रम packet device */
	__u32 num_devices;			/* out: Largest device index + 1 */
	__u32 padding;				/* Not used */
पूर्ण;

/*
 * packet ioctls
 */
#घोषणा PACKET_IOCTL_MAGIC	('X')
#घोषणा PACKET_CTRL_CMD		_IOWR(PACKET_IOCTL_MAGIC, 1, काष्ठा pkt_ctrl_command)


#पूर्ण_अगर /* _UAPI__PKTCDVD_H */
