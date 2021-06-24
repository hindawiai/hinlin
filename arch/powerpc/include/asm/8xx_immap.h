<शैली गुरु>
/*
 * MPC8xx Internal Memory Map
 * Copyright (c) 1997 Dan Malek (dmalek@jlc.net)
 *
 * The I/O on the MPC860 is comprised of blocks of special रेजिस्टरs
 * and the dual port ram क्रम the Communication Processor Module.
 * Within this space are functional units such as the SIU, memory
 * controller, प्रणाली समयrs, and other control functions.  It is
 * a combination that I found dअगरficult to separate पूर्णांकo logical
 * functional files.....but anyone अन्यथा is welcome to try.  -- Dan
 */
#अगर_घोषित __KERNEL__
#अगर_अघोषित __IMMAP_8XX__
#घोषणा __IMMAP_8XX__

/* System configuration रेजिस्टरs.
*/
प्रकार	काष्ठा sys_conf अणु
	uपूर्णांक	sc_siumcr;
	uपूर्णांक	sc_sypcr;
	uपूर्णांक	sc_swt;
	अक्षर	res1[2];
	uलघु	sc_swsr;
	uपूर्णांक	sc_sipend;
	uपूर्णांक	sc_simask;
	uपूर्णांक	sc_siel;
	uपूर्णांक	sc_sivec;
	uपूर्णांक	sc_tesr;
	अक्षर	res2[0xc];
	uपूर्णांक	sc_sdcr;
	अक्षर	res3[0x4c];
पूर्ण sysconf8xx_t;

/* PCMCIA configuration रेजिस्टरs.
*/
प्रकार काष्ठा pcmcia_conf अणु
	uपूर्णांक	pcmc_pbr0;
	uपूर्णांक	pcmc_por0;
	uपूर्णांक	pcmc_pbr1;
	uपूर्णांक	pcmc_por1;
	uपूर्णांक	pcmc_pbr2;
	uपूर्णांक	pcmc_por2;
	uपूर्णांक	pcmc_pbr3;
	uपूर्णांक	pcmc_por3;
	uपूर्णांक	pcmc_pbr4;
	uपूर्णांक	pcmc_por4;
	uपूर्णांक	pcmc_pbr5;
	uपूर्णांक	pcmc_por5;
	uपूर्णांक	pcmc_pbr6;
	uपूर्णांक	pcmc_por6;
	uपूर्णांक	pcmc_pbr7;
	uपूर्णांक	pcmc_por7;
	अक्षर	res1[0x20];
	uपूर्णांक	pcmc_pgcra;
	uपूर्णांक	pcmc_pgcrb;
	uपूर्णांक	pcmc_pscr;
	अक्षर	res2[4];
	uपूर्णांक	pcmc_pipr;
	अक्षर	res3[4];
	uपूर्णांक	pcmc_per;
	अक्षर	res4[4];
पूर्ण pcmconf8xx_t;

/* Memory controller रेजिस्टरs.
*/
प्रकार काष्ठा	mem_ctlr अणु
	uपूर्णांक	memc_br0;
	uपूर्णांक	memc_or0;
	uपूर्णांक	memc_br1;
	uपूर्णांक	memc_or1;
	uपूर्णांक	memc_br2;
	uपूर्णांक	memc_or2;
	uपूर्णांक	memc_br3;
	uपूर्णांक	memc_or3;
	uपूर्णांक	memc_br4;
	uपूर्णांक	memc_or4;
	uपूर्णांक	memc_br5;
	uपूर्णांक	memc_or5;
	uपूर्णांक	memc_br6;
	uपूर्णांक	memc_or6;
	uपूर्णांक	memc_br7;
	uपूर्णांक	memc_or7;
	अक्षर	res1[0x24];
	uपूर्णांक	memc_mar;
	uपूर्णांक	memc_mcr;
	अक्षर	res2[4];
	uपूर्णांक	memc_mamr;
	uपूर्णांक	memc_mbmr;
	uलघु	memc_mstat;
	uलघु	memc_mptpr;
	uपूर्णांक	memc_mdr;
	अक्षर	res3[0x80];
पूर्ण memctl8xx_t;

/*-----------------------------------------------------------------------
 * BR - Memory Controller: Base Register					16-9
 */
