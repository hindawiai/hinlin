<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Asymmetric खुला-key cryptography key type
 *
 * See Documentation/crypto/asymmetric-keys.rst
 *
 * Copyright (C) 2012 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */
#समावेश <keys/asymmetric-subtype.h>
#समावेश <keys/asymmetric-parser.h>
#समावेश <crypto/खुला_key.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/प्रकार.स>
#समावेश <keys/प्रणाली_keyring.h>
#समावेश <keys/user-type.h>
#समावेश "asymmetric_keys.h"

MODULE_LICENSE("GPL");

स्थिर अक्षर *स्थिर key_being_used_क्रम[NR__KEY_BEING_USED_FOR] = अणु
	[VERIFYING_MODULE_SIGNATURE]		= "mod sig",
	[VERIFYING_FIRMWARE_SIGNATURE]		= "firmware sig",
	[VERIFYING_KEXEC_PE_SIGNATURE]		= "kexec PE sig",
	[VERIFYING_KEY_SIGNATURE]		= "key sig",
	[VERIFYING_KEY_SELF_SIGNATURE]		= "key self sig",
	[VERIFYING_UNSPECIFIED_SIGNATURE]	= "unspec sig",
पूर्ण;
EXPORT_SYMBOL_GPL(key_being_used_क्रम);

अटल LIST_HEAD(asymmetric_key_parsers);
अटल DECLARE_RWSEM(asymmetric_key_parsers_sem);

/**
 * find_asymmetric_key - Find a key by ID.
 * @keyring: The keys to search.
 * @id_0: The first ID to look क्रम or शून्य.
 * @id_1: The second ID to look क्रम or शून्य.
 * @partial: Use partial match अगर true, exact अगर false.
 *
 * Find a key in the given keyring by identअगरier.  The preferred identअगरier is
 * the id_0 and the fallback identअगरier is the id_1.  If both are given, the
 * lookup is by the क्रमmer, but the latter must also match.
 */
काष्ठा key *find_asymmetric_key(काष्ठा key *keyring,
				स्थिर काष्ठा asymmetric_key_id *id_0,
				स्थिर काष्ठा asymmetric_key_id *id_1,
				bool partial)
अणु
	काष्ठा key *key;
	key_ref_t ref;
	स्थिर अक्षर *lookup;
	अक्षर *req, *p;
	पूर्णांक len;

	BUG_ON(!id_0 && !id_1);

	अगर (id_0) अणु
		lookup = id_0->data;
		len = id_0->len;
	पूर्ण अन्यथा अणु
		lookup = id_1->data;
		len = id_1->len;
	पूर्ण

	/* Conकाष्ठा an identअगरier "id:<keyid>". */
	p = req = kदो_स्मृति(2 + 1 + len * 2 + 1, GFP_KERNEL);
	अगर (!req)
		वापस ERR_PTR(-ENOMEM);

	अगर (partial) अणु
		*p++ = 'i';
		*p++ = 'd';
	पूर्ण अन्यथा अणु
		*p++ = 'e';
		*p++ = 'x';
	पूर्ण
	*p++ = ':';
	p = bin2hex(p, lookup, len);
	*p = 0;

	pr_debug("Look up: \"%s\"\n", req);

	ref = keyring_search(make_key_ref(keyring, 1),
			     &key_type_asymmetric, req, true);
	अगर (IS_ERR(ref))
		pr_debug("Request for key '%s' err %ld\n", req, PTR_ERR(ref));
	kमुक्त(req);

	अगर (IS_ERR(ref)) अणु
		चयन (PTR_ERR(ref)) अणु
			/* Hide some search errors */
		हाल -EACCES:
		हाल -ENOTसूची:
		हाल -EAGAIN:
			वापस ERR_PTR(-ENOKEY);
		शेष:
			वापस ERR_CAST(ref);
		पूर्ण
	पूर्ण

	key = key_ref_to_ptr(ref);
	अगर (id_0 && id_1) अणु
		स्थिर काष्ठा asymmetric_key_ids *kids = asymmetric_key_ids(key);

		अगर (!kids->id[1]) अणु
			pr_debug("First ID matches, but second is missing\n");
			जाओ reject;
		पूर्ण
		अगर (!asymmetric_key_id_same(id_1, kids->id[1])) अणु
			pr_debug("First ID matches, but second does not\n");
			जाओ reject;
		पूर्ण
	पूर्ण

	pr_devel("<==%s() = 0 [%x]\n", __func__, key_serial(key));
	वापस key;

