<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * pSeries_reconfig.c - support क्रम dynamic reconfiguration (including PCI
 * Hotplug and Dynamic Logical Partitioning on RPA platक्रमms).
 *
 * Copyright (C) 2005 Nathan Lynch
 * Copyright (C) 2005 IBM Corporation
 */

#समावेश <linux/kernel.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>

#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/machdep.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/mmu.h>

#समावेश "of_helpers.h"

अटल पूर्णांक pSeries_reconfig_add_node(स्थिर अक्षर *path, काष्ठा property *proplist)
अणु
	काष्ठा device_node *np;
	पूर्णांक err = -ENOMEM;

	np = kzalloc(माप(*np), GFP_KERNEL);
	अगर (!np)
		जाओ out_err;

	np->full_name = kstrdup(kbasename(path), GFP_KERNEL);
	अगर (!np->full_name)
		जाओ out_err;

	np->properties = proplist;
	of_node_set_flag(np, OF_DYNAMIC);
	of_node_init(np);

	np->parent = pseries_of_derive_parent(path);
	अगर (IS_ERR(np->parent)) अणु
		err = PTR_ERR(np->parent);
		जाओ out_err;
	पूर्ण

	err = of_attach_node(np);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "Failed to add device node %s\n", path);
		जाओ out_err;
	पूर्ण

	of_node_put(np->parent);

	वापस 0;

out_err:
	अगर (np) अणु
		of_node_put(np->parent);
		kमुक्त(np->full_name);
		kमुक्त(np);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक pSeries_reconfig_हटाओ_node(काष्ठा device_node *np)
अणु
	काष्ठा device_node *parent, *child;

	parent = of_get_parent(np);
	अगर (!parent)
		वापस -EINVAL;

	अगर ((child = of_get_next_child(np, शून्य))) अणु
		of_node_put(child);
		of_node_put(parent);
		वापस -EBUSY;
	पूर्ण

	of_detach_node(np);
	of_node_put(parent);
	वापस 0;
पूर्ण

/*
 * /proc/घातerpc/ofdt - yucky binary पूर्णांकerface क्रम adding and removing
 * OF device nodes.  Should be deprecated as soon as we get an
 * in-kernel wrapper क्रम the RTAS ibm,configure-connector call.
 */

अटल व्योम release_prop_list(स्थिर काष्ठा property *prop)
अणु
	काष्ठा property *next;
	क्रम (; prop; prop = next) अणु
		next = prop->next;
		kमुक्त(prop->name);
		kमुक्त(prop->value);
		kमुक्त(prop);
	पूर्ण

पूर्ण

/**
 * parse_next_property - process the next property from raw input buffer
 * @buf: input buffer, must be nul-terminated
 * @end: end of the input buffer + 1, क्रम validation
 * @name: वापस value; set to property name in buf
 * @length: वापस value; set to length of value
 * @value: वापस value; set to the property value in buf
 *
 * Note that the caller must make copies of the name and value वापसed,
 * this function करोes no allocation or copying of the data.  Return value
 * is set to the next name in buf, or शून्य on error.
 */
अटल अक्षर * parse_next_property(अक्षर *buf, अक्षर *end, अक्षर **name, पूर्णांक *length,
				  अचिन्हित अक्षर **value)
अणु
	अक्षर *पंचांगp;

	*name = buf;

	पंचांगp = म_अक्षर(buf, ' ');
	अगर (!पंचांगp) अणु
		prपूर्णांकk(KERN_ERR "property parse failed in %s at line %d\n",
		       __func__, __LINE__);
		वापस शून्य;
	पूर्ण
	*पंचांगp = '\0';

	अगर (++पंचांगp >= end) अणु
		prपूर्णांकk(KERN_ERR "property parse failed in %s at line %d\n",
		       __func__, __LINE__);
		वापस शून्य;
	पूर्ण

	/* now we're on the length */
	*length = -1;
	*length = simple_म_से_अदीर्घ(पंचांगp, &पंचांगp, 10);
	अगर (*length == -1) अणु
		prपूर्णांकk(KERN_ERR "property parse failed in %s at line %d\n",
		       __func__, __LINE__);
		वापस शून्य;
	पूर्ण
	अगर (*पंचांगp != ' ' || ++पंचांगp >= end) अणु
		prपूर्णांकk(KERN_ERR "property parse failed in %s at line %d\n",
		       __func__, __LINE__);
		वापस शून्य;
	पूर्ण

	/* now we're on the value */
	*value = पंचांगp;
	पंचांगp += *length;
	अगर (पंचांगp > end) अणु
		prपूर्णांकk(KERN_ERR "property parse failed in %s at line %d\n",
		       __func__, __LINE__);
		वापस शून्य;
	पूर्ण
	अन्यथा अगर (पंचांगp < end && *पंचांगp != ' ' && *tmp != '\0') अणु
		prपूर्णांकk(KERN_ERR "property parse failed in %s at line %d\n",
		       __func__, __LINE__);
		वापस शून्य;
	पूर्ण
	पंचांगp++;

	/* and now we should be on the next name, or the end */
	वापस पंचांगp;
