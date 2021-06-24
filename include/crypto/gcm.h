<शैली गुरु>
#अगर_अघोषित _CRYPTO_GCM_H
#घोषणा _CRYPTO_GCM_H

#समावेश <linux/त्रुटिसं.स>

#घोषणा GCM_AES_IV_SIZE 12
#घोषणा GCM_RFC4106_IV_SIZE 8
#घोषणा GCM_RFC4543_IV_SIZE 8

/*
 * validate authentication tag क्रम GCM
 */
अटल अंतरभूत पूर्णांक crypto_gcm_check_authsize(अचिन्हित पूर्णांक authsize)
अणु
	चयन (authsize) अणु
	हाल 4:
	हाल 8:
	हाल 12:
	हाल 13:
	हाल 14:
	हाल 15:
	हाल 16:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * validate authentication tag क्रम RFC4106
 */
अटल अंतरभूत पूर्णांक crypto_rfc4106_check_authsize(अचिन्हित पूर्णांक authsize)
अणु
	चयन (authsize) अणु
	हाल 8:
	हाल 12:
	हाल 16:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * validate assoclen क्रम RFC4106/RFC4543
 */
अटल अंतरभूत पूर्णांक crypto_ipsec_check_assoclen(अचिन्हित पूर्णांक assoclen)
अणु
	चयन (assoclen) अणु
	हाल 16:
	हाल 20:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर
