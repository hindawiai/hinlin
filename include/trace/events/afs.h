<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* AFS tracepoपूर्णांकs
 *
 * Copyright (C) 2016 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM afs

#अगर !defined(_TRACE_AFS_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_AFS_H

#समावेश <linux/tracepoपूर्णांक.h>

/*
 * Define क्रमागतs क्रम tracing inक्रमmation.
 */
#अगर_अघोषित __AFS_DECLARE_TRACE_ENUMS_ONCE_ONLY
#घोषणा __AFS_DECLARE_TRACE_ENUMS_ONCE_ONLY

क्रमागत afs_call_trace अणु
	afs_call_trace_alloc,
	afs_call_trace_मुक्त,
	afs_call_trace_get,
	afs_call_trace_put,
	afs_call_trace_wake,
	afs_call_trace_work,
पूर्ण;

क्रमागत afs_server_trace अणु
	afs_server_trace_alloc,
	afs_server_trace_callback,
	afs_server_trace_destroy,
	afs_server_trace_मुक्त,
	afs_server_trace_gc,
	afs_server_trace_get_by_addr,
	afs_server_trace_get_by_uuid,
	afs_server_trace_get_caps,
	afs_server_trace_get_install,
	afs_server_trace_get_new_cbi,
	afs_server_trace_get_probe,
	afs_server_trace_give_up_cb,
	afs_server_trace_purging,
	afs_server_trace_put_call,
	afs_server_trace_put_cbi,
	afs_server_trace_put_find_rsq,
	afs_server_trace_put_probe,
	afs_server_trace_put_slist,
	afs_server_trace_put_slist_isort,
	afs_server_trace_put_uuid_rsq,
	afs_server_trace_update,
पूर्ण;


क्रमागत afs_volume_trace अणु
	afs_volume_trace_alloc,
	afs_volume_trace_मुक्त,
	afs_volume_trace_get_alloc_sbi,
	afs_volume_trace_get_cell_insert,
	afs_volume_trace_get_new_op,
	afs_volume_trace_get_query_alias,
	afs_volume_trace_put_cell_dup,
	afs_volume_trace_put_cell_root,
	afs_volume_trace_put_destroy_sbi,
	afs_volume_trace_put_मुक्त_fc,
	afs_volume_trace_put_put_op,
	afs_volume_trace_put_query_alias,
	afs_volume_trace_put_validate_fc,
	afs_volume_trace_हटाओ,
पूर्ण;

क्रमागत afs_cell_trace अणु
	afs_cell_trace_alloc,
	afs_cell_trace_मुक्त,
	afs_cell_trace_get_queue_dns,
	afs_cell_trace_get_queue_manage,
	afs_cell_trace_get_queue_new,
	afs_cell_trace_get_vol,
	afs_cell_trace_insert,
	afs_cell_trace_manage,
	afs_cell_trace_put_candidate,
	afs_cell_trace_put_destroy,
	afs_cell_trace_put_queue_fail,
	afs_cell_trace_put_queue_work,
	afs_cell_trace_put_vol,
	afs_cell_trace_see_source,
	afs_cell_trace_see_ws,
	afs_cell_trace_unuse_alias,
	afs_cell_trace_unuse_check_alias,
	afs_cell_trace_unuse_delete,
	afs_cell_trace_unuse_fc,
	afs_cell_trace_unuse_lookup,
	afs_cell_trace_unuse_mntpt,
	afs_cell_trace_unuse_no_pin,
	afs_cell_trace_unuse_parse,
	afs_cell_trace_unuse_pin,
	afs_cell_trace_unuse_probe,
	afs_cell_trace_unuse_sbi,
	afs_cell_trace_unuse_ws,
	afs_cell_trace_use_alias,
	afs_cell_trace_use_check_alias,
	afs_cell_trace_use_fc,
	afs_cell_trace_use_fc_alias,
	afs_cell_trace_use_lookup,
	afs_cell_trace_use_mntpt,
	afs_cell_trace_use_pin,
	afs_cell_trace_use_probe,
	afs_cell_trace_use_sbi,
	afs_cell_trace_रुको,
पूर्ण;

क्रमागत afs_fs_operation अणु
	afs_FS_FetchData		= 130,	/* AFS Fetch file data */
	afs_FS_FetchACL			= 131,	/* AFS Fetch file ACL */
	afs_FS_FetchStatus		= 132,	/* AFS Fetch file status */
	afs_FS_StoreData		= 133,	/* AFS Store file data */
	afs_FS_StoreACL			= 134,	/* AFS Store file ACL */
	afs_FS_StoreStatus		= 135,	/* AFS Store file status */
	afs_FS_RemoveFile		= 136,	/* AFS Remove a file */
	afs_FS_CreateFile		= 137,	/* AFS Create a file */
	afs_FS_Rename			= 138,	/* AFS Rename or move a file or directory */
	afs_FS_Symlink			= 139,	/* AFS Create a symbolic link */
	afs_FS_Link			= 140,	/* AFS Create a hard link */
	afs_FS_MakeDir			= 141,	/* AFS Create a directory */
	afs_FS_RemoveDir		= 142,	/* AFS Remove a directory */
	afs_FS_GetVolumeInfo		= 148,	/* AFS Get inक्रमmation about a volume */
	afs_FS_GetVolumeStatus		= 149,	/* AFS Get volume status inक्रमmation */
	afs_FS_GetRootVolume		= 151,	/* AFS Get root volume name */
	afs_FS_SetLock			= 156,	/* AFS Request a file lock */
	afs_FS_ExtendLock		= 157,	/* AFS Extend a file lock */
	afs_FS_ReleaseLock		= 158,	/* AFS Release a file lock */
	afs_FS_Lookup			= 161,	/* AFS lookup file in directory */
	afs_FS_InlineBulkStatus		= 65536, /* AFS Fetch multiple file statuses with errors */
	afs_FS_FetchData64		= 65537, /* AFS Fetch file data */
	afs_FS_StoreData64		= 65538, /* AFS Store file data */
	afs_FS_GiveUpAllCallBacks	= 65539, /* AFS Give up all our callbacks on a server */
	afs_FS_GetCapabilities		= 65540, /* AFS Get FS server capabilities */

	yfs_FS_FetchData		= 130,	 /* YFS Fetch file data */
	yfs_FS_FetchACL			= 64131, /* YFS Fetch file ACL */
	yfs_FS_FetchStatus		= 64132, /* YFS Fetch file status */
	yfs_FS_StoreACL			= 64134, /* YFS Store file ACL */
	yfs_FS_StoreStatus		= 64135, /* YFS Store file status */
	yfs_FS_RemoveFile		= 64136, /* YFS Remove a file */
	yfs_FS_CreateFile		= 64137, /* YFS Create a file */
	yfs_FS_Rename			= 64138, /* YFS Rename or move a file or directory */
	yfs_FS_Symlink			= 64139, /* YFS Create a symbolic link */
	yfs_FS_Link			= 64140, /* YFS Create a hard link */
	yfs_FS_MakeDir			= 64141, /* YFS Create a directory */
	yfs_FS_RemoveDir		= 64142, /* YFS Remove a directory */
	yfs_FS_GetVolumeStatus		= 64149, /* YFS Get volume status inक्रमmation */
	yfs_FS_SetVolumeStatus		= 64150, /* YFS Set volume status inक्रमmation */
	yfs_FS_SetLock			= 64156, /* YFS Request a file lock */
	yfs_FS_ExtendLock		= 64157, /* YFS Extend a file lock */
	yfs_FS_ReleaseLock		= 64158, /* YFS Release a file lock */
	yfs_FS_Lookup			= 64161, /* YFS lookup file in directory */
	yfs_FS_FlushCPS			= 64165,
	yfs_FS_FetchOpaqueACL		= 64168,
	yfs_FS_WhoAmI			= 64170,
	yfs_FS_RemoveACL		= 64171,
	yfs_FS_RemoveFile2		= 64173,
	yfs_FS_StoreOpaqueACL2		= 64174,
	yfs_FS_InlineBulkStatus		= 64536, /* YFS Fetch multiple file statuses with errors */
	yfs_FS_FetchData64		= 64537, /* YFS Fetch file data */
	yfs_FS_StoreData64		= 64538, /* YFS Store file data */
	yfs_FS_UpdateSymlink		= 64540,
