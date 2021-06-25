<शैली गुरु>
/*
 * Sonics Silicon Backplane SoC host related functions.
 * Subप्रणाली core
 *
 * Copyright 2005, Broadcom Corporation
 * Copyright 2006, 2007, Michael Buesch <m@bues.ch>
 *
 * Licensed under the GNU/GPL. See COPYING क्रम details.
 */

#समावेश "ssb_private.h"

#समावेश <linux/bcm47xx_nvram.h>
#समावेश <linux/ssb/ssb.h>

अटल u8 ssb_host_soc_पढ़ो8(काष्ठा ssb_device *dev, u16 offset)
अणु
	काष्ठा ssb_bus *bus = dev->bus;

	offset += dev->core_index * SSB_CORE_SIZE;
	वापस पढ़ोb(bus->mmio + offset);
पूर्ण

अटल u16 ssb_host_soc_पढ़ो16(काष्ठा ssb_device *dev, u16 offset)
अणु
	काष्ठा ssb_bus *bus = dev->bus;

	offset += dev->core_index * SSB_CORE_SIZE;
	वापस पढ़ोw(bus->mmio + offset);
पूर्ण

अटल u32 ssb_host_soc_पढ़ो32(काष्ठा ssb_device *dev, u16 offset)
अणु
	काष्ठा ssb_bus *bus = dev->bus;

	offset += dev->core_index * SSB_CORE_SIZE;
	वापस पढ़ोl(bus->mmio + offset);
पूर्ण

#अगर_घोषित CONFIG_SSB_BLOCKIO
अटल व्योम ssb_host_soc_block_पढ़ो(काष्ठा ssb_device *dev, व्योम *buffer,
				    माप_प्रकार count, u16 offset, u8 reg_width)
अणु
	काष्ठा ssb_bus *bus = dev->bus;
	व्योम __iomem *addr;

	offset += dev->core_index * SSB_CORE_SIZE;
	addr = bus->mmio + offset;

	चयन (reg_width) अणु
	हाल माप(u8): अणु
		u8 *buf = buffer;

		जबतक (count) अणु
			*buf = __raw_पढ़ोb(addr);
			buf++;
			count--;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल माप(u16): अणु
		__le16 *buf = buffer;

		WARN_ON(count & 1);
		जबतक (count) अणु
			*buf = (__क्रमce __le16)__raw_पढ़ोw(addr);
			buf++;
			count -= 2;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल माप(u32): अणु
		__le32 *buf = buffer;

		WARN_ON(count & 3);
		जबतक (count) अणु
			*buf = (__क्रमce __le32)__raw_पढ़ोl(addr);
			buf++;
			count -= 4;
		पूर्ण
		अवरोध;
	पूर्ण
	शेष:
		WARN_ON(1);
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_SSB_BLOCKIO */

अटल व्योम ssb_host_soc_ग_लिखो8(काष्ठा ssb_device *dev, u16 offset, u8 value)
अणु
	काष्ठा ssb_bus *bus = dev->bus;

	offset += dev->core_index * SSB_CORE_SIZE;
	ग_लिखोb(value, bus->mmio + offset);
पूर्ण

अटल व्योम ssb_host_soc_ग_लिखो16(काष्ठा ssb_device *dev, u16 offset, u16 value)
अणु
	काष्ठा ssb_bus *bus = dev->bus;

	offset += dev->core_index * SSB_CORE_SIZE;
	ग_लिखोw(value, bus->mmio + offset);
पूर्ण

अटल व्योम ssb_host_soc_ग_लिखो32(काष्ठा ssb_device *dev, u16 offset, u32 value)
अणु
	काष्ठा ssb_bus *bus = dev->bus;

	offset += dev->core_index * SSB_CORE_SIZE;
	ग_लिखोl(value, bus->mmio + offset);
पूर्ण

