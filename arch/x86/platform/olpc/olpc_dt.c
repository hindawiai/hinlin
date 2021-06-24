<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * OLPC-specअगरic OFW device tree support code.
 *
 * Paul Mackerras	August 1996.
 * Copyright (C) 1996-2005 Paul Mackerras.
 *
 *  Adapted क्रम 64bit PowerPC by Dave Engebretsen and Peter Bergner.
 *    अणुengebret|bergnerपूर्ण@us.ibm.com
 *
 *  Adapted क्रम sparc by David S. Miller davem@davemloft.net
 *  Adapted क्रम x86/OLPC by Andres Salomon <dilinger@queued.net>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/memblock.h>
#समावेश <linux/of.h>
#समावेश <linux/of_pdt.h>
#समावेश <यंत्र/olpc.h>
#समावेश <यंत्र/olpc_ofw.h>

अटल phandle __init olpc_dt_माला_लोibling(phandle node)
अणु
	स्थिर व्योम *args[] = अणु (व्योम *)node पूर्ण;
	व्योम *res[] = अणु &node पूर्ण;

	अगर ((s32)node == -1)
		वापस 0;

	अगर (olpc_ofw("peer", args, res) || (s32)node == -1)
		वापस 0;

	वापस node;
पूर्ण

अटल phandle __init olpc_dt_अ_लोhild(phandle node)
अणु
	स्थिर व्योम *args[] = अणु (व्योम *)node पूर्ण;
	व्योम *res[] = अणु &node पूर्ण;

	अगर ((s32)node == -1)
		वापस 0;

	अगर (olpc_ofw("child", args, res) || (s32)node == -1) अणु
		pr_err("PROM: %s: fetching child failed!\n", __func__);
		वापस 0;
	पूर्ण

	वापस node;
पूर्ण

अटल पूर्णांक __init olpc_dt_getproplen(phandle node, स्थिर अक्षर *prop)
अणु
	स्थिर व्योम *args[] = अणु (व्योम *)node, prop पूर्ण;
	पूर्णांक len;
	व्योम *res[] = अणु &len पूर्ण;

	अगर ((s32)node == -1)
		वापस -1;

	अगर (olpc_ofw("getproplen", args, res)) अणु
		pr_err("PROM: %s: getproplen failed!\n", __func__);
		वापस -1;
	पूर्ण

	वापस len;
पूर्ण

अटल पूर्णांक __init olpc_dt_getproperty(phandle node, स्थिर अक्षर *prop,
		अक्षर *buf, पूर्णांक bufsize)
अणु
	पूर्णांक plen;

	plen = olpc_dt_getproplen(node, prop);
	अगर (plen > bufsize || plen < 1) अणु
		वापस -1;
	पूर्ण अन्यथा अणु
		स्थिर व्योम *args[] = अणु (व्योम *)node, prop, buf, (व्योम *)plen पूर्ण;
		व्योम *res[] = अणु &plen पूर्ण;

		अगर (olpc_ofw("getprop", args, res)) अणु
			pr_err("PROM: %s: getprop failed!\n", __func__);
			वापस -1;
		पूर्ण
	पूर्ण

	वापस plen;
पूर्ण

अटल पूर्णांक __init olpc_dt_nextprop(phandle node, अक्षर *prev, अक्षर *buf)
अणु
	स्थिर व्योम *args[] = अणु (व्योम *)node, prev, buf पूर्ण;
	पूर्णांक success;
	व्योम *res[] = अणु &success पूर्ण;

	buf[0] = '\0';

	अगर ((s32)node == -1)
		वापस -1;

	अगर (olpc_ofw("nextprop", args, res) || success != 1)
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक __init olpc_dt_pkg2path(phandle node, अक्षर *buf,
		स्थिर पूर्णांक buflen, पूर्णांक *len)
अणु
	स्थिर व्योम *args[] = अणु (व्योम *)node, buf, (व्योम *)buflen पूर्ण;
	व्योम *res[] = अणु len पूर्ण;

	अगर ((s32)node == -1)
		वापस -1;

	अगर (olpc_ofw("package-to-path", args, res) || *len < 1)
		वापस -1;

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक prom_early_allocated __initdata;

व्योम * __init prom_early_alloc(अचिन्हित दीर्घ size)
अणु
	अटल u8 *mem;
	अटल माप_प्रकार मुक्त_mem;
	व्योम *res;

	अगर (मुक्त_mem < size) अणु
		स्थिर माप_प्रकार chunk_size = max(PAGE_SIZE, size);

		/*
		 * To minimize the number of allocations, grab at least
		 * PAGE_SIZE of memory (that's an arbitrary choice that's
		 * fast enough on the platक्रमms we care about जबतक minimizing
		 * wasted booपंचांगem) and hand off chunks of it to callers.
		 */
		res = memblock_alloc(chunk_size, SMP_CACHE_BYTES);
		अगर (!res)
			panic("%s: Failed to allocate %zu bytes\n", __func__,
			      chunk_size);
		BUG_ON(!res);
		prom_early_allocated += chunk_size;
		स_रखो(res, 0, chunk_size);
		मुक्त_mem = chunk_size;
		mem = res;
	पूर्ण

	/* allocate from the local cache */
	मुक्त_mem -= size;
	res = mem;
	mem += size;
	वापस res;
पूर्ण

अटल काष्ठा of_pdt_ops prom_olpc_ops __initdata = अणु
	.nextprop = olpc_dt_nextprop,
	.getproplen = olpc_dt_getproplen,
	.getproperty = olpc_dt_getproperty,
	.अ_लोhild = olpc_dt_अ_लोhild,
	.माला_लोibling = olpc_dt_माला_लोibling,
	.pkg2path = olpc_dt_pkg2path,
पूर्ण;

