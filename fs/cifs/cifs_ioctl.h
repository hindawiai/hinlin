<शैली गुरु>
/*
 *   fs/cअगरs/cअगरs_ioctl.h
 *
 *   Structure definitions क्रम io control क्रम cअगरs/smb3
 *
 *   Copyright (c) 2015 Steve French <steve.french@primarydata.com>
 *
 *   This library is मुक्त software; you can redistribute it and/or modअगरy
 *   it under the terms of the GNU Lesser General Public License as published
 *   by the Free Software Foundation; either version 2.1 of the License, or
 *   (at your option) any later version.
 *
 *   This library is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
 *   the GNU Lesser General Public License क्रम more details.
 *
 */

काष्ठा smb_mnt_fs_info अणु
	__u32	version; /* 0001 */
	__u16	protocol_id;
	__u16	tcon_flags;
	__u32	vol_serial_number;
	__u32	vol_create_समय;
	__u32	share_caps;
	__u32	share_flags;
	__u32	sector_flags;
	__u32	optimal_sector_size;
	__u32	max_bytes_chunk;
	__u32	fs_attributes;
	__u32	max_path_component;
	__u32	device_type;
	__u32	device_अक्षरacteristics;
	__u32	maximal_access;
	__u64   cअगरs_posix_caps;
पूर्ण __packed;

काष्ठा smb_snapshot_array अणु
	__u32	number_of_snapshots;
	__u32	number_of_snapshots_वापसed;
	__u32	snapshot_array_size;
	/*	snapshots[]; */
पूर्ण __packed;

/* query_info flags */
#घोषणा PASSTHRU_QUERY_INFO	0x00000000
#घोषणा PASSTHRU_FSCTL		0x00000001
#घोषणा PASSTHRU_SET_INFO	0x00000002
काष्ठा smb_query_info अणु
	__u32   info_type;
	__u32   file_info_class;
	__u32   additional_inक्रमmation;
	__u32   flags;
	__u32	input_buffer_length;
	__u32	output_buffer_length;
	/* अक्षर buffer[]; */
पूर्ण __packed;

/*
 * Dumping the commonly used 16 byte (e.g. CCM and GCM128) keys still supported
 * क्रम backlevel compatibility, but is not sufficient क्रम dumping the less
 * frequently used GCM256 (32 byte) keys (see the newer "CIFS_DUMP_FULL_KEY"
 * ioctl क्रम dumping decryption info क्रम GCM256 mounts)
 */
काष्ठा smb3_key_debug_info अणु
	__u64	Suid;
	__u16	cipher_type;
	__u8	auth_key[16]; /* SMB2_NTLMV2_SESSKEY_SIZE */
	__u8	smb3encryptionkey[SMB3_SIGN_KEY_SIZE];
	__u8	smb3decryptionkey[SMB3_SIGN_KEY_SIZE];
पूर्ण __packed;

/*
 * Dump variable-sized keys
 */
काष्ठा smb3_full_key_debug_info अणु
	/* INPUT: size of userspace buffer */
	__u32   in_size;

	/*
	 * INPUT: 0 क्रम current user, otherwise session to dump
	 * OUTPUT: session id that was dumped
	 */
	__u64	session_id;
	__u16	cipher_type;
	__u8    session_key_length;
	__u8    server_in_key_length;
	__u8    server_out_key_length;
	__u8    data[];
	/*
	 * वापस this काष्ठा with the keys appended at the end:
	 * __u8 session_key[session_key_length];
	 * __u8 server_in_key[server_in_key_length];
	 * __u8 server_out_key[server_out_key_length];
	 */
पूर्ण __packed;

काष्ठा smb3_notअगरy अणु
	__u32	completion_filter;
	bool	watch_tree;
पूर्ण __packed;

#घोषणा CIFS_IOCTL_MAGIC	0xCF
#घोषणा CIFS_IOC_COPYCHUNK_खाता	_IOW(CIFS_IOCTL_MAGIC, 3, पूर्णांक)
#घोषणा CIFS_IOC_SET_INTEGRITY  _IO(CIFS_IOCTL_MAGIC, 4)
#घोषणा CIFS_IOC_GET_MNT_INFO _IOR(CIFS_IOCTL_MAGIC, 5, काष्ठा smb_mnt_fs_info)
#घोषणा CIFS_ENUMERATE_SNAPSHOTS _IOR(CIFS_IOCTL_MAGIC, 6, काष्ठा smb_snapshot_array)
#घोषणा CIFS_QUERY_INFO _IOWR(CIFS_IOCTL_MAGIC, 7, काष्ठा smb_query_info)
#घोषणा CIFS_DUMP_KEY _IOWR(CIFS_IOCTL_MAGIC, 8, काष्ठा smb3_key_debug_info)
#घोषणा CIFS_IOC_NOTIFY _IOW(CIFS_IOCTL_MAGIC, 9, काष्ठा smb3_notअगरy)
#घोषणा CIFS_DUMP_FULL_KEY _IOWR(CIFS_IOCTL_MAGIC, 10, काष्ठा smb3_full_key_debug_info)
#घोषणा CIFS_IOC_SHUTDOWN _IOR ('X', 125, __u32)

/*
 * Flags क्रम going करोwn operation
 */
#घोषणा CIFS_GOING_FLAGS_DEFAULT                0x0     /* going करोwn */
#घोषणा CIFS_GOING_FLAGS_LOGFLUSH               0x1     /* flush log but not data */
#घोषणा CIFS_GOING_FLAGS_NOLOGFLUSH             0x2     /* करोn't flush log nor data */

अटल अंतरभूत bool cअगरs_क्रमced_shutकरोwn(काष्ठा cअगरs_sb_info *sbi)
अणु
	अगर (CIFS_MOUNT_SHUTDOWN & sbi->mnt_cअगरs_flags)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण
