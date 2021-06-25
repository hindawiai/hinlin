<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    msp3400.h - definition क्रम msp3400 inमाला_दो and outमाला_दो

    Copyright (C) 2006 Hans Verkuil (hverkuil@xs4all.nl)

*/

#अगर_अघोषित _MSP3400_H_
#घोषणा _MSP3400_H_

/* msp3400 routing
   ===============

   The msp3400 has a complicated routing scheme with many possible
   combinations. The details are all in the datasheets but I will try
   to give a लघु description here.

   Inमाला_दो
   ======

   There are 1) tuner inमाला_दो, 2) I2S inमाला_दो, 3) SCART inमाला_दो. You will have
   to select which tuner input to use and which SCART input to use. The
   selected tuner input, the selected SCART input and all I2S inमाला_दो go to
   the DSP (the tuner input first goes through the demodulator).

   The DSP handles things like volume, bass/treble, balance, and some chips
   have support क्रम surround sound. It has several outमाला_दो: MAIN, AUX, I2S
   and SCART1/2. Each output can select which DSP input to use. So the MAIN
   output can select the tuner input जबतक at the same समय the SCART1 output
   uses the I2S input.

   Outमाला_दो
   =======

   Most DSP outमाला_दो are also the outमाला_दो of the msp3400. However, the SCART
   outमाला_दो of the msp3400 can select which input to use: either the SCART1 or
   SCART2 output from the DSP, or the msp3400 SCART inमाला_दो, thus completely
   bypassing the DSP.

   Summary
   =======

   So to specअगरy a complete routing scheme क्रम the msp3400 you will have to
   specअगरy in the 'input' arg of the s_routing function:

   1) which tuner input to use
   2) which SCART input to use
   3) which DSP input to use क्रम each DSP output

   And in the 'output' arg of the s_routing function you specअगरy:

   1) which SCART input to use क्रम each SCART output

   Depending on how the msp is wired to the other components you can
   ignore or mute certain inमाला_दो or outमाला_दो.

   Also, depending on the msp version only a subset of the inमाला_दो or
   outमाला_दो may be present. At the end of this header some tables are
   added containing a list of what is available क्रम each msp version.
 */

/* Inमाला_दो to the DSP unit: two independent selections have to be made:
   1) the tuner (SIF) input
   2) the SCART input
   Bits 0-2 are used क्रम the SCART input select, bit 3 is used क्रम the tuner
   input, bits 4-7 are reserved.
 */

/* SCART input to DSP selection */
#घोषणा MSP_IN_SCART1		0  /* Pin SC1_IN */
#घोषणा MSP_IN_SCART2		1  /* Pin SC2_IN */
#घोषणा MSP_IN_SCART3		2  /* Pin SC3_IN */
#घोषणा MSP_IN_SCART4		3  /* Pin SC4_IN */
#घोषणा MSP_IN_MONO		6  /* Pin MONO_IN */
#घोषणा MSP_IN_MUTE		7  /* Mute DSP input */
#घोषणा MSP_SCART_TO_DSP(in)	(in)
/* Tuner input to demodulator and DSP selection */
#घोषणा MSP_IN_TUNER1		0  /* Analog Sound IF input pin ANA_IN1 */
#घोषणा MSP_IN_TUNER2		1  /* Analog Sound IF input pin ANA_IN2 */
#घोषणा MSP_TUNER_TO_DSP(in)	((in) << 3)

/* The msp has up to 5 DSP outमाला_दो, each output can independently select
   a DSP input.

   The DSP outमाला_दो are: loudspeaker output (aka MAIN), headphones output
   (aka AUX), SCART1 DA output, SCART2 DA output and an I2S output.
   There also is a quasi-peak detector output, but that is not used by
   this driver and is set to the same input as the loudspeaker output.
   Not all outमाला_दो are supported by all msp models. Setting the input
   of an unsupported output will be ignored by the driver.

   There are up to 16 DSP inमाला_दो to choose from, so each output is
   asचिन्हित 4 bits.

   Note: the 44x8G can mix two inमाला_दो and feed the result back to the
   DSP. This is currently not implemented. Also not implemented is the
   multi-channel capable I2S3 input of the 44x0G. If someone can demonstrate
   a need क्रम one of those features then additional support can be added. */
#घोषणा MSP_DSP_IN_TUNER	0  /* Tuner DSP input */
#घोषणा MSP_DSP_IN_SCART	2  /* SCART DSP input */
#घोषणा MSP_DSP_IN_I2S1		5  /* I2S1 DSP input */
#घोषणा MSP_DSP_IN_I2S2		6  /* I2S2 DSP input */
#घोषणा MSP_DSP_IN_I2S3		7  /* I2S3 DSP input */
#घोषणा MSP_DSP_IN_MAIN_AVC	11 /* MAIN AVC processed DSP input */
#घोषणा MSP_DSP_IN_MAIN		12 /* MAIN DSP input */
#घोषणा MSP_DSP_IN_AUX		13 /* AUX DSP input */
#घोषणा MSP_DSP_TO_MAIN(in)	((in) << 4)
#घोषणा MSP_DSP_TO_AUX(in)	((in) << 8)
#घोषणा MSP_DSP_TO_SCART1(in)	((in) << 12)
#घोषणा MSP_DSP_TO_SCART2(in)	((in) << 16)
#घोषणा MSP_DSP_TO_I2S(in)	((in) << 20)

