<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2018 Intel Corporation. All rights reserved. */

#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/ndctl.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/mm.h>
#समावेश <linux/cred.h>
#समावेश <linux/key.h>
#समावेश <linux/key-type.h>
#समावेश <keys/user-type.h>
#समावेश <keys/encrypted-type.h>
#समावेश "nd-core.h"
#समावेश "nd.h"

#घोषणा NVDIMM_BASE_KEY		0
#घोषणा NVDIMM_NEW_KEY		1

अटल bool key_revalidate = true;
module_param(key_revalidate, bool, 0444);
MODULE_PARM_DESC(key_revalidate, "Require key validation at init.");

अटल स्थिर अक्षर zero_key[NVDIMM_PASSPHRASE_LEN];

अटल व्योम *key_data(काष्ठा key *key)
अणु
	काष्ठा encrypted_key_payload *epayload = dereference_key_locked(key);

	lockdep_निश्चित_held_पढ़ो(&key->sem);

	वापस epayload->decrypted_data;
पूर्ण

अटल व्योम nvdimm_put_key(काष्ठा key *key)
अणु
	अगर (!key)
		वापस;

	up_पढ़ो(&key->sem);
	key_put(key);
पूर्ण

/*
 * Retrieve kernel key क्रम DIMM and request from user space अगर
 * necessary. Returns a key held क्रम पढ़ो and must be put by
 * nvdimm_put_key() beक्रमe the usage goes out of scope.
 */
अटल काष्ठा key *nvdimm_request_key(काष्ठा nvdimm *nvdimm)
अणु
	काष्ठा key *key = शून्य;
	अटल स्थिर अक्षर NVDIMM_PREFIX[] = "nvdimm:";
	अक्षर desc[NVDIMM_KEY_DESC_LEN + माप(NVDIMM_PREFIX)];
	काष्ठा device *dev = &nvdimm->dev;

	प्र_लिखो(desc, "%s%s", NVDIMM_PREFIX, nvdimm->dimm_id);
	key = request_key(&key_type_encrypted, desc, "");
	अगर (IS_ERR(key)) अणु
		अगर (PTR_ERR(key) == -ENOKEY)
			dev_dbg(dev, "request_key() found no key\n");
		अन्यथा
			dev_dbg(dev, "request_key() upcall failed\n");
		key = शून्य;
	पूर्ण अन्यथा अणु
		काष्ठा encrypted_key_payload *epayload;

		करोwn_पढ़ो(&key->sem);
		epayload = dereference_key_locked(key);
		अगर (epayload->decrypted_datalen != NVDIMM_PASSPHRASE_LEN) अणु
			up_पढ़ो(&key->sem);
			key_put(key);
			key = शून्य;
		पूर्ण
	पूर्ण

	वापस key;
पूर्ण

अटल स्थिर व्योम *nvdimm_get_key_payload(काष्ठा nvdimm *nvdimm,
		काष्ठा key **key)
अणु
	*key = nvdimm_request_key(nvdimm);
	अगर (!*key)
		वापस zero_key;

	वापस key_data(*key);
पूर्ण

अटल काष्ठा key *nvdimm_lookup_user_key(काष्ठा nvdimm *nvdimm,
		key_serial_t id, पूर्णांक subclass)
अणु
	key_ref_t keyref;
	काष्ठा key *key;
	काष्ठा encrypted_key_payload *epayload;
	काष्ठा device *dev = &nvdimm->dev;

	keyref = lookup_user_key(id, 0, KEY_NEED_SEARCH);
	अगर (IS_ERR(keyref))
		वापस शून्य;

	key = key_ref_to_ptr(keyref);
	अगर (key->type != &key_type_encrypted) अणु
		key_put(key);
		वापस शून्य;
	पूर्ण

	dev_dbg(dev, "%s: key found: %#x\n", __func__, key_serial(key));

	करोwn_पढ़ो_nested(&key->sem, subclass);
	epayload = dereference_key_locked(key);
	अगर (epayload->decrypted_datalen != NVDIMM_PASSPHRASE_LEN) अणु
		up_पढ़ो(&key->sem);
		key_put(key);
		key = शून्य;
	पूर्ण
	वापस key;
पूर्ण

अटल स्थिर व्योम *nvdimm_get_user_key_payload(काष्ठा nvdimm *nvdimm,
		key_serial_t id, पूर्णांक subclass, काष्ठा key **key)
अणु
	*key = शून्य;
	अगर (id == 0) अणु
		अगर (subclass == NVDIMM_BASE_KEY)
			वापस zero_key;
		अन्यथा
			वापस शून्य;
	पूर्ण

	*key = nvdimm_lookup_user_key(nvdimm, id, subclass);
	अगर (!*key)
		वापस शून्य;

	वापस key_data(*key);
