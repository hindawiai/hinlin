<शैली गुरु>
/*
 * Sonics Silicon Backplane
 * SDIO-Hostbus related functions
 *
 * Copyright 2009 Albert Herranz <albert_herranz@yahoo.es>
 *
 * Based on drivers/ssb/pcmcia.c
 * Copyright 2006 Johannes Berg <johannes@sipsolutions.net>
 * Copyright 2007-2008 Michael Buesch <m@bues.ch>
 *
 * Licensed under the GNU/GPL. See COPYING क्रम details.
 *
 */

#समावेश "ssb_private.h"

#समावेश <linux/ssb/ssb.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/etherdevice.h>
#समावेश <linux/mmc/sdio_func.h>

/* Define the following to 1 to enable a prपूर्णांकk on each coreचयन. */
#घोषणा SSB_VERBOSE_SDIOCORESWITCH_DEBUG		0


/* Hardware invariants CIS tuples */
#घोषणा SSB_SDIO_CIS			0x80
#घोषणा  SSB_SDIO_CIS_SROMREV		0x00
#घोषणा  SSB_SDIO_CIS_ID		0x01
#घोषणा  SSB_SDIO_CIS_BOARDREV		0x02
#घोषणा  SSB_SDIO_CIS_PA		0x03
#घोषणा   SSB_SDIO_CIS_PA_PA0B0_LO	0
#घोषणा   SSB_SDIO_CIS_PA_PA0B0_HI	1
#घोषणा   SSB_SDIO_CIS_PA_PA0B1_LO	2
#घोषणा   SSB_SDIO_CIS_PA_PA0B1_HI	3
#घोषणा   SSB_SDIO_CIS_PA_PA0B2_LO	4
#घोषणा   SSB_SDIO_CIS_PA_PA0B2_HI	5
#घोषणा   SSB_SDIO_CIS_PA_ITSSI		6
#घोषणा   SSB_SDIO_CIS_PA_MAXPOW	7
#घोषणा  SSB_SDIO_CIS_OEMNAME		0x04
#घोषणा  SSB_SDIO_CIS_CCODE		0x05
#घोषणा  SSB_SDIO_CIS_ANTENNA		0x06
#घोषणा  SSB_SDIO_CIS_ANTGAIN		0x07
#घोषणा  SSB_SDIO_CIS_BFLAGS		0x08
#घोषणा  SSB_SDIO_CIS_LEDS		0x09

#घोषणा CISTPL_FUNCE_LAN_NODE_ID        0x04	/* same as in PCMCIA */


/*
 * Function 1 miscellaneous रेजिस्टरs.
 *
 * Definitions match src/include/sbsdपन.स from the
 * Android Open Source Project
 * http://android.git.kernel.org/?p=platक्रमm/प्रणाली/wlan/broadcom.git
 *
 */
#घोषणा SBSDIO_FUNC1_SBADDRLOW	0x1000a	/* SB Address winकरोw Low (b15) */
#घोषणा SBSDIO_FUNC1_SBADDRMID	0x1000b	/* SB Address winकरोw Mid (b23-b16) */
#घोषणा SBSDIO_FUNC1_SBADDRHIGH	0x1000c	/* SB Address winकरोw High (b24-b31) */

/* valid bits in SBSDIO_FUNC1_SBADDRxxx regs */
#घोषणा SBSDIO_SBADDRLOW_MASK	0x80	/* Valid address bits in SBADDRLOW */
#घोषणा SBSDIO_SBADDRMID_MASK	0xff	/* Valid address bits in SBADDRMID */
#घोषणा SBSDIO_SBADDRHIGH_MASK	0xff	/* Valid address bits in SBADDRHIGH */

#घोषणा SBSDIO_SB_OFT_ADDR_MASK	0x7FFF	/* sb offset addr is <= 15 bits, 32k */

/* REVISIT: this flag करोesn't seem to matter */
#घोषणा SBSDIO_SB_ACCESS_2_4B_FLAG	0x8000	/* क्रमces 32-bit SB access */


