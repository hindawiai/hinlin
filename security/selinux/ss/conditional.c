<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Authors: Karl MacMillan <kmacmillan@tresys.com>
 *	    Frank Mayer <mayerf@tresys.com>
 *
 * Copyright (C) 2003 - 2004 Tresys Technology, LLC
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>

#समावेश "security.h"
#समावेश "conditional.h"
#समावेश "services.h"

/*
 * cond_evaluate_expr evaluates a conditional expr
 * in reverse polish notation. It वापसs true (1), false (0),
 * or undefined (-1). Undefined occurs when the expression
 * exceeds the stack depth of COND_EXPR_MAXDEPTH.
 */
अटल पूर्णांक cond_evaluate_expr(काष्ठा policydb *p, काष्ठा cond_expr *expr)
अणु
	u32 i;
	पूर्णांक s[COND_EXPR_MAXDEPTH];
	पूर्णांक sp = -1;

	अगर (expr->len == 0)
		वापस -1;

	क्रम (i = 0; i < expr->len; i++) अणु
		काष्ठा cond_expr_node *node = &expr->nodes[i];

		चयन (node->expr_type) अणु
		हाल COND_BOOL:
			अगर (sp == (COND_EXPR_MAXDEPTH - 1))
				वापस -1;
			sp++;
			s[sp] = p->bool_val_to_काष्ठा[node->bool - 1]->state;
			अवरोध;
		हाल COND_NOT:
			अगर (sp < 0)
				वापस -1;
			s[sp] = !s[sp];
			अवरोध;
		हाल COND_OR:
			अगर (sp < 1)
				वापस -1;
			sp--;
			s[sp] |= s[sp + 1];
			अवरोध;
		हाल COND_AND:
			अगर (sp < 1)
				वापस -1;
			sp--;
			s[sp] &= s[sp + 1];
			अवरोध;
		हाल COND_XOR:
			अगर (sp < 1)
				वापस -1;
			sp--;
			s[sp] ^= s[sp + 1];
			अवरोध;
		हाल COND_EQ:
			अगर (sp < 1)
				वापस -1;
			sp--;
			s[sp] = (s[sp] == s[sp + 1]);
			अवरोध;
		हाल COND_NEQ:
			अगर (sp < 1)
				वापस -1;
			sp--;
			s[sp] = (s[sp] != s[sp + 1]);
			अवरोध;
		शेष:
			वापस -1;
		पूर्ण
	पूर्ण
	वापस s[0];
पूर्ण

/*
 * evaluate_cond_node evaluates the conditional stored in
 * a काष्ठा cond_node and अगर the result is dअगरferent than the
 * current state of the node it sets the rules in the true/false
 * list appropriately. If the result of the expression is undefined
 * all of the rules are disabled क्रम safety.
 */
अटल व्योम evaluate_cond_node(काष्ठा policydb *p, काष्ठा cond_node *node)
अणु
	काष्ठा avtab_node *avnode;
	पूर्णांक new_state;
	u32 i;

	new_state = cond_evaluate_expr(p, &node->expr);
	अगर (new_state != node->cur_state) अणु
		node->cur_state = new_state;
		अगर (new_state == -1)
			pr_err("SELinux: expression result was undefined - disabling all rules.\n");
		/* turn the rules on or off */
		क्रम (i = 0; i < node->true_list.len; i++) अणु
			avnode = node->true_list.nodes[i];
			अगर (new_state <= 0)
				avnode->key.specअगरied &= ~AVTAB_ENABLED;
			अन्यथा
				avnode->key.specअगरied |= AVTAB_ENABLED;
		पूर्ण

		क्रम (i = 0; i < node->false_list.len; i++) अणु
			avnode = node->false_list.nodes[i];
			/* -1 or 1 */
			अगर (new_state)
				avnode->key.specअगरied &= ~AVTAB_ENABLED;
			अन्यथा
				avnode->key.specअगरied |= AVTAB_ENABLED;
		पूर्ण
	पूर्ण
पूर्ण

व्योम evaluate_cond_nodes(काष्ठा policydb *p)
अणु
	u32 i;

	क्रम (i = 0; i < p->cond_list_len; i++)
		evaluate_cond_node(p, &p->cond_list[i]);
पूर्ण