पूर्ण


अटल पूर्णांक nvdimm_key_revalidate(काष्ठा nvdimm *nvdimm)
अणु
	काष्ठा key *key;
	पूर्णांक rc;
	स्थिर व्योम *data;

	अगर (!nvdimm->sec.ops->change_key)
		वापस -EOPNOTSUPP;

	data = nvdimm_get_key_payload(nvdimm, &key);

	/*
	 * Send the same key to the hardware as new and old key to
	 * verअगरy that the key is good.
	 */
	rc = nvdimm->sec.ops->change_key(nvdimm, data, data, NVDIMM_USER);
	अगर (rc < 0) अणु
		nvdimm_put_key(key);
		वापस rc;
	पूर्ण

	nvdimm_put_key(key);
	nvdimm->sec.flags = nvdimm_security_flags(nvdimm, NVDIMM_USER);
	वापस 0;
पूर्ण

अटल पूर्णांक __nvdimm_security_unlock(काष्ठा nvdimm *nvdimm)
अणु
	काष्ठा device *dev = &nvdimm->dev;
	काष्ठा nvdimm_bus *nvdimm_bus = walk_to_nvdimm_bus(dev);
	काष्ठा key *key;
	स्थिर व्योम *data;
	पूर्णांक rc;

	/* The bus lock should be held at the top level of the call stack */
	lockdep_निश्चित_held(&nvdimm_bus->reconfig_mutex);

	अगर (!nvdimm->sec.ops || !nvdimm->sec.ops->unlock
			|| !nvdimm->sec.flags)
		वापस -EIO;

	/* No need to go further अगर security is disabled */
	अगर (test_bit(NVDIMM_SECURITY_DISABLED, &nvdimm->sec.flags))
		वापस 0;

	अगर (test_bit(NDD_SECURITY_OVERWRITE, &nvdimm->flags)) अणु
		dev_dbg(dev, "Security operation in progress.\n");
		वापस -EBUSY;
	पूर्ण

	/*
	 * If the pre-OS has unlocked the DIMM, attempt to send the key
	 * from request_key() to the hardware क्रम verअगरication.  Failure
	 * to revalidate the key against the hardware results in a
	 * मुक्तze of the security configuration. I.e. अगर the OS करोes not
	 * have the key, security is being managed pre-OS.
	 */
	अगर (test_bit(NVDIMM_SECURITY_UNLOCKED, &nvdimm->sec.flags)) अणु
		अगर (!key_revalidate)
			वापस 0;

		वापस nvdimm_key_revalidate(nvdimm);
	पूर्ण अन्यथा
		data = nvdimm_get_key_payload(nvdimm, &key);

	rc = nvdimm->sec.ops->unlock(nvdimm, data);
	dev_dbg(dev, "key: %d unlock: %s\n", key_serial(key),
			rc == 0 ? "success" : "fail");

	nvdimm_put_key(key);
	nvdimm->sec.flags = nvdimm_security_flags(nvdimm, NVDIMM_USER);
	वापस rc;
पूर्ण

पूर्णांक nvdimm_security_unlock(काष्ठा device *dev)
अणु
	काष्ठा nvdimm *nvdimm = to_nvdimm(dev);
	पूर्णांक rc;

	nvdimm_bus_lock(dev);
	rc = __nvdimm_security_unlock(nvdimm);
	nvdimm_bus_unlock(dev);
	वापस rc;
पूर्ण

अटल पूर्णांक check_security_state(काष्ठा nvdimm *nvdimm)
अणु
	काष्ठा device *dev = &nvdimm->dev;

	अगर (test_bit(NVDIMM_SECURITY_FROZEN, &nvdimm->sec.flags)) अणु
		dev_dbg(dev, "Incorrect security state: %#lx\n",
				nvdimm->sec.flags);
		वापस -EIO;
	पूर्ण

	अगर (test_bit(NDD_SECURITY_OVERWRITE, &nvdimm->flags)) अणु
		dev_dbg(dev, "Security operation in progress.\n");
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक security_disable(काष्ठा nvdimm *nvdimm, अचिन्हित पूर्णांक keyid)
अणु
	काष्ठा device *dev = &nvdimm->dev;
	काष्ठा nvdimm_bus *nvdimm_bus = walk_to_nvdimm_bus(dev);
	काष्ठा key *key;
	पूर्णांक rc;
	स्थिर व्योम *data;

	/* The bus lock should be held at the top level of the call stack */
	lockdep_निश्चित_held(&nvdimm_bus->reconfig_mutex);

	अगर (!nvdimm->sec.ops || !nvdimm->sec.ops->disable
			|| !nvdimm->sec.flags)
		वापस -EOPNOTSUPP;

	rc = check_security_state(nvdimm);
	अगर (rc)
		वापस rc;

	data = nvdimm_get_user_key_payload(nvdimm, keyid,
			NVDIMM_BASE_KEY, &key);
	अगर (!data)
		वापस -ENOKEY;

	rc = nvdimm->sec.ops->disable(nvdimm, data);
	dev_dbg(dev, "key: %d disable: %s\n", key_serial(key),
			rc == 0 ? "success" : "fail");

	nvdimm_put_key(key);
	nvdimm->sec.flags = nvdimm_security_flags(nvdimm, NVDIMM_USER);
	वापस rc;
