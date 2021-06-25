<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * compat.c - A series of functions to make it easier to convert drivers that use
 *            the old isapnp APIs. If possible use the new APIs instead.
 *
 * Copyright 2002 Adam Belay <ambx1@neo.rr.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/isapnp.h>
#समावेश <linux/माला.स>

अटल व्योम pnp_convert_id(अक्षर *buf, अचिन्हित लघु venकरोr,
			   अचिन्हित लघु device)
अणु
	प्र_लिखो(buf, "%c%c%c%x%x%x%x",
		'A' + ((venकरोr >> 2) & 0x3f) - 1,
		'A' + (((venकरोr & 3) << 3) | ((venकरोr >> 13) & 7)) - 1,
		'A' + ((venकरोr >> 8) & 0x1f) - 1,
		(device >> 4) & 0x0f, device & 0x0f,
		(device >> 12) & 0x0f, (device >> 8) & 0x0f);
पूर्ण

काष्ठा pnp_dev *pnp_find_dev(काष्ठा pnp_card *card, अचिन्हित लघु venकरोr,
			     अचिन्हित लघु function, काष्ठा pnp_dev *from)
अणु
	अक्षर id[8];
	अक्षर any[8];

	pnp_convert_id(id, venकरोr, function);
	pnp_convert_id(any, ISAPNP_ANY_ID, ISAPNP_ANY_ID);
	अगर (card == शून्य) अणु	/* look क्रम a logical device from all cards */
		काष्ठा list_head *list;

		list = pnp_global.next;
		अगर (from)
			list = from->global_list.next;

		जबतक (list != &pnp_global) अणु
			काष्ठा pnp_dev *dev = global_to_pnp_dev(list);

			अगर (compare_pnp_id(dev->id, id) ||
			    (स_भेद(id, any, 7) == 0))
				वापस dev;
			list = list->next;
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा list_head *list;

		list = card->devices.next;
		अगर (from) अणु
			list = from->card_list.next;
			अगर (from->card != card)	/* something is wrong */
				वापस शून्य;
		पूर्ण
		जबतक (list != &card->devices) अणु
			काष्ठा pnp_dev *dev = card_to_pnp_dev(list);

			अगर (compare_pnp_id(dev->id, id))
				वापस dev;
			list = list->next;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

EXPORT_SYMBOL(pnp_find_dev);
