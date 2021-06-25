<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2011 Intel Corporation
 *
 * Author:
 * Dmitry Kasatkin <dmitry.kasatkin@पूर्णांकel.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/cred.h>
#समावेश <linux/kernel_पढ़ो_file.h>
#समावेश <linux/key-type.h>
#समावेश <linux/digsig.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <crypto/खुला_key.h>
#समावेश <keys/प्रणाली_keyring.h>

#समावेश "integrity.h"

अटल काष्ठा key *keyring[INTEGRITY_KEYRING_MAX];

अटल स्थिर अक्षर * स्थिर keyring_name[INTEGRITY_KEYRING_MAX] = अणु
#अगर_अघोषित CONFIG_INTEGRITY_TRUSTED_KEYRING
	"_evm",
	"_ima",
#अन्यथा
	".evm",
	".ima",
#पूर्ण_अगर
	".platform",
पूर्ण;

#अगर_घोषित CONFIG_IMA_KEYRINGS_PERMIT_SIGNED_BY_BUILTIN_OR_SECONDARY
#घोषणा restrict_link_to_ima restrict_link_by_builtin_and_secondary_trusted
#अन्यथा
#घोषणा restrict_link_to_ima restrict_link_by_builtin_trusted
#पूर्ण_अगर

अटल काष्ठा key *पूर्णांकegrity_keyring_from_id(स्थिर अचिन्हित पूर्णांक id)
अणु
	अगर (id >= INTEGRITY_KEYRING_MAX)
		वापस ERR_PTR(-EINVAL);

	अगर (!keyring[id]) अणु
		keyring[id] =
			request_key(&key_type_keyring, keyring_name[id], शून्य);
		अगर (IS_ERR(keyring[id])) अणु
			पूर्णांक err = PTR_ERR(keyring[id]);
			pr_err("no %s keyring: %d\n", keyring_name[id], err);
			keyring[id] = शून्य;
			वापस ERR_PTR(err);
		पूर्ण
	पूर्ण

	वापस keyring[id];
पूर्ण

पूर्णांक पूर्णांकegrity_digsig_verअगरy(स्थिर अचिन्हित पूर्णांक id, स्थिर अक्षर *sig, पूर्णांक siglen,
			    स्थिर अक्षर *digest, पूर्णांक digestlen)
अणु
	काष्ठा key *keyring;

	अगर (siglen < 2)
		वापस -EINVAL;

	keyring = पूर्णांकegrity_keyring_from_id(id);
	अगर (IS_ERR(keyring))
		वापस PTR_ERR(keyring);

	चयन (sig[1]) अणु
	हाल 1:
		/* v1 API expect signature without xattr type */
		वापस digsig_verअगरy(keyring, sig + 1, siglen - 1, digest,
				     digestlen);
	हाल 2:
		वापस asymmetric_verअगरy(keyring, sig, siglen, digest,
					 digestlen);
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

पूर्णांक पूर्णांकegrity_modsig_verअगरy(स्थिर अचिन्हित पूर्णांक id, स्थिर काष्ठा modsig *modsig)
अणु
	काष्ठा key *keyring;

	keyring = पूर्णांकegrity_keyring_from_id(id);
	अगर (IS_ERR(keyring))
		वापस PTR_ERR(keyring);

	वापस ima_modsig_verअगरy(keyring, modsig);
पूर्ण

अटल पूर्णांक __init __पूर्णांकegrity_init_keyring(स्थिर अचिन्हित पूर्णांक id,
					   key_perm_t perm,
					   काष्ठा key_restriction *restriction)
