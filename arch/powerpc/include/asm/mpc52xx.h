<शैली गुरु>
/*
 * Prototypes, etc. क्रम the Freescale MPC52xx embedded cpu chips
 * May need to be cleaned as the port goes on ...
 *
 * Copyright (C) 2004-2005 Sylvain Munaut <tnt@246tNt.com>
 * Copyright (C) 2003 MontaVista, Software, Inc.
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

#अगर_अघोषित __ASM_POWERPC_MPC52xx_H__
#घोषणा __ASM_POWERPC_MPC52xx_H__

#अगर_अघोषित __ASSEMBLY__
#समावेश <यंत्र/types.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/mpc5xxx.h>
#पूर्ण_अगर /* __ASSEMBLY__ */

#समावेश <linux/suspend.h>

/* Variants of the 5200(B) */
#घोषणा MPC5200_SVR		0x80110010
#घोषणा MPC5200_SVR_MASK	0xfffffff0
#घोषणा MPC5200B_SVR		0x80110020
#घोषणा MPC5200B_SVR_MASK	0xfffffff0

/* ======================================================================== */
/* Structures mapping of some unit रेजिस्टर set                             */
/* ======================================================================== */

#अगर_अघोषित __ASSEMBLY__

/* Memory Mapping Control */
काष्ठा mpc52xx_mmap_ctl अणु
	u32 mbar;		/* MMAP_CTRL + 0x00 */

	u32 cs0_start;		/* MMAP_CTRL + 0x04 */
	u32 cs0_stop;		/* MMAP_CTRL + 0x08 */
	u32 cs1_start;		/* MMAP_CTRL + 0x0c */
	u32 cs1_stop;		/* MMAP_CTRL + 0x10 */
	u32 cs2_start;		/* MMAP_CTRL + 0x14 */
	u32 cs2_stop;		/* MMAP_CTRL + 0x18 */
	u32 cs3_start;		/* MMAP_CTRL + 0x1c */
	u32 cs3_stop;		/* MMAP_CTRL + 0x20 */
	u32 cs4_start;		/* MMAP_CTRL + 0x24 */
	u32 cs4_stop;		/* MMAP_CTRL + 0x28 */
	u32 cs5_start;		/* MMAP_CTRL + 0x2c */
	u32 cs5_stop;		/* MMAP_CTRL + 0x30 */

	u32 sdram0;		/* MMAP_CTRL + 0x34 */
	u32 sdram1;		/* MMAP_CTRL + 0X38 */

	u32 reserved[4];	/* MMAP_CTRL + 0x3c .. 0x48 */

	u32 boot_start;		/* MMAP_CTRL + 0x4c */
	u32 boot_stop;		/* MMAP_CTRL + 0x50 */

	u32 ipbi_ws_ctrl;	/* MMAP_CTRL + 0x54 */

	u32 cs6_start;		/* MMAP_CTRL + 0x58 */
	u32 cs6_stop;		/* MMAP_CTRL + 0x5c */
	u32 cs7_start;		/* MMAP_CTRL + 0x60 */
	u32 cs7_stop;		/* MMAP_CTRL + 0x64 */
पूर्ण;

/* SDRAM control */
काष्ठा mpc52xx_sdram अणु
	u32 mode;		/* SDRAM + 0x00 */
	u32 ctrl;		/* SDRAM + 0x04 */
	u32 config1;		/* SDRAM + 0x08 */
	u32 config2;		/* SDRAM + 0x0c */
पूर्ण;

