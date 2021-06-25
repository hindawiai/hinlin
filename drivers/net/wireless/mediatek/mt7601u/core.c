<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014 Felix Fietkau <nbd@खोलोwrt.org>
 * Copyright (C) 2015 Jakub Kicinski <kubakici@wp.pl>
 */

#समावेश "mt7601u.h"

पूर्णांक mt7601u_रुको_asic_पढ़ोy(काष्ठा mt7601u_dev *dev)
अणु
	पूर्णांक i = 100;
	u32 val;

	करो अणु
		अगर (test_bit(MT7601U_STATE_REMOVED, &dev->state))
			वापस -EIO;

		val = mt7601u_rr(dev, MT_MAC_CSR0);
		अगर (val && ~val)
			वापस 0;

		udelay(10);
	पूर्ण जबतक (i--);

	वापस -EIO;
पूर्ण

bool mt76_poll(काष्ठा mt7601u_dev *dev, u32 offset, u32 mask, u32 val,
	       पूर्णांक समयout)
अणु
	u32 cur;

	समयout /= 10;
	करो अणु
		अगर (test_bit(MT7601U_STATE_REMOVED, &dev->state))
			वापस false;

		cur = mt7601u_rr(dev, offset) & mask;
		अगर (cur == val)
			वापस true;

		udelay(10);
	पूर्ण जबतक (समयout-- > 0);

	dev_err(dev->dev, "Error: Time out with reg %08x\n", offset);

	वापस false;
पूर्ण

bool mt76_poll_msec(काष्ठा mt7601u_dev *dev, u32 offset, u32 mask, u32 val,
		    पूर्णांक समयout)
अणु
	u32 cur;

	समयout /= 10;
	करो अणु
		अगर (test_bit(MT7601U_STATE_REMOVED, &dev->state))
			वापस false;

		cur = mt7601u_rr(dev, offset) & mask;
		अगर (cur == val)
			वापस true;

		msleep(10);
	पूर्ण जबतक (समयout-- > 0);

	dev_err(dev->dev, "Error: Time out with reg %08x\n", offset);

	वापस false;
पूर्ण
