<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// drivers/dma/imx-sdma.c
//
// This file contains a driver क्रम the Freescale Smart DMA engine
//
// Copyright 2010 Sascha Hauer, Pengutronix <s.hauer@pengutronix.de>
//
// Based on code from Freescale:
//
// Copyright 2004-2009 Freescale Semiconductor, Inc. All Rights Reserved.

#समावेश <linux/init.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/bitops.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/sched.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/firmware.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/workqueue.h>

#समावेश <यंत्र/irq.h>
#समावेश <linux/platक्रमm_data/dma-imx-sdma.h>
#समावेश <linux/platक्रमm_data/dma-imx.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/mfd/syscon/imx6q-iomuxc-gpr.h>

#समावेश "dmaengine.h"
#समावेश "virt-dma.h"

/* SDMA रेजिस्टरs */
#घोषणा SDMA_H_C0PTR		0x000
#घोषणा SDMA_H_INTR		0x004
#घोषणा SDMA_H_STATSTOP		0x008
#घोषणा SDMA_H_START		0x00c
#घोषणा SDMA_H_EVTOVR		0x010
#घोषणा SDMA_H_DSPOVR		0x014
#घोषणा SDMA_H_HOSTOVR		0x018
#घोषणा SDMA_H_EVTPEND		0x01c
#घोषणा SDMA_H_DSPENBL		0x020
#घोषणा SDMA_H_RESET		0x024
#घोषणा SDMA_H_EVTERR		0x028
#घोषणा SDMA_H_INTRMSK		0x02c
#घोषणा SDMA_H_PSW		0x030
#घोषणा SDMA_H_EVTERRDBG	0x034
#घोषणा SDMA_H_CONFIG		0x038
#घोषणा SDMA_ONCE_ENB		0x040
#घोषणा SDMA_ONCE_DATA		0x044
#घोषणा SDMA_ONCE_INSTR		0x048
#घोषणा SDMA_ONCE_STAT		0x04c
#घोषणा SDMA_ONCE_CMD		0x050
#घोषणा SDMA_EVT_MIRROR		0x054
#घोषणा SDMA_ILLINSTADDR	0x058
#घोषणा SDMA_CHN0ADDR		0x05c
#घोषणा SDMA_ONCE_RTB		0x060
#घोषणा SDMA_XTRIG_CONF1	0x070
#घोषणा SDMA_XTRIG_CONF2	0x074
#घोषणा SDMA_CHNENBL0_IMX35	0x200
#घोषणा SDMA_CHNENBL0_IMX31	0x080
#घोषणा SDMA_CHNPRI_0		0x100

/*
 * Buffer descriptor status values.
 */
#घोषणा BD_DONE  0x01
#घोषणा BD_WRAP  0x02
#घोषणा BD_CONT  0x04
#घोषणा BD_INTR  0x08
#घोषणा BD_RROR  0x10
#घोषणा BD_LAST  0x20
#घोषणा BD_EXTD  0x80

/*
 * Data Node descriptor status values.
 */
#घोषणा DND_END_OF_FRAME  0x80
#घोषणा DND_END_OF_XFER   0x40
#घोषणा DND_DONE          0x20
#घोषणा DND_UNUSED        0x01

/*
 * IPCV2 descriptor status values.
 */
#घोषणा BD_IPCV2_END_OF_FRAME  0x40

#घोषणा IPCV2_MAX_NODES        50
/*
 * Error bit set in the CCB status field by the SDMA,
 * in setbd routine, in हाल of a transfer error
 */
#घोषणा DATA_ERROR  0x10000000

/*
 * Buffer descriptor commands.
 */
#घोषणा C0_ADDR             0x01
#घोषणा C0_LOAD             0x02
#घोषणा C0_DUMP             0x03
#घोषणा C0_SETCTX           0x07
#घोषणा C0_GETCTX           0x03
#घोषणा C0_SETDM            0x01
#घोषणा C0_SETPM            0x04
#घोषणा C0_GETDM            0x02
#घोषणा C0_GETPM            0x08
/*
 * Change endianness indicator in the BD command field
 */
#घोषणा CHANGE_ENDIANNESS   0x80

/*
 *  p_2_p watermark_level description
 *	Bits		Name			Description
 *	0-7		Lower WML		Lower watermark level
 *	8		PS			1: Pad Swallowing
 *						0: No Pad Swallowing
 *	9		PA			1: Pad Adding
 *						0: No Pad Adding
 *	10		SPDIF			If this bit is set both source
 *						and destination are on SPBA
 *	11		Source Bit(SP)		1: Source on SPBA
 *						0: Source on AIPS
 *	12		Destination Bit(DP)	1: Destination on SPBA
 *						0: Destination on AIPS
 *	13-15		---------		MUST BE 0
 *	16-23		Higher WML		HWML
 *	24-27		N			Total number of samples after
 *						which Pad adding/Swallowing
 *						must be करोne. It must be odd.
 *	28		Lower WML Event(LWE)	SDMA events reg to check क्रम
 *						LWML event mask
 *						0: LWE in EVENTS रेजिस्टर
 *						1: LWE in EVENTS2 रेजिस्टर
 *	29		Higher WML Event(HWE)	SDMA events reg to check क्रम
 *						HWML event mask
 *						0: HWE in EVENTS रेजिस्टर
 *						1: HWE in EVENTS2 रेजिस्टर
 *	30		---------		MUST BE 0
 *	31		CONT			1: Amount of samples to be
 *						transferred is unknown and
 *						script will keep on
 *						transferring samples as दीर्घ as
 *						both events are detected and
 *						script must be manually stopped
 *						by the application
 *						0: The amount of samples to be
 *						transferred is equal to the
 *						count field of mode word
 */
#घोषणा SDMA_WATERMARK_LEVEL_LWML	0xFF
#घोषणा SDMA_WATERMARK_LEVEL_PS		BIT(8)
#घोषणा SDMA_WATERMARK_LEVEL_PA		BIT(9)
#घोषणा SDMA_WATERMARK_LEVEL_SPDIF	BIT(10)
#घोषणा SDMA_WATERMARK_LEVEL_SP		BIT(11)
#घोषणा SDMA_WATERMARK_LEVEL_DP		BIT(12)
#घोषणा SDMA_WATERMARK_LEVEL_HWML	(0xFF << 16)
#घोषणा SDMA_WATERMARK_LEVEL_LWE	BIT(28)
#घोषणा SDMA_WATERMARK_LEVEL_HWE	BIT(29)
#घोषणा SDMA_WATERMARK_LEVEL_CONT	BIT(31)

#घोषणा SDMA_DMA_BUSWIDTHS	(BIT(DMA_SLAVE_BUSWIDTH_1_BYTE) | \
				 BIT(DMA_SLAVE_BUSWIDTH_2_BYTES) | \
				 BIT(DMA_SLAVE_BUSWIDTH_4_BYTES))

#घोषणा SDMA_DMA_सूचीECTIONS	(BIT(DMA_DEV_TO_MEM) | \
				 BIT(DMA_MEM_TO_DEV) | \
				 BIT(DMA_DEV_TO_DEV))

/*
 * Mode/Count of data node descriptors - IPCv2
 */
काष्ठा sdma_mode_count अणु
#घोषणा SDMA_BD_MAX_CNT	0xffff
	u32 count   : 16; /* size of the buffer poपूर्णांकed by this BD */
	u32 status  :  8; /* E,R,I,C,W,D status bits stored here */
	u32 command :  8; /* command mostly used क्रम channel 0 */
पूर्ण;

/*
 * Buffer descriptor
 */
काष्ठा sdma_buffer_descriptor अणु
	काष्ठा sdma_mode_count  mode;
	u32 buffer_addr;	/* address of the buffer described */
	u32 ext_buffer_addr;	/* extended buffer address */
पूर्ण __attribute__ ((packed));

/**
 * काष्ठा sdma_channel_control - Channel control Block
 *
 * @current_bd_ptr:	current buffer descriptor processed
 * @base_bd_ptr:	first element of buffer descriptor array
 * @unused:		padding. The SDMA engine expects an array of 128 byte
 *			control blocks
 */
काष्ठा sdma_channel_control अणु
	u32 current_bd_ptr;
	u32 base_bd_ptr;
	u32 unused[2];
पूर्ण __attribute__ ((packed));

/**
 * काष्ठा sdma_state_रेजिस्टरs - SDMA context क्रम a channel
 *
 * @pc:		program counter
 * @unused1:	unused
 * @t:		test bit: status of arithmetic & test inकाष्ठाion
 * @rpc:	वापस program counter
 * @unused0:	unused
 * @sf:		source fault जबतक loading data
 * @spc:	loop start program counter
 * @unused2:	unused
 * @df:		destination fault जबतक storing data
 * @epc:	loop end program counter
 * @lm:		loop mode
 */
काष्ठा sdma_state_रेजिस्टरs अणु
	u32 pc     :14;
	u32 unused1: 1;
	u32 t      : 1;
	u32 rpc    :14;
	u32 unused0: 1;
	u32 sf     : 1;
	u32 spc    :14;
	u32 unused2: 1;
	u32 df     : 1;
	u32 epc    :14;
	u32 lm     : 2;
पूर्ण __attribute__ ((packed));

/**
 * काष्ठा sdma_context_data - sdma context specअगरic to a channel
 *
 * @channel_state:	channel state bits
 * @gReg:		general रेजिस्टरs
 * @mda:		burst dma destination address रेजिस्टर
 * @msa:		burst dma source address रेजिस्टर
 * @ms:			burst dma status रेजिस्टर
 * @md:			burst dma data रेजिस्टर
 * @pda:		peripheral dma destination address रेजिस्टर
 * @psa:		peripheral dma source address रेजिस्टर
 * @ps:			peripheral dma status रेजिस्टर
 * @pd:			peripheral dma data रेजिस्टर
 * @ca:			CRC polynomial रेजिस्टर
 * @cs:			CRC accumulator रेजिस्टर
 * @dda:		dedicated core destination address रेजिस्टर
 * @dsa:		dedicated core source address रेजिस्टर
 * @ds:			dedicated core status रेजिस्टर
 * @dd:			dedicated core data रेजिस्टर
 * @scratch0:		1st word of dedicated ram क्रम context चयन
 * @scratch1:		2nd word of dedicated ram क्रम context चयन
 * @scratch2:		3rd word of dedicated ram क्रम context चयन
 * @scratch3:		4th word of dedicated ram क्रम context चयन
 * @scratch4:		5th word of dedicated ram क्रम context चयन
 * @scratch5:		6th word of dedicated ram क्रम context चयन
 * @scratch6:		7th word of dedicated ram क्रम context चयन
 * @scratch7:		8th word of dedicated ram क्रम context चयन
 */
