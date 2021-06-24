<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* esp_scsi.h: Defines and काष्ठाures क्रम the ESP driver.
 *
 * Copyright (C) 2007 David S. Miller (davem@davemloft.net)
 */

#अगर_अघोषित _ESP_SCSI_H
#घोषणा _ESP_SCSI_H

					/* Access    Description      Offset */
#घोषणा ESP_TCLOW	0x00UL		/* rw  Low bits transfer count 0x00  */
#घोषणा ESP_TCMED	0x01UL		/* rw  Mid bits transfer count 0x04  */
#घोषणा ESP_FDATA	0x02UL		/* rw  FIFO data bits          0x08  */
#घोषणा ESP_CMD		0x03UL		/* rw  SCSI command bits       0x0c  */
#घोषणा ESP_STATUS	0x04UL		/* ro  ESP status रेजिस्टर     0x10  */
#घोषणा ESP_BUSID	ESP_STATUS	/* wo  BusID क्रम sel/resel     0x10  */
#घोषणा ESP_INTRPT	0x05UL		/* ro  Kind of पूर्णांकerrupt       0x14  */
#घोषणा ESP_TIMEO	ESP_INTRPT	/* wo  Timeout क्रम sel/resel   0x14  */
#घोषणा ESP_SSTEP	0x06UL		/* ro  Sequence step रेजिस्टर  0x18  */
#घोषणा ESP_STP		ESP_SSTEP	/* wo  Transfer period/sync    0x18  */
#घोषणा ESP_FFLAGS	0x07UL		/* ro  Bits current FIFO info  0x1c  */
#घोषणा ESP_SOFF	ESP_FFLAGS	/* wo  Sync offset             0x1c  */
#घोषणा ESP_CFG1	0x08UL		/* rw  First cfg रेजिस्टर      0x20  */
#घोषणा ESP_CFACT	0x09UL		/* wo  Clock conv factor       0x24  */
#घोषणा ESP_STATUS2	ESP_CFACT	/* ro  HME status2 रेजिस्टर    0x24  */
#घोषणा ESP_CTEST	0x0aUL		/* wo  Chip test रेजिस्टर      0x28  */
#घोषणा ESP_CFG2	0x0bUL		/* rw  Second cfg रेजिस्टर     0x2c  */
#घोषणा ESP_CFG3	0x0cUL		/* rw  Third cfg रेजिस्टर      0x30  */
#घोषणा ESP_CFG4	0x0dUL		/* rw  Fourth cfg रेजिस्टर     0x34  */
#घोषणा ESP_TCHI	0x0eUL		/* rw  High bits transf count  0x38  */
#घोषणा ESP_UID		ESP_TCHI	/* ro  Unique ID code          0x38  */
#घोषणा FAS_RLO		ESP_TCHI	/* rw  HME extended counter    0x38  */
#घोषणा ESP_FGRND	0x0fUL		/* rw  Data base क्रम fअगरo      0x3c  */
#घोषणा FAS_RHI		ESP_FGRND	/* rw  HME extended counter    0x3c  */

#घोषणा SBUS_ESP_REG_SIZE	0x40UL

/* Bitfield meanings क्रम the above रेजिस्टरs. */

/* ESP config reg 1, पढ़ो-ग_लिखो, found on all ESP chips */
#घोषणा ESP_CONFIG1_ID        0x07      /* My BUS ID bits */
#घोषणा ESP_CONFIG1_CHTEST    0x08      /* Enable ESP chip tests */
#घोषणा ESP_CONFIG1_PENABLE   0x10      /* Enable parity checks */
#घोषणा ESP_CONFIG1_PARTEST   0x20      /* Parity test mode enabled? */
#घोषणा ESP_CONFIG1_SRRDISAB  0x40      /* Disable SCSI reset reports */
#घोषणा ESP_CONFIG1_SLCABLE   0x80      /* Enable slow cable mode */

