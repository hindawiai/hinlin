<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Implementation of the policy database.
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
 * Updated: Hewlett-Packard <paul@paul-moore.com>
 *
 *      Added support क्रम the policy capability biपंचांगap
 *
 * Update: Mellanox Techonologies
 *
 *	Added Infiniband support
 *
 * Copyright (C) 2016 Mellanox Techonologies
 * Copyright (C) 2007 Hewlett-Packard Development Company, L.P.
 * Copyright (C) 2004-2005 Trusted Computer Solutions, Inc.
 * Copyright (C) 2003 - 2004 Tresys Technology, LLC
 */

#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/audit.h>
#समावेश "security.h"

#समावेश "policydb.h"
#समावेश "conditional.h"
#समावेश "mls.h"
#समावेश "services.h"

#घोषणा _DEBUG_HASHES

#अगर_घोषित DEBUG_HASHES
अटल स्थिर अक्षर *symtab_name[SYM_NUM] = अणु
	"common prefixes",
	"classes",
	"roles",
	"types",
	"users",
	"bools",
	"levels",
	"categories",
पूर्ण;
#पूर्ण_अगर

काष्ठा policydb_compat_info अणु
	पूर्णांक version;
	पूर्णांक sym_num;
	पूर्णांक ocon_num;
पूर्ण;

/* These need to be updated अगर SYM_NUM or OCON_NUM changes */
अटल काष्ठा policydb_compat_info policydb_compat[] = अणु
	अणु
		.version	= POLICYDB_VERSION_BASE,
		.sym_num	= SYM_NUM - 3,
		.ocon_num	= OCON_NUM - 3,
	पूर्ण,
	अणु
		.version	= POLICYDB_VERSION_BOOL,
		.sym_num	= SYM_NUM - 2,
		.ocon_num	= OCON_NUM - 3,
	पूर्ण,
	अणु
		.version	= POLICYDB_VERSION_IPV6,
		.sym_num	= SYM_NUM - 2,
		.ocon_num	= OCON_NUM - 2,
	पूर्ण,
	अणु
		.version	= POLICYDB_VERSION_NLCLASS,
		.sym_num	= SYM_NUM - 2,
		.ocon_num	= OCON_NUM - 2,
	पूर्ण,
	अणु
		.version	= POLICYDB_VERSION_MLS,
		.sym_num	= SYM_NUM,
		.ocon_num	= OCON_NUM - 2,
	पूर्ण,
	अणु
		.version	= POLICYDB_VERSION_AVTAB,
		.sym_num	= SYM_NUM,
		.ocon_num	= OCON_NUM - 2,
	पूर्ण,
	अणु
		.version	= POLICYDB_VERSION_RANGETRANS,
		.sym_num	= SYM_NUM,
		.ocon_num	= OCON_NUM - 2,
	पूर्ण,
	अणु
		.version	= POLICYDB_VERSION_POLCAP,
		.sym_num	= SYM_NUM,
		.ocon_num	= OCON_NUM - 2,
	पूर्ण,
	अणु
		.version	= POLICYDB_VERSION_PERMISSIVE,
		.sym_num	= SYM_NUM,
		.ocon_num	= OCON_NUM - 2,
	पूर्ण,
	अणु
		.version	= POLICYDB_VERSION_BOUNDARY,
		.sym_num	= SYM_NUM,
		.ocon_num	= OCON_NUM - 2,
	पूर्ण,
	अणु
		.version	= POLICYDB_VERSION_खाताNAME_TRANS,
		.sym_num	= SYM_NUM,
		.ocon_num	= OCON_NUM - 2,
	पूर्ण,
	अणु
		.version	= POLICYDB_VERSION_ROLETRANS,
		.sym_num	= SYM_NUM,
		.ocon_num	= OCON_NUM - 2,
	पूर्ण,
	अणु
		.version	= POLICYDB_VERSION_NEW_OBJECT_DEFAULTS,
		.sym_num	= SYM_NUM,
		.ocon_num	= OCON_NUM - 2,
	पूर्ण,
	अणु
		.version	= POLICYDB_VERSION_DEFAULT_TYPE,
		.sym_num	= SYM_NUM,
		.ocon_num	= OCON_NUM - 2,
	पूर्ण,
	अणु
		.version	= POLICYDB_VERSION_CONSTRAINT_NAMES,
		.sym_num	= SYM_NUM,
		.ocon_num	= OCON_NUM - 2,
	पूर्ण,
	अणु
		.version	= POLICYDB_VERSION_XPERMS_IOCTL,
		.sym_num	= SYM_NUM,
		.ocon_num	= OCON_NUM - 2,
	पूर्ण,
	अणु
		.version	= POLICYDB_VERSION_INFINIBAND,
		.sym_num	= SYM_NUM,
		.ocon_num	= OCON_NUM,
	पूर्ण,
	अणु
		.version	= POLICYDB_VERSION_GLBLUB,
		.sym_num	= SYM_NUM,
		.ocon_num	= OCON_NUM,
	पूर्ण,
	अणु
		.version	= POLICYDB_VERSION_COMP_FTRANS,
		.sym_num	= SYM_NUM,
		.ocon_num	= OCON_NUM,
	पूर्ण,
पूर्ण;

अटल काष्ठा policydb_compat_info *policydb_lookup_compat(पूर्णांक version)
अणु
	पूर्णांक i;
	काष्ठा policydb_compat_info *info = शून्य;

	क्रम (i = 0; i < ARRAY_SIZE(policydb_compat); i++) अणु
		अगर (policydb_compat[i].version == version) अणु
			info = &policydb_compat[i];
			अवरोध;
		पूर्ण
	पूर्ण
	वापस info;
पूर्ण

/*
 * The following *_destroy functions are used to
 * मुक्त any memory allocated क्रम each kind of
 * symbol data in the policy database.
 */

अटल पूर्णांक perm_destroy(व्योम *key, व्योम *datum, व्योम *p)
अणु
	kमुक्त(key);
	kमुक्त(datum);
	वापस 0;
पूर्ण

अटल पूर्णांक common_destroy(व्योम *key, व्योम *datum, व्योम *p)
अणु
	काष्ठा common_datum *comdatum;

	kमुक्त(key);
	अगर (datum) अणु
		comdatum = datum;
		hashtab_map(&comdatum->permissions.table, perm_destroy, शून्य);
		hashtab_destroy(&comdatum->permissions.table);
	पूर्ण
	kमुक्त(datum);
	वापस 0;
पूर्ण

अटल व्योम स्थिरraपूर्णांक_expr_destroy(काष्ठा स्थिरraपूर्णांक_expr *expr)
अणु
	अगर (expr) अणु
		ebiपंचांगap_destroy(&expr->names);
		अगर (expr->type_names) अणु
			ebiपंचांगap_destroy(&expr->type_names->types);
			ebiपंचांगap_destroy(&expr->type_names->negset);
			kमुक्त(expr->type_names);
		पूर्ण
		kमुक्त(expr);
	पूर्ण
पूर्ण

अटल पूर्णांक cls_destroy(व्योम *key, व्योम *datum, व्योम *p)
अणु
	काष्ठा class_datum *cladatum;
	काष्ठा स्थिरraपूर्णांक_node *स्थिरraपूर्णांक, *ctemp;
	काष्ठा स्थिरraपूर्णांक_expr *e, *eपंचांगp;

	kमुक्त(key);
	अगर (datum) अणु
		cladatum = datum;
		hashtab_map(&cladatum->permissions.table, perm_destroy, शून्य);
		hashtab_destroy(&cladatum->permissions.table);
		स्थिरraपूर्णांक = cladatum->स्थिरraपूर्णांकs;
		जबतक (स्थिरraपूर्णांक) अणु
			e = स्थिरraपूर्णांक->expr;
			जबतक (e) अणु
				eपंचांगp = e;
				e = e->next;
				स्थिरraपूर्णांक_expr_destroy(eपंचांगp);
			पूर्ण
			ctemp = स्थिरraपूर्णांक;
			स्थिरraपूर्णांक = स्थिरraपूर्णांक->next;
			kमुक्त(ctemp);
		पूर्ण

		स्थिरraपूर्णांक = cladatum->validatetrans;
		जबतक (स्थिरraपूर्णांक) अणु
			e = स्थिरraपूर्णांक->expr;
			जबतक (e) अणु
				eपंचांगp = e;
				e = e->next;
				स्थिरraपूर्णांक_expr_destroy(eपंचांगp);
			पूर्ण
			ctemp = स्थिरraपूर्णांक;
			स्थिरraपूर्णांक = स्थिरraपूर्णांक->next;
			kमुक्त(ctemp);
		पूर्ण
		kमुक्त(cladatum->comkey);
	पूर्ण
	kमुक्त(datum);
	वापस 0;
पूर्ण

अटल पूर्णांक role_destroy(व्योम *key, व्योम *datum, व्योम *p)
अणु
	काष्ठा role_datum *role;

	kमुक्त(key);
	अगर (datum) अणु
		role = datum;
		ebiपंचांगap_destroy(&role->करोminates);
		ebiपंचांगap_destroy(&role->types);
	पूर्ण
	kमुक्त(datum);
	वापस 0;
पूर्ण

अटल पूर्णांक type_destroy(व्योम *key, व्योम *datum, व्योम *p)
अणु
	kमुक्त(key);
	kमुक्त(datum);
	वापस 0;
पूर्ण

अटल पूर्णांक user_destroy(व्योम *key, व्योम *datum, व्योम *p)
अणु
	काष्ठा user_datum *usrdatum;

	kमुक्त(key);
	अगर (datum) अणु
		usrdatum = datum;
		ebiपंचांगap_destroy(&usrdatum->roles);
		ebiपंचांगap_destroy(&usrdatum->range.level[0].cat);
		ebiपंचांगap_destroy(&usrdatum->range.level[1].cat);
		ebiपंचांगap_destroy(&usrdatum->dfltlevel.cat);
	पूर्ण
	kमुक्त(datum);
	वापस 0;
पूर्ण

अटल पूर्णांक sens_destroy(व्योम *key, व्योम *datum, व्योम *p)
अणु
	काष्ठा level_datum *levdatum;

	kमुक्त(key);
	अगर (datum) अणु
		levdatum = datum;
		अगर (levdatum->level)
			ebiपंचांगap_destroy(&levdatum->level->cat);
		kमुक्त(levdatum->level);
	पूर्ण
	kमुक्त(datum);
	वापस 0;
पूर्ण

अटल पूर्णांक cat_destroy(व्योम *key, व्योम *datum, व्योम *p)
अणु
	kमुक्त(key);
	kमुक्त(datum);
	वापस 0;
पूर्ण

अटल पूर्णांक (*destroy_f[SYM_NUM]) (व्योम *key, व्योम *datum, व्योम *datap) =
अणु
	common_destroy,
	cls_destroy,
	role_destroy,
	type_destroy,
	user_destroy,
	cond_destroy_bool,
	sens_destroy,
	cat_destroy,
पूर्ण;

अटल पूर्णांक filenametr_destroy(व्योम *key, व्योम *datum, व्योम *p)
अणु
	काष्ठा filename_trans_key *ft = key;
	काष्ठा filename_trans_datum *next, *d = datum;

	kमुक्त(ft->name);
	kमुक्त(key);
	करो अणु
		ebiपंचांगap_destroy(&d->stypes);
		next = d->next;
		kमुक्त(d);
		d = next;
	पूर्ण जबतक (unlikely(d));
	cond_resched();
	वापस 0;
पूर्ण

अटल पूर्णांक range_tr_destroy(व्योम *key, व्योम *datum, व्योम *p)
अणु
	काष्ठा mls_range *rt = datum;

	kमुक्त(key);
	ebiपंचांगap_destroy(&rt->level[0].cat);
	ebiपंचांगap_destroy(&rt->level[1].cat);
	kमुक्त(datum);
	cond_resched();
	वापस 0;
पूर्ण

अटल पूर्णांक role_tr_destroy(व्योम *key, व्योम *datum, व्योम *p)
अणु
	kमुक्त(key);
	kमुक्त(datum);
	वापस 0;
पूर्ण

अटल व्योम ocontext_destroy(काष्ठा ocontext *c, पूर्णांक i)
अणु
	अगर (!c)
		वापस;

	context_destroy(&c->context[0]);
	context_destroy(&c->context[1]);
	अगर (i == OCON_ISID || i == OCON_FS ||
	    i == OCON_NETIF || i == OCON_FSUSE)
		kमुक्त(c->u.name);
	kमुक्त(c);
पूर्ण

/*
 * Initialize the role table.
 */
अटल पूर्णांक roles_init(काष्ठा policydb *p)
अणु
	अक्षर *key = शून्य;
	पूर्णांक rc;
	काष्ठा role_datum *role;

	role = kzalloc(माप(*role), GFP_KERNEL);
	अगर (!role)
		वापस -ENOMEM;

	rc = -EINVAL;
	role->value = ++p->p_roles.nprim;
	अगर (role->value != OBJECT_R_VAL)
		जाओ out;

	rc = -ENOMEM;
	key = kstrdup(OBJECT_R, GFP_KERNEL);
	अगर (!key)
		जाओ out;

	rc = symtab_insert(&p->p_roles, key, role);
	अगर (rc)
		जाओ out;

	वापस 0;
out:
	kमुक्त(key);
	kमुक्त(role);
	वापस rc;
पूर्ण

अटल u32 filenametr_hash(स्थिर व्योम *k)
अणु
	स्थिर काष्ठा filename_trans_key *ft = k;
	अचिन्हित दीर्घ hash;
	अचिन्हित पूर्णांक byte_num;
	अचिन्हित अक्षर focus;

	hash = ft->ttype ^ ft->tclass;

	byte_num = 0;
	जबतक ((focus = ft->name[byte_num++]))
		hash = partial_name_hash(focus, hash);
	वापस hash;
पूर्ण

अटल पूर्णांक filenametr_cmp(स्थिर व्योम *k1, स्थिर व्योम *k2)
अणु
	स्थिर काष्ठा filename_trans_key *ft1 = k1;
	स्थिर काष्ठा filename_trans_key *ft2 = k2;
	पूर्णांक v;

	v = ft1->ttype - ft2->ttype;
	अगर (v)
		वापस v;

	v = ft1->tclass - ft2->tclass;
	अगर (v)
		वापस v;

	वापस म_भेद(ft1->name, ft2->name);

पूर्ण

अटल स्थिर काष्ठा hashtab_key_params filenametr_key_params = अणु
	.hash = filenametr_hash,
	.cmp = filenametr_cmp,
पूर्ण;

काष्ठा filename_trans_datum *policydb_filenametr_search(
	काष्ठा policydb *p, काष्ठा filename_trans_key *key)
अणु
	वापस hashtab_search(&p->filename_trans, key, filenametr_key_params);
पूर्ण

अटल u32 rangetr_hash(स्थिर व्योम *k)
अणु
	स्थिर काष्ठा range_trans *key = k;

	वापस key->source_type + (key->target_type << 3) +
		(key->target_class << 5);
पूर्ण

अटल पूर्णांक rangetr_cmp(स्थिर व्योम *k1, स्थिर व्योम *k2)
अणु
	स्थिर काष्ठा range_trans *key1 = k1, *key2 = k2;
	पूर्णांक v;

	v = key1->source_type - key2->source_type;
	अगर (v)
		वापस v;

	v = key1->target_type - key2->target_type;
	अगर (v)
		वापस v;

	v = key1->target_class - key2->target_class;

	वापस v;