काष्ठा sdma_context_data अणु
	काष्ठा sdma_state_रेजिस्टरs  channel_state;
	u32  gReg[8];
	u32  mda;
	u32  msa;
	u32  ms;
	u32  md;
	u32  pda;
	u32  psa;
	u32  ps;
	u32  pd;
	u32  ca;
	u32  cs;
	u32  dda;
	u32  dsa;
	u32  ds;
	u32  dd;
	u32  scratch0;
	u32  scratch1;
	u32  scratch2;
	u32  scratch3;
	u32  scratch4;
	u32  scratch5;
	u32  scratch6;
	u32  scratch7;
पूर्ण __attribute__ ((packed));


काष्ठा sdma_engine;

/**
 * काष्ठा sdma_desc - descriptor काष्ठाor क्रम one transfer
 * @vd:			descriptor क्रम virt dma
 * @num_bd:		number of descriptors currently handling
 * @bd_phys:		physical address of bd
 * @buf_tail:		ID of the buffer that was processed
 * @buf_ptail:		ID of the previous buffer that was processed
 * @period_len:		period length, used in cyclic.
 * @chn_real_count:	the real count updated from bd->mode.count
 * @chn_count:		the transfer count set
 * @sdmac:		sdma_channel poपूर्णांकer
 * @bd:			poपूर्णांकer of allocate bd
 */
काष्ठा sdma_desc अणु
	काष्ठा virt_dma_desc	vd;
	अचिन्हित पूर्णांक		num_bd;
	dma_addr_t		bd_phys;
	अचिन्हित पूर्णांक		buf_tail;
	अचिन्हित पूर्णांक		buf_ptail;
	अचिन्हित पूर्णांक		period_len;
	अचिन्हित पूर्णांक		chn_real_count;
	अचिन्हित पूर्णांक		chn_count;
	काष्ठा sdma_channel	*sdmac;
	काष्ठा sdma_buffer_descriptor *bd;
पूर्ण;

/**
 * काष्ठा sdma_channel - housekeeping क्रम a SDMA channel
 *
 * @vc:			virt_dma base काष्ठाure
 * @desc:		sdma description including vd and other special member
 * @sdma:		poपूर्णांकer to the SDMA engine क्रम this channel
 * @channel:		the channel number, matches dmaengine chan_id + 1
 * @direction:		transfer type. Needed क्रम setting SDMA script
 * @slave_config:	Slave configuration
 * @peripheral_type:	Peripheral type. Needed क्रम setting SDMA script
 * @event_id0:		aka dma request line
 * @event_id1:		क्रम channels that use 2 events
 * @word_size:		peripheral access size
 * @pc_from_device:	script address क्रम those device_2_memory
 * @pc_to_device:	script address क्रम those memory_2_device
 * @device_to_device:	script address क्रम those device_2_device
 * @pc_to_pc:		script address क्रम those memory_2_memory
 * @flags:		loop mode or not
 * @per_address:	peripheral source or destination address in common हाल
 *                      destination address in p_2_p हाल
 * @per_address2:	peripheral source address in p_2_p हाल
 * @event_mask:		event mask used in p_2_p script
 * @watermark_level:	value क्रम gReg[7], some script will extend it from
 *			basic watermark such as p_2_p
 * @shp_addr:		value क्रम gReg[6]
 * @per_addr:		value क्रम gReg[2]
 * @status:		status of dma channel
 * @context_loaded:	ensure context is only loaded once
 * @data:		specअगरic sdma पूर्णांकerface काष्ठाure
 * @bd_pool:		dma_pool क्रम bd
 * @terminate_worker:	used to call back पूर्णांकo terminate work function
 */
काष्ठा sdma_channel अणु
	काष्ठा virt_dma_chan		vc;
	काष्ठा sdma_desc		*desc;
	काष्ठा sdma_engine		*sdma;
	अचिन्हित पूर्णांक			channel;
	क्रमागत dma_transfer_direction		direction;
	काष्ठा dma_slave_config		slave_config;
	क्रमागत sdma_peripheral_type	peripheral_type;
	अचिन्हित पूर्णांक			event_id0;
	अचिन्हित पूर्णांक			event_id1;
	क्रमागत dma_slave_buswidth		word_size;
	अचिन्हित पूर्णांक			pc_from_device, pc_to_device;
	अचिन्हित पूर्णांक			device_to_device;
	अचिन्हित पूर्णांक                    pc_to_pc;
	अचिन्हित दीर्घ			flags;
	dma_addr_t			per_address, per_address2;
	अचिन्हित दीर्घ			event_mask[2];
	अचिन्हित दीर्घ			watermark_level;
	u32				shp_addr, per_addr;
	क्रमागत dma_status			status;
	bool				context_loaded;
	काष्ठा imx_dma_data		data;
	काष्ठा work_काष्ठा		terminate_worker;
पूर्ण;

#घोषणा IMX_DMA_SG_LOOP		BIT(0)

#घोषणा MAX_DMA_CHANNELS 32
#घोषणा MXC_SDMA_DEFAULT_PRIORITY 1
#घोषणा MXC_SDMA_MIN_PRIORITY 1
#घोषणा MXC_SDMA_MAX_PRIORITY 7

#घोषणा SDMA_FIRMWARE_MAGIC 0x414d4453

/**
 * काष्ठा sdma_firmware_header - Layout of the firmware image
 *
 * @magic:		"SDMA"
 * @version_major:	increased whenever layout of काष्ठा
 *			sdma_script_start_addrs changes.
 * @version_minor:	firmware minor version (क्रम binary compatible changes)
 * @script_addrs_start:	offset of काष्ठा sdma_script_start_addrs in this image
 * @num_script_addrs:	Number of script addresses in this image
 * @ram_code_start:	offset of SDMA ram image in this firmware image
 * @ram_code_size:	size of SDMA ram image
 * @script_addrs:	Stores the start address of the SDMA scripts
 *			(in SDMA memory space)
 */
काष्ठा sdma_firmware_header अणु
	u32	magic;
	u32	version_major;
	u32	version_minor;
	u32	script_addrs_start;
	u32	num_script_addrs;
	u32	ram_code_start;
	u32	ram_code_size;
पूर्ण;

काष्ठा sdma_driver_data अणु
	पूर्णांक chnenbl0;
	पूर्णांक num_events;
	काष्ठा sdma_script_start_addrs	*script_addrs;
	bool check_ratio;
पूर्ण;

काष्ठा sdma_engine अणु
	काष्ठा device			*dev;
	काष्ठा sdma_channel		channel[MAX_DMA_CHANNELS];
	काष्ठा sdma_channel_control	*channel_control;
	व्योम __iomem			*regs;
	काष्ठा sdma_context_data	*context;
	dma_addr_t			context_phys;
	काष्ठा dma_device		dma_device;
	काष्ठा clk			*clk_ipg;
	काष्ठा clk			*clk_ahb;
	spinlock_t			channel_0_lock;
	u32				script_number;
	काष्ठा sdma_script_start_addrs	*script_addrs;
	स्थिर काष्ठा sdma_driver_data	*drvdata;
	u32				spba_start_addr;
	u32				spba_end_addr;
	अचिन्हित पूर्णांक			irq;
	dma_addr_t			bd0_phys;
	काष्ठा sdma_buffer_descriptor	*bd0;
	/* घड़ी ratio क्रम AHB:SDMA core. 1:1 is 1, 2:1 is 0*/
	bool				clk_ratio;
पूर्ण;

अटल पूर्णांक sdma_config_ग_लिखो(काष्ठा dma_chan *chan,
		       काष्ठा dma_slave_config *dmaengine_cfg,
		       क्रमागत dma_transfer_direction direction);

अटल काष्ठा sdma_driver_data sdma_imx31 = अणु
	.chnenbl0 = SDMA_CHNENBL0_IMX31,
	.num_events = 32,
पूर्ण;

अटल काष्ठा sdma_script_start_addrs sdma_script_imx25 = अणु
	.ap_2_ap_addr = 729,
	.uart_2_mcu_addr = 904,
	.per_2_app_addr = 1255,
	.mcu_2_app_addr = 834,
	.uartsh_2_mcu_addr = 1120,
	.per_2_shp_addr = 1329,
	.mcu_2_shp_addr = 1048,
	.ata_2_mcu_addr = 1560,
	.mcu_2_ata_addr = 1479,
	.app_2_per_addr = 1189,
	.app_2_mcu_addr = 770,
	.shp_2_per_addr = 1407,
	.shp_2_mcu_addr = 979,
पूर्ण;

अटल काष्ठा sdma_driver_data sdma_imx25 = अणु
	.chnenbl0 = SDMA_CHNENBL0_IMX35,
	.num_events = 48,
	.script_addrs = &sdma_script_imx25,
पूर्ण;

अटल काष्ठा sdma_driver_data sdma_imx35 = अणु
	.chnenbl0 = SDMA_CHNENBL0_IMX35,
	.num_events = 48,
पूर्ण;

अटल काष्ठा sdma_script_start_addrs sdma_script_imx51 = अणु
	.ap_2_ap_addr = 642,
	.uart_2_mcu_addr = 817,
	.mcu_2_app_addr = 747,
	.mcu_2_shp_addr = 961,
	.ata_2_mcu_addr = 1473,
	.mcu_2_ata_addr = 1392,
	.app_2_per_addr = 1033,
	.app_2_mcu_addr = 683,
	.shp_2_per_addr = 1251,
	.shp_2_mcu_addr = 892,
पूर्ण;

अटल काष्ठा sdma_driver_data sdma_imx51 = अणु
	.chnenbl0 = SDMA_CHNENBL0_IMX35,
	.num_events = 48,
	.script_addrs = &sdma_script_imx51,
पूर्ण;

अटल काष्ठा sdma_script_start_addrs sdma_script_imx53 = अणु
	.ap_2_ap_addr = 642,
	.app_2_mcu_addr = 683,
	.mcu_2_app_addr = 747,
	.uart_2_mcu_addr = 817,
	.shp_2_mcu_addr = 891,
	.mcu_2_shp_addr = 960,
	.uartsh_2_mcu_addr = 1032,
	.spdअगर_2_mcu_addr = 1100,
	.mcu_2_spdअगर_addr = 1134,
	.firi_2_mcu_addr = 1193,
	.mcu_2_firi_addr = 1290,
पूर्ण;

अटल काष्ठा sdma_driver_data sdma_imx53 = अणु
	.chnenbl0 = SDMA_CHNENBL0_IMX35,
	.num_events = 48,
	.script_addrs = &sdma_script_imx53,
पूर्ण;

अटल काष्ठा sdma_script_start_addrs sdma_script_imx6q = अणु
	.ap_2_ap_addr = 642,
	.uart_2_mcu_addr = 817,
	.mcu_2_app_addr = 747,
	.per_2_per_addr = 6331,
	.uartsh_2_mcu_addr = 1032,
	.mcu_2_shp_addr = 960,
	.app_2_mcu_addr = 683,
	.shp_2_mcu_addr = 891,
	.spdअगर_2_mcu_addr = 1100,
	.mcu_2_spdअगर_addr = 1134,
