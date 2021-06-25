<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * cistpl.c -- 16-bit PCMCIA Card Inक्रमmation Structure parser
 *
 * The initial developer of the original code is David A. Hinds
 * <dahinds@users.sourceक्रमge.net>.  Portions created by David A. Hinds
 * are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.
 *
 * (C) 1999		David A. Hinds
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/major.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/समयr.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/pci.h>
#समावेश <linux/ioport.h>
#समावेश <linux/पन.स>
#समावेश <linux/security.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <pcmcia/ss.h>
#समावेश <pcmcia/cisreg.h>
#समावेश <pcmcia/cistpl.h>
#समावेश <pcmcia/ds.h>
#समावेश "cs_internal.h"

अटल स्थिर u_अक्षर mantissa[] = अणु
    10, 12, 13, 15, 20, 25, 30, 35,
    40, 45, 50, 55, 60, 70, 80, 90
पूर्ण;

अटल स्थिर u_पूर्णांक exponent[] = अणु
    1, 10, 100, 1000, 10000, 100000, 1000000, 10000000
पूर्ण;

/* Convert an extended speed byte to a समय in nanoseconds */
#घोषणा SPEED_CVT(v) \
    (mantissa[(((v)>>3)&15)-1] * exponent[(v)&7] / 10)
/* Convert a घातer byte to a current in 0.1 microamps */
#घोषणा POWER_CVT(v) \
    (mantissa[((v)>>3)&15] * exponent[(v)&7] / 10)
#घोषणा POWER_SCALE(v)		(exponent[(v)&7])

/* Upper limit on reasonable # of tuples */
#घोषणा MAX_TUPLES		200

/* Bits in IRQInfo1 field */
#घोषणा IRQ_INFO2_VALID		0x10

/* 16-bit CIS? */
अटल पूर्णांक cis_width;
module_param(cis_width, पूर्णांक, 0444);

व्योम release_cis_mem(काष्ठा pcmcia_socket *s)
अणु
	mutex_lock(&s->ops_mutex);
	अगर (s->cis_mem.flags & MAP_ACTIVE) अणु
		s->cis_mem.flags &= ~MAP_ACTIVE;
		s->ops->set_mem_map(s, &s->cis_mem);
		अगर (s->cis_mem.res) अणु
			release_resource(s->cis_mem.res);
			kमुक्त(s->cis_mem.res);
			s->cis_mem.res = शून्य;
		पूर्ण
		iounmap(s->cis_virt);
		s->cis_virt = शून्य;
	पूर्ण
	mutex_unlock(&s->ops_mutex);
पूर्ण

/*
 * set_cis_map() - map the card memory at "card_offset" पूर्णांकo भव space.
 *
 * If flags & MAP_ATTRIB, map the attribute space, otherwise
 * map the memory space.
 *
 * Must be called with ops_mutex held.
 */
अटल व्योम __iomem *set_cis_map(काष्ठा pcmcia_socket *s,
				अचिन्हित पूर्णांक card_offset, अचिन्हित पूर्णांक flags)
अणु
	pccard_mem_map *mem = &s->cis_mem;
	पूर्णांक ret;

	अगर (!(s->features & SS_CAP_STATIC_MAP) && (mem->res == शून्य)) अणु
		mem->res = pcmcia_find_mem_region(0, s->map_size,
						s->map_size, 0, s);
		अगर (mem->res == शून्य) अणु
			dev_notice(&s->dev, "cs: unable to map card memory!\n");
			वापस शून्य;
		पूर्ण
		s->cis_virt = शून्य;
	पूर्ण

	अगर (!(s->features & SS_CAP_STATIC_MAP) && (!s->cis_virt))
		s->cis_virt = ioremap(mem->res->start, s->map_size);

	mem->card_start = card_offset;
	mem->flags = flags;

	ret = s->ops->set_mem_map(s, mem);
	अगर (ret) अणु
		iounmap(s->cis_virt);
		s->cis_virt = शून्य;
		वापस शून्य;
	पूर्ण

	अगर (s->features & SS_CAP_STATIC_MAP) अणु
		अगर (s->cis_virt)
			iounmap(s->cis_virt);
		s->cis_virt = ioremap(mem->अटल_start, s->map_size);
	पूर्ण

	वापस s->cis_virt;
पूर्ण


/* Bits in attr field */
#घोषणा IS_ATTR		1
#घोषणा IS_INसूचीECT	8

/*
 * pcmcia_पढ़ो_cis_mem() - low-level function to पढ़ो CIS memory
 *
 * must be called with ops_mutex held
 */
पूर्णांक pcmcia_पढ़ो_cis_mem(काष्ठा pcmcia_socket *s, पूर्णांक attr, u_पूर्णांक addr,
		 u_पूर्णांक len, व्योम *ptr)
अणु
	व्योम __iomem *sys, *end;
	अचिन्हित अक्षर *buf = ptr;

	dev_dbg(&s->dev, "pcmcia_read_cis_mem(%d, %#x, %u)\n", attr, addr, len);

	अगर (attr & IS_INसूचीECT) अणु
		/* Indirect accesses use a bunch of special रेजिस्टरs at fixed
		   locations in common memory */
		u_अक्षर flags = ICTRL0_COMMON|ICTRL0_AUTOINC|ICTRL0_BYTEGRAN;
		अगर (attr & IS_ATTR) अणु
			addr *= 2;
			flags = ICTRL0_AUTOINC;
		पूर्ण

		sys = set_cis_map(s, 0, MAP_ACTIVE |
				((cis_width) ? MAP_16BIT : 0));
		अगर (!sys) अणु
			dev_dbg(&s->dev, "could not map memory\n");
			स_रखो(ptr, 0xff, len);
			वापस -1;
		पूर्ण

		ग_लिखोb(flags, sys+CISREG_ICTRL0);
		ग_लिखोb(addr & 0xff, sys+CISREG_IADDR0);
		ग_लिखोb((addr>>8) & 0xff, sys+CISREG_IADDR1);
		ग_लिखोb((addr>>16) & 0xff, sys+CISREG_IADDR2);
		ग_लिखोb((addr>>24) & 0xff, sys+CISREG_IADDR3);
		क्रम ( ; len > 0; len--, buf++)
			*buf = पढ़ोb(sys+CISREG_IDATA0);
	पूर्ण अन्यथा अणु
		u_पूर्णांक inc = 1, card_offset, flags;

		अगर (addr > CISTPL_MAX_CIS_SIZE) अणु
			dev_dbg(&s->dev,
				"attempt to read CIS mem at addr %#x", addr);
			स_रखो(ptr, 0xff, len);
			वापस -1;
		पूर्ण

		flags = MAP_ACTIVE | ((cis_width) ? MAP_16BIT : 0);
		अगर (attr) अणु
			flags |= MAP_ATTRIB;
			inc++;
			addr *= 2;
		पूर्ण

		card_offset = addr & ~(s->map_size-1);
		जबतक (len) अणु
			sys = set_cis_map(s, card_offset, flags);
			अगर (!sys) अणु
				dev_dbg(&s->dev, "could not map memory\n");
				स_रखो(ptr, 0xff, len);
				वापस -1;
			पूर्ण
			end = sys + s->map_size;
			sys = sys + (addr & (s->map_size-1));
			क्रम ( ; len > 0; len--, buf++, sys += inc) अणु
				अगर (sys == end)
					अवरोध;
				*buf = पढ़ोb(sys);
			पूर्ण
			card_offset += s->map_size;
			addr = 0;
		पूर्ण
	पूर्ण
	dev_dbg(&s->dev, "  %#2.2x %#2.2x %#2.2x %#2.2x ...\n",
		*(u_अक्षर *)(ptr+0), *(u_अक्षर *)(ptr+1),
		*(u_अक्षर *)(ptr+2), *(u_अक्षर *)(ptr+3));
	वापस 0;
