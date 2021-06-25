<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <खोलोssl/sha.h>
#समावेश <खोलोssl/md5.h>

पूर्णांक मुख्य(व्योम)
अणु
	MD5_CTX context;
	अचिन्हित अक्षर md[MD5_DIGEST_LENGTH + SHA_DIGEST_LENGTH];
	अचिन्हित अक्षर dat[] = "12345";

	MD5_Init(&context);
	MD5_Update(&context, &dat[0], माप(dat));
	MD5_Final(&md[0], &context);

	SHA1(&dat[0], माप(dat), &md[0]);

	वापस 0;
पूर्ण
