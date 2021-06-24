<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2019 IBM Corporation
 * Author: Nayna Jain
 *
 *      - loads keys and hashes stored and controlled by the firmware.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/cred.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <यंत्र/secure_boot.h>
#समावेश <यंत्र/secvar.h>
#समावेश "keyring_handler.h"

/*
 * Get a certअगरicate list blob from the named secure variable.
 */
अटल __init व्योम *get_cert_list(u8 *key, अचिन्हित दीर्घ keylen, uपूर्णांक64_t *size)
अणु
	पूर्णांक rc;
	व्योम *db;

	rc = secvar_ops->get(key, keylen, शून्य, size);
	अगर (rc) अणु
		pr_err("Couldn't get size: %d\n", rc);
		वापस शून्य;
	पूर्ण

	db = kदो_स्मृति(*size, GFP_KERNEL);
	अगर (!db)
		वापस शून्य;

	rc = secvar_ops->get(key, keylen, db, size);
	अगर (rc) अणु
		kमुक्त(db);
		pr_err("Error reading %s var: %d\n", key, rc);
		वापस शून्य;
	पूर्ण

	वापस db;
पूर्ण

/*
 * Load the certs contained in the keys databases पूर्णांकo the platक्रमm trusted
 * keyring and the blacklisted X.509 cert SHA256 hashes पूर्णांकo the blacklist
 * keyring.
 */
अटल पूर्णांक __init load_घातerpc_certs(व्योम)
अणु
	व्योम *db = शून्य, *dbx = शून्य;
	uपूर्णांक64_t dbsize = 0, dbxsize = 0;
	पूर्णांक rc = 0;
	काष्ठा device_node *node;

	अगर (!secvar_ops)
		वापस -ENODEV;

	/* The following only applies क्रम the edk2-compat backend. */
	node = of_find_compatible_node(शून्य, शून्य, "ibm,edk2-compat-v1");
	अगर (!node)
		वापस -ENODEV;

	/*
	 * Get db, and dbx. They might not exist, so it isn't an error अगर we
	 * can't get them.
	 */
	db = get_cert_list("db", 3, &dbsize);
	अगर (!db) अणु
		pr_err("Couldn't get db list from firmware\n");
	पूर्ण अन्यथा अणु
		rc = parse_efi_signature_list("powerpc:db", db, dbsize,
					      get_handler_क्रम_db);
		अगर (rc)
			pr_err("Couldn't parse db signatures: %d\n", rc);
		kमुक्त(db);
	पूर्ण

	dbx = get_cert_list("dbx", 4,  &dbxsize);
	अगर (!dbx) अणु
		pr_info("Couldn't get dbx list from firmware\n");
	पूर्ण अन्यथा अणु
		rc = parse_efi_signature_list("powerpc:dbx", dbx, dbxsize,
					      get_handler_क्रम_dbx);
		अगर (rc)
			pr_err("Couldn't parse dbx signatures: %d\n", rc);
		kमुक्त(dbx);
	पूर्ण

	of_node_put(node);

	वापस rc;
पूर्ण
late_initcall(load_घातerpc_certs);