पूर्ण


/*
 * pcmcia_ग_लिखो_cis_mem() - low-level function to ग_लिखो CIS memory
 *
 * Probably only useful क्रम writing one-byte रेजिस्टरs. Must be called
 * with ops_mutex held.
 */
पूर्णांक pcmcia_ग_लिखो_cis_mem(काष्ठा pcmcia_socket *s, पूर्णांक attr, u_पूर्णांक addr,
		   u_पूर्णांक len, व्योम *ptr)
अणु
	व्योम __iomem *sys, *end;
	अचिन्हित अक्षर *buf = ptr;

	dev_dbg(&s->dev,
		"pcmcia_write_cis_mem(%d, %#x, %u)\n", attr, addr, len);

	अगर (attr & IS_INसूचीECT) अणु
		/* Indirect accesses use a bunch of special रेजिस्टरs at fixed
		   locations in common memory */
		u_अक्षर flags = ICTRL0_COMMON|ICTRL0_AUTOINC|ICTRL0_BYTEGRAN;
		अगर (attr & IS_ATTR) अणु
			addr *= 2;
			flags = ICTRL0_AUTOINC;
		पूर्ण

		sys = set_cis_map(s, 0, MAP_ACTIVE |
				((cis_width) ? MAP_16BIT : 0));
		अगर (!sys) अणु
			dev_dbg(&s->dev, "could not map memory\n");
			वापस -EINVAL;
		पूर्ण

		ग_लिखोb(flags, sys+CISREG_ICTRL0);
		ग_लिखोb(addr & 0xff, sys+CISREG_IADDR0);
		ग_लिखोb((addr>>8) & 0xff, sys+CISREG_IADDR1);
		ग_लिखोb((addr>>16) & 0xff, sys+CISREG_IADDR2);
		ग_लिखोb((addr>>24) & 0xff, sys+CISREG_IADDR3);
		क्रम ( ; len > 0; len--, buf++)
			ग_लिखोb(*buf, sys+CISREG_IDATA0);
	पूर्ण अन्यथा अणु
		u_पूर्णांक inc = 1, card_offset, flags;

		flags = MAP_ACTIVE | ((cis_width) ? MAP_16BIT : 0);
		अगर (attr & IS_ATTR) अणु
			flags |= MAP_ATTRIB;
			inc++;
			addr *= 2;
		पूर्ण

		card_offset = addr & ~(s->map_size-1);
		जबतक (len) अणु
			sys = set_cis_map(s, card_offset, flags);
			अगर (!sys) अणु
				dev_dbg(&s->dev, "could not map memory\n");
				वापस -EINVAL;
			पूर्ण

			end = sys + s->map_size;
			sys = sys + (addr & (s->map_size-1));
			क्रम ( ; len > 0; len--, buf++, sys += inc) अणु
				अगर (sys == end)
					अवरोध;
				ग_लिखोb(*buf, sys);
			पूर्ण
			card_offset += s->map_size;
			addr = 0;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण


/*
 * पढ़ो_cis_cache() - पढ़ो CIS memory or its associated cache
 *
 * This is a wrapper around पढ़ो_cis_mem, with the same पूर्णांकerface,
 * but which caches inक्रमmation, क्रम cards whose CIS may not be
 * पढ़ोable all the समय.
 */
अटल पूर्णांक पढ़ो_cis_cache(काष्ठा pcmcia_socket *s, पूर्णांक attr, u_पूर्णांक addr,
			माप_प्रकार len, व्योम *ptr)
अणु
	काष्ठा cis_cache_entry *cis;
	पूर्णांक ret = 0;

	अगर (s->state & SOCKET_CARDBUS)
		वापस -EINVAL;

	mutex_lock(&s->ops_mutex);
	अगर (s->fake_cis) अणु
		अगर (s->fake_cis_len >= addr+len)
			स_नकल(ptr, s->fake_cis+addr, len);
		अन्यथा अणु
			स_रखो(ptr, 0xff, len);
			ret = -EINVAL;
		पूर्ण
		mutex_unlock(&s->ops_mutex);
		वापस ret;
	पूर्ण

	list_क्रम_each_entry(cis, &s->cis_cache, node) अणु
		अगर (cis->addr == addr && cis->len == len && cis->attr == attr) अणु
			स_नकल(ptr, cis->cache, len);
			mutex_unlock(&s->ops_mutex);
			वापस 0;
		पूर्ण
	पूर्ण

	ret = pcmcia_पढ़ो_cis_mem(s, attr, addr, len, ptr);

	अगर (ret == 0) अणु
		/* Copy data पूर्णांकo the cache */
		cis = kदो_स्मृति(माप(काष्ठा cis_cache_entry) + len, GFP_KERNEL);
		अगर (cis) अणु
			cis->addr = addr;
			cis->len = len;
			cis->attr = attr;
			स_नकल(cis->cache, ptr, len);
			list_add(&cis->node, &s->cis_cache);
		पूर्ण
	पूर्ण
	mutex_unlock(&s->ops_mutex);

	वापस ret;
पूर्ण

अटल व्योम
हटाओ_cis_cache(काष्ठा pcmcia_socket *s, पूर्णांक attr, u_पूर्णांक addr, u_पूर्णांक len)
अणु
	काष्ठा cis_cache_entry *cis;

	mutex_lock(&s->ops_mutex);
	list_क्रम_each_entry(cis, &s->cis_cache, node)
		अगर (cis->addr == addr && cis->len == len && cis->attr == attr) अणु
			list_del(&cis->node);
			kमुक्त(cis);
			अवरोध;
		पूर्ण
	mutex_unlock(&s->ops_mutex);
पूर्ण

/**
 * destroy_cis_cache() - destroy the CIS cache
 * @s:		pcmcia_socket क्रम which CIS cache shall be destroyed
 *
 * This destroys the CIS cache but keeps any fake CIS alive. Must be
 * called with ops_mutex held.
 */
व्योम destroy_cis_cache(काष्ठा pcmcia_socket *s)
अणु
	काष्ठा list_head *l, *n;
	काष्ठा cis_cache_entry *cis;

	list_क्रम_each_safe(l, n, &s->cis_cache) अणु
		cis = list_entry(l, काष्ठा cis_cache_entry, node);
		list_del(&cis->node);
		kमुक्त(cis);
	पूर्ण
पूर्ण

/*
 * verअगरy_cis_cache() - करोes the CIS match what is in the CIS cache?
 */