/*
 * Address map within the SDIO function address space (128K).
 *
 *   Start   End     Description
 *   ------- ------- ------------------------------------------
 *   0x00000 0x0ffff selected backplane address winकरोw (64K)
 *   0x10000 0x1ffff backplane control रेजिस्टरs (max 64K)
 *
 * The current address winकरोw is configured by writing to रेजिस्टरs
 * SBADDRLOW, SBADDRMID and SBADDRHIGH.
 *
 * In order to access the contents of a 32-bit Silicon Backplane address
 * the backplane address winकरोw must be first loaded with the highest
 * 16 bits of the target address. Then, an access must be करोne to the
 * SDIO function address space using the lower 15 bits of the address.
 * Bit 15 of the address must be set when करोing 32 bit accesses.
 *
 * 10987654321098765432109876543210
 * WWWWWWWWWWWWWWWWW                 SB Address Winकरोw
 *                 OOOOOOOOOOOOOOOO  Offset within SB Address Winकरोw
 *                 a                 32-bit access flag
 */


/*
 * SSB I/O via SDIO.
 *
 * NOTE: SDIO address @addr is 17 bits दीर्घ (SDIO address space is 128K).
 */

अटल अंतरभूत काष्ठा device *ssb_sdio_dev(काष्ठा ssb_bus *bus)
अणु
	वापस &bus->host_sdio->dev;
पूर्ण

/* host claimed */
अटल पूर्णांक ssb_sdio_ग_लिखोb(काष्ठा ssb_bus *bus, अचिन्हित पूर्णांक addr, u8 val)
अणु
	पूर्णांक error = 0;

	sdio_ग_लिखोb(bus->host_sdio, val, addr, &error);
	अगर (unlikely(error)) अणु
		dev_dbg(ssb_sdio_dev(bus), "%08X <- %02x, error %d\n",
			addr, val, error);
	पूर्ण

	वापस error;
पूर्ण

#अगर 0
अटल u8 ssb_sdio_पढ़ोb(काष्ठा ssb_bus *bus, अचिन्हित पूर्णांक addr)
अणु
	u8 val;
	पूर्णांक error = 0;

	val = sdio_पढ़ोb(bus->host_sdio, addr, &error);
	अगर (unlikely(error)) अणु
		dev_dbg(ssb_sdio_dev(bus), "%08X -> %02x, error %d\n",
			addr, val, error);
	पूर्ण

	वापस val;
पूर्ण
#पूर्ण_अगर

/* host claimed */
अटल पूर्णांक ssb_sdio_set_sbaddr_winकरोw(काष्ठा ssb_bus *bus, u32 address)
अणु
	पूर्णांक error;

	error = ssb_sdio_ग_लिखोb(bus, SBSDIO_FUNC1_SBADDRLOW,
				(address >> 8) & SBSDIO_SBADDRLOW_MASK);
	अगर (error)
		जाओ out;
	error = ssb_sdio_ग_लिखोb(bus, SBSDIO_FUNC1_SBADDRMID,
				(address >> 16) & SBSDIO_SBADDRMID_MASK);
	अगर (error)
		जाओ out;
	error = ssb_sdio_ग_लिखोb(bus, SBSDIO_FUNC1_SBADDRHIGH,
				(address >> 24) & SBSDIO_SBADDRHIGH_MASK);
	अगर (error)
		जाओ out;
	bus->sdio_sbaddr = address;
out:
	अगर (error) अणु
		dev_dbg(ssb_sdio_dev(bus), "failed to set address window"
			" to 0x%08x, error %d\n", address, error);
	पूर्ण

	वापस error;
पूर्ण

/* क्रम क्रमागतeration use only */
u32 ssb_sdio_scan_पढ़ो32(काष्ठा ssb_bus *bus, u16 offset)
अणु
	u32 val;
	पूर्णांक error;

	sdio_claim_host(bus->host_sdio);
	val = sdio_पढ़ोl(bus->host_sdio, offset, &error);
	sdio_release_host(bus->host_sdio);
	अगर (unlikely(error)) अणु
		dev_dbg(ssb_sdio_dev(bus), "%04X:%04X > %08x, error %d\n",
			bus->sdio_sbaddr >> 16, offset, val, error);
	पूर्ण

	वापस val;
पूर्ण

/* क्रम क्रमागतeration use only */
पूर्णांक ssb_sdio_scan_चयन_coreidx(काष्ठा ssb_bus *bus, u8 coreidx)
अणु
	u32 sbaddr;
	पूर्णांक error;

	sbaddr = (coreidx * SSB_CORE_SIZE) + SSB_ENUM_BASE;
	sdio_claim_host(bus->host_sdio);
	error = ssb_sdio_set_sbaddr_winकरोw(bus, sbaddr);
	sdio_release_host(bus->host_sdio);
	अगर (error) अणु
		dev_err(ssb_sdio_dev(bus), "failed to switch to core %u,"
			" error %d\n", coreidx, error);
		जाओ out;
	पूर्ण
