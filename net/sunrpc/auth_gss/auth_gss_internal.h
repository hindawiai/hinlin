<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause
/*
 * linux/net/sunrpc/auth_gss/auth_gss_पूर्णांकernal.h
 *
 * Internal definitions क्रम RPCSEC_GSS client authentication
 *
 * Copyright (c) 2000 The Regents of the University of Michigan.
 * All rights reserved.
 *
 */
#समावेश <linux/err.h>
#समावेश <linux/माला.स>
#समावेश <linux/sunrpc/xdr.h>

अटल अंतरभूत स्थिर व्योम *
simple_get_bytes(स्थिर व्योम *p, स्थिर व्योम *end, व्योम *res, माप_प्रकार len)
अणु
	स्थिर व्योम *q = (स्थिर व्योम *)((स्थिर अक्षर *)p + len);
	अगर (unlikely(q > end || q < p))
		वापस ERR_PTR(-EFAULT);
	स_नकल(res, p, len);
	वापस q;
पूर्ण

अटल अंतरभूत स्थिर व्योम *
simple_get_netobj(स्थिर व्योम *p, स्थिर व्योम *end, काष्ठा xdr_netobj *dest)
अणु
	स्थिर व्योम *q;
	अचिन्हित पूर्णांक len;

	p = simple_get_bytes(p, end, &len, माप(len));
	अगर (IS_ERR(p))
		वापस p;
	q = (स्थिर व्योम *)((स्थिर अक्षर *)p + len);
	अगर (unlikely(q > end || q < p))
		वापस ERR_PTR(-EFAULT);
	अगर (len) अणु
		dest->data = kmemdup(p, len, GFP_NOFS);
		अगर (unlikely(dest->data == शून्य))
			वापस ERR_PTR(-ENOMEM);
	पूर्ण अन्यथा
		dest->data = शून्य;
	dest->len = len;
	वापस q;
पूर्ण