पूर्ण;

क्रमागत afs_vl_operation अणु
	afs_VL_GetEntryByNameU	= 527,		/* AFS Get Vol Entry By Name operation ID */
	afs_VL_GetAddrsU	= 533,		/* AFS Get FS server addresses */
	afs_YFSVL_GetEndpoपूर्णांकs	= 64002,	/* YFS Get FS & Vol server addresses */
	afs_YFSVL_GetCellName	= 64014,	/* YFS Get actual cell name */
	afs_VL_GetCapabilities	= 65537,	/* AFS Get VL server capabilities */
पूर्ण;

क्रमागत afs_edit_dir_op अणु
	afs_edit_dir_create,
	afs_edit_dir_create_error,
	afs_edit_dir_create_inval,
	afs_edit_dir_create_nospc,
	afs_edit_dir_delete,
	afs_edit_dir_delete_error,
	afs_edit_dir_delete_inval,
	afs_edit_dir_delete_noent,
पूर्ण;

क्रमागत afs_edit_dir_reason अणु
	afs_edit_dir_क्रम_create,
	afs_edit_dir_क्रम_link,
	afs_edit_dir_क्रम_सूची_गढ़ो,
	afs_edit_dir_क्रम_नाम_0,
	afs_edit_dir_क्रम_नाम_1,
	afs_edit_dir_क्रम_नाम_2,
	afs_edit_dir_क्रम_सूची_हटाओ,
	afs_edit_dir_क्रम_silly_0,
	afs_edit_dir_क्रम_silly_1,
	afs_edit_dir_क्रम_symlink,
	afs_edit_dir_क्रम_unlink,
पूर्ण;

क्रमागत afs_eproto_cause अणु
	afs_eproto_bad_status,
	afs_eproto_cb_count,
	afs_eproto_cb_fid_count,
	afs_eproto_cellname_len,
	afs_eproto_file_type,
	afs_eproto_ibulkst_cb_count,
	afs_eproto_ibulkst_count,
	afs_eproto_motd_len,
	afs_eproto_offline_msg_len,
	afs_eproto_volname_len,
	afs_eproto_yvl_fsendpt4_len,
	afs_eproto_yvl_fsendpt6_len,
	afs_eproto_yvl_fsendpt_num,
	afs_eproto_yvl_fsendpt_type,
	afs_eproto_yvl_vlendpt4_len,
	afs_eproto_yvl_vlendpt6_len,
	afs_eproto_yvl_vlendpt_type,
पूर्ण;

क्रमागत afs_io_error अणु
	afs_io_error_cm_reply,
	afs_io_error_extract,
	afs_io_error_fs_probe_fail,
	afs_io_error_vl_lookup_fail,
	afs_io_error_vl_probe_fail,
पूर्ण;

क्रमागत afs_file_error अणु
	afs_file_error_dir_bad_magic,
	afs_file_error_dir_big,
	afs_file_error_dir_missing_page,
	afs_file_error_dir_name_too_दीर्घ,
	afs_file_error_dir_over_end,
	afs_file_error_dir_small,
	afs_file_error_dir_unmarked_ext,
	afs_file_error_mntpt,
	afs_file_error_ग_लिखोback_fail,
पूर्ण;

क्रमागत afs_flock_event अणु
	afs_flock_acquired,
	afs_flock_callback_अवरोध,
	afs_flock_defer_unlock,
	afs_flock_extend_fail,
	afs_flock_fail_other,
	afs_flock_fail_perm,
	afs_flock_no_lockers,
	afs_flock_release_fail,
	afs_flock_silly_delete,
	afs_flock_बारtamp,
	afs_flock_try_to_lock,
	afs_flock_vfs_lock,
	afs_flock_vfs_locking,
	afs_flock_रुकोed,
	afs_flock_रुकोing,
	afs_flock_work_extending,
	afs_flock_work_retry,
	afs_flock_work_unlocking,
	afs_flock_would_block,
पूर्ण;

क्रमागत afs_flock_operation अणु
	afs_flock_op_copy_lock,
	afs_flock_op_flock,
	afs_flock_op_grant,
	afs_flock_op_lock,
	afs_flock_op_release_lock,
	afs_flock_op_वापस_ok,
	afs_flock_op_वापस_eagain,
	afs_flock_op_वापस_edeadlk,
	afs_flock_op_वापस_error,
	afs_flock_op_set_lock,
	afs_flock_op_unlock,
	afs_flock_op_wake,
पूर्ण;

क्रमागत afs_cb_अवरोध_reason अणु
	afs_cb_अवरोध_no_अवरोध,
	afs_cb_अवरोध_क्रम_callback,
	afs_cb_अवरोध_क्रम_deleted,
	afs_cb_अवरोध_क्रम_lapsed,
	afs_cb_अवरोध_क्रम_unlink,
	afs_cb_अवरोध_क्रम_vsअवरोध,
	afs_cb_अवरोध_क्रम_volume_callback,
	afs_cb_अवरोध_क्रम_zap,
पूर्ण;

#पूर्ण_अगर /* end __AFS_DECLARE_TRACE_ENUMS_ONCE_ONLY */

/*
 * Declare tracing inक्रमmation क्रमागतs and their string mappings क्रम display.
 */
#घोषणा afs_call_traces \
	EM(afs_call_trace_alloc,		"ALLOC") \
	EM(afs_call_trace_मुक्त,			"FREE ") \
	EM(afs_call_trace_get,			"GET  ") \
	EM(afs_call_trace_put,			"PUT  ") \
	EM(afs_call_trace_wake,			"WAKE ") \
	E_(afs_call_trace_work,			"QUEUE")

#घोषणा afs_server_traces \
	EM(afs_server_trace_alloc,		"ALLOC    ") \
	EM(afs_server_trace_callback,		"CALLBACK ") \
	EM(afs_server_trace_destroy,		"DESTROY  ") \
	EM(afs_server_trace_मुक्त,		"FREE     ") \
	EM(afs_server_trace_gc,			"GC       ") \
	EM(afs_server_trace_get_by_addr,	"GET addr ") \
	EM(afs_server_trace_get_by_uuid,	"GET uuid ") \
	EM(afs_server_trace_get_caps,		"GET caps ") \
	EM(afs_server_trace_get_install,	"GET inst ") \
	EM(afs_server_trace_get_new_cbi,	"GET cbi  ") \
	EM(afs_server_trace_get_probe,		"GET probe") \
	EM(afs_server_trace_give_up_cb,		"giveup-cb") \
	EM(afs_server_trace_purging,		"PURGE    ") \
	EM(afs_server_trace_put_call,		"PUT call ") \
	EM(afs_server_trace_put_cbi,		"PUT cbi  ") \
	EM(afs_server_trace_put_find_rsq,	"PUT f-rsq") \
	EM(afs_server_trace_put_probe,		"PUT probe") \
	EM(afs_server_trace_put_slist,		"PUT slist") \
	EM(afs_server_trace_put_slist_isort,	"PUT isort") \
	EM(afs_server_trace_put_uuid_rsq,	"PUT u-req") \
	E_(afs_server_trace_update,		"UPDATE")

#घोषणा afs_volume_traces \
	EM(afs_volume_trace_alloc,		"ALLOC         ") \
	EM(afs_volume_trace_मुक्त,		"FREE          ") \
	EM(afs_volume_trace_get_alloc_sbi,	"GET sbi-alloc ") \
	EM(afs_volume_trace_get_cell_insert,	"GET cell-insrt") \
	EM(afs_volume_trace_get_new_op,		"GET op-new    ") \
	EM(afs_volume_trace_get_query_alias,	"GET cell-alias") \
	EM(afs_volume_trace_put_cell_dup,	"PUT cell-dup  ") \
	EM(afs_volume_trace_put_cell_root,	"PUT cell-root ") \
	EM(afs_volume_trace_put_destroy_sbi,	"PUT sbi-destry") \
	EM(afs_volume_trace_put_मुक्त_fc,	"PUT fc-free   ") \
	EM(afs_volume_trace_put_put_op,		"PUT op-put    ") \
	EM(afs_volume_trace_put_query_alias,	"PUT cell-alias") \
	EM(afs_volume_trace_put_validate_fc,	"PUT fc-validat") \
	E_(afs_volume_trace_हटाओ,		"REMOVE        ")