पूर्ण;

अटल काष्ठा sdma_driver_data sdma_imx6q = अणु
	.chnenbl0 = SDMA_CHNENBL0_IMX35,
	.num_events = 48,
	.script_addrs = &sdma_script_imx6q,
पूर्ण;

अटल काष्ठा sdma_script_start_addrs sdma_script_imx7d = अणु
	.ap_2_ap_addr = 644,
	.uart_2_mcu_addr = 819,
	.mcu_2_app_addr = 749,
	.uartsh_2_mcu_addr = 1034,
	.mcu_2_shp_addr = 962,
	.app_2_mcu_addr = 685,
	.shp_2_mcu_addr = 893,
	.spdअगर_2_mcu_addr = 1102,
	.mcu_2_spdअगर_addr = 1136,
पूर्ण;

अटल काष्ठा sdma_driver_data sdma_imx7d = अणु
	.chnenbl0 = SDMA_CHNENBL0_IMX35,
	.num_events = 48,
	.script_addrs = &sdma_script_imx7d,
पूर्ण;

अटल काष्ठा sdma_driver_data sdma_imx8mq = अणु
	.chnenbl0 = SDMA_CHNENBL0_IMX35,
	.num_events = 48,
	.script_addrs = &sdma_script_imx7d,
	.check_ratio = 1,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sdma_dt_ids[] = अणु
	अणु .compatible = "fsl,imx6q-sdma", .data = &sdma_imx6q, पूर्ण,
	अणु .compatible = "fsl,imx53-sdma", .data = &sdma_imx53, पूर्ण,
	अणु .compatible = "fsl,imx51-sdma", .data = &sdma_imx51, पूर्ण,
	अणु .compatible = "fsl,imx35-sdma", .data = &sdma_imx35, पूर्ण,
	अणु .compatible = "fsl,imx31-sdma", .data = &sdma_imx31, पूर्ण,
	अणु .compatible = "fsl,imx25-sdma", .data = &sdma_imx25, पूर्ण,
	अणु .compatible = "fsl,imx7d-sdma", .data = &sdma_imx7d, पूर्ण,
	अणु .compatible = "fsl,imx8mq-sdma", .data = &sdma_imx8mq, पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sdma_dt_ids);

#घोषणा SDMA_H_CONFIG_DSPDMA	BIT(12) /* indicates अगर the DSPDMA is used */
#घोषणा SDMA_H_CONFIG_RTD_PINS	BIT(11) /* indicates अगर Real-Time Debug pins are enabled */
#घोषणा SDMA_H_CONFIG_ACR	BIT(4)  /* indicates अगर AHB freq /core freq = 2 or 1 */
#घोषणा SDMA_H_CONFIG_CSM	(3)       /* indicates which context चयन mode is selected*/

अटल अंतरभूत u32 chnenbl_ofs(काष्ठा sdma_engine *sdma, अचिन्हित पूर्णांक event)
अणु
	u32 chnenbl0 = sdma->drvdata->chnenbl0;
	वापस chnenbl0 + event * 4;
पूर्ण

अटल पूर्णांक sdma_config_ownership(काष्ठा sdma_channel *sdmac,
		bool event_override, bool mcu_override, bool dsp_override)
अणु
	काष्ठा sdma_engine *sdma = sdmac->sdma;
	पूर्णांक channel = sdmac->channel;
	अचिन्हित दीर्घ evt, mcu, dsp;

	अगर (event_override && mcu_override && dsp_override)
		वापस -EINVAL;

	evt = पढ़ोl_relaxed(sdma->regs + SDMA_H_EVTOVR);
	mcu = पढ़ोl_relaxed(sdma->regs + SDMA_H_HOSTOVR);
	dsp = पढ़ोl_relaxed(sdma->regs + SDMA_H_DSPOVR);

	अगर (dsp_override)
		__clear_bit(channel, &dsp);
	अन्यथा
		__set_bit(channel, &dsp);

	अगर (event_override)
		__clear_bit(channel, &evt);
	अन्यथा
		__set_bit(channel, &evt);

	अगर (mcu_override)
		__clear_bit(channel, &mcu);
	अन्यथा
		__set_bit(channel, &mcu);

	ग_लिखोl_relaxed(evt, sdma->regs + SDMA_H_EVTOVR);
	ग_लिखोl_relaxed(mcu, sdma->regs + SDMA_H_HOSTOVR);
	ग_लिखोl_relaxed(dsp, sdma->regs + SDMA_H_DSPOVR);

	वापस 0;
पूर्ण

अटल व्योम sdma_enable_channel(काष्ठा sdma_engine *sdma, पूर्णांक channel)
अणु
	ग_लिखोl(BIT(channel), sdma->regs + SDMA_H_START);
पूर्ण

/*
 * sdma_run_channel0 - run a channel and रुको till it's करोne
 */
अटल पूर्णांक sdma_run_channel0(काष्ठा sdma_engine *sdma)
अणु
	पूर्णांक ret;
	u32 reg;

	sdma_enable_channel(sdma, 0);

	ret = पढ़ोl_relaxed_poll_समयout_atomic(sdma->regs + SDMA_H_STATSTOP,
						reg, !(reg & 1), 1, 500);
	अगर (ret)
		dev_err(sdma->dev, "Timeout waiting for CH0 ready\n");

	/* Set bits of CONFIG रेजिस्टर with dynamic context चयनing */
	reg = पढ़ोl(sdma->regs + SDMA_H_CONFIG);
	अगर ((reg & SDMA_H_CONFIG_CSM) == 0) अणु
		reg |= SDMA_H_CONFIG_CSM;
		ग_लिखोl_relaxed(reg, sdma->regs + SDMA_H_CONFIG);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sdma_load_script(काष्ठा sdma_engine *sdma, व्योम *buf, पूर्णांक size,
		u32 address)
अणु
	काष्ठा sdma_buffer_descriptor *bd0 = sdma->bd0;
	व्योम *buf_virt;
	dma_addr_t buf_phys;
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	buf_virt = dma_alloc_coherent(sdma->dev, size, &buf_phys, GFP_KERNEL);
	अगर (!buf_virt) अणु
		वापस -ENOMEM;
	पूर्ण

	spin_lock_irqsave(&sdma->channel_0_lock, flags);

	bd0->mode.command = C0_SETPM;
	bd0->mode.status = BD_DONE | BD_WRAP | BD_EXTD;
	bd0->mode.count = size / 2;
	bd0->buffer_addr = buf_phys;
	bd0->ext_buffer_addr = address;

	स_नकल(buf_virt, buf, size);

	ret = sdma_run_channel0(sdma);

	spin_unlock_irqrestore(&sdma->channel_0_lock, flags);

	dma_मुक्त_coherent(sdma->dev, size, buf_virt, buf_phys);

	वापस ret;
पूर्ण

अटल व्योम sdma_event_enable(काष्ठा sdma_channel *sdmac, अचिन्हित पूर्णांक event)
अणु
	काष्ठा sdma_engine *sdma = sdmac->sdma;
	पूर्णांक channel = sdmac->channel;
	अचिन्हित दीर्घ val;
	u32 chnenbl = chnenbl_ofs(sdma, event);

	val = पढ़ोl_relaxed(sdma->regs + chnenbl);
	__set_bit(channel, &val);
	ग_लिखोl_relaxed(val, sdma->regs + chnenbl);
पूर्ण

अटल व्योम sdma_event_disable(काष्ठा sdma_channel *sdmac, अचिन्हित पूर्णांक event)
अणु
	काष्ठा sdma_engine *sdma = sdmac->sdma;
	पूर्णांक channel = sdmac->channel;
	u32 chnenbl = chnenbl_ofs(sdma, event);
	अचिन्हित दीर्घ val;

	val = पढ़ोl_relaxed(sdma->regs + chnenbl);
	__clear_bit(channel, &val);
	ग_लिखोl_relaxed(val, sdma->regs + chnenbl);
पूर्ण

अटल काष्ठा sdma_desc *to_sdma_desc(काष्ठा dma_async_tx_descriptor *t)
अणु
	वापस container_of(t, काष्ठा sdma_desc, vd.tx);
पूर्ण

अटल व्योम sdma_start_desc(काष्ठा sdma_channel *sdmac)
अणु
	काष्ठा virt_dma_desc *vd = vchan_next_desc(&sdmac->vc);
	काष्ठा sdma_desc *desc;
	काष्ठा sdma_engine *sdma = sdmac->sdma;
	पूर्णांक channel = sdmac->channel;

	अगर (!vd) अणु
		sdmac->desc = शून्य;
		वापस;
	पूर्ण
	sdmac->desc = desc = to_sdma_desc(&vd->tx);

	list_del(&vd->node);

	sdma->channel_control[channel].base_bd_ptr = desc->bd_phys;
	sdma->channel_control[channel].current_bd_ptr = desc->bd_phys;
	sdma_enable_channel(sdma, sdmac->channel);
पूर्ण

अटल व्योम sdma_update_channel_loop(काष्ठा sdma_channel *sdmac)
अणु
	काष्ठा sdma_buffer_descriptor *bd;
	पूर्णांक error = 0;
	क्रमागत dma_status	old_status = sdmac->status;

	/*
	 * loop mode. Iterate over descriptors, re-setup them and
	 * call callback function.
	 */
	जबतक (sdmac->desc) अणु
		काष्ठा sdma_desc *desc = sdmac->desc;

		bd = &desc->bd[desc->buf_tail];

		अगर (bd->mode.status & BD_DONE)
			अवरोध;

		अगर (bd->mode.status & BD_RROR) अणु
			bd->mode.status &= ~BD_RROR;
			sdmac->status = DMA_ERROR;
			error = -EIO;
		पूर्ण

	       /*
		* We use bd->mode.count to calculate the residue, since contains
		* the number of bytes present in the current buffer descriptor.
		*/

		desc->chn_real_count = bd->mode.count;
		bd->mode.status |= BD_DONE;
		bd->mode.count = desc->period_len;
		desc->buf_ptail = desc->buf_tail;
		desc->buf_tail = (desc->buf_tail + 1) % desc->num_bd;

		/*
		 * The callback is called from the पूर्णांकerrupt context in order
		 * to reduce latency and to aव्योम the risk of altering the
		 * SDMA transaction status by the समय the client tasklet is
		 * executed.
		 */
		spin_unlock(&sdmac->vc.lock);
		dmaengine_desc_get_callback_invoke(&desc->vd.tx, शून्य);
		spin_lock(&sdmac->vc.lock);

		अगर (error)
			sdmac->status = old_status;
	पूर्ण
पूर्ण

