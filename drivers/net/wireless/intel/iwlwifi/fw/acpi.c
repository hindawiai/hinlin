<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2017 Intel Deutschland GmbH
 * Copyright (C) 2019-2021 Intel Corporation
 */
#समावेश <linux/uuid.h>
#समावेश "iwl-drv.h"
#समावेश "iwl-debug.h"
#समावेश "acpi.h"
#समावेश "fw/runtime.h"

स्थिर guid_t iwl_guid = GUID_INIT(0xF21202BF, 0x8F78, 0x4DC6,
				  0xA5, 0xB3, 0x1F, 0x73,
				  0x8E, 0x28, 0x5A, 0xDE);
IWL_EXPORT_SYMBOL(iwl_guid);

स्थिर guid_t iwl_rfi_guid = GUID_INIT(0x7266172C, 0x220B, 0x4B29,
				      0x81, 0x4F, 0x75, 0xE4,
				      0xDD, 0x26, 0xB5, 0xFD);
IWL_EXPORT_SYMBOL(iwl_rfi_guid);

अटल पूर्णांक iwl_acpi_get_handle(काष्ठा device *dev, acpi_string method,
			       acpi_handle *ret_handle)
अणु
	acpi_handle root_handle;
	acpi_status status;

	root_handle = ACPI_HANDLE(dev);
	अगर (!root_handle) अणु
		IWL_DEBUG_DEV_RADIO(dev,
				    "ACPI: Could not retrieve root port handle\n");
		वापस -ENOENT;
	पूर्ण

	status = acpi_get_handle(root_handle, method, ret_handle);
	अगर (ACPI_FAILURE(status)) अणु
		IWL_DEBUG_DEV_RADIO(dev,
				    "ACPI: %s method not found\n", method);
		वापस -ENOENT;
	पूर्ण
	वापस 0;
पूर्ण

व्योम *iwl_acpi_get_object(काष्ठा device *dev, acpi_string method)
अणु
	काष्ठा acpi_buffer buf = अणुACPI_ALLOCATE_BUFFER, शून्यपूर्ण;
	acpi_handle handle;
	acpi_status status;
	पूर्णांक ret;

	ret = iwl_acpi_get_handle(dev, method, &handle);
	अगर (ret)
		वापस ERR_PTR(-ENOENT);

	/* Call the method with no arguments */
	status = acpi_evaluate_object(handle, शून्य, शून्य, &buf);
	अगर (ACPI_FAILURE(status)) अणु
		IWL_DEBUG_DEV_RADIO(dev,
				    "ACPI: %s method invocation failed (status: 0x%x)\n",
				    method, status);
		वापस ERR_PTR(-ENOENT);
	पूर्ण
	वापस buf.poपूर्णांकer;
पूर्ण
IWL_EXPORT_SYMBOL(iwl_acpi_get_object);

/*
 * Generic function क्रम evaluating a method defined in the device specअगरic
 * method (DSM) पूर्णांकerface. The वापसed acpi object must be मुक्तd by calling
 * function.
 */
अटल व्योम *iwl_acpi_get_dsm_object(काष्ठा device *dev, पूर्णांक rev, पूर्णांक func,
				     जोड़ acpi_object *args,
				     स्थिर guid_t *guid)
अणु
	जोड़ acpi_object *obj;

	obj = acpi_evaluate_dsm(ACPI_HANDLE(dev), guid, rev, func,
				args);
	अगर (!obj) अणु
		IWL_DEBUG_DEV_RADIO(dev,
				    "ACPI: DSM method invocation failed (rev: %d, func:%d)\n",
				    rev, func);
		वापस ERR_PTR(-ENOENT);
	पूर्ण
	वापस obj;
पूर्ण

/*
 * Generic function to evaluate a DSM with no arguments
 * and an पूर्णांकeger वापस value,
 * (as an पूर्णांकeger object or inside a buffer object),
 * verअगरy and assign the value in the "value" parameter.
 * वापस 0 in success and the appropriate त्रुटि_सं otherwise.
 */
अटल पूर्णांक iwl_acpi_get_dsm_पूर्णांकeger(काष्ठा device *dev, पूर्णांक rev, पूर्णांक func,
				    स्थिर guid_t *guid, u64 *value,
				    माप_प्रकार expected_size)
