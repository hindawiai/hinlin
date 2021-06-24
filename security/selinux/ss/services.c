<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Implementation of the security services.
 *
 * Authors : Stephen Smalley, <sds@tycho.nsa.gov>
 *	     James Morris <jmorris@redhat.com>
 *
 * Updated: Trusted Computer Solutions, Inc. <dgoeddel@trustedcs.com>
 *
 *	Support क्रम enhanced MLS infraकाष्ठाure.
 *	Support क्रम context based audit filters.
 *
 * Updated: Frank Mayer <mayerf@tresys.com> and Karl MacMillan <kmacmillan@tresys.com>
 *
 *	Added conditional policy language extensions
 *
 * Updated: Hewlett-Packard <paul@paul-moore.com>
 *
 *      Added support क्रम NetLabel
 *      Added support क्रम the policy capability biपंचांगap
 *
 * Updated: Chad Sellers <csellers@tresys.com>
 *
 *  Added validation of kernel classes and permissions
 *
 * Updated: KaiGai Kohei <kaigai@ak.jp.nec.com>
 *
 *  Added support क्रम bounds करोमुख्य and audit messaged on masked permissions
 *
 * Updated: Guiकरो Trentalancia <guiकरो@trentalancia.com>
 *
 *  Added support क्रम runसमय चयनing of the policy type
 *
 * Copyright (C) 2008, 2009 NEC Corporation
 * Copyright (C) 2006, 2007 Hewlett-Packard Development Company, L.P.
 * Copyright (C) 2004-2006 Trusted Computer Solutions, Inc.
 * Copyright (C) 2003 - 2004, 2006 Tresys Technology, LLC
 * Copyright (C) 2003 Red Hat, Inc., James Morris <jmorris@redhat.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/in.h>
#समावेश <linux/sched.h>
#समावेश <linux/audit.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/lsm_hooks.h>
#समावेश <net/netlabel.h>

#समावेश "flask.h"
#समावेश "avc.h"
#समावेश "avc_ss.h"
#समावेश "security.h"
#समावेश "context.h"
#समावेश "policydb.h"
#समावेश "sidtab.h"
#समावेश "services.h"
#समावेश "conditional.h"
#समावेश "mls.h"
#समावेश "objsec.h"
#समावेश "netlabel.h"
#समावेश "xfrm.h"
#समावेश "ebitmap.h"
#समावेश "audit.h"
#समावेश "policycap_names.h"
#समावेश "ima.h"

काष्ठा convert_context_args अणु
	काष्ठा selinux_state *state;
	काष्ठा policydb *oldp;
	काष्ठा policydb *newp;
पूर्ण;

काष्ठा selinux_policy_convert_data अणु
	काष्ठा convert_context_args args;
	काष्ठा sidtab_convert_params sidtab_params;
पूर्ण;

/* Forward declaration. */
अटल पूर्णांक context_काष्ठा_to_string(काष्ठा policydb *policydb,
				    काष्ठा context *context,
				    अक्षर **scontext,
				    u32 *scontext_len);

अटल पूर्णांक sidtab_entry_to_string(काष्ठा policydb *policydb,
				  काष्ठा sidtab *sidtab,
				  काष्ठा sidtab_entry *entry,
				  अक्षर **scontext,
				  u32 *scontext_len);

अटल व्योम context_काष्ठा_compute_av(काष्ठा policydb *policydb,
				      काष्ठा context *scontext,
				      काष्ठा context *tcontext,
				      u16 tclass,
				      काष्ठा av_decision *avd,
				      काष्ठा extended_perms *xperms);

अटल पूर्णांक selinux_set_mapping(काष्ठा policydb *pol,
			       काष्ठा security_class_mapping *map,
			       काष्ठा selinux_map *out_map)
अणु
	u16 i, j;
	अचिन्हित k;
	bool prपूर्णांक_unknown_handle = false;

	/* Find number of classes in the input mapping */
	अगर (!map)
		वापस -EINVAL;
	i = 0;
	जबतक (map[i].name)
		i++;

	/* Allocate space क्रम the class records, plus one क्रम class zero */
	out_map->mapping = kसुस्मृति(++i, माप(*out_map->mapping), GFP_ATOMIC);
	अगर (!out_map->mapping)
		वापस -ENOMEM;

	/* Store the raw class and permission values */
	j = 0;
	जबतक (map[j].name) अणु
		काष्ठा security_class_mapping *p_in = map + (j++);
		काष्ठा selinux_mapping *p_out = out_map->mapping + j;

		/* An empty class string skips ahead */
		अगर (!म_भेद(p_in->name, "")) अणु
			p_out->num_perms = 0;
			जारी;
		पूर्ण

		p_out->value = string_to_security_class(pol, p_in->name);
		अगर (!p_out->value) अणु
			pr_info("SELinux:  Class %s not defined in policy.\n",
			       p_in->name);
			अगर (pol->reject_unknown)
				जाओ err;
			p_out->num_perms = 0;
			prपूर्णांक_unknown_handle = true;
			जारी;
		पूर्ण

		k = 0;
		जबतक (p_in->perms[k]) अणु
			/* An empty permission string skips ahead */
			अगर (!*p_in->perms[k]) अणु
				k++;
				जारी;
			पूर्ण
			p_out->perms[k] = string_to_av_perm(pol, p_out->value,
							    p_in->perms[k]);
			अगर (!p_out->perms[k]) अणु
				pr_info("SELinux:  Permission %s in class %s not defined in policy.\n",
				       p_in->perms[k], p_in->name);
				अगर (pol->reject_unknown)
					जाओ err;
				prपूर्णांक_unknown_handle = true;
			पूर्ण

			k++;
		पूर्ण
		p_out->num_perms = k;
	पूर्ण

	अगर (prपूर्णांक_unknown_handle)
		pr_info("SELinux: the above unknown classes and permissions will be %s\n",
		       pol->allow_unknown ? "allowed" : "denied");

	out_map->size = i;
	वापस 0;
err:
	kमुक्त(out_map->mapping);
	out_map->mapping = शून्य;
	वापस -EINVAL;
पूर्ण

/*
 * Get real, policy values from mapped values
 */

अटल u16 unmap_class(काष्ठा selinux_map *map, u16 tclass)
अणु
	अगर (tclass < map->size)
		वापस map->mapping[tclass].value;

	वापस tclass;
पूर्ण

/*
 * Get kernel value क्रम class from its policy value
 */
अटल u16 map_class(काष्ठा selinux_map *map, u16 pol_value)
अणु
	u16 i;

	क्रम (i = 1; i < map->size; i++) अणु
		अगर (map->mapping[i].value == pol_value)
			वापस i;
	पूर्ण

	वापस SECCLASS_शून्य;
पूर्ण

अटल व्योम map_decision(काष्ठा selinux_map *map,
			 u16 tclass, काष्ठा av_decision *avd,
			 पूर्णांक allow_unknown)
अणु
	अगर (tclass < map->size) अणु
		काष्ठा selinux_mapping *mapping = &map->mapping[tclass];
		अचिन्हित पूर्णांक i, n = mapping->num_perms;
		u32 result;

		क्रम (i = 0, result = 0; i < n; i++) अणु
			अगर (avd->allowed & mapping->perms[i])
				result |= 1<<i;
			अगर (allow_unknown && !mapping->perms[i])
				result |= 1<<i;
		पूर्ण
		avd->allowed = result;

		क्रम (i = 0, result = 0; i < n; i++)
			अगर (avd->auditallow & mapping->perms[i])
				result |= 1<<i;
		avd->auditallow = result;

		क्रम (i = 0, result = 0; i < n; i++) अणु
			अगर (avd->auditdeny & mapping->perms[i])
				result |= 1<<i;
			अगर (!allow_unknown && !mapping->perms[i])
				result |= 1<<i;
		पूर्ण
		/*
		 * In हाल the kernel has a bug and requests a permission
		 * between num_perms and the maximum permission number, we
		 * should audit that denial
		 */
		क्रम (; i < (माप(u32)*8); i++)
			result |= 1<<i;
		avd->auditdeny = result;
	पूर्ण
पूर्ण

पूर्णांक security_mls_enabled(काष्ठा selinux_state *state)
अणु
	पूर्णांक mls_enabled;
	काष्ठा selinux_policy *policy;

	अगर (!selinux_initialized(state))
		वापस 0;

	rcu_पढ़ो_lock();
	policy = rcu_dereference(state->policy);
	mls_enabled = policy->policydb.mls_enabled;
	rcu_पढ़ो_unlock();
	वापस mls_enabled;
पूर्ण

/*
 * Return the boolean value of a स्थिरraपूर्णांक expression
 * when it is applied to the specअगरied source and target
 * security contexts.
 *
 * xcontext is a special beast...  It is used by the validatetrans rules
 * only.  For these rules, scontext is the context beक्रमe the transition,
 * tcontext is the context after the transition, and xcontext is the context
 * of the process perक्रमming the transition.  All other callers of
 * स्थिरraपूर्णांक_expr_eval should pass in शून्य क्रम xcontext.
 */
अटल पूर्णांक स्थिरraपूर्णांक_expr_eval(काष्ठा policydb *policydb,
				काष्ठा context *scontext,
				काष्ठा context *tcontext,
				काष्ठा context *xcontext,
				काष्ठा स्थिरraपूर्णांक_expr *cexpr)
अणु
	u32 val1, val2;
	काष्ठा context *c;
	काष्ठा role_datum *r1, *r2;
	काष्ठा mls_level *l1, *l2;
	काष्ठा स्थिरraपूर्णांक_expr *e;
	पूर्णांक s[CEXPR_MAXDEPTH];
	पूर्णांक sp = -1;

	क्रम (e = cexpr; e; e = e->next) अणु
		चयन (e->expr_type) अणु
		हाल CEXPR_NOT:
			BUG_ON(sp < 0);
			s[sp] = !s[sp];
			अवरोध;
		हाल CEXPR_AND:
			BUG_ON(sp < 1);
			sp--;
			s[sp] &= s[sp + 1];
			अवरोध;
		हाल CEXPR_OR:
			BUG_ON(sp < 1);
			sp--;
			s[sp] |= s[sp + 1];
			अवरोध;
		हाल CEXPR_ATTR:
			अगर (sp == (CEXPR_MAXDEPTH - 1))
				वापस 0;
			चयन (e->attr) अणु
			हाल CEXPR_USER:
				val1 = scontext->user;
				val2 = tcontext->user;
				अवरोध;
			हाल CEXPR_TYPE:
				val1 = scontext->type;
				val2 = tcontext->type;
				अवरोध;
			हाल CEXPR_ROLE:
				val1 = scontext->role;
				val2 = tcontext->role;
				r1 = policydb->role_val_to_काष्ठा[val1 - 1];
				r2 = policydb->role_val_to_काष्ठा[val2 - 1];
				चयन (e->op) अणु
				हाल CEXPR_DOM:
					s[++sp] = ebiपंचांगap_get_bit(&r1->करोminates,
								  val2 - 1);
					जारी;
				हाल CEXPR_DOMBY:
					s[++sp] = ebiपंचांगap_get_bit(&r2->करोminates,
								  val1 - 1);
					जारी;
				हाल CEXPR_INCOMP:
					s[++sp] = (!ebiपंचांगap_get_bit(&r1->करोminates,
								    val2 - 1) &&
						   !ebiपंचांगap_get_bit(&r2->करोminates,
								    val1 - 1));
					जारी;
				शेष:
					अवरोध;
				पूर्ण
				अवरोध;
			हाल CEXPR_L1L2:
				l1 = &(scontext->range.level[0]);
				l2 = &(tcontext->range.level[0]);
				जाओ mls_ops;
			हाल CEXPR_L1H2:
				l1 = &(scontext->range.level[0]);
				l2 = &(tcontext->range.level[1]);
				जाओ mls_ops;
			हाल CEXPR_H1L2:
				l1 = &(scontext->range.level[1]);
				l2 = &(tcontext->range.level[0]);
				जाओ mls_ops;
			हाल CEXPR_H1H2:
				l1 = &(scontext->range.level[1]);
				l2 = &(tcontext->range.level[1]);
				जाओ mls_ops;
			हाल CEXPR_L1H1:
				l1 = &(scontext->range.level[0]);
				l2 = &(scontext->range.level[1]);
				जाओ mls_ops;
			हाल CEXPR_L2H2:
				l1 = &(tcontext->range.level[0]);
				l2 = &(tcontext->range.level[1]);
				जाओ mls_ops;
mls_ops:
			चयन (e->op) अणु
			हाल CEXPR_EQ:
				s[++sp] = mls_level_eq(l1, l2);
				जारी;
			हाल CEXPR_NEQ:
				s[++sp] = !mls_level_eq(l1, l2);
				जारी;
			हाल CEXPR_DOM:
				s[++sp] = mls_level_करोm(l1, l2);
				जारी;
			हाल CEXPR_DOMBY:
				s[++sp] = mls_level_करोm(l2, l1);
				जारी;
			हाल CEXPR_INCOMP:
				s[++sp] = mls_level_incomp(l2, l1);
				जारी;
			शेष:
				BUG();
				वापस 0;
			पूर्ण
			अवरोध;
			शेष:
				BUG();
				वापस 0;
			पूर्ण

			चयन (e->op) अणु
			हाल CEXPR_EQ:
				s[++sp] = (val1 == val2);
				अवरोध;
			हाल CEXPR_NEQ:
				s[++sp] = (val1 != val2);
				अवरोध;
			शेष:
				BUG();
				वापस 0;
			पूर्ण
			अवरोध;
		हाल CEXPR_NAMES:
			अगर (sp == (CEXPR_MAXDEPTH-1))
				वापस 0;
			c = scontext;
			अगर (e->attr & CEXPR_TARGET)
				c = tcontext;
			अन्यथा अगर (e->attr & CEXPR_XTARGET) अणु
				c = xcontext;
				अगर (!c) अणु
					BUG();
					वापस 0;
				पूर्ण
			पूर्ण
			अगर (e->attr & CEXPR_USER)
				val1 = c->user;
			अन्यथा अगर (e->attr & CEXPR_ROLE)
				val1 = c->role;
			अन्यथा अगर (e->attr & CEXPR_TYPE)
				val1 = c->type;
			अन्यथा अणु
				BUG();
				वापस 0;
			पूर्ण

			चयन (e->op) अणु
			हाल CEXPR_EQ:
				s[++sp] = ebiपंचांगap_get_bit(&e->names, val1 - 1);
				अवरोध;
			हाल CEXPR_NEQ:
				s[++sp] = !ebiपंचांगap_get_bit(&e->names, val1 - 1);
				अवरोध;
			शेष:
				BUG();
				वापस 0;
			पूर्ण
			अवरोध;
		शेष:
			BUG();
			वापस 0;
		पूर्ण
	पूर्ण

	BUG_ON(sp != 0);
	वापस s[0];
पूर्ण

/*
 * security_dump_masked_av - dumps masked permissions during
 * security_compute_av due to RBAC, MLS/Constraपूर्णांक and Type bounds.
 */
अटल पूर्णांक dump_masked_av_helper(व्योम *k, व्योम *d, व्योम *args)
अणु
	काष्ठा perm_datum *pdatum = d;
	अक्षर **permission_names = args;

	BUG_ON(pdatum->value < 1 || pdatum->value > 32);

	permission_names[pdatum->value - 1] = (अक्षर *)k;

	वापस 0;
पूर्ण

अटल व्योम security_dump_masked_av(काष्ठा policydb *policydb,
				    काष्ठा context *scontext,
				    काष्ठा context *tcontext,
				    u16 tclass,
				    u32 permissions,
				    स्थिर अक्षर *reason)
अणु
	काष्ठा common_datum *common_dat;
	काष्ठा class_datum *tclass_dat;
	काष्ठा audit_buffer *ab;
	अक्षर *tclass_name;
	अक्षर *scontext_name = शून्य;
	अक्षर *tcontext_name = शून्य;
	अक्षर *permission_names[32];
	पूर्णांक index;
	u32 length;
	bool need_comma = false;

	अगर (!permissions)
		वापस;

	tclass_name = sym_name(policydb, SYM_CLASSES, tclass - 1);
	tclass_dat = policydb->class_val_to_काष्ठा[tclass - 1];
	common_dat = tclass_dat->comdatum;

	/* init permission_names */
	अगर (common_dat &&
	    hashtab_map(&common_dat->permissions.table,
			dump_masked_av_helper, permission_names) < 0)
		जाओ out;

	अगर (hashtab_map(&tclass_dat->permissions.table,
			dump_masked_av_helper, permission_names) < 0)
		जाओ out;

	/* get scontext/tcontext in text क्रमm */
	अगर (context_काष्ठा_to_string(policydb, scontext,
				     &scontext_name, &length) < 0)
		जाओ out;

	अगर (context_काष्ठा_to_string(policydb, tcontext,
				     &tcontext_name, &length) < 0)
		जाओ out;

	/* audit a message */
	ab = audit_log_start(audit_context(),
			     GFP_ATOMIC, AUDIT_SELINUX_ERR);
	अगर (!ab)
		जाओ out;

	audit_log_क्रमmat(ab, "op=security_compute_av reason=%s "
			 "scontext=%s tcontext=%s tclass=%s perms=",
			 reason, scontext_name, tcontext_name, tclass_name);

	क्रम (index = 0; index < 32; index++) अणु
		u32 mask = (1 << index);

		अगर ((mask & permissions) == 0)
			जारी;

		audit_log_क्रमmat(ab, "%s%s",
				 need_comma ? "," : "",
				 permission_names[index]
				 ? permission_names[index] : "????");
		need_comma = true;
	पूर्ण
	audit_log_end(ab);