#घोषणा BR_BA_MSK	0xffff8000	/* Base Address Mask			*/
#घोषणा BR_AT_MSK	0x00007000	/* Address Type Mask			*/
#घोषणा BR_PS_MSK	0x00000c00	/* Port Size Mask			*/
#घोषणा BR_PS_32	0x00000000	/* 32 bit port size			*/
#घोषणा BR_PS_16	0x00000800	/* 16 bit port size			*/
#घोषणा BR_PS_8		0x00000400	/*  8 bit port size			*/
#घोषणा BR_PARE		0x00000200	/* Parity Enable			*/
#घोषणा BR_WP		0x00000100	/* Write Protect			*/
#घोषणा BR_MS_MSK	0x000000c0	/* Machine Select Mask			*/
#घोषणा BR_MS_GPCM	0x00000000	/* G.P.C.M. Machine Select		*/
#घोषणा BR_MS_UPMA	0x00000080	/* U.P.M.A Machine Select		*/
#घोषणा BR_MS_UPMB	0x000000c0	/* U.P.M.B Machine Select		*/
#घोषणा BR_V		0x00000001	/* Bank Valid				*/

/*-----------------------------------------------------------------------
 * OR - Memory Controller: Option Register				16-11
 */
#घोषणा OR_AM_MSK	0xffff8000	/* Address Mask Mask			*/
#घोषणा OR_ATM_MSK	0x00007000	/* Address Type Mask Mask		*/
#घोषणा OR_CSNT_SAM	0x00000800	/* Chip Select Negation Time/ Start	*/
					/* Address Multiplex			*/
#घोषणा OR_ACS_MSK	0x00000600	/* Address to Chip Select Setup mask	*/
#घोषणा OR_ACS_DIV1	0x00000000	/* CS is output at the same समय	*/
#घोषणा OR_ACS_DIV4	0x00000400	/* CS is output 1/4 a घड़ी later	*/
#घोषणा OR_ACS_DIV2	0x00000600	/* CS is output 1/2 a घड़ी later	*/
#घोषणा OR_G5LA		0x00000400	/* Output #GPL5 on #GPL_A5		*/
#घोषणा OR_G5LS		0x00000200	/* Drive #GPL high on falling edge of...*/
#घोषणा OR_BI		0x00000100	/* Burst inhibit			*/
#घोषणा OR_SCY_MSK	0x000000f0	/* Cycle Length in Clocks		*/
#घोषणा OR_SCY_0_CLK	0x00000000	/* 0 घड़ी cycles रुको states		*/
#घोषणा OR_SCY_1_CLK	0x00000010	/* 1 घड़ी cycles रुको states		*/
#घोषणा OR_SCY_2_CLK	0x00000020	/* 2 घड़ी cycles रुको states		*/
#घोषणा OR_SCY_3_CLK	0x00000030	/* 3 घड़ी cycles रुको states		*/
#घोषणा OR_SCY_4_CLK	0x00000040	/* 4 घड़ी cycles रुको states		*/
#घोषणा OR_SCY_5_CLK	0x00000050	/* 5 घड़ी cycles रुको states		*/
#घोषणा OR_SCY_6_CLK	0x00000060	/* 6 घड़ी cycles रुको states		*/
#घोषणा OR_SCY_7_CLK	0x00000070	/* 7 घड़ी cycles रुको states		*/
#घोषणा OR_SCY_8_CLK	0x00000080	/* 8 घड़ी cycles रुको states		*/
#घोषणा OR_SCY_9_CLK	0x00000090	/* 9 घड़ी cycles रुको states		*/
#घोषणा OR_SCY_10_CLK	0x000000a0	/* 10 घड़ी cycles रुको states		*/
#घोषणा OR_SCY_11_CLK	0x000000b0	/* 11 घड़ी cycles रुको states		*/
#घोषणा OR_SCY_12_CLK	0x000000c0	/* 12 घड़ी cycles रुको states		*/
#घोषणा OR_SCY_13_CLK	0x000000d0	/* 13 घड़ी cycles रुको states		*/
#घोषणा OR_SCY_14_CLK	0x000000e0	/* 14 घड़ी cycles रुको states		*/
#घोषणा OR_SCY_15_CLK	0x000000f0	/* 15 घड़ी cycles रुको states		*/
#घोषणा OR_SETA		0x00000008	/* External Transfer Acknowledge	*/
#घोषणा OR_TRLX		0x00000004	/* Timing Relaxed			*/
#घोषणा OR_EHTR		0x00000002	/* Extended Hold Time on Read		*/

