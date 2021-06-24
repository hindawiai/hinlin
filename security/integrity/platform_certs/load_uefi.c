<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/cred.h>
#समावेश <linux/err.h>
#समावेश <linux/efi.h>
#समावेश <linux/slab.h>
#समावेश <keys/asymmetric-type.h>
#समावेश <keys/प्रणाली_keyring.h>
#समावेश "../integrity.h"
#समावेश "keyring_handler.h"

/*
 * Look to see अगर a UEFI variable called MokIgnoreDB exists and वापस true अगर
 * it करोes.
 *
 * This UEFI variable is set by the shim अगर a user tells the shim to not use
 * the certs/hashes in the UEFI db variable क्रम verअगरication purposes.  If it
 * is set, we should ignore the db variable also and the true वापस indicates
 * this.
 */
अटल __init bool uefi_check_ignore_db(व्योम)
अणु
	efi_status_t status;
	अचिन्हित पूर्णांक db = 0;
	अचिन्हित दीर्घ size = माप(db);
	efi_guid_t guid = EFI_SHIM_LOCK_GUID;

	status = efi.get_variable(L"MokIgnoreDB", &guid, शून्य, &size, &db);
	वापस status == EFI_SUCCESS;
पूर्ण

/*
 * Get a certअगरicate list blob from the named EFI variable.
 */
अटल __init व्योम *get_cert_list(efi_अक्षर16_t *name, efi_guid_t *guid,
				  अचिन्हित दीर्घ *size, efi_status_t *status)
अणु
	अचिन्हित दीर्घ lsize = 4;
	अचिन्हित दीर्घ पंचांगpdb[4];
	व्योम *db;

	*status = efi.get_variable(name, guid, शून्य, &lsize, &पंचांगpdb);
	अगर (*status == EFI_NOT_FOUND)
		वापस शून्य;

	अगर (*status != EFI_BUFFER_TOO_SMALL) अणु
		pr_err("Couldn't get size: 0x%lx\n", *status);
		वापस शून्य;
	पूर्ण

	db = kदो_स्मृति(lsize, GFP_KERNEL);
	अगर (!db)
		वापस शून्य;

	*status = efi.get_variable(name, guid, शून्य, &lsize, db);
	अगर (*status != EFI_SUCCESS) अणु
		kमुक्त(db);
		pr_err("Error reading db var: 0x%lx\n", *status);
		वापस शून्य;
	पूर्ण

	*size = lsize;
	वापस db;
पूर्ण

/*
 * load_moklist_certs() - Load MokList certs
 *
 * Load the certs contained in the UEFI MokListRT database पूर्णांकo the
 * platक्रमm trusted keyring.
 *
 * This routine checks the EFI MOK config table first. If and only अगर
 * that fails, this routine uses the MokListRT ordinary UEFI variable.
 *
 * Return:	Status
 */
अटल पूर्णांक __init load_moklist_certs(व्योम)
अणु
	काष्ठा efi_mokvar_table_entry *mokvar_entry;
	efi_guid_t mok_var = EFI_SHIM_LOCK_GUID;
	व्योम *mok;
	अचिन्हित दीर्घ moksize;
	efi_status_t status;
	पूर्णांक rc;

	/* First try to load certs from the EFI MOKvar config table.
	 * It's not an error if the MOKvar config table doesn't exist
	 * or the MokListRT entry is not found in it.
	 */
	mokvar_entry = efi_mokvar_entry_find("MokListRT");
	अगर (mokvar_entry) अणु
		rc = parse_efi_signature_list("UEFI:MokListRT (MOKvar table)",
					      mokvar_entry->data,
					      mokvar_entry->data_size,
					      get_handler_क्रम_db);
		/* All करोne अगर that worked. */
		अगर (!rc)
			वापस rc;

		pr_err("Couldn't parse MokListRT signatures from EFI MOKvar config table: %d\n",
		       rc);
	पूर्ण

	/* Get MokListRT. It might not exist, so it isn't an error
	 * अगर we can't get it.
	 */
	mok = get_cert_list(L"MokListRT", &mok_var, &moksize, &status);
	अगर (mok) अणु
		rc = parse_efi_signature_list("UEFI:MokListRT",
					      mok, moksize, get_handler_क्रम_db);
		kमुक्त(mok);
		अगर (rc)
			pr_err("Couldn't parse MokListRT signatures: %d\n", rc);
		वापस rc;
	पूर्ण
	अगर (status == EFI_NOT_FOUND)
		pr_debug("MokListRT variable wasn't found\n");
	अन्यथा
		pr_info("Couldn't get UEFI MokListRT\n");
	वापस 0;
