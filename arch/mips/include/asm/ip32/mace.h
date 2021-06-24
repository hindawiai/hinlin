<शैली गुरु>
/*
 * Definitions क्रम the SGI MACE (Mulसमयdia, Audio and Communications Engine)
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2000 Harald Koerfgen
 * Copyright (C) 2004 Ladislav Michl
 */

#अगर_अघोषित __ASM_MACE_H__
#घोषणा __ASM_MACE_H__

/*
 * Address map
 */
#घोषणा MACE_BASE	0x1f000000	/* physical */

/*
 * PCI पूर्णांकerface
 */
काष्ठा mace_pci अणु
	अस्थिर अचिन्हित पूर्णांक error_addr;
	अस्थिर अचिन्हित पूर्णांक error;
#घोषणा MACEPCI_ERROR_MASTER_ABORT		BIT(31)
#घोषणा MACEPCI_ERROR_TARGET_ABORT		BIT(30)
#घोषणा MACEPCI_ERROR_DATA_PARITY_ERR		BIT(29)
#घोषणा MACEPCI_ERROR_RETRY_ERR			BIT(28)
#घोषणा MACEPCI_ERROR_ILLEGAL_CMD		BIT(27)
#घोषणा MACEPCI_ERROR_SYSTEM_ERR		BIT(26)
#घोषणा MACEPCI_ERROR_INTERRUPT_TEST		BIT(25)
#घोषणा MACEPCI_ERROR_PARITY_ERR		BIT(24)
#घोषणा MACEPCI_ERROR_OVERRUN			BIT(23)
#घोषणा MACEPCI_ERROR_RSVD			BIT(22)
#घोषणा MACEPCI_ERROR_MEMORY_ADDR		BIT(21)
#घोषणा MACEPCI_ERROR_CONFIG_ADDR		BIT(20)
#घोषणा MACEPCI_ERROR_MASTER_ABORT_ADDR_VALID	BIT(19)
#घोषणा MACEPCI_ERROR_TARGET_ABORT_ADDR_VALID	BIT(18)
#घोषणा MACEPCI_ERROR_DATA_PARITY_ADDR_VALID	BIT(17)
#घोषणा MACEPCI_ERROR_RETRY_ADDR_VALID		BIT(16)
#घोषणा MACEPCI_ERROR_SIG_TABORT		BIT(4)
#घोषणा MACEPCI_ERROR_DEVSEL_MASK		0xc0
#घोषणा MACEPCI_ERROR_DEVSEL_FAST		0
#घोषणा MACEPCI_ERROR_DEVSEL_MED		0x40
#घोषणा MACEPCI_ERROR_DEVSEL_SLOW		0x80
#घोषणा MACEPCI_ERROR_FBB			BIT(1)
#घोषणा MACEPCI_ERROR_66MHZ			BIT(0)
	अस्थिर अचिन्हित पूर्णांक control;
#घोषणा MACEPCI_CONTROL_INT(x)			BIT(x)
#घोषणा MACEPCI_CONTROL_INT_MASK		0xff
#घोषणा MACEPCI_CONTROL_SERR_ENA		BIT(8)
#घोषणा MACEPCI_CONTROL_ARB_N6			BIT(9)
#घोषणा MACEPCI_CONTROL_PARITY_ERR		BIT(10)
#घोषणा MACEPCI_CONTROL_MRMRA_ENA		BIT(11)
#घोषणा MACEPCI_CONTROL_ARB_N3			BIT(12)
#घोषणा MACEPCI_CONTROL_ARB_N4			BIT(13)
#घोषणा MACEPCI_CONTROL_ARB_N5			BIT(14)
#घोषणा MACEPCI_CONTROL_PARK_LIU		BIT(15)
#घोषणा MACEPCI_CONTROL_INV_INT(x)		BIT(16+x)
#घोषणा MACEPCI_CONTROL_INV_INT_MASK		0x00ff0000
#घोषणा MACEPCI_CONTROL_OVERRUN_INT		BIT(24)
#घोषणा MACEPCI_CONTROL_PARITY_INT		BIT(25)
#घोषणा MACEPCI_CONTROL_SERR_INT		BIT(26)
#घोषणा MACEPCI_CONTROL_IT_INT			BIT(27)
#घोषणा MACEPCI_CONTROL_RE_INT			BIT(28)
#घोषणा MACEPCI_CONTROL_DPED_INT		BIT(29)
#घोषणा MACEPCI_CONTROL_TAR_INT			BIT(30)
#घोषणा MACEPCI_CONTROL_MAR_INT			BIT(31)
	अस्थिर अचिन्हित पूर्णांक rev;
	अचिन्हित पूर्णांक _pad[0xcf8/4 - 4];
	अस्थिर अचिन्हित पूर्णांक config_addr;
	जोड़ अणु
		अस्थिर अचिन्हित अक्षर b[4];
		अस्थिर अचिन्हित लघु w[2];
		अस्थिर अचिन्हित पूर्णांक l;
	पूर्ण config_data;