/* System Integration Timers.
*/
प्रकार काष्ठा	sys_पूर्णांक_समयrs अणु
	uलघु	sit_tbscr;
	अक्षर	res0[0x02];
	uपूर्णांक	sit_tbreff0;
	uपूर्णांक	sit_tbreff1;
	अक्षर	res1[0x14];
	uलघु	sit_rtcsc;
	अक्षर	res2[0x02];
	uपूर्णांक	sit_rtc;
	uपूर्णांक	sit_rtsec;
	uपूर्णांक	sit_rtcal;
	अक्षर	res3[0x10];
	uलघु	sit_piscr;
	अक्षर	res4[2];
	uपूर्णांक	sit_pitc;
	uपूर्णांक	sit_pitr;
	अक्षर	res5[0x34];
पूर्ण sit8xx_t;

#घोषणा TBSCR_TBIRQ_MASK	((uलघु)0xff00)
#घोषणा TBSCR_REFA		((uलघु)0x0080)
#घोषणा TBSCR_REFB		((uलघु)0x0040)
#घोषणा TBSCR_REFAE		((uलघु)0x0008)
#घोषणा TBSCR_REFBE		((uलघु)0x0004)
#घोषणा TBSCR_TBF		((uलघु)0x0002)
#घोषणा TBSCR_TBE		((uलघु)0x0001)

#घोषणा RTCSC_RTCIRQ_MASK	((uलघु)0xff00)
#घोषणा RTCSC_SEC		((uलघु)0x0080)
#घोषणा RTCSC_ALR		((uलघु)0x0040)
#घोषणा RTCSC_38K		((uलघु)0x0010)
#घोषणा RTCSC_SIE		((uलघु)0x0008)
#घोषणा RTCSC_ALE		((uलघु)0x0004)
#घोषणा RTCSC_RTF		((uलघु)0x0002)
#घोषणा RTCSC_RTE		((uलघु)0x0001)

#घोषणा PISCR_PIRQ_MASK		((uलघु)0xff00)
#घोषणा PISCR_PS		((uलघु)0x0080)
#घोषणा PISCR_PIE		((uलघु)0x0004)
#घोषणा PISCR_PTF		((uलघु)0x0002)
#घोषणा PISCR_PTE		((uलघु)0x0001)

/* Clocks and Reset.
*/
प्रकार काष्ठा clk_and_reset अणु
	uपूर्णांक	car_sccr;
	uपूर्णांक	car_plprcr;
	uपूर्णांक	car_rsr;
	अक्षर	res[0x74];        /* Reserved area                  */
पूर्ण car8xx_t;

/* System Integration Timers keys.
*/
प्रकार काष्ठा sitk अणु
	uपूर्णांक	sitk_tbscrk;
	uपूर्णांक	sitk_tbreff0k;
	uपूर्णांक	sitk_tbreff1k;
	uपूर्णांक	sitk_tbk;
	अक्षर	res1[0x10];
	uपूर्णांक	sitk_rtcsck;
	uपूर्णांक	sitk_rtck;
	uपूर्णांक	sitk_rtseck;
	uपूर्णांक	sitk_rtcalk;
	अक्षर	res2[0x10];
	uपूर्णांक	sitk_piscrk;
	uपूर्णांक	sitk_pitck;
	अक्षर	res3[0x38];
पूर्ण sitk8xx_t;

/* Clocks and reset keys.
*/
प्रकार काष्ठा cark अणु
	uपूर्णांक	cark_sccrk;
	uपूर्णांक	cark_plprcrk;
	uपूर्णांक	cark_rsrk;
	अक्षर	res[0x474];
पूर्ण cark8xx_t;

/* The key to unlock रेजिस्टरs मुख्यtained by keep-alive घातer.
*/
#घोषणा KAPWR_KEY	((अचिन्हित पूर्णांक)0x55ccaa33)

/* Video पूर्णांकerface.  MPC823 Only.
*/
प्रकार काष्ठा vid823 अणु
	uलघु	vid_vccr;
	uलघु	res1;
	u_अक्षर	vid_vsr;
	u_अक्षर	res2;
	u_अक्षर	vid_vcmr;
	u_अक्षर	res3;
	uपूर्णांक	vid_vbcb;
	uपूर्णांक	res4;
	uपूर्णांक	vid_vfcr0;
	uपूर्णांक	vid_vfaa0;
	uपूर्णांक	vid_vfba0;
	uपूर्णांक	vid_vfcr1;
	uपूर्णांक	vid_vfaa1;
	uपूर्णांक	vid_vfba1;
	u_अक्षर	res5[0x18];
पूर्ण vid823_t;

