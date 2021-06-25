<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _SPARC_ERRNO_H
#घोषणा _SPARC_ERRNO_H

/* These match the SunOS error numbering scheme. */

#समावेश <यंत्र-generic/त्रुटि_सं-base.h>

#घोषणा	EWOULDBLOCK	EAGAIN	/* Operation would block */
#घोषणा	EINPROGRESS	36	/* Operation now in progress */
#घोषणा	EALREADY	37	/* Operation alपढ़ोy in progress */
#घोषणा	ENOTSOCK	38	/* Socket operation on non-socket */
#घोषणा	EDESTADDRREQ	39	/* Destination address required */
#घोषणा	EMSGSIZE	40	/* Message too दीर्घ */
#घोषणा	EPROTOTYPE	41	/* Protocol wrong type क्रम socket */
#घोषणा	ENOPROTOOPT	42	/* Protocol not available */
#घोषणा	EPROTONOSUPPORT	43	/* Protocol not supported */
#घोषणा	ESOCKTNOSUPPORT	44	/* Socket type not supported */
#घोषणा	EOPNOTSUPP	45	/* Op not supported on transport endpoपूर्णांक */
#घोषणा	EPFNOSUPPORT	46	/* Protocol family not supported */
#घोषणा	EAFNOSUPPORT	47	/* Address family not supported by protocol */
#घोषणा	EADDRINUSE	48	/* Address alपढ़ोy in use */
#घोषणा	EADDRNOTAVAIL	49	/* Cannot assign requested address */
#घोषणा	ENETDOWN	50	/* Network is करोwn */
#घोषणा	ENETUNREACH	51	/* Network is unreachable */
#घोषणा	ENETRESET	52	/* Net dropped connection because of reset */
#घोषणा	ECONNABORTED	53	/* Software caused connection पात */
#घोषणा	ECONNRESET	54	/* Connection reset by peer */
#घोषणा	ENOBUFS		55	/* No buffer space available */
#घोषणा	EISCONN		56	/* Transport endpoपूर्णांक is alपढ़ोy connected */
#घोषणा	ENOTCONN	57	/* Transport endpoपूर्णांक is not connected */
#घोषणा	ESHUTDOWN	58	/* No send after transport endpoपूर्णांक shutकरोwn */
#घोषणा	ETOOMANYREFS	59	/* Too many references: cannot splice */
#घोषणा	ETIMEDOUT	60	/* Connection समयd out */
#घोषणा	ECONNREFUSED	61	/* Connection refused */
#घोषणा	ELOOP		62	/* Too many symbolic links encountered */
#घोषणा	ENAMETOOLONG	63	/* File name too दीर्घ */
#घोषणा	EHOSTDOWN	64	/* Host is करोwn */
#घोषणा	EHOSTUNREACH	65	/* No route to host */
#घोषणा	ENOTEMPTY	66	/* Directory not empty */
#घोषणा EPROCLIM        67      /* SUNOS: Too many processes */
#घोषणा	EUSERS		68	/* Too many users */
#घोषणा	EDQUOT		69	/* Quota exceeded */
#घोषणा	ESTALE		70	/* Stale file handle */
#घोषणा	EREMOTE		71	/* Object is remote */
#घोषणा	ENOSTR		72	/* Device not a stream */
#घोषणा	ETIME		73	/* Timer expired */
#घोषणा	ENOSR		74	/* Out of streams resources */
#घोषणा	ENOMSG		75	/* No message of desired type */
#घोषणा	EBADMSG		76	/* Not a data message */
#घोषणा	EIDRM		77	/* Identअगरier हटाओd */
#घोषणा	EDEADLK		78	/* Resource deadlock would occur */
#घोषणा	ENOLCK		79	/* No record locks available */
#घोषणा	ENONET		80	/* Machine is not on the network */
#घोषणा ERREMOTE        81      /* SunOS: Too many lvls of remote in path */
#घोषणा	ENOLINK		82	/* Link has been severed */
#घोषणा	EADV		83	/* Advertise error */
#घोषणा	ESRMNT		84	/* Srmount error */
#घोषणा	ECOMM		85      /* Communication error on send */
#घोषणा	EPROTO		86	/* Protocol error */
#घोषणा	EMULTIHOP	87	/* Multihop attempted */
#घोषणा	EDOTDOT		88	/* RFS specअगरic error */
#घोषणा	EREMCHG		89	/* Remote address changed */
#घोषणा	ENOSYS		90	/* Function not implemented */

