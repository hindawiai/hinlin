<शैली गुरु>
/*
 * drivers/video/clgenfb.h - Cirrus Logic chipset स्थिरants
 *
 * Copyright 1999 Jeff Garzik <jgarzik@pobox.com>
 *
 * Original clgenfb author:  Frank Neumann
 *
 * Based on retz3fb.c and clgen.c:
 *      Copyright (C) 1997 Jes Sorensen
 *      Copyright (C) 1996 Frank Neumann
 *
 ***************************************************************
 *
 * Format this code with GNU indent '-kr -i8 -pcs' options.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 *
 */

#अगर_अघोषित __CLGENFB_H__
#घोषणा __CLGENFB_H__

/* OLD COMMENT: definitions क्रम Piccolo/SD64 VGA controller chip   */
/* OLD COMMENT: these definitions might most of the समय also work */
/* OLD COMMENT: क्रम other CL-GD542x/543x based boards..            */

/*** External/General Registers ***/
#घोषणा CL_POS102	0x102  	/* POS102 रेजिस्टर */
#घोषणा CL_VSSM		0x46e8 	/* Adapter Sleep */
#घोषणा CL_VSSM2	0x3c3	/* Motherboard Sleep */

/*** VGA Sequencer Registers ***/
/* the following are from the "extension registers" group */
#घोषणा CL_SEQR6	0x6	/* Unlock ALL Extensions */
#घोषणा CL_SEQR7	0x7	/* Extended Sequencer Mode */
#घोषणा CL_SEQR8	0x8	/* EEPROM Control */
#घोषणा CL_SEQR9	0x9	/* Scratch Pad 0 (करो not access!) */
#घोषणा CL_SEQRA	0xa	/* Scratch Pad 1 (करो not access!) */
#घोषणा CL_SEQRB	0xb	/* VCLK0 Numerator */
#घोषणा CL_SEQRC	0xc	/* VCLK1 Numerator */
#घोषणा CL_SEQRD	0xd	/* VCLK2 Numerator */
#घोषणा CL_SEQRE	0xe	/* VCLK3 Numerator */
#घोषणा CL_SEQRF	0xf	/* DRAM Control */
#घोषणा CL_SEQR10	0x10	/* Graphics Cursor X Position */
#घोषणा CL_SEQR11	0x11	/* Graphics Cursor Y Position */
#घोषणा CL_SEQR12	0x12	/* Graphics Cursor Attributes */
#घोषणा CL_SEQR13	0x13	/* Graphics Cursor Pattern Address Offset */
#घोषणा CL_SEQR14	0x14	/* Scratch Pad 2 (CL-GD5426/'28 Only) (करो not access!) */
#घोषणा CL_SEQR15	0x15	/* Scratch Pad 3 (CL-GD5426/'28 Only) (करो not access!) */
#घोषणा CL_SEQR16	0x16	/* Perक्रमmance Tuning (CL-GD5424/'26/'28 Only) */
#घोषणा CL_SEQR17	0x17	/* Configuration ReadBack and Extended Control (CL-GF5428 Only) */
#घोषणा CL_SEQR18	0x18	/* Signature Generator Control (Not CL-GD5420) */
#घोषणा CL_SEQR19	0x19	/* Signature Generator Result Low Byte (Not CL-GD5420) */
#घोषणा CL_SEQR1A	0x1a	/* Signature Generator Result High Byte (Not CL-GD5420) */
#घोषणा CL_SEQR1B	0x1b	/* VCLK0 Denominator and Post-Scalar Value */
#घोषणा CL_SEQR1C	0x1c	/* VCLK1 Denominator and Post-Scalar Value */
#घोषणा CL_SEQR1D	0x1d	/* VCLK2 Denominator and Post-Scalar Value */
#घोषणा CL_SEQR1E	0x1e	/* VCLK3 Denominator and Post-Scalar Value */
#घोषणा CL_SEQR1F	0x1f	/* BIOS ROM ग_लिखो enable and MCLK Select */

