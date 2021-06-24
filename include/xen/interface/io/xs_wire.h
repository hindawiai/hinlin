<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Details of the "wire" protocol between Xen Store Daemon and client
 * library or guest kernel.
 * Copyright (C) 2005 Rusty Russell IBM Corporation
 */

#अगर_अघोषित _XS_WIRE_H
#घोषणा _XS_WIRE_H

क्रमागत xsd_sockmsg_type
अणु
    XS_DEBUG,
    XS_सूचीECTORY,
    XS_READ,
    XS_GET_PERMS,
    XS_WATCH,
    XS_UNWATCH,
    XS_TRANSACTION_START,
    XS_TRANSACTION_END,
    XS_INTRODUCE,
    XS_RELEASE,
    XS_GET_DOMAIN_PATH,
    XS_WRITE,
    XS_MKसूची,
    XS_RM,
    XS_SET_PERMS,
    XS_WATCH_EVENT,
    XS_ERROR,
    XS_IS_DOMAIN_INTRODUCED,
    XS_RESUME,
    XS_SET_TARGET,
    XS_RESTRICT,
    XS_RESET_WATCHES,
पूर्ण;

#घोषणा XS_WRITE_NONE "NONE"
#घोषणा XS_WRITE_CREATE "CREATE"
#घोषणा XS_WRITE_CREATE_EXCL "CREATE|EXCL"

/* We hand errors as strings, क्रम portability. */
काष्ठा xsd_errors
अणु
    पूर्णांक errnum;
    स्थिर अक्षर *errstring;
पूर्ण;
#घोषणा XSD_ERROR(x) अणु x, #x पूर्ण
अटल काष्ठा xsd_errors xsd_errors[] __attribute__((unused)) = अणु
    XSD_ERROR(EINVAL),
    XSD_ERROR(EACCES),
    XSD_ERROR(EEXIST),
    XSD_ERROR(EISसूची),
    XSD_ERROR(ENOENT),
    XSD_ERROR(ENOMEM),
    XSD_ERROR(ENOSPC),
    XSD_ERROR(EIO),
    XSD_ERROR(ENOTEMPTY),
    XSD_ERROR(ENOSYS),
    XSD_ERROR(EROFS),
    XSD_ERROR(EBUSY),
    XSD_ERROR(EAGAIN),
    XSD_ERROR(EISCONN)
पूर्ण;

काष्ठा xsd_sockmsg
अणु
    uपूर्णांक32_t type;  /* XS_??? */
    uपूर्णांक32_t req_id;/* Request identअगरier, echoed in daemon's response.  */
    uपूर्णांक32_t tx_id; /* Transaction id (0 अगर not related to a transaction). */
    uपूर्णांक32_t len;   /* Length of data following this. */

    /* Generally followed by nul-terminated string(s). */
पूर्ण;

क्रमागत xs_watch_type
अणु
    XS_WATCH_PATH = 0,
    XS_WATCH_TOKEN
पूर्ण;

/* Inter-करोमुख्य shared memory communications. */
#घोषणा XENSTORE_RING_SIZE 1024
प्रकार uपूर्णांक32_t XENSTORE_RING_IDX;
#घोषणा MASK_XENSTORE_IDX(idx) ((idx) & (XENSTORE_RING_SIZE-1))
काष्ठा xenstore_करोमुख्य_पूर्णांकerface अणु
    अक्षर req[XENSTORE_RING_SIZE]; /* Requests to xenstore daemon. */
    अक्षर rsp[XENSTORE_RING_SIZE]; /* Replies and async watch events. */
    XENSTORE_RING_IDX req_cons, req_prod;
    XENSTORE_RING_IDX rsp_cons, rsp_prod;
पूर्ण;

/* Violating this is very bad.  See करोcs/misc/xenstore.txt. */
#घोषणा XENSTORE_PAYLOAD_MAX 4096

#पूर्ण_अगर /* _XS_WIRE_H */