out:
	/* release scontext/tcontext */
	kमुक्त(tcontext_name);
	kमुक्त(scontext_name);

	वापस;
पूर्ण

/*
 * security_boundary_permission - drops violated permissions
 * on boundary स्थिरraपूर्णांक.
 */
अटल व्योम type_attribute_bounds_av(काष्ठा policydb *policydb,
				     काष्ठा context *scontext,
				     काष्ठा context *tcontext,
				     u16 tclass,
				     काष्ठा av_decision *avd)
अणु
	काष्ठा context lo_scontext;
	काष्ठा context lo_tcontext, *tcontextp = tcontext;
	काष्ठा av_decision lo_avd;
	काष्ठा type_datum *source;
	काष्ठा type_datum *target;
	u32 masked = 0;

	source = policydb->type_val_to_काष्ठा[scontext->type - 1];
	BUG_ON(!source);

	अगर (!source->bounds)
		वापस;

	target = policydb->type_val_to_काष्ठा[tcontext->type - 1];
	BUG_ON(!target);

	स_रखो(&lo_avd, 0, माप(lo_avd));

	स_नकल(&lo_scontext, scontext, माप(lo_scontext));
	lo_scontext.type = source->bounds;

	अगर (target->bounds) अणु
		स_नकल(&lo_tcontext, tcontext, माप(lo_tcontext));
		lo_tcontext.type = target->bounds;
		tcontextp = &lo_tcontext;
	पूर्ण

	context_काष्ठा_compute_av(policydb, &lo_scontext,
				  tcontextp,
				  tclass,
				  &lo_avd,
				  शून्य);

	masked = ~lo_avd.allowed & avd->allowed;

	अगर (likely(!masked))
		वापस;		/* no masked permission */

	/* mask violated permissions */
	avd->allowed &= ~masked;

	/* audit masked permissions */
	security_dump_masked_av(policydb, scontext, tcontext,
				tclass, masked, "bounds");
पूर्ण

/*
 * flag which drivers have permissions
 * only looking क्रम ioctl based extended permssions
 */
व्योम services_compute_xperms_drivers(
		काष्ठा extended_perms *xperms,
		काष्ठा avtab_node *node)
अणु
	अचिन्हित पूर्णांक i;

	अगर (node->datum.u.xperms->specअगरied == AVTAB_XPERMS_IOCTLDRIVER) अणु
		/* अगर one or more driver has all permissions allowed */
		क्रम (i = 0; i < ARRAY_SIZE(xperms->drivers.p); i++)
			xperms->drivers.p[i] |= node->datum.u.xperms->perms.p[i];
	पूर्ण अन्यथा अगर (node->datum.u.xperms->specअगरied == AVTAB_XPERMS_IOCTLFUNCTION) अणु
		/* अगर allowing permissions within a driver */
		security_xperm_set(xperms->drivers.p,
					node->datum.u.xperms->driver);
	पूर्ण

	xperms->len = 1;
पूर्ण

/*
 * Compute access vectors and extended permissions based on a context
 * काष्ठाure pair क्रम the permissions in a particular class.
 */
अटल व्योम context_काष्ठा_compute_av(काष्ठा policydb *policydb,
				      काष्ठा context *scontext,
				      काष्ठा context *tcontext,
				      u16 tclass,
				      काष्ठा av_decision *avd,
				      काष्ठा extended_perms *xperms)
अणु
	काष्ठा स्थिरraपूर्णांक_node *स्थिरraपूर्णांक;
	काष्ठा role_allow *ra;
	काष्ठा avtab_key avkey;
	काष्ठा avtab_node *node;
	काष्ठा class_datum *tclass_datum;
	काष्ठा ebiपंचांगap *sattr, *tattr;
	काष्ठा ebiपंचांगap_node *snode, *tnode;
	अचिन्हित पूर्णांक i, j;

	avd->allowed = 0;
	avd->auditallow = 0;
	avd->auditdeny = 0xffffffff;
	अगर (xperms) अणु
		स_रखो(&xperms->drivers, 0, माप(xperms->drivers));
		xperms->len = 0;
	पूर्ण

	अगर (unlikely(!tclass || tclass > policydb->p_classes.nprim)) अणु
		अगर (prपूर्णांकk_ratelimit())
			pr_warn("SELinux:  Invalid class %hu\n", tclass);
		वापस;
	पूर्ण

	tclass_datum = policydb->class_val_to_काष्ठा[tclass - 1];

	/*
	 * If a specअगरic type enक्रमcement rule was defined क्रम
	 * this permission check, then use it.
	 */
	avkey.target_class = tclass;
	avkey.specअगरied = AVTAB_AV | AVTAB_XPERMS;
	sattr = &policydb->type_attr_map_array[scontext->type - 1];
	tattr = &policydb->type_attr_map_array[tcontext->type - 1];
	ebiपंचांगap_क्रम_each_positive_bit(sattr, snode, i) अणु
		ebiपंचांगap_क्रम_each_positive_bit(tattr, tnode, j) अणु
			avkey.source_type = i + 1;
			avkey.target_type = j + 1;
			क्रम (node = avtab_search_node(&policydb->te_avtab,
						      &avkey);
			     node;
			     node = avtab_search_node_next(node, avkey.specअगरied)) अणु
				अगर (node->key.specअगरied == AVTAB_ALLOWED)
					avd->allowed |= node->datum.u.data;
				अन्यथा अगर (node->key.specअगरied == AVTAB_AUDITALLOW)
					avd->auditallow |= node->datum.u.data;
				अन्यथा अगर (node->key.specअगरied == AVTAB_AUDITDENY)
					avd->auditdeny &= node->datum.u.data;
				अन्यथा अगर (xperms && (node->key.specअगरied & AVTAB_XPERMS))
					services_compute_xperms_drivers(xperms, node);
			पूर्ण

			/* Check conditional av table क्रम additional permissions */
			cond_compute_av(&policydb->te_cond_avtab, &avkey,
					avd, xperms);

		पूर्ण
	पूर्ण

	/*
	 * Remove any permissions prohibited by a स्थिरraपूर्णांक (this includes
	 * the MLS policy).
	 */
	स्थिरraपूर्णांक = tclass_datum->स्थिरraपूर्णांकs;
	जबतक (स्थिरraपूर्णांक) अणु
		अगर ((स्थिरraपूर्णांक->permissions & (avd->allowed)) &&
		    !स्थिरraपूर्णांक_expr_eval(policydb, scontext, tcontext, शून्य,
					  स्थिरraपूर्णांक->expr)) अणु
			avd->allowed &= ~(स्थिरraपूर्णांक->permissions);
		पूर्ण
		स्थिरraपूर्णांक = स्थिरraपूर्णांक->next;
	पूर्ण

	/*
	 * If checking process transition permission and the
	 * role is changing, then check the (current_role, new_role)
	 * pair.
	 */
	अगर (tclass == policydb->process_class &&
	    (avd->allowed & policydb->process_trans_perms) &&
	    scontext->role != tcontext->role) अणु
		क्रम (ra = policydb->role_allow; ra; ra = ra->next) अणु
			अगर (scontext->role == ra->role &&
			    tcontext->role == ra->new_role)
				अवरोध;
		पूर्ण
		अगर (!ra)
			avd->allowed &= ~policydb->process_trans_perms;
	पूर्ण

	/*
	 * If the given source and target types have boundary
	 * स्थिरraपूर्णांक, lazy checks have to mask any violated
	 * permission and notice it to userspace via audit.
	 */
	type_attribute_bounds_av(policydb, scontext, tcontext,
				 tclass, avd);
पूर्ण

अटल पूर्णांक security_validtrans_handle_fail(काष्ठा selinux_state *state,
					काष्ठा selinux_policy *policy,
					काष्ठा sidtab_entry *oentry,
					काष्ठा sidtab_entry *nentry,
					काष्ठा sidtab_entry *tentry,
					u16 tclass)
अणु
	काष्ठा policydb *p = &policy->policydb;
	काष्ठा sidtab *sidtab = policy->sidtab;
	अक्षर *o = शून्य, *n = शून्य, *t = शून्य;
	u32 olen, nlen, tlen;

	अगर (sidtab_entry_to_string(p, sidtab, oentry, &o, &olen))
		जाओ out;
	अगर (sidtab_entry_to_string(p, sidtab, nentry, &n, &nlen))
		जाओ out;
	अगर (sidtab_entry_to_string(p, sidtab, tentry, &t, &tlen))
		जाओ out;
	audit_log(audit_context(), GFP_ATOMIC, AUDIT_SELINUX_ERR,
		  "op=security_validate_transition seresult=denied"
		  " oldcontext=%s newcontext=%s taskcontext=%s tclass=%s",
		  o, n, t, sym_name(p, SYM_CLASSES, tclass-1));
out:
	kमुक्त(o);
	kमुक्त(n);
	kमुक्त(t);

	अगर (!enक्रमcing_enabled(state))
		वापस 0;
	वापस -EPERM;
पूर्ण

अटल पूर्णांक security_compute_validatetrans(काष्ठा selinux_state *state,
					  u32 oldsid, u32 newsid, u32 tasksid,
					  u16 orig_tclass, bool user)
अणु
	काष्ठा selinux_policy *policy;
	काष्ठा policydb *policydb;
	काष्ठा sidtab *sidtab;
	काष्ठा sidtab_entry *oentry;
	काष्ठा sidtab_entry *nentry;
	काष्ठा sidtab_entry *tentry;
	काष्ठा class_datum *tclass_datum;
	काष्ठा स्थिरraपूर्णांक_node *स्थिरraपूर्णांक;
	u16 tclass;
	पूर्णांक rc = 0;


	अगर (!selinux_initialized(state))
		वापस 0;

	rcu_पढ़ो_lock();

	policy = rcu_dereference(state->policy);
	policydb = &policy->policydb;
	sidtab = policy->sidtab;

	अगर (!user)
		tclass = unmap_class(&policy->map, orig_tclass);
	अन्यथा
		tclass = orig_tclass;

	अगर (!tclass || tclass > policydb->p_classes.nprim) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण
	tclass_datum = policydb->class_val_to_काष्ठा[tclass - 1];

	oentry = sidtab_search_entry(sidtab, oldsid);
	अगर (!oentry) अणु
		pr_err("SELinux: %s:  unrecognized SID %d\n",
			__func__, oldsid);
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	nentry = sidtab_search_entry(sidtab, newsid);
	अगर (!nentry) अणु
		pr_err("SELinux: %s:  unrecognized SID %d\n",
			__func__, newsid);
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	tentry = sidtab_search_entry(sidtab, tasksid);
	अगर (!tentry) अणु
		pr_err("SELinux: %s:  unrecognized SID %d\n",
			__func__, tasksid);
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	स्थिरraपूर्णांक = tclass_datum->validatetrans;
	जबतक (स्थिरraपूर्णांक) अणु
		अगर (!स्थिरraपूर्णांक_expr_eval(policydb, &oentry->context,
					  &nentry->context, &tentry->context,
					  स्थिरraपूर्णांक->expr)) अणु
			अगर (user)
				rc = -EPERM;
			अन्यथा
				rc = security_validtrans_handle_fail(state,
								policy,
								oentry,
								nentry,
								tentry,
								tclass);
			जाओ out;
		पूर्ण
		स्थिरraपूर्णांक = स्थिरraपूर्णांक->next;
	पूर्ण

out:
	rcu_पढ़ो_unlock();
	वापस rc;
पूर्ण

पूर्णांक security_validate_transition_user(काष्ठा selinux_state *state,
				      u32 oldsid, u32 newsid, u32 tasksid,
				      u16 tclass)
अणु
	वापस security_compute_validatetrans(state, oldsid, newsid, tasksid,
					      tclass, true);
पूर्ण

पूर्णांक security_validate_transition(काष्ठा selinux_state *state,
				 u32 oldsid, u32 newsid, u32 tasksid,
				 u16 orig_tclass)
अणु
	वापस security_compute_validatetrans(state, oldsid, newsid, tasksid,
					      orig_tclass, false);
पूर्ण

/*
 * security_bounded_transition - check whether the given
 * transition is directed to bounded, or not.
 * It वापसs 0, अगर @newsid is bounded by @oldsid.
 * Otherwise, it वापसs error code.
 *
 * @oldsid : current security identअगरier
 * @newsid : destinated security identअगरier
 */
पूर्णांक security_bounded_transition(काष्ठा selinux_state *state,
				u32 old_sid, u32 new_sid)
अणु
	काष्ठा selinux_policy *policy;
	काष्ठा policydb *policydb;
	काष्ठा sidtab *sidtab;
	काष्ठा sidtab_entry *old_entry, *new_entry;
	काष्ठा type_datum *type;
	पूर्णांक index;
	पूर्णांक rc;

	अगर (!selinux_initialized(state))
		वापस 0;

	rcu_पढ़ो_lock();
	policy = rcu_dereference(state->policy);
	policydb = &policy->policydb;
	sidtab = policy->sidtab;

	rc = -EINVAL;
	old_entry = sidtab_search_entry(sidtab, old_sid);
	अगर (!old_entry) अणु
		pr_err("SELinux: %s: unrecognized SID %u\n",
		       __func__, old_sid);
		जाओ out;
	पूर्ण

	rc = -EINVAL;
	new_entry = sidtab_search_entry(sidtab, new_sid);
	अगर (!new_entry) अणु
		pr_err("SELinux: %s: unrecognized SID %u\n",
		       __func__, new_sid);
		जाओ out;
	पूर्ण

	rc = 0;
	/* type/करोमुख्य unchanged */
	अगर (old_entry->context.type == new_entry->context.type)
		जाओ out;

	index = new_entry->context.type;
	जबतक (true) अणु
		type = policydb->type_val_to_काष्ठा[index - 1];
		BUG_ON(!type);

		/* not bounded anymore */
		rc = -EPERM;
		अगर (!type->bounds)
			अवरोध;

		/* @newsid is bounded by @oldsid */
		rc = 0;
		अगर (type->bounds == old_entry->context.type)
			अवरोध;

		index = type->bounds;
	पूर्ण

	अगर (rc) अणु
		अक्षर *old_name = शून्य;
		अक्षर *new_name = शून्य;
		u32 length;

		अगर (!sidtab_entry_to_string(policydb, sidtab, old_entry,
					    &old_name, &length) &&
		    !sidtab_entry_to_string(policydb, sidtab, new_entry,
					    &new_name, &length)) अणु
			audit_log(audit_context(),
				  GFP_ATOMIC, AUDIT_SELINUX_ERR,
				  "op=security_bounded_transition "
				  "seresult=denied "
				  "oldcontext=%s newcontext=%s",
				  old_name, new_name);
		पूर्ण
		kमुक्त(new_name);
		kमुक्त(old_name);
	पूर्ण
out:
	rcu_पढ़ो_unlock();

	वापस rc;
पूर्ण

अटल व्योम avd_init(काष्ठा selinux_policy *policy, काष्ठा av_decision *avd)
अणु
	avd->allowed = 0;
	avd->auditallow = 0;
	avd->auditdeny = 0xffffffff;
	अगर (policy)
		avd->seqno = policy->latest_granting;
	अन्यथा
		avd->seqno = 0;
	avd->flags = 0;
पूर्ण

व्योम services_compute_xperms_decision(काष्ठा extended_perms_decision *xpermd,
					काष्ठा avtab_node *node)
अणु
	अचिन्हित पूर्णांक i;

	अगर (node->datum.u.xperms->specअगरied == AVTAB_XPERMS_IOCTLFUNCTION) अणु
		अगर (xpermd->driver != node->datum.u.xperms->driver)
			वापस;
	पूर्ण अन्यथा अगर (node->datum.u.xperms->specअगरied == AVTAB_XPERMS_IOCTLDRIVER) अणु
		अगर (!security_xperm_test(node->datum.u.xperms->perms.p,
					xpermd->driver))
			वापस;
	पूर्ण अन्यथा अणु
		BUG();
	पूर्ण

	अगर (node->key.specअगरied == AVTAB_XPERMS_ALLOWED) अणु
		xpermd->used |= XPERMS_ALLOWED;
		अगर (node->datum.u.xperms->specअगरied == AVTAB_XPERMS_IOCTLDRIVER) अणु
			स_रखो(xpermd->allowed->p, 0xff,
					माप(xpermd->allowed->p));
		पूर्ण
		अगर (node->datum.u.xperms->specअगरied == AVTAB_XPERMS_IOCTLFUNCTION) अणु
			क्रम (i = 0; i < ARRAY_SIZE(xpermd->allowed->p); i++)
				xpermd->allowed->p[i] |=
					node->datum.u.xperms->perms.p[i];
		पूर्ण
	पूर्ण अन्यथा अगर (node->key.specअगरied == AVTAB_XPERMS_AUDITALLOW) अणु
		xpermd->used |= XPERMS_AUDITALLOW;
		अगर (node->datum.u.xperms->specअगरied == AVTAB_XPERMS_IOCTLDRIVER) अणु
			स_रखो(xpermd->auditallow->p, 0xff,
					माप(xpermd->auditallow->p));
		पूर्ण
		अगर (node->datum.u.xperms->specअगरied == AVTAB_XPERMS_IOCTLFUNCTION) अणु
			क्रम (i = 0; i < ARRAY_SIZE(xpermd->auditallow->p); i++)
				xpermd->auditallow->p[i] |=
					node->datum.u.xperms->perms.p[i];
		पूर्ण
	पूर्ण अन्यथा अगर (node->key.specअगरied == AVTAB_XPERMS_DONTAUDIT) अणु
		xpermd->used |= XPERMS_DONTAUDIT;
		अगर (node->datum.u.xperms->specअगरied == AVTAB_XPERMS_IOCTLDRIVER) अणु
			स_रखो(xpermd->करोntaudit->p, 0xff,
					माप(xpermd->करोntaudit->p));
		पूर्ण
		अगर (node->datum.u.xperms->specअगरied == AVTAB_XPERMS_IOCTLFUNCTION) अणु
			क्रम (i = 0; i < ARRAY_SIZE(xpermd->करोntaudit->p); i++)
				xpermd->करोntaudit->p[i] |=
					node->datum.u.xperms->perms.p[i];
		पूर्ण
	पूर्ण अन्यथा अणु
		BUG();
	पूर्ण