पूर्ण

अटल काष्ठा property *new_property(स्थिर अक्षर *name, स्थिर पूर्णांक length,
				     स्थिर अचिन्हित अक्षर *value, काष्ठा property *last)
अणु
	काष्ठा property *new = kzalloc(माप(*new), GFP_KERNEL);

	अगर (!new)
		वापस शून्य;

	अगर (!(new->name = kstrdup(name, GFP_KERNEL)))
		जाओ cleanup;
	अगर (!(new->value = kदो_स्मृति(length + 1, GFP_KERNEL)))
		जाओ cleanup;

	स_नकल(new->value, value, length);
	*(((अक्षर *)new->value) + length) = 0;
	new->length = length;
	new->next = last;
	वापस new;

cleanup:
	kमुक्त(new->name);
	kमुक्त(new->value);
	kमुक्त(new);
	वापस शून्य;
पूर्ण

अटल पूर्णांक करो_add_node(अक्षर *buf, माप_प्रकार bufsize)
अणु
	अक्षर *path, *end, *name;
	काष्ठा device_node *np;
	काष्ठा property *prop = शून्य;
	अचिन्हित अक्षर* value;
	पूर्णांक length, rv = 0;

	end = buf + bufsize;
	path = buf;
	buf = म_अक्षर(buf, ' ');
	अगर (!buf)
		वापस -EINVAL;
	*buf = '\0';
	buf++;

	अगर ((np = of_find_node_by_path(path))) अणु
		of_node_put(np);
		वापस -EINVAL;
	पूर्ण

	/* rv = build_prop_list(पंचांगp, bufsize - (पंचांगp - buf), &proplist); */
	जबतक (buf < end &&
	       (buf = parse_next_property(buf, end, &name, &length, &value))) अणु
		काष्ठा property *last = prop;

		prop = new_property(name, length, value, last);
		अगर (!prop) अणु
			rv = -ENOMEM;
			prop = last;
			जाओ out;
		पूर्ण
	पूर्ण
	अगर (!buf) अणु
		rv = -EINVAL;
		जाओ out;
	पूर्ण

	rv = pSeries_reconfig_add_node(path, prop);

out:
	अगर (rv)
		release_prop_list(prop);
	वापस rv;
पूर्ण

अटल पूर्णांक करो_हटाओ_node(अक्षर *buf)
अणु
	काष्ठा device_node *node;
	पूर्णांक rv = -ENODEV;

	अगर ((node = of_find_node_by_path(buf)))
		rv = pSeries_reconfig_हटाओ_node(node);

	of_node_put(node);
	वापस rv;
पूर्ण

अटल अक्षर *parse_node(अक्षर *buf, माप_प्रकार bufsize, काष्ठा device_node **npp)
अणु
	अक्षर *handle_str;
	phandle handle;
	*npp = शून्य;

	handle_str = buf;

	buf = म_अक्षर(buf, ' ');
	अगर (!buf)
		वापस शून्य;
	*buf = '\0';
	buf++;

	handle = simple_म_से_अदीर्घ(handle_str, शून्य, 0);

	*npp = of_find_node_by_phandle(handle);
	वापस buf;
पूर्ण

अटल पूर्णांक करो_add_property(अक्षर *buf, माप_प्रकार bufsize)
अणु
	काष्ठा property *prop = शून्य;
	काष्ठा device_node *np;
	अचिन्हित अक्षर *value;
	अक्षर *name, *end;
	पूर्णांक length;
	end = buf + bufsize;
	buf = parse_node(buf, bufsize, &np);

	अगर (!np)
		वापस -ENODEV;

	अगर (parse_next_property(buf, end, &name, &length, &value) == शून्य)
		वापस -EINVAL;

	prop = new_property(name, length, value, शून्य);
	अगर (!prop)
		वापस -ENOMEM;

	of_add_property(np, prop);

	वापस 0;
