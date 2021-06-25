<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित _LMC_IOCTL_H_
#घोषणा _LMC_IOCTL_H_
/*	$Id: lmc_ioctl.h,v 1.15 2000/04/06 12:16:43 asj Exp $	*/

 /*
  * Copyright (c) 1997-2000 LAN Media Corporation (LMC)
  * All rights reserved.  www.lanmedia.com
  *
  * This code is written by:
  * Andrew Stanley-Jones (asj@cban.com)
  * Rob Braun (bbraun@vix.com),
  * Michael Graff (explorer@vix.com) and
  * Matt Thomas (matt@3am-software.com).
  */

#घोषणा LMCIOCGINFO             SIOCDEVPRIVATE+3 /* get current state */
#घोषणा LMCIOCSINFO             SIOCDEVPRIVATE+4 /* set state to user values */
#घोषणा LMCIOCGETLMCSTATS       SIOCDEVPRIVATE+5
#घोषणा LMCIOCCLEARLMCSTATS     SIOCDEVPRIVATE+6
#घोषणा LMCIOCDUMPEVENTLOG      SIOCDEVPRIVATE+7
#घोषणा LMCIOCGETXINFO          SIOCDEVPRIVATE+8
#घोषणा LMCIOCSETCIRCUIT        SIOCDEVPRIVATE+9
#घोषणा LMCIOCUNUSEDATM         SIOCDEVPRIVATE+10
#घोषणा LMCIOCRESET             SIOCDEVPRIVATE+11
#घोषणा LMCIOCT1CONTROL         SIOCDEVPRIVATE+12
#घोषणा LMCIOCIFTYPE            SIOCDEVPRIVATE+13
#घोषणा LMCIOCXILINX            SIOCDEVPRIVATE+14

#घोषणा LMC_CARDTYPE_UNKNOWN            -1
#घोषणा LMC_CARDTYPE_HSSI               1       /* probed card is a HSSI card */
#घोषणा LMC_CARDTYPE_DS3                2       /* probed card is a DS3 card */
#घोषणा LMC_CARDTYPE_SSI                3       /* probed card is a SSI card */
#घोषणा LMC_CARDTYPE_T1                 4       /* probed card is a T1 card */

#घोषणा LMC_CTL_CARDTYPE_LMC5200	0	/* HSSI */
#घोषणा LMC_CTL_CARDTYPE_LMC5245	1	/* DS3 */
#घोषणा LMC_CTL_CARDTYPE_LMC1000	2	/* SSI, V.35 */
#घोषणा LMC_CTL_CARDTYPE_LMC1200        3       /* DS1 */

#घोषणा LMC_CTL_OFF			0	/* generic OFF value */
#घोषणा LMC_CTL_ON			1	/* generic ON value */

#घोषणा LMC_CTL_CLOCK_SOURCE_EXT	0	/* घड़ी off line */
#घोषणा LMC_CTL_CLOCK_SOURCE_INT	1	/* पूर्णांकernal घड़ी */

#घोषणा LMC_CTL_CRC_LENGTH_16		16
#घोषणा LMC_CTL_CRC_LENGTH_32		32
#घोषणा LMC_CTL_CRC_BYTESIZE_2          2
#घोषणा LMC_CTL_CRC_BYTESIZE_4          4


#घोषणा LMC_CTL_CABLE_LENGTH_LT_100FT	0	/* DS3 cable < 100 feet */
#घोषणा LMC_CTL_CABLE_LENGTH_GT_100FT	1	/* DS3 cable >= 100 feet */

#घोषणा LMC_CTL_CIRCUIT_TYPE_E1 0
#घोषणा LMC_CTL_CIRCUIT_TYPE_T1 1

/*
 * IFTYPE defines
 */
#घोषणा LMC_PPP         1               /* use generic HDLC पूर्णांकerface */
#घोषणा LMC_NET         2               /* use direct net पूर्णांकerface */
#घोषणा LMC_RAW         3               /* use direct net पूर्णांकerface */

/*
 * These are not in the least IOCTL related, but I want them common.
 */
/*
 * assignments क्रम the GPIO रेजिस्टर on the DEC chip (common)
 */
#घोषणा LMC_GEP_INIT		0x01 /* 0: */
#घोषणा LMC_GEP_RESET		0x02 /* 1: */
#घोषणा LMC_GEP_MODE		0x10 /* 4: */
#घोषणा LMC_GEP_DP		0x20 /* 5: */
#घोषणा LMC_GEP_DATA		0x40 /* 6: serial out */
#घोषणा LMC_GEP_CLK	        0x80 /* 7: serial घड़ी */