पूर्ण

व्योम security_compute_xperms_decision(काष्ठा selinux_state *state,
				      u32 ssid,
				      u32 tsid,
				      u16 orig_tclass,
				      u8 driver,
				      काष्ठा extended_perms_decision *xpermd)
अणु
	काष्ठा selinux_policy *policy;
	काष्ठा policydb *policydb;
	काष्ठा sidtab *sidtab;
	u16 tclass;
	काष्ठा context *scontext, *tcontext;
	काष्ठा avtab_key avkey;
	काष्ठा avtab_node *node;
	काष्ठा ebiपंचांगap *sattr, *tattr;
	काष्ठा ebiपंचांगap_node *snode, *tnode;
	अचिन्हित पूर्णांक i, j;

	xpermd->driver = driver;
	xpermd->used = 0;
	स_रखो(xpermd->allowed->p, 0, माप(xpermd->allowed->p));
	स_रखो(xpermd->auditallow->p, 0, माप(xpermd->auditallow->p));
	स_रखो(xpermd->करोntaudit->p, 0, माप(xpermd->करोntaudit->p));

	rcu_पढ़ो_lock();
	अगर (!selinux_initialized(state))
		जाओ allow;

	policy = rcu_dereference(state->policy);
	policydb = &policy->policydb;
	sidtab = policy->sidtab;

	scontext = sidtab_search(sidtab, ssid);
	अगर (!scontext) अणु
		pr_err("SELinux: %s:  unrecognized SID %d\n",
		       __func__, ssid);
		जाओ out;
	पूर्ण

	tcontext = sidtab_search(sidtab, tsid);
	अगर (!tcontext) अणु
		pr_err("SELinux: %s:  unrecognized SID %d\n",
		       __func__, tsid);
		जाओ out;
	पूर्ण

	tclass = unmap_class(&policy->map, orig_tclass);
	अगर (unlikely(orig_tclass && !tclass)) अणु
		अगर (policydb->allow_unknown)
			जाओ allow;
		जाओ out;
	पूर्ण


	अगर (unlikely(!tclass || tclass > policydb->p_classes.nprim)) अणु
		pr_warn_ratelimited("SELinux:  Invalid class %hu\n", tclass);
		जाओ out;
	पूर्ण

	avkey.target_class = tclass;
	avkey.specअगरied = AVTAB_XPERMS;
	sattr = &policydb->type_attr_map_array[scontext->type - 1];
	tattr = &policydb->type_attr_map_array[tcontext->type - 1];
	ebiपंचांगap_क्रम_each_positive_bit(sattr, snode, i) अणु
		ebiपंचांगap_क्रम_each_positive_bit(tattr, tnode, j) अणु
			avkey.source_type = i + 1;
			avkey.target_type = j + 1;
			क्रम (node = avtab_search_node(&policydb->te_avtab,
						      &avkey);
			     node;
			     node = avtab_search_node_next(node, avkey.specअगरied))
				services_compute_xperms_decision(xpermd, node);

			cond_compute_xperms(&policydb->te_cond_avtab,
						&avkey, xpermd);
		पूर्ण
	पूर्ण
out:
	rcu_पढ़ो_unlock();
	वापस;
allow:
	स_रखो(xpermd->allowed->p, 0xff, माप(xpermd->allowed->p));
	जाओ out;
पूर्ण

/**
 * security_compute_av - Compute access vector decisions.
 * @ssid: source security identअगरier
 * @tsid: target security identअगरier
 * @tclass: target security class
 * @avd: access vector decisions
 * @xperms: extended permissions
 *
 * Compute a set of access vector decisions based on the
 * SID pair (@ssid, @tsid) क्रम the permissions in @tclass.
 */
व्योम security_compute_av(काष्ठा selinux_state *state,
			 u32 ssid,
			 u32 tsid,
			 u16 orig_tclass,
			 काष्ठा av_decision *avd,
			 काष्ठा extended_perms *xperms)
अणु
	काष्ठा selinux_policy *policy;
	काष्ठा policydb *policydb;
	काष्ठा sidtab *sidtab;
	u16 tclass;
	काष्ठा context *scontext = शून्य, *tcontext = शून्य;

	rcu_पढ़ो_lock();
	policy = rcu_dereference(state->policy);
	avd_init(policy, avd);
	xperms->len = 0;
	अगर (!selinux_initialized(state))
		जाओ allow;

	policydb = &policy->policydb;
	sidtab = policy->sidtab;

	scontext = sidtab_search(sidtab, ssid);
	अगर (!scontext) अणु
		pr_err("SELinux: %s:  unrecognized SID %d\n",
		       __func__, ssid);
		जाओ out;
	पूर्ण

	/* permissive करोमुख्य? */
	अगर (ebiपंचांगap_get_bit(&policydb->permissive_map, scontext->type))
		avd->flags |= AVD_FLAGS_PERMISSIVE;

	tcontext = sidtab_search(sidtab, tsid);
	अगर (!tcontext) अणु
		pr_err("SELinux: %s:  unrecognized SID %d\n",
		       __func__, tsid);
		जाओ out;
	पूर्ण

	tclass = unmap_class(&policy->map, orig_tclass);
	अगर (unlikely(orig_tclass && !tclass)) अणु
		अगर (policydb->allow_unknown)
			जाओ allow;
		जाओ out;
	पूर्ण
	context_काष्ठा_compute_av(policydb, scontext, tcontext, tclass, avd,
				  xperms);
	map_decision(&policy->map, orig_tclass, avd,
		     policydb->allow_unknown);
out:
	rcu_पढ़ो_unlock();
	वापस;
allow:
	avd->allowed = 0xffffffff;
	जाओ out;
पूर्ण

व्योम security_compute_av_user(काष्ठा selinux_state *state,
			      u32 ssid,
			      u32 tsid,
			      u16 tclass,
			      काष्ठा av_decision *avd)
अणु
	काष्ठा selinux_policy *policy;
	काष्ठा policydb *policydb;
	काष्ठा sidtab *sidtab;
	काष्ठा context *scontext = शून्य, *tcontext = शून्य;

	rcu_पढ़ो_lock();
	policy = rcu_dereference(state->policy);
	avd_init(policy, avd);
	अगर (!selinux_initialized(state))
		जाओ allow;

	policydb = &policy->policydb;
	sidtab = policy->sidtab;

	scontext = sidtab_search(sidtab, ssid);
	अगर (!scontext) अणु
		pr_err("SELinux: %s:  unrecognized SID %d\n",
		       __func__, ssid);
		जाओ out;
	पूर्ण

	/* permissive करोमुख्य? */
	अगर (ebiपंचांगap_get_bit(&policydb->permissive_map, scontext->type))
		avd->flags |= AVD_FLAGS_PERMISSIVE;

	tcontext = sidtab_search(sidtab, tsid);
	अगर (!tcontext) अणु
		pr_err("SELinux: %s:  unrecognized SID %d\n",
		       __func__, tsid);
		जाओ out;
	पूर्ण

	अगर (unlikely(!tclass)) अणु
		अगर (policydb->allow_unknown)
			जाओ allow;
		जाओ out;
	पूर्ण

	context_काष्ठा_compute_av(policydb, scontext, tcontext, tclass, avd,
				  शून्य);
 out:
	rcu_पढ़ो_unlock();
	वापस;
allow:
	avd->allowed = 0xffffffff;
	जाओ out;
पूर्ण

/*
 * Write the security context string representation of
 * the context काष्ठाure `context' पूर्णांकo a dynamically
 * allocated string of the correct size.  Set `*scontext'
 * to poपूर्णांक to this string and set `*scontext_len' to
 * the length of the string.
 */
अटल पूर्णांक context_काष्ठा_to_string(काष्ठा policydb *p,
				    काष्ठा context *context,
				    अक्षर **scontext, u32 *scontext_len)
अणु
	अक्षर *scontextp;

	अगर (scontext)
		*scontext = शून्य;
	*scontext_len = 0;

	अगर (context->len) अणु
		*scontext_len = context->len;
		अगर (scontext) अणु
			*scontext = kstrdup(context->str, GFP_ATOMIC);
			अगर (!(*scontext))
				वापस -ENOMEM;
		पूर्ण
		वापस 0;
	पूर्ण

	/* Compute the size of the context. */
	*scontext_len += म_माप(sym_name(p, SYM_USERS, context->user - 1)) + 1;
	*scontext_len += म_माप(sym_name(p, SYM_ROLES, context->role - 1)) + 1;
	*scontext_len += म_माप(sym_name(p, SYM_TYPES, context->type - 1)) + 1;
	*scontext_len += mls_compute_context_len(p, context);

	अगर (!scontext)
		वापस 0;

	/* Allocate space क्रम the context; caller must मुक्त this space. */
	scontextp = kदो_स्मृति(*scontext_len, GFP_ATOMIC);
	अगर (!scontextp)
		वापस -ENOMEM;
	*scontext = scontextp;

	/*
	 * Copy the user name, role name and type name पूर्णांकo the context.
	 */
	scontextp += प्र_लिखो(scontextp, "%s:%s:%s",
		sym_name(p, SYM_USERS, context->user - 1),
		sym_name(p, SYM_ROLES, context->role - 1),
		sym_name(p, SYM_TYPES, context->type - 1));

	mls_sid_to_context(p, context, &scontextp);

	*scontextp = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक sidtab_entry_to_string(काष्ठा policydb *p,
				  काष्ठा sidtab *sidtab,
				  काष्ठा sidtab_entry *entry,
				  अक्षर **scontext, u32 *scontext_len)
अणु
	पूर्णांक rc = sidtab_sid2str_get(sidtab, entry, scontext, scontext_len);

	अगर (rc != -ENOENT)
		वापस rc;

	rc = context_काष्ठा_to_string(p, &entry->context, scontext,
				      scontext_len);
	अगर (!rc && scontext)
		sidtab_sid2str_put(sidtab, entry, *scontext, *scontext_len);
	वापस rc;
पूर्ण

#समावेश "initial_sid_to_string.h"

पूर्णांक security_sidtab_hash_stats(काष्ठा selinux_state *state, अक्षर *page)
अणु
	काष्ठा selinux_policy *policy;
	पूर्णांक rc;

	अगर (!selinux_initialized(state)) अणु
		pr_err("SELinux: %s:  called before initial load_policy\n",
		       __func__);
		वापस -EINVAL;
	पूर्ण

	rcu_पढ़ो_lock();
	policy = rcu_dereference(state->policy);
	rc = sidtab_hash_stats(policy->sidtab, page);
	rcu_पढ़ो_unlock();

	वापस rc;
पूर्ण

स्थिर अक्षर *security_get_initial_sid_context(u32 sid)
अणु
	अगर (unlikely(sid > SECINITSID_NUM))
		वापस शून्य;
	वापस initial_sid_to_string[sid];
पूर्ण

अटल पूर्णांक security_sid_to_context_core(काष्ठा selinux_state *state,
					u32 sid, अक्षर **scontext,
					u32 *scontext_len, पूर्णांक क्रमce,
					पूर्णांक only_invalid)
अणु
	काष्ठा selinux_policy *policy;
	काष्ठा policydb *policydb;
	काष्ठा sidtab *sidtab;
	काष्ठा sidtab_entry *entry;
	पूर्णांक rc = 0;

	अगर (scontext)
		*scontext = शून्य;
	*scontext_len  = 0;

	अगर (!selinux_initialized(state)) अणु
		अगर (sid <= SECINITSID_NUM) अणु
			अक्षर *scontextp;
			स्थिर अक्षर *s = initial_sid_to_string[sid];

			अगर (!s)
				वापस -EINVAL;
			*scontext_len = म_माप(s) + 1;
			अगर (!scontext)
				वापस 0;
			scontextp = kmemdup(s, *scontext_len, GFP_ATOMIC);
			अगर (!scontextp)
				वापस -ENOMEM;
			*scontext = scontextp;
			वापस 0;
		पूर्ण
		pr_err("SELinux: %s:  called before initial "
		       "load_policy on unknown SID %d\n", __func__, sid);
		वापस -EINVAL;
	पूर्ण
	rcu_पढ़ो_lock();
	policy = rcu_dereference(state->policy);
	policydb = &policy->policydb;
	sidtab = policy->sidtab;

	अगर (क्रमce)
		entry = sidtab_search_entry_क्रमce(sidtab, sid);
	अन्यथा
		entry = sidtab_search_entry(sidtab, sid);
	अगर (!entry) अणु
		pr_err("SELinux: %s:  unrecognized SID %d\n",
			__func__, sid);
		rc = -EINVAL;
		जाओ out_unlock;
	पूर्ण
	अगर (only_invalid && !entry->context.len)
		जाओ out_unlock;

	rc = sidtab_entry_to_string(policydb, sidtab, entry, scontext,
				    scontext_len);

out_unlock:
	rcu_पढ़ो_unlock();
	वापस rc;

पूर्ण

/**
 * security_sid_to_context - Obtain a context क्रम a given SID.
 * @sid: security identअगरier, SID
 * @scontext: security context
 * @scontext_len: length in bytes
 *
 * Write the string representation of the context associated with @sid
 * पूर्णांकo a dynamically allocated string of the correct size.  Set @scontext
 * to poपूर्णांक to this string and set @scontext_len to the length of the string.
 */
पूर्णांक security_sid_to_context(काष्ठा selinux_state *state,
			    u32 sid, अक्षर **scontext, u32 *scontext_len)
अणु
	वापस security_sid_to_context_core(state, sid, scontext,
					    scontext_len, 0, 0);
पूर्ण

पूर्णांक security_sid_to_context_क्रमce(काष्ठा selinux_state *state, u32 sid,
				  अक्षर **scontext, u32 *scontext_len)
अणु
	वापस security_sid_to_context_core(state, sid, scontext,
					    scontext_len, 1, 0);
पूर्ण

/**
 * security_sid_to_context_inval - Obtain a context क्रम a given SID अगर it
 *                                 is invalid.
 * @sid: security identअगरier, SID
 * @scontext: security context
 * @scontext_len: length in bytes
 *
 * Write the string representation of the context associated with @sid
 * पूर्णांकo a dynamically allocated string of the correct size, but only अगर the
 * context is invalid in the current policy.  Set @scontext to poपूर्णांक to
 * this string (or शून्य अगर the context is valid) and set @scontext_len to
 * the length of the string (or 0 अगर the context is valid).
 */
पूर्णांक security_sid_to_context_inval(काष्ठा selinux_state *state, u32 sid,
				  अक्षर **scontext, u32 *scontext_len)
अणु
	वापस security_sid_to_context_core(state, sid, scontext,
					    scontext_len, 1, 1);
पूर्ण

/*
 * Caveat:  Mutates scontext.
 */
अटल पूर्णांक string_to_context_काष्ठा(काष्ठा policydb *pol,
				    काष्ठा sidtab *sidtabp,
				    अक्षर *scontext,
				    काष्ठा context *ctx,
				    u32 def_sid)
अणु
	काष्ठा role_datum *role;
	काष्ठा type_datum *typdatum;
	काष्ठा user_datum *usrdatum;
	अक्षर *scontextp, *p, oldc;
	पूर्णांक rc = 0;

	context_init(ctx);

	/* Parse the security context. */

	rc = -EINVAL;
	scontextp = (अक्षर *) scontext;

	/* Extract the user. */
	p = scontextp;
	जबतक (*p && *p != ':')
		p++;

	अगर (*p == 0)
		जाओ out;

	*p++ = 0;

	usrdatum = symtab_search(&pol->p_users, scontextp);
	अगर (!usrdatum)
		जाओ out;

	ctx->user = usrdatum->value;

	/* Extract role. */
	scontextp = p;
	जबतक (*p && *p != ':')
		p++;

	अगर (*p == 0)
		जाओ out;

	*p++ = 0;

	role = symtab_search(&pol->p_roles, scontextp);
	अगर (!role)
		जाओ out;
	ctx->role = role->value;

	/* Extract type. */
	scontextp = p;
	जबतक (*p && *p != ':')
		p++;
	oldc = *p;
	*p++ = 0;

	typdatum = symtab_search(&pol->p_types, scontextp);
	अगर (!typdatum || typdatum->attribute)
		जाओ out;

	ctx->type = typdatum->value;

	rc = mls_context_to_sid(pol, oldc, p, ctx, sidtabp, def_sid);
	अगर (rc)
		जाओ out;

	/* Check the validity of the new context. */
	rc = -EINVAL;
	अगर (!policydb_context_isvalid(pol, ctx))
		जाओ out;
	rc = 0;
