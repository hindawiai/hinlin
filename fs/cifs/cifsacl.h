<शैली गुरु>
/*
 *   fs/cअगरs/cअगरsacl.h
 *
 *   Copyright (c) International Business Machines  Corp., 2007
 *   Author(s): Steve French (sfrench@us.ibm.com)
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
 *   You should have received a copy of the GNU Lesser General Public License
 *   aदीर्घ with this library; अगर not, ग_लिखो to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#अगर_अघोषित _CIFSACL_H
#घोषणा _CIFSACL_H


#घोषणा NUM_AUTHS (6)	/* number of authority fields */
#घोषणा SID_MAX_SUB_AUTHORITIES (15) /* max number of sub authority fields */

#घोषणा READ_BIT        0x4
#घोषणा WRITE_BIT       0x2
#घोषणा EXEC_BIT        0x1

#घोषणा ACL_OWNER_MASK 0700
#घोषणा ACL_GROUP_MASK 0070
#घोषणा ACL_EVERYONE_MASK 0007

#घोषणा UBITSHIFT	6
#घोषणा GBITSHIFT	3

#घोषणा ACCESS_ALLOWED	0
#घोषणा ACCESS_DENIED	1

#घोषणा SIDOWNER 1
#घोषणा SIDGROUP 2

/*
 * Security Descriptor length containing DACL with 3 ACEs (one each क्रम
 * owner, group and world).
 */
#घोषणा DEFAULT_SEC_DESC_LEN (माप(काष्ठा cअगरs_ntsd) + \
			      माप(काष्ठा cअगरs_acl) + \
			      (माप(काष्ठा cअगरs_ace) * 4))

/*
 * Maximum size of a string representation of a SID:
 *
 * The fields are अचिन्हित values in decimal. So:
 *
 * u8:  max 3 bytes in decimal
 * u32: max 10 bytes in decimal
 *
 * "S-" + 3 bytes क्रम version field + 15 क्रम authority field + शून्य terminator
 *
 * For authority field, max is when all 6 values are non-zero and it must be
 * represented in hex. So "-0x" + 12 hex digits.
 *
 * Add 11 bytes क्रम each subauthority field (10 bytes each + 1 क्रम '-')
 */
#घोषणा SID_STRING_BASE_SIZE (2 + 3 + 15 + 1)
#घोषणा SID_STRING_SUBAUTH_SIZE (11) /* size of a single subauth string */

काष्ठा cअगरs_ntsd अणु
	__le16 revision; /* revision level */
	__le16 type;
	__le32 osiकरोffset;
	__le32 gsiकरोffset;
	__le32 sacloffset;
	__le32 dacloffset;
पूर्ण __attribute__((packed));

काष्ठा cअगरs_sid अणु
	__u8 revision; /* revision level */
	__u8 num_subauth;
	__u8 authority[NUM_AUTHS];
	__le32 sub_auth[SID_MAX_SUB_AUTHORITIES]; /* sub_auth[num_subauth] */
पूर्ण __attribute__((packed));

/* size of a काष्ठा cअगरs_sid, sans sub_auth array */
#घोषणा CIFS_SID_BASE_SIZE (1 + 1 + NUM_AUTHS)

काष्ठा cअगरs_acl अणु
	__le16 revision; /* revision level */
	__le16 size;
	__le32 num_aces;
पूर्ण __attribute__((packed));

/* ACE types - see MS-DTYP 2.4.4.1 */
#घोषणा ACCESS_ALLOWED_ACE_TYPE	0x00
#घोषणा ACCESS_DENIED_ACE_TYPE	0x01
#घोषणा SYSTEM_AUDIT_ACE_TYPE	0x02
#घोषणा SYSTEM_ALARM_ACE_TYPE	0x03
#घोषणा ACCESS_ALLOWED_COMPOUND_ACE_TYPE 0x04
#घोषणा ACCESS_ALLOWED_OBJECT_ACE_TYPE	0x05
#घोषणा ACCESS_DENIED_OBJECT_ACE_TYPE	0x06
#घोषणा SYSTEM_AUDIT_OBJECT_ACE_TYPE	0x07
#घोषणा SYSTEM_ALARM_OBJECT_ACE_TYPE	0x08
#घोषणा ACCESS_ALLOWED_CALLBACK_ACE_TYPE 0x09
#घोषणा ACCESS_DENIED_CALLBACK_ACE_TYPE	0x0A
#घोषणा ACCESS_ALLOWED_CALLBACK_OBJECT_ACE_TYPE 0x0B
#घोषणा ACCESS_DENIED_CALLBACK_OBJECT_ACE_TYPE  0x0C
#घोषणा SYSTEM_AUDIT_CALLBACK_ACE_TYPE	0x0D
#घोषणा SYSTEM_ALARM_CALLBACK_ACE_TYPE	0x0E /* Reserved */
#घोषणा SYSTEM_AUDIT_CALLBACK_OBJECT_ACE_TYPE 0x0F
#घोषणा SYSTEM_ALARM_CALLBACK_OBJECT_ACE_TYPE 0x10 /* reserved */
#घोषणा SYSTEM_MANDATORY_LABEL_ACE_TYPE	0x11
#घोषणा SYSTEM_RESOURCE_ATTRIBUTE_ACE_TYPE 0x12
#घोषणा SYSTEM_SCOPED_POLICY_ID_ACE_TYPE 0x13

