<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Procedures क्रम creating, accessing and पूर्णांकerpreting the device tree.
 *
 * Paul Mackerras	August 1996.
 * Copyright (C) 1996-2005 Paul Mackerras.
 * 
 *  Adapted क्रम 64bit PowerPC by Dave Engebretsen and Peter Bergner.
 *    अणुengebret|bergnerपूर्ण@us.ibm.com 
 *
 *  Adapted क्रम sparc32 by David S. Miller davem@davemloft.net
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/memblock.h>

#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/oplib.h>
#समावेश <यंत्र/leon.h>
#समावेश <यंत्र/leon_amba.h>

#समावेश "prom.h"

व्योम * __init prom_early_alloc(अचिन्हित दीर्घ size)
अणु
	व्योम *ret;

	ret = memblock_alloc(size, SMP_CACHE_BYTES);
	अगर (!ret)
		panic("%s: Failed to allocate %lu bytes\n", __func__, size);

	prom_early_allocated += size;

	वापस ret;
पूर्ण

/* The following routines deal with the black magic of fully naming a
 * node.
 *
 * Certain well known named nodes are just the simple name string.
 *
 * Actual devices have an address specअगरier appended to the base name
 * string, like this "foo@addr".  The "addr" can be in any number of
 * क्रमmats, and the platक्रमm plus the type of the node determine the
 * क्रमmat and how it is स्थिरructed.
 *
 * For children of the ROOT node, the naming convention is fixed and
 * determined by whether this is a sun4u or sun4v प्रणाली.
 *
 * For children of other nodes, it is bus type specअगरic.  So
 * we walk up the tree until we discover a "device_type" property
 * we recognize and we go from there.
 */
अटल व्योम __init sparc32_path_component(काष्ठा device_node *dp, अक्षर *पंचांगp_buf)
अणु
	स्थिर अक्षर *name = of_get_property(dp, "name", शून्य);
	काष्ठा linux_prom_रेजिस्टरs *regs;
	काष्ठा property *rprop;

	rprop = of_find_property(dp, "reg", शून्य);
	अगर (!rprop)
		वापस;

	regs = rprop->value;
	प्र_लिखो(पंचांगp_buf, "%s@%x,%x",
		name,
		regs->which_io, regs->phys_addr);
पूर्ण

/* "name@slot,offset"  */
अटल व्योम __init sbus_path_component(काष्ठा device_node *dp, अक्षर *पंचांगp_buf)
अणु
	स्थिर अक्षर *name = of_get_property(dp, "name", शून्य);
	काष्ठा linux_prom_रेजिस्टरs *regs;
	काष्ठा property *prop;

	prop = of_find_property(dp, "reg", शून्य);
	अगर (!prop)
		वापस;

	regs = prop->value;
	प्र_लिखो(पंचांगp_buf, "%s@%x,%x",
		name,
		regs->which_io,
		regs->phys_addr);
पूर्ण

/* "name@devnum[,func]" */
अटल व्योम __init pci_path_component(काष्ठा device_node *dp, अक्षर *पंचांगp_buf)
अणु
	स्थिर अक्षर *name = of_get_property(dp, "name", शून्य);
	काष्ठा linux_prom_pci_रेजिस्टरs *regs;
	काष्ठा property *prop;
	अचिन्हित पूर्णांक devfn;

	prop = of_find_property(dp, "reg", शून्य);
	अगर (!prop)
		वापस;

	regs = prop->value;
	devfn = (regs->phys_hi >> 8) & 0xff;
	अगर (devfn & 0x07) अणु
		प्र_लिखो(पंचांगp_buf, "%s@%x,%x",
			name,
			devfn >> 3,
			devfn & 0x07);
	पूर्ण अन्यथा अणु
		प्र_लिखो(पंचांगp_buf, "%s@%x",
			name,
			devfn >> 3);
	पूर्ण
पूर्ण

/* "name@addrhi,addrlo" */
अटल व्योम __init ebus_path_component(काष्ठा device_node *dp, अक्षर *पंचांगp_buf)
अणु
	स्थिर अक्षर *name = of_get_property(dp, "name", शून्य);
	काष्ठा linux_prom_रेजिस्टरs *regs;
	काष्ठा property *prop;

	prop = of_find_property(dp, "reg", शून्य);
	अगर (!prop)
		वापस;

	regs = prop->value;

	प्र_लिखो(पंचांगp_buf, "%s@%x,%x",
		name,
		regs->which_io, regs->phys_addr);
पूर्ण

/* "name@irq,addrlo" */
अटल व्योम __init ambapp_path_component(काष्ठा device_node *dp, अक्षर *पंचांगp_buf)
अणु
	स्थिर अक्षर *name = of_get_property(dp, "name", शून्य);
	काष्ठा amba_prom_रेजिस्टरs *regs;
	अचिन्हित पूर्णांक *पूर्णांकr;
	अचिन्हित पूर्णांक reg0;
	काष्ठा property *prop;
	पूर्णांक पूर्णांकerrupt = 0;

	/* In order to get a unique ID in the device tree (multiple AMBA devices
	 * may have the same name) the node number is prपूर्णांकed
	 */
	prop = of_find_property(dp, "reg", शून्य);
	अगर (!prop) अणु
		reg0 = (अचिन्हित पूर्णांक)dp->phandle;
	पूर्ण अन्यथा अणु
		regs = prop->value;
		reg0 = regs->phys_addr;
	पूर्ण

	/* Not all cores have Interrupt */
	prop = of_find_property(dp, "interrupts", शून्य);
	अगर (!prop)
		पूर्णांकr = &पूर्णांकerrupt; /* IRQ0 करोes not exist */
	अन्यथा
		पूर्णांकr = prop->value;

	प्र_लिखो(पंचांगp_buf, "%s@%x,%x", name, *पूर्णांकr, reg0);
