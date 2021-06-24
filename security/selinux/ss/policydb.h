<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * A policy database (policydb) specअगरies the
 * configuration data क्रम the security policy.
 *
 * Author : Stephen Smalley, <sds@tycho.nsa.gov>
 */

/*
 * Updated: Trusted Computer Solutions, Inc. <dgoeddel@trustedcs.com>
 *
 *	Support क्रम enhanced MLS infraकाष्ठाure.
 *
 * Updated: Frank Mayer <mayerf@tresys.com> and Karl MacMillan <kmacmillan@tresys.com>
 *
 *	Added conditional policy language extensions
 *
 * Copyright (C) 2004-2005 Trusted Computer Solutions, Inc.
 * Copyright (C) 2003 - 2004 Tresys Technology, LLC
 */

#अगर_अघोषित _SS_POLICYDB_H_
#घोषणा _SS_POLICYDB_H_

#समावेश "symtab.h"
#समावेश "avtab.h"
#समावेश "sidtab.h"
#समावेश "ebitmap.h"
#समावेश "mls_types.h"
#समावेश "context.h"
#समावेश "constraint.h"

/*
 * A datum type is defined क्रम each kind of symbol
 * in the configuration data:  inभागidual permissions,
 * common prefixes क्रम access vectors, classes,
 * users, roles, types, sensitivities, categories, etc.
 */

/* Permission attributes */
काष्ठा perm_datum अणु
	u32 value;		/* permission bit + 1 */
पूर्ण;

/* Attributes of a common prefix क्रम access vectors */
काष्ठा common_datum अणु
	u32 value;			/* पूर्णांकernal common value */
	काष्ठा symtab permissions;	/* common permissions */
पूर्ण;

/* Class attributes */
काष्ठा class_datum अणु
	u32 value;			/* class value */
	अक्षर *comkey;			/* common name */
	काष्ठा common_datum *comdatum;	/* common datum */
	काष्ठा symtab permissions;	/* class-specअगरic permission symbol table */
	काष्ठा स्थिरraपूर्णांक_node *स्थिरraपूर्णांकs;	/* स्थिरraपूर्णांकs on class permissions */
	काष्ठा स्थिरraपूर्णांक_node *validatetrans;	/* special transition rules */
/* Options how a new object user, role, and type should be decided */
#घोषणा DEFAULT_SOURCE         1
#घोषणा DEFAULT_TARGET         2
	अक्षर शेष_user;
	अक्षर शेष_role;
	अक्षर शेष_type;
/* Options how a new object range should be decided */
#घोषणा DEFAULT_SOURCE_LOW     1
#घोषणा DEFAULT_SOURCE_HIGH    2
#घोषणा DEFAULT_SOURCE_LOW_HIGH        3
#घोषणा DEFAULT_TARGET_LOW     4
#घोषणा DEFAULT_TARGET_HIGH    5
#घोषणा DEFAULT_TARGET_LOW_HIGH        6
#घोषणा DEFAULT_GLBLUB		7
	अक्षर शेष_range;
पूर्ण;

/* Role attributes */
काष्ठा role_datum अणु
	u32 value;			/* पूर्णांकernal role value */
	u32 bounds;			/* boundary of role */
	काष्ठा ebiपंचांगap करोminates;	/* set of roles करोminated by this role */
	काष्ठा ebiपंचांगap types;		/* set of authorized types क्रम role */
पूर्ण;

काष्ठा role_trans_key अणु
	u32 role;		/* current role */
	u32 type;		/* program executable type, or new object type */
	u32 tclass;		/* process class, or new object class */
पूर्ण;

काष्ठा role_trans_datum अणु
	u32 new_role;		/* new role */
पूर्ण;

काष्ठा filename_trans_key अणु
	u32 ttype;		/* parent dir context */
	u16 tclass;		/* class of new object */
	स्थिर अक्षर *name;	/* last path component */
पूर्ण;

