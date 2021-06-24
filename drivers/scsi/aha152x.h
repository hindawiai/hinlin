<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _AHA152X_H
#घोषणा _AHA152X_H

/*
 * $Id: aha152x.h,v 2.7 2004/01/24 11:39:03 fischer Exp $
 */

/* number of queueable commands
   (unless we support more than 1 cmd_per_lun this should करो) */
#घोषणा AHA152X_MAXQUEUE 7

#घोषणा AHA152X_REVID "Adaptec 152x SCSI driver; $Revision: 2.7 $"

/* port addresses */
#घोषणा SCSISEQ      (HOSTIOPORT0+0x00)    /* SCSI sequence control */
#घोषणा SXFRCTL0     (HOSTIOPORT0+0x01)    /* SCSI transfer control 0 */
#घोषणा SXFRCTL1     (HOSTIOPORT0+0x02)    /* SCSI transfer control 1 */
#घोषणा SCSISIG      (HOSTIOPORT0+0x03)    /* SCSI संकेत in/out */
#घोषणा SCSIRATE     (HOSTIOPORT0+0x04)    /* SCSI rate control */
#घोषणा SELID        (HOSTIOPORT0+0x05)    /* selection/reselection ID */
#घोषणा SCSIID       SELID                 /* SCSI ID */
#घोषणा SCSIDAT      (HOSTIOPORT0+0x06)    /* SCSI latched data */
#घोषणा SCSIBUS      (HOSTIOPORT0+0x07)    /* SCSI data bus */
#घोषणा STCNT0       (HOSTIOPORT0+0x08)    /* SCSI transfer count 0 */
#घोषणा STCNT1       (HOSTIOPORT0+0x09)    /* SCSI transfer count 1 */
#घोषणा STCNT2       (HOSTIOPORT0+0x0a)    /* SCSI transfer count 2 */
#घोषणा SSTAT0       (HOSTIOPORT0+0x0b)    /* SCSI पूर्णांकerrupt status 0 */
#घोषणा SSTAT1       (HOSTIOPORT0+0x0c)    /* SCSI पूर्णांकerrupt status 1 */
#घोषणा SSTAT2       (HOSTIOPORT0+0x0d)    /* SCSI पूर्णांकerrupt status 2 */
#घोषणा SCSITEST     (HOSTIOPORT0+0x0e)    /* SCSI test control */
#घोषणा SSTAT3       SCSITEST              /* SCSI पूर्णांकerrupt status 3 */
#घोषणा SSTAT4       (HOSTIOPORT0+0x0f)    /* SCSI status 4 */
#घोषणा SIMODE0      (HOSTIOPORT1+0x10)    /* SCSI पूर्णांकerrupt mode 0 */
#घोषणा SIMODE1      (HOSTIOPORT1+0x11)    /* SCSI पूर्णांकerrupt mode 1 */
#घोषणा DMACNTRL0    (HOSTIOPORT1+0x12)    /* DMA control 0 */
#घोषणा DMACNTRL1    (HOSTIOPORT1+0x13)    /* DMA control 1 */
#घोषणा DMASTAT      (HOSTIOPORT1+0x14)    /* DMA status */
#घोषणा FIFOSTAT     (HOSTIOPORT1+0x15)    /* FIFO status */
#घोषणा DATAPORT     (HOSTIOPORT1+0x16)    /* DATA port */
#घोषणा BRSTCNTRL    (HOSTIOPORT1+0x18)    /* burst control */
#घोषणा PORTA        (HOSTIOPORT1+0x1a)    /* PORT A */
#घोषणा PORTB        (HOSTIOPORT1+0x1b)    /* PORT B */
#घोषणा REV          (HOSTIOPORT1+0x1c)    /* revision */
#घोषणा STACK        (HOSTIOPORT1+0x1d)    /* stack */
#घोषणा TEST         (HOSTIOPORT1+0x1e)    /* test रेजिस्टर */

#घोषणा IO_RANGE        0x20

