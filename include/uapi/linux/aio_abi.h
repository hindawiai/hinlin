<शैली गुरु>
/* include/linux/aio_abi.h
 *
 * Copyright 2000,2001,2002 Red Hat.
 *
 * Written by Benjamin LaHaise <bcrl@kvack.org>
 *
 * Distribute under the terms of the GPLv2 (see ../../COPYING) or under 
 * the following terms.
 *
 * Permission to use, copy, modअगरy, and distribute this software and its
 * करोcumentation is hereby granted, provided that the above copyright
 * notice appears in all copies.  This software is provided without any
 * warranty, express or implied.  Red Hat makes no representations about
 * the suitability of this software क्रम any purpose.
 *
 * IN NO EVENT SHALL RED HAT BE LIABLE TO ANY PARTY FOR सूचीECT, INसूचीECT,
 * SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT OF THE USE OF
 * THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF RED HAT HAS BEEN ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * RED HAT DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND
 * RED HAT HAS NO OBLIGATION TO PROVIDE MAINTEन_अंकCE, SUPPORT, UPDATES,
 * ENHANCEMENTS, OR MODIFICATIONS.
 */
#अगर_अघोषित __LINUX__AIO_ABI_H
#घोषणा __LINUX__AIO_ABI_H

#समावेश <linux/types.h>
#समावेश <linux/fs.h>
#समावेश <यंत्र/byteorder.h>

प्रकार __kernel_uदीर्घ_t aio_context_t;

क्रमागत अणु
	IOCB_CMD_PREAD = 0,
	IOCB_CMD_PWRITE = 1,
	IOCB_CMD_FSYNC = 2,
	IOCB_CMD_FDSYNC = 3,
	/* 4 was the experimental IOCB_CMD_PREADX */
	IOCB_CMD_POLL = 5,
	IOCB_CMD_NOOP = 6,
	IOCB_CMD_PREADV = 7,
	IOCB_CMD_PWRITEV = 8,
पूर्ण;

/*
 * Valid flags क्रम the "aio_flags" member of the "struct iocb".
 *
 * IOCB_FLAG_RESFD - Set अगर the "aio_resfd" member of the "struct iocb"
 *                   is valid.
 * IOCB_FLAG_IOPRIO - Set अगर the "aio_reqprio" member of the "struct iocb"
 *                    is valid.
 */
#घोषणा IOCB_FLAG_RESFD		(1 << 0)
#घोषणा IOCB_FLAG_IOPRIO	(1 << 1)

/* पढ़ो() from /dev/aio वापसs these काष्ठाures. */
काष्ठा io_event अणु
	__u64		data;		/* the data field from the iocb */
	__u64		obj;		/* what iocb this event came from */
	__s64		res;		/* result code क्रम this event */
	__s64		res2;		/* secondary result */
पूर्ण;

/*
 * we always use a 64bit off_t when communicating
 * with userland.  its up to libraries to करो the
 * proper padding and aio_error असलtraction
 */

काष्ठा iocb अणु
	/* these are पूर्णांकernal to the kernel/libc. */
	__u64	aio_data;	/* data to be वापसed in event's data */

#अगर defined(__BYTE_ORDER) ? __BYTE_ORDER == __LITTLE_ENDIAN : defined(__LITTLE_ENDIAN)
	__u32	aio_key;	/* the kernel sets aio_key to the req # */
	__kernel_rwf_t aio_rw_flags;	/* RWF_* flags */
#या_अगर defined(__BYTE_ORDER) ? __BYTE_ORDER == __BIG_ENDIAN : defined(__BIG_ENDIAN)
	__kernel_rwf_t aio_rw_flags;	/* RWF_* flags */
	__u32	aio_key;	/* the kernel sets aio_key to the req # */
#अन्यथा
#त्रुटि edit क्रम your odd byteorder.
#पूर्ण_अगर

	/* common fields */
	__u16	aio_lio_opcode;	/* see IOCB_CMD_ above */
	__s16	aio_reqprio;
	__u32	aio_fildes;

	__u64	aio_buf;
	__u64	aio_nbytes;
	__s64	aio_offset;

	/* extra parameters */
	__u64	aio_reserved2;	/* TODO: use this क्रम a (काष्ठा sigevent *) */

	/* flags क्रम the "struct iocb" */
	__u32	aio_flags;

	/*
	 * अगर the IOCB_FLAG_RESFD flag of "aio_flags" is set, this is an
	 * eventfd to संकेत AIO पढ़ोiness to
	 */
	__u32	aio_resfd;
पूर्ण; /* 64 bytes */

#अघोषित IFBIG
#अघोषित IFLITTLE

#पूर्ण_अगर /* __LINUX__AIO_ABI_H */