पूर्ण

अटल स्थिर काष्ठा hashtab_key_params rangetr_key_params = अणु
	.hash = rangetr_hash,
	.cmp = rangetr_cmp,
पूर्ण;

काष्ठा mls_range *policydb_rangetr_search(काष्ठा policydb *p,
					  काष्ठा range_trans *key)
अणु
	वापस hashtab_search(&p->range_tr, key, rangetr_key_params);
पूर्ण

अटल u32 role_trans_hash(स्थिर व्योम *k)
अणु
	स्थिर काष्ठा role_trans_key *key = k;

	वापस key->role + (key->type << 3) + (key->tclass << 5);
पूर्ण

अटल पूर्णांक role_trans_cmp(स्थिर व्योम *k1, स्थिर व्योम *k2)
अणु
	स्थिर काष्ठा role_trans_key *key1 = k1, *key2 = k2;
	पूर्णांक v;

	v = key1->role - key2->role;
	अगर (v)
		वापस v;

	v = key1->type - key2->type;
	अगर (v)
		वापस v;

	वापस key1->tclass - key2->tclass;
पूर्ण

अटल स्थिर काष्ठा hashtab_key_params roletr_key_params = अणु
	.hash = role_trans_hash,
	.cmp = role_trans_cmp,
पूर्ण;

काष्ठा role_trans_datum *policydb_roletr_search(काष्ठा policydb *p,
						काष्ठा role_trans_key *key)
अणु
	वापस hashtab_search(&p->role_tr, key, roletr_key_params);
पूर्ण

/*
 * Initialize a policy database काष्ठाure.
 */
अटल व्योम policydb_init(काष्ठा policydb *p)
अणु
	स_रखो(p, 0, माप(*p));

	avtab_init(&p->te_avtab);
	cond_policydb_init(p);

	ebiपंचांगap_init(&p->filename_trans_ttypes);
	ebiपंचांगap_init(&p->policycaps);
	ebiपंचांगap_init(&p->permissive_map);
पूर्ण

/*
 * The following *_index functions are used to
 * define the val_to_name and val_to_काष्ठा arrays
 * in a policy database काष्ठाure.  The val_to_name
 * arrays are used when converting security context
 * काष्ठाures पूर्णांकo string representations.  The
 * val_to_काष्ठा arrays are used when the attributes
 * of a class, role, or user are needed.
 */

अटल पूर्णांक common_index(व्योम *key, व्योम *datum, व्योम *datap)
अणु
	काष्ठा policydb *p;
	काष्ठा common_datum *comdatum;

	comdatum = datum;
	p = datap;
	अगर (!comdatum->value || comdatum->value > p->p_commons.nprim)
		वापस -EINVAL;

	p->sym_val_to_name[SYM_COMMONS][comdatum->value - 1] = key;

	वापस 0;
पूर्ण

अटल पूर्णांक class_index(व्योम *key, व्योम *datum, व्योम *datap)
अणु
	काष्ठा policydb *p;
	काष्ठा class_datum *cladatum;

	cladatum = datum;
	p = datap;
	अगर (!cladatum->value || cladatum->value > p->p_classes.nprim)
		वापस -EINVAL;

	p->sym_val_to_name[SYM_CLASSES][cladatum->value - 1] = key;
	p->class_val_to_काष्ठा[cladatum->value - 1] = cladatum;
	वापस 0;
पूर्ण

अटल पूर्णांक role_index(व्योम *key, व्योम *datum, व्योम *datap)
अणु
	काष्ठा policydb *p;
	काष्ठा role_datum *role;

	role = datum;
	p = datap;
	अगर (!role->value
	    || role->value > p->p_roles.nprim
	    || role->bounds > p->p_roles.nprim)
		वापस -EINVAL;

	p->sym_val_to_name[SYM_ROLES][role->value - 1] = key;
	p->role_val_to_काष्ठा[role->value - 1] = role;
	वापस 0;
पूर्ण

अटल पूर्णांक type_index(व्योम *key, व्योम *datum, व्योम *datap)
अणु
	काष्ठा policydb *p;
	काष्ठा type_datum *typdatum;

	typdatum = datum;
	p = datap;

	अगर (typdatum->primary) अणु
		अगर (!typdatum->value
		    || typdatum->value > p->p_types.nprim
		    || typdatum->bounds > p->p_types.nprim)
			वापस -EINVAL;
		p->sym_val_to_name[SYM_TYPES][typdatum->value - 1] = key;
		p->type_val_to_काष्ठा[typdatum->value - 1] = typdatum;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक user_index(व्योम *key, व्योम *datum, व्योम *datap)
अणु
	काष्ठा policydb *p;
	काष्ठा user_datum *usrdatum;

	usrdatum = datum;
	p = datap;
	अगर (!usrdatum->value
	    || usrdatum->value > p->p_users.nprim
	    || usrdatum->bounds > p->p_users.nprim)
		वापस -EINVAL;

	p->sym_val_to_name[SYM_USERS][usrdatum->value - 1] = key;
	p->user_val_to_काष्ठा[usrdatum->value - 1] = usrdatum;
	वापस 0;
पूर्ण

अटल पूर्णांक sens_index(व्योम *key, व्योम *datum, व्योम *datap)
अणु
	काष्ठा policydb *p;
	काष्ठा level_datum *levdatum;

	levdatum = datum;
	p = datap;

	अगर (!levdatum->isalias) अणु
		अगर (!levdatum->level->sens ||
		    levdatum->level->sens > p->p_levels.nprim)
			वापस -EINVAL;

		p->sym_val_to_name[SYM_LEVELS][levdatum->level->sens - 1] = key;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cat_index(व्योम *key, व्योम *datum, व्योम *datap)
अणु
	काष्ठा policydb *p;
	काष्ठा cat_datum *catdatum;

	catdatum = datum;
	p = datap;

	अगर (!catdatum->isalias) अणु
		अगर (!catdatum->value || catdatum->value > p->p_cats.nprim)
			वापस -EINVAL;

		p->sym_val_to_name[SYM_CATS][catdatum->value - 1] = key;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक (*index_f[SYM_NUM]) (व्योम *key, व्योम *datum, व्योम *datap) =
अणु
	common_index,
	class_index,
	role_index,
	type_index,
	user_index,
	cond_index_bool,
	sens_index,
	cat_index,
पूर्ण;

#अगर_घोषित DEBUG_HASHES
अटल व्योम hash_eval(काष्ठा hashtab *h, स्थिर अक्षर *hash_name)
अणु
	काष्ठा hashtab_info info;

	hashtab_stat(h, &info);
	pr_debug("SELinux: %s:  %d entries and %d/%d buckets used, longest chain length %d\n",
		 hash_name, h->nel, info.slots_used, h->size,
		 info.max_chain_len);
पूर्ण

अटल व्योम symtab_hash_eval(काष्ठा symtab *s)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < SYM_NUM; i++)
		hash_eval(&s[i].table, symtab_name[i]);
पूर्ण

#अन्यथा
अटल अंतरभूत व्योम hash_eval(काष्ठा hashtab *h, अक्षर *hash_name)
अणु
पूर्ण
#पूर्ण_अगर

/*
 * Define the other val_to_name and val_to_काष्ठा arrays
 * in a policy database काष्ठाure.
 *
 * Caller must clean up on failure.
 */
अटल पूर्णांक policydb_index(काष्ठा policydb *p)
अणु
	पूर्णांक i, rc;

	अगर (p->mls_enabled)
		pr_debug("SELinux:  %d users, %d roles, %d types, %d bools, %d sens, %d cats\n",
			 p->p_users.nprim, p->p_roles.nprim, p->p_types.nprim,
			 p->p_bools.nprim, p->p_levels.nprim, p->p_cats.nprim);
	अन्यथा
		pr_debug("SELinux:  %d users, %d roles, %d types, %d bools\n",
			 p->p_users.nprim, p->p_roles.nprim, p->p_types.nprim,
			 p->p_bools.nprim);

	pr_debug("SELinux:  %d classes, %d rules\n",
		 p->p_classes.nprim, p->te_avtab.nel);

#अगर_घोषित DEBUG_HASHES
	avtab_hash_eval(&p->te_avtab, "rules");
	symtab_hash_eval(p->symtab);
#पूर्ण_अगर

	p->class_val_to_काष्ठा = kसुस्मृति(p->p_classes.nprim,
					 माप(*p->class_val_to_काष्ठा),
					 GFP_KERNEL);
	अगर (!p->class_val_to_काष्ठा)
		वापस -ENOMEM;

	p->role_val_to_काष्ठा = kसुस्मृति(p->p_roles.nprim,
					माप(*p->role_val_to_काष्ठा),
					GFP_KERNEL);
	अगर (!p->role_val_to_काष्ठा)
		वापस -ENOMEM;

	p->user_val_to_काष्ठा = kसुस्मृति(p->p_users.nprim,
					माप(*p->user_val_to_काष्ठा),
					GFP_KERNEL);
	अगर (!p->user_val_to_काष्ठा)
		वापस -ENOMEM;

	p->type_val_to_काष्ठा = kvसुस्मृति(p->p_types.nprim,
					 माप(*p->type_val_to_काष्ठा),
					 GFP_KERNEL);
	अगर (!p->type_val_to_काष्ठा)
		वापस -ENOMEM;

	rc = cond_init_bool_indexes(p);
	अगर (rc)
		जाओ out;

	क्रम (i = 0; i < SYM_NUM; i++) अणु
		p->sym_val_to_name[i] = kvसुस्मृति(p->symtab[i].nprim,
						 माप(अक्षर *),
						 GFP_KERNEL);
		अगर (!p->sym_val_to_name[i])
			वापस -ENOMEM;

		rc = hashtab_map(&p->symtab[i].table, index_f[i], p);
		अगर (rc)
			जाओ out;
	पूर्ण
	rc = 0;
out:
	वापस rc;
पूर्ण

/*
 * Free any memory allocated by a policy database काष्ठाure.
 */
व्योम policydb_destroy(काष्ठा policydb *p)
अणु
	काष्ठा ocontext *c, *cपंचांगp;
	काष्ठा genfs *g, *gपंचांगp;
	पूर्णांक i;
	काष्ठा role_allow *ra, *lra = शून्य;

	क्रम (i = 0; i < SYM_NUM; i++) अणु
		cond_resched();
		hashtab_map(&p->symtab[i].table, destroy_f[i], शून्य);
		hashtab_destroy(&p->symtab[i].table);
	पूर्ण

	क्रम (i = 0; i < SYM_NUM; i++)
		kvमुक्त(p->sym_val_to_name[i]);

	kमुक्त(p->class_val_to_काष्ठा);
	kमुक्त(p->role_val_to_काष्ठा);
	kमुक्त(p->user_val_to_काष्ठा);
	kvमुक्त(p->type_val_to_काष्ठा);

	avtab_destroy(&p->te_avtab);

	क्रम (i = 0; i < OCON_NUM; i++) अणु
		cond_resched();
		c = p->ocontexts[i];
		जबतक (c) अणु
			cपंचांगp = c;
			c = c->next;
			ocontext_destroy(cपंचांगp, i);
		पूर्ण
		p->ocontexts[i] = शून्य;
	पूर्ण

	g = p->genfs;
	जबतक (g) अणु
		cond_resched();
		kमुक्त(g->fstype);
		c = g->head;
		जबतक (c) अणु
			cपंचांगp = c;
			c = c->next;
			ocontext_destroy(cपंचांगp, OCON_FSUSE);
		पूर्ण
		gपंचांगp = g;
		g = g->next;
		kमुक्त(gपंचांगp);
	पूर्ण
	p->genfs = शून्य;

	cond_policydb_destroy(p);

	hashtab_map(&p->role_tr, role_tr_destroy, शून्य);
	hashtab_destroy(&p->role_tr);

	क्रम (ra = p->role_allow; ra; ra = ra->next) अणु
		cond_resched();
		kमुक्त(lra);
		lra = ra;
	पूर्ण
	kमुक्त(lra);

	hashtab_map(&p->filename_trans, filenametr_destroy, शून्य);
	hashtab_destroy(&p->filename_trans);

	hashtab_map(&p->range_tr, range_tr_destroy, शून्य);
	hashtab_destroy(&p->range_tr);

	अगर (p->type_attr_map_array) अणु
		क्रम (i = 0; i < p->p_types.nprim; i++)
			ebiपंचांगap_destroy(&p->type_attr_map_array[i]);
		kvमुक्त(p->type_attr_map_array);
	पूर्ण

	ebiपंचांगap_destroy(&p->filename_trans_ttypes);
	ebiपंचांगap_destroy(&p->policycaps);
	ebiपंचांगap_destroy(&p->permissive_map);
पूर्ण

/*
 * Load the initial SIDs specअगरied in a policy database
 * काष्ठाure पूर्णांकo a SID table.
 */
पूर्णांक policydb_load_isids(काष्ठा policydb *p, काष्ठा sidtab *s)
अणु
	काष्ठा ocontext *head, *c;
	पूर्णांक rc;

	rc = sidtab_init(s);
	अगर (rc) अणु
		pr_err("SELinux:  out of memory on SID table init\n");
		जाओ out;
	पूर्ण

	head = p->ocontexts[OCON_ISID];
	क्रम (c = head; c; c = c->next) अणु
		u32 sid = c->sid[0];
		स्थिर अक्षर *name = security_get_initial_sid_context(sid);

		अगर (sid == SECSID_शून्य) अणु
			pr_err("SELinux:  SID 0 was assigned a context.\n");
			sidtab_destroy(s);
			जाओ out;
		पूर्ण

		/* Ignore initial SIDs unused by this kernel. */
		अगर (!name)
			जारी;

		rc = sidtab_set_initial(s, sid, &c->context[0]);
		अगर (rc) अणु
			pr_err("SELinux:  unable to load initial SID %s.\n",
			       name);
			sidtab_destroy(s);
			जाओ out;
		पूर्ण
	पूर्ण
	rc = 0;
out:
	वापस rc;
पूर्ण

पूर्णांक policydb_class_isvalid(काष्ठा policydb *p, अचिन्हित पूर्णांक class)
अणु
	अगर (!class || class > p->p_classes.nprim)
		वापस 0;
	वापस 1;
पूर्ण

पूर्णांक policydb_role_isvalid(काष्ठा policydb *p, अचिन्हित पूर्णांक role)
अणु
	अगर (!role || role > p->p_roles.nprim)
		वापस 0;
	वापस 1;
पूर्ण

पूर्णांक policydb_type_isvalid(काष्ठा policydb *p, अचिन्हित पूर्णांक type)
अणु
	अगर (!type || type > p->p_types.nprim)
		वापस 0;
	वापस 1;
पूर्ण

/*
 * Return 1 अगर the fields in the security context
 * काष्ठाure `c' are valid.  Return 0 otherwise.
 */