पूर्ण

अटल पूर्णांक करो_हटाओ_property(अक्षर *buf, माप_प्रकार bufsize)
अणु
	काष्ठा device_node *np;
	अक्षर *पंचांगp;
	buf = parse_node(buf, bufsize, &np);

	अगर (!np)
		वापस -ENODEV;

	पंचांगp = म_अक्षर(buf,' ');
	अगर (पंचांगp)
		*पंचांगp = '\0';

	अगर (म_माप(buf) == 0)
		वापस -EINVAL;

	वापस of_हटाओ_property(np, of_find_property(np, buf, शून्य));
पूर्ण

अटल पूर्णांक करो_update_property(अक्षर *buf, माप_प्रकार bufsize)
अणु
	काष्ठा device_node *np;
	अचिन्हित अक्षर *value;
	अक्षर *name, *end, *next_prop;
	पूर्णांक length;
	काष्ठा property *newprop;
	buf = parse_node(buf, bufsize, &np);
	end = buf + bufsize;

	अगर (!np)
		वापस -ENODEV;

	next_prop = parse_next_property(buf, end, &name, &length, &value);
	अगर (!next_prop)
		वापस -EINVAL;

	अगर (!म_माप(name))
		वापस -ENODEV;

	newprop = new_property(name, length, value, शून्य);
	अगर (!newprop)
		वापस -ENOMEM;

	अगर (!म_भेद(name, "slb-size") || !म_भेद(name, "ibm,slb-size"))
		slb_set_size(*(पूर्णांक *)value);

	वापस of_update_property(np, newprop);
पूर्ण

/**
 * ofdt_ग_लिखो - perक्रमm operations on the Open Firmware device tree
 *
 * @file: not used
 * @buf: command and arguments
 * @count: size of the command buffer
 * @off: not used
 *
 * Operations supported at this समय are addition and removal of
 * whole nodes aदीर्घ with their properties.  Operations on inभागidual
 * properties are not implemented (yet).
 */
अटल sमाप_प्रकार ofdt_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf, माप_प्रकार count,
			  loff_t *off)
अणु
	पूर्णांक rv;
	अक्षर *kbuf;
	अक्षर *पंचांगp;

	kbuf = memdup_user_nul(buf, count);
	अगर (IS_ERR(kbuf))
		वापस PTR_ERR(kbuf);

	पंचांगp = म_अक्षर(kbuf, ' ');
	अगर (!पंचांगp) अणु
		rv = -EINVAL;
		जाओ out;
	पूर्ण
	*पंचांगp = '\0';
	पंचांगp++;

	अगर (!म_भेद(kbuf, "add_node"))
		rv = करो_add_node(पंचांगp, count - (पंचांगp - kbuf));
	अन्यथा अगर (!म_भेद(kbuf, "remove_node"))
		rv = करो_हटाओ_node(पंचांगp);
	अन्यथा अगर (!म_भेद(kbuf, "add_property"))
		rv = करो_add_property(पंचांगp, count - (पंचांगp - kbuf));
	अन्यथा अगर (!म_भेद(kbuf, "remove_property"))
		rv = करो_हटाओ_property(पंचांगp, count - (पंचांगp - kbuf));
	अन्यथा अगर (!म_भेद(kbuf, "update_property"))
		rv = करो_update_property(पंचांगp, count - (पंचांगp - kbuf));
	अन्यथा
		rv = -EINVAL;
out:
	kमुक्त(kbuf);
	वापस rv ? rv : count;
पूर्ण

अटल स्थिर काष्ठा proc_ops ofdt_proc_ops = अणु
	.proc_ग_लिखो	= ofdt_ग_लिखो,
	.proc_lseek	= noop_llseek,
पूर्ण;

/* create /proc/घातerpc/ofdt ग_लिखो-only by root */
अटल पूर्णांक proc_ppc64_create_ofdt(व्योम)
अणु
	काष्ठा proc_dir_entry *ent;

	ent = proc_create("powerpc/ofdt", 0200, शून्य, &ofdt_proc_ops);
	अगर (ent)
		proc_set_size(ent, 0);

	वापस 0;
पूर्ण
machine_device_initcall(pseries, proc_ppc64_create_ofdt);
