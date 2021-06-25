<शैली गुरु>
/*
 * Ceph - scalable distributed file प्रणाली
 *
 * Copyright (C) 2004-2010 Sage Weil <sage@newdream.net>
 *
 * This is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU Lesser General Public
 * License version 2.1, as published by the Free Software
 * Foundation.  See file COPYING.
 *
 */

#अगर_अघोषित CEPH_RBD_TYPES_H
#घोषणा CEPH_RBD_TYPES_H

#समावेश <linux/types.h>

/* For क्रमmat version 2, rbd image 'foo' consists of objects
 *   rbd_id.foo		- id of image
 *   rbd_header.<id>	- image metadata
 *   rbd_object_map.<id> - optional image object map
 *   rbd_data.<id>.0000000000000000
 *   rbd_data.<id>.0000000000000001
 *   ...		- data
 * Clients करो not access header data directly in rbd क्रमmat 2.
 */

#घोषणा RBD_HEADER_PREFIX      "rbd_header."
#घोषणा RBD_OBJECT_MAP_PREFIX  "rbd_object_map."
#घोषणा RBD_ID_PREFIX          "rbd_id."
#घोषणा RBD_V2_DATA_FORMAT     "%s.%016llx"

#घोषणा RBD_LOCK_NAME          "rbd_lock"
#घोषणा RBD_LOCK_TAG           "internal"
#घोषणा RBD_LOCK_COOKIE_PREFIX "auto"

क्रमागत rbd_notअगरy_op अणु
	RBD_NOTIFY_OP_ACQUIRED_LOCK      = 0,
	RBD_NOTIFY_OP_RELEASED_LOCK      = 1,
	RBD_NOTIFY_OP_REQUEST_LOCK       = 2,
	RBD_NOTIFY_OP_HEADER_UPDATE      = 3,
पूर्ण;

#घोषणा OBJECT_NONEXISTENT	0
#घोषणा OBJECT_EXISTS		1
#घोषणा OBJECT_PENDING		2
#घोषणा OBJECT_EXISTS_CLEAN	3

#घोषणा RBD_FLAG_OBJECT_MAP_INVALID	(1ULL << 0)
#घोषणा RBD_FLAG_FAST_DIFF_INVALID	(1ULL << 1)

/*
 * For क्रमmat version 1, rbd image 'foo' consists of objects
 *   foo.rbd		- image metadata
 *   rb.<idhi>.<idlo>.<extra>.000000000000
 *   rb.<idhi>.<idlo>.<extra>.000000000001
 *   ...		- data
 * There is no notion of a persistent image id in rbd क्रमmat 1.
 */

#घोषणा RBD_SUFFIX		".rbd"
#घोषणा RBD_V1_DATA_FORMAT	"%s.%012llx"

#घोषणा RBD_सूचीECTORY           "rbd_directory"
#घोषणा RBD_INFO                "rbd_info"

#घोषणा RBD_DEFAULT_OBJ_ORDER	22   /* 4MB */
#घोषणा RBD_MIN_OBJ_ORDER       16
#घोषणा RBD_MAX_OBJ_ORDER       30

#घोषणा RBD_HEADER_TEXT		"<<< Rados Block Device Image >>>\n"
#घोषणा RBD_HEADER_SIGNATURE	"RBD"
#घोषणा RBD_HEADER_VERSION	"001.005"

काष्ठा rbd_image_snap_ondisk अणु
	__le64 id;
	__le64 image_size;
पूर्ण __attribute__((packed));

काष्ठा rbd_image_header_ondisk अणु
	अक्षर text[40];
	अक्षर object_prefix[24];
	अक्षर signature[4];
	अक्षर version[8];
	काष्ठा अणु
		__u8 order;
		__u8 crypt_type;
		__u8 comp_type;
		__u8 unused;
	पूर्ण __attribute__((packed)) options;
	__le64 image_size;
	__le64 snap_seq;
	__le32 snap_count;
	__le32 reserved;
	__le64 snap_names_len;
	काष्ठा rbd_image_snap_ondisk snaps[];
पूर्ण __attribute__((packed));


#पूर्ण_अगर