/* used in aha152x_porttest */
#घोषणा O_PORTA         0x1a               /* PORT A */
#घोषणा O_PORTB         0x1b               /* PORT B */
#घोषणा O_DMACNTRL1     0x13               /* DMA control 1 */
#घोषणा O_STACK         0x1d               /* stack */

/* used in tc1550_porttest */
#घोषणा O_TC_PORTA      0x0a               /* PORT A */
#घोषणा O_TC_PORTB      0x0b               /* PORT B */
#घोषणा O_TC_DMACNTRL1  0x03               /* DMA control 1 */
#घोषणा O_TC_STACK      0x0d               /* stack */

/* bits and biपंचांगasks to ports */

/* SCSI sequence control */
#घोषणा TEMODEO      0x80
#घोषणा ENSELO       0x40
#घोषणा ENSELI       0x20
#घोषणा ENRESELI     0x10
#घोषणा ENAUTOATNO   0x08
#घोषणा ENAUTOATNI   0x04
#घोषणा ENAUTOATNP   0x02
#घोषणा SCSIRSTO     0x01

/* SCSI transfer control 0 */
#घोषणा SCSIEN       0x80
#घोषणा DMAEN        0x40
#घोषणा CH1          0x20
#घोषणा CLRSTCNT     0x10
#घोषणा SPIOEN       0x08
#घोषणा CLRCH1       0x02

/* SCSI transfer control 1 */
#घोषणा BITBUCKET    0x80
#घोषणा SWRAPEN      0x40
#घोषणा ENSPCHK      0x20
#घोषणा STIMESEL     0x18    /* mask */
#घोषणा STIMESEL_    3
#घोषणा ENSTIMER     0x04
#घोषणा BYTEALIGN    0x02

/* SCSI संकेत IN */
#घोषणा SIG_CDI          0x80
#घोषणा SIG_IOI          0x40
#घोषणा SIG_MSGI         0x20
#घोषणा SIG_ATNI         0x10
#घोषणा SIG_SELI         0x08
#घोषणा SIG_BSYI         0x04
#घोषणा SIG_REQI         0x02
#घोषणा SIG_ACKI         0x01

/* SCSI Phases */
#घोषणा P_MASK       (SIG_MSGI|SIG_CDI|SIG_IOI)
#घोषणा P_DATAO      (0)
#घोषणा P_DATAI      (SIG_IOI)
#घोषणा P_CMD        (SIG_CDI)
#घोषणा P_STATUS     (SIG_CDI|SIG_IOI)
#घोषणा P_MSGO       (SIG_MSGI|SIG_CDI)
#घोषणा P_MSGI       (SIG_MSGI|SIG_CDI|SIG_IOI)

/* SCSI संकेत OUT */
#घोषणा SIG_CDO          0x80
#घोषणा SIG_IOO          0x40
#घोषणा SIG_MSGO         0x20
#घोषणा SIG_ATNO         0x10
#घोषणा SIG_SELO         0x08
#घोषणा SIG_BSYO         0x04
#घोषणा SIG_REQO         0x02
#घोषणा SIG_ACKO         0x01

/* SCSI rate control */
#घोषणा SXFR         0x70    /* mask */
#घोषणा SXFR_        4
#घोषणा SOFS         0x0f    /* mask */

/* SCSI ID */
#घोषणा OID          0x70
#घोषणा OID_         4
#घोषणा TID          0x07

/* SCSI transfer count */
#घोषणा GETSTCNT() ( (GETPORT(STCNT2)<<16) \
                   + (GETPORT(STCNT1)<< 8) \
                   + GETPORT(STCNT0) )

#घोषणा SETSTCNT(X) अणु SETPORT(STCNT2, ((X) & 0xFF0000) >> 16); \
                      SETPORT(STCNT1, ((X) & 0x00FF00) >>  8); \
                      SETPORT(STCNT0, ((X) & 0x0000FF) ); पूर्ण

/* SCSI पूर्णांकerrupt status */
#घोषणा TARGET       0x80
#घोषणा SELDO        0x40
#घोषणा SELDI        0x20
#घोषणा SELINGO      0x10
#घोषणा SWRAP        0x08
#घोषणा SDONE        0x04
#घोषणा SPIORDY      0x02
#घोषणा DMADONE      0x01