out:
	वापस error;
पूर्ण

/* host must be alपढ़ोy claimed */
अटल पूर्णांक ssb_sdio_चयन_core(काष्ठा ssb_bus *bus, काष्ठा ssb_device *dev)
अणु
	u8 coreidx = dev->core_index;
	u32 sbaddr;
	पूर्णांक error = 0;

	sbaddr = (coreidx * SSB_CORE_SIZE) + SSB_ENUM_BASE;
	अगर (unlikely(bus->sdio_sbaddr != sbaddr)) अणु
#अगर SSB_VERBOSE_SDIOCORESWITCH_DEBUG
		dev_info(ssb_sdio_dev(bus),
			   "switching to %s core, index %d\n",
			   ssb_core_name(dev->id.coreid), coreidx);
#पूर्ण_अगर
		error = ssb_sdio_set_sbaddr_winकरोw(bus, sbaddr);
		अगर (error) अणु
			dev_dbg(ssb_sdio_dev(bus), "failed to switch to"
				" core %u, error %d\n", coreidx, error);
			जाओ out;
		पूर्ण
		bus->mapped_device = dev;
	पूर्ण

out:
	वापस error;
पूर्ण

अटल u8 ssb_sdio_पढ़ो8(काष्ठा ssb_device *dev, u16 offset)
अणु
	काष्ठा ssb_bus *bus = dev->bus;
	u8 val = 0xff;
	पूर्णांक error = 0;

	sdio_claim_host(bus->host_sdio);
	अगर (unlikely(ssb_sdio_चयन_core(bus, dev)))
		जाओ out;
	offset |= bus->sdio_sbaddr & 0xffff;
	offset &= SBSDIO_SB_OFT_ADDR_MASK;
	val = sdio_पढ़ोb(bus->host_sdio, offset, &error);
	अगर (error) अणु
		dev_dbg(ssb_sdio_dev(bus), "%04X:%04X > %02x, error %d\n",
			bus->sdio_sbaddr >> 16, offset, val, error);
	पूर्ण
out:
	sdio_release_host(bus->host_sdio);

	वापस val;
पूर्ण

अटल u16 ssb_sdio_पढ़ो16(काष्ठा ssb_device *dev, u16 offset)
अणु
	काष्ठा ssb_bus *bus = dev->bus;
	u16 val = 0xffff;
	पूर्णांक error = 0;

	sdio_claim_host(bus->host_sdio);
	अगर (unlikely(ssb_sdio_चयन_core(bus, dev)))
		जाओ out;
	offset |= bus->sdio_sbaddr & 0xffff;
	offset &= SBSDIO_SB_OFT_ADDR_MASK;
	val = sdio_पढ़ोw(bus->host_sdio, offset, &error);
	अगर (error) अणु
		dev_dbg(ssb_sdio_dev(bus), "%04X:%04X > %04x, error %d\n",
			bus->sdio_sbaddr >> 16, offset, val, error);
	पूर्ण
out:
	sdio_release_host(bus->host_sdio);

	वापस val;
पूर्ण

अटल u32 ssb_sdio_पढ़ो32(काष्ठा ssb_device *dev, u16 offset)
अणु
	काष्ठा ssb_bus *bus = dev->bus;
	u32 val = 0xffffffff;
	पूर्णांक error = 0;

	sdio_claim_host(bus->host_sdio);
	अगर (unlikely(ssb_sdio_चयन_core(bus, dev)))
		जाओ out;
	offset |= bus->sdio_sbaddr & 0xffff;
	offset &= SBSDIO_SB_OFT_ADDR_MASK;
	offset |= SBSDIO_SB_ACCESS_2_4B_FLAG;	/* 32 bit data access */
	val = sdio_पढ़ोl(bus->host_sdio, offset, &error);
	अगर (error) अणु
		dev_dbg(ssb_sdio_dev(bus), "%04X:%04X > %08x, error %d\n",
			bus->sdio_sbaddr >> 16, offset, val, error);
	पूर्ण
out:
	sdio_release_host(bus->host_sdio);

	वापस val;
पूर्ण

