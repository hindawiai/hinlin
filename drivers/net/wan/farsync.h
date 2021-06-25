<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *      FarSync X21 driver क्रम Linux
 *
 *      Actually sync driver क्रम X.21, V.35 and V.24 on FarSync T-series cards
 *
 *      Copyright (C) 2001 FarSite Communications Ltd.
 *      www.farsite.co.uk
 *
 *      Author: R.J.Dunlop      <bob.dunlop@farsite.co.uk>
 *
 *      For the most part this file only contains काष्ठाures and inक्रमmation
 *      that is visible to applications outside the driver. Shared memory
 *      layout etc is पूर्णांकernal to the driver and described within farsync.c.
 *      Overlap exists in that the values used क्रम some fields within the
 *      ioctl पूर्णांकerface extend पूर्णांकo the cards firmware पूर्णांकerface so values in
 *      this file may not be changed arbitrarily.
 */

/*      What's in a name
 *
 *      The project name क्रम this driver is Oscar. The driver is पूर्णांकended to be
 *      used with the FarSite T-Series cards (T2P & T4P) running in the high
 *      speed frame shअगरter mode. This is someबार referred to as X.21 mode
 *      which is a complete misnomer as the card जारीs to support V.24 and
 *      V.35 as well as X.21.
 *
 *      A लघु common prefix is useful क्रम routines within the driver to aव्योम
 *      conflict with other similar drivers and I chosen to use "fst_" क्रम this
 *      purpose (FarSite T-series).
 *
 *      Finally the device driver needs a लघु network पूर्णांकerface name. Since
 *      "hdlc" is alपढ़ोy in use I've chosen the even less inक्रमmative "sync"
 *      क्रम the present.
 */
#घोषणा FST_NAME                "fst"           /* In debug/info etc */
#घोषणा FST_NDEV_NAME           "sync"          /* For net पूर्णांकerface */
#घोषणा FST_DEV_NAME            "farsync"       /* For misc पूर्णांकerfaces */


/*      User version number
 *
 *      This version number is incremented with each official release of the
 *      package and is a simplअगरied number क्रम normal user reference.
 *      Inभागidual files are tracked by the version control प्रणाली and may
 *      have inभागidual versions (or IDs) that move much faster than the
 *      the release version as inभागidual updates are tracked.
 */
#घोषणा FST_USER_VERSION        "1.04"


/*      Ioctl call command values
 */
#घोषणा FSTWRITE        (SIOCDEVPRIVATE+10)
#घोषणा FSTCPURESET     (SIOCDEVPRIVATE+11)
#घोषणा FSTCPURELEASE   (SIOCDEVPRIVATE+12)
#घोषणा FSTGETCONF      (SIOCDEVPRIVATE+13)
#घोषणा FSTSETCONF      (SIOCDEVPRIVATE+14)


/*      FSTWRITE
 *
 *      Used to ग_लिखो a block of data (firmware etc) beक्रमe the card is running
 */
काष्ठा fstioc_ग_लिखो अणु
        अचिन्हित पूर्णांक  size;
        अचिन्हित पूर्णांक  offset;
	अचिन्हित अक्षर data[];
पूर्ण;


/*      FSTCPURESET and FSTCPURELEASE
 *
 *      These take no additional data.
 *      FSTCPURESET क्रमces the cards CPU पूर्णांकo a reset state and holds it there.
 *      FSTCPURELEASE releases the CPU from this reset state allowing it to run,
 *      the reset vector should be setup beक्रमe this ioctl is run.
 */

/*      FSTGETCONF and FSTSETCONF
 *
 *      Get and set a card/ports configuration.
 *      In order to allow selective setting of items and क्रम the kernel to
 *      indicate a partial status response the first field "valid" is a biपंचांगask
 *      indicating which other fields in the काष्ठाure are valid.
 *      Many of the field names in this काष्ठाure match those used in the
 *      firmware shared memory configuration पूर्णांकerface and come originally from
 *      the NT header file Smc.h
 *
 *      When used with FSTGETCONF this काष्ठाure should be zeroed beक्रमe use.
 *      This is to allow क्रम possible future expansion when some of the fields
 *      might be used to indicate a dअगरferent (expanded) काष्ठाure.
 */
