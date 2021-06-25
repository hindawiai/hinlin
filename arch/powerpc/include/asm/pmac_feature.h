<शैली गुरु>
/*
 * Definition of platक्रमm feature hooks क्रम PowerMacs
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1998 Paul Mackerras &
 *                    Ben. Herrenschmidt.
 *
 *
 * Note: I हटाओd media-bay details from the feature stuff, I believe it's
 *       not worth it, the media-bay driver can directly use the mac-io
 *       ASIC रेजिस्टरs.
 *
 * Implementation note: Currently, none of these functions will block.
 * However, they may पूर्णांकernally protect themselves with a spinlock
 * क्रम way too दीर्घ. Be prepared क्रम at least some of these to block
 * in the future.
 *
 * Unless specअगरically defined, the result code is assumed to be an
 * error when negative, 0 is the शेष success result. Some functions
 * may वापस additional positive result values.
 *
 * To keep implementation simple, all feature calls are assumed to have
 * the prototype parameters (काष्ठा device_node* node, पूर्णांक value).
 * When either is not used, pass 0.
 */

#अगर_घोषित __KERNEL__
#अगर_अघोषित __ASM_POWERPC_PMAC_FEATURE_H
#घोषणा __ASM_POWERPC_PMAC_FEATURE_H

#समावेश <यंत्र/macपन.स>
#समावेश <यंत्र/machdep.h>

/*
 * Known Mac motherboard models
 *
 * Please, report any error here to benh@kernel.crashing.org, thanks !
 *
 * Note that I करोn't fully मुख्यtain this list क्रम Core99 & MacRISC2
 * and I'm considering removing all NewWorld entries from it and
 * entirely rely on the model string.
 */

/* PowerSurge are the first generation of PCI Pmacs. This include
 * all of the Gअक्रम-Central based machines. We currently करोn't
 * dअगरferentiate most of them.
 */
#घोषणा PMAC_TYPE_PSURGE		0x10	/* PowerSurge */
#घोषणा PMAC_TYPE_ANS			0x11	/* Apple Network Server */

/* Here is the infamous serie of OHare based machines
 */
#घोषणा PMAC_TYPE_COMET			0x20	/* Believed to be PowerBook 2400 */
#घोषणा PMAC_TYPE_HOOPER		0x21	/* Believed to be PowerBook 3400 */
#घोषणा PMAC_TYPE_KANGA			0x22	/* PowerBook 3500 (first G3) */
#घोषणा PMAC_TYPE_ALCHEMY		0x23	/* Alchemy motherboard base */
#घोषणा PMAC_TYPE_GAZELLE		0x24	/* Spartacus, some 5xxx/6xxx */
#घोषणा PMAC_TYPE_UNKNOWN_OHARE		0x2f	/* Unknown, but OHare based */

/* Here are the Heathrow based machines
 * FIXME: Dअगरferenciate wallstreet,मुख्यstreet,wallstreetII
 */
#घोषणा PMAC_TYPE_GOSSAMER		0x30	/* Gossamer motherboard */
#घोषणा PMAC_TYPE_SILK			0x31	/* Desktop PowerMac G3 */
#घोषणा PMAC_TYPE_WALLSTREET		0x32	/* Wallstreet/Mainstreet PowerBook*/
#घोषणा PMAC_TYPE_UNKNOWN_HEATHROW	0x3f	/* Unknown but heathrow based */

/* Here are newworld machines based on Paddington (heathrow derivative)
 */
#घोषणा PMAC_TYPE_101_PBOOK		0x40	/* 101 PowerBook (aka Lombard) */
#घोषणा PMAC_TYPE_ORIG_IMAC		0x41	/* First generation iMac */
#घोषणा PMAC_TYPE_YOSEMITE		0x42	/* B&W G3 */
#घोषणा PMAC_TYPE_YIKES			0x43	/* Yikes G4 (PCI graphics) */
#घोषणा PMAC_TYPE_UNKNOWN_PADDINGTON	0x4f	/* Unknown but paddington based */

/* Core99 machines based on UniNorth 1.0 and 1.5
 *
 * Note: A single entry here may cover several actual models according
 * to the device-tree. (Sawtooth is most tower G4s, FW_IMAC is most
 * FireWire based iMacs, etc...). Those machines are too similar to be
 * distinguished here, when they need to be dअगरferencied, use the
 * device-tree "model" or "compatible" property.
 */