reject:
	key_put(key);
	वापस ERR_PTR(-EKEYREJECTED);
पूर्ण
EXPORT_SYMBOL_GPL(find_asymmetric_key);

/**
 * asymmetric_key_generate_id: Conकाष्ठा an asymmetric key ID
 * @val_1: First binary blob
 * @len_1: Length of first binary blob
 * @val_2: Second binary blob
 * @len_2: Length of second binary blob
 *
 * Conकाष्ठा an asymmetric key ID from a pair of binary blobs.
 */
काष्ठा asymmetric_key_id *asymmetric_key_generate_id(स्थिर व्योम *val_1,
						     माप_प्रकार len_1,
						     स्थिर व्योम *val_2,
						     माप_प्रकार len_2)
अणु
	काष्ठा asymmetric_key_id *kid;

	kid = kदो_स्मृति(माप(काष्ठा asymmetric_key_id) + len_1 + len_2,
		      GFP_KERNEL);
	अगर (!kid)
		वापस ERR_PTR(-ENOMEM);
	kid->len = len_1 + len_2;
	स_नकल(kid->data, val_1, len_1);
	स_नकल(kid->data + len_1, val_2, len_2);
	वापस kid;
पूर्ण
EXPORT_SYMBOL_GPL(asymmetric_key_generate_id);

/**
 * asymmetric_key_id_same - Return true अगर two asymmetric keys IDs are the same.
 * @kid1: The key ID to compare
 * @kid2: The key ID to compare
 */
bool asymmetric_key_id_same(स्थिर काष्ठा asymmetric_key_id *kid1,
			    स्थिर काष्ठा asymmetric_key_id *kid2)
अणु
	अगर (!kid1 || !kid2)
		वापस false;
	अगर (kid1->len != kid2->len)
		वापस false;
	वापस स_भेद(kid1->data, kid2->data, kid1->len) == 0;
पूर्ण
EXPORT_SYMBOL_GPL(asymmetric_key_id_same);

/**
 * asymmetric_key_id_partial - Return true अगर two asymmetric keys IDs
 * partially match
 * @kid1: The key ID to compare
 * @kid2: The key ID to compare
 */
bool asymmetric_key_id_partial(स्थिर काष्ठा asymmetric_key_id *kid1,
			       स्थिर काष्ठा asymmetric_key_id *kid2)
अणु
	अगर (!kid1 || !kid2)
		वापस false;
	अगर (kid1->len < kid2->len)
		वापस false;
	वापस स_भेद(kid1->data + (kid1->len - kid2->len),
		      kid2->data, kid2->len) == 0;
पूर्ण
EXPORT_SYMBOL_GPL(asymmetric_key_id_partial);

/**
 * asymmetric_match_key_ids - Search asymmetric key IDs
 * @kids: The list of key IDs to check
 * @match_id: The key ID we're looking क्रम
 * @match: The match function to use
 */
अटल bool asymmetric_match_key_ids(
	स्थिर काष्ठा asymmetric_key_ids *kids,
	स्थिर काष्ठा asymmetric_key_id *match_id,
	bool (*match)(स्थिर काष्ठा asymmetric_key_id *kid1,
		      स्थिर काष्ठा asymmetric_key_id *kid2))
अणु
	पूर्णांक i;

	अगर (!kids || !match_id)
		वापस false;
	क्रम (i = 0; i < ARRAY_SIZE(kids->id); i++)
		अगर (match(kids->id[i], match_id))
			वापस true;
	वापस false;
पूर्ण