/* ESP config reg 2, पढ़ो-ग_लिखो, found only on esp100a+esp200+esp236 chips */
#घोषणा ESP_CONFIG2_DMAPARITY 0x01      /* enable DMA Parity (200,236) */
#घोषणा ESP_CONFIG2_REGPARITY 0x02      /* enable reg Parity (200,236) */
#घोषणा ESP_CONFIG2_BADPARITY 0x04      /* Bad parity target पात  */
#घोषणा ESP_CONFIG2_SCSI2ENAB 0x08      /* Enable SCSI-2 features (tgपंचांगode) */
#घोषणा ESP_CONFIG2_HI        0x10      /* High Impedance DREQ ???  */
#घोषणा ESP_CONFIG2_HMEFENAB  0x10      /* HME features enable */
#घोषणा ESP_CONFIG2_BCM       0x20      /* Enable byte-ctrl (236)   */
#घोषणा ESP_CONFIG2_DISPINT   0x20      /* Disable छोड़ो irq (hme) */
#घोषणा ESP_CONFIG2_FENAB     0x40      /* Enable features (fas100,216) */
#घोषणा ESP_CONFIG2_SPL       0x40      /* Enable status-phase latch (236) */
#घोषणा ESP_CONFIG2_MKDONE    0x40      /* HME magic feature */
#घोषणा ESP_CONFIG2_HME32     0x80      /* HME 32 extended */
#घोषणा ESP_CONFIG2_MAGIC     0xe0      /* Invalid bits... */

/* ESP config रेजिस्टर 3 पढ़ो-ग_लिखो, found only esp236+fas236+fas100a+hme chips */
#घोषणा ESP_CONFIG3_FCLOCK    0x01     /* FAST SCSI घड़ी rate (esp100a/hme) */
#घोषणा ESP_CONFIG3_TEM       0x01     /* Enable thresh-8 mode (esp/fas236)  */
#घोषणा ESP_CONFIG3_FAST      0x02     /* Enable FAST SCSI     (esp100a/hme) */
#घोषणा ESP_CONFIG3_ADMA      0x02     /* Enable alternate-dma (esp/fas236)  */
#घोषणा ESP_CONFIG3_TENB      0x04     /* group2 SCSI2 support (esp100a/hme) */
#घोषणा ESP_CONFIG3_SRB       0x04     /* Save residual byte   (esp/fas236)  */
#घोषणा ESP_CONFIG3_TMS       0x08     /* Three-byte msg's ok  (esp100a/hme) */
#घोषणा ESP_CONFIG3_FCLK      0x08     /* Fast SCSI घड़ी rate (esp/fas236)  */
#घोषणा ESP_CONFIG3_IDMSG     0x10     /* ID message checking  (esp100a/hme) */
#घोषणा ESP_CONFIG3_FSCSI     0x10     /* Enable FAST SCSI     (esp/fas236)  */
#घोषणा ESP_CONFIG3_GTM       0x20     /* group2 SCSI2 support (esp/fas236)  */
#घोषणा ESP_CONFIG3_IDBIT3    0x20     /* Bit 3 of HME SCSI-ID (hme)         */
#घोषणा ESP_CONFIG3_TBMS      0x40     /* Three-byte msg's ok  (esp/fas236)  */
#घोषणा ESP_CONFIG3_EWIDE     0x40     /* Enable Wide-SCSI     (hme)         */
#घोषणा ESP_CONFIG3_IMS       0x80     /* ID msg chk'ng        (esp/fas236)  */
#घोषणा ESP_CONFIG3_OBPUSH    0x80     /* Push odd-byte to dma (hme)         */

/* ESP config रेजिस्टर 4 पढ़ो-ग_लिखो */
#घोषणा ESP_CONFIG4_BBTE      0x01     /* Back-to-back transfers     (fsc)   */
#घोषणा ESP_CONGIG4_TEST      0x02     /* Transfer counter test mode (fsc)   */
#घोषणा ESP_CONFIG4_RADE      0x04     /* Active negation   (am53c974/fsc)   */
#घोषणा ESP_CONFIG4_RAE       0x08     /* Act. negation REQ/ACK (am53c974)   */
#घोषणा ESP_CONFIG4_PWD       0x20     /* Reduced घातer feature (am53c974)   */
#घोषणा ESP_CONFIG4_GE0       0x40     /* Glitch eater bit 0    (am53c974)   */
#घोषणा ESP_CONFIG4_GE1       0x80     /* Glitch eater bit 1    (am53c974)   */

