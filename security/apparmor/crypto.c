<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AppArmor security module
 *
 * This file contains AppArmor policy loading पूर्णांकerface function definitions.
 *
 * Copyright 2013 Canonical Ltd.
 *
 * Fns to provide a checksum of policy that has been loaded this can be
 * compared to userspace policy compiles to check loaded policy is what
 * it should be.
 */

#समावेश <crypto/hash.h>

#समावेश "include/apparmor.h"
#समावेश "include/crypto.h"

अटल अचिन्हित पूर्णांक apparmor_hash_size;

अटल काष्ठा crypto_shash *apparmor_tfm;

अचिन्हित पूर्णांक aa_hash_size(व्योम)
अणु
	वापस apparmor_hash_size;
पूर्ण

अक्षर *aa_calc_hash(व्योम *data, माप_प्रकार len)
अणु
	SHASH_DESC_ON_STACK(desc, apparmor_tfm);
	अक्षर *hash = शून्य;
	पूर्णांक error = -ENOMEM;

	अगर (!apparmor_tfm)
		वापस शून्य;

	hash = kzalloc(apparmor_hash_size, GFP_KERNEL);
	अगर (!hash)
		जाओ fail;

	desc->tfm = apparmor_tfm;

	error = crypto_shash_init(desc);
	अगर (error)
		जाओ fail;
	error = crypto_shash_update(desc, (u8 *) data, len);
	अगर (error)
		जाओ fail;
	error = crypto_shash_final(desc, hash);
	अगर (error)
		जाओ fail;

	वापस hash;

fail:
	kमुक्त(hash);

	वापस ERR_PTR(error);
पूर्ण

पूर्णांक aa_calc_profile_hash(काष्ठा aa_profile *profile, u32 version, व्योम *start,
			 माप_प्रकार len)
अणु
	SHASH_DESC_ON_STACK(desc, apparmor_tfm);
	पूर्णांक error = -ENOMEM;
	__le32 le32_version = cpu_to_le32(version);

	अगर (!aa_g_hash_policy)
		वापस 0;

	अगर (!apparmor_tfm)
		वापस 0;

	profile->hash = kzalloc(apparmor_hash_size, GFP_KERNEL);
	अगर (!profile->hash)
		जाओ fail;

	desc->tfm = apparmor_tfm;

	error = crypto_shash_init(desc);
	अगर (error)
		जाओ fail;
	error = crypto_shash_update(desc, (u8 *) &le32_version, 4);
	अगर (error)
		जाओ fail;
	error = crypto_shash_update(desc, (u8 *) start, len);
	अगर (error)
		जाओ fail;
	error = crypto_shash_final(desc, profile->hash);
	अगर (error)
		जाओ fail;

	वापस 0;

fail:
	kमुक्त(profile->hash);
	profile->hash = शून्य;

	वापस error;
पूर्ण

अटल पूर्णांक __init init_profile_hash(व्योम)
अणु
	काष्ठा crypto_shash *tfm;

	अगर (!apparmor_initialized)
		वापस 0;

	tfm = crypto_alloc_shash("sha1", 0, 0);
	अगर (IS_ERR(tfm)) अणु
		पूर्णांक error = PTR_ERR(tfm);
		AA_ERROR("failed to setup profile sha1 hashing: %d\n", error);
		वापस error;
	पूर्ण
	apparmor_tfm = tfm;
	apparmor_hash_size = crypto_shash_digestsize(apparmor_tfm);

	aa_info_message("AppArmor sha1 policy hashing enabled");

	वापस 0;
पूर्ण

late_initcall(init_profile_hash);