/* SDMA */
काष्ठा mpc52xx_sdma अणु
	u32 taskBar;		/* SDMA + 0x00 */
	u32 currentPoपूर्णांकer;	/* SDMA + 0x04 */
	u32 endPoपूर्णांकer;		/* SDMA + 0x08 */
	u32 variablePoपूर्णांकer;	/* SDMA + 0x0c */

	u8 IntVect1;		/* SDMA + 0x10 */
	u8 IntVect2;		/* SDMA + 0x11 */
	u16 PtdCntrl;		/* SDMA + 0x12 */

	u32 IntPend;		/* SDMA + 0x14 */
	u32 IntMask;		/* SDMA + 0x18 */

	u16 tcr[16];		/* SDMA + 0x1c .. 0x3a */

	u8 ipr[32];		/* SDMA + 0x3c .. 0x5b */

	u32 cReqSelect;		/* SDMA + 0x5c */
	u32 task_size0;		/* SDMA + 0x60 */
	u32 task_size1;		/* SDMA + 0x64 */
	u32 MDEDebug;		/* SDMA + 0x68 */
	u32 ADSDebug;		/* SDMA + 0x6c */
	u32 Value1;		/* SDMA + 0x70 */
	u32 Value2;		/* SDMA + 0x74 */
	u32 Control;		/* SDMA + 0x78 */
	u32 Status;		/* SDMA + 0x7c */
	u32 PTDDebug;		/* SDMA + 0x80 */
पूर्ण;

/* GPT */
काष्ठा mpc52xx_gpt अणु
	u32 mode;		/* GPTx + 0x00 */
	u32 count;		/* GPTx + 0x04 */
	u32 pwm;		/* GPTx + 0x08 */
	u32 status;		/* GPTx + 0X0c */
पूर्ण;

/* GPIO */
काष्ठा mpc52xx_gpio अणु
	u32 port_config;	/* GPIO + 0x00 */
	u32 simple_gpioe;	/* GPIO + 0x04 */
	u32 simple_ode;		/* GPIO + 0x08 */
	u32 simple_ddr;		/* GPIO + 0x0c */
	u32 simple_dvo;		/* GPIO + 0x10 */
	u32 simple_ival;	/* GPIO + 0x14 */
	u8 outo_gpioe;		/* GPIO + 0x18 */
	u8 reserved1[3];	/* GPIO + 0x19 */
	u8 outo_dvo;		/* GPIO + 0x1c */
	u8 reserved2[3];	/* GPIO + 0x1d */
	u8 sपूर्णांक_gpioe;		/* GPIO + 0x20 */
	u8 reserved3[3];	/* GPIO + 0x21 */
	u8 sपूर्णांक_ode;		/* GPIO + 0x24 */
	u8 reserved4[3];	/* GPIO + 0x25 */
	u8 sपूर्णांक_ddr;		/* GPIO + 0x28 */
	u8 reserved5[3];	/* GPIO + 0x29 */
	u8 sपूर्णांक_dvo;		/* GPIO + 0x2c */
	u8 reserved6[3];	/* GPIO + 0x2d */
	u8 sपूर्णांक_पूर्णांकen;		/* GPIO + 0x30 */
	u8 reserved7[3];	/* GPIO + 0x31 */
	u16 sपूर्णांक_itype;		/* GPIO + 0x34 */
	u16 reserved8;		/* GPIO + 0x36 */
	u8 gpio_control;	/* GPIO + 0x38 */
	u8 reserved9[3];	/* GPIO + 0x39 */
	u8 sपूर्णांक_istat;		/* GPIO + 0x3c */
	u8 sपूर्णांक_ival;		/* GPIO + 0x3d */
	u8 bus_errs;		/* GPIO + 0x3e */
	u8 reserved10;		/* GPIO + 0x3f */
पूर्ण;

#घोषणा MPC52xx_GPIO_PSC_CONFIG_UART_WITHOUT_CD	4
#घोषणा MPC52xx_GPIO_PSC_CONFIG_UART_WITH_CD	5
#घोषणा MPC52xx_GPIO_PCI_DIS			(1<<15)