पूर्ण;
#घोषणा MACEPCI_LOW_MEMORY		0x1a000000
#घोषणा MACEPCI_LOW_IO			0x18000000
#घोषणा MACEPCI_SWAPPED_VIEW		0
#घोषणा MACEPCI_NATIVE_VIEW		0x40000000
#घोषणा MACEPCI_IO			0x80000000
#घोषणा MACEPCI_HI_MEMORY		0x280000000
#घोषणा MACEPCI_HI_IO			0x100000000

/*
 * Video पूर्णांकerface
 */
काष्ठा mace_video अणु
	अचिन्हित दीर्घ xxx;	/* later... */
पूर्ण;

/*
 * Ethernet पूर्णांकerface
 */
काष्ठा mace_ethernet अणु
	अस्थिर u64 mac_ctrl;
	अस्थिर अचिन्हित दीर्घ पूर्णांक_stat;
	अस्थिर अचिन्हित दीर्घ dma_ctrl;
	अस्थिर अचिन्हित दीर्घ समयr;
	अस्थिर अचिन्हित दीर्घ tx_पूर्णांक_al;
	अस्थिर अचिन्हित दीर्घ rx_पूर्णांक_al;
	अस्थिर अचिन्हित दीर्घ tx_info;
	अस्थिर अचिन्हित दीर्घ tx_info_al;
	अस्थिर अचिन्हित दीर्घ rx_buff;
	अस्थिर अचिन्हित दीर्घ rx_buff_al1;
	अस्थिर अचिन्हित दीर्घ rx_buff_al2;
	अस्थिर अचिन्हित दीर्घ diag;
	अस्थिर अचिन्हित दीर्घ phy_data;
	अस्थिर अचिन्हित दीर्घ phy_regs;
	अस्थिर अचिन्हित दीर्घ phy_trans_go;
	अस्थिर अचिन्हित दीर्घ backoff_seed;
	/*===================================*/
	अस्थिर अचिन्हित दीर्घ imq_reserved[4];
	अस्थिर अचिन्हित दीर्घ mac_addr;
	अस्थिर अचिन्हित दीर्घ mac_addr2;
	अस्थिर अचिन्हित दीर्घ mcast_filter;
	अस्थिर अचिन्हित दीर्घ tx_ring_base;
	/* Following are पढ़ो-only रेजिस्टरs क्रम debugging */
	अस्थिर अचिन्हित दीर्घ tx_pkt1_hdr;
	अस्थिर अचिन्हित दीर्घ tx_pkt1_ptr[3];
	अस्थिर अचिन्हित दीर्घ tx_pkt2_hdr;
	अस्थिर अचिन्हित दीर्घ tx_pkt2_ptr[3];
	/*===================================*/
	अस्थिर अचिन्हित दीर्घ rx_fअगरo;
पूर्ण;

/*
 * Peripherals
 */