व्योम cond_policydb_init(काष्ठा policydb *p)
अणु
	p->bool_val_to_काष्ठा = शून्य;
	p->cond_list = शून्य;
	p->cond_list_len = 0;

	avtab_init(&p->te_cond_avtab);
पूर्ण

अटल व्योम cond_node_destroy(काष्ठा cond_node *node)
अणु
	kमुक्त(node->expr.nodes);
	/* the avtab_ptr_t nodes are destroyed by the avtab */
	kमुक्त(node->true_list.nodes);
	kमुक्त(node->false_list.nodes);
पूर्ण

अटल व्योम cond_list_destroy(काष्ठा policydb *p)
अणु
	u32 i;

	क्रम (i = 0; i < p->cond_list_len; i++)
		cond_node_destroy(&p->cond_list[i]);
	kमुक्त(p->cond_list);
पूर्ण

व्योम cond_policydb_destroy(काष्ठा policydb *p)
अणु
	kमुक्त(p->bool_val_to_काष्ठा);
	avtab_destroy(&p->te_cond_avtab);
	cond_list_destroy(p);
पूर्ण

पूर्णांक cond_init_bool_indexes(काष्ठा policydb *p)
अणु
	kमुक्त(p->bool_val_to_काष्ठा);
	p->bool_val_to_काष्ठा = kदो_स्मृति_array(p->p_bools.nprim,
					      माप(*p->bool_val_to_काष्ठा),
					      GFP_KERNEL);
	अगर (!p->bool_val_to_काष्ठा)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

पूर्णांक cond_destroy_bool(व्योम *key, व्योम *datum, व्योम *p)
अणु
	kमुक्त(key);
	kमुक्त(datum);
	वापस 0;
पूर्ण

पूर्णांक cond_index_bool(व्योम *key, व्योम *datum, व्योम *datap)
अणु
	काष्ठा policydb *p;
	काष्ठा cond_bool_datum *booldatum;

	booldatum = datum;
	p = datap;

	अगर (!booldatum->value || booldatum->value > p->p_bools.nprim)
		वापस -EINVAL;

	p->sym_val_to_name[SYM_BOOLS][booldatum->value - 1] = key;
	p->bool_val_to_काष्ठा[booldatum->value - 1] = booldatum;

	वापस 0;
पूर्ण

अटल पूर्णांक bool_isvalid(काष्ठा cond_bool_datum *b)
अणु
	अगर (!(b->state == 0 || b->state == 1))
		वापस 0;
	वापस 1;
पूर्ण

पूर्णांक cond_पढ़ो_bool(काष्ठा policydb *p, काष्ठा symtab *s, व्योम *fp)
अणु
	अक्षर *key = शून्य;
	काष्ठा cond_bool_datum *booldatum;
	__le32 buf[3];
	u32 len;
	पूर्णांक rc;

	booldatum = kzalloc(माप(*booldatum), GFP_KERNEL);
	अगर (!booldatum)
		वापस -ENOMEM;

	rc = next_entry(buf, fp, माप(buf));
	अगर (rc)
		जाओ err;

	booldatum->value = le32_to_cpu(buf[0]);
	booldatum->state = le32_to_cpu(buf[1]);

	rc = -EINVAL;
	अगर (!bool_isvalid(booldatum))
		जाओ err;

	len = le32_to_cpu(buf[2]);
	अगर (((len == 0) || (len == (u32)-1)))
		जाओ err;

	rc = -ENOMEM;
	key = kदो_स्मृति(len + 1, GFP_KERNEL);
	अगर (!key)
		जाओ err;
	rc = next_entry(key, fp, len);
	अगर (rc)
		जाओ err;
	key[len] = '\0';
	rc = symtab_insert(s, key, booldatum);
	अगर (rc)
		जाओ err;

	वापस 0;
err:
	cond_destroy_bool(key, booldatum, शून्य);
	वापस rc;
पूर्ण

काष्ठा cond_insertf_data अणु
	काष्ठा policydb *p;
	काष्ठा avtab_node **dst;
	काष्ठा cond_av_list *other;
पूर्ण;