#घोषणा ESP_CONFIG_GE_12NS    (0)
#घोषणा ESP_CONFIG_GE_25NS    (ESP_CONFIG_GE1)
#घोषणा ESP_CONFIG_GE_35NS    (ESP_CONFIG_GE0)
#घोषणा ESP_CONFIG_GE_0NS     (ESP_CONFIG_GE0 | ESP_CONFIG_GE1)

/* ESP command रेजिस्टर पढ़ो-ग_लिखो */
/* Group 1 commands:  These may be sent at any poपूर्णांक in समय to the ESP
 *                    chip.  None of them can generate पूर्णांकerrupts 'cept
 *                    the "SCSI bus reset" command अगर you have not disabled
 *                    SCSI reset पूर्णांकerrupts in the config1 ESP रेजिस्टर.
 */
#घोषणा ESP_CMD_शून्य          0x00     /* Null command, ie. a nop */
#घोषणा ESP_CMD_FLUSH         0x01     /* FIFO Flush */
#घोषणा ESP_CMD_RC            0x02     /* Chip reset */
#घोषणा ESP_CMD_RS            0x03     /* SCSI bus reset */

/* Group 2 commands:  ESP must be an initiator and connected to a target
 *                    क्रम these commands to work.
 */
#घोषणा ESP_CMD_TI            0x10     /* Transfer Inक्रमmation */
#घोषणा ESP_CMD_ICCSEQ        0x11     /* Initiator cmd complete sequence */
#घोषणा ESP_CMD_MOK           0x12     /* Message okie-करोkie */
#घोषणा ESP_CMD_TPAD          0x18     /* Transfer Pad */
#घोषणा ESP_CMD_SATN          0x1a     /* Set ATN */
#घोषणा ESP_CMD_RATN          0x1b     /* De-निश्चित ATN */

/* Group 3 commands:  ESP must be in the MSGOUT or MSGIN state and be connected
 *                    to a target as the initiator क्रम these commands to work.
 */
#घोषणा ESP_CMD_SMSG          0x20     /* Send message */
#घोषणा ESP_CMD_SSTAT         0x21     /* Send status */
#घोषणा ESP_CMD_SDATA         0x22     /* Send data */
#घोषणा ESP_CMD_DSEQ          0x23     /* Disजारी Sequence */
#घोषणा ESP_CMD_TSEQ          0x24     /* Terminate Sequence */
#घोषणा ESP_CMD_TCCSEQ        0x25     /* Target cmd cmplt sequence */
#घोषणा ESP_CMD_DCNCT         0x27     /* Disconnect */
#घोषणा ESP_CMD_RMSG          0x28     /* Receive Message */
#घोषणा ESP_CMD_RCMD          0x29     /* Receive Command */
#घोषणा ESP_CMD_RDATA         0x2a     /* Receive Data */
#घोषणा ESP_CMD_RCSEQ         0x2b     /* Receive cmd sequence */

/* Group 4 commands:  The ESP must be in the disconnected state and must
 *                    not be connected to any tarमाला_लो as initiator क्रम
 *                    these commands to work.
 */
#घोषणा ESP_CMD_RSEL          0x40     /* Reselect */
#घोषणा ESP_CMD_SEL           0x41     /* Select w/o ATN */
#घोषणा ESP_CMD_SELA          0x42     /* Select w/ATN */
#घोषणा ESP_CMD_SELAS         0x43     /* Select w/ATN & STOP */
#घोषणा ESP_CMD_ESEL          0x44     /* Enable selection */
#घोषणा ESP_CMD_DSEL          0x45     /* Disable selections */
#घोषणा ESP_CMD_SA3           0x46     /* Select w/ATN3 */
#घोषणा ESP_CMD_RSEL3         0x47     /* Reselect3 */

/* This bit enables the ESP's DMA on the SBus */
#घोषणा ESP_CMD_DMA           0x80     /* Do DMA? */

/* ESP status रेजिस्टर पढ़ो-only */
#घोषणा ESP_STAT_PIO          0x01     /* IO phase bit */
#घोषणा ESP_STAT_PCD          0x02     /* CD phase bit */
#घोषणा ESP_STAT_PMSG         0x04     /* MSG phase bit */
#घोषणा ESP_STAT_PMASK        0x07     /* Mask of phase bits */
#घोषणा ESP_STAT_TDONE        0x08     /* Transfer Completed */
#घोषणा ESP_STAT_TCNT         0x10     /* Transfer Counter Is Zero */
#घोषणा ESP_STAT_PERR         0x20     /* Parity error */
#घोषणा ESP_STAT_SPAM         0x40     /* Real bad error */
/* This indicates the 'interrupt pending' condition on esp236, it is a reserved
 * bit on other revs of the ESP.
 */
