<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * tree.c: Basic device tree traversal/scanning क्रम the Linux
 *         prom library.
 *
 * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 * Copyright (C) 1996,1997 Jakub Jelinek (jj@sunsite.mff.cuni.cz)
 */

#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/खोलोprom.h>
#समावेश <यंत्र/oplib.h>
#समावेश <यंत्र/ldc.h>

अटल phandle prom_node_to_node(स्थिर अक्षर *type, phandle node)
अणु
	अचिन्हित दीर्घ args[5];

	args[0] = (अचिन्हित दीर्घ) type;
	args[1] = 1;
	args[2] = 1;
	args[3] = (अचिन्हित पूर्णांक) node;
	args[4] = (अचिन्हित दीर्घ) -1;

	p1275_cmd_direct(args);

	वापस (phandle) args[4];
पूर्ण

/* Return the child of node 'node' or zero अगर no this node has no
 * direct descendent.
 */
अंतरभूत phandle __prom_अ_लोhild(phandle node)
अणु
	वापस prom_node_to_node("child", node);
पूर्ण

phandle prom_अ_लोhild(phandle node)
अणु
	phandle cnode;

	अगर ((s32)node == -1)
		वापस 0;
	cnode = __prom_अ_लोhild(node);
	अगर ((s32)cnode == -1)
		वापस 0;
	वापस cnode;
पूर्ण
EXPORT_SYMBOL(prom_अ_लोhild);

अंतरभूत phandle prom_getparent(phandle node)
अणु
	phandle cnode;

	अगर ((s32)node == -1)
		वापस 0;
	cnode = prom_node_to_node("parent", node);
	अगर ((s32)cnode == -1)
		वापस 0;
	वापस cnode;
पूर्ण

/* Return the next sibling of node 'node' or zero अगर no more siblings
 * at this level of depth in the tree.
 */
अंतरभूत phandle __prom_माला_लोibling(phandle node)
अणु
	वापस prom_node_to_node(prom_peer_name, node);
पूर्ण

phandle prom_माला_लोibling(phandle node)
अणु
	phandle sibnode;

	अगर ((s32)node == -1)
		वापस 0;
	sibnode = __prom_माला_लोibling(node);
	अगर ((s32)sibnode == -1)
		वापस 0;

	वापस sibnode;
पूर्ण
EXPORT_SYMBOL(prom_माला_लोibling);

/* Return the length in bytes of property 'prop' at node 'node'.
 * Return -1 on error.
 */
पूर्णांक prom_getproplen(phandle node, स्थिर अक्षर *prop)
अणु
	अचिन्हित दीर्घ args[6];

	अगर (!node || !prop)
		वापस -1;

	args[0] = (अचिन्हित दीर्घ) "getproplen";
	args[1] = 2;
	args[2] = 1;
	args[3] = (अचिन्हित पूर्णांक) node;
	args[4] = (अचिन्हित दीर्घ) prop;
	args[5] = (अचिन्हित दीर्घ) -1;

	p1275_cmd_direct(args);

	वापस (पूर्णांक) args[5];
पूर्ण
EXPORT_SYMBOL(prom_getproplen);

/* Acquire a property 'prop' at node 'node' and place it in
 * 'buffer' which has a size of 'bufsize'.  If the acquisition
 * was successful the length will be वापसed, अन्यथा -1 is वापसed.
 */
पूर्णांक prom_getproperty(phandle node, स्थिर अक्षर *prop,
		     अक्षर *buffer, पूर्णांक bufsize)
अणु
	अचिन्हित दीर्घ args[8];
	पूर्णांक plen;

	plen = prom_getproplen(node, prop);
	अगर ((plen > bufsize) || (plen == 0) || (plen == -1))
		वापस -1;

	args[0] = (अचिन्हित दीर्घ) prom_getprop_name;
	args[1] = 4;
	args[2] = 1;
	args[3] = (अचिन्हित पूर्णांक) node;
	args[4] = (अचिन्हित दीर्घ) prop;
	args[5] = (अचिन्हित दीर्घ) buffer;
	args[6] = bufsize;
	args[7] = (अचिन्हित दीर्घ) -1;

	p1275_cmd_direct(args);

	वापस (पूर्णांक) args[7];
