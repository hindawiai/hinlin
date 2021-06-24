<शैली गुरु>
/* Extract X.509 certअगरicate in DER क्रमm from PKCS#11 or PEM.
 *
 * Copyright तऊ 2014-2015 Red Hat, Inc. All Rights Reserved.
 * Copyright तऊ 2015      Intel Corporation.
 *
 * Authors: David Howells <dhowells@redhat.com>
 *          David Woodhouse <dwmw2@infradead.org>
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
#समावेश <err.h>
#समावेश <खोलोssl/bपन.स>
#समावेश <खोलोssl/pem.h>
#समावेश <खोलोssl/err.h>
#समावेश <खोलोssl/engine.h>

#घोषणा PKEY_ID_PKCS7 2

अटल __attribute__((noवापस))
व्योम क्रमmat(व्योम)
अणु
	ख_लिखो(मानक_त्रुटि,
		"Usage: scripts/extract-cert <source> <dest>\n");
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
अटल BIO *wb;
अटल अक्षर *cert_dst;
अटल पूर्णांक kbuild_verbose;

अटल व्योम ग_लिखो_cert(X509 *x509)
अणु
	अक्षर buf[200];

	अगर (!wb) अणु
		wb = BIO_new_file(cert_dst, "wb");
		ERR(!wb, "%s", cert_dst);
	पूर्ण
	X509_NAME_oneline(X509_get_subject_name(x509), buf, माप(buf));
	ERR(!i2d_X509_bio(wb, x509), "%s", cert_dst);
	अगर (kbuild_verbose)
		ख_लिखो(मानक_त्रुटि, "Extracted cert: %s\n", buf);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	अक्षर *cert_src;

	OpenSSL_add_all_algorithms();
	ERR_load_crypto_strings();
	ERR_clear_error();

	kbuild_verbose = म_से_प(दो_पर्या("KBUILD_VERBOSE")?:"0");

        key_pass = दो_पर्या("KBUILD_SIGN_PIN");

	अगर (argc != 3)
		क्रमmat();

	cert_src = argv[1];
	cert_dst = argv[2];

	अगर (!cert_src[0]) अणु
		/* Invoked with no input; create empty file */
		खाता *f = ख_खोलो(cert_dst, "wb");
		ERR(!f, "%s", cert_dst);
		ख_बंद(f);
		निकास(0);
	पूर्ण अन्यथा अगर (!म_भेदन(cert_src, "pkcs11:", 7)) अणु
		ENGINE *e;
		काष्ठा अणु
			स्थिर अक्षर *cert_id;
			X509 *cert;
		पूर्ण parms;

		parms.cert_id = cert_src;
		parms.cert = शून्य;

		ENGINE_load_builtin_engines();
		drain_खोलोssl_errors();
		e = ENGINE_by_id("pkcs11");
		ERR(!e, "Load PKCS#11 ENGINE");
		अगर (ENGINE_init(e))
			drain_खोलोssl_errors();
		अन्यथा
			ERR(1, "ENGINE_init");
		अगर (key_pass)
			ERR(!ENGINE_ctrl_cmd_string(e, "PIN", key_pass, 0), "Set PKCS#11 PIN");
		ENGINE_ctrl_cmd(e, "LOAD_CERT_CTRL", 0, &parms, शून्य, 1);
		ERR(!parms.cert, "Get X.509 from PKCS#11");
		ग_लिखो_cert(parms.cert);
	पूर्ण अन्यथा अणु
		BIO *b;
		X509 *x509;

		b = BIO_new_file(cert_src, "rb");
		ERR(!b, "%s", cert_src);

		जबतक (1) अणु
			x509 = PEM_पढ़ो_bio_X509(b, शून्य, शून्य, शून्य);
			अगर (wb && !x509) अणु
				अचिन्हित दीर्घ err = ERR_peek_last_error();
				अगर (ERR_GET_LIB(err) == ERR_LIB_PEM &&
				    ERR_GET_REASON(err) == PEM_R_NO_START_LINE) अणु
					ERR_clear_error();
					अवरोध;
				पूर्ण
			पूर्ण
			ERR(!x509, "%s", cert_src);
			ग_लिखो_cert(x509);
		पूर्ण
	पूर्ण

	BIO_मुक्त(wb);

	वापस 0;
पूर्ण
