<शैली गुरु>
/*
 * Intel i82586 Ethernet definitions
 *
 * This is an extension to the Linux operating प्रणाली, and is covered by the
 * same Gnu Public License that covers that work.
 *
 * copyrights (c) 1994 by Michael Hipp (hippm@inक्रमmatik.uni-tuebingen.de)
 *
 * I have करोne a look in the following sources:
 *   crynwr-packet-driver by Russ Nelson
 *   Garret A. Wollman's i82586-driver क्रम BSD
 */

/*
 * Cloned from ni52.h, copyright as above.
 *
 * Modअगरied क्रम Sun3 OBIO i82586 by Sam Creasey (sammy@sammy.net)
 */


/* defines क्रम the obio chip (not vme) */
#घोषणा IEOB_NORSET 0x80        /* करोn't reset the board */
#घोषणा IEOB_ONAIR  0x40        /* put us on the air */
#घोषणा IEOB_ATTEN  0x20        /* attention! */
#घोषणा IEOB_IENAB  0x10        /* पूर्णांकerrupt enable */
#घोषणा IEOB_XXXXX  0x08        /* मुक्त bit */
#घोषणा IEOB_XCVRL2 0x04        /* level 2 transceiver? */
#घोषणा IEOB_BUSERR 0x02        /* bus error */
#घोषणा IEOB_INT    0x01        /* पूर्णांकerrupt */

/* where the obio one lives */
#घोषणा IE_OBIO 0xc0000
#घोषणा IE_IRQ 3

/*
 * where to find the System Configuration Poपूर्णांकer (SCP)
 */
#घोषणा SCP_DEFAULT_ADDRESS 0xfffff4


/*
 * System Configuration Poपूर्णांकer Struct
 */

काष्ठा scp_काष्ठा
अणु
  अचिन्हित लघु zero_dum0;	/* has to be zero */
  अचिन्हित अक्षर  sysbus;	/* 0=16Bit,1=8Bit */
  अचिन्हित अक्षर  zero_dum1;	/* has to be zero क्रम 586 */
  अचिन्हित लघु zero_dum2;
  अचिन्हित लघु zero_dum3;
  अक्षर          *iscp;		/* poपूर्णांकer to the iscp-block */
पूर्ण;


/*
 * Intermediate System Configuration Poपूर्णांकer (ISCP)
 */
काष्ठा iscp_काष्ठा
अणु
  अचिन्हित अक्षर  busy;          /* 586 clears after successful init */
  अचिन्हित अक्षर  zero_dummy;    /* has to be zero */
  अचिन्हित लघु scb_offset;    /* poपूर्णांकeroffset to the scb_base */
  अक्षर          *scb_base;      /* base-address of all 16-bit offsets */
पूर्ण;

/*
 * System Control Block (SCB)
 */
काष्ठा scb_काष्ठा
अणु
  अचिन्हित अक्षर rus;
  अचिन्हित अक्षर cus;
  अचिन्हित अक्षर cmd_ruc;           /* command word: RU part */
  अचिन्हित अक्षर cmd_cuc;           /* command word: CU part & ACK */
  अचिन्हित लघु cbl_offset;    /* poपूर्णांकeroffset, command block list */
  अचिन्हित लघु rfa_offset;    /* poपूर्णांकeroffset, receive frame area */
  अचिन्हित लघु crc_errs;      /* CRC-Error counter */
  अचिन्हित लघु aln_errs;      /* allignmenterror counter */
  अचिन्हित लघु rsc_errs;      /* Resourceerror counter */
  अचिन्हित लघु ovrn_errs;     /* OVerrunerror counter */
पूर्ण;

/*
 * possible command values क्रम the command word
 */
#घोषणा RUC_MASK	0x0070	/* mask क्रम RU commands */
#घोषणा RUC_NOP		0x0000	/* NOP-command */
#घोषणा RUC_START	0x0010	/* start RU */
#घोषणा RUC_RESUME	0x0020	/* resume RU after suspend */
#घोषणा RUC_SUSPEND	0x0030	/* suspend RU */
#घोषणा RUC_ABORT	0x0040	/* पात receiver operation immediately */

#घोषणा CUC_MASK        0x07  /* mask क्रम CU command */
#घोषणा CUC_NOP         0x00  /* NOP-command */
#घोषणा CUC_START       0x01  /* start execution of 1. cmd on the CBL */
#घोषणा CUC_RESUME      0x02  /* resume after suspend */
#घोषणा CUC_SUSPEND     0x03  /* Suspend CU */
#घोषणा CUC_ABORT       0x04  /* पात command operation immediately */

#घोषणा ACK_MASK        0xf0  /* mask क्रम ACK command */
#घोषणा ACK_CX          0x80  /* acknowledges STAT_CX */
#घोषणा ACK_FR          0x40  /* ack. STAT_FR */
#घोषणा ACK_CNA         0x20  /* ack. STAT_CNA */
#घोषणा ACK_RNR         0x10  /* ack. STAT_RNR */

/*
 * possible status values क्रम the status word
 */