/* LCD पूर्णांकerface.  823 Only.
*/
प्रकार काष्ठा lcd अणु
	uपूर्णांक	lcd_lccr;
	uपूर्णांक	lcd_lchcr;
	uपूर्णांक	lcd_lcvcr;
	अक्षर	res1[4];
	uपूर्णांक	lcd_lcfaa;
	uपूर्णांक	lcd_lcfba;
	अक्षर	lcd_lcsr;
	अक्षर	res2[0x7];
पूर्ण lcd823_t;

/* I2C
*/
प्रकार काष्ठा i2c अणु
	u_अक्षर	i2c_i2mod;
	अक्षर	res1[3];
	u_अक्षर	i2c_i2add;
	अक्षर	res2[3];
	u_अक्षर	i2c_i2brg;
	अक्षर	res3[3];
	u_अक्षर	i2c_i2com;
	अक्षर	res4[3];
	u_अक्षर	i2c_i2cer;
	अक्षर	res5[3];
	u_अक्षर	i2c_i2cmr;
	अक्षर	res6[0x8b];
पूर्ण i2c8xx_t;

/* DMA control/status रेजिस्टरs.
*/
प्रकार काष्ठा sdma_csr अणु
	अक्षर	res1[4];
	uपूर्णांक	sdma_sdar;
	u_अक्षर	sdma_sdsr;
	अक्षर	res3[3];
	u_अक्षर	sdma_sdmr;
	अक्षर	res4[3];
	u_अक्षर	sdma_idsr1;
	अक्षर	res5[3];
	u_अक्षर	sdma_idmr1;
	अक्षर	res6[3];
	u_अक्षर	sdma_idsr2;
	अक्षर	res7[3];
	u_अक्षर	sdma_idmr2;
	अक्षर	res8[0x13];
पूर्ण sdma8xx_t;

/* Communication Processor Module Interrupt Controller.
*/
प्रकार काष्ठा cpm_ic अणु
	uलघु	cpic_civr;
	अक्षर	res[0xe];
	uपूर्णांक	cpic_cicr;
	uपूर्णांक	cpic_cipr;
	uपूर्णांक	cpic_cimr;
	uपूर्णांक	cpic_cisr;
पूर्ण cpic8xx_t;

/* Input/Output Port control/status रेजिस्टरs.
*/
प्रकार काष्ठा io_port अणु
	uलघु	iop_padir;
	uलघु	iop_papar;
	uलघु	iop_paodr;
	uलघु	iop_padat;
	अक्षर	res1[8];
	uलघु	iop_pcdir;
	uलघु	iop_pcpar;
	uलघु	iop_pcso;
	uलघु	iop_pcdat;
	uलघु	iop_pcपूर्णांक;
	अक्षर	res2[6];
	uलघु	iop_pddir;
	uलघु	iop_pdpar;
	अक्षर	res3[2];
	uलघु	iop_pddat;
	uपूर्णांक	uपंचांगode;
	अक्षर	res4[4];
पूर्ण iop8xx_t;

/* Communication Processor Module Timers
*/
प्रकार काष्ठा cpm_समयrs अणु
	uलघु	cpmt_tgcr;
	अक्षर	res1[0xe];
	uलघु	cpmt_पंचांगr1;
	uलघु	cpmt_पंचांगr2;
	uलघु	cpmt_trr1;
	uलघु	cpmt_trr2;
	uलघु	cpmt_tcr1;
	uलघु	cpmt_tcr2;
	uलघु	cpmt_tcn1;
	uलघु	cpmt_tcn2;
	uलघु	cpmt_पंचांगr3;
	uलघु	cpmt_पंचांगr4;
	uलघु	cpmt_trr3;
	uलघु	cpmt_trr4;
	uलघु	cpmt_tcr3;
	uलघु	cpmt_tcr4;
	uलघु	cpmt_tcn3;
	uलघु	cpmt_tcn4;
	uलघु	cpmt_ter1;
	uलघु	cpmt_ter2;
	uलघु	cpmt_ter3;
	uलघु	cpmt_ter4;
	अक्षर	res2[8];
पूर्ण cpmसमयr8xx_t;

/* Finally, the Communication Processor stuff.....
*/
प्रकार काष्ठा scc अणु		/* Serial communication channels */
	uपूर्णांक	scc_gsmrl;
	uपूर्णांक	scc_gsmrh;
	uलघु	scc_psmr;
	अक्षर	res1[2];
	uलघु	scc_todr;
	uलघु	scc_dsr;
	uलघु	scc_scce;
	अक्षर	res2[2];
	uलघु	scc_sccm;
	अक्षर	res3;
	u_अक्षर	scc_sccs;
	अक्षर	res4[8];
