<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * tree.c: Basic device tree traversal/scanning क्रम the Linux
 *         prom library.
 *
 * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 */

#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/module.h>

#समावेश <यंत्र/खोलोprom.h>
#समावेश <यंत्र/oplib.h>

बाह्य व्योम restore_current(व्योम);

अटल अक्षर promlib_buf[128];

/* Internal version of prom_अ_लोhild that करोes not alter वापस values. */
अटल phandle __prom_अ_लोhild(phandle node)
अणु
	अचिन्हित दीर्घ flags;
	phandle cnode;

	spin_lock_irqsave(&prom_lock, flags);
	cnode = prom_nodeops->no_child(node);
	restore_current();
	spin_unlock_irqrestore(&prom_lock, flags);

	वापस cnode;
पूर्ण

/* Return the child of node 'node' or zero अगर no this node has no
 * direct descendent.
 */
phandle prom_अ_लोhild(phandle node)
अणु
	phandle cnode;

	अगर ((s32)node == -1)
		वापस 0;

	cnode = __prom_अ_लोhild(node);
	अगर (cnode == 0 || (s32)cnode == -1)
		वापस 0;

	वापस cnode;
पूर्ण
EXPORT_SYMBOL(prom_अ_लोhild);

/* Internal version of prom_माला_लोibling that करोes not alter वापस values. */
अटल phandle __prom_माला_लोibling(phandle node)
अणु
	अचिन्हित दीर्घ flags;
	phandle cnode;

	spin_lock_irqsave(&prom_lock, flags);
	cnode = prom_nodeops->no_nextnode(node);
	restore_current();
	spin_unlock_irqrestore(&prom_lock, flags);

	वापस cnode;
पूर्ण

/* Return the next sibling of node 'node' or zero अगर no more siblings
 * at this level of depth in the tree.
 */
phandle prom_माला_लोibling(phandle node)
अणु
	phandle sibnode;

	अगर ((s32)node == -1)
		वापस 0;

	sibnode = __prom_माला_लोibling(node);
	अगर (sibnode == 0 || (s32)sibnode == -1)
		वापस 0;

	वापस sibnode;
पूर्ण
EXPORT_SYMBOL(prom_माला_लोibling);

/* Return the length in bytes of property 'prop' at node 'node'.
 * Return -1 on error.
 */
