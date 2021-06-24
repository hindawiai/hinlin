<शैली गुरु>
/* Sign a module file using the given key.
 *
 * Copyright तऊ 2014-2016 Red Hat, Inc. All Rights Reserved.
 * Copyright तऊ 2015      Intel Corporation.
 * Copyright तऊ 2016      Hewlett Packard Enterprise Development LP
 *
 * Authors: David Howells <dhowells@redhat.com>
 *          David Woodhouse <dwmw2@infradead.org>
 *          Juerg Haefliger <juerg.haefliger@hpe.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1
 * of the licence, or (at your option) any later version.
 */
#घोषणा _GNU_SOURCE
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <मानक_निवेशt.h>
#समावेश <stdbool.h>
#समावेश <माला.स>
#समावेश <getopt.h>
#समावेश <err.h>
#समावेश <arpa/inet.h>
#समावेश <खोलोssl/खोलोsslv.h>
#समावेश <खोलोssl/bपन.स>
#समावेश <खोलोssl/evp.h>
#समावेश <खोलोssl/pem.h>
#समावेश <खोलोssl/err.h>
#समावेश <खोलोssl/engine.h>

/*
 * Use CMS अगर we have खोलोssl-1.0.0 or newer available - otherwise we have to
 * assume that it's not available and its header file is missing and that we
 * should use PKCS#7 instead.  Switching to the older PKCS#7 क्रमmat restricts
 * the options we have on specअगरying the X.509 certअगरicate we want.
 *
 * Further, older versions of OpenSSL करोn't support manually adding signers to
 * the PKCS#7 message so have to accept that we get a certअगरicate included in
 * the signature message.  Nor करो such older versions of OpenSSL support
 * signing with anything other than SHA1 - so we're stuck with that अगर such is
 * the हाल.
 */
#अगर defined(LIBRESSL_VERSION_NUMBER) || \
	OPENSSL_VERSION_NUMBER < 0x10000000L || \
	defined(OPENSSL_NO_CMS)
#घोषणा USE_PKCS7
#पूर्ण_अगर
#अगर_अघोषित USE_PKCS7
#समावेश <खोलोssl/cms.h>
#अन्यथा
#समावेश <खोलोssl/pkcs7.h>
#पूर्ण_अगर

काष्ठा module_signature अणु
	uपूर्णांक8_t		algo;		/* Public-key crypto algorithm [0] */
	uपूर्णांक8_t		hash;		/* Digest algorithm [0] */
	uपूर्णांक8_t		id_type;	/* Key identअगरier type [PKEY_ID_PKCS7] */
	uपूर्णांक8_t		signer_len;	/* Length of signer's name [0] */
	uपूर्णांक8_t		key_id_len;	/* Length of key identअगरier [0] */
	uपूर्णांक8_t		__pad[3];
	uपूर्णांक32_t	sig_len;	/* Length of signature data */
पूर्ण;

#घोषणा PKEY_ID_PKCS7 2

अटल अक्षर magic_number[] = "~Module signature appended~\n";

अटल __attribute__((noवापस))
व्योम क्रमmat(व्योम)
अणु
	ख_लिखो(मानक_त्रुटि,
		"Usage: scripts/sign-file [-dp] <hash algo> <key> <x509> <module> [<dest>]\n");
	ख_लिखो(मानक_त्रुटि,
		"       scripts/sign-file -s <raw sig> <hash algo> <x509> <module> [<dest>]\n");
	निकास(2);
पूर्ण

अटल व्योम display_खोलोssl_errors(पूर्णांक l)
अणु
	स्थिर अक्षर *file;
	अक्षर buf[120];
	पूर्णांक e, line;

	अगर (ERR_peek_error() == 0)
		वापस;
	ख_लिखो(मानक_त्रुटि, "At main.c:%d:\n", l);

	जबतक ((e = ERR_get_error_line(&file, &line))) अणु
		ERR_error_string(e, buf);
		ख_लिखो(मानक_त्रुटि, "- SSL %s: %s:%d\n", buf, file, line);
	पूर्ण
