<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * starfire.c: Starfire/E10000 support.
 *
 * Copyright (C) 1998 David S. Miller (davem@redhat.com)
 * Copyright (C) 2000 Anton Blanअक्षरd (anton@samba.org)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/oplib.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/upa.h>
#समावेश <यंत्र/starfire.h>

/*
 * A few places around the kernel check this to see अगर
 * they need to call us to करो things in a Starfire specअगरic
 * way.
 */
पूर्णांक this_is_starfire = 0;

व्योम check_अगर_starfire(व्योम)
अणु
	phandle ssnode = prom_finddevice("/ssp-serial");
	अगर (ssnode != 0 && (s32)ssnode != -1)
		this_is_starfire = 1;
पूर्ण

/*
 * Each Starfire board has 32 रेजिस्टरs which perक्रमm translation
 * and delivery of traditional पूर्णांकerrupt packets पूर्णांकo the extended
 * Starfire hardware क्रमmat.  Essentially UPAID's now have 2 more
 * bits than in all previous Sun5 प्रणालीs.
 */
काष्ठा starfire_irqinfo अणु
	अचिन्हित दीर्घ imap_slots[32];
	अचिन्हित दीर्घ tregs[32];
	काष्ठा starfire_irqinfo *next;
	पूर्णांक upaid, hwmid;
पूर्ण;

अटल काष्ठा starfire_irqinfo *sflist = शून्य;

/* Beam me up Scott(McNeil)y... */
व्योम starfire_hookup(पूर्णांक upaid)
अणु
	काष्ठा starfire_irqinfo *p;
	अचिन्हित दीर्घ treg_base, hwmid, i;

	p = kदो_स्मृति(माप(*p), GFP_KERNEL);
	अगर (!p) अणु
		prom_म_लिखो("starfire_hookup: No memory, this is insane.\n");
		prom_halt();
	पूर्ण
	treg_base = 0x100fc000000UL;
	hwmid = ((upaid & 0x3c) << 1) |
		((upaid & 0x40) >> 4) |
		(upaid & 0x3);
	p->hwmid = hwmid;
	treg_base += (hwmid << 33UL);
	treg_base += 0x200UL;
	क्रम (i = 0; i < 32; i++) अणु
		p->imap_slots[i] = 0UL;
		p->tregs[i] = treg_base + (i * 0x10UL);
		/* Lets play it safe and not overग_लिखो existing mappings */
		अगर (upa_पढ़ोl(p->tregs[i]) != 0)
			p->imap_slots[i] = 0xdeadbeaf;
	पूर्ण
	p->upaid = upaid;
	p->next = sflist;
	sflist = p;
पूर्ण

अचिन्हित पूर्णांक starfire_translate(अचिन्हित दीर्घ imap,
				अचिन्हित पूर्णांक upaid)
अणु
	काष्ठा starfire_irqinfo *p;
	अचिन्हित पूर्णांक bus_hwmid;
	अचिन्हित पूर्णांक i;

	bus_hwmid = (((अचिन्हित दीर्घ)imap) >> 33) & 0x7f;
	क्रम (p = sflist; p != शून्य; p = p->next)
		अगर (p->hwmid == bus_hwmid)
			अवरोध;
	अगर (p == शून्य) अणु
		prom_म_लिखो("XFIRE: Cannot find irqinfo for imap %016lx\n",
			    ((अचिन्हित दीर्घ)imap));
		prom_halt();
	पूर्ण
	क्रम (i = 0; i < 32; i++) अणु
		अगर (p->imap_slots[i] == imap ||
		    p->imap_slots[i] == 0UL)
			अवरोध;
	पूर्ण
	अगर (i == 32) अणु
		prपूर्णांकk("starfire_translate: Are you kidding me?\n");
		panic("Lucy in the sky....");
	पूर्ण
	p->imap_slots[i] = imap;

	/* map to real upaid */
	upaid = (((upaid & 0x3c) << 1) |
		 ((upaid & 0x40) >> 4) |
		 (upaid & 0x3));

	upa_ग_लिखोl(upaid, p->tregs[i]);

	वापस i;
पूर्ण