अणु
	जोड़ acpi_object *obj;
	पूर्णांक ret = 0;

	obj = iwl_acpi_get_dsm_object(dev, rev, func, शून्य, guid);
	अगर (IS_ERR(obj)) अणु
		IWL_DEBUG_DEV_RADIO(dev,
				    "Failed to get  DSM object. func= %d\n",
				    func);
		वापस -ENOENT;
	पूर्ण

	अगर (obj->type == ACPI_TYPE_INTEGER) अणु
		*value = obj->पूर्णांकeger.value;
	पूर्ण अन्यथा अगर (obj->type == ACPI_TYPE_BUFFER) अणु
		__le64 le_value = 0;

		अगर (WARN_ON_ONCE(expected_size > माप(le_value)))
			वापस -EINVAL;

		/* अगर the buffer size करोesn't match the expected size */
		अगर (obj->buffer.length != expected_size)
			IWL_DEBUG_DEV_RADIO(dev,
					    "ACPI: DSM invalid buffer size, padding or truncating (%d)\n",
					    obj->buffer.length);

		 /* assuming LE from Intel BIOS spec */
		स_नकल(&le_value, obj->buffer.poपूर्णांकer,
		       min_t(माप_प्रकार, expected_size, (माप_प्रकार)obj->buffer.length));
		*value = le64_to_cpu(le_value);
	पूर्ण अन्यथा अणु
		IWL_DEBUG_DEV_RADIO(dev,
				    "ACPI: DSM method did not return a valid object, type=%d\n",
				    obj->type);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	IWL_DEBUG_DEV_RADIO(dev,
			    "ACPI: DSM method evaluated: func=%d, ret=%d\n",
			    func, ret);
out:
	ACPI_FREE(obj);
	वापस ret;
पूर्ण

/*
 * Evaluate a DSM with no arguments and a u8 वापस value,
 */
पूर्णांक iwl_acpi_get_dsm_u8(काष्ठा device *dev, पूर्णांक rev, पूर्णांक func,
			स्थिर guid_t *guid, u8 *value)
अणु
	पूर्णांक ret;
	u64 val;

	ret = iwl_acpi_get_dsm_पूर्णांकeger(dev, rev, func,
				       guid, &val, माप(u8));

	अगर (ret < 0)
		वापस ret;

	/* cast val (u64) to be u8 */
	*value = (u8)val;
	वापस 0;
पूर्ण
IWL_EXPORT_SYMBOL(iwl_acpi_get_dsm_u8);

जोड़ acpi_object *iwl_acpi_get_wअगरi_pkg(काष्ठा device *dev,
					 जोड़ acpi_object *data,
					 पूर्णांक data_size, पूर्णांक *tbl_rev)
