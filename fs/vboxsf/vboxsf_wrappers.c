<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Wrapper functions क्रम the shfl host calls.
 *
 * Copyright (C) 2006-2018 Oracle Corporation
 */

#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/vbox_err.h>
#समावेश <linux/vbox_utils.h>
#समावेश "vfsmod.h"

#घोषणा SHFL_REQUEST \
	(VMMDEV_REQUESTOR_KERNEL | VMMDEV_REQUESTOR_USR_DRV_OTHER | \
	 VMMDEV_REQUESTOR_CON_DONT_KNOW | VMMDEV_REQUESTOR_TRUST_NOT_GIVEN)

अटल u32 vboxsf_client_id;

पूर्णांक vboxsf_connect(व्योम)
अणु
	काष्ठा vbg_dev *gdev;
	काष्ठा vmmdev_hgcm_service_location loc;
	पूर्णांक err, vbox_status;

	loc.type = VMMDEV_HGCM_LOC_LOCALHOST_EXISTING;
	म_नकल(loc.u.localhost.service_name, "VBoxSharedFolders");

	gdev = vbg_get_gdev();
	अगर (IS_ERR(gdev))
		वापस -ENODEV;	/* No guest-device */

	err = vbg_hgcm_connect(gdev, SHFL_REQUEST, &loc,
			       &vboxsf_client_id, &vbox_status);
	vbg_put_gdev(gdev);

	वापस err ? err : vbg_status_code_to_त्रुटि_सं(vbox_status);
पूर्ण

व्योम vboxsf_disconnect(व्योम)
अणु
	काष्ठा vbg_dev *gdev;
	पूर्णांक vbox_status;

	gdev = vbg_get_gdev();
	अगर (IS_ERR(gdev))
		वापस;   /* guest-device is gone, alपढ़ोy disconnected */

	vbg_hgcm_disconnect(gdev, SHFL_REQUEST, vboxsf_client_id, &vbox_status);
	vbg_put_gdev(gdev);
पूर्ण

अटल पूर्णांक vboxsf_call(u32 function, व्योम *parms, u32 parm_count, पूर्णांक *status)
अणु
	काष्ठा vbg_dev *gdev;
	पूर्णांक err, vbox_status;

	gdev = vbg_get_gdev();
	अगर (IS_ERR(gdev))
		वापस -ESHUTDOWN; /* guest-dev हटाओd underneath us */

	err = vbg_hgcm_call(gdev, SHFL_REQUEST, vboxsf_client_id, function,
			    U32_MAX, parms, parm_count, &vbox_status);
	vbg_put_gdev(gdev);

	अगर (err < 0)
		वापस err;

	अगर (status)
		*status = vbox_status;

	वापस vbg_status_code_to_त्रुटि_सं(vbox_status);
पूर्ण

पूर्णांक vboxsf_map_folder(काष्ठा shfl_string *folder_name, u32 *root)
अणु
	काष्ठा shfl_map_folder parms;
	पूर्णांक err, status;

	parms.path.type = VMMDEV_HGCM_PARM_TYPE_LINADDR_KERNEL;
	parms.path.u.poपूर्णांकer.size = shfl_string_buf_size(folder_name);
	parms.path.u.poपूर्णांकer.u.linear_addr = (uपूर्णांकptr_t)folder_name;

	parms.root.type = VMMDEV_HGCM_PARM_TYPE_32BIT;
	parms.root.u.value32 = 0;

	parms.delimiter.type = VMMDEV_HGCM_PARM_TYPE_32BIT;
	parms.delimiter.u.value32 = '/';

	parms.हाल_sensitive.type = VMMDEV_HGCM_PARM_TYPE_32BIT;
	parms.हाल_sensitive.u.value32 = 1;

	err = vboxsf_call(SHFL_FN_MAP_FOLDER, &parms, SHFL_CPARMS_MAP_FOLDER,
			  &status);
	अगर (err == -ENOSYS && status == VERR_NOT_IMPLEMENTED)
		vbg_err("%s: Error host is too old\n", __func__);

	*root = parms.root.u.value32;
	वापस err;
पूर्ण

पूर्णांक vboxsf_unmap_folder(u32 root)
अणु
	काष्ठा shfl_unmap_folder parms;

	parms.root.type = VMMDEV_HGCM_PARM_TYPE_32BIT;
	parms.root.u.value32 = root;

	वापस vboxsf_call(SHFL_FN_UNMAP_FOLDER, &parms,
			   SHFL_CPARMS_UNMAP_FOLDER, शून्य);
पूर्ण