/*
 * HSSI GPIO assignments
 */
#घोषणा LMC_GEP_HSSI_ST		0x04 /* 2: receive timing sense (deprecated) */
#घोषणा LMC_GEP_HSSI_CLOCK	0x08 /* 3: घड़ी source */

/*
 * T1 GPIO assignments
 */
#घोषणा LMC_GEP_SSI_GENERATOR	0x04 /* 2: enable prog freq gen serial i/f */
#घोषणा LMC_GEP_SSI_TXCLOCK	0x08 /* 3: provide घड़ी on TXCLOCK output */

/*
 * Common MII16 bits
 */
#घोषणा LMC_MII16_LED0         0x0080
#घोषणा LMC_MII16_LED1         0x0100
#घोषणा LMC_MII16_LED2         0x0200
#घोषणा LMC_MII16_LED3         0x0400  /* Error, and the red one */
#घोषणा LMC_MII16_LED_ALL      0x0780  /* LED bit mask */
#घोषणा LMC_MII16_FIFO_RESET   0x0800

/*
 * definitions क्रम HSSI
 */
#घोषणा LMC_MII16_HSSI_TA      0x0001
#घोषणा LMC_MII16_HSSI_CA      0x0002
#घोषणा LMC_MII16_HSSI_LA      0x0004
#घोषणा LMC_MII16_HSSI_LB      0x0008
#घोषणा LMC_MII16_HSSI_LC      0x0010
#घोषणा LMC_MII16_HSSI_TM      0x0020
#घोषणा LMC_MII16_HSSI_CRC     0x0040

/*
 * assignments क्रम the MII रेजिस्टर 16 (DS3)
 */
#घोषणा LMC_MII16_DS3_ZERO	0x0001
#घोषणा LMC_MII16_DS3_TRLBK	0x0002
#घोषणा LMC_MII16_DS3_LNLBK	0x0004
#घोषणा LMC_MII16_DS3_RAIS	0x0008
#घोषणा LMC_MII16_DS3_TAIS	0x0010
#घोषणा LMC_MII16_DS3_BIST	0x0020
#घोषणा LMC_MII16_DS3_DLOS	0x0040
#घोषणा LMC_MII16_DS3_CRC	0x1000
#घोषणा LMC_MII16_DS3_SCRAM	0x2000
#घोषणा LMC_MII16_DS3_SCRAM_LARS 0x4000

/* Note: 2 pairs of LEDs where swapped by mistake
 * in Xilinx code क्रम DS3 & DS1 adapters */
#घोषणा LMC_DS3_LED0    0x0100          /* bit 08  yellow */
#घोषणा LMC_DS3_LED1    0x0080          /* bit 07  blue   */
#घोषणा LMC_DS3_LED2    0x0400          /* bit 10  green  */
#घोषणा LMC_DS3_LED3    0x0200          /* bit 09  red    */

/*
 * framer रेजिस्टर 0 and 7 (7 is latched and reset on पढ़ो)
 */
#घोषणा LMC_FRAMER_REG0_DLOS            0x80    /* digital loss of service */
#घोषणा LMC_FRAMER_REG0_OOFS            0x40    /* out of frame sync */
#घोषणा LMC_FRAMER_REG0_AIS             0x20    /* alarm indication संकेत */
#घोषणा LMC_FRAMER_REG0_CIS             0x10    /* channel idle */
#घोषणा LMC_FRAMER_REG0_LOC             0x08    /* loss of घड़ी */

/*
 * Framer रेजिस्टर 9 contains the blue alarm संकेत
 */
#घोषणा LMC_FRAMER_REG9_RBLUE          0x02     /* Blue alarm failure */

/*
 * Framer रेजिस्टर 0x10 contains xbit error
 */
#घोषणा LMC_FRAMER_REG10_XBIT          0x01     /* X bit error alarm failure */

/*
 * And SSI, LMC1000
 */
#घोषणा LMC_MII16_SSI_DTR	0x0001	/* DTR output RW */
#घोषणा LMC_MII16_SSI_DSR	0x0002	/* DSR input RO */
#घोषणा LMC_MII16_SSI_RTS	0x0004	/* RTS output RW */
#घोषणा LMC_MII16_SSI_CTS	0x0008	/* CTS input RO */
#घोषणा LMC_MII16_SSI_DCD	0x0010	/* DCD input RO */
#घोषणा LMC_MII16_SSI_RI		0x0020	/* RI input RO */
#घोषणा LMC_MII16_SSI_CRC                0x1000  /* CRC select - RW */