पूर्ण scc_t;

प्रकार काष्ठा smc अणु		/* Serial management channels */
	अक्षर	res1[2];
	uलघु	smc_smcmr;
	अक्षर	res2[2];
	u_अक्षर	smc_smce;
	अक्षर	res3[3];
	u_अक्षर	smc_smcm;
	अक्षर	res4[5];
पूर्ण smc_t;

/* MPC860T Fast Ethernet Controller.  It isn't part of the CPM, but
 * it fits within the address space.
 */

प्रकार काष्ठा fec अणु
	uपूर्णांक	fec_addr_low;		/* lower 32 bits of station address	*/
	uलघु	fec_addr_high;		/* upper 16 bits of station address	*/
	uलघु	res1;			/* reserved				*/
	uपूर्णांक	fec_grp_hash_table_high;	/* upper 32-bits of hash table		*/
	uपूर्णांक	fec_grp_hash_table_low;	/* lower 32-bits of hash table		*/
	uपूर्णांक	fec_r_des_start;	/* beginning of Rx descriptor ring	*/
	uपूर्णांक	fec_x_des_start;	/* beginning of Tx descriptor ring	*/
	uपूर्णांक	fec_r_buff_size;	/* Rx buffer size			*/
	uपूर्णांक	res2[9];		/* reserved				*/
	uपूर्णांक	fec_ecntrl;		/* ethernet control रेजिस्टर		*/
	uपूर्णांक	fec_ievent;		/* पूर्णांकerrupt event रेजिस्टर		*/
	uपूर्णांक	fec_imask;		/* पूर्णांकerrupt mask रेजिस्टर		*/
	uपूर्णांक	fec_ivec;		/* पूर्णांकerrupt level and vector status	*/
	uपूर्णांक	fec_r_des_active;	/* Rx ring updated flag			*/
	uपूर्णांक	fec_x_des_active;	/* Tx ring updated flag			*/
	uपूर्णांक	res3[10];		/* reserved				*/
	uपूर्णांक	fec_mii_data;		/* MII data रेजिस्टर			*/
	uपूर्णांक	fec_mii_speed;		/* MII speed control रेजिस्टर		*/
	uपूर्णांक	res4[17];		/* reserved				*/
	uपूर्णांक	fec_r_bound;		/* end of RAM (पढ़ो-only)		*/
	uपूर्णांक	fec_r_fstart;		/* Rx FIFO start address		*/
	uपूर्णांक	res5[6];		/* reserved				*/
	uपूर्णांक	fec_x_fstart;		/* Tx FIFO start address		*/
	uपूर्णांक	res6[17];		/* reserved				*/
	uपूर्णांक	fec_fun_code;		/* fec SDMA function code		*/
	uपूर्णांक	res7[3];		/* reserved				*/
	uपूर्णांक	fec_r_cntrl;		/* Rx control रेजिस्टर			*/
	uपूर्णांक	fec_r_hash;		/* Rx hash रेजिस्टर			*/
	uपूर्णांक	res8[14];		/* reserved				*/
	uपूर्णांक	fec_x_cntrl;		/* Tx control रेजिस्टर			*/
	uपूर्णांक	res9[0x1e];		/* reserved				*/
पूर्ण fec_t;

/* The FEC and LCD color map share the same address space....
 * I guess we will never see an 823T :-).
 */
जोड़ fec_lcd अणु
	fec_t	fl_un_fec;
	u_अक्षर	fl_un_cmap[0x200];
पूर्ण;