काष्ठा fstioc_info अणु
        अचिन्हित पूर्णांक   valid;           /* Bits of काष्ठाure that are valid */
        अचिन्हित पूर्णांक   nports;          /* Number of serial ports */
        अचिन्हित पूर्णांक   type;            /* Type index of card */
        अचिन्हित पूर्णांक   state;           /* State of card */
        अचिन्हित पूर्णांक   index;           /* Index of port ioctl was issued on */
        अचिन्हित पूर्णांक   smcFirmwareVersion;
        अचिन्हित दीर्घ  kernelVersion;   /* What Kernel version we are working with */
        अचिन्हित लघु lineInterface;   /* Physical पूर्णांकerface type */
        अचिन्हित अक्षर  proto;           /* Line protocol */
        अचिन्हित अक्षर  पूर्णांकernalClock;   /* 1 => पूर्णांकernal घड़ी, 0 => बाह्यal */
        अचिन्हित पूर्णांक   lineSpeed;       /* Speed in bps */
        अचिन्हित पूर्णांक   v24IpSts;        /* V.24 control input status */
        अचिन्हित पूर्णांक   v24OpSts;        /* V.24 control output status */
        अचिन्हित लघु घड़ीStatus;     /* lsb: 0=> present, 1=> असलent */
        अचिन्हित लघु cableStatus;     /* lsb: 0=> present, 1=> असलent */
        अचिन्हित लघु cardMode;        /* lsb: LED id mode */
        अचिन्हित लघु debug;           /* Debug flags */
        अचिन्हित अक्षर  transparentMode; /* Not used always 0 */
        अचिन्हित अक्षर  invertClock;     /* Invert घड़ी feature क्रम syncing */
        अचिन्हित अक्षर  startingSlot;    /* Time slot to use क्रम start of tx */
        अचिन्हित अक्षर  घड़ीSource;     /* External or पूर्णांकernal */
        अचिन्हित अक्षर  framing;         /* E1, T1 or J1 */
        अचिन्हित अक्षर  काष्ठाure;       /* unframed, द्विगुन, crc4, f4, f12, */
                                        /* f24 f72 */
        अचिन्हित अक्षर  पूर्णांकerface;       /* rj48c or bnc */
        अचिन्हित अक्षर  coding;          /* hdb3 b8zs */
        अचिन्हित अक्षर  lineBuildOut;    /* 0, -7.5, -15, -22 */
        अचिन्हित अक्षर  equalizer;       /* लघु or lon haul settings */
        अचिन्हित अक्षर  loopMode;        /* various loopbacks */
        अचिन्हित अक्षर  range;           /* cable lengths */
        अचिन्हित अक्षर  txBufferMode;    /* tx elastic buffer depth */
        अचिन्हित अक्षर  rxBufferMode;    /* rx elastic buffer depth */
        अचिन्हित अक्षर  losThreshold;    /* Attenuation on LOS संकेत */
        अचिन्हित अक्षर  idleCode;        /* Value to send as idle बारlot */
        अचिन्हित पूर्णांक   receiveBufferDelay; /* delay thro rx buffer बारlots */
        अचिन्हित पूर्णांक   framingErrorCount; /* framing errors */
        अचिन्हित पूर्णांक   codeViolationCount; /* code violations */
        अचिन्हित पूर्णांक   crcErrorCount;   /* CRC errors */
        पूर्णांक            lineAttenuation; /* in dB*/
        अचिन्हित लघु lossOfSignal;
        अचिन्हित लघु receiveRemoteAlarm;
        अचिन्हित लघु alarmIndicationSignal;
पूर्ण;

/* "valid" biपंचांगask */
#घोषणा FSTVAL_NONE     0x00000000      /* Nothing valid (firmware not running).
                                         * Slight misnomer. In fact nports,
                                         * type, state and index will be set
                                         * based on hardware detected.
                                         */
#घोषणा FSTVAL_OMODEM   0x0000001F      /* First 5 bits correspond to the
                                         * output status bits defined क्रम
                                         * v24OpSts
                                         */
#घोषणा FSTVAL_SPEED    0x00000020      /* पूर्णांकernalClock, lineSpeed, घड़ीStatus
                                         */
#घोषणा FSTVAL_CABLE    0x00000040      /* lineInterface, cableStatus */
#घोषणा FSTVAL_IMODEM   0x00000080      /* v24IpSts */
#घोषणा FSTVAL_CARD     0x00000100      /* nports, type, state, index,
                                         * smcFirmwareVersion
                                         */