पूर्णांक verअगरy_cis_cache(काष्ठा pcmcia_socket *s)
अणु
	काष्ठा cis_cache_entry *cis;
	अक्षर *buf;
	पूर्णांक ret;

	अगर (s->state & SOCKET_CARDBUS)
		वापस -EINVAL;

	buf = kदो_स्मृति(256, GFP_KERNEL);
	अगर (buf == शून्य) अणु
		dev_warn(&s->dev, "no memory for verifying CIS\n");
		वापस -ENOMEM;
	पूर्ण
	mutex_lock(&s->ops_mutex);
	list_क्रम_each_entry(cis, &s->cis_cache, node) अणु
		पूर्णांक len = cis->len;

		अगर (len > 256)
			len = 256;

		ret = pcmcia_पढ़ो_cis_mem(s, cis->attr, cis->addr, len, buf);
		अगर (ret || स_भेद(buf, cis->cache, len) != 0) अणु
			kमुक्त(buf);
			mutex_unlock(&s->ops_mutex);
			वापस -1;
		पूर्ण
	पूर्ण
	kमुक्त(buf);
	mutex_unlock(&s->ops_mutex);
	वापस 0;
पूर्ण

/*
 * pcmcia_replace_cis() - use a replacement CIS instead of the card's CIS
 *
 * For really bad cards, we provide a facility क्रम uploading a
 * replacement CIS.
 */
पूर्णांक pcmcia_replace_cis(काष्ठा pcmcia_socket *s,
		       स्थिर u8 *data, स्थिर माप_प्रकार len)
अणु
	अगर (len > CISTPL_MAX_CIS_SIZE) अणु
		dev_warn(&s->dev, "replacement CIS too big\n");
		वापस -EINVAL;
	पूर्ण
	mutex_lock(&s->ops_mutex);
	kमुक्त(s->fake_cis);
	s->fake_cis = kदो_स्मृति(len, GFP_KERNEL);
	अगर (s->fake_cis == शून्य) अणु
		dev_warn(&s->dev, "no memory to replace CIS\n");
		mutex_unlock(&s->ops_mutex);
		वापस -ENOMEM;
	पूर्ण
	s->fake_cis_len = len;
	स_नकल(s->fake_cis, data, len);
	dev_info(&s->dev, "Using replacement CIS\n");
	mutex_unlock(&s->ops_mutex);
	वापस 0;
पूर्ण

/* The high-level CIS tuple services */

काष्ठा tuple_flags अणु
	u_पूर्णांक		link_space:4;
	u_पूर्णांक		has_link:1;
	u_पूर्णांक		mfc_fn:3;
	u_पूर्णांक		space:4;
पूर्ण;

#घोषणा LINK_SPACE(f)	(((काष्ठा tuple_flags *)(&(f)))->link_space)
#घोषणा HAS_LINK(f)	(((काष्ठा tuple_flags *)(&(f)))->has_link)
#घोषणा MFC_FN(f)	(((काष्ठा tuple_flags *)(&(f)))->mfc_fn)
#घोषणा SPACE(f)	(((काष्ठा tuple_flags *)(&(f)))->space)

पूर्णांक pccard_get_first_tuple(काष्ठा pcmcia_socket *s, अचिन्हित पूर्णांक function,
			tuple_t *tuple)
अणु
	अगर (!s)
		वापस -EINVAL;

	अगर (!(s->state & SOCKET_PRESENT) || (s->state & SOCKET_CARDBUS))
		वापस -ENODEV;
	tuple->TupleLink = tuple->Flags = 0;

	/* Assume presence of a LONGLINK_C to address 0 */
	tuple->CISOffset = tuple->LinkOffset = 0;
	SPACE(tuple->Flags) = HAS_LINK(tuple->Flags) = 1;

	अगर ((s->functions > 1) && !(tuple->Attributes & TUPLE_RETURN_COMMON)) अणु
		cisdata_t req = tuple->DesiredTuple;
		tuple->DesiredTuple = CISTPL_LONGLINK_MFC;
		अगर (pccard_get_next_tuple(s, function, tuple) == 0) अणु
			tuple->DesiredTuple = CISTPL_LINKTARGET;
			अगर (pccard_get_next_tuple(s, function, tuple) != 0)
				वापस -ENOSPC;
		पूर्ण अन्यथा
			tuple->CISOffset = tuple->TupleLink = 0;
		tuple->DesiredTuple = req;
	पूर्ण
	वापस pccard_get_next_tuple(s, function, tuple);
पूर्ण

अटल पूर्णांक follow_link(काष्ठा pcmcia_socket *s, tuple_t *tuple)
अणु
	u_अक्षर link[5];
	u_पूर्णांक ofs;
	पूर्णांक ret;

	अगर (MFC_FN(tuple->Flags)) अणु
		/* Get indirect link from the MFC tuple */
		ret = पढ़ो_cis_cache(s, LINK_SPACE(tuple->Flags),
				tuple->LinkOffset, 5, link);
		अगर (ret)
			वापस -1;
		ofs = get_unaligned_le32(link + 1);
		SPACE(tuple->Flags) = (link[0] == CISTPL_MFC_ATTR);
		/* Move to the next indirect link */
		tuple->LinkOffset += 5;
		MFC_FN(tuple->Flags)--;
	पूर्ण अन्यथा अगर (HAS_LINK(tuple->Flags)) अणु
		ofs = tuple->LinkOffset;
		SPACE(tuple->Flags) = LINK_SPACE(tuple->Flags);
		HAS_LINK(tuple->Flags) = 0;
	पूर्ण अन्यथा
		वापस -1;

	अगर (SPACE(tuple->Flags)) अणु
		/* This is ugly, but a common CIS error is to code the दीर्घ
		   link offset incorrectly, so we check the right spot... */
		ret = पढ़ो_cis_cache(s, SPACE(tuple->Flags), ofs, 5, link);
		अगर (ret)
			वापस -1;
		अगर ((link[0] == CISTPL_LINKTARGET) && (link[1] >= 3) &&
			(म_भेदन(link+2, "CIS", 3) == 0))
			वापस ofs;
		हटाओ_cis_cache(s, SPACE(tuple->Flags), ofs, 5);
		/* Then, we try the wrong spot... */
		ofs = ofs >> 1;
	पूर्ण
	ret = पढ़ो_cis_cache(s, SPACE(tuple->Flags), ofs, 5, link);
	अगर (ret)
		वापस -1;
	अगर ((link[0] == CISTPL_LINKTARGET) && (link[1] >= 3) &&
		(म_भेदन(link+2, "CIS", 3) == 0))
		वापस ofs;
	हटाओ_cis_cache(s, SPACE(tuple->Flags), ofs, 5);
	वापस -1;
पूर्ण

पूर्णांक pccard_get_next_tuple(काष्ठा pcmcia_socket *s, अचिन्हित पूर्णांक function,
			tuple_t *tuple)
