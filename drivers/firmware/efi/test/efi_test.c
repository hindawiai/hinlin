<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * EFI Test Driver क्रम Runसमय Services
 *
 * Copyright(C) 2012-2016 Canonical Ltd.
 *
 * This driver exports EFI runसमय services पूर्णांकerfaces पूर्णांकo userspace, which
 * allow to use and test UEFI runसमय services provided by firmware.
 *
 */

#समावेश <linux/miscdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/efi.h>
#समावेश <linux/security.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>

#समावेश "efi_test.h"

MODULE_AUTHOR("Ivan Hu <ivan.hu@canonical.com>");
MODULE_DESCRIPTION("EFI Test Driver");
MODULE_LICENSE("GPL");

/*
 * Count the bytes in 'str', including the terminating शून्य.
 *
 * Note this function वापसs the number of *bytes*, not the number of
 * ucs2 अक्षरacters.
 */
अटल अंतरभूत माप_प्रकार user_ucs2_strsize(efi_अक्षर16_t  __user *str)
अणु
	efi_अक्षर16_t *s = str, c;
	माप_प्रकार len;

	अगर (!str)
		वापस 0;

	/* Include terminating शून्य */
	len = माप(efi_अक्षर16_t);

	अगर (get_user(c, s++)) अणु
		/* Can't पढ़ो userspace memory क्रम size */
		वापस 0;
	पूर्ण

	जबतक (c != 0) अणु
		अगर (get_user(c, s++)) अणु
			/* Can't पढ़ो userspace memory क्रम size */
			वापस 0;
		पूर्ण
		len += माप(efi_अक्षर16_t);
	पूर्ण
	वापस len;
पूर्ण

/*
 * Allocate a buffer and copy a ucs2 string from user space पूर्णांकo it.
 */
अटल अंतरभूत पूर्णांक
copy_ucs2_from_user_len(efi_अक्षर16_t **dst, efi_अक्षर16_t __user *src,
			माप_प्रकार len)
अणु
	efi_अक्षर16_t *buf;

	अगर (!src) अणु
		*dst = शून्य;
		वापस 0;
	पूर्ण

	buf = memdup_user(src, len);
	अगर (IS_ERR(buf)) अणु
		*dst = शून्य;
		वापस PTR_ERR(buf);
	पूर्ण
	*dst = buf;

	वापस 0;
पूर्ण

/*
 * Count the bytes in 'str', including the terminating शून्य.
 *
 * Just a wrap क्रम user_ucs2_strsize
 */
अटल अंतरभूत पूर्णांक
get_ucs2_strsize_from_user(efi_अक्षर16_t __user *src, माप_प्रकार *len)
अणु
	*len = user_ucs2_strsize(src);
	अगर (*len == 0)
		वापस -EFAULT;

	वापस 0;
पूर्ण

/*
 * Calculate the required buffer allocation size and copy a ucs2 string
 * from user space पूर्णांकo it.
 *
 * This function dअगरfers from copy_ucs2_from_user_len() because it
 * calculates the size of the buffer to allocate by taking the length of
 * the string 'src'.
 *
 * If a non-zero value is वापसed, the caller MUST NOT access 'dst'.
 *
 * It is the caller's responsibility to free 'dst'.
 */
अटल अंतरभूत पूर्णांक
copy_ucs2_from_user(efi_अक्षर16_t **dst, efi_अक्षर16_t __user *src)
अणु
	माप_प्रकार len;

	len = user_ucs2_strsize(src);
	अगर (len == 0)
		वापस -EFAULT;
	वापस copy_ucs2_from_user_len(dst, src, len);
पूर्ण

/*
 * Copy a ucs2 string to a user buffer.
 *
 * This function is a simple wrapper around copy_to_user() that करोes
 * nothing अगर 'src' is शून्य, which is useful क्रम reducing the amount of
 * शून्य checking the caller has to करो.
 *
 * 'len' specअगरies the number of bytes to copy.
 */
अटल अंतरभूत पूर्णांक
copy_ucs2_to_user_len(efi_अक्षर16_t __user *dst, efi_अक्षर16_t *src, माप_प्रकार len)
अणु
	अगर (!src)
		वापस 0;

	वापस copy_to_user(dst, src, len);
पूर्ण

