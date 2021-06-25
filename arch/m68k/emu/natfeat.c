<शैली गुरु>
/*
 * natfeat.c - ARAnyM hardware support via Native Features (natfeats)
 *
 * Copyright (c) 2005 Petr Stehlik of ARAnyM dev team
 *
 * Reworked क्रम Linux by Roman Zippel <zippel@linux-m68k.org>
 *
 * This software may be used and distributed according to the terms of
 * the GNU General Public License (GPL), incorporated herein by reference.
 */

#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/console.h>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/natfeat.h>

बाह्य दीर्घ nf_get_id_phys(अचिन्हित दीर्घ feature_name);

यंत्र("\n"
"	.global nf_get_id_phys,nf_call\n"
"nf_get_id_phys:\n"
"	.short	0x7300\n"
"	rts\n"
"nf_call:\n"
"	.short	0x7301\n"
"	rts\n"
"1:	moveq.l	#0,%d0\n"
"	rts\n"
"	.section __ex_table,\"a\"\n"
"	.long	nf_get_id_phys,1b\n"
"	.long	nf_call,1b\n"
"	.previous");
EXPORT_SYMBOL_GPL(nf_call);

दीर्घ nf_get_id(स्थिर अक्षर *feature_name)
अणु
	/* feature_name may be in vदो_स्मृति()ed memory, so make a copy */
	अक्षर name_copy[32];
	माप_प्रकार n;

	n = strlcpy(name_copy, feature_name, माप(name_copy));
	अगर (n >= माप(name_copy))
		वापस 0;

	वापस nf_get_id_phys(virt_to_phys(name_copy));
पूर्ण
EXPORT_SYMBOL_GPL(nf_get_id);

व्योम nfprपूर्णांक(स्थिर अक्षर *fmt, ...)
अणु
	अटल अक्षर buf[256];
	बहु_सूची ap;
	पूर्णांक n;

	बहु_शुरू(ap, fmt);
	n = vsnम_लिखो(buf, 256, fmt, ap);
	nf_call(nf_get_id("NF_STDERR"), virt_to_phys(buf));
	बहु_पूर्ण(ap);
पूर्ण

अटल व्योम nf_घातeroff(व्योम)
अणु
	दीर्घ id = nf_get_id("NF_SHUTDOWN");

	अगर (id)
		nf_call(id);
पूर्ण

व्योम __init nf_init(व्योम)
अणु
	अचिन्हित दीर्घ id, version;
	अक्षर buf[256];

	id = nf_get_id("NF_VERSION");
	अगर (!id)
		वापस;
	version = nf_call(id);

	id = nf_get_id("NF_NAME");
	अगर (!id)
		वापस;
	nf_call(id, virt_to_phys(buf), 256);
	buf[255] = 0;

	pr_info("NatFeats found (%s, %lu.%lu)\n", buf, version >> 16,
		version & 0xffff);

	mach_घातer_off = nf_घातeroff;
पूर्ण