#घोषणा afs_cell_traces \
	EM(afs_cell_trace_alloc,		"ALLOC     ") \
	EM(afs_cell_trace_मुक्त,			"FREE      ") \
	EM(afs_cell_trace_get_queue_dns,	"GET q-dns ") \
	EM(afs_cell_trace_get_queue_manage,	"GET q-mng ") \
	EM(afs_cell_trace_get_queue_new,	"GET q-new ") \
	EM(afs_cell_trace_get_vol,		"GET vol   ") \
	EM(afs_cell_trace_insert,		"INSERT    ") \
	EM(afs_cell_trace_manage,		"MANAGE    ") \
	EM(afs_cell_trace_put_candidate,	"PUT candid") \
	EM(afs_cell_trace_put_destroy,		"PUT destry") \
	EM(afs_cell_trace_put_queue_work,	"PUT q-work") \
	EM(afs_cell_trace_put_queue_fail,	"PUT q-fail") \
	EM(afs_cell_trace_put_vol,		"PUT vol   ") \
	EM(afs_cell_trace_see_source,		"SEE source") \
	EM(afs_cell_trace_see_ws,		"SEE ws    ") \
	EM(afs_cell_trace_unuse_alias,		"UNU alias ") \
	EM(afs_cell_trace_unuse_check_alias,	"UNU chk-al") \
	EM(afs_cell_trace_unuse_delete,		"UNU delete") \
	EM(afs_cell_trace_unuse_fc,		"UNU fc    ") \
	EM(afs_cell_trace_unuse_lookup,		"UNU lookup") \
	EM(afs_cell_trace_unuse_mntpt,		"UNU mntpt ") \
	EM(afs_cell_trace_unuse_parse,		"UNU parse ") \
	EM(afs_cell_trace_unuse_pin,		"UNU pin   ") \
	EM(afs_cell_trace_unuse_probe,		"UNU probe ") \
	EM(afs_cell_trace_unuse_sbi,		"UNU sbi   ") \
	EM(afs_cell_trace_unuse_ws,		"UNU ws    ") \
	EM(afs_cell_trace_use_alias,		"USE alias ") \
	EM(afs_cell_trace_use_check_alias,	"USE chk-al") \
	EM(afs_cell_trace_use_fc,		"USE fc    ") \
	EM(afs_cell_trace_use_fc_alias,		"USE fc-al ") \
	EM(afs_cell_trace_use_lookup,		"USE lookup") \
	EM(afs_cell_trace_use_mntpt,		"USE mntpt ") \
	EM(afs_cell_trace_use_pin,		"USE pin   ") \
	EM(afs_cell_trace_use_probe,		"USE probe ") \
	EM(afs_cell_trace_use_sbi,		"USE sbi   ") \
	E_(afs_cell_trace_रुको,			"WAIT      ")

#घोषणा afs_fs_operations \
	EM(afs_FS_FetchData,			"FS.FetchData") \
	EM(afs_FS_FetchStatus,			"FS.FetchStatus") \
	EM(afs_FS_StoreData,			"FS.StoreData") \
	EM(afs_FS_StoreStatus,			"FS.StoreStatus") \
	EM(afs_FS_RemoveFile,			"FS.RemoveFile") \
	EM(afs_FS_CreateFile,			"FS.CreateFile") \
	EM(afs_FS_Rename,			"FS.Rename") \
	EM(afs_FS_Symlink,			"FS.Symlink") \
	EM(afs_FS_Link,				"FS.Link") \
	EM(afs_FS_MakeDir,			"FS.MakeDir") \
	EM(afs_FS_RemoveDir,			"FS.RemoveDir") \
	EM(afs_FS_GetVolumeInfo,		"FS.GetVolumeInfo") \
	EM(afs_FS_GetVolumeStatus,		"FS.GetVolumeStatus") \
	EM(afs_FS_GetRootVolume,		"FS.GetRootVolume") \
	EM(afs_FS_SetLock,			"FS.SetLock") \
	EM(afs_FS_ExtendLock,			"FS.ExtendLock") \
	EM(afs_FS_ReleaseLock,			"FS.ReleaseLock") \
	EM(afs_FS_Lookup,			"FS.Lookup") \
	EM(afs_FS_InlineBulkStatus,		"FS.InlineBulkStatus") \
	EM(afs_FS_FetchData64,			"FS.FetchData64") \
	EM(afs_FS_StoreData64,			"FS.StoreData64") \
	EM(afs_FS_GiveUpAllCallBacks,		"FS.GiveUpAllCallBacks") \
	EM(afs_FS_GetCapabilities,		"FS.GetCapabilities") \
	EM(yfs_FS_FetchACL,			"YFS.FetchACL") \
	EM(yfs_FS_FetchStatus,			"YFS.FetchStatus") \
	EM(yfs_FS_StoreACL,			"YFS.StoreACL") \
	EM(yfs_FS_StoreStatus,			"YFS.StoreStatus") \
	EM(yfs_FS_RemoveFile,			"YFS.RemoveFile") \
	EM(yfs_FS_CreateFile,			"YFS.CreateFile") \
	EM(yfs_FS_Rename,			"YFS.Rename") \
	EM(yfs_FS_Symlink,			"YFS.Symlink") \
	EM(yfs_FS_Link,				"YFS.Link") \
	EM(yfs_FS_MakeDir,			"YFS.MakeDir") \
	EM(yfs_FS_RemoveDir,			"YFS.RemoveDir") \
	EM(yfs_FS_GetVolumeStatus,		"YFS.GetVolumeStatus") \
	EM(yfs_FS_SetVolumeStatus,		"YFS.SetVolumeStatus") \
	EM(yfs_FS_SetLock,			"YFS.SetLock") \
	EM(yfs_FS_ExtendLock,			"YFS.ExtendLock") \
	EM(yfs_FS_ReleaseLock,			"YFS.ReleaseLock") \
	EM(yfs_FS_Lookup,			"YFS.Lookup") \
	EM(yfs_FS_FlushCPS,			"YFS.FlushCPS") \
	EM(yfs_FS_FetchOpaqueACL,		"YFS.FetchOpaqueACL") \
	EM(yfs_FS_WhoAmI,			"YFS.WhoAmI") \
	EM(yfs_FS_RemoveACL,			"YFS.RemoveACL") \
	EM(yfs_FS_RemoveFile2,			"YFS.RemoveFile2") \
	EM(yfs_FS_StoreOpaqueACL2,		"YFS.StoreOpaqueACL2") \
	EM(yfs_FS_InlineBulkStatus,		"YFS.InlineBulkStatus") \
	EM(yfs_FS_FetchData64,			"YFS.FetchData64") \
	EM(yfs_FS_StoreData64,			"YFS.StoreData64") \
	E_(yfs_FS_UpdateSymlink,		"YFS.UpdateSymlink")

#घोषणा afs_vl_operations \
	EM(afs_VL_GetEntryByNameU,		"VL.GetEntryByNameU") \
	EM(afs_VL_GetAddrsU,			"VL.GetAddrsU") \
	EM(afs_YFSVL_GetEndpoपूर्णांकs,		"YFSVL.GetEndpoints") \
	EM(afs_YFSVL_GetCellName,		"YFSVL.GetCellName") \
	E_(afs_VL_GetCapabilities,		"VL.GetCapabilities")