#घोषणा FSTVAL_PROTO    0x00000200      /* proto */
#घोषणा FSTVAL_MODE     0x00000400      /* cardMode */
#घोषणा FSTVAL_PHASE    0x00000800      /* Clock phase */
#घोषणा FSTVAL_TE1      0x00001000      /* T1E1 Configuration */
#घोषणा FSTVAL_DEBUG    0x80000000      /* debug */
#घोषणा FSTVAL_ALL      0x00001FFF      /* Note: करोes not include DEBUG flag */

/* "type" */
#घोषणा FST_TYPE_NONE   0               /* Probably should never happen */
#घोषणा FST_TYPE_T2P    1               /* T2P X21 2 port card */
#घोषणा FST_TYPE_T4P    2               /* T4P X21 4 port card */
#घोषणा FST_TYPE_T1U    3               /* T1U X21 1 port card */
#घोषणा FST_TYPE_T2U    4               /* T2U X21 2 port card */
#घोषणा FST_TYPE_T4U    5               /* T4U X21 4 port card */
#घोषणा FST_TYPE_TE1    6               /* T1E1 X21 1 port card */

/* "family" */
#घोषणा FST_FAMILY_TXP  0               /* T2P or T4P */
#घोषणा FST_FAMILY_TXU  1               /* T1U or T2U or T4U */

/* "state" */
#घोषणा FST_UNINIT      0               /* Raw uninitialised state following
                                         * प्रणाली startup */
#घोषणा FST_RESET       1               /* Processor held in reset state */
#घोषणा FST_DOWNLOAD    2               /* Card being करोwnloaded */
#घोषणा FST_STARTING    3               /* Released following करोwnload */
#घोषणा FST_RUNNING     4               /* Processor running */
#घोषणा FST_BADVERSION  5               /* Bad shared memory version detected */
#घोषणा FST_HALTED      6               /* Processor flagged a halt */
#घोषणा FST_IFAILED     7               /* Firmware issued initialisation failed
                                         * पूर्णांकerrupt
                                         */
/* "lineInterface" */
#घोषणा V24             1
#घोषणा X21             2
#घोषणा V35             3
#घोषणा X21D            4
#घोषणा T1              5
#घोषणा E1              6
#घोषणा J1              7

/* "proto" */
#घोषणा FST_RAW         4               /* Two way raw packets */
#घोषणा FST_GEN_HDLC    5               /* Using "Generic HDLC" module */

/* "internalClock" */
#घोषणा INTCLK          1
#घोषणा EXTCLK          0

/* "v24IpSts" biपंचांगask */
#घोषणा IPSTS_CTS       0x00000001      /* Clear To Send (Indicate क्रम X.21) */
#घोषणा IPSTS_INDICATE  IPSTS_CTS
#घोषणा IPSTS_DSR       0x00000002      /* Data Set Ready (T2P Port A) */
#घोषणा IPSTS_DCD       0x00000004      /* Data Carrier Detect */
#घोषणा IPSTS_RI        0x00000008      /* Ring Indicator (T2P Port A) */
#घोषणा IPSTS_TMI       0x00000010      /* Test Mode Indicator (Not Supported)*/

/* "v24OpSts" biपंचांगask */
#घोषणा OPSTS_RTS       0x00000001      /* Request To Send (Control क्रम X.21) */
#घोषणा OPSTS_CONTROL   OPSTS_RTS
#घोषणा OPSTS_DTR       0x00000002      /* Data Terminal Ready */
#घोषणा OPSTS_DSRS      0x00000004      /* Data Signalling Rate Select (Not
                                         * Supported) */
#घोषणा OPSTS_SS        0x00000008      /* Select Standby (Not Supported) */
#घोषणा OPSTS_LL        0x00000010      /* Maपूर्णांकenance Test (Not Supported) */

/* "cardMode" biपंचांगask */
#घोषणा CARD_MODE_IDENTIFY      0x0001

/* 
 * Constants क्रम T1/E1 configuration
 */

/*
 * Clock source
 */
#घोषणा CLOCKING_SLAVE       0
#घोषणा CLOCKING_MASTER      1

/*
 * Framing
 */
