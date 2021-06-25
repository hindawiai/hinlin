<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _ASM_GENERIC_ERRNO_H
#घोषणा _ASM_GENERIC_ERRNO_H

#समावेश <यंत्र-generic/त्रुटि_सं-base.h>

#घोषणा	EDEADLK		35	/* Resource deadlock would occur */
#घोषणा	ENAMETOOLONG	36	/* File name too दीर्घ */
#घोषणा	ENOLCK		37	/* No record locks available */

/*
 * This error code is special: arch syscall entry code will वापस
 * -ENOSYS अगर users try to call a syscall that करोesn't exist.  To keep
 * failures of syscalls that really करो exist distinguishable from
 * failures due to attempts to use a nonexistent syscall, syscall
 * implementations should refrain from वापसing -ENOSYS.
 */
#घोषणा	ENOSYS		38	/* Invalid प्रणाली call number */

#घोषणा	ENOTEMPTY	39	/* Directory not empty */
#घोषणा	ELOOP		40	/* Too many symbolic links encountered */
#घोषणा	EWOULDBLOCK	EAGAIN	/* Operation would block */
#घोषणा	ENOMSG		42	/* No message of desired type */
#घोषणा	EIDRM		43	/* Identअगरier हटाओd */
#घोषणा	ECHRNG		44	/* Channel number out of range */
#घोषणा	EL2NSYNC	45	/* Level 2 not synchronized */
#घोषणा	EL3HLT		46	/* Level 3 halted */
#घोषणा	EL3RST		47	/* Level 3 reset */
#घोषणा	ELNRNG		48	/* Link number out of range */
#घोषणा	EUNATCH		49	/* Protocol driver not attached */
#घोषणा	ENOCSI		50	/* No CSI काष्ठाure available */
#घोषणा	EL2HLT		51	/* Level 2 halted */
#घोषणा	EBADE		52	/* Invalid exchange */
#घोषणा	EBADR		53	/* Invalid request descriptor */
#घोषणा	EXFULL		54	/* Exchange full */
#घोषणा	ENOANO		55	/* No anode */
#घोषणा	EBADRQC		56	/* Invalid request code */
#घोषणा	EBADSLT		57	/* Invalid slot */

#घोषणा	EDEADLOCK	EDEADLK