#घोषणा SETSDONE     0x80
#घोषणा CLRSELDO     0x40
#घोषणा CLRSELDI     0x20
#घोषणा CLRSELINGO   0x10
#घोषणा CLRSWRAP     0x08
#घोषणा CLRSDONE     0x04
#घोषणा CLRSPIORDY   0x02
#घोषणा CLRDMADONE   0x01

/* SCSI status 1 */
#घोषणा SELTO        0x80
#घोषणा ATNTARG      0x40
#घोषणा SCSIRSTI     0x20
#घोषणा PHASEMIS     0x10
#घोषणा BUSFREE      0x08
#घोषणा SCSIPERR     0x04
#घोषणा PHASECHG     0x02
#घोषणा REQINIT      0x01

#घोषणा CLRSELTIMO   0x80
#घोषणा CLRATNO      0x40
#घोषणा CLRSCSIRSTI  0x20
#घोषणा CLRBUSFREE   0x08
#घोषणा CLRSCSIPERR  0x04
#घोषणा CLRPHASECHG  0x02
#घोषणा CLRREQINIT   0x01

/* SCSI status 2 */
#घोषणा SOFFSET      0x20
#घोषणा SEMPTY       0x10
#घोषणा SFULL        0x08
#घोषणा SFCNT        0x07    /* mask */

/* SCSI status 3 */
#घोषणा SCSICNT      0xf0    /* mask */
#घोषणा SCSICNT_     4
#घोषणा OFFCNT       0x0f    /* mask */

/* SCSI TEST control */
#घोषणा SCTESTU      0x08
#घोषणा SCTESTD      0x04
#घोषणा STCTEST      0x01

/* SCSI status 4 */
#घोषणा SYNCERR      0x04
#घोषणा FWERR        0x02
#घोषणा FRERR        0x01

#घोषणा CLRSYNCERR   0x04
#घोषणा CLRFWERR     0x02
#घोषणा CLRFRERR     0x01

/* SCSI पूर्णांकerrupt mode 0 */
#घोषणा ENSELDO      0x40
#घोषणा ENSELDI      0x20
#घोषणा ENSELINGO    0x10
#घोषणा ENSWRAP      0x08
#घोषणा ENSDONE      0x04
#घोषणा ENSPIORDY    0x02
#घोषणा ENDMADONE    0x01

/* SCSI पूर्णांकerrupt mode 1 */
#घोषणा ENSELTIMO    0x80
#घोषणा ENATNTARG    0x40
#घोषणा ENSCSIRST    0x20
#घोषणा ENPHASEMIS   0x10
#घोषणा ENBUSFREE    0x08
#घोषणा ENSCSIPERR   0x04
#घोषणा ENPHASECHG   0x02
#घोषणा ENREQINIT    0x01

/* DMA control 0 */
#घोषणा ENDMA        0x80
#घोषणा _8BIT        0x40
#घोषणा DMA          0x20
#घोषणा WRITE_READ   0x08
#घोषणा INTEN        0x04
#घोषणा RSTFIFO      0x02
#घोषणा SWINT        0x01

/* DMA control 1 */
#घोषणा PWRDWN       0x80
#घोषणा STK          0x07    /* mask */

/* DMA status */
#घोषणा ATDONE       0x80
#घोषणा WORDRDY      0x40
#घोषणा INTSTAT      0x20
#घोषणा DFIFOFULL    0x10
#घोषणा DFIFOEMP     0x08

/* BURST control */
#घोषणा BON          0xf0
#घोषणा BOFF         0x0f

/* TEST REGISTER */
#घोषणा BOFFTMR      0x40
#घोषणा BONTMR       0x20
#घोषणा STCNTH       0x10
#घोषणा STCNTM       0x08
#घोषणा STCNTL       0x04
#घोषणा SCSIBLK      0x02
#घोषणा DMABLK       0x01