/* GPIO with WakeUp*/
काष्ठा mpc52xx_gpio_wkup अणु
	u8 wkup_gpioe;		/* GPIO_WKUP + 0x00 */
	u8 reserved1[3];	/* GPIO_WKUP + 0x03 */
	u8 wkup_ode;		/* GPIO_WKUP + 0x04 */
	u8 reserved2[3];	/* GPIO_WKUP + 0x05 */
	u8 wkup_ddr;		/* GPIO_WKUP + 0x08 */
	u8 reserved3[3];	/* GPIO_WKUP + 0x09 */
	u8 wkup_dvo;		/* GPIO_WKUP + 0x0C */
	u8 reserved4[3];	/* GPIO_WKUP + 0x0D */
	u8 wkup_पूर्णांकen;		/* GPIO_WKUP + 0x10 */
	u8 reserved5[3];	/* GPIO_WKUP + 0x11 */
	u8 wkup_iपूर्णांकen;		/* GPIO_WKUP + 0x14 */
	u8 reserved6[3];	/* GPIO_WKUP + 0x15 */
	u16 wkup_itype;		/* GPIO_WKUP + 0x18 */
	u8 reserved7[2];	/* GPIO_WKUP + 0x1A */
	u8 wkup_maste;		/* GPIO_WKUP + 0x1C */
	u8 reserved8[3];	/* GPIO_WKUP + 0x1D */
	u8 wkup_ival;		/* GPIO_WKUP + 0x20 */
	u8 reserved9[3];	/* GPIO_WKUP + 0x21 */
	u8 wkup_istat;		/* GPIO_WKUP + 0x24 */
	u8 reserved10[3];	/* GPIO_WKUP + 0x25 */
पूर्ण;

/* XLB Bus control */
काष्ठा mpc52xx_xlb अणु
	u8 reserved[0x40];
	u32 config;		/* XLB + 0x40 */
	u32 version;		/* XLB + 0x44 */
	u32 status;		/* XLB + 0x48 */
	u32 पूर्णांक_enable;		/* XLB + 0x4c */
	u32 addr_capture;	/* XLB + 0x50 */
	u32 bus_sig_capture;	/* XLB + 0x54 */
	u32 addr_समयout;	/* XLB + 0x58 */
	u32 data_समयout;	/* XLB + 0x5c */
	u32 bus_act_समयout;	/* XLB + 0x60 */
	u32 master_pri_enable;	/* XLB + 0x64 */
	u32 master_priority;	/* XLB + 0x68 */
	u32 base_address;	/* XLB + 0x6c */
	u32 snoop_winकरोw;	/* XLB + 0x70 */
पूर्ण;

#घोषणा MPC52xx_XLB_CFG_PLDIS		(1 << 31)
#घोषणा MPC52xx_XLB_CFG_SNOOP		(1 << 15)

