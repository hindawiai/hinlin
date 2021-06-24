<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2008, Creative Technology Ltd. All Rights Reserved.
 */

#अगर_अघोषित _20K2REGISTERS_H_
#घोषणा _20K2REGISTERS_H_


/* Timer Registers */
#घोषणा WC		0x1b7000
#घोषणा TIMR		0x1b7004
# define	TIMR_IE		(1<<15)
# define	TIMR_IP		(1<<14)
#घोषणा GIP		0x1b7010
#घोषणा GIE		0x1b7014

/* I2C Registers */
#घोषणा I2C_IF_ADDRESS   0x1B9000
#घोषणा I2C_IF_WDATA     0x1B9004
#घोषणा I2C_IF_RDATA     0x1B9008
#घोषणा I2C_IF_STATUS    0x1B900C
#घोषणा I2C_IF_WLOCK     0x1B9010

/* Global Control Registers */
#घोषणा GLOBAL_CNTL_GCTL    0x1B7090

/* PLL Registers */
#घोषणा PLL_CTL 		0x1B7080
#घोषणा PLL_STAT		0x1B7084
#घोषणा PLL_ENB			0x1B7088

/* SRC Registers */
#घोषणा SRC_CTL             0x1A0000 /* 0x1A0000 + (256 * Chn) */
#घोषणा SRC_CCR             0x1A0004 /* 0x1A0004 + (256 * Chn) */
#घोषणा SRC_IMAP            0x1A0008 /* 0x1A0008 + (256 * Chn) */
#घोषणा SRC_CA              0x1A0010 /* 0x1A0010 + (256 * Chn) */
#घोषणा SRC_CF              0x1A0014 /* 0x1A0014 + (256 * Chn) */
#घोषणा SRC_SA              0x1A0018 /* 0x1A0018 + (256 * Chn) */
#घोषणा SRC_LA              0x1A001C /* 0x1A001C + (256 * Chn) */
#घोषणा SRC_CTLSWR	    0x1A0020 /* 0x1A0020 + (256 * Chn) */
#घोषणा SRC_CD		    0x1A0080 /* 0x1A0080 + (256 * Chn) + (4 * Regn) */
#घोषणा SRC_MCTL		0x1A012C
#घोषणा SRC_IP			0x1A102C /* 0x1A102C + (256 * Regn) */
#घोषणा SRC_ENB			0x1A282C /* 0x1A282C + (256 * Regn) */
#घोषणा SRC_ENBSTAT		0x1A202C
#घोषणा SRC_ENBSA		0x1A232C
#घोषणा SRC_DN0Z		0x1A0030
#घोषणा SRC_DN1Z		0x1A0040
#घोषणा SRC_UPZ			0x1A0060

/* GPIO Registers */
#घोषणा GPIO_DATA           0x1B7020
#घोषणा GPIO_CTRL           0x1B7024
#घोषणा GPIO_EXT_DATA       0x1B70A0

/* Virtual memory रेजिस्टरs */
#घोषणा VMEM_PTPAL          0x1C6300 /* 0x1C6300 + (16 * Chn) */
#घोषणा VMEM_PTPAH          0x1C6304 /* 0x1C6304 + (16 * Chn) */
#घोषणा VMEM_CTL            0x1C7000

/* Transport Registers */
#घोषणा TRANSPORT_ENB       0x1B6000
#घोषणा TRANSPORT_CTL       0x1B6004
#घोषणा TRANSPORT_INT       0x1B6008

/* Audio IO */
#घोषणा AUDIO_IO_AIM        0x1B5000 /* 0x1B5000 + (0x04 * Chn) */
#घोषणा AUDIO_IO_TX_CTL     0x1B5400 /* 0x1B5400 + (0x40 * Chn) */
#घोषणा AUDIO_IO_TX_CSTAT_L 0x1B5408 /* 0x1B5408 + (0x40 * Chn) */
#घोषणा AUDIO_IO_TX_CSTAT_H 0x1B540C /* 0x1B540C + (0x40 * Chn) */
#घोषणा AUDIO_IO_RX_CTL     0x1B5410 /* 0x1B5410 + (0x40 * Chn) */
#घोषणा AUDIO_IO_RX_SRT_CTL 0x1B5420 /* 0x1B5420 + (0x40 * Chn) */
#घोषणा AUDIO_IO_MCLK       0x1B5600
#घोषणा AUDIO_IO_TX_BLRCLK  0x1B5604
#घोषणा AUDIO_IO_RX_BLRCLK  0x1B5608

/* Mixer */
#घोषणा MIXER_AMOPLO		0x130000 /* 0x130000 + (8 * Chn) [4095 : 0] */
#घोषणा MIXER_AMOPHI		0x130004 /* 0x130004 + (8 * Chn) [4095 : 0] */
#घोषणा MIXER_PRING_LO_HI	0x188000 /* 0x188000 + (4 * Chn) [4095 : 0] */
#घोषणा MIXER_PMOPLO		0x138000 /* 0x138000 + (8 * Chn) [4095 : 0] */
#घोषणा MIXER_PMOPHI		0x138004 /* 0x138004 + (8 * Chn) [4095 : 0] */
#घोषणा MIXER_AR_ENABLE		0x19000C

#पूर्ण_अगर