पूर्णांक policydb_context_isvalid(काष्ठा policydb *p, काष्ठा context *c)
अणु
	काष्ठा role_datum *role;
	काष्ठा user_datum *usrdatum;

	अगर (!c->role || c->role > p->p_roles.nprim)
		वापस 0;

	अगर (!c->user || c->user > p->p_users.nprim)
		वापस 0;

	अगर (!c->type || c->type > p->p_types.nprim)
		वापस 0;

	अगर (c->role != OBJECT_R_VAL) अणु
		/*
		 * Role must be authorized क्रम the type.
		 */
		role = p->role_val_to_काष्ठा[c->role - 1];
		अगर (!role || !ebiपंचांगap_get_bit(&role->types, c->type - 1))
			/* role may not be associated with type */
			वापस 0;

		/*
		 * User must be authorized क्रम the role.
		 */
		usrdatum = p->user_val_to_काष्ठा[c->user - 1];
		अगर (!usrdatum)
			वापस 0;

		अगर (!ebiपंचांगap_get_bit(&usrdatum->roles, c->role - 1))
			/* user may not be associated with role */
			वापस 0;
	पूर्ण

	अगर (!mls_context_isvalid(p, c))
		वापस 0;

	वापस 1;
पूर्ण

/*
 * Read a MLS range काष्ठाure from a policydb binary
 * representation file.
 */
अटल पूर्णांक mls_पढ़ो_range_helper(काष्ठा mls_range *r, व्योम *fp)
अणु
	__le32 buf[2];
	u32 items;
	पूर्णांक rc;

	rc = next_entry(buf, fp, माप(u32));
	अगर (rc)
		जाओ out;

	rc = -EINVAL;
	items = le32_to_cpu(buf[0]);
	अगर (items > ARRAY_SIZE(buf)) अणु
		pr_err("SELinux: mls:  range overflow\n");
		जाओ out;
	पूर्ण

	rc = next_entry(buf, fp, माप(u32) * items);
	अगर (rc) अणु
		pr_err("SELinux: mls:  truncated range\n");
		जाओ out;
	पूर्ण

	r->level[0].sens = le32_to_cpu(buf[0]);
	अगर (items > 1)
		r->level[1].sens = le32_to_cpu(buf[1]);
	अन्यथा
		r->level[1].sens = r->level[0].sens;

	rc = ebiपंचांगap_पढ़ो(&r->level[0].cat, fp);
	अगर (rc) अणु
		pr_err("SELinux: mls:  error reading low categories\n");
		जाओ out;
	पूर्ण
	अगर (items > 1) अणु
		rc = ebiपंचांगap_पढ़ो(&r->level[1].cat, fp);
		अगर (rc) अणु
			pr_err("SELinux: mls:  error reading high categories\n");
			जाओ bad_high;
		पूर्ण
	पूर्ण अन्यथा अणु
		rc = ebiपंचांगap_cpy(&r->level[1].cat, &r->level[0].cat);
		अगर (rc) अणु
			pr_err("SELinux: mls:  out of memory\n");
			जाओ bad_high;
		पूर्ण
	पूर्ण

	वापस 0;
bad_high:
	ebiपंचांगap_destroy(&r->level[0].cat);
out:
	वापस rc;
पूर्ण

/*
 * Read and validate a security context काष्ठाure
 * from a policydb binary representation file.
 */
अटल पूर्णांक context_पढ़ो_and_validate(काष्ठा context *c,
				     काष्ठा policydb *p,
				     व्योम *fp)
अणु
	__le32 buf[3];
	पूर्णांक rc;

	rc = next_entry(buf, fp, माप buf);
	अगर (rc) अणु
		pr_err("SELinux: context truncated\n");
		जाओ out;
	पूर्ण
	c->user = le32_to_cpu(buf[0]);
	c->role = le32_to_cpu(buf[1]);
	c->type = le32_to_cpu(buf[2]);
	अगर (p->policyvers >= POLICYDB_VERSION_MLS) अणु
		rc = mls_पढ़ो_range_helper(&c->range, fp);
		अगर (rc) अणु
			pr_err("SELinux: error reading MLS range of context\n");
			जाओ out;
		पूर्ण
	पूर्ण

	rc = -EINVAL;
	अगर (!policydb_context_isvalid(p, c)) अणु
		pr_err("SELinux:  invalid security context\n");
		context_destroy(c);
		जाओ out;
	पूर्ण
	rc = 0;
out:
	वापस rc;
पूर्ण

/*
 * The following *_पढ़ो functions are used to
 * पढ़ो the symbol data from a policy database
 * binary representation file.
 */

अटल पूर्णांक str_पढ़ो(अक्षर **strp, gfp_t flags, व्योम *fp, u32 len)
अणु
	पूर्णांक rc;
	अक्षर *str;

	अगर ((len == 0) || (len == (u32)-1))
		वापस -EINVAL;

	str = kदो_स्मृति(len + 1, flags | __GFP_NOWARN);
	अगर (!str)
		वापस -ENOMEM;

	rc = next_entry(str, fp, len);
	अगर (rc) अणु
		kमुक्त(str);
		वापस rc;
	पूर्ण

	str[len] = '\0';
	*strp = str;
	वापस 0;
पूर्ण

अटल पूर्णांक perm_पढ़ो(काष्ठा policydb *p, काष्ठा symtab *s, व्योम *fp)
अणु
	अक्षर *key = शून्य;
	काष्ठा perm_datum *perdatum;
	पूर्णांक rc;
	__le32 buf[2];
	u32 len;

	perdatum = kzalloc(माप(*perdatum), GFP_KERNEL);
	अगर (!perdatum)
		वापस -ENOMEM;

	rc = next_entry(buf, fp, माप buf);
	अगर (rc)
		जाओ bad;

	len = le32_to_cpu(buf[0]);
	perdatum->value = le32_to_cpu(buf[1]);

	rc = str_पढ़ो(&key, GFP_KERNEL, fp, len);
	अगर (rc)
		जाओ bad;

	rc = symtab_insert(s, key, perdatum);
	अगर (rc)
		जाओ bad;

	वापस 0;
bad:
	perm_destroy(key, perdatum, शून्य);
	वापस rc;
पूर्ण

अटल पूर्णांक common_पढ़ो(काष्ठा policydb *p, काष्ठा symtab *s, व्योम *fp)
अणु
	अक्षर *key = शून्य;
	काष्ठा common_datum *comdatum;
	__le32 buf[4];
	u32 len, nel;
	पूर्णांक i, rc;

	comdatum = kzalloc(माप(*comdatum), GFP_KERNEL);
	अगर (!comdatum)
		वापस -ENOMEM;

	rc = next_entry(buf, fp, माप buf);
	अगर (rc)
		जाओ bad;

	len = le32_to_cpu(buf[0]);
	comdatum->value = le32_to_cpu(buf[1]);
	nel = le32_to_cpu(buf[3]);

	rc = symtab_init(&comdatum->permissions, nel);
	अगर (rc)
		जाओ bad;
	comdatum->permissions.nprim = le32_to_cpu(buf[2]);

	rc = str_पढ़ो(&key, GFP_KERNEL, fp, len);
	अगर (rc)
		जाओ bad;

	क्रम (i = 0; i < nel; i++) अणु
		rc = perm_पढ़ो(p, &comdatum->permissions, fp);
		अगर (rc)
			जाओ bad;
	पूर्ण

	rc = symtab_insert(s, key, comdatum);
	अगर (rc)
		जाओ bad;
	वापस 0;
bad:
	common_destroy(key, comdatum, शून्य);
	वापस rc;
पूर्ण

अटल व्योम type_set_init(काष्ठा type_set *t)
अणु
	ebiपंचांगap_init(&t->types);
	ebiपंचांगap_init(&t->negset);
पूर्ण

अटल पूर्णांक type_set_पढ़ो(काष्ठा type_set *t, व्योम *fp)
अणु
	__le32 buf[1];
	पूर्णांक rc;

	अगर (ebiपंचांगap_पढ़ो(&t->types, fp))
		वापस -EINVAL;
	अगर (ebiपंचांगap_पढ़ो(&t->negset, fp))
		वापस -EINVAL;

	rc = next_entry(buf, fp, माप(u32));
	अगर (rc < 0)
		वापस -EINVAL;
	t->flags = le32_to_cpu(buf[0]);

	वापस 0;
पूर्ण


अटल पूर्णांक पढ़ो_cons_helper(काष्ठा policydb *p,
				काष्ठा स्थिरraपूर्णांक_node **nodep,
				पूर्णांक ncons, पूर्णांक allowxtarget, व्योम *fp)
अणु
	काष्ठा स्थिरraपूर्णांक_node *c, *lc;
	काष्ठा स्थिरraपूर्णांक_expr *e, *le;
	__le32 buf[3];
	u32 nexpr;
	पूर्णांक rc, i, j, depth;

	lc = शून्य;
	क्रम (i = 0; i < ncons; i++) अणु
		c = kzalloc(माप(*c), GFP_KERNEL);
		अगर (!c)
			वापस -ENOMEM;

		अगर (lc)
			lc->next = c;
		अन्यथा
			*nodep = c;

		rc = next_entry(buf, fp, (माप(u32) * 2));
		अगर (rc)
			वापस rc;
		c->permissions = le32_to_cpu(buf[0]);
		nexpr = le32_to_cpu(buf[1]);
		le = शून्य;
		depth = -1;
		क्रम (j = 0; j < nexpr; j++) अणु
			e = kzalloc(माप(*e), GFP_KERNEL);
			अगर (!e)
				वापस -ENOMEM;

			अगर (le)
				le->next = e;
			अन्यथा
				c->expr = e;

			rc = next_entry(buf, fp, (माप(u32) * 3));
			अगर (rc)
				वापस rc;
			e->expr_type = le32_to_cpu(buf[0]);
			e->attr = le32_to_cpu(buf[1]);
			e->op = le32_to_cpu(buf[2]);

			चयन (e->expr_type) अणु
			हाल CEXPR_NOT:
				अगर (depth < 0)
					वापस -EINVAL;
				अवरोध;
			हाल CEXPR_AND:
			हाल CEXPR_OR:
				अगर (depth < 1)
					वापस -EINVAL;
				depth--;
				अवरोध;
			हाल CEXPR_ATTR:
				अगर (depth == (CEXPR_MAXDEPTH - 1))
					वापस -EINVAL;
				depth++;
				अवरोध;
			हाल CEXPR_NAMES:
				अगर (!allowxtarget && (e->attr & CEXPR_XTARGET))
					वापस -EINVAL;
				अगर (depth == (CEXPR_MAXDEPTH - 1))
					वापस -EINVAL;
				depth++;
				rc = ebiपंचांगap_पढ़ो(&e->names, fp);
				अगर (rc)
					वापस rc;
				अगर (p->policyvers >=
				    POLICYDB_VERSION_CONSTRAINT_NAMES) अणु
					e->type_names = kzalloc(माप
						(*e->type_names), GFP_KERNEL);
					अगर (!e->type_names)
						वापस -ENOMEM;
					type_set_init(e->type_names);
					rc = type_set_पढ़ो(e->type_names, fp);
					अगर (rc)
						वापस rc;
				पूर्ण
				अवरोध;
			शेष:
				वापस -EINVAL;
			पूर्ण
			le = e;
		पूर्ण
		अगर (depth != 0)
			वापस -EINVAL;
		lc = c;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक class_पढ़ो(काष्ठा policydb *p, काष्ठा symtab *s, व्योम *fp)
अणु
	अक्षर *key = शून्य;
	काष्ठा class_datum *cladatum;
	__le32 buf[6];
	u32 len, len2, ncons, nel;
	पूर्णांक i, rc;

	cladatum = kzalloc(माप(*cladatum), GFP_KERNEL);
	अगर (!cladatum)
		वापस -ENOMEM;

	rc = next_entry(buf, fp, माप(u32)*6);
	अगर (rc)
		जाओ bad;

	len = le32_to_cpu(buf[0]);
	len2 = le32_to_cpu(buf[1]);
	cladatum->value = le32_to_cpu(buf[2]);
	nel = le32_to_cpu(buf[4]);

	rc = symtab_init(&cladatum->permissions, nel);
	अगर (rc)
		जाओ bad;
	cladatum->permissions.nprim = le32_to_cpu(buf[3]);

	ncons = le32_to_cpu(buf[5]);

	rc = str_पढ़ो(&key, GFP_KERNEL, fp, len);
	अगर (rc)
		जाओ bad;

	अगर (len2) अणु
		rc = str_पढ़ो(&cladatum->comkey, GFP_KERNEL, fp, len2);
		अगर (rc)
			जाओ bad;

		rc = -EINVAL;
		cladatum->comdatum = symtab_search(&p->p_commons,
						   cladatum->comkey);
		अगर (!cladatum->comdatum) अणु
			pr_err("SELinux:  unknown common %s\n",
			       cladatum->comkey);
			जाओ bad;
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < nel; i++) अणु
		rc = perm_पढ़ो(p, &cladatum->permissions, fp);
		अगर (rc)
			जाओ bad;
	पूर्ण

	rc = पढ़ो_cons_helper(p, &cladatum->स्थिरraपूर्णांकs, ncons, 0, fp);
	अगर (rc)
		जाओ bad;

	अगर (p->policyvers >= POLICYDB_VERSION_VALIDATETRANS) अणु
		/* grab the validatetrans rules */
		rc = next_entry(buf, fp, माप(u32));
		अगर (rc)
			जाओ bad;
		ncons = le32_to_cpu(buf[0]);
		rc = पढ़ो_cons_helper(p, &cladatum->validatetrans,
				ncons, 1, fp);
		अगर (rc)
			जाओ bad;
	पूर्ण

	अगर (p->policyvers >= POLICYDB_VERSION_NEW_OBJECT_DEFAULTS) अणु
		rc = next_entry(buf, fp, माप(u32) * 3);
		अगर (rc)
			जाओ bad;

		cladatum->शेष_user = le32_to_cpu(buf[0]);
		cladatum->शेष_role = le32_to_cpu(buf[1]);
		cladatum->शेष_range = le32_to_cpu(buf[2]);
	पूर्ण

	अगर (p->policyvers >= POLICYDB_VERSION_DEFAULT_TYPE) अणु
		rc = next_entry(buf, fp, माप(u32) * 1);
		अगर (rc)
			जाओ bad;
		cladatum->शेष_type = le32_to_cpu(buf[0]);
	पूर्ण

	rc = symtab_insert(s, key, cladatum);
	अगर (rc)
		जाओ bad;

	वापस 0;
bad:
	cls_destroy(key, cladatum, शून्य);
	वापस rc;
पूर्ण

अटल पूर्णांक role_पढ़ो(काष्ठा policydb *p, काष्ठा symtab *s, व्योम *fp)
अणु
	अक्षर *key = शून्य;
	काष्ठा role_datum *role;
	पूर्णांक rc, to_पढ़ो = 2;
	__le32 buf[3];
	u32 len;

	role = kzalloc(माप(*role), GFP_KERNEL);
	अगर (!role)
		वापस -ENOMEM;

	अगर (p->policyvers >= POLICYDB_VERSION_BOUNDARY)
		to_पढ़ो = 3;

	rc = next_entry(buf, fp, माप(buf[0]) * to_पढ़ो);
	अगर (rc)
		जाओ bad;

	len = le32_to_cpu(buf[0]);
	role->value = le32_to_cpu(buf[1]);
	अगर (p->policyvers >= POLICYDB_VERSION_BOUNDARY)
		role->bounds = le32_to_cpu(buf[2]);

	rc = str_पढ़ो(&key, GFP_KERNEL, fp, len);
	अगर (rc)
		जाओ bad;

	rc = ebiपंचांगap_पढ़ो(&role->करोminates, fp);
	अगर (rc)
		जाओ bad;

	rc = ebiपंचांगap_पढ़ो(&role->types, fp);
	अगर (rc)
		जाओ bad;

	अगर (म_भेद(key, OBJECT_R) == 0) अणु
		rc = -EINVAL;
		अगर (role->value != OBJECT_R_VAL) अणु
			pr_err("SELinux: Role %s has wrong value %d\n",
			       OBJECT_R, role->value);
			जाओ bad;
		पूर्ण
		rc = 0;
		जाओ bad;
	पूर्ण

	rc = symtab_insert(s, key, role);
	अगर (rc)
		जाओ bad;
	वापस 0;
