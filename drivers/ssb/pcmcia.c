<शैली गुरु>
/*
 * Sonics Silicon Backplane
 * PCMCIA-Hostbus related functions
 *
 * Copyright 2006 Johannes Berg <johannes@sipsolutions.net>
 * Copyright 2007-2008 Michael Buesch <m@bues.ch>
 *
 * Licensed under the GNU/GPL. See COPYING क्रम details.
 */

#समावेश "ssb_private.h"

#समावेश <linux/ssb/ssb.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/etherdevice.h>

#समावेश <pcmcia/cistpl.h>
#समावेश <pcmcia/ciscode.h>
#समावेश <pcmcia/ds.h>
#समावेश <pcmcia/cisreg.h>


/* Define the following to 1 to enable a prपूर्णांकk on each coreचयन. */
#घोषणा SSB_VERBOSE_PCMCIACORESWITCH_DEBUG		0


/* PCMCIA configuration रेजिस्टरs */
#घोषणा SSB_PCMCIA_ADDRESS0		0x2E
#घोषणा SSB_PCMCIA_ADDRESS1		0x30
#घोषणा SSB_PCMCIA_ADDRESS2		0x32
#घोषणा SSB_PCMCIA_MEMSEG		0x34
#घोषणा SSB_PCMCIA_SPROMCTL		0x36
#घोषणा  SSB_PCMCIA_SPROMCTL_IDLE	0
#घोषणा  SSB_PCMCIA_SPROMCTL_WRITE	1
#घोषणा  SSB_PCMCIA_SPROMCTL_READ	2
#घोषणा  SSB_PCMCIA_SPROMCTL_WRITEEN	4
#घोषणा  SSB_PCMCIA_SPROMCTL_WRITEDIS	7
#घोषणा  SSB_PCMCIA_SPROMCTL_DONE	8
#घोषणा SSB_PCMCIA_SPROM_DATALO		0x38
#घोषणा SSB_PCMCIA_SPROM_DATAHI		0x3A
#घोषणा SSB_PCMCIA_SPROM_ADDRLO		0x3C
#घोषणा SSB_PCMCIA_SPROM_ADDRHI		0x3E

/* Hardware invariants CIS tuples */
#घोषणा SSB_PCMCIA_CIS			0x80
#घोषणा  SSB_PCMCIA_CIS_ID		0x01
#घोषणा  SSB_PCMCIA_CIS_BOARDREV	0x02
#घोषणा  SSB_PCMCIA_CIS_PA		0x03
#घोषणा   SSB_PCMCIA_CIS_PA_PA0B0_LO	0
#घोषणा   SSB_PCMCIA_CIS_PA_PA0B0_HI	1
#घोषणा   SSB_PCMCIA_CIS_PA_PA0B1_LO	2
#घोषणा   SSB_PCMCIA_CIS_PA_PA0B1_HI	3
#घोषणा   SSB_PCMCIA_CIS_PA_PA0B2_LO	4
#घोषणा   SSB_PCMCIA_CIS_PA_PA0B2_HI	5
#घोषणा   SSB_PCMCIA_CIS_PA_ITSSI	6
#घोषणा   SSB_PCMCIA_CIS_PA_MAXPOW	7
#घोषणा  SSB_PCMCIA_CIS_OEMNAME		0x04
#घोषणा  SSB_PCMCIA_CIS_CCODE		0x05
#घोषणा  SSB_PCMCIA_CIS_ANTENNA		0x06
#घोषणा  SSB_PCMCIA_CIS_ANTGAIN		0x07
#घोषणा  SSB_PCMCIA_CIS_BFLAGS		0x08
#घोषणा  SSB_PCMCIA_CIS_LEDS		0x09

/* PCMCIA SPROM size. */
#घोषणा SSB_PCMCIA_SPROM_SIZE		256
#घोषणा SSB_PCMCIA_SPROM_SIZE_BYTES	(SSB_PCMCIA_SPROM_SIZE * माप(u16))