पूर्ण
EXPORT_SYMBOL(prom_getproperty);

/* Acquire an पूर्णांकeger property and वापस its value.  Returns -1
 * on failure.
 */
पूर्णांक prom_getपूर्णांक(phandle node, स्थिर अक्षर *prop)
अणु
	पूर्णांक पूर्णांकprop;

	अगर (prom_getproperty(node, prop, (अक्षर *) &पूर्णांकprop, माप(पूर्णांक)) != -1)
		वापस पूर्णांकprop;

	वापस -1;
पूर्ण
EXPORT_SYMBOL(prom_getपूर्णांक);

/* Acquire an पूर्णांकeger property, upon error वापस the passed शेष
 * पूर्णांकeger.
 */

पूर्णांक prom_getपूर्णांकशेष(phandle node, स्थिर अक्षर *property, पूर्णांक deflt)
अणु
	पूर्णांक retval;

	retval = prom_getपूर्णांक(node, property);
	अगर (retval == -1)
		वापस deflt;

	वापस retval;
पूर्ण
EXPORT_SYMBOL(prom_getपूर्णांकशेष);

/* Acquire a boolean property, 1=TRUE 0=FALSE. */
पूर्णांक prom_getbool(phandle node, स्थिर अक्षर *prop)
अणु
	पूर्णांक retval;

	retval = prom_getproplen(node, prop);
	अगर (retval == -1)
		वापस 0;
	वापस 1;
पूर्ण
EXPORT_SYMBOL(prom_getbool);

/* Acquire a property whose value is a string, वापसs a null
 * string on error.  The अक्षर poपूर्णांकer is the user supplied string
 * buffer.
 */
व्योम prom_माला_लोtring(phandle node, स्थिर अक्षर *prop, अक्षर *user_buf,
		पूर्णांक ubuf_size)
अणु
	पूर्णांक len;

	len = prom_getproperty(node, prop, user_buf, ubuf_size);
	अगर (len != -1)
		वापस;
	user_buf[0] = 0;
पूर्ण
EXPORT_SYMBOL(prom_माला_लोtring);

/* Does the device at node 'node' have name 'name'?
 * YES = 1   NO = 0
 */
पूर्णांक prom_nodematch(phandle node, स्थिर अक्षर *name)
अणु
	अक्षर namebuf[128];
	prom_getproperty(node, "name", namebuf, माप(namebuf));
	अगर (म_भेद(namebuf, name) == 0)
		वापस 1;
	वापस 0;
पूर्ण

/* Search siblings at 'node_start' क्रम a node with name
 * 'nodename'.  Return node अगर successful, zero अगर not.
 */
phandle prom_searchsiblings(phandle node_start, स्थिर अक्षर *nodename)
अणु
	phandle thisnode;
	पूर्णांक error;
	अक्षर promlib_buf[128];

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

अटल स्थिर अक्षर *prom_nextprop_name = "nextprop";

/* Return the first property type क्रम node 'node'.
 * buffer should be at least 32B in length
 */
अक्षर *prom_firstprop(phandle node, अक्षर *buffer)
अणु
	अचिन्हित दीर्घ args[7];

	*buffer = 0;
	अगर ((s32)node == -1)
		वापस buffer;

	args[0] = (अचिन्हित दीर्घ) prom_nextprop_name;
	args[1] = 3;
	args[2] = 1;
	args[3] = (अचिन्हित पूर्णांक) node;
	args[4] = 0;
	args[5] = (अचिन्हित दीर्घ) buffer;
	args[6] = (अचिन्हित दीर्घ) -1;

	p1275_cmd_direct(args);

	वापस buffer;
पूर्ण
EXPORT_SYMBOL(prom_firstprop);

/* Return the property type string after property type 'oprop'
 * at node 'node' .  Returns शून्य string अगर no more
 * property types क्रम this node.
 */