काष्ठा filename_trans_datum अणु
	काष्ठा ebiपंचांगap stypes;	/* biपंचांगap of source types क्रम this otype */
	u32 otype;		/* resulting type of new object */
	काष्ठा filename_trans_datum *next;	/* record क्रम next otype*/
पूर्ण;

काष्ठा role_allow अणु
	u32 role;		/* current role */
	u32 new_role;		/* new role */
	काष्ठा role_allow *next;
पूर्ण;

/* Type attributes */
काष्ठा type_datum अणु
	u32 value;		/* पूर्णांकernal type value */
	u32 bounds;		/* boundary of type */
	अचिन्हित अक्षर primary;	/* primary name? */
	अचिन्हित अक्षर attribute;/* attribute ?*/
पूर्ण;

/* User attributes */
काष्ठा user_datum अणु
	u32 value;			/* पूर्णांकernal user value */
	u32 bounds;			/* bounds of user */
	काष्ठा ebiपंचांगap roles;		/* set of authorized roles क्रम user */
	काष्ठा mls_range range;		/* MLS range (min - max) क्रम user */
	काष्ठा mls_level dfltlevel;	/* शेष login MLS level क्रम user */
पूर्ण;


/* Sensitivity attributes */
काष्ठा level_datum अणु
	काष्ठा mls_level *level;	/* sensitivity and associated categories */
	अचिन्हित अक्षर isalias;	/* is this sensitivity an alias क्रम another? */
पूर्ण;

/* Category attributes */
काष्ठा cat_datum अणु
	u32 value;		/* पूर्णांकernal category bit + 1 */
	अचिन्हित अक्षर isalias;  /* is this category an alias क्रम another? */
पूर्ण;

काष्ठा range_trans अणु
	u32 source_type;
	u32 target_type;
	u32 target_class;
पूर्ण;

/* Boolean data type */
काष्ठा cond_bool_datum अणु
	__u32 value;		/* पूर्णांकernal type value */
	पूर्णांक state;
पूर्ण;

काष्ठा cond_node;

/*
 * type set preserves data needed to determine स्थिरraपूर्णांक info from
 * policy source. This is not used by the kernel policy but allows
 * utilities such as audit2allow to determine स्थिरraपूर्णांक denials.
 */
काष्ठा type_set अणु
	काष्ठा ebiपंचांगap types;
	काष्ठा ebiपंचांगap negset;
	u32 flags;
पूर्ण;

/*
 * The configuration data includes security contexts क्रम
 * initial SIDs, unlabeled file प्रणालीs, TCP and UDP port numbers,
 * network पूर्णांकerfaces, and nodes.  This काष्ठाure stores the
 * relevant data क्रम one such entry.  Entries of the same kind
 * (e.g. all initial SIDs) are linked together पूर्णांकo a list.
 */
काष्ठा ocontext अणु
	जोड़ अणु
		अक्षर *name;	/* name of initial SID, fs, netअगर, fstype, path */
		काष्ठा अणु
			u8 protocol;
			u16 low_port;
			u16 high_port;
		पूर्ण port;		/* TCP or UDP port inक्रमmation */
		काष्ठा अणु
			u32 addr;
			u32 mask;
		पूर्ण node;		/* node inक्रमmation */
		काष्ठा अणु
			u32 addr[4];
			u32 mask[4];
		पूर्ण node6;        /* IPv6 node inक्रमmation */
		काष्ठा अणु
			u64 subnet_prefix;
			u16 low_pkey;
			u16 high_pkey;
		पूर्ण ibpkey;
		काष्ठा अणु
			अक्षर *dev_name;
			u8 port;
		पूर्ण ibendport;
	पूर्ण u;
	जोड़ अणु
		u32 sclass;  /* security class क्रम genfs */
		u32 behavior;  /* labeling behavior क्रम fs_use */
	पूर्ण v;
	काष्ठा context context[2];	/* security context(s) */
	u32 sid[2];	/* SID(s) */
	काष्ठा ocontext *next;