#घोषणा afs_edit_dir_ops				  \
	EM(afs_edit_dir_create,			"create") \
	EM(afs_edit_dir_create_error,		"c_fail") \
	EM(afs_edit_dir_create_inval,		"c_invl") \
	EM(afs_edit_dir_create_nospc,		"c_nspc") \
	EM(afs_edit_dir_delete,			"delete") \
	EM(afs_edit_dir_delete_error,		"d_err ") \
	EM(afs_edit_dir_delete_inval,		"d_invl") \
	E_(afs_edit_dir_delete_noent,		"d_nent")

#घोषणा afs_edit_dir_reasons				  \
	EM(afs_edit_dir_क्रम_create,		"Create") \
	EM(afs_edit_dir_क्रम_link,		"Link  ") \
	EM(afs_edit_dir_क्रम_सूची_गढ़ो,		"MkDir ") \
	EM(afs_edit_dir_क्रम_नाम_0,		"Renam0") \
	EM(afs_edit_dir_क्रम_नाम_1,		"Renam1") \
	EM(afs_edit_dir_क्रम_नाम_2,		"Renam2") \
	EM(afs_edit_dir_क्रम_सूची_हटाओ,		"RmDir ") \
	EM(afs_edit_dir_क्रम_silly_0,		"S_Ren0") \
	EM(afs_edit_dir_क्रम_silly_1,		"S_Ren1") \
	EM(afs_edit_dir_क्रम_symlink,		"Symlnk") \
	E_(afs_edit_dir_क्रम_unlink,		"Unlink")

#घोषणा afs_eproto_causes			\
	EM(afs_eproto_bad_status,	"BadStatus") \
	EM(afs_eproto_cb_count,		"CbCount") \
	EM(afs_eproto_cb_fid_count,	"CbFidCount") \
	EM(afs_eproto_cellname_len,	"CellNameLen") \
	EM(afs_eproto_file_type,	"FileTYpe") \
	EM(afs_eproto_ibulkst_cb_count,	"IBS.CbCount") \
	EM(afs_eproto_ibulkst_count,	"IBS.FidCount") \
	EM(afs_eproto_motd_len,		"MotdLen") \
	EM(afs_eproto_offline_msg_len,	"OfflineMsgLen") \
	EM(afs_eproto_volname_len,	"VolNameLen") \
	EM(afs_eproto_yvl_fsendpt4_len,	"YVL.FsEnd4Len") \
	EM(afs_eproto_yvl_fsendpt6_len,	"YVL.FsEnd6Len") \
	EM(afs_eproto_yvl_fsendpt_num,	"YVL.FsEndCount") \
	EM(afs_eproto_yvl_fsendpt_type,	"YVL.FsEndType") \
	EM(afs_eproto_yvl_vlendpt4_len,	"YVL.VlEnd4Len") \
	EM(afs_eproto_yvl_vlendpt6_len,	"YVL.VlEnd6Len") \
	E_(afs_eproto_yvl_vlendpt_type,	"YVL.VlEndType")

#घोषणा afs_io_errors							\
	EM(afs_io_error_cm_reply,		"CM_REPLY")		\
	EM(afs_io_error_extract,		"EXTRACT")		\
	EM(afs_io_error_fs_probe_fail,		"FS_PROBE_FAIL")	\
	EM(afs_io_error_vl_lookup_fail,		"VL_LOOKUP_FAIL")	\
	E_(afs_io_error_vl_probe_fail,		"VL_PROBE_FAIL")

#घोषणा afs_file_errors							\
	EM(afs_file_error_dir_bad_magic,	"DIR_BAD_MAGIC")	\
	EM(afs_file_error_dir_big,		"DIR_BIG")		\
	EM(afs_file_error_dir_missing_page,	"DIR_MISSING_PAGE")	\
	EM(afs_file_error_dir_name_too_दीर्घ,	"DIR_NAME_TOO_LONG")	\
	EM(afs_file_error_dir_over_end,		"DIR_ENT_OVER_END")	\
	EM(afs_file_error_dir_small,		"DIR_SMALL")		\
	EM(afs_file_error_dir_unmarked_ext,	"DIR_UNMARKED_EXT")	\
	EM(afs_file_error_mntpt,		"MNTPT_READ_FAILED")	\
	E_(afs_file_error_ग_लिखोback_fail,	"WRITEBACK_FAILED")

#घोषणा afs_flock_types							\
	EM(F_RDLCK,				"RDLCK")		\
	EM(F_WRLCK,				"WRLCK")		\
	E_(F_UNLCK,				"UNLCK")

#घोषणा afs_flock_states						\
	EM(AFS_VNODE_LOCK_NONE,			"NONE")			\
	EM(AFS_VNODE_LOCK_WAITING_FOR_CB,	"WAIT_FOR_CB")		\
	EM(AFS_VNODE_LOCK_SETTING,		"SETTING")		\
	EM(AFS_VNODE_LOCK_GRANTED,		"GRANTED")		\
	EM(AFS_VNODE_LOCK_EXTENDING,		"EXTENDING")		\
	EM(AFS_VNODE_LOCK_NEED_UNLOCK,		"NEED_UNLOCK")		\
	EM(AFS_VNODE_LOCK_UNLOCKING,		"UNLOCKING")		\
	E_(AFS_VNODE_LOCK_DELETED,		"DELETED")

#घोषणा afs_flock_events						\
	EM(afs_flock_acquired,			"Acquired")		\
	EM(afs_flock_callback_अवरोध,		"Callback")		\
	EM(afs_flock_defer_unlock,		"D-Unlock")		\
	EM(afs_flock_extend_fail,		"Ext_Fail")		\
	EM(afs_flock_fail_other,		"ErrOther")		\
	EM(afs_flock_fail_perm,			"ErrPerm ")		\
	EM(afs_flock_no_lockers,		"NoLocker")		\
	EM(afs_flock_release_fail,		"Rel_Fail")		\
	EM(afs_flock_silly_delete,		"SillyDel")		\
	EM(afs_flock_बारtamp,			"Timestmp")		\
	EM(afs_flock_try_to_lock,		"TryToLck")		\
	EM(afs_flock_vfs_lock,			"VFSLock ")		\
	EM(afs_flock_vfs_locking,		"VFSLking")		\
	EM(afs_flock_रुकोed,			"Waited  ")		\
	EM(afs_flock_रुकोing,			"Waiting ")		\
	EM(afs_flock_work_extending,		"Extendng")		\
	EM(afs_flock_work_retry,		"Retry   ")		\
	EM(afs_flock_work_unlocking,		"Unlcking")		\
	E_(afs_flock_would_block,		"EWOULDBL")

#घोषणा afs_flock_operations						\
	EM(afs_flock_op_copy_lock,		"COPY    ")		\
	EM(afs_flock_op_flock,			"->flock ")		\
	EM(afs_flock_op_grant,			"GRANT   ")		\
	EM(afs_flock_op_lock,			"->lock  ")		\
	EM(afs_flock_op_release_lock,		"RELEASE ")		\
	EM(afs_flock_op_वापस_ok,		"<-OK    ")		\
	EM(afs_flock_op_वापस_edeadlk,		"<-EDEADL")		\
	EM(afs_flock_op_वापस_eagain,		"<-EAGAIN")		\
	EM(afs_flock_op_वापस_error,		"<-ERROR ")		\
	EM(afs_flock_op_set_lock,		"SET     ")		\
	EM(afs_flock_op_unlock,			"UNLOCK  ")		\
	E_(afs_flock_op_wake,			"WAKE    ")

#घोषणा afs_cb_अवरोध_reasons						\
	EM(afs_cb_अवरोध_no_अवरोध,		"no-break")		\
	EM(afs_cb_अवरोध_क्रम_callback,		"break-cb")		\
	EM(afs_cb_अवरोध_क्रम_deleted,		"break-del")		\
	EM(afs_cb_अवरोध_क्रम_lapsed,		"break-lapsed")		\
	EM(afs_cb_अवरोध_क्रम_unlink,		"break-unlink")		\
	EM(afs_cb_अवरोध_क्रम_vsअवरोध,		"break-vs")		\
	EM(afs_cb_अवरोध_क्रम_volume_callback,	"break-v-cb")		\
	E_(afs_cb_अवरोध_क्रम_zap,		"break-zap")

/*
 * Export क्रमागत symbols via userspace.
 */