/* Audio रेजिस्टरs */
काष्ठा mace_audio अणु
	अस्थिर अचिन्हित दीर्घ control;
	अस्थिर अचिन्हित दीर्घ codec_control;		/* codec status control */
	अस्थिर अचिन्हित दीर्घ codec_mask;		/* codec status input mask */
	अस्थिर अचिन्हित दीर्घ codec_पढ़ो;		/* codec status पढ़ो data */
	काष्ठा अणु
		अस्थिर अचिन्हित दीर्घ control;		/* channel control */
		अस्थिर अचिन्हित दीर्घ पढ़ो_ptr;	/* channel पढ़ो poपूर्णांकer */
		अस्थिर अचिन्हित दीर्घ ग_लिखो_ptr;	/* channel ग_लिखो poपूर्णांकer */
		अस्थिर अचिन्हित दीर्घ depth;		/* channel depth */
	पूर्ण chan[3];
पूर्ण;


/* रेजिस्टर definitions क्रम parallel port DMA */
काष्ठा mace_parport अणु
	/* 0 - करो nothing,
	 * 1 - pulse terminal count to the device after buffer is drained */
#घोषणा MACEPAR_CONTEXT_LASTFLAG	BIT(63)
	/* Should not cross 4K page boundary */
#घोषणा MACEPAR_CONTEXT_DATA_BOUND	0x0000000000001000UL
#घोषणा MACEPAR_CONTEXT_DATALEN_MASK	0x00000fff00000000UL
#घोषणा MACEPAR_CONTEXT_DATALEN_SHIFT	32
	/* Can be arbitrarily aligned on any byte boundary on output,
	 * 64 byte aligned on input */
#घोषणा MACEPAR_CONTEXT_BASEADDR_MASK	0x00000000ffffffffUL
	अस्थिर u64 context_a;
	अस्थिर u64 context_b;
	/* 0 - mem->device, 1 - device->mem */
#घोषणा MACEPAR_CTLSTAT_सूचीECTION	BIT(0)
	/* 0 - channel frozen, 1 - channel enabled */
#घोषणा MACEPAR_CTLSTAT_ENABLE		BIT(1)
	/* 0 - channel active, 1 - complete channel reset */
#घोषणा MACEPAR_CTLSTAT_RESET		BIT(2)
#घोषणा MACEPAR_CTLSTAT_CTXB_VALID	BIT(3)
#घोषणा MACEPAR_CTLSTAT_CTXA_VALID	BIT(4)
	अस्थिर u64 cntlstat;		/* Control/Status रेजिस्टर */
#घोषणा MACEPAR_DIAG_CTXINUSE		BIT(0)
	/* 1 - Dma engine is enabled and processing something */
#घोषणा MACEPAR_DIAG_DMACTIVE		BIT(1)
	/* Counter of bytes left */
#घोषणा MACEPAR_DIAG_CTRMASK		0x0000000000003ffcUL
#घोषणा MACEPAR_DIAG_CTRSHIFT		2
	अस्थिर u64 diagnostic;	/* RO: diagnostic रेजिस्टर */
पूर्ण;

/* ISA Control and DMA रेजिस्टरs */
काष्ठा mace_isactrl अणु
	अस्थिर अचिन्हित दीर्घ ringbase;
#घोषणा MACEISA_RINGBUFFERS_SIZE	(8 * 4096)

	अस्थिर अचिन्हित दीर्घ misc;
#घोषणा MACEISA_FLASH_WE		BIT(0)	/* 1=> Enable FLASH ग_लिखोs */
#घोषणा MACEISA_PWD_CLEAR		BIT(1)	/* 1=> PWD CLEAR jumper detected */
#घोषणा MACEISA_NIC_DEASSERT		BIT(2)
#घोषणा MACEISA_NIC_DATA		BIT(3)
#घोषणा MACEISA_LED_RED			BIT(4)	/* 0=> Illuminate red LED */
#घोषणा MACEISA_LED_GREEN		BIT(5)	/* 0=> Illuminate green LED */
#घोषणा MACEISA_DP_RAM_ENABLE		BIT(6)

	अस्थिर अचिन्हित दीर्घ istat;
	अस्थिर अचिन्हित दीर्घ imask;