पूर्ण;

काष्ठा genfs अणु
	अक्षर *fstype;
	काष्ठा ocontext *head;
	काष्ठा genfs *next;
पूर्ण;

/* symbol table array indices */
#घोषणा SYM_COMMONS 0
#घोषणा SYM_CLASSES 1
#घोषणा SYM_ROLES   2
#घोषणा SYM_TYPES   3
#घोषणा SYM_USERS   4
#घोषणा SYM_BOOLS   5
#घोषणा SYM_LEVELS  6
#घोषणा SYM_CATS    7
#घोषणा SYM_NUM     8

/* object context array indices */
#घोषणा OCON_ISID	0 /* initial SIDs */
#घोषणा OCON_FS		1 /* unlabeled file प्रणालीs */
#घोषणा OCON_PORT	2 /* TCP and UDP port numbers */
#घोषणा OCON_NETIF	3 /* network पूर्णांकerfaces */
#घोषणा OCON_NODE	4 /* nodes */
#घोषणा OCON_FSUSE	5 /* fs_use */
#घोषणा OCON_NODE6	6 /* IPv6 nodes */
#घोषणा OCON_IBPKEY	7 /* Infiniband PKeys */
#घोषणा OCON_IBENDPORT	8 /* Infiniband end ports */
#घोषणा OCON_NUM	9

/* The policy database */
काष्ठा policydb अणु
	पूर्णांक mls_enabled;

	/* symbol tables */
	काष्ठा symtab symtab[SYM_NUM];
#घोषणा p_commons symtab[SYM_COMMONS]
#घोषणा p_classes symtab[SYM_CLASSES]
#घोषणा p_roles symtab[SYM_ROLES]
#घोषणा p_types symtab[SYM_TYPES]
#घोषणा p_users symtab[SYM_USERS]
#घोषणा p_bools symtab[SYM_BOOLS]
#घोषणा p_levels symtab[SYM_LEVELS]
#घोषणा p_cats symtab[SYM_CATS]

	/* symbol names indexed by (value - 1) */
	अक्षर		**sym_val_to_name[SYM_NUM];

	/* class, role, and user attributes indexed by (value - 1) */
	काष्ठा class_datum **class_val_to_काष्ठा;
	काष्ठा role_datum **role_val_to_काष्ठा;
	काष्ठा user_datum **user_val_to_काष्ठा;
	काष्ठा type_datum **type_val_to_काष्ठा;

	/* type enक्रमcement access vectors and transitions */
	काष्ठा avtab te_avtab;

	/* role transitions */
	काष्ठा hashtab role_tr;

	/* file transitions with the last path component */
	/* quickly exclude lookups when parent ttype has no rules */
	काष्ठा ebiपंचांगap filename_trans_ttypes;
	/* actual set of filename_trans rules */
	काष्ठा hashtab filename_trans;
	/* only used अगर policyvers < POLICYDB_VERSION_COMP_FTRANS */
	u32 compat_filename_trans_count;

	/* bools indexed by (value - 1) */
	काष्ठा cond_bool_datum **bool_val_to_काष्ठा;
	/* type enक्रमcement conditional access vectors and transitions */
	काष्ठा avtab te_cond_avtab;
	/* array indexing te_cond_avtab by conditional */
	काष्ठा cond_node *cond_list;
	u32 cond_list_len;

	/* role allows */
	काष्ठा role_allow *role_allow;

	/* security contexts of initial SIDs, unlabeled file प्रणालीs,
	   TCP or UDP port numbers, network पूर्णांकerfaces and nodes */
	काष्ठा ocontext *ocontexts[OCON_NUM];

	/* security contexts क्रम files in fileप्रणालीs that cannot support
	   a persistent label mapping or use another
	   fixed labeling behavior. */
	काष्ठा genfs *genfs;

	/* range transitions table (range_trans_key -> mls_range) */
	काष्ठा hashtab range_tr;

	/* type -> attribute reverse mapping */
	काष्ठा ebiपंचांगap *type_attr_map_array;

	काष्ठा ebiपंचांगap policycaps;

	काष्ठा ebiपंचांगap permissive_map;

	/* length of this policy when it was loaded */
	माप_प्रकार len;

	अचिन्हित पूर्णांक policyvers;

	अचिन्हित पूर्णांक reject_unknown : 1;
	अचिन्हित पूर्णांक allow_unknown : 1;

	u16 process_class;
	u32 process_trans_perms;
