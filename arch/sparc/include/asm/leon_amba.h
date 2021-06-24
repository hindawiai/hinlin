<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
*Copyright (C) 2004 Konrad Eisele (eiselekd@web.de,konrad@gaisler.com), Gaisler Research
*Copyright (C) 2004 Stefan Holst (mail@s-holst.de), Uni-Stuttgart
*Copyright (C) 2009 Daniel Hellstrom (daniel@gaisler.com),Konrad Eisele (konrad@gaisler.com) Aeroflex Gaisler AB
*/

#अगर_अघोषित LEON_AMBA_H_INCLUDE
#घोषणा LEON_AMBA_H_INCLUDE

#अगर_अघोषित __ASSEMBLY__

काष्ठा amba_prom_रेजिस्टरs अणु
	अचिन्हित पूर्णांक phys_addr;	/* The physical address of this रेजिस्टर */
	अचिन्हित पूर्णांक reg_size;	/* How many bytes करोes this रेजिस्टर take up? */
पूर्ण;

#पूर्ण_अगर

/*
 *  The following defines the bits in the LEON UART Status Registers.
 */

#घोषणा LEON_REG_UART_STATUS_DR   0x00000001	/* Data Ready */
#घोषणा LEON_REG_UART_STATUS_TSE  0x00000002	/* TX Send Register Empty */
#घोषणा LEON_REG_UART_STATUS_THE  0x00000004	/* TX Hold Register Empty */
#घोषणा LEON_REG_UART_STATUS_BR   0x00000008	/* Break Error */
#घोषणा LEON_REG_UART_STATUS_OE   0x00000010	/* RX Overrun Error */
#घोषणा LEON_REG_UART_STATUS_PE   0x00000020	/* RX Parity Error */
#घोषणा LEON_REG_UART_STATUS_FE   0x00000040	/* RX Framing Error */
#घोषणा LEON_REG_UART_STATUS_ERR  0x00000078	/* Error Mask */

/*
 *  The following defines the bits in the LEON UART Ctrl Registers.
 */

#घोषणा LEON_REG_UART_CTRL_RE     0x00000001	/* Receiver enable */
#घोषणा LEON_REG_UART_CTRL_TE     0x00000002	/* Transmitter enable */
#घोषणा LEON_REG_UART_CTRL_RI     0x00000004	/* Receiver पूर्णांकerrupt enable */
#घोषणा LEON_REG_UART_CTRL_TI     0x00000008	/* Transmitter irq */
#घोषणा LEON_REG_UART_CTRL_PS     0x00000010	/* Parity select */
#घोषणा LEON_REG_UART_CTRL_PE     0x00000020	/* Parity enable */
#घोषणा LEON_REG_UART_CTRL_FL     0x00000040	/* Flow control enable */
#घोषणा LEON_REG_UART_CTRL_LB     0x00000080	/* Loop Back enable */

#घोषणा LEON3_GPTIMER_EN 1
#घोषणा LEON3_GPTIMER_RL 2
#घोषणा LEON3_GPTIMER_LD 4
#घोषणा LEON3_GPTIMER_IRQEN 8
#घोषणा LEON3_GPTIMER_SEPIRQ 8
#घोषणा LEON3_GPTIMER_TIMERS 0x7

#घोषणा LEON23_REG_TIMER_CONTROL_EN    0x00000001 /* 1 = enable counting */
/* 0 = hold scalar and counter */
#घोषणा LEON23_REG_TIMER_CONTROL_RL    0x00000002 /* 1 = reload at 0 */
						  /* 0 = stop at 0 */
#घोषणा LEON23_REG_TIMER_CONTROL_LD    0x00000004 /* 1 = load counter */
						  /* 0 = no function */
#घोषणा LEON23_REG_TIMER_CONTROL_IQ    0x00000008 /* 1 = irq enable */
						  /* 0 = no function */

/*
 *  The following defines the bits in the LEON PS/2 Status Registers.
 */

#घोषणा LEON_REG_PS2_STATUS_DR   0x00000001	/* Data Ready */
#घोषणा LEON_REG_PS2_STATUS_PE   0x00000002	/* Parity error */
#घोषणा LEON_REG_PS2_STATUS_FE   0x00000004	/* Framing error */
#घोषणा LEON_REG_PS2_STATUS_KI   0x00000008	/* Keyboard inhibit */
#घोषणा LEON_REG_PS2_STATUS_RF   0x00000010	/* RX buffer full */
#घोषणा LEON_REG_PS2_STATUS_TF   0x00000020	/* TX buffer full */

/*
 *  The following defines the bits in the LEON PS/2 Ctrl Registers.
 */