/* Write to a PCMCIA configuration रेजिस्टर. */
अटल पूर्णांक ssb_pcmcia_cfg_ग_लिखो(काष्ठा ssb_bus *bus, u8 offset, u8 value)
अणु
	पूर्णांक res;

	res = pcmcia_ग_लिखो_config_byte(bus->host_pcmcia, offset, value);
	अगर (unlikely(res != 0))
		वापस -EBUSY;

	वापस 0;
पूर्ण

/* Read from a PCMCIA configuration रेजिस्टर. */
अटल पूर्णांक ssb_pcmcia_cfg_पढ़ो(काष्ठा ssb_bus *bus, u8 offset, u8 *value)
अणु
	पूर्णांक res;

	res = pcmcia_पढ़ो_config_byte(bus->host_pcmcia, offset, value);
	अगर (unlikely(res != 0))
		वापस -EBUSY;

	वापस 0;
पूर्ण

पूर्णांक ssb_pcmcia_चयन_coreidx(काष्ठा ssb_bus *bus,
			      u8 coreidx)
अणु
	पूर्णांक err;
	पूर्णांक attempts = 0;
	u32 cur_core;
	u32 addr;
	u32 पढ़ो_addr;
	u8 val;

	addr = (coreidx * SSB_CORE_SIZE) + SSB_ENUM_BASE;
	जबतक (1) अणु
		err = ssb_pcmcia_cfg_ग_लिखो(bus, SSB_PCMCIA_ADDRESS0,
					   (addr & 0x0000F000) >> 12);
		अगर (err)
			जाओ error;
		err = ssb_pcmcia_cfg_ग_लिखो(bus, SSB_PCMCIA_ADDRESS1,
					   (addr & 0x00FF0000) >> 16);
		अगर (err)
			जाओ error;
		err = ssb_pcmcia_cfg_ग_लिखो(bus, SSB_PCMCIA_ADDRESS2,
					   (addr & 0xFF000000) >> 24);
		अगर (err)
			जाओ error;

		पढ़ो_addr = 0;

		err = ssb_pcmcia_cfg_पढ़ो(bus, SSB_PCMCIA_ADDRESS0, &val);
		अगर (err)
			जाओ error;
		पढ़ो_addr |= ((u32)(val & 0x0F)) << 12;
		err = ssb_pcmcia_cfg_पढ़ो(bus, SSB_PCMCIA_ADDRESS1, &val);
		अगर (err)
			जाओ error;
		पढ़ो_addr |= ((u32)val) << 16;
		err = ssb_pcmcia_cfg_पढ़ो(bus, SSB_PCMCIA_ADDRESS2, &val);
		अगर (err)
			जाओ error;
		पढ़ो_addr |= ((u32)val) << 24;

		cur_core = (पढ़ो_addr - SSB_ENUM_BASE) / SSB_CORE_SIZE;
		अगर (cur_core == coreidx)
			अवरोध;

		err = -ETIMEDOUT;
		अगर (attempts++ > SSB_BAR0_MAX_RETRIES)
			जाओ error;
		udelay(10);
	पूर्ण

	वापस 0;
error:
	pr_err("Failed to switch to core %u\n", coreidx);
	वापस err;
पूर्ण

अटल पूर्णांक ssb_pcmcia_चयन_core(काष्ठा ssb_bus *bus, काष्ठा ssb_device *dev)
अणु
	पूर्णांक err;

#अगर SSB_VERBOSE_PCMCIACORESWITCH_DEBUG
	pr_info("Switching to %s core, index %d\n",
		ssb_core_name(dev->id.coreid), dev->core_index);
#पूर्ण_अगर

	err = ssb_pcmcia_चयन_coreidx(bus, dev->core_index);
	अगर (!err)
		bus->mapped_device = dev;

	वापस err;
पूर्ण