अणु
	पूर्णांक i;
	जोड़ acpi_object *wअगरi_pkg;

	/*
	 * We need at least one entry in the wअगरi package that
	 * describes the करोमुख्य, and one more entry, otherwise there's
	 * no poपूर्णांक in पढ़ोing it.
	 */
	अगर (WARN_ON_ONCE(data_size < 2))
		वापस ERR_PTR(-EINVAL);

	/*
	 * We need at least two packages, one क्रम the revision and one
	 * क्रम the data itself.  Also check that the revision is valid
	 * (i.e. it is an पूर्णांकeger (each caller has to check by itself
	 * अगर the वापसed revision is supported)).
	 */
	अगर (data->type != ACPI_TYPE_PACKAGE ||
	    data->package.count < 2 ||
	    data->package.elements[0].type != ACPI_TYPE_INTEGER) अणु
		IWL_DEBUG_DEV_RADIO(dev, "Invalid packages structure\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	*tbl_rev = data->package.elements[0].पूर्णांकeger.value;

	/* loop through all the packages to find the one क्रम WiFi */
	क्रम (i = 1; i < data->package.count; i++) अणु
		जोड़ acpi_object *करोमुख्य;

		wअगरi_pkg = &data->package.elements[i];

		/* skip entries that are not a package with the right size */
		अगर (wअगरi_pkg->type != ACPI_TYPE_PACKAGE ||
		    wअगरi_pkg->package.count != data_size)
			जारी;

		करोमुख्य = &wअगरi_pkg->package.elements[0];
		अगर (करोमुख्य->type == ACPI_TYPE_INTEGER &&
		    करोमुख्य->पूर्णांकeger.value == ACPI_WIFI_DOMAIN)
			जाओ found;
	पूर्ण

	वापस ERR_PTR(-ENOENT);

found:
	वापस wअगरi_pkg;
पूर्ण
IWL_EXPORT_SYMBOL(iwl_acpi_get_wअगरi_pkg);

पूर्णांक iwl_acpi_get_tas(काष्ठा iwl_fw_runसमय *fwrt,
		     __le32 *block_list_array,
		     पूर्णांक *block_list_size)
अणु
	जोड़ acpi_object *wअगरi_pkg, *data;
	पूर्णांक ret, tbl_rev, i;
	bool enabled;

	data = iwl_acpi_get_object(fwrt->dev, ACPI_WTAS_METHOD);
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	wअगरi_pkg = iwl_acpi_get_wअगरi_pkg(fwrt->dev, data,
					 ACPI_WTAS_WIFI_DATA_SIZE,
					 &tbl_rev);
	अगर (IS_ERR(wअगरi_pkg)) अणु
		ret = PTR_ERR(wअगरi_pkg);
		जाओ out_मुक्त;
	पूर्ण

	अगर (wअगरi_pkg->package.elements[0].type != ACPI_TYPE_INTEGER ||
	    tbl_rev != 0) अणु
		ret = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण

	enabled = !!wअगरi_pkg->package.elements[0].पूर्णांकeger.value;

	अगर (!enabled) अणु
		*block_list_size = -1;
		IWL_DEBUG_RADIO(fwrt, "TAS not enabled\n");
		ret = 0;
		जाओ out_मुक्त;
	पूर्ण

	अगर (wअगरi_pkg->package.elements[1].type != ACPI_TYPE_INTEGER ||
	    wअगरi_pkg->package.elements[1].पूर्णांकeger.value >
	    APCI_WTAS_BLACK_LIST_MAX) अणु
		IWL_DEBUG_RADIO(fwrt, "TAS invalid array size %llu\n",
				wअगरi_pkg->package.elements[1].पूर्णांकeger.value);
		ret = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण
	*block_list_size = wअगरi_pkg->package.elements[1].पूर्णांकeger.value;

	IWL_DEBUG_RADIO(fwrt, "TAS array size %d\n", *block_list_size);
	अगर (*block_list_size > APCI_WTAS_BLACK_LIST_MAX) अणु
		IWL_DEBUG_RADIO(fwrt, "TAS invalid array size value %u\n",
				*block_list_size);
		ret = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण

	क्रम (i = 0; i < *block_list_size; i++) अणु
		u32 country;

		अगर (wअगरi_pkg->package.elements[2 + i].type !=
		    ACPI_TYPE_INTEGER) अणु
			IWL_DEBUG_RADIO(fwrt,
					"TAS invalid array elem %d\n", 2 + i);
			ret = -EINVAL;
			जाओ out_मुक्त;
		पूर्ण

		country = wअगरi_pkg->package.elements[2 + i].पूर्णांकeger.value;
		block_list_array[i] = cpu_to_le32(country);
		IWL_DEBUG_RADIO(fwrt, "TAS block list country %d\n", country);
	पूर्ण

	ret = 0;
out_मुक्त:
	kमुक्त(data);
	वापस ret;
पूर्ण
IWL_EXPORT_SYMBOL(iwl_acpi_get_tas);

पूर्णांक iwl_acpi_get_mcc(काष्ठा device *dev, अक्षर *mcc)
अणु
	जोड़ acpi_object *wअगरi_pkg, *data;
	u32 mcc_val;
	पूर्णांक ret, tbl_rev;

	data = iwl_acpi_get_object(dev, ACPI_WRDD_METHOD);
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	wअगरi_pkg = iwl_acpi_get_wअगरi_pkg(dev, data, ACPI_WRDD_WIFI_DATA_SIZE,
					 &tbl_rev);
	अगर (IS_ERR(wअगरi_pkg)) अणु
		ret = PTR_ERR(wअगरi_pkg);
		जाओ out_मुक्त;
	पूर्ण

	अगर (wअगरi_pkg->package.elements[1].type != ACPI_TYPE_INTEGER ||
	    tbl_rev != 0) अणु
		ret = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण

	mcc_val = wअगरi_pkg->package.elements[1].पूर्णांकeger.value;

	mcc[0] = (mcc_val >> 8) & 0xff;
	mcc[1] = mcc_val & 0xff;
	mcc[2] = '\0';

	ret = 0;
out_मुक्त:
	kमुक्त(data);
	वापस ret;
पूर्ण
IWL_EXPORT_SYMBOL(iwl_acpi_get_mcc);

u64 iwl_acpi_get_pwr_limit(काष्ठा device *dev)
अणु
	जोड़ acpi_object *data, *wअगरi_pkg;
	u64 dflt_pwr_limit;
	पूर्णांक tbl_rev;

	data = iwl_acpi_get_object(dev, ACPI_SPLC_METHOD);
	अगर (IS_ERR(data)) अणु
		dflt_pwr_limit = 0;
		जाओ out;
	पूर्ण

	wअगरi_pkg = iwl_acpi_get_wअगरi_pkg(dev, data,
					 ACPI_SPLC_WIFI_DATA_SIZE, &tbl_rev);
	अगर (IS_ERR(wअगरi_pkg) || tbl_rev != 0 ||
	    wअगरi_pkg->package.elements[1].पूर्णांकeger.value != ACPI_TYPE_INTEGER) अणु
		dflt_pwr_limit = 0;
		जाओ out_मुक्त;
	पूर्ण

	dflt_pwr_limit = wअगरi_pkg->package.elements[1].पूर्णांकeger.value;
out_मुक्त:
	kमुक्त(data);
out:
	वापस dflt_pwr_limit;
पूर्ण
IWL_EXPORT_SYMBOL(iwl_acpi_get_pwr_limit);

पूर्णांक iwl_acpi_get_eckv(काष्ठा device *dev, u32 *extl_clk)
अणु
	जोड़ acpi_object *wअगरi_pkg, *data;
	पूर्णांक ret, tbl_rev;

	data = iwl_acpi_get_object(dev, ACPI_ECKV_METHOD);
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	wअगरi_pkg = iwl_acpi_get_wअगरi_pkg(dev, data, ACPI_ECKV_WIFI_DATA_SIZE,
					 &tbl_rev);
	अगर (IS_ERR(wअगरi_pkg)) अणु
		ret = PTR_ERR(wअगरi_pkg);
		जाओ out_मुक्त;
	पूर्ण

	अगर (wअगरi_pkg->package.elements[1].type != ACPI_TYPE_INTEGER ||
	    tbl_rev != 0) अणु
		ret = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण

	*extl_clk = wअगरi_pkg->package.elements[1].पूर्णांकeger.value;

	ret = 0;

out_मुक्त:
	kमुक्त(data);
	वापस ret;
पूर्ण
IWL_EXPORT_SYMBOL(iwl_acpi_get_eckv);

अटल पूर्णांक iwl_sar_set_profile(जोड़ acpi_object *table,
			       काष्ठा iwl_sar_profile *profile,
			       bool enabled)
अणु
	पूर्णांक i;

	profile->enabled = enabled;

	क्रम (i = 0; i < ACPI_SAR_TABLE_SIZE; i++) अणु
		अगर (table[i].type != ACPI_TYPE_INTEGER ||
		    table[i].पूर्णांकeger.value > U8_MAX)
			वापस -EINVAL;

		profile->table[i] = table[i].पूर्णांकeger.value;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iwl_sar_fill_table(काष्ठा iwl_fw_runसमय *fwrt,
			      __le16 *per_chain, u32 n_subbands,
			      पूर्णांक prof_a, पूर्णांक prof_b)
अणु
	पूर्णांक profs[ACPI_SAR_NUM_CHAIN_LIMITS] = अणु prof_a, prof_b पूर्ण;
	पूर्णांक i, j, idx;

	क्रम (i = 0; i < ACPI_SAR_NUM_CHAIN_LIMITS; i++) अणु
		काष्ठा iwl_sar_profile *prof;

		/* करोn't allow SAR to be disabled (profile 0 means disable) */
		अगर (profs[i] == 0)
			वापस -EPERM;

		/* we are off by one, so allow up to ACPI_SAR_PROखाता_NUM */
		अगर (profs[i] > ACPI_SAR_PROखाता_NUM)
			वापस -EINVAL;

		/* profiles go from 1 to 4, so decrement to access the array */
		prof = &fwrt->sar_profiles[profs[i] - 1];

		/* अगर the profile is disabled, करो nothing */
		अगर (!prof->enabled) अणु
			IWL_DEBUG_RADIO(fwrt, "SAR profile %d is disabled.\n",
					profs[i]);
			/*
			 * अगर one of the profiles is disabled, we
			 * ignore all of them and वापस 1 to
			 * dअगरferentiate disabled from other failures.
			 */
			वापस 1;
		पूर्ण

		IWL_DEBUG_INFO(fwrt,
			       "SAR EWRD: chain %d profile index %d\n",
			       i, profs[i]);
		IWL_DEBUG_RADIO(fwrt, "  Chain[%d]:\n", i);
		क्रम (j = 0; j < n_subbands; j++) अणु
			idx = i * ACPI_SAR_NUM_SUB_BANDS + j;
			per_chain[i * n_subbands + j] =
				cpu_to_le16(prof->table[idx]);
			IWL_DEBUG_RADIO(fwrt, "    Band[%d] = %d * .125dBm\n",
					j, prof->table[idx]);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक iwl_sar_select_profile(काष्ठा iwl_fw_runसमय *fwrt,
			   __le16 *per_chain, u32 n_tables, u32 n_subbands,
			   पूर्णांक prof_a, पूर्णांक prof_b)
अणु
	पूर्णांक i, ret = 0;

	क्रम (i = 0; i < n_tables; i++) अणु
		ret = iwl_sar_fill_table(fwrt,
			 &per_chain[i * n_subbands * ACPI_SAR_NUM_CHAIN_LIMITS],
			 n_subbands, prof_a, prof_b);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण
IWL_EXPORT_SYMBOL(iwl_sar_select_profile);

पूर्णांक iwl_sar_get_wrds_table(काष्ठा iwl_fw_runसमय *fwrt)
अणु
	जोड़ acpi_object *wअगरi_pkg, *table, *data;
	bool enabled;
	पूर्णांक ret, tbl_rev;

	data = iwl_acpi_get_object(fwrt->dev, ACPI_WRDS_METHOD);
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	wअगरi_pkg = iwl_acpi_get_wअगरi_pkg(fwrt->dev, data,
					 ACPI_WRDS_WIFI_DATA_SIZE, &tbl_rev);
	अगर (IS_ERR(wअगरi_pkg)) अणु
		ret = PTR_ERR(wअगरi_pkg);
		जाओ out_मुक्त;
	पूर्ण

	अगर (tbl_rev != 0) अणु
		ret = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण

	अगर (wअगरi_pkg->package.elements[1].type != ACPI_TYPE_INTEGER) अणु
		ret = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण

	enabled = !!(wअगरi_pkg->package.elements[1].पूर्णांकeger.value);

	/* position of the actual table */
	table = &wअगरi_pkg->package.elements[2];

	/* The profile from WRDS is officially profile 1, but goes
	 * पूर्णांकo sar_profiles[0] (because we करोn't have a profile 0).
	 */
	ret = iwl_sar_set_profile(table, &fwrt->sar_profiles[0], enabled);
out_मुक्त:
	kमुक्त(data);
	वापस ret;
पूर्ण
IWL_EXPORT_SYMBOL(iwl_sar_get_wrds_table);

पूर्णांक iwl_sar_get_ewrd_table(काष्ठा iwl_fw_runसमय *fwrt)
अणु
	जोड़ acpi_object *wअगरi_pkg, *data;
	bool enabled;
	पूर्णांक i, n_profiles, tbl_rev, pos;
	पूर्णांक ret = 0;

	data = iwl_acpi_get_object(fwrt->dev, ACPI_EWRD_METHOD);
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	wअगरi_pkg = iwl_acpi_get_wअगरi_pkg(fwrt->dev, data,
					 ACPI_EWRD_WIFI_DATA_SIZE, &tbl_rev);
	अगर (IS_ERR(wअगरi_pkg)) अणु
		ret = PTR_ERR(wअगरi_pkg);
		जाओ out_मुक्त;
	पूर्ण

	अगर (tbl_rev != 0) अणु
		ret = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण

	अगर (wअगरi_pkg->package.elements[1].type != ACPI_TYPE_INTEGER ||
	    wअगरi_pkg->package.elements[2].type != ACPI_TYPE_INTEGER) अणु
		ret = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण

	enabled = !!(wअगरi_pkg->package.elements[1].पूर्णांकeger.value);
	n_profiles = wअगरi_pkg->package.elements[2].पूर्णांकeger.value;

	/*
	 * Check the validity of n_profiles.  The EWRD profiles start
	 * from index 1, so the maximum value allowed here is
	 * ACPI_SAR_PROखाताS_NUM - 1.
	 */
	अगर (n_profiles <= 0 || n_profiles >= ACPI_SAR_PROखाता_NUM) अणु
		ret = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण

	/* the tables start at element 3 */
	pos = 3;

	क्रम (i = 0; i < n_profiles; i++) अणु
		/* The EWRD profiles officially go from 2 to 4, but we
		 * save them in sar_profiles[1-3] (because we करोn't
		 * have profile 0).  So in the array we start from 1.
		 */
		ret = iwl_sar_set_profile(&wअगरi_pkg->package.elements[pos],
					  &fwrt->sar_profiles[i + 1],
					  enabled);
		अगर (ret < 0)
			अवरोध;

		/* go to the next table */
		pos += ACPI_SAR_TABLE_SIZE;
	पूर्ण

out_मुक्त:
	kमुक्त(data);
	वापस ret;
पूर्ण
IWL_EXPORT_SYMBOL(iwl_sar_get_ewrd_table);

पूर्णांक iwl_sar_get_wgds_table(काष्ठा iwl_fw_runसमय *fwrt)
अणु
	जोड़ acpi_object *wअगरi_pkg, *data;
	पूर्णांक i, j, ret, tbl_rev;
	पूर्णांक idx = 1;

	data = iwl_acpi_get_object(fwrt->dev, ACPI_WGDS_METHOD);
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	wअगरi_pkg = iwl_acpi_get_wअगरi_pkg(fwrt->dev, data,
					 ACPI_WGDS_WIFI_DATA_SIZE, &tbl_rev);

	अगर (IS_ERR(wअगरi_pkg)) अणु
		ret = PTR_ERR(wअगरi_pkg);
		जाओ out_मुक्त;
	पूर्ण

	अगर (tbl_rev > 1) अणु
		ret = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण

	fwrt->geo_rev = tbl_rev;
	क्रम (i = 0; i < ACPI_NUM_GEO_PROखाताS; i++) अणु
		क्रम (j = 0; j < ACPI_GEO_TABLE_SIZE; j++) अणु
			जोड़ acpi_object *entry;

			entry = &wअगरi_pkg->package.elements[idx++];
			अगर (entry->type != ACPI_TYPE_INTEGER ||
			    entry->पूर्णांकeger.value > U8_MAX) अणु
				ret = -EINVAL;
				जाओ out_मुक्त;
			पूर्ण

			fwrt->geo_profiles[i].values[j] = entry->पूर्णांकeger.value;
		पूर्ण
	पूर्ण
	ret = 0;
out_मुक्त:
	kमुक्त(data);
	वापस ret;
पूर्ण
IWL_EXPORT_SYMBOL(iwl_sar_get_wgds_table);

bool iwl_sar_geo_support(काष्ठा iwl_fw_runसमय *fwrt)
अणु
	/*
	 * The GEO_TX_POWER_LIMIT command is not supported on earlier
	 * firmware versions.  Unक्रमtunately, we करोn't have a TLV API
	 * flag to rely on, so rely on the major version which is in
	 * the first byte of ucode_ver.  This was implemented
	 * initially on version 38 and then backported to 17.  It was
	 * also backported to 29, but only क्रम 7265D devices.  The
	 * पूर्णांकention was to have it in 36 as well, but not all 8000
	 * family got this feature enabled.  The 8000 family is the
	 * only one using version 36, so skip this version entirely.
	 */
	वापस IWL_UCODE_SERIAL(fwrt->fw->ucode_ver) >= 38 ||
	       IWL_UCODE_SERIAL(fwrt->fw->ucode_ver) == 17 ||
	       (IWL_UCODE_SERIAL(fwrt->fw->ucode_ver) == 29 &&
		((fwrt->trans->hw_rev & CSR_HW_REV_TYPE_MSK) ==
		 CSR_HW_REV_TYPE_7265D));
पूर्ण
IWL_EXPORT_SYMBOL(iwl_sar_geo_support);

पूर्णांक iwl_sar_geo_init(काष्ठा iwl_fw_runसमय *fwrt,
		     काष्ठा iwl_per_chain_offset *table, u32 n_bands)
अणु
	पूर्णांक ret, i, j;

	अगर (!iwl_sar_geo_support(fwrt))
		वापस -EOPNOTSUPP;

	ret = iwl_sar_get_wgds_table(fwrt);
	अगर (ret < 0) अणु
		IWL_DEBUG_RADIO(fwrt,
				"Geo SAR BIOS table invalid or unavailable. (%d)\n",
				ret);
		/* we करोn't fail अगर the table is not available */
		वापस -ENOENT;
	पूर्ण

	क्रम (i = 0; i < ACPI_NUM_GEO_PROखाताS; i++) अणु
		क्रम (j = 0; j < n_bands; j++) अणु
			काष्ठा iwl_per_chain_offset *chain =
				&table[i * n_bands + j];
			u8 *value;

			अगर (j * ACPI_GEO_PER_CHAIN_SIZE >=
			    ARRAY_SIZE(fwrt->geo_profiles[0].values))
				/*
				 * Currently we only store lb an hb values, and
				 * करोn't have any special ones क्रम uhb. So leave
				 * those empty क्रम the समय being
				 */
				अवरोध;

			value = &fwrt->geo_profiles[i].values[j *
				ACPI_GEO_PER_CHAIN_SIZE];
			chain->max_tx_घातer = cpu_to_le16(value[0]);
			chain->chain_a = value[1];
			chain->chain_b = value[2];
			IWL_DEBUG_RADIO(fwrt,
					"SAR geographic profile[%d] Band[%d]: chain A = %d chain B = %d max_tx_power = %d\n",
					i, j, value[1], value[2], value[0]);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
IWL_EXPORT_SYMBOL(iwl_sar_geo_init);

अटल u32 iwl_acpi_eval_dsm_func(काष्ठा device *dev, क्रमागत iwl_dsm_funcs_rev_0 eval_func)
अणु
	जोड़ acpi_object *obj;
	u32 ret;

	obj = iwl_acpi_get_dsm_object(dev, 0,
				      eval_func, शून्य,
				      &iwl_guid);

	अगर (IS_ERR(obj)) अणु
		IWL_DEBUG_DEV_RADIO(dev,
				    "ACPI: DSM func '%d': Got Error in obj = %ld\n",
				    eval_func,
				    PTR_ERR(obj));
		वापस 0;
	पूर्ण

	अगर (obj->type != ACPI_TYPE_INTEGER) अणु
		IWL_DEBUG_DEV_RADIO(dev,
				    "ACPI: DSM func '%d' did not return a valid object, type=%d\n",
				    eval_func,
				    obj->type);
		ret = 0;
		जाओ out;
	पूर्ण

	ret = obj->पूर्णांकeger.value;
	IWL_DEBUG_DEV_RADIO(dev,
			    "ACPI: DSM method evaluated: func='%d', ret=%d\n",
			    eval_func,
			    ret);
out:
	ACPI_FREE(obj);
	वापस ret;
पूर्ण

__le32 iwl_acpi_get_lari_config_biपंचांगap(काष्ठा iwl_fw_runसमय *fwrt)
अणु
	u32 ret;
	__le32 config_biपंचांगap = 0;

	/*
	 ** Evaluate func 'DSM_FUNC_ENABLE_INDONESIA_5G2'
	 */
	ret = iwl_acpi_eval_dsm_func(fwrt->dev, DSM_FUNC_ENABLE_INDONESIA_5G2);

	अगर (ret == DSM_VALUE_INDONESIA_ENABLE)
		config_biपंचांगap |=
			cpu_to_le32(LARI_CONFIG_ENABLE_5G2_IN_INDONESIA_MSK);

	/*
	 ** Evaluate func 'DSM_FUNC_DISABLE_SRD'
	 */
	ret = iwl_acpi_eval_dsm_func(fwrt->dev, DSM_FUNC_DISABLE_SRD);

	अगर (ret == DSM_VALUE_SRD_PASSIVE)
		config_biपंचांगap |=
			cpu_to_le32(LARI_CONFIG_CHANGE_ETSI_TO_PASSIVE_MSK);

	अन्यथा अगर (ret == DSM_VALUE_SRD_DISABLE)
		config_biपंचांगap |=
			cpu_to_le32(LARI_CONFIG_CHANGE_ETSI_TO_DISABLED_MSK);

	वापस config_biपंचांगap;
पूर्ण
IWL_EXPORT_SYMBOL(iwl_acpi_get_lari_config_biपंचांगap);