#घोषणा	EBFONT		59	/* Bad font file क्रमmat */
#घोषणा	ENOSTR		60	/* Device not a stream */
#घोषणा	ENODATA		61	/* No data available */
#घोषणा	ETIME		62	/* Timer expired */
#घोषणा	ENOSR		63	/* Out of streams resources */
#घोषणा	ENONET		64	/* Machine is not on the network */
#घोषणा	ENOPKG		65	/* Package not installed */
#घोषणा	EREMOTE		66	/* Object is remote */
#घोषणा	ENOLINK		67	/* Link has been severed */
#घोषणा	EADV		68	/* Advertise error */
#घोषणा	ESRMNT		69	/* Srmount error */
#घोषणा	ECOMM		70	/* Communication error on send */
#घोषणा	EPROTO		71	/* Protocol error */
#घोषणा	EMULTIHOP	72	/* Multihop attempted */
#घोषणा	EDOTDOT		73	/* RFS specअगरic error */
#घोषणा	EBADMSG		74	/* Not a data message */
#घोषणा	EOVERFLOW	75	/* Value too large क्रम defined data type */
#घोषणा	ENOTUNIQ	76	/* Name not unique on network */
#घोषणा	EBADFD		77	/* File descriptor in bad state */
#घोषणा	EREMCHG		78	/* Remote address changed */
#घोषणा	ELIBACC		79	/* Can not access a needed shared library */
#घोषणा	ELIBBAD		80	/* Accessing a corrupted shared library */
#घोषणा	ELIBSCN		81	/* .lib section in a.out corrupted */
#घोषणा	ELIBMAX		82	/* Attempting to link in too many shared libraries */
#घोषणा	ELIBEXEC	83	/* Cannot exec a shared library directly */
#घोषणा	EILSEQ		84	/* Illegal byte sequence */
#घोषणा	ERESTART	85	/* Interrupted प्रणाली call should be restarted */
#घोषणा	ESTRPIPE	86	/* Streams pipe error */
#घोषणा	EUSERS		87	/* Too many users */
#घोषणा	ENOTSOCK	88	/* Socket operation on non-socket */
#घोषणा	EDESTADDRREQ	89	/* Destination address required */
#घोषणा	EMSGSIZE	90	/* Message too दीर्घ */
#घोषणा	EPROTOTYPE	91	/* Protocol wrong type क्रम socket */
#घोषणा	ENOPROTOOPT	92	/* Protocol not available */
#घोषणा	EPROTONOSUPPORT	93	/* Protocol not supported */
#घोषणा	ESOCKTNOSUPPORT	94	/* Socket type not supported */
#घोषणा	EOPNOTSUPP	95	/* Operation not supported on transport endpoपूर्णांक */
#घोषणा	EPFNOSUPPORT	96	/* Protocol family not supported */
#घोषणा	EAFNOSUPPORT	97	/* Address family not supported by protocol */
#घोषणा	EADDRINUSE	98	/* Address alपढ़ोy in use */
#घोषणा	EADDRNOTAVAIL	99	/* Cannot assign requested address */
#घोषणा	ENETDOWN	100	/* Network is करोwn */
#घोषणा	ENETUNREACH	101	/* Network is unreachable */
#घोषणा	ENETRESET	102	/* Network dropped connection because of reset */
#घोषणा	ECONNABORTED	103	/* Software caused connection पात */
#घोषणा	ECONNRESET	104	/* Connection reset by peer */
#घोषणा	ENOBUFS		105	/* No buffer space available */
#घोषणा	EISCONN		106	/* Transport endpoपूर्णांक is alपढ़ोy connected */
#घोषणा	ENOTCONN	107	/* Transport endpoपूर्णांक is not connected */
#घोषणा	ESHUTDOWN	108	/* Cannot send after transport endpoपूर्णांक shutकरोwn */
#घोषणा	ETOOMANYREFS	109	/* Too many references: cannot splice */
#घोषणा	ETIMEDOUT	110	/* Connection समयd out */
#घोषणा	ECONNREFUSED	111	/* Connection refused */
#घोषणा	EHOSTDOWN	112	/* Host is करोwn */
#घोषणा	EHOSTUNREACH	113	/* No route to host */
#घोषणा	EALREADY	114	/* Operation alपढ़ोy in progress */
#घोषणा	EINPROGRESS	115	/* Operation now in progress */
#घोषणा	ESTALE		116	/* Stale file handle */
#घोषणा	EUCLEAN		117	/* Structure needs cleaning */
#घोषणा	ENOTNAM		118	/* Not a XENIX named type file */
#घोषणा	ENAVAIL		119	/* No XENIX semaphores available */
#घोषणा	EISNAM		120	/* Is a named type file */
#घोषणा	EREMOTEIO	121	/* Remote I/O error */
#घोषणा	EDQUOT		122	/* Quota exceeded */

#घोषणा	ENOMEDIUM	123	/* No medium found */
#घोषणा	EMEDIUMTYPE	124	/* Wrong medium type */
#घोषणा	ECANCELED	125	/* Operation Canceled */
#घोषणा	ENOKEY		126	/* Required key not available */
#घोषणा	EKEYEXPIRED	127	/* Key has expired */
#घोषणा	EKEYREVOKED	128	/* Key has been revoked */
#घोषणा	EKEYREJECTED	129	/* Key was rejected by service */

/* क्रम robust mutexes */
#घोषणा	EOWNERDEAD	130	/* Owner died */
#घोषणा	ENOTRECOVERABLE	131	/* State not recoverable */

#घोषणा ERFKILL		132	/* Operation not possible due to RF-समाप्त */

#घोषणा EHWPOISON	133	/* Memory page has hardware error */

#पूर्ण_अगर