पूर्ण

अटल व्योम drain_खोलोssl_errors(व्योम)
अणु
	स्थिर अक्षर *file;
	पूर्णांक line;

	अगर (ERR_peek_error() == 0)
		वापस;
	जबतक (ERR_get_error_line(&file, &line)) अणुपूर्ण
पूर्ण

#घोषणा ERR(cond, fmt, ...)				\
	करो अणु						\
		bool __cond = (cond);			\
		display_खोलोssl_errors(__LINE__);	\
		अगर (__cond) अणु				\
			err(1, fmt, ## __VA_ARGS__);	\
		पूर्ण					\
	पूर्ण जबतक(0)

अटल स्थिर अक्षर *key_pass;

अटल पूर्णांक pem_pw_cb(अक्षर *buf, पूर्णांक len, पूर्णांक w, व्योम *v)
अणु
	पूर्णांक pwlen;

	अगर (!key_pass)
		वापस -1;

	pwlen = म_माप(key_pass);
	अगर (pwlen >= len)
		वापस -1;

	म_नकल(buf, key_pass);

	/* If it's wrong, don't keep trying it. */
	key_pass = शून्य;

	वापस pwlen;
पूर्ण

अटल EVP_PKEY *पढ़ो_निजी_key(स्थिर अक्षर *निजी_key_name)
अणु
	EVP_PKEY *निजी_key;

	अगर (!म_भेदन(निजी_key_name, "pkcs11:", 7)) अणु
		ENGINE *e;

		ENGINE_load_builtin_engines();
		drain_खोलोssl_errors();
		e = ENGINE_by_id("pkcs11");
		ERR(!e, "Load PKCS#11 ENGINE");
		अगर (ENGINE_init(e))
			drain_खोलोssl_errors();
		अन्यथा
			ERR(1, "ENGINE_init");
		अगर (key_pass)
			ERR(!ENGINE_ctrl_cmd_string(e, "PIN", key_pass, 0),
			    "Set PKCS#11 PIN");
		निजी_key = ENGINE_load_निजी_key(e, निजी_key_name,
						      शून्य, शून्य);
		ERR(!निजी_key, "%s", निजी_key_name);
	पूर्ण अन्यथा अणु
		BIO *b;

		b = BIO_new_file(निजी_key_name, "rb");
		ERR(!b, "%s", निजी_key_name);
		निजी_key = PEM_पढ़ो_bio_PrivateKey(b, शून्य, pem_pw_cb,
						      शून्य);
		ERR(!निजी_key, "%s", निजी_key_name);
		BIO_मुक्त(b);
	पूर्ण

	वापस निजी_key;
पूर्ण

अटल X509 *पढ़ो_x509(स्थिर अक्षर *x509_name)
अणु
	अचिन्हित अक्षर buf[2];
	X509 *x509;
	BIO *b;
	पूर्णांक n;

	b = BIO_new_file(x509_name, "rb");
	ERR(!b, "%s", x509_name);

	/* Look at the first two bytes of the file to determine the encoding */
	n = BIO_पढ़ो(b, buf, 2);
	अगर (n != 2) अणु
		अगर (BIO_should_retry(b)) अणु
			ख_लिखो(मानक_त्रुटि, "%s: Read wanted retry\n", x509_name);
			निकास(1);
		पूर्ण
		अगर (n >= 0) अणु
			ख_लिखो(मानक_त्रुटि, "%s: Short read\n", x509_name);
			निकास(1);
		पूर्ण
		ERR(1, "%s", x509_name);
	पूर्ण

	ERR(BIO_reset(b) != 0, "%s", x509_name);

	अगर (buf[0] == 0x30 && buf[1] >= 0x81 && buf[1] <= 0x84)
		/* Assume raw DER encoded X.509 */
		x509 = d2i_X509_bio(b, शून्य);
	अन्यथा
		/* Assume PEM encoded X.509 */
		x509 = PEM_पढ़ो_bio_X509(b, शून्य, शून्य, शून्य);

	BIO_मुक्त(b);
	ERR(!x509, "%s", x509_name);

	वापस x509;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा module_signature sig_info = अणु .id_type = PKEY_ID_PKCS7 पूर्ण;
	अक्षर *hash_algo = शून्य;
	अक्षर *निजी_key_name = शून्य, *raw_sig_name = शून्य;
	अक्षर *x509_name, *module_name, *dest_name;
	bool save_sig = false, replace_orig;
	bool sign_only = false;
	bool raw_sig = false;
	अचिन्हित अक्षर buf[4096];
	अचिन्हित दीर्घ module_size, sig_size;
	अचिन्हित पूर्णांक use_चिन्हित_attrs;
	स्थिर EVP_MD *digest_algo;
	EVP_PKEY *निजी_key;
#अगर_अघोषित USE_PKCS7
	CMS_ContentInfo *cms = शून्य;
	अचिन्हित पूर्णांक use_keyid = 0;
#अन्यथा
	PKCS7 *pkcs7 = शून्य;
#पूर्ण_अगर
	X509 *x509;
	BIO *bd, *bm;
	पूर्णांक opt, n;
	OpenSSL_add_all_algorithms();
	ERR_load_crypto_strings();
	ERR_clear_error();

	key_pass = दो_पर्या("KBUILD_SIGN_PIN");

#अगर_अघोषित USE_PKCS7
	use_चिन्हित_attrs = CMS_NOATTR;
#अन्यथा
	use_चिन्हित_attrs = PKCS7_NOATTR;
#पूर्ण_अगर

	करो अणु
		opt = getopt(argc, argv, "sdpk");
		चयन (opt) अणु
		हाल 's': raw_sig = true; अवरोध;
		हाल 'p': save_sig = true; अवरोध;
		हाल 'd': sign_only = true; save_sig = true; अवरोध;
#अगर_अघोषित USE_PKCS7
		हाल 'k': use_keyid = CMS_USE_KEYID; अवरोध;
#पूर्ण_अगर
		हाल -1: अवरोध;
		शेष: क्रमmat();
		पूर्ण
	पूर्ण जबतक (opt != -1);

	argc -= optind;
	argv += optind;
	अगर (argc < 4 || argc > 5)
		क्रमmat();

	अगर (raw_sig) अणु
		raw_sig_name = argv[0];
		hash_algo = argv[1];
	पूर्ण अन्यथा अणु
		hash_algo = argv[0];
		निजी_key_name = argv[1];
	पूर्ण
	x509_name = argv[2];
	module_name = argv[3];
	अगर (argc == 5 && म_भेद(argv[3], argv[4]) != 0) अणु
		dest_name = argv[4];
		replace_orig = false;
	पूर्ण अन्यथा अणु
		ERR(aप्र_लिखो(&dest_name, "%s.~signed~", module_name) < 0,
		    "asprintf");
		replace_orig = true;
	पूर्ण

#अगर_घोषित USE_PKCS7
	अगर (म_भेद(hash_algo, "sha1") != 0) अणु
		ख_लिखो(मानक_त्रुटि, "sign-file: %s only supports SHA1 signing\n",
			OPENSSL_VERSION_TEXT);
		निकास(3);
	पूर्ण
#पूर्ण_अगर

	/* Open the module file */
	bm = BIO_new_file(module_name, "rb");
	ERR(!bm, "%s", module_name);

	अगर (!raw_sig) अणु
		/* Read the निजी key and the X.509 cert the PKCS#7 message
		 * will poपूर्णांक to.
		 */
		निजी_key = पढ़ो_निजी_key(निजी_key_name);
		x509 = पढ़ो_x509(x509_name);

		/* Digest the module data. */
		OpenSSL_add_all_digests();
		display_खोलोssl_errors(__LINE__);
		digest_algo = EVP_get_digestbyname(hash_algo);
		ERR(!digest_algo, "EVP_get_digestbyname");

#अगर_अघोषित USE_PKCS7
		/* Load the signature message from the digest buffer. */
		cms = CMS_sign(शून्य, शून्य, शून्य, शून्य,
			       CMS_NOCERTS | CMS_PARTIAL | CMS_BINARY |
			       CMS_DETACHED | CMS_STREAM);
		ERR(!cms, "CMS_sign");

		ERR(!CMS_add1_signer(cms, x509, निजी_key, digest_algo,
				     CMS_NOCERTS | CMS_BINARY |
				     CMS_NOSMIMECAP | use_keyid |
				     use_चिन्हित_attrs),
		    "CMS_add1_signer");
		ERR(CMS_final(cms, bm, शून्य, CMS_NOCERTS | CMS_BINARY) < 0,
		    "CMS_final");

#अन्यथा
		pkcs7 = PKCS7_sign(x509, निजी_key, शून्य, bm,
				   PKCS7_NOCERTS | PKCS7_BINARY |
				   PKCS7_DETACHED | use_चिन्हित_attrs);
		ERR(!pkcs7, "PKCS7_sign");
#पूर्ण_अगर

		अगर (save_sig) अणु
			अक्षर *sig_file_name;
			BIO *b;

			ERR(aप्र_लिखो(&sig_file_name, "%s.p7s", module_name) < 0,
			    "asprintf");
			b = BIO_new_file(sig_file_name, "wb");
			ERR(!b, "%s", sig_file_name);
#अगर_अघोषित USE_PKCS7
			ERR(i2d_CMS_bio_stream(b, cms, शून्य, 0) < 0,
			    "%s", sig_file_name);
#अन्यथा
			ERR(i2d_PKCS7_bio(b, pkcs7) < 0,
			    "%s", sig_file_name);
#पूर्ण_अगर
			BIO_मुक्त(b);
		पूर्ण

		अगर (sign_only) अणु
			BIO_मुक्त(bm);
			वापस 0;
		पूर्ण
	पूर्ण

	/* Open the destination file now so that we can shovel the module data
	 * across as we पढ़ो it.
	 */
	bd = BIO_new_file(dest_name, "wb");
	ERR(!bd, "%s", dest_name);

	/* Append the marker and the PKCS#7 message to the destination file */
	ERR(BIO_reset(bm) < 0, "%s", module_name);
	जबतक ((n = BIO_पढ़ो(bm, buf, माप(buf))),
	       n > 0) अणु
		ERR(BIO_ग_लिखो(bd, buf, n) < 0, "%s", dest_name);
	पूर्ण
	BIO_मुक्त(bm);
	ERR(n < 0, "%s", module_name);
	module_size = BIO_number_written(bd);

	अगर (!raw_sig) अणु
#अगर_अघोषित USE_PKCS7
		ERR(i2d_CMS_bio_stream(bd, cms, शून्य, 0) < 0, "%s", dest_name);
#अन्यथा
		ERR(i2d_PKCS7_bio(bd, pkcs7) < 0, "%s", dest_name);
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		BIO *b;

		/* Read the raw signature file and ग_लिखो the data to the
		 * destination file
		 */
		b = BIO_new_file(raw_sig_name, "rb");
		ERR(!b, "%s", raw_sig_name);
		जबतक ((n = BIO_पढ़ो(b, buf, माप(buf))), n > 0)
			ERR(BIO_ग_लिखो(bd, buf, n) < 0, "%s", dest_name);
		BIO_मुक्त(b);
	पूर्ण

	sig_size = BIO_number_written(bd) - module_size;
	sig_info.sig_len = htonl(sig_size);
	ERR(BIO_ग_लिखो(bd, &sig_info, माप(sig_info)) < 0, "%s", dest_name);
	ERR(BIO_ग_लिखो(bd, magic_number, माप(magic_number) - 1) < 0, "%s", dest_name);

	ERR(BIO_मुक्त(bd) < 0, "%s", dest_name);

	/* Finally, अगर we're signing in place, replace the original. */
	अगर (replace_orig)
		ERR(नाम(dest_name, module_name) < 0, "%s", dest_name);

	वापस 0;
पूर्ण