#अगर_घोषित CONFIG_SSB_BLOCKIO
अटल व्योम ssb_sdio_block_पढ़ो(काष्ठा ssb_device *dev, व्योम *buffer,
				  माप_प्रकार count, u16 offset, u8 reg_width)
अणु
	माप_प्रकार saved_count = count;
	काष्ठा ssb_bus *bus = dev->bus;
	पूर्णांक error = 0;

	sdio_claim_host(bus->host_sdio);
	अगर (unlikely(ssb_sdio_चयन_core(bus, dev))) अणु
		error = -EIO;
		स_रखो(buffer, 0xff, count);
		जाओ err_out;
	पूर्ण
	offset |= bus->sdio_sbaddr & 0xffff;
	offset &= SBSDIO_SB_OFT_ADDR_MASK;

	चयन (reg_width) अणु
	हाल माप(u8): अणु
		error = sdio_पढ़ोsb(bus->host_sdio, buffer, offset, count);
		अवरोध;
	पूर्ण
	हाल माप(u16): अणु
		WARN_ON(count & 1);
		error = sdio_पढ़ोsb(bus->host_sdio, buffer, offset, count);
		अवरोध;
	पूर्ण
	हाल माप(u32): अणु
		WARN_ON(count & 3);
		offset |= SBSDIO_SB_ACCESS_2_4B_FLAG;	/* 32 bit data access */
		error = sdio_पढ़ोsb(bus->host_sdio, buffer, offset, count);
		अवरोध;
	पूर्ण
	शेष:
		WARN_ON(1);
	पूर्ण
	अगर (!error)
		जाओ out;

err_out:
	dev_dbg(ssb_sdio_dev(bus), "%04X:%04X (width=%u, len=%zu), error %d\n",
		bus->sdio_sbaddr >> 16, offset, reg_width, saved_count, error);
out:
	sdio_release_host(bus->host_sdio);
पूर्ण
#पूर्ण_अगर /* CONFIG_SSB_BLOCKIO */

अटल व्योम ssb_sdio_ग_लिखो8(काष्ठा ssb_device *dev, u16 offset, u8 val)
अणु
	काष्ठा ssb_bus *bus = dev->bus;
	पूर्णांक error = 0;

	sdio_claim_host(bus->host_sdio);
	अगर (unlikely(ssb_sdio_चयन_core(bus, dev)))
		जाओ out;
	offset |= bus->sdio_sbaddr & 0xffff;
	offset &= SBSDIO_SB_OFT_ADDR_MASK;
	sdio_ग_लिखोb(bus->host_sdio, val, offset, &error);
	अगर (error) अणु
		dev_dbg(ssb_sdio_dev(bus), "%04X:%04X < %02x, error %d\n",
			bus->sdio_sbaddr >> 16, offset, val, error);
	पूर्ण
out:
	sdio_release_host(bus->host_sdio);
पूर्ण

अटल व्योम ssb_sdio_ग_लिखो16(काष्ठा ssb_device *dev, u16 offset, u16 val)
अणु
	काष्ठा ssb_bus *bus = dev->bus;
	पूर्णांक error = 0;

	sdio_claim_host(bus->host_sdio);
	अगर (unlikely(ssb_sdio_चयन_core(bus, dev)))
		जाओ out;
	offset |= bus->sdio_sbaddr & 0xffff;
	offset &= SBSDIO_SB_OFT_ADDR_MASK;
	sdio_ग_लिखोw(bus->host_sdio, val, offset, &error);
	अगर (error) अणु
		dev_dbg(ssb_sdio_dev(bus), "%04X:%04X < %04x, error %d\n",
			bus->sdio_sbaddr >> 16, offset, val, error);
	पूर्ण
out:
	sdio_release_host(bus->host_sdio);
पूर्ण

अटल व्योम ssb_sdio_ग_लिखो32(काष्ठा ssb_device *dev, u16 offset, u32 val)
अणु
	काष्ठा ssb_bus *bus = dev->bus;
	पूर्णांक error = 0;

	sdio_claim_host(bus->host_sdio);
	अगर (unlikely(ssb_sdio_चयन_core(bus, dev)))
		जाओ out;
	offset |= bus->sdio_sbaddr & 0xffff;
	offset &= SBSDIO_SB_OFT_ADDR_MASK;
	offset |= SBSDIO_SB_ACCESS_2_4B_FLAG;	/* 32 bit data access */
	sdio_ग_लिखोl(bus->host_sdio, val, offset, &error);
	अगर (error) अणु
		dev_dbg(ssb_sdio_dev(bus), "%04X:%04X < %08x, error %d\n",
			bus->sdio_sbaddr >> 16, offset, val, error);
	पूर्ण
	अगर (bus->quirks & SSB_QUIRK_SDIO_READ_AFTER_WRITE32)
		sdio_पढ़ोl(bus->host_sdio, 0, &error);