/*** CRT Controller Registers ***/
#घोषणा CL_CRT22	0x22	/* Graphics Data Latches ReadBack */
#घोषणा CL_CRT24	0x24	/* Attribute Controller Toggle ReadBack */
#घोषणा CL_CRT26	0x26	/* Attribute Controller Index ReadBack */
/* the following are from the "extension registers" group */
#घोषणा CL_CRT19	0x19	/* Interlace End */
#घोषणा CL_CRT1A	0x1a	/* Interlace Control */
#घोषणा CL_CRT1B	0x1b	/* Extended Display Controls */
#घोषणा CL_CRT1C	0x1c	/* Sync adjust and genlock रेजिस्टर */
#घोषणा CL_CRT1D	0x1d	/* Overlay Extended Control रेजिस्टर */
#घोषणा CL_CRT1E	0x1e	/* Another overflow रेजिस्टर */
#घोषणा CL_CRT25	0x25	/* Part Status Register */
#घोषणा CL_CRT27	0x27	/* ID Register */
#घोषणा CL_CRT51	0x51	/* P4 disable "flicker fixer" */

/*** Graphics Controller Registers ***/
/* the following are from the "extension registers" group */
#घोषणा CL_GR9		0x9	/* Offset Register 0 */
#घोषणा CL_GRA		0xa	/* Offset Register 1 */
#घोषणा CL_GRB		0xb	/* Graphics Controller Mode Extensions */
#घोषणा CL_GRC		0xc	/* Color Key (CL-GD5424/'26/'28 Only) */
#घोषणा CL_GRD		0xd	/* Color Key Mask (CL-GD5424/'26/'28 Only) */
#घोषणा CL_GRE		0xe	/* Miscellaneous Control (Cl-GD5428 Only) */
#घोषणा CL_GRF		0xf	/* Display Compression Control रेजिस्टर */
#घोषणा CL_GR10		0x10	/* 16-bit Pixel BG Color High Byte (Not CL-GD5420) */
#घोषणा CL_GR11		0x11	/* 16-bit Pixel FG Color High Byte (Not CL-GD5420) */
#घोषणा CL_GR12		0x12	/* Background Color Byte 2 Register */
#घोषणा CL_GR13		0x13	/* Foreground Color Byte 2 Register */
#घोषणा CL_GR14		0x14	/* Background Color Byte 3 Register */
#घोषणा CL_GR15		0x15	/* Foreground Color Byte 3 Register */
/* the following are CL-GD5426/'28 specअगरic blitter रेजिस्टरs */
#घोषणा CL_GR20		0x20	/* BLT Width Low */
#घोषणा CL_GR21		0x21	/* BLT Width High */
#घोषणा CL_GR22		0x22	/* BLT Height Low */
#घोषणा CL_GR23		0x23	/* BLT Height High */
#घोषणा CL_GR24		0x24	/* BLT Destination Pitch Low */
#घोषणा CL_GR25		0x25	/* BLT Destination Pitch High */
#घोषणा CL_GR26		0x26	/* BLT Source Pitch Low */
#घोषणा CL_GR27		0x27	/* BLT Source Pitch High */
#घोषणा CL_GR28		0x28	/* BLT Destination Start Low */
#घोषणा CL_GR29		0x29	/* BLT Destination Start Mid */
#घोषणा CL_GR2A		0x2a	/* BLT Destination Start High */
#घोषणा CL_GR2C		0x2c	/* BLT Source Start Low */
#घोषणा CL_GR2D		0x2d	/* BLT Source Start Mid */
#घोषणा CL_GR2E		0x2e	/* BLT Source Start High */
#घोषणा CL_GR2F		0x2f	/* Picasso IV Blitter compat mode..? */
#घोषणा CL_GR30		0x30	/* BLT Mode */
#घोषणा CL_GR31		0x31	/* BLT Start/Status */
#घोषणा CL_GR32		0x32	/* BLT Raster Operation */
#घोषणा CL_GR33		0x33	/* another P4 "compat" रेजिस्टर.. */
#घोषणा CL_GR34		0x34	/* Transparent Color Select Low */
#घोषणा CL_GR35		0x35	/* Transparent Color Select High */
#घोषणा CL_GR38		0x38	/* Source Transparent Color Mask Low */
#घोषणा CL_GR39		0x39	/* Source Transparent Color Mask High */

/*** Attribute Controller Registers ***/
#घोषणा CL_AR33		0x33	/* The "real" Pixel Panning रेजिस्टर (?) */
#घोषणा CL_AR34		0x34	/* TEST */

#पूर्ण_अगर /* __CLGENFB_H__ */
