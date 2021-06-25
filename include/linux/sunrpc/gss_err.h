<शैली गुरु>
/*
 *  linux/include/sunrpc/gss_err.h
 *
 *  Adapted from MIT Kerberos 5-1.2.1 include/gssapi/gssapi.h
 *
 *  Copyright (c) 2002 The Regents of the University of Michigan.
 *  All rights reserved.
 *
 *  Andy Adamson   <andros@umich.edu>
 */

/*
 * Copyright 1993 by OpenVision Technologies, Inc.
 * 
 * Permission to use, copy, modअगरy, distribute, and sell this software
 * and its करोcumentation क्रम any purpose is hereby granted without fee,
 * provided that the above copyright notice appears in all copies and
 * that both that copyright notice and this permission notice appear in
 * supporting करोcumentation, and that the name of OpenVision not be used
 * in advertising or खुलाity pertaining to distribution of the software
 * without specअगरic, written prior permission. OpenVision makes no
 * representations about the suitability of this software क्रम any
 * purpose.  It is provided "as is" without express or implied warranty.
 * 
 * OPENVISION DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL OPENVISION BE LIABLE FOR ANY SPECIAL, INसूचीECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF
 * USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

#अगर_अघोषित _LINUX_SUNRPC_GSS_ERR_H
#घोषणा _LINUX_SUNRPC_GSS_ERR_H

प्रकार अचिन्हित पूर्णांक OM_uपूर्णांक32;

/*
 * Flag bits क्रम context-level services.
 */
#घोषणा GSS_C_DELEG_FLAG 1
#घोषणा GSS_C_MUTUAL_FLAG 2
#घोषणा GSS_C_REPLAY_FLAG 4
#घोषणा GSS_C_SEQUENCE_FLAG 8
#घोषणा GSS_C_CONF_FLAG 16
#घोषणा GSS_C_INTEG_FLAG 32
#घोषणा	GSS_C_ANON_FLAG 64
#घोषणा GSS_C_PROT_READY_FLAG 128
#घोषणा GSS_C_TRANS_FLAG 256

/*
 * Credential usage options
 */
#घोषणा GSS_C_BOTH 0
#घोषणा GSS_C_INITIATE 1
#घोषणा GSS_C_ACCEPT 2

/*
 * Status code types क्रम gss_display_status
 */
#घोषणा GSS_C_GSS_CODE 1
#घोषणा GSS_C_MECH_CODE 2


/*
 * Expiration समय of 2^32-1 seconds means infinite lअगरeसमय क्रम a
 * credential or security context
 */
#घोषणा GSS_C_INDEFINITE ((OM_uपूर्णांक32) 0xfffffffful)


/* Major status codes */

#घोषणा GSS_S_COMPLETE 0

/*
 * Some "helper" definitions to make the status code macros obvious.
 */
#घोषणा GSS_C_CALLING_ERROR_OFFSET 24
#घोषणा GSS_C_ROUTINE_ERROR_OFFSET 16
#घोषणा GSS_C_SUPPLEMENTARY_OFFSET 0
#घोषणा GSS_C_CALLING_ERROR_MASK ((OM_uपूर्णांक32) 0377ul)
#घोषणा GSS_C_ROUTINE_ERROR_MASK ((OM_uपूर्णांक32) 0377ul)
#घोषणा GSS_C_SUPPLEMENTARY_MASK ((OM_uपूर्णांक32) 0177777ul)

/*
 * The macros that test status codes क्रम error conditions.  Note that the
 * GSS_ERROR() macro has changed slightly from the V1 GSSAPI so that it now
 * evaluates its argument only once.
 */
#घोषणा GSS_CALLING_ERROR(x) \
  ((x) & (GSS_C_CALLING_ERROR_MASK << GSS_C_CALLING_ERROR_OFFSET))
#घोषणा GSS_ROUTINE_ERROR(x) \
  ((x) & (GSS_C_ROUTINE_ERROR_MASK << GSS_C_ROUTINE_ERROR_OFFSET))
#घोषणा GSS_SUPPLEMENTARY_INFO(x) \
  ((x) & (GSS_C_SUPPLEMENTARY_MASK << GSS_C_SUPPLEMENTARY_OFFSET))
#घोषणा GSS_ERROR(x) \
  ((x) & ((GSS_C_CALLING_ERROR_MASK << GSS_C_CALLING_ERROR_OFFSET) | \
	  (GSS_C_ROUTINE_ERROR_MASK << GSS_C_ROUTINE_ERROR_OFFSET)))

/*
 * Now the actual status code definitions
 */

/*
 * Calling errors:
 */
#घोषणा GSS_S_CALL_INACCESSIBLE_READ \
                             (((OM_uपूर्णांक32) 1ul) << GSS_C_CALLING_ERROR_OFFSET)
#घोषणा GSS_S_CALL_INACCESSIBLE_WRITE \
                             (((OM_uपूर्णांक32) 2ul) << GSS_C_CALLING_ERROR_OFFSET)