पूर्णांक ssb_pcmcia_चयन_segment(काष्ठा ssb_bus *bus, u8 seg)
अणु
	पूर्णांक attempts = 0;
	पूर्णांक err;
	u8 val;

	WARN_ON((seg != 0) && (seg != 1));
	जबतक (1) अणु
		err = ssb_pcmcia_cfg_ग_लिखो(bus, SSB_PCMCIA_MEMSEG, seg);
		अगर (err)
			जाओ error;
		err = ssb_pcmcia_cfg_पढ़ो(bus, SSB_PCMCIA_MEMSEG, &val);
		अगर (err)
			जाओ error;
		अगर (val == seg)
			अवरोध;

		err = -ETIMEDOUT;
		अगर (unlikely(attempts++ > SSB_BAR0_MAX_RETRIES))
			जाओ error;
		udelay(10);
	पूर्ण
	bus->mapped_pcmcia_seg = seg;

	वापस 0;
error:
	pr_err("Failed to switch pcmcia segment\n");
	वापस err;
पूर्ण

अटल पूर्णांक select_core_and_segment(काष्ठा ssb_device *dev,
				   u16 *offset)
अणु
	काष्ठा ssb_bus *bus = dev->bus;
	पूर्णांक err;
	u8 need_segment;

	अगर (*offset >= 0x800) अणु
		*offset -= 0x800;
		need_segment = 1;
	पूर्ण अन्यथा
		need_segment = 0;

	अगर (unlikely(dev != bus->mapped_device)) अणु
		err = ssb_pcmcia_चयन_core(bus, dev);
		अगर (unlikely(err))
			वापस err;
	पूर्ण
	अगर (unlikely(need_segment != bus->mapped_pcmcia_seg)) अणु
		err = ssb_pcmcia_चयन_segment(bus, need_segment);
		अगर (unlikely(err))
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल u8 ssb_pcmcia_पढ़ो8(काष्ठा ssb_device *dev, u16 offset)
अणु
	काष्ठा ssb_bus *bus = dev->bus;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;
	u8 value = 0xFF;

	spin_lock_irqsave(&bus->bar_lock, flags);
	err = select_core_and_segment(dev, &offset);
	अगर (likely(!err))
		value = पढ़ोb(bus->mmio + offset);
	spin_unlock_irqrestore(&bus->bar_lock, flags);

	वापस value;
पूर्ण

अटल u16 ssb_pcmcia_पढ़ो16(काष्ठा ssb_device *dev, u16 offset)
अणु
	काष्ठा ssb_bus *bus = dev->bus;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;
	u16 value = 0xFFFF;

	spin_lock_irqsave(&bus->bar_lock, flags);
	err = select_core_and_segment(dev, &offset);
	अगर (likely(!err))
		value = पढ़ोw(bus->mmio + offset);
	spin_unlock_irqrestore(&bus->bar_lock, flags);

	वापस value;
पूर्ण

अटल u32 ssb_pcmcia_पढ़ो32(काष्ठा ssb_device *dev, u16 offset)
अणु
	काष्ठा ssb_bus *bus = dev->bus;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;
	u32 lo = 0xFFFFFFFF, hi = 0xFFFFFFFF;

	spin_lock_irqsave(&bus->bar_lock, flags);
	err = select_core_and_segment(dev, &offset);
	अगर (likely(!err)) अणु
		lo = पढ़ोw(bus->mmio + offset);
		hi = पढ़ोw(bus->mmio + offset + 2);
	पूर्ण
	spin_unlock_irqrestore(&bus->bar_lock, flags);

	वापस (lo | (hi << 16));
पूर्ण

#अगर_घोषित CONFIG_SSB_BLOCKIO
अटल व्योम ssb_pcmcia_block_पढ़ो(काष्ठा ssb_device *dev, व्योम *buffer,
				  माप_प्रकार count, u16 offset, u8 reg_width)
अणु
	काष्ठा ssb_bus *bus = dev->bus;
	अचिन्हित दीर्घ flags;
	व्योम __iomem *addr = bus->mmio + offset;
	पूर्णांक err;

	spin_lock_irqsave(&bus->bar_lock, flags);
	err = select_core_and_segment(dev, &offset);
	अगर (unlikely(err)) अणु
		स_रखो(buffer, 0xFF, count);
		जाओ unlock;
	पूर्ण
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
		__le16 *buf = buffer;

		WARN_ON(count & 3);
		जबतक (count) अणु
			*buf = (__क्रमce __le16)__raw_पढ़ोw(addr);
			buf++;
			*buf = (__क्रमce __le16)__raw_पढ़ोw(addr + 2);
			buf++;
			count -= 4;
		पूर्ण
		अवरोध;
	पूर्ण
	शेष:
		WARN_ON(1);
	पूर्ण