out:
	अगर (rc)
		context_destroy(ctx);
	वापस rc;
पूर्ण

अटल पूर्णांक security_context_to_sid_core(काष्ठा selinux_state *state,
					स्थिर अक्षर *scontext, u32 scontext_len,
					u32 *sid, u32 def_sid, gfp_t gfp_flags,
					पूर्णांक क्रमce)
अणु
	काष्ठा selinux_policy *policy;
	काष्ठा policydb *policydb;
	काष्ठा sidtab *sidtab;
	अक्षर *scontext2, *str = शून्य;
	काष्ठा context context;
	पूर्णांक rc = 0;

	/* An empty security context is never valid. */
	अगर (!scontext_len)
		वापस -EINVAL;

	/* Copy the string to allow changes and ensure a NUL terminator */
	scontext2 = kmemdup_nul(scontext, scontext_len, gfp_flags);
	अगर (!scontext2)
		वापस -ENOMEM;

	अगर (!selinux_initialized(state)) अणु
		पूर्णांक i;

		क्रम (i = 1; i < SECINITSID_NUM; i++) अणु
			स्थिर अक्षर *s = initial_sid_to_string[i];

			अगर (s && !म_भेद(s, scontext2)) अणु
				*sid = i;
				जाओ out;
			पूर्ण
		पूर्ण
		*sid = SECINITSID_KERNEL;
		जाओ out;
	पूर्ण
	*sid = SECSID_शून्य;

	अगर (क्रमce) अणु
		/* Save another copy क्रम storing in unपूर्णांकerpreted क्रमm */
		rc = -ENOMEM;
		str = kstrdup(scontext2, gfp_flags);
		अगर (!str)
			जाओ out;
	पूर्ण
retry:
	rcu_पढ़ो_lock();
	policy = rcu_dereference(state->policy);
	policydb = &policy->policydb;
	sidtab = policy->sidtab;
	rc = string_to_context_काष्ठा(policydb, sidtab, scontext2,
				      &context, def_sid);
	अगर (rc == -EINVAL && क्रमce) अणु
		context.str = str;
		context.len = म_माप(str) + 1;
		str = शून्य;
	पूर्ण अन्यथा अगर (rc)
		जाओ out_unlock;
	rc = sidtab_context_to_sid(sidtab, &context, sid);
	अगर (rc == -ESTALE) अणु
		rcu_पढ़ो_unlock();
		अगर (context.str) अणु
			str = context.str;
			context.str = शून्य;
		पूर्ण
		context_destroy(&context);
		जाओ retry;
	पूर्ण
	context_destroy(&context);
out_unlock:
	rcu_पढ़ो_unlock();
out:
	kमुक्त(scontext2);
	kमुक्त(str);
	वापस rc;
पूर्ण

/**
 * security_context_to_sid - Obtain a SID क्रम a given security context.
 * @scontext: security context
 * @scontext_len: length in bytes
 * @sid: security identअगरier, SID
 * @gfp: context क्रम the allocation
 *
 * Obtains a SID associated with the security context that
 * has the string representation specअगरied by @scontext.
 * Returns -%EINVAL अगर the context is invalid, -%ENOMEM अगर insufficient
 * memory is available, or 0 on success.
 */
पूर्णांक security_context_to_sid(काष्ठा selinux_state *state,
			    स्थिर अक्षर *scontext, u32 scontext_len, u32 *sid,
			    gfp_t gfp)
अणु
	वापस security_context_to_sid_core(state, scontext, scontext_len,
					    sid, SECSID_शून्य, gfp, 0);
पूर्ण

पूर्णांक security_context_str_to_sid(काष्ठा selinux_state *state,
				स्थिर अक्षर *scontext, u32 *sid, gfp_t gfp)
अणु
	वापस security_context_to_sid(state, scontext, म_माप(scontext),
				       sid, gfp);
पूर्ण

/**
 * security_context_to_sid_शेष - Obtain a SID क्रम a given security context,
 * falling back to specअगरied शेष अगर needed.
 *
 * @scontext: security context
 * @scontext_len: length in bytes
 * @sid: security identअगरier, SID
 * @def_sid: शेष SID to assign on error
 *
 * Obtains a SID associated with the security context that
 * has the string representation specअगरied by @scontext.
 * The शेष SID is passed to the MLS layer to be used to allow
 * kernel labeling of the MLS field अगर the MLS field is not present
 * (क्रम upgrading to MLS without full relabel).
 * Implicitly क्रमces adding of the context even अगर it cannot be mapped yet.
 * Returns -%EINVAL अगर the context is invalid, -%ENOMEM अगर insufficient
 * memory is available, or 0 on success.
 */
पूर्णांक security_context_to_sid_शेष(काष्ठा selinux_state *state,
				    स्थिर अक्षर *scontext, u32 scontext_len,
				    u32 *sid, u32 def_sid, gfp_t gfp_flags)
अणु
	वापस security_context_to_sid_core(state, scontext, scontext_len,
					    sid, def_sid, gfp_flags, 1);
पूर्ण

पूर्णांक security_context_to_sid_क्रमce(काष्ठा selinux_state *state,
				  स्थिर अक्षर *scontext, u32 scontext_len,
				  u32 *sid)
अणु
	वापस security_context_to_sid_core(state, scontext, scontext_len,
					    sid, SECSID_शून्य, GFP_KERNEL, 1);
पूर्ण

अटल पूर्णांक compute_sid_handle_invalid_context(
	काष्ठा selinux_state *state,
	काष्ठा selinux_policy *policy,
	काष्ठा sidtab_entry *sentry,
	काष्ठा sidtab_entry *tentry,
	u16 tclass,
	काष्ठा context *newcontext)
अणु
	काष्ठा policydb *policydb = &policy->policydb;
	काष्ठा sidtab *sidtab = policy->sidtab;
	अक्षर *s = शून्य, *t = शून्य, *n = शून्य;
	u32 slen, tlen, nlen;
	काष्ठा audit_buffer *ab;

	अगर (sidtab_entry_to_string(policydb, sidtab, sentry, &s, &slen))
		जाओ out;
	अगर (sidtab_entry_to_string(policydb, sidtab, tentry, &t, &tlen))
		जाओ out;
	अगर (context_काष्ठा_to_string(policydb, newcontext, &n, &nlen))
		जाओ out;
	ab = audit_log_start(audit_context(), GFP_ATOMIC, AUDIT_SELINUX_ERR);
	audit_log_क्रमmat(ab,
			 "op=security_compute_sid invalid_context=");
	/* no need to record the NUL with untrusted strings */
	audit_log_n_untrustedstring(ab, n, nlen - 1);
	audit_log_क्रमmat(ab, " scontext=%s tcontext=%s tclass=%s",
			 s, t, sym_name(policydb, SYM_CLASSES, tclass-1));
	audit_log_end(ab);
out:
	kमुक्त(s);
	kमुक्त(t);
	kमुक्त(n);
	अगर (!enक्रमcing_enabled(state))
		वापस 0;
	वापस -EACCES;
पूर्ण

अटल व्योम filename_compute_type(काष्ठा policydb *policydb,
				  काष्ठा context *newcontext,
				  u32 stype, u32 ttype, u16 tclass,
				  स्थिर अक्षर *objname)
अणु
	काष्ठा filename_trans_key ft;
	काष्ठा filename_trans_datum *datum;

	/*
	 * Most filename trans rules are going to live in specअगरic directories
	 * like /dev or /var/run.  This biपंचांगap will quickly skip rule searches
	 * अगर the ttype करोes not contain any rules.
	 */
	अगर (!ebiपंचांगap_get_bit(&policydb->filename_trans_ttypes, ttype))
		वापस;

	ft.ttype = ttype;
	ft.tclass = tclass;
	ft.name = objname;

	datum = policydb_filenametr_search(policydb, &ft);
	जबतक (datum) अणु
		अगर (ebiपंचांगap_get_bit(&datum->stypes, stype - 1)) अणु
			newcontext->type = datum->otype;
			वापस;
		पूर्ण
		datum = datum->next;
	पूर्ण
पूर्ण

अटल पूर्णांक security_compute_sid(काष्ठा selinux_state *state,
				u32 ssid,
				u32 tsid,
				u16 orig_tclass,
				u32 specअगरied,
				स्थिर अक्षर *objname,
				u32 *out_sid,
				bool kern)
अणु
	काष्ठा selinux_policy *policy;
	काष्ठा policydb *policydb;
	काष्ठा sidtab *sidtab;
	काष्ठा class_datum *cladatum;
	काष्ठा context *scontext, *tcontext, newcontext;
	काष्ठा sidtab_entry *sentry, *tentry;
	काष्ठा avtab_key avkey;
	काष्ठा avtab_datum *avdatum;
	काष्ठा avtab_node *node;
	u16 tclass;
	पूर्णांक rc = 0;
	bool sock;

	अगर (!selinux_initialized(state)) अणु
		चयन (orig_tclass) अणु
		हाल SECCLASS_PROCESS: /* kernel value */
			*out_sid = ssid;
			अवरोध;
		शेष:
			*out_sid = tsid;
			अवरोध;
		पूर्ण
		जाओ out;
	पूर्ण

retry:
	cladatum = शून्य;
	context_init(&newcontext);

	rcu_पढ़ो_lock();

	policy = rcu_dereference(state->policy);

	अगर (kern) अणु
		tclass = unmap_class(&policy->map, orig_tclass);
		sock = security_is_socket_class(orig_tclass);
	पूर्ण अन्यथा अणु
		tclass = orig_tclass;
		sock = security_is_socket_class(map_class(&policy->map,
							  tclass));
	पूर्ण

	policydb = &policy->policydb;
	sidtab = policy->sidtab;

	sentry = sidtab_search_entry(sidtab, ssid);
	अगर (!sentry) अणु
		pr_err("SELinux: %s:  unrecognized SID %d\n",
		       __func__, ssid);
		rc = -EINVAL;
		जाओ out_unlock;
	पूर्ण
	tentry = sidtab_search_entry(sidtab, tsid);
	अगर (!tentry) अणु
		pr_err("SELinux: %s:  unrecognized SID %d\n",
		       __func__, tsid);
		rc = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	scontext = &sentry->context;
	tcontext = &tentry->context;

	अगर (tclass && tclass <= policydb->p_classes.nprim)
		cladatum = policydb->class_val_to_काष्ठा[tclass - 1];

	/* Set the user identity. */
	चयन (specअगरied) अणु
	हाल AVTAB_TRANSITION:
	हाल AVTAB_CHANGE:
		अगर (cladatum && cladatum->शेष_user == DEFAULT_TARGET) अणु
			newcontext.user = tcontext->user;
		पूर्ण अन्यथा अणु
			/* notice this माला_लो both DEFAULT_SOURCE and unset */
			/* Use the process user identity. */
			newcontext.user = scontext->user;
		पूर्ण
		अवरोध;
	हाल AVTAB_MEMBER:
		/* Use the related object owner. */
		newcontext.user = tcontext->user;
		अवरोध;
	पूर्ण

	/* Set the role to शेष values. */
	अगर (cladatum && cladatum->शेष_role == DEFAULT_SOURCE) अणु
		newcontext.role = scontext->role;
	पूर्ण अन्यथा अगर (cladatum && cladatum->शेष_role == DEFAULT_TARGET) अणु
		newcontext.role = tcontext->role;
	पूर्ण अन्यथा अणु
		अगर ((tclass == policydb->process_class) || sock)
			newcontext.role = scontext->role;
		अन्यथा
			newcontext.role = OBJECT_R_VAL;
	पूर्ण

	/* Set the type to शेष values. */
	अगर (cladatum && cladatum->शेष_type == DEFAULT_SOURCE) अणु
		newcontext.type = scontext->type;
	पूर्ण अन्यथा अगर (cladatum && cladatum->शेष_type == DEFAULT_TARGET) अणु
		newcontext.type = tcontext->type;
	पूर्ण अन्यथा अणु
		अगर ((tclass == policydb->process_class) || sock) अणु
			/* Use the type of process. */
			newcontext.type = scontext->type;
		पूर्ण अन्यथा अणु
			/* Use the type of the related object. */
			newcontext.type = tcontext->type;
		पूर्ण
	पूर्ण

	/* Look क्रम a type transition/member/change rule. */
	avkey.source_type = scontext->type;
	avkey.target_type = tcontext->type;
	avkey.target_class = tclass;
	avkey.specअगरied = specअगरied;
	avdatum = avtab_search(&policydb->te_avtab, &avkey);

	/* If no permanent rule, also check क्रम enabled conditional rules */
	अगर (!avdatum) अणु
		node = avtab_search_node(&policydb->te_cond_avtab, &avkey);
		क्रम (; node; node = avtab_search_node_next(node, specअगरied)) अणु
			अगर (node->key.specअगरied & AVTAB_ENABLED) अणु
				avdatum = &node->datum;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (avdatum) अणु
		/* Use the type from the type transition/member/change rule. */
		newcontext.type = avdatum->u.data;
	पूर्ण

	/* अगर we have a objname this is a file trans check so check those rules */
	अगर (objname)
		filename_compute_type(policydb, &newcontext, scontext->type,
				      tcontext->type, tclass, objname);

	/* Check क्रम class-specअगरic changes. */
	अगर (specअगरied & AVTAB_TRANSITION) अणु
		/* Look क्रम a role transition rule. */
		काष्ठा role_trans_datum *rtd;
		काष्ठा role_trans_key rtk = अणु
			.role = scontext->role,
			.type = tcontext->type,
			.tclass = tclass,
		पूर्ण;

		rtd = policydb_roletr_search(policydb, &rtk);
		अगर (rtd)
			newcontext.role = rtd->new_role;
	पूर्ण

	/* Set the MLS attributes.
	   This is करोne last because it may allocate memory. */
	rc = mls_compute_sid(policydb, scontext, tcontext, tclass, specअगरied,
			     &newcontext, sock);
	अगर (rc)
		जाओ out_unlock;

	/* Check the validity of the context. */
	अगर (!policydb_context_isvalid(policydb, &newcontext)) अणु
		rc = compute_sid_handle_invalid_context(state, policy, sentry,
							tentry, tclass,
							&newcontext);
		अगर (rc)
			जाओ out_unlock;
	पूर्ण
	/* Obtain the sid क्रम the context. */
	rc = sidtab_context_to_sid(sidtab, &newcontext, out_sid);
	अगर (rc == -ESTALE) अणु
		rcu_पढ़ो_unlock();
		context_destroy(&newcontext);
		जाओ retry;
	पूर्ण
out_unlock:
	rcu_पढ़ो_unlock();
	context_destroy(&newcontext);
out:
	वापस rc;
पूर्ण

/**
 * security_transition_sid - Compute the SID क्रम a new subject/object.
 * @ssid: source security identअगरier
 * @tsid: target security identअगरier
 * @tclass: target security class
 * @out_sid: security identअगरier क्रम new subject/object
 *
 * Compute a SID to use क्रम labeling a new subject or object in the
 * class @tclass based on a SID pair (@ssid, @tsid).
 * Return -%EINVAL अगर any of the parameters are invalid, -%ENOMEM
 * अगर insufficient memory is available, or %0 अगर the new SID was
 * computed successfully.
 */
पूर्णांक security_transition_sid(काष्ठा selinux_state *state,
			    u32 ssid, u32 tsid, u16 tclass,
			    स्थिर काष्ठा qstr *qstr, u32 *out_sid)
अणु
	वापस security_compute_sid(state, ssid, tsid, tclass,
				    AVTAB_TRANSITION,
				    qstr ? qstr->name : शून्य, out_sid, true);
पूर्ण

पूर्णांक security_transition_sid_user(काष्ठा selinux_state *state,
				 u32 ssid, u32 tsid, u16 tclass,
				 स्थिर अक्षर *objname, u32 *out_sid)
अणु
	वापस security_compute_sid(state, ssid, tsid, tclass,
				    AVTAB_TRANSITION,
				    objname, out_sid, false);
पूर्ण

/**
 * security_member_sid - Compute the SID क्रम member selection.
 * @ssid: source security identअगरier
 * @tsid: target security identअगरier
 * @tclass: target security class
 * @out_sid: security identअगरier क्रम selected member
 *
 * Compute a SID to use when selecting a member of a polyinstantiated
 * object of class @tclass based on a SID pair (@ssid, @tsid).
 * Return -%EINVAL अगर any of the parameters are invalid, -%ENOMEM
 * अगर insufficient memory is available, or %0 अगर the SID was
 * computed successfully.
 */
पूर्णांक security_member_sid(काष्ठा selinux_state *state,
			u32 ssid,
			u32 tsid,
			u16 tclass,
			u32 *out_sid)
अणु
	वापस security_compute_sid(state, ssid, tsid, tclass,
				    AVTAB_MEMBER, शून्य,
				    out_sid, false);
पूर्ण

/**
 * security_change_sid - Compute the SID क्रम object relabeling.
 * @ssid: source security identअगरier
 * @tsid: target security identअगरier
 * @tclass: target security class
 * @out_sid: security identअगरier क्रम selected member
 *
 * Compute a SID to use क्रम relabeling an object of class @tclass
 * based on a SID pair (@ssid, @tsid).
 * Return -%EINVAL अगर any of the parameters are invalid, -%ENOMEM
 * अगर insufficient memory is available, or %0 अगर the SID was
 * computed successfully.
 */
