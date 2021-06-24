<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* prom_common.c: OF device tree support common code.
 *
 * Paul Mackerras	August 1996.
 * Copyright (C) 1996-2005 Paul Mackerras.
 *
 *  Adapted क्रम 64bit PowerPC by Dave Engebretsen and Peter Bergner.
 *    अणुengebret|bergnerपूर्ण@us.ibm.com
 *
 *  Adapted क्रम sparc by David S. Miller davem@davemloft.net
 */

#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/of_pdt.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/oplib.h>

#समावेश "prom.h"

काष्ठा device_node *of_console_device;
EXPORT_SYMBOL(of_console_device);

अक्षर *of_console_path;
EXPORT_SYMBOL(of_console_path);

अक्षर *of_console_options;
EXPORT_SYMBOL(of_console_options);

पूर्णांक of_getपूर्णांकprop_शेष(काष्ठा device_node *np, स्थिर अक्षर *name, पूर्णांक def)
अणु
	काष्ठा property *prop;
	पूर्णांक len;

	prop = of_find_property(np, name, &len);
	अगर (!prop || len != 4)
		वापस def;

	वापस *(पूर्णांक *) prop->value;
पूर्ण
EXPORT_SYMBOL(of_getपूर्णांकprop_शेष);

DEFINE_MUTEX(of_set_property_mutex);
EXPORT_SYMBOL(of_set_property_mutex);

पूर्णांक of_set_property(काष्ठा device_node *dp, स्थिर अक्षर *name, व्योम *val, पूर्णांक len)
अणु
	काष्ठा property **prevp;
	अचिन्हित दीर्घ flags;
	व्योम *new_val;
	पूर्णांक err;

	new_val = kmemdup(val, len, GFP_KERNEL);
	अगर (!new_val)
		वापस -ENOMEM;

	err = -ENODEV;

	mutex_lock(&of_set_property_mutex);
	raw_spin_lock_irqsave(&devtree_lock, flags);
	prevp = &dp->properties;
	जबतक (*prevp) अणु
		काष्ठा property *prop = *prevp;

		अगर (!strहालcmp(prop->name, name)) अणु
			व्योम *old_val = prop->value;
			पूर्णांक ret;

			ret = prom_setprop(dp->phandle, name, val, len);

			err = -EINVAL;
			अगर (ret >= 0) अणु
				prop->value = new_val;
				prop->length = len;

				अगर (OF_IS_DYNAMIC(prop))
					kमुक्त(old_val);

				OF_MARK_DYNAMIC(prop);

				err = 0;
			पूर्ण
			अवरोध;
		पूर्ण
		prevp = &(*prevp)->next;
	पूर्ण
	raw_spin_unlock_irqrestore(&devtree_lock, flags);
	mutex_unlock(&of_set_property_mutex);

	/* XXX Upate procfs अगर necessary... */

	वापस err;
पूर्ण
EXPORT_SYMBOL(of_set_property);

पूर्णांक of_find_in_proplist(स्थिर अक्षर *list, स्थिर अक्षर *match, पूर्णांक len)
अणु
	जबतक (len > 0) अणु
		पूर्णांक l;

		अगर (!म_भेद(list, match))
			वापस 1;
		l = म_माप(list) + 1;
		list += l;
		len -= l;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(of_find_in_proplist);

/*
 * SPARC32 and SPARC64's prom_nextprop() करो things dअगरferently
 * here, despite sharing the same पूर्णांकerface.  SPARC32 करोesn't fill in 'buf',
 * वापसing शून्य on an error.  SPARC64 fills in 'buf', but sets it to an
 * empty string upon error.
 */
अटल पूर्णांक __init handle_nextprop_quirks(अक्षर *buf, स्थिर अक्षर *name)
अणु
	अगर (!name || म_माप(name) == 0)
		वापस -1;

#अगर_घोषित CONFIG_SPARC32
	म_नकल(buf, name);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक __init prom_common_nextprop(phandle node, अक्षर *prev, अक्षर *buf)
अणु
	स्थिर अक्षर *name;

	buf[0] = '\0';
	name = prom_nextprop(node, prev, buf);
	वापस handle_nextprop_quirks(buf, name);
पूर्ण

अचिन्हित पूर्णांक prom_early_allocated __initdata;

अटल काष्ठा of_pdt_ops prom_sparc_ops __initdata = अणु
	.nextprop = prom_common_nextprop,
	.getproplen = prom_getproplen,
	.getproperty = prom_getproperty,
	.अ_लोhild = prom_अ_लोhild,
	.माला_लोibling = prom_माला_लोibling,
पूर्ण;

व्योम __init prom_build_devicetree(व्योम)
अणु
	of_pdt_build_devicetree(prom_root_node, &prom_sparc_ops);
	of_console_init();

	pr_info("PROM: Built device tree with %u bytes of memory.\n",
			prom_early_allocated);
पूर्ण