/**
 * vboxsf_create - Create a new file or folder
 * @root:         Root of the shared folder in which to create the file
 * @parsed_path:  The path of the file or folder relative to the shared folder
 * @param:        create_parms Parameters क्रम file/folder creation.
 *
 * Create a new file or folder or खोलो an existing one in a shared folder.
 * Note this function always वापसs 0 / success unless an exceptional condition
 * occurs - out of memory, invalid arguments, etc. If the file or folder could
 * not be खोलोed or created, create_parms->handle will be set to
 * SHFL_HANDLE_NIL on वापस.  In this हाल the value in create_parms->result
 * provides inक्रमmation as to why (e.g. SHFL_खाता_EXISTS), create_parms->result
 * is also set on success as additional inक्रमmation.
 *
 * Returns:
 * 0 or negative त्रुटि_सं value.
 */
पूर्णांक vboxsf_create(u32 root, काष्ठा shfl_string *parsed_path,
		  काष्ठा shfl_createparms *create_parms)
अणु
	काष्ठा shfl_create parms;

	parms.root.type = VMMDEV_HGCM_PARM_TYPE_32BIT;
	parms.root.u.value32 = root;

	parms.path.type = VMMDEV_HGCM_PARM_TYPE_LINADDR_KERNEL;
	parms.path.u.poपूर्णांकer.size = shfl_string_buf_size(parsed_path);
	parms.path.u.poपूर्णांकer.u.linear_addr = (uपूर्णांकptr_t)parsed_path;

	parms.parms.type = VMMDEV_HGCM_PARM_TYPE_LINADDR_KERNEL;
	parms.parms.u.poपूर्णांकer.size = माप(काष्ठा shfl_createparms);
	parms.parms.u.poपूर्णांकer.u.linear_addr = (uपूर्णांकptr_t)create_parms;

	वापस vboxsf_call(SHFL_FN_CREATE, &parms, SHFL_CPARMS_CREATE, शून्य);
पूर्ण

पूर्णांक vboxsf_बंद(u32 root, u64 handle)
अणु
	काष्ठा shfl_बंद parms;

	parms.root.type = VMMDEV_HGCM_PARM_TYPE_32BIT;
	parms.root.u.value32 = root;

	parms.handle.type = VMMDEV_HGCM_PARM_TYPE_64BIT;
	parms.handle.u.value64 = handle;

	वापस vboxsf_call(SHFL_FN_CLOSE, &parms, SHFL_CPARMS_CLOSE, शून्य);
पूर्ण

पूर्णांक vboxsf_हटाओ(u32 root, काष्ठा shfl_string *parsed_path, u32 flags)
अणु
	काष्ठा shfl_हटाओ parms;

	parms.root.type = VMMDEV_HGCM_PARM_TYPE_32BIT;
	parms.root.u.value32 = root;

	parms.path.type = VMMDEV_HGCM_PARM_TYPE_LINADDR_KERNEL_IN;
	parms.path.u.poपूर्णांकer.size = shfl_string_buf_size(parsed_path);
	parms.path.u.poपूर्णांकer.u.linear_addr = (uपूर्णांकptr_t)parsed_path;

	parms.flags.type = VMMDEV_HGCM_PARM_TYPE_32BIT;
	parms.flags.u.value32 = flags;

	वापस vboxsf_call(SHFL_FN_REMOVE, &parms, SHFL_CPARMS_REMOVE, शून्य);
पूर्ण

पूर्णांक vboxsf_नाम(u32 root, काष्ठा shfl_string *src_path,
		  काष्ठा shfl_string *dest_path, u32 flags)
अणु
	काष्ठा shfl_नाम parms;

	parms.root.type = VMMDEV_HGCM_PARM_TYPE_32BIT;
	parms.root.u.value32 = root;

	parms.src.type = VMMDEV_HGCM_PARM_TYPE_LINADDR_KERNEL_IN;
	parms.src.u.poपूर्णांकer.size = shfl_string_buf_size(src_path);
	parms.src.u.poपूर्णांकer.u.linear_addr = (uपूर्णांकptr_t)src_path;

	parms.dest.type = VMMDEV_HGCM_PARM_TYPE_LINADDR_KERNEL_IN;
	parms.dest.u.poपूर्णांकer.size = shfl_string_buf_size(dest_path);
	parms.dest.u.poपूर्णांकer.u.linear_addr = (uपूर्णांकptr_t)dest_path;

	parms.flags.type = VMMDEV_HGCM_PARM_TYPE_32BIT;
	parms.flags.u.value32 = flags;

	वापस vboxsf_call(SHFL_FN_RENAME, &parms, SHFL_CPARMS_RENAME, शून्य);
पूर्ण

