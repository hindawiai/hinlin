<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *    wd33c93.h -  Linux device driver definitions क्रम the
 *                 Commoकरोre Amiga A2091/590 SCSI controller card
 *
 *    IMPORTANT: This file is क्रम version 1.25 - 09/Jul/1997
 *
 * Copyright (c) 1996 John Shअगरflett, GeoLog Consulting
 *    john@geolog.com
 *    jshअगरfle@netcom.com
 */
#अगर_अघोषित WD33C93_H
#घोषणा WD33C93_H


#घोषणा PROC_INTERFACE     /* add code क्रम /proc/scsi/wd33c93/xxx पूर्णांकerface */
#अगर_घोषित  PROC_INTERFACE
#घोषणा PROC_STATISTICS    /* add code क्रम keeping various real समय stats */
#पूर्ण_अगर

#घोषणा SYNC_DEBUG         /* extra info on sync negotiation prपूर्णांकed */
#घोषणा DEBUGGING_ON       /* enable command-line debugging biपंचांगask */
#घोषणा DEBUG_DEFAULTS 0   /* शेष debugging biपंचांगask */


#अगर_घोषित DEBUGGING_ON
#घोषणा DB(f,a) अगर (hostdata->args & (f)) a;
#अन्यथा
#घोषणा DB(f,a)
#पूर्ण_अगर

#घोषणा uअक्षर अचिन्हित अक्षर


/* wd रेजिस्टर names */
#घोषणा WD_OWN_ID    0x00
#घोषणा WD_CONTROL      0x01
#घोषणा WD_TIMEOUT_PERIOD  0x02
#घोषणा WD_CDB_1     0x03
#घोषणा WD_CDB_2     0x04
#घोषणा WD_CDB_3     0x05
#घोषणा WD_CDB_4     0x06
#घोषणा WD_CDB_5     0x07
#घोषणा WD_CDB_6     0x08
#घोषणा WD_CDB_7     0x09
#घोषणा WD_CDB_8     0x0a
#घोषणा WD_CDB_9     0x0b
#घोषणा WD_CDB_10    0x0c
#घोषणा WD_CDB_11    0x0d
#घोषणा WD_CDB_12    0x0e
#घोषणा WD_TARGET_LUN      0x0f
#घोषणा WD_COMMAND_PHASE   0x10
#घोषणा WD_SYNCHRONOUS_TRANSFER 0x11
#घोषणा WD_TRANSFER_COUNT_MSB 0x12
#घोषणा WD_TRANSFER_COUNT  0x13
#घोषणा WD_TRANSFER_COUNT_LSB 0x14
#घोषणा WD_DESTINATION_ID  0x15
#घोषणा WD_SOURCE_ID    0x16
#घोषणा WD_SCSI_STATUS     0x17
#घोषणा WD_COMMAND      0x18
#घोषणा WD_DATA      0x19
#घोषणा WD_QUEUE_TAG    0x1a
#घोषणा WD_AUXILIARY_STATUS   0x1f

/* WD commands */
#घोषणा WD_CMD_RESET    0x00
#घोषणा WD_CMD_ABORT    0x01
#घोषणा WD_CMD_ASSERT_ATN  0x02
#घोषणा WD_CMD_NEGATE_ACK  0x03
#घोषणा WD_CMD_DISCONNECT  0x04
#घोषणा WD_CMD_RESELECT    0x05
#घोषणा WD_CMD_SEL_ATN     0x06
#घोषणा WD_CMD_SEL      0x07
#घोषणा WD_CMD_SEL_ATN_XFER   0x08
#घोषणा WD_CMD_SEL_XFER    0x09
#घोषणा WD_CMD_RESEL_RECEIVE  0x0a
#घोषणा WD_CMD_RESEL_SEND  0x0b
#घोषणा WD_CMD_WAIT_SEL_RECEIVE 0x0c
#घोषणा WD_CMD_TRANS_ADDR  0x18
#घोषणा WD_CMD_TRANS_INFO  0x20
#घोषणा WD_CMD_TRANSFER_PAD   0x21
#घोषणा WD_CMD_SBT_MODE    0x80

