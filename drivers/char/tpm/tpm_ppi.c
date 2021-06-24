<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012-2014 Intel Corporation
 *
 * Authors:
 * Xiaoyan Zhang <xiaoyan.zhang@पूर्णांकel.com>
 * Jiang Liu <jiang.liu@linux.पूर्णांकel.com>
 * Jarkko Sakkinen <jarkko.sakkinen@linux.पूर्णांकel.com>
 *
 * Maपूर्णांकained by: <tpmdd-devel@lists.sourceक्रमge.net>
 *
 * This file contains implementation of the sysfs पूर्णांकerface क्रम PPI.
 */


#समावेश <linux/acpi.h>
#समावेश "tpm.h"

#घोषणा TPM_PPI_REVISION_ID_1	1
#घोषणा TPM_PPI_REVISION_ID_2	2
#घोषणा TPM_PPI_FN_VERSION	1
#घोषणा TPM_PPI_FN_SUBREQ	2
#घोषणा TPM_PPI_FN_GETREQ	3
#घोषणा TPM_PPI_FN_GETACT	4
#घोषणा TPM_PPI_FN_GETRSP	5
#घोषणा TPM_PPI_FN_SUBREQ2	7
#घोषणा TPM_PPI_FN_GETOPR	8
#घोषणा PPI_TPM_REQ_MAX		101 /* PPI 1.3 क्रम TPM 2 */
#घोषणा PPI_VS_REQ_START	128
#घोषणा PPI_VS_REQ_END		255

अटल स्थिर guid_t tpm_ppi_guid =
	GUID_INIT(0x3DDDFAA6, 0x361B, 0x4EB4,
		  0xA4, 0x24, 0x8D, 0x10, 0x08, 0x9D, 0x16, 0x53);

अटल bool tpm_ppi_req_has_parameter(u64 req)
अणु
	वापस req == 23;
पूर्ण

अटल अंतरभूत जोड़ acpi_object *
tpm_eval_dsm(acpi_handle ppi_handle, पूर्णांक func, acpi_object_type type,
	     जोड़ acpi_object *argv4, u64 rev)
अणु
	BUG_ON(!ppi_handle);
	वापस acpi_evaluate_dsm_typed(ppi_handle, &tpm_ppi_guid,
				       rev, func, argv4, type);
पूर्ण