/* Output SCART select: the SCART outमाला_दो can select which input
   to use. */
#घोषणा MSP_SC_IN_SCART1	0  /* SCART1 input, bypassing the DSP */
#घोषणा MSP_SC_IN_SCART2	1  /* SCART2 input, bypassing the DSP */
#घोषणा MSP_SC_IN_SCART3	2  /* SCART3 input, bypassing the DSP */
#घोषणा MSP_SC_IN_SCART4	3  /* SCART4 input, bypassing the DSP */
#घोषणा MSP_SC_IN_DSP_SCART1	4  /* DSP SCART1 input */
#घोषणा MSP_SC_IN_DSP_SCART2	5  /* DSP SCART2 input */
#घोषणा MSP_SC_IN_MONO		6  /* MONO input, bypassing the DSP */
#घोषणा MSP_SC_IN_MUTE		7  /* MUTE output */
#घोषणा MSP_SC_TO_SCART1(in)	(in)
#घोषणा MSP_SC_TO_SCART2(in)	((in) << 4)

/* Shortcut macros */
#घोषणा MSP_INPUT(sc, t, मुख्य_aux_src, sc_i2s_src) \
	(MSP_SCART_TO_DSP(sc) | \
	 MSP_TUNER_TO_DSP(t) | \
	 MSP_DSP_TO_MAIN(मुख्य_aux_src) | \
	 MSP_DSP_TO_AUX(मुख्य_aux_src) | \
	 MSP_DSP_TO_SCART1(sc_i2s_src) | \
	 MSP_DSP_TO_SCART2(sc_i2s_src) | \
	 MSP_DSP_TO_I2S(sc_i2s_src))
#घोषणा MSP_INPUT_DEFAULT MSP_INPUT(MSP_IN_SCART1, MSP_IN_TUNER1, \
				    MSP_DSP_IN_TUNER, MSP_DSP_IN_TUNER)
#घोषणा MSP_OUTPUT(sc) \
	(MSP_SC_TO_SCART1(sc) | \
	 MSP_SC_TO_SCART2(sc))
/* This equals the RESET position of the msp3400 ACB रेजिस्टर */
#घोषणा MSP_OUTPUT_DEFAULT (MSP_SC_TO_SCART1(MSP_SC_IN_SCART3) | \
			    MSP_SC_TO_SCART2(MSP_SC_IN_DSP_SCART1))

/* Tuner inमाला_दो vs. msp version */
/* Chip      TUNER_1   TUNER_2
   -------------------------
   msp34x0b  y         y
   msp34x0c  y         y
   msp34x0d  y         y
   msp34x5d  y         n
   msp34x7d  y         n
   msp34x0g  y         y
   msp34x1g  y         y
   msp34x2g  y         y
   msp34x5g  y         n
   msp34x7g  y         n
   msp44x0g  y         y
   msp44x8g  y         y
 */

/* SCART inमाला_दो vs. msp version */
/* Chip      SC1 SC2 SC3 SC4
   -------------------------
   msp34x0b  y   y   y   n
   msp34x0c  y   y   y   n
   msp34x0d  y   y   y   y
   msp34x5d  y   y   n   n
   msp34x7d  y   n   n   n
   msp34x0g  y   y   y   y
   msp34x1g  y   y   y   y
   msp34x2g  y   y   y   y
   msp34x5g  y   y   n   n
   msp34x7g  y   n   n   n
   msp44x0g  y   y   y   y
   msp44x8g  y   y   y   y
 */

/* DSP inमाला_दो vs. msp version (tuner and SCART inमाला_दो are always available) */
/* Chip      I2S1 I2S2 I2S3 MAIN_AVC MAIN AUX
   ------------------------------------------
   msp34x0b  y    n    n    n        n    n
   msp34x0c  y    y    n    n        n    n
   msp34x0d  y    y    n    n        n    n
   msp34x5d  y    y    n    n        n    n
   msp34x7d  n    n    n    n        n    n
   msp34x0g  y    y    n    n        n    n
   msp34x1g  y    y    n    n        n    n
   msp34x2g  y    y    n    y        y    y
   msp34x5g  y    y    n    n        n    n
   msp34x7g  n    n    n    n        n    n
   msp44x0g  y    y    y    y        y    y
   msp44x8g  y    y    y    n        n    n
 */

/* DSP outमाला_दो vs. msp version */
/* Chip      MAIN AUX SCART1 SCART2 I2S
   ------------------------------------
   msp34x0b  y    y   y      n      y
   msp34x0c  y    y   y      n      y
   msp34x0d  y    y   y      y      y
   msp34x5d  y    n   y      n      y
   msp34x7d  y    n   y      n      n
   msp34x0g  y    y   y      y      y
   msp34x1g  y    y   y      y      y
   msp34x2g  y    y   y      y      y
   msp34x5g  y    n   y      n      y
   msp34x7g  y    n   y      n      n
   msp44x0g  y    y   y      y      y
   msp44x8g  y    y   y      y      y
 */

#पूर्ण_अगर /* MSP3400_H */