अणु
	u_अक्षर link[2], पंचांगp;
	पूर्णांक ofs, i, attr;
	पूर्णांक ret;

	अगर (!s)
		वापस -EINVAL;
	अगर (!(s->state & SOCKET_PRESENT) || (s->state & SOCKET_CARDBUS))
		वापस -ENODEV;

	link[1] = tuple->TupleLink;
	ofs = tuple->CISOffset + tuple->TupleLink;
	attr = SPACE(tuple->Flags);

	क्रम (i = 0; i < MAX_TUPLES; i++) अणु
		अगर (link[1] == 0xff)
			link[0] = CISTPL_END;
		अन्यथा अणु
			ret = पढ़ो_cis_cache(s, attr, ofs, 2, link);
			अगर (ret)
				वापस -1;
			अगर (link[0] == CISTPL_शून्य) अणु
				ofs++;
				जारी;
			पूर्ण
		पूर्ण

		/* End of chain?  Follow दीर्घ link अगर possible */
		अगर (link[0] == CISTPL_END) अणु
			ofs = follow_link(s, tuple);
			अगर (ofs < 0)
				वापस -ENOSPC;
			attr = SPACE(tuple->Flags);
			ret = पढ़ो_cis_cache(s, attr, ofs, 2, link);
			अगर (ret)
				वापस -1;
		पूर्ण

		/* Is this a link tuple?  Make a note of it */
		अगर ((link[0] == CISTPL_LONGLINK_A) ||
			(link[0] == CISTPL_LONGLINK_C) ||
			(link[0] == CISTPL_LONGLINK_MFC) ||
			(link[0] == CISTPL_LINKTARGET) ||
			(link[0] == CISTPL_INसूचीECT) ||
			(link[0] == CISTPL_NO_LINK)) अणु
			चयन (link[0]) अणु
			हाल CISTPL_LONGLINK_A:
				HAS_LINK(tuple->Flags) = 1;
				LINK_SPACE(tuple->Flags) = attr | IS_ATTR;
				ret = पढ़ो_cis_cache(s, attr, ofs+2, 4,
						&tuple->LinkOffset);
				अगर (ret)
					वापस -1;
				अवरोध;
			हाल CISTPL_LONGLINK_C:
				HAS_LINK(tuple->Flags) = 1;
				LINK_SPACE(tuple->Flags) = attr & ~IS_ATTR;
				ret = पढ़ो_cis_cache(s, attr, ofs+2, 4,
						&tuple->LinkOffset);
				अगर (ret)
					वापस -1;
				अवरोध;
			हाल CISTPL_INसूचीECT:
				HAS_LINK(tuple->Flags) = 1;
				LINK_SPACE(tuple->Flags) = IS_ATTR |
					IS_INसूचीECT;
				tuple->LinkOffset = 0;
				अवरोध;
			हाल CISTPL_LONGLINK_MFC:
				tuple->LinkOffset = ofs + 3;
				LINK_SPACE(tuple->Flags) = attr;
				अगर (function == BIND_FN_ALL) अणु
					/* Follow all the MFC links */
					ret = पढ़ो_cis_cache(s, attr, ofs+2,
							1, &पंचांगp);
					अगर (ret)
						वापस -1;
					MFC_FN(tuple->Flags) = पंचांगp;
				पूर्ण अन्यथा अणु
					/* Follow exactly one of the links */
					MFC_FN(tuple->Flags) = 1;
					tuple->LinkOffset += function * 5;
				पूर्ण
				अवरोध;
			हाल CISTPL_NO_LINK:
				HAS_LINK(tuple->Flags) = 0;
				अवरोध;
			पूर्ण
			अगर ((tuple->Attributes & TUPLE_RETURN_LINK) &&
				(tuple->DesiredTuple == RETURN_FIRST_TUPLE))
				अवरोध;
		पूर्ण अन्यथा
			अगर (tuple->DesiredTuple == RETURN_FIRST_TUPLE)
				अवरोध;

		अगर (link[0] == tuple->DesiredTuple)
			अवरोध;
		ofs += link[1] + 2;
	पूर्ण
	अगर (i == MAX_TUPLES) अणु
		dev_dbg(&s->dev, "cs: overrun in pcmcia_get_next_tuple\n");
		वापस -ENOSPC;
	पूर्ण

	tuple->TupleCode = link[0];
	tuple->TupleLink = link[1];
	tuple->CISOffset = ofs + 2;
	वापस 0;
पूर्ण

पूर्णांक pccard_get_tuple_data(काष्ठा pcmcia_socket *s, tuple_t *tuple)
अणु
	u_पूर्णांक len;
	पूर्णांक ret;

	अगर (!s)
		वापस -EINVAL;

	अगर (tuple->TupleLink < tuple->TupleOffset)
		वापस -ENOSPC;
	len = tuple->TupleLink - tuple->TupleOffset;
	tuple->TupleDataLen = tuple->TupleLink;
	अगर (len == 0)
		वापस 0;
	ret = पढ़ो_cis_cache(s, SPACE(tuple->Flags),
			tuple->CISOffset + tuple->TupleOffset,
			min(len, (u_पूर्णांक) tuple->TupleDataMax),
			tuple->TupleData);
	अगर (ret)
		वापस -1;
	वापस 0;
पूर्ण


/* Parsing routines क्रम inभागidual tuples */

अटल पूर्णांक parse_device(tuple_t *tuple, cistpl_device_t *device)
अणु
	पूर्णांक i;
	u_अक्षर scale;
	u_अक्षर *p, *q;

	p = (u_अक्षर *)tuple->TupleData;
	q = p + tuple->TupleDataLen;

	device->ndev = 0;
	क्रम (i = 0; i < CISTPL_MAX_DEVICES; i++) अणु

		अगर (*p == 0xff)
			अवरोध;
		device->dev[i].type = (*p >> 4);
		device->dev[i].wp = (*p & 0x08) ? 1 : 0;
		चयन (*p & 0x07) अणु
		हाल 0:
			device->dev[i].speed = 0;
			अवरोध;
		हाल 1:
			device->dev[i].speed = 250;
			अवरोध;
		हाल 2:
			device->dev[i].speed = 200;
			अवरोध;
		हाल 3:
			device->dev[i].speed = 150;
			अवरोध;
		हाल 4:
			device->dev[i].speed = 100;
			अवरोध;
		हाल 7:
			अगर (++p == q)
				वापस -EINVAL;
			device->dev[i].speed = SPEED_CVT(*p);
			जबतक (*p & 0x80)
				अगर (++p == q)
					वापस -EINVAL;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		अगर (++p == q)
			वापस -EINVAL;
		अगर (*p == 0xff)
			अवरोध;
		scale = *p & 7;
		अगर (scale == 7)
			वापस -EINVAL;
		device->dev[i].size = ((*p >> 3) + 1) * (512 << (scale*2));
		device->ndev++;
		अगर (++p == q)
			अवरोध;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक parse_checksum(tuple_t *tuple, cistpl_checksum_t *csum)
अणु
	u_अक्षर *p;
	अगर (tuple->TupleDataLen < 5)
		वापस -EINVAL;
	p = (u_अक्षर *) tuple->TupleData;
	csum->addr = tuple->CISOffset + get_unaligned_le16(p) - 2;
	csum->len = get_unaligned_le16(p + 2);
	csum->sum = *(p + 4);
	वापस 0;
पूर्ण


अटल पूर्णांक parse_दीर्घlink(tuple_t *tuple, cistpl_दीर्घlink_t *link)
अणु
	अगर (tuple->TupleDataLen < 4)
		वापस -EINVAL;
	link->addr = get_unaligned_le32(tuple->TupleData);
	वापस 0;
पूर्ण


अटल पूर्णांक parse_दीर्घlink_mfc(tuple_t *tuple, cistpl_दीर्घlink_mfc_t *link)
अणु
	u_अक्षर *p;
	पूर्णांक i;

	p = (u_अक्षर *)tuple->TupleData;

	link->nfn = *p; p++;
	अगर (tuple->TupleDataLen <= link->nfn*5)
		वापस -EINVAL;
	क्रम (i = 0; i < link->nfn; i++) अणु
		link->fn[i].space = *p; p++;
		link->fn[i].addr = get_unaligned_le32(p);
		p += 4;
	पूर्ण
	वापस 0;
पूर्ण


अटल पूर्णांक parse_strings(u_अक्षर *p, u_अक्षर *q, पूर्णांक max,
			 अक्षर *s, u_अक्षर *ofs, u_अक्षर *found)