/* Clock Distribution control */
काष्ठा mpc52xx_cdm अणु
	u32 jtag_id;		/* CDM + 0x00  reg0 पढ़ो only */
	u32 rstcfg;		/* CDM + 0x04  reg1 पढ़ो only */
	u32 bपढ़ोcrumb;		/* CDM + 0x08  reg2 */

	u8 mem_clk_sel;		/* CDM + 0x0c  reg3 byte0 */
	u8 xlb_clk_sel;		/* CDM + 0x0d  reg3 byte1 पढ़ो only */
	u8 ipb_clk_sel;		/* CDM + 0x0e  reg3 byte2 */
	u8 pci_clk_sel;		/* CDM + 0x0f  reg3 byte3 */

	u8 ext_48mhz_en;	/* CDM + 0x10  reg4 byte0 */
	u8 fd_enable;		/* CDM + 0x11  reg4 byte1 */
	u16 fd_counters;	/* CDM + 0x12  reg4 byte2,3 */

	u32 clk_enables;	/* CDM + 0x14  reg5 */

	u8 osc_disable;		/* CDM + 0x18  reg6 byte0 */
	u8 reserved0[3];	/* CDM + 0x19  reg6 byte1,2,3 */

	u8 ccs_sleep_enable;	/* CDM + 0x1c  reg7 byte0 */
	u8 osc_sleep_enable;	/* CDM + 0x1d  reg7 byte1 */
	u8 reserved1;		/* CDM + 0x1e  reg7 byte2 */
	u8 ccs_qreq_test;	/* CDM + 0x1f  reg7 byte3 */

	u8 soft_reset;		/* CDM + 0x20  u8 byte0 */
	u8 no_ckstp;		/* CDM + 0x21  u8 byte0 */
	u8 reserved2[2];	/* CDM + 0x22  u8 byte1,2,3 */

	u8 pll_lock;		/* CDM + 0x24  reg9 byte0 */
	u8 pll_looselock;	/* CDM + 0x25  reg9 byte1 */
	u8 pll_sm_lockwin;	/* CDM + 0x26  reg9 byte2 */
	u8 reserved3;		/* CDM + 0x27  reg9 byte3 */

	u16 reserved4;		/* CDM + 0x28  reg10 byte0,1 */
	u16 mclken_भाग_psc1;	/* CDM + 0x2a  reg10 byte2,3 */

	u16 reserved5;		/* CDM + 0x2c  reg11 byte0,1 */
	u16 mclken_भाग_psc2;	/* CDM + 0x2e  reg11 byte2,3 */

	u16 reserved6;		/* CDM + 0x30  reg12 byte0,1 */
	u16 mclken_भाग_psc3;	/* CDM + 0x32  reg12 byte2,3 */

	u16 reserved7;		/* CDM + 0x34  reg13 byte0,1 */
	u16 mclken_भाग_psc6;	/* CDM + 0x36  reg13 byte2,3 */
पूर्ण;

/* Interrupt controller Register set */
काष्ठा mpc52xx_पूर्णांकr अणु
	u32 per_mask;		/* INTR + 0x00 */
	u32 per_pri1;		/* INTR + 0x04 */
	u32 per_pri2;		/* INTR + 0x08 */
	u32 per_pri3;		/* INTR + 0x0c */
	u32 ctrl;		/* INTR + 0x10 */
	u32 मुख्य_mask;		/* INTR + 0x14 */
	u32 मुख्य_pri1;		/* INTR + 0x18 */
	u32 मुख्य_pri2;		/* INTR + 0x1c */
	u32 reserved1;		/* INTR + 0x20 */
	u32 enc_status;		/* INTR + 0x24 */
	u32 crit_status;	/* INTR + 0x28 */
	u32 मुख्य_status;	/* INTR + 0x2c */
	u32 per_status;		/* INTR + 0x30 */
	u32 reserved2;		/* INTR + 0x34 */
	u32 per_error;		/* INTR + 0x38 */
पूर्ण;

#पूर्ण_अगर /* __ASSEMBLY__ */


/* ========================================================================= */
/* Prototypes क्रम MPC52xx sysdev                                             */
/* ========================================================================= */

#अगर_अघोषित __ASSEMBLY__

/* mpc52xx_common.c */
बाह्य व्योम mpc5200_setup_xlb_arbiter(व्योम);
बाह्य व्योम mpc52xx_declare_of_platक्रमm_devices(व्योम);
बाह्य पूर्णांक mpc5200_psc_ac97_gpio_reset(पूर्णांक psc_number);
बाह्य व्योम mpc52xx_map_common_devices(व्योम);
बाह्य पूर्णांक mpc52xx_set_psc_clkभाग(पूर्णांक psc_id, पूर्णांक clkभाग);
बाह्य अचिन्हित पूर्णांक mpc52xx_get_xtal_freq(काष्ठा device_node *node);
बाह्य व्योम __noवापस mpc52xx_restart(अक्षर *cmd);

/* mpc52xx_gpt.c */
काष्ठा mpc52xx_gpt_priv;
बाह्य काष्ठा mpc52xx_gpt_priv *mpc52xx_gpt_from_irq(पूर्णांक irq);
बाह्य पूर्णांक mpc52xx_gpt_start_समयr(काष्ठा mpc52xx_gpt_priv *gpt, u64 period,
                            पूर्णांक continuous);