अटल दीर्घ efi_runसमय_get_variable(अचिन्हित दीर्घ arg)
अणु
	काष्ठा efi_getvariable __user *getvariable_user;
	काष्ठा efi_getvariable getvariable;
	अचिन्हित दीर्घ datasize = 0, prev_datasize, *dz;
	efi_guid_t venकरोr_guid, *vd = शून्य;
	efi_status_t status;
	efi_अक्षर16_t *name = शून्य;
	u32 attr, *at;
	व्योम *data = शून्य;
	पूर्णांक rv = 0;

	getvariable_user = (काष्ठा efi_getvariable __user *)arg;

	अगर (copy_from_user(&getvariable, getvariable_user,
			   माप(getvariable)))
		वापस -EFAULT;
	अगर (getvariable.data_size &&
	    get_user(datasize, getvariable.data_size))
		वापस -EFAULT;
	अगर (getvariable.venकरोr_guid) अणु
		अगर (copy_from_user(&venकरोr_guid, getvariable.venकरोr_guid,
					माप(venकरोr_guid)))
			वापस -EFAULT;
		vd = &venकरोr_guid;
	पूर्ण

	अगर (getvariable.variable_name) अणु
		rv = copy_ucs2_from_user(&name, getvariable.variable_name);
		अगर (rv)
			वापस rv;
	पूर्ण

	at = getvariable.attributes ? &attr : शून्य;
	dz = getvariable.data_size ? &datasize : शून्य;

	अगर (getvariable.data_size && getvariable.data) अणु
		data = kदो_स्मृति(datasize, GFP_KERNEL);
		अगर (!data) अणु
			kमुक्त(name);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	prev_datasize = datasize;
	status = efi.get_variable(name, vd, at, dz, data);
	kमुक्त(name);

	अगर (put_user(status, getvariable.status)) अणु
		rv = -EFAULT;
		जाओ out;
	पूर्ण

	अगर (status != EFI_SUCCESS) अणु
		अगर (status == EFI_BUFFER_TOO_SMALL) अणु
			अगर (dz && put_user(datasize, getvariable.data_size)) अणु
				rv = -EFAULT;
				जाओ out;
			पूर्ण
		पूर्ण
		rv = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (prev_datasize < datasize) अणु
		rv = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (data) अणु
		अगर (copy_to_user(getvariable.data, data, datasize)) अणु
			rv = -EFAULT;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (at && put_user(attr, getvariable.attributes)) अणु
		rv = -EFAULT;
		जाओ out;
	पूर्ण

	अगर (dz && put_user(datasize, getvariable.data_size))
		rv = -EFAULT;

out:
	kमुक्त(data);
	वापस rv;

पूर्ण

अटल दीर्घ efi_runसमय_set_variable(अचिन्हित दीर्घ arg)
अणु
	काष्ठा efi_setvariable __user *setvariable_user;
	काष्ठा efi_setvariable setvariable;
	efi_guid_t venकरोr_guid;
	efi_status_t status;
	efi_अक्षर16_t *name = शून्य;
	व्योम *data;
	पूर्णांक rv = 0;

	setvariable_user = (काष्ठा efi_setvariable __user *)arg;

	अगर (copy_from_user(&setvariable, setvariable_user, माप(setvariable)))
		वापस -EFAULT;
	अगर (copy_from_user(&venकरोr_guid, setvariable.venकरोr_guid,
				माप(venकरोr_guid)))
		वापस -EFAULT;

	अगर (setvariable.variable_name) अणु
		rv = copy_ucs2_from_user(&name, setvariable.variable_name);
		अगर (rv)
			वापस rv;
	पूर्ण

	data = memdup_user(setvariable.data, setvariable.data_size);
	अगर (IS_ERR(data)) अणु
		kमुक्त(name);
		वापस PTR_ERR(data);
	पूर्ण

	status = efi.set_variable(name, &venकरोr_guid,
				setvariable.attributes,
				setvariable.data_size, data);

	अगर (put_user(status, setvariable.status)) अणु
		rv = -EFAULT;
		जाओ out;
	पूर्ण

	rv = status == EFI_SUCCESS ? 0 : -EINVAL;

out:
	kमुक्त(data);
	kमुक्त(name);

	वापस rv;
पूर्ण