out:
	sdio_release_host(bus->host_sdio);
पूर्ण

#अगर_घोषित CONFIG_SSB_BLOCKIO
अटल व्योम ssb_sdio_block_ग_लिखो(काष्ठा ssb_device *dev, स्थिर व्योम *buffer,
				   माप_प्रकार count, u16 offset, u8 reg_width)
अणु
	माप_प्रकार saved_count = count;
	काष्ठा ssb_bus *bus = dev->bus;
	पूर्णांक error = 0;

	sdio_claim_host(bus->host_sdio);
	अगर (unlikely(ssb_sdio_चयन_core(bus, dev))) अणु
		error = -EIO;
		स_रखो((व्योम *)buffer, 0xff, count);
		जाओ err_out;
	पूर्ण
	offset |= bus->sdio_sbaddr & 0xffff;
	offset &= SBSDIO_SB_OFT_ADDR_MASK;

	चयन (reg_width) अणु
	हाल माप(u8):
		error = sdio_ग_लिखोsb(bus->host_sdio, offset,
				     (व्योम *)buffer, count);
		अवरोध;
	हाल माप(u16):
		WARN_ON(count & 1);
		error = sdio_ग_लिखोsb(bus->host_sdio, offset,
				     (व्योम *)buffer, count);
		अवरोध;
	हाल माप(u32):
		WARN_ON(count & 3);
		offset |= SBSDIO_SB_ACCESS_2_4B_FLAG;	/* 32 bit data access */
		error = sdio_ग_लिखोsb(bus->host_sdio, offset,
				     (व्योम *)buffer, count);
		अवरोध;
	शेष:
		WARN_ON(1);
	पूर्ण
	अगर (!error)
		जाओ out;

err_out:
	dev_dbg(ssb_sdio_dev(bus), "%04X:%04X (width=%u, len=%zu), error %d\n",
		bus->sdio_sbaddr >> 16, offset, reg_width, saved_count, error);
out:
	sdio_release_host(bus->host_sdio);
पूर्ण

#पूर्ण_अगर /* CONFIG_SSB_BLOCKIO */

/* Not "static", as it's used in मुख्य.c */
स्थिर काष्ठा ssb_bus_ops ssb_sdio_ops = अणु
	.पढ़ो8		= ssb_sdio_पढ़ो8,
	.पढ़ो16		= ssb_sdio_पढ़ो16,
	.पढ़ो32		= ssb_sdio_पढ़ो32,
	.ग_लिखो8		= ssb_sdio_ग_लिखो8,
	.ग_लिखो16	= ssb_sdio_ग_लिखो16,
	.ग_लिखो32	= ssb_sdio_ग_लिखो32,
#अगर_घोषित CONFIG_SSB_BLOCKIO
	.block_पढ़ो	= ssb_sdio_block_पढ़ो,
	.block_ग_लिखो	= ssb_sdio_block_ग_लिखो,
#पूर्ण_अगर
पूर्ण;

#घोषणा GOTO_ERROR_ON(condition, description) करो अणु	\
	अगर (unlikely(condition)) अणु			\
		error_description = description;	\
		जाओ error;				\
	पूर्ण						\
  पूर्ण जबतक (0)

पूर्णांक ssb_sdio_get_invariants(काष्ठा ssb_bus *bus,
			    काष्ठा ssb_init_invariants *iv)
