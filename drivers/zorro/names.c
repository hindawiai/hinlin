<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	Zorro Device Name Tables
 *
 *	Copyright (C) 1999--2000 Geert Uytterhoeven
 *
 *	Based on the PCI version:
 *
 *	Copyright 1992--1999 Drew Eckhardt, Frederic Potter,
 *	David Mosberger-Tang, Martin Mares
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/zorro.h>


काष्ठा zorro_prod_info अणु
	__u16 prod;
	अचिन्हित लघु seen;
	स्थिर अक्षर *name;
पूर्ण;

काष्ठा zorro_manuf_info अणु
	__u16 manuf;
	अचिन्हित लघु nr;
	स्थिर अक्षर *name;
	काष्ठा zorro_prod_info *prods;
पूर्ण;

/*
 * This is ridiculous, but we want the strings in
 * the .init section so that they करोn't take up
 * real memory.. Parse the same file multiple बार
 * to get all the info.
 */
#घोषणा MANUF( manuf, name )		अटल अक्षर __manufstr_##manuf[] __initdata = name;
#घोषणा ENDMANUF()
#घोषणा PRODUCT( manuf, prod, name ) 	अटल अक्षर __prodstr_##manuf##prod[] __initdata = name;
#समावेश "devlist.h"


#घोषणा MANUF( manuf, name )		अटल काष्ठा zorro_prod_info __prods_##manuf[] __initdata = अणु
#घोषणा ENDMANUF()			पूर्ण;
#घोषणा PRODUCT( manuf, prod, name )	अणु 0x##prod, 0, __prodstr_##manuf##prod पूर्ण,
#समावेश "devlist.h"

अटल काष्ठा zorro_manuf_info __initdata zorro_manuf_list[] = अणु
#घोषणा MANUF( manuf, name )		अणु 0x##manuf, ARRAY_SIZE(__prods_##manuf), __manufstr_##manuf, __prods_##manuf पूर्ण,
#घोषणा ENDMANUF()
#घोषणा PRODUCT( manuf, prod, name )
#समावेश "devlist.h"
पूर्ण;

#घोषणा MANUFS ARRAY_SIZE(zorro_manuf_list)

व्योम __init zorro_name_device(काष्ठा zorro_dev *dev)
अणु
	स्थिर काष्ठा zorro_manuf_info *manuf_p = zorro_manuf_list;
	पूर्णांक i = MANUFS;
	अक्षर *name = dev->name;

	करो अणु
		अगर (manuf_p->manuf == ZORRO_MANUF(dev->id))
			जाओ match_manuf;
		manuf_p++;
	पूर्ण जबतक (--i);

	/* Couldn't find either the manufacturer nor the product */
	वापस;

	match_manuf: अणु
		काष्ठा zorro_prod_info *prod_p = manuf_p->prods;
		पूर्णांक i = manuf_p->nr;

		जबतक (i > 0) अणु
			अगर (prod_p->prod ==
			    ((ZORRO_PROD(dev->id)<<8) | ZORRO_EPC(dev->id)))
				जाओ match_prod;
			prod_p++;
			i--;
		पूर्ण

		/* Ok, found the manufacturer, but unknown product */
		प्र_लिखो(name, "Zorro device %08x (%s)", dev->id, manuf_p->name);
		वापस;

		/* Full match */
		match_prod: अणु
			अक्षर *n = name + प्र_लिखो(name, "%s %s", manuf_p->name, prod_p->name);
			पूर्णांक nr = prod_p->seen + 1;
			prod_p->seen = nr;
			अगर (nr > 1)
				प्र_लिखो(n, " (#%d)", nr);
		पूर्ण
	पूर्ण
पूर्ण
