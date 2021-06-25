<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2010 IBM Corporation
 * Copyright (c) 2019-2021, Linaro Limited
 *
 * See Documentation/security/keys/trusted-encrypted.rst
 */

#समावेश <keys/user-type.h>
#समावेश <keys/trusted-type.h>
#समावेश <keys/trusted_tee.h>
#समावेश <keys/trusted_tpm.h>
#समावेश <linux/capability.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/key-type.h>
#समावेश <linux/module.h>
#समावेश <linux/parser.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/slab.h>
#समावेश <linux/अटल_call.h>
#समावेश <linux/माला.स>
#समावेश <linux/uaccess.h>

अटल अक्षर *trusted_key_source;
module_param_named(source, trusted_key_source, अक्षरp, 0);
MODULE_PARM_DESC(source, "Select trusted keys source (tpm or tee)");

अटल स्थिर काष्ठा trusted_key_source trusted_key_sources[] = अणु
#अगर defined(CONFIG_TCG_TPM)
	अणु "tpm", &trusted_key_tpm_ops पूर्ण,
#पूर्ण_अगर
#अगर defined(CONFIG_TEE)
	अणु "tee", &trusted_key_tee_ops पूर्ण,
#पूर्ण_अगर
पूर्ण;

DEFINE_STATIC_CALL_शून्य(trusted_key_init, *trusted_key_sources[0].ops->init);
DEFINE_STATIC_CALL_शून्य(trusted_key_seal, *trusted_key_sources[0].ops->seal);
DEFINE_STATIC_CALL_शून्य(trusted_key_unseal,
			*trusted_key_sources[0].ops->unseal);
DEFINE_STATIC_CALL_शून्य(trusted_key_get_अक्रमom,
			*trusted_key_sources[0].ops->get_अक्रमom);
DEFINE_STATIC_CALL_शून्य(trusted_key_निकास, *trusted_key_sources[0].ops->निकास);
अटल अचिन्हित अक्षर migratable;

क्रमागत अणु
	Opt_err,
	Opt_new, Opt_load, Opt_update,
पूर्ण;

अटल स्थिर match_table_t key_tokens = अणु
	अणुOpt_new, "new"पूर्ण,
	अणुOpt_load, "load"पूर्ण,
	अणुOpt_update, "update"पूर्ण,
	अणुOpt_err, शून्यपूर्ण
पूर्ण;

/*
 * datablob_parse - parse the keyctl data and fill in the
 *                  payload काष्ठाure
 *
 * On success वापसs 0, otherwise -EINVAL.
 */
अटल पूर्णांक datablob_parse(अक्षर **datablob, काष्ठा trusted_key_payload *p)
अणु
	substring_t args[MAX_OPT_ARGS];
	दीर्घ keylen;
	पूर्णांक ret = -EINVAL;
	पूर्णांक key_cmd;
	अक्षर *c;

	/* मुख्य command */
	c = strsep(datablob, " \t");
	अगर (!c)
		वापस -EINVAL;
	key_cmd = match_token(c, key_tokens, args);
	चयन (key_cmd) अणु
	हाल Opt_new:
		/* first argument is key size */
		c = strsep(datablob, " \t");
		अगर (!c)
			वापस -EINVAL;
		ret = kम_से_दीर्घ(c, 10, &keylen);
		अगर (ret < 0 || keylen < MIN_KEY_SIZE || keylen > MAX_KEY_SIZE)
			वापस -EINVAL;
		p->key_len = keylen;
		ret = Opt_new;
		अवरोध;
	हाल Opt_load:
		/* first argument is sealed blob */
		c = strsep(datablob, " \t");
		अगर (!c)
			वापस -EINVAL;
		p->blob_len = म_माप(c) / 2;
		अगर (p->blob_len > MAX_BLOB_SIZE)
			वापस -EINVAL;
		ret = hex2bin(p->blob, c, p->blob_len);
		अगर (ret < 0)
			वापस -EINVAL;
		ret = Opt_load;
		अवरोध;
	हाल Opt_update:
		ret = Opt_update;
		अवरोध;
	हाल Opt_err:
		वापस -EINVAL;
	पूर्ण
	वापस ret;