#घोषणा LEON_REG_PS2_CTRL_RE 0x00000001	/* Receiver enable */
#घोषणा LEON_REG_PS2_CTRL_TE 0x00000002	/* Transmitter enable */
#घोषणा LEON_REG_PS2_CTRL_RI 0x00000004	/* Keyboard receive irq  */
#घोषणा LEON_REG_PS2_CTRL_TI 0x00000008	/* Keyboard transmit irq */

#घोषणा LEON3_IRQMPSTATUS_CPUNR     28
#घोषणा LEON3_IRQMPSTATUS_BROADCAST 27

#घोषणा GPTIMER_CONFIG_IRQNT(a)          (((a) >> 3) & 0x1f)
#घोषणा GPTIMER_CONFIG_ISSEP(a)          ((a) & (1 << 8))
#घोषणा GPTIMER_CONFIG_NTIMERS(a)        ((a) & (0x7))
#घोषणा LEON3_GPTIMER_CTRL_PENDING       0x10
#घोषणा LEON3_GPTIMER_CONFIG_NRTIMERS(c) ((c)->config & 0x7)
#घोषणा LEON3_GPTIMER_CTRL_ISPENDING(r)  (((r)&LEON3_GPTIMER_CTRL_PENDING) ? 1 : 0)

#अगर_अघोषित __ASSEMBLY__

काष्ठा leon3_irqctrl_regs_map अणु
	u32 ilevel;
	u32 ipend;
	u32 अगरorce;
	u32 iclear;
	u32 mpstatus;
	u32 mpbroadcast;
	u32 notused02;
	u32 notused03;
	u32 ampctrl;
	u32 icsel[2];
	u32 notused13;
	u32 notused20;
	u32 notused21;
	u32 notused22;
	u32 notused23;
	u32 mask[16];
	u32 क्रमce[16];
	/* Extended IRQ रेजिस्टरs */
	u32 पूर्णांकid[16];	/* 0xc0 */
	u32 unused[(0x1000-0x100)/4];
पूर्ण;

काष्ठा leon3_apbuart_regs_map अणु
	u32 data;
	u32 status;
	u32 ctrl;
	u32 scaler;
पूर्ण;

काष्ठा leon3_gpसमयrelem_regs_map अणु
	u32 val;
	u32 rld;
	u32 ctrl;
	u32 unused;
पूर्ण;

काष्ठा leon3_gpसमयr_regs_map अणु
	u32 scalar;
	u32 scalar_reload;
	u32 config;
	u32 unused;
	काष्ठा leon3_gpसमयrelem_regs_map e[8];
पूर्ण;

/*
 *  Types and काष्ठाure used क्रम AMBA Plug & Play bus scanning
 */

#घोषणा AMBA_MAXAPB_DEVS 64
#घोषणा AMBA_MAXAPB_DEVS_PERBUS 16

काष्ठा amba_device_table अणु
	पूर्णांक devnr;		   /* number of devices on AHB or APB bus */
	अचिन्हित पूर्णांक *addr[16];    /* addresses to the devices configuration tables */
	अचिन्हित पूर्णांक allocbits[1]; /* 0=unallocated, 1=allocated driver */
पूर्ण;

काष्ठा amba_apbslv_device_table अणु
	पूर्णांक devnr;		                  /* number of devices on AHB or APB bus */
	अचिन्हित पूर्णांक *addr[AMBA_MAXAPB_DEVS];     /* addresses to the devices configuration tables */
	अचिन्हित पूर्णांक apbmst[AMBA_MAXAPB_DEVS];    /* apb master अगर a entry is a apb slave */
	अचिन्हित पूर्णांक apbmstidx[AMBA_MAXAPB_DEVS]; /* apb master idx अगर a entry is a apb slave */
	अचिन्हित पूर्णांक allocbits[4];                /* 0=unallocated, 1=allocated driver */
पूर्ण;

काष्ठा amba_confarea_type अणु
	काष्ठा amba_confarea_type *next;/* next bus in chain */
	काष्ठा amba_device_table ahbmst;
	काष्ठा amba_device_table ahbslv;
	काष्ठा amba_apbslv_device_table apbslv;
	अचिन्हित पूर्णांक apbmst;
पूर्ण;

/* collect apb slaves */
काष्ठा amba_apb_device अणु
	अचिन्हित पूर्णांक start, irq, bus_id;
	काष्ठा amba_confarea_type *bus;
पूर्ण;

/* collect ahb slaves */
काष्ठा amba_ahb_device अणु
	अचिन्हित पूर्णांक start[4], irq, bus_id;
	काष्ठा amba_confarea_type *bus;
पूर्ण;

काष्ठा device_node;
व्योम _amba_init(काष्ठा device_node *dp, काष्ठा device_node ***nextp);