#घोषणा ESP_STAT_INTR         0x80             /* Interrupt */

/* The status रेजिस्टर can be masked with ESP_STAT_PMASK and compared
 * with the following values to determine the current phase the ESP
 * (at least thinks it) is in.  For our purposes we also add our own
 * software 'done' bit क्रम our phase management engine.
 */
#घोषणा ESP_DOP   (0)                                       /* Data Out  */
#घोषणा ESP_DIP   (ESP_STAT_PIO)                            /* Data In   */
#घोषणा ESP_CMDP  (ESP_STAT_PCD)                            /* Command   */
#घोषणा ESP_STATP (ESP_STAT_PCD|ESP_STAT_PIO)               /* Status    */
#घोषणा ESP_MOP   (ESP_STAT_PMSG|ESP_STAT_PCD)              /* Message Out */
#घोषणा ESP_MIP   (ESP_STAT_PMSG|ESP_STAT_PCD|ESP_STAT_PIO) /* Message In */

/* HME only: status 2 रेजिस्टर */
#घोषणा ESP_STAT2_SCHBIT      0x01 /* Upper bits 3-7 of sstep enabled */
#घोषणा ESP_STAT2_FFLAGS      0x02 /* The fअगरo flags are now latched */
#घोषणा ESP_STAT2_XCNT        0x04 /* The transfer counter is latched */
#घोषणा ESP_STAT2_CREGA       0x08 /* The command reg is active now */
#घोषणा ESP_STAT2_WIDE        0x10 /* Interface on this adapter is wide */
#घोषणा ESP_STAT2_F1BYTE      0x20 /* There is one byte at top of fअगरo */
#घोषणा ESP_STAT2_FMSB        0x40 /* Next byte in fअगरo is most signअगरicant */
#घोषणा ESP_STAT2_FEMPTY      0x80 /* FIFO is empty */

/* ESP पूर्णांकerrupt रेजिस्टर पढ़ो-only */
#घोषणा ESP_INTR_S            0x01     /* Select w/o ATN */
#घोषणा ESP_INTR_SATN         0x02     /* Select w/ATN */
#घोषणा ESP_INTR_RSEL         0x04     /* Reselected */
#घोषणा ESP_INTR_FDONE        0x08     /* Function करोne */
#घोषणा ESP_INTR_BSERV        0x10     /* Bus service */
#घोषणा ESP_INTR_DC           0x20     /* Disconnect */
#घोषणा ESP_INTR_IC           0x40     /* Illegal command given */
#घोषणा ESP_INTR_SR           0x80     /* SCSI bus reset detected */

/* ESP sequence step रेजिस्टर पढ़ो-only */
#घोषणा ESP_STEP_VBITS        0x07     /* Valid bits */
#घोषणा ESP_STEP_ASEL         0x00     /* Selection&Arbitrate cmplt */
#घोषणा ESP_STEP_SID          0x01     /* One msg byte sent */
#घोषणा ESP_STEP_NCMD         0x02     /* Was not in command phase */
#घोषणा ESP_STEP_PPC          0x03     /* Early phase chg caused cmnd
                                        * bytes to be lost
                                        */
#घोषणा ESP_STEP_FINI4        0x04     /* Command was sent ok */

/* Ho hum, some ESP's set the step रेजिस्टर to this as well... */
#घोषणा ESP_STEP_FINI5        0x05
#घोषणा ESP_STEP_FINI6        0x06
#घोषणा ESP_STEP_FINI7        0x07

/* ESP chip-test रेजिस्टर पढ़ो-ग_लिखो */
#घोषणा ESP_TEST_TARG         0x01     /* Target test mode */
#घोषणा ESP_TEST_INI          0x02     /* Initiator test mode */
#घोषणा ESP_TEST_TS           0x04     /* Tristate test mode */

/* ESP unique ID रेजिस्टर पढ़ो-only, found on fas236+fas100a only */
#घोषणा ESP_UID_FAM           0xf8     /* ESP family biपंचांगask */