पूर्णांक vboxsf_पढ़ो(u32 root, u64 handle, u64 offset, u32 *buf_len, u8 *buf)
अणु
	काष्ठा shfl_पढ़ो parms;
	पूर्णांक err;

	parms.root.type = VMMDEV_HGCM_PARM_TYPE_32BIT;
	parms.root.u.value32 = root;

	parms.handle.type = VMMDEV_HGCM_PARM_TYPE_64BIT;
	parms.handle.u.value64 = handle;
	parms.offset.type = VMMDEV_HGCM_PARM_TYPE_64BIT;
	parms.offset.u.value64 = offset;
	parms.cb.type = VMMDEV_HGCM_PARM_TYPE_32BIT;
	parms.cb.u.value32 = *buf_len;
	parms.buffer.type = VMMDEV_HGCM_PARM_TYPE_LINADDR_KERNEL_OUT;
	parms.buffer.u.poपूर्णांकer.size = *buf_len;
	parms.buffer.u.poपूर्णांकer.u.linear_addr = (uपूर्णांकptr_t)buf;

	err = vboxsf_call(SHFL_FN_READ, &parms, SHFL_CPARMS_READ, शून्य);

	*buf_len = parms.cb.u.value32;
	वापस err;
पूर्ण

पूर्णांक vboxsf_ग_लिखो(u32 root, u64 handle, u64 offset, u32 *buf_len, u8 *buf)
अणु
	काष्ठा shfl_ग_लिखो parms;
	पूर्णांक err;

	parms.root.type = VMMDEV_HGCM_PARM_TYPE_32BIT;
	parms.root.u.value32 = root;

	parms.handle.type = VMMDEV_HGCM_PARM_TYPE_64BIT;
	parms.handle.u.value64 = handle;
	parms.offset.type = VMMDEV_HGCM_PARM_TYPE_64BIT;
	parms.offset.u.value64 = offset;
	parms.cb.type = VMMDEV_HGCM_PARM_TYPE_32BIT;
	parms.cb.u.value32 = *buf_len;
	parms.buffer.type = VMMDEV_HGCM_PARM_TYPE_LINADDR_KERNEL_IN;
	parms.buffer.u.poपूर्णांकer.size = *buf_len;
	parms.buffer.u.poपूर्णांकer.u.linear_addr = (uपूर्णांकptr_t)buf;

	err = vboxsf_call(SHFL_FN_WRITE, &parms, SHFL_CPARMS_WRITE, शून्य);

	*buf_len = parms.cb.u.value32;
	वापस err;
पूर्ण

/* Returns 0 on success, 1 on end-of-dir, negative त्रुटि_सं otherwise */
पूर्णांक vboxsf_dirinfo(u32 root, u64 handle,
		   काष्ठा shfl_string *parsed_path, u32 flags, u32 index,
		   u32 *buf_len, काष्ठा shfl_dirinfo *buf, u32 *file_count)
अणु
	काष्ठा shfl_list parms;
	पूर्णांक err, status;

	parms.root.type = VMMDEV_HGCM_PARM_TYPE_32BIT;
	parms.root.u.value32 = root;

	parms.handle.type = VMMDEV_HGCM_PARM_TYPE_64BIT;
	parms.handle.u.value64 = handle;
	parms.flags.type = VMMDEV_HGCM_PARM_TYPE_32BIT;
	parms.flags.u.value32 = flags;
	parms.cb.type = VMMDEV_HGCM_PARM_TYPE_32BIT;
	parms.cb.u.value32 = *buf_len;
	अगर (parsed_path) अणु
		parms.path.type = VMMDEV_HGCM_PARM_TYPE_LINADDR_KERNEL_IN;
		parms.path.u.poपूर्णांकer.size = shfl_string_buf_size(parsed_path);
		parms.path.u.poपूर्णांकer.u.linear_addr = (uपूर्णांकptr_t)parsed_path;
	पूर्ण अन्यथा अणु
		parms.path.type = VMMDEV_HGCM_PARM_TYPE_LINADDR_IN;
		parms.path.u.poपूर्णांकer.size = 0;
		parms.path.u.poपूर्णांकer.u.linear_addr = 0;
	पूर्ण

	parms.buffer.type = VMMDEV_HGCM_PARM_TYPE_LINADDR_KERNEL_OUT;
	parms.buffer.u.poपूर्णांकer.size = *buf_len;
	parms.buffer.u.poपूर्णांकer.u.linear_addr = (uपूर्णांकptr_t)buf;

	parms.resume_poपूर्णांक.type = VMMDEV_HGCM_PARM_TYPE_32BIT;
	parms.resume_poपूर्णांक.u.value32 = index;
	parms.file_count.type = VMMDEV_HGCM_PARM_TYPE_32BIT;
	parms.file_count.u.value32 = 0;	/* out parameter only */

	err = vboxsf_call(SHFL_FN_LIST, &parms, SHFL_CPARMS_LIST, &status);
	अगर (err == -ENODATA && status == VERR_NO_MORE_खाताS)
		err = 1;

	*buf_len = parms.cb.u.value32;
	*file_count = parms.file_count.u.value32;
	वापस err;
