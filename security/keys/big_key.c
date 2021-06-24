<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Large capacity key type
 *
 * Copyright (C) 2017-2020 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 * Copyright (C) 2013 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#घोषणा pr_fmt(fmt) "big_key: "fmt
#समावेश <linux/init.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/file.h>
#समावेश <linux/shmem_fs.h>
#समावेश <linux/err.h>
#समावेश <linux/अक्रमom.h>
#समावेश <keys/user-type.h>
#समावेश <keys/big_key-type.h>
#समावेश <crypto/chacha20poly1305.h>

/*
 * Layout of key payload words.
 */
क्रमागत अणु
	big_key_data,
	big_key_path,
	big_key_path_2nd_part,
	big_key_len,
पूर्ण;

/*
 * If the data is under this limit, there's no poपूर्णांक creating a shm file to
 * hold it as the permanently resident metadata क्रम the shmem fs will be at
 * least as large as the data.
 */
#घोषणा BIG_KEY_खाता_THRESHOLD (माप(काष्ठा inode) + माप(काष्ठा dentry))

/*
 * big_key defined keys take an arbitrary string as the description and an
 * arbitrary blob of data as the payload
 */
काष्ठा key_type key_type_big_key = अणु
	.name			= "big_key",
	.preparse		= big_key_preparse,
	.मुक्त_preparse		= big_key_मुक्त_preparse,
	.instantiate		= generic_key_instantiate,
	.revoke			= big_key_revoke,
	.destroy		= big_key_destroy,
	.describe		= big_key_describe,
	.पढ़ो			= big_key_पढ़ो,
	.update			= big_key_update,
पूर्ण;

/*
 * Preparse a big key
 */
पूर्णांक big_key_preparse(काष्ठा key_preparsed_payload *prep)
अणु
	काष्ठा path *path = (काष्ठा path *)&prep->payload.data[big_key_path];
	काष्ठा file *file;
	u8 *buf, *enckey;
	sमाप_प्रकार written;
	माप_प्रकार datalen = prep->datalen;
	माप_प्रकार enclen = datalen + CHACHA20POLY1305_AUTHTAG_SIZE;
	पूर्णांक ret;

	अगर (datalen <= 0 || datalen > 1024 * 1024 || !prep->data)
		वापस -EINVAL;

	/* Set an arbitrary quota */
	prep->quotalen = 16;

	prep->payload.data[big_key_len] = (व्योम *)(अचिन्हित दीर्घ)datalen;

	अगर (datalen > BIG_KEY_खाता_THRESHOLD) अणु
		/* Create a shmem file to store the data in.  This will permit the data
		 * to be swapped out अगर needed.
		 *
		 * File content is stored encrypted with अक्रमomly generated key.
		 * Since the key is अक्रमom क्रम each file, we can set the nonce
		 * to zero, provided we never define a ->update() call.
		 */
		loff_t pos = 0;

		buf = kvदो_स्मृति(enclen, GFP_KERNEL);
		अगर (!buf)
			वापस -ENOMEM;

		/* generate अक्रमom key */
		enckey = kदो_स्मृति(CHACHA20POLY1305_KEY_SIZE, GFP_KERNEL);
		अगर (!enckey) अणु
			ret = -ENOMEM;
			जाओ error;
		पूर्ण
		ret = get_अक्रमom_bytes_रुको(enckey, CHACHA20POLY1305_KEY_SIZE);
		अगर (unlikely(ret))
			जाओ err_enckey;

		/* encrypt data */
		chacha20poly1305_encrypt(buf, prep->data, datalen, शून्य, 0,
					 0, enckey);

		/* save aligned data to file */
		file = shmem_kernel_file_setup("", enclen, 0);
		अगर (IS_ERR(file)) अणु
			ret = PTR_ERR(file);
			जाओ err_enckey;
		पूर्ण

		written = kernel_ग_लिखो(file, buf, enclen, &pos);
		अगर (written != enclen) अणु
			ret = written;
			अगर (written >= 0)
				ret = -EIO;
			जाओ err_fput;
		पूर्ण

		/* Pin the mount and dentry to the key so that we can खोलो it again
		 * later
		 */
		prep->payload.data[big_key_data] = enckey;
		*path = file->f_path;
		path_get(path);
		fput(file);
		kvमुक्त_sensitive(buf, enclen);
	पूर्ण अन्यथा अणु
		/* Just store the data in a buffer */
		व्योम *data = kदो_स्मृति(datalen, GFP_KERNEL);

		अगर (!data)
			वापस -ENOMEM;

		prep->payload.data[big_key_data] = data;
		स_नकल(data, prep->data, prep->datalen);
	पूर्ण
	वापस 0;

err_fput:
	fput(file);
err_enckey:
	kमुक्त_sensitive(enckey);
error:
	kvमुक्त_sensitive(buf, enclen);
	वापस ret;