#अघोषित EM
#अघोषित E_
#घोषणा EM(a, b) TRACE_DEFINE_ENUM(a);
#घोषणा E_(a, b) TRACE_DEFINE_ENUM(a);

afs_call_traces;
afs_server_traces;
afs_cell_traces;
afs_fs_operations;
afs_vl_operations;
afs_edit_dir_ops;
afs_edit_dir_reasons;
afs_eproto_causes;
afs_io_errors;
afs_file_errors;
afs_flock_types;
afs_flock_operations;
afs_cb_अवरोध_reasons;

/*
 * Now redefine the EM() and E_() macros to map the क्रमागतs to the strings that
 * will be prपूर्णांकed in the output.
 */
#अघोषित EM
#अघोषित E_
#घोषणा EM(a, b)	अणु a, b पूर्ण,
#घोषणा E_(a, b)	अणु a, b पूर्ण

TRACE_EVENT(afs_receive_data,
	    TP_PROTO(काष्ठा afs_call *call, काष्ठा iov_iter *iter,
		     bool want_more, पूर्णांक ret),

	    TP_ARGS(call, iter, want_more, ret),

	    TP_STRUCT__entry(
		    __field(loff_t,			reमुख्य		)
		    __field(अचिन्हित पूर्णांक,		call		)
		    __field(क्रमागत afs_call_state,	state		)
		    __field(अचिन्हित लघु,		unmarshall	)
		    __field(bool,			want_more	)
		    __field(पूर्णांक,			ret		)
			     ),

	    TP_fast_assign(
		    __entry->call	= call->debug_id;
		    __entry->state	= call->state;
		    __entry->unmarshall	= call->unmarshall;
		    __entry->reमुख्य	= iov_iter_count(iter);
		    __entry->want_more	= want_more;
		    __entry->ret	= ret;
			   ),

	    TP_prपूर्णांकk("c=%08x r=%llu u=%u w=%u s=%u ret=%d",
		      __entry->call,
		      __entry->reमुख्य,
		      __entry->unmarshall,
		      __entry->want_more,
		      __entry->state,
		      __entry->ret)
	    );

TRACE_EVENT(afs_notअगरy_call,
	    TP_PROTO(काष्ठा rxrpc_call *rxcall, काष्ठा afs_call *call),

	    TP_ARGS(rxcall, call),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,		call		)
		    __field(क्रमागत afs_call_state,	state		)
		    __field(अचिन्हित लघु,		unmarshall	)
			     ),

	    TP_fast_assign(
		    __entry->call	= call->debug_id;
		    __entry->state	= call->state;
		    __entry->unmarshall	= call->unmarshall;
			   ),

	    TP_prपूर्णांकk("c=%08x s=%u u=%u",
		      __entry->call,
		      __entry->state, __entry->unmarshall)
	    );

TRACE_EVENT(afs_cb_call,
	    TP_PROTO(काष्ठा afs_call *call),

	    TP_ARGS(call),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,		call		)
		    __field(स्थिर अक्षर *,		name		)
		    __field(u32,			op		)
			     ),

	    TP_fast_assign(
		    __entry->call	= call->debug_id;
		    __entry->name	= call->type->name;
		    __entry->op		= call->operation_ID;
			   ),

	    TP_prपूर्णांकk("c=%08x %s o=%u",
		      __entry->call,
		      __entry->name,
		      __entry->op)
	    );

TRACE_EVENT(afs_call,
	    TP_PROTO(काष्ठा afs_call *call, क्रमागत afs_call_trace op,
		     पूर्णांक usage, पूर्णांक outstanding, स्थिर व्योम *where),

	    TP_ARGS(call, op, usage, outstanding, where),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,		call		)
		    __field(पूर्णांक,			op		)
		    __field(पूर्णांक,			usage		)
		    __field(पूर्णांक,			outstanding	)
		    __field(स्थिर व्योम *,		where		)
			     ),

	    TP_fast_assign(
		    __entry->call = call->debug_id;
		    __entry->op = op;
		    __entry->usage = usage;
		    __entry->outstanding = outstanding;
		    __entry->where = where;
			   ),

	    TP_prपूर्णांकk("c=%08x %s u=%d o=%d sp=%pSR",
		      __entry->call,
		      __prपूर्णांक_symbolic(__entry->op, afs_call_traces),
		      __entry->usage,
		      __entry->outstanding,
		      __entry->where)
	    );

TRACE_EVENT(afs_make_fs_call,
	    TP_PROTO(काष्ठा afs_call *call, स्थिर काष्ठा afs_fid *fid),

	    TP_ARGS(call, fid),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,		call		)
		    __field(क्रमागत afs_fs_operation,	op		)
		    __field_काष्ठा(काष्ठा afs_fid,	fid		)
			     ),

	    TP_fast_assign(
		    __entry->call = call->debug_id;
		    __entry->op = call->operation_ID;
		    अगर (fid) अणु
			    __entry->fid = *fid;
		    पूर्ण अन्यथा अणु
			    __entry->fid.vid = 0;
			    __entry->fid.vnode = 0;
			    __entry->fid.unique = 0;
		    पूर्ण
			   ),

	    TP_prपूर्णांकk("c=%08x %06llx:%06llx:%06x %s",
		      __entry->call,
		      __entry->fid.vid,
		      __entry->fid.vnode,
		      __entry->fid.unique,
		      __prपूर्णांक_symbolic(__entry->op, afs_fs_operations))
	    );

TRACE_EVENT(afs_make_fs_calli,
	    TP_PROTO(काष्ठा afs_call *call, स्थिर काष्ठा afs_fid *fid,
		     अचिन्हित पूर्णांक i),

	    TP_ARGS(call, fid, i),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,		call		)
		    __field(अचिन्हित पूर्णांक,		i		)
		    __field(क्रमागत afs_fs_operation,	op		)
		    __field_काष्ठा(काष्ठा afs_fid,	fid		)
			     ),

	    TP_fast_assign(
		    __entry->call = call->debug_id;
		    __entry->i = i;
		    __entry->op = call->operation_ID;
		    अगर (fid) अणु
			    __entry->fid = *fid;
		    पूर्ण अन्यथा अणु
			    __entry->fid.vid = 0;
			    __entry->fid.vnode = 0;
			    __entry->fid.unique = 0;
		    पूर्ण
			   ),

	    TP_prपूर्णांकk("c=%08x %06llx:%06llx:%06x %s i=%u",
		      __entry->call,
		      __entry->fid.vid,
		      __entry->fid.vnode,
		      __entry->fid.unique,
		      __prपूर्णांक_symbolic(__entry->op, afs_fs_operations),
		      __entry->i)
	    );

TRACE_EVENT(afs_make_fs_call1,
	    TP_PROTO(काष्ठा afs_call *call, स्थिर काष्ठा afs_fid *fid,
		     स्थिर काष्ठा qstr *name),

	    TP_ARGS(call, fid, name),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,		call		)
		    __field(क्रमागत afs_fs_operation,	op		)
		    __field_काष्ठा(काष्ठा afs_fid,	fid		)
		    __array(अक्षर,			name, 24	)
			     ),

	    TP_fast_assign(
		    अचिन्हित पूर्णांक __len = min_t(अचिन्हित पूर्णांक, name->len, 23);
		    __entry->call = call->debug_id;
		    __entry->op = call->operation_ID;
		    अगर (fid) अणु
			    __entry->fid = *fid;
		    पूर्ण अन्यथा अणु
			    __entry->fid.vid = 0;
			    __entry->fid.vnode = 0;
			    __entry->fid.unique = 0;
		    पूर्ण
		    स_नकल(__entry->name, name->name, __len);
		    __entry->name[__len] = 0;
			   ),

	    TP_prपूर्णांकk("c=%08x %06llx:%06llx:%06x %s \"%s\"",
		      __entry->call,
		      __entry->fid.vid,
		      __entry->fid.vnode,
		      __entry->fid.unique,
		      __prपूर्णांक_symbolic(__entry->op, afs_fs_operations),
		      __entry->name)
	    );

