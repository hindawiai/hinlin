<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2019 Microsoft Corporation.
 *
 * Author:  Jaskaran Singh Khurana <jaskarankhurana@linux.microsoft.com>
 *
 */
#समावेश <linux/device-mapper.h>
#समावेश <linux/verअगरication.h>
#समावेश <keys/user-type.h>
#समावेश <linux/module.h>
#समावेश "dm-verity.h"
#समावेश "dm-verity-verify-sig.h"

#घोषणा DM_VERITY_VERIFY_ERR(s) DM_VERITY_ROOT_HASH_VERIFICATION " " s

अटल bool require_signatures;
module_param(require_signatures, bool, 0444);
MODULE_PARM_DESC(require_signatures,
		"Verify the roothash of dm-verity hash tree");

#घोषणा DM_VERITY_IS_SIG_FORCE_ENABLED() \
	(require_signatures != false)

bool verity_verअगरy_is_sig_opt_arg(स्थिर अक्षर *arg_name)
अणु
	वापस (!strहालcmp(arg_name,
			    DM_VERITY_ROOT_HASH_VERIFICATION_OPT_SIG_KEY));
पूर्ण

अटल पूर्णांक verity_verअगरy_get_sig_from_key(स्थिर अक्षर *key_desc,
					काष्ठा dm_verity_sig_opts *sig_opts)
अणु
	काष्ठा key *key;
	स्थिर काष्ठा user_key_payload *ukp;
	पूर्णांक ret = 0;

	key = request_key(&key_type_user,
			key_desc, शून्य);
	अगर (IS_ERR(key))
		वापस PTR_ERR(key);

	करोwn_पढ़ो(&key->sem);

	ukp = user_key_payload_locked(key);
	अगर (!ukp) अणु
		ret = -EKEYREVOKED;
		जाओ end;
	पूर्ण

	sig_opts->sig = kदो_स्मृति(ukp->datalen, GFP_KERNEL);
	अगर (!sig_opts->sig) अणु
		ret = -ENOMEM;
		जाओ end;
	पूर्ण
	sig_opts->sig_size = ukp->datalen;

	स_नकल(sig_opts->sig, ukp->data, sig_opts->sig_size);

end:
	up_पढ़ो(&key->sem);
	key_put(key);

	वापस ret;
पूर्ण

पूर्णांक verity_verअगरy_sig_parse_opt_args(काष्ठा dm_arg_set *as,
				     काष्ठा dm_verity *v,
				     काष्ठा dm_verity_sig_opts *sig_opts,
				     अचिन्हित पूर्णांक *argc,
				     स्थिर अक्षर *arg_name)
अणु
	काष्ठा dm_target *ti = v->ti;
	पूर्णांक ret = 0;
	स्थिर अक्षर *sig_key = शून्य;

	अगर (!*argc) अणु
		ti->error = DM_VERITY_VERIFY_ERR("Signature key not specified");
		वापस -EINVAL;
	पूर्ण

	sig_key = dm_shअगरt_arg(as);
	(*argc)--;

	ret = verity_verअगरy_get_sig_from_key(sig_key, sig_opts);
	अगर (ret < 0)
		ti->error = DM_VERITY_VERIFY_ERR("Invalid key specified");

	v->signature_key_desc = kstrdup(sig_key, GFP_KERNEL);
	अगर (!v->signature_key_desc)
		वापस -ENOMEM;

	वापस ret;
पूर्ण

/*
 * verअगरy_verअगरy_roothash - Verअगरy the root hash of the verity hash device
 *			     using builtin trusted keys.
 *
 * @root_hash: For verity, the roothash/data to be verअगरied.
 * @root_hash_len: Size of the roothash/data to be verअगरied.
 * @sig_data: The trusted signature that verअगरies the roothash/data.
 * @sig_len: Size of the signature.
 *
 */
पूर्णांक verity_verअगरy_root_hash(स्थिर व्योम *root_hash, माप_प्रकार root_hash_len,
			    स्थिर व्योम *sig_data, माप_प्रकार sig_len)
अणु
	पूर्णांक ret;

	अगर (!root_hash || root_hash_len == 0)
		वापस -EINVAL;

	अगर (!sig_data  || sig_len == 0) अणु
		अगर (DM_VERITY_IS_SIG_FORCE_ENABLED())
			वापस -ENOKEY;
		अन्यथा
			वापस 0;
	पूर्ण

	ret = verअगरy_pkcs7_signature(root_hash, root_hash_len, sig_data,
				sig_len,
#अगर_घोषित CONFIG_DM_VERITY_VERIFY_ROOTHASH_SIG_SECONDARY_KEYRING
				VERIFY_USE_SECONDARY_KEYRING,
#अन्यथा
				शून्य,
#पूर्ण_अगर
				VERIFYING_UNSPECIFIED_SIGNATURE, शून्य, शून्य);

	वापस ret;
पूर्ण

व्योम verity_verअगरy_sig_opts_cleanup(काष्ठा dm_verity_sig_opts *sig_opts)
अणु
	kमुक्त(sig_opts->sig);
	sig_opts->sig = शून्य;
	sig_opts->sig_size = 0;
पूर्ण
