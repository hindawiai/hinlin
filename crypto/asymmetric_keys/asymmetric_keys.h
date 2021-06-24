<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* Internal definitions क्रम asymmetric key type
 *
 * Copyright (C) 2012 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <keys/asymmetric-type.h>

बाह्य काष्ठा asymmetric_key_id *asymmetric_key_hex_to_key_id(स्थिर अक्षर *id);

बाह्य पूर्णांक __asymmetric_key_hex_to_key_id(स्थिर अक्षर *id,
					  काष्ठा asymmetric_key_id *match_id,
					  माप_प्रकार hexlen);

बाह्य पूर्णांक asymmetric_key_eds_op(काष्ठा kernel_pkey_params *params,
				 स्थिर व्योम *in, व्योम *out);