अटल व्योम mxc_sdma_handle_channel_normal(काष्ठा sdma_channel *data)
अणु
	काष्ठा sdma_channel *sdmac = (काष्ठा sdma_channel *) data;
	काष्ठा sdma_buffer_descriptor *bd;
	पूर्णांक i, error = 0;

	sdmac->desc->chn_real_count = 0;
	/*
	 * non loop mode. Iterate over all descriptors, collect
	 * errors and call callback function
	 */
	क्रम (i = 0; i < sdmac->desc->num_bd; i++) अणु
		bd = &sdmac->desc->bd[i];

		 अगर (bd->mode.status & (BD_DONE | BD_RROR))
			error = -EIO;
		 sdmac->desc->chn_real_count += bd->mode.count;
	पूर्ण

	अगर (error)
		sdmac->status = DMA_ERROR;
	अन्यथा
		sdmac->status = DMA_COMPLETE;
पूर्ण

अटल irqवापस_t sdma_पूर्णांक_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sdma_engine *sdma = dev_id;
	अचिन्हित दीर्घ stat;

	stat = पढ़ोl_relaxed(sdma->regs + SDMA_H_INTR);
	ग_लिखोl_relaxed(stat, sdma->regs + SDMA_H_INTR);
	/* channel 0 is special and not handled here, see run_channel0() */
	stat &= ~1;

	जबतक (stat) अणु
		पूर्णांक channel = fls(stat) - 1;
		काष्ठा sdma_channel *sdmac = &sdma->channel[channel];
		काष्ठा sdma_desc *desc;

		spin_lock(&sdmac->vc.lock);
		desc = sdmac->desc;
		अगर (desc) अणु
			अगर (sdmac->flags & IMX_DMA_SG_LOOP) अणु
				sdma_update_channel_loop(sdmac);
			पूर्ण अन्यथा अणु
				mxc_sdma_handle_channel_normal(sdmac);
				vchan_cookie_complete(&desc->vd);
				sdma_start_desc(sdmac);
			पूर्ण
		पूर्ण

		spin_unlock(&sdmac->vc.lock);
		__clear_bit(channel, &stat);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/*
 * sets the pc of SDMA script according to the peripheral type
 */
अटल व्योम sdma_get_pc(काष्ठा sdma_channel *sdmac,
		क्रमागत sdma_peripheral_type peripheral_type)
अणु
	काष्ठा sdma_engine *sdma = sdmac->sdma;
	पूर्णांक per_2_emi = 0, emi_2_per = 0;
	/*
	 * These are needed once we start to support transfers between
	 * two peripherals or memory-to-memory transfers
	 */
	पूर्णांक per_2_per = 0, emi_2_emi = 0;

	sdmac->pc_from_device = 0;
	sdmac->pc_to_device = 0;
	sdmac->device_to_device = 0;
	sdmac->pc_to_pc = 0;

	चयन (peripheral_type) अणु
	हाल IMX_DMATYPE_MEMORY:
		emi_2_emi = sdma->script_addrs->ap_2_ap_addr;
		अवरोध;
	हाल IMX_DMATYPE_DSP:
		emi_2_per = sdma->script_addrs->bp_2_ap_addr;
		per_2_emi = sdma->script_addrs->ap_2_bp_addr;
		अवरोध;
	हाल IMX_DMATYPE_FIRI:
		per_2_emi = sdma->script_addrs->firi_2_mcu_addr;
		emi_2_per = sdma->script_addrs->mcu_2_firi_addr;
		अवरोध;
	हाल IMX_DMATYPE_UART:
		per_2_emi = sdma->script_addrs->uart_2_mcu_addr;
		emi_2_per = sdma->script_addrs->mcu_2_app_addr;
		अवरोध;
	हाल IMX_DMATYPE_UART_SP:
		per_2_emi = sdma->script_addrs->uartsh_2_mcu_addr;
		emi_2_per = sdma->script_addrs->mcu_2_shp_addr;
		अवरोध;
	हाल IMX_DMATYPE_ATA:
		per_2_emi = sdma->script_addrs->ata_2_mcu_addr;
		emi_2_per = sdma->script_addrs->mcu_2_ata_addr;
		अवरोध;
	हाल IMX_DMATYPE_CSPI:
	हाल IMX_DMATYPE_EXT:
	हाल IMX_DMATYPE_SSI:
	हाल IMX_DMATYPE_SAI:
		per_2_emi = sdma->script_addrs->app_2_mcu_addr;
		emi_2_per = sdma->script_addrs->mcu_2_app_addr;
		अवरोध;
	हाल IMX_DMATYPE_SSI_DUAL:
		per_2_emi = sdma->script_addrs->ssish_2_mcu_addr;
		emi_2_per = sdma->script_addrs->mcu_2_ssish_addr;
		अवरोध;
	हाल IMX_DMATYPE_SSI_SP:
	हाल IMX_DMATYPE_MMC:
	हाल IMX_DMATYPE_SDHC:
	हाल IMX_DMATYPE_CSPI_SP:
	हाल IMX_DMATYPE_ESAI:
	हाल IMX_DMATYPE_MSHC_SP:
		per_2_emi = sdma->script_addrs->shp_2_mcu_addr;
		emi_2_per = sdma->script_addrs->mcu_2_shp_addr;
		अवरोध;
	हाल IMX_DMATYPE_ASRC:
		per_2_emi = sdma->script_addrs->asrc_2_mcu_addr;
		emi_2_per = sdma->script_addrs->asrc_2_mcu_addr;
		per_2_per = sdma->script_addrs->per_2_per_addr;
		अवरोध;
	हाल IMX_DMATYPE_ASRC_SP:
		per_2_emi = sdma->script_addrs->shp_2_mcu_addr;
		emi_2_per = sdma->script_addrs->mcu_2_shp_addr;
		per_2_per = sdma->script_addrs->per_2_per_addr;
		अवरोध;
	हाल IMX_DMATYPE_MSHC:
		per_2_emi = sdma->script_addrs->mshc_2_mcu_addr;
		emi_2_per = sdma->script_addrs->mcu_2_mshc_addr;
		अवरोध;
	हाल IMX_DMATYPE_CCM:
		per_2_emi = sdma->script_addrs->dptc_dvfs_addr;
		अवरोध;
	हाल IMX_DMATYPE_SPDIF:
		per_2_emi = sdma->script_addrs->spdअगर_2_mcu_addr;
		emi_2_per = sdma->script_addrs->mcu_2_spdअगर_addr;
		अवरोध;
	हाल IMX_DMATYPE_IPU_MEMORY:
		emi_2_per = sdma->script_addrs->ext_mem_2_ipu_addr;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	sdmac->pc_from_device = per_2_emi;
	sdmac->pc_to_device = emi_2_per;
	sdmac->device_to_device = per_2_per;
	sdmac->pc_to_pc = emi_2_emi;
पूर्ण

अटल पूर्णांक sdma_load_context(काष्ठा sdma_channel *sdmac)
अणु
	काष्ठा sdma_engine *sdma = sdmac->sdma;
	पूर्णांक channel = sdmac->channel;
	पूर्णांक load_address;
	काष्ठा sdma_context_data *context = sdma->context;
	काष्ठा sdma_buffer_descriptor *bd0 = sdma->bd0;
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	अगर (sdmac->context_loaded)
		वापस 0;

	अगर (sdmac->direction == DMA_DEV_TO_MEM)
		load_address = sdmac->pc_from_device;
	अन्यथा अगर (sdmac->direction == DMA_DEV_TO_DEV)
		load_address = sdmac->device_to_device;
	अन्यथा अगर (sdmac->direction == DMA_MEM_TO_MEM)
		load_address = sdmac->pc_to_pc;
	अन्यथा
		load_address = sdmac->pc_to_device;

	अगर (load_address < 0)
		वापस load_address;

	dev_dbg(sdma->dev, "load_address = %d\n", load_address);
	dev_dbg(sdma->dev, "wml = 0x%08x\n", (u32)sdmac->watermark_level);
	dev_dbg(sdma->dev, "shp_addr = 0x%08x\n", sdmac->shp_addr);
	dev_dbg(sdma->dev, "per_addr = 0x%08x\n", sdmac->per_addr);
	dev_dbg(sdma->dev, "event_mask0 = 0x%08x\n", (u32)sdmac->event_mask[0]);
	dev_dbg(sdma->dev, "event_mask1 = 0x%08x\n", (u32)sdmac->event_mask[1]);

	spin_lock_irqsave(&sdma->channel_0_lock, flags);

	स_रखो(context, 0, माप(*context));
	context->channel_state.pc = load_address;

	/* Send by context the event mask,base address क्रम peripheral
	 * and watermark level
	 */
	context->gReg[0] = sdmac->event_mask[1];
	context->gReg[1] = sdmac->event_mask[0];
	context->gReg[2] = sdmac->per_addr;
	context->gReg[6] = sdmac->shp_addr;
	context->gReg[7] = sdmac->watermark_level;

	bd0->mode.command = C0_SETDM;
	bd0->mode.status = BD_DONE | BD_WRAP | BD_EXTD;
	bd0->mode.count = माप(*context) / 4;
	bd0->buffer_addr = sdma->context_phys;
	bd0->ext_buffer_addr = 2048 + (माप(*context) / 4) * channel;
	ret = sdma_run_channel0(sdma);

	spin_unlock_irqrestore(&sdma->channel_0_lock, flags);

	sdmac->context_loaded = true;

	वापस ret;
पूर्ण

अटल काष्ठा sdma_channel *to_sdma_chan(काष्ठा dma_chan *chan)
अणु
	वापस container_of(chan, काष्ठा sdma_channel, vc.chan);
पूर्ण

अटल पूर्णांक sdma_disable_channel(काष्ठा dma_chan *chan)
अणु
	काष्ठा sdma_channel *sdmac = to_sdma_chan(chan);
	काष्ठा sdma_engine *sdma = sdmac->sdma;
	पूर्णांक channel = sdmac->channel;

	ग_लिखोl_relaxed(BIT(channel), sdma->regs + SDMA_H_STATSTOP);
	sdmac->status = DMA_ERROR;

	वापस 0;
पूर्ण
अटल व्योम sdma_channel_terminate_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sdma_channel *sdmac = container_of(work, काष्ठा sdma_channel,
						  terminate_worker);
	अचिन्हित दीर्घ flags;
	LIST_HEAD(head);

	/*
	 * According to NXP R&D team a delay of one BD SDMA cost समय
	 * (maximum is 1ms) should be added after disable of the channel
	 * bit, to ensure SDMA core has really been stopped after SDMA
	 * clients call .device_terminate_all.
	 */
	usleep_range(1000, 2000);

	spin_lock_irqsave(&sdmac->vc.lock, flags);
	vchan_get_all_descriptors(&sdmac->vc, &head);
	spin_unlock_irqrestore(&sdmac->vc.lock, flags);
	vchan_dma_desc_मुक्त_list(&sdmac->vc, &head);
	sdmac->context_loaded = false;