#घोषणा PMAC_TYPE_ORIG_IBOOK		0x40	/* First iBook model (no firewire) */
#घोषणा PMAC_TYPE_SAWTOOTH		0x41	/* Desktop G4s */
#घोषणा PMAC_TYPE_FW_IMAC		0x42	/* FireWire iMacs (except Pangea based) */
#घोषणा PMAC_TYPE_FW_IBOOK		0x43	/* FireWire iBooks (except iBook2) */
#घोषणा PMAC_TYPE_CUBE			0x44	/* Cube PowerMac */
#घोषणा PMAC_TYPE_QUICKSILVER		0x45	/* QuickSilver G4s */
#घोषणा PMAC_TYPE_PISMO			0x46	/* Pismo PowerBook */
#घोषणा PMAC_TYPE_TITANIUM		0x47	/* Titanium PowerBook */
#घोषणा PMAC_TYPE_TITANIUM2		0x48	/* Titanium II PowerBook (no L3, M6) */
#घोषणा PMAC_TYPE_TITANIUM3		0x49	/* Titanium III PowerBook (with L3 & M7) */
#घोषणा PMAC_TYPE_TITANIUM4		0x50	/* Titanium IV PowerBook (with L3 & M9) */
#घोषणा PMAC_TYPE_EMAC			0x50	/* eMac */
#घोषणा PMAC_TYPE_UNKNOWN_CORE99	0x5f

/* MacRisc2 with UniNorth 2.0 */
#घोषणा PMAC_TYPE_RACKMAC		0x80	/* XServe */
#घोषणा PMAC_TYPE_WINDTUNNEL		0x81

/* MacRISC2 machines based on the Pangea chipset
 */
#घोषणा PMAC_TYPE_PANGEA_IMAC		0x100	/* Flower Power iMac */
#घोषणा PMAC_TYPE_IBOOK2		0x101	/* iBook2 (polycarbonate) */
#घोषणा PMAC_TYPE_FLAT_PANEL_IMAC	0x102	/* Flat panel iMac */
#घोषणा PMAC_TYPE_UNKNOWN_PANGEA	0x10f

/* MacRISC2 machines based on the Intrepid chipset
 */
#घोषणा PMAC_TYPE_UNKNOWN_INTREPID	0x11f	/* Generic */

/* MacRISC4 / G5 machines. We करोn't have per-machine selection here anymore,
 * but rather machine families
 */
#घोषणा PMAC_TYPE_POWERMAC_G5		0x150	/* U3 & U3H based */
#घोषणा PMAC_TYPE_POWERMAC_G5_U3L	0x151	/* U3L based desktop */
#घोषणा PMAC_TYPE_IMAC_G5		0x152	/* iMac G5 */
#घोषणा PMAC_TYPE_XSERVE_G5		0x153	/* Xserve G5 */
#घोषणा PMAC_TYPE_UNKNOWN_K2		0x19f	/* Any other K2 based */
#घोषणा PMAC_TYPE_UNKNOWN_SHASTA       	0x19e	/* Any other Shasta based */

/*
 * Motherboard flags
 */

#घोषणा PMAC_MB_CAN_SLEEP		0x00000001
#घोषणा PMAC_MB_HAS_FW_POWER		0x00000002
#घोषणा PMAC_MB_OLD_CORE99		0x00000004
#घोषणा PMAC_MB_MOBILE			0x00000008
#घोषणा PMAC_MB_MAY_SLEEP		0x00000010

/*
 * Feature calls supported on pmac
 *
 */

/*
 * Use this अंतरभूत wrapper
 */
काष्ठा device_node;

अटल अंतरभूत दीर्घ pmac_call_feature(पूर्णांक selector, काष्ठा device_node* node,
					दीर्घ param, दीर्घ value)
अणु
	अगर (!ppc_md.feature_call || !machine_is(घातermac))
		वापस -ENODEV;
	वापस ppc_md.feature_call(selector, node, param, value);
पूर्ण