पूर्णांक security_change_sid(काष्ठा selinux_state *state,
			u32 ssid,
			u32 tsid,
			u16 tclass,
			u32 *out_sid)
अणु
	वापस security_compute_sid(state,
				    ssid, tsid, tclass, AVTAB_CHANGE, शून्य,
				    out_sid, false);
पूर्ण

अटल अंतरभूत पूर्णांक convert_context_handle_invalid_context(
	काष्ठा selinux_state *state,
	काष्ठा policydb *policydb,
	काष्ठा context *context)
अणु
	अक्षर *s;
	u32 len;

	अगर (enक्रमcing_enabled(state))
		वापस -EINVAL;

	अगर (!context_काष्ठा_to_string(policydb, context, &s, &len)) अणु
		pr_warn("SELinux:  Context %s would be invalid if enforcing\n",
			s);
		kमुक्त(s);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Convert the values in the security context
 * काष्ठाure `oldc' from the values specअगरied
 * in the policy `p->oldp' to the values specअगरied
 * in the policy `p->newp', storing the new context
 * in `newc'.  Verअगरy that the context is valid
 * under the new policy.
 */
अटल पूर्णांक convert_context(काष्ठा context *oldc, काष्ठा context *newc, व्योम *p)
अणु
	काष्ठा convert_context_args *args;
	काष्ठा ocontext *oc;
	काष्ठा role_datum *role;
	काष्ठा type_datum *typdatum;
	काष्ठा user_datum *usrdatum;
	अक्षर *s;
	u32 len;
	पूर्णांक rc;

	args = p;

	अगर (oldc->str) अणु
		s = kstrdup(oldc->str, GFP_KERNEL);
		अगर (!s)
			वापस -ENOMEM;

		rc = string_to_context_काष्ठा(args->newp, शून्य, s,
					      newc, SECSID_शून्य);
		अगर (rc == -EINVAL) अणु
			/*
			 * Retain string representation क्रम later mapping.
			 *
			 * IMPORTANT: We need to copy the contents of oldc->str
			 * back पूर्णांकo s again because string_to_context_काष्ठा()
			 * may have garbled it.
			 */
			स_नकल(s, oldc->str, oldc->len);
			context_init(newc);
			newc->str = s;
			newc->len = oldc->len;
			वापस 0;
		पूर्ण
		kमुक्त(s);
		अगर (rc) अणु
			/* Other error condition, e.g. ENOMEM. */
			pr_err("SELinux:   Unable to map context %s, rc = %d.\n",
			       oldc->str, -rc);
			वापस rc;
		पूर्ण
		pr_info("SELinux:  Context %s became valid (mapped).\n",
			oldc->str);
		वापस 0;
	पूर्ण

	context_init(newc);

	/* Convert the user. */
	rc = -EINVAL;
	usrdatum = symtab_search(&args->newp->p_users,
				 sym_name(args->oldp,
					  SYM_USERS, oldc->user - 1));
	अगर (!usrdatum)
		जाओ bad;
	newc->user = usrdatum->value;

	/* Convert the role. */
	rc = -EINVAL;
	role = symtab_search(&args->newp->p_roles,
			     sym_name(args->oldp, SYM_ROLES, oldc->role - 1));
	अगर (!role)
		जाओ bad;
	newc->role = role->value;

	/* Convert the type. */
	rc = -EINVAL;
	typdatum = symtab_search(&args->newp->p_types,
				 sym_name(args->oldp,
					  SYM_TYPES, oldc->type - 1));
	अगर (!typdatum)
		जाओ bad;
	newc->type = typdatum->value;

	/* Convert the MLS fields अगर dealing with MLS policies */
	अगर (args->oldp->mls_enabled && args->newp->mls_enabled) अणु
		rc = mls_convert_context(args->oldp, args->newp, oldc, newc);
		अगर (rc)
			जाओ bad;
	पूर्ण अन्यथा अगर (!args->oldp->mls_enabled && args->newp->mls_enabled) अणु
		/*
		 * Switching between non-MLS and MLS policy:
		 * ensure that the MLS fields of the context क्रम all
		 * existing entries in the sidtab are filled in with a
		 * suitable शेष value, likely taken from one of the
		 * initial SIDs.
		 */
		oc = args->newp->ocontexts[OCON_ISID];
		जबतक (oc && oc->sid[0] != SECINITSID_UNLABELED)
			oc = oc->next;
		rc = -EINVAL;
		अगर (!oc) अणु
			pr_err("SELinux:  unable to look up"
				" the initial SIDs list\n");
			जाओ bad;
		पूर्ण
		rc = mls_range_set(newc, &oc->context[0].range);
		अगर (rc)
			जाओ bad;
	पूर्ण

	/* Check the validity of the new context. */
	अगर (!policydb_context_isvalid(args->newp, newc)) अणु
		rc = convert_context_handle_invalid_context(args->state,
							args->oldp,
							oldc);
		अगर (rc)
			जाओ bad;
	पूर्ण

	वापस 0;
bad:
	/* Map old representation to string and save it. */
	rc = context_काष्ठा_to_string(args->oldp, oldc, &s, &len);
	अगर (rc)
		वापस rc;
	context_destroy(newc);
	newc->str = s;
	newc->len = len;
	pr_info("SELinux:  Context %s became invalid (unmapped).\n",
		newc->str);
	वापस 0;
पूर्ण

अटल व्योम security_load_policycaps(काष्ठा selinux_state *state,
				काष्ठा selinux_policy *policy)
अणु
	काष्ठा policydb *p;
	अचिन्हित पूर्णांक i;
	काष्ठा ebiपंचांगap_node *node;

	p = &policy->policydb;

	क्रम (i = 0; i < ARRAY_SIZE(state->policycap); i++)
		WRITE_ONCE(state->policycap[i],
			ebiपंचांगap_get_bit(&p->policycaps, i));

	क्रम (i = 0; i < ARRAY_SIZE(selinux_policycap_names); i++)
		pr_info("SELinux:  policy capability %s=%d\n",
			selinux_policycap_names[i],
			ebiपंचांगap_get_bit(&p->policycaps, i));

	ebiपंचांगap_क्रम_each_positive_bit(&p->policycaps, node, i) अणु
		अगर (i >= ARRAY_SIZE(selinux_policycap_names))
			pr_info("SELinux:  unknown policy capability %u\n",
				i);
	पूर्ण
पूर्ण

अटल पूर्णांक security_preserve_bools(काष्ठा selinux_policy *oldpolicy,
				काष्ठा selinux_policy *newpolicy);

अटल व्योम selinux_policy_मुक्त(काष्ठा selinux_policy *policy)
अणु
	अगर (!policy)
		वापस;

	sidtab_destroy(policy->sidtab);
	kमुक्त(policy->map.mapping);
	policydb_destroy(&policy->policydb);
	kमुक्त(policy->sidtab);
	kमुक्त(policy);
पूर्ण

अटल व्योम selinux_policy_cond_मुक्त(काष्ठा selinux_policy *policy)
अणु
	cond_policydb_destroy_dup(&policy->policydb);
	kमुक्त(policy);
पूर्ण

व्योम selinux_policy_cancel(काष्ठा selinux_state *state,
			   काष्ठा selinux_load_state *load_state)
अणु
	काष्ठा selinux_policy *oldpolicy;

	oldpolicy = rcu_dereference_रक्षित(state->policy,
					lockdep_is_held(&state->policy_mutex));

	sidtab_cancel_convert(oldpolicy->sidtab);
	selinux_policy_मुक्त(load_state->policy);
	kमुक्त(load_state->convert_data);
पूर्ण

अटल व्योम selinux_notअगरy_policy_change(काष्ठा selinux_state *state,
					u32 seqno)
अणु
	/* Flush बाह्यal caches and notअगरy userspace of policy load */
	avc_ss_reset(state->avc, seqno);
	selnl_notअगरy_policyload(seqno);
	selinux_status_update_policyload(state, seqno);
	selinux_netlbl_cache_invalidate();
	selinux_xfrm_notअगरy_policyload();
	selinux_ima_measure_state_locked(state);
पूर्ण

व्योम selinux_policy_commit(काष्ठा selinux_state *state,
			   काष्ठा selinux_load_state *load_state)
अणु
	काष्ठा selinux_policy *oldpolicy, *newpolicy = load_state->policy;
	अचिन्हित दीर्घ flags;
	u32 seqno;

	oldpolicy = rcu_dereference_रक्षित(state->policy,
					lockdep_is_held(&state->policy_mutex));

	/* If चयनing between dअगरferent policy types, log MLS status */
	अगर (oldpolicy) अणु
		अगर (oldpolicy->policydb.mls_enabled && !newpolicy->policydb.mls_enabled)
			pr_info("SELinux: Disabling MLS support...\n");
		अन्यथा अगर (!oldpolicy->policydb.mls_enabled && newpolicy->policydb.mls_enabled)
			pr_info("SELinux: Enabling MLS support...\n");
	पूर्ण

	/* Set latest granting seqno क्रम new policy. */
	अगर (oldpolicy)
		newpolicy->latest_granting = oldpolicy->latest_granting + 1;
	अन्यथा
		newpolicy->latest_granting = 1;
	seqno = newpolicy->latest_granting;

	/* Install the new policy. */
	अगर (oldpolicy) अणु
		sidtab_मुक्तze_begin(oldpolicy->sidtab, &flags);
		rcu_assign_poपूर्णांकer(state->policy, newpolicy);
		sidtab_मुक्तze_end(oldpolicy->sidtab, &flags);
	पूर्ण अन्यथा अणु
		rcu_assign_poपूर्णांकer(state->policy, newpolicy);
	पूर्ण

	/* Load the policycaps from the new policy */
	security_load_policycaps(state, newpolicy);

	अगर (!selinux_initialized(state)) अणु
		/*
		 * After first policy load, the security server is
		 * marked as initialized and पढ़ोy to handle requests and
		 * any objects created prior to policy load are then labeled.
		 */
		selinux_mark_initialized(state);
		selinux_complete_init();
	पूर्ण

	/* Free the old policy */
	synchronize_rcu();
	selinux_policy_मुक्त(oldpolicy);
	kमुक्त(load_state->convert_data);

	/* Notअगरy others of the policy change */
	selinux_notअगरy_policy_change(state, seqno);
पूर्ण

/**
 * security_load_policy - Load a security policy configuration.
 * @data: binary policy data
 * @len: length of data in bytes
 *
 * Load a new set of security policy configuration data,
 * validate it and convert the SID table as necessary.
 * This function will flush the access vector cache after
 * loading the new policy.
 */
पूर्णांक security_load_policy(काष्ठा selinux_state *state, व्योम *data, माप_प्रकार len,
			 काष्ठा selinux_load_state *load_state)
अणु
	काष्ठा selinux_policy *newpolicy, *oldpolicy;
	काष्ठा selinux_policy_convert_data *convert_data;
	पूर्णांक rc = 0;
	काष्ठा policy_file file = अणु data, len पूर्ण, *fp = &file;

	newpolicy = kzalloc(माप(*newpolicy), GFP_KERNEL);
	अगर (!newpolicy)
		वापस -ENOMEM;

	newpolicy->sidtab = kzalloc(माप(*newpolicy->sidtab), GFP_KERNEL);
	अगर (!newpolicy->sidtab) अणु
		rc = -ENOMEM;
		जाओ err_policy;
	पूर्ण

	rc = policydb_पढ़ो(&newpolicy->policydb, fp);
	अगर (rc)
		जाओ err_sidtab;

	newpolicy->policydb.len = len;
	rc = selinux_set_mapping(&newpolicy->policydb, secclass_map,
				&newpolicy->map);
	अगर (rc)
		जाओ err_policydb;

	rc = policydb_load_isids(&newpolicy->policydb, newpolicy->sidtab);
	अगर (rc) अणु
		pr_err("SELinux:  unable to load the initial SIDs\n");
		जाओ err_mapping;
	पूर्ण

	अगर (!selinux_initialized(state)) अणु
		/* First policy load, so no need to preserve state from old policy */
		load_state->policy = newpolicy;
		load_state->convert_data = शून्य;
		वापस 0;
	पूर्ण

	oldpolicy = rcu_dereference_रक्षित(state->policy,
					lockdep_is_held(&state->policy_mutex));

	/* Preserve active boolean values from the old policy */
	rc = security_preserve_bools(oldpolicy, newpolicy);
	अगर (rc) अणु
		pr_err("SELinux:  unable to preserve booleans\n");
		जाओ err_मुक्त_isids;
	पूर्ण

	convert_data = kदो_स्मृति(माप(*convert_data), GFP_KERNEL);
	अगर (!convert_data) अणु
		rc = -ENOMEM;
		जाओ err_मुक्त_isids;
	पूर्ण

	/*
	 * Convert the पूर्णांकernal representations of contexts
	 * in the new SID table.
	 */
	convert_data->args.state = state;
	convert_data->args.oldp = &oldpolicy->policydb;
	convert_data->args.newp = &newpolicy->policydb;

	convert_data->sidtab_params.func = convert_context;
	convert_data->sidtab_params.args = &convert_data->args;
	convert_data->sidtab_params.target = newpolicy->sidtab;

	rc = sidtab_convert(oldpolicy->sidtab, &convert_data->sidtab_params);
	अगर (rc) अणु
		pr_err("SELinux:  unable to convert the internal"
			" representation of contexts in the new SID"
			" table\n");
		जाओ err_मुक्त_convert_data;
	पूर्ण

	load_state->policy = newpolicy;
	load_state->convert_data = convert_data;
	वापस 0;

err_मुक्त_convert_data:
	kमुक्त(convert_data);
err_मुक्त_isids:
	sidtab_destroy(newpolicy->sidtab);
err_mapping:
	kमुक्त(newpolicy->map.mapping);
err_policydb:
	policydb_destroy(&newpolicy->policydb);
err_sidtab:
	kमुक्त(newpolicy->sidtab);
err_policy:
	kमुक्त(newpolicy);

	वापस rc;
पूर्ण

/**
 * security_port_sid - Obtain the SID क्रम a port.
 * @protocol: protocol number
 * @port: port number
 * @out_sid: security identअगरier
 */
पूर्णांक security_port_sid(काष्ठा selinux_state *state,
		      u8 protocol, u16 port, u32 *out_sid)
अणु
	काष्ठा selinux_policy *policy;
	काष्ठा policydb *policydb;
	काष्ठा sidtab *sidtab;
	काष्ठा ocontext *c;
	पूर्णांक rc;

	अगर (!selinux_initialized(state)) अणु
		*out_sid = SECINITSID_PORT;
		वापस 0;
	पूर्ण

retry:
	rc = 0;
	rcu_पढ़ो_lock();
	policy = rcu_dereference(state->policy);
	policydb = &policy->policydb;
	sidtab = policy->sidtab;

	c = policydb->ocontexts[OCON_PORT];
	जबतक (c) अणु
		अगर (c->u.port.protocol == protocol &&
		    c->u.port.low_port <= port &&
		    c->u.port.high_port >= port)
			अवरोध;
		c = c->next;
	पूर्ण

	अगर (c) अणु
		अगर (!c->sid[0]) अणु
			rc = sidtab_context_to_sid(sidtab, &c->context[0],
						   &c->sid[0]);
			अगर (rc == -ESTALE) अणु
				rcu_पढ़ो_unlock();
				जाओ retry;
			पूर्ण
			अगर (rc)
				जाओ out;
		पूर्ण
		*out_sid = c->sid[0];
	पूर्ण अन्यथा अणु
		*out_sid = SECINITSID_PORT;
	पूर्ण

out:
	rcu_पढ़ो_unlock();
	वापस rc;
पूर्ण

/**
 * security_pkey_sid - Obtain the SID क्रम a pkey.
 * @subnet_prefix: Subnet Prefix
 * @pkey_num: pkey number
 * @out_sid: security identअगरier
 */
पूर्णांक security_ib_pkey_sid(काष्ठा selinux_state *state,
			 u64 subnet_prefix, u16 pkey_num, u32 *out_sid)
अणु
	काष्ठा selinux_policy *policy;
	काष्ठा policydb *policydb;
	काष्ठा sidtab *sidtab;
	काष्ठा ocontext *c;
	पूर्णांक rc;

	अगर (!selinux_initialized(state)) अणु
		*out_sid = SECINITSID_UNLABELED;
		वापस 0;
	पूर्ण

retry:
	rc = 0;
	rcu_पढ़ो_lock();
	policy = rcu_dereference(state->policy);
	policydb = &policy->policydb;
	sidtab = policy->sidtab;

	c = policydb->ocontexts[OCON_IBPKEY];
	जबतक (c) अणु
		अगर (c->u.ibpkey.low_pkey <= pkey_num &&
		    c->u.ibpkey.high_pkey >= pkey_num &&
		    c->u.ibpkey.subnet_prefix == subnet_prefix)
			अवरोध;

		c = c->next;
	पूर्ण

	अगर (c) अणु
		अगर (!c->sid[0]) अणु
			rc = sidtab_context_to_sid(sidtab,
						   &c->context[0],
						   &c->sid[0]);
			अगर (rc == -ESTALE) अणु
				rcu_पढ़ो_unlock();
				जाओ retry;
			पूर्ण
			अगर (rc)
				जाओ out;
		पूर्ण
		*out_sid = c->sid[0];
	पूर्ण अन्यथा
		*out_sid = SECINITSID_UNLABELED;