#घोषणा STAT_MASK       0xf0  /* mask क्रम cause of पूर्णांकerrupt */
#घोषणा STAT_CX         0x80  /* CU finished cmd with its I bit set */
#घोषणा STAT_FR         0x40  /* RU finished receiving a frame */
#घोषणा STAT_CNA        0x20  /* CU left active state */
#घोषणा STAT_RNR        0x10  /* RU left पढ़ोy state */

#घोषणा CU_STATUS       0x7   /* CU status, 0=idle */
#घोषणा CU_SUSPEND      0x1   /* CU is suspended */
#घोषणा CU_ACTIVE       0x2   /* CU is active */

#घोषणा RU_STATUS	0x70	/* RU status, 0=idle */
#घोषणा RU_SUSPEND	0x10	/* RU suspended */
#घोषणा RU_NOSPACE	0x20	/* RU no resources */
#घोषणा RU_READY	0x40	/* RU is पढ़ोy */

/*
 * Receive Frame Descriptor (RFD)
 */
काष्ठा rfd_काष्ठा
अणु
  अचिन्हित अक्षर  stat_low;	/* status word */
  अचिन्हित अक्षर  stat_high;	/* status word */
  अचिन्हित अक्षर  rfd_sf;	/* 82596 mode only */
  अचिन्हित अक्षर  last;		/* Bit15,Last Frame on List / Bit14,suspend */
  अचिन्हित लघु next;		/* linkoffset to next RFD */
  अचिन्हित लघु rbd_offset;	/* poपूर्णांकeroffset to RBD-buffer */
  अचिन्हित अक्षर  dest[ETH_ALEN];	/* ethernet-address, destination */
  अचिन्हित अक्षर  source[ETH_ALEN];	/* ethernet-address, source */
  अचिन्हित लघु length;	/* 802.3 frame-length */
  अचिन्हित लघु zero_dummy;	/* dummy */
पूर्ण;

#घोषणा RFD_LAST     0x80	/* last: last rfd in the list */
#घोषणा RFD_SUSP     0x40	/* last: suspend RU after  */
#घोषणा RFD_COMPL    0x80
#घोषणा RFD_OK       0x20
#घोषणा RFD_BUSY     0x40
#घोषणा RFD_ERR_LEN  0x10     /* Length error (अगर enabled length-checking */
#घोषणा RFD_ERR_CRC  0x08     /* CRC error */
#घोषणा RFD_ERR_ALGN 0x04     /* Alignment error */
#घोषणा RFD_ERR_RNR  0x02     /* status: receiver out of resources */
#घोषणा RFD_ERR_OVR  0x01     /* DMA Overrun! */

#घोषणा RFD_ERR_FTS  0x0080	/* Frame to लघु */
#घोषणा RFD_ERR_NEOP 0x0040	/* No EOP flag (क्रम bitstuffing only) */
#घोषणा RFD_ERR_TRUN 0x0020	/* (82596 only/SF mode) indicates truncated frame */
#घोषणा RFD_MATCHADD 0x0002     /* status: Destinationaddress !matches IA (only 82596) */
#घोषणा RFD_COLLDET  0x0001	/* Detected collision during reception */

/*
 * Receive Buffer Descriptor (RBD)
 */
काष्ठा rbd_काष्ठा
अणु
  अचिन्हित लघु status;	/* status word,number of used bytes in buff */
  अचिन्हित लघु next;		/* poपूर्णांकeroffset to next RBD */
  अक्षर          *buffer;	/* receive buffer address poपूर्णांकer */
  अचिन्हित लघु size;		/* size of this buffer */
  अचिन्हित लघु zero_dummy;    /* dummy */
पूर्ण;

#घोषणा RBD_LAST	0x8000	/* last buffer */
#घोषणा RBD_USED	0x4000	/* this buffer has data */
#घोषणा RBD_MASK	0x3fff	/* size-mask क्रम length */

/*
 * Statusvalues क्रम Commands/RFD
 */
#घोषणा STAT_COMPL   0x8000	/* status: frame/command is complete */
#घोषणा STAT_BUSY    0x4000	/* status: frame/command is busy */
#घोषणा STAT_OK      0x2000	/* status: frame/command is ok */

/*
 * Action-Commands
 */
#घोषणा CMD_NOP		0x0000	/* NOP */
#घोषणा CMD_IASETUP	0x0001	/* initial address setup command */
#घोषणा CMD_CONFIGURE	0x0002	/* configure command */
#घोषणा CMD_MCSETUP	0x0003	/* MC setup command */
#घोषणा CMD_XMIT	0x0004	/* transmit command */
#घोषणा CMD_TDR		0x0005	/* समय करोमुख्य reflectometer (TDR) command */
#घोषणा CMD_DUMP	0x0006	/* dump command */
#घोषणा CMD_DIAGNOSE	0x0007	/* diagnose command */

/*
 * Action command bits
 */
#घोषणा CMD_LAST	0x8000	/* indicates last command in the CBL */
#घोषणा CMD_SUSPEND	0x4000	/* suspend CU after this CB */
#घोषणा CMD_INT		0x2000	/* generate पूर्णांकerrupt after execution */

/*
 * NOP - command
 */