/* PMAC_FTR_SERIAL_ENABLE	(काष्ठा device_node* node, पूर्णांक param, पूर्णांक value)
 * enable/disable an SCC side. Pass the node corresponding to the
 * channel side as a parameter.
 * param is the type of port
 * अगर param is ored with PMAC_SCC_FLAG_XMON, then the SCC is locked enabled
 * क्रम use by xmon.
 */
#घोषणा PMAC_FTR_SCC_ENABLE		PMAC_FTR_DEF(0)
	#घोषणा PMAC_SCC_ASYNC		0
	#घोषणा PMAC_SCC_IRDA		1
	#घोषणा PMAC_SCC_I2S1		2
	#घोषणा PMAC_SCC_FLAG_XMON	0x00001000

/* PMAC_FTR_MODEM_ENABLE	(काष्ठा device_node* node, 0, पूर्णांक value)
 * enable/disable the पूर्णांकernal modem.
 */
#घोषणा PMAC_FTR_MODEM_ENABLE		PMAC_FTR_DEF(1)

/* PMAC_FTR_SWIM3_ENABLE	(काष्ठा device_node* node, 0,पूर्णांक value)
 * enable/disable the swim3 (floppy) cell of a mac-io ASIC
 */
#घोषणा PMAC_FTR_SWIM3_ENABLE		PMAC_FTR_DEF(2)

/* PMAC_FTR_MESH_ENABLE		(काष्ठा device_node* node, 0, पूर्णांक value)
 * enable/disable the mesh (scsi) cell of a mac-io ASIC
 */
#घोषणा PMAC_FTR_MESH_ENABLE		PMAC_FTR_DEF(3)

/* PMAC_FTR_IDE_ENABLE		(काष्ठा device_node* node, पूर्णांक busID, पूर्णांक value)
 * enable/disable an IDE port of a mac-io ASIC
 * pass the busID parameter
 */
#घोषणा PMAC_FTR_IDE_ENABLE		PMAC_FTR_DEF(4)

/* PMAC_FTR_IDE_RESET		(काष्ठा device_node* node, पूर्णांक busID, पूर्णांक value)
 * निश्चित(1)/release(0) an IDE reset line (mac-io IDE only)
 */
#घोषणा PMAC_FTR_IDE_RESET		PMAC_FTR_DEF(5)

/* PMAC_FTR_BMAC_ENABLE		(काष्ठा device_node* node, 0, पूर्णांक value)
 * enable/disable the bmac (ethernet) cell of a mac-io ASIC, also drive
 * it's reset line
 */
#घोषणा PMAC_FTR_BMAC_ENABLE		PMAC_FTR_DEF(6)

/* PMAC_FTR_GMAC_ENABLE		(काष्ठा device_node* node, 0, पूर्णांक value)
 * enable/disable the gmac (ethernet) cell of an uninorth ASIC. This
 * control the cell's घड़ी.
 */
#घोषणा PMAC_FTR_GMAC_ENABLE		PMAC_FTR_DEF(7)

/* PMAC_FTR_GMAC_PHY_RESET	(काष्ठा device_node* node, 0, 0)
 * Perक्रमm a HW reset of the PHY connected to a gmac controller.
 * Pass the gmac device node, not the PHY node.
 */
#घोषणा PMAC_FTR_GMAC_PHY_RESET		PMAC_FTR_DEF(8)

/* PMAC_FTR_SOUND_CHIP_ENABLE	(काष्ठा device_node* node, 0, पूर्णांक value)
 * enable/disable the sound chip, whatever it is and provided it can
 * actually be controlled
 */
#घोषणा PMAC_FTR_SOUND_CHIP_ENABLE	PMAC_FTR_DEF(9)

/* -- add various tweaks related to sound routing -- */

/* PMAC_FTR_AIRPORT_ENABLE	(काष्ठा device_node* node, 0, पूर्णांक value)
 * enable/disable the airport card
 */
#घोषणा PMAC_FTR_AIRPORT_ENABLE		PMAC_FTR_DEF(10)

/* PMAC_FTR_RESET_CPU		(शून्य, पूर्णांक cpu_nr, 0)
 * toggle the reset line of a CPU on an uninorth-based SMP machine
 */
#घोषणा PMAC_FTR_RESET_CPU		PMAC_FTR_DEF(11)