bad:
	role_destroy(key, role, शून्य);
	वापस rc;
पूर्ण

अटल पूर्णांक type_पढ़ो(काष्ठा policydb *p, काष्ठा symtab *s, व्योम *fp)
अणु
	अक्षर *key = शून्य;
	काष्ठा type_datum *typdatum;
	पूर्णांक rc, to_पढ़ो = 3;
	__le32 buf[4];
	u32 len;

	typdatum = kzalloc(माप(*typdatum), GFP_KERNEL);
	अगर (!typdatum)
		वापस -ENOMEM;

	अगर (p->policyvers >= POLICYDB_VERSION_BOUNDARY)
		to_पढ़ो = 4;

	rc = next_entry(buf, fp, माप(buf[0]) * to_पढ़ो);
	अगर (rc)
		जाओ bad;

	len = le32_to_cpu(buf[0]);
	typdatum->value = le32_to_cpu(buf[1]);
	अगर (p->policyvers >= POLICYDB_VERSION_BOUNDARY) अणु
		u32 prop = le32_to_cpu(buf[2]);

		अगर (prop & TYPEDATUM_PROPERTY_PRIMARY)
			typdatum->primary = 1;
		अगर (prop & TYPEDATUM_PROPERTY_ATTRIBUTE)
			typdatum->attribute = 1;

		typdatum->bounds = le32_to_cpu(buf[3]);
	पूर्ण अन्यथा अणु
		typdatum->primary = le32_to_cpu(buf[2]);
	पूर्ण

	rc = str_पढ़ो(&key, GFP_KERNEL, fp, len);
	अगर (rc)
		जाओ bad;

	rc = symtab_insert(s, key, typdatum);
	अगर (rc)
		जाओ bad;
	वापस 0;
bad:
	type_destroy(key, typdatum, शून्य);
	वापस rc;
पूर्ण


/*
 * Read a MLS level काष्ठाure from a policydb binary
 * representation file.
 */
अटल पूर्णांक mls_पढ़ो_level(काष्ठा mls_level *lp, व्योम *fp)
अणु
	__le32 buf[1];
	पूर्णांक rc;

	स_रखो(lp, 0, माप(*lp));

	rc = next_entry(buf, fp, माप buf);
	अगर (rc) अणु
		pr_err("SELinux: mls: truncated level\n");
		वापस rc;
	पूर्ण
	lp->sens = le32_to_cpu(buf[0]);

	rc = ebiपंचांगap_पढ़ो(&lp->cat, fp);
	अगर (rc) अणु
		pr_err("SELinux: mls:  error reading level categories\n");
		वापस rc;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक user_पढ़ो(काष्ठा policydb *p, काष्ठा symtab *s, व्योम *fp)
अणु
	अक्षर *key = शून्य;
	काष्ठा user_datum *usrdatum;
	पूर्णांक rc, to_पढ़ो = 2;
	__le32 buf[3];
	u32 len;

	usrdatum = kzalloc(माप(*usrdatum), GFP_KERNEL);
	अगर (!usrdatum)
		वापस -ENOMEM;

	अगर (p->policyvers >= POLICYDB_VERSION_BOUNDARY)
		to_पढ़ो = 3;

	rc = next_entry(buf, fp, माप(buf[0]) * to_पढ़ो);
	अगर (rc)
		जाओ bad;

	len = le32_to_cpu(buf[0]);
	usrdatum->value = le32_to_cpu(buf[1]);
	अगर (p->policyvers >= POLICYDB_VERSION_BOUNDARY)
		usrdatum->bounds = le32_to_cpu(buf[2]);

	rc = str_पढ़ो(&key, GFP_KERNEL, fp, len);
	अगर (rc)
		जाओ bad;

	rc = ebiपंचांगap_पढ़ो(&usrdatum->roles, fp);
	अगर (rc)
		जाओ bad;

	अगर (p->policyvers >= POLICYDB_VERSION_MLS) अणु
		rc = mls_पढ़ो_range_helper(&usrdatum->range, fp);
		अगर (rc)
			जाओ bad;
		rc = mls_पढ़ो_level(&usrdatum->dfltlevel, fp);
		अगर (rc)
			जाओ bad;
	पूर्ण

	rc = symtab_insert(s, key, usrdatum);
	अगर (rc)
		जाओ bad;
	वापस 0;
bad:
	user_destroy(key, usrdatum, शून्य);
	वापस rc;
पूर्ण

अटल पूर्णांक sens_पढ़ो(काष्ठा policydb *p, काष्ठा symtab *s, व्योम *fp)
अणु
	अक्षर *key = शून्य;
	काष्ठा level_datum *levdatum;
	पूर्णांक rc;
	__le32 buf[2];
	u32 len;

	levdatum = kzalloc(माप(*levdatum), GFP_ATOMIC);
	अगर (!levdatum)
		वापस -ENOMEM;

	rc = next_entry(buf, fp, माप buf);
	अगर (rc)
		जाओ bad;

	len = le32_to_cpu(buf[0]);
	levdatum->isalias = le32_to_cpu(buf[1]);

	rc = str_पढ़ो(&key, GFP_ATOMIC, fp, len);
	अगर (rc)
		जाओ bad;

	rc = -ENOMEM;
	levdatum->level = kदो_स्मृति(माप(*levdatum->level), GFP_ATOMIC);
	अगर (!levdatum->level)
		जाओ bad;

	rc = mls_पढ़ो_level(levdatum->level, fp);
	अगर (rc)
		जाओ bad;

	rc = symtab_insert(s, key, levdatum);
	अगर (rc)
		जाओ bad;
	वापस 0;
bad:
	sens_destroy(key, levdatum, शून्य);
	वापस rc;
पूर्ण

अटल पूर्णांक cat_पढ़ो(काष्ठा policydb *p, काष्ठा symtab *s, व्योम *fp)
अणु
	अक्षर *key = शून्य;
	काष्ठा cat_datum *catdatum;
	पूर्णांक rc;
	__le32 buf[3];
	u32 len;

	catdatum = kzalloc(माप(*catdatum), GFP_ATOMIC);
	अगर (!catdatum)
		वापस -ENOMEM;

	rc = next_entry(buf, fp, माप buf);
	अगर (rc)
		जाओ bad;

	len = le32_to_cpu(buf[0]);
	catdatum->value = le32_to_cpu(buf[1]);
	catdatum->isalias = le32_to_cpu(buf[2]);

	rc = str_पढ़ो(&key, GFP_ATOMIC, fp, len);
	अगर (rc)
		जाओ bad;

	rc = symtab_insert(s, key, catdatum);
	अगर (rc)
		जाओ bad;
	वापस 0;
bad:
	cat_destroy(key, catdatum, शून्य);
	वापस rc;
पूर्ण

अटल पूर्णांक (*पढ़ो_f[SYM_NUM]) (काष्ठा policydb *p, काष्ठा symtab *s, व्योम *fp) =
अणु
	common_पढ़ो,
	class_पढ़ो,
	role_पढ़ो,
	type_पढ़ो,
	user_पढ़ो,
	cond_पढ़ो_bool,
	sens_पढ़ो,
	cat_पढ़ो,
पूर्ण;

अटल पूर्णांक user_bounds_sanity_check(व्योम *key, व्योम *datum, व्योम *datap)
अणु
	काष्ठा user_datum *upper, *user;
	काष्ठा policydb *p = datap;
	पूर्णांक depth = 0;

	upper = user = datum;
	जबतक (upper->bounds) अणु
		काष्ठा ebiपंचांगap_node *node;
		अचिन्हित दीर्घ bit;

		अगर (++depth == POLICYDB_BOUNDS_MAXDEPTH) अणु
			pr_err("SELinux: user %s: "
			       "too deep or looped boundary",
			       (अक्षर *) key);
			वापस -EINVAL;
		पूर्ण

		upper = p->user_val_to_काष्ठा[upper->bounds - 1];
		ebiपंचांगap_क्रम_each_positive_bit(&user->roles, node, bit) अणु
			अगर (ebiपंचांगap_get_bit(&upper->roles, bit))
				जारी;

			pr_err("SELinux: boundary violated policy: "
			       "user=%s role=%s bounds=%s\n",
			       sym_name(p, SYM_USERS, user->value - 1),
			       sym_name(p, SYM_ROLES, bit),
			       sym_name(p, SYM_USERS, upper->value - 1));

			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक role_bounds_sanity_check(व्योम *key, व्योम *datum, व्योम *datap)
अणु
	काष्ठा role_datum *upper, *role;
	काष्ठा policydb *p = datap;
	पूर्णांक depth = 0;

	upper = role = datum;
	जबतक (upper->bounds) अणु
		काष्ठा ebiपंचांगap_node *node;
		अचिन्हित दीर्घ bit;

		अगर (++depth == POLICYDB_BOUNDS_MAXDEPTH) अणु
			pr_err("SELinux: role %s: "
			       "too deep or looped bounds\n",
			       (अक्षर *) key);
			वापस -EINVAL;
		पूर्ण

		upper = p->role_val_to_काष्ठा[upper->bounds - 1];
		ebiपंचांगap_क्रम_each_positive_bit(&role->types, node, bit) अणु
			अगर (ebiपंचांगap_get_bit(&upper->types, bit))
				जारी;

			pr_err("SELinux: boundary violated policy: "
			       "role=%s type=%s bounds=%s\n",
			       sym_name(p, SYM_ROLES, role->value - 1),
			       sym_name(p, SYM_TYPES, bit),
			       sym_name(p, SYM_ROLES, upper->value - 1));

			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक type_bounds_sanity_check(व्योम *key, व्योम *datum, व्योम *datap)
अणु
	काष्ठा type_datum *upper;
	काष्ठा policydb *p = datap;
	पूर्णांक depth = 0;

	upper = datum;
	जबतक (upper->bounds) अणु
		अगर (++depth == POLICYDB_BOUNDS_MAXDEPTH) अणु
			pr_err("SELinux: type %s: "
			       "too deep or looped boundary\n",
			       (अक्षर *) key);
			वापस -EINVAL;
		पूर्ण

		upper = p->type_val_to_काष्ठा[upper->bounds - 1];
		BUG_ON(!upper);

		अगर (upper->attribute) अणु
			pr_err("SELinux: type %s: "
			       "bounded by attribute %s",
			       (अक्षर *) key,
			       sym_name(p, SYM_TYPES, upper->value - 1));
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक policydb_bounds_sanity_check(काष्ठा policydb *p)
अणु
	पूर्णांक rc;

	अगर (p->policyvers < POLICYDB_VERSION_BOUNDARY)
		वापस 0;

	rc = hashtab_map(&p->p_users.table, user_bounds_sanity_check, p);
	अगर (rc)
		वापस rc;

	rc = hashtab_map(&p->p_roles.table, role_bounds_sanity_check, p);
	अगर (rc)
		वापस rc;

	rc = hashtab_map(&p->p_types.table, type_bounds_sanity_check, p);
	अगर (rc)
		वापस rc;

	वापस 0;
पूर्ण

u16 string_to_security_class(काष्ठा policydb *p, स्थिर अक्षर *name)
अणु
	काष्ठा class_datum *cladatum;

	cladatum = symtab_search(&p->p_classes, name);
	अगर (!cladatum)
		वापस 0;

	वापस cladatum->value;
पूर्ण

u32 string_to_av_perm(काष्ठा policydb *p, u16 tclass, स्थिर अक्षर *name)
अणु
	काष्ठा class_datum *cladatum;
	काष्ठा perm_datum *perdatum = शून्य;
	काष्ठा common_datum *comdatum;

	अगर (!tclass || tclass > p->p_classes.nprim)
		वापस 0;

	cladatum = p->class_val_to_काष्ठा[tclass-1];
	comdatum = cladatum->comdatum;
	अगर (comdatum)
		perdatum = symtab_search(&comdatum->permissions, name);
	अगर (!perdatum)
		perdatum = symtab_search(&cladatum->permissions, name);
	अगर (!perdatum)
		वापस 0;

	वापस 1U << (perdatum->value-1);
पूर्ण

अटल पूर्णांक range_पढ़ो(काष्ठा policydb *p, व्योम *fp)
अणु
	काष्ठा range_trans *rt = शून्य;
	काष्ठा mls_range *r = शून्य;
	पूर्णांक i, rc;
	__le32 buf[2];
	u32 nel;

	अगर (p->policyvers < POLICYDB_VERSION_MLS)
		वापस 0;

	rc = next_entry(buf, fp, माप(u32));
	अगर (rc)
		वापस rc;

	nel = le32_to_cpu(buf[0]);

	rc = hashtab_init(&p->range_tr, nel);
	अगर (rc)
		वापस rc;

	क्रम (i = 0; i < nel; i++) अणु
		rc = -ENOMEM;
		rt = kzalloc(माप(*rt), GFP_KERNEL);
		अगर (!rt)
			जाओ out;

		rc = next_entry(buf, fp, (माप(u32) * 2));
		अगर (rc)
			जाओ out;

		rt->source_type = le32_to_cpu(buf[0]);
		rt->target_type = le32_to_cpu(buf[1]);
		अगर (p->policyvers >= POLICYDB_VERSION_RANGETRANS) अणु
			rc = next_entry(buf, fp, माप(u32));
			अगर (rc)
				जाओ out;
			rt->target_class = le32_to_cpu(buf[0]);
		पूर्ण अन्यथा
			rt->target_class = p->process_class;

		rc = -EINVAL;
		अगर (!policydb_type_isvalid(p, rt->source_type) ||
		    !policydb_type_isvalid(p, rt->target_type) ||
		    !policydb_class_isvalid(p, rt->target_class))
			जाओ out;

		rc = -ENOMEM;
		r = kzalloc(माप(*r), GFP_KERNEL);
		अगर (!r)
			जाओ out;

		rc = mls_पढ़ो_range_helper(r, fp);
		अगर (rc)
			जाओ out;

		rc = -EINVAL;
		अगर (!mls_range_isvalid(p, r)) अणु
			pr_warn("SELinux:  rangetrans:  invalid range\n");
			जाओ out;
		पूर्ण

		rc = hashtab_insert(&p->range_tr, rt, r, rangetr_key_params);
		अगर (rc)
			जाओ out;

		rt = शून्य;
		r = शून्य;
	पूर्ण
	hash_eval(&p->range_tr, "rangetr");
	rc = 0;
out:
	kमुक्त(rt);
	kमुक्त(r);
	वापस rc;
पूर्ण