पूर्ण

अटल काष्ठा trusted_key_payload *trusted_payload_alloc(काष्ठा key *key)
अणु
	काष्ठा trusted_key_payload *p = शून्य;
	पूर्णांक ret;

	ret = key_payload_reserve(key, माप(*p));
	अगर (ret < 0)
		जाओ err;
	p = kzalloc(माप(*p), GFP_KERNEL);
	अगर (!p)
		जाओ err;

	p->migratable = migratable;
err:
	वापस p;
पूर्ण

/*
 * trusted_instantiate - create a new trusted key
 *
 * Unseal an existing trusted blob or, क्रम a new key, get a
 * अक्रमom key, then seal and create a trusted key-type key,
 * adding it to the specअगरied keyring.
 *
 * On success, वापस 0. Otherwise वापस त्रुटि_सं.
 */
अटल पूर्णांक trusted_instantiate(काष्ठा key *key,
			       काष्ठा key_preparsed_payload *prep)
अणु
	काष्ठा trusted_key_payload *payload = शून्य;
	माप_प्रकार datalen = prep->datalen;
	अक्षर *datablob, *orig_datablob;
	पूर्णांक ret = 0;
	पूर्णांक key_cmd;
	माप_प्रकार key_len;

	अगर (datalen <= 0 || datalen > 32767 || !prep->data)
		वापस -EINVAL;

	orig_datablob = datablob = kदो_स्मृति(datalen + 1, GFP_KERNEL);
	अगर (!datablob)
		वापस -ENOMEM;
	स_नकल(datablob, prep->data, datalen);
	datablob[datalen] = '\0';

	payload = trusted_payload_alloc(key);
	अगर (!payload) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	key_cmd = datablob_parse(&datablob, payload);
	अगर (key_cmd < 0) अणु
		ret = key_cmd;
		जाओ out;
	पूर्ण

	dump_payload(payload);

	चयन (key_cmd) अणु
	हाल Opt_load:
		ret = अटल_call(trusted_key_unseal)(payload, datablob);
		dump_payload(payload);
		अगर (ret < 0)
			pr_info("key_unseal failed (%d)\n", ret);
		अवरोध;
	हाल Opt_new:
		key_len = payload->key_len;
		ret = अटल_call(trusted_key_get_अक्रमom)(payload->key,
							  key_len);
		अगर (ret < 0)
			जाओ out;

		अगर (ret != key_len) अणु
			pr_info("key_create failed (%d)\n", ret);
			ret = -EIO;
			जाओ out;
		पूर्ण

		ret = अटल_call(trusted_key_seal)(payload, datablob);
		अगर (ret < 0)
			pr_info("key_seal failed (%d)\n", ret);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
out:
	kमुक्त_sensitive(orig_datablob);
	अगर (!ret)
		rcu_assign_keypoपूर्णांकer(key, payload);
	अन्यथा
		kमुक्त_sensitive(payload);
	वापस ret;
पूर्ण

अटल व्योम trusted_rcu_मुक्त(काष्ठा rcu_head *rcu)
अणु
	काष्ठा trusted_key_payload *p;

	p = container_of(rcu, काष्ठा trusted_key_payload, rcu);
	kमुक्त_sensitive(p);
पूर्ण

/*
 * trusted_update - reseal an existing key with new PCR values
 */