अणु
	पूर्णांक i, j, ns;

	अगर (p == q)
		वापस -EINVAL;
	ns = 0; j = 0;
	क्रम (i = 0; i < max; i++) अणु
		अगर (*p == 0xff)
			अवरोध;
		ofs[i] = j;
		ns++;
		क्रम (;;) अणु
			s[j++] = (*p == 0xff) ? '\0' : *p;
			अगर ((*p == '\0') || (*p == 0xff))
				अवरोध;
			अगर (++p == q)
				वापस -EINVAL;
		पूर्ण
		अगर ((*p == 0xff) || (++p == q))
			अवरोध;
	पूर्ण
	अगर (found) अणु
		*found = ns;
		वापस 0;
	पूर्ण

	वापस (ns == max) ? 0 : -EINVAL;
पूर्ण


अटल पूर्णांक parse_vers_1(tuple_t *tuple, cistpl_vers_1_t *vers_1)
अणु
	u_अक्षर *p, *q;

	p = (u_अक्षर *)tuple->TupleData;
	q = p + tuple->TupleDataLen;

	vers_1->major = *p; p++;
	vers_1->minor = *p; p++;
	अगर (p >= q)
		वापस -EINVAL;

	वापस parse_strings(p, q, CISTPL_VERS_1_MAX_PROD_STRINGS,
			vers_1->str, vers_1->ofs, &vers_1->ns);
पूर्ण


अटल पूर्णांक parse_altstr(tuple_t *tuple, cistpl_altstr_t *altstr)
अणु
	u_अक्षर *p, *q;

	p = (u_अक्षर *)tuple->TupleData;
	q = p + tuple->TupleDataLen;

	वापस parse_strings(p, q, CISTPL_MAX_ALTSTR_STRINGS,
			altstr->str, altstr->ofs, &altstr->ns);
पूर्ण


अटल पूर्णांक parse_jedec(tuple_t *tuple, cistpl_jedec_t *jedec)
अणु
	u_अक्षर *p, *q;
	पूर्णांक nid;

	p = (u_अक्षर *)tuple->TupleData;
	q = p + tuple->TupleDataLen;

	क्रम (nid = 0; nid < CISTPL_MAX_DEVICES; nid++) अणु
		अगर (p > q-2)
			अवरोध;
		jedec->id[nid].mfr = p[0];
		jedec->id[nid].info = p[1];
		p += 2;
	पूर्ण
	jedec->nid = nid;
	वापस 0;
पूर्ण


अटल पूर्णांक parse_manfid(tuple_t *tuple, cistpl_manfid_t *m)
अणु
	अगर (tuple->TupleDataLen < 4)
		वापस -EINVAL;
	m->manf = get_unaligned_le16(tuple->TupleData);
	m->card = get_unaligned_le16(tuple->TupleData + 2);
	वापस 0;
पूर्ण


अटल पूर्णांक parse_funcid(tuple_t *tuple, cistpl_funcid_t *f)
अणु
	u_अक्षर *p;
	अगर (tuple->TupleDataLen < 2)
		वापस -EINVAL;
	p = (u_अक्षर *)tuple->TupleData;
	f->func = p[0];
	f->sysinit = p[1];
	वापस 0;
पूर्ण


अटल पूर्णांक parse_funce(tuple_t *tuple, cistpl_funce_t *f)
अणु
	u_अक्षर *p;
	पूर्णांक i;
	अगर (tuple->TupleDataLen < 1)
		वापस -EINVAL;
	p = (u_अक्षर *)tuple->TupleData;
	f->type = p[0];
	क्रम (i = 1; i < tuple->TupleDataLen; i++)
		f->data[i-1] = p[i];
	वापस 0;
पूर्ण


अटल पूर्णांक parse_config(tuple_t *tuple, cistpl_config_t *config)
अणु
	पूर्णांक rasz, rmsz, i;
	u_अक्षर *p;

	p = (u_अक्षर *)tuple->TupleData;
	rasz = *p & 0x03;
	rmsz = (*p & 0x3c) >> 2;
	अगर (tuple->TupleDataLen < rasz+rmsz+4)
		वापस -EINVAL;
	config->last_idx = *(++p);
	p++;
	config->base = 0;
	क्रम (i = 0; i <= rasz; i++)
		config->base += p[i] << (8*i);
	p += rasz+1;
	क्रम (i = 0; i < 4; i++)
		config->rmask[i] = 0;
	क्रम (i = 0; i <= rmsz; i++)
		config->rmask[i>>2] += p[i] << (8*(i%4));
	config->subtuples = tuple->TupleDataLen - (rasz+rmsz+4);
	वापस 0;
पूर्ण

/* The following routines are all used to parse the nighपंचांगarish
 * config table entries.
 */

अटल u_अक्षर *parse_घातer(u_अक्षर *p, u_अक्षर *q, cistpl_घातer_t *pwr)
अणु
	पूर्णांक i;
	u_पूर्णांक scale;

	अगर (p == q)
		वापस शून्य;
	pwr->present = *p;
	pwr->flags = 0;
	p++;
	क्रम (i = 0; i < 7; i++)
		अगर (pwr->present & (1<<i)) अणु
			अगर (p == q)
				वापस शून्य;
			pwr->param[i] = POWER_CVT(*p);
			scale = POWER_SCALE(*p);
			जबतक (*p & 0x80) अणु
				अगर (++p == q)
					वापस शून्य;
				अगर ((*p & 0x7f) < 100)
					pwr->param[i] +=
						(*p & 0x7f) * scale / 100;
				अन्यथा अगर (*p == 0x7d)
					pwr->flags |= CISTPL_POWER_HIGHZ_OK;
				अन्यथा अगर (*p == 0x7e)
					pwr->param[i] = 0;
				अन्यथा अगर (*p == 0x7f)
					pwr->flags |= CISTPL_POWER_HIGHZ_REQ;
				अन्यथा
					वापस शून्य;
			पूर्ण
			p++;
		पूर्ण
	वापस p;
पूर्ण


अटल u_अक्षर *parse_timing(u_अक्षर *p, u_अक्षर *q, cistpl_timing_t *timing)
अणु
	u_अक्षर scale;

	अगर (p == q)
		वापस शून्य;
	scale = *p;
	अगर ((scale & 3) != 3) अणु
		अगर (++p == q)
			वापस शून्य;
		timing->रुको = SPEED_CVT(*p);
		timing->रुकोscale = exponent[scale & 3];
	पूर्ण अन्यथा
		timing->रुको = 0;
	scale >>= 2;
	अगर ((scale & 7) != 7) अणु
		अगर (++p == q)
			वापस शून्य;
		timing->पढ़ोy = SPEED_CVT(*p);
		timing->rdyscale = exponent[scale & 7];
	पूर्ण अन्यथा
		timing->पढ़ोy = 0;
	scale >>= 3;
	अगर (scale != 7) अणु
		अगर (++p == q)
			वापस शून्य;
		timing->reserved = SPEED_CVT(*p);
		timing->rsvscale = exponent[scale];
	पूर्ण अन्यथा
		timing->reserved = 0;
	p++;
	वापस p;
पूर्ण


