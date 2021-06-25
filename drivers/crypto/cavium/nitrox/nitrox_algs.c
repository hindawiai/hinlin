<शैली गुरु>
#समावेश "nitrox_common.h"

पूर्णांक nitrox_crypto_रेजिस्टर(व्योम)
अणु
	पूर्णांक err;

	err = nitrox_रेजिस्टर_skciphers();
	अगर (err)
		वापस err;

	err = nitrox_रेजिस्टर_aeads();
	अगर (err) अणु
		nitrox_unरेजिस्टर_skciphers();
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

व्योम nitrox_crypto_unरेजिस्टर(व्योम)
अणु
	nitrox_unरेजिस्टर_aeads();
	nitrox_unरेजिस्टर_skciphers();
पूर्ण
