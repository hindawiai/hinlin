<शैली गुरु>
/*
 * Sonics Silicon Backplane
 * Common SPROM support routines
 *
 * Copyright (C) 2005-2008 Michael Buesch <m@bues.ch>
 * Copyright (C) 2005 Martin Langer <martin-langer@gmx.de>
 * Copyright (C) 2005 Stefano Brivio <st3@riseup.net>
 * Copyright (C) 2005 Danny van Dyk <kugelfang@gentoo.org>
 * Copyright (C) 2005 Andreas Jaggi <andreas.jaggi@waterwave.ch>
 *
 * Licensed under the GNU/GPL. See COPYING क्रम details.
 */

#समावेश "ssb_private.h"

#समावेश <linux/प्रकार.स>
#समावेश <linux/slab.h>


अटल पूर्णांक(*get_fallback_sprom)(काष्ठा ssb_bus *dev, काष्ठा ssb_sprom *out);


अटल पूर्णांक sprom2hex(स्थिर u16 *sprom, अक्षर *buf, माप_प्रकार buf_len,
		     माप_प्रकार sprom_size_words)
अणु
	पूर्णांक i, pos = 0;

	क्रम (i = 0; i < sprom_size_words; i++)
		pos += scnम_लिखो(buf + pos, buf_len - pos - 1,
				"%04X", swab16(sprom[i]) & 0xFFFF);
	pos += scnम_लिखो(buf + pos, buf_len - pos - 1, "\n");

	वापस pos + 1;
पूर्ण

अटल पूर्णांक hex2sprom(u16 *sprom, स्थिर अक्षर *dump, माप_प्रकार len,
		     माप_प्रकार sprom_size_words)
अणु
	अक्षर c, पंचांगp[5] = अणु 0 पूर्ण;
	पूर्णांक err, cnt = 0;
	अचिन्हित दीर्घ parsed;

	/* Strip whitespace at the end. */
	जबतक (len) अणु
		c = dump[len - 1];
		अगर (!है_खाली(c) && c != '\0')
			अवरोध;
		len--;
	पूर्ण
	/* Length must match exactly. */
	अगर (len != sprom_size_words * 4)
		वापस -EINVAL;

	जबतक (cnt < sprom_size_words) अणु
		स_नकल(पंचांगp, dump, 4);
		dump += 4;
		err = kम_से_अदीर्घ(पंचांगp, 16, &parsed);
		अगर (err)
			वापस err;
		sprom[cnt++] = swab16((u16)parsed);
	पूर्ण

	वापस 0;
पूर्ण

/* Common sprom device-attribute show-handler */
sमाप_प्रकार ssb_attr_sprom_show(काष्ठा ssb_bus *bus, अक्षर *buf,
			    पूर्णांक (*sprom_पढ़ो)(काष्ठा ssb_bus *bus, u16 *sprom))
अणु
	u16 *sprom;
	पूर्णांक err = -ENOMEM;
	sमाप_प्रकार count = 0;
	माप_प्रकार sprom_size_words = bus->sprom_size;

	sprom = kसुस्मृति(sprom_size_words, माप(u16), GFP_KERNEL);
	अगर (!sprom)
		जाओ out;

	/* Use पूर्णांकerruptible locking, as the SPROM ग_लिखो might
	 * be holding the lock क्रम several seconds. So allow userspace
	 * to cancel operation.
	 */
	err = -ERESTARTSYS;
	अगर (mutex_lock_पूर्णांकerruptible(&bus->sprom_mutex))
		जाओ out_kमुक्त;
	err = sprom_पढ़ो(bus, sprom);
	mutex_unlock(&bus->sprom_mutex);

	अगर (!err)
		count = sprom2hex(sprom, buf, PAGE_SIZE, sprom_size_words);

out_kमुक्त:
	kमुक्त(sprom);
out:
	वापस err ? err : count;
पूर्ण

/* Common sprom device-attribute store-handler */
sमाप_प्रकार ssb_attr_sprom_store(काष्ठा ssb_bus *bus,
			     स्थिर अक्षर *buf, माप_प्रकार count,
			     पूर्णांक (*sprom_check_crc)(स्थिर u16 *sprom, माप_प्रकार size),
			     पूर्णांक (*sprom_ग_लिखो)(काष्ठा ssb_bus *bus, स्थिर u16 *sprom))