अटल दीर्घ efi_runसमय_get_समय(अचिन्हित दीर्घ arg)
अणु
	काष्ठा efi_समय_लो __user *समय_लो_user;
	काष्ठा efi_समय_लो  समय_लो;
	efi_status_t status;
	efi_समय_cap_t cap;
	efi_समय_प्रकार efi_समय;

	समय_लो_user = (काष्ठा efi_समय_लो __user *)arg;
	अगर (copy_from_user(&समय_लो, समय_लो_user, माप(समय_लो)))
		वापस -EFAULT;

	status = efi.get_समय(समय_लो.समय ? &efi_समय : शून्य,
			      समय_लो.capabilities ? &cap : शून्य);

	अगर (put_user(status, समय_लो.status))
		वापस -EFAULT;

	अगर (status != EFI_SUCCESS)
		वापस -EINVAL;

	अगर (समय_लो.capabilities) अणु
		efi_समय_cap_t __user *cap_local;

		cap_local = (efi_समय_cap_t *)समय_लो.capabilities;
		अगर (put_user(cap.resolution, &(cap_local->resolution)) ||
			put_user(cap.accuracy, &(cap_local->accuracy)) ||
			put_user(cap.sets_to_zero, &(cap_local->sets_to_zero)))
			वापस -EFAULT;
	पूर्ण
	अगर (समय_लो.समय) अणु
		अगर (copy_to_user(समय_लो.समय, &efi_समय, माप(efi_समय_प्रकार)))
			वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

अटल दीर्घ efi_runसमय_set_समय(अचिन्हित दीर्घ arg)
अणु
	काष्ठा efi_समय_रखो __user *समय_रखो_user;
	काष्ठा efi_समय_रखो समय_रखो;
	efi_status_t status;
	efi_समय_प्रकार efi_समय;

	समय_रखो_user = (काष्ठा efi_समय_रखो __user *)arg;
	अगर (copy_from_user(&समय_रखो, समय_रखो_user, माप(समय_रखो)))
		वापस -EFAULT;
	अगर (copy_from_user(&efi_समय, समय_रखो.समय,
					माप(efi_समय_प्रकार)))
		वापस -EFAULT;
	status = efi.set_समय(&efi_समय);

	अगर (put_user(status, समय_रखो.status))
		वापस -EFAULT;

	वापस status == EFI_SUCCESS ? 0 : -EINVAL;
पूर्ण

अटल दीर्घ efi_runसमय_get_wakeसमय(अचिन्हित दीर्घ arg)
अणु
	काष्ठा efi_getwakeupसमय __user *getwakeupसमय_user;
	काष्ठा efi_getwakeupसमय getwakeupसमय;
	efi_bool_t enabled, pending;
	efi_status_t status;
	efi_समय_प्रकार efi_समय;

	getwakeupसमय_user = (काष्ठा efi_getwakeupसमय __user *)arg;
	अगर (copy_from_user(&getwakeupसमय, getwakeupसमय_user,
				माप(getwakeupसमय)))
		वापस -EFAULT;

	status = efi.get_wakeup_समय(
		getwakeupसमय.enabled ? (efi_bool_t *)&enabled : शून्य,
		getwakeupसमय.pending ? (efi_bool_t *)&pending : शून्य,
		getwakeupसमय.समय ? &efi_समय : शून्य);

	अगर (put_user(status, getwakeupसमय.status))
		वापस -EFAULT;

	अगर (status != EFI_SUCCESS)
		वापस -EINVAL;

	अगर (getwakeupसमय.enabled && put_user(enabled,
						getwakeupसमय.enabled))
		वापस -EFAULT;

	अगर (getwakeupसमय.समय) अणु
		अगर (copy_to_user(getwakeupसमय.समय, &efi_समय,
				माप(efi_समय_प्रकार)))
			वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

अटल दीर्घ efi_runसमय_set_wakeसमय(अचिन्हित दीर्घ arg)
अणु
	काष्ठा efi_setwakeupसमय __user *setwakeupसमय_user;
	काष्ठा efi_setwakeupसमय setwakeupसमय;
	efi_bool_t enabled;
	efi_status_t status;
	efi_समय_प्रकार efi_समय;

	setwakeupसमय_user = (काष्ठा efi_setwakeupसमय __user *)arg;

	अगर (copy_from_user(&setwakeupसमय, setwakeupसमय_user,
				माप(setwakeupसमय)))
		वापस -EFAULT;

	enabled = setwakeupसमय.enabled;
	अगर (setwakeupसमय.समय) अणु
		अगर (copy_from_user(&efi_समय, setwakeupसमय.समय,
					माप(efi_समय_प्रकार)))
			वापस -EFAULT;

		status = efi.set_wakeup_समय(enabled, &efi_समय);
	पूर्ण अन्यथा
		status = efi.set_wakeup_समय(enabled, शून्य);

	अगर (put_user(status, setwakeupसमय.status))
		वापस -EFAULT;

	वापस status == EFI_SUCCESS ? 0 : -EINVAL;