पूर्ण

/*
 * Clear preparsement.
 */
व्योम big_key_मुक्त_preparse(काष्ठा key_preparsed_payload *prep)
अणु
	अगर (prep->datalen > BIG_KEY_खाता_THRESHOLD) अणु
		काष्ठा path *path = (काष्ठा path *)&prep->payload.data[big_key_path];

		path_put(path);
	पूर्ण
	kमुक्त_sensitive(prep->payload.data[big_key_data]);
पूर्ण

/*
 * dispose of the links from a revoked keyring
 * - called with the key sem ग_लिखो-locked
 */
व्योम big_key_revoke(काष्ठा key *key)
अणु
	काष्ठा path *path = (काष्ठा path *)&key->payload.data[big_key_path];

	/* clear the quota */
	key_payload_reserve(key, 0);
	अगर (key_is_positive(key) &&
	    (माप_प्रकार)key->payload.data[big_key_len] > BIG_KEY_खाता_THRESHOLD)
		vfs_truncate(path, 0);
पूर्ण

/*
 * dispose of the data dangling from the corpse of a big_key key
 */
व्योम big_key_destroy(काष्ठा key *key)
अणु
	माप_प्रकार datalen = (माप_प्रकार)key->payload.data[big_key_len];

	अगर (datalen > BIG_KEY_खाता_THRESHOLD) अणु
		काष्ठा path *path = (काष्ठा path *)&key->payload.data[big_key_path];

		path_put(path);
		path->mnt = शून्य;
		path->dentry = शून्य;
	पूर्ण
	kमुक्त_sensitive(key->payload.data[big_key_data]);
	key->payload.data[big_key_data] = शून्य;
पूर्ण

/*
 * Update a big key
 */
पूर्णांक big_key_update(काष्ठा key *key, काष्ठा key_preparsed_payload *prep)
अणु
	पूर्णांक ret;

	ret = key_payload_reserve(key, prep->datalen);
	अगर (ret < 0)
		वापस ret;

	अगर (key_is_positive(key))
		big_key_destroy(key);

	वापस generic_key_instantiate(key, prep);
पूर्ण

/*
 * describe the big_key key
 */
व्योम big_key_describe(स्थिर काष्ठा key *key, काष्ठा seq_file *m)
अणु
	माप_प्रकार datalen = (माप_प्रकार)key->payload.data[big_key_len];

	seq_माला_दो(m, key->description);

	अगर (key_is_positive(key))
		seq_म_लिखो(m, ": %zu [%s]",
			   datalen,
			   datalen > BIG_KEY_खाता_THRESHOLD ? "file" : "buff");
पूर्ण

/*
 * पढ़ो the key data
 * - the key's semaphore is पढ़ो-locked
 */
दीर्घ big_key_पढ़ो(स्थिर काष्ठा key *key, अक्षर *buffer, माप_प्रकार buflen)
अणु
	माप_प्रकार datalen = (माप_प्रकार)key->payload.data[big_key_len];
	दीर्घ ret;

	अगर (!buffer || buflen < datalen)
		वापस datalen;

	अगर (datalen > BIG_KEY_खाता_THRESHOLD) अणु
		काष्ठा path *path = (काष्ठा path *)&key->payload.data[big_key_path];
		काष्ठा file *file;
		u8 *buf, *enckey = (u8 *)key->payload.data[big_key_data];
		माप_प्रकार enclen = datalen + CHACHA20POLY1305_AUTHTAG_SIZE;
		loff_t pos = 0;

		buf = kvदो_स्मृति(enclen, GFP_KERNEL);
		अगर (!buf)
			वापस -ENOMEM;

		file = dentry_खोलो(path, O_RDONLY, current_cred());
		अगर (IS_ERR(file)) अणु
			ret = PTR_ERR(file);
			जाओ error;
		पूर्ण

		/* पढ़ो file to kernel and decrypt */
		ret = kernel_पढ़ो(file, buf, enclen, &pos);
		अगर (ret != enclen) अणु
			अगर (ret >= 0)
				ret = -EIO;
			जाओ err_fput;
		पूर्ण

		ret = chacha20poly1305_decrypt(buf, buf, enclen, शून्य, 0, 0,
					       enckey) ? 0 : -EBADMSG;
		अगर (unlikely(ret))
			जाओ err_fput;

		ret = datalen;

		/* copy out decrypted data */
		स_नकल(buffer, buf, datalen);

err_fput:
		fput(file);
error:
		kvमुक्त_sensitive(buf, enclen);
	पूर्ण अन्यथा अणु
		ret = datalen;
		स_नकल(buffer, key->payload.data[big_key_data], datalen);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Register key type
 */
अटल पूर्णांक __init big_key_init(व्योम)
अणु
	वापस रेजिस्टर_key_type(&key_type_big_key);
पूर्ण

late_initcall(big_key_init);
