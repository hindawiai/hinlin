<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* miscellaneous bits
 *
 * Copyright (C) 2002, 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश "internal.h"
#समावेश "afs_fs.h"
#समावेश "protocol_uae.h"

/*
 * convert an AFS पात code to a Linux error number
 */
पूर्णांक afs_पात_to_error(u32 पात_code)
अणु
	चयन (पात_code) अणु
		/* Low त्रुटि_सं codes inserted पूर्णांकo पात namespace */
	हाल 13:		वापस -EACCES;
	हाल 27:		वापस -EFBIG;
	हाल 30:		वापस -EROFS;

		/* VICE "special error" codes; 101 - 111 */
	हाल VSALVAGE:		वापस -EIO;
	हाल VNOVNODE:		वापस -ENOENT;
	हाल VNOVOL:		वापस -ENOMEDIUM;
	हाल VVOLEXISTS:	वापस -EEXIST;
	हाल VNOSERVICE:	वापस -EIO;
	हाल VOFFLINE:		वापस -ENOENT;
	हाल VONLINE:		वापस -EEXIST;
	हाल VDISKFULL:		वापस -ENOSPC;
	हाल VOVERQUOTA:	वापस -EDQUOT;
	हाल VBUSY:		वापस -EBUSY;
	हाल VMOVED:		वापस -ENXIO;

		/* Volume Location server errors */
	हाल AFSVL_IDEXIST:		वापस -EEXIST;
	हाल AFSVL_IO:			वापस -EREMOTEIO;
	हाल AFSVL_NAMEEXIST:		वापस -EEXIST;
	हाल AFSVL_CREATEFAIL:		वापस -EREMOTEIO;
	हाल AFSVL_NOENT:		वापस -ENOMEDIUM;
	हाल AFSVL_EMPTY:		वापस -ENOMEDIUM;
	हाल AFSVL_ENTDELETED:		वापस -ENOMEDIUM;
	हाल AFSVL_BADNAME:		वापस -EINVAL;
	हाल AFSVL_BADINDEX:		वापस -EINVAL;
	हाल AFSVL_BADVOLTYPE:		वापस -EINVAL;
	हाल AFSVL_BADSERVER:		वापस -EINVAL;
	हाल AFSVL_BADPARTITION:	वापस -EINVAL;
	हाल AFSVL_REPSFULL:		वापस -EFBIG;
	हाल AFSVL_NOREPSERVER:		वापस -ENOENT;
	हाल AFSVL_DUPREPSERVER:	वापस -EEXIST;
	हाल AFSVL_RWNOTFOUND:		वापस -ENOENT;
	हाल AFSVL_BADREFCOUNT:		वापस -EINVAL;
	हाल AFSVL_SIZEEXCEEDED:	वापस -EINVAL;
	हाल AFSVL_BADENTRY:		वापस -EINVAL;
	हाल AFSVL_BADVOLIDBUMP:	वापस -EINVAL;
	हाल AFSVL_IDALREADYHASHED:	वापस -EINVAL;
	हाल AFSVL_ENTRYLOCKED:		वापस -EBUSY;
	हाल AFSVL_BADVOLOPER:		वापस -EBADRQC;
	हाल AFSVL_BADRELLOCKTYPE:	वापस -EINVAL;
	हाल AFSVL_RERELEASE:		वापस -EREMOTEIO;
	हाल AFSVL_BADSERVERFLAG:	वापस -EINVAL;
	हाल AFSVL_PERM:		वापस -EACCES;
	हाल AFSVL_NOMEM:		वापस -EREMOTEIO;

		/* Unअगरied AFS error table */
	हाल UAEPERM:			वापस -EPERM;
	हाल UAENOENT:			वापस -ENOENT;
	हाल UAEACCES:			वापस -EACCES;
	हाल UAEBUSY:			वापस -EBUSY;
	हाल UAEEXIST:			वापस -EEXIST;
	हाल UAENOTसूची:			वापस -ENOTसूची;
	हाल UAEISसूची:			वापस -EISसूची;
	हाल UAEFBIG:			वापस -EFBIG;
	हाल UAENOSPC:			वापस -ENOSPC;
	हाल UAEROFS:			वापस -EROFS;
	हाल UAEMLINK:			वापस -EMLINK;
	हाल UAEDEADLK:			वापस -EDEADLK;
	हाल UAENAMETOOLONG:		वापस -ENAMETOOLONG;
	हाल UAENOLCK:			वापस -ENOLCK;
	हाल UAENOTEMPTY:		वापस -ENOTEMPTY;
	हाल UAELOOP:			वापस -ELOOP;
	हाल UAEOVERFLOW:		वापस -EOVERFLOW;
	हाल UAENOMEDIUM:		वापस -ENOMEDIUM;
	हाल UAEDQUOT:			वापस -EDQUOT;

		/* RXKAD पात codes; from include/rxrpc/packet.h.  ET "RXK" == 0x1260B00 */
	हाल RXKADINCONSISTENCY: वापस -EPROTO;
	हाल RXKADPACKETSHORT:	वापस -EPROTO;
	हाल RXKADLEVELFAIL:	वापस -EKEYREJECTED;
	हाल RXKADTICKETLEN:	वापस -EKEYREJECTED;
	हाल RXKADOUTOFSEQUENCE: वापस -EPROTO;
	हाल RXKADNOAUTH:	वापस -EKEYREJECTED;
	हाल RXKADBADKEY:	वापस -EKEYREJECTED;
	हाल RXKADBADTICKET:	वापस -EKEYREJECTED;
	हाल RXKADUNKNOWNKEY:	वापस -EKEYREJECTED;
	हाल RXKADEXPIRED:	वापस -EKEYEXPIRED;
	हाल RXKADSEALEDINCON:	वापस -EKEYREJECTED;
	हाल RXKADDATALEN:	वापस -EKEYREJECTED;
	हाल RXKADILLEGALLEVEL:	वापस -EKEYREJECTED;

	हाल RXGEN_OPCODE:	वापस -ENOTSUPP;

	शेष:		वापस -EREMOTEIO;
	पूर्ण
