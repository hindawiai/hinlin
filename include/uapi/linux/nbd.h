<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-1.0+ WITH Linux-syscall-note */
/*
 * 1999 Copyright (C) Pavel Machek, pavel@ucw.cz. This code is GPL.
 * 1999/11/04 Copyright (C) 1999 VMware, Inc. (Regis "HPReg" Duchesne)
 *            Made nbd_end_request() use the io_request_lock
 * 2001 Copyright (C) Steven Whitehouse
 *            New nbd_end_request() क्रम compatibility with new linux block
 *            layer code.
 * 2003/06/24 Louis D. Langholtz <ldl@aros.net>
 *            Removed unneeded blksize_bits field from nbd_device काष्ठा.
 *            Cleanup PARANOIA usage & code.
 * 2004/02/19 Paul Clements
 *            Removed PARANOIA, plus various cleanup and comments
 */

#अगर_अघोषित _UAPILINUX_NBD_H
#घोषणा _UAPILINUX_NBD_H

#समावेश <linux/types.h>

#घोषणा NBD_SET_SOCK	_IO( 0xab, 0 )
#घोषणा NBD_SET_BLKSIZE	_IO( 0xab, 1 )
#घोषणा NBD_SET_SIZE	_IO( 0xab, 2 )
#घोषणा NBD_DO_IT	_IO( 0xab, 3 )
#घोषणा NBD_CLEAR_SOCK	_IO( 0xab, 4 )
#घोषणा NBD_CLEAR_QUE	_IO( 0xab, 5 )
#घोषणा NBD_PRINT_DEBUG	_IO( 0xab, 6 )
#घोषणा NBD_SET_SIZE_BLOCKS	_IO( 0xab, 7 )
#घोषणा NBD_DISCONNECT  _IO( 0xab, 8 )
#घोषणा NBD_SET_TIMEOUT _IO( 0xab, 9 )
#घोषणा NBD_SET_FLAGS   _IO( 0xab, 10)

क्रमागत अणु
	NBD_CMD_READ = 0,
	NBD_CMD_WRITE = 1,
	NBD_CMD_DISC = 2,
	NBD_CMD_FLUSH = 3,
	NBD_CMD_TRIM = 4
पूर्ण;

/* values क्रम flags field, these are server पूर्णांकeraction specअगरic. */
#घोषणा NBD_FLAG_HAS_FLAGS	(1 << 0) /* nbd-server supports flags */
#घोषणा NBD_FLAG_READ_ONLY	(1 << 1) /* device is पढ़ो-only */
#घोषणा NBD_FLAG_SEND_FLUSH	(1 << 2) /* can flush ग_लिखोback cache */
#घोषणा NBD_FLAG_SEND_FUA	(1 << 3) /* send FUA (क्रमced unit access) */
/* there is a gap here to match userspace */
#घोषणा NBD_FLAG_SEND_TRIM	(1 << 5) /* send trim/discard */
#घोषणा NBD_FLAG_CAN_MULTI_CONN	(1 << 8)	/* Server supports multiple connections per export. */

/* values क्रम cmd flags in the upper 16 bits of request type */
#घोषणा NBD_CMD_FLAG_FUA	(1 << 16) /* FUA (क्रमced unit access) op */

/* These are client behavior specअगरic flags. */
#घोषणा NBD_CFLAG_DESTROY_ON_DISCONNECT	(1 << 0) /* delete the nbd device on
						    disconnect. */
#घोषणा NBD_CFLAG_DISCONNECT_ON_CLOSE (1 << 1) /* disconnect the nbd device on
						*  बंद by last खोलोer.
						*/

/* userspace करोesn't need the nbd_device काष्ठाure */

/* These are sent over the network in the request/reply magic fields */

#घोषणा NBD_REQUEST_MAGIC 0x25609513
#घोषणा NBD_REPLY_MAGIC 0x67446698
/* Do *not* use magics: 0x12560953 0x96744668. */

/*
 * This is the packet used क्रम communication between client and
 * server. All data are in network byte order.
 */
काष्ठा nbd_request अणु
	__be32 magic;
	__be32 type;	/* == READ || == WRITE 	*/
	अक्षर handle[8];
	__be64 from;
	__be32 len;
पूर्ण __attribute__((packed));

/*
 * This is the reply packet that nbd-server sends back to the client after
 * it has completed an I/O request (or an error occurs).
 */
काष्ठा nbd_reply अणु
	__be32 magic;
	__be32 error;		/* 0 = ok, अन्यथा error	*/
	अक्षर handle[8];		/* handle you got from request	*/
पूर्ण;
#पूर्ण_अगर /* _UAPILINUX_NBD_H */