पूर्ण __अक्रमomize_layout;

बाह्य व्योम policydb_destroy(काष्ठा policydb *p);
बाह्य पूर्णांक policydb_load_isids(काष्ठा policydb *p, काष्ठा sidtab *s);
बाह्य पूर्णांक policydb_context_isvalid(काष्ठा policydb *p, काष्ठा context *c);
बाह्य पूर्णांक policydb_class_isvalid(काष्ठा policydb *p, अचिन्हित पूर्णांक class);
बाह्य पूर्णांक policydb_type_isvalid(काष्ठा policydb *p, अचिन्हित पूर्णांक type);
बाह्य पूर्णांक policydb_role_isvalid(काष्ठा policydb *p, अचिन्हित पूर्णांक role);
बाह्य पूर्णांक policydb_पढ़ो(काष्ठा policydb *p, व्योम *fp);
बाह्य पूर्णांक policydb_ग_लिखो(काष्ठा policydb *p, व्योम *fp);

बाह्य काष्ठा filename_trans_datum *policydb_filenametr_search(
	काष्ठा policydb *p, काष्ठा filename_trans_key *key);

बाह्य काष्ठा mls_range *policydb_rangetr_search(
	काष्ठा policydb *p, काष्ठा range_trans *key);

बाह्य काष्ठा role_trans_datum *policydb_roletr_search(
	काष्ठा policydb *p, काष्ठा role_trans_key *key);

#घोषणा POLICYDB_CONFIG_MLS    1

/* the config flags related to unknown classes/perms are bits 2 and 3 */
#घोषणा REJECT_UNKNOWN	0x00000002
#घोषणा ALLOW_UNKNOWN	0x00000004

#घोषणा OBJECT_R "object_r"
#घोषणा OBJECT_R_VAL 1

#घोषणा POLICYDB_MAGIC SELINUX_MAGIC
#घोषणा POLICYDB_STRING "SE Linux"

काष्ठा policy_file अणु
	अक्षर *data;
	माप_प्रकार len;
पूर्ण;

काष्ठा policy_data अणु
	काष्ठा policydb *p;
	व्योम *fp;
पूर्ण;

अटल अंतरभूत पूर्णांक next_entry(व्योम *buf, काष्ठा policy_file *fp, माप_प्रकार bytes)
अणु
	अगर (bytes > fp->len)
		वापस -EINVAL;

	स_नकल(buf, fp->data, bytes);
	fp->data += bytes;
	fp->len -= bytes;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक put_entry(स्थिर व्योम *buf, माप_प्रकार bytes, पूर्णांक num, काष्ठा policy_file *fp)
अणु
	माप_प्रकार len = bytes * num;

	स_नकल(fp->data, buf, len);
	fp->data += len;
	fp->len -= len;

	वापस 0;
पूर्ण

अटल अंतरभूत अक्षर *sym_name(काष्ठा policydb *p, अचिन्हित पूर्णांक sym_num, अचिन्हित पूर्णांक element_nr)
अणु
	वापस p->sym_val_to_name[sym_num][element_nr];
पूर्ण

बाह्य u16 string_to_security_class(काष्ठा policydb *p, स्थिर अक्षर *name);
बाह्य u32 string_to_av_perm(काष्ठा policydb *p, u16 tclass, स्थिर अक्षर *name);

#पूर्ण_अगर	/* _SS_POLICYDB_H_ */

