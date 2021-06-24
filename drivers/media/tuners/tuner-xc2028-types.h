<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * tuner-xc2028_types
 *
 * This file includes पूर्णांकernal tipes to be used inside tuner-xc2028.
 * Shouldn't be included outside tuner-xc2028
 *
 * Copyright (c) 2007-2008 Mauro Carvalho Chehab <mchehab@kernel.org>
 */

/* xc3028 firmware types */

/* BASE firmware should be loaded beक्रमe any other firmware */
#घोषणा BASE		(1<<0)
#घोषणा BASE_TYPES	(BASE|F8MHZ|MTS|FM|INPUT1|INPUT2|INIT1)

/* F8MHZ marks BASE firmwares क्रम 8 MHz Bandwidth */
#घोषणा F8MHZ		(1<<1)

/* Multichannel Television Sound (MTS)
   Those firmwares are capable of using xc2038 DSP to decode audio and
   produce a baseband audio output on some pins of the chip.
   There are MTS firmwares क्रम the most used video standards. It should be
   required to use MTS firmwares, depending on the way audio is routed पूर्णांकo
   the bridge chip
 */
#घोषणा MTS		(1<<2)

/* FIXME: I have no idea what's the dअगरference between
   D2620 and D2633 firmwares
 */
#घोषणा D2620		(1<<3)
#घोषणा D2633		(1<<4)

/* DTV firmwares क्रम 6, 7 and 8 MHz
   DTV6 - 6MHz - ATSC/DVB-C/DVB-T/ISDB-T/DOCSIS
   DTV8 - 8MHz - DVB-C/DVB-T
 */
#घोषणा DTV6           (1 << 5)
#घोषणा QAM            (1 << 6)
#घोषणा DTV7		(1<<7)
#घोषणा DTV78		(1<<8)
#घोषणा DTV8		(1<<9)

#घोषणा DTV_TYPES	(D2620|D2633|DTV6|QAM|DTV7|DTV78|DTV8|ATSC)

/* There's a FM | BASE firmware + FM specअगरic firmware (std=0) */
#घोषणा	FM		(1<<10)

#घोषणा STD_SPECIFIC_TYPES (MTS|FM|LCD|NOGD)

/* Applies only क्रम FM firmware
   Makes it use RF input 1 (pin #2) instead of input 2 (pin #4)
 */
#घोषणा INPUT1		(1<<11)


/* LCD firmwares exist only क्रम MTS STD/MN (PAL or NTSC/M)
	and क्रम non-MTS STD/MN (PAL, NTSC/M or NTSC/Kr)
	There are variants both with and without NOGD
	Those firmwares produce better result with LCD displays
 */
#घोषणा LCD		(1<<12)

/* NOGD firmwares exist only क्रम MTS STD/MN (PAL or NTSC/M)
	and क्रम non-MTS STD/MN (PAL, NTSC/M or NTSC/Kr)
	The NOGD firmwares करोn't have group delay compensation filter
 */
#घोषणा NOGD		(1<<13)

/* Old firmwares were broken पूर्णांकo init0 and init1 */
#घोषणा INIT1		(1<<14)

/* SCODE firmware selects particular behaviours */
#घोषणा MONO           (1 << 15)
#घोषणा ATSC           (1 << 16)
#घोषणा IF             (1 << 17)
#घोषणा LG60           (1 << 18)
#घोषणा ATI638         (1 << 19)
#घोषणा OREN538        (1 << 20)
#घोषणा OREN36         (1 << 21)
#घोषणा TOYOTA388      (1 << 22)
#घोषणा TOYOTA794      (1 << 23)
#घोषणा DIBCOM52       (1 << 24)
#घोषणा ZARLINK456     (1 << 25)
#घोषणा CHINA          (1 << 26)
#घोषणा F6MHZ          (1 << 27)
#घोषणा INPUT2         (1 << 28)
#घोषणा SCODE          (1 << 29)

/* This flag identअगरies that the scode table has a new क्रमmat */
#घोषणा HAS_IF         (1 << 30)

/* There are dअगरferent scode tables क्रम MTS and non-MTS.
   The MTS firmwares support mono only
  */
#घोषणा SCODE_TYPES (SCODE | MTS)


/* Newer types not defined on videodev2.h.
   The original idea were to move all those types to videodev2.h, but
   it seemed overसमाप्त, since, with the exception of SECAM/K3, the other
   types seem to be स्वतःdetected.
   It is not clear where secam/k3 is used, nor we have a feedback of this
   working or being स्वतःdetected by the standard secam firmware.
 */

#घोषणा V4L2_STD_SECAM_K3	(0x04000000)

/* Audio types */

#घोषणा V4L2_STD_A2_A		(1LL<<32)
#घोषणा V4L2_STD_A2_B		(1LL<<33)
#घोषणा V4L2_STD_NICAM_A	(1LL<<34)
#घोषणा V4L2_STD_NICAM_B	(1LL<<35)
#घोषणा V4L2_STD_AM		(1LL<<36)
#घोषणा V4L2_STD_BTSC		(1LL<<37)
#घोषणा V4L2_STD_EIAJ		(1LL<<38)

#घोषणा V4L2_STD_A2		(V4L2_STD_A2_A    | V4L2_STD_A2_B)
#घोषणा V4L2_STD_NICAM		(V4L2_STD_NICAM_A | V4L2_STD_NICAM_B)

/* To preserve backward compatibility,
   (std & V4L2_STD_AUDIO) = 0 means that ALL audio stds are supported
 */

#घोषणा V4L2_STD_AUDIO		(V4L2_STD_A2    | \
				 V4L2_STD_NICAM | \
				 V4L2_STD_AM    | \
				 V4L2_STD_BTSC  | \
				 V4L2_STD_EIAJ)

/* Used standards with audio restrictions */

#घोषणा V4L2_STD_PAL_BG_A2_A	(V4L2_STD_PAL_BG | V4L2_STD_A2_A)
#घोषणा V4L2_STD_PAL_BG_A2_B	(V4L2_STD_PAL_BG | V4L2_STD_A2_B)
#घोषणा V4L2_STD_PAL_BG_NICAM_A	(V4L2_STD_PAL_BG | V4L2_STD_NICAM_A)
#घोषणा V4L2_STD_PAL_BG_NICAM_B	(V4L2_STD_PAL_BG | V4L2_STD_NICAM_B)
#घोषणा V4L2_STD_PAL_DK_A2	(V4L2_STD_PAL_DK | V4L2_STD_A2)
#घोषणा V4L2_STD_PAL_DK_NICAM	(V4L2_STD_PAL_DK | V4L2_STD_NICAM)
#घोषणा V4L2_STD_SECAM_L_NICAM	(V4L2_STD_SECAM_L | V4L2_STD_NICAM)
#घोषणा V4L2_STD_SECAM_L_AM	(V4L2_STD_SECAM_L | V4L2_STD_AM)