अटल पूर्णांक filename_trans_पढ़ो_helper_compat(काष्ठा policydb *p, व्योम *fp)
अणु
	काष्ठा filename_trans_key key, *ft = शून्य;
	काष्ठा filename_trans_datum *last, *datum = शून्य;
	अक्षर *name = शून्य;
	u32 len, stype, otype;
	__le32 buf[4];
	पूर्णांक rc;

	/* length of the path component string */
	rc = next_entry(buf, fp, माप(u32));
	अगर (rc)
		वापस rc;
	len = le32_to_cpu(buf[0]);

	/* path component string */
	rc = str_पढ़ो(&name, GFP_KERNEL, fp, len);
	अगर (rc)
		वापस rc;

	rc = next_entry(buf, fp, माप(u32) * 4);
	अगर (rc)
		जाओ out;

	stype = le32_to_cpu(buf[0]);
	key.ttype = le32_to_cpu(buf[1]);
	key.tclass = le32_to_cpu(buf[2]);
	key.name = name;

	otype = le32_to_cpu(buf[3]);

	last = शून्य;
	datum = policydb_filenametr_search(p, &key);
	जबतक (datum) अणु
		अगर (unlikely(ebiपंचांगap_get_bit(&datum->stypes, stype - 1))) अणु
			/* conflicting/duplicate rules are ignored */
			datum = शून्य;
			जाओ out;
		पूर्ण
		अगर (likely(datum->otype == otype))
			अवरोध;
		last = datum;
		datum = datum->next;
	पूर्ण
	अगर (!datum) अणु
		rc = -ENOMEM;
		datum = kदो_स्मृति(माप(*datum), GFP_KERNEL);
		अगर (!datum)
			जाओ out;

		ebiपंचांगap_init(&datum->stypes);
		datum->otype = otype;
		datum->next = शून्य;

		अगर (unlikely(last)) अणु
			last->next = datum;
		पूर्ण अन्यथा अणु
			rc = -ENOMEM;
			ft = kmemdup(&key, माप(key), GFP_KERNEL);
			अगर (!ft)
				जाओ out;

			rc = hashtab_insert(&p->filename_trans, ft, datum,
					    filenametr_key_params);
			अगर (rc)
				जाओ out;
			name = शून्य;

			rc = ebiपंचांगap_set_bit(&p->filename_trans_ttypes,
					     key.ttype, 1);
			अगर (rc)
				वापस rc;
		पूर्ण
	पूर्ण
	kमुक्त(name);
	वापस ebiपंचांगap_set_bit(&datum->stypes, stype - 1, 1);

out:
	kमुक्त(ft);
	kमुक्त(name);
	kमुक्त(datum);
	वापस rc;
पूर्ण

अटल पूर्णांक filename_trans_पढ़ो_helper(काष्ठा policydb *p, व्योम *fp)
अणु
	काष्ठा filename_trans_key *ft = शून्य;
	काष्ठा filename_trans_datum **dst, *datum, *first = शून्य;
	अक्षर *name = शून्य;
	u32 len, ttype, tclass, ndatum, i;
	__le32 buf[3];
	पूर्णांक rc;

	/* length of the path component string */
	rc = next_entry(buf, fp, माप(u32));
	अगर (rc)
		वापस rc;
	len = le32_to_cpu(buf[0]);

	/* path component string */
	rc = str_पढ़ो(&name, GFP_KERNEL, fp, len);
	अगर (rc)
		वापस rc;

	rc = next_entry(buf, fp, माप(u32) * 3);
	अगर (rc)
		जाओ out;

	ttype = le32_to_cpu(buf[0]);
	tclass = le32_to_cpu(buf[1]);

	ndatum = le32_to_cpu(buf[2]);
	अगर (ndatum == 0) अणु
		pr_err("SELinux:  Filename transition key with no datum\n");
		rc = -ENOENT;
		जाओ out;
	पूर्ण

	dst = &first;
	क्रम (i = 0; i < ndatum; i++) अणु
		rc = -ENOMEM;
		datum = kदो_स्मृति(माप(*datum), GFP_KERNEL);
		अगर (!datum)
			जाओ out;

		*dst = datum;

		/* ebiपंचांगap_पढ़ो() will at least init the biपंचांगap */
		rc = ebiपंचांगap_पढ़ो(&datum->stypes, fp);
		अगर (rc)
			जाओ out;

		rc = next_entry(buf, fp, माप(u32));
		अगर (rc)
			जाओ out;

		datum->otype = le32_to_cpu(buf[0]);
		datum->next = शून्य;

		dst = &datum->next;
	पूर्ण

	rc = -ENOMEM;
	ft = kदो_स्मृति(माप(*ft), GFP_KERNEL);
	अगर (!ft)
		जाओ out;

	ft->ttype = ttype;
	ft->tclass = tclass;
	ft->name = name;

	rc = hashtab_insert(&p->filename_trans, ft, first,
			    filenametr_key_params);
	अगर (rc == -EEXIST)
		pr_err("SELinux:  Duplicate filename transition key\n");
	अगर (rc)
		जाओ out;

	वापस ebiपंचांगap_set_bit(&p->filename_trans_ttypes, ttype, 1);

out:
	kमुक्त(ft);
	kमुक्त(name);
	जबतक (first) अणु
		datum = first;
		first = first->next;

		ebiपंचांगap_destroy(&datum->stypes);
		kमुक्त(datum);
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक filename_trans_पढ़ो(काष्ठा policydb *p, व्योम *fp)
अणु
	u32 nel;
	__le32 buf[1];
	पूर्णांक rc, i;

	अगर (p->policyvers < POLICYDB_VERSION_खाताNAME_TRANS)
		वापस 0;

	rc = next_entry(buf, fp, माप(u32));
	अगर (rc)
		वापस rc;
	nel = le32_to_cpu(buf[0]);

	अगर (p->policyvers < POLICYDB_VERSION_COMP_FTRANS) अणु
		p->compat_filename_trans_count = nel;

		rc = hashtab_init(&p->filename_trans, (1 << 11));
		अगर (rc)
			वापस rc;

		क्रम (i = 0; i < nel; i++) अणु
			rc = filename_trans_पढ़ो_helper_compat(p, fp);
			अगर (rc)
				वापस rc;
		पूर्ण
	पूर्ण अन्यथा अणु
		rc = hashtab_init(&p->filename_trans, nel);
		अगर (rc)
			वापस rc;

		क्रम (i = 0; i < nel; i++) अणु
			rc = filename_trans_पढ़ो_helper(p, fp);
			अगर (rc)
				वापस rc;
		पूर्ण
	पूर्ण
	hash_eval(&p->filename_trans, "filenametr");
	वापस 0;
पूर्ण

अटल पूर्णांक genfs_पढ़ो(काष्ठा policydb *p, व्योम *fp)
अणु
	पूर्णांक i, j, rc;
	u32 nel, nel2, len, len2;
	__le32 buf[1];
	काष्ठा ocontext *l, *c;
	काष्ठा ocontext *newc = शून्य;
	काष्ठा genfs *genfs_p, *genfs;
	काष्ठा genfs *newgenfs = शून्य;

	rc = next_entry(buf, fp, माप(u32));
	अगर (rc)
		वापस rc;
	nel = le32_to_cpu(buf[0]);

	क्रम (i = 0; i < nel; i++) अणु
		rc = next_entry(buf, fp, माप(u32));
		अगर (rc)
			जाओ out;
		len = le32_to_cpu(buf[0]);

		rc = -ENOMEM;
		newgenfs = kzalloc(माप(*newgenfs), GFP_KERNEL);
		अगर (!newgenfs)
			जाओ out;

		rc = str_पढ़ो(&newgenfs->fstype, GFP_KERNEL, fp, len);
		अगर (rc)
			जाओ out;

		क्रम (genfs_p = शून्य, genfs = p->genfs; genfs;
		     genfs_p = genfs, genfs = genfs->next) अणु
			rc = -EINVAL;
			अगर (म_भेद(newgenfs->fstype, genfs->fstype) == 0) अणु
				pr_err("SELinux:  dup genfs fstype %s\n",
				       newgenfs->fstype);
				जाओ out;
			पूर्ण
			अगर (म_भेद(newgenfs->fstype, genfs->fstype) < 0)
				अवरोध;
		पूर्ण
		newgenfs->next = genfs;
		अगर (genfs_p)
			genfs_p->next = newgenfs;
		अन्यथा
			p->genfs = newgenfs;
		genfs = newgenfs;
		newgenfs = शून्य;

		rc = next_entry(buf, fp, माप(u32));
		अगर (rc)
			जाओ out;

		nel2 = le32_to_cpu(buf[0]);
		क्रम (j = 0; j < nel2; j++) अणु
			rc = next_entry(buf, fp, माप(u32));
			अगर (rc)
				जाओ out;
			len = le32_to_cpu(buf[0]);

			rc = -ENOMEM;
			newc = kzalloc(माप(*newc), GFP_KERNEL);
			अगर (!newc)
				जाओ out;

			rc = str_पढ़ो(&newc->u.name, GFP_KERNEL, fp, len);
			अगर (rc)
				जाओ out;

			rc = next_entry(buf, fp, माप(u32));
			अगर (rc)
				जाओ out;

			newc->v.sclass = le32_to_cpu(buf[0]);
			rc = context_पढ़ो_and_validate(&newc->context[0], p, fp);
			अगर (rc)
				जाओ out;

			क्रम (l = शून्य, c = genfs->head; c;
			     l = c, c = c->next) अणु
				rc = -EINVAL;
				अगर (!म_भेद(newc->u.name, c->u.name) &&
				    (!c->v.sclass || !newc->v.sclass ||
				     newc->v.sclass == c->v.sclass)) अणु
					pr_err("SELinux:  dup genfs entry (%s,%s)\n",
					       genfs->fstype, c->u.name);
					जाओ out;
				पूर्ण
				len = म_माप(newc->u.name);
				len2 = म_माप(c->u.name);
				अगर (len > len2)
					अवरोध;
			पूर्ण

			newc->next = c;
			अगर (l)
				l->next = newc;
			अन्यथा
				genfs->head = newc;
			newc = शून्य;
		पूर्ण
	पूर्ण
	rc = 0;
out:
	अगर (newgenfs) अणु
		kमुक्त(newgenfs->fstype);
		kमुक्त(newgenfs);
	पूर्ण
	ocontext_destroy(newc, OCON_FSUSE);

	वापस rc;
पूर्ण

अटल पूर्णांक ocontext_पढ़ो(काष्ठा policydb *p, काष्ठा policydb_compat_info *info,
			 व्योम *fp)
अणु
	पूर्णांक i, j, rc;
	u32 nel, len;
	__be64 prefixbuf[1];
	__le32 buf[3];
	काष्ठा ocontext *l, *c;
	u32 nodebuf[8];

	क्रम (i = 0; i < info->ocon_num; i++) अणु
		rc = next_entry(buf, fp, माप(u32));
		अगर (rc)
			जाओ out;
		nel = le32_to_cpu(buf[0]);

		l = शून्य;
		क्रम (j = 0; j < nel; j++) अणु
			rc = -ENOMEM;
			c = kzalloc(माप(*c), GFP_KERNEL);
			अगर (!c)
				जाओ out;
			अगर (l)
				l->next = c;
			अन्यथा
				p->ocontexts[i] = c;
			l = c;

			चयन (i) अणु
			हाल OCON_ISID:
				rc = next_entry(buf, fp, माप(u32));
				अगर (rc)
					जाओ out;

				c->sid[0] = le32_to_cpu(buf[0]);
				rc = context_पढ़ो_and_validate(&c->context[0], p, fp);
				अगर (rc)
					जाओ out;
				अवरोध;
			हाल OCON_FS:
			हाल OCON_NETIF:
				rc = next_entry(buf, fp, माप(u32));
				अगर (rc)
					जाओ out;
				len = le32_to_cpu(buf[0]);

				rc = str_पढ़ो(&c->u.name, GFP_KERNEL, fp, len);
				अगर (rc)
					जाओ out;

				rc = context_पढ़ो_and_validate(&c->context[0], p, fp);
				अगर (rc)
					जाओ out;
				rc = context_पढ़ो_and_validate(&c->context[1], p, fp);
				अगर (rc)
					जाओ out;
				अवरोध;
			हाल OCON_PORT:
				rc = next_entry(buf, fp, माप(u32)*3);
				अगर (rc)
					जाओ out;
				c->u.port.protocol = le32_to_cpu(buf[0]);
				c->u.port.low_port = le32_to_cpu(buf[1]);
				c->u.port.high_port = le32_to_cpu(buf[2]);
				rc = context_पढ़ो_and_validate(&c->context[0], p, fp);
				अगर (rc)
					जाओ out;
				अवरोध;
			हाल OCON_NODE:
				rc = next_entry(nodebuf, fp, माप(u32) * 2);
				अगर (rc)
					जाओ out;
				c->u.node.addr = nodebuf[0]; /* network order */
				c->u.node.mask = nodebuf[1]; /* network order */
				rc = context_पढ़ो_and_validate(&c->context[0], p, fp);
				अगर (rc)
					जाओ out;
				अवरोध;
			हाल OCON_FSUSE:
				rc = next_entry(buf, fp, माप(u32)*2);
				अगर (rc)
					जाओ out;

				rc = -EINVAL;
				c->v.behavior = le32_to_cpu(buf[0]);
				/* Determined at runसमय, not in policy DB. */
				अगर (c->v.behavior == SECURITY_FS_USE_MNTPOINT)
					जाओ out;
				अगर (c->v.behavior > SECURITY_FS_USE_MAX)
					जाओ out;

				len = le32_to_cpu(buf[1]);
				rc = str_पढ़ो(&c->u.name, GFP_KERNEL, fp, len);
				अगर (rc)
					जाओ out;

				rc = context_पढ़ो_and_validate(&c->context[0], p, fp);
				अगर (rc)
					जाओ out;
				अवरोध;
			हाल OCON_NODE6: अणु
				पूर्णांक k;

				rc = next_entry(nodebuf, fp, माप(u32) * 8);
				अगर (rc)
					जाओ out;
				क्रम (k = 0; k < 4; k++)
					c->u.node6.addr[k] = nodebuf[k];
				क्रम (k = 0; k < 4; k++)
					c->u.node6.mask[k] = nodebuf[k+4];
				rc = context_पढ़ो_and_validate(&c->context[0], p, fp);
				अगर (rc)
					जाओ out;
				अवरोध;
			पूर्ण
			हाल OCON_IBPKEY: अणु
				u32 pkey_lo, pkey_hi;

				rc = next_entry(prefixbuf, fp, माप(u64));
				अगर (rc)
					जाओ out;

				/* we need to have subnet_prefix in CPU order */
				c->u.ibpkey.subnet_prefix = be64_to_cpu(prefixbuf[0]);

				rc = next_entry(buf, fp, माप(u32) * 2);
				अगर (rc)
					जाओ out;

				pkey_lo = le32_to_cpu(buf[0]);
				pkey_hi = le32_to_cpu(buf[1]);

				अगर (pkey_lo > U16_MAX || pkey_hi > U16_MAX) अणु
					rc = -EINVAL;
					जाओ out;
				पूर्ण

				c->u.ibpkey.low_pkey  = pkey_lo;
				c->u.ibpkey.high_pkey = pkey_hi;

				rc = context_पढ़ो_and_validate(&c->context[0],
							       p,
							       fp);
				अगर (rc)
					जाओ out;
				अवरोध;
			पूर्ण
			हाल OCON_IBENDPORT: अणु
				u32 port;

				rc = next_entry(buf, fp, माप(u32) * 2);
				अगर (rc)
					जाओ out;
				len = le32_to_cpu(buf[0]);

				rc = str_पढ़ो(&c->u.ibendport.dev_name, GFP_KERNEL, fp, len);
				अगर (rc)
					जाओ out;

				port = le32_to_cpu(buf[1]);
				अगर (port > U8_MAX || port == 0) अणु
					rc = -EINVAL;
					जाओ out;
				पूर्ण

				c->u.ibendport.port = port;

				rc = context_पढ़ो_and_validate(&c->context[0],
							       p,
							       fp);
				अगर (rc)
					जाओ out;
				अवरोध;
			पूर्ण /* end हाल */
			पूर्ण /* end चयन */
		पूर्ण
	पूर्ण
	rc = 0;