unlock:
	spin_unlock_irqrestore(&bus->bar_lock, flags);
पूर्ण
#पूर्ण_अगर /* CONFIG_SSB_BLOCKIO */

अटल व्योम ssb_pcmcia_ग_लिखो8(काष्ठा ssb_device *dev, u16 offset, u8 value)
अणु
	काष्ठा ssb_bus *bus = dev->bus;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	spin_lock_irqsave(&bus->bar_lock, flags);
	err = select_core_and_segment(dev, &offset);
	अगर (likely(!err))
		ग_लिखोb(value, bus->mmio + offset);
	spin_unlock_irqrestore(&bus->bar_lock, flags);
पूर्ण

अटल व्योम ssb_pcmcia_ग_लिखो16(काष्ठा ssb_device *dev, u16 offset, u16 value)
अणु
	काष्ठा ssb_bus *bus = dev->bus;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	spin_lock_irqsave(&bus->bar_lock, flags);
	err = select_core_and_segment(dev, &offset);
	अगर (likely(!err))
		ग_लिखोw(value, bus->mmio + offset);
	spin_unlock_irqrestore(&bus->bar_lock, flags);
पूर्ण

अटल व्योम ssb_pcmcia_ग_लिखो32(काष्ठा ssb_device *dev, u16 offset, u32 value)
अणु
	काष्ठा ssb_bus *bus = dev->bus;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	spin_lock_irqsave(&bus->bar_lock, flags);
	err = select_core_and_segment(dev, &offset);
	अगर (likely(!err)) अणु
		ग_लिखोw((value & 0x0000FFFF), bus->mmio + offset);
		ग_लिखोw(((value & 0xFFFF0000) >> 16), bus->mmio + offset + 2);
	पूर्ण
	spin_unlock_irqrestore(&bus->bar_lock, flags);
पूर्ण

#अगर_घोषित CONFIG_SSB_BLOCKIO
अटल व्योम ssb_pcmcia_block_ग_लिखो(काष्ठा ssb_device *dev, स्थिर व्योम *buffer,
				   माप_प्रकार count, u16 offset, u8 reg_width)
अणु
	काष्ठा ssb_bus *bus = dev->bus;
	अचिन्हित दीर्घ flags;
	व्योम __iomem *addr = bus->mmio + offset;
	पूर्णांक err;

	spin_lock_irqsave(&bus->bar_lock, flags);
	err = select_core_and_segment(dev, &offset);
	अगर (unlikely(err))
		जाओ unlock;
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
		स्थिर __le16 *buf = buffer;

		WARN_ON(count & 3);
		जबतक (count) अणु
			__raw_ग_लिखोw((__क्रमce u16)(*buf), addr);
			buf++;
			__raw_ग_लिखोw((__क्रमce u16)(*buf), addr + 2);
			buf++;
			count -= 4;
		पूर्ण
		अवरोध;
	पूर्ण
	शेष:
		WARN_ON(1);
	पूर्ण
unlock:
	spin_unlock_irqrestore(&bus->bar_lock, flags);
पूर्ण
#पूर्ण_अगर /* CONFIG_SSB_BLOCKIO */

/* Not "static", as it's used in मुख्य.c */
स्थिर काष्ठा ssb_bus_ops ssb_pcmcia_ops = अणु
	.पढ़ो8		= ssb_pcmcia_पढ़ो8,
	.पढ़ो16		= ssb_pcmcia_पढ़ो16,
	.पढ़ो32		= ssb_pcmcia_पढ़ो32,
	.ग_लिखो8		= ssb_pcmcia_ग_लिखो8,
	.ग_लिखो16	= ssb_pcmcia_ग_लिखो16,
	.ग_लिखो32	= ssb_pcmcia_ग_लिखो32,