पूर्णांक prom_getproplen(phandle node, स्थिर अक्षर *prop)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	अगर((!node) || (!prop))
		वापस -1;
		
	spin_lock_irqsave(&prom_lock, flags);
	ret = prom_nodeops->no_proplen(node, prop);
	restore_current();
	spin_unlock_irqrestore(&prom_lock, flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(prom_getproplen);

/* Acquire a property 'prop' at node 'node' and place it in
 * 'buffer' which has a size of 'bufsize'.  If the acquisition
 * was successful the length will be वापसed, अन्यथा -1 is वापसed.
 */
पूर्णांक prom_getproperty(phandle node, स्थिर अक्षर *prop, अक्षर *buffer, पूर्णांक bufsize)
अणु
	पूर्णांक plen, ret;
	अचिन्हित दीर्घ flags;

	plen = prom_getproplen(node, prop);
	अगर((plen > bufsize) || (plen == 0) || (plen == -1))
		वापस -1;
	/* Ok, things seem all right. */
	spin_lock_irqsave(&prom_lock, flags);
	ret = prom_nodeops->no_getprop(node, prop, buffer);
	restore_current();
	spin_unlock_irqrestore(&prom_lock, flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(prom_getproperty);

/* Acquire an पूर्णांकeger property and वापस its value.  Returns -1
 * on failure.
 */
पूर्णांक prom_getपूर्णांक(phandle node, अक्षर *prop)
अणु
	अटल पूर्णांक पूर्णांकprop;

	अगर(prom_getproperty(node, prop, (अक्षर *) &पूर्णांकprop, माप(पूर्णांक)) != -1)
		वापस पूर्णांकprop;

	वापस -1;
पूर्ण
EXPORT_SYMBOL(prom_getपूर्णांक);

/* Acquire an पूर्णांकeger property, upon error वापस the passed शेष
 * पूर्णांकeger.
 */
पूर्णांक prom_getपूर्णांकशेष(phandle node, अक्षर *property, पूर्णांक deflt)
अणु
	पूर्णांक retval;

	retval = prom_getपूर्णांक(node, property);
	अगर(retval == -1) वापस deflt;

	वापस retval;
पूर्ण
EXPORT_SYMBOL(prom_getपूर्णांकशेष);

/* Acquire a boolean property, 1=TRUE 0=FALSE. */
पूर्णांक prom_getbool(phandle node, अक्षर *prop)
अणु
	पूर्णांक retval;

	retval = prom_getproplen(node, prop);
	अगर(retval == -1) वापस 0;
	वापस 1;
पूर्ण
EXPORT_SYMBOL(prom_getbool);

/* Acquire a property whose value is a string, वापसs a null
 * string on error.  The अक्षर poपूर्णांकer is the user supplied string
 * buffer.
 */
व्योम prom_माला_लोtring(phandle node, अक्षर *prop, अक्षर *user_buf, पूर्णांक ubuf_size)
अणु
	पूर्णांक len;

	len = prom_getproperty(node, prop, user_buf, ubuf_size);
	अगर(len != -1) वापस;
	user_buf[0] = 0;
पूर्ण
EXPORT_SYMBOL(prom_माला_लोtring);


/* Search siblings at 'node_start' क्रम a node with name
 * 'nodename'.  Return node अगर successful, zero अगर not.
 */
phandle prom_searchsiblings(phandle node_start, अक्षर *nodename)
अणु

	phandle thisnode;
	पूर्णांक error;

	क्रम(thisnode = node_start; thisnode;
	    thisnode=prom_माला_लोibling(thisnode)) अणु
		error = prom_getproperty(thisnode, "name", promlib_buf,
					 माप(promlib_buf));
		/* Should this ever happen? */
		अगर(error == -1) जारी;
		अगर(म_भेद(nodename, promlib_buf)==0) वापस thisnode;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(prom_searchsiblings);

/* Interal version of nextprop that करोes not alter वापस values. */
अटल अक्षर *__prom_nextprop(phandle node, अक्षर * oprop)
अणु
	अचिन्हित दीर्घ flags;
	अक्षर *prop;

	spin_lock_irqsave(&prom_lock, flags);
	prop = prom_nodeops->no_nextprop(node, oprop);
	restore_current();
	spin_unlock_irqrestore(&prom_lock, flags);

	वापस prop;
पूर्ण

/* Return the property type string after property type 'oprop'
 * at node 'node' .  Returns empty string अगर no more
 * property types क्रम this node.
 */
अक्षर *prom_nextprop(phandle node, अक्षर *oprop, अक्षर *buffer)
अणु
	अगर (node == 0 || (s32)node == -1)
		वापस "";

	वापस __prom_nextprop(node, oprop);
पूर्ण
EXPORT_SYMBOL(prom_nextprop);

phandle prom_finddevice(अक्षर *name)
अणु
	अक्षर nbuf[128];
	अक्षर *s = name, *d;
	phandle node = prom_root_node, node2;
	अचिन्हित पूर्णांक which_io, phys_addr;
	काष्ठा linux_prom_रेजिस्टरs reg[PROMREG_MAX];

	जबतक (*s++) अणु
		अगर (!*s) वापस node; /* path '.../' is legal */
		node = prom_अ_लोhild(node);

		क्रम (d = nbuf; *s != 0 && *s != '@' && *s != '/';)
			*d++ = *s++;
		*d = 0;
		
		node = prom_searchsiblings(node, nbuf);
		अगर (!node)
			वापस 0;

		अगर (*s == '@') अणु
			अगर (है_षष्ठादशक(s[1]) && s[2] == ',') अणु
				which_io = simple_म_से_अदीर्घ(s+1, शून्य, 16);
				phys_addr = simple_म_से_अदीर्घ(s+3, &d, 16);
				अगर (d != s + 3 && (!*d || *d == '/')
				    && d <= s + 3 + 8) अणु
					node2 = node;
					जबतक (node2 && (s32)node2 != -1) अणु
						अगर (prom_getproperty (node2, "reg", (अक्षर *)reg, माप (reg)) > 0) अणु
							अगर (which_io == reg[0].which_io && phys_addr == reg[0].phys_addr) अणु
								node = node2;
								अवरोध;
							पूर्ण
						पूर्ण
						node2 = prom_माला_लोibling(node2);
						अगर (!node2 || (s32)node2 == -1)
							अवरोध;
						node2 = prom_searchsiblings(prom_माला_लोibling(node2), nbuf);
					पूर्ण
				पूर्ण
			पूर्ण
			जबतक (*s != 0 && *s != '/') s++;
		पूर्ण
	पूर्ण
	वापस node;
पूर्ण
EXPORT_SYMBOL(prom_finddevice);

/* Set property 'pname' at node 'node' to value 'value' which has a length
 * of 'size' bytes.  Return the number of bytes the prom accepted.
 */
पूर्णांक prom_setprop(phandle node, स्थिर अक्षर *pname, अक्षर *value, पूर्णांक size)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (size == 0)
		वापस 0;
	अगर ((pname == शून्य) || (value == शून्य))
		वापस 0;
	spin_lock_irqsave(&prom_lock, flags);
	ret = prom_nodeops->no_setprop(node, pname, value, size);
	restore_current();
	spin_unlock_irqrestore(&prom_lock, flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(prom_setprop);

phandle prom_inst2pkg(पूर्णांक inst)
अणु
	phandle node;
	अचिन्हित दीर्घ flags;
	
	spin_lock_irqsave(&prom_lock, flags);
	node = (*romvec->pv_v2devops.v2_inst2pkg)(inst);
	restore_current();
	spin_unlock_irqrestore(&prom_lock, flags);
	अगर ((s32)node == -1)
		वापस 0;
	वापस node;
पूर्ण
