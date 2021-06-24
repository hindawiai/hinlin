<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * include/linux/अक्रमom.h
 *
 * Include file क्रम the अक्रमom number generator.
 */

#अगर_अघोषित _UAPI_LINUX_RANDOM_H
#घोषणा _UAPI_LINUX_RANDOM_H

#समावेश <linux/types.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/irqnr.h>

/* ioctl()'s क्रम the अक्रमom number generator */

/* Get the entropy count. */
#घोषणा RNDGETENTCNT	_IOR( 'R', 0x00, पूर्णांक )

/* Add to (or subtract from) the entropy count.  (Superuser only.) */
#घोषणा RNDADDTOENTCNT	_IOW( 'R', 0x01, पूर्णांक )

/* Get the contents of the entropy pool.  (Superuser only.) */
#घोषणा RNDGETPOOL	_IOR( 'R', 0x02, पूर्णांक [2] )

/* 
 * Write bytes पूर्णांकo the entropy pool and add to the entropy count.
 * (Superuser only.)
 */
#घोषणा RNDADDENTROPY	_IOW( 'R', 0x03, पूर्णांक [2] )

/* Clear entropy count to 0.  (Superuser only.) */
#घोषणा RNDZAPENTCNT	_IO( 'R', 0x04 )

/* Clear the entropy pool and associated counters.  (Superuser only.) */
#घोषणा RNDCLEARPOOL	_IO( 'R', 0x06 )

/* Reseed CRNG.  (Superuser only.) */
#घोषणा RNDRESEEDCRNG	_IO( 'R', 0x07 )

काष्ठा अक्रम_pool_info अणु
	पूर्णांक	entropy_count;
	पूर्णांक	buf_size;
	__u32	buf[0];
पूर्ण;

/*
 * Flags क्रम getअक्रमom(2)
 *
 * GRND_NONBLOCK	Don't block and वापस EAGAIN instead
 * GRND_RANDOM		No effect
 * GRND_INSECURE	Return non-cryptographic अक्रमom bytes
 */
#घोषणा GRND_NONBLOCK	0x0001
#घोषणा GRND_RANDOM	0x0002
#घोषणा GRND_INSECURE	0x0004

#पूर्ण_अगर /* _UAPI_LINUX_RANDOM_H */