अक्षर *prom_nextprop(phandle node, स्थिर अक्षर *oprop, अक्षर *buffer)
अणु
	अचिन्हित दीर्घ args[7];
	अक्षर buf[32];

	अगर ((s32)node == -1) अणु
		*buffer = 0;
		वापस buffer;
	पूर्ण
	अगर (oprop == buffer) अणु
		म_नकल (buf, oprop);
		oprop = buf;
	पूर्ण

	args[0] = (अचिन्हित दीर्घ) prom_nextprop_name;
	args[1] = 3;
	args[2] = 1;
	args[3] = (अचिन्हित पूर्णांक) node;
	args[4] = (अचिन्हित दीर्घ) oprop;
	args[5] = (अचिन्हित दीर्घ) buffer;
	args[6] = (अचिन्हित दीर्घ) -1;

	p1275_cmd_direct(args);

	वापस buffer;
पूर्ण
EXPORT_SYMBOL(prom_nextprop);

phandle prom_finddevice(स्थिर अक्षर *name)
अणु
	अचिन्हित दीर्घ args[5];

	अगर (!name)
		वापस 0;
	args[0] = (अचिन्हित दीर्घ) "finddevice";
	args[1] = 1;
	args[2] = 1;
	args[3] = (अचिन्हित दीर्घ) name;
	args[4] = (अचिन्हित दीर्घ) -1;

	p1275_cmd_direct(args);

	वापस (पूर्णांक) args[4];
पूर्ण
EXPORT_SYMBOL(prom_finddevice);

पूर्णांक prom_node_has_property(phandle node, स्थिर अक्षर *prop)
अणु
	अक्षर buf [32];
        
	*buf = 0;
	करो अणु
		prom_nextprop(node, buf, buf);
		अगर (!म_भेद(buf, prop))
			वापस 1;
	पूर्ण जबतक (*buf);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(prom_node_has_property);

/* Set property 'pname' at node 'node' to value 'value' which has a length
 * of 'size' bytes.  Return the number of bytes the prom accepted.
 */
पूर्णांक
prom_setprop(phandle node, स्थिर अक्षर *pname, अक्षर *value, पूर्णांक size)
अणु
	अचिन्हित दीर्घ args[8];

	अगर (size == 0)
		वापस 0;
	अगर ((pname == 0) || (value == 0))
		वापस 0;
	
#अगर_घोषित CONFIG_SUN_LDOMS
	अगर (lकरोm_करोमुख्यing_enabled) अणु
		lकरोm_set_var(pname, value);
		वापस 0;
	पूर्ण
#पूर्ण_अगर
	args[0] = (अचिन्हित दीर्घ) "setprop";
	args[1] = 4;
	args[2] = 1;
	args[3] = (अचिन्हित पूर्णांक) node;
	args[4] = (अचिन्हित दीर्घ) pname;
	args[5] = (अचिन्हित दीर्घ) value;
	args[6] = size;
	args[7] = (अचिन्हित दीर्घ) -1;

	p1275_cmd_direct(args);

	वापस (पूर्णांक) args[7];
पूर्ण
EXPORT_SYMBOL(prom_setprop);

अंतरभूत phandle prom_inst2pkg(पूर्णांक inst)
अणु
	अचिन्हित दीर्घ args[5];
	phandle node;
	
	args[0] = (अचिन्हित दीर्घ) "instance-to-package";
	args[1] = 1;
	args[2] = 1;
	args[3] = (अचिन्हित पूर्णांक) inst;
	args[4] = (अचिन्हित दीर्घ) -1;

	p1275_cmd_direct(args);

	node = (पूर्णांक) args[4];
	अगर ((s32)node == -1)
		वापस 0;
	वापस node;
पूर्ण

पूर्णांक prom_ihandle2path(पूर्णांक handle, अक्षर *buffer, पूर्णांक bufsize)
अणु
	अचिन्हित दीर्घ args[7];

	args[0] = (अचिन्हित दीर्घ) "instance-to-path";
	args[1] = 3;
	args[2] = 1;
	args[3] = (अचिन्हित पूर्णांक) handle;
	args[4] = (अचिन्हित दीर्घ) buffer;
	args[5] = bufsize;
	args[6] = (अचिन्हित दीर्घ) -1;

	p1275_cmd_direct(args);

	वापस (पूर्णांक) args[6];
पूर्ण