#घोषणा ESP_FAMILY(uid) (((uid) & ESP_UID_FAM) >> 3)

/* Values क्रम the ESP family bits */
#घोषणा ESP_UID_F100A         0x00     /* ESP FAS100A  */
#घोषणा ESP_UID_F236          0x02     /* ESP FAS236   */
#घोषणा ESP_UID_HME           0x0a     /* FAS HME      */
#घोषणा ESP_UID_FSC           0x14     /* NCR/Symbios Logic 53CF9x-2 */

/* ESP fअगरo flags रेजिस्टर पढ़ो-only */
/* Note that the following implies a 16 byte FIFO on the ESP. */
#घोषणा ESP_FF_FBYTES         0x1f     /* Num bytes in FIFO */
#घोषणा ESP_FF_ONOTZERO       0x20     /* offset ctr not zero (esp100) */
#घोषणा ESP_FF_SSTEP          0xe0     /* Sequence step */

/* ESP घड़ी conversion factor रेजिस्टर ग_लिखो-only */
#घोषणा ESP_CCF_F0            0x00     /* 35.01MHz - 40MHz */
#घोषणा ESP_CCF_NEVER         0x01     /* Set it to this and die */
#घोषणा ESP_CCF_F2            0x02     /* 10MHz */
#घोषणा ESP_CCF_F3            0x03     /* 10.01MHz - 15MHz */
#घोषणा ESP_CCF_F4            0x04     /* 15.01MHz - 20MHz */
#घोषणा ESP_CCF_F5            0x05     /* 20.01MHz - 25MHz */
#घोषणा ESP_CCF_F6            0x06     /* 25.01MHz - 30MHz */
#घोषणा ESP_CCF_F7            0x07     /* 30.01MHz - 35MHz */

/* HME only... */
#घोषणा ESP_BUSID_RESELID     0x10
#घोषणा ESP_BUSID_CTR32BIT    0x40

#घोषणा ESP_BUS_TIMEOUT        250     /* In milli-seconds */
#घोषणा ESP_TIMEO_CONST       8192
#घोषणा ESP_NEG_DEFP(mhz, cfact) \
        ((ESP_BUS_TIMEOUT * ((mhz) / 1000)) / (8192 * (cfact)))
#घोषणा ESP_HZ_TO_CYCLE(hertz)  ((1000000000) / ((hertz) / 1000))
#घोषणा ESP_TICK(ccf, cycle)  ((7682 * (ccf) * (cycle) / 1000))

/* For slow to medium speed input घड़ी rates we shoot क्रम 5mb/s, but क्रम high
 * input घड़ी rates we try to करो 10mb/s although I करोn't think a transfer can
 * even run that fast with an ESP even with DMA2 scatter gather pipelining.
 */
#घोषणा SYNC_DEFP_SLOW            0x32   /* 5mb/s  */
#घोषणा SYNC_DEFP_FAST            0x19   /* 10mb/s */

काष्ठा esp_cmd_priv अणु
	पूर्णांक			num_sg;
	पूर्णांक			cur_residue;
	काष्ठा scatterlist	*prv_sg;
	काष्ठा scatterlist	*cur_sg;
	पूर्णांक			tot_residue;
पूर्ण;
#घोषणा ESP_CMD_PRIV(CMD)	((काष्ठा esp_cmd_priv *)(&(CMD)->SCp))

/* NOTE: this क्रमागत is ordered based on chip features! */
क्रमागत esp_rev अणु
	ESP100,  /* NCR53C90 - very broken */
	ESP100A, /* NCR53C90A */
	ESP236,
	FAS236,
	PCSCSI,  /* AM53c974 */
	FSC,     /* NCR/Symbios Logic 53CF9x-2 */
	FAS100A,
	FAST,
	FASHME,
पूर्ण;

काष्ठा esp_cmd_entry अणु
	काष्ठा list_head	list;

	काष्ठा scsi_cmnd	*cmd;

	अचिन्हित पूर्णांक		saved_cur_residue;
	काष्ठा scatterlist	*saved_prv_sg;
	काष्ठा scatterlist	*saved_cur_sg;
	अचिन्हित पूर्णांक		saved_tot_residue;

	u8			flags;