#अगर_घोषित CONFIG_SSB_BLOCKIO
	.block_पढ़ो	= ssb_pcmcia_block_पढ़ो,
	.block_ग_लिखो	= ssb_pcmcia_block_ग_लिखो,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक ssb_pcmcia_sprom_command(काष्ठा ssb_bus *bus, u8 command)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err;
	u8 value;

	err = ssb_pcmcia_cfg_ग_लिखो(bus, SSB_PCMCIA_SPROMCTL, command);
	अगर (err)
		वापस err;
	क्रम (i = 0; i < 1000; i++) अणु
		err = ssb_pcmcia_cfg_पढ़ो(bus, SSB_PCMCIA_SPROMCTL, &value);
		अगर (err)
			वापस err;
		अगर (value & SSB_PCMCIA_SPROMCTL_DONE)
			वापस 0;
		udelay(10);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

/* offset is the 16bit word offset */
अटल पूर्णांक ssb_pcmcia_sprom_पढ़ो(काष्ठा ssb_bus *bus, u16 offset, u16 *value)
अणु
	पूर्णांक err;
	u8 lo, hi;

	offset *= 2; /* Make byte offset */

	err = ssb_pcmcia_cfg_ग_लिखो(bus, SSB_PCMCIA_SPROM_ADDRLO,
				   (offset & 0x00FF));
	अगर (err)
		वापस err;
	err = ssb_pcmcia_cfg_ग_लिखो(bus, SSB_PCMCIA_SPROM_ADDRHI,
				   (offset & 0xFF00) >> 8);
	अगर (err)
		वापस err;
	err = ssb_pcmcia_sprom_command(bus, SSB_PCMCIA_SPROMCTL_READ);
	अगर (err)
		वापस err;
	err = ssb_pcmcia_cfg_पढ़ो(bus, SSB_PCMCIA_SPROM_DATALO, &lo);
	अगर (err)
		वापस err;
	err = ssb_pcmcia_cfg_पढ़ो(bus, SSB_PCMCIA_SPROM_DATAHI, &hi);
	अगर (err)
		वापस err;
	*value = (lo | (((u16)hi) << 8));

	वापस 0;
पूर्ण

/* offset is the 16bit word offset */
अटल पूर्णांक ssb_pcmcia_sprom_ग_लिखो(काष्ठा ssb_bus *bus, u16 offset, u16 value)
अणु
	पूर्णांक err;

	offset *= 2; /* Make byte offset */

	err = ssb_pcmcia_cfg_ग_लिखो(bus, SSB_PCMCIA_SPROM_ADDRLO,
				   (offset & 0x00FF));
	अगर (err)
		वापस err;
	err = ssb_pcmcia_cfg_ग_लिखो(bus, SSB_PCMCIA_SPROM_ADDRHI,
				   (offset & 0xFF00) >> 8);
	अगर (err)
		वापस err;
	err = ssb_pcmcia_cfg_ग_लिखो(bus, SSB_PCMCIA_SPROM_DATALO,
				   (value & 0x00FF));
	अगर (err)
		वापस err;
	err = ssb_pcmcia_cfg_ग_लिखो(bus, SSB_PCMCIA_SPROM_DATAHI,
				   (value & 0xFF00) >> 8);
	अगर (err)
		वापस err;
	err = ssb_pcmcia_sprom_command(bus, SSB_PCMCIA_SPROMCTL_WRITE);
	अगर (err)
		वापस err;
	msleep(20);

	वापस 0;
पूर्ण

/* Read the SPROM image. bufsize is in 16bit words. */
अटल पूर्णांक ssb_pcmcia_sprom_पढ़ो_all(काष्ठा ssb_bus *bus, u16 *sprom)
अणु
	पूर्णांक err, i;

	क्रम (i = 0; i < SSB_PCMCIA_SPROM_SIZE; i++) अणु
		err = ssb_pcmcia_sprom_पढ़ो(bus, i, &sprom[i]);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/* Write the SPROM image. size is in 16bit words. */