अटल u_अक्षर *parse_io(u_अक्षर *p, u_अक्षर *q, cistpl_io_t *io)
अणु
	पूर्णांक i, j, bsz, lsz;

	अगर (p == q)
		वापस शून्य;
	io->flags = *p;

	अगर (!(*p & 0x80)) अणु
		io->nwin = 1;
		io->win[0].base = 0;
		io->win[0].len = (1 << (io->flags & CISTPL_IO_LINES_MASK));
		वापस p+1;
	पूर्ण

	अगर (++p == q)
		वापस शून्य;
	io->nwin = (*p & 0x0f) + 1;
	bsz = (*p & 0x30) >> 4;
	अगर (bsz == 3)
		bsz++;
	lsz = (*p & 0xc0) >> 6;
	अगर (lsz == 3)
		lsz++;
	p++;

	क्रम (i = 0; i < io->nwin; i++) अणु
		io->win[i].base = 0;
		io->win[i].len = 1;
		क्रम (j = 0; j < bsz; j++, p++) अणु
			अगर (p == q)
				वापस शून्य;
			io->win[i].base += *p << (j*8);
		पूर्ण
		क्रम (j = 0; j < lsz; j++, p++) अणु
			अगर (p == q)
				वापस शून्य;
			io->win[i].len += *p << (j*8);
		पूर्ण
	पूर्ण
	वापस p;
पूर्ण


अटल u_अक्षर *parse_mem(u_अक्षर *p, u_अक्षर *q, cistpl_mem_t *mem)
अणु
	पूर्णांक i, j, asz, lsz, has_ha;
	u_पूर्णांक len, ca, ha;

	अगर (p == q)
		वापस शून्य;

	mem->nwin = (*p & 0x07) + 1;
	lsz = (*p & 0x18) >> 3;
	asz = (*p & 0x60) >> 5;
	has_ha = (*p & 0x80);
	अगर (++p == q)
		वापस शून्य;

	क्रम (i = 0; i < mem->nwin; i++) अणु
		len = ca = ha = 0;
		क्रम (j = 0; j < lsz; j++, p++) अणु
			अगर (p == q)
				वापस शून्य;
			len += *p << (j*8);
		पूर्ण
		क्रम (j = 0; j < asz; j++, p++) अणु
			अगर (p == q)
				वापस शून्य;
			ca += *p << (j*8);
		पूर्ण
		अगर (has_ha)
			क्रम (j = 0; j < asz; j++, p++) अणु
				अगर (p == q)
					वापस शून्य;
				ha += *p << (j*8);
			पूर्ण
		mem->win[i].len = len << 8;
		mem->win[i].card_addr = ca << 8;
		mem->win[i].host_addr = ha << 8;
	पूर्ण
	वापस p;
पूर्ण


अटल u_अक्षर *parse_irq(u_अक्षर *p, u_अक्षर *q, cistpl_irq_t *irq)
अणु
	अगर (p == q)
		वापस शून्य;
	irq->IRQInfo1 = *p; p++;
	अगर (irq->IRQInfo1 & IRQ_INFO2_VALID) अणु
		अगर (p+2 > q)
			वापस शून्य;
		irq->IRQInfo2 = (p[1]<<8) + p[0];
		p += 2;
	पूर्ण
	वापस p;
पूर्ण


अटल पूर्णांक parse_cftable_entry(tuple_t *tuple,
			       cistpl_cftable_entry_t *entry)
अणु
	u_अक्षर *p, *q, features;

	p = tuple->TupleData;
	q = p + tuple->TupleDataLen;
	entry->index = *p & 0x3f;
	entry->flags = 0;
	अगर (*p & 0x40)
		entry->flags |= CISTPL_CFTABLE_DEFAULT;
	अगर (*p & 0x80) अणु
		अगर (++p == q)
			वापस -EINVAL;
		अगर (*p & 0x10)
			entry->flags |= CISTPL_CFTABLE_BVDS;
		अगर (*p & 0x20)
			entry->flags |= CISTPL_CFTABLE_WP;
		अगर (*p & 0x40)
			entry->flags |= CISTPL_CFTABLE_RDYBSY;
		अगर (*p & 0x80)
			entry->flags |= CISTPL_CFTABLE_MWAIT;
		entry->पूर्णांकerface = *p & 0x0f;
	पूर्ण अन्यथा
		entry->पूर्णांकerface = 0;

	/* Process optional features */
	अगर (++p == q)
		वापस -EINVAL;
	features = *p; p++;

	/* Power options */
	अगर ((features & 3) > 0) अणु
		p = parse_घातer(p, q, &entry->vcc);
		अगर (p == शून्य)
			वापस -EINVAL;
	पूर्ण अन्यथा
		entry->vcc.present = 0;
	अगर ((features & 3) > 1) अणु
		p = parse_घातer(p, q, &entry->vpp1);
		अगर (p == शून्य)
			वापस -EINVAL;
	पूर्ण अन्यथा
		entry->vpp1.present = 0;
	अगर ((features & 3) > 2) अणु
		p = parse_घातer(p, q, &entry->vpp2);
		अगर (p == शून्य)
			वापस -EINVAL;
	पूर्ण अन्यथा
		entry->vpp2.present = 0;

	/* Timing options */
	अगर (features & 0x04) अणु
		p = parse_timing(p, q, &entry->timing);
		अगर (p == शून्य)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		entry->timing.रुको = 0;
		entry->timing.पढ़ोy = 0;
		entry->timing.reserved = 0;
	पूर्ण

	/* I/O winकरोw options */
	अगर (features & 0x08) अणु
		p = parse_io(p, q, &entry->io);
		अगर (p == शून्य)
			वापस -EINVAL;
	पूर्ण अन्यथा
		entry->io.nwin = 0;

	/* Interrupt options */
	अगर (features & 0x10) अणु
		p = parse_irq(p, q, &entry->irq);
		अगर (p == शून्य)
			वापस -EINVAL;
	पूर्ण अन्यथा
		entry->irq.IRQInfo1 = 0;

	चयन (features & 0x60) अणु
	हाल 0x00:
		entry->mem.nwin = 0;
		अवरोध;
	हाल 0x20:
		entry->mem.nwin = 1;
		entry->mem.win[0].len = get_unaligned_le16(p) << 8;
		entry->mem.win[0].card_addr = 0;
		entry->mem.win[0].host_addr = 0;
		p += 2;
		अगर (p > q)
			वापस -EINVAL;
		अवरोध;
	हाल 0x40:
		entry->mem.nwin = 1;
		entry->mem.win[0].len = get_unaligned_le16(p) << 8;
		entry->mem.win[0].card_addr = get_unaligned_le16(p + 2) << 8;
		entry->mem.win[0].host_addr = 0;
		p += 4;
		अगर (p > q)
			वापस -EINVAL;
		अवरोध;
	हाल 0x60:
		p = parse_mem(p, q, &entry->mem);
		अगर (p == शून्य)
			वापस -EINVAL;
		अवरोध;
	पूर्ण

	/* Misc features */
	अगर (features & 0x80) अणु
		अगर (p == q)
			वापस -EINVAL;
		entry->flags |= (*p << 8);
		जबतक (*p & 0x80)
			अगर (++p == q)
				वापस -EINVAL;
		p++;
	पूर्ण

	entry->subtuples = q-p;

	वापस 0;
पूर्ण