पूर्ण

अटल पूर्णांक sdma_terminate_all(काष्ठा dma_chan *chan)
अणु
	काष्ठा sdma_channel *sdmac = to_sdma_chan(chan);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sdmac->vc.lock, flags);

	sdma_disable_channel(chan);

	अगर (sdmac->desc) अणु
		vchan_terminate_vdesc(&sdmac->desc->vd);
		sdmac->desc = शून्य;
		schedule_work(&sdmac->terminate_worker);
	पूर्ण

	spin_unlock_irqrestore(&sdmac->vc.lock, flags);

	वापस 0;
पूर्ण

अटल व्योम sdma_channel_synchronize(काष्ठा dma_chan *chan)
अणु
	काष्ठा sdma_channel *sdmac = to_sdma_chan(chan);

	vchan_synchronize(&sdmac->vc);

	flush_work(&sdmac->terminate_worker);
पूर्ण

अटल व्योम sdma_set_watermarklevel_क्रम_p2p(काष्ठा sdma_channel *sdmac)
अणु
	काष्ठा sdma_engine *sdma = sdmac->sdma;

	पूर्णांक lwml = sdmac->watermark_level & SDMA_WATERMARK_LEVEL_LWML;
	पूर्णांक hwml = (sdmac->watermark_level & SDMA_WATERMARK_LEVEL_HWML) >> 16;

	set_bit(sdmac->event_id0 % 32, &sdmac->event_mask[1]);
	set_bit(sdmac->event_id1 % 32, &sdmac->event_mask[0]);

	अगर (sdmac->event_id0 > 31)
		sdmac->watermark_level |= SDMA_WATERMARK_LEVEL_LWE;

	अगर (sdmac->event_id1 > 31)
		sdmac->watermark_level |= SDMA_WATERMARK_LEVEL_HWE;

	/*
	 * If LWML(src_maxburst) > HWML(dst_maxburst), we need
	 * swap LWML and HWML of INFO(A.3.2.5.1), also need swap
	 * r0(event_mask[1]) and r1(event_mask[0]).
	 */
	अगर (lwml > hwml) अणु
		sdmac->watermark_level &= ~(SDMA_WATERMARK_LEVEL_LWML |
						SDMA_WATERMARK_LEVEL_HWML);
		sdmac->watermark_level |= hwml;
		sdmac->watermark_level |= lwml << 16;
		swap(sdmac->event_mask[0], sdmac->event_mask[1]);
	पूर्ण

	अगर (sdmac->per_address2 >= sdma->spba_start_addr &&
			sdmac->per_address2 <= sdma->spba_end_addr)
		sdmac->watermark_level |= SDMA_WATERMARK_LEVEL_SP;

	अगर (sdmac->per_address >= sdma->spba_start_addr &&
			sdmac->per_address <= sdma->spba_end_addr)
		sdmac->watermark_level |= SDMA_WATERMARK_LEVEL_DP;

	sdmac->watermark_level |= SDMA_WATERMARK_LEVEL_CONT;
पूर्ण

अटल पूर्णांक sdma_config_channel(काष्ठा dma_chan *chan)
अणु
	काष्ठा sdma_channel *sdmac = to_sdma_chan(chan);
	पूर्णांक ret;

	sdma_disable_channel(chan);

	sdmac->event_mask[0] = 0;
	sdmac->event_mask[1] = 0;
	sdmac->shp_addr = 0;
	sdmac->per_addr = 0;

	चयन (sdmac->peripheral_type) अणु
	हाल IMX_DMATYPE_DSP:
		sdma_config_ownership(sdmac, false, true, true);
		अवरोध;
	हाल IMX_DMATYPE_MEMORY:
		sdma_config_ownership(sdmac, false, true, false);
		अवरोध;
	शेष:
		sdma_config_ownership(sdmac, true, true, false);
		अवरोध;
	पूर्ण

	sdma_get_pc(sdmac, sdmac->peripheral_type);

	अगर ((sdmac->peripheral_type != IMX_DMATYPE_MEMORY) &&
			(sdmac->peripheral_type != IMX_DMATYPE_DSP)) अणु
		/* Handle multiple event channels dअगरferently */
		अगर (sdmac->event_id1) अणु
			अगर (sdmac->peripheral_type == IMX_DMATYPE_ASRC_SP ||
			    sdmac->peripheral_type == IMX_DMATYPE_ASRC)
				sdma_set_watermarklevel_क्रम_p2p(sdmac);
		पूर्ण अन्यथा
			__set_bit(sdmac->event_id0, sdmac->event_mask);

		/* Address */
		sdmac->shp_addr = sdmac->per_address;
		sdmac->per_addr = sdmac->per_address2;
	पूर्ण अन्यथा अणु
		sdmac->watermark_level = 0; /* FIXME: M3_BASE_ADDRESS */
	पूर्ण

	ret = sdma_load_context(sdmac);

	वापस ret;
पूर्ण

अटल पूर्णांक sdma_set_channel_priority(काष्ठा sdma_channel *sdmac,
		अचिन्हित पूर्णांक priority)
अणु
	काष्ठा sdma_engine *sdma = sdmac->sdma;
	पूर्णांक channel = sdmac->channel;

	अगर (priority < MXC_SDMA_MIN_PRIORITY
	    || priority > MXC_SDMA_MAX_PRIORITY) अणु
		वापस -EINVAL;
	पूर्ण

	ग_लिखोl_relaxed(priority, sdma->regs + SDMA_CHNPRI_0 + 4 * channel);

	वापस 0;
पूर्ण

अटल पूर्णांक sdma_request_channel0(काष्ठा sdma_engine *sdma)
अणु
	पूर्णांक ret = -EBUSY;

	sdma->bd0 = dma_alloc_coherent(sdma->dev, PAGE_SIZE, &sdma->bd0_phys,
					GFP_NOWAIT);
	अगर (!sdma->bd0) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	sdma->channel_control[0].base_bd_ptr = sdma->bd0_phys;
	sdma->channel_control[0].current_bd_ptr = sdma->bd0_phys;

	sdma_set_channel_priority(&sdma->channel[0], MXC_SDMA_DEFAULT_PRIORITY);
	वापस 0;
out:

	वापस ret;
पूर्ण


अटल पूर्णांक sdma_alloc_bd(काष्ठा sdma_desc *desc)
अणु
	u32 bd_size = desc->num_bd * माप(काष्ठा sdma_buffer_descriptor);
	पूर्णांक ret = 0;

	desc->bd = dma_alloc_coherent(desc->sdmac->sdma->dev, bd_size,
				       &desc->bd_phys, GFP_NOWAIT);
	अगर (!desc->bd) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल व्योम sdma_मुक्त_bd(काष्ठा sdma_desc *desc)
अणु
	u32 bd_size = desc->num_bd * माप(काष्ठा sdma_buffer_descriptor);

	dma_मुक्त_coherent(desc->sdmac->sdma->dev, bd_size, desc->bd,
			  desc->bd_phys);
पूर्ण

अटल व्योम sdma_desc_मुक्त(काष्ठा virt_dma_desc *vd)
अणु
	काष्ठा sdma_desc *desc = container_of(vd, काष्ठा sdma_desc, vd);

	sdma_मुक्त_bd(desc);
	kमुक्त(desc);
पूर्ण

अटल पूर्णांक sdma_alloc_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा sdma_channel *sdmac = to_sdma_chan(chan);
	काष्ठा imx_dma_data *data = chan->निजी;
	काष्ठा imx_dma_data mem_data;
	पूर्णांक prio, ret;

	/*
	 * MEMCPY may never setup chan->निजी by filter function such as
	 * dmatest, thus create 'struct imx_dma_data mem_data' क्रम this हाल.
	 * Please note in any other slave हाल, you have to setup chan->निजी
	 * with 'struct imx_dma_data' in your own filter function अगर you want to
	 * request dma channel by dma_request_channel() rather than
	 * dma_request_slave_channel(). Othwise, 'MEMCPY in case?' will appear
	 * to warn you to correct your filter function.
	 */
	अगर (!data) अणु
		dev_dbg(sdmac->sdma->dev, "MEMCPY in case?\n");
		mem_data.priority = 2;
		mem_data.peripheral_type = IMX_DMATYPE_MEMORY;
		mem_data.dma_request = 0;
		mem_data.dma_request2 = 0;
		data = &mem_data;

		sdma_get_pc(sdmac, IMX_DMATYPE_MEMORY);
	पूर्ण

	चयन (data->priority) अणु
	हाल DMA_PRIO_HIGH:
		prio = 3;
		अवरोध;
	हाल DMA_PRIO_MEDIUM:
		prio = 2;
		अवरोध;
	हाल DMA_PRIO_LOW:
	शेष:
		prio = 1;
		अवरोध;
	पूर्ण

	sdmac->peripheral_type = data->peripheral_type;
	sdmac->event_id0 = data->dma_request;
	sdmac->event_id1 = data->dma_request2;

	ret = clk_enable(sdmac->sdma->clk_ipg);
	अगर (ret)
		वापस ret;
	ret = clk_enable(sdmac->sdma->clk_ahb);
	अगर (ret)
		जाओ disable_clk_ipg;

	ret = sdma_set_channel_priority(sdmac, prio);
	अगर (ret)
		जाओ disable_clk_ahb;

	वापस 0;

disable_clk_ahb:
	clk_disable(sdmac->sdma->clk_ahb);
disable_clk_ipg:
	clk_disable(sdmac->sdma->clk_ipg);
	वापस ret;
पूर्ण

अटल व्योम sdma_मुक्त_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा sdma_channel *sdmac = to_sdma_chan(chan);
	काष्ठा sdma_engine *sdma = sdmac->sdma;

	sdma_terminate_all(chan);

	sdma_channel_synchronize(chan);

	sdma_event_disable(sdmac, sdmac->event_id0);
	अगर (sdmac->event_id1)
		sdma_event_disable(sdmac, sdmac->event_id1);

	sdmac->event_id0 = 0;
	sdmac->event_id1 = 0;
	sdmac->context_loaded = false;

	sdma_set_channel_priority(sdmac, 0);

	clk_disable(sdma->clk_ipg);
	clk_disable(sdma->clk_ahb);
पूर्ण

अटल काष्ठा sdma_desc *sdma_transfer_init(काष्ठा sdma_channel *sdmac,
				क्रमागत dma_transfer_direction direction, u32 bds)