बाह्य u64 mpc52xx_gpt_समयr_period(काष्ठा mpc52xx_gpt_priv *gpt);
बाह्य पूर्णांक mpc52xx_gpt_stop_समयr(काष्ठा mpc52xx_gpt_priv *gpt);

/* mpc52xx_lpbfअगरo.c */
#घोषणा MPC52XX_LPBFIFO_FLAG_READ		(0)
#घोषणा MPC52XX_LPBFIFO_FLAG_WRITE		(1<<0)
#घोषणा MPC52XX_LPBFIFO_FLAG_NO_INCREMENT	(1<<1)
#घोषणा MPC52XX_LPBFIFO_FLAG_NO_DMA		(1<<2)
#घोषणा MPC52XX_LPBFIFO_FLAG_POLL_DMA		(1<<3)

काष्ठा mpc52xx_lpbfअगरo_request अणु
	काष्ठा list_head list;

	/* localplus bus address */
	अचिन्हित पूर्णांक cs;
	माप_प्रकार offset;

	/* Memory address */
	व्योम *data;
	phys_addr_t data_phys;

	/* Details of transfer */
	माप_प्रकार size;
	माप_प्रकार pos;	/* current position of transfer */
	पूर्णांक flags;
	पूर्णांक defer_xfer_start;

	/* What to करो when finished */
	व्योम (*callback)(काष्ठा mpc52xx_lpbfअगरo_request *);

	व्योम *priv;		/* Driver निजी data */

	/* statistics */
	पूर्णांक irq_count;
	पूर्णांक irq_ticks;
	u8 last_byte;
	पूर्णांक buffer_not_करोne_cnt;
पूर्ण;

बाह्य पूर्णांक mpc52xx_lpbfअगरo_submit(काष्ठा mpc52xx_lpbfअगरo_request *req);
बाह्य व्योम mpc52xx_lpbfअगरo_पात(काष्ठा mpc52xx_lpbfअगरo_request *req);
बाह्य व्योम mpc52xx_lpbfअगरo_poll(व्योम);
बाह्य पूर्णांक mpc52xx_lpbfअगरo_start_xfer(काष्ठा mpc52xx_lpbfअगरo_request *req);

/* mpc52xx_pic.c */
बाह्य व्योम mpc52xx_init_irq(व्योम);
बाह्य अचिन्हित पूर्णांक mpc52xx_get_irq(व्योम);

/* mpc52xx_pci.c */
#अगर_घोषित CONFIG_PCI
बाह्य पूर्णांक __init mpc52xx_add_bridge(काष्ठा device_node *node);
बाह्य व्योम __init mpc52xx_setup_pci(व्योम);
#अन्यथा
अटल अंतरभूत व्योम mpc52xx_setup_pci(व्योम) अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __ASSEMBLY__ */

#अगर_घोषित CONFIG_PM
काष्ठा mpc52xx_suspend अणु
	व्योम (*board_suspend_prepare)(व्योम __iomem *mbar);
	व्योम (*board_resume_finish)(व्योम __iomem *mbar);
पूर्ण;

बाह्य काष्ठा mpc52xx_suspend mpc52xx_suspend;
बाह्य पूर्णांक __init mpc52xx_pm_init(व्योम);
बाह्य पूर्णांक mpc52xx_set_wakeup_gpio(u8 pin, u8 level);

/* lite5200 calls mpc5200 suspend functions, so here they are */
बाह्य पूर्णांक mpc52xx_pm_prepare(व्योम);
बाह्य पूर्णांक mpc52xx_pm_enter(suspend_state_t);
बाह्य व्योम mpc52xx_pm_finish(व्योम);
बाह्य अक्षर saved_sram[0x4000]; /* reuse buffer from mpc52xx suspend */

#अगर_घोषित CONFIG_PPC_LITE5200
पूर्णांक __init lite5200_pm_init(व्योम);
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_PM */

#पूर्ण_अगर /* __ASM_POWERPC_MPC52xx_H__ */