TRACE_EVENT(afs_make_fs_call2,
	    TP_PROTO(काष्ठा afs_call *call, स्थिर काष्ठा afs_fid *fid,
		     स्थिर काष्ठा qstr *name, स्थिर काष्ठा qstr *name2),

	    TP_ARGS(call, fid, name, name2),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,		call		)
		    __field(क्रमागत afs_fs_operation,	op		)
		    __field_काष्ठा(काष्ठा afs_fid,	fid		)
		    __array(अक्षर,			name, 24	)
		    __array(अक्षर,			name2, 24	)
			     ),

	    TP_fast_assign(
		    अचिन्हित पूर्णांक __len = min_t(अचिन्हित पूर्णांक, name->len, 23);
		    अचिन्हित पूर्णांक __len2 = min_t(अचिन्हित पूर्णांक, name2->len, 23);
		    __entry->call = call->debug_id;
		    __entry->op = call->operation_ID;
		    अगर (fid) अणु
			    __entry->fid = *fid;
		    पूर्ण अन्यथा अणु
			    __entry->fid.vid = 0;
			    __entry->fid.vnode = 0;
			    __entry->fid.unique = 0;
		    पूर्ण
		    स_नकल(__entry->name, name->name, __len);
		    __entry->name[__len] = 0;
		    स_नकल(__entry->name2, name2->name, __len2);
		    __entry->name2[__len2] = 0;
			   ),

	    TP_prपूर्णांकk("c=%08x %06llx:%06llx:%06x %s \"%s\" \"%s\"",
		      __entry->call,
		      __entry->fid.vid,
		      __entry->fid.vnode,
		      __entry->fid.unique,
		      __prपूर्णांक_symbolic(__entry->op, afs_fs_operations),
		      __entry->name,
		      __entry->name2)
	    );

TRACE_EVENT(afs_make_vl_call,
	    TP_PROTO(काष्ठा afs_call *call),

	    TP_ARGS(call),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,		call		)
		    __field(क्रमागत afs_vl_operation,	op		)
			     ),

	    TP_fast_assign(
		    __entry->call = call->debug_id;
		    __entry->op = call->operation_ID;
			   ),

	    TP_prपूर्णांकk("c=%08x %s",
		      __entry->call,
		      __prपूर्णांक_symbolic(__entry->op, afs_vl_operations))
	    );

TRACE_EVENT(afs_call_करोne,
	    TP_PROTO(काष्ठा afs_call *call),

	    TP_ARGS(call),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,		call		)
		    __field(काष्ठा rxrpc_call *,	rx_call		)
		    __field(पूर्णांक,			ret		)
		    __field(u32,			पात_code	)
			     ),

	    TP_fast_assign(
		    __entry->call = call->debug_id;
		    __entry->rx_call = call->rxcall;
		    __entry->ret = call->error;
		    __entry->पात_code = call->पात_code;
			   ),

	    TP_prपूर्णांकk("   c=%08x ret=%d ab=%d [%p]",
		      __entry->call,
		      __entry->ret,
		      __entry->पात_code,
		      __entry->rx_call)
	    );

TRACE_EVENT(afs_send_data,
	    TP_PROTO(काष्ठा afs_call *call, काष्ठा msghdr *msg),

	    TP_ARGS(call, msg),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,		call		)
		    __field(अचिन्हित पूर्णांक,		flags		)
		    __field(loff_t,			offset		)
		    __field(loff_t,			count		)
			     ),

	    TP_fast_assign(
		    __entry->call = call->debug_id;
		    __entry->flags = msg->msg_flags;
		    __entry->offset = msg->msg_iter.xarray_start + msg->msg_iter.iov_offset;
		    __entry->count = iov_iter_count(&msg->msg_iter);
			   ),

	    TP_prपूर्णांकk(" c=%08x o=%llx n=%llx f=%x",
		      __entry->call, __entry->offset, __entry->count,
		      __entry->flags)
	    );

TRACE_EVENT(afs_sent_data,
	    TP_PROTO(काष्ठा afs_call *call, काष्ठा msghdr *msg, पूर्णांक ret),

	    TP_ARGS(call, msg, ret),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,		call		)
		    __field(पूर्णांक,			ret		)
		    __field(loff_t,			offset		)
		    __field(loff_t,			count		)
			     ),

	    TP_fast_assign(
		    __entry->call = call->debug_id;
		    __entry->ret = ret;
		    __entry->offset = msg->msg_iter.xarray_start + msg->msg_iter.iov_offset;
		    __entry->count = iov_iter_count(&msg->msg_iter);
			   ),

	    TP_prपूर्णांकk(" c=%08x o=%llx n=%llx r=%x",
		      __entry->call, __entry->offset, __entry->count,
		      __entry->ret)
	    );

TRACE_EVENT(afs_dir_check_failed,
	    TP_PROTO(काष्ठा afs_vnode *vnode, loff_t off, loff_t i_size),

	    TP_ARGS(vnode, off, i_size),

	    TP_STRUCT__entry(
		    __field(काष्ठा afs_vnode *,		vnode		)
		    __field(loff_t,			off		)
		    __field(loff_t,			i_size		)
			     ),

	    TP_fast_assign(
		    __entry->vnode = vnode;
		    __entry->off = off;
		    __entry->i_size = i_size;
			   ),

	    TP_prपूर्णांकk("vn=%p %llx/%llx",
		      __entry->vnode, __entry->off, __entry->i_size)
	    );

TRACE_EVENT(afs_page_dirty,
	    TP_PROTO(काष्ठा afs_vnode *vnode, स्थिर अक्षर *where, काष्ठा page *page),

	    TP_ARGS(vnode, where, page),

	    TP_STRUCT__entry(
		    __field(काष्ठा afs_vnode *,		vnode		)
		    __field(स्थिर अक्षर *,		where		)
		    __field(pgoff_t,			page		)
		    __field(अचिन्हित दीर्घ,		from		)
		    __field(अचिन्हित दीर्घ,		to		)
			     ),

	    TP_fast_assign(
		    __entry->vnode = vnode;
		    __entry->where = where;
		    __entry->page = page->index;
		    __entry->from = afs_page_dirty_from(page, page->निजी);
		    __entry->to = afs_page_dirty_to(page, page->निजी);
		    __entry->to |= (afs_is_page_dirty_mmapped(page->निजी) ?
				    (1UL << (BITS_PER_LONG - 1)) : 0);
			   ),

	    TP_prपूर्णांकk("vn=%p %lx %s %lx-%lx%s",
		      __entry->vnode, __entry->page, __entry->where,
		      __entry->from,
		      __entry->to & ~(1UL << (BITS_PER_LONG - 1)),
		      __entry->to & (1UL << (BITS_PER_LONG - 1)) ? " M" : "")
	    );

TRACE_EVENT(afs_call_state,
	    TP_PROTO(काष्ठा afs_call *call,
		     क्रमागत afs_call_state from,
		     क्रमागत afs_call_state to,
		     पूर्णांक ret, u32 remote_पात),

	    TP_ARGS(call, from, to, ret, remote_पात),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,		call		)
		    __field(क्रमागत afs_call_state,	from		)
		    __field(क्रमागत afs_call_state,	to		)
		    __field(पूर्णांक,			ret		)
		    __field(u32,			पात		)
			     ),

	    TP_fast_assign(
		    __entry->call = call->debug_id;
		    __entry->from = from;
		    __entry->to = to;
		    __entry->ret = ret;
		    __entry->पात = remote_पात;
			   ),

	    TP_prपूर्णांकk("c=%08x %u->%u r=%d ab=%d",
		      __entry->call,
		      __entry->from, __entry->to,
		      __entry->ret, __entry->पात)
	    );

