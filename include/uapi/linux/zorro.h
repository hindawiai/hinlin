<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 *  linux/zorro.h -- Amiga AutoConfig (Zorro) Bus Definitions
 *
 *  Copyright (C) 1995--2003 Geert Uytterhoeven
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License.  See the file COPYING in the मुख्य directory of this archive
 *  क्रम more details.
 */

#अगर_अघोषित _UAPI_LINUX_ZORRO_H
#घोषणा _UAPI_LINUX_ZORRO_H

#समावेश <linux/types.h>


    /*
     *  Each Zorro board has a 32-bit ID of the क्रमm
     *
     *      mmmmmmmmmmmmmmmmppppppppeeeeeeee
     *
     *  with
     *
     *      mmmmmmmmmmmmmmmm	16-bit Manufacturer ID (asचिन्हित by CBM (sigh))
     *      pppppppp		8-bit Product ID (asचिन्हित by manufacturer)
     *      eeeeeeee		8-bit Extended Product ID (currently only used
     *				क्रम some GVP boards)
     */


#घोषणा ZORRO_MANUF(id)		((id) >> 16)
#घोषणा ZORRO_PROD(id)		(((id) >> 8) & 0xff)
#घोषणा ZORRO_EPC(id)		((id) & 0xff)

#घोषणा ZORRO_ID(manuf, prod, epc) \
	((ZORRO_MANUF_##manuf << 16) | ((prod) << 8) | (epc))

प्रकार __u32 zorro_id;


/* Include the ID list */
#समावेश <linux/zorro_ids.h>


    /*
     *  GVP identअगरies most of its products through the 'extended product code'
     *  (epc). The epc has to be ANDed with the GVP_PRODMASK beक्रमe the
     *  identअगरication.
     */

#घोषणा GVP_PRODMASK		(0xf8)
#घोषणा GVP_SCSICLKMASK		(0x01)

क्रमागत GVP_flags अणु
	GVP_IO			= 0x01,
	GVP_ACCEL		= 0x02,
	GVP_SCSI		= 0x04,
	GVP_24BITDMA		= 0x08,
	GVP_25BITDMA		= 0x10,
	GVP_NOBANK		= 0x20,
	GVP_14MHZ		= 0x40,
पूर्ण;


काष्ठा Node अणु
	__be32 ln_Succ;		/* Poपूर्णांकer to next (successor) */
	__be32 ln_Pred;		/* Poपूर्णांकer to previous (predecessor) */
	__u8   ln_Type;
	__s8   ln_Pri;		/* Priority, क्रम sorting */
	__be32 ln_Name;		/* ID string, null terminated */
पूर्ण __packed;

काष्ठा ExpansionRom अणु
	/* -First 16 bytes of the expansion ROM */
	__u8   er_Type;		/* Board type, size and flags */
	__u8   er_Product;	/* Product number, asचिन्हित by manufacturer */
	__u8   er_Flags;		/* Flags */
	__u8   er_Reserved03;	/* Must be zero ($ff inverted) */
	__be16 er_Manufacturer;	/* Unique ID, ASSIGNED BY COMMODORE-AMIGA! */
	__be32 er_SerialNumber;	/* Available क्रम use by manufacturer */
	__be16 er_InitDiagVec;	/* Offset to optional "DiagArea" काष्ठाure */
	__u8   er_Reserved0c;
	__u8   er_Reserved0d;
	__u8   er_Reserved0e;
	__u8   er_Reserved0f;
पूर्ण __packed;

/* er_Type board type bits */
#घोषणा ERT_TYPEMASK	0xc0
#घोषणा ERT_ZORROII	0xc0
#घोषणा ERT_ZORROIII	0x80

/* other bits defined in er_Type */
#घोषणा ERTB_MEMLIST	5		/* Link RAM पूर्णांकo मुक्त memory list */
#घोषणा ERTF_MEMLIST	(1<<5)

काष्ठा ConfigDev अणु
	काष्ठा Node	cd_Node;
	__u8		cd_Flags;	/* (पढ़ो/ग_लिखो) */
	__u8		cd_Pad;		/* reserved */
	काष्ठा ExpansionRom cd_Rom;	/* copy of board's expansion ROM */
	__be32		cd_BoardAddr;	/* where in memory the board was placed */
	__be32		cd_BoardSize;	/* size of board in bytes */
	__be16		cd_SlotAddr;	/* which slot number (PRIVATE) */
	__be16		cd_SlotSize;	/* number of slots (PRIVATE) */
	__be32		cd_Driver;	/* poपूर्णांकer to node of driver */
	__be32		cd_NextCD;	/* linked list of drivers to config */
	__be32		cd_Unused[4];	/* क्रम whatever the driver wants */
पूर्ण __packed;

#घोषणा ZORRO_NUM_AUTO		16

#पूर्ण_अगर /* _UAPI_LINUX_ZORRO_H */