अटल phandle __init olpc_dt_finddevice(स्थिर अक्षर *path)
अणु
	phandle node;
	स्थिर व्योम *args[] = अणु path पूर्ण;
	व्योम *res[] = अणु &node पूर्ण;

	अगर (olpc_ofw("finddevice", args, res)) अणु
		pr_err("olpc_dt: finddevice failed!\n");
		वापस 0;
	पूर्ण

	अगर ((s32) node == -1)
		वापस 0;

	वापस node;
पूर्ण

अटल पूर्णांक __init olpc_dt_पूर्णांकerpret(स्थिर अक्षर *words)
अणु
	पूर्णांक result;
	स्थिर व्योम *args[] = अणु words पूर्ण;
	व्योम *res[] = अणु &result पूर्ण;

	अगर (olpc_ofw("interpret", args, res)) अणु
		pr_err("olpc_dt: interpret failed!\n");
		वापस -1;
	पूर्ण

	वापस result;
पूर्ण

/*
 * Extract board revision directly from OFW device tree.
 * We can't use olpc_platform_info because that hasn't been set up yet.
 */
अटल u32 __init olpc_dt_get_board_revision(व्योम)
अणु
	phandle node;
	__be32 rev;
	पूर्णांक r;

	node = olpc_dt_finddevice("/");
	अगर (!node)
		वापस 0;

	r = olpc_dt_getproperty(node, "board-revision-int",
				(अक्षर *) &rev, माप(rev));
	अगर (r < 0)
		वापस 0;

	वापस be32_to_cpu(rev);
पूर्ण

अटल पूर्णांक __init olpc_dt_compatible_match(phandle node, स्थिर अक्षर *compat)
अणु
	अक्षर buf[64], *p;
	पूर्णांक plen, len;

	plen = olpc_dt_getproperty(node, "compatible", buf, माप(buf));
	अगर (plen <= 0)
		वापस 0;

	len = म_माप(compat);
	क्रम (p = buf; p < buf + plen; p += म_माप(p) + 1) अणु
		अगर (म_भेद(p, compat) == 0)
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

व्योम __init olpc_dt_fixup(व्योम)
अणु
	phandle node;
	u32 board_rev;

	node = olpc_dt_finddevice("/battery@0");
	अगर (!node)
		वापस;

	board_rev = olpc_dt_get_board_revision();
	अगर (!board_rev)
		वापस;

	अगर (board_rev >= olpc_board_pre(0xd0)) अणु
		/* XO-1.5 */

		अगर (olpc_dt_compatible_match(node, "olpc,xo1.5-battery"))
			वापस;

		/* Add olpc,xo1.5-battery compatible marker to battery node */
		olpc_dt_पूर्णांकerpret("\" /battery@0\" find-device");
		olpc_dt_पूर्णांकerpret("  \" olpc,xo1.5-battery\" +compatible");
		olpc_dt_पूर्णांकerpret("device-end");

		अगर (olpc_dt_compatible_match(node, "olpc,xo1-battery")) अणु
			/*
			 * If we have a olpc,xo1-battery compatible, then we're
			 * running a new enough firmware that alपढ़ोy has
			 * the dcon node.
			 */
			वापस;
		पूर्ण

		/* Add dcon device */
		olpc_dt_पूर्णांकerpret("\" /pci/display@1\" find-device");
		olpc_dt_पूर्णांकerpret("  new-device");
		olpc_dt_पूर्णांकerpret("    \" dcon\" device-name");
		olpc_dt_पूर्णांकerpret("    \" olpc,xo1-dcon\" +compatible");
		olpc_dt_पूर्णांकerpret("  finish-device");
		olpc_dt_पूर्णांकerpret("device-end");
	पूर्ण अन्यथा अणु
		/* XO-1 */

		अगर (olpc_dt_compatible_match(node, "olpc,xo1-battery")) अणु
			/*
			 * If we have a olpc,xo1-battery compatible, then we're
			 * running a new enough firmware that alपढ़ोy has
			 * the dcon and RTC nodes.
			 */
			वापस;
		पूर्ण

		/* Add dcon device, mark RTC as olpc,xo1-rtc */
		olpc_dt_पूर्णांकerpret("\" /pci/display@1,1\" find-device");
		olpc_dt_पूर्णांकerpret("  new-device");
		olpc_dt_पूर्णांकerpret("    \" dcon\" device-name");
		olpc_dt_पूर्णांकerpret("    \" olpc,xo1-dcon\" +compatible");
		olpc_dt_पूर्णांकerpret("  finish-device");
		olpc_dt_पूर्णांकerpret("device-end");

		olpc_dt_पूर्णांकerpret("\" /rtc\" find-device");
		olpc_dt_पूर्णांकerpret(" \" olpc,xo1-rtc\" +compatible");
		olpc_dt_पूर्णांकerpret("device-end");
	पूर्ण

	/* Add olpc,xo1-battery compatible marker to battery node */
	olpc_dt_पूर्णांकerpret("\" /battery@0\" find-device");
	olpc_dt_पूर्णांकerpret("  \" olpc,xo1-battery\" +compatible");
	olpc_dt_पूर्णांकerpret("device-end");
पूर्ण

व्योम __init olpc_dt_build_devicetree(व्योम)
अणु
	phandle root;

	अगर (!olpc_ofw_is_installed())
		वापस;

	olpc_dt_fixup();

	root = olpc_dt_माला_लोibling(0);
	अगर (!root) अणु
		pr_err("PROM: unable to get root node from OFW!\n");
		वापस;
	पूर्ण
	of_pdt_build_devicetree(root, &prom_olpc_ops);

	pr_info("PROM DT: Built device tree with %u bytes of memory.\n",
			prom_early_allocated);
पूर्ण