/* PMAC_FTR_USB_ENABLE		(काष्ठा device_node* node, 0, पूर्णांक value)
 * enable/disable an USB cell, aदीर्घ with the घातer of the USB "pad"
 * on keylargo based machines
 */
#घोषणा PMAC_FTR_USB_ENABLE		PMAC_FTR_DEF(12)

/* PMAC_FTR_1394_ENABLE		(काष्ठा device_node* node, 0, पूर्णांक value)
 * enable/disable the firewire cell of an uninorth ASIC.
 */
#घोषणा PMAC_FTR_1394_ENABLE		PMAC_FTR_DEF(13)

/* PMAC_FTR_1394_CABLE_POWER	(काष्ठा device_node* node, 0, पूर्णांक value)
 * enable/disable the firewire cable घातer supply of the uninorth
 * firewire cell
 */
#घोषणा PMAC_FTR_1394_CABLE_POWER	PMAC_FTR_DEF(14)

/* PMAC_FTR_SLEEP_STATE		(काष्ठा device_node* node, 0, पूर्णांक value)
 * set the sleep state of the motherboard.
 *
 * Pass -1 as value to query क्रम sleep capability
 * Pass 1 to set IOs to sleep
 * Pass 0 to set IOs to wake
 */
#घोषणा PMAC_FTR_SLEEP_STATE		PMAC_FTR_DEF(15)

/* PMAC_FTR_GET_MB_INFO		(शून्य, selector, 0)
 *
 * वापसs some motherboard infos.
 * selector: 0  - model id
 *           1  - model flags (capabilities)
 *           2  - model name (cast to स्थिर अक्षर *)
 */
#घोषणा PMAC_FTR_GET_MB_INFO		PMAC_FTR_DEF(16)
#घोषणा   PMAC_MB_INFO_MODEL	0
#घोषणा   PMAC_MB_INFO_FLAGS	1
#घोषणा   PMAC_MB_INFO_NAME	2

/* PMAC_FTR_READ_GPIO		(शून्य, पूर्णांक index, 0)
 *
 * पढ़ो a GPIO from a mac-io controller of type KeyLargo or Pangea.
 * the value वापसed is a byte (positive), or a negative error code
 */
#घोषणा PMAC_FTR_READ_GPIO		PMAC_FTR_DEF(17)

/* PMAC_FTR_WRITE_GPIO		(शून्य, पूर्णांक index, पूर्णांक value)
 *
 * ग_लिखो a GPIO of a mac-io controller of type KeyLargo or Pangea.
 */
#घोषणा PMAC_FTR_WRITE_GPIO		PMAC_FTR_DEF(18)

/* PMAC_FTR_ENABLE_MPIC
 *
 * Enable the MPIC cell
 */
#घोषणा PMAC_FTR_ENABLE_MPIC		PMAC_FTR_DEF(19)

/* PMAC_FTR_AACK_DELAY_ENABLE	(शून्य, पूर्णांक enable, 0)
 *
 * Enable/disable the AACK delay on the northbridge क्रम प्रणालीs using DFS
 */
#घोषणा PMAC_FTR_AACK_DELAY_ENABLE     	PMAC_FTR_DEF(20)

/* PMAC_FTR_DEVICE_CAN_WAKE
 *
 * Used by video drivers to inक्रमm प्रणाली that they can actually perक्रमm
 * wakeup from sleep
 */
#घोषणा PMAC_FTR_DEVICE_CAN_WAKE	PMAC_FTR_DEF(22)


/* Don't use those directly, they are क्रम the sake of pmac_setup.c */
बाह्य दीर्घ pmac_करो_feature_call(अचिन्हित पूर्णांक selector, ...);
बाह्य व्योम pmac_feature_init(व्योम);

/* Video suspend tweak */
बाह्य व्योम pmac_set_early_video_resume(व्योम (*proc)(व्योम *data), व्योम *data);
बाह्य व्योम pmac_call_early_video_resume(व्योम);

#घोषणा PMAC_FTR_DEF(x) ((0x6660000) | (x))

/* The AGP driver रेजिस्टरs itself here */
बाह्य व्योम pmac_रेजिस्टर_agp_pm(काष्ठा pci_dev *bridge,
				 पूर्णांक (*suspend)(काष्ठा pci_dev *bridge),
				 पूर्णांक (*resume)(काष्ठा pci_dev *bridge));