/* ASR रेजिस्टर */
#घोषणा ASR_INT         (0x80)
#घोषणा ASR_LCI         (0x40)
#घोषणा ASR_BSY         (0x20)
#घोषणा ASR_CIP         (0x10)
#घोषणा ASR_PE          (0x02)
#घोषणा ASR_DBR         (0x01)

/* SCSI Bus Phases */
#घोषणा PHS_DATA_OUT    0x00
#घोषणा PHS_DATA_IN     0x01
#घोषणा PHS_COMMAND     0x02
#घोषणा PHS_STATUS      0x03
#घोषणा PHS_MESS_OUT    0x06
#घोषणा PHS_MESS_IN     0x07

/* Command Status Register definitions */

  /* reset state पूर्णांकerrupts */
#घोषणा CSR_RESET    0x00
#घोषणा CSR_RESET_AF    0x01

  /* successful completion पूर्णांकerrupts */
#घोषणा CSR_RESELECT    0x10
#घोषणा CSR_SELECT      0x11
#घोषणा CSR_SEL_XFER_DONE  0x16
#घोषणा CSR_XFER_DONE      0x18

  /* छोड़ोd or पातed पूर्णांकerrupts */
#घोषणा CSR_MSGIN    0x20
#घोषणा CSR_SDP         0x21
#घोषणा CSR_SEL_ABORT      0x22
#घोषणा CSR_RESEL_ABORT    0x25
#घोषणा CSR_RESEL_ABORT_AM 0x27
#घोषणा CSR_ABORT    0x28

  /* terminated पूर्णांकerrupts */
#घोषणा CSR_INVALID     0x40
#घोषणा CSR_UNEXP_DISC     0x41
#घोषणा CSR_TIMEOUT     0x42
#घोषणा CSR_PARITY      0x43
#घोषणा CSR_PARITY_ATN     0x44
#घोषणा CSR_BAD_STATUS     0x45
#घोषणा CSR_UNEXP    0x48

  /* service required पूर्णांकerrupts */
#घोषणा CSR_RESEL    0x80
#घोषणा CSR_RESEL_AM    0x81
#घोषणा CSR_DISC     0x85
#घोषणा CSR_SRV_REQ     0x88

   /* Own ID/CDB Size रेजिस्टर */
#घोषणा OWNID_EAF    0x08
#घोषणा OWNID_EHP    0x10
#घोषणा OWNID_RAF    0x20
#घोषणा OWNID_FS_8   0x00
#घोषणा OWNID_FS_12  0x40
#घोषणा OWNID_FS_16  0x80

   /* define these so we करोn't have to change a2091.c, etc. */
#घोषणा WD33C93_FS_8_10  OWNID_FS_8
#घोषणा WD33C93_FS_12_15 OWNID_FS_12
#घोषणा WD33C93_FS_16_20 OWNID_FS_16

   /* pass input-घड़ी explicitly. accepted mhz values are 8-10,12-20 */
#घोषणा WD33C93_FS_MHZ(mhz) (mhz)

   /* Control रेजिस्टर */
#घोषणा CTRL_HSP     0x01
#घोषणा CTRL_HA      0x02
#घोषणा CTRL_IDI     0x04
#घोषणा CTRL_EDI     0x08
#घोषणा CTRL_HHP     0x10
#घोषणा CTRL_POLLED  0x00
#घोषणा CTRL_BURST   0x20
#घोषणा CTRL_BUS     0x40
#घोषणा CTRL_DMA     0x80

   /* Timeout Period रेजिस्टर */
#घोषणा TIMEOUT_PERIOD_VALUE  20    /* 20 = 200 ms */

   /* Synchronous Transfer Register */
#घोषणा STR_FSS      0x80

   /* Destination ID रेजिस्टर */
#घोषणा DSTID_DPD    0x40
#घोषणा DATA_OUT_सूची 0
#घोषणा DATA_IN_सूची  1
#घोषणा DSTID_SCC    0x80

   /* Source ID रेजिस्टर */
#घोषणा SRCID_MASK   0x07
#घोषणा SRCID_SIV    0x08
#घोषणा SRCID_DSP    0x20
#घोषणा SRCID_ES     0x40
#घोषणा SRCID_ER     0x80

   /* This is what the 3393 chip looks like to us */
प्रकार काष्ठा अणु
#अगर_घोषित CONFIG_WD33C93_PIO
   अचिन्हित पूर्णांक   SASR;
   अचिन्हित पूर्णांक   SCMD;