पूर्ण

अटल दीर्घ efi_runसमय_get_nextvariablename(अचिन्हित दीर्घ arg)
अणु
	काष्ठा efi_getnextvariablename __user *getnextvariablename_user;
	काष्ठा efi_getnextvariablename getnextvariablename;
	अचिन्हित दीर्घ name_size, prev_name_size = 0, *ns = शून्य;
	efi_status_t status;
	efi_guid_t *vd = शून्य;
	efi_guid_t venकरोr_guid;
	efi_अक्षर16_t *name = शून्य;
	पूर्णांक rv = 0;

	getnextvariablename_user = (काष्ठा efi_getnextvariablename __user *)arg;

	अगर (copy_from_user(&getnextvariablename, getnextvariablename_user,
			   माप(getnextvariablename)))
		वापस -EFAULT;

	अगर (getnextvariablename.variable_name_size) अणु
		अगर (get_user(name_size, getnextvariablename.variable_name_size))
			वापस -EFAULT;
		ns = &name_size;
		prev_name_size = name_size;
	पूर्ण

	अगर (getnextvariablename.venकरोr_guid) अणु
		अगर (copy_from_user(&venकरोr_guid,
				getnextvariablename.venकरोr_guid,
				माप(venकरोr_guid)))
			वापस -EFAULT;
		vd = &venकरोr_guid;
	पूर्ण

	अगर (getnextvariablename.variable_name) अणु
		माप_प्रकार name_string_size = 0;

		rv = get_ucs2_strsize_from_user(
				getnextvariablename.variable_name,
				&name_string_size);
		अगर (rv)
			वापस rv;
		/*
		 * The name_size may be smaller than the real buffer size where
		 * variable name located in some use हालs. The most typical
		 * हाल is passing a 0 to get the required buffer size क्रम the
		 * 1st समय call. So we need to copy the content from user
		 * space क्रम at least the string size of variable name, or अन्यथा
		 * the name passed to UEFI may not be terminated as we expected.
		 */
		rv = copy_ucs2_from_user_len(&name,
				getnextvariablename.variable_name,
				prev_name_size > name_string_size ?
				prev_name_size : name_string_size);
		अगर (rv)
			वापस rv;
	पूर्ण

	status = efi.get_next_variable(ns, name, vd);

	अगर (put_user(status, getnextvariablename.status)) अणु
		rv = -EFAULT;
		जाओ out;
	पूर्ण

	अगर (status != EFI_SUCCESS) अणु
		अगर (status == EFI_BUFFER_TOO_SMALL) अणु
			अगर (ns && put_user(*ns,
				getnextvariablename.variable_name_size)) अणु
				rv = -EFAULT;
				जाओ out;
			पूर्ण
		पूर्ण
		rv = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (name) अणु
		अगर (copy_ucs2_to_user_len(getnextvariablename.variable_name,
						name, prev_name_size)) अणु
			rv = -EFAULT;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (ns) अणु
		अगर (put_user(*ns, getnextvariablename.variable_name_size)) अणु
			rv = -EFAULT;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (vd) अणु
		अगर (copy_to_user(getnextvariablename.venकरोr_guid, vd,
							माप(efi_guid_t)))
			rv = -EFAULT;
	पूर्ण

out:
	kमुक्त(name);
	वापस rv;
पूर्ण

अटल दीर्घ efi_runसमय_get_nexthighmonocount(अचिन्हित दीर्घ arg)
अणु
	काष्ठा efi_getnexthighmonotoniccount __user *getnexthighmonocount_user;
	काष्ठा efi_getnexthighmonotoniccount getnexthighmonocount;
	efi_status_t status;
	u32 count;

	getnexthighmonocount_user = (काष्ठा
			efi_getnexthighmonotoniccount __user *)arg;

	अगर (copy_from_user(&getnexthighmonocount,
			   getnexthighmonocount_user,
			   माप(getnexthighmonocount)))
		वापस -EFAULT;

	status = efi.get_next_high_mono_count(
		getnexthighmonocount.high_count ? &count : शून्य);

	अगर (put_user(status, getnexthighmonocount.status))
		वापस -EFAULT;

	अगर (status != EFI_SUCCESS)
		वापस -EINVAL;

	अगर (getnexthighmonocount.high_count &&
	    put_user(count, getnexthighmonocount.high_count))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल दीर्घ efi_runसमय_reset_प्रणाली(अचिन्हित दीर्घ arg)
