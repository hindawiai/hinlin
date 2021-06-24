<शैली गुरु>
/*
 *  linux/include/linux/sunrpc/gss_asn1.h
 *
 *  minimal asn1 क्रम generic encoding/decoding of gss tokens
 *
 *  Adapted from MIT Kerberos 5-1.2.1 lib/include/krb5.h,
 *  lib/gssapi/krb5/gssapiP_krb5.h, and others
 *
 *  Copyright (c) 2000 The Regents of the University of Michigan.
 *  All rights reserved.
 *
 *  Andy Adamson   <andros@umich.edu>
 */

/*
 * Copyright 1995 by the Massachusetts Institute of Technology.
 * All Rights Reserved.
 *
 * Export of this software from the United States of America may
 *   require a specअगरic license from the United States Government.
 *   It is the responsibility of any person or organization contemplating
 *   export to obtain such a license beक्रमe exporting.
 *
 * WITHIN THAT CONSTRAINT, permission to use, copy, modअगरy, and
 * distribute this software and its करोcumentation क्रम any purpose and
 * without fee is hereby granted, provided that the above copyright
 * notice appear in all copies and that both that copyright notice and
 * this permission notice appear in supporting करोcumentation, and that
 * the name of M.I.T. not be used in advertising or खुलाity pertaining
 * to distribution of the software without specअगरic, written prior
 * permission.  Furthermore अगर you modअगरy this software you must label
 * your software as modअगरied software and not distribute it in such a
 * fashion that it might be confused with the original M.I.T. software.
 * M.I.T. makes no representations about the suitability of
 * this software क्रम any purpose.  It is provided "as is" without express
 * or implied warranty.
 *
 */


#समावेश <linux/sunrpc/gss_api.h>

#घोषणा SIZखातापूर्ण_INT 4

/* from gssapi_err_generic.h */
#घोषणा G_BAD_SERVICE_NAME                       (-2045022976L)
#घोषणा G_BAD_STRING_UID                         (-2045022975L)
#घोषणा G_NOUSER                                 (-2045022974L)
#घोषणा G_VALIDATE_FAILED                        (-2045022973L)
#घोषणा G_BUFFER_ALLOC                           (-2045022972L)
#घोषणा G_BAD_MSG_CTX                            (-2045022971L)
#घोषणा G_WRONG_SIZE                             (-2045022970L)
#घोषणा G_BAD_USAGE                              (-2045022969L)
#घोषणा G_UNKNOWN_QOP                            (-2045022968L)
#घोषणा G_NO_HOSTNAME                            (-2045022967L)
#घोषणा G_BAD_HOSTNAME                           (-2045022966L)
#घोषणा G_WRONG_MECH                             (-2045022965L)
#घोषणा G_BAD_TOK_HEADER                         (-2045022964L)
#घोषणा G_BAD_सूचीECTION                          (-2045022963L)
#घोषणा G_TOK_TRUNC                              (-2045022962L)
#घोषणा G_REFLECT                                (-2045022961L)
#घोषणा G_WRONG_TOKID                            (-2045022960L)

#घोषणा g_OID_equal(o1,o2) \
   (((o1)->len == (o2)->len) && \
    (स_भेद((o1)->data,(o2)->data,(पूर्णांक) (o1)->len) == 0))

u32 g_verअगरy_token_header(
     काष्ठा xdr_netobj *mech,
     पूर्णांक *body_size,
     अचिन्हित अक्षर **buf_in,
     पूर्णांक toksize);

पूर्णांक g_token_size(
     काष्ठा xdr_netobj *mech,
     अचिन्हित पूर्णांक body_size);

व्योम g_make_token_header(
     काष्ठा xdr_netobj *mech,
     पूर्णांक body_size,
     अचिन्हित अक्षर **buf);