पूर्ण

अटल पूर्णांक security_update(काष्ठा nvdimm *nvdimm, अचिन्हित पूर्णांक keyid,
		अचिन्हित पूर्णांक new_keyid,
		क्रमागत nvdimm_passphrase_type pass_type)
अणु
	काष्ठा device *dev = &nvdimm->dev;
	काष्ठा nvdimm_bus *nvdimm_bus = walk_to_nvdimm_bus(dev);
	काष्ठा key *key, *newkey;
	पूर्णांक rc;
	स्थिर व्योम *data, *newdata;

	/* The bus lock should be held at the top level of the call stack */
	lockdep_निश्चित_held(&nvdimm_bus->reconfig_mutex);

	अगर (!nvdimm->sec.ops || !nvdimm->sec.ops->change_key
			|| !nvdimm->sec.flags)
		वापस -EOPNOTSUPP;

	rc = check_security_state(nvdimm);
	अगर (rc)
		वापस rc;

	data = nvdimm_get_user_key_payload(nvdimm, keyid,
			NVDIMM_BASE_KEY, &key);
	अगर (!data)
		वापस -ENOKEY;

	newdata = nvdimm_get_user_key_payload(nvdimm, new_keyid,
			NVDIMM_NEW_KEY, &newkey);
	अगर (!newdata) अणु
		nvdimm_put_key(key);
		वापस -ENOKEY;
	पूर्ण

	rc = nvdimm->sec.ops->change_key(nvdimm, data, newdata, pass_type);
	dev_dbg(dev, "key: %d %d update%s: %s\n",
			key_serial(key), key_serial(newkey),
			pass_type == NVDIMM_MASTER ? "(master)" : "(user)",
			rc == 0 ? "success" : "fail");

	nvdimm_put_key(newkey);
	nvdimm_put_key(key);
	अगर (pass_type == NVDIMM_MASTER)
		nvdimm->sec.ext_flags = nvdimm_security_flags(nvdimm,
				NVDIMM_MASTER);
	अन्यथा
		nvdimm->sec.flags = nvdimm_security_flags(nvdimm,
				NVDIMM_USER);
	वापस rc;
पूर्ण

अटल पूर्णांक security_erase(काष्ठा nvdimm *nvdimm, अचिन्हित पूर्णांक keyid,
		क्रमागत nvdimm_passphrase_type pass_type)
अणु
	काष्ठा device *dev = &nvdimm->dev;
	काष्ठा nvdimm_bus *nvdimm_bus = walk_to_nvdimm_bus(dev);
	काष्ठा key *key = शून्य;
	पूर्णांक rc;
	स्थिर व्योम *data;

	/* The bus lock should be held at the top level of the call stack */
	lockdep_निश्चित_held(&nvdimm_bus->reconfig_mutex);

	अगर (!nvdimm->sec.ops || !nvdimm->sec.ops->erase
			|| !nvdimm->sec.flags)
		वापस -EOPNOTSUPP;

	rc = check_security_state(nvdimm);
	अगर (rc)
		वापस rc;

	अगर (!test_bit(NVDIMM_SECURITY_UNLOCKED, &nvdimm->sec.ext_flags)
			&& pass_type == NVDIMM_MASTER) अणु
		dev_dbg(dev,
			"Attempt to secure erase in wrong master state.\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	data = nvdimm_get_user_key_payload(nvdimm, keyid,
			NVDIMM_BASE_KEY, &key);
	अगर (!data)
		वापस -ENOKEY;

	rc = nvdimm->sec.ops->erase(nvdimm, data, pass_type);
	dev_dbg(dev, "key: %d erase%s: %s\n", key_serial(key),
			pass_type == NVDIMM_MASTER ? "(master)" : "(user)",
			rc == 0 ? "success" : "fail");

	nvdimm_put_key(key);
	nvdimm->sec.flags = nvdimm_security_flags(nvdimm, NVDIMM_USER);
	वापस rc;