/* helper function can be called directly with pre-allocated memory */
अंतरभूत पूर्णांक __asymmetric_key_hex_to_key_id(स्थिर अक्षर *id,
				   काष्ठा asymmetric_key_id *match_id,
				   माप_प्रकार hexlen)
अणु
	match_id->len = hexlen;
	वापस hex2bin(match_id->data, id, hexlen);
पूर्ण

/**
 * asymmetric_key_hex_to_key_id - Convert a hex string पूर्णांकo a key ID.
 * @id: The ID as a hex string.
 */
काष्ठा asymmetric_key_id *asymmetric_key_hex_to_key_id(स्थिर अक्षर *id)
अणु
	काष्ठा asymmetric_key_id *match_id;
	माप_प्रकार asciihexlen;
	पूर्णांक ret;

	अगर (!*id)
		वापस ERR_PTR(-EINVAL);
	asciihexlen = म_माप(id);
	अगर (asciihexlen & 1)
		वापस ERR_PTR(-EINVAL);

	match_id = kदो_स्मृति(माप(काष्ठा asymmetric_key_id) + asciihexlen / 2,
			   GFP_KERNEL);
	अगर (!match_id)
		वापस ERR_PTR(-ENOMEM);
	ret = __asymmetric_key_hex_to_key_id(id, match_id, asciihexlen / 2);
	अगर (ret < 0) अणु
		kमुक्त(match_id);
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	वापस match_id;
पूर्ण

/*
 * Match asymmetric keys by an exact match on an ID.
 */
अटल bool asymmetric_key_cmp(स्थिर काष्ठा key *key,
			       स्थिर काष्ठा key_match_data *match_data)
अणु
	स्थिर काष्ठा asymmetric_key_ids *kids = asymmetric_key_ids(key);
	स्थिर काष्ठा asymmetric_key_id *match_id = match_data->preparsed;

	वापस asymmetric_match_key_ids(kids, match_id,
					asymmetric_key_id_same);
पूर्ण

/*
 * Match asymmetric keys by a partial match on an IDs.
 */
अटल bool asymmetric_key_cmp_partial(स्थिर काष्ठा key *key,
				       स्थिर काष्ठा key_match_data *match_data)
अणु
	स्थिर काष्ठा asymmetric_key_ids *kids = asymmetric_key_ids(key);
	स्थिर काष्ठा asymmetric_key_id *match_id = match_data->preparsed;

	वापस asymmetric_match_key_ids(kids, match_id,
					asymmetric_key_id_partial);
पूर्ण

/*
 * Preparse the match criterion.  If we करोn't set lookup_type and cmp,
 * the शेष will be an exact match on the key description.
 *
 * There are some specअगरiers क्रम matching key IDs rather than by the key
 * description:
 *
 *	"id:<id>" - find a key by partial match on any available ID
 *	"ex:<id>" - find a key by exact match on any available ID
 *
 * These have to be searched by iteration rather than by direct lookup because
 * the key is hashed according to its description.
 */
अटल पूर्णांक asymmetric_key_match_preparse(काष्ठा key_match_data *match_data)
अणु
	काष्ठा asymmetric_key_id *match_id;
	स्थिर अक्षर *spec = match_data->raw_data;
	स्थिर अक्षर *id;
	bool (*cmp)(स्थिर काष्ठा key *, स्थिर काष्ठा key_match_data *) =
		asymmetric_key_cmp;

	अगर (!spec || !*spec)
		वापस -EINVAL;
	अगर (spec[0] == 'i' &&
	    spec[1] == 'd' &&
	    spec[2] == ':') अणु
		id = spec + 3;
		cmp = asymmetric_key_cmp_partial;
	पूर्ण अन्यथा अगर (spec[0] == 'e' &&
		   spec[1] == 'x' &&
		   spec[2] == ':') अणु
		id = spec + 3;
	पूर्ण अन्यथा अणु
		जाओ शेष_match;
	पूर्ण

	match_id = asymmetric_key_hex_to_key_id(id);
	अगर (IS_ERR(match_id))
		वापस PTR_ERR(match_id);

	match_data->preparsed = match_id;
	match_data->cmp = cmp;
	match_data->lookup_type = KEYRING_SEARCH_LOOKUP_ITERATE;
	वापस 0;