out:
	वापस rc;
पूर्ण

/*
 * Read the configuration data from a policy database binary
 * representation file पूर्णांकo a policy database काष्ठाure.
 */
पूर्णांक policydb_पढ़ो(काष्ठा policydb *p, व्योम *fp)
अणु
	काष्ठा role_allow *ra, *lra;
	काष्ठा role_trans_key *rtk = शून्य;
	काष्ठा role_trans_datum *rtd = शून्य;
	पूर्णांक i, j, rc;
	__le32 buf[4];
	u32 len, nprim, nel, perm;

	अक्षर *policydb_str;
	काष्ठा policydb_compat_info *info;

	policydb_init(p);

	/* Read the magic number and string length. */
	rc = next_entry(buf, fp, माप(u32) * 2);
	अगर (rc)
		जाओ bad;

	rc = -EINVAL;
	अगर (le32_to_cpu(buf[0]) != POLICYDB_MAGIC) अणु
		pr_err("SELinux:  policydb magic number 0x%x does "
		       "not match expected magic number 0x%x\n",
		       le32_to_cpu(buf[0]), POLICYDB_MAGIC);
		जाओ bad;
	पूर्ण

	rc = -EINVAL;
	len = le32_to_cpu(buf[1]);
	अगर (len != म_माप(POLICYDB_STRING)) अणु
		pr_err("SELinux:  policydb string length %d does not "
		       "match expected length %zu\n",
		       len, म_माप(POLICYDB_STRING));
		जाओ bad;
	पूर्ण

	rc = -ENOMEM;
	policydb_str = kदो_स्मृति(len + 1, GFP_KERNEL);
	अगर (!policydb_str) अणु
		pr_err("SELinux:  unable to allocate memory for policydb "
		       "string of length %d\n", len);
		जाओ bad;
	पूर्ण

	rc = next_entry(policydb_str, fp, len);
	अगर (rc) अणु
		pr_err("SELinux:  truncated policydb string identifier\n");
		kमुक्त(policydb_str);
		जाओ bad;
	पूर्ण

	rc = -EINVAL;
	policydb_str[len] = '\0';
	अगर (म_भेद(policydb_str, POLICYDB_STRING)) अणु
		pr_err("SELinux:  policydb string %s does not match "
		       "my string %s\n", policydb_str, POLICYDB_STRING);
		kमुक्त(policydb_str);
		जाओ bad;
	पूर्ण
	/* Done with policydb_str. */
	kमुक्त(policydb_str);
	policydb_str = शून्य;

	/* Read the version and table sizes. */
	rc = next_entry(buf, fp, माप(u32)*4);
	अगर (rc)
		जाओ bad;

	rc = -EINVAL;
	p->policyvers = le32_to_cpu(buf[0]);
	अगर (p->policyvers < POLICYDB_VERSION_MIN ||
	    p->policyvers > POLICYDB_VERSION_MAX) अणु
		pr_err("SELinux:  policydb version %d does not match "
		       "my version range %d-%d\n",
		       le32_to_cpu(buf[0]), POLICYDB_VERSION_MIN, POLICYDB_VERSION_MAX);
		जाओ bad;
	पूर्ण

	अगर ((le32_to_cpu(buf[1]) & POLICYDB_CONFIG_MLS)) अणु
		p->mls_enabled = 1;

		rc = -EINVAL;
		अगर (p->policyvers < POLICYDB_VERSION_MLS) अणु
			pr_err("SELinux: security policydb version %d "
				"(MLS) not backwards compatible\n",
				p->policyvers);
			जाओ bad;
		पूर्ण
	पूर्ण
	p->reject_unknown = !!(le32_to_cpu(buf[1]) & REJECT_UNKNOWN);
	p->allow_unknown = !!(le32_to_cpu(buf[1]) & ALLOW_UNKNOWN);

	अगर (p->policyvers >= POLICYDB_VERSION_POLCAP) अणु
		rc = ebiपंचांगap_पढ़ो(&p->policycaps, fp);
		अगर (rc)
			जाओ bad;
	पूर्ण

	अगर (p->policyvers >= POLICYDB_VERSION_PERMISSIVE) अणु
		rc = ebiपंचांगap_पढ़ो(&p->permissive_map, fp);
		अगर (rc)
			जाओ bad;
	पूर्ण

	rc = -EINVAL;
	info = policydb_lookup_compat(p->policyvers);
	अगर (!info) अणु
		pr_err("SELinux:  unable to find policy compat info "
		       "for version %d\n", p->policyvers);
		जाओ bad;
	पूर्ण

	rc = -EINVAL;
	अगर (le32_to_cpu(buf[2]) != info->sym_num ||
		le32_to_cpu(buf[3]) != info->ocon_num) अणु
		pr_err("SELinux:  policydb table sizes (%d,%d) do "
		       "not match mine (%d,%d)\n", le32_to_cpu(buf[2]),
			le32_to_cpu(buf[3]),
		       info->sym_num, info->ocon_num);
		जाओ bad;
	पूर्ण

	क्रम (i = 0; i < info->sym_num; i++) अणु
		rc = next_entry(buf, fp, माप(u32)*2);
		अगर (rc)
			जाओ bad;
		nprim = le32_to_cpu(buf[0]);
		nel = le32_to_cpu(buf[1]);

		rc = symtab_init(&p->symtab[i], nel);
		अगर (rc)
			जाओ out;

		अगर (i == SYM_ROLES) अणु
			rc = roles_init(p);
			अगर (rc)
				जाओ out;
		पूर्ण

		क्रम (j = 0; j < nel; j++) अणु
			rc = पढ़ो_f[i](p, &p->symtab[i], fp);
			अगर (rc)
				जाओ bad;
		पूर्ण

		p->symtab[i].nprim = nprim;
	पूर्ण

	rc = -EINVAL;
	p->process_class = string_to_security_class(p, "process");
	अगर (!p->process_class) अणु
		pr_err("SELinux: process class is required, not defined in policy\n");
		जाओ bad;
	पूर्ण

	rc = avtab_पढ़ो(&p->te_avtab, fp, p);
	अगर (rc)
		जाओ bad;

	अगर (p->policyvers >= POLICYDB_VERSION_BOOL) अणु
		rc = cond_पढ़ो_list(p, fp);
		अगर (rc)
			जाओ bad;
	पूर्ण

	rc = next_entry(buf, fp, माप(u32));
	अगर (rc)
		जाओ bad;
	nel = le32_to_cpu(buf[0]);

	rc = hashtab_init(&p->role_tr, nel);
	अगर (rc)
		जाओ bad;
	क्रम (i = 0; i < nel; i++) अणु
		rc = -ENOMEM;
		rtk = kदो_स्मृति(माप(*rtk), GFP_KERNEL);
		अगर (!rtk)
			जाओ bad;

		rc = -ENOMEM;
		rtd = kदो_स्मृति(माप(*rtd), GFP_KERNEL);
		अगर (!rtd)
			जाओ bad;

		rc = next_entry(buf, fp, माप(u32)*3);
		अगर (rc)
			जाओ bad;

		rc = -EINVAL;
		rtk->role = le32_to_cpu(buf[0]);
		rtk->type = le32_to_cpu(buf[1]);
		rtd->new_role = le32_to_cpu(buf[2]);
		अगर (p->policyvers >= POLICYDB_VERSION_ROLETRANS) अणु
			rc = next_entry(buf, fp, माप(u32));
			अगर (rc)
				जाओ bad;
			rtk->tclass = le32_to_cpu(buf[0]);
		पूर्ण अन्यथा
			rtk->tclass = p->process_class;

		rc = -EINVAL;
		अगर (!policydb_role_isvalid(p, rtk->role) ||
		    !policydb_type_isvalid(p, rtk->type) ||
		    !policydb_class_isvalid(p, rtk->tclass) ||
		    !policydb_role_isvalid(p, rtd->new_role))
			जाओ bad;

		rc = hashtab_insert(&p->role_tr, rtk, rtd, roletr_key_params);
		अगर (rc)
			जाओ bad;

		rtk = शून्य;
		rtd = शून्य;
	पूर्ण

	rc = next_entry(buf, fp, माप(u32));
	अगर (rc)
		जाओ bad;
	nel = le32_to_cpu(buf[0]);
	lra = शून्य;
	क्रम (i = 0; i < nel; i++) अणु
		rc = -ENOMEM;
		ra = kzalloc(माप(*ra), GFP_KERNEL);
		अगर (!ra)
			जाओ bad;
		अगर (lra)
			lra->next = ra;
		अन्यथा
			p->role_allow = ra;
		rc = next_entry(buf, fp, माप(u32)*2);
		अगर (rc)
			जाओ bad;

		rc = -EINVAL;
		ra->role = le32_to_cpu(buf[0]);
		ra->new_role = le32_to_cpu(buf[1]);
		अगर (!policydb_role_isvalid(p, ra->role) ||
		    !policydb_role_isvalid(p, ra->new_role))
			जाओ bad;
		lra = ra;
	पूर्ण

	rc = filename_trans_पढ़ो(p, fp);
	अगर (rc)
		जाओ bad;

	rc = policydb_index(p);
	अगर (rc)
		जाओ bad;

	rc = -EINVAL;
	perm = string_to_av_perm(p, p->process_class, "transition");
	अगर (!perm) अणु
		pr_err("SELinux: process transition permission is required, not defined in policy\n");
		जाओ bad;
	पूर्ण
	p->process_trans_perms = perm;
	perm = string_to_av_perm(p, p->process_class, "dyntransition");
	अगर (!perm) अणु
		pr_err("SELinux: process dyntransition permission is required, not defined in policy\n");
		जाओ bad;
	पूर्ण
	p->process_trans_perms |= perm;

	rc = ocontext_पढ़ो(p, info, fp);
	अगर (rc)
		जाओ bad;

	rc = genfs_पढ़ो(p, fp);
	अगर (rc)
		जाओ bad;

	rc = range_पढ़ो(p, fp);
	अगर (rc)
		जाओ bad;

	rc = -ENOMEM;
	p->type_attr_map_array = kvसुस्मृति(p->p_types.nprim,
					  माप(*p->type_attr_map_array),
					  GFP_KERNEL);
	अगर (!p->type_attr_map_array)
		जाओ bad;

	/* just in हाल ebiपंचांगap_init() becomes more than just a स_रखो(0): */
	क्रम (i = 0; i < p->p_types.nprim; i++)
		ebiपंचांगap_init(&p->type_attr_map_array[i]);

	क्रम (i = 0; i < p->p_types.nprim; i++) अणु
		काष्ठा ebiपंचांगap *e = &p->type_attr_map_array[i];

		अगर (p->policyvers >= POLICYDB_VERSION_AVTAB) अणु
			rc = ebiपंचांगap_पढ़ो(e, fp);
			अगर (rc)
				जाओ bad;
		पूर्ण
		/* add the type itself as the degenerate हाल */
		rc = ebiपंचांगap_set_bit(e, i, 1);
		अगर (rc)
			जाओ bad;
	पूर्ण

	rc = policydb_bounds_sanity_check(p);
	अगर (rc)
		जाओ bad;

	rc = 0;
out:
	वापस rc;
bad:
	kमुक्त(rtk);
	kमुक्त(rtd);
	policydb_destroy(p);
	जाओ out;
पूर्ण

/*
 * Write a MLS level काष्ठाure to a policydb binary
 * representation file.
 */
अटल पूर्णांक mls_ग_लिखो_level(काष्ठा mls_level *l, व्योम *fp)
अणु
	__le32 buf[1];
	पूर्णांक rc;

	buf[0] = cpu_to_le32(l->sens);
	rc = put_entry(buf, माप(u32), 1, fp);
	अगर (rc)
		वापस rc;

	rc = ebiपंचांगap_ग_लिखो(&l->cat, fp);
	अगर (rc)
		वापस rc;

	वापस 0;
पूर्ण

/*
 * Write a MLS range काष्ठाure to a policydb binary
 * representation file.
 */
अटल पूर्णांक mls_ग_लिखो_range_helper(काष्ठा mls_range *r, व्योम *fp)
अणु
	__le32 buf[3];
	माप_प्रकार items;
	पूर्णांक rc, eq;

	eq = mls_level_eq(&r->level[1], &r->level[0]);

	अगर (eq)
		items = 2;
	अन्यथा
		items = 3;
	buf[0] = cpu_to_le32(items-1);
	buf[1] = cpu_to_le32(r->level[0].sens);
	अगर (!eq)
		buf[2] = cpu_to_le32(r->level[1].sens);

	BUG_ON(items > ARRAY_SIZE(buf));

	rc = put_entry(buf, माप(u32), items, fp);
	अगर (rc)
		वापस rc;

	rc = ebiपंचांगap_ग_लिखो(&r->level[0].cat, fp);
	अगर (rc)
		वापस rc;
	अगर (!eq) अणु
		rc = ebiपंचांगap_ग_लिखो(&r->level[1].cat, fp);
		अगर (rc)
			वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sens_ग_लिखो(व्योम *vkey, व्योम *datum, व्योम *ptr)
अणु
	अक्षर *key = vkey;
	काष्ठा level_datum *levdatum = datum;
	काष्ठा policy_data *pd = ptr;
	व्योम *fp = pd->fp;
	__le32 buf[2];
	माप_प्रकार len;
	पूर्णांक rc;

	len = म_माप(key);
	buf[0] = cpu_to_le32(len);
	buf[1] = cpu_to_le32(levdatum->isalias);
	rc = put_entry(buf, माप(u32), 2, fp);
	अगर (rc)
		वापस rc;

	rc = put_entry(key, 1, len, fp);
	अगर (rc)
		वापस rc;

	rc = mls_ग_लिखो_level(levdatum->level, fp);
	अगर (rc)
		वापस rc;

	वापस 0;
पूर्ण

अटल पूर्णांक cat_ग_लिखो(व्योम *vkey, व्योम *datum, व्योम *ptr)
अणु
	अक्षर *key = vkey;
	काष्ठा cat_datum *catdatum = datum;
	काष्ठा policy_data *pd = ptr;
	व्योम *fp = pd->fp;
	__le32 buf[3];
	माप_प्रकार len;
	पूर्णांक rc;

	len = म_माप(key);
	buf[0] = cpu_to_le32(len);
	buf[1] = cpu_to_le32(catdatum->value);
	buf[2] = cpu_to_le32(catdatum->isalias);
	rc = put_entry(buf, माप(u32), 3, fp);
	अगर (rc)
		वापस rc;

	rc = put_entry(key, 1, len, fp);
	अगर (rc)
		वापस rc;

	वापस 0;
पूर्ण