पूर्ण

अटल पूर्णांक security_overग_लिखो(काष्ठा nvdimm *nvdimm, अचिन्हित पूर्णांक keyid)
अणु
	काष्ठा device *dev = &nvdimm->dev;
	काष्ठा nvdimm_bus *nvdimm_bus = walk_to_nvdimm_bus(dev);
	काष्ठा key *key = शून्य;
	पूर्णांक rc;
	स्थिर व्योम *data;

	/* The bus lock should be held at the top level of the call stack */
	lockdep_निश्चित_held(&nvdimm_bus->reconfig_mutex);

	अगर (!nvdimm->sec.ops || !nvdimm->sec.ops->overग_लिखो
			|| !nvdimm->sec.flags)
		वापस -EOPNOTSUPP;

	अगर (dev->driver == शून्य) अणु
		dev_dbg(dev, "Unable to overwrite while DIMM active.\n");
		वापस -EINVAL;
	पूर्ण

	rc = check_security_state(nvdimm);
	अगर (rc)
		वापस rc;

	data = nvdimm_get_user_key_payload(nvdimm, keyid,
			NVDIMM_BASE_KEY, &key);
	अगर (!data)
		वापस -ENOKEY;

	rc = nvdimm->sec.ops->overग_लिखो(nvdimm, data);
	dev_dbg(dev, "key: %d overwrite submission: %s\n", key_serial(key),
			rc == 0 ? "success" : "fail");

	nvdimm_put_key(key);
	अगर (rc == 0) अणु
		set_bit(NDD_SECURITY_OVERWRITE, &nvdimm->flags);
		set_bit(NDD_WORK_PENDING, &nvdimm->flags);
		set_bit(NVDIMM_SECURITY_OVERWRITE, &nvdimm->sec.flags);
		/*
		 * Make sure we करोn't lose device जबतक करोing overग_लिखो
		 * query.
		 */
		get_device(dev);
		queue_delayed_work(प्रणाली_wq, &nvdimm->dwork, 0);
	पूर्ण

	वापस rc;
पूर्ण

व्योम __nvdimm_security_overग_लिखो_query(काष्ठा nvdimm *nvdimm)
अणु
	काष्ठा nvdimm_bus *nvdimm_bus = walk_to_nvdimm_bus(&nvdimm->dev);
	पूर्णांक rc;
	अचिन्हित पूर्णांक पंचांगo;

	/* The bus lock should be held at the top level of the call stack */
	lockdep_निश्चित_held(&nvdimm_bus->reconfig_mutex);

	/*
	 * Abort and release device अगर we no दीर्घer have the overग_लिखो
	 * flag set. It means the work has been canceled.
	 */
	अगर (!test_bit(NDD_WORK_PENDING, &nvdimm->flags))
		वापस;

	पंचांगo = nvdimm->sec.overग_लिखो_पंचांगo;

	अगर (!nvdimm->sec.ops || !nvdimm->sec.ops->query_overग_लिखो
			|| !nvdimm->sec.flags)
		वापस;

	rc = nvdimm->sec.ops->query_overग_लिखो(nvdimm);
	अगर (rc == -EBUSY) अणु

		/* setup delayed work again */
		पंचांगo += 10;
		queue_delayed_work(प्रणाली_wq, &nvdimm->dwork, पंचांगo * HZ);
		nvdimm->sec.overग_लिखो_पंचांगo = min(15U * 60U, पंचांगo);
		वापस;
	पूर्ण

	अगर (rc < 0)
		dev_dbg(&nvdimm->dev, "overwrite failed\n");
	अन्यथा
		dev_dbg(&nvdimm->dev, "overwrite completed\n");

	/*
	 * Mark the overग_लिखो work करोne and update dimm security flags,
	 * then send a sysfs event notअगरication to wake up userspace
	 * poll thपढ़ोs to picked up the changed state.
	 */
	nvdimm->sec.overग_लिखो_पंचांगo = 0;
	clear_bit(NDD_SECURITY_OVERWRITE, &nvdimm->flags);
	clear_bit(NDD_WORK_PENDING, &nvdimm->flags);
	nvdimm->sec.flags = nvdimm_security_flags(nvdimm, NVDIMM_USER);
	nvdimm->sec.ext_flags = nvdimm_security_flags(nvdimm, NVDIMM_MASTER);
	अगर (nvdimm->sec.overग_लिखो_state)
		sysfs_notअगरy_dirent(nvdimm->sec.overग_लिखो_state);
	put_device(&nvdimm->dev);