अटल पूर्णांक trusted_update(काष्ठा key *key, काष्ठा key_preparsed_payload *prep)
अणु
	काष्ठा trusted_key_payload *p;
	काष्ठा trusted_key_payload *new_p;
	माप_प्रकार datalen = prep->datalen;
	अक्षर *datablob, *orig_datablob;
	पूर्णांक ret = 0;

	अगर (key_is_negative(key))
		वापस -ENOKEY;
	p = key->payload.data[0];
	अगर (!p->migratable)
		वापस -EPERM;
	अगर (datalen <= 0 || datalen > 32767 || !prep->data)
		वापस -EINVAL;

	orig_datablob = datablob = kदो_स्मृति(datalen + 1, GFP_KERNEL);
	अगर (!datablob)
		वापस -ENOMEM;

	new_p = trusted_payload_alloc(key);
	अगर (!new_p) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	स_नकल(datablob, prep->data, datalen);
	datablob[datalen] = '\0';
	ret = datablob_parse(&datablob, new_p);
	अगर (ret != Opt_update) अणु
		ret = -EINVAL;
		kमुक्त_sensitive(new_p);
		जाओ out;
	पूर्ण

	/* copy old key values, and reseal with new pcrs */
	new_p->migratable = p->migratable;
	new_p->key_len = p->key_len;
	स_नकल(new_p->key, p->key, p->key_len);
	dump_payload(p);
	dump_payload(new_p);

	ret = अटल_call(trusted_key_seal)(new_p, datablob);
	अगर (ret < 0) अणु
		pr_info("key_seal failed (%d)\n", ret);
		kमुक्त_sensitive(new_p);
		जाओ out;
	पूर्ण

	rcu_assign_keypoपूर्णांकer(key, new_p);
	call_rcu(&p->rcu, trusted_rcu_मुक्त);
out:
	kमुक्त_sensitive(orig_datablob);
	वापस ret;
पूर्ण

/*
 * trusted_पढ़ो - copy the sealed blob data to userspace in hex.
 * On success, वापस to userspace the trusted key datablob size.
 */
अटल दीर्घ trusted_पढ़ो(स्थिर काष्ठा key *key, अक्षर *buffer,
			 माप_प्रकार buflen)
अणु
	स्थिर काष्ठा trusted_key_payload *p;
	अक्षर *bufp;
	पूर्णांक i;

	p = dereference_key_locked(key);
	अगर (!p)
		वापस -EINVAL;

	अगर (buffer && buflen >= 2 * p->blob_len) अणु
		bufp = buffer;
		क्रम (i = 0; i < p->blob_len; i++)
			bufp = hex_byte_pack(bufp, p->blob[i]);
	पूर्ण
	वापस 2 * p->blob_len;
पूर्ण

/*
 * trusted_destroy - clear and मुक्त the key's payload
 */
अटल व्योम trusted_destroy(काष्ठा key *key)
अणु
	kमुक्त_sensitive(key->payload.data[0]);
पूर्ण

काष्ठा key_type key_type_trusted = अणु
	.name = "trusted",
	.instantiate = trusted_instantiate,
	.update = trusted_update,
	.destroy = trusted_destroy,
	.describe = user_describe,
	.पढ़ो = trusted_पढ़ो,
पूर्ण;
EXPORT_SYMBOL_GPL(key_type_trusted);

अटल पूर्णांक __init init_trusted(व्योम)
अणु
	पूर्णांक i, ret = 0;

	क्रम (i = 0; i < ARRAY_SIZE(trusted_key_sources); i++) अणु
		अगर (trusted_key_source &&
		    म_भेदन(trusted_key_source, trusted_key_sources[i].name,
			    म_माप(trusted_key_sources[i].name)))
			जारी;

		अटल_call_update(trusted_key_init,
				   trusted_key_sources[i].ops->init);
		अटल_call_update(trusted_key_seal,
				   trusted_key_sources[i].ops->seal);
		अटल_call_update(trusted_key_unseal,
				   trusted_key_sources[i].ops->unseal);
		अटल_call_update(trusted_key_get_अक्रमom,
				   trusted_key_sources[i].ops->get_अक्रमom);
		अटल_call_update(trusted_key_निकास,
				   trusted_key_sources[i].ops->निकास);
		migratable = trusted_key_sources[i].ops->migratable;

		ret = अटल_call(trusted_key_init)();
		अगर (!ret)
			अवरोध;
	पूर्ण

	/*
	 * encrypted_keys.ko depends on successful load of this module even अगर
	 * trusted key implementation is not found.
	 */
	अगर (ret == -ENODEV)
		वापस 0;

	वापस ret;
पूर्ण

अटल व्योम __निकास cleanup_trusted(व्योम)
अणु
	अटल_call(trusted_key_निकास)();
पूर्ण

late_initcall(init_trusted);
module_निकास(cleanup_trusted);

MODULE_LICENSE("GPL");