शेष_match:
	वापस 0;
पूर्ण

/*
 * Free the preparsed the match criterion.
 */
अटल व्योम asymmetric_key_match_मुक्त(काष्ठा key_match_data *match_data)
अणु
	kमुक्त(match_data->preparsed);
पूर्ण

/*
 * Describe the asymmetric key
 */
अटल व्योम asymmetric_key_describe(स्थिर काष्ठा key *key, काष्ठा seq_file *m)
अणु
	स्थिर काष्ठा asymmetric_key_subtype *subtype = asymmetric_key_subtype(key);
	स्थिर काष्ठा asymmetric_key_ids *kids = asymmetric_key_ids(key);
	स्थिर काष्ठा asymmetric_key_id *kid;
	स्थिर अचिन्हित अक्षर *p;
	पूर्णांक n;

	seq_माला_दो(m, key->description);

	अगर (subtype) अणु
		seq_माला_दो(m, ": ");
		subtype->describe(key, m);

		अगर (kids && kids->id[1]) अणु
			kid = kids->id[1];
			seq_अ_दो(m, ' ');
			n = kid->len;
			p = kid->data;
			अगर (n > 4) अणु
				p += n - 4;
				n = 4;
			पूर्ण
			seq_म_लिखो(m, "%*phN", n, p);
		पूर्ण

		seq_माला_दो(m, " [");
		/* put something here to indicate the key's capabilities */
		seq_अ_दो(m, ']');
	पूर्ण
पूर्ण

/*
 * Preparse a asymmetric payload to get क्रमmat the contents appropriately क्रम the
 * पूर्णांकernal payload to cut करोwn on the number of scans of the data perक्रमmed.
 *
 * We also generate a proposed description from the contents of the key that
 * can be used to name the key अगर the user करोesn't want to provide one.
 */
अटल पूर्णांक asymmetric_key_preparse(काष्ठा key_preparsed_payload *prep)
अणु
	काष्ठा asymmetric_key_parser *parser;
	पूर्णांक ret;

	pr_devel("==>%s()\n", __func__);

	अगर (prep->datalen == 0)
		वापस -EINVAL;

	करोwn_पढ़ो(&asymmetric_key_parsers_sem);

	ret = -EBADMSG;
	list_क्रम_each_entry(parser, &asymmetric_key_parsers, link) अणु
		pr_debug("Trying parser '%s'\n", parser->name);

		ret = parser->parse(prep);
		अगर (ret != -EBADMSG) अणु
			pr_debug("Parser recognised the format (ret %d)\n",
				 ret);
			अवरोध;
		पूर्ण
	पूर्ण

	up_पढ़ो(&asymmetric_key_parsers_sem);
	pr_devel("<==%s() = %d\n", __func__, ret);
	वापस ret;
पूर्ण

/*
 * Clean up the key ID list
 */
अटल व्योम asymmetric_key_मुक्त_kids(काष्ठा asymmetric_key_ids *kids)
अणु
	पूर्णांक i;

	अगर (kids) अणु
		क्रम (i = 0; i < ARRAY_SIZE(kids->id); i++)
			kमुक्त(kids->id[i]);
		kमुक्त(kids);
	पूर्ण
पूर्ण

/*
 * Clean up the preparse data
 */
अटल व्योम asymmetric_key_मुक्त_preparse(काष्ठा key_preparsed_payload *prep)
अणु
	काष्ठा asymmetric_key_subtype *subtype = prep->payload.data[asym_subtype];
	काष्ठा asymmetric_key_ids *kids = prep->payload.data[asym_key_ids];

	pr_devel("==>%s()\n", __func__);

	अगर (subtype) अणु
		subtype->destroy(prep->payload.data[asym_crypto],
				 prep->payload.data[asym_auth]);
		module_put(subtype->owner);
	पूर्ण
	asymmetric_key_मुक्त_kids(kids);
	kमुक्त(prep->description);