/*
 * bits 0x0080 through 0x0800 are generic, and described
 * above with LMC_MII16_LED[0123] _LED_ALL, and _FIFO_RESET
 */
#घोषणा LMC_MII16_SSI_LL		0x1000	/* LL output RW */
#घोषणा LMC_MII16_SSI_RL		0x2000	/* RL output RW */
#घोषणा LMC_MII16_SSI_TM		0x4000	/* TM input RO */
#घोषणा LMC_MII16_SSI_LOOP	0x8000	/* loopback enable RW */

/*
 * Some of the MII16 bits are mirrored in the MII17 रेजिस्टर as well,
 * but let's keep thing separate क्रम now, and get only the cable from
 * the MII17.
 */
#घोषणा LMC_MII17_SSI_CABLE_MASK	0x0038	/* mask to extract the cable type */
#घोषणा LMC_MII17_SSI_CABLE_SHIFT 3	/* shअगरt to extract the cable type */

/*
 * And T1, LMC1200
 */
#घोषणा LMC_MII16_T1_UNUSED1    0x0003
#घोषणा LMC_MII16_T1_XOE                0x0004
#घोषणा LMC_MII16_T1_RST                0x0008  /* T1 chip reset - RW */
#घोषणा LMC_MII16_T1_Z                  0x0010  /* output impedance T1=1, E1=0 output - RW */
#घोषणा LMC_MII16_T1_INTR               0x0020  /* पूर्णांकerrupt from 8370 - RO */
#घोषणा LMC_MII16_T1_ONESEC             0x0040  /* one second square wave - ro */

#घोषणा LMC_MII16_T1_LED0               0x0100
#घोषणा LMC_MII16_T1_LED1               0x0080
#घोषणा LMC_MII16_T1_LED2               0x0400
#घोषणा LMC_MII16_T1_LED3               0x0200
#घोषणा LMC_MII16_T1_FIFO_RESET 0x0800

#घोषणा LMC_MII16_T1_CRC                0x1000  /* CRC select - RW */
#घोषणा LMC_MII16_T1_UNUSED2    0xe000


/* 8370 framer रेजिस्टरs  */

#घोषणा T1FRAMER_ALARM1_STATUS  0x47
#घोषणा T1FRAMER_ALARM2_STATUS  0x48
#घोषणा T1FRAMER_FERR_LSB               0x50
#घोषणा T1FRAMER_FERR_MSB               0x51    /* framing bit error counter */
#घोषणा T1FRAMER_LCV_LSB                0x54
#घोषणा T1FRAMER_LCV_MSB                0x55    /* line code violation counter */
#घोषणा T1FRAMER_AERR                   0x5A

/* mask क्रम the above AERR रेजिस्टर */
#घोषणा T1FRAMER_LOF_MASK               (0x0f0) /* receive loss of frame */
#घोषणा T1FRAMER_COFA_MASK              (0x0c0) /* change of frame alignment */
#घोषणा T1FRAMER_SEF_MASK               (0x03)  /* severely errored frame  */

/* 8370 framer रेजिस्टर ALM1 (0x47) values
 * used to determine link status
 */

#घोषणा T1F_SIGFRZ      0x01    /* संकेतing मुक्तze */
#घोषणा T1F_RLOF        0x02    /* receive loss of frame alignment */
#घोषणा T1F_RLOS        0x04    /* receive loss of संकेत */
#घोषणा T1F_RALOS       0x08    /* receive analog loss of संकेत or RCKI loss of घड़ी */
#घोषणा T1F_RAIS        0x10    /* receive alarm indication संकेत */
#घोषणा T1F_UNUSED      0x20
#घोषणा T1F_RYEL        0x40    /* receive yellow alarm */
#घोषणा T1F_RMYEL       0x80    /* receive multअगरrame yellow alarm */

#घोषणा LMC_T1F_WRITE       0
#घोषणा LMC_T1F_READ        1

प्रकार काष्ठा lmc_st1f_control अणु
  पूर्णांक command;
  पूर्णांक address;
  पूर्णांक value;
  अक्षर __user *data;
पूर्ण lmc_t1f_control;

क्रमागत lmc_xilinx_c अणु
    lmc_xilinx_reset = 1,
    lmc_xilinx_load_prom = 2,
    lmc_xilinx_load = 3
पूर्ण;

काष्ठा lmc_xilinx_control अणु
    क्रमागत lmc_xilinx_c command;
    पूर्णांक len;
    अक्षर __user *data;
पूर्ण;

/* ------------------ end T1 defs ------------------- */

#घोषणा LMC_MII_LedMask                 0x0780
#घोषणा LMC_MII_LedBitPos               7

#पूर्ण_अगर