अटल पूर्णांक role_trans_ग_लिखो_one(व्योम *key, व्योम *datum, व्योम *ptr)
अणु
	काष्ठा role_trans_key *rtk = key;
	काष्ठा role_trans_datum *rtd = datum;
	काष्ठा policy_data *pd = ptr;
	व्योम *fp = pd->fp;
	काष्ठा policydb *p = pd->p;
	__le32 buf[3];
	पूर्णांक rc;

	buf[0] = cpu_to_le32(rtk->role);
	buf[1] = cpu_to_le32(rtk->type);
	buf[2] = cpu_to_le32(rtd->new_role);
	rc = put_entry(buf, माप(u32), 3, fp);
	अगर (rc)
		वापस rc;
	अगर (p->policyvers >= POLICYDB_VERSION_ROLETRANS) अणु
		buf[0] = cpu_to_le32(rtk->tclass);
		rc = put_entry(buf, माप(u32), 1, fp);
		अगर (rc)
			वापस rc;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक role_trans_ग_लिखो(काष्ठा policydb *p, व्योम *fp)
अणु
	काष्ठा policy_data pd = अणु .p = p, .fp = fp पूर्ण;
	__le32 buf[1];
	पूर्णांक rc;

	buf[0] = cpu_to_le32(p->role_tr.nel);
	rc = put_entry(buf, माप(u32), 1, fp);
	अगर (rc)
		वापस rc;

	वापस hashtab_map(&p->role_tr, role_trans_ग_लिखो_one, &pd);
पूर्ण

अटल पूर्णांक role_allow_ग_लिखो(काष्ठा role_allow *r, व्योम *fp)
अणु
	काष्ठा role_allow *ra;
	__le32 buf[2];
	माप_प्रकार nel;
	पूर्णांक rc;

	nel = 0;
	क्रम (ra = r; ra; ra = ra->next)
		nel++;
	buf[0] = cpu_to_le32(nel);
	rc = put_entry(buf, माप(u32), 1, fp);
	अगर (rc)
		वापस rc;
	क्रम (ra = r; ra; ra = ra->next) अणु
		buf[0] = cpu_to_le32(ra->role);
		buf[1] = cpu_to_le32(ra->new_role);
		rc = put_entry(buf, माप(u32), 2, fp);
		अगर (rc)
			वापस rc;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Write a security context काष्ठाure
 * to a policydb binary representation file.
 */
अटल पूर्णांक context_ग_लिखो(काष्ठा policydb *p, काष्ठा context *c,
			 व्योम *fp)
अणु
	पूर्णांक rc;
	__le32 buf[3];

	buf[0] = cpu_to_le32(c->user);
	buf[1] = cpu_to_le32(c->role);
	buf[2] = cpu_to_le32(c->type);

	rc = put_entry(buf, माप(u32), 3, fp);
	अगर (rc)
		वापस rc;

	rc = mls_ग_लिखो_range_helper(&c->range, fp);
	अगर (rc)
		वापस rc;

	वापस 0;
पूर्ण

/*
 * The following *_ग_लिखो functions are used to
 * ग_लिखो the symbol data to a policy database
 * binary representation file.
 */

अटल पूर्णांक perm_ग_लिखो(व्योम *vkey, व्योम *datum, व्योम *fp)
अणु
	अक्षर *key = vkey;
	काष्ठा perm_datum *perdatum = datum;
	__le32 buf[2];
	माप_प्रकार len;
	पूर्णांक rc;

	len = म_माप(key);
	buf[0] = cpu_to_le32(len);
	buf[1] = cpu_to_le32(perdatum->value);
	rc = put_entry(buf, माप(u32), 2, fp);
	अगर (rc)
		वापस rc;

	rc = put_entry(key, 1, len, fp);
	अगर (rc)
		वापस rc;

	वापस 0;
पूर्ण

अटल पूर्णांक common_ग_लिखो(व्योम *vkey, व्योम *datum, व्योम *ptr)
अणु
	अक्षर *key = vkey;
	काष्ठा common_datum *comdatum = datum;
	काष्ठा policy_data *pd = ptr;
	व्योम *fp = pd->fp;
	__le32 buf[4];
	माप_प्रकार len;
	पूर्णांक rc;

	len = म_माप(key);
	buf[0] = cpu_to_le32(len);
	buf[1] = cpu_to_le32(comdatum->value);
	buf[2] = cpu_to_le32(comdatum->permissions.nprim);
	buf[3] = cpu_to_le32(comdatum->permissions.table.nel);
	rc = put_entry(buf, माप(u32), 4, fp);
	अगर (rc)
		वापस rc;

	rc = put_entry(key, 1, len, fp);
	अगर (rc)
		वापस rc;

	rc = hashtab_map(&comdatum->permissions.table, perm_ग_लिखो, fp);
	अगर (rc)
		वापस rc;

	वापस 0;
पूर्ण

अटल पूर्णांक type_set_ग_लिखो(काष्ठा type_set *t, व्योम *fp)
अणु
	पूर्णांक rc;
	__le32 buf[1];

	अगर (ebiपंचांगap_ग_लिखो(&t->types, fp))
		वापस -EINVAL;
	अगर (ebiपंचांगap_ग_लिखो(&t->negset, fp))
		वापस -EINVAL;

	buf[0] = cpu_to_le32(t->flags);
	rc = put_entry(buf, माप(u32), 1, fp);
	अगर (rc)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक ग_लिखो_cons_helper(काष्ठा policydb *p, काष्ठा स्थिरraपूर्णांक_node *node,
			     व्योम *fp)
अणु
	काष्ठा स्थिरraपूर्णांक_node *c;
	काष्ठा स्थिरraपूर्णांक_expr *e;
	__le32 buf[3];
	u32 nel;
	पूर्णांक rc;

	क्रम (c = node; c; c = c->next) अणु
		nel = 0;
		क्रम (e = c->expr; e; e = e->next)
			nel++;
		buf[0] = cpu_to_le32(c->permissions);
		buf[1] = cpu_to_le32(nel);
		rc = put_entry(buf, माप(u32), 2, fp);
		अगर (rc)
			वापस rc;
		क्रम (e = c->expr; e; e = e->next) अणु
			buf[0] = cpu_to_le32(e->expr_type);
			buf[1] = cpu_to_le32(e->attr);
			buf[2] = cpu_to_le32(e->op);
			rc = put_entry(buf, माप(u32), 3, fp);
			अगर (rc)
				वापस rc;

			चयन (e->expr_type) अणु
			हाल CEXPR_NAMES:
				rc = ebiपंचांगap_ग_लिखो(&e->names, fp);
				अगर (rc)
					वापस rc;
				अगर (p->policyvers >=
					POLICYDB_VERSION_CONSTRAINT_NAMES) अणु
					rc = type_set_ग_लिखो(e->type_names, fp);
					अगर (rc)
						वापस rc;
				पूर्ण
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक class_ग_लिखो(व्योम *vkey, व्योम *datum, व्योम *ptr)
अणु
	अक्षर *key = vkey;
	काष्ठा class_datum *cladatum = datum;
	काष्ठा policy_data *pd = ptr;
	व्योम *fp = pd->fp;
	काष्ठा policydb *p = pd->p;
	काष्ठा स्थिरraपूर्णांक_node *c;
	__le32 buf[6];
	u32 ncons;
	माप_प्रकार len, len2;
	पूर्णांक rc;

	len = म_माप(key);
	अगर (cladatum->comkey)
		len2 = म_माप(cladatum->comkey);
	अन्यथा
		len2 = 0;

	ncons = 0;
	क्रम (c = cladatum->स्थिरraपूर्णांकs; c; c = c->next)
		ncons++;

	buf[0] = cpu_to_le32(len);
	buf[1] = cpu_to_le32(len2);
	buf[2] = cpu_to_le32(cladatum->value);
	buf[3] = cpu_to_le32(cladatum->permissions.nprim);
	buf[4] = cpu_to_le32(cladatum->permissions.table.nel);
	buf[5] = cpu_to_le32(ncons);
	rc = put_entry(buf, माप(u32), 6, fp);
	अगर (rc)
		वापस rc;

	rc = put_entry(key, 1, len, fp);
	अगर (rc)
		वापस rc;

	अगर (cladatum->comkey) अणु
		rc = put_entry(cladatum->comkey, 1, len2, fp);
		अगर (rc)
			वापस rc;
	पूर्ण

	rc = hashtab_map(&cladatum->permissions.table, perm_ग_लिखो, fp);
	अगर (rc)
		वापस rc;

	rc = ग_लिखो_cons_helper(p, cladatum->स्थिरraपूर्णांकs, fp);
	अगर (rc)
		वापस rc;

	/* ग_लिखो out the validatetrans rule */
	ncons = 0;
	क्रम (c = cladatum->validatetrans; c; c = c->next)
		ncons++;

	buf[0] = cpu_to_le32(ncons);
	rc = put_entry(buf, माप(u32), 1, fp);
	अगर (rc)
		वापस rc;

	rc = ग_लिखो_cons_helper(p, cladatum->validatetrans, fp);
	अगर (rc)
		वापस rc;

	अगर (p->policyvers >= POLICYDB_VERSION_NEW_OBJECT_DEFAULTS) अणु
		buf[0] = cpu_to_le32(cladatum->शेष_user);
		buf[1] = cpu_to_le32(cladatum->शेष_role);
		buf[2] = cpu_to_le32(cladatum->शेष_range);

		rc = put_entry(buf, माप(uपूर्णांक32_t), 3, fp);
		अगर (rc)
			वापस rc;
	पूर्ण

	अगर (p->policyvers >= POLICYDB_VERSION_DEFAULT_TYPE) अणु
		buf[0] = cpu_to_le32(cladatum->शेष_type);
		rc = put_entry(buf, माप(uपूर्णांक32_t), 1, fp);
		अगर (rc)
			वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक role_ग_लिखो(व्योम *vkey, व्योम *datum, व्योम *ptr)
अणु
	अक्षर *key = vkey;
	काष्ठा role_datum *role = datum;
	काष्ठा policy_data *pd = ptr;
	व्योम *fp = pd->fp;
	काष्ठा policydb *p = pd->p;
	__le32 buf[3];
	माप_प्रकार items, len;
	पूर्णांक rc;

	len = म_माप(key);
	items = 0;
	buf[items++] = cpu_to_le32(len);
	buf[items++] = cpu_to_le32(role->value);
	अगर (p->policyvers >= POLICYDB_VERSION_BOUNDARY)
		buf[items++] = cpu_to_le32(role->bounds);

	BUG_ON(items > ARRAY_SIZE(buf));

	rc = put_entry(buf, माप(u32), items, fp);
	अगर (rc)
		वापस rc;

	rc = put_entry(key, 1, len, fp);
	अगर (rc)
		वापस rc;

	rc = ebiपंचांगap_ग_लिखो(&role->करोminates, fp);
	अगर (rc)
		वापस rc;

	rc = ebiपंचांगap_ग_लिखो(&role->types, fp);
	अगर (rc)
		वापस rc;

	वापस 0;
पूर्ण

अटल पूर्णांक type_ग_लिखो(व्योम *vkey, व्योम *datum, व्योम *ptr)
अणु
	अक्षर *key = vkey;
	काष्ठा type_datum *typdatum = datum;
	काष्ठा policy_data *pd = ptr;
	काष्ठा policydb *p = pd->p;
	व्योम *fp = pd->fp;
	__le32 buf[4];
	पूर्णांक rc;
	माप_प्रकार items, len;

	len = म_माप(key);
	items = 0;
	buf[items++] = cpu_to_le32(len);
	buf[items++] = cpu_to_le32(typdatum->value);
	अगर (p->policyvers >= POLICYDB_VERSION_BOUNDARY) अणु
		u32 properties = 0;

		अगर (typdatum->primary)
			properties |= TYPEDATUM_PROPERTY_PRIMARY;

		अगर (typdatum->attribute)
			properties |= TYPEDATUM_PROPERTY_ATTRIBUTE;

		buf[items++] = cpu_to_le32(properties);
		buf[items++] = cpu_to_le32(typdatum->bounds);
	पूर्ण अन्यथा अणु
		buf[items++] = cpu_to_le32(typdatum->primary);
	पूर्ण
	BUG_ON(items > ARRAY_SIZE(buf));
	rc = put_entry(buf, माप(u32), items, fp);
	अगर (rc)
		वापस rc;

	rc = put_entry(key, 1, len, fp);
	अगर (rc)
		वापस rc;

	वापस 0;
पूर्ण

अटल पूर्णांक user_ग_लिखो(व्योम *vkey, व्योम *datum, व्योम *ptr)
अणु
	अक्षर *key = vkey;
	काष्ठा user_datum *usrdatum = datum;
	काष्ठा policy_data *pd = ptr;
	काष्ठा policydb *p = pd->p;
	व्योम *fp = pd->fp;
	__le32 buf[3];
	माप_प्रकार items, len;
	पूर्णांक rc;

	len = म_माप(key);
	items = 0;
	buf[items++] = cpu_to_le32(len);
	buf[items++] = cpu_to_le32(usrdatum->value);
	अगर (p->policyvers >= POLICYDB_VERSION_BOUNDARY)
		buf[items++] = cpu_to_le32(usrdatum->bounds);
	BUG_ON(items > ARRAY_SIZE(buf));
	rc = put_entry(buf, माप(u32), items, fp);
	अगर (rc)
		वापस rc;

	rc = put_entry(key, 1, len, fp);
	अगर (rc)
		वापस rc;

	rc = ebiपंचांगap_ग_लिखो(&usrdatum->roles, fp);
	अगर (rc)
		वापस rc;

	rc = mls_ग_लिखो_range_helper(&usrdatum->range, fp);
	अगर (rc)
		वापस rc;

	rc = mls_ग_लिखो_level(&usrdatum->dfltlevel, fp);
	अगर (rc)
		वापस rc;

	वापस 0;
पूर्ण

अटल पूर्णांक (*ग_लिखो_f[SYM_NUM]) (व्योम *key, व्योम *datum,
				व्योम *datap) =
अणु
	common_ग_लिखो,
	class_ग_लिखो,
	role_ग_लिखो,
	type_ग_लिखो,
	user_ग_लिखो,
	cond_ग_लिखो_bool,
	sens_ग_लिखो,
	cat_ग_लिखो,
पूर्ण;

अटल पूर्णांक ocontext_ग_लिखो(काष्ठा policydb *p, काष्ठा policydb_compat_info *info,
			  व्योम *fp)