#घोषणा FRAMING_E1           0
#घोषणा FRAMING_J1           1
#घोषणा FRAMING_T1           2

/*
 * Structure
 */
#घोषणा STRUCTURE_UNFRAMED   0
#घोषणा STRUCTURE_E1_DOUBLE  1
#घोषणा STRUCTURE_E1_CRC4    2
#घोषणा STRUCTURE_E1_CRC4M   3
#घोषणा STRUCTURE_T1_4       4
#घोषणा STRUCTURE_T1_12      5
#घोषणा STRUCTURE_T1_24      6
#घोषणा STRUCTURE_T1_72      7

/*
 * Interface
 */
#घोषणा INTERFACE_RJ48C      0
#घोषणा INTERFACE_BNC        1

/*
 * Coding
 */

#घोषणा CODING_HDB3          0
#घोषणा CODING_NRZ           1
#घोषणा CODING_CMI           2
#घोषणा CODING_CMI_HDB3      3
#घोषणा CODING_CMI_B8ZS      4
#घोषणा CODING_AMI           5
#घोषणा CODING_AMI_ZCS       6
#घोषणा CODING_B8ZS          7

/*
 * Line Build Out
 */
#घोषणा LBO_0dB              0
#घोषणा LBO_7dB5             1
#घोषणा LBO_15dB             2
#घोषणा LBO_22dB5            3

/*
 * Range क्रम दीर्घ haul t1 > 655ft
 */
#घोषणा RANGE_0_133_FT       0
#घोषणा RANGE_0_40_M         RANGE_0_133_FT
#घोषणा RANGE_133_266_FT     1
#घोषणा RANGE_40_81_M        RANGE_133_266_FT
#घोषणा RANGE_266_399_FT     2
#घोषणा RANGE_81_122_M       RANGE_266_399_FT
#घोषणा RANGE_399_533_FT     3
#घोषणा RANGE_122_162_M       RANGE_399_533_FT
#घोषणा RANGE_533_655_FT     4
#घोषणा RANGE_162_200_M      RANGE_533_655_FT
/*
 * Receive Equaliser
 */
#घोषणा EQUALIZER_SHORT      0
#घोषणा EQUALIZER_LONG       1

/*
 * Loop modes
 */
#घोषणा LOOP_NONE            0
#घोषणा LOOP_LOCAL           1
#घोषणा LOOP_PAYLOAD_EXC_TS0 2
#घोषणा LOOP_PAYLOAD_INC_TS0 3
#घोषणा LOOP_REMOTE          4

/*
 * Buffer modes
 */
#घोषणा BUFFER_2_FRAME       0
#घोषणा BUFFER_1_FRAME       1
#घोषणा BUFFER_96_BIT        2
#घोषणा BUFFER_NONE          3

/*      Debug support
 *
 *      These should only be enabled क्रम development kernels, production code
 *      should define FST_DEBUG=0 in order to exclude the code.
 *      Setting FST_DEBUG=1 will include all the debug code but in a disabled
 *      state, use the FSTSETCONF ioctl to enable specअगरic debug actions, or
 *      FST_DEBUG can be set to prime the debug selection.
 */
#घोषणा FST_DEBUG       0x0000
#अगर FST_DEBUG

बाह्य पूर्णांक fst_debug_mask;              /* Bit mask of actions to debug, bits
                                         * listed below. Note: Bit 0 is used
                                         * to trigger the inclusion of this
                                         * code, without enabling any actions.
                                         */
#घोषणा DBG_INIT        0x0002          /* Card detection and initialisation */
#घोषणा DBG_OPEN        0x0004          /* Open and बंद sequences */
#घोषणा DBG_PCI         0x0008          /* PCI config operations */
#घोषणा DBG_IOCTL       0x0010          /* Ioctls and other config */
#घोषणा DBG_INTR        0x0020          /* Interrupt routines (be careful) */
#घोषणा DBG_TX          0x0040          /* Packet transmission */
#घोषणा DBG_RX          0x0080          /* Packet reception */
#घोषणा DBG_CMD         0x0100          /* Port command issuing */

#घोषणा DBG_ASS         0xFFFF          /* Assert like statements. Code that
                                         * should never be reached, अगर you see
                                         * one of these then I've been an ass
                                         */
#पूर्ण_अगर  /* FST_DEBUG */

