<शैली गुरु>
/*
 *   fs/cअगरs/cअगरs_spnego.h -- SPNEGO upcall management क्रम CIFS
 *
 *   Copyright (c) 2007 Red Hat, Inc.
 *   Author(s): Jeff Layton (jlayton@redhat.com)
 *              Steve French (sfrench@us.ibm.com)
 *
 *   This library is मुक्त software; you can redistribute it and/or modअगरy
 *   it under the terms of the GNU Lesser General Public License as published
 *   by the Free Software Foundation; either version 2.1 of the License, or
 *   (at your option) any later version.
 *
 *   This library is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
 *   the GNU Lesser General Public License क्रम more details.
 *
 *   You should have received a copy of the GNU Lesser General Public License
 *   aदीर्घ with this library; अगर not, ग_लिखो to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#अगर_अघोषित _CIFS_SPNEGO_H
#घोषणा _CIFS_SPNEGO_H

#घोषणा CIFS_SPNEGO_UPCALL_VERSION 2

/*
 * The version field should always be set to CIFS_SPNEGO_UPCALL_VERSION.
 * The flags field is क्रम future use. The request-key callout should set
 * sesskey_len and secblob_len, and then concatenate the SessKey+SecBlob
 * and stuff it in the data field.
 */
काष्ठा cअगरs_spnego_msg अणु
	uपूर्णांक32_t	version;
	uपूर्णांक32_t	flags;
	uपूर्णांक32_t	sesskey_len;
	uपूर्णांक32_t	secblob_len;
	uपूर्णांक8_t		data[1];
पूर्ण;

#अगर_घोषित __KERNEL__
बाह्य काष्ठा key_type cअगरs_spnego_key_type;
बाह्य काष्ठा key *cअगरs_get_spnego_key(काष्ठा cअगरs_ses *sesInfo);
#पूर्ण_अगर /* KERNEL */

#पूर्ण_अगर /* _CIFS_SPNEGO_H */