अणु
	काष्ठा sdma_desc *desc;

	desc = kzalloc((माप(*desc)), GFP_NOWAIT);
	अगर (!desc)
		जाओ err_out;

	sdmac->status = DMA_IN_PROGRESS;
	sdmac->direction = direction;
	sdmac->flags = 0;

	desc->chn_count = 0;
	desc->chn_real_count = 0;
	desc->buf_tail = 0;
	desc->buf_ptail = 0;
	desc->sdmac = sdmac;
	desc->num_bd = bds;

	अगर (sdma_alloc_bd(desc))
		जाओ err_desc_out;

	/* No slave_config called in MEMCPY हाल, so करो here */
	अगर (direction == DMA_MEM_TO_MEM)
		sdma_config_ownership(sdmac, false, true, false);

	अगर (sdma_load_context(sdmac))
		जाओ err_desc_out;

	वापस desc;

err_desc_out:
	kमुक्त(desc);
err_out:
	वापस शून्य;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *sdma_prep_स_नकल(
		काष्ठा dma_chan *chan, dma_addr_t dma_dst,
		dma_addr_t dma_src, माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा sdma_channel *sdmac = to_sdma_chan(chan);
	काष्ठा sdma_engine *sdma = sdmac->sdma;
	पूर्णांक channel = sdmac->channel;
	माप_प्रकार count;
	पूर्णांक i = 0, param;
	काष्ठा sdma_buffer_descriptor *bd;
	काष्ठा sdma_desc *desc;

	अगर (!chan || !len)
		वापस शून्य;

	dev_dbg(sdma->dev, "memcpy: %pad->%pad, len=%zu, channel=%d.\n",
		&dma_src, &dma_dst, len, channel);

	desc = sdma_transfer_init(sdmac, DMA_MEM_TO_MEM,
					len / SDMA_BD_MAX_CNT + 1);
	अगर (!desc)
		वापस शून्य;

	करो अणु
		count = min_t(माप_प्रकार, len, SDMA_BD_MAX_CNT);
		bd = &desc->bd[i];
		bd->buffer_addr = dma_src;
		bd->ext_buffer_addr = dma_dst;
		bd->mode.count = count;
		desc->chn_count += count;
		bd->mode.command = 0;

		dma_src += count;
		dma_dst += count;
		len -= count;
		i++;

		param = BD_DONE | BD_EXTD | BD_CONT;
		/* last bd */
		अगर (!len) अणु
			param |= BD_INTR;
			param |= BD_LAST;
			param &= ~BD_CONT;
		पूर्ण

		dev_dbg(sdma->dev, "entry %d: count: %zd dma: 0x%x %s%s\n",
				i, count, bd->buffer_addr,
				param & BD_WRAP ? "wrap" : "",
				param & BD_INTR ? " intr" : "");

		bd->mode.status = param;
	पूर्ण जबतक (len);

	वापस vchan_tx_prep(&sdmac->vc, &desc->vd, flags);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *sdma_prep_slave_sg(
		काष्ठा dma_chan *chan, काष्ठा scatterlist *sgl,
		अचिन्हित पूर्णांक sg_len, क्रमागत dma_transfer_direction direction,
		अचिन्हित दीर्घ flags, व्योम *context)
अणु
	काष्ठा sdma_channel *sdmac = to_sdma_chan(chan);
	काष्ठा sdma_engine *sdma = sdmac->sdma;
	पूर्णांक i, count;
	पूर्णांक channel = sdmac->channel;
	काष्ठा scatterlist *sg;
	काष्ठा sdma_desc *desc;

	sdma_config_ग_लिखो(chan, &sdmac->slave_config, direction);

	desc = sdma_transfer_init(sdmac, direction, sg_len);
	अगर (!desc)
		जाओ err_out;

	dev_dbg(sdma->dev, "setting up %d entries for channel %d.\n",
			sg_len, channel);

	क्रम_each_sg(sgl, sg, sg_len, i) अणु
		काष्ठा sdma_buffer_descriptor *bd = &desc->bd[i];
		पूर्णांक param;

		bd->buffer_addr = sg->dma_address;

		count = sg_dma_len(sg);

		अगर (count > SDMA_BD_MAX_CNT) अणु
			dev_err(sdma->dev, "SDMA channel %d: maximum bytes for sg entry exceeded: %d > %d\n",
					channel, count, SDMA_BD_MAX_CNT);
			जाओ err_bd_out;
		पूर्ण

		bd->mode.count = count;
		desc->chn_count += count;

		अगर (sdmac->word_size > DMA_SLAVE_BUSWIDTH_4_BYTES)
			जाओ err_bd_out;

		चयन (sdmac->word_size) अणु
		हाल DMA_SLAVE_BUSWIDTH_4_BYTES:
			bd->mode.command = 0;
			अगर (count & 3 || sg->dma_address & 3)
				जाओ err_bd_out;
			अवरोध;
		हाल DMA_SLAVE_BUSWIDTH_2_BYTES:
			bd->mode.command = 2;
			अगर (count & 1 || sg->dma_address & 1)
				जाओ err_bd_out;
			अवरोध;
		हाल DMA_SLAVE_BUSWIDTH_1_BYTE:
			bd->mode.command = 1;
			अवरोध;
		शेष:
			जाओ err_bd_out;
		पूर्ण

		param = BD_DONE | BD_EXTD | BD_CONT;

		अगर (i + 1 == sg_len) अणु
			param |= BD_INTR;
			param |= BD_LAST;
			param &= ~BD_CONT;
		पूर्ण

		dev_dbg(sdma->dev, "entry %d: count: %d dma: %#llx %s%s\n",
				i, count, (u64)sg->dma_address,
				param & BD_WRAP ? "wrap" : "",
				param & BD_INTR ? " intr" : "");

		bd->mode.status = param;
	पूर्ण

	वापस vchan_tx_prep(&sdmac->vc, &desc->vd, flags);
err_bd_out:
	sdma_मुक्त_bd(desc);
	kमुक्त(desc);
err_out:
	sdmac->status = DMA_ERROR;
	वापस शून्य;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *sdma_prep_dma_cyclic(
		काष्ठा dma_chan *chan, dma_addr_t dma_addr, माप_प्रकार buf_len,
		माप_प्रकार period_len, क्रमागत dma_transfer_direction direction,
		अचिन्हित दीर्घ flags)
अणु
	काष्ठा sdma_channel *sdmac = to_sdma_chan(chan);
	काष्ठा sdma_engine *sdma = sdmac->sdma;
	पूर्णांक num_periods = buf_len / period_len;
	पूर्णांक channel = sdmac->channel;
	पूर्णांक i = 0, buf = 0;
	काष्ठा sdma_desc *desc;

	dev_dbg(sdma->dev, "%s channel: %d\n", __func__, channel);

	sdma_config_ग_लिखो(chan, &sdmac->slave_config, direction);

	desc = sdma_transfer_init(sdmac, direction, num_periods);
	अगर (!desc)
		जाओ err_out;

	desc->period_len = period_len;

	sdmac->flags |= IMX_DMA_SG_LOOP;

	अगर (period_len > SDMA_BD_MAX_CNT) अणु
		dev_err(sdma->dev, "SDMA channel %d: maximum period size exceeded: %zu > %d\n",
				channel, period_len, SDMA_BD_MAX_CNT);
		जाओ err_bd_out;
	पूर्ण

	जबतक (buf < buf_len) अणु
		काष्ठा sdma_buffer_descriptor *bd = &desc->bd[i];
		पूर्णांक param;

		bd->buffer_addr = dma_addr;

		bd->mode.count = period_len;

		अगर (sdmac->word_size > DMA_SLAVE_BUSWIDTH_4_BYTES)
			जाओ err_bd_out;
		अगर (sdmac->word_size == DMA_SLAVE_BUSWIDTH_4_BYTES)
			bd->mode.command = 0;
		अन्यथा
			bd->mode.command = sdmac->word_size;

		param = BD_DONE | BD_EXTD | BD_CONT | BD_INTR;
		अगर (i + 1 == num_periods)
			param |= BD_WRAP;

		dev_dbg(sdma->dev, "entry %d: count: %zu dma: %#llx %s%s\n",
				i, period_len, (u64)dma_addr,
				param & BD_WRAP ? "wrap" : "",
				param & BD_INTR ? " intr" : "");

		bd->mode.status = param;

		dma_addr += period_len;
		buf += period_len;

		i++;
	पूर्ण

	वापस vchan_tx_prep(&sdmac->vc, &desc->vd, flags);
err_bd_out:
	sdma_मुक्त_bd(desc);
	kमुक्त(desc);
err_out:
	sdmac->status = DMA_ERROR;
	वापस शून्य;
पूर्ण

अटल पूर्णांक sdma_config_ग_लिखो(काष्ठा dma_chan *chan,
		       काष्ठा dma_slave_config *dmaengine_cfg,
		       क्रमागत dma_transfer_direction direction)
अणु
	काष्ठा sdma_channel *sdmac = to_sdma_chan(chan);

	अगर (direction == DMA_DEV_TO_MEM) अणु
		sdmac->per_address = dmaengine_cfg->src_addr;
		sdmac->watermark_level = dmaengine_cfg->src_maxburst *
			dmaengine_cfg->src_addr_width;
		sdmac->word_size = dmaengine_cfg->src_addr_width;
	पूर्ण अन्यथा अगर (direction == DMA_DEV_TO_DEV) अणु
		sdmac->per_address2 = dmaengine_cfg->src_addr;
		sdmac->per_address = dmaengine_cfg->dst_addr;
		sdmac->watermark_level = dmaengine_cfg->src_maxburst &
			SDMA_WATERMARK_LEVEL_LWML;
		sdmac->watermark_level |= (dmaengine_cfg->dst_maxburst << 16) &
			SDMA_WATERMARK_LEVEL_HWML;
		sdmac->word_size = dmaengine_cfg->dst_addr_width;
	पूर्ण अन्यथा अणु
		sdmac->per_address = dmaengine_cfg->dst_addr;
		sdmac->watermark_level = dmaengine_cfg->dst_maxburst *
			dmaengine_cfg->dst_addr_width;
		sdmac->word_size = dmaengine_cfg->dst_addr_width;
	पूर्ण
	sdmac->direction = direction;
	वापस sdma_config_channel(chan);
पूर्ण

अटल पूर्णांक sdma_config(काष्ठा dma_chan *chan,
		       काष्ठा dma_slave_config *dmaengine_cfg)
अणु
	काष्ठा sdma_channel *sdmac = to_sdma_chan(chan);

	स_नकल(&sdmac->slave_config, dmaengine_cfg, माप(*dmaengine_cfg));

	/* Set ENBLn earlier to make sure dma request triggered after that */
	अगर (sdmac->event_id0 >= sdmac->sdma->drvdata->num_events)
		वापस -EINVAL;
	sdma_event_enable(sdmac, sdmac->event_id0);

	अगर (sdmac->event_id1) अणु
		अगर (sdmac->event_id1 >= sdmac->sdma->drvdata->num_events)
			वापस -EINVAL;
		sdma_event_enable(sdmac, sdmac->event_id1);
	पूर्ण

	वापस 0;
पूर्ण

अटल क्रमागत dma_status sdma_tx_status(काष्ठा dma_chan *chan,
				      dma_cookie_t cookie,
				      काष्ठा dma_tx_state *txstate)
अणु
	काष्ठा sdma_channel *sdmac = to_sdma_chan(chan);
	काष्ठा sdma_desc *desc = शून्य;
	u32 residue;
	काष्ठा virt_dma_desc *vd;
	क्रमागत dma_status ret;
	अचिन्हित दीर्घ flags;

	ret = dma_cookie_status(chan, cookie, txstate);
	अगर (ret == DMA_COMPLETE || !txstate)
		वापस ret;

	spin_lock_irqsave(&sdmac->vc.lock, flags);

	vd = vchan_find_desc(&sdmac->vc, cookie);
	अगर (vd)
		desc = to_sdma_desc(&vd->tx);
	अन्यथा अगर (sdmac->desc && sdmac->desc->vd.tx.cookie == cookie)
		desc = sdmac->desc;

	अगर (desc) अणु
		अगर (sdmac->flags & IMX_DMA_SG_LOOP)
			residue = (desc->num_bd - desc->buf_ptail) *
				desc->period_len - desc->chn_real_count;
		अन्यथा
			residue = desc->chn_count - desc->chn_real_count;
	पूर्ण अन्यथा अणु
		residue = 0;
	पूर्ण

	spin_unlock_irqrestore(&sdmac->vc.lock, flags);

	dma_set_tx_state(txstate, chan->completed_cookie, chan->cookie,
			 residue);

	वापस sdmac->status;
पूर्ण

अटल व्योम sdma_issue_pending(काष्ठा dma_chan *chan)
अणु
	काष्ठा sdma_channel *sdmac = to_sdma_chan(chan);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sdmac->vc.lock, flags);
	अगर (vchan_issue_pending(&sdmac->vc) && !sdmac->desc)
		sdma_start_desc(sdmac);
	spin_unlock_irqrestore(&sdmac->vc.lock, flags);