/* The rest have no SunOS equivalent. */
#घोषणा	ESTRPIPE	91	/* Streams pipe error */
#घोषणा	EOVERFLOW	92	/* Value too large क्रम defined data type */
#घोषणा	EBADFD		93	/* File descriptor in bad state */
#घोषणा	ECHRNG		94	/* Channel number out of range */
#घोषणा	EL2NSYNC	95	/* Level 2 not synchronized */
#घोषणा	EL3HLT		96	/* Level 3 halted */
#घोषणा	EL3RST		97	/* Level 3 reset */
#घोषणा	ELNRNG		98	/* Link number out of range */
#घोषणा	EUNATCH		99	/* Protocol driver not attached */
#घोषणा	ENOCSI		100	/* No CSI काष्ठाure available */
#घोषणा	EL2HLT		101	/* Level 2 halted */
#घोषणा	EBADE		102	/* Invalid exchange */
#घोषणा	EBADR		103	/* Invalid request descriptor */
#घोषणा	EXFULL		104	/* Exchange full */
#घोषणा	ENOANO		105	/* No anode */
#घोषणा	EBADRQC		106	/* Invalid request code */
#घोषणा	EBADSLT		107	/* Invalid slot */
#घोषणा	EDEADLOCK	108	/* File locking deadlock error */
#घोषणा	EBFONT		109	/* Bad font file क्रमmat */
#घोषणा	ELIBEXEC	110	/* Cannot exec a shared library directly */
#घोषणा	ENODATA		111	/* No data available */
#घोषणा	ELIBBAD		112	/* Accessing a corrupted shared library */
#घोषणा	ENOPKG		113	/* Package not installed */
#घोषणा	ELIBACC		114	/* Can not access a needed shared library */
#घोषणा	ENOTUNIQ	115	/* Name not unique on network */
#घोषणा	ERESTART	116	/* Interrupted syscall should be restarted */
#घोषणा	EUCLEAN		117	/* Structure needs cleaning */
#घोषणा	ENOTNAM		118	/* Not a XENIX named type file */
#घोषणा	ENAVAIL		119	/* No XENIX semaphores available */
#घोषणा	EISNAM		120	/* Is a named type file */
#घोषणा	EREMOTEIO	121	/* Remote I/O error */
#घोषणा	EILSEQ		122	/* Illegal byte sequence */
#घोषणा	ELIBMAX		123	/* Aपंचांगpt to link in too many shared libs */
#घोषणा	ELIBSCN		124	/* .lib section in a.out corrupted */

#घोषणा	ENOMEDIUM	125	/* No medium found */
#घोषणा	EMEDIUMTYPE	126	/* Wrong medium type */
#घोषणा	ECANCELED	127	/* Operation Cancelled */
#घोषणा	ENOKEY		128	/* Required key not available */
#घोषणा	EKEYEXPIRED	129	/* Key has expired */
#घोषणा	EKEYREVOKED	130	/* Key has been revoked */
#घोषणा	EKEYREJECTED	131	/* Key was rejected by service */

/* क्रम robust mutexes */
#घोषणा	EOWNERDEAD	132	/* Owner died */
#घोषणा	ENOTRECOVERABLE	133	/* State not recoverable */

#घोषणा	ERFKILL		134	/* Operation not possible due to RF-समाप्त */

#घोषणा EHWPOISON	135	/* Memory page has hardware error */

#पूर्ण_अगर