अटल पूर्णांक parse_device_geo(tuple_t *tuple, cistpl_device_geo_t *geo)
अणु
	u_अक्षर *p, *q;
	पूर्णांक n;

	p = (u_अक्षर *)tuple->TupleData;
	q = p + tuple->TupleDataLen;

	क्रम (n = 0; n < CISTPL_MAX_DEVICES; n++) अणु
		अगर (p > q-6)
			अवरोध;
		geo->geo[n].buswidth = p[0];
		geo->geo[n].erase_block = 1 << (p[1]-1);
		geo->geo[n].पढ़ो_block  = 1 << (p[2]-1);
		geo->geo[n].ग_लिखो_block = 1 << (p[3]-1);
		geo->geo[n].partition   = 1 << (p[4]-1);
		geo->geo[n].पूर्णांकerleave  = 1 << (p[5]-1);
		p += 6;
	पूर्ण
	geo->ngeo = n;
	वापस 0;
पूर्ण


अटल पूर्णांक parse_vers_2(tuple_t *tuple, cistpl_vers_2_t *v2)
अणु
	u_अक्षर *p, *q;

	अगर (tuple->TupleDataLen < 10)
		वापस -EINVAL;

	p = tuple->TupleData;
	q = p + tuple->TupleDataLen;

	v2->vers = p[0];
	v2->comply = p[1];
	v2->dindex = get_unaligned_le16(p + 2);
	v2->vspec8 = p[6];
	v2->vspec9 = p[7];
	v2->nhdr = p[8];
	p += 9;
	वापस parse_strings(p, q, 2, v2->str, &v2->venकरोr, शून्य);
पूर्ण


अटल पूर्णांक parse_org(tuple_t *tuple, cistpl_org_t *org)
अणु
	u_अक्षर *p, *q;
	पूर्णांक i;

	p = tuple->TupleData;
	q = p + tuple->TupleDataLen;
	अगर (p == q)
		वापस -EINVAL;
	org->data_org = *p;
	अगर (++p == q)
		वापस -EINVAL;
	क्रम (i = 0; i < 30; i++) अणु
		org->desc[i] = *p;
		अगर (*p == '\0')
			अवरोध;
		अगर (++p == q)
			वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण


अटल पूर्णांक parse_क्रमmat(tuple_t *tuple, cistpl_क्रमmat_t *fmt)
अणु
	u_अक्षर *p;

	अगर (tuple->TupleDataLen < 10)
		वापस -EINVAL;

	p = tuple->TupleData;

	fmt->type = p[0];
	fmt->edc = p[1];
	fmt->offset = get_unaligned_le32(p + 2);
	fmt->length = get_unaligned_le32(p + 6);

	वापस 0;
पूर्ण


पूर्णांक pcmcia_parse_tuple(tuple_t *tuple, cisparse_t *parse)
अणु
	पूर्णांक ret = 0;

	अगर (tuple->TupleDataLen > tuple->TupleDataMax)
		वापस -EINVAL;
	चयन (tuple->TupleCode) अणु
	हाल CISTPL_DEVICE:
	हाल CISTPL_DEVICE_A:
		ret = parse_device(tuple, &parse->device);
		अवरोध;
	हाल CISTPL_CHECKSUM:
		ret = parse_checksum(tuple, &parse->checksum);
		अवरोध;
	हाल CISTPL_LONGLINK_A:
	हाल CISTPL_LONGLINK_C:
		ret = parse_दीर्घlink(tuple, &parse->दीर्घlink);
		अवरोध;
	हाल CISTPL_LONGLINK_MFC:
		ret = parse_दीर्घlink_mfc(tuple, &parse->दीर्घlink_mfc);
		अवरोध;
	हाल CISTPL_VERS_1:
		ret = parse_vers_1(tuple, &parse->version_1);
		अवरोध;
	हाल CISTPL_ALTSTR:
		ret = parse_altstr(tuple, &parse->altstr);
		अवरोध;
	हाल CISTPL_JEDEC_A:
	हाल CISTPL_JEDEC_C:
		ret = parse_jedec(tuple, &parse->jedec);
		अवरोध;
	हाल CISTPL_MANFID:
		ret = parse_manfid(tuple, &parse->manfid);
		अवरोध;
	हाल CISTPL_FUNCID:
		ret = parse_funcid(tuple, &parse->funcid);
		अवरोध;
	हाल CISTPL_FUNCE:
		ret = parse_funce(tuple, &parse->funce);
		अवरोध;
	हाल CISTPL_CONFIG:
		ret = parse_config(tuple, &parse->config);
		अवरोध;
	हाल CISTPL_CFTABLE_ENTRY:
		ret = parse_cftable_entry(tuple, &parse->cftable_entry);
		अवरोध;
	हाल CISTPL_DEVICE_GEO:
	हाल CISTPL_DEVICE_GEO_A:
		ret = parse_device_geo(tuple, &parse->device_geo);
		अवरोध;
	हाल CISTPL_VERS_2:
		ret = parse_vers_2(tuple, &parse->vers_2);
		अवरोध;
	हाल CISTPL_ORG:
		ret = parse_org(tuple, &parse->org);
		अवरोध;
	हाल CISTPL_FORMAT:
	हाल CISTPL_FORMAT_A:
		ret = parse_क्रमmat(tuple, &parse->क्रमmat);
		अवरोध;
	हाल CISTPL_NO_LINK:
	हाल CISTPL_LINKTARGET:
		ret = 0;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	अगर (ret)
		pr_debug("parse_tuple failed %d\n", ret);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(pcmcia_parse_tuple);


/**
 * pccard_validate_cis() - check whether card has a sensible CIS
 * @s:		the काष्ठा pcmcia_socket we are to check
 * @info:	वापसs the number of tuples in the (valid) CIS, or 0
 *
 * This tries to determine अगर a card has a sensible CIS.  In @info, it
 * वापसs the number of tuples in the CIS, or 0 अगर the CIS looks bad. The
 * checks include making sure several critical tuples are present and
 * valid; seeing अगर the total number of tuples is reasonable; and
 * looking क्रम tuples that use reserved codes.
 *
 * The function वापसs 0 on success.
 */