पूर्ण

#घोषणा SDMA_SCRIPT_ADDRS_ARRAY_SIZE_V1	34
#घोषणा SDMA_SCRIPT_ADDRS_ARRAY_SIZE_V2	38
#घोषणा SDMA_SCRIPT_ADDRS_ARRAY_SIZE_V3	41
#घोषणा SDMA_SCRIPT_ADDRS_ARRAY_SIZE_V4	42

अटल व्योम sdma_add_scripts(काष्ठा sdma_engine *sdma,
		स्थिर काष्ठा sdma_script_start_addrs *addr)
अणु
	s32 *addr_arr = (u32 *)addr;
	s32 *saddr_arr = (u32 *)sdma->script_addrs;
	पूर्णांक i;

	/* use the शेष firmware in ROM अगर missing बाह्यal firmware */
	अगर (!sdma->script_number)
		sdma->script_number = SDMA_SCRIPT_ADDRS_ARRAY_SIZE_V1;

	अगर (sdma->script_number > माप(काष्ठा sdma_script_start_addrs)
				  / माप(s32)) अणु
		dev_err(sdma->dev,
			"SDMA script number %d not match with firmware.\n",
			sdma->script_number);
		वापस;
	पूर्ण

	क्रम (i = 0; i < sdma->script_number; i++)
		अगर (addr_arr[i] > 0)
			saddr_arr[i] = addr_arr[i];
पूर्ण

अटल व्योम sdma_load_firmware(स्थिर काष्ठा firmware *fw, व्योम *context)
अणु
	काष्ठा sdma_engine *sdma = context;
	स्थिर काष्ठा sdma_firmware_header *header;
	स्थिर काष्ठा sdma_script_start_addrs *addr;
	अचिन्हित लघु *ram_code;

	अगर (!fw) अणु
		dev_info(sdma->dev, "external firmware not found, using ROM firmware\n");
		/* In this हाल we just use the ROM firmware. */
		वापस;
	पूर्ण

	अगर (fw->size < माप(*header))
		जाओ err_firmware;

	header = (काष्ठा sdma_firmware_header *)fw->data;

	अगर (header->magic != SDMA_FIRMWARE_MAGIC)
		जाओ err_firmware;
	अगर (header->ram_code_start + header->ram_code_size > fw->size)
		जाओ err_firmware;
	चयन (header->version_major) अणु
	हाल 1:
		sdma->script_number = SDMA_SCRIPT_ADDRS_ARRAY_SIZE_V1;
		अवरोध;
	हाल 2:
		sdma->script_number = SDMA_SCRIPT_ADDRS_ARRAY_SIZE_V2;
		अवरोध;
	हाल 3:
		sdma->script_number = SDMA_SCRIPT_ADDRS_ARRAY_SIZE_V3;
		अवरोध;
	हाल 4:
		sdma->script_number = SDMA_SCRIPT_ADDRS_ARRAY_SIZE_V4;
		अवरोध;
	शेष:
		dev_err(sdma->dev, "unknown firmware version\n");
		जाओ err_firmware;
	पूर्ण

	addr = (व्योम *)header + header->script_addrs_start;
	ram_code = (व्योम *)header + header->ram_code_start;

	clk_enable(sdma->clk_ipg);
	clk_enable(sdma->clk_ahb);
	/* करोwnload the RAM image क्रम SDMA */
	sdma_load_script(sdma, ram_code,
			header->ram_code_size,
			addr->ram_code_start_addr);
	clk_disable(sdma->clk_ipg);
	clk_disable(sdma->clk_ahb);

	sdma_add_scripts(sdma, addr);

	dev_info(sdma->dev, "loaded firmware %d.%d\n",
			header->version_major,
			header->version_minor);

err_firmware:
	release_firmware(fw);
पूर्ण

#घोषणा EVENT_REMAP_CELLS 3

अटल पूर्णांक sdma_event_remap(काष्ठा sdma_engine *sdma)
अणु
	काष्ठा device_node *np = sdma->dev->of_node;
	काष्ठा device_node *gpr_np = of_parse_phandle(np, "gpr", 0);
	काष्ठा property *event_remap;
	काष्ठा regmap *gpr;
	अक्षर propname[] = "fsl,sdma-event-remap";
	u32 reg, val, shअगरt, num_map, i;
	पूर्णांक ret = 0;

	अगर (IS_ERR(np) || IS_ERR(gpr_np))
		जाओ out;

	event_remap = of_find_property(np, propname, शून्य);
	num_map = event_remap ? (event_remap->length / माप(u32)) : 0;
	अगर (!num_map) अणु
		dev_dbg(sdma->dev, "no event needs to be remapped\n");
		जाओ out;
	पूर्ण अन्यथा अगर (num_map % EVENT_REMAP_CELLS) अणु
		dev_err(sdma->dev, "the property %s must modulo %d\n",
				propname, EVENT_REMAP_CELLS);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	gpr = syscon_node_to_regmap(gpr_np);
	अगर (IS_ERR(gpr)) अणु
		dev_err(sdma->dev, "failed to get gpr regmap\n");
		ret = PTR_ERR(gpr);
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < num_map; i += EVENT_REMAP_CELLS) अणु
		ret = of_property_पढ़ो_u32_index(np, propname, i, &reg);
		अगर (ret) अणु
			dev_err(sdma->dev, "failed to read property %s index %d\n",
					propname, i);
			जाओ out;
		पूर्ण

		ret = of_property_पढ़ो_u32_index(np, propname, i + 1, &shअगरt);
		अगर (ret) अणु
			dev_err(sdma->dev, "failed to read property %s index %d\n",
					propname, i + 1);
			जाओ out;
		पूर्ण

		ret = of_property_पढ़ो_u32_index(np, propname, i + 2, &val);
		अगर (ret) अणु
			dev_err(sdma->dev, "failed to read property %s index %d\n",
					propname, i + 2);
			जाओ out;
		पूर्ण

		regmap_update_bits(gpr, reg, BIT(shअगरt), val << shअगरt);
	पूर्ण

out:
	अगर (!IS_ERR(gpr_np))
		of_node_put(gpr_np);

	वापस ret;
पूर्ण

अटल पूर्णांक sdma_get_firmware(काष्ठा sdma_engine *sdma,
		स्थिर अक्षर *fw_name)
अणु
	पूर्णांक ret;

	ret = request_firmware_noरुको(THIS_MODULE,
			FW_ACTION_HOTPLUG, fw_name, sdma->dev,
			GFP_KERNEL, sdma, sdma_load_firmware);

	वापस ret;
पूर्ण

अटल पूर्णांक sdma_init(काष्ठा sdma_engine *sdma)
अणु
	पूर्णांक i, ret;
	dma_addr_t ccb_phys;

	ret = clk_enable(sdma->clk_ipg);
	अगर (ret)
		वापस ret;
	ret = clk_enable(sdma->clk_ahb);
	अगर (ret)
		जाओ disable_clk_ipg;

	अगर (sdma->drvdata->check_ratio &&
	    (clk_get_rate(sdma->clk_ahb) == clk_get_rate(sdma->clk_ipg)))
		sdma->clk_ratio = 1;

	/* Be sure SDMA has not started yet */
	ग_लिखोl_relaxed(0, sdma->regs + SDMA_H_C0PTR);

	sdma->channel_control = dma_alloc_coherent(sdma->dev,
			MAX_DMA_CHANNELS * माप (काष्ठा sdma_channel_control) +
			माप(काष्ठा sdma_context_data),
			&ccb_phys, GFP_KERNEL);

	अगर (!sdma->channel_control) अणु
		ret = -ENOMEM;
		जाओ err_dma_alloc;
	पूर्ण

	sdma->context = (व्योम *)sdma->channel_control +
		MAX_DMA_CHANNELS * माप (काष्ठा sdma_channel_control);
	sdma->context_phys = ccb_phys +
		MAX_DMA_CHANNELS * माप (काष्ठा sdma_channel_control);

	/* disable all channels */
	क्रम (i = 0; i < sdma->drvdata->num_events; i++)
		ग_लिखोl_relaxed(0, sdma->regs + chnenbl_ofs(sdma, i));

	/* All channels have priority 0 */
	क्रम (i = 0; i < MAX_DMA_CHANNELS; i++)
		ग_लिखोl_relaxed(0, sdma->regs + SDMA_CHNPRI_0 + i * 4);

	ret = sdma_request_channel0(sdma);
	अगर (ret)
		जाओ err_dma_alloc;

	sdma_config_ownership(&sdma->channel[0], false, true, false);

	/* Set Command Channel (Channel Zero) */
	ग_लिखोl_relaxed(0x4050, sdma->regs + SDMA_CHN0ADDR);

	/* Set bits of CONFIG रेजिस्टर but with अटल context चयनing */
	अगर (sdma->clk_ratio)
		ग_लिखोl_relaxed(SDMA_H_CONFIG_ACR, sdma->regs + SDMA_H_CONFIG);
	अन्यथा
		ग_लिखोl_relaxed(0, sdma->regs + SDMA_H_CONFIG);

	ग_लिखोl_relaxed(ccb_phys, sdma->regs + SDMA_H_C0PTR);

	/* Initializes channel's priorities */
	sdma_set_channel_priority(&sdma->channel[0], 7);

	clk_disable(sdma->clk_ipg);
	clk_disable(sdma->clk_ahb);

	वापस 0;