out:
	rcu_पढ़ो_unlock();
	वापस rc;
पूर्ण

/**
 * security_ib_endport_sid - Obtain the SID क्रम a subnet management पूर्णांकerface.
 * @dev_name: device name
 * @port: port number
 * @out_sid: security identअगरier
 */
पूर्णांक security_ib_endport_sid(काष्ठा selinux_state *state,
			    स्थिर अक्षर *dev_name, u8 port_num, u32 *out_sid)
अणु
	काष्ठा selinux_policy *policy;
	काष्ठा policydb *policydb;
	काष्ठा sidtab *sidtab;
	काष्ठा ocontext *c;
	पूर्णांक rc;

	अगर (!selinux_initialized(state)) अणु
		*out_sid = SECINITSID_UNLABELED;
		वापस 0;
	पूर्ण

retry:
	rc = 0;
	rcu_पढ़ो_lock();
	policy = rcu_dereference(state->policy);
	policydb = &policy->policydb;
	sidtab = policy->sidtab;

	c = policydb->ocontexts[OCON_IBENDPORT];
	जबतक (c) अणु
		अगर (c->u.ibendport.port == port_num &&
		    !म_भेदन(c->u.ibendport.dev_name,
			     dev_name,
			     IB_DEVICE_NAME_MAX))
			अवरोध;

		c = c->next;
	पूर्ण

	अगर (c) अणु
		अगर (!c->sid[0]) अणु
			rc = sidtab_context_to_sid(sidtab, &c->context[0],
						   &c->sid[0]);
			अगर (rc == -ESTALE) अणु
				rcu_पढ़ो_unlock();
				जाओ retry;
			पूर्ण
			अगर (rc)
				जाओ out;
		पूर्ण
		*out_sid = c->sid[0];
	पूर्ण अन्यथा
		*out_sid = SECINITSID_UNLABELED;

out:
	rcu_पढ़ो_unlock();
	वापस rc;
पूर्ण

/**
 * security_netअगर_sid - Obtain the SID क्रम a network पूर्णांकerface.
 * @name: पूर्णांकerface name
 * @अगर_sid: पूर्णांकerface SID
 */
पूर्णांक security_netअगर_sid(काष्ठा selinux_state *state,
		       अक्षर *name, u32 *अगर_sid)
अणु
	काष्ठा selinux_policy *policy;
	काष्ठा policydb *policydb;
	काष्ठा sidtab *sidtab;
	पूर्णांक rc;
	काष्ठा ocontext *c;

	अगर (!selinux_initialized(state)) अणु
		*अगर_sid = SECINITSID_NETIF;
		वापस 0;
	पूर्ण

retry:
	rc = 0;
	rcu_पढ़ो_lock();
	policy = rcu_dereference(state->policy);
	policydb = &policy->policydb;
	sidtab = policy->sidtab;

	c = policydb->ocontexts[OCON_NETIF];
	जबतक (c) अणु
		अगर (म_भेद(name, c->u.name) == 0)
			अवरोध;
		c = c->next;
	पूर्ण

	अगर (c) अणु
		अगर (!c->sid[0] || !c->sid[1]) अणु
			rc = sidtab_context_to_sid(sidtab, &c->context[0],
						   &c->sid[0]);
			अगर (rc == -ESTALE) अणु
				rcu_पढ़ो_unlock();
				जाओ retry;
			पूर्ण
			अगर (rc)
				जाओ out;
			rc = sidtab_context_to_sid(sidtab, &c->context[1],
						   &c->sid[1]);
			अगर (rc == -ESTALE) अणु
				rcu_पढ़ो_unlock();
				जाओ retry;
			पूर्ण
			अगर (rc)
				जाओ out;
		पूर्ण
		*अगर_sid = c->sid[0];
	पूर्ण अन्यथा
		*अगर_sid = SECINITSID_NETIF;

out:
	rcu_पढ़ो_unlock();
	वापस rc;
पूर्ण

अटल पूर्णांक match_ipv6_addrmask(u32 *input, u32 *addr, u32 *mask)
अणु
	पूर्णांक i, fail = 0;

	क्रम (i = 0; i < 4; i++)
		अगर (addr[i] != (input[i] & mask[i])) अणु
			fail = 1;
			अवरोध;
		पूर्ण

	वापस !fail;
पूर्ण

/**
 * security_node_sid - Obtain the SID क्रम a node (host).
 * @करोमुख्य: communication करोमुख्य aka address family
 * @addrp: address
 * @addrlen: address length in bytes
 * @out_sid: security identअगरier
 */
पूर्णांक security_node_sid(काष्ठा selinux_state *state,
		      u16 करोमुख्य,
		      व्योम *addrp,
		      u32 addrlen,
		      u32 *out_sid)
अणु
	काष्ठा selinux_policy *policy;
	काष्ठा policydb *policydb;
	काष्ठा sidtab *sidtab;
	पूर्णांक rc;
	काष्ठा ocontext *c;

	अगर (!selinux_initialized(state)) अणु
		*out_sid = SECINITSID_NODE;
		वापस 0;
	पूर्ण

retry:
	rcu_पढ़ो_lock();
	policy = rcu_dereference(state->policy);
	policydb = &policy->policydb;
	sidtab = policy->sidtab;

	चयन (करोमुख्य) अणु
	हाल AF_INET: अणु
		u32 addr;

		rc = -EINVAL;
		अगर (addrlen != माप(u32))
			जाओ out;

		addr = *((u32 *)addrp);

		c = policydb->ocontexts[OCON_NODE];
		जबतक (c) अणु
			अगर (c->u.node.addr == (addr & c->u.node.mask))
				अवरोध;
			c = c->next;
		पूर्ण
		अवरोध;
	पूर्ण

	हाल AF_INET6:
		rc = -EINVAL;
		अगर (addrlen != माप(u64) * 2)
			जाओ out;
		c = policydb->ocontexts[OCON_NODE6];
		जबतक (c) अणु
			अगर (match_ipv6_addrmask(addrp, c->u.node6.addr,
						c->u.node6.mask))
				अवरोध;
			c = c->next;
		पूर्ण
		अवरोध;

	शेष:
		rc = 0;
		*out_sid = SECINITSID_NODE;
		जाओ out;
	पूर्ण

	अगर (c) अणु
		अगर (!c->sid[0]) अणु
			rc = sidtab_context_to_sid(sidtab,
						   &c->context[0],
						   &c->sid[0]);
			अगर (rc == -ESTALE) अणु
				rcu_पढ़ो_unlock();
				जाओ retry;
			पूर्ण
			अगर (rc)
				जाओ out;
		पूर्ण
		*out_sid = c->sid[0];
	पूर्ण अन्यथा अणु
		*out_sid = SECINITSID_NODE;
	पूर्ण

	rc = 0;
out:
	rcu_पढ़ो_unlock();
	वापस rc;
पूर्ण

#घोषणा SIDS_NEL 25

/**
 * security_get_user_sids - Obtain reachable SIDs क्रम a user.
 * @fromsid: starting SID
 * @username: username
 * @sids: array of reachable SIDs क्रम user
 * @nel: number of elements in @sids
 *
 * Generate the set of SIDs क्रम legal security contexts
 * क्रम a given user that can be reached by @fromsid.
 * Set *@sids to poपूर्णांक to a dynamically allocated
 * array containing the set of SIDs.  Set *@nel to the
 * number of elements in the array.
 */

पूर्णांक security_get_user_sids(काष्ठा selinux_state *state,
			   u32 fromsid,
			   अक्षर *username,
			   u32 **sids,
			   u32 *nel)
अणु
	काष्ठा selinux_policy *policy;
	काष्ठा policydb *policydb;
	काष्ठा sidtab *sidtab;
	काष्ठा context *fromcon, usercon;
	u32 *mysids = शून्य, *mysids2, sid;
	u32 i, j, mynel, maxnel = SIDS_NEL;
	काष्ठा user_datum *user;
	काष्ठा role_datum *role;
	काष्ठा ebiपंचांगap_node *rnode, *tnode;
	पूर्णांक rc;

	*sids = शून्य;
	*nel = 0;

	अगर (!selinux_initialized(state))
		वापस 0;

	mysids = kसुस्मृति(maxnel, माप(*mysids), GFP_KERNEL);
	अगर (!mysids)
		वापस -ENOMEM;

retry:
	mynel = 0;
	rcu_पढ़ो_lock();
	policy = rcu_dereference(state->policy);
	policydb = &policy->policydb;
	sidtab = policy->sidtab;

	context_init(&usercon);

	rc = -EINVAL;
	fromcon = sidtab_search(sidtab, fromsid);
	अगर (!fromcon)
		जाओ out_unlock;

	rc = -EINVAL;
	user = symtab_search(&policydb->p_users, username);
	अगर (!user)
		जाओ out_unlock;

	usercon.user = user->value;

	ebiपंचांगap_क्रम_each_positive_bit(&user->roles, rnode, i) अणु
		role = policydb->role_val_to_काष्ठा[i];
		usercon.role = i + 1;
		ebiपंचांगap_क्रम_each_positive_bit(&role->types, tnode, j) अणु
			usercon.type = j + 1;

			अगर (mls_setup_user_range(policydb, fromcon, user,
						 &usercon))
				जारी;

			rc = sidtab_context_to_sid(sidtab, &usercon, &sid);
			अगर (rc == -ESTALE) अणु
				rcu_पढ़ो_unlock();
				जाओ retry;
			पूर्ण
			अगर (rc)
				जाओ out_unlock;
			अगर (mynel < maxnel) अणु
				mysids[mynel++] = sid;
			पूर्ण अन्यथा अणु
				rc = -ENOMEM;
				maxnel += SIDS_NEL;
				mysids2 = kसुस्मृति(maxnel, माप(*mysids2), GFP_ATOMIC);
				अगर (!mysids2)
					जाओ out_unlock;
				स_नकल(mysids2, mysids, mynel * माप(*mysids2));
				kमुक्त(mysids);
				mysids = mysids2;
				mysids[mynel++] = sid;
			पूर्ण
		पूर्ण
	पूर्ण
	rc = 0;
out_unlock:
	rcu_पढ़ो_unlock();
	अगर (rc || !mynel) अणु
		kमुक्त(mysids);
		वापस rc;
	पूर्ण

	rc = -ENOMEM;
	mysids2 = kसुस्मृति(mynel, माप(*mysids2), GFP_KERNEL);
	अगर (!mysids2) अणु
		kमुक्त(mysids);
		वापस rc;
	पूर्ण
	क्रम (i = 0, j = 0; i < mynel; i++) अणु
		काष्ठा av_decision dummy_avd;
		rc = avc_has_perm_noaudit(state,
					  fromsid, mysids[i],
					  SECCLASS_PROCESS, /* kernel value */
					  PROCESS__TRANSITION, AVC_STRICT,
					  &dummy_avd);
		अगर (!rc)
			mysids2[j++] = mysids[i];
		cond_resched();
	पूर्ण
	kमुक्त(mysids);
	*sids = mysids2;
	*nel = j;
	वापस 0;
पूर्ण

/**
 * __security_genfs_sid - Helper to obtain a SID क्रम a file in a fileप्रणाली
 * @fstype: fileप्रणाली type
 * @path: path from root of mount
 * @sclass: file security class
 * @sid: SID क्रम path
 *
 * Obtain a SID to use क्रम a file in a fileप्रणाली that
 * cannot support xattr or use a fixed labeling behavior like
 * transition SIDs or task SIDs.
 *
 * WARNING: This function may वापस -ESTALE, indicating that the caller
 * must retry the operation after re-acquiring the policy poपूर्णांकer!
 */
अटल अंतरभूत पूर्णांक __security_genfs_sid(काष्ठा selinux_policy *policy,
				       स्थिर अक्षर *fstype,
				       अक्षर *path,
				       u16 orig_sclass,
				       u32 *sid)
अणु
	काष्ठा policydb *policydb = &policy->policydb;
	काष्ठा sidtab *sidtab = policy->sidtab;
	पूर्णांक len;
	u16 sclass;
	काष्ठा genfs *genfs;
	काष्ठा ocontext *c;
	पूर्णांक rc, cmp = 0;

	जबतक (path[0] == '/' && path[1] == '/')
		path++;

	sclass = unmap_class(&policy->map, orig_sclass);
	*sid = SECINITSID_UNLABELED;

	क्रम (genfs = policydb->genfs; genfs; genfs = genfs->next) अणु
		cmp = म_भेद(fstype, genfs->fstype);
		अगर (cmp <= 0)
			अवरोध;
	पूर्ण

	rc = -ENOENT;
	अगर (!genfs || cmp)
		जाओ out;

	क्रम (c = genfs->head; c; c = c->next) अणु
		len = म_माप(c->u.name);
		अगर ((!c->v.sclass || sclass == c->v.sclass) &&
		    (म_भेदन(c->u.name, path, len) == 0))
			अवरोध;
	पूर्ण

	rc = -ENOENT;
	अगर (!c)
		जाओ out;

	अगर (!c->sid[0]) अणु
		rc = sidtab_context_to_sid(sidtab, &c->context[0], &c->sid[0]);
		अगर (rc)
			जाओ out;
	पूर्ण

	*sid = c->sid[0];
	rc = 0;
out:
	वापस rc;
पूर्ण

/**
 * security_genfs_sid - Obtain a SID क्रम a file in a fileप्रणाली
 * @fstype: fileप्रणाली type
 * @path: path from root of mount
 * @sclass: file security class
 * @sid: SID क्रम path
 *
 * Acquire policy_rwlock beक्रमe calling __security_genfs_sid() and release
 * it afterward.
 */
पूर्णांक security_genfs_sid(काष्ठा selinux_state *state,
		       स्थिर अक्षर *fstype,
		       अक्षर *path,
		       u16 orig_sclass,
		       u32 *sid)
अणु
	काष्ठा selinux_policy *policy;
	पूर्णांक retval;

	अगर (!selinux_initialized(state)) अणु
		*sid = SECINITSID_UNLABELED;
		वापस 0;
	पूर्ण

	करो अणु
		rcu_पढ़ो_lock();
		policy = rcu_dereference(state->policy);
		retval = __security_genfs_sid(policy, fstype, path,
					      orig_sclass, sid);
		rcu_पढ़ो_unlock();
	पूर्ण जबतक (retval == -ESTALE);
	वापस retval;
पूर्ण

पूर्णांक selinux_policy_genfs_sid(काष्ठा selinux_policy *policy,
			स्थिर अक्षर *fstype,
			अक्षर *path,
			u16 orig_sclass,
			u32 *sid)
अणु
	/* no lock required, policy is not yet accessible by other thपढ़ोs */
	वापस __security_genfs_sid(policy, fstype, path, orig_sclass, sid);
पूर्ण

/**
 * security_fs_use - Determine how to handle labeling क्रम a fileप्रणाली.
 * @sb: superblock in question
 */
पूर्णांक security_fs_use(काष्ठा selinux_state *state, काष्ठा super_block *sb)
अणु
	काष्ठा selinux_policy *policy;
	काष्ठा policydb *policydb;
	काष्ठा sidtab *sidtab;
	पूर्णांक rc;
	काष्ठा ocontext *c;
	काष्ठा superblock_security_काष्ठा *sbsec = selinux_superblock(sb);
	स्थिर अक्षर *fstype = sb->s_type->name;

	अगर (!selinux_initialized(state)) अणु
		sbsec->behavior = SECURITY_FS_USE_NONE;
		sbsec->sid = SECINITSID_UNLABELED;
		वापस 0;
	पूर्ण

retry:
	rc = 0;
	rcu_पढ़ो_lock();
	policy = rcu_dereference(state->policy);
	policydb = &policy->policydb;
	sidtab = policy->sidtab;

	c = policydb->ocontexts[OCON_FSUSE];
	जबतक (c) अणु
		अगर (म_भेद(fstype, c->u.name) == 0)
			अवरोध;
		c = c->next;
	पूर्ण

	अगर (c) अणु
		sbsec->behavior = c->v.behavior;
		अगर (!c->sid[0]) अणु
			rc = sidtab_context_to_sid(sidtab, &c->context[0],
						   &c->sid[0]);
			अगर (rc == -ESTALE) अणु
				rcu_पढ़ो_unlock();
				जाओ retry;
			पूर्ण
			अगर (rc)
				जाओ out;
		पूर्ण
		sbsec->sid = c->sid[0];
	पूर्ण अन्यथा अणु
		rc = __security_genfs_sid(policy, fstype, "/",
					SECCLASS_सूची, &sbsec->sid);
		अगर (rc == -ESTALE) अणु
			rcu_पढ़ो_unlock();
			जाओ retry;
		पूर्ण
		अगर (rc) अणु
			sbsec->behavior = SECURITY_FS_USE_NONE;
			rc = 0;
		पूर्ण अन्यथा अणु
			sbsec->behavior = SECURITY_FS_USE_GENFS;
		पूर्ण
	पूर्ण

out:
	rcu_पढ़ो_unlock();
	वापस rc;
पूर्ण

पूर्णांक security_get_bools(काष्ठा selinux_policy *policy,
		       u32 *len, अक्षर ***names, पूर्णांक **values)