पूर्ण

/*
 * load_uefi_certs() - Load certs from UEFI sources
 *
 * Load the certs contained in the UEFI databases पूर्णांकo the platक्रमm trusted
 * keyring and the UEFI blacklisted X.509 cert SHA256 hashes पूर्णांकo the blacklist
 * keyring.
 */
अटल पूर्णांक __init load_uefi_certs(व्योम)
अणु
	efi_guid_t secure_var = EFI_IMAGE_SECURITY_DATABASE_GUID;
	efi_guid_t mok_var = EFI_SHIM_LOCK_GUID;
	व्योम *db = शून्य, *dbx = शून्य, *mokx = शून्य;
	अचिन्हित दीर्घ dbsize = 0, dbxsize = 0, mokxsize = 0;
	efi_status_t status;
	पूर्णांक rc = 0;

	अगर (!efi_rt_services_supported(EFI_RT_SUPPORTED_GET_VARIABLE))
		वापस false;

	/* Get db and dbx.  They might not exist, so it isn't an error
	 * अगर we can't get them.
	 */
	अगर (!uefi_check_ignore_db()) अणु
		db = get_cert_list(L"db", &secure_var, &dbsize, &status);
		अगर (!db) अणु
			अगर (status == EFI_NOT_FOUND)
				pr_debug("MODSIGN: db variable wasn't found\n");
			अन्यथा
				pr_err("MODSIGN: Couldn't get UEFI db list\n");
		पूर्ण अन्यथा अणु
			rc = parse_efi_signature_list("UEFI:db",
					db, dbsize, get_handler_क्रम_db);
			अगर (rc)
				pr_err("Couldn't parse db signatures: %d\n",
				       rc);
			kमुक्त(db);
		पूर्ण
	पूर्ण

	dbx = get_cert_list(L"dbx", &secure_var, &dbxsize, &status);
	अगर (!dbx) अणु
		अगर (status == EFI_NOT_FOUND)
			pr_debug("dbx variable wasn't found\n");
		अन्यथा
			pr_info("Couldn't get UEFI dbx list\n");
	पूर्ण अन्यथा अणु
		rc = parse_efi_signature_list("UEFI:dbx",
					      dbx, dbxsize,
					      get_handler_क्रम_dbx);
		अगर (rc)
			pr_err("Couldn't parse dbx signatures: %d\n", rc);
		kमुक्त(dbx);
	पूर्ण

	mokx = get_cert_list(L"MokListXRT", &mok_var, &mokxsize, &status);
	अगर (!mokx) अणु
		अगर (status == EFI_NOT_FOUND)
			pr_debug("mokx variable wasn't found\n");
		अन्यथा
			pr_info("Couldn't get mokx list\n");
	पूर्ण अन्यथा अणु
		rc = parse_efi_signature_list("UEFI:MokListXRT",
					      mokx, mokxsize,
					      get_handler_क्रम_dbx);
		अगर (rc)
			pr_err("Couldn't parse mokx signatures %d\n", rc);
		kमुक्त(mokx);
	पूर्ण

	/* Load the MokListRT certs */
	rc = load_moklist_certs();

	वापस rc;
पूर्ण
late_initcall(load_uefi_certs);