पूर्णांक pccard_validate_cis(काष्ठा pcmcia_socket *s, अचिन्हित पूर्णांक *info)
अणु
	tuple_t *tuple;
	cisparse_t *p;
	अचिन्हित पूर्णांक count = 0;
	पूर्णांक ret, reserved, dev_ok = 0, ident_ok = 0;

	अगर (!s)
		वापस -EINVAL;

	अगर (s->functions || !(s->state & SOCKET_PRESENT)) अणु
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	/* We करो not want to validate the CIS cache... */
	mutex_lock(&s->ops_mutex);
	destroy_cis_cache(s);
	mutex_unlock(&s->ops_mutex);

	tuple = kदो_स्मृति(माप(*tuple), GFP_KERNEL);
	अगर (tuple == शून्य) अणु
		dev_warn(&s->dev, "no memory to validate CIS\n");
		वापस -ENOMEM;
	पूर्ण
	p = kदो_स्मृति(माप(*p), GFP_KERNEL);
	अगर (p == शून्य) अणु
		kमुक्त(tuple);
		dev_warn(&s->dev, "no memory to validate CIS\n");
		वापस -ENOMEM;
	पूर्ण

	count = reserved = 0;
	tuple->DesiredTuple = RETURN_FIRST_TUPLE;
	tuple->Attributes = TUPLE_RETURN_COMMON;
	ret = pccard_get_first_tuple(s, BIND_FN_ALL, tuple);
	अगर (ret != 0)
		जाओ करोne;

	/* First tuple should be DEVICE; we should really have either that
	   or a CFTABLE_ENTRY of some sort */
	अगर ((tuple->TupleCode == CISTPL_DEVICE) ||
	    (!pccard_पढ़ो_tuple(s, BIND_FN_ALL, CISTPL_CFTABLE_ENTRY, p)) ||
	    (!pccard_पढ़ो_tuple(s, BIND_FN_ALL, CISTPL_CFTABLE_ENTRY_CB, p)))
		dev_ok++;

	/* All cards should have a MANFID tuple, and/or a VERS_1 or VERS_2
	   tuple, क्रम card identअगरication.  Certain old D-Link and Linksys
	   cards have only a broken VERS_2 tuple; hence the bogus test. */
	अगर ((pccard_पढ़ो_tuple(s, BIND_FN_ALL, CISTPL_MANFID, p) == 0) ||
	    (pccard_पढ़ो_tuple(s, BIND_FN_ALL, CISTPL_VERS_1, p) == 0) ||
	    (pccard_पढ़ो_tuple(s, BIND_FN_ALL, CISTPL_VERS_2, p) != -ENOSPC))
		ident_ok++;

	अगर (!dev_ok && !ident_ok)
		जाओ करोne;

	क्रम (count = 1; count < MAX_TUPLES; count++) अणु
		ret = pccard_get_next_tuple(s, BIND_FN_ALL, tuple);
		अगर (ret != 0)
			अवरोध;
		अगर (((tuple->TupleCode > 0x23) && (tuple->TupleCode < 0x40)) ||
		    ((tuple->TupleCode > 0x47) && (tuple->TupleCode < 0x80)) ||
		    ((tuple->TupleCode > 0x90) && (tuple->TupleCode < 0xff)))
			reserved++;
	पूर्ण
	अगर ((count == MAX_TUPLES) || (reserved > 5) ||
		((!dev_ok || !ident_ok) && (count > 10)))
		count = 0;

	ret = 0;

करोne:
	/* invalidate CIS cache on failure */
	अगर (!dev_ok || !ident_ok || !count) अणु
		mutex_lock(&s->ops_mutex);
		destroy_cis_cache(s);
		mutex_unlock(&s->ops_mutex);
		/* We dअगरferentiate between dev_ok, ident_ok and count
		   failures to allow क्रम an override क्रम anonymous cards
		   in ds.c */
		अगर (!dev_ok || !ident_ok)
			ret = -EIO;
		अन्यथा
			ret = -EFAULT;
	पूर्ण

	अगर (info)
		*info = count;
	kमुक्त(tuple);
	kमुक्त(p);
	वापस ret;
पूर्ण


#घोषणा to_socket(_dev) container_of(_dev, काष्ठा pcmcia_socket, dev)

अटल sमाप_प्रकार pccard_extract_cis(काष्ठा pcmcia_socket *s, अक्षर *buf,
				  loff_t off, माप_प्रकार count)
अणु
	tuple_t tuple;
	पूर्णांक status, i;
	loff_t poपूर्णांकer = 0;
	sमाप_प्रकार ret = 0;
	u_अक्षर *tuplebuffer;
	u_अक्षर *tempbuffer;

	tuplebuffer = kदो_स्मृति_array(256, माप(u_अक्षर), GFP_KERNEL);
	अगर (!tuplebuffer)
		वापस -ENOMEM;

	tempbuffer = kदो_स्मृति_array(258, माप(u_अक्षर), GFP_KERNEL);
	अगर (!tempbuffer) अणु
		ret = -ENOMEM;
		जाओ मुक्त_tuple;
	पूर्ण

	स_रखो(&tuple, 0, माप(tuple_t));

	tuple.Attributes = TUPLE_RETURN_LINK | TUPLE_RETURN_COMMON;
	tuple.DesiredTuple = RETURN_FIRST_TUPLE;
	tuple.TupleOffset = 0;

	status = pccard_get_first_tuple(s, BIND_FN_ALL, &tuple);
	जबतक (!status) अणु
		tuple.TupleData = tuplebuffer;
		tuple.TupleDataMax = 255;
		स_रखो(tuplebuffer, 0, माप(u_अक्षर) * 255);

		status = pccard_get_tuple_data(s, &tuple);
		अगर (status)
			अवरोध;

		अगर (off < (poपूर्णांकer + 2 + tuple.TupleDataLen)) अणु
			tempbuffer[0] = tuple.TupleCode & 0xff;
			tempbuffer[1] = tuple.TupleLink & 0xff;
			क्रम (i = 0; i < tuple.TupleDataLen; i++)
				tempbuffer[i + 2] = tuplebuffer[i] & 0xff;

			क्रम (i = 0; i < (2 + tuple.TupleDataLen); i++) अणु
				अगर (((i + poपूर्णांकer) >= off) &&
				    (i + poपूर्णांकer) < (off + count)) अणु
					buf[ret] = tempbuffer[i];
					ret++;
				पूर्ण
			पूर्ण
		पूर्ण

		poपूर्णांकer += 2 + tuple.TupleDataLen;

		अगर (poपूर्णांकer >= (off + count))
			अवरोध;

		अगर (tuple.TupleCode == CISTPL_END)
			अवरोध;
		status = pccard_get_next_tuple(s, BIND_FN_ALL, &tuple);
	पूर्ण

	kमुक्त(tempbuffer);
 मुक्त_tuple:
	kमुक्त(tuplebuffer);

	वापस ret;
पूर्ण


अटल sमाप_प्रकार pccard_show_cis(काष्ठा file *filp, काष्ठा kobject *kobj,
			       काष्ठा bin_attribute *bin_attr,
			       अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक size = 0x200;

	अगर (off >= size)
		count = 0;
	अन्यथा अणु
		काष्ठा pcmcia_socket *s;
		अचिन्हित पूर्णांक chains = 1;

		अगर (off + count > size)
			count = size - off;

		s = to_socket(kobj_to_dev(kobj));

		अगर (!(s->state & SOCKET_PRESENT))
			वापस -ENODEV;
		अगर (!s->functions && pccard_validate_cis(s, &chains))
			वापस -EIO;
		अगर (!chains)
			वापस -ENODATA;

		count = pccard_extract_cis(s, buf, off, count);
	पूर्ण

	वापस count;
पूर्ण


अटल sमाप_प्रकार pccard_store_cis(काष्ठा file *filp, काष्ठा kobject *kobj,
				काष्ठा bin_attribute *bin_attr,
				अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा pcmcia_socket *s;
	पूर्णांक error;

	error = security_locked_करोwn(LOCKDOWN_PCMCIA_CIS);
	अगर (error)
		वापस error;

	s = to_socket(kobj_to_dev(kobj));

	अगर (off)
		वापस -EINVAL;

	अगर (count >= CISTPL_MAX_CIS_SIZE)
		वापस -EINVAL;

	अगर (!(s->state & SOCKET_PRESENT))
		वापस -ENODEV;

	error = pcmcia_replace_cis(s, buf, count);
	अगर (error)
		वापस -EIO;

	pcmcia_parse_uevents(s, PCMCIA_UEVENT_REQUERY);

	वापस count;
पूर्ण


स्थिर काष्ठा bin_attribute pccard_cis_attr = अणु
	.attr = अणु .name = "cis", .mode = S_IRUGO | S_IWUSR पूर्ण,
	.size = 0x200,
	.पढ़ो = pccard_show_cis,
	.ग_लिखो = pccard_store_cis,
पूर्ण;