अणु
	काष्ठा policydb *policydb;
	u32 i;
	पूर्णांक rc;

	policydb = &policy->policydb;

	*names = शून्य;
	*values = शून्य;

	rc = 0;
	*len = policydb->p_bools.nprim;
	अगर (!*len)
		जाओ out;

	rc = -ENOMEM;
	*names = kसुस्मृति(*len, माप(अक्षर *), GFP_ATOMIC);
	अगर (!*names)
		जाओ err;

	rc = -ENOMEM;
	*values = kसुस्मृति(*len, माप(पूर्णांक), GFP_ATOMIC);
	अगर (!*values)
		जाओ err;

	क्रम (i = 0; i < *len; i++) अणु
		(*values)[i] = policydb->bool_val_to_काष्ठा[i]->state;

		rc = -ENOMEM;
		(*names)[i] = kstrdup(sym_name(policydb, SYM_BOOLS, i),
				      GFP_ATOMIC);
		अगर (!(*names)[i])
			जाओ err;
	पूर्ण
	rc = 0;
out:
	वापस rc;
err:
	अगर (*names) अणु
		क्रम (i = 0; i < *len; i++)
			kमुक्त((*names)[i]);
		kमुक्त(*names);
	पूर्ण
	kमुक्त(*values);
	*len = 0;
	*names = शून्य;
	*values = शून्य;
	जाओ out;
पूर्ण


पूर्णांक security_set_bools(काष्ठा selinux_state *state, u32 len, पूर्णांक *values)
अणु
	काष्ठा selinux_policy *newpolicy, *oldpolicy;
	पूर्णांक rc;
	u32 i, seqno = 0;

	अगर (!selinux_initialized(state))
		वापस -EINVAL;

	oldpolicy = rcu_dereference_रक्षित(state->policy,
					lockdep_is_held(&state->policy_mutex));

	/* Consistency check on number of booleans, should never fail */
	अगर (WARN_ON(len != oldpolicy->policydb.p_bools.nprim))
		वापस -EINVAL;

	newpolicy = kmemdup(oldpolicy, माप(*newpolicy), GFP_KERNEL);
	अगर (!newpolicy)
		वापस -ENOMEM;

	/*
	 * Deep copy only the parts of the policydb that might be
	 * modअगरied as a result of changing booleans.
	 */
	rc = cond_policydb_dup(&newpolicy->policydb, &oldpolicy->policydb);
	अगर (rc) अणु
		kमुक्त(newpolicy);
		वापस -ENOMEM;
	पूर्ण

	/* Update the boolean states in the copy */
	क्रम (i = 0; i < len; i++) अणु
		पूर्णांक new_state = !!values[i];
		पूर्णांक old_state = newpolicy->policydb.bool_val_to_काष्ठा[i]->state;

		अगर (new_state != old_state) अणु
			audit_log(audit_context(), GFP_ATOMIC,
				AUDIT_MAC_CONFIG_CHANGE,
				"bool=%s val=%d old_val=%d auid=%u ses=%u",
				sym_name(&newpolicy->policydb, SYM_BOOLS, i),
				new_state,
				old_state,
				from_kuid(&init_user_ns, audit_get_loginuid(current)),
				audit_get_sessionid(current));
			newpolicy->policydb.bool_val_to_काष्ठा[i]->state = new_state;
		पूर्ण
	पूर्ण

	/* Re-evaluate the conditional rules in the copy */
	evaluate_cond_nodes(&newpolicy->policydb);

	/* Set latest granting seqno क्रम new policy */
	newpolicy->latest_granting = oldpolicy->latest_granting + 1;
	seqno = newpolicy->latest_granting;

	/* Install the new policy */
	rcu_assign_poपूर्णांकer(state->policy, newpolicy);

	/*
	 * Free the conditional portions of the old policydb
	 * that were copied क्रम the new policy, and the oldpolicy
	 * काष्ठाure itself but not what it references.
	 */
	synchronize_rcu();
	selinux_policy_cond_मुक्त(oldpolicy);

	/* Notअगरy others of the policy change */
	selinux_notअगरy_policy_change(state, seqno);
	वापस 0;
पूर्ण

पूर्णांक security_get_bool_value(काष्ठा selinux_state *state,
			    u32 index)
अणु
	काष्ठा selinux_policy *policy;
	काष्ठा policydb *policydb;
	पूर्णांक rc;
	u32 len;

	अगर (!selinux_initialized(state))
		वापस 0;

	rcu_पढ़ो_lock();
	policy = rcu_dereference(state->policy);
	policydb = &policy->policydb;

	rc = -EFAULT;
	len = policydb->p_bools.nprim;
	अगर (index >= len)
		जाओ out;

	rc = policydb->bool_val_to_काष्ठा[index]->state;
out:
	rcu_पढ़ो_unlock();
	वापस rc;
पूर्ण

अटल पूर्णांक security_preserve_bools(काष्ठा selinux_policy *oldpolicy,
				काष्ठा selinux_policy *newpolicy)
अणु
	पूर्णांक rc, *bvalues = शून्य;
	अक्षर **bnames = शून्य;
	काष्ठा cond_bool_datum *booldatum;
	u32 i, nbools = 0;

	rc = security_get_bools(oldpolicy, &nbools, &bnames, &bvalues);
	अगर (rc)
		जाओ out;
	क्रम (i = 0; i < nbools; i++) अणु
		booldatum = symtab_search(&newpolicy->policydb.p_bools,
					bnames[i]);
		अगर (booldatum)
			booldatum->state = bvalues[i];
	पूर्ण
	evaluate_cond_nodes(&newpolicy->policydb);

out:
	अगर (bnames) अणु
		क्रम (i = 0; i < nbools; i++)
			kमुक्त(bnames[i]);
	पूर्ण
	kमुक्त(bnames);
	kमुक्त(bvalues);
	वापस rc;
पूर्ण

/*
 * security_sid_mls_copy() - computes a new sid based on the given
 * sid and the mls portion of mls_sid.
 */
पूर्णांक security_sid_mls_copy(काष्ठा selinux_state *state,
			  u32 sid, u32 mls_sid, u32 *new_sid)
अणु
	काष्ठा selinux_policy *policy;
	काष्ठा policydb *policydb;
	काष्ठा sidtab *sidtab;
	काष्ठा context *context1;
	काष्ठा context *context2;
	काष्ठा context newcon;
	अक्षर *s;
	u32 len;
	पूर्णांक rc;

	अगर (!selinux_initialized(state)) अणु
		*new_sid = sid;
		वापस 0;
	पूर्ण

retry:
	rc = 0;
	context_init(&newcon);

	rcu_पढ़ो_lock();
	policy = rcu_dereference(state->policy);
	policydb = &policy->policydb;
	sidtab = policy->sidtab;

	अगर (!policydb->mls_enabled) अणु
		*new_sid = sid;
		जाओ out_unlock;
	पूर्ण

	rc = -EINVAL;
	context1 = sidtab_search(sidtab, sid);
	अगर (!context1) अणु
		pr_err("SELinux: %s:  unrecognized SID %d\n",
			__func__, sid);
		जाओ out_unlock;
	पूर्ण

	rc = -EINVAL;
	context2 = sidtab_search(sidtab, mls_sid);
	अगर (!context2) अणु
		pr_err("SELinux: %s:  unrecognized SID %d\n",
			__func__, mls_sid);
		जाओ out_unlock;
	पूर्ण

	newcon.user = context1->user;
	newcon.role = context1->role;
	newcon.type = context1->type;
	rc = mls_context_cpy(&newcon, context2);
	अगर (rc)
		जाओ out_unlock;

	/* Check the validity of the new context. */
	अगर (!policydb_context_isvalid(policydb, &newcon)) अणु
		rc = convert_context_handle_invalid_context(state, policydb,
							&newcon);
		अगर (rc) अणु
			अगर (!context_काष्ठा_to_string(policydb, &newcon, &s,
						      &len)) अणु
				काष्ठा audit_buffer *ab;

				ab = audit_log_start(audit_context(),
						     GFP_ATOMIC,
						     AUDIT_SELINUX_ERR);
				audit_log_क्रमmat(ab,
						 "op=security_sid_mls_copy invalid_context=");
				/* करोn't record NUL with untrusted strings */
				audit_log_n_untrustedstring(ab, s, len - 1);
				audit_log_end(ab);
				kमुक्त(s);
			पूर्ण
			जाओ out_unlock;
		पूर्ण
	पूर्ण
	rc = sidtab_context_to_sid(sidtab, &newcon, new_sid);
	अगर (rc == -ESTALE) अणु
		rcu_पढ़ो_unlock();
		context_destroy(&newcon);
		जाओ retry;
	पूर्ण
out_unlock:
	rcu_पढ़ो_unlock();
	context_destroy(&newcon);
	वापस rc;
पूर्ण

/**
 * security_net_peersid_resolve - Compare and resolve two network peer SIDs
 * @nlbl_sid: NetLabel SID
 * @nlbl_type: NetLabel labeling protocol type
 * @xfrm_sid: XFRM SID
 *
 * Description:
 * Compare the @nlbl_sid and @xfrm_sid values and अगर the two SIDs can be
 * resolved पूर्णांकo a single SID it is वापसed via @peer_sid and the function
 * वापसs zero.  Otherwise @peer_sid is set to SECSID_शून्य and the function
 * वापसs a negative value.  A table summarizing the behavior is below:
 *
 *                                 | function वापस |      @sid
 *   ------------------------------+-----------------+-----------------
 *   no peer labels                |        0        |    SECSID_शून्य
 *   single peer label             |        0        |    <peer_label>
 *   multiple, consistent labels   |        0        |    <peer_label>
 *   multiple, inconsistent labels |    -<त्रुटि_सं>     |    SECSID_शून्य
 *
 */
पूर्णांक security_net_peersid_resolve(काष्ठा selinux_state *state,
				 u32 nlbl_sid, u32 nlbl_type,
				 u32 xfrm_sid,
				 u32 *peer_sid)
अणु
	काष्ठा selinux_policy *policy;
	काष्ठा policydb *policydb;
	काष्ठा sidtab *sidtab;
	पूर्णांक rc;
	काष्ठा context *nlbl_ctx;
	काष्ठा context *xfrm_ctx;

	*peer_sid = SECSID_शून्य;

	/* handle the common (which also happens to be the set of easy) हालs
	 * right away, these two अगर statements catch everything involving a
	 * single or असलent peer SID/label */
	अगर (xfrm_sid == SECSID_शून्य) अणु
		*peer_sid = nlbl_sid;
		वापस 0;
	पूर्ण
	/* NOTE: an nlbl_type == NETLBL_NLTYPE_UNLABELED is a "fallback" label
	 * and is treated as अगर nlbl_sid == SECSID_शून्य when a XFRM SID/label
	 * is present */
	अगर (nlbl_sid == SECSID_शून्य || nlbl_type == NETLBL_NLTYPE_UNLABELED) अणु
		*peer_sid = xfrm_sid;
		वापस 0;
	पूर्ण

	अगर (!selinux_initialized(state))
		वापस 0;

	rcu_पढ़ो_lock();
	policy = rcu_dereference(state->policy);
	policydb = &policy->policydb;
	sidtab = policy->sidtab;

	/*
	 * We करोn't need to check initialized here since the only way both
	 * nlbl_sid and xfrm_sid are not equal to SECSID_शून्य would be अगर the
	 * security server was initialized and state->initialized was true.
	 */
	अगर (!policydb->mls_enabled) अणु
		rc = 0;
		जाओ out;
	पूर्ण

	rc = -EINVAL;
	nlbl_ctx = sidtab_search(sidtab, nlbl_sid);
	अगर (!nlbl_ctx) अणु
		pr_err("SELinux: %s:  unrecognized SID %d\n",
		       __func__, nlbl_sid);
		जाओ out;
	पूर्ण
	rc = -EINVAL;
	xfrm_ctx = sidtab_search(sidtab, xfrm_sid);
	अगर (!xfrm_ctx) अणु
		pr_err("SELinux: %s:  unrecognized SID %d\n",
		       __func__, xfrm_sid);
		जाओ out;
	पूर्ण
	rc = (mls_context_cmp(nlbl_ctx, xfrm_ctx) ? 0 : -EACCES);
	अगर (rc)
		जाओ out;

	/* at present NetLabel SIDs/labels really only carry MLS
	 * inक्रमmation so अगर the MLS portion of the NetLabel SID
	 * matches the MLS portion of the labeled XFRM SID/label
	 * then pass aदीर्घ the XFRM SID as it is the most
	 * expressive */
	*peer_sid = xfrm_sid;
out:
	rcu_पढ़ो_unlock();
	वापस rc;
पूर्ण

अटल पूर्णांक get_classes_callback(व्योम *k, व्योम *d, व्योम *args)
अणु
	काष्ठा class_datum *datum = d;
	अक्षर *name = k, **classes = args;
	पूर्णांक value = datum->value - 1;

	classes[value] = kstrdup(name, GFP_ATOMIC);
	अगर (!classes[value])
		वापस -ENOMEM;

	वापस 0;
पूर्ण

पूर्णांक security_get_classes(काष्ठा selinux_policy *policy,
			 अक्षर ***classes, पूर्णांक *nclasses)
अणु
	काष्ठा policydb *policydb;
	पूर्णांक rc;

	policydb = &policy->policydb;

	rc = -ENOMEM;
	*nclasses = policydb->p_classes.nprim;
	*classes = kसुस्मृति(*nclasses, माप(**classes), GFP_ATOMIC);
	अगर (!*classes)
		जाओ out;

	rc = hashtab_map(&policydb->p_classes.table, get_classes_callback,
			 *classes);
	अगर (rc) अणु
		पूर्णांक i;
		क्रम (i = 0; i < *nclasses; i++)
			kमुक्त((*classes)[i]);
		kमुक्त(*classes);
	पूर्ण

out:
	वापस rc;
पूर्ण

अटल पूर्णांक get_permissions_callback(व्योम *k, व्योम *d, व्योम *args)
अणु
	काष्ठा perm_datum *datum = d;
	अक्षर *name = k, **perms = args;
	पूर्णांक value = datum->value - 1;

	perms[value] = kstrdup(name, GFP_ATOMIC);
	अगर (!perms[value])
		वापस -ENOMEM;

	वापस 0;
पूर्ण

पूर्णांक security_get_permissions(काष्ठा selinux_policy *policy,
			     अक्षर *class, अक्षर ***perms, पूर्णांक *nperms)
अणु
	काष्ठा policydb *policydb;
	पूर्णांक rc, i;
	काष्ठा class_datum *match;

	policydb = &policy->policydb;

	rc = -EINVAL;
	match = symtab_search(&policydb->p_classes, class);
	अगर (!match) अणु
		pr_err("SELinux: %s:  unrecognized class %s\n",
			__func__, class);
		जाओ out;
	पूर्ण

	rc = -ENOMEM;
	*nperms = match->permissions.nprim;
	*perms = kसुस्मृति(*nperms, माप(**perms), GFP_ATOMIC);
	अगर (!*perms)
		जाओ out;

	अगर (match->comdatum) अणु
		rc = hashtab_map(&match->comdatum->permissions.table,
				 get_permissions_callback, *perms);
		अगर (rc)
			जाओ err;
	पूर्ण

	rc = hashtab_map(&match->permissions.table, get_permissions_callback,
			 *perms);
	अगर (rc)
		जाओ err;

out:
	वापस rc;

err:
	क्रम (i = 0; i < *nperms; i++)
		kमुक्त((*perms)[i]);
	kमुक्त(*perms);
	वापस rc;
पूर्ण

पूर्णांक security_get_reject_unknown(काष्ठा selinux_state *state)
अणु
	काष्ठा selinux_policy *policy;
	पूर्णांक value;

	अगर (!selinux_initialized(state))
		वापस 0;

	rcu_पढ़ो_lock();
	policy = rcu_dereference(state->policy);
	value = policy->policydb.reject_unknown;
	rcu_पढ़ो_unlock();
	वापस value;
पूर्ण

पूर्णांक security_get_allow_unknown(काष्ठा selinux_state *state)
अणु
	काष्ठा selinux_policy *policy;
	पूर्णांक value;

	अगर (!selinux_initialized(state))
		वापस 0;

	rcu_पढ़ो_lock();
	policy = rcu_dereference(state->policy);
	value = policy->policydb.allow_unknown;
	rcu_पढ़ो_unlock();
	वापस value;
पूर्ण

/**
 * security_policycap_supported - Check क्रम a specअगरic policy capability
 * @req_cap: capability
 *
 * Description:
 * This function queries the currently loaded policy to see अगर it supports the
 * capability specअगरied by @req_cap.  Returns true (1) अगर the capability is
 * supported, false (0) अगर it isn't supported.
 *
 */
पूर्णांक security_policycap_supported(काष्ठा selinux_state *state,
				 अचिन्हित पूर्णांक req_cap)
अणु
	काष्ठा selinux_policy *policy;
	पूर्णांक rc;

	अगर (!selinux_initialized(state))
		वापस 0;

	rcu_पढ़ो_lock();
	policy = rcu_dereference(state->policy);
	rc = ebiपंचांगap_get_bit(&policy->policydb.policycaps, req_cap);
	rcu_पढ़ो_unlock();

	वापस rc;
पूर्ण

काष्ठा selinux_audit_rule अणु
	u32 au_seqno;
	काष्ठा context au_ctxt;
पूर्ण;

व्योम selinux_audit_rule_मुक्त(व्योम *vrule)
अणु
	काष्ठा selinux_audit_rule *rule = vrule;

	अगर (rule) अणु
		context_destroy(&rule->au_ctxt);
		kमुक्त(rule);
	पूर्ण
पूर्ण