#घोषणा GSS_S_CALL_BAD_STRUCTURE \
                             (((OM_uपूर्णांक32) 3ul) << GSS_C_CALLING_ERROR_OFFSET)

/*
 * Routine errors:
 */
#घोषणा GSS_S_BAD_MECH (((OM_uपूर्णांक32) 1ul) << GSS_C_ROUTINE_ERROR_OFFSET)
#घोषणा GSS_S_BAD_NAME (((OM_uपूर्णांक32) 2ul) << GSS_C_ROUTINE_ERROR_OFFSET)
#घोषणा GSS_S_BAD_NAMETYPE (((OM_uपूर्णांक32) 3ul) << GSS_C_ROUTINE_ERROR_OFFSET)
#घोषणा GSS_S_BAD_BINDINGS (((OM_uपूर्णांक32) 4ul) << GSS_C_ROUTINE_ERROR_OFFSET)
#घोषणा GSS_S_BAD_STATUS (((OM_uपूर्णांक32) 5ul) << GSS_C_ROUTINE_ERROR_OFFSET)
#घोषणा GSS_S_BAD_SIG (((OM_uपूर्णांक32) 6ul) << GSS_C_ROUTINE_ERROR_OFFSET)
#घोषणा GSS_S_NO_CRED (((OM_uपूर्णांक32) 7ul) << GSS_C_ROUTINE_ERROR_OFFSET)
#घोषणा GSS_S_NO_CONTEXT (((OM_uपूर्णांक32) 8ul) << GSS_C_ROUTINE_ERROR_OFFSET)
#घोषणा GSS_S_DEFECTIVE_TOKEN (((OM_uपूर्णांक32) 9ul) << GSS_C_ROUTINE_ERROR_OFFSET)
#घोषणा GSS_S_DEFECTIVE_CREDENTIAL \
     (((OM_uपूर्णांक32) 10ul) << GSS_C_ROUTINE_ERROR_OFFSET)
#घोषणा GSS_S_CREDENTIALS_EXPIRED \
     (((OM_uपूर्णांक32) 11ul) << GSS_C_ROUTINE_ERROR_OFFSET)
#घोषणा GSS_S_CONTEXT_EXPIRED \
     (((OM_uपूर्णांक32) 12ul) << GSS_C_ROUTINE_ERROR_OFFSET)
#घोषणा GSS_S_FAILURE (((OM_uपूर्णांक32) 13ul) << GSS_C_ROUTINE_ERROR_OFFSET)
#घोषणा GSS_S_BAD_QOP (((OM_uपूर्णांक32) 14ul) << GSS_C_ROUTINE_ERROR_OFFSET)
#घोषणा GSS_S_UNAUTHORIZED (((OM_uपूर्णांक32) 15ul) << GSS_C_ROUTINE_ERROR_OFFSET)
#घोषणा GSS_S_UNAVAILABLE (((OM_uपूर्णांक32) 16ul) << GSS_C_ROUTINE_ERROR_OFFSET)
#घोषणा GSS_S_DUPLICATE_ELEMENT \
     (((OM_uपूर्णांक32) 17ul) << GSS_C_ROUTINE_ERROR_OFFSET)
#घोषणा GSS_S_NAME_NOT_MN \
     (((OM_uपूर्णांक32) 18ul) << GSS_C_ROUTINE_ERROR_OFFSET)

/*
 * Supplementary info bits:
 */
#घोषणा GSS_S_CONTINUE_NEEDED (1 << (GSS_C_SUPPLEMENTARY_OFFSET + 0))
#घोषणा GSS_S_DUPLICATE_TOKEN (1 << (GSS_C_SUPPLEMENTARY_OFFSET + 1))
#घोषणा GSS_S_OLD_TOKEN (1 << (GSS_C_SUPPLEMENTARY_OFFSET + 2))
#घोषणा GSS_S_UNSEQ_TOKEN (1 << (GSS_C_SUPPLEMENTARY_OFFSET + 3))
#घोषणा GSS_S_GAP_TOKEN (1 << (GSS_C_SUPPLEMENTARY_OFFSET + 4))

/* XXXX these are not part of the GSSAPI C bindings!  (but should be) */

#घोषणा GSS_CALLING_ERROR_FIELD(x) \
   (((x) >> GSS_C_CALLING_ERROR_OFFSET) & GSS_C_CALLING_ERROR_MASK)
#घोषणा GSS_ROUTINE_ERROR_FIELD(x) \
   (((x) >> GSS_C_ROUTINE_ERROR_OFFSET) & GSS_C_ROUTINE_ERROR_MASK)
#घोषणा GSS_SUPPLEMENTARY_INFO_FIELD(x) \
   (((x) >> GSS_C_SUPPLEMENTARY_OFFSET) & GSS_C_SUPPLEMENTARY_MASK)

/* XXXX This is a necessary evil until the spec is fixed */
#घोषणा GSS_S_CRED_UNAVAIL GSS_S_FAILURE

#पूर्ण_अगर /* __LINUX_SUNRPC_GSS_ERR_H */