अटल sमाप_प्रकार tpm_show_ppi_version(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा tpm_chip *chip = to_tpm_chip(dev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%s\n", chip->ppi_version);
पूर्ण

अटल sमाप_प्रकार tpm_show_ppi_request(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	sमाप_प्रकार size = -EINVAL;
	जोड़ acpi_object *obj;
	काष्ठा tpm_chip *chip = to_tpm_chip(dev);
	u64 rev = TPM_PPI_REVISION_ID_2;
	u64 req;

	अगर (म_भेद(chip->ppi_version, "1.2") < 0)
		rev = TPM_PPI_REVISION_ID_1;

	obj = tpm_eval_dsm(chip->acpi_dev_handle, TPM_PPI_FN_GETREQ,
			   ACPI_TYPE_PACKAGE, शून्य, rev);
	अगर (!obj)
		वापस -ENXIO;

	/*
	 * output.poपूर्णांकer should be of package type, including two पूर्णांकegers.
	 * The first is function वापस code, 0 means success and 1 means
	 * error. The second is pending TPM operation requested by the OS, 0
	 * means none and >0 means operation value.
	 */
	अगर (obj->package.count == 3 &&
	    obj->package.elements[0].type == ACPI_TYPE_INTEGER &&
	    obj->package.elements[1].type == ACPI_TYPE_INTEGER &&
	    obj->package.elements[2].type == ACPI_TYPE_INTEGER) अणु
		अगर (obj->package.elements[0].पूर्णांकeger.value)
			size = -EFAULT;
		अन्यथा अणु
			req = obj->package.elements[1].पूर्णांकeger.value;
			अगर (tpm_ppi_req_has_parameter(req))
				size = scnम_लिखो(buf, PAGE_SIZE,
				    "%llu %llu\n", req,
				    obj->package.elements[2].पूर्णांकeger.value);
			अन्यथा
				size = scnम_लिखो(buf, PAGE_SIZE,
						"%llu\n", req);
		पूर्ण
	पूर्ण अन्यथा अगर (obj->package.count == 2 &&
	    obj->package.elements[0].type == ACPI_TYPE_INTEGER &&
	    obj->package.elements[1].type == ACPI_TYPE_INTEGER) अणु
		अगर (obj->package.elements[0].पूर्णांकeger.value)
			size = -EFAULT;
		अन्यथा
			size = scnम_लिखो(buf, PAGE_SIZE, "%llu\n",
				 obj->package.elements[1].पूर्णांकeger.value);
	पूर्ण

	ACPI_FREE(obj);

	वापस size;
पूर्ण

अटल sमाप_प्रकार tpm_store_ppi_request(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	u32 req;
	u64 ret;
	पूर्णांक func = TPM_PPI_FN_SUBREQ;
	जोड़ acpi_object *obj, पंचांगp[2];
	जोड़ acpi_object argv4 = ACPI_INIT_DSM_ARGV4(2, पंचांगp);
	काष्ठा tpm_chip *chip = to_tpm_chip(dev);
	u64 rev = TPM_PPI_REVISION_ID_1;

	/*
	 * the function to submit TPM operation request to pre-os environment
	 * is updated with function index from SUBREQ to SUBREQ2 since PPI
	 * version 1.1
	 */
	अगर (acpi_check_dsm(chip->acpi_dev_handle, &tpm_ppi_guid,
			   TPM_PPI_REVISION_ID_1, 1 << TPM_PPI_FN_SUBREQ2))
		func = TPM_PPI_FN_SUBREQ2;

	/*
	 * PPI spec defines params[3].type as ACPI_TYPE_PACKAGE. Some BIOS
	 * accept buffer/string/पूर्णांकeger type, but some BIOS accept buffer/
	 * string/package type. For PPI version 1.0 and 1.1, use buffer type
	 * क्रम compatibility, and use package type since 1.2 according to spec.
	 */
	अगर (म_भेद(chip->ppi_version, "1.3") == 0) अणु
		अगर (माला_पूछो(buf, "%llu %llu", &पंचांगp[0].पूर्णांकeger.value,
			   &पंचांगp[1].पूर्णांकeger.value) != 2)
			जाओ ppi12;
		rev = TPM_PPI_REVISION_ID_2;
		पंचांगp[0].type = ACPI_TYPE_INTEGER;
		पंचांगp[1].type = ACPI_TYPE_INTEGER;
	पूर्ण अन्यथा अगर (म_भेद(chip->ppi_version, "1.2") < 0) अणु
		अगर (माला_पूछो(buf, "%d", &req) != 1)
			वापस -EINVAL;
		argv4.type = ACPI_TYPE_BUFFER;
		argv4.buffer.length = माप(req);
		argv4.buffer.poपूर्णांकer = (u8 *)&req;
	पूर्ण अन्यथा अणु
ppi12:
		argv4.package.count = 1;
		पंचांगp[0].type = ACPI_TYPE_INTEGER;
		अगर (माला_पूछो(buf, "%llu", &पंचांगp[0].पूर्णांकeger.value) != 1)
			वापस -EINVAL;
	पूर्ण

	obj = tpm_eval_dsm(chip->acpi_dev_handle, func, ACPI_TYPE_INTEGER,
			   &argv4, rev);
	अगर (!obj) अणु
		वापस -ENXIO;
	पूर्ण अन्यथा अणु
		ret = obj->पूर्णांकeger.value;
		ACPI_FREE(obj);
	पूर्ण

	अगर (ret == 0)
		वापस (acpi_status)count;

	वापस (ret == 1) ? -EPERM : -EFAULT;
पूर्ण

अटल sमाप_प्रकार tpm_show_ppi_transition_action(काष्ठा device *dev,
					      काष्ठा device_attribute *attr,
					      अक्षर *buf)
अणु
	u32 ret;
	acpi_status status;
	जोड़ acpi_object *obj = शून्य;
	जोड़ acpi_object पंचांगp = अणु
		.buffer.type = ACPI_TYPE_BUFFER,
		.buffer.length = 0,
		.buffer.poपूर्णांकer = शून्य
	पूर्ण;
	काष्ठा tpm_chip *chip = to_tpm_chip(dev);

	अटल अक्षर *info[] = अणु
		"None",
		"Shutdown",
		"Reboot",
		"OS Vendor-specific",
		"Error",
	पूर्ण;

	/*
	 * PPI spec defines params[3].type as empty package, but some platक्रमms
	 * (e.g. Capella with PPI 1.0) need पूर्णांकeger/string/buffer type, so क्रम
	 * compatibility, define params[3].type as buffer, अगर PPI version < 1.2
	 */
	अगर (म_भेद(chip->ppi_version, "1.2") < 0)
		obj = &पंचांगp;
	obj = tpm_eval_dsm(chip->acpi_dev_handle, TPM_PPI_FN_GETACT,
			   ACPI_TYPE_INTEGER, obj, TPM_PPI_REVISION_ID_1);
	अगर (!obj) अणु
		वापस -ENXIO;
	पूर्ण अन्यथा अणु
		ret = obj->पूर्णांकeger.value;
		ACPI_FREE(obj);
	पूर्ण

	अगर (ret < ARRAY_SIZE(info) - 1)
		status = scnम_लिखो(buf, PAGE_SIZE, "%d: %s\n", ret, info[ret]);
	अन्यथा
		status = scnम_लिखो(buf, PAGE_SIZE, "%d: %s\n", ret,
				   info[ARRAY_SIZE(info)-1]);
	वापस status;
पूर्ण

अटल sमाप_प्रकार tpm_show_ppi_response(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     अक्षर *buf)
अणु
	acpi_status status = -EINVAL;
	जोड़ acpi_object *obj, *ret_obj;
	u64 req, res;
	काष्ठा tpm_chip *chip = to_tpm_chip(dev);

	obj = tpm_eval_dsm(chip->acpi_dev_handle, TPM_PPI_FN_GETRSP,
			   ACPI_TYPE_PACKAGE, शून्य, TPM_PPI_REVISION_ID_1);
	अगर (!obj)
		वापस -ENXIO;

	/*
	 * parameter output.poपूर्णांकer should be of package type, including
	 * 3 पूर्णांकegers. The first means function वापस code, the second means
	 * most recent TPM operation request, and the last means response to
	 * the most recent TPM operation request. Only अगर the first is 0, and
	 * the second पूर्णांकeger is not 0, the response makes sense.
	 */
	ret_obj = obj->package.elements;
	अगर (obj->package.count < 3 ||
	    ret_obj[0].type != ACPI_TYPE_INTEGER ||
	    ret_obj[1].type != ACPI_TYPE_INTEGER ||
	    ret_obj[2].type != ACPI_TYPE_INTEGER)
		जाओ cleanup;

	अगर (ret_obj[0].पूर्णांकeger.value) अणु
		status = -EFAULT;
		जाओ cleanup;
	पूर्ण

	req = ret_obj[1].पूर्णांकeger.value;
	res = ret_obj[2].पूर्णांकeger.value;
	अगर (req) अणु
		अगर (res == 0)
			status = scnम_लिखो(buf, PAGE_SIZE, "%llu %s\n", req,
					   "0: Success");
		अन्यथा अगर (res == 0xFFFFFFF0)
			status = scnम_लिखो(buf, PAGE_SIZE, "%llu %s\n", req,
					   "0xFFFFFFF0: User Abort");
		अन्यथा अगर (res == 0xFFFFFFF1)
			status = scnम_लिखो(buf, PAGE_SIZE, "%llu %s\n", req,
					   "0xFFFFFFF1: BIOS Failure");
		अन्यथा अगर (res >= 1 && res <= 0x00000FFF)
			status = scnम_लिखो(buf, PAGE_SIZE, "%llu %llu: %s\n",
					   req, res, "Corresponding TPM error");
		अन्यथा
			status = scnम_लिखो(buf, PAGE_SIZE, "%llu %llu: %s\n",
					   req, res, "Error");
	पूर्ण अन्यथा अणु
		status = scnम_लिखो(buf, PAGE_SIZE, "%llu: %s\n",
				   req, "No Recent Request");
	पूर्ण

cleanup:
	ACPI_FREE(obj);
	वापस status;
पूर्ण

अटल sमाप_प्रकार show_ppi_operations(acpi_handle dev_handle, अक्षर *buf, u32 start,
				   u32 end)
अणु
	पूर्णांक i;
	u32 ret;
	अक्षर *str = buf;
	जोड़ acpi_object *obj, पंचांगp;
	जोड़ acpi_object argv = ACPI_INIT_DSM_ARGV4(1, &पंचांगp);

	अटल अक्षर *info[] = अणु
		"Not implemented",
		"BIOS only",
		"Blocked for OS by BIOS",
		"User required",
		"User not required",
	पूर्ण;

	अगर (!acpi_check_dsm(dev_handle, &tpm_ppi_guid, TPM_PPI_REVISION_ID_1,
			    1 << TPM_PPI_FN_GETOPR))
		वापस -EPERM;

	पंचांगp.पूर्णांकeger.type = ACPI_TYPE_INTEGER;
	क्रम (i = start; i <= end; i++) अणु
		पंचांगp.पूर्णांकeger.value = i;
		obj = tpm_eval_dsm(dev_handle, TPM_PPI_FN_GETOPR,
				   ACPI_TYPE_INTEGER, &argv,
				   TPM_PPI_REVISION_ID_1);
		अगर (!obj) अणु
			वापस -ENOMEM;
		पूर्ण अन्यथा अणु
			ret = obj->पूर्णांकeger.value;
			ACPI_FREE(obj);
		पूर्ण

		अगर (ret > 0 && ret < ARRAY_SIZE(info))
			str += scnम_लिखो(str, PAGE_SIZE, "%d %d: %s\n",
					 i, ret, info[ret]);
	पूर्ण

	वापस str - buf;
पूर्ण

अटल sमाप_प्रकार tpm_show_ppi_tcg_operations(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf)
अणु
	काष्ठा tpm_chip *chip = to_tpm_chip(dev);

	वापस show_ppi_operations(chip->acpi_dev_handle, buf, 0,
				   PPI_TPM_REQ_MAX);
पूर्ण

अटल sमाप_प्रकार tpm_show_ppi_vs_operations(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	काष्ठा tpm_chip *chip = to_tpm_chip(dev);

	वापस show_ppi_operations(chip->acpi_dev_handle, buf, PPI_VS_REQ_START,
				   PPI_VS_REQ_END);
पूर्ण

अटल DEVICE_ATTR(version, S_IRUGO, tpm_show_ppi_version, शून्य);
अटल DEVICE_ATTR(request, S_IRUGO | S_IWUSR | S_IWGRP,
		   tpm_show_ppi_request, tpm_store_ppi_request);
अटल DEVICE_ATTR(transition_action, S_IRUGO,
		   tpm_show_ppi_transition_action, शून्य);
अटल DEVICE_ATTR(response, S_IRUGO, tpm_show_ppi_response, शून्य);
अटल DEVICE_ATTR(tcg_operations, S_IRUGO, tpm_show_ppi_tcg_operations, शून्य);
अटल DEVICE_ATTR(vs_operations, S_IRUGO, tpm_show_ppi_vs_operations, शून्य);

अटल काष्ठा attribute *ppi_attrs[] = अणु
	&dev_attr_version.attr,
	&dev_attr_request.attr,
	&dev_attr_transition_action.attr,
	&dev_attr_response.attr,
	&dev_attr_tcg_operations.attr,
	&dev_attr_vs_operations.attr, शून्य,
पूर्ण;
अटल स्थिर काष्ठा attribute_group ppi_attr_grp = अणु
	.name = "ppi",
	.attrs = ppi_attrs
पूर्ण;

व्योम tpm_add_ppi(काष्ठा tpm_chip *chip)
अणु
	जोड़ acpi_object *obj;

	अगर (!chip->acpi_dev_handle)
		वापस;

	अगर (!acpi_check_dsm(chip->acpi_dev_handle, &tpm_ppi_guid,
			    TPM_PPI_REVISION_ID_1, 1 << TPM_PPI_FN_VERSION))
		वापस;

	/* Cache PPI version string. */
	obj = acpi_evaluate_dsm_typed(chip->acpi_dev_handle, &tpm_ppi_guid,
				      TPM_PPI_REVISION_ID_1,
				      TPM_PPI_FN_VERSION,
				      शून्य, ACPI_TYPE_STRING);
	अगर (obj) अणु
		strlcpy(chip->ppi_version, obj->string.poपूर्णांकer,
			माप(chip->ppi_version));
		ACPI_FREE(obj);
	पूर्ण

	chip->groups[chip->groups_cnt++] = &ppi_attr_grp;
पूर्ण