अणु
	अचिन्हित पूर्णांक i, j, rc;
	माप_प्रकार nel, len;
	__be64 prefixbuf[1];
	__le32 buf[3];
	u32 nodebuf[8];
	काष्ठा ocontext *c;
	क्रम (i = 0; i < info->ocon_num; i++) अणु
		nel = 0;
		क्रम (c = p->ocontexts[i]; c; c = c->next)
			nel++;
		buf[0] = cpu_to_le32(nel);
		rc = put_entry(buf, माप(u32), 1, fp);
		अगर (rc)
			वापस rc;
		क्रम (c = p->ocontexts[i]; c; c = c->next) अणु
			चयन (i) अणु
			हाल OCON_ISID:
				buf[0] = cpu_to_le32(c->sid[0]);
				rc = put_entry(buf, माप(u32), 1, fp);
				अगर (rc)
					वापस rc;
				rc = context_ग_लिखो(p, &c->context[0], fp);
				अगर (rc)
					वापस rc;
				अवरोध;
			हाल OCON_FS:
			हाल OCON_NETIF:
				len = म_माप(c->u.name);
				buf[0] = cpu_to_le32(len);
				rc = put_entry(buf, माप(u32), 1, fp);
				अगर (rc)
					वापस rc;
				rc = put_entry(c->u.name, 1, len, fp);
				अगर (rc)
					वापस rc;
				rc = context_ग_लिखो(p, &c->context[0], fp);
				अगर (rc)
					वापस rc;
				rc = context_ग_लिखो(p, &c->context[1], fp);
				अगर (rc)
					वापस rc;
				अवरोध;
			हाल OCON_PORT:
				buf[0] = cpu_to_le32(c->u.port.protocol);
				buf[1] = cpu_to_le32(c->u.port.low_port);
				buf[2] = cpu_to_le32(c->u.port.high_port);
				rc = put_entry(buf, माप(u32), 3, fp);
				अगर (rc)
					वापस rc;
				rc = context_ग_लिखो(p, &c->context[0], fp);
				अगर (rc)
					वापस rc;
				अवरोध;
			हाल OCON_NODE:
				nodebuf[0] = c->u.node.addr; /* network order */
				nodebuf[1] = c->u.node.mask; /* network order */
				rc = put_entry(nodebuf, माप(u32), 2, fp);
				अगर (rc)
					वापस rc;
				rc = context_ग_लिखो(p, &c->context[0], fp);
				अगर (rc)
					वापस rc;
				अवरोध;
			हाल OCON_FSUSE:
				buf[0] = cpu_to_le32(c->v.behavior);
				len = म_माप(c->u.name);
				buf[1] = cpu_to_le32(len);
				rc = put_entry(buf, माप(u32), 2, fp);
				अगर (rc)
					वापस rc;
				rc = put_entry(c->u.name, 1, len, fp);
				अगर (rc)
					वापस rc;
				rc = context_ग_लिखो(p, &c->context[0], fp);
				अगर (rc)
					वापस rc;
				अवरोध;
			हाल OCON_NODE6:
				क्रम (j = 0; j < 4; j++)
					nodebuf[j] = c->u.node6.addr[j]; /* network order */
				क्रम (j = 0; j < 4; j++)
					nodebuf[j + 4] = c->u.node6.mask[j]; /* network order */
				rc = put_entry(nodebuf, माप(u32), 8, fp);
				अगर (rc)
					वापस rc;
				rc = context_ग_लिखो(p, &c->context[0], fp);
				अगर (rc)
					वापस rc;
				अवरोध;
			हाल OCON_IBPKEY:
				/* subnet_prefix is in CPU order */
				prefixbuf[0] = cpu_to_be64(c->u.ibpkey.subnet_prefix);

				rc = put_entry(prefixbuf, माप(u64), 1, fp);
				अगर (rc)
					वापस rc;

				buf[0] = cpu_to_le32(c->u.ibpkey.low_pkey);
				buf[1] = cpu_to_le32(c->u.ibpkey.high_pkey);

				rc = put_entry(buf, माप(u32), 2, fp);
				अगर (rc)
					वापस rc;
				rc = context_ग_लिखो(p, &c->context[0], fp);
				अगर (rc)
					वापस rc;
				अवरोध;
			हाल OCON_IBENDPORT:
				len = म_माप(c->u.ibendport.dev_name);
				buf[0] = cpu_to_le32(len);
				buf[1] = cpu_to_le32(c->u.ibendport.port);
				rc = put_entry(buf, माप(u32), 2, fp);
				अगर (rc)
					वापस rc;
				rc = put_entry(c->u.ibendport.dev_name, 1, len, fp);
				अगर (rc)
					वापस rc;
				rc = context_ग_लिखो(p, &c->context[0], fp);
				अगर (rc)
					वापस rc;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक genfs_ग_लिखो(काष्ठा policydb *p, व्योम *fp)
अणु
	काष्ठा genfs *genfs;
	काष्ठा ocontext *c;
	माप_प्रकार len;
	__le32 buf[1];
	पूर्णांक rc;

	len = 0;
	क्रम (genfs = p->genfs; genfs; genfs = genfs->next)
		len++;
	buf[0] = cpu_to_le32(len);
	rc = put_entry(buf, माप(u32), 1, fp);
	अगर (rc)
		वापस rc;
	क्रम (genfs = p->genfs; genfs; genfs = genfs->next) अणु
		len = म_माप(genfs->fstype);
		buf[0] = cpu_to_le32(len);
		rc = put_entry(buf, माप(u32), 1, fp);
		अगर (rc)
			वापस rc;
		rc = put_entry(genfs->fstype, 1, len, fp);
		अगर (rc)
			वापस rc;
		len = 0;
		क्रम (c = genfs->head; c; c = c->next)
			len++;
		buf[0] = cpu_to_le32(len);
		rc = put_entry(buf, माप(u32), 1, fp);
		अगर (rc)
			वापस rc;
		क्रम (c = genfs->head; c; c = c->next) अणु
			len = म_माप(c->u.name);
			buf[0] = cpu_to_le32(len);
			rc = put_entry(buf, माप(u32), 1, fp);
			अगर (rc)
				वापस rc;
			rc = put_entry(c->u.name, 1, len, fp);
			अगर (rc)
				वापस rc;
			buf[0] = cpu_to_le32(c->v.sclass);
			rc = put_entry(buf, माप(u32), 1, fp);
			अगर (rc)
				वापस rc;
			rc = context_ग_लिखो(p, &c->context[0], fp);
			अगर (rc)
				वापस rc;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक range_ग_लिखो_helper(व्योम *key, व्योम *data, व्योम *ptr)
अणु
	__le32 buf[2];
	काष्ठा range_trans *rt = key;
	काष्ठा mls_range *r = data;
	काष्ठा policy_data *pd = ptr;
	व्योम *fp = pd->fp;
	काष्ठा policydb *p = pd->p;
	पूर्णांक rc;

	buf[0] = cpu_to_le32(rt->source_type);
	buf[1] = cpu_to_le32(rt->target_type);
	rc = put_entry(buf, माप(u32), 2, fp);
	अगर (rc)
		वापस rc;
	अगर (p->policyvers >= POLICYDB_VERSION_RANGETRANS) अणु
		buf[0] = cpu_to_le32(rt->target_class);
		rc = put_entry(buf, माप(u32), 1, fp);
		अगर (rc)
			वापस rc;
	पूर्ण
	rc = mls_ग_लिखो_range_helper(r, fp);
	अगर (rc)
		वापस rc;

	वापस 0;
पूर्ण

अटल पूर्णांक range_ग_लिखो(काष्ठा policydb *p, व्योम *fp)
अणु
	__le32 buf[1];
	पूर्णांक rc;
	काष्ठा policy_data pd;

	pd.p = p;
	pd.fp = fp;

	buf[0] = cpu_to_le32(p->range_tr.nel);
	rc = put_entry(buf, माप(u32), 1, fp);
	अगर (rc)
		वापस rc;

	/* actually ग_लिखो all of the entries */
	rc = hashtab_map(&p->range_tr, range_ग_लिखो_helper, &pd);
	अगर (rc)
		वापस rc;

	वापस 0;
पूर्ण

अटल पूर्णांक filename_ग_लिखो_helper_compat(व्योम *key, व्योम *data, व्योम *ptr)
अणु
	काष्ठा filename_trans_key *ft = key;
	काष्ठा filename_trans_datum *datum = data;
	काष्ठा ebiपंचांगap_node *node;
	व्योम *fp = ptr;
	__le32 buf[4];
	पूर्णांक rc;
	u32 bit, len = म_माप(ft->name);

	करो अणु
		ebiपंचांगap_क्रम_each_positive_bit(&datum->stypes, node, bit) अणु
			buf[0] = cpu_to_le32(len);
			rc = put_entry(buf, माप(u32), 1, fp);
			अगर (rc)
				वापस rc;

			rc = put_entry(ft->name, माप(अक्षर), len, fp);
			अगर (rc)
				वापस rc;

			buf[0] = cpu_to_le32(bit + 1);
			buf[1] = cpu_to_le32(ft->ttype);
			buf[2] = cpu_to_le32(ft->tclass);
			buf[3] = cpu_to_le32(datum->otype);

			rc = put_entry(buf, माप(u32), 4, fp);
			अगर (rc)
				वापस rc;
		पूर्ण

		datum = datum->next;
	पूर्ण जबतक (unlikely(datum));

	वापस 0;
पूर्ण

अटल पूर्णांक filename_ग_लिखो_helper(व्योम *key, व्योम *data, व्योम *ptr)
अणु
	काष्ठा filename_trans_key *ft = key;
	काष्ठा filename_trans_datum *datum;
	व्योम *fp = ptr;
	__le32 buf[3];
	पूर्णांक rc;
	u32 ndatum, len = म_माप(ft->name);

	buf[0] = cpu_to_le32(len);
	rc = put_entry(buf, माप(u32), 1, fp);
	अगर (rc)
		वापस rc;

	rc = put_entry(ft->name, माप(अक्षर), len, fp);
	अगर (rc)
		वापस rc;

	ndatum = 0;
	datum = data;
	करो अणु
		ndatum++;
		datum = datum->next;
	पूर्ण जबतक (unlikely(datum));

	buf[0] = cpu_to_le32(ft->ttype);
	buf[1] = cpu_to_le32(ft->tclass);
	buf[2] = cpu_to_le32(ndatum);
	rc = put_entry(buf, माप(u32), 3, fp);
	अगर (rc)
		वापस rc;

	datum = data;
	करो अणु
		rc = ebiपंचांगap_ग_लिखो(&datum->stypes, fp);
		अगर (rc)
			वापस rc;

		buf[0] = cpu_to_le32(datum->otype);
		rc = put_entry(buf, माप(u32), 1, fp);
		अगर (rc)
			वापस rc;

		datum = datum->next;
	पूर्ण जबतक (unlikely(datum));

	वापस 0;
पूर्ण

अटल पूर्णांक filename_trans_ग_लिखो(काष्ठा policydb *p, व्योम *fp)
अणु
	__le32 buf[1];
	पूर्णांक rc;

	अगर (p->policyvers < POLICYDB_VERSION_खाताNAME_TRANS)
		वापस 0;

	अगर (p->policyvers < POLICYDB_VERSION_COMP_FTRANS) अणु
		buf[0] = cpu_to_le32(p->compat_filename_trans_count);
		rc = put_entry(buf, माप(u32), 1, fp);
		अगर (rc)
			वापस rc;

		rc = hashtab_map(&p->filename_trans,
				 filename_ग_लिखो_helper_compat, fp);
	पूर्ण अन्यथा अणु
		buf[0] = cpu_to_le32(p->filename_trans.nel);
		rc = put_entry(buf, माप(u32), 1, fp);
		अगर (rc)
			वापस rc;

		rc = hashtab_map(&p->filename_trans, filename_ग_लिखो_helper, fp);
	पूर्ण
	वापस rc;
पूर्ण

/*
 * Write the configuration data in a policy database
 * काष्ठाure to a policy database binary representation
 * file.
 */
पूर्णांक policydb_ग_लिखो(काष्ठा policydb *p, व्योम *fp)
अणु
	अचिन्हित पूर्णांक i, num_syms;
	पूर्णांक rc;
	__le32 buf[4];
	u32 config;
	माप_प्रकार len;
	काष्ठा policydb_compat_info *info;

	/*
	 * refuse to ग_लिखो policy older than compressed avtab
	 * to simplअगरy the ग_लिखोr.  There are other tests dropped
	 * since we assume this throughout the ग_लिखोr code.  Be
	 * careful अगर you ever try to हटाओ this restriction
	 */
	अगर (p->policyvers < POLICYDB_VERSION_AVTAB) अणु
		pr_err("SELinux: refusing to write policy version %d."
		       "  Because it is less than version %d\n", p->policyvers,
		       POLICYDB_VERSION_AVTAB);
		वापस -EINVAL;
	पूर्ण

	config = 0;
	अगर (p->mls_enabled)
		config |= POLICYDB_CONFIG_MLS;

	अगर (p->reject_unknown)
		config |= REJECT_UNKNOWN;
	अगर (p->allow_unknown)
		config |= ALLOW_UNKNOWN;

	/* Write the magic number and string identअगरiers. */
	buf[0] = cpu_to_le32(POLICYDB_MAGIC);
	len = म_माप(POLICYDB_STRING);
	buf[1] = cpu_to_le32(len);
	rc = put_entry(buf, माप(u32), 2, fp);
	अगर (rc)
		वापस rc;
	rc = put_entry(POLICYDB_STRING, 1, len, fp);
	अगर (rc)
		वापस rc;

	/* Write the version, config, and table sizes. */
	info = policydb_lookup_compat(p->policyvers);
	अगर (!info) अणु
		pr_err("SELinux: compatibility lookup failed for policy "
		    "version %d", p->policyvers);
		वापस -EINVAL;
	पूर्ण

	buf[0] = cpu_to_le32(p->policyvers);
	buf[1] = cpu_to_le32(config);
	buf[2] = cpu_to_le32(info->sym_num);
	buf[3] = cpu_to_le32(info->ocon_num);

	rc = put_entry(buf, माप(u32), 4, fp);
	अगर (rc)
		वापस rc;

	अगर (p->policyvers >= POLICYDB_VERSION_POLCAP) अणु
		rc = ebiपंचांगap_ग_लिखो(&p->policycaps, fp);
		अगर (rc)
			वापस rc;
	पूर्ण

	अगर (p->policyvers >= POLICYDB_VERSION_PERMISSIVE) अणु
		rc = ebiपंचांगap_ग_लिखो(&p->permissive_map, fp);
		अगर (rc)
			वापस rc;
	पूर्ण

	num_syms = info->sym_num;
	क्रम (i = 0; i < num_syms; i++) अणु
		काष्ठा policy_data pd;

		pd.fp = fp;
		pd.p = p;

		buf[0] = cpu_to_le32(p->symtab[i].nprim);
		buf[1] = cpu_to_le32(p->symtab[i].table.nel);

		rc = put_entry(buf, माप(u32), 2, fp);
		अगर (rc)
			वापस rc;
		rc = hashtab_map(&p->symtab[i].table, ग_लिखो_f[i], &pd);
		अगर (rc)
			वापस rc;
	पूर्ण

	rc = avtab_ग_लिखो(p, &p->te_avtab, fp);
	अगर (rc)
		वापस rc;

	rc = cond_ग_लिखो_list(p, fp);
	अगर (rc)
		वापस rc;

	rc = role_trans_ग_लिखो(p, fp);
	अगर (rc)
		वापस rc;

	rc = role_allow_ग_लिखो(p->role_allow, fp);
	अगर (rc)
		वापस rc;

	rc = filename_trans_ग_लिखो(p, fp);
	अगर (rc)
		वापस rc;

	rc = ocontext_ग_लिखो(p, info, fp);
	अगर (rc)
		वापस rc;

	rc = genfs_ग_लिखो(p, fp);
	अगर (rc)
		वापस rc;

	rc = range_ग_लिखो(p, fp);
	अगर (rc)
		वापस rc;

	क्रम (i = 0; i < p->p_types.nprim; i++) अणु
		काष्ठा ebiपंचांगap *e = &p->type_attr_map_array[i];

		rc = ebiपंचांगap_ग_लिखो(e, fp);
		अगर (rc)
			वापस rc;
	पूर्ण

	वापस 0;
पूर्ण