पूर्ण

पूर्णांक vboxsf_fsinfo(u32 root, u64 handle, u32 flags,
		  u32 *buf_len, व्योम *buf)
अणु
	काष्ठा shfl_inक्रमmation parms;
	पूर्णांक err;

	parms.root.type = VMMDEV_HGCM_PARM_TYPE_32BIT;
	parms.root.u.value32 = root;

	parms.handle.type = VMMDEV_HGCM_PARM_TYPE_64BIT;
	parms.handle.u.value64 = handle;
	parms.flags.type = VMMDEV_HGCM_PARM_TYPE_32BIT;
	parms.flags.u.value32 = flags;
	parms.cb.type = VMMDEV_HGCM_PARM_TYPE_32BIT;
	parms.cb.u.value32 = *buf_len;
	parms.info.type = VMMDEV_HGCM_PARM_TYPE_LINADDR_KERNEL;
	parms.info.u.poपूर्णांकer.size = *buf_len;
	parms.info.u.poपूर्णांकer.u.linear_addr = (uपूर्णांकptr_t)buf;

	err = vboxsf_call(SHFL_FN_INFORMATION, &parms, SHFL_CPARMS_INFORMATION,
			  शून्य);

	*buf_len = parms.cb.u.value32;
	वापस err;
पूर्ण

पूर्णांक vboxsf_पढ़ोlink(u32 root, काष्ठा shfl_string *parsed_path,
		    u32 buf_len, u8 *buf)
अणु
	काष्ठा shfl_पढ़ोLink parms;

	parms.root.type = VMMDEV_HGCM_PARM_TYPE_32BIT;
	parms.root.u.value32 = root;

	parms.path.type = VMMDEV_HGCM_PARM_TYPE_LINADDR_KERNEL_IN;
	parms.path.u.poपूर्णांकer.size = shfl_string_buf_size(parsed_path);
	parms.path.u.poपूर्णांकer.u.linear_addr = (uपूर्णांकptr_t)parsed_path;

	parms.buffer.type = VMMDEV_HGCM_PARM_TYPE_LINADDR_KERNEL_OUT;
	parms.buffer.u.poपूर्णांकer.size = buf_len;
	parms.buffer.u.poपूर्णांकer.u.linear_addr = (uपूर्णांकptr_t)buf;

	वापस vboxsf_call(SHFL_FN_READLINK, &parms, SHFL_CPARMS_READLINK,
			   शून्य);
पूर्ण

पूर्णांक vboxsf_symlink(u32 root, काष्ठा shfl_string *new_path,
		   काष्ठा shfl_string *old_path, काष्ठा shfl_fsobjinfo *buf)
अणु
	काष्ठा shfl_symlink parms;

	parms.root.type = VMMDEV_HGCM_PARM_TYPE_32BIT;
	parms.root.u.value32 = root;

	parms.new_path.type = VMMDEV_HGCM_PARM_TYPE_LINADDR_KERNEL_IN;
	parms.new_path.u.poपूर्णांकer.size = shfl_string_buf_size(new_path);
	parms.new_path.u.poपूर्णांकer.u.linear_addr = (uपूर्णांकptr_t)new_path;

	parms.old_path.type = VMMDEV_HGCM_PARM_TYPE_LINADDR_KERNEL_IN;
	parms.old_path.u.poपूर्णांकer.size = shfl_string_buf_size(old_path);
	parms.old_path.u.poपूर्णांकer.u.linear_addr = (uपूर्णांकptr_t)old_path;

	parms.info.type = VMMDEV_HGCM_PARM_TYPE_LINADDR_KERNEL_OUT;
	parms.info.u.poपूर्णांकer.size = माप(काष्ठा shfl_fsobjinfo);
	parms.info.u.poपूर्णांकer.u.linear_addr = (uपूर्णांकptr_t)buf;

	वापस vboxsf_call(SHFL_FN_SYMLINK, &parms, SHFL_CPARMS_SYMLINK, शून्य);
पूर्ण

पूर्णांक vboxsf_set_utf8(व्योम)
अणु
	वापस vboxsf_call(SHFL_FN_SET_UTF8, शून्य, 0, शून्य);
पूर्ण

पूर्णांक vboxsf_set_symlinks(व्योम)
अणु
	वापस vboxsf_call(SHFL_FN_SET_SYMLINKS, शून्य, 0, शून्य);
पूर्ण