TRACE_EVENT(afs_lookup,
	    TP_PROTO(काष्ठा afs_vnode *dvnode, स्थिर काष्ठा qstr *name,
		     काष्ठा afs_fid *fid),

	    TP_ARGS(dvnode, name, fid),

	    TP_STRUCT__entry(
		    __field_काष्ठा(काष्ठा afs_fid,	dfid		)
		    __field_काष्ठा(काष्ठा afs_fid,	fid		)
		    __array(अक्षर,			name, 24	)
			     ),

	    TP_fast_assign(
		    पूर्णांक __len = min_t(पूर्णांक, name->len, 23);
		    __entry->dfid = dvnode->fid;
		    __entry->fid = *fid;
		    स_नकल(__entry->name, name->name, __len);
		    __entry->name[__len] = 0;
			   ),

	    TP_prपूर्णांकk("d=%llx:%llx:%x \"%s\" f=%llx:%x",
		      __entry->dfid.vid, __entry->dfid.vnode, __entry->dfid.unique,
		      __entry->name,
		      __entry->fid.vnode, __entry->fid.unique)
	    );

TRACE_EVENT(afs_edit_dir,
	    TP_PROTO(काष्ठा afs_vnode *dvnode,
		     क्रमागत afs_edit_dir_reason why,
		     क्रमागत afs_edit_dir_op op,
		     अचिन्हित पूर्णांक block,
		     अचिन्हित पूर्णांक slot,
		     अचिन्हित पूर्णांक f_vnode,
		     अचिन्हित पूर्णांक f_unique,
		     स्थिर अक्षर *name),

	    TP_ARGS(dvnode, why, op, block, slot, f_vnode, f_unique, name),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,		vnode		)
		    __field(अचिन्हित पूर्णांक,		unique		)
		    __field(क्रमागत afs_edit_dir_reason,	why		)
		    __field(क्रमागत afs_edit_dir_op,	op		)
		    __field(अचिन्हित पूर्णांक,		block		)
		    __field(अचिन्हित लघु,		slot		)
		    __field(अचिन्हित पूर्णांक,		f_vnode		)
		    __field(अचिन्हित पूर्णांक,		f_unique	)
		    __array(अक्षर,			name, 24	)
			     ),

	    TP_fast_assign(
		    पूर्णांक __len = म_माप(name);
		    __len = min(__len, 23);
		    __entry->vnode	= dvnode->fid.vnode;
		    __entry->unique	= dvnode->fid.unique;
		    __entry->why	= why;
		    __entry->op		= op;
		    __entry->block	= block;
		    __entry->slot	= slot;
		    __entry->f_vnode	= f_vnode;
		    __entry->f_unique	= f_unique;
		    स_नकल(__entry->name, name, __len);
		    __entry->name[__len] = 0;
			   ),

	    TP_prपूर्णांकk("d=%x:%x %s %s %u[%u] f=%x:%x \"%s\"",
		      __entry->vnode, __entry->unique,
		      __prपूर्णांक_symbolic(__entry->why, afs_edit_dir_reasons),
		      __prपूर्णांक_symbolic(__entry->op, afs_edit_dir_ops),
		      __entry->block, __entry->slot,
		      __entry->f_vnode, __entry->f_unique,
		      __entry->name)
	    );

TRACE_EVENT(afs_protocol_error,
	    TP_PROTO(काष्ठा afs_call *call, क्रमागत afs_eproto_cause cause),

	    TP_ARGS(call, cause),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,		call		)
		    __field(क्रमागत afs_eproto_cause,	cause		)
			     ),

	    TP_fast_assign(
		    __entry->call = call ? call->debug_id : 0;
		    __entry->cause = cause;
			   ),

	    TP_prपूर्णांकk("c=%08x %s",
		      __entry->call,
		      __prपूर्णांक_symbolic(__entry->cause, afs_eproto_causes))
	    );

TRACE_EVENT(afs_io_error,
	    TP_PROTO(अचिन्हित पूर्णांक call, पूर्णांक error, क्रमागत afs_io_error where),

	    TP_ARGS(call, error, where),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,	call		)
		    __field(पूर्णांक,		error		)
		    __field(क्रमागत afs_io_error,	where		)
			     ),

	    TP_fast_assign(
		    __entry->call = call;
		    __entry->error = error;
		    __entry->where = where;
			   ),

	    TP_prपूर्णांकk("c=%08x r=%d %s",
		      __entry->call, __entry->error,
		      __prपूर्णांक_symbolic(__entry->where, afs_io_errors))
	    );

TRACE_EVENT(afs_file_error,
	    TP_PROTO(काष्ठा afs_vnode *vnode, पूर्णांक error, क्रमागत afs_file_error where),

	    TP_ARGS(vnode, error, where),

	    TP_STRUCT__entry(
		    __field_काष्ठा(काष्ठा afs_fid,	fid		)
		    __field(पूर्णांक,			error		)
		    __field(क्रमागत afs_file_error,	where		)
			     ),

	    TP_fast_assign(
		    __entry->fid = vnode->fid;
		    __entry->error = error;
		    __entry->where = where;
			   ),

	    TP_prपूर्णांकk("%llx:%llx:%x r=%d %s",
		      __entry->fid.vid, __entry->fid.vnode, __entry->fid.unique,
		      __entry->error,
		      __prपूर्णांक_symbolic(__entry->where, afs_file_errors))
	    );

TRACE_EVENT(afs_cm_no_server,
	    TP_PROTO(काष्ठा afs_call *call, काष्ठा sockaddr_rxrpc *srx),

	    TP_ARGS(call, srx),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,			call	)
		    __field(अचिन्हित पूर्णांक,			op_id	)
		    __field_काष्ठा(काष्ठा sockaddr_rxrpc,	srx	)
			     ),

	    TP_fast_assign(
		    __entry->call = call->debug_id;
		    __entry->op_id = call->operation_ID;
		    स_नकल(&__entry->srx, srx, माप(__entry->srx));
			   ),

	    TP_prपूर्णांकk("c=%08x op=%u %pISpc",
		      __entry->call, __entry->op_id, &__entry->srx.transport)
	    );

TRACE_EVENT(afs_cm_no_server_u,
	    TP_PROTO(काष्ठा afs_call *call, स्थिर uuid_t *uuid),

	    TP_ARGS(call, uuid),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,			call	)
		    __field(अचिन्हित पूर्णांक,			op_id	)
		    __field_काष्ठा(uuid_t,			uuid	)
			     ),

	    TP_fast_assign(
		    __entry->call = call->debug_id;
		    __entry->op_id = call->operation_ID;
		    स_नकल(&__entry->uuid, uuid, माप(__entry->uuid));
			   ),

	    TP_prपूर्णांकk("c=%08x op=%u %pU",
		      __entry->call, __entry->op_id, &__entry->uuid)
	    );

TRACE_EVENT(afs_flock_ev,
	    TP_PROTO(काष्ठा afs_vnode *vnode, काष्ठा file_lock *fl,
		     क्रमागत afs_flock_event event, पूर्णांक error),

	    TP_ARGS(vnode, fl, event, error),

	    TP_STRUCT__entry(
		    __field_काष्ठा(काष्ठा afs_fid,	fid		)
		    __field(क्रमागत afs_flock_event,	event		)
		    __field(क्रमागत afs_lock_state,	state		)
		    __field(पूर्णांक,			error		)
		    __field(अचिन्हित पूर्णांक,		debug_id	)
			     ),

	    TP_fast_assign(
		    __entry->fid = vnode->fid;
		    __entry->event = event;
		    __entry->state = vnode->lock_state;
		    __entry->error = error;
		    __entry->debug_id = fl ? fl->fl_u.afs.debug_id : 0;
			   ),

	    TP_prपूर्णांकk("%llx:%llx:%x %04x %s s=%s e=%d",
		      __entry->fid.vid, __entry->fid.vnode, __entry->fid.unique,
		      __entry->debug_id,
		      __prपूर्णांक_symbolic(__entry->event, afs_flock_events),
		      __prपूर्णांक_symbolic(__entry->state, afs_flock_states),
		      __entry->error)
	    );

