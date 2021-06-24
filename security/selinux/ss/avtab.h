<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * An access vector table (avtab) is a hash table
 * of access vectors and transition types indexed
 * by a type pair and a class.  An access vector
 * table is used to represent the type enक्रमcement
 * tables.
 *
 *  Author : Stephen Smalley, <sds@tycho.nsa.gov>
 */

/* Updated: Frank Mayer <mayerf@tresys.com> and Karl MacMillan <kmacmillan@tresys.com>
 *
 * 	Added conditional policy language extensions
 *
 * Copyright (C) 2003 Tresys Technology, LLC
 *
 * Updated: Yuichi Nakamura <ynakam@hitachisoft.jp>
 * 	Tuned number of hash slots क्रम avtab to reduce memory usage
 */
#अगर_अघोषित _SS_AVTAB_H_
#घोषणा _SS_AVTAB_H_

#समावेश "security.h"

काष्ठा avtab_key अणु
	u16 source_type;	/* source type */
	u16 target_type;	/* target type */
	u16 target_class;	/* target object class */
#घोषणा AVTAB_ALLOWED		0x0001
#घोषणा AVTAB_AUDITALLOW	0x0002
#घोषणा AVTAB_AUDITDENY		0x0004
#घोषणा AVTAB_AV		(AVTAB_ALLOWED | AVTAB_AUDITALLOW | AVTAB_AUDITDENY)
#घोषणा AVTAB_TRANSITION	0x0010
#घोषणा AVTAB_MEMBER		0x0020
#घोषणा AVTAB_CHANGE		0x0040
#घोषणा AVTAB_TYPE		(AVTAB_TRANSITION | AVTAB_MEMBER | AVTAB_CHANGE)
/* extended permissions */
#घोषणा AVTAB_XPERMS_ALLOWED	0x0100
#घोषणा AVTAB_XPERMS_AUDITALLOW	0x0200
#घोषणा AVTAB_XPERMS_DONTAUDIT	0x0400
#घोषणा AVTAB_XPERMS		(AVTAB_XPERMS_ALLOWED | \
				AVTAB_XPERMS_AUDITALLOW | \
				AVTAB_XPERMS_DONTAUDIT)
#घोषणा AVTAB_ENABLED_OLD   0x80000000 /* reserved क्रम used in cond_avtab */
#घोषणा AVTAB_ENABLED		0x8000 /* reserved क्रम used in cond_avtab */
	u16 specअगरied;	/* what field is specअगरied */
पूर्ण;

/*
 * For operations that require more than the 32 permissions provided by the avc
 * extended permissions may be used to provide 256 bits of permissions.
 */
काष्ठा avtab_extended_perms अणु
/* These are not flags. All 256 values may be used */
#घोषणा AVTAB_XPERMS_IOCTLFUNCTION	0x01
#घोषणा AVTAB_XPERMS_IOCTLDRIVER	0x02
	/* extension of the avtab_key specअगरied */
	u8 specअगरied; /* ioctl, netfilter, ... */
	/*
	 * अगर 256 bits is not adequate as is often the हाल with ioctls, then
	 * multiple extended perms may be used and the driver field
	 * specअगरies which permissions are included.
	 */
	u8 driver;
	/* 256 bits of permissions */
	काष्ठा extended_perms_data perms;
पूर्ण;

काष्ठा avtab_datum अणु
	जोड़ अणु
		u32 data; /* access vector or type value */
		काष्ठा avtab_extended_perms *xperms;
	पूर्ण u;
पूर्ण;

काष्ठा avtab_node अणु
	काष्ठा avtab_key key;
	काष्ठा avtab_datum datum;
	काष्ठा avtab_node *next;
पूर्ण;

काष्ठा avtab अणु
	काष्ठा avtab_node **htable;
	u32 nel;	/* number of elements */
	u32 nslot;      /* number of hash slots */
	u32 mask;       /* mask to compute hash func */
पूर्ण;

व्योम avtab_init(काष्ठा avtab *h);
पूर्णांक avtab_alloc(काष्ठा avtab *, u32);
पूर्णांक avtab_alloc_dup(काष्ठा avtab *new, स्थिर काष्ठा avtab *orig);
काष्ठा avtab_datum *avtab_search(काष्ठा avtab *h, काष्ठा avtab_key *k);
व्योम avtab_destroy(काष्ठा avtab *h);
व्योम avtab_hash_eval(काष्ठा avtab *h, अक्षर *tag);

काष्ठा policydb;
पूर्णांक avtab_पढ़ो_item(काष्ठा avtab *a, व्योम *fp, काष्ठा policydb *pol,
		    पूर्णांक (*insert)(काष्ठा avtab *a, काष्ठा avtab_key *k,
				  काष्ठा avtab_datum *d, व्योम *p),
		    व्योम *p);

पूर्णांक avtab_पढ़ो(काष्ठा avtab *a, व्योम *fp, काष्ठा policydb *pol);
पूर्णांक avtab_ग_लिखो_item(काष्ठा policydb *p, काष्ठा avtab_node *cur, व्योम *fp);
पूर्णांक avtab_ग_लिखो(काष्ठा policydb *p, काष्ठा avtab *a, व्योम *fp);

काष्ठा avtab_node *avtab_insert_nonunique(काष्ठा avtab *h, काष्ठा avtab_key *key,
					  काष्ठा avtab_datum *datum);

काष्ठा avtab_node *avtab_search_node(काष्ठा avtab *h, काष्ठा avtab_key *key);

काष्ठा avtab_node *avtab_search_node_next(काष्ठा avtab_node *node, पूर्णांक specअगरied);

#घोषणा MAX_AVTAB_HASH_BITS 16
#घोषणा MAX_AVTAB_HASH_BUCKETS (1 << MAX_AVTAB_HASH_BITS)

#पूर्ण_अगर	/* _SS_AVTAB_H_ */