अणु
	u16 *sprom;
	पूर्णांक res = 0, err = -ENOMEM;
	माप_प्रकार sprom_size_words = bus->sprom_size;
	काष्ठा ssb_मुक्तze_context मुक्तze;

	sprom = kसुस्मृति(bus->sprom_size, माप(u16), GFP_KERNEL);
	अगर (!sprom)
		जाओ out;
	err = hex2sprom(sprom, buf, count, sprom_size_words);
	अगर (err) अणु
		err = -EINVAL;
		जाओ out_kमुक्त;
	पूर्ण
	err = sprom_check_crc(sprom, sprom_size_words);
	अगर (err) अणु
		err = -EINVAL;
		जाओ out_kमुक्त;
	पूर्ण

	/* Use पूर्णांकerruptible locking, as the SPROM ग_लिखो might
	 * be holding the lock क्रम several seconds. So allow userspace
	 * to cancel operation.
	 */
	err = -ERESTARTSYS;
	अगर (mutex_lock_पूर्णांकerruptible(&bus->sprom_mutex))
		जाओ out_kमुक्त;
	err = ssb_devices_मुक्तze(bus, &मुक्तze);
	अगर (err) अणु
		pr_err("SPROM write: Could not freeze all devices\n");
		जाओ out_unlock;
	पूर्ण
	res = sprom_ग_लिखो(bus, sprom);
	err = ssb_devices_thaw(&मुक्तze);
	अगर (err)
		pr_err("SPROM write: Could not thaw all devices\n");
out_unlock:
	mutex_unlock(&bus->sprom_mutex);
out_kमुक्त:
	kमुक्त(sprom);
out:
	अगर (res)
		वापस res;
	वापस err ? err : count;
पूर्ण

/**
 * ssb_arch_रेजिस्टर_fallback_sprom - Registers a method providing a
 * fallback SPROM अगर no SPROM is found.
 *
 * @sprom_callback: The callback function.
 *
 * With this function the architecture implementation may रेजिस्टर a
 * callback handler which fills the SPROM data काष्ठाure. The fallback is
 * only used क्रम PCI based SSB devices, where no valid SPROM can be found
 * in the shaकरोw रेजिस्टरs.
 *
 * This function is useful क्रम weird architectures that have a half-assed
 * SSB device hardwired to their PCI bus.
 *
 * Note that it करोes only work with PCI attached SSB devices. PCMCIA
 * devices currently करोn't use this fallback.
 * Architectures must provide the SPROM क्रम native SSB devices anyway, so
 * the fallback also isn't used क्रम native devices.
 *
 * This function is available क्रम architecture code, only. So it is not
 * exported.
 */
पूर्णांक ssb_arch_रेजिस्टर_fallback_sprom(पूर्णांक (*sprom_callback)(काष्ठा ssb_bus *bus,
				     काष्ठा ssb_sprom *out))
अणु
	अगर (get_fallback_sprom)
		वापस -EEXIST;
	get_fallback_sprom = sprom_callback;

	वापस 0;
पूर्ण

पूर्णांक ssb_fill_sprom_with_fallback(काष्ठा ssb_bus *bus, काष्ठा ssb_sprom *out)
अणु
	अगर (!get_fallback_sprom)
		वापस -ENOENT;

	वापस get_fallback_sprom(bus, out);
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/IsSpromAvailable */
bool ssb_is_sprom_available(काष्ठा ssb_bus *bus)
अणु
	/* status रेजिस्टर only exists on chipcomon rev >= 11 and we need check
	 * क्रम >= 31 only
	 */
	/* this routine dअगरfers from specs as we करो not access SPROM directly
	 * on PCMCIA
	 */
	अगर (bus->bustype == SSB_BUSTYPE_PCI &&
	    bus->chipco.dev &&	/* can be unavailable! */
	    bus->chipco.dev->id.revision >= 31)
		वापस bus->chipco.capabilities & SSB_CHIPCO_CAP_SPROM;

	वापस true;
पूर्ण