TRACE_EVENT(afs_flock_op,
	    TP_PROTO(काष्ठा afs_vnode *vnode, काष्ठा file_lock *fl,
		     क्रमागत afs_flock_operation op),

	    TP_ARGS(vnode, fl, op),

	    TP_STRUCT__entry(
		    __field_काष्ठा(काष्ठा afs_fid,	fid		)
		    __field(loff_t,			from		)
		    __field(loff_t,			len		)
		    __field(क्रमागत afs_flock_operation,	op		)
		    __field(अचिन्हित अक्षर,		type		)
		    __field(अचिन्हित पूर्णांक,		flags		)
		    __field(अचिन्हित पूर्णांक,		debug_id	)
			     ),

	    TP_fast_assign(
		    __entry->fid = vnode->fid;
		    __entry->from = fl->fl_start;
		    __entry->len = fl->fl_end - fl->fl_start + 1;
		    __entry->op = op;
		    __entry->type = fl->fl_type;
		    __entry->flags = fl->fl_flags;
		    __entry->debug_id = fl->fl_u.afs.debug_id;
			   ),

	    TP_prपूर्णांकk("%llx:%llx:%x %04x %s t=%s R=%llx/%llx f=%x",
		      __entry->fid.vid, __entry->fid.vnode, __entry->fid.unique,
		      __entry->debug_id,
		      __prपूर्णांक_symbolic(__entry->op, afs_flock_operations),
		      __prपूर्णांक_symbolic(__entry->type, afs_flock_types),
		      __entry->from, __entry->len, __entry->flags)
	    );

TRACE_EVENT(afs_reload_dir,
	    TP_PROTO(काष्ठा afs_vnode *vnode),

	    TP_ARGS(vnode),

	    TP_STRUCT__entry(
		    __field_काष्ठा(काष्ठा afs_fid,	fid		)
			     ),

	    TP_fast_assign(
		    __entry->fid = vnode->fid;
			   ),

	    TP_prपूर्णांकk("%llx:%llx:%x",
		      __entry->fid.vid, __entry->fid.vnode, __entry->fid.unique)
	    );

TRACE_EVENT(afs_silly_नाम,
	    TP_PROTO(काष्ठा afs_vnode *vnode, bool करोne),

	    TP_ARGS(vnode, करोne),

	    TP_STRUCT__entry(
		    __field_काष्ठा(काष्ठा afs_fid,	fid		)
		    __field(bool,			करोne		)
			     ),

	    TP_fast_assign(
		    __entry->fid = vnode->fid;
		    __entry->करोne = करोne;
			   ),

	    TP_prपूर्णांकk("%llx:%llx:%x done=%u",
		      __entry->fid.vid, __entry->fid.vnode, __entry->fid.unique,
		      __entry->करोne)
	    );

TRACE_EVENT(afs_get_tree,
	    TP_PROTO(काष्ठा afs_cell *cell, काष्ठा afs_volume *volume),

	    TP_ARGS(cell, volume),

	    TP_STRUCT__entry(
		    __field(u64,			vid		)
		    __array(अक्षर,			cell, 24	)
		    __array(अक्षर,			volume, 24	)
			     ),

	    TP_fast_assign(
		    पूर्णांक __len;
		    __entry->vid = volume->vid;
		    __len = min_t(पूर्णांक, cell->name_len, 23);
		    स_नकल(__entry->cell, cell->name, __len);
		    __entry->cell[__len] = 0;
		    __len = min_t(पूर्णांक, volume->name_len, 23);
		    स_नकल(__entry->volume, volume->name, __len);
		    __entry->volume[__len] = 0;
			   ),

	    TP_prपूर्णांकk("--- MOUNT %s:%s %llx",
		      __entry->cell, __entry->volume, __entry->vid)
	    );

TRACE_EVENT(afs_cb_अवरोध,
	    TP_PROTO(काष्ठा afs_fid *fid, अचिन्हित पूर्णांक cb_अवरोध,
		     क्रमागत afs_cb_अवरोध_reason reason, bool skipped),

	    TP_ARGS(fid, cb_अवरोध, reason, skipped),

	    TP_STRUCT__entry(
		    __field_काष्ठा(काष्ठा afs_fid,	fid		)
		    __field(अचिन्हित पूर्णांक,		cb_अवरोध	)
		    __field(क्रमागत afs_cb_अवरोध_reason,	reason		)
		    __field(bool,			skipped		)
			     ),

	    TP_fast_assign(
		    __entry->fid	= *fid;
		    __entry->cb_अवरोध	= cb_अवरोध;
		    __entry->reason	= reason;
		    __entry->skipped	= skipped;
			   ),

	    TP_prपूर्णांकk("%llx:%llx:%x b=%x s=%u %s",
		      __entry->fid.vid, __entry->fid.vnode, __entry->fid.unique,
		      __entry->cb_अवरोध,
		      __entry->skipped,
		      __prपूर्णांक_symbolic(__entry->reason, afs_cb_अवरोध_reasons))
	    );

TRACE_EVENT(afs_cb_miss,
	    TP_PROTO(काष्ठा afs_fid *fid, क्रमागत afs_cb_अवरोध_reason reason),

	    TP_ARGS(fid, reason),

	    TP_STRUCT__entry(
		    __field_काष्ठा(काष्ठा afs_fid,	fid		)
		    __field(क्रमागत afs_cb_अवरोध_reason,	reason		)
			     ),

	    TP_fast_assign(
		    __entry->fid	= *fid;
		    __entry->reason	= reason;
			   ),

	    TP_prपूर्णांकk(" %llx:%llx:%x %s",
		      __entry->fid.vid, __entry->fid.vnode, __entry->fid.unique,
		      __prपूर्णांक_symbolic(__entry->reason, afs_cb_अवरोध_reasons))
	    );

TRACE_EVENT(afs_server,
	    TP_PROTO(काष्ठा afs_server *server, पूर्णांक ref, पूर्णांक active,
		     क्रमागत afs_server_trace reason),

	    TP_ARGS(server, ref, active, reason),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,		server		)
		    __field(पूर्णांक,			ref		)
		    __field(पूर्णांक,			active		)
		    __field(पूर्णांक,			reason		)
			     ),

	    TP_fast_assign(
		    __entry->server = server->debug_id;
		    __entry->ref = ref;
		    __entry->active = active;
		    __entry->reason = reason;
			   ),

	    TP_prपूर्णांकk("s=%08x %s u=%d a=%d",
		      __entry->server,
		      __prपूर्णांक_symbolic(__entry->reason, afs_server_traces),
		      __entry->ref,
		      __entry->active)
	    );

TRACE_EVENT(afs_volume,
	    TP_PROTO(afs_volid_t vid, पूर्णांक ref, क्रमागत afs_volume_trace reason),

	    TP_ARGS(vid, ref, reason),

	    TP_STRUCT__entry(
		    __field(afs_volid_t,		vid		)
		    __field(पूर्णांक,			ref		)
		    __field(क्रमागत afs_volume_trace,	reason		)
			     ),

	    TP_fast_assign(
		    __entry->vid = vid;
		    __entry->ref = ref;
		    __entry->reason = reason;
			   ),

	    TP_prपूर्णांकk("V=%llx %s u=%d",
		      __entry->vid,
		      __prपूर्णांक_symbolic(__entry->reason, afs_volume_traces),
		      __entry->ref)
	    );

TRACE_EVENT(afs_cell,
	    TP_PROTO(अचिन्हित पूर्णांक cell_debug_id, पूर्णांक usage, पूर्णांक active,
		     क्रमागत afs_cell_trace reason),

	    TP_ARGS(cell_debug_id, usage, active, reason),

	    TP_STRUCT__entry(
		    __field(अचिन्हित पूर्णांक,		cell		)
		    __field(पूर्णांक,			usage		)
		    __field(पूर्णांक,			active		)
		    __field(पूर्णांक,			reason		)
			     ),

	    TP_fast_assign(
		    __entry->cell = cell_debug_id;
		    __entry->usage = usage;
		    __entry->active = active;
		    __entry->reason = reason;
			   ),

	    TP_prपूर्णांकk("L=%08x %s u=%d a=%d",
		      __entry->cell,
		      __prपूर्णांक_symbolic(__entry->reason, afs_cell_traces),
		      __entry->usage,
		      __entry->active)
	    );

#पूर्ण_अगर /* _TRACE_AFS_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