#घोषणा ESP_CMD_FLAG_WRITE	0x01 /* DMA is a ग_लिखो */
#घोषणा ESP_CMD_FLAG_AUTOSENSE	0x04 /* Doing स्वतःmatic REQUEST_SENSE */
#घोषणा ESP_CMD_FLAG_RESIDUAL	0x08 /* AM53c974 BLAST residual */

	u8			tag[2];
	u8			orig_tag[2];

	u8			status;
	u8			message;

	अचिन्हित अक्षर		*sense_ptr;
	अचिन्हित अक्षर		*saved_sense_ptr;
	dma_addr_t		sense_dma;

	काष्ठा completion	*eh_करोne;
पूर्ण;

#घोषणा ESP_DEFAULT_TAGS	16

#घोषणा ESP_MAX_TARGET		16
#घोषणा ESP_MAX_LUN		8
#घोषणा ESP_MAX_TAG		256

काष्ठा esp_lun_data अणु
	काष्ठा esp_cmd_entry	*non_tagged_cmd;
	पूर्णांक			num_tagged;
	पूर्णांक			hold;
	काष्ठा esp_cmd_entry	*tagged_cmds[ESP_MAX_TAG];
पूर्ण;

काष्ठा esp_target_data अणु
	/* These are the ESP_STP, ESP_SOFF, and ESP_CFG3 रेजिस्टर values which
	 * match the currently negotiated settings क्रम this target.  The SCSI
	 * protocol values are मुख्यtained in spi_अणुoffset,period,wideपूर्ण(starget).
	 */
	u8			esp_period;
	u8			esp_offset;
	u8			esp_config3;

	u8			flags;
#घोषणा ESP_TGT_WIDE		0x01
#घोषणा ESP_TGT_DISCONNECT	0x02
#घोषणा ESP_TGT_NEGO_WIDE	0x04
#घोषणा ESP_TGT_NEGO_SYNC	0x08
#घोषणा ESP_TGT_CHECK_NEGO	0x40
#घोषणा ESP_TGT_BROKEN		0x80

	/* When ESP_TGT_CHECK_NEGO is set, on the next scsi command to this
	 * device we will try to negotiate the following parameters.
	 */
	u8			nego_goal_period;
	u8			nego_goal_offset;
	u8			nego_goal_width;
	u8			nego_goal_tags;

	काष्ठा scsi_target	*starget;
पूर्ण;

काष्ठा esp_event_ent अणु
	u8			type;
#घोषणा ESP_EVENT_TYPE_EVENT	0x01
#घोषणा ESP_EVENT_TYPE_CMD	0x02
	u8			val;

	u8			sreg;
	u8			seqreg;
	u8			sreg2;
	u8			ireg;
	u8			select_state;
	u8			event;
	u8			__pad;
पूर्ण;

काष्ठा esp;
काष्ठा esp_driver_ops अणु
	/* Read and ग_लिखो the ESP 8-bit रेजिस्टरs.  On some
	 * applications of the ESP chip the रेजिस्टरs are at 4-byte
	 * instead of 1-byte पूर्णांकervals.
	 */
	व्योम (*esp_ग_लिखो8)(काष्ठा esp *esp, u8 val, अचिन्हित दीर्घ reg);
	u8 (*esp_पढ़ो8)(काष्ठा esp *esp, अचिन्हित दीर्घ reg);

	/* Return non-zero अगर there is an IRQ pending.  Usually this
	 * status bit lives in the DMA controller sitting in front of
	 * the ESP.  This has to be accurate or अन्यथा the ESP पूर्णांकerrupt
	 * handler will not run.
	 */
	पूर्णांक (*irq_pending)(काष्ठा esp *esp);

	/* Return the maximum allowable size of a DMA transfer क्रम a
	 * given buffer.
	 */
	u32 (*dma_length_limit)(काष्ठा esp *esp, u32 dma_addr,
				u32 dma_len);

	/* Reset the DMA engine entirely.  On वापस, ESP पूर्णांकerrupts
	 * should be enabled.  Often the पूर्णांकerrupt enabling is
	 * controlled in the DMA engine.
	 */
	व्योम (*reset_dma)(काष्ठा esp *esp);

	/* Drain any pending DMA in the DMA engine after a transfer.
	 * This is क्रम ग_लिखोs to memory.
	 */
	व्योम (*dma_drain)(काष्ठा esp *esp);

	/* Invalidate the DMA engine after a DMA transfer.  */
	व्योम (*dma_invalidate)(काष्ठा esp *esp);

	/* Setup an ESP command that will use a DMA transfer.
	 * The 'esp_count' specअगरies what transfer length should be
	 * programmed पूर्णांकo the ESP transfer counter रेजिस्टरs, whereas
	 * the 'dma_count' is the length that should be programmed पूर्णांकo
	 * the DMA controller.  Usually they are the same.  If 'write'
	 * is non-zero, this transfer is a ग_लिखो पूर्णांकo memory.  'cmd'
	 * holds the ESP command that should be issued by calling
	 * scsi_esp_cmd() at the appropriate समय जबतक programming
	 * the DMA hardware.
	 */
	व्योम (*send_dma_cmd)(काष्ठा esp *esp, u32 dma_addr, u32 esp_count,
			     u32 dma_count, पूर्णांक ग_लिखो, u8 cmd);

	/* Return non-zero अगर the DMA engine is reporting an error
	 * currently.
	 */
	पूर्णांक (*dma_error)(काष्ठा esp *esp);