अटल पूर्णांक cond_insertf(काष्ठा avtab *a, काष्ठा avtab_key *k, काष्ठा avtab_datum *d, व्योम *ptr)
अणु
	काष्ठा cond_insertf_data *data = ptr;
	काष्ठा policydb *p = data->p;
	काष्ठा cond_av_list *other = data->other;
	काष्ठा avtab_node *node_ptr;
	u32 i;
	bool found;

	/*
	 * For type rules we have to make certain there aren't any
	 * conflicting rules by searching the te_avtab and the
	 * cond_te_avtab.
	 */
	अगर (k->specअगरied & AVTAB_TYPE) अणु
		अगर (avtab_search(&p->te_avtab, k)) अणु
			pr_err("SELinux: type rule already exists outside of a conditional.\n");
			वापस -EINVAL;
		पूर्ण
		/*
		 * If we are पढ़ोing the false list other will be a poपूर्णांकer to
		 * the true list. We can have duplicate entries अगर there is only
		 * 1 other entry and it is in our true list.
		 *
		 * If we are पढ़ोing the true list (other == शून्य) there shouldn't
		 * be any other entries.
		 */
		अगर (other) अणु
			node_ptr = avtab_search_node(&p->te_cond_avtab, k);
			अगर (node_ptr) अणु
				अगर (avtab_search_node_next(node_ptr, k->specअगरied)) अणु
					pr_err("SELinux: too many conflicting type rules.\n");
					वापस -EINVAL;
				पूर्ण
				found = false;
				क्रम (i = 0; i < other->len; i++) अणु
					अगर (other->nodes[i] == node_ptr) अणु
						found = true;
						अवरोध;
					पूर्ण
				पूर्ण
				अगर (!found) अणु
					pr_err("SELinux: conflicting type rules.\n");
					वापस -EINVAL;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (avtab_search(&p->te_cond_avtab, k)) अणु
				pr_err("SELinux: conflicting type rules when adding type rule for true.\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	node_ptr = avtab_insert_nonunique(&p->te_cond_avtab, k, d);
	अगर (!node_ptr) अणु
		pr_err("SELinux: could not insert rule.\n");
		वापस -ENOMEM;
	पूर्ण

	*data->dst = node_ptr;
	वापस 0;
पूर्ण

अटल पूर्णांक cond_पढ़ो_av_list(काष्ठा policydb *p, व्योम *fp,
			     काष्ठा cond_av_list *list,
			     काष्ठा cond_av_list *other)
अणु
	पूर्णांक rc;
	__le32 buf[1];
	u32 i, len;
	काष्ठा cond_insertf_data data;

	rc = next_entry(buf, fp, माप(u32));
	अगर (rc)
		वापस rc;

	len = le32_to_cpu(buf[0]);
	अगर (len == 0)
		वापस 0;

	list->nodes = kसुस्मृति(len, माप(*list->nodes), GFP_KERNEL);
	अगर (!list->nodes)
		वापस -ENOMEM;

	data.p = p;
	data.other = other;
	क्रम (i = 0; i < len; i++) अणु
		data.dst = &list->nodes[i];
		rc = avtab_पढ़ो_item(&p->te_cond_avtab, fp, p, cond_insertf,
				     &data);
		अगर (rc) अणु
			kमुक्त(list->nodes);
			list->nodes = शून्य;
			वापस rc;
		पूर्ण
	पूर्ण

	list->len = len;
	वापस 0;
पूर्ण

अटल पूर्णांक expr_node_isvalid(काष्ठा policydb *p, काष्ठा cond_expr_node *expr)
अणु
	अगर (expr->expr_type <= 0 || expr->expr_type > COND_LAST) अणु
		pr_err("SELinux: conditional expressions uses unknown operator.\n");
		वापस 0;
	पूर्ण

	अगर (expr->bool > p->p_bools.nprim) अणु
		pr_err("SELinux: conditional expressions uses unknown bool.\n");
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक cond_पढ़ो_node(काष्ठा policydb *p, काष्ठा cond_node *node, व्योम *fp)
अणु
	__le32 buf[2];
	u32 i, len;
	पूर्णांक rc;

	rc = next_entry(buf, fp, माप(u32) * 2);
	अगर (rc)
		वापस rc;

	node->cur_state = le32_to_cpu(buf[0]);

	/* expr */
	len = le32_to_cpu(buf[1]);
	node->expr.nodes = kसुस्मृति(len, माप(*node->expr.nodes), GFP_KERNEL);
	अगर (!node->expr.nodes)
		वापस -ENOMEM;

	node->expr.len = len;

	क्रम (i = 0; i < len; i++) अणु
		काष्ठा cond_expr_node *expr = &node->expr.nodes[i];

		rc = next_entry(buf, fp, माप(u32) * 2);
		अगर (rc)
			वापस rc;

		expr->expr_type = le32_to_cpu(buf[0]);
		expr->bool = le32_to_cpu(buf[1]);

		अगर (!expr_node_isvalid(p, expr))
			वापस -EINVAL;
	पूर्ण

	rc = cond_पढ़ो_av_list(p, fp, &node->true_list, शून्य);
	अगर (rc)
		वापस rc;
	वापस cond_पढ़ो_av_list(p, fp, &node->false_list, &node->true_list);
पूर्ण

पूर्णांक cond_पढ़ो_list(काष्ठा policydb *p, व्योम *fp)
अणु
	__le32 buf[1];
	u32 i, len;
	पूर्णांक rc;

	rc = next_entry(buf, fp, माप(buf));
	अगर (rc)
		वापस rc;

	len = le32_to_cpu(buf[0]);

	p->cond_list = kसुस्मृति(len, माप(*p->cond_list), GFP_KERNEL);
	अगर (!p->cond_list)
		वापस -ENOMEM;

	rc = avtab_alloc(&(p->te_cond_avtab), p->te_avtab.nel);
	अगर (rc)
		जाओ err;

	p->cond_list_len = len;

	क्रम (i = 0; i < len; i++) अणु
		rc = cond_पढ़ो_node(p, &p->cond_list[i], fp);
		अगर (rc)
			जाओ err;
	पूर्ण
	वापस 0;
err:
	cond_list_destroy(p);
	p->cond_list = शून्य;
	वापस rc;
पूर्ण

पूर्णांक cond_ग_लिखो_bool(व्योम *vkey, व्योम *datum, व्योम *ptr)
अणु
	अक्षर *key = vkey;
	काष्ठा cond_bool_datum *booldatum = datum;
	काष्ठा policy_data *pd = ptr;
	व्योम *fp = pd->fp;
	__le32 buf[3];
	u32 len;
	पूर्णांक rc;

	len = म_माप(key);
	buf[0] = cpu_to_le32(booldatum->value);
	buf[1] = cpu_to_le32(booldatum->state);
	buf[2] = cpu_to_le32(len);
	rc = put_entry(buf, माप(u32), 3, fp);
	अगर (rc)
		वापस rc;
	rc = put_entry(key, 1, len, fp);
	अगर (rc)
		वापस rc;
	वापस 0;
पूर्ण

/*
 * cond_ग_लिखो_cond_av_list करोesn't ग_लिखो out the av_list nodes.
 * Instead it ग_लिखोs out the key/value pairs from the avtab. This
 * is necessary because there is no way to uniquely identअगरying rules
 * in the avtab so it is not possible to associate inभागidual rules
 * in the avtab with a conditional without saving them as part of
 * the conditional. This means that the avtab with the conditional
 * rules will not be saved but will be rebuilt on policy load.
 */
अटल पूर्णांक cond_ग_लिखो_av_list(काष्ठा policydb *p,
			      काष्ठा cond_av_list *list, काष्ठा policy_file *fp)
अणु
	__le32 buf[1];
	u32 i;
	पूर्णांक rc;

	buf[0] = cpu_to_le32(list->len);
	rc = put_entry(buf, माप(u32), 1, fp);
	अगर (rc)
		वापस rc;

	क्रम (i = 0; i < list->len; i++) अणु
		rc = avtab_ग_लिखो_item(p, list->nodes[i], fp);
		अगर (rc)
			वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cond_ग_लिखो_node(काष्ठा policydb *p, काष्ठा cond_node *node,
		    काष्ठा policy_file *fp)
अणु
	__le32 buf[2];
	पूर्णांक rc;
	u32 i;

	buf[0] = cpu_to_le32(node->cur_state);
	rc = put_entry(buf, माप(u32), 1, fp);
	अगर (rc)
		वापस rc;

	buf[0] = cpu_to_le32(node->expr.len);
	rc = put_entry(buf, माप(u32), 1, fp);
	अगर (rc)
		वापस rc;

	क्रम (i = 0; i < node->expr.len; i++) अणु
		buf[0] = cpu_to_le32(node->expr.nodes[i].expr_type);
		buf[1] = cpu_to_le32(node->expr.nodes[i].bool);
		rc = put_entry(buf, माप(u32), 2, fp);
		अगर (rc)
			वापस rc;
	पूर्ण

	rc = cond_ग_लिखो_av_list(p, &node->true_list, fp);
	अगर (rc)
		वापस rc;
	rc = cond_ग_लिखो_av_list(p, &node->false_list, fp);
	अगर (rc)
		वापस rc;

	वापस 0;
पूर्ण

पूर्णांक cond_ग_लिखो_list(काष्ठा policydb *p, व्योम *fp)
अणु
	u32 i;
	__le32 buf[1];
	पूर्णांक rc;

	buf[0] = cpu_to_le32(p->cond_list_len);
	rc = put_entry(buf, माप(u32), 1, fp);
	अगर (rc)
		वापस rc;

	क्रम (i = 0; i < p->cond_list_len; i++) अणु
		rc = cond_ग_लिखो_node(p, &p->cond_list[i], fp);
		अगर (rc)
			वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

व्योम cond_compute_xperms(काष्ठा avtab *ctab, काष्ठा avtab_key *key,
		काष्ठा extended_perms_decision *xpermd)
अणु
	काष्ठा avtab_node *node;

	अगर (!ctab || !key || !xpermd)
		वापस;

	क्रम (node = avtab_search_node(ctab, key); node;
			node = avtab_search_node_next(node, key->specअगरied)) अणु
		अगर (node->key.specअगरied & AVTAB_ENABLED)
			services_compute_xperms_decision(xpermd, node);
	पूर्ण
	वापस;

पूर्ण
/* Determine whether additional permissions are granted by the conditional
 * av table, and अगर so, add them to the result
 */
व्योम cond_compute_av(काष्ठा avtab *ctab, काष्ठा avtab_key *key,
		काष्ठा av_decision *avd, काष्ठा extended_perms *xperms)
अणु
	काष्ठा avtab_node *node;

	अगर (!ctab || !key || !avd)
		वापस;

	क्रम (node = avtab_search_node(ctab, key); node;
				node = avtab_search_node_next(node, key->specअगरied)) अणु
		अगर ((u16)(AVTAB_ALLOWED|AVTAB_ENABLED) ==
		    (node->key.specअगरied & (AVTAB_ALLOWED|AVTAB_ENABLED)))
			avd->allowed |= node->datum.u.data;
		अगर ((u16)(AVTAB_AUDITDENY|AVTAB_ENABLED) ==
		    (node->key.specअगरied & (AVTAB_AUDITDENY|AVTAB_ENABLED)))
			/* Since a '0' in an auditdeny mask represents a
			 * permission we करो NOT want to audit (करोntaudit), we use
			 * the '&' operand to ensure that all '0's in the mask
			 * are retained (much unlike the allow and auditallow हालs).
			 */
			avd->auditdeny &= node->datum.u.data;
		अगर ((u16)(AVTAB_AUDITALLOW|AVTAB_ENABLED) ==
		    (node->key.specअगरied & (AVTAB_AUDITALLOW|AVTAB_ENABLED)))
			avd->auditallow |= node->datum.u.data;
		अगर (xperms && (node->key.specअगरied & AVTAB_ENABLED) &&
				(node->key.specअगरied & AVTAB_XPERMS))
			services_compute_xperms_drivers(xperms, node);
	पूर्ण
पूर्ण

अटल पूर्णांक cond_dup_av_list(काष्ठा cond_av_list *new,
			काष्ठा cond_av_list *orig,
			काष्ठा avtab *avtab)
अणु
	u32 i;

	स_रखो(new, 0, माप(*new));

	new->nodes = kसुस्मृति(orig->len, माप(*new->nodes), GFP_KERNEL);
	अगर (!new->nodes)
		वापस -ENOMEM;

	क्रम (i = 0; i < orig->len; i++) अणु
		new->nodes[i] = avtab_insert_nonunique(avtab,
						       &orig->nodes[i]->key,
						       &orig->nodes[i]->datum);
		अगर (!new->nodes[i])
			वापस -ENOMEM;
		new->len++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक duplicate_policydb_cond_list(काष्ठा policydb *newp,
					काष्ठा policydb *origp)
अणु
	पूर्णांक rc, i, j;

	rc = avtab_alloc_dup(&newp->te_cond_avtab, &origp->te_cond_avtab);
	अगर (rc)
		वापस rc;

	newp->cond_list_len = 0;
	newp->cond_list = kसुस्मृति(origp->cond_list_len,
				माप(*newp->cond_list),
				GFP_KERNEL);
	अगर (!newp->cond_list)
		जाओ error;

	क्रम (i = 0; i < origp->cond_list_len; i++) अणु
		काष्ठा cond_node *newn = &newp->cond_list[i];
		काष्ठा cond_node *orign = &origp->cond_list[i];

		newp->cond_list_len++;

		newn->cur_state = orign->cur_state;
		newn->expr.nodes = kसुस्मृति(orign->expr.len,
					माप(*newn->expr.nodes), GFP_KERNEL);
		अगर (!newn->expr.nodes)
			जाओ error;
		क्रम (j = 0; j < orign->expr.len; j++)
			newn->expr.nodes[j] = orign->expr.nodes[j];
		newn->expr.len = orign->expr.len;

		rc = cond_dup_av_list(&newn->true_list, &orign->true_list,
				&newp->te_cond_avtab);
		अगर (rc)
			जाओ error;

		rc = cond_dup_av_list(&newn->false_list, &orign->false_list,
				&newp->te_cond_avtab);
		अगर (rc)
			जाओ error;
	पूर्ण

	वापस 0;

error:
	avtab_destroy(&newp->te_cond_avtab);
	cond_list_destroy(newp);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक cond_bools_destroy(व्योम *key, व्योम *datum, व्योम *args)
अणु
	/* key was not copied so no need to मुक्त here */
	kमुक्त(datum);
	वापस 0;
पूर्ण

अटल पूर्णांक cond_bools_copy(काष्ठा hashtab_node *new, काष्ठा hashtab_node *orig, व्योम *args)
अणु
	काष्ठा cond_bool_datum *datum;

	datum = kmemdup(orig->datum, माप(काष्ठा cond_bool_datum),
			GFP_KERNEL);
	अगर (!datum)
		वापस -ENOMEM;

	new->key = orig->key; /* No need to copy, never modअगरied */
	new->datum = datum;
	वापस 0;
पूर्ण

अटल पूर्णांक cond_bools_index(व्योम *key, व्योम *datum, व्योम *args)
अणु
	काष्ठा cond_bool_datum *booldatum, **cond_bool_array;

	booldatum = datum;
	cond_bool_array = args;
	cond_bool_array[booldatum->value - 1] = booldatum;

	वापस 0;
पूर्ण

अटल पूर्णांक duplicate_policydb_bools(काष्ठा policydb *newdb,
				काष्ठा policydb *orig)
अणु
	काष्ठा cond_bool_datum **cond_bool_array;
	पूर्णांक rc;

	cond_bool_array = kदो_स्मृति_array(orig->p_bools.nprim,
					माप(*orig->bool_val_to_काष्ठा),
					GFP_KERNEL);
	अगर (!cond_bool_array)
		वापस -ENOMEM;

	rc = hashtab_duplicate(&newdb->p_bools.table, &orig->p_bools.table,
			cond_bools_copy, cond_bools_destroy, शून्य);
	अगर (rc) अणु
		kमुक्त(cond_bool_array);
		वापस -ENOMEM;
	पूर्ण

	hashtab_map(&newdb->p_bools.table, cond_bools_index, cond_bool_array);
	newdb->bool_val_to_काष्ठा = cond_bool_array;

	newdb->p_bools.nprim = orig->p_bools.nprim;

	वापस 0;
पूर्ण

व्योम cond_policydb_destroy_dup(काष्ठा policydb *p)
अणु
	hashtab_map(&p->p_bools.table, cond_bools_destroy, शून्य);
	hashtab_destroy(&p->p_bools.table);
	cond_policydb_destroy(p);
पूर्ण

पूर्णांक cond_policydb_dup(काष्ठा policydb *new, काष्ठा policydb *orig)
अणु
	cond_policydb_init(new);

	अगर (duplicate_policydb_bools(new, orig))
		वापस -ENOMEM;

	अगर (duplicate_policydb_cond_list(new, orig)) अणु
		cond_policydb_destroy_dup(new);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण
