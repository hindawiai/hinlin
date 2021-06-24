<शैली गुरु>
/*
 * Product specअगरic probe and attach routines क्रम:
 *      3940, 2940, aic7895, aic7890, aic7880,
 *	aic7870, aic7860 and aic7850 SCSI controllers
 *
 * Copyright (c) 1994-2001 Justin T. Gibbs.
 * Copyright (c) 2000-2001 Adaptec Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modअगरication.
 * 2. Redistributions in binary क्रमm must reproduce at minimum a disclaimer
 *    substantially similar to the "NO WARRANTY" disclaimer below
 *    ("Disclaimer") and any redistribution must be conditioned upon
 *    including a substantially similar Disclaimer requirement क्रम further
 *    binary redistribution.
 * 3. Neither the names of the above-listed copyright holders nor the names
 *    of any contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * NO WARRANTY
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES.
 *
 * $Id: //depot/aic7xxx/aic7xxx/aic7xxx_pci.c#79 $
 */

#समावेश "aic7xxx_osm.h"
#समावेश "aic7xxx_inline.h"
#समावेश "aic7xxx_93cx6.h"
#समावेश "aic7xxx_pci.h"

अटल अंतरभूत uपूर्णांक64_t
ahc_compose_id(u_पूर्णांक device, u_पूर्णांक venकरोr, u_पूर्णांक subdevice, u_पूर्णांक subvenकरोr)
अणु
	uपूर्णांक64_t id;

	id = subvenकरोr
	   | (subdevice << 16)
	   | ((uपूर्णांक64_t)venकरोr << 32)
	   | ((uपूर्णांक64_t)device << 48);

	वापस (id);
पूर्ण

#घोषणा AHC_PCI_IOADDR	PCIR_MAPS	/* I/O Address */
#घोषणा AHC_PCI_MEMADDR	(PCIR_MAPS + 4)	/* Mem I/O Address */

#घोषणा DEVID_9005_TYPE(id) ((id) & 0xF)
#घोषणा		DEVID_9005_TYPE_HBA		0x0	/* Standard Card */
#घोषणा		DEVID_9005_TYPE_AAA		0x3	/* RAID Card */
#घोषणा		DEVID_9005_TYPE_SISL		0x5	/* Container ROMB */
#घोषणा		DEVID_9005_TYPE_MB		0xF	/* On Motherboard */

#घोषणा DEVID_9005_MAXRATE(id) (((id) & 0x30) >> 4)
#घोषणा		DEVID_9005_MAXRATE_U160		0x0
#घोषणा		DEVID_9005_MAXRATE_ULTRA2	0x1
#घोषणा		DEVID_9005_MAXRATE_ULTRA	0x2
#घोषणा		DEVID_9005_MAXRATE_FAST		0x3

#घोषणा DEVID_9005_MFUNC(id) (((id) & 0x40) >> 6)

#घोषणा DEVID_9005_CLASS(id) (((id) & 0xFF00) >> 8)
#घोषणा		DEVID_9005_CLASS_SPI		0x0	/* Parallel SCSI */

#घोषणा SUBID_9005_TYPE(id) ((id) & 0xF)
#घोषणा		SUBID_9005_TYPE_MB		0xF	/* On Motherboard */
#घोषणा		SUBID_9005_TYPE_CARD		0x0	/* Standard Card */
#घोषणा		SUBID_9005_TYPE_LCCARD		0x1	/* Low Cost Card */
#घोषणा		SUBID_9005_TYPE_RAID		0x3	/* Combined with Raid */

#घोषणा SUBID_9005_TYPE_KNOWN(id)			\
	  ((((id) & 0xF) == SUBID_9005_TYPE_MB)		\
	|| (((id) & 0xF) == SUBID_9005_TYPE_CARD)	\
	|| (((id) & 0xF) == SUBID_9005_TYPE_LCCARD)	\
	|| (((id) & 0xF) == SUBID_9005_TYPE_RAID))

#घोषणा SUBID_9005_MAXRATE(id) (((id) & 0x30) >> 4)
#घोषणा		SUBID_9005_MAXRATE_ULTRA2	0x0
#घोषणा		SUBID_9005_MAXRATE_ULTRA	0x1
#घोषणा		SUBID_9005_MAXRATE_U160		0x2
#घोषणा		SUBID_9005_MAXRATE_RESERVED	0x3

#घोषणा SUBID_9005_SEEPTYPE(id)						\
	((SUBID_9005_TYPE(id) == SUBID_9005_TYPE_MB)			\
	 ? ((id) & 0xC0) >> 6						\
	 : ((id) & 0x300) >> 8)
#घोषणा		SUBID_9005_SEEPTYPE_NONE	0x0
#घोषणा		SUBID_9005_SEEPTYPE_1K		0x1
#घोषणा		SUBID_9005_SEEPTYPE_2K_4K	0x2
#घोषणा		SUBID_9005_SEEPTYPE_RESERVED	0x3
#घोषणा SUBID_9005_AUTOTERM(id)						\
	((SUBID_9005_TYPE(id) == SUBID_9005_TYPE_MB)			\
	 ? (((id) & 0x400) >> 10) == 0					\
	 : (((id) & 0x40) >> 6) == 0)

#घोषणा SUBID_9005_NUMCHAN(id)						\
	((SUBID_9005_TYPE(id) == SUBID_9005_TYPE_MB)			\
	 ? ((id) & 0x300) >> 8						\
	 : ((id) & 0xC00) >> 10)

#घोषणा SUBID_9005_LEGACYCONN(id)					\
	((SUBID_9005_TYPE(id) == SUBID_9005_TYPE_MB)			\
	 ? 0								\
	 : ((id) & 0x80) >> 7)

#घोषणा SUBID_9005_MFUNCENB(id)						\
	((SUBID_9005_TYPE(id) == SUBID_9005_TYPE_MB)			\
	 ? ((id) & 0x800) >> 11						\
	 : ((id) & 0x1000) >> 12)
/*
 * Inक्रमmational only. Should use chip रेजिस्टर to be
 * certain, but may be use in identअगरication strings.
 */
#घोषणा SUBID_9005_CARD_SCSIWIDTH_MASK	0x2000
#घोषणा SUBID_9005_CARD_PCIWIDTH_MASK	0x4000
#घोषणा SUBID_9005_CARD_SEDIFF_MASK	0x8000

अटल ahc_device_setup_t ahc_aic785X_setup;
अटल ahc_device_setup_t ahc_aic7860_setup;
अटल ahc_device_setup_t ahc_apa1480_setup;
अटल ahc_device_setup_t ahc_aic7870_setup;
अटल ahc_device_setup_t ahc_aic7870h_setup;
अटल ahc_device_setup_t ahc_aha394X_setup;
अटल ahc_device_setup_t ahc_aha394Xh_setup;
अटल ahc_device_setup_t ahc_aha494X_setup;
अटल ahc_device_setup_t ahc_aha494Xh_setup;
अटल ahc_device_setup_t ahc_aha398X_setup;
अटल ahc_device_setup_t ahc_aic7880_setup;
अटल ahc_device_setup_t ahc_aic7880h_setup;
अटल ahc_device_setup_t ahc_aha2940Pro_setup;
अटल ahc_device_setup_t ahc_aha394XU_setup;
अटल ahc_device_setup_t ahc_aha394XUh_setup;
अटल ahc_device_setup_t ahc_aha398XU_setup;
अटल ahc_device_setup_t ahc_aic7890_setup;
अटल ahc_device_setup_t ahc_aic7892_setup;
अटल ahc_device_setup_t ahc_aic7895_setup;
अटल ahc_device_setup_t ahc_aic7895h_setup;
अटल ahc_device_setup_t ahc_aic7896_setup;
अटल ahc_device_setup_t ahc_aic7899_setup;
अटल ahc_device_setup_t ahc_aha29160C_setup;
अटल ahc_device_setup_t ahc_raid_setup;
अटल ahc_device_setup_t ahc_aha394XX_setup;
अटल ahc_device_setup_t ahc_aha494XX_setup;
अटल ahc_device_setup_t ahc_aha398XX_setup;

अटल स्थिर काष्ठा ahc_pci_identity ahc_pci_ident_table[] = अणु
	/* aic7850 based controllers */
	अणु
		ID_AHA_2902_04_10_15_20C_30C,
		ID_ALL_MASK,
		"Adaptec 2902/04/10/15/20C/30C SCSI adapter",
		ahc_aic785X_setup
	पूर्ण,
	/* aic7860 based controllers */
	अणु
		ID_AHA_2930CU,
		ID_ALL_MASK,
		"Adaptec 2930CU SCSI adapter",
		ahc_aic7860_setup
	पूर्ण,
	अणु
		ID_AHA_1480A & ID_DEV_VENDOR_MASK,
		ID_DEV_VENDOR_MASK,
		"Adaptec 1480A Ultra SCSI adapter",
		ahc_apa1480_setup
	पूर्ण,
	अणु
		ID_AHA_2940AU_0 & ID_DEV_VENDOR_MASK,
		ID_DEV_VENDOR_MASK,
		"Adaptec 2940A Ultra SCSI adapter",
		ahc_aic7860_setup
	पूर्ण,
	अणु
		ID_AHA_2940AU_CN & ID_DEV_VENDOR_MASK,
		ID_DEV_VENDOR_MASK,
		"Adaptec 2940A/CN Ultra SCSI adapter",
		ahc_aic7860_setup
	पूर्ण,
	अणु
		ID_AHA_2930C_VAR & ID_DEV_VENDOR_MASK,
		ID_DEV_VENDOR_MASK,
		"Adaptec 2930C Ultra SCSI adapter (VAR)",
		ahc_aic7860_setup
	पूर्ण,
	/* aic7870 based controllers */
	अणु
		ID_AHA_2940,
		ID_ALL_MASK,
		"Adaptec 2940 SCSI adapter",
		ahc_aic7870_setup
	पूर्ण,
	अणु
		ID_AHA_3940,
		ID_ALL_MASK,
		"Adaptec 3940 SCSI adapter",
		ahc_aha394X_setup
	पूर्ण,
	अणु
		ID_AHA_398X,
		ID_ALL_MASK,
		"Adaptec 398X SCSI RAID adapter",
		ahc_aha398X_setup
	पूर्ण,
	अणु
		ID_AHA_2944,
		ID_ALL_MASK,
		"Adaptec 2944 SCSI adapter",
		ahc_aic7870h_setup
	पूर्ण,
	अणु
		ID_AHA_3944,
		ID_ALL_MASK,
		"Adaptec 3944 SCSI adapter",
		ahc_aha394Xh_setup
	पूर्ण,
	अणु
		ID_AHA_4944,
		ID_ALL_MASK,
		"Adaptec 4944 SCSI adapter",
		ahc_aha494Xh_setup
	पूर्ण,
	/* aic7880 based controllers */
	अणु
		ID_AHA_2940U & ID_DEV_VENDOR_MASK,
		ID_DEV_VENDOR_MASK,
		"Adaptec 2940 Ultra SCSI adapter",
		ahc_aic7880_setup
	पूर्ण,
	अणु
		ID_AHA_3940U & ID_DEV_VENDOR_MASK,
		ID_DEV_VENDOR_MASK,
		"Adaptec 3940 Ultra SCSI adapter",
		ahc_aha394XU_setup
	पूर्ण,
	अणु
		ID_AHA_2944U & ID_DEV_VENDOR_MASK,
		ID_DEV_VENDOR_MASK,
		"Adaptec 2944 Ultra SCSI adapter",
		ahc_aic7880h_setup
	पूर्ण,
	अणु
		ID_AHA_3944U & ID_DEV_VENDOR_MASK,
		ID_DEV_VENDOR_MASK,
		"Adaptec 3944 Ultra SCSI adapter",
		ahc_aha394XUh_setup
	पूर्ण,
	अणु
		ID_AHA_398XU & ID_DEV_VENDOR_MASK,
		ID_DEV_VENDOR_MASK,
		"Adaptec 398X Ultra SCSI RAID adapter",
		ahc_aha398XU_setup
	पूर्ण,
	अणु
		/*
		 * XXX Don't know the slot numbers
		 * so we can't identअगरy channels
		 */
		ID_AHA_4944U & ID_DEV_VENDOR_MASK,
		ID_DEV_VENDOR_MASK,
		"Adaptec 4944 Ultra SCSI adapter",
		ahc_aic7880h_setup
	पूर्ण,
	अणु
		ID_AHA_2930U & ID_DEV_VENDOR_MASK,
		ID_DEV_VENDOR_MASK,
		"Adaptec 2930 Ultra SCSI adapter",
		ahc_aic7880_setup
	पूर्ण,
	अणु
		ID_AHA_2940U_PRO & ID_DEV_VENDOR_MASK,
		ID_DEV_VENDOR_MASK,
		"Adaptec 2940 Pro Ultra SCSI adapter",
		ahc_aha2940Pro_setup
	पूर्ण,
	अणु
		ID_AHA_2940U_CN & ID_DEV_VENDOR_MASK,
		ID_DEV_VENDOR_MASK,
		"Adaptec 2940/CN Ultra SCSI adapter",
		ahc_aic7880_setup
	पूर्ण,
	/* Ignore all SISL (AAC on MB) based controllers. */
	अणु
		ID_9005_SISL_ID,
		ID_9005_SISL_MASK,
		शून्य,
		शून्य
	पूर्ण,
	/* aic7890 based controllers */
	अणु
		ID_AHA_2930U2,
		ID_ALL_MASK,
		"Adaptec 2930 Ultra2 SCSI adapter",
		ahc_aic7890_setup
	पूर्ण,
	अणु
		ID_AHA_2940U2B,
		ID_ALL_MASK,
		"Adaptec 2940B Ultra2 SCSI adapter",
		ahc_aic7890_setup
	पूर्ण,
	अणु
		ID_AHA_2940U2_OEM,
		ID_ALL_MASK,
		"Adaptec 2940 Ultra2 SCSI adapter (OEM)",
		ahc_aic7890_setup
	पूर्ण,
	अणु
		ID_AHA_2940U2,
		ID_ALL_MASK,
		"Adaptec 2940 Ultra2 SCSI adapter",
		ahc_aic7890_setup
	पूर्ण,
	अणु
		ID_AHA_2950U2B,
		ID_ALL_MASK,
		"Adaptec 2950 Ultra2 SCSI adapter",
		ahc_aic7890_setup
	पूर्ण,
	अणु
		ID_AIC7890_ARO,
		ID_ALL_MASK,
		"Adaptec aic7890/91 Ultra2 SCSI adapter (ARO)",
		ahc_aic7890_setup
	पूर्ण,
	अणु
		ID_AAA_131U2,
		ID_ALL_MASK,
		"Adaptec AAA-131 Ultra2 RAID adapter",
		ahc_aic7890_setup
	पूर्ण,
	/* aic7892 based controllers */
	अणु
		ID_AHA_29160,
		ID_ALL_MASK,
		"Adaptec 29160 Ultra160 SCSI adapter",
		ahc_aic7892_setup
	पूर्ण,
	अणु
		ID_AHA_29160_CPQ,
		ID_ALL_MASK,
		"Adaptec (Compaq OEM) 29160 Ultra160 SCSI adapter",
		ahc_aic7892_setup
	पूर्ण,
	अणु
		ID_AHA_29160N,
		ID_ALL_MASK,
		"Adaptec 29160N Ultra160 SCSI adapter",
		ahc_aic7892_setup
	पूर्ण,
	अणु
		ID_AHA_29160C,
		ID_ALL_MASK,
		"Adaptec 29160C Ultra160 SCSI adapter",
		ahc_aha29160C_setup
	पूर्ण,
	अणु
		ID_AHA_29160B,
		ID_ALL_MASK,
		"Adaptec 29160B Ultra160 SCSI adapter",
		ahc_aic7892_setup
	पूर्ण,
	अणु
		ID_AHA_19160B,
		ID_ALL_MASK,
		"Adaptec 19160B Ultra160 SCSI adapter",
		ahc_aic7892_setup
	पूर्ण,
	अणु
		ID_AIC7892_ARO,
		ID_ALL_MASK,
		"Adaptec aic7892 Ultra160 SCSI adapter (ARO)",
		ahc_aic7892_setup
	पूर्ण,
	अणु
		ID_AHA_2915_30LP,
		ID_ALL_MASK,
		"Adaptec 2915/30LP Ultra160 SCSI adapter",
		ahc_aic7892_setup
	पूर्ण,
	/* aic7895 based controllers */	
	अणु
		ID_AHA_2940U_DUAL,
		ID_ALL_MASK,
		"Adaptec 2940/DUAL Ultra SCSI adapter",
		ahc_aic7895_setup
	पूर्ण,
	अणु
		ID_AHA_3940AU,
		ID_ALL_MASK,
		"Adaptec 3940A Ultra SCSI adapter",
		ahc_aic7895_setup
	पूर्ण,
	अणु
		ID_AHA_3944AU,
		ID_ALL_MASK,
		"Adaptec 3944A Ultra SCSI adapter",
		ahc_aic7895h_setup
	पूर्ण,
	अणु
		ID_AIC7895_ARO,
		ID_AIC7895_ARO_MASK,
		"Adaptec aic7895 Ultra SCSI adapter (ARO)",
		ahc_aic7895_setup
	पूर्ण,
	/* aic7896/97 based controllers */	
	अणु
		ID_AHA_3950U2B_0,
		ID_ALL_MASK,
		"Adaptec 3950B Ultra2 SCSI adapter",
		ahc_aic7896_setup
	पूर्ण,
	अणु
		ID_AHA_3950U2B_1,
		ID_ALL_MASK,
		"Adaptec 3950B Ultra2 SCSI adapter",
		ahc_aic7896_setup
	पूर्ण,
	अणु
		ID_AHA_3950U2D_0,
		ID_ALL_MASK,
		"Adaptec 3950D Ultra2 SCSI adapter",
		ahc_aic7896_setup
	पूर्ण,
	अणु
		ID_AHA_3950U2D_1,
		ID_ALL_MASK,
		"Adaptec 3950D Ultra2 SCSI adapter",
		ahc_aic7896_setup
	पूर्ण,
	अणु
		ID_AIC7896_ARO,
		ID_ALL_MASK,
		"Adaptec aic7896/97 Ultra2 SCSI adapter (ARO)",
		ahc_aic7896_setup
	पूर्ण,
	/* aic7899 based controllers */	
	अणु
		ID_AHA_3960D,
		ID_ALL_MASK,
		"Adaptec 3960D Ultra160 SCSI adapter",
		ahc_aic7899_setup
	पूर्ण,
	अणु
		ID_AHA_3960D_CPQ,
		ID_ALL_MASK,
		"Adaptec (Compaq OEM) 3960D Ultra160 SCSI adapter",
		ahc_aic7899_setup
	पूर्ण,
	अणु
		ID_AIC7899_ARO,
		ID_ALL_MASK,
		"Adaptec aic7899 Ultra160 SCSI adapter (ARO)",
		ahc_aic7899_setup
	पूर्ण,
	/* Generic chip probes क्रम devices we करोn't know 'exactly' */
	अणु
		ID_AIC7850 & ID_DEV_VENDOR_MASK,
		ID_DEV_VENDOR_MASK,
		"Adaptec aic7850 SCSI adapter",
		ahc_aic785X_setup
	पूर्ण,
	अणु
		ID_AIC7855 & ID_DEV_VENDOR_MASK,
		ID_DEV_VENDOR_MASK,
		"Adaptec aic7855 SCSI adapter",
		ahc_aic785X_setup
	पूर्ण,
	अणु
		ID_AIC7859 & ID_DEV_VENDOR_MASK,
		ID_DEV_VENDOR_MASK,
		"Adaptec aic7859 SCSI adapter",
		ahc_aic7860_setup
	पूर्ण,
	अणु
		ID_AIC7860 & ID_DEV_VENDOR_MASK,
		ID_DEV_VENDOR_MASK,
		"Adaptec aic7860 Ultra SCSI adapter",
		ahc_aic7860_setup
	पूर्ण,
	अणु
		ID_AIC7870 & ID_DEV_VENDOR_MASK,
		ID_DEV_VENDOR_MASK,
		"Adaptec aic7870 SCSI adapter",
		ahc_aic7870_setup
	पूर्ण,
	अणु
		ID_AIC7880 & ID_DEV_VENDOR_MASK,
		ID_DEV_VENDOR_MASK,
		"Adaptec aic7880 Ultra SCSI adapter",
		ahc_aic7880_setup
	पूर्ण,
	अणु
		ID_AIC7890 & ID_9005_GENERIC_MASK,
		ID_9005_GENERIC_MASK,
		"Adaptec aic7890/91 Ultra2 SCSI adapter",
		ahc_aic7890_setup
	पूर्ण,
	अणु
		ID_AIC7892 & ID_9005_GENERIC_MASK,
		ID_9005_GENERIC_MASK,
		"Adaptec aic7892 Ultra160 SCSI adapter",
		ahc_aic7892_setup
	पूर्ण,
	अणु
		ID_AIC7895 & ID_DEV_VENDOR_MASK,
		ID_DEV_VENDOR_MASK,
		"Adaptec aic7895 Ultra SCSI adapter",
		ahc_aic7895_setup
	पूर्ण,
	अणु
		ID_AIC7896 & ID_9005_GENERIC_MASK,
		ID_9005_GENERIC_MASK,
		"Adaptec aic7896/97 Ultra2 SCSI adapter",
		ahc_aic7896_setup
	पूर्ण,
	अणु
		ID_AIC7899 & ID_9005_GENERIC_MASK,
		ID_9005_GENERIC_MASK,
		"Adaptec aic7899 Ultra160 SCSI adapter",
		ahc_aic7899_setup
	पूर्ण,
	अणु
		ID_AIC7810 & ID_DEV_VENDOR_MASK,
		ID_DEV_VENDOR_MASK,
		"Adaptec aic7810 RAID memory controller",
		ahc_raid_setup
	पूर्ण,
	अणु
		ID_AIC7815 & ID_DEV_VENDOR_MASK,
		ID_DEV_VENDOR_MASK,
		"Adaptec aic7815 RAID memory controller",
		ahc_raid_setup
	पूर्ण
पूर्ण;

अटल स्थिर u_पूर्णांक ahc_num_pci_devs = ARRAY_SIZE(ahc_pci_ident_table);
		
#घोषणा AHC_394X_SLOT_CHANNEL_A	4
#घोषणा AHC_394X_SLOT_CHANNEL_B	5

#घोषणा AHC_398X_SLOT_CHANNEL_A	4
#घोषणा AHC_398X_SLOT_CHANNEL_B	8
#घोषणा AHC_398X_SLOT_CHANNEL_C	12

#घोषणा AHC_494X_SLOT_CHANNEL_A	4
#घोषणा AHC_494X_SLOT_CHANNEL_B	5
#घोषणा AHC_494X_SLOT_CHANNEL_C	6
#घोषणा AHC_494X_SLOT_CHANNEL_D	7

#घोषणा	DEVCONFIG		0x40
#घोषणा		PCIERRGENDIS	0x80000000ul
#घोषणा		SCBSIZE32	0x00010000ul	/* aic789X only */
#घोषणा		REXTVALID	0x00001000ul	/* ultra cards only */
#घोषणा		MPORTMODE	0x00000400ul	/* aic7870+ only */
#घोषणा		RAMPSM		0x00000200ul	/* aic7870+ only */
#घोषणा		VOLSENSE	0x00000100ul
#घोषणा		PCI64BIT	0x00000080ul	/* 64Bit PCI bus (Ultra2 Only)*/
#घोषणा		SCBRAMSEL	0x00000080ul
#घोषणा		MRDCEN		0x00000040ul
#घोषणा		EXTSCBTIME	0x00000020ul	/* aic7870 only */
#घोषणा		EXTSCBPEN	0x00000010ul	/* aic7870 only */
#घोषणा		BERREN		0x00000008ul
#घोषणा		DACEN		0x00000004ul
#घोषणा		STPWLEVEL	0x00000002ul
#घोषणा		DIFACTNEGEN	0x00000001ul	/* aic7870 only */

#घोषणा	CSIZE_LATTIME		0x0c
#घोषणा		CACHESIZE	0x0000003ful	/* only 5 bits */
#घोषणा		LATTIME		0x0000ff00ul

/* PCI STATUS definitions */
#घोषणा	DPE	0x80
#घोषणा SSE	0x40
#घोषणा	RMA	0x20
#घोषणा	RTA	0x10
#घोषणा STA	0x08
#घोषणा DPR	0x01

अटल पूर्णांक ahc_9005_subdevinfo_valid(uपूर्णांक16_t device, uपूर्णांक16_t venकरोr,
				     uपूर्णांक16_t subdevice, uपूर्णांक16_t subvenकरोr);
अटल पूर्णांक ahc_ext_scbram_present(काष्ठा ahc_softc *ahc);
अटल व्योम ahc_scbram_config(काष्ठा ahc_softc *ahc, पूर्णांक enable,
				  पूर्णांक pcheck, पूर्णांक fast, पूर्णांक large);
अटल व्योम ahc_probe_ext_scbram(काष्ठा ahc_softc *ahc);
अटल व्योम check_extport(काष्ठा ahc_softc *ahc, u_पूर्णांक *sxfrctl1);
अटल व्योम ahc_parse_pci_eeprom(काष्ठा ahc_softc *ahc,
				 काष्ठा seeprom_config *sc);
अटल व्योम configure_termination(काष्ठा ahc_softc *ahc,
				  काष्ठा seeprom_descriptor *sd,
				  u_पूर्णांक adapter_control,
	 			  u_पूर्णांक *sxfrctl1);

अटल व्योम ahc_new_term_detect(काष्ठा ahc_softc *ahc,
				पूर्णांक *enableSEC_low,
				पूर्णांक *enableSEC_high,
				पूर्णांक *enablePRI_low,
				पूर्णांक *enablePRI_high,
				पूर्णांक *eeprom_present);
अटल व्योम aic787X_cable_detect(काष्ठा ahc_softc *ahc, पूर्णांक *पूर्णांकernal50_present,
				 पूर्णांक *पूर्णांकernal68_present,
				 पूर्णांक *बाह्यalcable_present,
				 पूर्णांक *eeprom_present);
अटल व्योम aic785X_cable_detect(काष्ठा ahc_softc *ahc, पूर्णांक *पूर्णांकernal50_present,
				 पूर्णांक *बाह्यalcable_present,
				 पूर्णांक *eeprom_present);
अटल व्योम    ग_लिखो_brdctl(काष्ठा ahc_softc *ahc, uपूर्णांक8_t value);
अटल uपूर्णांक8_t पढ़ो_brdctl(काष्ठा ahc_softc *ahc);
अटल व्योम ahc_pci_पूर्णांकr(काष्ठा ahc_softc *ahc);
अटल पूर्णांक  ahc_pci_chip_init(काष्ठा ahc_softc *ahc);

अटल पूर्णांक
ahc_9005_subdevinfo_valid(uपूर्णांक16_t device, uपूर्णांक16_t venकरोr,
			  uपूर्णांक16_t subdevice, uपूर्णांक16_t subvenकरोr)
अणु
	पूर्णांक result;

	/* Default to invalid. */
	result = 0;
	अगर (venकरोr == 0x9005
	 && subvenकरोr == 0x9005
         && subdevice != device
         && SUBID_9005_TYPE_KNOWN(subdevice) != 0) अणु

		चयन (SUBID_9005_TYPE(subdevice)) अणु
		हाल SUBID_9005_TYPE_MB:
			अवरोध;
		हाल SUBID_9005_TYPE_CARD:
		हाल SUBID_9005_TYPE_LCCARD:
			/*
			 * Currently only trust Adaptec cards to
			 * get the sub device info correct.
			 */
			अगर (DEVID_9005_TYPE(device) == DEVID_9005_TYPE_HBA)
				result = 1;
			अवरोध;
		हाल SUBID_9005_TYPE_RAID:
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	वापस (result);
पूर्ण

स्थिर काष्ठा ahc_pci_identity *
ahc_find_pci_device(ahc_dev_softc_t pci)
अणु
	uपूर्णांक64_t  full_id;
	uपूर्णांक16_t  device;
	uपूर्णांक16_t  venकरोr;
	uपूर्णांक16_t  subdevice;
	uपूर्णांक16_t  subvenकरोr;
	स्थिर काष्ठा ahc_pci_identity *entry;
	u_पूर्णांक	  i;

	venकरोr = ahc_pci_पढ़ो_config(pci, PCIR_DEVVENDOR, /*bytes*/2);
	device = ahc_pci_पढ़ो_config(pci, PCIR_DEVICE, /*bytes*/2);
	subvenकरोr = ahc_pci_पढ़ो_config(pci, PCIR_SUBVEND_0, /*bytes*/2);
	subdevice = ahc_pci_पढ़ो_config(pci, PCIR_SUBDEV_0, /*bytes*/2);
	full_id = ahc_compose_id(device, venकरोr, subdevice, subvenकरोr);

	/*
	 * If the second function is not hooked up, ignore it.
	 * Unक्रमtunately, not all MB venकरोrs implement the
	 * subdevice ID as per the Adaptec spec, so करो our best
	 * to sanity check it prior to accepting the subdevice
	 * ID as valid.
	 */
	अगर (ahc_get_pci_function(pci) > 0
	 && ahc_9005_subdevinfo_valid(device, venकरोr, subdevice, subvenकरोr)
	 && SUBID_9005_MFUNCENB(subdevice) == 0)
		वापस (शून्य);

	क्रम (i = 0; i < ahc_num_pci_devs; i++) अणु
		entry = &ahc_pci_ident_table[i];
		अगर (entry->full_id == (full_id & entry->id_mask)) अणु
			/* Honor exclusion entries. */
			अगर (entry->name == शून्य)
				वापस (शून्य);
			वापस (entry);
		पूर्ण
	पूर्ण
	वापस (शून्य);
पूर्ण

पूर्णांक
ahc_pci_config(काष्ठा ahc_softc *ahc, स्थिर काष्ठा ahc_pci_identity *entry)
अणु
	u_पूर्णांक	 command;
	u_पूर्णांक	 our_id;
	u_पूर्णांक	 sxfrctl1;
	u_पूर्णांक	 scsiseq;
	u_पूर्णांक	 dscommand0;
	uपूर्णांक32_t devconfig;
	पूर्णांक	 error;
	uपूर्णांक8_t	 sblkctl;

	our_id = 0;
	error = entry->setup(ahc);
	अगर (error != 0)
		वापस (error);
	ahc->chip |= AHC_PCI;
	ahc->description = entry->name;

	pci_set_घातer_state(ahc->dev_softc, AHC_POWER_STATE_D0);

	error = ahc_pci_map_रेजिस्टरs(ahc);
	अगर (error != 0)
		वापस (error);

	/*
	 * Beक्रमe we जारी probing the card, ensure that
	 * its पूर्णांकerrupts are *disabled*.  We करोn't want
	 * a misstep to hang the machine in an पूर्णांकerrupt
	 * storm.
	 */
	ahc_पूर्णांकr_enable(ahc, FALSE);

	devconfig = ahc_pci_पढ़ो_config(ahc->dev_softc, DEVCONFIG, /*bytes*/4);

	/*
	 * If we need to support high memory, enable dual
	 * address cycles.  This bit must be set to enable
	 * high address bit generation even अगर we are on a
	 * 64bit bus (PCI64BIT set in devconfig).
	 */
	अगर ((ahc->flags & AHC_39BIT_ADDRESSING) != 0) अणु

		अगर (bootverbose)
			prपूर्णांकk("%s: Enabling 39Bit Addressing\n",
			       ahc_name(ahc));
		devconfig |= DACEN;
	पूर्ण
	
	/* Ensure that pci error generation, a test feature, is disabled. */
	devconfig |= PCIERRGENDIS;

	ahc_pci_ग_लिखो_config(ahc->dev_softc, DEVCONFIG, devconfig, /*bytes*/4);

	/* Ensure busmastering is enabled */
	command = ahc_pci_पढ़ो_config(ahc->dev_softc, PCIR_COMMAND, /*bytes*/2);
	command |= PCIM_CMD_BUSMASTEREN;

	ahc_pci_ग_लिखो_config(ahc->dev_softc, PCIR_COMMAND, command, /*bytes*/2);

	/* On all PCI adapters, we allow SCB paging */
	ahc->flags |= AHC_PAGESCBS;

	error = ahc_softc_init(ahc);
	अगर (error != 0)
		वापस (error);

	/*
	 * Disable PCI parity error checking.  Users typically
	 * करो this to work around broken PCI chipsets that get
	 * the parity timing wrong and thus generate lots of spurious
	 * errors.  The chip only allows us to disable *all* parity
	 * error reporting when करोing this, so CIO bus, scb ram, and
	 * scratch ram parity errors will be ignored too.
	 */
	अगर ((ahc->flags & AHC_DISABLE_PCI_PERR) != 0)
		ahc->seqctl |= FAILDIS;

	ahc->bus_पूर्णांकr = ahc_pci_पूर्णांकr;
	ahc->bus_chip_init = ahc_pci_chip_init;

	/* Remember how the card was setup in हाल there is no SEEPROM */
	अगर ((ahc_inb(ahc, HCNTRL) & POWRDN) == 0) अणु
		ahc_छोड़ो(ahc);
		अगर ((ahc->features & AHC_ULTRA2) != 0)
			our_id = ahc_inb(ahc, SCSIID_ULTRA2) & OID;
		अन्यथा
			our_id = ahc_inb(ahc, SCSIID) & OID;
		sxfrctl1 = ahc_inb(ahc, SXFRCTL1) & STPWEN;
		scsiseq = ahc_inb(ahc, SCSISEQ);
	पूर्ण अन्यथा अणु
		sxfrctl1 = STPWEN;
		our_id = 7;
		scsiseq = 0;
	पूर्ण

	error = ahc_reset(ahc, /*reinit*/FALSE);
	अगर (error != 0)
		वापस (ENXIO);

	अगर ((ahc->features & AHC_DT) != 0) अणु
		u_पूर्णांक sfunct;

		/* Perक्रमm ALT-Mode Setup */
		sfunct = ahc_inb(ahc, SFUNCT) & ~ALT_MODE;
		ahc_outb(ahc, SFUNCT, sfunct | ALT_MODE);
		ahc_outb(ahc, OPTIONMODE,
			 OPTIONMODE_DEFAULTS|AUTOACKEN|BUSFREEREV|EXPPHASEDIS);
		ahc_outb(ahc, SFUNCT, sfunct);

		/* Normal mode setup */
		ahc_outb(ahc, CRCCONTROL1, CRCVALCHKEN|CRCENDCHKEN|CRCREQCHKEN
					  |TARGCRCENDEN);
	पूर्ण

	dscommand0 = ahc_inb(ahc, DSCOMMAND0);
	dscommand0 |= MPARCKEN|CACHETHEN;
	अगर ((ahc->features & AHC_ULTRA2) != 0) अणु

		/*
		 * DPARCKEN करोesn't work correctly on
		 * some MBs so करोn't use it.
		 */
		dscommand0 &= ~DPARCKEN;
	पूर्ण

	/*
	 * Handle chips that must have cache line
	 * streaming (dis/en)abled.
	 */
	अगर ((ahc->bugs & AHC_CACHETHEN_DIS_BUG) != 0)
		dscommand0 |= CACHETHEN;

	अगर ((ahc->bugs & AHC_CACHETHEN_BUG) != 0)
		dscommand0 &= ~CACHETHEN;

	ahc_outb(ahc, DSCOMMAND0, dscommand0);

	ahc->pci_cachesize =
	    ahc_pci_पढ़ो_config(ahc->dev_softc, CSIZE_LATTIME,
				/*bytes*/1) & CACHESIZE;
	ahc->pci_cachesize *= 4;

	अगर ((ahc->bugs & AHC_PCI_2_1_RETRY_BUG) != 0
	 && ahc->pci_cachesize == 4) अणु

		ahc_pci_ग_लिखो_config(ahc->dev_softc, CSIZE_LATTIME,
				     0, /*bytes*/1);
		ahc->pci_cachesize = 0;
	पूर्ण

	/*
	 * We cannot perक्रमm ULTRA speeds without the presence
	 * of the बाह्यal precision resistor.
	 */
	अगर ((ahc->features & AHC_ULTRA) != 0) अणु
		uपूर्णांक32_t devconfig;

		devconfig = ahc_pci_पढ़ो_config(ahc->dev_softc,
						DEVCONFIG, /*bytes*/4);
		अगर ((devconfig & REXTVALID) == 0)
			ahc->features &= ~AHC_ULTRA;
	पूर्ण

	/* See अगर we have a SEEPROM and perक्रमm स्वतः-term */
	check_extport(ahc, &sxfrctl1);

	/*
	 * Take the LED out of diagnostic mode
	 */
	sblkctl = ahc_inb(ahc, SBLKCTL);
	ahc_outb(ahc, SBLKCTL, (sblkctl & ~(DIAGLEDEN|DIAGLEDON)));

	अगर ((ahc->features & AHC_ULTRA2) != 0) अणु
		ahc_outb(ahc, DFF_THRSH, RD_DFTHRSH_MAX|WR_DFTHRSH_MAX);
	पूर्ण अन्यथा अणु
		ahc_outb(ahc, DSPCISTATUS, DFTHRSH_100);
	पूर्ण

	अगर (ahc->flags & AHC_USEDEFAULTS) अणु
		/*
		 * PCI Adapter शेष setup
		 * Should only be used अगर the adapter करोes not have
		 * a SEEPROM.
		 */
		/* See अगर someone अन्यथा set us up alपढ़ोy */
		अगर ((ahc->flags & AHC_NO_BIOS_INIT) == 0
		 && scsiseq != 0) अणु
			prपूर्णांकk("%s: Using left over BIOS settings\n",
				ahc_name(ahc));
			ahc->flags &= ~AHC_USEDEFAULTS;
			ahc->flags |= AHC_BIOS_ENABLED;
		पूर्ण अन्यथा अणु
			/*
			 * Assume only one connector and always turn
			 * on termination.
			 */
 			our_id = 0x07;
			sxfrctl1 = STPWEN;
		पूर्ण
		ahc_outb(ahc, SCSICONF, our_id|ENSPCHK|RESET_SCSI);

		ahc->our_id = our_id;
	पूर्ण

	/*
	 * Take a look to see अगर we have बाह्यal SRAM.
	 * We currently करो not attempt to use SRAM that is
	 * shared among multiple controllers.
	 */
	ahc_probe_ext_scbram(ahc);

	/*
	 * Record our termination setting क्रम the
	 * generic initialization routine.
	 */
	अगर ((sxfrctl1 & STPWEN) != 0)
		ahc->flags |= AHC_TERM_ENB_A;

	/*
	 * Save chip रेजिस्टर configuration data क्रम chip resets
	 * that occur during runसमय and resume events.
	 */
	ahc->bus_softc.pci_softc.devconfig =
	    ahc_pci_पढ़ो_config(ahc->dev_softc, DEVCONFIG, /*bytes*/4);
	ahc->bus_softc.pci_softc.command =
	    ahc_pci_पढ़ो_config(ahc->dev_softc, PCIR_COMMAND, /*bytes*/1);
	ahc->bus_softc.pci_softc.csize_latसमय =
	    ahc_pci_पढ़ो_config(ahc->dev_softc, CSIZE_LATTIME, /*bytes*/1);
	ahc->bus_softc.pci_softc.dscommand0 = ahc_inb(ahc, DSCOMMAND0);
	ahc->bus_softc.pci_softc.dspcistatus = ahc_inb(ahc, DSPCISTATUS);
	अगर ((ahc->features & AHC_DT) != 0) अणु
		u_पूर्णांक sfunct;

		sfunct = ahc_inb(ahc, SFUNCT) & ~ALT_MODE;
		ahc_outb(ahc, SFUNCT, sfunct | ALT_MODE);
		ahc->bus_softc.pci_softc.optionmode = ahc_inb(ahc, OPTIONMODE);
		ahc->bus_softc.pci_softc.targcrccnt = ahc_inw(ahc, TARGCRCCNT);
		ahc_outb(ahc, SFUNCT, sfunct);
		ahc->bus_softc.pci_softc.crccontrol1 =
		    ahc_inb(ahc, CRCCONTROL1);
	पूर्ण
	अगर ((ahc->features & AHC_MULTI_FUNC) != 0)
		ahc->bus_softc.pci_softc.scbbaddr = ahc_inb(ahc, SCBBADDR);

	अगर ((ahc->features & AHC_ULTRA2) != 0)
		ahc->bus_softc.pci_softc.dff_thrsh = ahc_inb(ahc, DFF_THRSH);

	/* Core initialization */
	error = ahc_init(ahc);
	अगर (error != 0)
		वापस (error);
	ahc->init_level++;

	/*
	 * Allow पूर्णांकerrupts now that we are completely setup.
	 */
	वापस ahc_pci_map_पूर्णांक(ahc);
पूर्ण

/*
 * Test क्रम the presence of बाह्यal sram in an
 * "unshared" configuration.
 */
अटल पूर्णांक
ahc_ext_scbram_present(काष्ठा ahc_softc *ahc)
अणु
	u_पूर्णांक chip;
	पूर्णांक ramps;
	पूर्णांक single_user;
	uपूर्णांक32_t devconfig;

	chip = ahc->chip & AHC_CHIPID_MASK;
	devconfig = ahc_pci_पढ़ो_config(ahc->dev_softc,
					DEVCONFIG, /*bytes*/4);
	single_user = (devconfig & MPORTMODE) != 0;

	अगर ((ahc->features & AHC_ULTRA2) != 0)
		ramps = (ahc_inb(ahc, DSCOMMAND0) & RAMPS) != 0;
	अन्यथा अगर (chip == AHC_AIC7895 || chip == AHC_AIC7895C)
		/*
		 * External SCBRAM arbitration is flakey
		 * on these chips.  Unक्रमtunately this means
		 * we करोn't use the extra SCB ram space on the
		 * 3940AUW.
		 */
		ramps = 0;
	अन्यथा अगर (chip >= AHC_AIC7870)
		ramps = (devconfig & RAMPSM) != 0;
	अन्यथा
		ramps = 0;

	अगर (ramps && single_user)
		वापस (1);
	वापस (0);
पूर्ण

/*
 * Enable बाह्यal scbram.
 */
अटल व्योम
ahc_scbram_config(काष्ठा ahc_softc *ahc, पूर्णांक enable, पूर्णांक pcheck,
		  पूर्णांक fast, पूर्णांक large)
अणु
	uपूर्णांक32_t devconfig;

	अगर (ahc->features & AHC_MULTI_FUNC) अणु
		/*
		 * Set the SCB Base addr (highest address bit)
		 * depending on which channel we are.
		 */
		ahc_outb(ahc, SCBBADDR, ahc_get_pci_function(ahc->dev_softc));
	पूर्ण

	ahc->flags &= ~AHC_LSCBS_ENABLED;
	अगर (large)
		ahc->flags |= AHC_LSCBS_ENABLED;
	devconfig = ahc_pci_पढ़ो_config(ahc->dev_softc, DEVCONFIG, /*bytes*/4);
	अगर ((ahc->features & AHC_ULTRA2) != 0) अणु
		u_पूर्णांक dscommand0;

		dscommand0 = ahc_inb(ahc, DSCOMMAND0);
		अगर (enable)
			dscommand0 &= ~INTSCBRAMSEL;
		अन्यथा
			dscommand0 |= INTSCBRAMSEL;
		अगर (large)
			dscommand0 &= ~USCBSIZE32;
		अन्यथा
			dscommand0 |= USCBSIZE32;
		ahc_outb(ahc, DSCOMMAND0, dscommand0);
	पूर्ण अन्यथा अणु
		अगर (fast)
			devconfig &= ~EXTSCBTIME;
		अन्यथा
			devconfig |= EXTSCBTIME;
		अगर (enable)
			devconfig &= ~SCBRAMSEL;
		अन्यथा
			devconfig |= SCBRAMSEL;
		अगर (large)
			devconfig &= ~SCBSIZE32;
		अन्यथा
			devconfig |= SCBSIZE32;
	पूर्ण
	अगर (pcheck)
		devconfig |= EXTSCBPEN;
	अन्यथा
		devconfig &= ~EXTSCBPEN;

	ahc_pci_ग_लिखो_config(ahc->dev_softc, DEVCONFIG, devconfig, /*bytes*/4);
पूर्ण

/*
 * Take a look to see अगर we have बाह्यal SRAM.
 * We currently करो not attempt to use SRAM that is
 * shared among multiple controllers.
 */
अटल व्योम
ahc_probe_ext_scbram(काष्ठा ahc_softc *ahc)
अणु
	पूर्णांक num_scbs;
	पूर्णांक test_num_scbs;
	पूर्णांक enable;
	पूर्णांक pcheck;
	पूर्णांक fast;
	पूर्णांक large;

	enable = FALSE;
	pcheck = FALSE;
	fast = FALSE;
	large = FALSE;
	num_scbs = 0;
	
	अगर (ahc_ext_scbram_present(ahc) == 0)
		जाओ करोne;

	/*
	 * Probe क्रम the best parameters to use.
	 */
	ahc_scbram_config(ahc, /*enable*/TRUE, pcheck, fast, large);
	num_scbs = ahc_probe_scbs(ahc);
	अगर (num_scbs == 0) अणु
		/* The SRAM wasn't really present. */
		जाओ करोne;
	पूर्ण
	enable = TRUE;

	/*
	 * Clear any outstanding parity error
	 * and ensure that parity error reporting
	 * is enabled.
	 */
	ahc_outb(ahc, SEQCTL, 0);
	ahc_outb(ahc, CLRINT, CLRPARERR);
	ahc_outb(ahc, CLRINT, CLRBRKADRINT);

	/* Now see अगर we can करो parity */
	ahc_scbram_config(ahc, enable, /*pcheck*/TRUE, fast, large);
	num_scbs = ahc_probe_scbs(ahc);
	अगर ((ahc_inb(ahc, INTSTAT) & BRKADRINT) == 0
	 || (ahc_inb(ahc, ERROR) & MPARERR) == 0)
		pcheck = TRUE;

	/* Clear any resulting parity error */
	ahc_outb(ahc, CLRINT, CLRPARERR);
	ahc_outb(ahc, CLRINT, CLRBRKADRINT);

	/* Now see अगर we can करो fast timing */
	ahc_scbram_config(ahc, enable, pcheck, /*fast*/TRUE, large);
	test_num_scbs = ahc_probe_scbs(ahc);
	अगर (test_num_scbs == num_scbs
	 && ((ahc_inb(ahc, INTSTAT) & BRKADRINT) == 0
	  || (ahc_inb(ahc, ERROR) & MPARERR) == 0))
		fast = TRUE;

	/*
	 * See अगर we can use large SCBs and still मुख्यtain
	 * the same overall count of SCBs.
	 */
	अगर ((ahc->features & AHC_LARGE_SCBS) != 0) अणु
		ahc_scbram_config(ahc, enable, pcheck, fast, /*large*/TRUE);
		test_num_scbs = ahc_probe_scbs(ahc);
		अगर (test_num_scbs >= num_scbs) अणु
			large = TRUE;
			num_scbs = test_num_scbs;
	 		अगर (num_scbs >= 64) अणु
				/*
				 * We have enough space to move the
				 * "busy targets table" पूर्णांकo SCB space
				 * and make it qualअगरy all the way to the
				 * lun level.
				 */
				ahc->flags |= AHC_SCB_BTT;
			पूर्ण
		पूर्ण
	पूर्ण
करोne:
	/*
	 * Disable parity error reporting until we
	 * can load inकाष्ठाion ram.
	 */
	ahc_outb(ahc, SEQCTL, PERRORDIS|FAILDIS);
	/* Clear any latched parity error */
	ahc_outb(ahc, CLRINT, CLRPARERR);
	ahc_outb(ahc, CLRINT, CLRBRKADRINT);
	अगर (bootverbose && enable) अणु
		prपूर्णांकk("%s: External SRAM, %s access%s, %dbytes/SCB\n",
		       ahc_name(ahc), fast ? "fast" : "slow", 
		       pcheck ? ", parity checking enabled" : "",
		       large ? 64 : 32);
	पूर्ण
	ahc_scbram_config(ahc, enable, pcheck, fast, large);
पूर्ण

/*
 * Perक्रमm some simple tests that should catch situations where
 * our रेजिस्टरs are invalidly mapped.
 */
पूर्णांक
ahc_pci_test_रेजिस्टर_access(काष्ठा ahc_softc *ahc)
अणु
	पूर्णांक	 error;
	u_पूर्णांक	 status1;
	uपूर्णांक32_t cmd;
	uपूर्णांक8_t	 hcntrl;

	error = EIO;

	/*
	 * Enable PCI error पूर्णांकerrupt status, but suppress NMIs
	 * generated by SERR उठाओd due to target पातs.
	 */
	cmd = ahc_pci_पढ़ो_config(ahc->dev_softc, PCIR_COMMAND, /*bytes*/2);
	ahc_pci_ग_लिखो_config(ahc->dev_softc, PCIR_COMMAND,
			     cmd & ~PCIM_CMD_SERRESPEN, /*bytes*/2);

	/*
	 * First a simple test to see अगर any
	 * रेजिस्टरs can be पढ़ो.  Reading
	 * HCNTRL has no side effects and has
	 * at least one bit that is guaranteed to
	 * be zero so it is a good रेजिस्टर to
	 * use क्रम this test.
	 */
	hcntrl = ahc_inb(ahc, HCNTRL);

	अगर (hcntrl == 0xFF)
		जाओ fail;

	अगर ((hcntrl & CHIPRST) != 0) अणु
		/*
		 * The chip has not been initialized since
		 * PCI/EISA/VLB bus reset.  Don't trust
		 * "left over BIOS data".
		 */
		ahc->flags |= AHC_NO_BIOS_INIT;
	पूर्ण

	/*
	 * Next create a situation where ग_लिखो combining
	 * or पढ़ो prefetching could be initiated by the
	 * CPU or host bridge.  Our device करोes not support
	 * either, so look क्रम data corruption and/or flagged
	 * PCI errors.  First छोड़ो without causing another
	 * chip reset.
	 */
	hcntrl &= ~CHIPRST;
	ahc_outb(ahc, HCNTRL, hcntrl|PAUSE);
	जबतक (ahc_is_छोड़ोd(ahc) == 0)
		;

	/* Clear any PCI errors that occurred beक्रमe our driver attached. */
	status1 = ahc_pci_पढ़ो_config(ahc->dev_softc,
				      PCIR_STATUS + 1, /*bytes*/1);
	ahc_pci_ग_लिखो_config(ahc->dev_softc, PCIR_STATUS + 1,
			     status1, /*bytes*/1);
	ahc_outb(ahc, CLRINT, CLRPARERR);

	ahc_outb(ahc, SEQCTL, PERRORDIS);
	ahc_outb(ahc, SCBPTR, 0);
	ahc_outl(ahc, SCB_BASE, 0x5aa555aa);
	अगर (ahc_inl(ahc, SCB_BASE) != 0x5aa555aa)
		जाओ fail;

	status1 = ahc_pci_पढ़ो_config(ahc->dev_softc,
				      PCIR_STATUS + 1, /*bytes*/1);
	अगर ((status1 & STA) != 0)
		जाओ fail;

	error = 0;

fail:
	/* Silently clear any latched errors. */
	status1 = ahc_pci_पढ़ो_config(ahc->dev_softc,
				      PCIR_STATUS + 1, /*bytes*/1);
	ahc_pci_ग_लिखो_config(ahc->dev_softc, PCIR_STATUS + 1,
			     status1, /*bytes*/1);
	ahc_outb(ahc, CLRINT, CLRPARERR);
	ahc_outb(ahc, SEQCTL, PERRORDIS|FAILDIS);
	ahc_pci_ग_लिखो_config(ahc->dev_softc, PCIR_COMMAND, cmd, /*bytes*/2);
	वापस (error);
पूर्ण

/*
 * Check the बाह्यal port logic क्रम a serial eeprom
 * and termination/cable detection contrls.
 */
अटल व्योम
check_extport(काष्ठा ahc_softc *ahc, u_पूर्णांक *sxfrctl1)
अणु
	काष्ठा	seeprom_descriptor sd;
	काष्ठा	seeprom_config *sc;
	पूर्णांक	have_seeprom;
	पूर्णांक	have_स्वतःterm;

	sd.sd_ahc = ahc;
	sd.sd_control_offset = SEECTL;		
	sd.sd_status_offset = SEECTL;		
	sd.sd_dataout_offset = SEECTL;		
	sc = ahc->seep_config;

	/*
	 * For some multi-channel devices, the c46 is simply too
	 * small to work.  For the other controller types, we can
	 * get our inक्रमmation from either SEEPROM type.  Set the
	 * type to start our probe with accordingly.
	 */
	अगर (ahc->flags & AHC_LARGE_SEEPROM)
		sd.sd_chip = C56_66;
	अन्यथा
		sd.sd_chip = C46;

	sd.sd_MS = SEEMS;
	sd.sd_RDY = SEERDY;
	sd.sd_CS = SEECS;
	sd.sd_CK = SEECK;
	sd.sd_DO = SEEDO;
	sd.sd_DI = SEEDI;

	have_seeprom = ahc_acquire_seeprom(ahc, &sd);
	अगर (have_seeprom) अणु

		अगर (bootverbose) 
			prपूर्णांकk("%s: Reading SEEPROM...", ahc_name(ahc));

		क्रम (;;) अणु
			u_पूर्णांक start_addr;

			start_addr = 32 * (ahc->channel - 'A');

			have_seeprom = ahc_पढ़ो_seeprom(&sd, (uपूर्णांक16_t *)sc,
							start_addr,
							माप(*sc)/2);

			अगर (have_seeprom)
				have_seeprom = ahc_verअगरy_cksum(sc);

			अगर (have_seeprom != 0 || sd.sd_chip == C56_66) अणु
				अगर (bootverbose) अणु
					अगर (have_seeprom == 0)
						prपूर्णांकk ("checksum error\n");
					अन्यथा
						prपूर्णांकk ("done.\n");
				पूर्ण
				अवरोध;
			पूर्ण
			sd.sd_chip = C56_66;
		पूर्ण
		ahc_release_seeprom(&sd);

		/* Remember the SEEPROM type क्रम later */
		अगर (sd.sd_chip == C56_66)
			ahc->flags |= AHC_LARGE_SEEPROM;
	पूर्ण

	अगर (!have_seeprom) अणु
		/*
		 * Pull scratch ram settings and treat them as
		 * अगर they are the contents of an seeprom अगर
		 * the 'ADPT' signature is found in SCB2.
		 * We manually compose the data as 16bit values
		 * to aव्योम endian issues.
		 */
		ahc_outb(ahc, SCBPTR, 2);
		अगर (ahc_inb(ahc, SCB_BASE) == 'A'
		 && ahc_inb(ahc, SCB_BASE + 1) == 'D'
		 && ahc_inb(ahc, SCB_BASE + 2) == 'P'
		 && ahc_inb(ahc, SCB_BASE + 3) == 'T') अणु
			uपूर्णांक16_t *sc_data;
			पूर्णांक	  i;

			sc_data = (uपूर्णांक16_t *)sc;
			क्रम (i = 0; i < 32; i++, sc_data++) अणु
				पूर्णांक	j;

				j = i * 2;
				*sc_data = ahc_inb(ahc, SRAM_BASE + j)
					 | ahc_inb(ahc, SRAM_BASE + j + 1) << 8;
			पूर्ण
			have_seeprom = ahc_verअगरy_cksum(sc);
			अगर (have_seeprom)
				ahc->flags |= AHC_SCB_CONFIG_USED;
		पूर्ण
		/*
		 * Clear any SCB parity errors in हाल this data and
		 * its associated parity was not initialized by the BIOS
		 */
		ahc_outb(ahc, CLRINT, CLRPARERR);
		ahc_outb(ahc, CLRINT, CLRBRKADRINT);
	पूर्ण

	अगर (!have_seeprom) अणु
		अगर (bootverbose)
			prपूर्णांकk("%s: No SEEPROM available.\n", ahc_name(ahc));
		ahc->flags |= AHC_USEDEFAULTS;
		kमुक्त(ahc->seep_config);
		ahc->seep_config = शून्य;
		sc = शून्य;
	पूर्ण अन्यथा अणु
		ahc_parse_pci_eeprom(ahc, sc);
	पूर्ण

	/*
	 * Cards that have the बाह्यal logic necessary to talk to
	 * a SEEPROM, are almost certain to have the reमुख्यing logic
	 * necessary क्रम स्वतः-termination control.  This assumption
	 * hasn't failed yet...
	 */
	have_स्वतःterm = have_seeprom;

	/*
	 * Some low-cost chips have SEEPROM and स्वतः-term control built
	 * in, instead of using a GAL.  They can tell us directly
	 * अगर the termination logic is enabled.
	 */
	अगर ((ahc->features & AHC_SPIOCAP) != 0) अणु
		अगर ((ahc_inb(ahc, SPIOCAP) & SSPIOCPS) == 0)
			have_स्वतःterm = FALSE;
	पूर्ण

	अगर (have_स्वतःterm) अणु
		ahc->flags |= AHC_HAS_TERM_LOGIC;
		ahc_acquire_seeprom(ahc, &sd);
		configure_termination(ahc, &sd, sc->adapter_control, sxfrctl1);
		ahc_release_seeprom(&sd);
	पूर्ण अन्यथा अगर (have_seeprom) अणु
		*sxfrctl1 &= ~STPWEN;
		अगर ((sc->adapter_control & CFSTERM) != 0)
			*sxfrctl1 |= STPWEN;
		अगर (bootverbose)
			prपूर्णांकk("%s: Low byte termination %sabled\n",
			       ahc_name(ahc),
			       (*sxfrctl1 & STPWEN) ? "en" : "dis");
	पूर्ण
पूर्ण

अटल व्योम
ahc_parse_pci_eeprom(काष्ठा ahc_softc *ahc, काष्ठा seeprom_config *sc)
अणु
	/*
	 * Put the data we've collected करोwn पूर्णांकo SRAM
	 * where ahc_init will find it.
	 */
	पूर्णांक	 i;
	पूर्णांक	 max_targ = sc->max_tarमाला_लो & CFMAXTARG;
	u_पूर्णांक	 scsi_conf;
	uपूर्णांक16_t discenable;
	uपूर्णांक16_t ultraenb;

	discenable = 0;
	ultraenb = 0;
	अगर ((sc->adapter_control & CFULTRAEN) != 0) अणु
		/*
		 * Determine अगर this adapter has a "newstyle"
		 * SEEPROM क्रमmat.
		 */
		क्रम (i = 0; i < max_targ; i++) अणु
			अगर ((sc->device_flags[i] & CFSYNCHISULTRA) != 0) अणु
				ahc->flags |= AHC_NEWEEPROM_FMT;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < max_targ; i++) अणु
		u_पूर्णांक     scsirate;
		uपूर्णांक16_t target_mask;

		target_mask = 0x01 << i;
		अगर (sc->device_flags[i] & CFDISC)
			discenable |= target_mask;
		अगर ((ahc->flags & AHC_NEWEEPROM_FMT) != 0) अणु
			अगर ((sc->device_flags[i] & CFSYNCHISULTRA) != 0)
				ultraenb |= target_mask;
		पूर्ण अन्यथा अगर ((sc->adapter_control & CFULTRAEN) != 0) अणु
			ultraenb |= target_mask;
		पूर्ण
		अगर ((sc->device_flags[i] & CFXFER) == 0x04
		 && (ultraenb & target_mask) != 0) अणु
			/* Treat 10MHz as a non-ultra speed */
			sc->device_flags[i] &= ~CFXFER;
		 	ultraenb &= ~target_mask;
		पूर्ण
		अगर ((ahc->features & AHC_ULTRA2) != 0) अणु
			u_पूर्णांक offset;

			अगर (sc->device_flags[i] & CFSYNCH)
				offset = MAX_OFFSET_ULTRA2;
			अन्यथा 
				offset = 0;
			ahc_outb(ahc, TARG_OFFSET + i, offset);

			/*
			 * The ultra enable bits contain the
			 * high bit of the ultra2 sync rate
			 * field.
			 */
			scsirate = (sc->device_flags[i] & CFXFER)
				 | ((ultraenb & target_mask) ? 0x8 : 0x0);
			अगर (sc->device_flags[i] & CFWIDEB)
				scsirate |= WIDEXFER;
		पूर्ण अन्यथा अणु
			scsirate = (sc->device_flags[i] & CFXFER) << 4;
			अगर (sc->device_flags[i] & CFSYNCH)
				scsirate |= SOFS;
			अगर (sc->device_flags[i] & CFWIDEB)
				scsirate |= WIDEXFER;
		पूर्ण
		ahc_outb(ahc, TARG_SCSIRATE + i, scsirate);
	पूर्ण
	ahc->our_id = sc->brसमय_id & CFSCSIID;

	scsi_conf = (ahc->our_id & 0x7);
	अगर (sc->adapter_control & CFSPARITY)
		scsi_conf |= ENSPCHK;
	अगर (sc->adapter_control & CFRESETB)
		scsi_conf |= RESET_SCSI;

	ahc->flags |= (sc->adapter_control & CFBOOTCHAN) >> CFBOOTCHANSHIFT;

	अगर (sc->bios_control & CFEXTEND)
		ahc->flags |= AHC_EXTENDED_TRANS_A;

	अगर (sc->bios_control & CFBIOSEN)
		ahc->flags |= AHC_BIOS_ENABLED;
	अगर (ahc->features & AHC_ULTRA
	 && (ahc->flags & AHC_NEWEEPROM_FMT) == 0) अणु
		/* Should we enable Ultra mode? */
		अगर (!(sc->adapter_control & CFULTRAEN))
			/* Treat us as a non-ultra card */
			ultraenb = 0;
	पूर्ण

	अगर (sc->signature == CFSIGNATURE
	 || sc->signature == CFSIGNATURE2) अणु
		uपूर्णांक32_t devconfig;

		/* Honor the STPWLEVEL settings */
		devconfig = ahc_pci_पढ़ो_config(ahc->dev_softc,
						DEVCONFIG, /*bytes*/4);
		devconfig &= ~STPWLEVEL;
		अगर ((sc->bios_control & CFSTPWLEVEL) != 0)
			devconfig |= STPWLEVEL;
		ahc_pci_ग_लिखो_config(ahc->dev_softc, DEVCONFIG,
				     devconfig, /*bytes*/4);
	पूर्ण
	/* Set SCSICONF info */
	ahc_outb(ahc, SCSICONF, scsi_conf);
	ahc_outb(ahc, DISC_DSB, ~(discenable & 0xff));
	ahc_outb(ahc, DISC_DSB + 1, ~((discenable >> 8) & 0xff));
	ahc_outb(ahc, ULTRA_ENB, ultraenb & 0xff);
	ahc_outb(ahc, ULTRA_ENB + 1, (ultraenb >> 8) & 0xff);
पूर्ण

अटल व्योम
configure_termination(काष्ठा ahc_softc *ahc,
		      काष्ठा seeprom_descriptor *sd,
		      u_पूर्णांक adapter_control,
		      u_पूर्णांक *sxfrctl1)
अणु
	uपूर्णांक8_t brddat;
	
	brddat = 0;

	/*
	 * Update the settings in sxfrctl1 to match the
	 * termination settings 
	 */
	*sxfrctl1 = 0;
	
	/*
	 * SEECS must be on क्रम the GALS to latch
	 * the data properly.  Be sure to leave MS
	 * on or we will release the seeprom.
	 */
	SEEPROM_OUTB(sd, sd->sd_MS | sd->sd_CS);
	अगर ((adapter_control & CFAUTOTERM) != 0
	 || (ahc->features & AHC_NEW_TERMCTL) != 0) अणु
		पूर्णांक पूर्णांकernal50_present;
		पूर्णांक पूर्णांकernal68_present;
		पूर्णांक बाह्यalcable_present;
		पूर्णांक eeprom_present;
		पूर्णांक enableSEC_low;
		पूर्णांक enableSEC_high;
		पूर्णांक enablePRI_low;
		पूर्णांक enablePRI_high;
		पूर्णांक sum;

		enableSEC_low = 0;
		enableSEC_high = 0;
		enablePRI_low = 0;
		enablePRI_high = 0;
		अगर ((ahc->features & AHC_NEW_TERMCTL) != 0) अणु
			ahc_new_term_detect(ahc, &enableSEC_low,
					    &enableSEC_high,
					    &enablePRI_low,
					    &enablePRI_high,
					    &eeprom_present);
			अगर ((adapter_control & CFSEAUTOTERM) == 0) अणु
				अगर (bootverbose)
					prपूर्णांकk("%s: Manual SE Termination\n",
					       ahc_name(ahc));
				enableSEC_low = (adapter_control & CFSELOWTERM);
				enableSEC_high =
				    (adapter_control & CFSEHIGHTERM);
			पूर्ण
			अगर ((adapter_control & CFAUTOTERM) == 0) अणु
				अगर (bootverbose)
					prपूर्णांकk("%s: Manual LVD Termination\n",
					       ahc_name(ahc));
				enablePRI_low = (adapter_control & CFSTERM);
				enablePRI_high = (adapter_control & CFWSTERM);
			पूर्ण
			/* Make the table calculations below happy */
			पूर्णांकernal50_present = 0;
			पूर्णांकernal68_present = 1;
			बाह्यalcable_present = 1;
		पूर्ण अन्यथा अगर ((ahc->features & AHC_SPIOCAP) != 0) अणु
			aic785X_cable_detect(ahc, &पूर्णांकernal50_present,
					     &बाह्यalcable_present,
					     &eeprom_present);
			/* Can never support a wide connector. */
			पूर्णांकernal68_present = 0;
		पूर्ण अन्यथा अणु
			aic787X_cable_detect(ahc, &पूर्णांकernal50_present,
					     &पूर्णांकernal68_present,
					     &बाह्यalcable_present,
					     &eeprom_present);
		पूर्ण

		अगर ((ahc->features & AHC_WIDE) == 0)
			पूर्णांकernal68_present = 0;

		अगर (bootverbose
		 && (ahc->features & AHC_ULTRA2) == 0) अणु
			prपूर्णांकk("%s: internal 50 cable %s present",
			       ahc_name(ahc),
			       पूर्णांकernal50_present ? "is":"not");

			अगर ((ahc->features & AHC_WIDE) != 0)
				prपूर्णांकk(", internal 68 cable %s present",
				       पूर्णांकernal68_present ? "is":"not");
			prपूर्णांकk("\n%s: external cable %s present\n",
			       ahc_name(ahc),
			       बाह्यalcable_present ? "is":"not");
		पूर्ण
		अगर (bootverbose)
			prपूर्णांकk("%s: BIOS eeprom %s present\n",
			       ahc_name(ahc), eeprom_present ? "is" : "not");

		अगर ((ahc->flags & AHC_INT50_SPEEDFLEX) != 0) अणु
			/*
			 * The 50 pin connector is a separate bus,
			 * so क्रमce it to always be terminated.
			 * In the future, perक्रमm current sensing
			 * to determine अगर we are in the middle of
			 * a properly terminated bus.
			 */
			पूर्णांकernal50_present = 0;
		पूर्ण

		/*
		 * Now set the termination based on what
		 * we found.
		 * Flash Enable = BRDDAT7
		 * Secondary High Term Enable = BRDDAT6
		 * Secondary Low Term Enable = BRDDAT5 (7890)
		 * Primary High Term Enable = BRDDAT4 (7890)
		 */
		अगर ((ahc->features & AHC_ULTRA2) == 0
		 && (पूर्णांकernal50_present != 0)
		 && (पूर्णांकernal68_present != 0)
		 && (बाह्यalcable_present != 0)) अणु
			prपूर्णांकk("%s: Illegal cable configuration!!. "
			       "Only two connectors on the "
			       "adapter may be used at a "
			       "time!\n", ahc_name(ahc));

			/*
			 * Pretend there are no cables in the hope
			 * that having all of the termination on
			 * gives us a more stable bus.
			 */
		 	पूर्णांकernal50_present = 0;
			पूर्णांकernal68_present = 0;
			बाह्यalcable_present = 0;
		पूर्ण

		अगर ((ahc->features & AHC_WIDE) != 0
		 && ((बाह्यalcable_present == 0)
		  || (पूर्णांकernal68_present == 0)
		  || (enableSEC_high != 0))) अणु
			brddat |= BRDDAT6;
			अगर (bootverbose) अणु
				अगर ((ahc->flags & AHC_INT50_SPEEDFLEX) != 0)
					prपूर्णांकk("%s: 68 pin termination "
					       "Enabled\n", ahc_name(ahc));
				अन्यथा
					prपूर्णांकk("%s: %sHigh byte termination "
					       "Enabled\n", ahc_name(ahc),
					       enableSEC_high ? "Secondary "
							      : "");
			पूर्ण
		पूर्ण

		sum = पूर्णांकernal50_present + पूर्णांकernal68_present
		    + बाह्यalcable_present;
		अगर (sum < 2 || (enableSEC_low != 0)) अणु
			अगर ((ahc->features & AHC_ULTRA2) != 0)
				brddat |= BRDDAT5;
			अन्यथा
				*sxfrctl1 |= STPWEN;
			अगर (bootverbose) अणु
				अगर ((ahc->flags & AHC_INT50_SPEEDFLEX) != 0)
					prपूर्णांकk("%s: 50 pin termination "
					       "Enabled\n", ahc_name(ahc));
				अन्यथा
					prपूर्णांकk("%s: %sLow byte termination "
					       "Enabled\n", ahc_name(ahc),
					       enableSEC_low ? "Secondary "
							     : "");
			पूर्ण
		पूर्ण

		अगर (enablePRI_low != 0) अणु
			*sxfrctl1 |= STPWEN;
			अगर (bootverbose)
				prपूर्णांकk("%s: Primary Low Byte termination "
				       "Enabled\n", ahc_name(ahc));
		पूर्ण

		/*
		 * Setup STPWEN beक्रमe setting up the rest of
		 * the termination per the tech note on the U160 cards.
		 */
		ahc_outb(ahc, SXFRCTL1, *sxfrctl1);

		अगर (enablePRI_high != 0) अणु
			brddat |= BRDDAT4;
			अगर (bootverbose)
				prपूर्णांकk("%s: Primary High Byte "
				       "termination Enabled\n",
				       ahc_name(ahc));
		पूर्ण
		
		ग_लिखो_brdctl(ahc, brddat);

	पूर्ण अन्यथा अणु
		अगर ((adapter_control & CFSTERM) != 0) अणु
			*sxfrctl1 |= STPWEN;

			अगर (bootverbose)
				prपूर्णांकk("%s: %sLow byte termination Enabled\n",
				       ahc_name(ahc),
				       (ahc->features & AHC_ULTRA2) ? "Primary "
								    : "");
		पूर्ण

		अगर ((adapter_control & CFWSTERM) != 0
		 && (ahc->features & AHC_WIDE) != 0) अणु
			brddat |= BRDDAT6;
			अगर (bootverbose)
				prपूर्णांकk("%s: %sHigh byte termination Enabled\n",
				       ahc_name(ahc),
				       (ahc->features & AHC_ULTRA2)
				     ? "Secondary " : "");
		पूर्ण

		/*
		 * Setup STPWEN beक्रमe setting up the rest of
		 * the termination per the tech note on the U160 cards.
		 */
		ahc_outb(ahc, SXFRCTL1, *sxfrctl1);

		अगर ((ahc->features & AHC_WIDE) != 0)
			ग_लिखो_brdctl(ahc, brddat);
	पूर्ण
	SEEPROM_OUTB(sd, sd->sd_MS); /* Clear CS */
पूर्ण

अटल व्योम
ahc_new_term_detect(काष्ठा ahc_softc *ahc, पूर्णांक *enableSEC_low,
		    पूर्णांक *enableSEC_high, पूर्णांक *enablePRI_low,
		    पूर्णांक *enablePRI_high, पूर्णांक *eeprom_present)
अणु
	uपूर्णांक8_t brdctl;

	/*
	 * BRDDAT7 = Eeprom
	 * BRDDAT6 = Enable Secondary High Byte termination
	 * BRDDAT5 = Enable Secondary Low Byte termination
	 * BRDDAT4 = Enable Primary high byte termination
	 * BRDDAT3 = Enable Primary low byte termination
	 */
	brdctl = पढ़ो_brdctl(ahc);
	*eeprom_present = brdctl & BRDDAT7;
	*enableSEC_high = (brdctl & BRDDAT6);
	*enableSEC_low = (brdctl & BRDDAT5);
	*enablePRI_high = (brdctl & BRDDAT4);
	*enablePRI_low = (brdctl & BRDDAT3);
पूर्ण

अटल व्योम
aic787X_cable_detect(काष्ठा ahc_softc *ahc, पूर्णांक *पूर्णांकernal50_present,
		     पूर्णांक *पूर्णांकernal68_present, पूर्णांक *बाह्यalcable_present,
		     पूर्णांक *eeprom_present)
अणु
	uपूर्णांक8_t brdctl;

	/*
	 * First पढ़ो the status of our cables.
	 * Set the rom bank to 0 since the
	 * bank setting serves as a multiplexor
	 * क्रम the cable detection logic.
	 * BRDDAT5 controls the bank चयन.
	 */
	ग_लिखो_brdctl(ahc, 0);

	/*
	 * Now पढ़ो the state of the पूर्णांकernal
	 * connectors.  BRDDAT6 is INT50 and
	 * BRDDAT7 is INT68.
	 */
	brdctl = पढ़ो_brdctl(ahc);
	*पूर्णांकernal50_present = (brdctl & BRDDAT6) ? 0 : 1;
	*पूर्णांकernal68_present = (brdctl & BRDDAT7) ? 0 : 1;

	/*
	 * Set the rom bank to 1 and determine
	 * the other संकेतs.
	 */
	ग_लिखो_brdctl(ahc, BRDDAT5);

	/*
	 * Now पढ़ो the state of the बाह्यal
	 * connectors.  BRDDAT6 is EXT68 and
	 * BRDDAT7 is EPROMPS.
	 */
	brdctl = पढ़ो_brdctl(ahc);
	*बाह्यalcable_present = (brdctl & BRDDAT6) ? 0 : 1;
	*eeprom_present = (brdctl & BRDDAT7) ? 1 : 0;
पूर्ण

अटल व्योम
aic785X_cable_detect(काष्ठा ahc_softc *ahc, पूर्णांक *पूर्णांकernal50_present,
		     पूर्णांक *बाह्यalcable_present, पूर्णांक *eeprom_present)
अणु
	uपूर्णांक8_t brdctl;
	uपूर्णांक8_t spiocap;

	spiocap = ahc_inb(ahc, SPIOCAP);
	spiocap &= ~SOFTCMDEN;
	spiocap |= EXT_BRDCTL;
	ahc_outb(ahc, SPIOCAP, spiocap);
	ahc_outb(ahc, BRDCTL, BRDRW|BRDCS);
	ahc_flush_device_ग_लिखोs(ahc);
	ahc_delay(500);
	ahc_outb(ahc, BRDCTL, 0);
	ahc_flush_device_ग_लिखोs(ahc);
	ahc_delay(500);
	brdctl = ahc_inb(ahc, BRDCTL);
	*पूर्णांकernal50_present = (brdctl & BRDDAT5) ? 0 : 1;
	*बाह्यalcable_present = (brdctl & BRDDAT6) ? 0 : 1;
	*eeprom_present = (ahc_inb(ahc, SPIOCAP) & EEPROM) ? 1 : 0;
पूर्ण
	
पूर्णांक
ahc_acquire_seeprom(काष्ठा ahc_softc *ahc, काष्ठा seeprom_descriptor *sd)
अणु
	पूर्णांक रुको;

	अगर ((ahc->features & AHC_SPIOCAP) != 0
	 && (ahc_inb(ahc, SPIOCAP) & SEEPROM) == 0)
		वापस (0);

	/*
	 * Request access of the memory port.  When access is
	 * granted, SEERDY will go high.  We use a 1 second
	 * समयout which should be near 1 second more than
	 * is needed.  Reason: after the chip reset, there
	 * should be no contention.
	 */
	SEEPROM_OUTB(sd, sd->sd_MS);
	रुको = 1000;  /* 1 second समयout in msec */
	जबतक (--रुको && ((SEEPROM_STATUS_INB(sd) & sd->sd_RDY) == 0)) अणु
		ahc_delay(1000);  /* delay 1 msec */
	पूर्ण
	अगर ((SEEPROM_STATUS_INB(sd) & sd->sd_RDY) == 0) अणु
		SEEPROM_OUTB(sd, 0); 
		वापस (0);
	पूर्ण
	वापस(1);
पूर्ण

व्योम
ahc_release_seeprom(काष्ठा seeprom_descriptor *sd)
अणु
	/* Release access to the memory port and the serial EEPROM. */
	SEEPROM_OUTB(sd, 0);
पूर्ण

अटल व्योम
ग_लिखो_brdctl(काष्ठा ahc_softc *ahc, uपूर्णांक8_t value)
अणु
	uपूर्णांक8_t brdctl;

	अगर ((ahc->chip & AHC_CHIPID_MASK) == AHC_AIC7895) अणु
		brdctl = BRDSTB;
	 	अगर (ahc->channel == 'B')
			brdctl |= BRDCS;
	पूर्ण अन्यथा अगर ((ahc->features & AHC_ULTRA2) != 0) अणु
		brdctl = 0;
	पूर्ण अन्यथा अणु
		brdctl = BRDSTB|BRDCS;
	पूर्ण
	ahc_outb(ahc, BRDCTL, brdctl);
	ahc_flush_device_ग_लिखोs(ahc);
	brdctl |= value;
	ahc_outb(ahc, BRDCTL, brdctl);
	ahc_flush_device_ग_लिखोs(ahc);
	अगर ((ahc->features & AHC_ULTRA2) != 0)
		brdctl |= BRDSTB_ULTRA2;
	अन्यथा
		brdctl &= ~BRDSTB;
	ahc_outb(ahc, BRDCTL, brdctl);
	ahc_flush_device_ग_लिखोs(ahc);
	अगर ((ahc->features & AHC_ULTRA2) != 0)
		brdctl = 0;
	अन्यथा
		brdctl &= ~BRDCS;
	ahc_outb(ahc, BRDCTL, brdctl);
पूर्ण

अटल uपूर्णांक8_t
पढ़ो_brdctl(काष्ठा ahc_softc *ahc)
अणु
	uपूर्णांक8_t brdctl;
	uपूर्णांक8_t value;

	अगर ((ahc->chip & AHC_CHIPID_MASK) == AHC_AIC7895) अणु
		brdctl = BRDRW;
	 	अगर (ahc->channel == 'B')
			brdctl |= BRDCS;
	पूर्ण अन्यथा अगर ((ahc->features & AHC_ULTRA2) != 0) अणु
		brdctl = BRDRW_ULTRA2;
	पूर्ण अन्यथा अणु
		brdctl = BRDRW|BRDCS;
	पूर्ण
	ahc_outb(ahc, BRDCTL, brdctl);
	ahc_flush_device_ग_लिखोs(ahc);
	value = ahc_inb(ahc, BRDCTL);
	ahc_outb(ahc, BRDCTL, 0);
	वापस (value);
पूर्ण

अटल व्योम
ahc_pci_पूर्णांकr(काष्ठा ahc_softc *ahc)
अणु
	u_पूर्णांक error;
	u_पूर्णांक status1;

	error = ahc_inb(ahc, ERROR);
	अगर ((error & PCIERRSTAT) == 0)
		वापस;

	status1 = ahc_pci_पढ़ो_config(ahc->dev_softc,
				      PCIR_STATUS + 1, /*bytes*/1);

	prपूर्णांकk("%s: PCI error Interrupt at seqaddr = 0x%x\n",
	      ahc_name(ahc),
	      ahc_inb(ahc, SEQADDR0) | (ahc_inb(ahc, SEQADDR1) << 8));

	अगर (status1 & DPE) अणु
		ahc->pci_target_perr_count++;
		prपूर्णांकk("%s: Data Parity Error Detected during address "
		       "or write data phase\n", ahc_name(ahc));
	पूर्ण
	अगर (status1 & SSE) अणु
		prपूर्णांकk("%s: Signal System Error Detected\n", ahc_name(ahc));
	पूर्ण
	अगर (status1 & RMA) अणु
		prपूर्णांकk("%s: Received a Master Abort\n", ahc_name(ahc));
	पूर्ण
	अगर (status1 & RTA) अणु
		prपूर्णांकk("%s: Received a Target Abort\n", ahc_name(ahc));
	पूर्ण
	अगर (status1 & STA) अणु
		prपूर्णांकk("%s: Signaled a Target Abort\n", ahc_name(ahc));
	पूर्ण
	अगर (status1 & DPR) अणु
		prपूर्णांकk("%s: Data Parity Error has been reported via PERR#\n",
		       ahc_name(ahc));
	पूर्ण

	/* Clear latched errors. */
	ahc_pci_ग_लिखो_config(ahc->dev_softc, PCIR_STATUS + 1,
			     status1, /*bytes*/1);

	अगर ((status1 & (DPE|SSE|RMA|RTA|STA|DPR)) == 0) अणु
		prपूर्णांकk("%s: Latched PCIERR interrupt with "
		       "no status bits set\n", ahc_name(ahc)); 
	पूर्ण अन्यथा अणु
		ahc_outb(ahc, CLRINT, CLRPARERR);
	पूर्ण

	अगर (ahc->pci_target_perr_count > AHC_PCI_TARGET_PERR_THRESH) अणु
		prपूर्णांकk(
"%s: WARNING WARNING WARNING WARNING\n"
"%s: Too many PCI parity errors observed as a target.\n"
"%s: Some device on this bus is generating bad parity.\n"
"%s: This is an error *observed by*, not *generated by*, this controller.\n"
"%s: PCI parity error checking has been disabled.\n"
"%s: WARNING WARNING WARNING WARNING\n",
		       ahc_name(ahc), ahc_name(ahc), ahc_name(ahc),
		       ahc_name(ahc), ahc_name(ahc), ahc_name(ahc));
		ahc->seqctl |= FAILDIS;
		ahc_outb(ahc, SEQCTL, ahc->seqctl);
	पूर्ण
	ahc_unछोड़ो(ahc);
पूर्ण

अटल पूर्णांक
ahc_pci_chip_init(काष्ठा ahc_softc *ahc)
अणु
	ahc_outb(ahc, DSCOMMAND0, ahc->bus_softc.pci_softc.dscommand0);
	ahc_outb(ahc, DSPCISTATUS, ahc->bus_softc.pci_softc.dspcistatus);
	अगर ((ahc->features & AHC_DT) != 0) अणु
		u_पूर्णांक sfunct;

		sfunct = ahc_inb(ahc, SFUNCT) & ~ALT_MODE;
		ahc_outb(ahc, SFUNCT, sfunct | ALT_MODE);
		ahc_outb(ahc, OPTIONMODE, ahc->bus_softc.pci_softc.optionmode);
		ahc_outw(ahc, TARGCRCCNT, ahc->bus_softc.pci_softc.targcrccnt);
		ahc_outb(ahc, SFUNCT, sfunct);
		ahc_outb(ahc, CRCCONTROL1,
			 ahc->bus_softc.pci_softc.crccontrol1);
	पूर्ण
	अगर ((ahc->features & AHC_MULTI_FUNC) != 0)
		ahc_outb(ahc, SCBBADDR, ahc->bus_softc.pci_softc.scbbaddr);

	अगर ((ahc->features & AHC_ULTRA2) != 0)
		ahc_outb(ahc, DFF_THRSH, ahc->bus_softc.pci_softc.dff_thrsh);

	वापस (ahc_chip_init(ahc));
पूर्ण

व्योम __maybe_unused
ahc_pci_resume(काष्ठा ahc_softc *ahc)
अणु
	/*
	 * We assume that the OS has restored our रेजिस्टर
	 * mappings, etc.  Just update the config space रेजिस्टरs
	 * that the OS करोesn't know about and rely on our chip
	 * reset handler to handle the rest.
	 */
	ahc_pci_ग_लिखो_config(ahc->dev_softc, DEVCONFIG,
			     ahc->bus_softc.pci_softc.devconfig, /*bytes*/4);
	ahc_pci_ग_लिखो_config(ahc->dev_softc, PCIR_COMMAND,
			     ahc->bus_softc.pci_softc.command, /*bytes*/1);
	ahc_pci_ग_लिखो_config(ahc->dev_softc, CSIZE_LATTIME,
			     ahc->bus_softc.pci_softc.csize_latसमय, /*bytes*/1);
	अगर ((ahc->flags & AHC_HAS_TERM_LOGIC) != 0) अणु
		काष्ठा	seeprom_descriptor sd;
		u_पूर्णांक	sxfrctl1;

		sd.sd_ahc = ahc;
		sd.sd_control_offset = SEECTL;		
		sd.sd_status_offset = SEECTL;		
		sd.sd_dataout_offset = SEECTL;		

		ahc_acquire_seeprom(ahc, &sd);
		configure_termination(ahc, &sd,
				      ahc->seep_config->adapter_control,
				      &sxfrctl1);
		ahc_release_seeprom(&sd);
	पूर्ण
पूर्ण

अटल पूर्णांक
ahc_aic785X_setup(काष्ठा ahc_softc *ahc)
अणु
	ahc_dev_softc_t pci;
	uपूर्णांक8_t rev;

	pci = ahc->dev_softc;
	ahc->channel = 'A';
	ahc->chip = AHC_AIC7850;
	ahc->features = AHC_AIC7850_FE;
	ahc->bugs |= AHC_TMODE_WIDEODD_BUG|AHC_CACHETHEN_BUG|AHC_PCI_MWI_BUG;
	rev = ahc_pci_पढ़ो_config(pci, PCIR_REVID, /*bytes*/1);
	अगर (rev >= 1)
		ahc->bugs |= AHC_PCI_2_1_RETRY_BUG;
	ahc->inकाष्ठाion_ram_size = 512;
	वापस (0);
पूर्ण

अटल पूर्णांक
ahc_aic7860_setup(काष्ठा ahc_softc *ahc)
अणु
	ahc_dev_softc_t pci;
	uपूर्णांक8_t rev;

	pci = ahc->dev_softc;
	ahc->channel = 'A';
	ahc->chip = AHC_AIC7860;
	ahc->features = AHC_AIC7860_FE;
	ahc->bugs |= AHC_TMODE_WIDEODD_BUG|AHC_CACHETHEN_BUG|AHC_PCI_MWI_BUG;
	rev = ahc_pci_पढ़ो_config(pci, PCIR_REVID, /*bytes*/1);
	अगर (rev >= 1)
		ahc->bugs |= AHC_PCI_2_1_RETRY_BUG;
	ahc->inकाष्ठाion_ram_size = 512;
	वापस (0);
पूर्ण

अटल पूर्णांक
ahc_apa1480_setup(काष्ठा ahc_softc *ahc)
अणु
	पूर्णांक error;

	error = ahc_aic7860_setup(ahc);
	अगर (error != 0)
		वापस (error);
	ahc->features |= AHC_REMOVABLE;
	वापस (0);
पूर्ण

अटल पूर्णांक
ahc_aic7870_setup(काष्ठा ahc_softc *ahc)
अणु

	ahc->channel = 'A';
	ahc->chip = AHC_AIC7870;
	ahc->features = AHC_AIC7870_FE;
	ahc->bugs |= AHC_TMODE_WIDEODD_BUG|AHC_CACHETHEN_BUG|AHC_PCI_MWI_BUG;
	ahc->inकाष्ठाion_ram_size = 512;
	वापस (0);
पूर्ण

अटल पूर्णांक
ahc_aic7870h_setup(काष्ठा ahc_softc *ahc)
अणु
	पूर्णांक error = ahc_aic7870_setup(ahc);

	ahc->features |= AHC_HVD;

	वापस error;
पूर्ण

अटल पूर्णांक
ahc_aha394X_setup(काष्ठा ahc_softc *ahc)
अणु
	पूर्णांक error;

	error = ahc_aic7870_setup(ahc);
	अगर (error == 0)
		error = ahc_aha394XX_setup(ahc);
	वापस (error);
पूर्ण

अटल पूर्णांक
ahc_aha394Xh_setup(काष्ठा ahc_softc *ahc)
अणु
	पूर्णांक error = ahc_aha394X_setup(ahc);

	ahc->features |= AHC_HVD;

	वापस error;
पूर्ण

अटल पूर्णांक
ahc_aha398X_setup(काष्ठा ahc_softc *ahc)
अणु
	पूर्णांक error;

	error = ahc_aic7870_setup(ahc);
	अगर (error == 0)
		error = ahc_aha398XX_setup(ahc);
	वापस (error);
पूर्ण

अटल पूर्णांक
ahc_aha494X_setup(काष्ठा ahc_softc *ahc)
अणु
	पूर्णांक error;

	error = ahc_aic7870_setup(ahc);
	अगर (error == 0)
		error = ahc_aha494XX_setup(ahc);
	वापस (error);
पूर्ण

अटल पूर्णांक
ahc_aha494Xh_setup(काष्ठा ahc_softc *ahc)
अणु
	पूर्णांक error = ahc_aha494X_setup(ahc);

	ahc->features |= AHC_HVD;

	वापस error;
पूर्ण

अटल पूर्णांक
ahc_aic7880_setup(काष्ठा ahc_softc *ahc)
अणु
	ahc_dev_softc_t pci;
	uपूर्णांक8_t rev;

	pci = ahc->dev_softc;
	ahc->channel = 'A';
	ahc->chip = AHC_AIC7880;
	ahc->features = AHC_AIC7880_FE;
	ahc->bugs |= AHC_TMODE_WIDEODD_BUG;
	rev = ahc_pci_पढ़ो_config(pci, PCIR_REVID, /*bytes*/1);
	अगर (rev >= 1) अणु
		ahc->bugs |= AHC_PCI_2_1_RETRY_BUG;
	पूर्ण अन्यथा अणु
		ahc->bugs |= AHC_CACHETHEN_BUG|AHC_PCI_MWI_BUG;
	पूर्ण
	ahc->inकाष्ठाion_ram_size = 512;
	वापस (0);
पूर्ण

अटल पूर्णांक
ahc_aic7880h_setup(काष्ठा ahc_softc *ahc)
अणु
	पूर्णांक error = ahc_aic7880_setup(ahc);

	ahc->features |= AHC_HVD;

	वापस error;
पूर्ण


अटल पूर्णांक
ahc_aha2940Pro_setup(काष्ठा ahc_softc *ahc)
अणु

	ahc->flags |= AHC_INT50_SPEEDFLEX;
	वापस (ahc_aic7880_setup(ahc));
पूर्ण

अटल पूर्णांक
ahc_aha394XU_setup(काष्ठा ahc_softc *ahc)
अणु
	पूर्णांक error;

	error = ahc_aic7880_setup(ahc);
	अगर (error == 0)
		error = ahc_aha394XX_setup(ahc);
	वापस (error);
पूर्ण

अटल पूर्णांक
ahc_aha394XUh_setup(काष्ठा ahc_softc *ahc)
अणु
	पूर्णांक error = ahc_aha394XU_setup(ahc);

	ahc->features |= AHC_HVD;

	वापस error;
पूर्ण

अटल पूर्णांक
ahc_aha398XU_setup(काष्ठा ahc_softc *ahc)
अणु
	पूर्णांक error;

	error = ahc_aic7880_setup(ahc);
	अगर (error == 0)
		error = ahc_aha398XX_setup(ahc);
	वापस (error);
पूर्ण

अटल पूर्णांक
ahc_aic7890_setup(काष्ठा ahc_softc *ahc)
अणु
	ahc_dev_softc_t pci;
	uपूर्णांक8_t rev;

	pci = ahc->dev_softc;
	ahc->channel = 'A';
	ahc->chip = AHC_AIC7890;
	ahc->features = AHC_AIC7890_FE;
	ahc->flags |= AHC_NEWEEPROM_FMT;
	rev = ahc_pci_पढ़ो_config(pci, PCIR_REVID, /*bytes*/1);
	अगर (rev == 0)
		ahc->bugs |= AHC_AUTOFLUSH_BUG|AHC_CACHETHEN_BUG;
	ahc->inकाष्ठाion_ram_size = 768;
	वापस (0);
पूर्ण

अटल पूर्णांक
ahc_aic7892_setup(काष्ठा ahc_softc *ahc)
अणु

	ahc->channel = 'A';
	ahc->chip = AHC_AIC7892;
	ahc->features = AHC_AIC7892_FE;
	ahc->flags |= AHC_NEWEEPROM_FMT;
	ahc->bugs |= AHC_SCBCHAN_UPLOAD_BUG;
	ahc->inकाष्ठाion_ram_size = 1024;
	वापस (0);
पूर्ण

अटल पूर्णांक
ahc_aic7895_setup(काष्ठा ahc_softc *ahc)
अणु
	ahc_dev_softc_t pci;
	uपूर्णांक8_t rev;

	pci = ahc->dev_softc;
	ahc->channel = ahc_get_pci_function(pci) == 1 ? 'B' : 'A';
	/*
	 * The 'C' revision of the aic7895 has a few additional features.
	 */
	rev = ahc_pci_पढ़ो_config(pci, PCIR_REVID, /*bytes*/1);
	अगर (rev >= 4) अणु
		ahc->chip = AHC_AIC7895C;
		ahc->features = AHC_AIC7895C_FE;
	पूर्ण अन्यथा  अणु
		u_पूर्णांक command;

		ahc->chip = AHC_AIC7895;
		ahc->features = AHC_AIC7895_FE;

		/*
		 * The BIOS disables the use of MWI transactions
		 * since it करोes not have the MWI bug work around
		 * we have.  Disabling MWI reduces perक्रमmance, so
		 * turn it on again.
		 */
		command = ahc_pci_पढ़ो_config(pci, PCIR_COMMAND, /*bytes*/1);
		command |= PCIM_CMD_MWRICEN;
		ahc_pci_ग_लिखो_config(pci, PCIR_COMMAND, command, /*bytes*/1);
		ahc->bugs |= AHC_PCI_MWI_BUG;
	पूर्ण
	/*
	 * XXX Does CACHETHEN really not work???  What about PCI retry?
	 * on C level chips.  Need to test, but क्रम now, play it safe.
	 */
	ahc->bugs |= AHC_TMODE_WIDEODD_BUG|AHC_PCI_2_1_RETRY_BUG
		  |  AHC_CACHETHEN_BUG;

#अगर 0
	uपूर्णांक32_t devconfig;

	/*
	 * Cachesize must also be zero due to stray DAC
	 * problem when sitting behind some bridges.
	 */
	ahc_pci_ग_लिखो_config(pci, CSIZE_LATTIME, 0, /*bytes*/1);
	devconfig = ahc_pci_पढ़ो_config(pci, DEVCONFIG, /*bytes*/1);
	devconfig |= MRDCEN;
	ahc_pci_ग_लिखो_config(pci, DEVCONFIG, devconfig, /*bytes*/1);
#पूर्ण_अगर
	ahc->flags |= AHC_NEWEEPROM_FMT;
	ahc->inकाष्ठाion_ram_size = 512;
	वापस (0);
पूर्ण

अटल पूर्णांक
ahc_aic7895h_setup(काष्ठा ahc_softc *ahc)
अणु
	पूर्णांक error = ahc_aic7895_setup(ahc);

	ahc->features |= AHC_HVD;

	वापस error;
पूर्ण

अटल पूर्णांक
ahc_aic7896_setup(काष्ठा ahc_softc *ahc)
अणु
	ahc_dev_softc_t pci;

	pci = ahc->dev_softc;
	ahc->channel = ahc_get_pci_function(pci) == 1 ? 'B' : 'A';
	ahc->chip = AHC_AIC7896;
	ahc->features = AHC_AIC7896_FE;
	ahc->flags |= AHC_NEWEEPROM_FMT;
	ahc->bugs |= AHC_CACHETHEN_DIS_BUG;
	ahc->inकाष्ठाion_ram_size = 768;
	वापस (0);
पूर्ण

अटल पूर्णांक
ahc_aic7899_setup(काष्ठा ahc_softc *ahc)
अणु
	ahc_dev_softc_t pci;

	pci = ahc->dev_softc;
	ahc->channel = ahc_get_pci_function(pci) == 1 ? 'B' : 'A';
	ahc->chip = AHC_AIC7899;
	ahc->features = AHC_AIC7899_FE;
	ahc->flags |= AHC_NEWEEPROM_FMT;
	ahc->bugs |= AHC_SCBCHAN_UPLOAD_BUG;
	ahc->inकाष्ठाion_ram_size = 1024;
	वापस (0);
पूर्ण

अटल पूर्णांक
ahc_aha29160C_setup(काष्ठा ahc_softc *ahc)
अणु
	पूर्णांक error;

	error = ahc_aic7899_setup(ahc);
	अगर (error != 0)
		वापस (error);
	ahc->features |= AHC_REMOVABLE;
	वापस (0);
पूर्ण

अटल पूर्णांक
ahc_raid_setup(काष्ठा ahc_softc *ahc)
अणु
	prपूर्णांकk("RAID functionality unsupported\n");
	वापस (ENXIO);
पूर्ण

अटल पूर्णांक
ahc_aha394XX_setup(काष्ठा ahc_softc *ahc)
अणु
	ahc_dev_softc_t pci;

	pci = ahc->dev_softc;
	चयन (ahc_get_pci_slot(pci)) अणु
	हाल AHC_394X_SLOT_CHANNEL_A:
		ahc->channel = 'A';
		अवरोध;
	हाल AHC_394X_SLOT_CHANNEL_B:
		ahc->channel = 'B';
		अवरोध;
	शेष:
		prपूर्णांकk("adapter at unexpected slot %d\n"
		       "unable to map to a channel\n",
		       ahc_get_pci_slot(pci));
		ahc->channel = 'A';
	पूर्ण
	वापस (0);
पूर्ण

अटल पूर्णांक
ahc_aha398XX_setup(काष्ठा ahc_softc *ahc)
अणु
	ahc_dev_softc_t pci;

	pci = ahc->dev_softc;
	चयन (ahc_get_pci_slot(pci)) अणु
	हाल AHC_398X_SLOT_CHANNEL_A:
		ahc->channel = 'A';
		अवरोध;
	हाल AHC_398X_SLOT_CHANNEL_B:
		ahc->channel = 'B';
		अवरोध;
	हाल AHC_398X_SLOT_CHANNEL_C:
		ahc->channel = 'C';
		अवरोध;
	शेष:
		prपूर्णांकk("adapter at unexpected slot %d\n"
		       "unable to map to a channel\n",
		       ahc_get_pci_slot(pci));
		ahc->channel = 'A';
		अवरोध;
	पूर्ण
	ahc->flags |= AHC_LARGE_SEEPROM;
	वापस (0);
पूर्ण

अटल पूर्णांक
ahc_aha494XX_setup(काष्ठा ahc_softc *ahc)
अणु
	ahc_dev_softc_t pci;

	pci = ahc->dev_softc;
	चयन (ahc_get_pci_slot(pci)) अणु
	हाल AHC_494X_SLOT_CHANNEL_A:
		ahc->channel = 'A';
		अवरोध;
	हाल AHC_494X_SLOT_CHANNEL_B:
		ahc->channel = 'B';
		अवरोध;
	हाल AHC_494X_SLOT_CHANNEL_C:
		ahc->channel = 'C';
		अवरोध;
	हाल AHC_494X_SLOT_CHANNEL_D:
		ahc->channel = 'D';
		अवरोध;
	शेष:
		prपूर्णांकk("adapter at unexpected slot %d\n"
		       "unable to map to a channel\n",
		       ahc_get_pci_slot(pci));
		ahc->channel = 'A';
	पूर्ण
	ahc->flags |= AHC_LARGE_SEEPROM;
	वापस (0);
पूर्ण