#घोषणा MACEISA_AUDIO_SW_INT		BIT(0)
#घोषणा MACEISA_AUDIO_SC_INT		BIT(1)
#घोषणा MACEISA_AUDIO1_DMAT_INT		BIT(2)
#घोषणा MACEISA_AUDIO1_OF_INT		BIT(3)
#घोषणा MACEISA_AUDIO2_DMAT_INT		BIT(4)
#घोषणा MACEISA_AUDIO2_MERR_INT		BIT(5)
#घोषणा MACEISA_AUDIO3_DMAT_INT		BIT(6)
#घोषणा MACEISA_AUDIO3_MERR_INT		BIT(7)
#घोषणा MACEISA_RTC_INT			BIT(8)
#घोषणा MACEISA_KEYB_INT		BIT(9)
#घोषणा MACEISA_KEYB_POLL_INT		BIT(10)
#घोषणा MACEISA_MOUSE_INT		BIT(11)
#घोषणा MACEISA_MOUSE_POLL_INT		BIT(12)
#घोषणा MACEISA_TIMER0_INT		BIT(13)
#घोषणा MACEISA_TIMER1_INT		BIT(14)
#घोषणा MACEISA_TIMER2_INT		BIT(15)
#घोषणा MACEISA_PARALLEL_INT		BIT(16)
#घोषणा MACEISA_PAR_CTXA_INT		BIT(17)
#घोषणा MACEISA_PAR_CTXB_INT		BIT(18)
#घोषणा MACEISA_PAR_MERR_INT		BIT(19)
#घोषणा MACEISA_SERIAL1_INT		BIT(20)
#घोषणा MACEISA_SERIAL1_TDMAT_INT	BIT(21)
#घोषणा MACEISA_SERIAL1_TDMAPR_INT	BIT(22)
#घोषणा MACEISA_SERIAL1_TDMAME_INT	BIT(23)
#घोषणा MACEISA_SERIAL1_RDMAT_INT	BIT(24)
#घोषणा MACEISA_SERIAL1_RDMAOR_INT	BIT(25)
#घोषणा MACEISA_SERIAL2_INT		BIT(26)
#घोषणा MACEISA_SERIAL2_TDMAT_INT	BIT(27)
#घोषणा MACEISA_SERIAL2_TDMAPR_INT	BIT(28)
#घोषणा MACEISA_SERIAL2_TDMAME_INT	BIT(29)
#घोषणा MACEISA_SERIAL2_RDMAT_INT	BIT(30)
#घोषणा MACEISA_SERIAL2_RDMAOR_INT	BIT(31)

	अस्थिर अचिन्हित दीर्घ _pad[0x2000/8 - 4];

	अस्थिर अचिन्हित दीर्घ dp_ram[0x400];
	काष्ठा mace_parport parport;
पूर्ण;

/* Keyboard & Mouse रेजिस्टरs
 * -> drivers/input/serio/maceps2.c */
काष्ठा mace_ps2port अणु
	अस्थिर अचिन्हित दीर्घ tx;
	अस्थिर अचिन्हित दीर्घ rx;
	अस्थिर अचिन्हित दीर्घ control;
	अस्थिर अचिन्हित दीर्घ status;
पूर्ण;

काष्ठा mace_ps2 अणु
	काष्ठा mace_ps2port keyb;
	काष्ठा mace_ps2port mouse;
पूर्ण;

/* I2C रेजिस्टरs
 * -> drivers/i2c/algos/i2c-algo-sgi.c */
काष्ठा mace_i2c अणु
	अस्थिर अचिन्हित दीर्घ config;
#घोषणा MACEI2C_RESET		BIT(0)
#घोषणा MACEI2C_FAST		BIT(1)
#घोषणा MACEI2C_DATA_OVERRIDE	BIT(2)
#घोषणा MACEI2C_CLOCK_OVERRIDE	BIT(3)
#घोषणा MACEI2C_DATA_STATUS	BIT(4)
#घोषणा MACEI2C_CLOCK_STATUS	BIT(5)
	अस्थिर अचिन्हित दीर्घ control;
	अस्थिर अचिन्हित दीर्घ data;