#अन्यथा
   अस्थिर अचिन्हित अक्षर  *SASR;
   अस्थिर अचिन्हित अक्षर  *SCMD;
#पूर्ण_अगर
पूर्ण wd33c93_regs;


प्रकार पूर्णांक (*dma_setup_t) (काष्ठा scsi_cmnd *SCpnt, पूर्णांक dir_in);
प्रकार व्योम (*dma_stop_t) (काष्ठा Scsi_Host *instance,
		काष्ठा scsi_cmnd *SCpnt, पूर्णांक status);


#घोषणा ILLEGAL_STATUS_BYTE   0xff

#घोषणा DEFAULT_SX_PER   376     /* (ns) fairly safe */
#घोषणा DEFAULT_SX_OFF   0       /* aka async */

#घोषणा OPTIMUM_SX_PER   252     /* (ns) best we can करो (mult-of-4) */
#घोषणा OPTIMUM_SX_OFF   12      /* size of wd3393 fअगरo */

काष्ठा sx_period अणु
   अचिन्हित पूर्णांक   period_ns;
   uअक्षर          reg_value;
   पूर्ण;

/* FEF: defines क्रम hostdata->dma_buffer_pool */

#घोषणा BUF_CHIP_ALLOCED 0
#घोषणा BUF_SCSI_ALLOCED 1

काष्ठा WD33C93_hostdata अणु
    काष्ठा Scsi_Host *next;
    wd33c93_regs     regs;
    spinlock_t       lock;
    uअक्षर            घड़ी_freq;
    uअक्षर            chip;             /* what kind of wd33c93? */
    uअक्षर            microcode;        /* microcode rev */
    uअक्षर            dma_buffer_pool;  /* FEF: buffer from chip_ram? */
    पूर्णांक              dma_dir;          /* data transfer dir. */
    dma_setup_t      dma_setup;
    dma_stop_t       dma_stop;
    अचिन्हित पूर्णांक     dma_xfer_mask;
    uअक्षर            *dma_bounce_buffer;
    अचिन्हित पूर्णांक     dma_bounce_len;
    अस्थिर uअक्षर   busy[8];          /* index = target, bit = lun */
    अस्थिर काष्ठा scsi_cmnd *input_Q;       /* commands रुकोing to be started */
    अस्थिर काष्ठा scsi_cmnd *selecting;     /* trying to select this command */
    अस्थिर काष्ठा scsi_cmnd *connected;     /* currently connected command */
    अस्थिर काष्ठा scsi_cmnd *disconnected_Q;/* commands रुकोing क्रम reconnect */
    uअक्षर            state;            /* what we are currently करोing */
    uअक्षर            dma;              /* current state of DMA (on/off) */
    uअक्षर            level2;           /* extent to which Level-2 commands are used */
    uअक्षर            disconnect;       /* disconnect/reselect policy */
    अचिन्हित पूर्णांक     args;             /* set from command-line argument */
    uअक्षर            incoming_msg[8];  /* filled during message_in phase */
    पूर्णांक              incoming_ptr;     /* मुख्यly used with EXTENDED messages */
    uअक्षर            outgoing_msg[8];  /* send this during next message_out */
    पूर्णांक              outgoing_len;     /* length of outgoing message */
    अचिन्हित पूर्णांक     शेष_sx_per;   /* शेष transfer period क्रम SCSI bus */
    uअक्षर            sync_xfer[8];     /* sync_xfer reg settings per target */
    uअक्षर            sync_stat[8];     /* status of sync negotiation per target */
    uअक्षर            no_sync;          /* biपंचांगask: करोn't करो sync on these tarमाला_लो */
    uअक्षर            no_dma;           /* set this flag to disable DMA */
    uअक्षर            dma_mode;         /* DMA Burst Mode or Single Byte DMA */
    uअक्षर            fast;             /* set this flag to enable Fast SCSI */
    काष्ठा sx_period sx_table[9];      /* transfer periods क्रम actual DTC-setting */
#अगर_घोषित PROC_INTERFACE
    uअक्षर            proc;             /* biपंचांगask: what's in proc output */