पूर्ण

/*
 * dispose of the data dangling from the corpse of a asymmetric key
 */
अटल व्योम asymmetric_key_destroy(काष्ठा key *key)
अणु
	काष्ठा asymmetric_key_subtype *subtype = asymmetric_key_subtype(key);
	काष्ठा asymmetric_key_ids *kids = key->payload.data[asym_key_ids];
	व्योम *data = key->payload.data[asym_crypto];
	व्योम *auth = key->payload.data[asym_auth];

	key->payload.data[asym_crypto] = शून्य;
	key->payload.data[asym_subtype] = शून्य;
	key->payload.data[asym_key_ids] = शून्य;
	key->payload.data[asym_auth] = शून्य;

	अगर (subtype) अणु
		subtype->destroy(data, auth);
		module_put(subtype->owner);
	पूर्ण

	asymmetric_key_मुक्त_kids(kids);
पूर्ण

अटल काष्ठा key_restriction *asymmetric_restriction_alloc(
	key_restrict_link_func_t check,
	काष्ठा key *key)
अणु
	काष्ठा key_restriction *keyres =
		kzalloc(माप(काष्ठा key_restriction), GFP_KERNEL);

	अगर (!keyres)
		वापस ERR_PTR(-ENOMEM);

	keyres->check = check;
	keyres->key = key;
	keyres->keytype = &key_type_asymmetric;

	वापस keyres;
पूर्ण

/*
 * look up keyring restrict functions क्रम asymmetric keys
 */
अटल काष्ठा key_restriction *asymmetric_lookup_restriction(
	स्थिर अक्षर *restriction)
अणु
	अक्षर *restrict_method;
	अक्षर *parse_buf;
	अक्षर *next;
	काष्ठा key_restriction *ret = ERR_PTR(-EINVAL);

	अगर (म_भेद("builtin_trusted", restriction) == 0)
		वापस asymmetric_restriction_alloc(
			restrict_link_by_builtin_trusted, शून्य);

	अगर (म_भेद("builtin_and_secondary_trusted", restriction) == 0)
		वापस asymmetric_restriction_alloc(
			restrict_link_by_builtin_and_secondary_trusted, शून्य);

	parse_buf = kstrndup(restriction, PAGE_SIZE, GFP_KERNEL);
	अगर (!parse_buf)
		वापस ERR_PTR(-ENOMEM);

	next = parse_buf;
	restrict_method = strsep(&next, ":");

	अगर ((म_भेद(restrict_method, "key_or_keyring") == 0) && next) अणु
		अक्षर *key_text;
		key_serial_t serial;
		काष्ठा key *key;
		key_restrict_link_func_t link_fn =
			restrict_link_by_key_or_keyring;
		bool allow_null_key = false;

		key_text = strsep(&next, ":");

		अगर (next) अणु
			अगर (म_भेद(next, "chain") != 0)
				जाओ out;

			link_fn = restrict_link_by_key_or_keyring_chain;
			allow_null_key = true;
		पूर्ण

		अगर (kstrtos32(key_text, 0, &serial) < 0)
			जाओ out;

		अगर ((serial == 0) && allow_null_key) अणु
			key = शून्य;
		पूर्ण अन्यथा अणु
			key = key_lookup(serial);
			अगर (IS_ERR(key)) अणु
				ret = ERR_CAST(key);
				जाओ out;
			पूर्ण
		पूर्ण

		ret = asymmetric_restriction_alloc(link_fn, key);
		अगर (IS_ERR(ret))
			key_put(key);
	पूर्ण

out:
	kमुक्त(parse_buf);
	वापस ret;
पूर्ण

पूर्णांक asymmetric_key_eds_op(काष्ठा kernel_pkey_params *params,
			  स्थिर व्योम *in, व्योम *out)