पूर्ण;

/* Timer रेजिस्टरs */
प्रकार जोड़ अणु
	अस्थिर अचिन्हित दीर्घ ust_msc;
	काष्ठा reg अणु
		अस्थिर अचिन्हित पूर्णांक ust;
		अस्थिर अचिन्हित पूर्णांक msc;
	पूर्ण reg;
पूर्ण समयr_reg;

काष्ठा mace_समयrs अणु
	अस्थिर अचिन्हित दीर्घ ust;
#घोषणा MACE_UST_PERIOD_NS	960

	अस्थिर अचिन्हित दीर्घ compare1;
	अस्थिर अचिन्हित दीर्घ compare2;
	अस्थिर अचिन्हित दीर्घ compare3;

	समयr_reg audio_in;
	समयr_reg audio_out1;
	समयr_reg audio_out2;
	समयr_reg video_in1;
	समयr_reg video_in2;
	समयr_reg video_out;
पूर्ण;

काष्ठा mace_perअगर अणु
	काष्ठा mace_audio audio;
	अक्षर _pad0[0x10000 - माप(काष्ठा mace_audio)];

	काष्ठा mace_isactrl ctrl;
	अक्षर _pad1[0x10000 - माप(काष्ठा mace_isactrl)];

	काष्ठा mace_ps2 ps2;
	अक्षर _pad2[0x10000 - माप(काष्ठा mace_ps2)];

	काष्ठा mace_i2c i2c;
	अक्षर _pad3[0x10000 - माप(काष्ठा mace_i2c)];

	काष्ठा mace_समयrs समयrs;
	अक्षर _pad4[0x10000 - माप(काष्ठा mace_समयrs)];
पूर्ण;


/*
 * ISA peripherals
 */

/* Parallel port */
काष्ठा mace_parallel अणु
पूर्ण;

काष्ठा mace_ecp1284 अणु	/* later... */
पूर्ण;

/* Serial port */
काष्ठा mace_serial अणु
	अस्थिर अचिन्हित दीर्घ xxx;	/* later... */
पूर्ण;

काष्ठा mace_isa अणु
	काष्ठा mace_parallel parallel;
	अक्षर _pad1[0x8000 - माप(काष्ठा mace_parallel)];

	काष्ठा mace_ecp1284 ecp1284;
	अक्षर _pad2[0x8000 - माप(काष्ठा mace_ecp1284)];

	काष्ठा mace_serial serial1;
	अक्षर _pad3[0x8000 - माप(काष्ठा mace_serial)];

	काष्ठा mace_serial serial2;
	अक्षर _pad4[0x8000 - माप(काष्ठा mace_serial)];

	अस्थिर अचिन्हित अक्षर rtc[0x10000];
पूर्ण;

काष्ठा sgi_mace अणु
	अक्षर _reserved[0x80000];

	काष्ठा mace_pci pci;
	अक्षर _pad0[0x80000 - माप(काष्ठा mace_pci)];

	काष्ठा mace_video video_in1;
	अक्षर _pad1[0x80000 - माप(काष्ठा mace_video)];

	काष्ठा mace_video video_in2;
	अक्षर _pad2[0x80000 - माप(काष्ठा mace_video)];

	काष्ठा mace_video video_out;
	अक्षर _pad3[0x80000 - माप(काष्ठा mace_video)];

	काष्ठा mace_ethernet eth;
	अक्षर _pad4[0x80000 - माप(काष्ठा mace_ethernet)];

	काष्ठा mace_perअगर perअगर;
	अक्षर _pad5[0x80000 - माप(काष्ठा mace_perअगर)];

	काष्ठा mace_isa isa;
	अक्षर _pad6[0x80000 - माप(काष्ठा mace_isa)];
पूर्ण;

बाह्य काष्ठा sgi_mace __iomem *mace;

#पूर्ण_अगर /* __ASM_MACE_H__ */