#अगर_घोषित PROC_STATISTICS
    अचिन्हित दीर्घ    cmd_cnt[8];       /* # of commands issued per target */
    अचिन्हित दीर्घ    पूर्णांक_cnt;          /* # of पूर्णांकerrupts serviced */
    अचिन्हित दीर्घ    pio_cnt;          /* # of pio data transfers */
    अचिन्हित दीर्घ    dma_cnt;          /* # of DMA data transfers */
    अचिन्हित दीर्घ    disc_allowed_cnt[8]; /* # of disconnects allowed per target */
    अचिन्हित दीर्घ    disc_करोne_cnt[8]; /* # of disconnects करोne per target*/
#पूर्ण_अगर
#पूर्ण_अगर
    पूर्ण;


/* defines क्रम hostdata->chip */

#घोषणा C_WD33C93       0
#घोषणा C_WD33C93A      1
#घोषणा C_WD33C93B      2
#घोषणा C_UNKNOWN_CHIP  100

/* defines क्रम hostdata->state */

#घोषणा S_UNCONNECTED         0
#घोषणा S_SELECTING           1
#घोषणा S_RUNNING_LEVEL2      2
#घोषणा S_CONNECTED           3
#घोषणा S_PRE_TMP_DISC        4
#घोषणा S_PRE_CMP_DISC        5

/* defines क्रम hostdata->dma */

#घोषणा D_DMA_OFF          0
#घोषणा D_DMA_RUNNING      1

/* defines क्रम hostdata->level2 */
/* NOTE: only the first 3 are implemented so far */

#घोषणा L2_NONE      1  /* no combination commands - we get lots of पूर्णांकs */
#घोषणा L2_SELECT    2  /* start with SEL_ATN_XFER, but never resume it */
#घोषणा L2_BASIC     3  /* resume after STATUS पूर्णांकs & RDP messages */
#घोषणा L2_DATA      4  /* resume after DATA_IN/OUT पूर्णांकs */
#घोषणा L2_MOST      5  /* resume after anything except a RESELECT पूर्णांक */
#घोषणा L2_RESELECT  6  /* resume after everything, including RESELECT पूर्णांकs */
#घोषणा L2_ALL       7  /* always resume */

/* defines क्रम hostdata->disconnect */

#घोषणा DIS_NEVER    0
#घोषणा DIS_ADAPTIVE 1
#घोषणा DIS_ALWAYS   2

/* defines क्रम hostdata->args */

#घोषणा DB_TEST1              1<<0
#घोषणा DB_TEST2              1<<1
#घोषणा DB_QUEUE_COMMAND      1<<2
#घोषणा DB_EXECUTE            1<<3
#घोषणा DB_INTR               1<<4
#घोषणा DB_TRANSFER           1<<5
#घोषणा DB_MASK               0x3f

/* defines क्रम hostdata->sync_stat[] */

#घोषणा SS_UNSET     0
#घोषणा SS_FIRST     1
#घोषणा SS_WAITING   2
#घोषणा SS_SET       3

/* defines क्रम hostdata->proc */

#घोषणा PR_VERSION   1<<0
#घोषणा PR_INFO      1<<1
#घोषणा PR_STATISTICS 1<<2
#घोषणा PR_CONNECTED 1<<3
#घोषणा PR_INPUTQ    1<<4
#घोषणा PR_DISCQ     1<<5
#घोषणा PR_TEST      1<<6
#घोषणा PR_STOP      1<<7


व्योम wd33c93_init (काष्ठा Scsi_Host *instance, स्थिर wd33c93_regs regs,
         dma_setup_t setup, dma_stop_t stop, पूर्णांक घड़ी_freq);
पूर्णांक wd33c93_पात (काष्ठा scsi_cmnd *cmd);
पूर्णांक wd33c93_queuecommand (काष्ठा Scsi_Host *h, काष्ठा scsi_cmnd *cmd);
व्योम wd33c93_पूर्णांकr (काष्ठा Scsi_Host *instance);
पूर्णांक wd33c93_show_info(काष्ठा seq_file *, काष्ठा Scsi_Host *);
पूर्णांक wd33c93_ग_लिखो_info(काष्ठा Scsi_Host *, अक्षर *, पूर्णांक);
पूर्णांक wd33c93_host_reset (काष्ठा scsi_cmnd *);

#पूर्ण_अगर /* WD33C93_H */