बाह्य अचिन्हित दीर्घ amba_प्रणाली_id;
बाह्य काष्ठा leon3_irqctrl_regs_map *leon3_irqctrl_regs;
बाह्य काष्ठा leon3_gpसमयr_regs_map *leon3_gpसमयr_regs;
बाह्य काष्ठा amba_apb_device leon_percpu_समयr_dev[16];
बाह्य पूर्णांक leondebug_irq_disable;
बाह्य पूर्णांक leon_debug_irqout;
बाह्य अचिन्हित दीर्घ leon3_gpसमयr_irq;
बाह्य अचिन्हित पूर्णांक sparc_leon_eirq;

#पूर्ण_अगर /* __ASSEMBLY__ */

#घोषणा LEON3_IO_AREA 0xfff00000
#घोषणा LEON3_CONF_AREA 0xff000
#घोषणा LEON3_AHB_SLAVE_CONF_AREA (1 << 11)

#घोषणा LEON3_AHB_CONF_WORDS 8
#घोषणा LEON3_APB_CONF_WORDS 2
#घोषणा LEON3_AHB_MASTERS 16
#घोषणा LEON3_AHB_SLAVES 16
#घोषणा LEON3_APB_SLAVES 16
#घोषणा LEON3_APBUARTS 8

/* Venकरोr codes */
#घोषणा VENDOR_GAISLER   1
#घोषणा VENDOR_PENDER    2
#घोषणा VENDOR_ESA       4
#घोषणा VENDOR_OPENCORES 8

/* Gaisler Research device id's */
#घोषणा GAISLER_LEON3    0x003
#घोषणा GAISLER_LEON3DSU 0x004
#घोषणा GAISLER_ETHAHB   0x005
#घोषणा GAISLER_APBMST   0x006
#घोषणा GAISLER_AHBUART  0x007
#घोषणा GAISLER_SRCTRL   0x008
#घोषणा GAISLER_SDCTRL   0x009
#घोषणा GAISLER_APBUART  0x00C
#घोषणा GAISLER_IRQMP    0x00D
#घोषणा GAISLER_AHBRAM   0x00E
#घोषणा GAISLER_GPTIMER  0x011
#घोषणा GAISLER_PCITRG   0x012
#घोषणा GAISLER_PCISBRG  0x013
#घोषणा GAISLER_PCIFBRG  0x014
#घोषणा GAISLER_PCITRACE 0x015
#घोषणा GAISLER_PCIDMA   0x016
#घोषणा GAISLER_AHBTRACE 0x017
#घोषणा GAISLER_ETHDSU   0x018
#घोषणा GAISLER_PIOPORT  0x01A
#घोषणा GAISLER_GRGPIO   0x01A
#घोषणा GAISLER_AHBJTAG  0x01c
#घोषणा GAISLER_ETHMAC   0x01D
#घोषणा GAISLER_AHB2AHB  0x020
#घोषणा GAISLER_USBDC    0x021
#घोषणा GAISLER_ATACTRL  0x024
#घोषणा GAISLER_DDRSPA   0x025
#घोषणा GAISLER_USBEHC   0x026
#घोषणा GAISLER_USBUHC   0x027
#घोषणा GAISLER_I2CMST   0x028
#घोषणा GAISLER_SPICTRL  0x02D
#घोषणा GAISLER_DDR2SPA  0x02E
#घोषणा GAISLER_SPIMCTRL 0x045
#घोषणा GAISLER_LEON4    0x048
#घोषणा GAISLER_LEON4DSU 0x049
#घोषणा GAISLER_AHBSTAT  0x052
#घोषणा GAISLER_FTMCTRL  0x054
#घोषणा GAISLER_KBD      0x060
#घोषणा GAISLER_VGA      0x061
#घोषणा GAISLER_SVGA     0x063
#घोषणा GAISLER_GRSYSMON 0x066
#घोषणा GAISLER_GRACECTRL 0x067

#घोषणा GAISLER_L2TIME   0xffd	/* पूर्णांकernal device: leon2 समयr */
#घोषणा GAISLER_L2C      0xffe	/* पूर्णांकernal device: leon2compat */
#घोषणा GAISLER_PLUGPLAY 0xfff	/* पूर्णांकernal device: plug & play configarea */

/* Chip IDs */
#घोषणा AEROFLEX_UT699    0x0699
#घोषणा LEON4_NEXTREME1   0x0102
#घोषणा GAISLER_GR712RC   0x0712

#घोषणा amba_venकरोr(x) (((x) >> 24) & 0xff)

#घोषणा amba_device(x) (((x) >> 12) & 0xfff)

#पूर्ण_अगर