पूर्ण

अटल व्योम __init __build_path_component(काष्ठा device_node *dp, अक्षर *पंचांगp_buf)
अणु
	काष्ठा device_node *parent = dp->parent;

	अगर (parent != शून्य) अणु
		अगर (of_node_is_type(parent, "pci") ||
		    of_node_is_type(parent, "pciex"))
			वापस pci_path_component(dp, पंचांगp_buf);
		अगर (of_node_is_type(parent, "sbus"))
			वापस sbus_path_component(dp, पंचांगp_buf);
		अगर (of_node_is_type(parent, "ebus"))
			वापस ebus_path_component(dp, पंचांगp_buf);
		अगर (of_node_is_type(parent, "ambapp"))
			वापस ambapp_path_component(dp, पंचांगp_buf);

		/* "isa" is handled with platक्रमm naming */
	पूर्ण

	/* Use platक्रमm naming convention.  */
	वापस sparc32_path_component(dp, पंचांगp_buf);
पूर्ण

अक्षर * __init build_path_component(काष्ठा device_node *dp)
अणु
	स्थिर अक्षर *name = of_get_property(dp, "name", शून्य);
	अक्षर पंचांगp_buf[64], *n;

	पंचांगp_buf[0] = '\0';
	__build_path_component(dp, पंचांगp_buf);
	अगर (पंचांगp_buf[0] == '\0')
		म_नकल(पंचांगp_buf, name);

	n = prom_early_alloc(म_माप(पंचांगp_buf) + 1);
	म_नकल(n, पंचांगp_buf);

	वापस n;
पूर्ण

बाह्य व्योम restore_current(व्योम);

व्योम __init of_console_init(व्योम)
अणु
	अक्षर *msg = "OF stdout device is: %s\n";
	काष्ठा device_node *dp;
	अचिन्हित दीर्घ flags;
	स्थिर अक्षर *type;
	phandle node;
	पूर्णांक skip, पंचांगp, fd;

	of_console_path = prom_early_alloc(256);

	चयन (prom_vers) अणु
	हाल PROM_V0:
		skip = 0;
		चयन (*romvec->pv_मानक_निकास) अणु
		हाल PROMDEV_SCREEN:
			type = "display";
			अवरोध;

		हाल PROMDEV_TTYB:
			skip = 1;
			fallthrough;

		हाल PROMDEV_TTYA:
			type = "serial";
			अवरोध;

		शेष:
			prom_म_लिखो("Invalid PROM_V0 stdout value %u\n",
				    *romvec->pv_मानक_निकास);
			prom_halt();
		पूर्ण

		पंचांगp = skip;
		क्रम_each_node_by_type(dp, type) अणु
			अगर (!पंचांगp--)
				अवरोध;
		पूर्ण
		अगर (!dp) अणु
			prom_म_लिखो("Cannot find PROM_V0 console node.\n");
			prom_halt();
		पूर्ण
		of_console_device = dp;

		प्र_लिखो(of_console_path, "%pOF", dp);
		अगर (!म_भेद(type, "serial")) अणु
			म_जोड़ो(of_console_path,
			       (skip ? ":b" : ":a"));
		पूर्ण
		अवरोध;

	शेष:
	हाल PROM_V2:
	हाल PROM_V3:
		fd = *romvec->pv_v2bootargs.fd_मानक_निकास;

		spin_lock_irqsave(&prom_lock, flags);
		node = (*romvec->pv_v2devops.v2_inst2pkg)(fd);
		restore_current();
		spin_unlock_irqrestore(&prom_lock, flags);

		अगर (!node) अणु
			prom_म_लिखो("Cannot resolve stdout node from "
				    "instance %08x.\n", fd);
			prom_halt();
		पूर्ण
		dp = of_find_node_by_phandle(node);

		अगर (!of_node_is_type(dp, "display") &&
		    !of_node_is_type(dp, "serial")) अणु
			prom_म_लिखो("Console device_type is neither display "
				    "nor serial.\n");
			prom_halt();
		पूर्ण

		of_console_device = dp;

		अगर (prom_vers == PROM_V2) अणु
			प्र_लिखो(of_console_path, "%pOF", dp);
			चयन (*romvec->pv_मानक_निकास) अणु
			हाल PROMDEV_TTYA:
				म_जोड़ो(of_console_path, ":a");
				अवरोध;
			हाल PROMDEV_TTYB:
				म_जोड़ो(of_console_path, ":b");
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			स्थिर अक्षर *path;

			dp = of_find_node_by_path("/");
			path = of_get_property(dp, "stdout-path", शून्य);
			अगर (!path) अणु
				prom_म_लिखो("No stdout-path in root node.\n");
				prom_halt();
			पूर्ण
			म_नकल(of_console_path, path);
		पूर्ण
		अवरोध;
	पूर्ण

	of_console_options = म_खोजप(of_console_path, ':');
	अगर (of_console_options) अणु
		of_console_options++;
		अगर (*of_console_options == '\0')
			of_console_options = शून्य;
	पूर्ण

	prपूर्णांकk(msg, of_console_path);
पूर्ण

व्योम __init of_fill_in_cpu_data(व्योम)
अणु
पूर्ण

व्योम __init irq_trans_init(काष्ठा device_node *dp)
अणु
पूर्ण
