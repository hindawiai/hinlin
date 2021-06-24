<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * MPC5121 Prototypes and definitions
 */

#अगर_अघोषित __ASM_POWERPC_MPC5121_H__
#घोषणा __ASM_POWERPC_MPC5121_H__

/* MPC512x Reset module रेजिस्टरs */
काष्ठा mpc512x_reset_module अणु
	u32	rcwlr;	/* Reset Configuration Word Low Register */
	u32	rcwhr;	/* Reset Configuration Word High Register */
	u32	reserved1;
	u32	reserved2;
	u32	rsr;	/* Reset Status Register */
	u32	rmr;	/* Reset Mode Register */
	u32	rpr;	/* Reset Protection Register */
	u32	rcr;	/* Reset Control Register */
	u32	rcer;	/* Reset Control Enable Register */
पूर्ण;

/*
 * Clock Control Module
 */
काष्ठा mpc512x_ccm अणु
	u32	spmr;	/* System PLL Mode Register */
	u32	sccr1;	/* System Clock Control Register 1 */
	u32	sccr2;	/* System Clock Control Register 2 */
	u32	scfr1;	/* System Clock Frequency Register 1 */
	u32	scfr2;	/* System Clock Frequency Register 2 */
	u32	scfr2s;	/* System Clock Frequency Shaकरोw Register 2 */
	u32	bcr;	/* Bपढ़ो Crumb Register */
	u32	psc_ccr[12];	/* PSC Clock Control Registers */
	u32	spccr;	/* SPDIF Clock Control Register */
	u32	cccr;	/* CFM Clock Control Register */
	u32	dccr;	/* DIU Clock Control Register */
	u32	mscan_ccr[4];	/* MSCAN Clock Control Registers */
	u32	out_ccr[4];	/* OUT CLK Configure Registers */
	u32	rsv0[2];	/* Reserved */
	u32	scfr3;		/* System Clock Frequency Register 3 */
	u32	rsv1[3];	/* Reserved */
	u32	spll_lock_cnt;	/* System PLL Lock Counter */
	u8	res[0x6c];	/* Reserved */
पूर्ण;

/*
 * LPC Module
 */
काष्ठा mpc512x_lpc अणु
	u32	cs_cfg[8];	/* CS config */
	u32	cs_ctrl;	/* CS Control Register */
	u32	cs_status;	/* CS Status Register */
	u32	burst_ctrl;	/* CS Burst Control Register */
	u32	deadcycle_ctrl;	/* CS Deadcycle Control Register */
	u32	holdcycle_ctrl;	/* CS Holdcycle Control Register */
	u32	alt;		/* Address Latch Timing Register */
पूर्ण;

पूर्णांक mpc512x_cs_config(अचिन्हित पूर्णांक cs, u32 val);

/*
 * SCLPC Module (LPB FIFO)
 */
काष्ठा mpc512x_lpbfअगरo अणु
	u32	pkt_size;	/* SCLPC Packet Size Register */
	u32	start_addr;	/* SCLPC Start Address Register */
	u32	ctrl;		/* SCLPC Control Register */
	u32	enable;		/* SCLPC Enable Register */
	u32	reserved1;
	u32	status;		/* SCLPC Status Register */
	u32	bytes_करोne;	/* SCLPC Bytes Done Register */
	u32	emb_sc;		/* EMB Share Counter Register */
	u32	emb_pc;		/* EMB Pause Control Register */
	u32	reserved2[7];
	u32	data_word;	/* LPC RX/TX FIFO Data Word Register */
	u32	fअगरo_status;	/* LPC RX/TX FIFO Status Register */
	u32	fअगरo_ctrl;	/* LPC RX/TX FIFO Control Register */
	u32	fअगरo_alarm;	/* LPC RX/TX FIFO Alarm Register */
पूर्ण;

#घोषणा MPC512X_SCLPC_START		(1 << 31)
#घोषणा MPC512X_SCLPC_CS(x)		(((x) & 0x7) << 24)
#घोषणा MPC512X_SCLPC_FLUSH		(1 << 17)
#घोषणा MPC512X_SCLPC_READ		(1 << 16)
#घोषणा MPC512X_SCLPC_DAI		(1 << 8)
#घोषणा MPC512X_SCLPC_BPT(x)		((x) & 0x3f)
#घोषणा MPC512X_SCLPC_RESET		(1 << 24)
#घोषणा MPC512X_SCLPC_FIFO_RESET	(1 << 16)
#घोषणा MPC512X_SCLPC_ABORT_INT_ENABLE	(1 << 9)
#घोषणा MPC512X_SCLPC_NORM_INT_ENABLE	(1 << 8)
#घोषणा MPC512X_SCLPC_ENABLE		(1 << 0)
#घोषणा MPC512X_SCLPC_SUCCESS		(1 << 24)
#घोषणा MPC512X_SCLPC_FIFO_CTRL(x)	(((x) & 0x7) << 24)
#घोषणा MPC512X_SCLPC_FIFO_ALARM(x)	((x) & 0x3ff)

क्रमागत lpb_dev_portsize अणु
	LPB_DEV_PORTSIZE_UNDEFINED = 0,
	LPB_DEV_PORTSIZE_1_BYTE = 1,
	LPB_DEV_PORTSIZE_2_BYTES = 2,
	LPB_DEV_PORTSIZE_4_BYTES = 4,
	LPB_DEV_PORTSIZE_8_BYTES = 8
पूर्ण;

क्रमागत mpc512x_lpbfअगरo_req_dir अणु
	MPC512X_LPBFIFO_REQ_सूची_READ,
	MPC512X_LPBFIFO_REQ_सूची_WRITE
पूर्ण;

काष्ठा mpc512x_lpbfअगरo_request अणु
	phys_addr_t dev_phys_addr; /* physical address of some device on LPB */
	व्योम *ram_virt_addr; /* भव address of some region in RAM */
	u32 size;
	क्रमागत lpb_dev_portsize portsize;
	क्रमागत mpc512x_lpbfअगरo_req_dir dir;
	व्योम (*callback)(काष्ठा mpc512x_lpbfअगरo_request *);
पूर्ण;

पूर्णांक mpc512x_lpbfअगरo_submit(काष्ठा mpc512x_lpbfअगरo_request *req);

#पूर्ण_अगर /* __ASM_POWERPC_MPC5121_H__ */