अटल पूर्णांक ssb_pcmcia_sprom_ग_लिखो_all(काष्ठा ssb_bus *bus, स्थिर u16 *sprom)
अणु
	पूर्णांक i, err;
	bool failed = 0;
	माप_प्रकार size = SSB_PCMCIA_SPROM_SIZE;

	pr_notice("Writing SPROM. Do NOT turn off the power! Please stand by...\n");
	err = ssb_pcmcia_sprom_command(bus, SSB_PCMCIA_SPROMCTL_WRITEEN);
	अगर (err) अणु
		pr_notice("Could not enable SPROM write access\n");
		वापस -EBUSY;
	पूर्ण
	pr_notice("[ 0%%");
	msleep(500);
	क्रम (i = 0; i < size; i++) अणु
		अगर (i == size / 4)
			pr_cont("25%%");
		अन्यथा अगर (i == size / 2)
			pr_cont("50%%");
		अन्यथा अगर (i == (size * 3) / 4)
			pr_cont("75%%");
		अन्यथा अगर (i % 2)
			pr_cont(".");
		err = ssb_pcmcia_sprom_ग_लिखो(bus, i, sprom[i]);
		अगर (err) अणु
			pr_notice("Failed to write to SPROM\n");
			failed = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	err = ssb_pcmcia_sprom_command(bus, SSB_PCMCIA_SPROMCTL_WRITEDIS);
	अगर (err) अणु
		pr_notice("Could not disable SPROM write access\n");
		failed = 1;
	पूर्ण
	msleep(500);
	अगर (!failed) अणु
		pr_cont("100%% ]\n");
		pr_notice("SPROM written\n");
	पूर्ण

	वापस failed ? -EBUSY : 0;
पूर्ण

अटल पूर्णांक ssb_pcmcia_sprom_check_crc(स्थिर u16 *sprom, माप_प्रकार size)
अणु
	//TODO
	वापस 0;
पूर्ण

#घोषणा GOTO_ERROR_ON(condition, description) करो अणु	\
	अगर (unlikely(condition)) अणु			\
		error_description = description;	\
		जाओ error;				\
	पूर्ण						\
  पूर्ण जबतक (0)

अटल पूर्णांक ssb_pcmcia_get_mac(काष्ठा pcmcia_device *p_dev,
			tuple_t *tuple,
			व्योम *priv)
अणु
	काष्ठा ssb_sprom *sprom = priv;

	अगर (tuple->TupleData[0] != CISTPL_FUNCE_LAN_NODE_ID)
		वापस -EINVAL;
	अगर (tuple->TupleDataLen != ETH_ALEN + 2)
		वापस -EINVAL;
	अगर (tuple->TupleData[1] != ETH_ALEN)
		वापस -EINVAL;
	स_नकल(sprom->il0mac, &tuple->TupleData[2], ETH_ALEN);
	वापस 0;
पूर्ण;

अटल पूर्णांक ssb_pcmcia_करो_get_invariants(काष्ठा pcmcia_device *p_dev,
					tuple_t *tuple,
					व्योम *priv)