पूर्णांक selinux_audit_rule_init(u32 field, u32 op, अक्षर *rulestr, व्योम **vrule)
अणु
	काष्ठा selinux_state *state = &selinux_state;
	काष्ठा selinux_policy *policy;
	काष्ठा policydb *policydb;
	काष्ठा selinux_audit_rule *पंचांगprule;
	काष्ठा role_datum *roledatum;
	काष्ठा type_datum *typedatum;
	काष्ठा user_datum *userdatum;
	काष्ठा selinux_audit_rule **rule = (काष्ठा selinux_audit_rule **)vrule;
	पूर्णांक rc = 0;

	*rule = शून्य;

	अगर (!selinux_initialized(state))
		वापस -EOPNOTSUPP;

	चयन (field) अणु
	हाल AUDIT_SUBJ_USER:
	हाल AUDIT_SUBJ_ROLE:
	हाल AUDIT_SUBJ_TYPE:
	हाल AUDIT_OBJ_USER:
	हाल AUDIT_OBJ_ROLE:
	हाल AUDIT_OBJ_TYPE:
		/* only 'equals' and 'not equals' fit user, role, and type */
		अगर (op != Audit_equal && op != Audit_not_equal)
			वापस -EINVAL;
		अवरोध;
	हाल AUDIT_SUBJ_SEN:
	हाल AUDIT_SUBJ_CLR:
	हाल AUDIT_OBJ_LEV_LOW:
	हाल AUDIT_OBJ_LEV_HIGH:
		/* we करो not allow a range, indicated by the presence of '-' */
		अगर (म_अक्षर(rulestr, '-'))
			वापस -EINVAL;
		अवरोध;
	शेष:
		/* only the above fields are valid */
		वापस -EINVAL;
	पूर्ण

	पंचांगprule = kzalloc(माप(काष्ठा selinux_audit_rule), GFP_KERNEL);
	अगर (!पंचांगprule)
		वापस -ENOMEM;

	context_init(&पंचांगprule->au_ctxt);

	rcu_पढ़ो_lock();
	policy = rcu_dereference(state->policy);
	policydb = &policy->policydb;

	पंचांगprule->au_seqno = policy->latest_granting;

	चयन (field) अणु
	हाल AUDIT_SUBJ_USER:
	हाल AUDIT_OBJ_USER:
		rc = -EINVAL;
		userdatum = symtab_search(&policydb->p_users, rulestr);
		अगर (!userdatum)
			जाओ out;
		पंचांगprule->au_ctxt.user = userdatum->value;
		अवरोध;
	हाल AUDIT_SUBJ_ROLE:
	हाल AUDIT_OBJ_ROLE:
		rc = -EINVAL;
		roledatum = symtab_search(&policydb->p_roles, rulestr);
		अगर (!roledatum)
			जाओ out;
		पंचांगprule->au_ctxt.role = roledatum->value;
		अवरोध;
	हाल AUDIT_SUBJ_TYPE:
	हाल AUDIT_OBJ_TYPE:
		rc = -EINVAL;
		typedatum = symtab_search(&policydb->p_types, rulestr);
		अगर (!typedatum)
			जाओ out;
		पंचांगprule->au_ctxt.type = typedatum->value;
		अवरोध;
	हाल AUDIT_SUBJ_SEN:
	हाल AUDIT_SUBJ_CLR:
	हाल AUDIT_OBJ_LEV_LOW:
	हाल AUDIT_OBJ_LEV_HIGH:
		rc = mls_from_string(policydb, rulestr, &पंचांगprule->au_ctxt,
				     GFP_ATOMIC);
		अगर (rc)
			जाओ out;
		अवरोध;
	पूर्ण
	rc = 0;
out:
	rcu_पढ़ो_unlock();

	अगर (rc) अणु
		selinux_audit_rule_मुक्त(पंचांगprule);
		पंचांगprule = शून्य;
	पूर्ण

	*rule = पंचांगprule;

	वापस rc;
पूर्ण

/* Check to see अगर the rule contains any selinux fields */
पूर्णांक selinux_audit_rule_known(काष्ठा audit_krule *rule)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < rule->field_count; i++) अणु
		काष्ठा audit_field *f = &rule->fields[i];
		चयन (f->type) अणु
		हाल AUDIT_SUBJ_USER:
		हाल AUDIT_SUBJ_ROLE:
		हाल AUDIT_SUBJ_TYPE:
		हाल AUDIT_SUBJ_SEN:
		हाल AUDIT_SUBJ_CLR:
		हाल AUDIT_OBJ_USER:
		हाल AUDIT_OBJ_ROLE:
		हाल AUDIT_OBJ_TYPE:
		हाल AUDIT_OBJ_LEV_LOW:
		हाल AUDIT_OBJ_LEV_HIGH:
			वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक selinux_audit_rule_match(u32 sid, u32 field, u32 op, व्योम *vrule)
अणु
	काष्ठा selinux_state *state = &selinux_state;
	काष्ठा selinux_policy *policy;
	काष्ठा context *ctxt;
	काष्ठा mls_level *level;
	काष्ठा selinux_audit_rule *rule = vrule;
	पूर्णांक match = 0;

	अगर (unlikely(!rule)) अणु
		WARN_ONCE(1, "selinux_audit_rule_match: missing rule\n");
		वापस -ENOENT;
	पूर्ण

	अगर (!selinux_initialized(state))
		वापस 0;

	rcu_पढ़ो_lock();

	policy = rcu_dereference(state->policy);

	अगर (rule->au_seqno < policy->latest_granting) अणु
		match = -ESTALE;
		जाओ out;
	पूर्ण

	ctxt = sidtab_search(policy->sidtab, sid);
	अगर (unlikely(!ctxt)) अणु
		WARN_ONCE(1, "selinux_audit_rule_match: unrecognized SID %d\n",
			  sid);
		match = -ENOENT;
		जाओ out;
	पूर्ण

	/* a field/op pair that is not caught here will simply fall through
	   without a match */
	चयन (field) अणु
	हाल AUDIT_SUBJ_USER:
	हाल AUDIT_OBJ_USER:
		चयन (op) अणु
		हाल Audit_equal:
			match = (ctxt->user == rule->au_ctxt.user);
			अवरोध;
		हाल Audit_not_equal:
			match = (ctxt->user != rule->au_ctxt.user);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल AUDIT_SUBJ_ROLE:
	हाल AUDIT_OBJ_ROLE:
		चयन (op) अणु
		हाल Audit_equal:
			match = (ctxt->role == rule->au_ctxt.role);
			अवरोध;
		हाल Audit_not_equal:
			match = (ctxt->role != rule->au_ctxt.role);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल AUDIT_SUBJ_TYPE:
	हाल AUDIT_OBJ_TYPE:
		चयन (op) अणु
		हाल Audit_equal:
			match = (ctxt->type == rule->au_ctxt.type);
			अवरोध;
		हाल Audit_not_equal:
			match = (ctxt->type != rule->au_ctxt.type);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल AUDIT_SUBJ_SEN:
	हाल AUDIT_SUBJ_CLR:
	हाल AUDIT_OBJ_LEV_LOW:
	हाल AUDIT_OBJ_LEV_HIGH:
		level = ((field == AUDIT_SUBJ_SEN ||
			  field == AUDIT_OBJ_LEV_LOW) ?
			 &ctxt->range.level[0] : &ctxt->range.level[1]);
		चयन (op) अणु
		हाल Audit_equal:
			match = mls_level_eq(&rule->au_ctxt.range.level[0],
					     level);
			अवरोध;
		हाल Audit_not_equal:
			match = !mls_level_eq(&rule->au_ctxt.range.level[0],
					      level);
			अवरोध;
		हाल Audit_lt:
			match = (mls_level_करोm(&rule->au_ctxt.range.level[0],
					       level) &&
				 !mls_level_eq(&rule->au_ctxt.range.level[0],
					       level));
			अवरोध;
		हाल Audit_le:
			match = mls_level_करोm(&rule->au_ctxt.range.level[0],
					      level);
			अवरोध;
		हाल Audit_gt:
			match = (mls_level_करोm(level,
					      &rule->au_ctxt.range.level[0]) &&
				 !mls_level_eq(level,
					       &rule->au_ctxt.range.level[0]));
			अवरोध;
		हाल Audit_ge:
			match = mls_level_करोm(level,
					      &rule->au_ctxt.range.level[0]);
			अवरोध;
		पूर्ण
	पूर्ण

out:
	rcu_पढ़ो_unlock();
	वापस match;
पूर्ण

अटल पूर्णांक aurule_avc_callback(u32 event)
अणु
	अगर (event == AVC_CALLBACK_RESET)
		वापस audit_update_lsm_rules();
	वापस 0;
पूर्ण

अटल पूर्णांक __init aurule_init(व्योम)
अणु
	पूर्णांक err;

	err = avc_add_callback(aurule_avc_callback, AVC_CALLBACK_RESET);
	अगर (err)
		panic("avc_add_callback() failed, error %d\n", err);

	वापस err;
पूर्ण
__initcall(aurule_init);

#अगर_घोषित CONFIG_NETLABEL
/**
 * security_netlbl_cache_add - Add an entry to the NetLabel cache
 * @secattr: the NetLabel packet security attributes
 * @sid: the SELinux SID
 *
 * Description:
 * Attempt to cache the context in @ctx, which was derived from the packet in
 * @skb, in the NetLabel subप्रणाली cache.  This function assumes @secattr has
 * alपढ़ोy been initialized.
 *
 */
अटल व्योम security_netlbl_cache_add(काष्ठा netlbl_lsm_secattr *secattr,
				      u32 sid)
अणु
	u32 *sid_cache;

	sid_cache = kदो_स्मृति(माप(*sid_cache), GFP_ATOMIC);
	अगर (sid_cache == शून्य)
		वापस;
	secattr->cache = netlbl_secattr_cache_alloc(GFP_ATOMIC);
	अगर (secattr->cache == शून्य) अणु
		kमुक्त(sid_cache);
		वापस;
	पूर्ण

	*sid_cache = sid;
	secattr->cache->मुक्त = kमुक्त;
	secattr->cache->data = sid_cache;
	secattr->flags |= NETLBL_SECATTR_CACHE;
पूर्ण

/**
 * security_netlbl_secattr_to_sid - Convert a NetLabel secattr to a SELinux SID
 * @secattr: the NetLabel packet security attributes
 * @sid: the SELinux SID
 *
 * Description:
 * Convert the given NetLabel security attributes in @secattr पूर्णांकo a
 * SELinux SID.  If the @secattr field करोes not contain a full SELinux
 * SID/context then use SECINITSID_NETMSG as the foundation.  If possible the
 * 'cache' field of @secattr is set and the CACHE flag is set; this is to
 * allow the @secattr to be used by NetLabel to cache the secattr to SID
 * conversion क्रम future lookups.  Returns zero on success, negative values on
 * failure.
 *
 */
पूर्णांक security_netlbl_secattr_to_sid(काष्ठा selinux_state *state,
				   काष्ठा netlbl_lsm_secattr *secattr,
				   u32 *sid)
अणु
	काष्ठा selinux_policy *policy;
	काष्ठा policydb *policydb;
	काष्ठा sidtab *sidtab;
	पूर्णांक rc;
	काष्ठा context *ctx;
	काष्ठा context ctx_new;

	अगर (!selinux_initialized(state)) अणु
		*sid = SECSID_शून्य;
		वापस 0;
	पूर्ण

retry:
	rc = 0;
	rcu_पढ़ो_lock();
	policy = rcu_dereference(state->policy);
	policydb = &policy->policydb;
	sidtab = policy->sidtab;

	अगर (secattr->flags & NETLBL_SECATTR_CACHE)
		*sid = *(u32 *)secattr->cache->data;
	अन्यथा अगर (secattr->flags & NETLBL_SECATTR_SECID)
		*sid = secattr->attr.secid;
	अन्यथा अगर (secattr->flags & NETLBL_SECATTR_MLS_LVL) अणु
		rc = -EIDRM;
		ctx = sidtab_search(sidtab, SECINITSID_NETMSG);
		अगर (ctx == शून्य)
			जाओ out;

		context_init(&ctx_new);
		ctx_new.user = ctx->user;
		ctx_new.role = ctx->role;
		ctx_new.type = ctx->type;
		mls_import_netlbl_lvl(policydb, &ctx_new, secattr);
		अगर (secattr->flags & NETLBL_SECATTR_MLS_CAT) अणु
			rc = mls_import_netlbl_cat(policydb, &ctx_new, secattr);
			अगर (rc)
				जाओ out;
		पूर्ण
		rc = -EIDRM;
		अगर (!mls_context_isvalid(policydb, &ctx_new)) अणु
			ebiपंचांगap_destroy(&ctx_new.range.level[0].cat);
			जाओ out;
		पूर्ण

		rc = sidtab_context_to_sid(sidtab, &ctx_new, sid);
		ebiपंचांगap_destroy(&ctx_new.range.level[0].cat);
		अगर (rc == -ESTALE) अणु
			rcu_पढ़ो_unlock();
			जाओ retry;
		पूर्ण
		अगर (rc)
			जाओ out;

		security_netlbl_cache_add(secattr, *sid);
	पूर्ण अन्यथा
		*sid = SECSID_शून्य;

out:
	rcu_पढ़ो_unlock();
	वापस rc;
पूर्ण

/**
 * security_netlbl_sid_to_secattr - Convert a SELinux SID to a NetLabel secattr
 * @sid: the SELinux SID
 * @secattr: the NetLabel packet security attributes
 *
 * Description:
 * Convert the given SELinux SID in @sid पूर्णांकo a NetLabel security attribute.
 * Returns zero on success, negative values on failure.
 *
 */
पूर्णांक security_netlbl_sid_to_secattr(काष्ठा selinux_state *state,
				   u32 sid, काष्ठा netlbl_lsm_secattr *secattr)
अणु
	काष्ठा selinux_policy *policy;
	काष्ठा policydb *policydb;
	पूर्णांक rc;
	काष्ठा context *ctx;

	अगर (!selinux_initialized(state))
		वापस 0;

	rcu_पढ़ो_lock();
	policy = rcu_dereference(state->policy);
	policydb = &policy->policydb;

	rc = -ENOENT;
	ctx = sidtab_search(policy->sidtab, sid);
	अगर (ctx == शून्य)
		जाओ out;

	rc = -ENOMEM;
	secattr->करोमुख्य = kstrdup(sym_name(policydb, SYM_TYPES, ctx->type - 1),
				  GFP_ATOMIC);
	अगर (secattr->करोमुख्य == शून्य)
		जाओ out;

	secattr->attr.secid = sid;
	secattr->flags |= NETLBL_SECATTR_DOMAIN_CPY | NETLBL_SECATTR_SECID;
	mls_export_netlbl_lvl(policydb, ctx, secattr);
	rc = mls_export_netlbl_cat(policydb, ctx, secattr);
out:
	rcu_पढ़ो_unlock();
	वापस rc;
पूर्ण
#पूर्ण_अगर /* CONFIG_NETLABEL */

/**
 * __security_पढ़ो_policy - पढ़ो the policy.
 * @policy: SELinux policy
 * @data: binary policy data
 * @len: length of data in bytes
 *
 */
अटल पूर्णांक __security_पढ़ो_policy(काष्ठा selinux_policy *policy,
				  व्योम *data, माप_प्रकार *len)
अणु
	पूर्णांक rc;
	काष्ठा policy_file fp;

	fp.data = data;
	fp.len = *len;

	rc = policydb_ग_लिखो(&policy->policydb, &fp);
	अगर (rc)
		वापस rc;

	*len = (अचिन्हित दीर्घ)fp.data - (अचिन्हित दीर्घ)data;
	वापस 0;
पूर्ण

/**
 * security_पढ़ो_policy - पढ़ो the policy.
 * @state: selinux_state
 * @data: binary policy data
 * @len: length of data in bytes
 *
 */
पूर्णांक security_पढ़ो_policy(काष्ठा selinux_state *state,
			 व्योम **data, माप_प्रकार *len)
अणु
	काष्ठा selinux_policy *policy;

	policy = rcu_dereference_रक्षित(
			state->policy, lockdep_is_held(&state->policy_mutex));
	अगर (!policy)
		वापस -EINVAL;

	*len = policy->policydb.len;
	*data = vदो_स्मृति_user(*len);
	अगर (!*data)
		वापस -ENOMEM;

	वापस __security_पढ़ो_policy(policy, *data, len);
पूर्ण

/**
 * security_पढ़ो_state_kernel - पढ़ो the policy.
 * @state: selinux_state
 * @data: binary policy data
 * @len: length of data in bytes
 *
 * Allocates kernel memory क्रम पढ़ोing SELinux policy.
 * This function is क्रम पूर्णांकernal use only and should not
 * be used क्रम वापसing data to user space.
 *
 * This function must be called with policy_mutex held.
 */
पूर्णांक security_पढ़ो_state_kernel(काष्ठा selinux_state *state,
			       व्योम **data, माप_प्रकार *len)
अणु
	काष्ठा selinux_policy *policy;

	policy = rcu_dereference_रक्षित(
			state->policy, lockdep_is_held(&state->policy_mutex));
	अगर (!policy)
		वापस -EINVAL;

	*len = policy->policydb.len;
	*data = vदो_स्मृति(*len);
	अगर (!*data)
		वापस -ENOMEM;

	वापस __security_पढ़ो_policy(policy, *data, len);
पूर्ण