पूर्ण

व्योम nvdimm_security_overग_लिखो_query(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nvdimm *nvdimm =
		container_of(work, typeof(*nvdimm), dwork.work);

	nvdimm_bus_lock(&nvdimm->dev);
	__nvdimm_security_overग_लिखो_query(nvdimm);
	nvdimm_bus_unlock(&nvdimm->dev);
पूर्ण

#घोषणा OPS							\
	C( OP_FREEZE,		"freeze",		1),	\
	C( OP_DISABLE,		"disable",		2),	\
	C( OP_UPDATE,		"update",		3),	\
	C( OP_ERASE,		"erase",		2),	\
	C( OP_OVERWRITE,	"overwrite",		2),	\
	C( OP_MASTER_UPDATE,	"master_update",	3),	\
	C( OP_MASTER_ERASE,	"master_erase",		2)
#अघोषित C
#घोषणा C(a, b, c) a
क्रमागत nvdimmsec_op_ids अणु OPS पूर्ण;
#अघोषित C
#घोषणा C(a, b, c) अणु b, c पूर्ण
अटल काष्ठा अणु
	स्थिर अक्षर *name;
	पूर्णांक args;
पूर्ण ops[] = अणु OPS पूर्ण;
#अघोषित C

#घोषणा SEC_CMD_SIZE 32
#घोषणा KEY_ID_SIZE 10

sमाप_प्रकार nvdimm_security_store(काष्ठा device *dev, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा nvdimm *nvdimm = to_nvdimm(dev);
	sमाप_प्रकार rc;
	अक्षर cmd[SEC_CMD_SIZE+1], keystr[KEY_ID_SIZE+1],
		nkeystr[KEY_ID_SIZE+1];
	अचिन्हित पूर्णांक key, newkey;
	पूर्णांक i;

	rc = माला_पूछो(buf, "%"__stringअगरy(SEC_CMD_SIZE)"s"
			" %"__stringअगरy(KEY_ID_SIZE)"s"
			" %"__stringअगरy(KEY_ID_SIZE)"s",
			cmd, keystr, nkeystr);
	अगर (rc < 1)
		वापस -EINVAL;
	क्रम (i = 0; i < ARRAY_SIZE(ops); i++)
		अगर (sysfs_streq(cmd, ops[i].name))
			अवरोध;
	अगर (i >= ARRAY_SIZE(ops))
		वापस -EINVAL;
	अगर (ops[i].args > 1)
		rc = kstrtouपूर्णांक(keystr, 0, &key);
	अगर (rc >= 0 && ops[i].args > 2)
		rc = kstrtouपूर्णांक(nkeystr, 0, &newkey);
	अगर (rc < 0)
		वापस rc;

	अगर (i == OP_FREEZE) अणु
		dev_dbg(dev, "freeze\n");
		rc = nvdimm_security_मुक्तze(nvdimm);
	पूर्ण अन्यथा अगर (i == OP_DISABLE) अणु
		dev_dbg(dev, "disable %u\n", key);
		rc = security_disable(nvdimm, key);
	पूर्ण अन्यथा अगर (i == OP_UPDATE || i == OP_MASTER_UPDATE) अणु
		dev_dbg(dev, "%s %u %u\n", ops[i].name, key, newkey);
		rc = security_update(nvdimm, key, newkey, i == OP_UPDATE
				? NVDIMM_USER : NVDIMM_MASTER);
	पूर्ण अन्यथा अगर (i == OP_ERASE || i == OP_MASTER_ERASE) अणु
		dev_dbg(dev, "%s %u\n", ops[i].name, key);
		अगर (atomic_पढ़ो(&nvdimm->busy)) अणु
			dev_dbg(dev, "Unable to secure erase while DIMM active.\n");
			वापस -EBUSY;
		पूर्ण
		rc = security_erase(nvdimm, key, i == OP_ERASE
				? NVDIMM_USER : NVDIMM_MASTER);
	पूर्ण अन्यथा अगर (i == OP_OVERWRITE) अणु
		dev_dbg(dev, "overwrite %u\n", key);
		अगर (atomic_पढ़ो(&nvdimm->busy)) अणु
			dev_dbg(dev, "Unable to overwrite while DIMM active.\n");
			वापस -EBUSY;
		पूर्ण
		rc = security_overग_लिखो(nvdimm, key);
	पूर्ण अन्यथा
		वापस -EINVAL;

	अगर (rc == 0)
		rc = len;
	वापस rc;
पूर्ण