#अगर_घोषित CONFIG_SSB_BLOCKIO
अटल व्योम ssb_host_soc_block_ग_लिखो(काष्ठा ssb_device *dev, स्थिर व्योम *buffer,
				     माप_प्रकार count, u16 offset, u8 reg_width)
अणु
	काष्ठा ssb_bus *bus = dev->bus;
	व्योम __iomem *addr;

	offset += dev->core_index * SSB_CORE_SIZE;
	addr = bus->mmio + offset;

	चयन (reg_width) अणु
	हाल माप(u8): अणु
		स्थिर u8 *buf = buffer;

		जबतक (count) अणु
			__raw_ग_लिखोb(*buf, addr);
			buf++;
			count--;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल माप(u16): अणु
		स्थिर __le16 *buf = buffer;

		WARN_ON(count & 1);
		जबतक (count) अणु
			__raw_ग_लिखोw((__क्रमce u16)(*buf), addr);
			buf++;
			count -= 2;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल माप(u32): अणु
		स्थिर __le32 *buf = buffer;

		WARN_ON(count & 3);
		जबतक (count) अणु
			__raw_ग_लिखोl((__क्रमce u32)(*buf), addr);
			buf++;
			count -= 4;
		पूर्ण
		अवरोध;
	पूर्ण
	शेष:
		WARN_ON(1);
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_SSB_BLOCKIO */

/* Ops क्रम the plain SSB bus without a host-device (no PCI or PCMCIA). */
स्थिर काष्ठा ssb_bus_ops ssb_host_soc_ops = अणु
	.पढ़ो8		= ssb_host_soc_पढ़ो8,
	.पढ़ो16		= ssb_host_soc_पढ़ो16,
	.पढ़ो32		= ssb_host_soc_पढ़ो32,
	.ग_लिखो8		= ssb_host_soc_ग_लिखो8,
	.ग_लिखो16	= ssb_host_soc_ग_लिखो16,
	.ग_लिखो32	= ssb_host_soc_ग_लिखो32,
#अगर_घोषित CONFIG_SSB_BLOCKIO
	.block_पढ़ो	= ssb_host_soc_block_पढ़ो,
	.block_ग_लिखो	= ssb_host_soc_block_ग_लिखो,
#पूर्ण_अगर
पूर्ण;

पूर्णांक ssb_host_soc_get_invariants(काष्ठा ssb_bus *bus,
				काष्ठा ssb_init_invariants *iv)
अणु
	अक्षर buf[20];
	पूर्णांक len, err;

	/* Fill boardinfo काष्ठाure */
	स_रखो(&iv->boardinfo, 0, माप(काष्ठा ssb_boardinfo));

	len = bcm47xx_nvram_दो_पर्या("boardvendor", buf, माप(buf));
	अगर (len > 0) अणु
		err = kstrtou16(strim(buf), 0, &iv->boardinfo.venकरोr);
		अगर (err)
			pr_warn("Couldn't parse nvram board vendor entry with value \"%s\"\n",
				buf);
	पूर्ण
	अगर (!iv->boardinfo.venकरोr)
		iv->boardinfo.venकरोr = SSB_BOARDVENDOR_BCM;

	len = bcm47xx_nvram_दो_पर्या("boardtype", buf, माप(buf));
	अगर (len > 0) अणु
		err = kstrtou16(strim(buf), 0, &iv->boardinfo.type);
		अगर (err)
			pr_warn("Couldn't parse nvram board type entry with value \"%s\"\n",
				buf);
	पूर्ण

	स_रखो(&iv->sprom, 0, माप(काष्ठा ssb_sprom));
	ssb_fill_sprom_with_fallback(bus, &iv->sprom);

	अगर (bcm47xx_nvram_दो_पर्या("cardbus", buf, माप(buf)) >= 0)
		iv->has_cardbus_slot = !!simple_म_से_अदीर्घ(buf, शून्य, 10);

	वापस 0;
पूर्ण