err_dma_alloc:
	clk_disable(sdma->clk_ahb);
disable_clk_ipg:
	clk_disable(sdma->clk_ipg);
	dev_err(sdma->dev, "initialisation failed with %d\n", ret);
	वापस ret;
पूर्ण

अटल bool sdma_filter_fn(काष्ठा dma_chan *chan, व्योम *fn_param)
अणु
	काष्ठा sdma_channel *sdmac = to_sdma_chan(chan);
	काष्ठा imx_dma_data *data = fn_param;

	अगर (!imx_dma_is_general_purpose(chan))
		वापस false;

	sdmac->data = *data;
	chan->निजी = &sdmac->data;

	वापस true;
पूर्ण

अटल काष्ठा dma_chan *sdma_xlate(काष्ठा of_phandle_args *dma_spec,
				   काष्ठा of_dma *ofdma)
अणु
	काष्ठा sdma_engine *sdma = ofdma->of_dma_data;
	dma_cap_mask_t mask = sdma->dma_device.cap_mask;
	काष्ठा imx_dma_data data;

	अगर (dma_spec->args_count != 3)
		वापस शून्य;

	data.dma_request = dma_spec->args[0];
	data.peripheral_type = dma_spec->args[1];
	data.priority = dma_spec->args[2];
	/*
	 * init dma_request2 to zero, which is not used by the dts.
	 * For P2P, dma_request2 is init from dma_request_channel(),
	 * chan->निजी will poपूर्णांक to the imx_dma_data, and in
	 * device_alloc_chan_resources(), imx_dma_data.dma_request2 will
	 * be set to sdmac->event_id1.
	 */
	data.dma_request2 = 0;

	वापस __dma_request_channel(&mask, sdma_filter_fn, &data,
				     ofdma->of_node);
पूर्ण

अटल पूर्णांक sdma_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device_node *spba_bus;
	स्थिर अक्षर *fw_name;
	पूर्णांक ret;
	पूर्णांक irq;
	काष्ठा resource *iores;
	काष्ठा resource spba_res;
	पूर्णांक i;
	काष्ठा sdma_engine *sdma;
	s32 *saddr_arr;

	ret = dma_coerce_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	अगर (ret)
		वापस ret;

	sdma = devm_kzalloc(&pdev->dev, माप(*sdma), GFP_KERNEL);
	अगर (!sdma)
		वापस -ENOMEM;

	spin_lock_init(&sdma->channel_0_lock);

	sdma->dev = &pdev->dev;
	sdma->drvdata = of_device_get_match_data(sdma->dev);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	iores = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	sdma->regs = devm_ioremap_resource(&pdev->dev, iores);
	अगर (IS_ERR(sdma->regs))
		वापस PTR_ERR(sdma->regs);

	sdma->clk_ipg = devm_clk_get(&pdev->dev, "ipg");
	अगर (IS_ERR(sdma->clk_ipg))
		वापस PTR_ERR(sdma->clk_ipg);

	sdma->clk_ahb = devm_clk_get(&pdev->dev, "ahb");
	अगर (IS_ERR(sdma->clk_ahb))
		वापस PTR_ERR(sdma->clk_ahb);

	ret = clk_prepare(sdma->clk_ipg);
	अगर (ret)
		वापस ret;

	ret = clk_prepare(sdma->clk_ahb);
	अगर (ret)
		जाओ err_clk;

	ret = devm_request_irq(&pdev->dev, irq, sdma_पूर्णांक_handler, 0, "sdma",
			       sdma);
	अगर (ret)
		जाओ err_irq;

	sdma->irq = irq;

	sdma->script_addrs = kzalloc(माप(*sdma->script_addrs), GFP_KERNEL);
	अगर (!sdma->script_addrs) अणु
		ret = -ENOMEM;
		जाओ err_irq;
	पूर्ण

	/* initially no scripts available */
	saddr_arr = (s32 *)sdma->script_addrs;
	क्रम (i = 0; i < माप(*sdma->script_addrs) / माप(s32); i++)
		saddr_arr[i] = -EINVAL;

	dma_cap_set(DMA_SLAVE, sdma->dma_device.cap_mask);
	dma_cap_set(DMA_CYCLIC, sdma->dma_device.cap_mask);
	dma_cap_set(DMA_MEMCPY, sdma->dma_device.cap_mask);

	INIT_LIST_HEAD(&sdma->dma_device.channels);
	/* Initialize channel parameters */
	क्रम (i = 0; i < MAX_DMA_CHANNELS; i++) अणु
		काष्ठा sdma_channel *sdmac = &sdma->channel[i];

		sdmac->sdma = sdma;

		sdmac->channel = i;
		sdmac->vc.desc_मुक्त = sdma_desc_मुक्त;
		INIT_WORK(&sdmac->terminate_worker,
				sdma_channel_terminate_work);
		/*
		 * Add the channel to the DMAC list. Do not add channel 0 though
		 * because we need it पूर्णांकernally in the SDMA driver. This also means
		 * that channel 0 in dmaengine counting matches sdma channel 1.
		 */
		अगर (i)
			vchan_init(&sdmac->vc, &sdma->dma_device);
	पूर्ण

	ret = sdma_init(sdma);
	अगर (ret)
		जाओ err_init;

	ret = sdma_event_remap(sdma);
	अगर (ret)
		जाओ err_init;

	अगर (sdma->drvdata->script_addrs)
		sdma_add_scripts(sdma, sdma->drvdata->script_addrs);

	sdma->dma_device.dev = &pdev->dev;

	sdma->dma_device.device_alloc_chan_resources = sdma_alloc_chan_resources;
	sdma->dma_device.device_मुक्त_chan_resources = sdma_मुक्त_chan_resources;
	sdma->dma_device.device_tx_status = sdma_tx_status;
	sdma->dma_device.device_prep_slave_sg = sdma_prep_slave_sg;
	sdma->dma_device.device_prep_dma_cyclic = sdma_prep_dma_cyclic;
	sdma->dma_device.device_config = sdma_config;
	sdma->dma_device.device_terminate_all = sdma_terminate_all;
	sdma->dma_device.device_synchronize = sdma_channel_synchronize;
	sdma->dma_device.src_addr_widths = SDMA_DMA_BUSWIDTHS;
	sdma->dma_device.dst_addr_widths = SDMA_DMA_BUSWIDTHS;
	sdma->dma_device.directions = SDMA_DMA_सूचीECTIONS;
	sdma->dma_device.residue_granularity = DMA_RESIDUE_GRANULARITY_SEGMENT;
	sdma->dma_device.device_prep_dma_स_नकल = sdma_prep_स_नकल;
	sdma->dma_device.device_issue_pending = sdma_issue_pending;
	sdma->dma_device.copy_align = 2;
	dma_set_max_seg_size(sdma->dma_device.dev, SDMA_BD_MAX_CNT);

	platक्रमm_set_drvdata(pdev, sdma);

	ret = dma_async_device_रेजिस्टर(&sdma->dma_device);
	अगर (ret) अणु
		dev_err(&pdev->dev, "unable to register\n");
		जाओ err_init;
	पूर्ण

	अगर (np) अणु
		ret = of_dma_controller_रेजिस्टर(np, sdma_xlate, sdma);
		अगर (ret) अणु
			dev_err(&pdev->dev, "failed to register controller\n");
			जाओ err_रेजिस्टर;
		पूर्ण

		spba_bus = of_find_compatible_node(शून्य, शून्य, "fsl,spba-bus");
		ret = of_address_to_resource(spba_bus, 0, &spba_res);
		अगर (!ret) अणु
			sdma->spba_start_addr = spba_res.start;
			sdma->spba_end_addr = spba_res.end;
		पूर्ण
		of_node_put(spba_bus);
	पूर्ण

	/*
	 * Because that device tree करोes not encode ROM script address,
	 * the RAM script in firmware is mandatory क्रम device tree
	 * probe, otherwise it fails.
	 */
	ret = of_property_पढ़ो_string(np, "fsl,sdma-ram-script-name",
				      &fw_name);
	अगर (ret) अणु
		dev_warn(&pdev->dev, "failed to get firmware name\n");
	पूर्ण अन्यथा अणु
		ret = sdma_get_firmware(sdma, fw_name);
		अगर (ret)
			dev_warn(&pdev->dev, "failed to get firmware from device tree\n");
	पूर्ण

	वापस 0;

err_रेजिस्टर:
	dma_async_device_unरेजिस्टर(&sdma->dma_device);
err_init:
	kमुक्त(sdma->script_addrs);
err_irq:
	clk_unprepare(sdma->clk_ahb);
err_clk:
	clk_unprepare(sdma->clk_ipg);
	वापस ret;
पूर्ण

अटल पूर्णांक sdma_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sdma_engine *sdma = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	devm_मुक्त_irq(&pdev->dev, sdma->irq, sdma);
	dma_async_device_unरेजिस्टर(&sdma->dma_device);
	kमुक्त(sdma->script_addrs);
	clk_unprepare(sdma->clk_ahb);
	clk_unprepare(sdma->clk_ipg);
	/* Kill the tasklet */
	क्रम (i = 0; i < MAX_DMA_CHANNELS; i++) अणु
		काष्ठा sdma_channel *sdmac = &sdma->channel[i];

		tasklet_समाप्त(&sdmac->vc.task);
		sdma_मुक्त_chan_resources(&sdmac->vc.chan);
	पूर्ण

	platक्रमm_set_drvdata(pdev, शून्य);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sdma_driver = अणु
	.driver		= अणु
		.name	= "imx-sdma",
		.of_match_table = sdma_dt_ids,
	पूर्ण,
	.हटाओ		= sdma_हटाओ,
	.probe		= sdma_probe,
पूर्ण;

module_platक्रमm_driver(sdma_driver);

MODULE_AUTHOR("Sascha Hauer, Pengutronix <s.hauer@pengutronix.de>");
MODULE_DESCRIPTION("i.MX SDMA driver");
#अगर IS_ENABLED(CONFIG_SOC_IMX6Q)
MODULE_FIRMWARE("imx/sdma/sdma-imx6q.bin");
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_SOC_IMX7D)
MODULE_FIRMWARE("imx/sdma/sdma-imx7d.bin");
#पूर्ण_अगर
MODULE_LICENSE("GPL");