अणु
	काष्ठा ssb_init_invariants *iv = priv;
	काष्ठा ssb_sprom *sprom = &iv->sprom;
	काष्ठा ssb_boardinfo *bi = &iv->boardinfo;
	स्थिर अक्षर *error_description;

	GOTO_ERROR_ON(tuple->TupleDataLen < 1, "VEN tpl < 1");
	चयन (tuple->TupleData[0]) अणु
	हाल SSB_PCMCIA_CIS_ID:
		GOTO_ERROR_ON((tuple->TupleDataLen != 5) &&
			      (tuple->TupleDataLen != 7),
			      "id tpl size");
		bi->venकरोr = tuple->TupleData[1] |
			((u16)tuple->TupleData[2] << 8);
		अवरोध;
	हाल SSB_PCMCIA_CIS_BOARDREV:
		GOTO_ERROR_ON(tuple->TupleDataLen != 2,
			"boardrev tpl size");
		sprom->board_rev = tuple->TupleData[1];
		अवरोध;
	हाल SSB_PCMCIA_CIS_PA:
		GOTO_ERROR_ON((tuple->TupleDataLen != 9) &&
			(tuple->TupleDataLen != 10),
			"pa tpl size");
		sprom->pa0b0 = tuple->TupleData[1] |
			((u16)tuple->TupleData[2] << 8);
		sprom->pa0b1 = tuple->TupleData[3] |
			((u16)tuple->TupleData[4] << 8);
		sprom->pa0b2 = tuple->TupleData[5] |
			((u16)tuple->TupleData[6] << 8);
		sprom->itssi_a = tuple->TupleData[7];
		sprom->itssi_bg = tuple->TupleData[7];
		sprom->maxpwr_a = tuple->TupleData[8];
		sprom->maxpwr_bg = tuple->TupleData[8];
		अवरोध;
	हाल SSB_PCMCIA_CIS_OEMNAME:
		/* We ignore this. */
		अवरोध;
	हाल SSB_PCMCIA_CIS_CCODE:
		GOTO_ERROR_ON(tuple->TupleDataLen != 2,
			"ccode tpl size");
		sprom->country_code = tuple->TupleData[1];
		अवरोध;
	हाल SSB_PCMCIA_CIS_ANTENNA:
		GOTO_ERROR_ON(tuple->TupleDataLen != 2,
			"ant tpl size");
		sprom->ant_available_a = tuple->TupleData[1];
		sprom->ant_available_bg = tuple->TupleData[1];
		अवरोध;
	हाल SSB_PCMCIA_CIS_ANTGAIN:
		GOTO_ERROR_ON(tuple->TupleDataLen != 2,
			"antg tpl size");
		sprom->antenna_gain.a0 = tuple->TupleData[1];
		sprom->antenna_gain.a1 = tuple->TupleData[1];
		sprom->antenna_gain.a2 = tuple->TupleData[1];
		sprom->antenna_gain.a3 = tuple->TupleData[1];
		अवरोध;
	हाल SSB_PCMCIA_CIS_BFLAGS:
		GOTO_ERROR_ON((tuple->TupleDataLen != 3) &&
			(tuple->TupleDataLen != 5),
			"bfl tpl size");
		sprom->boardflags_lo = tuple->TupleData[1] |
			((u16)tuple->TupleData[2] << 8);
		अवरोध;
	हाल SSB_PCMCIA_CIS_LEDS:
		GOTO_ERROR_ON(tuple->TupleDataLen != 5,
			"leds tpl size");
		sprom->gpio0 = tuple->TupleData[1];
		sprom->gpio1 = tuple->TupleData[2];
		sprom->gpio2 = tuple->TupleData[3];
		sprom->gpio3 = tuple->TupleData[4];
		अवरोध;
	पूर्ण
	वापस -ENOSPC; /* जारी with next entry */

error:
	pr_err("PCMCIA: Failed to fetch device invariants: %s\n",
	       error_description);
	वापस -ENODEV;
पूर्ण


पूर्णांक ssb_pcmcia_get_invariants(काष्ठा ssb_bus *bus,
			      काष्ठा ssb_init_invariants *iv)
अणु
	काष्ठा ssb_sprom *sprom = &iv->sprom;
	पूर्णांक res;

	स_रखो(sprom, 0xFF, माप(*sprom));
	sprom->revision = 1;
	sprom->boardflags_lo = 0;
	sprom->boardflags_hi = 0;

	/* First fetch the MAC address. */
	res = pcmcia_loop_tuple(bus->host_pcmcia, CISTPL_FUNCE,
				ssb_pcmcia_get_mac, sprom);
	अगर (res != 0) अणु
		pr_err("PCMCIA: Failed to fetch MAC address\n");
		वापस -ENODEV;
	पूर्ण

	/* Fetch the venकरोr specअगरic tuples. */
	res = pcmcia_loop_tuple(bus->host_pcmcia, SSB_PCMCIA_CIS,
				ssb_pcmcia_करो_get_invariants, iv);
	अगर ((res == 0) || (res == -ENOSPC))
		वापस 0;

	pr_err("PCMCIA: Failed to fetch device invariants\n");
	वापस -ENODEV;
