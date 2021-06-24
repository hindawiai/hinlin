<शैली गुरु>
/*
 *	Interface to the TURBOchannel related routines.
 *
 *	Copyright (c) 1998  Harald Koerfgen
 *	Copyright (c) 2005  James Simmons
 *	Copyright (c) 2006  Maciej W. Rozycki
 *
 *	Based on:
 *
 *	"TURBOchannel Firmware Specification", EK-TCAAD-FS-004
 *
 *	from Digital Equipment Corporation.
 *
 *	This file is subject to the terms and conditions of the GNU
 *	General Public License.  See the file "COPYING" in the मुख्य
 *	directory of this archive क्रम more details.
 */
#अगर_अघोषित _LINUX_TC_H
#घोषणा _LINUX_TC_H

#समावेश <linux/compiler.h>
#समावेश <linux/device.h>
#समावेश <linux/ioport.h>
#समावेश <linux/types.h>

/*
 * Offsets क्रम the ROM header locations क्रम TURBOchannel cards.
 */
#घोषणा TC_OLDCARD	0x3c0000
#घोषणा TC_NEWCARD	0x000000

#घोषणा TC_ROM_WIDTH	0x3e0
#घोषणा TC_ROM_STRIDE	0x3e4
#घोषणा TC_ROM_SIZE	0x3e8
#घोषणा TC_SLOT_SIZE	0x3ec
#घोषणा TC_PATTERN0	0x3f0
#घोषणा TC_PATTERN1	0x3f4
#घोषणा TC_PATTERN2	0x3f8
#घोषणा TC_PATTERN3	0x3fc
#घोषणा TC_FIRM_VER	0x400
#घोषणा TC_VENDOR	0x420
#घोषणा TC_MODULE	0x440
#घोषणा TC_FIRM_TYPE	0x460
#घोषणा TC_FLAGS	0x470
#घोषणा TC_ROM_OBJECTS	0x480

/*
 * Inक्रमmation obtained through the get_tcinfo() PROM call.
 */
काष्ठा tcinfo अणु
	s32		revision;	/* Hardware revision level. */
	s32		clk_period;	/* Clock period in nanoseconds. */
	s32		slot_size;	/* Slot size in megabytes. */
	s32		io_समयout;	/* I/O समयout in cycles. */
	s32		dma_range;	/* DMA address range in megabytes. */
	s32		max_dma_burst;	/* Maximum DMA burst length. */
	s32		parity;		/* System module supports TC parity. */
	s32		reserved[4];
पूर्ण;

/*
 * TURBOchannel bus.
 */
काष्ठा tc_bus अणु
	काष्ठा list_head devices;	/* List of devices on this bus. */
	काष्ठा resource	resource[2];	/* Address space routed to this bus. */

	काष्ठा device	dev;
	अक्षर		name[13];
	resource_माप_प्रकार	slot_base;
	resource_माप_प्रकार	ext_slot_base;
	resource_माप_प्रकार	ext_slot_size;
	पूर्णांक		num_tcslots;
	काष्ठा tcinfo	info;
पूर्ण;

/*
 * TURBOchannel device.
 */
काष्ठा tc_dev अणु
	काष्ठा list_head node;		/* Node in list of all TC devices. */
	काष्ठा tc_bus	*bus;		/* Bus this device is on. */
	काष्ठा tc_driver *driver;	/* Which driver has allocated this
					   device. */
	काष्ठा device	dev;		/* Generic device पूर्णांकerface. */
	काष्ठा resource	resource;	/* Address space of this device. */
	u64		dma_mask;	/* DMA addressable range. */
	अक्षर		venकरोr[9];
	अक्षर		name[9];
	अक्षर		firmware[9];
	पूर्णांक		पूर्णांकerrupt;
	पूर्णांक		slot;
पूर्ण;

#घोषणा to_tc_dev(n) container_of(n, काष्ठा tc_dev, dev)

काष्ठा tc_device_id अणु
	अक्षर		venकरोr[9];
	अक्षर		name[9];
पूर्ण;

/*
 * TURBOchannel driver.
 */
काष्ठा tc_driver अणु
	काष्ठा list_head node;
	स्थिर काष्ठा tc_device_id *id_table;
	काष्ठा device_driver driver;
पूर्ण;

#घोषणा to_tc_driver(drv) container_of(drv, काष्ठा tc_driver, driver)

/*
 * Return TURBOchannel घड़ी frequency in Hz.
 */
अटल अंतरभूत अचिन्हित दीर्घ tc_get_speed(काष्ठा tc_bus *tbus)
अणु
	वापस 100000 * (10000 / (अचिन्हित दीर्घ)tbus->info.clk_period);
पूर्ण

#अगर_घोषित CONFIG_TC

बाह्य काष्ठा bus_type tc_bus_type;

बाह्य पूर्णांक tc_रेजिस्टर_driver(काष्ठा tc_driver *tdrv);
बाह्य व्योम tc_unरेजिस्टर_driver(काष्ठा tc_driver *tdrv);

#अन्यथा /* !CONFIG_TC */

अटल अंतरभूत पूर्णांक tc_रेजिस्टर_driver(काष्ठा tc_driver *tdrv) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम tc_unरेजिस्टर_driver(काष्ठा tc_driver *tdrv) अणु पूर्ण

#पूर्ण_अगर /* CONFIG_TC */

/*
 * These have to be provided by the architecture.
 */
बाह्य पूर्णांक tc_pपढ़ोb(u8 *valp, व्योम __iomem *addr);
बाह्य पूर्णांक tc_bus_get_info(काष्ठा tc_bus *tbus);
बाह्य व्योम tc_device_get_irq(काष्ठा tc_dev *tdev);

#पूर्ण_अगर /* _LINUX_TC_H */