अणु
	काष्ठा efi_resetप्रणाली __user *resetप्रणाली_user;
	काष्ठा efi_resetप्रणाली resetप्रणाली;
	व्योम *data = शून्य;

	resetप्रणाली_user = (काष्ठा efi_resetप्रणाली __user *)arg;
	अगर (copy_from_user(&resetप्रणाली, resetप्रणाली_user,
						माप(resetप्रणाली)))
		वापस -EFAULT;
	अगर (resetप्रणाली.data_size != 0) अणु
		data = memdup_user((व्योम *)resetप्रणाली.data,
						resetप्रणाली.data_size);
		अगर (IS_ERR(data))
			वापस PTR_ERR(data);
	पूर्ण

	efi.reset_प्रणाली(resetप्रणाली.reset_type, resetप्रणाली.status,
				resetप्रणाली.data_size, (efi_अक्षर16_t *)data);

	kमुक्त(data);
	वापस 0;
पूर्ण

अटल दीर्घ efi_runसमय_query_variableinfo(अचिन्हित दीर्घ arg)
अणु
	काष्ठा efi_queryvariableinfo __user *queryvariableinfo_user;
	काष्ठा efi_queryvariableinfo queryvariableinfo;
	efi_status_t status;
	u64 max_storage, reमुख्यing, max_size;

	queryvariableinfo_user = (काष्ठा efi_queryvariableinfo __user *)arg;

	अगर (copy_from_user(&queryvariableinfo, queryvariableinfo_user,
			   माप(queryvariableinfo)))
		वापस -EFAULT;

	status = efi.query_variable_info(queryvariableinfo.attributes,
					 &max_storage, &reमुख्यing, &max_size);

	अगर (put_user(status, queryvariableinfo.status))
		वापस -EFAULT;

	अगर (status != EFI_SUCCESS)
		वापस -EINVAL;

	अगर (put_user(max_storage,
		     queryvariableinfo.maximum_variable_storage_size))
		वापस -EFAULT;

	अगर (put_user(reमुख्यing,
		     queryvariableinfo.reमुख्यing_variable_storage_size))
		वापस -EFAULT;

	अगर (put_user(max_size, queryvariableinfo.maximum_variable_size))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल दीर्घ efi_runसमय_query_capsulecaps(अचिन्हित दीर्घ arg)
अणु
	काष्ठा efi_querycapsulecapabilities __user *qcaps_user;
	काष्ठा efi_querycapsulecapabilities qcaps;
	efi_capsule_header_t *capsules;
	efi_status_t status;
	u64 max_size;
	पूर्णांक i, reset_type;
	पूर्णांक rv = 0;

	qcaps_user = (काष्ठा efi_querycapsulecapabilities __user *)arg;

	अगर (copy_from_user(&qcaps, qcaps_user, माप(qcaps)))
		वापस -EFAULT;

	अगर (qcaps.capsule_count == अच_दीर्घ_उच्च)
		वापस -EINVAL;

	capsules = kसुस्मृति(qcaps.capsule_count + 1,
			   माप(efi_capsule_header_t), GFP_KERNEL);
	अगर (!capsules)
		वापस -ENOMEM;

	क्रम (i = 0; i < qcaps.capsule_count; i++) अणु
		efi_capsule_header_t *c;
		/*
		 * We cannot dereference qcaps.capsule_header_array directly to
		 * obtain the address of the capsule as it resides in the
		 * user space
		 */
		अगर (get_user(c, qcaps.capsule_header_array + i)) अणु
			rv = -EFAULT;
			जाओ out;
		पूर्ण
		अगर (copy_from_user(&capsules[i], c,
				माप(efi_capsule_header_t))) अणु
			rv = -EFAULT;
			जाओ out;
		पूर्ण
	पूर्ण

	qcaps.capsule_header_array = &capsules;

	status = efi.query_capsule_caps((efi_capsule_header_t **)
					qcaps.capsule_header_array,
					qcaps.capsule_count,
					&max_size, &reset_type);

	अगर (put_user(status, qcaps.status)) अणु
		rv = -EFAULT;
		जाओ out;
	पूर्ण

	अगर (status != EFI_SUCCESS) अणु
		rv = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (put_user(max_size, qcaps.maximum_capsule_size)) अणु
		rv = -EFAULT;
		जाओ out;
	पूर्ण

	अगर (put_user(reset_type, qcaps.reset_type))
		rv = -EFAULT;