अणु
	स्थिर काष्ठा asymmetric_key_subtype *subtype;
	काष्ठा key *key = params->key;
	पूर्णांक ret;

	pr_devel("==>%s()\n", __func__);

	अगर (key->type != &key_type_asymmetric)
		वापस -EINVAL;
	subtype = asymmetric_key_subtype(key);
	अगर (!subtype ||
	    !key->payload.data[0])
		वापस -EINVAL;
	अगर (!subtype->eds_op)
		वापस -ENOTSUPP;

	ret = subtype->eds_op(params, in, out);

	pr_devel("<==%s() = %d\n", __func__, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक asymmetric_key_verअगरy_signature(काष्ठा kernel_pkey_params *params,
					   स्थिर व्योम *in, स्थिर व्योम *in2)
अणु
	काष्ठा खुला_key_signature sig = अणु
		.s_size		= params->in2_len,
		.digest_size	= params->in_len,
		.encoding	= params->encoding,
		.hash_algo	= params->hash_algo,
		.digest		= (व्योम *)in,
		.s		= (व्योम *)in2,
	पूर्ण;

	वापस verअगरy_signature(params->key, &sig);
पूर्ण

काष्ठा key_type key_type_asymmetric = अणु
	.name			= "asymmetric",
	.preparse		= asymmetric_key_preparse,
	.मुक्त_preparse		= asymmetric_key_मुक्त_preparse,
	.instantiate		= generic_key_instantiate,
	.match_preparse		= asymmetric_key_match_preparse,
	.match_मुक्त		= asymmetric_key_match_मुक्त,
	.destroy		= asymmetric_key_destroy,
	.describe		= asymmetric_key_describe,
	.lookup_restriction	= asymmetric_lookup_restriction,
	.asym_query		= query_asymmetric_key,
	.asym_eds_op		= asymmetric_key_eds_op,
	.asym_verअगरy_signature	= asymmetric_key_verअगरy_signature,
पूर्ण;
EXPORT_SYMBOL_GPL(key_type_asymmetric);

/**
 * रेजिस्टर_asymmetric_key_parser - Register a asymmetric key blob parser
 * @parser: The parser to रेजिस्टर
 */
पूर्णांक रेजिस्टर_asymmetric_key_parser(काष्ठा asymmetric_key_parser *parser)
अणु
	काष्ठा asymmetric_key_parser *cursor;
	पूर्णांक ret;

	करोwn_ग_लिखो(&asymmetric_key_parsers_sem);

	list_क्रम_each_entry(cursor, &asymmetric_key_parsers, link) अणु
		अगर (म_भेद(cursor->name, parser->name) == 0) अणु
			pr_err("Asymmetric key parser '%s' already registered\n",
			       parser->name);
			ret = -EEXIST;
			जाओ out;
		पूर्ण
	पूर्ण

	list_add_tail(&parser->link, &asymmetric_key_parsers);

	pr_notice("Asymmetric key parser '%s' registered\n", parser->name);
	ret = 0;

out:
	up_ग_लिखो(&asymmetric_key_parsers_sem);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(रेजिस्टर_asymmetric_key_parser);

/**
 * unरेजिस्टर_asymmetric_key_parser - Unरेजिस्टर a asymmetric key blob parser
 * @parser: The parser to unरेजिस्टर
 */
व्योम unरेजिस्टर_asymmetric_key_parser(काष्ठा asymmetric_key_parser *parser)
अणु
	करोwn_ग_लिखो(&asymmetric_key_parsers_sem);
	list_del(&parser->link);
	up_ग_लिखो(&asymmetric_key_parsers_sem);

	pr_notice("Asymmetric key parser '%s' unregistered\n", parser->name);
पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_asymmetric_key_parser);

/*
 * Module stuff
 */
अटल पूर्णांक __init asymmetric_key_init(व्योम)
अणु
	वापस रेजिस्टर_key_type(&key_type_asymmetric);
पूर्ण

अटल व्योम __निकास asymmetric_key_cleanup(व्योम)
अणु
	unरेजिस्टर_key_type(&key_type_asymmetric);
पूर्ण

module_init(asymmetric_key_init);
module_निकास(asymmetric_key_cleanup);