/* Those are meant to be used by video drivers to deal with AGP
 * suspend resume properly
 */
बाह्य व्योम pmac_suspend_agp_क्रम_card(काष्ठा pci_dev *dev);
बाह्य व्योम pmac_resume_agp_क्रम_card(काष्ठा pci_dev *dev);

/*
 * The part below is क्रम use by macio_asic.c only, करो not rely
 * on the data काष्ठाures or स्थिरants below in a normal driver
 *
 */

#घोषणा MAX_MACIO_CHIPS		2

क्रमागत अणु
	macio_unknown = 0,
	macio_gअक्रम_central,
	macio_ohare,
	macio_ohareII,
	macio_heathrow,
	macio_gatwick,
	macio_paddington,
	macio_keylargo,
	macio_pangea,
	macio_पूर्णांकrepid,
	macio_keylargo2,
	macio_shasta,
पूर्ण;

काष्ठा macio_chip
अणु
	काष्ठा device_node	*of_node;
	पूर्णांक			type;
	स्थिर अक्षर		*name;
	पूर्णांक			rev;
	अस्थिर u32		__iomem *base;
	अचिन्हित दीर्घ		flags;

	/* For use by macio_asic PCI driver */
	काष्ठा macio_bus	lbus;
पूर्ण;

बाह्य काष्ठा macio_chip macio_chips[MAX_MACIO_CHIPS];

#घोषणा MACIO_FLAG_SCCA_ON	0x00000001
#घोषणा MACIO_FLAG_SCCB_ON	0x00000002
#घोषणा MACIO_FLAG_SCC_LOCKED	0x00000004
#घोषणा MACIO_FLAG_AIRPORT_ON	0x00000010
#घोषणा MACIO_FLAG_FW_SUPPORTED	0x00000020

बाह्य काष्ठा macio_chip* macio_find(काष्ठा device_node* child, पूर्णांक type);

#घोषणा MACIO_FCR32(macio, r)	((macio)->base + ((r) >> 2))
#घोषणा MACIO_FCR8(macio, r)	(((अस्थिर u8 __iomem *)((macio)->base)) + (r))

#घोषणा MACIO_IN32(r)		(in_le32(MACIO_FCR32(macio,r)))
#घोषणा MACIO_OUT32(r,v)	(out_le32(MACIO_FCR32(macio,r), (v)))
#घोषणा MACIO_BIS(r,v)		(MACIO_OUT32((r), MACIO_IN32(r) | (v)))
#घोषणा MACIO_BIC(r,v)		(MACIO_OUT32((r), MACIO_IN32(r) & ~(v)))
#घोषणा MACIO_IN8(r)		(in_8(MACIO_FCR8(macio,r)))
#घोषणा MACIO_OUT8(r,v)		(out_8(MACIO_FCR8(macio,r), (v)))

/*
 * Those are exported by pmac feature क्रम पूर्णांकernal use by arch code
 * only like the platक्रमm function callbacks, करो not use directly in drivers
 */
बाह्य raw_spinlock_t feature_lock;
बाह्य काष्ठा device_node *uninorth_node;
बाह्य u32 __iomem *uninorth_base;

/*
 * Uninorth reg. access. Note that Uni-N regs are big endian
 */

#घोषणा UN_REG(r)	(uninorth_base + ((r) >> 2))
#घोषणा UN_IN(r)	(in_be32(UN_REG(r)))
#घोषणा UN_OUT(r,v)	(out_be32(UN_REG(r), (v)))
#घोषणा UN_BIS(r,v)	(UN_OUT((r), UN_IN(r) | (v)))
#घोषणा UN_BIC(r,v)	(UN_OUT((r), UN_IN(r) & ~(v)))

/* Uninorth variant:
 *
 * 0 = not uninorth
 * 1 = U1.x or U2.x
 * 3 = U3
 * 4 = U4
 */
बाह्य पूर्णांक pmac_get_uninorth_variant(व्योम);

#पूर्ण_अगर /* __ASM_POWERPC_PMAC_FEATURE_H */
#पूर्ण_अगर /* __KERNEL__ */
