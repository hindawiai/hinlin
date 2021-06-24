<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* pdt.c: OF PROM device tree support code.
 *
 * Paul Mackerras	August 1996.
 * Copyright (C) 1996-2005 Paul Mackerras.
 *
 *  Adapted क्रम 64bit PowerPC by Dave Engebretsen and Peter Bergner.
 *    अणुengebret|bergnerपूर्ण@us.ibm.com
 *
 *  Adapted क्रम sparc by David S. Miller davem@davemloft.net
 *  Adapted क्रम multiple architectures by Andres Salomon <dilinger@queued.net>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/of_pdt.h>

अटल काष्ठा of_pdt_ops *of_pdt_prom_ops __initdata;

#अगर defined(CONFIG_SPARC)
अचिन्हित पूर्णांक of_pdt_unique_id __initdata;

#घोषणा of_pdt_incr_unique_id(p) करो अणु \
	(p)->unique_id = of_pdt_unique_id++; \
पूर्ण जबतक (0)

अटल अक्षर * __init of_pdt_build_full_name(काष्ठा device_node *dp)
अणु
	वापस build_path_component(dp);
पूर्ण

#अन्यथा /* CONFIG_SPARC */

अटल अंतरभूत व्योम of_pdt_incr_unique_id(व्योम *p) अणु पूर्ण
अटल अंतरभूत व्योम irq_trans_init(काष्ठा device_node *dp) अणु पूर्ण

अटल अक्षर * __init of_pdt_build_full_name(काष्ठा device_node *dp)
अणु
	अटल पूर्णांक failsafe_id = 0; /* क्रम generating unique names on failure */
	स्थिर अक्षर *name;
	अक्षर path[256];
	अक्षर *buf;
	पूर्णांक len;

	अगर (!of_pdt_prom_ops->pkg2path(dp->phandle, path, माप(path), &len)) अणु
		name = kbasename(path);
		buf = prom_early_alloc(म_माप(name) + 1);
		म_नकल(buf, name);
		वापस buf;
	पूर्ण

	name = of_get_property(dp, "name", &len);
	buf = prom_early_alloc(len + 16);
	प्र_लिखो(buf, "%s@unknown%i", name, failsafe_id++);
	pr_err("%s: pkg2path failed; assigning %s\n", __func__, buf);
	वापस buf;
पूर्ण

#पूर्ण_अगर /* !CONFIG_SPARC */

अटल काष्ठा property * __init of_pdt_build_one_prop(phandle node, अक्षर *prev,
					       अक्षर *special_name,
					       व्योम *special_val,
					       पूर्णांक special_len)
अणु
	अटल काष्ठा property *पंचांगp = शून्य;
	काष्ठा property *p;
	पूर्णांक err;

	अगर (पंचांगp) अणु
		p = पंचांगp;
		स_रखो(p, 0, माप(*p) + 32);
		पंचांगp = शून्य;
	पूर्ण अन्यथा अणु
		p = prom_early_alloc(माप(काष्ठा property) + 32);
		of_pdt_incr_unique_id(p);
	पूर्ण

	p->name = (अक्षर *) (p + 1);
	अगर (special_name) अणु
		म_नकल(p->name, special_name);
		p->length = special_len;
		p->value = prom_early_alloc(special_len);
		स_नकल(p->value, special_val, special_len);
	पूर्ण अन्यथा अणु
		err = of_pdt_prom_ops->nextprop(node, prev, p->name);
		अगर (err) अणु
			पंचांगp = p;
			वापस शून्य;
		पूर्ण
		p->length = of_pdt_prom_ops->getproplen(node, p->name);
		अगर (p->length <= 0) अणु
			p->length = 0;
		पूर्ण अन्यथा अणु
			पूर्णांक len;

			p->value = prom_early_alloc(p->length + 1);
			len = of_pdt_prom_ops->getproperty(node, p->name,
					p->value, p->length);
			अगर (len <= 0)
				p->length = 0;
			((अचिन्हित अक्षर *)p->value)[p->length] = '\0';
		पूर्ण
	पूर्ण
	वापस p;
पूर्ण

अटल काष्ठा property * __init of_pdt_build_prop_list(phandle node)
अणु
	काष्ठा property *head, *tail;

	head = tail = of_pdt_build_one_prop(node, शून्य,
				     ".node", &node, माप(node));

	tail->next = of_pdt_build_one_prop(node, शून्य, शून्य, शून्य, 0);
	tail = tail->next;
	जबतक(tail) अणु
		tail->next = of_pdt_build_one_prop(node, tail->name,
					    शून्य, शून्य, 0);
		tail = tail->next;
	पूर्ण

	वापस head;
पूर्ण

अटल अक्षर * __init of_pdt_get_one_property(phandle node, स्थिर अक्षर *name)
अणु
	अक्षर *buf = "<NULL>";
	पूर्णांक len;

	len = of_pdt_prom_ops->getproplen(node, name);
	अगर (len > 0) अणु
		buf = prom_early_alloc(len);
		len = of_pdt_prom_ops->getproperty(node, name, buf, len);
	पूर्ण

	वापस buf;
पूर्ण

अटल काष्ठा device_node * __init of_pdt_create_node(phandle node,
						    काष्ठा device_node *parent)
अणु
	काष्ठा device_node *dp;

	अगर (!node)
		वापस शून्य;

	dp = prom_early_alloc(माप(*dp));
	of_node_init(dp);
	of_pdt_incr_unique_id(dp);
	dp->parent = parent;

	dp->name = of_pdt_get_one_property(node, "name");
	dp->phandle = node;

	dp->properties = of_pdt_build_prop_list(node);

	dp->full_name = of_pdt_build_full_name(dp);

	irq_trans_init(dp);

	वापस dp;
पूर्ण

अटल काष्ठा device_node * __init of_pdt_build_tree(काष्ठा device_node *parent,
						   phandle node)
अणु
	काष्ठा device_node *ret = शून्य, *prev_sibling = शून्य;
	काष्ठा device_node *dp;

	जबतक (1) अणु
		dp = of_pdt_create_node(node, parent);
		अगर (!dp)
			अवरोध;

		अगर (prev_sibling)
			prev_sibling->sibling = dp;

		अगर (!ret)
			ret = dp;
		prev_sibling = dp;

		dp->child = of_pdt_build_tree(dp, of_pdt_prom_ops->अ_लोhild(node));

		node = of_pdt_prom_ops->माला_लोibling(node);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम * __init kernel_tree_alloc(u64 size, u64 align)
अणु
	वापस prom_early_alloc(size);
पूर्ण

व्योम __init of_pdt_build_devicetree(phandle root_node, काष्ठा of_pdt_ops *ops)
अणु
	BUG_ON(!ops);
	of_pdt_prom_ops = ops;

	of_root = of_pdt_create_node(root_node, शून्य);
	of_root->full_name = "/";

	of_root->child = of_pdt_build_tree(of_root,
				of_pdt_prom_ops->अ_लोhild(of_root->phandle));

	/* Get poपूर्णांकer to "/chosen" and "/aliases" nodes क्रम use everywhere */
	of_alias_scan(kernel_tree_alloc);
पूर्ण