प्रकार काष्ठा comm_proc अणु
	/* General control and status रेजिस्टरs.
	*/
	uलघु	cp_cpcr;
	u_अक्षर	res1[2];
	uलघु	cp_rccr;
	u_अक्षर	res2;
	u_अक्षर	cp_rmds;
	u_अक्षर	res3[4];
	uलघु	cp_cpmcr1;
	uलघु	cp_cpmcr2;
	uलघु	cp_cpmcr3;
	uलघु	cp_cpmcr4;
	u_अक्षर	res4[2];
	uलघु	cp_rter;
	u_अक्षर	res5[2];
	uलघु	cp_rपंचांगr;
	u_अक्षर	res6[0x14];

	/* Baud rate generators.
	*/
	uपूर्णांक	cp_brgc1;
	uपूर्णांक	cp_brgc2;
	uपूर्णांक	cp_brgc3;
	uपूर्णांक	cp_brgc4;

	/* Serial Communication Channels.
	*/
	scc_t	cp_scc[4];

	/* Serial Management Channels.
	*/
	smc_t	cp_smc[2];

	/* Serial Peripheral Interface.
	*/
	uलघु	cp_spmode;
	u_अक्षर	res7[4];
	u_अक्षर	cp_spie;
	u_अक्षर	res8[3];
	u_अक्षर	cp_spim;
	u_अक्षर	res9[2];
	u_अक्षर	cp_spcom;
	u_अक्षर	res10[2];

	/* Parallel Interface Port.
	*/
	u_अक्षर	res11[2];
	uलघु	cp_pipc;
	u_अक्षर	res12[2];
	uलघु	cp_ptpr;
	uपूर्णांक	cp_pbdir;
	uपूर्णांक	cp_pbpar;
	u_अक्षर	res13[2];
	uलघु	cp_pbodr;
	uपूर्णांक	cp_pbdat;

	/* Port E - MPC87x/88x only.
	 */
	uपूर्णांक	cp_pedir;
	uपूर्णांक	cp_pepar;
	uपूर्णांक	cp_peso;
	uपूर्णांक	cp_peodr;
	uपूर्णांक	cp_pedat;

	/* Communications Processor Timing Register -
	   Contains RMII Timing क्रम the FECs on MPC87x/88x only.
	*/
	uपूर्णांक	cp_cptr;

	/* Serial Interface and Time Slot Assignment.
	*/
	uपूर्णांक	cp_simode;
	u_अक्षर	cp_sigmr;
	u_अक्षर	res15;
	u_अक्षर	cp_sistr;
	u_अक्षर	cp_sicmr;
	u_अक्षर	res16[4];
	uपूर्णांक	cp_sicr;
	uपूर्णांक	cp_sirp;
	u_अक्षर	res17[0xc];

	/* 256 bytes of MPC823 video controller RAM array.
	*/
	u_अक्षर	cp_vcram[0x100];
	u_अक्षर	cp_siram[0x200];

	/* The fast ethernet controller is not really part of the CPM,
	 * but it resides in the address space.
	 * The LCD color map is also here.
	 */
	जोड़	fec_lcd	fl_un;
#घोषणा cp_fec		fl_un.fl_un_fec
#घोषणा lcd_cmap	fl_un.fl_un_cmap
	अक्षर	res18[0xE00];

	/* The DUET family has a second FEC here */
	fec_t	cp_fec2;
#घोषणा cp_fec1	cp_fec	/* consistency macro */

	/* Dual Ported RAM follows.
	 * There are many dअगरferent क्रमmats क्रम this memory area
	 * depending upon the devices used and options chosen.
	 * Some processors करोn't have all of it populated.
	 */
	u_अक्षर	cp_dpmem[0x1C00];	/* BD / Data / ucode */
	u_अक्षर	cp_dparam[0x400];	/* Parameter RAM */
पूर्ण cpm8xx_t;

/* Internal memory map.
*/
प्रकार काष्ठा immap अणु
	sysconf8xx_t	im_siu_conf;	/* SIU Configuration */
	pcmconf8xx_t	im_pcmcia;	/* PCMCIA Configuration */
	memctl8xx_t	im_memctl;	/* Memory Controller */
	sit8xx_t	im_sit;		/* System पूर्णांकegration समयrs */
	car8xx_t	im_clkrst;	/* Clocks and reset */
	sitk8xx_t	im_sitk;	/* Sys पूर्णांक समयr keys */
	cark8xx_t	im_clkrstk;	/* Clocks and reset keys */
	vid823_t	im_vid;		/* Video (823 only) */
	lcd823_t	im_lcd;		/* LCD (823 only) */
	i2c8xx_t	im_i2c;		/* I2C control/status */
	sdma8xx_t	im_sdma;	/* SDMA control/status */
	cpic8xx_t	im_cpic;	/* CPM Interrupt Controller */
	iop8xx_t	im_ioport;	/* IO Port control/status */
	cpmसमयr8xx_t	im_cpmसमयr;	/* CPM समयrs */
	cpm8xx_t	im_cpm;		/* Communication processor */
पूर्ण immap_t;

#पूर्ण_अगर /* __IMMAP_8XX__ */
#पूर्ण_अगर /* __KERNEL__ */