काष्ठा nop_cmd_काष्ठा
अणु
  अचिन्हित लघु cmd_status;	/* status of this command */
  अचिन्हित लघु cmd_cmd;       /* the command itself (+bits) */
  अचिन्हित लघु cmd_link;      /* offsetpoपूर्णांकer to next command */
पूर्ण;

/*
 * IA Setup command
 */
काष्ठा iasetup_cmd_काष्ठा
अणु
  अचिन्हित लघु cmd_status;
  अचिन्हित लघु cmd_cmd;
  अचिन्हित लघु cmd_link;
  अचिन्हित अक्षर  iaddr[6];
पूर्ण;

/*
 * Configure command
 */
काष्ठा configure_cmd_काष्ठा
अणु
  अचिन्हित लघु cmd_status;
  अचिन्हित लघु cmd_cmd;
  अचिन्हित लघु cmd_link;
  अचिन्हित अक्षर  byte_cnt;   /* size of the config-cmd */
  अचिन्हित अक्षर  fअगरo;       /* fअगरo/recv monitor */
  अचिन्हित अक्षर  sav_bf;     /* save bad frames (bit7=1)*/
  अचिन्हित अक्षर  adr_len;    /* adr_len(0-2),al_loc(3),pream(4-5),loopbak(6-7)*/
  अचिन्हित अक्षर  priority;   /* lin_prio(0-2),exp_prio(4-6),bof_metd(7) */
  अचिन्हित अक्षर  अगरs;        /* पूर्णांकer frame spacing */
  अचिन्हित अक्षर  समय_low;   /* slot समय low */
  अचिन्हित अक्षर  समय_high;  /* slot समय high(0-2) and max. retries(4-7) */
  अचिन्हित अक्षर  promisc;    /* promisc-mode(0) , et al (1-7) */
  अचिन्हित अक्षर  carr_coll;  /* carrier(0-3)/collision(4-7) stuff */
  अचिन्हित अक्षर  fram_len;   /* minimal frame len */
  अचिन्हित अक्षर  dummy;	     /* dummy */
पूर्ण;

/*
 * Multicast Setup command
 */
काष्ठा mcsetup_cmd_काष्ठा
अणु
  अचिन्हित लघु cmd_status;
  अचिन्हित लघु cmd_cmd;
  अचिन्हित लघु cmd_link;
  अचिन्हित लघु mc_cnt;		/* number of bytes in the MC-List */
  अचिन्हित अक्षर  mc_list[0][6];  	/* poपूर्णांकer to 6 bytes entries */
पूर्ण;

/*
 * DUMP command
 */
काष्ठा dump_cmd_काष्ठा
अणु
  अचिन्हित लघु cmd_status;
  अचिन्हित लघु cmd_cmd;
  अचिन्हित लघु cmd_link;
  अचिन्हित लघु dump_offset;    /* poपूर्णांकeroffset to DUMP space */
पूर्ण;

/*
 * transmit command
 */
काष्ठा transmit_cmd_काष्ठा
अणु
  अचिन्हित लघु cmd_status;
  अचिन्हित लघु cmd_cmd;
  अचिन्हित लघु cmd_link;
  अचिन्हित लघु tbd_offset;	/* poपूर्णांकeroffset to TBD */
  अचिन्हित अक्षर  dest[6];       /* destination address of the frame */
  अचिन्हित लघु length;	/* user defined: 802.3 length / Ether type */
पूर्ण;

#घोषणा TCMD_ERRMASK     0x0fa0
#घोषणा TCMD_MAXCOLLMASK 0x000f
#घोषणा TCMD_MAXCOLL     0x0020
#घोषणा TCMD_HEARTBEAT   0x0040
#घोषणा TCMD_DEFERRED    0x0080
#घोषणा TCMD_UNDERRUN    0x0100
#घोषणा TCMD_LOSTCTS     0x0200
#घोषणा TCMD_NOCARRIER   0x0400
#घोषणा TCMD_LATECOLL    0x0800

काष्ठा tdr_cmd_काष्ठा
अणु
  अचिन्हित लघु cmd_status;
  अचिन्हित लघु cmd_cmd;
  अचिन्हित लघु cmd_link;
  अचिन्हित लघु status;
पूर्ण;

#घोषणा TDR_LNK_OK	0x8000	/* No link problem identअगरied */
#घोषणा TDR_XCVR_PRB	0x4000	/* indicates a transceiver problem */
#घोषणा TDR_ET_OPN	0x2000	/* खोलो, no correct termination */
#घोषणा TDR_ET_SRT	0x1000	/* TDR detected a लघु circuit */
#घोषणा TDR_TIMEMASK	0x07ff	/* mask क्रम the समय field */

/*
 * Transmit Buffer Descriptor (TBD)
 */
काष्ठा tbd_काष्ठा
अणु
  अचिन्हित लघु size;		/* size + खातापूर्ण-Flag(15) */
  अचिन्हित लघु next;          /* poपूर्णांकeroffset to next TBD */
  अक्षर          *buffer;        /* poपूर्णांकer to buffer */
पूर्ण;

#घोषणा TBD_LAST 0x8000         /* खातापूर्ण-Flag, indicates last buffer in list */