पूर्ण

/*
 * Select the error to report from a set of errors.
 */
व्योम afs_prioritise_error(काष्ठा afs_error *e, पूर्णांक error, u32 पात_code)
अणु
	चयन (error) अणु
	हाल 0:
		वापस;
	शेष:
		अगर (e->error == -ETIMEDOUT ||
		    e->error == -ETIME)
			वापस;
		fallthrough;
	हाल -ETIMEDOUT:
	हाल -ETIME:
		अगर (e->error == -ENOMEM ||
		    e->error == -ENONET)
			वापस;
		fallthrough;
	हाल -ENOMEM:
	हाल -ENONET:
		अगर (e->error == -ERFKILL)
			वापस;
		fallthrough;
	हाल -ERFKILL:
		अगर (e->error == -EADDRNOTAVAIL)
			वापस;
		fallthrough;
	हाल -EADDRNOTAVAIL:
		अगर (e->error == -ENETUNREACH)
			वापस;
		fallthrough;
	हाल -ENETUNREACH:
		अगर (e->error == -EHOSTUNREACH)
			वापस;
		fallthrough;
	हाल -EHOSTUNREACH:
		अगर (e->error == -EHOSTDOWN)
			वापस;
		fallthrough;
	हाल -EHOSTDOWN:
		अगर (e->error == -ECONNREFUSED)
			वापस;
		fallthrough;
	हाल -ECONNREFUSED:
		अगर (e->error == -ECONNRESET)
			वापस;
		fallthrough;
	हाल -ECONNRESET: /* Responded, but call expired. */
		अगर (e->responded)
			वापस;
		e->error = error;
		वापस;

	हाल -ECONNABORTED:
		e->responded = true;
		e->error = afs_पात_to_error(पात_code);
		वापस;
	पूर्ण
पूर्ण