अणु
	स्थिर काष्ठा cred *cred = current_cred();
	पूर्णांक err = 0;

	keyring[id] = keyring_alloc(keyring_name[id], KUIDT_INIT(0),
				    KGIDT_INIT(0), cred, perm,
				    KEY_ALLOC_NOT_IN_QUOTA, restriction, शून्य);
	अगर (IS_ERR(keyring[id])) अणु
		err = PTR_ERR(keyring[id]);
		pr_info("Can't allocate %s keyring (%d)\n",
			keyring_name[id], err);
		keyring[id] = शून्य;
	पूर्ण अन्यथा अणु
		अगर (id == INTEGRITY_KEYRING_PLATFORM)
			set_platक्रमm_trusted_keys(keyring[id]);
		अगर (id == INTEGRITY_KEYRING_IMA)
			load_module_cert(keyring[id]);
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक __init पूर्णांकegrity_init_keyring(स्थिर अचिन्हित पूर्णांक id)
अणु
	काष्ठा key_restriction *restriction;
	key_perm_t perm;

	perm = (KEY_POS_ALL & ~KEY_POS_SETATTR) | KEY_USR_VIEW
		| KEY_USR_READ | KEY_USR_SEARCH;

	अगर (id == INTEGRITY_KEYRING_PLATFORM) अणु
		restriction = शून्य;
		जाओ out;
	पूर्ण

	अगर (!IS_ENABLED(CONFIG_INTEGRITY_TRUSTED_KEYRING))
		वापस 0;

	restriction = kzalloc(माप(काष्ठा key_restriction), GFP_KERNEL);
	अगर (!restriction)
		वापस -ENOMEM;

	restriction->check = restrict_link_to_ima;
	perm |= KEY_USR_WRITE;

out:
	वापस __पूर्णांकegrity_init_keyring(id, perm, restriction);
पूर्ण

अटल पूर्णांक __init पूर्णांकegrity_add_key(स्थिर अचिन्हित पूर्णांक id, स्थिर व्योम *data,
				    off_t size, key_perm_t perm)
अणु
	key_ref_t key;
	पूर्णांक rc = 0;

	अगर (!keyring[id])
		वापस -EINVAL;

	key = key_create_or_update(make_key_ref(keyring[id], 1), "asymmetric",
				   शून्य, data, size, perm,
				   KEY_ALLOC_NOT_IN_QUOTA);
	अगर (IS_ERR(key)) अणु
		rc = PTR_ERR(key);
		pr_err("Problem loading X.509 certificate %d\n", rc);
	पूर्ण अन्यथा अणु
		pr_notice("Loaded X.509 cert '%s'\n",
			  key_ref_to_ptr(key)->description);
		key_ref_put(key);
	पूर्ण

	वापस rc;

पूर्ण

पूर्णांक __init पूर्णांकegrity_load_x509(स्थिर अचिन्हित पूर्णांक id, स्थिर अक्षर *path)
अणु
	व्योम *data = शून्य;
	माप_प्रकार size;
	पूर्णांक rc;
	key_perm_t perm;

	rc = kernel_पढ़ो_file_from_path(path, 0, &data, पूर्णांक_उच्च, शून्य,
					READING_X509_CERTIFICATE);
	अगर (rc < 0) अणु
		pr_err("Unable to open file: %s (%d)", path, rc);
		वापस rc;
	पूर्ण
	size = rc;

	perm = (KEY_POS_ALL & ~KEY_POS_SETATTR) | KEY_USR_VIEW | KEY_USR_READ;

	pr_info("Loading X.509 certificate: %s\n", path);
	rc = पूर्णांकegrity_add_key(id, (स्थिर व्योम *)data, size, perm);

	vमुक्त(data);
	वापस rc;
पूर्ण

पूर्णांक __init पूर्णांकegrity_load_cert(स्थिर अचिन्हित पूर्णांक id, स्थिर अक्षर *source,
			       स्थिर व्योम *data, माप_प्रकार len, key_perm_t perm)
अणु
	अगर (!data)
		वापस -EINVAL;

	pr_info("Loading X.509 certificate: %s\n", source);
	वापस पूर्णांकegrity_add_key(id, data, len, perm);
पूर्ण