पूर्ण;

#घोषणा ESP_MAX_MSG_SZ		8
#घोषणा ESP_EVENT_LOG_SZ	32

#घोषणा ESP_QUICKIRQ_LIMIT	100
#घोषणा ESP_RESELECT_TAG_LIMIT	2500

काष्ठा esp अणु
	व्योम __iomem		*regs;
	व्योम __iomem		*dma_regs;

	स्थिर काष्ठा esp_driver_ops *ops;

	काष्ठा Scsi_Host	*host;
	काष्ठा device		*dev;

	काष्ठा esp_cmd_entry	*active_cmd;

	काष्ठा list_head	queued_cmds;
	काष्ठा list_head	active_cmds;

	u8			*command_block;
	dma_addr_t		command_block_dma;

	अचिन्हित पूर्णांक		data_dma_len;

	/* The following are used to determine the cause of an IRQ. Upon every
	 * IRQ entry we synchronize these with the hardware रेजिस्टरs.
	 */
	u8			sreg;
	u8			seqreg;
	u8			sreg2;
	u8			ireg;

	u32			prev_hme_dmacsr;
	u8			prev_soff;
	u8			prev_stp;
	u8			prev_cfg3;
	u8			num_tags;

	काष्ठा list_head	esp_cmd_pool;

	काष्ठा esp_target_data	target[ESP_MAX_TARGET];

	पूर्णांक			fअगरo_cnt;
	u8			fअगरo[16];

	काष्ठा esp_event_ent	esp_event_log[ESP_EVENT_LOG_SZ];
	पूर्णांक			esp_event_cur;

	u8			msg_out[ESP_MAX_MSG_SZ];
	पूर्णांक			msg_out_len;

	u8			msg_in[ESP_MAX_MSG_SZ];
	पूर्णांक			msg_in_len;

	u8			bursts;
	u8			config1;
	u8			config2;
	u8			config4;

	u8			scsi_id;
	u32			scsi_id_mask;

	क्रमागत esp_rev		rev;

	u32			flags;
#घोषणा ESP_FLAG_DIFFERENTIAL	0x00000001
#घोषणा ESP_FLAG_RESETTING	0x00000002
#घोषणा ESP_FLAG_WIDE_CAPABLE	0x00000008
#घोषणा ESP_FLAG_QUICKIRQ_CHECK	0x00000010
#घोषणा ESP_FLAG_DISABLE_SYNC	0x00000020
#घोषणा ESP_FLAG_USE_FIFO	0x00000040
#घोषणा ESP_FLAG_NO_DMA_MAP	0x00000080

	u8			select_state;
#घोषणा ESP_SELECT_NONE		0x00 /* Not selecting */
#घोषणा ESP_SELECT_BASIC	0x01 /* Select w/o MSGOUT phase */
#घोषणा ESP_SELECT_MSGOUT	0x02 /* Select with MSGOUT */

	/* When we are not selecting, we are expecting an event.  */
	u8			event;
#घोषणा ESP_EVENT_NONE		0x00
#घोषणा ESP_EVENT_CMD_START	0x01
#घोषणा ESP_EVENT_CMD_DONE	0x02
#घोषणा ESP_EVENT_DATA_IN	0x03
#घोषणा ESP_EVENT_DATA_OUT	0x04
#घोषणा ESP_EVENT_DATA_DONE	0x05
#घोषणा ESP_EVENT_MSGIN		0x06
#घोषणा ESP_EVENT_MSGIN_MORE	0x07
#घोषणा ESP_EVENT_MSGIN_DONE	0x08
#घोषणा ESP_EVENT_MSGOUT	0x09
#घोषणा ESP_EVENT_MSGOUT_DONE	0x0a
#घोषणा ESP_EVENT_STATUS	0x0b
#घोषणा ESP_EVENT_FREE_BUS	0x0c
#घोषणा ESP_EVENT_CHECK_PHASE	0x0d
#घोषणा ESP_EVENT_RESET		0x10

	/* Probed in esp_get_घड़ी_params() */
	u32			cfact;
	u32			cfreq;
	u32			ccycle;
	u32			ctick;
	u32			neg_defp;
	u32			sync_defp;

	/* Computed in esp_reset_esp() */
	u32			max_period;
	u32			min_period;
	u32			radelay;

	/* ESP_CMD_SELAS command state */
	u8			*cmd_bytes_ptr;
	पूर्णांक			cmd_bytes_left;

	काष्ठा completion	*eh_reset;

	व्योम			*dma;
	पूर्णांक			dmarev;

	/* These are used by esp_send_pio_cmd() */
	u8 __iomem		*fअगरo_reg;
	पूर्णांक			send_cmd_error;
	u32			send_cmd_residual;
पूर्ण;

/* A front-end driver क्रम the ESP chip should करो the following in
 * it's device probe routine:
 * 1) Allocate the host and निजी area using scsi_host_alloc()
 *    with size 'sizeof(struct esp)'.  The first argument to
 *    scsi_host_alloc() should be &scsi_esp_ढाँचा.
 * 2) Set host->max_id as appropriate.
 * 3) Set esp->host to the scsi_host itself, and esp->dev
 *    to the device object poपूर्णांकer.
 * 4) Hook up esp->ops to the front-end implementation.
 * 5) If the ESP chip supports wide transfers, set ESP_FLAG_WIDE_CAPABLE
 *    in esp->flags.
 * 6) Map the DMA and ESP chip रेजिस्टरs.
 * 7) DMA map the ESP command block, store the DMA address
 *    in esp->command_block_dma.
 * 8) Register the scsi_esp_पूर्णांकr() पूर्णांकerrupt handler.
 * 9) Probe क्रम and provide the following chip properties:
 *    esp->scsi_id (assign to esp->host->this_id too)
 *    esp->scsi_id_mask
 *    If ESP bus is dअगरferential, set ESP_FLAG_DIFFERENTIAL
 *    esp->cfreq
 *    DMA burst bit mask in esp->bursts, अगर necessary
 * 10) Perक्रमm any actions necessary beक्रमe the ESP device can
 *     be programmed क्रम the first समय.  On some configs, क्रम
 *     example, the DMA engine has to be reset beक्रमe ESP can
 *     be programmed.
 * 11) If necessary, call dev_set_drvdata() as needed.
 * 12) Call scsi_esp_रेजिस्टर() with prepared 'esp' काष्ठाure.
 * 13) Check scsi_esp_रेजिस्टर() वापस value, release all resources
 *     अगर an error was वापसed.
 */
बाह्य काष्ठा scsi_host_ढाँचा scsi_esp_ढाँचा;
बाह्य पूर्णांक scsi_esp_रेजिस्टर(काष्ठा esp *);

बाह्य व्योम scsi_esp_unरेजिस्टर(काष्ठा esp *);
बाह्य irqवापस_t scsi_esp_पूर्णांकr(पूर्णांक, व्योम *);
बाह्य व्योम scsi_esp_cmd(काष्ठा esp *, u8);

बाह्य व्योम esp_send_pio_cmd(काष्ठा esp *esp, u32 dma_addr, u32 esp_count,
			     u32 dma_count, पूर्णांक ग_लिखो, u8 cmd);

#पूर्ण_अगर /* !(_ESP_SCSI_H) */