/* ACE flags */
#घोषणा OBJECT_INHERIT_ACE	0x01
#घोषणा CONTAINER_INHERIT_ACE	0x02
#घोषणा NO_PROPAGATE_INHERIT_ACE 0x04
#घोषणा INHERIT_ONLY_ACE	0x08
#घोषणा INHERITED_ACE		0x10
#घोषणा SUCCESSFUL_ACCESS_ACE_FLAG 0x40
#घोषणा FAILED_ACCESS_ACE_FLAG	0x80

काष्ठा cअगरs_ace अणु
	__u8 type; /* see above and MS-DTYP 2.4.4.1 */
	__u8 flags;
	__le16 size;
	__le32 access_req;
	काष्ठा cअगरs_sid sid; /* ie UUID of user or group who माला_लो these perms */
पूर्ण __attribute__((packed));

/*
 * The current SMB3 क्रमm of security descriptor is similar to what was used क्रम
 * cअगरs (see above) but some fields are split, and fields in the काष्ठा below
 * matches names of fields to the spec, MS-DTYP (see sections 2.4.5 and
 * 2.4.6). Note that "CamelCase" fields are used in this काष्ठा in order to
 * match the MS-DTYP and MS-SMB2 specs which define the wire क्रमmat.
 */
काष्ठा smb3_sd अणु
	__u8 Revision; /* revision level, MUST be one */
	__u8 Sbz1; /* only meaningful अगर 'RM' flag set below */
	__le16 Control;
	__le32 OffsetOwner;
	__le32 OffsetGroup;
	__le32 OffsetSacl;
	__le32 OffsetDacl;
पूर्ण __packed;

/* Meaning of 'Control' field flags */
#घोषणा ACL_CONTROL_SR	0x8000	/* Self relative */
#घोषणा ACL_CONTROL_RM	0x4000	/* Resource manager control bits */
#घोषणा ACL_CONTROL_PS	0x2000	/* SACL रक्षित from inherits */
#घोषणा ACL_CONTROL_PD	0x1000	/* DACL रक्षित from inherits */
#घोषणा ACL_CONTROL_SI	0x0800	/* SACL Auto-Inherited */
#घोषणा ACL_CONTROL_DI	0x0400	/* DACL Auto-Inherited */
#घोषणा ACL_CONTROL_SC	0x0200	/* SACL computed through inheritance */
#घोषणा ACL_CONTROL_DC	0x0100	/* DACL computed through inheritence */
#घोषणा ACL_CONTROL_SS	0x0080	/* Create server ACL */
#घोषणा ACL_CONTROL_DT	0x0040	/* DACL provided by trusted source */
#घोषणा ACL_CONTROL_SD	0x0020	/* SACL शेषed */
#घोषणा ACL_CONTROL_SP	0x0010	/* SACL is present on object */
#घोषणा ACL_CONTROL_DD	0x0008	/* DACL शेषed */
#घोषणा ACL_CONTROL_DP	0x0004	/* DACL is present on object */
#घोषणा ACL_CONTROL_GD	0x0002	/* Group was शेषed */
#घोषणा ACL_CONTROL_OD	0x0001	/* User was शेषed */

/* Meaning of AclRevision flags */
#घोषणा ACL_REVISION	0x02 /* See section 2.4.4.1 of MS-DTYP */
#घोषणा ACL_REVISION_DS	0x04 /* Additional AceTypes allowed */

काष्ठा smb3_acl अणु
	u8 AclRevision; /* revision level */
	u8 Sbz1; /* MBZ */
	__le16 AclSize;
	__le16 AceCount;
	__le16 Sbz2; /* MBZ */
पूर्ण __packed;

/*
 * Used to store the special 'NFS SIDs' used to persist the POSIX uid and gid
 * See http://technet.microsoft.com/en-us/library/hh509017(v=ws.10).aspx
 */
काष्ठा owner_sid अणु
	u8 Revision;
	u8 NumAuth;
	u8 Authority[6];
	__le32 SubAuthorities[3];
पूर्ण __packed;

काष्ठा owner_group_sids अणु
	काष्ठा owner_sid owner;
	काष्ठा owner_sid group;
पूर्ण __packed;

/*
 * Minimum security identअगरier can be one क्रम प्रणाली defined Users
 * and Groups such as शून्य SID and World or Built-in accounts such
 * as Administrator and Guest and consists of
 * Revision + Num (Sub)Auths + Authority + Doमुख्य (one Subauthority)
 */
#घोषणा MIN_SID_LEN  (1 + 1 + 6 + 4) /* in bytes */

/*
 * Minimum security descriptor can be one without any SACL and DACL and can
 * consist of revision, type, and two sids of minimum size क्रम owner and group
 */
#घोषणा MIN_SEC_DESC_LEN  (माप(काष्ठा cअगरs_ntsd) + (2 * MIN_SID_LEN))

#पूर्ण_अगर /* _CIFSACL_H */
