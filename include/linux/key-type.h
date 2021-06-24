<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* Definitions क्रम key type implementations
 *
 * Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#अगर_अघोषित _LINUX_KEY_TYPE_H
#घोषणा _LINUX_KEY_TYPE_H

#समावेश <linux/key.h>
#समावेश <linux/त्रुटिसं.स>

#अगर_घोषित CONFIG_KEYS

काष्ठा kernel_pkey_query;
काष्ठा kernel_pkey_params;

/*
 * Pre-parsed payload, used by key add, update and instantiate.
 *
 * This काष्ठा will be cleared and data and datalen will be set with the data
 * and length parameters from the caller and quotalen will be set from
 * def_datalen from the key type.  Then अगर the preparse() op is provided by the
 * key type, that will be called.  Then the काष्ठा will be passed to the
 * instantiate() or the update() op.
 *
 * If the preparse() op is given, the मुक्त_preparse() op will be called to
 * clear the contents.
 */
काष्ठा key_preparsed_payload अणु
	स्थिर अक्षर	*orig_description; /* Actual or proposed description (maybe शून्य) */
	अक्षर		*description;	/* Proposed key description (or शून्य) */
	जोड़ key_payload payload;	/* Proposed payload */
	स्थिर व्योम	*data;		/* Raw data */
	माप_प्रकार		datalen;	/* Raw datalen */
	माप_प्रकार		quotalen;	/* Quota length क्रम proposed payload */
	समय64_t	expiry;		/* Expiry समय of key */
पूर्ण __अक्रमomize_layout;

प्रकार पूर्णांक (*request_key_actor_t)(काष्ठा key *auth_key, व्योम *aux);

/*
 * Preparsed matching criterion.
 */
काष्ठा key_match_data अणु
	/* Comparison function, शेषs to exact description match, but can be
	 * overridden by type->match_preparse().  Should वापस true अगर a match
	 * is found and false अगर not.
	 */
	bool (*cmp)(स्थिर काष्ठा key *key,
		    स्थिर काष्ठा key_match_data *match_data);

	स्थिर व्योम	*raw_data;	/* Raw match data */
	व्योम		*preparsed;	/* For ->match_preparse() to stash stuff */
	अचिन्हित	lookup_type;	/* Type of lookup क्रम this search. */
#घोषणा KEYRING_SEARCH_LOOKUP_सूचीECT	0x0000	/* Direct lookup by description. */
#घोषणा KEYRING_SEARCH_LOOKUP_ITERATE	0x0001	/* Iterative search. */
पूर्ण;

/*
 * kernel managed key type definition
 */
काष्ठा key_type अणु
	/* name of the type */
	स्थिर अक्षर *name;

	/* शेष payload length क्रम quota precalculation (optional)
	 * - this can be used instead of calling key_payload_reserve(), that
	 *   function only needs to be called अगर the real datalen is dअगरferent
	 */
	माप_प्रकार def_datalen;

	अचिन्हित पूर्णांक flags;
#घोषणा KEY_TYPE_NET_DOMAIN	0x00000001 /* Keys of this type have a net namespace करोमुख्य */

	/* vet a description */
	पूर्णांक (*vet_description)(स्थिर अक्षर *description);

	/* Preparse the data blob from userspace that is to be the payload,
	 * generating a proposed description and payload that will be handed to
	 * the instantiate() and update() ops.
	 */
	पूर्णांक (*preparse)(काष्ठा key_preparsed_payload *prep);

	/* Free a preparse data काष्ठाure.
	 */
	व्योम (*मुक्त_preparse)(काष्ठा key_preparsed_payload *prep);

	/* instantiate a key of this type
	 * - this method should call key_payload_reserve() to determine अगर the
	 *   user's quota will hold the payload
	 */
	पूर्णांक (*instantiate)(काष्ठा key *key, काष्ठा key_preparsed_payload *prep);

	/* update a key of this type (optional)
	 * - this method should call key_payload_reserve() to recalculate the
	 *   quota consumption
	 * - the key must be locked against पढ़ो when modअगरying
	 */
	पूर्णांक (*update)(काष्ठा key *key, काष्ठा key_preparsed_payload *prep);

	/* Preparse the data supplied to ->match() (optional).  The
	 * data to be preparsed can be found in match_data->raw_data.
	 * The lookup type can also be set by this function.
	 */
	पूर्णांक (*match_preparse)(काष्ठा key_match_data *match_data);

	/* Free preparsed match data (optional).  This should be supplied it
	 * ->match_preparse() is supplied. */
	व्योम (*match_मुक्त)(काष्ठा key_match_data *match_data);

	/* clear some of the data from a key on revokation (optional)
	 * - the key's semaphore will be ग_लिखो-locked by the caller
	 */
	व्योम (*revoke)(काष्ठा key *key);

	/* clear the data from a key (optional) */
	व्योम (*destroy)(काष्ठा key *key);

	/* describe a key */
	व्योम (*describe)(स्थिर काष्ठा key *key, काष्ठा seq_file *p);

	/* पढ़ो a key's data (optional)
	 * - permission checks will be करोne by the caller
	 * - the key's semaphore will be पढ़ोlocked by the caller
	 * - should वापस the amount of data that could be पढ़ो, no matter how
	 *   much is copied पूर्णांकo the buffer
	 * - shouldn't करो the copy अगर the buffer is शून्य
	 */
	दीर्घ (*पढ़ो)(स्थिर काष्ठा key *key, अक्षर *buffer, माप_प्रकार buflen);

	/* handle request_key() क्रम this type instead of invoking
	 * /sbin/request-key (optional)
	 * - key is the key to instantiate
	 * - authkey is the authority to assume when instantiating this key
	 * - op is the operation to be करोne, usually "create"
	 * - the call must not वापस until the instantiation process has run
	 *   its course
	 */
	request_key_actor_t request_key;

	/* Look up a keyring access restriction (optional)
	 *
	 * - शून्य is a valid वापस value (meaning the requested restriction
	 *   is known but will never block addition of a key)
	 * - should वापस -EINVAL अगर the restriction is unknown
	 */
	काष्ठा key_restriction *(*lookup_restriction)(स्थिर अक्षर *params);

	/* Asymmetric key accessor functions. */
	पूर्णांक (*asym_query)(स्थिर काष्ठा kernel_pkey_params *params,
			  काष्ठा kernel_pkey_query *info);
	पूर्णांक (*asym_eds_op)(काष्ठा kernel_pkey_params *params,
			   स्थिर व्योम *in, व्योम *out);
	पूर्णांक (*asym_verअगरy_signature)(काष्ठा kernel_pkey_params *params,
				     स्थिर व्योम *in, स्थिर व्योम *in2);

	/* पूर्णांकernal fields */
	काष्ठा list_head	link;		/* link in types list */
	काष्ठा lock_class_key	lock_class;	/* key->sem lock class */
पूर्ण __अक्रमomize_layout;

बाह्य काष्ठा key_type key_type_keyring;

बाह्य पूर्णांक रेजिस्टर_key_type(काष्ठा key_type *ktype);
बाह्य व्योम unरेजिस्टर_key_type(काष्ठा key_type *ktype);

बाह्य पूर्णांक key_payload_reserve(काष्ठा key *key, माप_प्रकार datalen);
बाह्य पूर्णांक key_instantiate_and_link(काष्ठा key *key,
				    स्थिर व्योम *data,
				    माप_प्रकार datalen,
				    काष्ठा key *keyring,
				    काष्ठा key *authkey);
बाह्य पूर्णांक key_reject_and_link(काष्ठा key *key,
			       अचिन्हित समयout,
			       अचिन्हित error,
			       काष्ठा key *keyring,
			       काष्ठा key *authkey);
बाह्य व्योम complete_request_key(काष्ठा key *authkey, पूर्णांक error);

अटल अंतरभूत पूर्णांक key_negate_and_link(काष्ठा key *key,
				      अचिन्हित समयout,
				      काष्ठा key *keyring,
				      काष्ठा key *authkey)
अणु
	वापस key_reject_and_link(key, समयout, ENOKEY, keyring, authkey);
पूर्ण

बाह्य पूर्णांक generic_key_instantiate(काष्ठा key *key, काष्ठा key_preparsed_payload *prep);

#पूर्ण_अगर /* CONFIG_KEYS */
#पूर्ण_अगर /* _LINUX_KEY_TYPE_H */