पूर्ण

अटल sमाप_प्रकार ssb_pcmcia_attr_sprom_show(काष्ठा device *pcmciadev,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	काष्ठा pcmcia_device *pdev =
		container_of(pcmciadev, काष्ठा pcmcia_device, dev);
	काष्ठा ssb_bus *bus;

	bus = ssb_pcmcia_dev_to_bus(pdev);
	अगर (!bus)
		वापस -ENODEV;

	वापस ssb_attr_sprom_show(bus, buf,
				   ssb_pcmcia_sprom_पढ़ो_all);
पूर्ण

अटल sमाप_प्रकार ssb_pcmcia_attr_sprom_store(काष्ठा device *pcmciadev,
					   काष्ठा device_attribute *attr,
					   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा pcmcia_device *pdev =
		container_of(pcmciadev, काष्ठा pcmcia_device, dev);
	काष्ठा ssb_bus *bus;

	bus = ssb_pcmcia_dev_to_bus(pdev);
	अगर (!bus)
		वापस -ENODEV;

	वापस ssb_attr_sprom_store(bus, buf, count,
				    ssb_pcmcia_sprom_check_crc,
				    ssb_pcmcia_sprom_ग_लिखो_all);
पूर्ण

अटल DEVICE_ATTR(ssb_sprom, 0600,
		   ssb_pcmcia_attr_sprom_show,
		   ssb_pcmcia_attr_sprom_store);

अटल पूर्णांक ssb_pcmcia_cor_setup(काष्ठा ssb_bus *bus, u8 cor)
अणु
	u8 val;
	पूर्णांक err;

	err = ssb_pcmcia_cfg_पढ़ो(bus, cor, &val);
	अगर (err)
		वापस err;
	val &= ~COR_SOFT_RESET;
	val |= COR_FUNC_ENA | COR_IREQ_ENA | COR_LEVEL_REQ;
	err = ssb_pcmcia_cfg_ग_लिखो(bus, cor, val);
	अगर (err)
		वापस err;
	msleep(40);

	वापस 0;
पूर्ण

/* Initialize the PCMCIA hardware. This is called on Init and Resume. */
पूर्णांक ssb_pcmcia_hardware_setup(काष्ठा ssb_bus *bus)
अणु
	पूर्णांक err;

	अगर (bus->bustype != SSB_BUSTYPE_PCMCIA)
		वापस 0;

	/* Switch segment to a known state and sync
	 * bus->mapped_pcmcia_seg with hardware state. */
	ssb_pcmcia_चयन_segment(bus, 0);
	/* Init the COR रेजिस्टर. */
	err = ssb_pcmcia_cor_setup(bus, CISREG_COR);
	अगर (err)
		वापस err;
	/* Some cards also need this रेजिस्टर to get poked. */
	err = ssb_pcmcia_cor_setup(bus, CISREG_COR + 0x80);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

व्योम ssb_pcmcia_निकास(काष्ठा ssb_bus *bus)
अणु
	अगर (bus->bustype != SSB_BUSTYPE_PCMCIA)
		वापस;

	device_हटाओ_file(&bus->host_pcmcia->dev, &dev_attr_ssb_sprom);
पूर्ण

पूर्णांक ssb_pcmcia_init(काष्ठा ssb_bus *bus)
अणु
	पूर्णांक err;

	अगर (bus->bustype != SSB_BUSTYPE_PCMCIA)
		वापस 0;

	err = ssb_pcmcia_hardware_setup(bus);
	अगर (err)
		जाओ error;

	bus->sprom_size = SSB_PCMCIA_SPROM_SIZE;
	mutex_init(&bus->sprom_mutex);
	err = device_create_file(&bus->host_pcmcia->dev, &dev_attr_ssb_sprom);
	अगर (err)
		जाओ error;

	वापस 0;
error:
	pr_err("Failed to initialize PCMCIA host device\n");
	वापस err;
पूर्ण
