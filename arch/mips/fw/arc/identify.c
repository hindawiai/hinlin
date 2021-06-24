<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * identअगरy.c: identअगरy machine by looking up प्रणाली identअगरier
 *
 * Copyright (C) 1998 Thomas Bogenकरोerfer
 *
 * This code is based on arch/mips/sgi/kernel/प्रणाली.c, which is
 *
 * Copyright (C) 1996 David S. Miller (davem@davemloft.net)
 */
#समावेश <linux/bug.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>

#समावेश <यंत्र/sgialib.h>
#समावेश <यंत्र/bootinfo.h>

काष्ठा smatch अणु
	अक्षर *arcname;
	अक्षर *liname;
	पूर्णांक flags;
पूर्ण;

अटल काष्ठा smatch mach_table[] = अणु
	अणु
		.arcname	= "SGI-IP22",
		.liname		= "SGI Indy",
		.flags		= PROM_FLAG_ARCS,
	पूर्ण, अणु
		.arcname	= "SGI-IP28",
		.liname		= "SGI IP28",
		.flags		= PROM_FLAG_ARCS,
	पूर्ण, अणु
		.arcname	= "SGI-IP30",
		.liname		= "SGI Octane",
		.flags		= PROM_FLAG_ARCS,
	पूर्ण, अणु
		.arcname	= "SGI-IP32",
		.liname		= "SGI O2",
		.flags		= PROM_FLAG_ARCS,
	पूर्ण, अणु
		.arcname	= "Microsoft-Jazz",
		.liname		= "Jazz MIPS_Magnum_4000",
		.flags		= 0,
	पूर्ण, अणु
		.arcname	= "PICA-61",
		.liname		= "Jazz Acer_PICA_61",
		.flags		= 0,
	पूर्ण, अणु
		.arcname	= "RM200PCI",
		.liname		= "SNI RM200_PCI",
		.flags		= PROM_FLAG_DONT_FREE_TEMP,
	पूर्ण, अणु
		.arcname	= "RM200PCI-R5K",
		.liname		= "SNI RM200_PCI-R5K",
		.flags		= PROM_FLAG_DONT_FREE_TEMP,
	पूर्ण
पूर्ण;

पूर्णांक prom_flags;

अटल काष्ठा smatch * __init string_to_mach(स्थिर अक्षर *s)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(mach_table); i++) अणु
		अगर (!म_भेद(s, mach_table[i].arcname))
			वापस &mach_table[i];
	पूर्ण

	panic("Yeee, could not determine architecture type <%s>", s);
पूर्ण

अक्षर *प्रणाली_type;

स्थिर अक्षर *get_प्रणाली_type(व्योम)
अणु
	वापस प्रणाली_type;
पूर्ण

अटल pcomponent * __init ArcGetChild(pcomponent *Current)
अणु
	वापस (pcomponent *) ARC_CALL1(child_component, Current);
पूर्ण

व्योम __init prom_identअगरy_arch(व्योम)
अणु
	pcomponent *p;
	काष्ठा smatch *mach;
	स्थिर अक्षर *iname;

	/*
	 * The root component tells us what machine architecture we have here.
	 */
	p = ArcGetChild(PROM_शून्य_COMPONENT);
	अगर (p == शून्य) अणु
		iname = "Unknown";
	पूर्ण अन्यथा
		iname = (अक्षर *) (दीर्घ) p->iname;

	prपूर्णांकk("ARCH: %s\n", iname);
	mach = string_to_mach(iname);
	प्रणाली_type = mach->liname;

	prom_flags = mach->flags;
पूर्ण