out:
	kमुक्त(capsules);
	वापस rv;
पूर्ण

अटल दीर्घ efi_runसमय_get_supported_mask(अचिन्हित दीर्घ arg)
अणु
	अचिन्हित पूर्णांक __user *supported_mask;
	पूर्णांक rv = 0;

	supported_mask = (अचिन्हित पूर्णांक *)arg;

	अगर (put_user(efi.runसमय_supported_mask, supported_mask))
		rv = -EFAULT;

	वापस rv;
पूर्ण

अटल दीर्घ efi_test_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
							अचिन्हित दीर्घ arg)
अणु
	चयन (cmd) अणु
	हाल EFI_RUNTIME_GET_VARIABLE:
		वापस efi_runसमय_get_variable(arg);

	हाल EFI_RUNTIME_SET_VARIABLE:
		वापस efi_runसमय_set_variable(arg);

	हाल EFI_RUNTIME_GET_TIME:
		वापस efi_runसमय_get_समय(arg);

	हाल EFI_RUNTIME_SET_TIME:
		वापस efi_runसमय_set_समय(arg);

	हाल EFI_RUNTIME_GET_WAKETIME:
		वापस efi_runसमय_get_wakeसमय(arg);

	हाल EFI_RUNTIME_SET_WAKETIME:
		वापस efi_runसमय_set_wakeसमय(arg);

	हाल EFI_RUNTIME_GET_NEXTVARIABLENAME:
		वापस efi_runसमय_get_nextvariablename(arg);

	हाल EFI_RUNTIME_GET_NEXTHIGHMONOTONICCOUNT:
		वापस efi_runसमय_get_nexthighmonocount(arg);

	हाल EFI_RUNTIME_QUERY_VARIABLEINFO:
		वापस efi_runसमय_query_variableinfo(arg);

	हाल EFI_RUNTIME_QUERY_CAPSULECAPABILITIES:
		वापस efi_runसमय_query_capsulecaps(arg);

	हाल EFI_RUNTIME_RESET_SYSTEM:
		वापस efi_runसमय_reset_प्रणाली(arg);

	हाल EFI_RUNTIME_GET_SUPPORTED_MASK:
		वापस efi_runसमय_get_supported_mask(arg);
	पूर्ण

	वापस -ENOTTY;
पूर्ण

अटल पूर्णांक efi_test_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक ret = security_locked_करोwn(LOCKDOWN_EFI_TEST);

	अगर (ret)
		वापस ret;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;
	/*
	 * nothing special to करो here
	 * We करो accept multiple खोलो files at the same समय as we
	 * synchronize on the per call operation.
	 */
	वापस 0;
पूर्ण

अटल पूर्णांक efi_test_बंद(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस 0;
पूर्ण

/*
 *	The various file operations we support.
 */
अटल स्थिर काष्ठा file_operations efi_test_fops = अणु
	.owner		= THIS_MODULE,
	.unlocked_ioctl	= efi_test_ioctl,
	.खोलो		= efi_test_खोलो,
	.release	= efi_test_बंद,
	.llseek		= no_llseek,
पूर्ण;

अटल काष्ठा miscdevice efi_test_dev = अणु
	MISC_DYNAMIC_MINOR,
	"efi_test",
	&efi_test_fops
पूर्ण;

अटल पूर्णांक __init efi_test_init(व्योम)
अणु
	पूर्णांक ret;

	ret = misc_रेजिस्टर(&efi_test_dev);
	अगर (ret) अणु
		pr_err("efi_test: can't misc_register on minor=%d\n",
			MISC_DYNAMIC_MINOR);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास efi_test_निकास(व्योम)
अणु
	misc_deरेजिस्टर(&efi_test_dev);
पूर्ण

module_init(efi_test_init);
module_निकास(efi_test_निकास);