/* On the AHA-152x board PORTA and PORTB contain
   some inक्रमmation about the board's configuration. */
प्रकार जोड़ अणु
  काष्ठा अणु
    अचिन्हित reserved:2;    /* reserved */
    अचिन्हित tardisc:1;     /* Target disconnect: 0=disabled, 1=enabled */
    अचिन्हित syncneg:1;     /* Initial sync neg: 0=disabled, 1=enabled */
    अचिन्हित msgclasses:2;  /* Message classes
                                 0=#4
                                 1=#0, #1, #2, #3, #4
                                 2=#0, #3, #4
                                 3=#0, #4
                             */
    अचिन्हित boot:1;        /* boot: 0=disabled, 1=enabled */
    अचिन्हित dma:1;         /* Transfer mode: 0=PIO; 1=DMA */
    अचिन्हित id:3;          /* SCSI-id */
    अचिन्हित irq:2;         /* IRQ-Channel: 0,3=12, 1=10, 2=11 */
    अचिन्हित dmachan:2;     /* DMA-Channel: 0=0, 1=5, 2=6, 3=7 */
    अचिन्हित parity:1;      /* SCSI-parity: 1=enabled 0=disabled */
  पूर्ण fields;
  अचिन्हित लघु port;
पूर्ण aha152x_config ;

#घोषणा cf_parity     fields.parity
#घोषणा cf_dmachan    fields.dmachan
#घोषणा cf_irq        fields.irq
#घोषणा cf_id         fields.id
#घोषणा cf_dma        fields.dma
#घोषणा cf_boot       fields.boot
#घोषणा cf_msgclasses fields.msgclasses
#घोषणा cf_syncneg    fields.syncneg
#घोषणा cf_tardisc    fields.tardisc
#घोषणा cf_port       port

/* Some macros to manipulate ports and their bits */

#घोषणा SETPORT(PORT, VAL)	outb( (VAL), (PORT) )
#घोषणा GETPORT(PORT)		inb( PORT )
#घोषणा SETBITS(PORT, BITS)	outb( (inb(PORT) | (BITS)), (PORT) )
#घोषणा CLRBITS(PORT, BITS)	outb( (inb(PORT) & ~(BITS)), (PORT) )
#घोषणा TESTHI(PORT, BITS)	((inb(PORT) & (BITS)) == (BITS))
#घोषणा TESTLO(PORT, BITS)	((inb(PORT) & (BITS)) == 0)

#घोषणा SETRATE(RATE)		SETPORT(SCSIRATE,(RATE) & 0x7f)

#अगर defined(AHA152X_DEBUG)
क्रमागत अणु
  debug_procinfo  = 0x0001,
  debug_queue     = 0x0002,
  debug_locking   = 0x0004,
  debug_पूर्णांकr      = 0x0008,
  debug_selection = 0x0010,
  debug_msgo      = 0x0020,
  debug_msgi      = 0x0040,
  debug_status    = 0x0080,
  debug_cmd       = 0x0100,
  debug_datai     = 0x0200,
  debug_datao     = 0x0400,
  debug_eh	  = 0x0800,
  debug_करोne      = 0x1000,
  debug_phases    = 0x2000,
पूर्ण;
#पूर्ण_अगर

/* क्रम the pcmcia stub */
काष्ठा aha152x_setup अणु
	पूर्णांक io_port;
	पूर्णांक irq;
	पूर्णांक scsiid;
	पूर्णांक reconnect;
	पूर्णांक parity;
	पूर्णांक synchronous;
	पूर्णांक delay;
	पूर्णांक ext_trans;
	पूर्णांक tc1550;
#अगर defined(AHA152X_DEBUG)
	पूर्णांक debug;
#पूर्ण_अगर
	अक्षर *conf;
पूर्ण;

काष्ठा Scsi_Host *aha152x_probe_one(काष्ठा aha152x_setup *);
व्योम aha152x_release(काष्ठा Scsi_Host *);
पूर्णांक aha152x_host_reset_host(काष्ठा Scsi_Host *);

#पूर्ण_अगर /* _AHA152X_H */