अणु
	काष्ठा ssb_sprom *sprom = &iv->sprom;
	काष्ठा ssb_boardinfo *bi = &iv->boardinfo;
	स्थिर अक्षर *error_description = "none";
	काष्ठा sdio_func_tuple *tuple;
	व्योम *mac;

	स_रखो(sprom, 0xFF, माप(*sprom));
	sprom->boardflags_lo = 0;
	sprom->boardflags_hi = 0;

	tuple = bus->host_sdio->tuples;
	जबतक (tuple) अणु
		चयन (tuple->code) अणु
		हाल 0x22: /* extended function */
			चयन (tuple->data[0]) अणु
			हाल CISTPL_FUNCE_LAN_NODE_ID:
				GOTO_ERROR_ON((tuple->size != 7) &&
					      (tuple->data[1] != 6),
					      "mac tpl size");
				/* fetch the MAC address. */
				mac = tuple->data + 2;
				स_नकल(sprom->il0mac, mac, ETH_ALEN);
				स_नकल(sprom->et1mac, mac, ETH_ALEN);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			अवरोध;
		हाल 0x80: /* venकरोr specअगरic tuple */
			चयन (tuple->data[0]) अणु
			हाल SSB_SDIO_CIS_SROMREV:
				GOTO_ERROR_ON(tuple->size != 2,
					      "sromrev tpl size");
				sprom->revision = tuple->data[1];
				अवरोध;
			हाल SSB_SDIO_CIS_ID:
				GOTO_ERROR_ON((tuple->size != 5) &&
					      (tuple->size != 7),
					      "id tpl size");
				bi->venकरोr = tuple->data[1] |
					     (tuple->data[2]<<8);
				अवरोध;
			हाल SSB_SDIO_CIS_BOARDREV:
				GOTO_ERROR_ON(tuple->size != 2,
					      "boardrev tpl size");
				sprom->board_rev = tuple->data[1];
				अवरोध;
			हाल SSB_SDIO_CIS_PA:
				GOTO_ERROR_ON((tuple->size != 9) &&
					      (tuple->size != 10),
					      "pa tpl size");
				sprom->pa0b0 = tuple->data[1] |
					 ((u16)tuple->data[2] << 8);
				sprom->pa0b1 = tuple->data[3] |
					 ((u16)tuple->data[4] << 8);
				sprom->pa0b2 = tuple->data[5] |
					 ((u16)tuple->data[6] << 8);
				sprom->itssi_a = tuple->data[7];
				sprom->itssi_bg = tuple->data[7];
				sprom->maxpwr_a = tuple->data[8];
				sprom->maxpwr_bg = tuple->data[8];
				अवरोध;
			हाल SSB_SDIO_CIS_OEMNAME:
				/* Not present */
				अवरोध;
			हाल SSB_SDIO_CIS_CCODE:
				GOTO_ERROR_ON(tuple->size != 2,
					      "ccode tpl size");
				sprom->country_code = tuple->data[1];
				अवरोध;
			हाल SSB_SDIO_CIS_ANTENNA:
				GOTO_ERROR_ON(tuple->size != 2,
					      "ant tpl size");
				sprom->ant_available_a = tuple->data[1];
				sprom->ant_available_bg = tuple->data[1];
				अवरोध;
			हाल SSB_SDIO_CIS_ANTGAIN:
				GOTO_ERROR_ON(tuple->size != 2,
					      "antg tpl size");
				sprom->antenna_gain.a0 = tuple->data[1];
				sprom->antenna_gain.a1 = tuple->data[1];
				sprom->antenna_gain.a2 = tuple->data[1];
				sprom->antenna_gain.a3 = tuple->data[1];
				अवरोध;
			हाल SSB_SDIO_CIS_BFLAGS:
				GOTO_ERROR_ON((tuple->size != 3) &&
					      (tuple->size != 5),
					      "bfl tpl size");
				sprom->boardflags_lo = tuple->data[1] |
						 ((u16)tuple->data[2] << 8);
				अवरोध;
			हाल SSB_SDIO_CIS_LEDS:
				GOTO_ERROR_ON(tuple->size != 5,
					      "leds tpl size");
				sprom->gpio0 = tuple->data[1];
				sprom->gpio1 = tuple->data[2];
				sprom->gpio2 = tuple->data[3];
				sprom->gpio3 = tuple->data[4];
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		tuple = tuple->next;
	पूर्ण

	वापस 0;
error:
	dev_err(ssb_sdio_dev(bus), "failed to fetch device invariants: %s\n",
		error_description);
	वापस -ENODEV;
पूर्ण

व्योम ssb_sdio_निकास(काष्ठा ssb_bus *bus)
अणु
	अगर (bus->bustype != SSB_BUSTYPE_SDIO)
		वापस;
	/* Nothing to करो here. */
पूर्ण

पूर्णांक ssb_sdio_init(काष्ठा ssb_bus *bus)
अणु
	अगर (bus->bustype != SSB_BUSTYPE_SDIO)
		वापस 0;

	bus->sdio_sbaddr = ~0;

	वापस 0;
पूर्ण
