<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * st_spi_fsm.c	- ST Fast Sequence Mode (FSM) Serial Flash Controller
 *
 * Author: Angus Clark <angus.clark@st.com>
 *
 * Copyright (C) 2010-2014 STMicroelectronics Limited
 *
 * JEDEC probe based on drivers/mtd/devices/m25p80.c
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/spi-nor.h>
#समावेश <linux/sched.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/clk.h>

#समावेश "serial_flash_cmds.h"

/*
 * FSM SPI Controller Registers
 */
#घोषणा SPI_CLOCKDIV			0x0010
#घोषणा SPI_MODESELECT			0x0018
#घोषणा SPI_CONFIGDATA			0x0020
#घोषणा SPI_STA_MODE_CHANGE		0x0028
#घोषणा SPI_FAST_SEQ_TRANSFER_SIZE	0x0100
#घोषणा SPI_FAST_SEQ_ADD1		0x0104
#घोषणा SPI_FAST_SEQ_ADD2		0x0108
#घोषणा SPI_FAST_SEQ_ADD_CFG		0x010c
#घोषणा SPI_FAST_SEQ_OPC1		0x0110
#घोषणा SPI_FAST_SEQ_OPC2		0x0114
#घोषणा SPI_FAST_SEQ_OPC3		0x0118
#घोषणा SPI_FAST_SEQ_OPC4		0x011c
#घोषणा SPI_FAST_SEQ_OPC5		0x0120
#घोषणा SPI_MODE_BITS			0x0124
#घोषणा SPI_DUMMY_BITS			0x0128
#घोषणा SPI_FAST_SEQ_FLASH_STA_DATA	0x012c
#घोषणा SPI_FAST_SEQ_1			0x0130
#घोषणा SPI_FAST_SEQ_2			0x0134
#घोषणा SPI_FAST_SEQ_3			0x0138
#घोषणा SPI_FAST_SEQ_4			0x013c
#घोषणा SPI_FAST_SEQ_CFG		0x0140
#घोषणा SPI_FAST_SEQ_STA		0x0144
#घोषणा SPI_QUAD_BOOT_SEQ_INIT_1	0x0148
#घोषणा SPI_QUAD_BOOT_SEQ_INIT_2	0x014c
#घोषणा SPI_QUAD_BOOT_READ_SEQ_1	0x0150
#घोषणा SPI_QUAD_BOOT_READ_SEQ_2	0x0154
#घोषणा SPI_PROGRAM_ERASE_TIME		0x0158
#घोषणा SPI_MULT_PAGE_REPEAT_SEQ_1	0x015c
#घोषणा SPI_MULT_PAGE_REPEAT_SEQ_2	0x0160
#घोषणा SPI_STATUS_WR_TIME_REG		0x0164
#घोषणा SPI_FAST_SEQ_DATA_REG		0x0300

/*
 * Register: SPI_MODESELECT
 */
#घोषणा SPI_MODESELECT_CONTIG		0x01
#घोषणा SPI_MODESELECT_FASTREAD		0x02
#घोषणा SPI_MODESELECT_DUALIO		0x04
#घोषणा SPI_MODESELECT_FSM		0x08
#घोषणा SPI_MODESELECT_QUADBOOT		0x10

/*
 * Register: SPI_CONFIGDATA
 */
#घोषणा SPI_CFG_DEVICE_ST		0x1
#घोषणा SPI_CFG_DEVICE_ATMEL		0x4
#घोषणा SPI_CFG_MIN_CS_HIGH(x)		(((x) & 0xfff) << 4)
#घोषणा SPI_CFG_CS_SETUPHOLD(x)		(((x) & 0xff) << 16)
#घोषणा SPI_CFG_DATA_HOLD(x)		(((x) & 0xff) << 24)

#घोषणा SPI_CFG_DEFAULT_MIN_CS_HIGH    SPI_CFG_MIN_CS_HIGH(0x0AA)
#घोषणा SPI_CFG_DEFAULT_CS_SETUPHOLD   SPI_CFG_CS_SETUPHOLD(0xA0)
#घोषणा SPI_CFG_DEFAULT_DATA_HOLD      SPI_CFG_DATA_HOLD(0x00)

/*
 * Register: SPI_FAST_SEQ_TRANSFER_SIZE
 */
#घोषणा TRANSFER_SIZE(x)		((x) * 8)

/*
 * Register: SPI_FAST_SEQ_ADD_CFG
 */
#घोषणा ADR_CFG_CYCLES_ADD1(x)		((x) << 0)
#घोषणा ADR_CFG_PADS_1_ADD1		(0x0 << 6)
#घोषणा ADR_CFG_PADS_2_ADD1		(0x1 << 6)
#घोषणा ADR_CFG_PADS_4_ADD1		(0x3 << 6)
#घोषणा ADR_CFG_CSDEASSERT_ADD1		(1   << 8)
#घोषणा ADR_CFG_CYCLES_ADD2(x)		((x) << (0+16))
#घोषणा ADR_CFG_PADS_1_ADD2		(0x0 << (6+16))
#घोषणा ADR_CFG_PADS_2_ADD2		(0x1 << (6+16))
#घोषणा ADR_CFG_PADS_4_ADD2		(0x3 << (6+16))
#घोषणा ADR_CFG_CSDEASSERT_ADD2		(1   << (8+16))

/*
 * Register: SPI_FAST_SEQ_n
 */
#घोषणा SEQ_OPC_OPCODE(x)		((x) << 0)
#घोषणा SEQ_OPC_CYCLES(x)		((x) << 8)
#घोषणा SEQ_OPC_PADS_1			(0x0 << 14)
#घोषणा SEQ_OPC_PADS_2			(0x1 << 14)
#घोषणा SEQ_OPC_PADS_4			(0x3 << 14)
#घोषणा SEQ_OPC_CSDEASSERT		(1   << 16)

/*
 * Register: SPI_FAST_SEQ_CFG
 */
#घोषणा SEQ_CFG_STARTSEQ		(1 << 0)
#घोषणा SEQ_CFG_SWRESET			(1 << 5)
#घोषणा SEQ_CFG_CSDEASSERT		(1 << 6)
#घोषणा SEQ_CFG_READNOTWRITE		(1 << 7)
#घोषणा SEQ_CFG_ERASE			(1 << 8)
#घोषणा SEQ_CFG_PADS_1			(0x0 << 16)
#घोषणा SEQ_CFG_PADS_2			(0x1 << 16)
#घोषणा SEQ_CFG_PADS_4			(0x3 << 16)

/*
 * Register: SPI_MODE_BITS
 */
#घोषणा MODE_DATA(x)			(x & 0xff)
#घोषणा MODE_CYCLES(x)			((x & 0x3f) << 16)
#घोषणा MODE_PADS_1			(0x0 << 22)
#घोषणा MODE_PADS_2			(0x1 << 22)
#घोषणा MODE_PADS_4			(0x3 << 22)
#घोषणा DUMMY_CSDEASSERT		(1   << 24)

/*
 * Register: SPI_DUMMY_BITS
 */
#घोषणा DUMMY_CYCLES(x)			((x & 0x3f) << 16)
#घोषणा DUMMY_PADS_1			(0x0 << 22)
#घोषणा DUMMY_PADS_2			(0x1 << 22)
#घोषणा DUMMY_PADS_4			(0x3 << 22)
#घोषणा DUMMY_CSDEASSERT		(1   << 24)

/*
 * Register: SPI_FAST_SEQ_FLASH_STA_DATA
 */
#घोषणा STA_DATA_BYTE1(x)		((x & 0xff) << 0)
#घोषणा STA_DATA_BYTE2(x)		((x & 0xff) << 8)
#घोषणा STA_PADS_1			(0x0 << 16)
#घोषणा STA_PADS_2			(0x1 << 16)
#घोषणा STA_PADS_4			(0x3 << 16)
#घोषणा STA_CSDEASSERT			(0x1 << 20)
#घोषणा STA_RDNOTWR			(0x1 << 21)

/*
 * FSM SPI Inकाष्ठाion Opcodes
 */
#घोषणा STFSM_OPC_CMD			0x1
#घोषणा STFSM_OPC_ADD			0x2
#घोषणा STFSM_OPC_STA			0x3
#घोषणा STFSM_OPC_MODE			0x4
#घोषणा STFSM_OPC_DUMMY		0x5
#घोषणा STFSM_OPC_DATA			0x6
#घोषणा STFSM_OPC_WAIT			0x7
#घोषणा STFSM_OPC_JUMP			0x8
#घोषणा STFSM_OPC_GOTO			0x9
#घोषणा STFSM_OPC_STOP			0xF

/*
 * FSM SPI Inकाष्ठाions (== opcode + opeअक्रम).
 */
#घोषणा STFSM_INSTR(cmd, op)		((cmd) | ((op) << 4))

#घोषणा STFSM_INST_CMD1			STFSM_INSTR(STFSM_OPC_CMD,	1)
#घोषणा STFSM_INST_CMD2			STFSM_INSTR(STFSM_OPC_CMD,	2)
#घोषणा STFSM_INST_CMD3			STFSM_INSTR(STFSM_OPC_CMD,	3)
#घोषणा STFSM_INST_CMD4			STFSM_INSTR(STFSM_OPC_CMD,	4)
#घोषणा STFSM_INST_CMD5			STFSM_INSTR(STFSM_OPC_CMD,	5)
#घोषणा STFSM_INST_ADD1			STFSM_INSTR(STFSM_OPC_ADD,	1)
#घोषणा STFSM_INST_ADD2			STFSM_INSTR(STFSM_OPC_ADD,	2)

#घोषणा STFSM_INST_DATA_WRITE		STFSM_INSTR(STFSM_OPC_DATA,	1)
#घोषणा STFSM_INST_DATA_READ		STFSM_INSTR(STFSM_OPC_DATA,	2)

#घोषणा STFSM_INST_STA_RD1		STFSM_INSTR(STFSM_OPC_STA,	0x1)
#घोषणा STFSM_INST_STA_WR1		STFSM_INSTR(STFSM_OPC_STA,	0x1)
#घोषणा STFSM_INST_STA_RD2		STFSM_INSTR(STFSM_OPC_STA,	0x2)
#घोषणा STFSM_INST_STA_WR1_2		STFSM_INSTR(STFSM_OPC_STA,	0x3)

#घोषणा STFSM_INST_MODE			STFSM_INSTR(STFSM_OPC_MODE,	0)
#घोषणा STFSM_INST_DUMMY		STFSM_INSTR(STFSM_OPC_DUMMY,	0)
#घोषणा STFSM_INST_WAIT			STFSM_INSTR(STFSM_OPC_WAIT,	0)
#घोषणा STFSM_INST_STOP			STFSM_INSTR(STFSM_OPC_STOP,	0)

#घोषणा STFSM_DEFAULT_EMI_FREQ 100000000UL                        /* 100 MHz */
#घोषणा STFSM_DEFAULT_WR_TIME  (STFSM_DEFAULT_EMI_FREQ * (15/1000)) /* 15ms */

#घोषणा STFSM_FLASH_SAFE_FREQ  10000000UL                         /* 10 MHz */

#घोषणा STFSM_MAX_WAIT_SEQ_MS  1000     /* FSM execution समय */

/* S25FLxxxS commands */
#घोषणा S25FL_CMD_WRITE4_1_1_4 0x34
#घोषणा S25FL_CMD_SE4          0xdc
#घोषणा S25FL_CMD_CLSR         0x30
#घोषणा S25FL_CMD_DYBWR                0xe1
#घोषणा S25FL_CMD_DYBRD                0xe0
#घोषणा S25FL_CMD_WRITE4       0x12    /* Note, opcode clashes with
					* 'SPINOR_OP_WRITE_1_4_4'
					* as found on N25Qxxx devices! */

/* Status रेजिस्टर */
#घोषणा FLASH_STATUS_BUSY      0x01
#घोषणा FLASH_STATUS_WEL       0x02
#घोषणा FLASH_STATUS_BP0       0x04
#घोषणा FLASH_STATUS_BP1       0x08
#घोषणा FLASH_STATUS_BP2       0x10
#घोषणा FLASH_STATUS_SRWP0     0x80
#घोषणा FLASH_STATUS_TIMEOUT   0xff
/* S25FL Error Flags */
#घोषणा S25FL_STATUS_E_ERR     0x20
#घोषणा S25FL_STATUS_P_ERR     0x40

#घोषणा N25Q_CMD_WRVCR         0x81
#घोषणा N25Q_CMD_RDVCR         0x85
#घोषणा N25Q_CMD_RDVECR        0x65
#घोषणा N25Q_CMD_RDNVCR        0xb5
#घोषणा N25Q_CMD_WRNVCR        0xb1

#घोषणा FLASH_PAGESIZE         256			/* In Bytes    */
#घोषणा FLASH_PAGESIZE_32      (FLASH_PAGESIZE / 4)	/* In uपूर्णांक32_t */
#घोषणा FLASH_MAX_BUSY_WAIT    (300 * HZ)	/* Maximum 'CHIPERASE' समय */

/*
 * Flags to tweak operation of शेष पढ़ो/ग_लिखो/erase routines
 */
#घोषणा CFG_READ_TOGGLE_32BIT_ADDR     0x00000001
#घोषणा CFG_WRITE_TOGGLE_32BIT_ADDR    0x00000002
#घोषणा CFG_ERASESEC_TOGGLE_32BIT_ADDR 0x00000008
#घोषणा CFG_S25FL_CHECK_ERROR_FLAGS    0x00000010

काष्ठा stfsm_seq अणु
	uपूर्णांक32_t data_size;
	uपूर्णांक32_t addr1;
	uपूर्णांक32_t addr2;
	uपूर्णांक32_t addr_cfg;
	uपूर्णांक32_t seq_opc[5];
	uपूर्णांक32_t mode;
	uपूर्णांक32_t dummy;
	uपूर्णांक32_t status;
	uपूर्णांक8_t  seq[16];
	uपूर्णांक32_t seq_cfg;
पूर्ण __packed __aligned(4);

काष्ठा stfsm अणु
	काष्ठा device		*dev;
	व्योम __iomem		*base;
	काष्ठा mtd_info		mtd;
	काष्ठा mutex		lock;
	काष्ठा flash_info       *info;
	काष्ठा clk              *clk;

	uपूर्णांक32_t                configuration;
	uपूर्णांक32_t                fअगरo_dir_delay;
	bool                    booted_from_spi;
	bool                    reset_संकेत;
	bool                    reset_por;

	काष्ठा stfsm_seq stfsm_seq_पढ़ो;
	काष्ठा stfsm_seq stfsm_seq_ग_लिखो;
	काष्ठा stfsm_seq stfsm_seq_en_32bit_addr;
पूर्ण;

/* Parameters to configure a READ or WRITE FSM sequence */
काष्ठा seq_rw_config अणु
	uपूर्णांक32_t        flags;          /* flags to support config */
	uपूर्णांक8_t         cmd;            /* FLASH command */
	पूर्णांक             ग_लिखो;          /* Write Sequence */
	uपूर्णांक8_t         addr_pads;      /* No. of addr pads (MODE & DUMMY) */
	uपूर्णांक8_t         data_pads;      /* No. of data pads */
	uपूर्णांक8_t         mode_data;      /* MODE data */
	uपूर्णांक8_t         mode_cycles;    /* No. of MODE cycles */
	uपूर्णांक8_t         dummy_cycles;   /* No. of DUMMY cycles */
पूर्ण;

/* SPI Flash Device Table */
काष्ठा flash_info अणु
	अक्षर            *name;
	/*
	 * JEDEC id zero means "no ID" (most older chips); otherwise it has
	 * a high byte of zero plus three data bytes: the manufacturer id,
	 * then a two byte device id.
	 */
	u32             jedec_id;
	u16             ext_id;
	/*
	 * The size listed here is what works with SPINOR_OP_SE, which isn't
	 * necessarily called a "sector" by the venकरोr.
	 */
	अचिन्हित        sector_size;
	u16             n_sectors;
	u32             flags;
	/*
	 * Note, where FAST_READ is supported, freq_max specअगरies the
	 * FAST_READ frequency, not the READ frequency.
	 */
	u32             max_freq;
	पूर्णांक             (*config)(काष्ठा stfsm *);
पूर्ण;

अटल पूर्णांक stfsm_n25q_config(काष्ठा stfsm *fsm);
अटल पूर्णांक stfsm_mx25_config(काष्ठा stfsm *fsm);
अटल पूर्णांक stfsm_s25fl_config(काष्ठा stfsm *fsm);
अटल पूर्णांक stfsm_w25q_config(काष्ठा stfsm *fsm);

अटल काष्ठा flash_info flash_types[] = अणु
	/*
	 * ST Microelectronics/Numonyx --
	 * (newer production versions may have feature updates
	 * (eg faster operating frequency)
	 */
#घोषणा M25P_FLAG (FLASH_FLAG_READ_WRITE | FLASH_FLAG_READ_FAST)
	अणु "m25p40",  0x202013, 0,  64 * 1024,   8, M25P_FLAG, 25, शून्य पूर्ण,
	अणु "m25p80",  0x202014, 0,  64 * 1024,  16, M25P_FLAG, 25, शून्य पूर्ण,
	अणु "m25p16",  0x202015, 0,  64 * 1024,  32, M25P_FLAG, 25, शून्य पूर्ण,
	अणु "m25p32",  0x202016, 0,  64 * 1024,  64, M25P_FLAG, 50, शून्य पूर्ण,
	अणु "m25p64",  0x202017, 0,  64 * 1024, 128, M25P_FLAG, 50, शून्य पूर्ण,
	अणु "m25p128", 0x202018, 0, 256 * 1024,  64, M25P_FLAG, 50, शून्य पूर्ण,

#घोषणा M25PX_FLAG (FLASH_FLAG_READ_WRITE      |	\
		    FLASH_FLAG_READ_FAST        |	\
		    FLASH_FLAG_READ_1_1_2       |	\
		    FLASH_FLAG_WRITE_1_1_2)
	अणु "m25px32", 0x207116, 0,  64 * 1024,  64, M25PX_FLAG, 75, शून्य पूर्ण,
	अणु "m25px64", 0x207117, 0,  64 * 1024, 128, M25PX_FLAG, 75, शून्य पूर्ण,

	/* Macronix MX25xxx
	 *     - Support क्रम 'FLASH_FLAG_WRITE_1_4_4' is omitted क्रम devices
	 *       where operating frequency must be reduced.
	 */
#घोषणा MX25_FLAG (FLASH_FLAG_READ_WRITE       |	\
		   FLASH_FLAG_READ_FAST         |	\
		   FLASH_FLAG_READ_1_1_2        |	\
		   FLASH_FLAG_READ_1_2_2        |	\
		   FLASH_FLAG_READ_1_1_4        |	\
		   FLASH_FLAG_SE_4K             |	\
		   FLASH_FLAG_SE_32K)
	अणु "mx25l3255e",  0xc29e16, 0, 64 * 1024, 64,
	  (MX25_FLAG | FLASH_FLAG_WRITE_1_4_4), 86,
	  stfsm_mx25_configपूर्ण,
	अणु "mx25l25635e", 0xc22019, 0, 64*1024, 512,
	  (MX25_FLAG | FLASH_FLAG_32BIT_ADDR | FLASH_FLAG_RESET), 70,
	  stfsm_mx25_config पूर्ण,
	अणु "mx25l25655e", 0xc22619, 0, 64*1024, 512,
	  (MX25_FLAG | FLASH_FLAG_32BIT_ADDR | FLASH_FLAG_RESET), 70,
	  stfsm_mx25_configपूर्ण,

#घोषणा N25Q_FLAG (FLASH_FLAG_READ_WRITE       |	\
		   FLASH_FLAG_READ_FAST         |	\
		   FLASH_FLAG_READ_1_1_2        |	\
		   FLASH_FLAG_READ_1_2_2        |	\
		   FLASH_FLAG_READ_1_1_4        |	\
		   FLASH_FLAG_READ_1_4_4        |	\
		   FLASH_FLAG_WRITE_1_1_2       |	\
		   FLASH_FLAG_WRITE_1_2_2       |	\
		   FLASH_FLAG_WRITE_1_1_4       |	\
		   FLASH_FLAG_WRITE_1_4_4)
	अणु "n25q128", 0x20ba18, 0, 64 * 1024,  256, N25Q_FLAG, 108,
	  stfsm_n25q_config पूर्ण,
	अणु "n25q256", 0x20ba19, 0, 64 * 1024,  512,
	  N25Q_FLAG | FLASH_FLAG_32BIT_ADDR, 108, stfsm_n25q_config पूर्ण,

	/*
	 * Spansion S25FLxxxP
	 *     - 256KiB and 64KiB sector variants (identअगरied by ext. JEDEC)
	 */
#घोषणा S25FLXXXP_FLAG (FLASH_FLAG_READ_WRITE  |	\
			FLASH_FLAG_READ_1_1_2   |	\
			FLASH_FLAG_READ_1_2_2   |	\
			FLASH_FLAG_READ_1_1_4   |	\
			FLASH_FLAG_READ_1_4_4   |	\
			FLASH_FLAG_WRITE_1_1_4  |	\
			FLASH_FLAG_READ_FAST)
	अणु "s25fl032p",  0x010215, 0x4d00,  64 * 1024,  64, S25FLXXXP_FLAG, 80,
	  stfsm_s25fl_configपूर्ण,
	अणु "s25fl129p0", 0x012018, 0x4d00, 256 * 1024,  64, S25FLXXXP_FLAG, 80,
	  stfsm_s25fl_config पूर्ण,
	अणु "s25fl129p1", 0x012018, 0x4d01,  64 * 1024, 256, S25FLXXXP_FLAG, 80,
	  stfsm_s25fl_config पूर्ण,

	/*
	 * Spansion S25FLxxxS
	 *     - 256KiB and 64KiB sector variants (identअगरied by ext. JEDEC)
	 *     - RESET# संकेत supported by die but not bristled out on all
	 *       package types.  The package type is a function of board design,
	 *       so this inक्रमmation is captured in the board's flags.
	 *     - Supports 'DYB' sector protection. Depending on variant, sectors
	 *       may शेष to locked state on घातer-on.
	 */
#घोषणा S25FLXXXS_FLAG (S25FLXXXP_FLAG         |	\
			FLASH_FLAG_RESET        |	\
			FLASH_FLAG_DYB_LOCKING)
	अणु "s25fl128s0", 0x012018, 0x0300,  256 * 1024, 64, S25FLXXXS_FLAG, 80,
	  stfsm_s25fl_config पूर्ण,
	अणु "s25fl128s1", 0x012018, 0x0301,  64 * 1024, 256, S25FLXXXS_FLAG, 80,
	  stfsm_s25fl_config पूर्ण,
	अणु "s25fl256s0", 0x010219, 0x4d00, 256 * 1024, 128,
	  S25FLXXXS_FLAG | FLASH_FLAG_32BIT_ADDR, 80, stfsm_s25fl_config पूर्ण,
	अणु "s25fl256s1", 0x010219, 0x4d01,  64 * 1024, 512,
	  S25FLXXXS_FLAG | FLASH_FLAG_32BIT_ADDR, 80, stfsm_s25fl_config पूर्ण,

	/* Winbond -- w25x "blocks" are 64K, "sectors" are 4KiB */
#घोषणा W25X_FLAG (FLASH_FLAG_READ_WRITE       |	\
		   FLASH_FLAG_READ_FAST         |	\
		   FLASH_FLAG_READ_1_1_2        |	\
		   FLASH_FLAG_WRITE_1_1_2)
	अणु "w25x40",  0xef3013, 0,  64 * 1024,   8, W25X_FLAG, 75, शून्य पूर्ण,
	अणु "w25x80",  0xef3014, 0,  64 * 1024,  16, W25X_FLAG, 75, शून्य पूर्ण,
	अणु "w25x16",  0xef3015, 0,  64 * 1024,  32, W25X_FLAG, 75, शून्य पूर्ण,
	अणु "w25x32",  0xef3016, 0,  64 * 1024,  64, W25X_FLAG, 75, शून्य पूर्ण,
	अणु "w25x64",  0xef3017, 0,  64 * 1024, 128, W25X_FLAG, 75, शून्य पूर्ण,

	/* Winbond -- w25q "blocks" are 64K, "sectors" are 4KiB */
#घोषणा W25Q_FLAG (FLASH_FLAG_READ_WRITE       |	\
		   FLASH_FLAG_READ_FAST         |	\
		   FLASH_FLAG_READ_1_1_2        |	\
		   FLASH_FLAG_READ_1_2_2        |	\
		   FLASH_FLAG_READ_1_1_4        |	\
		   FLASH_FLAG_READ_1_4_4        |	\
		   FLASH_FLAG_WRITE_1_1_4)
	अणु "w25q80",  0xef4014, 0,  64 * 1024,  16, W25Q_FLAG, 80,
	  stfsm_w25q_config पूर्ण,
	अणु "w25q16",  0xef4015, 0,  64 * 1024,  32, W25Q_FLAG, 80,
	  stfsm_w25q_config पूर्ण,
	अणु "w25q32",  0xef4016, 0,  64 * 1024,  64, W25Q_FLAG, 80,
	  stfsm_w25q_config पूर्ण,
	अणु "w25q64",  0xef4017, 0,  64 * 1024, 128, W25Q_FLAG, 80,
	  stfsm_w25q_config पूर्ण,

	/* Sentinel */
	अणु शून्य, 0x000000, 0, 0, 0, 0, 0, शून्य पूर्ण,
पूर्ण;

/*
 * FSM message sequence configurations:
 *
 * All configs are presented in order of preference
 */

/* Default READ configurations, in order of preference */
अटल काष्ठा seq_rw_config शेष_पढ़ो_configs[] = अणु
	अणुFLASH_FLAG_READ_1_4_4, SPINOR_OP_READ_1_4_4,	0, 4, 4, 0x00, 2, 4पूर्ण,
	अणुFLASH_FLAG_READ_1_1_4, SPINOR_OP_READ_1_1_4,	0, 1, 4, 0x00, 4, 0पूर्ण,
	अणुFLASH_FLAG_READ_1_2_2, SPINOR_OP_READ_1_2_2,	0, 2, 2, 0x00, 4, 0पूर्ण,
	अणुFLASH_FLAG_READ_1_1_2, SPINOR_OP_READ_1_1_2,	0, 1, 2, 0x00, 0, 8पूर्ण,
	अणुFLASH_FLAG_READ_FAST,	SPINOR_OP_READ_FAST,	0, 1, 1, 0x00, 0, 8पूर्ण,
	अणुFLASH_FLAG_READ_WRITE, SPINOR_OP_READ,		0, 1, 1, 0x00, 0, 0पूर्ण,
	अणु0x00,			0,			0, 0, 0, 0x00, 0, 0पूर्ण,
पूर्ण;

/* Default WRITE configurations */
अटल काष्ठा seq_rw_config शेष_ग_लिखो_configs[] = अणु
	अणुFLASH_FLAG_WRITE_1_4_4, SPINOR_OP_WRITE_1_4_4, 1, 4, 4, 0x00, 0, 0पूर्ण,
	अणुFLASH_FLAG_WRITE_1_1_4, SPINOR_OP_WRITE_1_1_4, 1, 1, 4, 0x00, 0, 0पूर्ण,
	अणुFLASH_FLAG_WRITE_1_2_2, SPINOR_OP_WRITE_1_2_2, 1, 2, 2, 0x00, 0, 0पूर्ण,
	अणुFLASH_FLAG_WRITE_1_1_2, SPINOR_OP_WRITE_1_1_2, 1, 1, 2, 0x00, 0, 0पूर्ण,
	अणुFLASH_FLAG_READ_WRITE,  SPINOR_OP_WRITE,       1, 1, 1, 0x00, 0, 0पूर्ण,
	अणु0x00,			 0,			0, 0, 0, 0x00, 0, 0पूर्ण,
पूर्ण;

/*
 * [N25Qxxx] Configuration
 */
#घोषणा N25Q_VCR_DUMMY_CYCLES(x)	(((x) & 0xf) << 4)
#घोषणा N25Q_VCR_XIP_DISABLED		((uपूर्णांक8_t)0x1 << 3)
#घोषणा N25Q_VCR_WRAP_CONT		0x3

/* N25Q 3-byte Address READ configurations
 *	- 'FAST' variants configured क्रम 8 dummy cycles.
 *
 * Note, the number of dummy cycles used क्रम 'FAST' READ operations is
 * configurable and would normally be tuned according to the READ command and
 * operating frequency.  However, this applies universally to all 'FAST' READ
 * commands, including those used by the SPIBoot controller, and reमुख्यs in
 * क्रमce until the device is घातer-cycled.  Since the SPIBoot controller is
 * hard-wired to use 8 dummy cycles, we must configure the device to also use 8
 * cycles.
 */
अटल काष्ठा seq_rw_config n25q_पढ़ो3_configs[] = अणु
	अणुFLASH_FLAG_READ_1_4_4, SPINOR_OP_READ_1_4_4,	0, 4, 4, 0x00, 0, 8पूर्ण,
	अणुFLASH_FLAG_READ_1_1_4, SPINOR_OP_READ_1_1_4,	0, 1, 4, 0x00, 0, 8पूर्ण,
	अणुFLASH_FLAG_READ_1_2_2, SPINOR_OP_READ_1_2_2,	0, 2, 2, 0x00, 0, 8पूर्ण,
	अणुFLASH_FLAG_READ_1_1_2, SPINOR_OP_READ_1_1_2,	0, 1, 2, 0x00, 0, 8पूर्ण,
	अणुFLASH_FLAG_READ_FAST,	SPINOR_OP_READ_FAST,	0, 1, 1, 0x00, 0, 8पूर्ण,
	अणुFLASH_FLAG_READ_WRITE, SPINOR_OP_READ,	        0, 1, 1, 0x00, 0, 0पूर्ण,
	अणु0x00,			0,			0, 0, 0, 0x00, 0, 0पूर्ण,
पूर्ण;

/* N25Q 4-byte Address READ configurations
 *	- use special 4-byte address READ commands (reduces overheads, and
 *        reduces risk of hitting watchकरोg reset issues).
 *	- 'FAST' variants configured क्रम 8 dummy cycles (see note above.)
 */
अटल काष्ठा seq_rw_config n25q_पढ़ो4_configs[] = अणु
	अणुFLASH_FLAG_READ_1_4_4, SPINOR_OP_READ_1_4_4_4B, 0, 4, 4, 0x00, 0, 8पूर्ण,
	अणुFLASH_FLAG_READ_1_1_4, SPINOR_OP_READ_1_1_4_4B, 0, 1, 4, 0x00, 0, 8पूर्ण,
	अणुFLASH_FLAG_READ_1_2_2, SPINOR_OP_READ_1_2_2_4B, 0, 2, 2, 0x00, 0, 8पूर्ण,
	अणुFLASH_FLAG_READ_1_1_2, SPINOR_OP_READ_1_1_2_4B, 0, 1, 2, 0x00, 0, 8पूर्ण,
	अणुFLASH_FLAG_READ_FAST,	SPINOR_OP_READ_FAST_4B,  0, 1, 1, 0x00, 0, 8पूर्ण,
	अणुFLASH_FLAG_READ_WRITE, SPINOR_OP_READ_4B,       0, 1, 1, 0x00, 0, 0पूर्ण,
	अणु0x00,			0,                       0, 0, 0, 0x00, 0, 0पूर्ण,
पूर्ण;

/*
 * [MX25xxx] Configuration
 */
#घोषणा MX25_STATUS_QE			(0x1 << 6)

अटल पूर्णांक stfsm_mx25_en_32bit_addr_seq(काष्ठा stfsm_seq *seq)
अणु
	seq->seq_opc[0] = (SEQ_OPC_PADS_1 |
			   SEQ_OPC_CYCLES(8) |
			   SEQ_OPC_OPCODE(SPINOR_OP_EN4B) |
			   SEQ_OPC_CSDEASSERT);

	seq->seq[0] = STFSM_INST_CMD1;
	seq->seq[1] = STFSM_INST_WAIT;
	seq->seq[2] = STFSM_INST_STOP;

	seq->seq_cfg = (SEQ_CFG_PADS_1 |
			SEQ_CFG_ERASE |
			SEQ_CFG_READNOTWRITE |
			SEQ_CFG_CSDEASSERT |
			SEQ_CFG_STARTSEQ);

	वापस 0;
पूर्ण

/*
 * [S25FLxxx] Configuration
 */
#घोषणा STFSM_S25FL_CONFIG_QE		(0x1 << 1)

/*
 * S25FLxxxS devices provide three ways of supporting 32-bit addressing: Bank
 * Register, Extended Address Modes, and a 32-bit address command set.  The
 * 32-bit address command set is used here, since it aव्योमs any problems with
 * entering a state that is incompatible with the SPIBoot Controller.
 */
अटल काष्ठा seq_rw_config stfsm_s25fl_पढ़ो4_configs[] = अणु
	अणुFLASH_FLAG_READ_1_4_4,  SPINOR_OP_READ_1_4_4_4B,  0, 4, 4, 0x00, 2, 4पूर्ण,
	अणुFLASH_FLAG_READ_1_1_4,  SPINOR_OP_READ_1_1_4_4B,  0, 1, 4, 0x00, 0, 8पूर्ण,
	अणुFLASH_FLAG_READ_1_2_2,  SPINOR_OP_READ_1_2_2_4B,  0, 2, 2, 0x00, 4, 0पूर्ण,
	अणुFLASH_FLAG_READ_1_1_2,  SPINOR_OP_READ_1_1_2_4B,  0, 1, 2, 0x00, 0, 8पूर्ण,
	अणुFLASH_FLAG_READ_FAST,   SPINOR_OP_READ_FAST_4B,   0, 1, 1, 0x00, 0, 8पूर्ण,
	अणुFLASH_FLAG_READ_WRITE,  SPINOR_OP_READ_4B,        0, 1, 1, 0x00, 0, 0पूर्ण,
	अणु0x00,                   0,                        0, 0, 0, 0x00, 0, 0पूर्ण,
पूर्ण;

अटल काष्ठा seq_rw_config stfsm_s25fl_ग_लिखो4_configs[] = अणु
	अणुFLASH_FLAG_WRITE_1_1_4, S25FL_CMD_WRITE4_1_1_4, 1, 1, 4, 0x00, 0, 0पूर्ण,
	अणुFLASH_FLAG_READ_WRITE,  S25FL_CMD_WRITE4,       1, 1, 1, 0x00, 0, 0पूर्ण,
	अणु0x00,                   0,                      0, 0, 0, 0x00, 0, 0पूर्ण,
पूर्ण;

/*
 * [W25Qxxx] Configuration
 */
#घोषणा W25Q_STATUS_QE			(0x1 << 1)

अटल काष्ठा stfsm_seq stfsm_seq_पढ़ो_jedec = अणु
	.data_size = TRANSFER_SIZE(8),
	.seq_opc[0] = (SEQ_OPC_PADS_1 |
		       SEQ_OPC_CYCLES(8) |
		       SEQ_OPC_OPCODE(SPINOR_OP_RDID)),
	.seq = अणु
		STFSM_INST_CMD1,
		STFSM_INST_DATA_READ,
		STFSM_INST_STOP,
	पूर्ण,
	.seq_cfg = (SEQ_CFG_PADS_1 |
		    SEQ_CFG_READNOTWRITE |
		    SEQ_CFG_CSDEASSERT |
		    SEQ_CFG_STARTSEQ),
पूर्ण;

अटल काष्ठा stfsm_seq stfsm_seq_पढ़ो_status_fअगरo = अणु
	.data_size = TRANSFER_SIZE(4),
	.seq_opc[0] = (SEQ_OPC_PADS_1 |
		       SEQ_OPC_CYCLES(8) |
		       SEQ_OPC_OPCODE(SPINOR_OP_RDSR)),
	.seq = अणु
		STFSM_INST_CMD1,
		STFSM_INST_DATA_READ,
		STFSM_INST_STOP,
	पूर्ण,
	.seq_cfg = (SEQ_CFG_PADS_1 |
		    SEQ_CFG_READNOTWRITE |
		    SEQ_CFG_CSDEASSERT |
		    SEQ_CFG_STARTSEQ),
पूर्ण;

अटल काष्ठा stfsm_seq stfsm_seq_erase_sector = अणु
	/* 'addr_cfg' configured during initialisation */
	.seq_opc = अणु
		(SEQ_OPC_PADS_1 | SEQ_OPC_CYCLES(8) |
		 SEQ_OPC_OPCODE(SPINOR_OP_WREN) | SEQ_OPC_CSDEASSERT),

		(SEQ_OPC_PADS_1 | SEQ_OPC_CYCLES(8) |
		 SEQ_OPC_OPCODE(SPINOR_OP_SE)),
	पूर्ण,
	.seq = अणु
		STFSM_INST_CMD1,
		STFSM_INST_CMD2,
		STFSM_INST_ADD1,
		STFSM_INST_ADD2,
		STFSM_INST_STOP,
	पूर्ण,
	.seq_cfg = (SEQ_CFG_PADS_1 |
		    SEQ_CFG_READNOTWRITE |
		    SEQ_CFG_CSDEASSERT |
		    SEQ_CFG_STARTSEQ),
पूर्ण;

अटल काष्ठा stfsm_seq stfsm_seq_erase_chip = अणु
	.seq_opc = अणु
		(SEQ_OPC_PADS_1 | SEQ_OPC_CYCLES(8) |
		 SEQ_OPC_OPCODE(SPINOR_OP_WREN) | SEQ_OPC_CSDEASSERT),

		(SEQ_OPC_PADS_1 | SEQ_OPC_CYCLES(8) |
		 SEQ_OPC_OPCODE(SPINOR_OP_CHIP_ERASE) | SEQ_OPC_CSDEASSERT),
	पूर्ण,
	.seq = अणु
		STFSM_INST_CMD1,
		STFSM_INST_CMD2,
		STFSM_INST_WAIT,
		STFSM_INST_STOP,
	पूर्ण,
	.seq_cfg = (SEQ_CFG_PADS_1 |
		    SEQ_CFG_ERASE |
		    SEQ_CFG_READNOTWRITE |
		    SEQ_CFG_CSDEASSERT |
		    SEQ_CFG_STARTSEQ),
पूर्ण;

अटल काष्ठा stfsm_seq stfsm_seq_ग_लिखो_status = अणु
	.seq_opc[0] = (SEQ_OPC_PADS_1 | SEQ_OPC_CYCLES(8) |
		       SEQ_OPC_OPCODE(SPINOR_OP_WREN) | SEQ_OPC_CSDEASSERT),
	.seq_opc[1] = (SEQ_OPC_PADS_1 | SEQ_OPC_CYCLES(8) |
		       SEQ_OPC_OPCODE(SPINOR_OP_WRSR)),
	.seq = अणु
		STFSM_INST_CMD1,
		STFSM_INST_CMD2,
		STFSM_INST_STA_WR1,
		STFSM_INST_STOP,
	पूर्ण,
	.seq_cfg = (SEQ_CFG_PADS_1 |
		    SEQ_CFG_READNOTWRITE |
		    SEQ_CFG_CSDEASSERT |
		    SEQ_CFG_STARTSEQ),
पूर्ण;

/* Dummy sequence to पढ़ो one byte of data from flash पूर्णांकo the FIFO */
अटल स्थिर काष्ठा stfsm_seq stfsm_seq_load_fअगरo_byte = अणु
	.data_size = TRANSFER_SIZE(1),
	.seq_opc[0] = (SEQ_OPC_PADS_1 |
		       SEQ_OPC_CYCLES(8) |
		       SEQ_OPC_OPCODE(SPINOR_OP_RDID)),
	.seq = अणु
		STFSM_INST_CMD1,
		STFSM_INST_DATA_READ,
		STFSM_INST_STOP,
	पूर्ण,
	.seq_cfg = (SEQ_CFG_PADS_1 |
		    SEQ_CFG_READNOTWRITE |
		    SEQ_CFG_CSDEASSERT |
		    SEQ_CFG_STARTSEQ),
पूर्ण;

अटल पूर्णांक stfsm_n25q_en_32bit_addr_seq(काष्ठा stfsm_seq *seq)
अणु
	seq->seq_opc[0] = (SEQ_OPC_PADS_1 | SEQ_OPC_CYCLES(8) |
			   SEQ_OPC_OPCODE(SPINOR_OP_EN4B));
	seq->seq_opc[1] = (SEQ_OPC_PADS_1 | SEQ_OPC_CYCLES(8) |
			   SEQ_OPC_OPCODE(SPINOR_OP_WREN) |
			   SEQ_OPC_CSDEASSERT);

	seq->seq[0] = STFSM_INST_CMD2;
	seq->seq[1] = STFSM_INST_CMD1;
	seq->seq[2] = STFSM_INST_WAIT;
	seq->seq[3] = STFSM_INST_STOP;

	seq->seq_cfg = (SEQ_CFG_PADS_1 |
			SEQ_CFG_ERASE |
			SEQ_CFG_READNOTWRITE |
			SEQ_CFG_CSDEASSERT |
			SEQ_CFG_STARTSEQ);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक stfsm_is_idle(काष्ठा stfsm *fsm)
अणु
	वापस पढ़ोl(fsm->base + SPI_FAST_SEQ_STA) & 0x10;
पूर्ण

अटल अंतरभूत uपूर्णांक32_t stfsm_fअगरo_available(काष्ठा stfsm *fsm)
अणु
	वापस (पढ़ोl(fsm->base + SPI_FAST_SEQ_STA) >> 5) & 0x7f;
पूर्ण

अटल अंतरभूत व्योम stfsm_load_seq(काष्ठा stfsm *fsm,
				  स्थिर काष्ठा stfsm_seq *seq)
अणु
	व्योम __iomem *dst = fsm->base + SPI_FAST_SEQ_TRANSFER_SIZE;
	स्थिर uपूर्णांक32_t *src = (स्थिर uपूर्णांक32_t *)seq;
	पूर्णांक words = माप(*seq) / माप(*src);

	BUG_ON(!stfsm_is_idle(fsm));

	जबतक (words--) अणु
		ग_लिखोl(*src, dst);
		src++;
		dst += 4;
	पूर्ण
पूर्ण

अटल व्योम stfsm_रुको_seq(काष्ठा stfsm *fsm)
अणु
	अचिन्हित दीर्घ deadline;
	पूर्णांक समयout = 0;

	deadline = jअगरfies + msecs_to_jअगरfies(STFSM_MAX_WAIT_SEQ_MS);

	जबतक (!समयout) अणु
		अगर (समय_after_eq(jअगरfies, deadline))
			समयout = 1;

		अगर (stfsm_is_idle(fsm))
			वापस;

		cond_resched();
	पूर्ण

	dev_err(fsm->dev, "timeout on sequence completion\n");
पूर्ण

अटल व्योम stfsm_पढ़ो_fअगरo(काष्ठा stfsm *fsm, uपूर्णांक32_t *buf, uपूर्णांक32_t size)
अणु
	uपूर्णांक32_t reमुख्यing = size >> 2;
	uपूर्णांक32_t avail;
	uपूर्णांक32_t words;

	dev_dbg(fsm->dev, "Reading %d bytes from FIFO\n", size);

	BUG_ON((((uपूर्णांकptr_t)buf) & 0x3) || (size & 0x3));

	जबतक (reमुख्यing) अणु
		क्रम (;;) अणु
			avail = stfsm_fअगरo_available(fsm);
			अगर (avail)
				अवरोध;
			udelay(1);
		पूर्ण
		words = min(avail, reमुख्यing);
		reमुख्यing -= words;

		पढ़ोsl(fsm->base + SPI_FAST_SEQ_DATA_REG, buf, words);
		buf += words;
	पूर्ण
पूर्ण

/*
 * Clear the data FIFO
 *
 * Typically, this is only required during driver initialisation, where no
 * assumptions can be made regarding the state of the FIFO.
 *
 * The process of clearing the FIFO is complicated by fact that जबतक it is
 * possible क्रम the FIFO to contain an arbitrary number of bytes [1], the
 * SPI_FAST_SEQ_STA रेजिस्टर only reports the number of complete 32-bit words
 * present.  Furthermore, data can only be drained from the FIFO by पढ़ोing
 * complete 32-bit words.
 *
 * With this in mind, a two stage process is used to the clear the FIFO:
 *
 *     1. Read any complete 32-bit words from the FIFO, as reported by the
 *        SPI_FAST_SEQ_STA रेजिस्टर.
 *
 *     2. Mop up any reमुख्यing bytes.  At this poपूर्णांक, it is not known अगर there
 *        are 0, 1, 2, or 3 bytes in the FIFO.  To handle all हालs, a dummy FSM
 *        sequence is used to load one byte at a समय, until a complete 32-bit
 *        word is क्रमmed; at most, 4 bytes will need to be loaded.
 *
 * [1] It is theoretically possible क्रम the FIFO to contain an arbitrary number
 *     of bits.  However, since there are no known use-हालs that leave
 *     incomplete bytes in the FIFO, only words and bytes are considered here.
 */
अटल व्योम stfsm_clear_fअगरo(काष्ठा stfsm *fsm)
अणु
	स्थिर काष्ठा stfsm_seq *seq = &stfsm_seq_load_fअगरo_byte;
	uपूर्णांक32_t words, i;

	/* 1. Clear any 32-bit words */
	words = stfsm_fअगरo_available(fsm);
	अगर (words) अणु
		क्रम (i = 0; i < words; i++)
			पढ़ोl(fsm->base + SPI_FAST_SEQ_DATA_REG);
		dev_dbg(fsm->dev, "cleared %d words from FIFO\n", words);
	पूर्ण

	/*
	 * 2. Clear any reमुख्यing bytes
	 *    - Load the FIFO, one byte at a समय, until a complete 32-bit word
	 *      is available.
	 */
	क्रम (i = 0, words = 0; i < 4 && !words; i++) अणु
		stfsm_load_seq(fsm, seq);
		stfsm_रुको_seq(fsm);
		words = stfsm_fअगरo_available(fsm);
	पूर्ण

	/*    - A single word must be available now */
	अगर (words != 1) अणु
		dev_err(fsm->dev, "failed to clear bytes from the data FIFO\n");
		वापस;
	पूर्ण

	/*    - Read the 32-bit word */
	पढ़ोl(fsm->base + SPI_FAST_SEQ_DATA_REG);

	dev_dbg(fsm->dev, "cleared %d byte(s) from the data FIFO\n", 4 - i);
पूर्ण

अटल पूर्णांक stfsm_ग_लिखो_fअगरo(काष्ठा stfsm *fsm, स्थिर uपूर्णांक32_t *buf,
			    uपूर्णांक32_t size)
अणु
	uपूर्णांक32_t words = size >> 2;

	dev_dbg(fsm->dev, "writing %d bytes to FIFO\n", size);

	BUG_ON((((uपूर्णांकptr_t)buf) & 0x3) || (size & 0x3));

	ग_लिखोsl(fsm->base + SPI_FAST_SEQ_DATA_REG, buf, words);

	वापस size;
पूर्ण

अटल पूर्णांक stfsm_enter_32bit_addr(काष्ठा stfsm *fsm, पूर्णांक enter)
अणु
	काष्ठा stfsm_seq *seq = &fsm->stfsm_seq_en_32bit_addr;
	uपूर्णांक32_t cmd = enter ? SPINOR_OP_EN4B : SPINOR_OP_EX4B;

	seq->seq_opc[0] = (SEQ_OPC_PADS_1 |
			   SEQ_OPC_CYCLES(8) |
			   SEQ_OPC_OPCODE(cmd) |
			   SEQ_OPC_CSDEASSERT);

	stfsm_load_seq(fsm, seq);

	stfsm_रुको_seq(fsm);

	वापस 0;
पूर्ण

अटल uपूर्णांक8_t stfsm_रुको_busy(काष्ठा stfsm *fsm)
अणु
	काष्ठा stfsm_seq *seq = &stfsm_seq_पढ़ो_status_fअगरo;
	अचिन्हित दीर्घ deadline;
	uपूर्णांक32_t status;
	पूर्णांक समयout = 0;

	/* Use RDRS1 */
	seq->seq_opc[0] = (SEQ_OPC_PADS_1 |
			   SEQ_OPC_CYCLES(8) |
			   SEQ_OPC_OPCODE(SPINOR_OP_RDSR));

	/* Load पढ़ो_status sequence */
	stfsm_load_seq(fsm, seq);

	/*
	 * Repeat until busy bit is deनिश्चितed, or समयout, or error (S25FLxxxS)
	 */
	deadline = jअगरfies + FLASH_MAX_BUSY_WAIT;
	जबतक (!समयout) अणु
		अगर (समय_after_eq(jअगरfies, deadline))
			समयout = 1;

		stfsm_रुको_seq(fsm);

		stfsm_पढ़ो_fअगरo(fsm, &status, 4);

		अगर ((status & FLASH_STATUS_BUSY) == 0)
			वापस 0;

		अगर ((fsm->configuration & CFG_S25FL_CHECK_ERROR_FLAGS) &&
		    ((status & S25FL_STATUS_P_ERR) ||
		     (status & S25FL_STATUS_E_ERR)))
			वापस (uपूर्णांक8_t)(status & 0xff);

		अगर (!समयout)
			/* Restart */
			ग_लिखोl(seq->seq_cfg, fsm->base + SPI_FAST_SEQ_CFG);

		cond_resched();
	पूर्ण

	dev_err(fsm->dev, "timeout on wait_busy\n");

	वापस FLASH_STATUS_TIMEOUT;
पूर्ण

अटल पूर्णांक stfsm_पढ़ो_status(काष्ठा stfsm *fsm, uपूर्णांक8_t cmd,
			     uपूर्णांक8_t *data, पूर्णांक bytes)
अणु
	काष्ठा stfsm_seq *seq = &stfsm_seq_पढ़ो_status_fअगरo;
	uपूर्णांक32_t पंचांगp;
	uपूर्णांक8_t *t = (uपूर्णांक8_t *)&पंचांगp;
	पूर्णांक i;

	dev_dbg(fsm->dev, "read 'status' register [0x%02x], %d byte(s)\n",
		cmd, bytes);

	BUG_ON(bytes != 1 && bytes != 2);

	seq->seq_opc[0] = (SEQ_OPC_PADS_1 | SEQ_OPC_CYCLES(8) |
			   SEQ_OPC_OPCODE(cmd));

	stfsm_load_seq(fsm, seq);

	stfsm_पढ़ो_fअगरo(fsm, &पंचांगp, 4);

	क्रम (i = 0; i < bytes; i++)
		data[i] = t[i];

	stfsm_रुको_seq(fsm);

	वापस 0;
पूर्ण

अटल पूर्णांक stfsm_ग_लिखो_status(काष्ठा stfsm *fsm, uपूर्णांक8_t cmd,
			    uपूर्णांक16_t data, पूर्णांक bytes, पूर्णांक रुको_busy)
अणु
	काष्ठा stfsm_seq *seq = &stfsm_seq_ग_लिखो_status;

	dev_dbg(fsm->dev,
		"write 'status' register [0x%02x], %d byte(s), 0x%04x\n"
		" %s wait-busy\n", cmd, bytes, data, रुको_busy ? "with" : "no");

	BUG_ON(bytes != 1 && bytes != 2);

	seq->seq_opc[1] = (SEQ_OPC_PADS_1 | SEQ_OPC_CYCLES(8) |
			   SEQ_OPC_OPCODE(cmd));

	seq->status = (uपूर्णांक32_t)data | STA_PADS_1 | STA_CSDEASSERT;
	seq->seq[2] = (bytes == 1) ? STFSM_INST_STA_WR1 : STFSM_INST_STA_WR1_2;

	stfsm_load_seq(fsm, seq);

	stfsm_रुको_seq(fsm);

	अगर (रुको_busy)
		stfsm_रुको_busy(fsm);

	वापस 0;
पूर्ण

/*
 * SoC reset on 'boot-from-spi' प्रणालीs
 *
 * Certain modes of operation cause the Flash device to enter a particular state
 * क्रम a period of समय (e.g. 'Erase Sector', 'Quad Enable', and 'Enter 32-bit
 * Addr' commands).  On boot-from-spi प्रणालीs, it is important to consider what
 * happens अगर a warm reset occurs during this period.  The SPIBoot controller
 * assumes that Flash device is in its शेष reset state, 24-bit address mode,
 * and पढ़ोy to accept commands.  This can be achieved using some क्रमm of
 * on-board logic/controller to क्रमce a device POR in response to a SoC-level
 * reset or by making use of the device reset संकेत अगर available (limited
 * number of devices only).
 *
 * Failure to take such precautions can cause problems following a warm reset.
 * For some operations (e.g. ERASE), there is little that can be करोne.  For
 * other modes of operation (e.g. 32-bit addressing), options are often
 * available that can help minimise the winकरोw in which a reset could cause a
 * problem.
 *
 */
अटल bool stfsm_can_handle_soc_reset(काष्ठा stfsm *fsm)
अणु
	/* Reset संकेत is available on the board and supported by the device */
	अगर (fsm->reset_संकेत && fsm->info->flags & FLASH_FLAG_RESET)
		वापस true;

	/* Board-level logic क्रमces a घातer-on-reset */
	अगर (fsm->reset_por)
		वापस true;

	/* Reset is not properly handled and may result in failure to reboot */
	वापस false;
पूर्ण

/* Configure 'addr_cfg' according to addressing mode */
अटल व्योम stfsm_prepare_erasesec_seq(काष्ठा stfsm *fsm,
				       काष्ठा stfsm_seq *seq)
अणु
	पूर्णांक addr1_cycles = fsm->info->flags & FLASH_FLAG_32BIT_ADDR ? 16 : 8;

	seq->addr_cfg = (ADR_CFG_CYCLES_ADD1(addr1_cycles) |
			 ADR_CFG_PADS_1_ADD1 |
			 ADR_CFG_CYCLES_ADD2(16) |
			 ADR_CFG_PADS_1_ADD2 |
			 ADR_CFG_CSDEASSERT_ADD2);
पूर्ण

/* Search क्रम preferred configuration based on available flags */
अटल काष्ठा seq_rw_config *
stfsm_search_seq_rw_configs(काष्ठा stfsm *fsm,
			    काष्ठा seq_rw_config cfgs[])
अणु
	काष्ठा seq_rw_config *config;
	पूर्णांक flags = fsm->info->flags;

	क्रम (config = cfgs; config->cmd != 0; config++)
		अगर ((config->flags & flags) == config->flags)
			वापस config;

	वापस शून्य;
पूर्ण

/* Prepare a READ/WRITE sequence according to configuration parameters */
अटल व्योम stfsm_prepare_rw_seq(काष्ठा stfsm *fsm,
				 काष्ठा stfsm_seq *seq,
				 काष्ठा seq_rw_config *cfg)
अणु
	पूर्णांक addr1_cycles, addr2_cycles;
	पूर्णांक i = 0;

	स_रखो(seq, 0, माप(*seq));

	/* Add READ/WRITE OPC  */
	seq->seq_opc[i++] = (SEQ_OPC_PADS_1 |
			     SEQ_OPC_CYCLES(8) |
			     SEQ_OPC_OPCODE(cfg->cmd));

	/* Add WREN OPC क्रम a WRITE sequence */
	अगर (cfg->ग_लिखो)
		seq->seq_opc[i++] = (SEQ_OPC_PADS_1 |
				     SEQ_OPC_CYCLES(8) |
				     SEQ_OPC_OPCODE(SPINOR_OP_WREN) |
				     SEQ_OPC_CSDEASSERT);

	/* Address configuration (24 or 32-bit addresses) */
	addr1_cycles  = (fsm->info->flags & FLASH_FLAG_32BIT_ADDR) ? 16 : 8;
	addr1_cycles /= cfg->addr_pads;
	addr2_cycles  = 16 / cfg->addr_pads;
	seq->addr_cfg = ((addr1_cycles & 0x3f) << 0 |	/* ADD1 cycles */
			 (cfg->addr_pads - 1) << 6 |	/* ADD1 pads */
			 (addr2_cycles & 0x3f) << 16 |	/* ADD2 cycles */
			 ((cfg->addr_pads - 1) << 22));	/* ADD2 pads */

	/* Data/Sequence configuration */
	seq->seq_cfg = ((cfg->data_pads - 1) << 16 |
			SEQ_CFG_STARTSEQ |
			SEQ_CFG_CSDEASSERT);
	अगर (!cfg->ग_लिखो)
		seq->seq_cfg |= SEQ_CFG_READNOTWRITE;

	/* Mode configuration (no. of pads taken from addr cfg) */
	seq->mode = ((cfg->mode_data & 0xff) << 0 |	/* data */
		     (cfg->mode_cycles & 0x3f) << 16 |	/* cycles */
		     (cfg->addr_pads - 1) << 22);	/* pads */

	/* Dummy configuration (no. of pads taken from addr cfg) */
	seq->dummy = ((cfg->dummy_cycles & 0x3f) << 16 |	/* cycles */
		      (cfg->addr_pads - 1) << 22);		/* pads */


	/* Inकाष्ठाion sequence */
	i = 0;
	अगर (cfg->ग_लिखो)
		seq->seq[i++] = STFSM_INST_CMD2;

	seq->seq[i++] = STFSM_INST_CMD1;

	seq->seq[i++] = STFSM_INST_ADD1;
	seq->seq[i++] = STFSM_INST_ADD2;

	अगर (cfg->mode_cycles)
		seq->seq[i++] = STFSM_INST_MODE;

	अगर (cfg->dummy_cycles)
		seq->seq[i++] = STFSM_INST_DUMMY;

	seq->seq[i++] =
		cfg->ग_लिखो ? STFSM_INST_DATA_WRITE : STFSM_INST_DATA_READ;
	seq->seq[i++] = STFSM_INST_STOP;
पूर्ण

अटल पूर्णांक stfsm_search_prepare_rw_seq(काष्ठा stfsm *fsm,
				       काष्ठा stfsm_seq *seq,
				       काष्ठा seq_rw_config *cfgs)
अणु
	काष्ठा seq_rw_config *config;

	config = stfsm_search_seq_rw_configs(fsm, cfgs);
	अगर (!config) अणु
		dev_err(fsm->dev, "failed to find suitable config\n");
		वापस -EINVAL;
	पूर्ण

	stfsm_prepare_rw_seq(fsm, seq, config);

	वापस 0;
पूर्ण

/* Prepare a READ/WRITE/ERASE 'default' sequences */
अटल पूर्णांक stfsm_prepare_rwe_seqs_शेष(काष्ठा stfsm *fsm)
अणु
	uपूर्णांक32_t flags = fsm->info->flags;
	पूर्णांक ret;

	/* Configure 'READ' sequence */
	ret = stfsm_search_prepare_rw_seq(fsm, &fsm->stfsm_seq_पढ़ो,
					  शेष_पढ़ो_configs);
	अगर (ret) अणु
		dev_err(fsm->dev,
			"failed to prep READ sequence with flags [0x%08x]\n",
			flags);
		वापस ret;
	पूर्ण

	/* Configure 'WRITE' sequence */
	ret = stfsm_search_prepare_rw_seq(fsm, &fsm->stfsm_seq_ग_लिखो,
					  शेष_ग_लिखो_configs);
	अगर (ret) अणु
		dev_err(fsm->dev,
			"failed to prep WRITE sequence with flags [0x%08x]\n",
			flags);
		वापस ret;
	पूर्ण

	/* Configure 'ERASE_SECTOR' sequence */
	stfsm_prepare_erasesec_seq(fsm, &stfsm_seq_erase_sector);

	वापस 0;
पूर्ण

अटल पूर्णांक stfsm_mx25_config(काष्ठा stfsm *fsm)
अणु
	uपूर्णांक32_t flags = fsm->info->flags;
	uपूर्णांक32_t data_pads;
	uपूर्णांक8_t sta;
	पूर्णांक ret;
	bool soc_reset;

	/*
	 * Use शेष READ/WRITE sequences
	 */
	ret = stfsm_prepare_rwe_seqs_शेष(fsm);
	अगर (ret)
		वापस ret;

	/*
	 * Configure 32-bit Address Support
	 */
	अगर (flags & FLASH_FLAG_32BIT_ADDR) अणु
		/* Configure 'enter_32bitaddr' FSM sequence */
		stfsm_mx25_en_32bit_addr_seq(&fsm->stfsm_seq_en_32bit_addr);

		soc_reset = stfsm_can_handle_soc_reset(fsm);
		अगर (soc_reset || !fsm->booted_from_spi)
			/* If we can handle SoC resets, we enable 32-bit address
			 * mode pervasively */
			stfsm_enter_32bit_addr(fsm, 1);

		अन्यथा
			/* Else, enable/disable 32-bit addressing beक्रमe/after
			 * each operation */
			fsm->configuration = (CFG_READ_TOGGLE_32BIT_ADDR |
					      CFG_WRITE_TOGGLE_32BIT_ADDR |
					      CFG_ERASESEC_TOGGLE_32BIT_ADDR);
	पूर्ण

	/* Check status of 'QE' bit, update अगर required. */
	stfsm_पढ़ो_status(fsm, SPINOR_OP_RDSR, &sta, 1);
	data_pads = ((fsm->stfsm_seq_पढ़ो.seq_cfg >> 16) & 0x3) + 1;
	अगर (data_pads == 4) अणु
		अगर (!(sta & MX25_STATUS_QE)) अणु
			/* Set 'QE' */
			sta |= MX25_STATUS_QE;

			stfsm_ग_लिखो_status(fsm, SPINOR_OP_WRSR, sta, 1, 1);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (sta & MX25_STATUS_QE) अणु
			/* Clear 'QE' */
			sta &= ~MX25_STATUS_QE;

			stfsm_ग_लिखो_status(fsm, SPINOR_OP_WRSR, sta, 1, 1);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक stfsm_n25q_config(काष्ठा stfsm *fsm)
अणु
	uपूर्णांक32_t flags = fsm->info->flags;
	uपूर्णांक8_t vcr;
	पूर्णांक ret = 0;
	bool soc_reset;

	/* Configure 'READ' sequence */
	अगर (flags & FLASH_FLAG_32BIT_ADDR)
		ret = stfsm_search_prepare_rw_seq(fsm, &fsm->stfsm_seq_पढ़ो,
						  n25q_पढ़ो4_configs);
	अन्यथा
		ret = stfsm_search_prepare_rw_seq(fsm, &fsm->stfsm_seq_पढ़ो,
						  n25q_पढ़ो3_configs);
	अगर (ret) अणु
		dev_err(fsm->dev,
			"failed to prepare READ sequence with flags [0x%08x]\n",
			flags);
		वापस ret;
	पूर्ण

	/* Configure 'WRITE' sequence (शेष configs) */
	ret = stfsm_search_prepare_rw_seq(fsm, &fsm->stfsm_seq_ग_लिखो,
					  शेष_ग_लिखो_configs);
	अगर (ret) अणु
		dev_err(fsm->dev,
			"preparing WRITE sequence using flags [0x%08x] failed\n",
			flags);
		वापस ret;
	पूर्ण

	/* * Configure 'ERASE_SECTOR' sequence */
	stfsm_prepare_erasesec_seq(fsm, &stfsm_seq_erase_sector);

	/* Configure 32-bit address support */
	अगर (flags & FLASH_FLAG_32BIT_ADDR) अणु
		stfsm_n25q_en_32bit_addr_seq(&fsm->stfsm_seq_en_32bit_addr);

		soc_reset = stfsm_can_handle_soc_reset(fsm);
		अगर (soc_reset || !fsm->booted_from_spi) अणु
			/*
			 * If we can handle SoC resets, we enable 32-bit
			 * address mode pervasively
			 */
			stfsm_enter_32bit_addr(fsm, 1);
		पूर्ण अन्यथा अणु
			/*
			 * If not, enable/disable क्रम WRITE and ERASE
			 * operations (READ uses special commands)
			 */
			fsm->configuration = (CFG_WRITE_TOGGLE_32BIT_ADDR |
					      CFG_ERASESEC_TOGGLE_32BIT_ADDR);
		पूर्ण
	पूर्ण

	/*
	 * Configure device to use 8 dummy cycles
	 */
	vcr = (N25Q_VCR_DUMMY_CYCLES(8) | N25Q_VCR_XIP_DISABLED |
	       N25Q_VCR_WRAP_CONT);
	stfsm_ग_लिखो_status(fsm, N25Q_CMD_WRVCR, vcr, 1, 0);

	वापस 0;
पूर्ण

अटल व्योम stfsm_s25fl_prepare_erasesec_seq_32(काष्ठा stfsm_seq *seq)
अणु
	seq->seq_opc[1] = (SEQ_OPC_PADS_1 |
			   SEQ_OPC_CYCLES(8) |
			   SEQ_OPC_OPCODE(S25FL_CMD_SE4));

	seq->addr_cfg = (ADR_CFG_CYCLES_ADD1(16) |
			 ADR_CFG_PADS_1_ADD1 |
			 ADR_CFG_CYCLES_ADD2(16) |
			 ADR_CFG_PADS_1_ADD2 |
			 ADR_CFG_CSDEASSERT_ADD2);
पूर्ण

अटल व्योम stfsm_s25fl_पढ़ो_dyb(काष्ठा stfsm *fsm, uपूर्णांक32_t offs, uपूर्णांक8_t *dby)
अणु
	uपूर्णांक32_t पंचांगp;
	काष्ठा stfsm_seq seq = अणु
		.data_size = TRANSFER_SIZE(4),
		.seq_opc[0] = (SEQ_OPC_PADS_1 |
			       SEQ_OPC_CYCLES(8) |
			       SEQ_OPC_OPCODE(S25FL_CMD_DYBRD)),
		.addr_cfg = (ADR_CFG_CYCLES_ADD1(16) |
			     ADR_CFG_PADS_1_ADD1 |
			     ADR_CFG_CYCLES_ADD2(16) |
			     ADR_CFG_PADS_1_ADD2),
		.addr1 = (offs >> 16) & 0xffff,
		.addr2 = offs & 0xffff,
		.seq = अणु
			STFSM_INST_CMD1,
			STFSM_INST_ADD1,
			STFSM_INST_ADD2,
			STFSM_INST_DATA_READ,
			STFSM_INST_STOP,
		पूर्ण,
		.seq_cfg = (SEQ_CFG_PADS_1 |
			    SEQ_CFG_READNOTWRITE |
			    SEQ_CFG_CSDEASSERT |
			    SEQ_CFG_STARTSEQ),
	पूर्ण;

	stfsm_load_seq(fsm, &seq);

	stfsm_पढ़ो_fअगरo(fsm, &पंचांगp, 4);

	*dby = (uपूर्णांक8_t)(पंचांगp >> 24);

	stfsm_रुको_seq(fsm);
पूर्ण

अटल व्योम stfsm_s25fl_ग_लिखो_dyb(काष्ठा stfsm *fsm, uपूर्णांक32_t offs, uपूर्णांक8_t dby)
अणु
	काष्ठा stfsm_seq seq = अणु
		.seq_opc[0] = (SEQ_OPC_PADS_1 | SEQ_OPC_CYCLES(8) |
			       SEQ_OPC_OPCODE(SPINOR_OP_WREN) |
			       SEQ_OPC_CSDEASSERT),
		.seq_opc[1] = (SEQ_OPC_PADS_1 | SEQ_OPC_CYCLES(8) |
			       SEQ_OPC_OPCODE(S25FL_CMD_DYBWR)),
		.addr_cfg = (ADR_CFG_CYCLES_ADD1(16) |
			     ADR_CFG_PADS_1_ADD1 |
			     ADR_CFG_CYCLES_ADD2(16) |
			     ADR_CFG_PADS_1_ADD2),
		.status = (uपूर्णांक32_t)dby | STA_PADS_1 | STA_CSDEASSERT,
		.addr1 = (offs >> 16) & 0xffff,
		.addr2 = offs & 0xffff,
		.seq = अणु
			STFSM_INST_CMD1,
			STFSM_INST_CMD2,
			STFSM_INST_ADD1,
			STFSM_INST_ADD2,
			STFSM_INST_STA_WR1,
			STFSM_INST_STOP,
		पूर्ण,
		.seq_cfg = (SEQ_CFG_PADS_1 |
			    SEQ_CFG_READNOTWRITE |
			    SEQ_CFG_CSDEASSERT |
			    SEQ_CFG_STARTSEQ),
	पूर्ण;

	stfsm_load_seq(fsm, &seq);
	stfsm_रुको_seq(fsm);

	stfsm_रुको_busy(fsm);
पूर्ण

अटल पूर्णांक stfsm_s25fl_clear_status_reg(काष्ठा stfsm *fsm)
अणु
	काष्ठा stfsm_seq seq = अणु
		.seq_opc[0] = (SEQ_OPC_PADS_1 |
			       SEQ_OPC_CYCLES(8) |
			       SEQ_OPC_OPCODE(S25FL_CMD_CLSR) |
			       SEQ_OPC_CSDEASSERT),
		.seq_opc[1] = (SEQ_OPC_PADS_1 |
			       SEQ_OPC_CYCLES(8) |
			       SEQ_OPC_OPCODE(SPINOR_OP_WRDI) |
			       SEQ_OPC_CSDEASSERT),
		.seq = अणु
			STFSM_INST_CMD1,
			STFSM_INST_CMD2,
			STFSM_INST_WAIT,
			STFSM_INST_STOP,
		पूर्ण,
		.seq_cfg = (SEQ_CFG_PADS_1 |
			    SEQ_CFG_ERASE |
			    SEQ_CFG_READNOTWRITE |
			    SEQ_CFG_CSDEASSERT |
			    SEQ_CFG_STARTSEQ),
	पूर्ण;

	stfsm_load_seq(fsm, &seq);

	stfsm_रुको_seq(fsm);

	वापस 0;
पूर्ण

अटल पूर्णांक stfsm_s25fl_config(काष्ठा stfsm *fsm)
अणु
	काष्ठा flash_info *info = fsm->info;
	uपूर्णांक32_t flags = info->flags;
	uपूर्णांक32_t data_pads;
	uपूर्णांक32_t offs;
	uपूर्णांक16_t sta_wr;
	uपूर्णांक8_t sr1, cr1, dyb;
	पूर्णांक update_sr = 0;
	पूर्णांक ret;

	अगर (flags & FLASH_FLAG_32BIT_ADDR) अणु
		/*
		 * Prepare Read/Write/Erase sequences according to S25FLxxx
		 * 32-bit address command set
		 */
		ret = stfsm_search_prepare_rw_seq(fsm, &fsm->stfsm_seq_पढ़ो,
						  stfsm_s25fl_पढ़ो4_configs);
		अगर (ret)
			वापस ret;

		ret = stfsm_search_prepare_rw_seq(fsm, &fsm->stfsm_seq_ग_लिखो,
						  stfsm_s25fl_ग_लिखो4_configs);
		अगर (ret)
			वापस ret;

		stfsm_s25fl_prepare_erasesec_seq_32(&stfsm_seq_erase_sector);

	पूर्ण अन्यथा अणु
		/* Use शेष configurations क्रम 24-bit addressing */
		ret = stfsm_prepare_rwe_seqs_शेष(fsm);
		अगर (ret)
			वापस ret;
	पूर्ण

	/*
	 * For devices that support 'DYB' sector locking, check lock status and
	 * unlock sectors अगर necessary (some variants घातer-on with sectors
	 * locked by शेष)
	 */
	अगर (flags & FLASH_FLAG_DYB_LOCKING) अणु
		offs = 0;
		क्रम (offs = 0; offs < info->sector_size * info->n_sectors;) अणु
			stfsm_s25fl_पढ़ो_dyb(fsm, offs, &dyb);
			अगर (dyb == 0x00)
				stfsm_s25fl_ग_लिखो_dyb(fsm, offs, 0xff);

			/* Handle bottom/top 4KiB parameter sectors */
			अगर ((offs < info->sector_size * 2) ||
			    (offs >= (info->sector_size - info->n_sectors * 4)))
				offs += 0x1000;
			अन्यथा
				offs += 0x10000;
		पूर्ण
	पूर्ण

	/* Check status of 'QE' bit, update अगर required. */
	stfsm_पढ़ो_status(fsm, SPINOR_OP_RDCR, &cr1, 1);
	data_pads = ((fsm->stfsm_seq_पढ़ो.seq_cfg >> 16) & 0x3) + 1;
	अगर (data_pads == 4) अणु
		अगर (!(cr1 & STFSM_S25FL_CONFIG_QE)) अणु
			/* Set 'QE' */
			cr1 |= STFSM_S25FL_CONFIG_QE;

			update_sr = 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (cr1 & STFSM_S25FL_CONFIG_QE) अणु
			/* Clear 'QE' */
			cr1 &= ~STFSM_S25FL_CONFIG_QE;

			update_sr = 1;
		पूर्ण
	पूर्ण
	अगर (update_sr) अणु
		stfsm_पढ़ो_status(fsm, SPINOR_OP_RDSR, &sr1, 1);
		sta_wr = ((uपूर्णांक16_t)cr1  << 8) | sr1;
		stfsm_ग_लिखो_status(fsm, SPINOR_OP_WRSR, sta_wr, 2, 1);
	पूर्ण

	/*
	 * S25FLxxx devices support Program and Error error flags.
	 * Configure driver to check flags and clear अगर necessary.
	 */
	fsm->configuration |= CFG_S25FL_CHECK_ERROR_FLAGS;

	वापस 0;
पूर्ण

अटल पूर्णांक stfsm_w25q_config(काष्ठा stfsm *fsm)
अणु
	uपूर्णांक32_t data_pads;
	uपूर्णांक8_t sr1, sr2;
	uपूर्णांक16_t sr_wr;
	पूर्णांक update_sr = 0;
	पूर्णांक ret;

	ret = stfsm_prepare_rwe_seqs_शेष(fsm);
	अगर (ret)
		वापस ret;

	/* Check status of 'QE' bit, update अगर required. */
	stfsm_पढ़ो_status(fsm, SPINOR_OP_RDCR, &sr2, 1);
	data_pads = ((fsm->stfsm_seq_पढ़ो.seq_cfg >> 16) & 0x3) + 1;
	अगर (data_pads == 4) अणु
		अगर (!(sr2 & W25Q_STATUS_QE)) अणु
			/* Set 'QE' */
			sr2 |= W25Q_STATUS_QE;
			update_sr = 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (sr2 & W25Q_STATUS_QE) अणु
			/* Clear 'QE' */
			sr2 &= ~W25Q_STATUS_QE;
			update_sr = 1;
		पूर्ण
	पूर्ण
	अगर (update_sr) अणु
		/* Write status रेजिस्टर */
		stfsm_पढ़ो_status(fsm, SPINOR_OP_RDSR, &sr1, 1);
		sr_wr = ((uपूर्णांक16_t)sr2 << 8) | sr1;
		stfsm_ग_लिखो_status(fsm, SPINOR_OP_WRSR, sr_wr, 2, 1);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक stfsm_पढ़ो(काष्ठा stfsm *fsm, uपूर्णांक8_t *buf, uपूर्णांक32_t size,
		      uपूर्णांक32_t offset)
अणु
	काष्ठा stfsm_seq *seq = &fsm->stfsm_seq_पढ़ो;
	uपूर्णांक32_t data_pads;
	uपूर्णांक32_t पढ़ो_mask;
	uपूर्णांक32_t size_ub;
	uपूर्णांक32_t size_lb;
	uपूर्णांक32_t size_mop;
	uपूर्णांक32_t पंचांगp[4];
	uपूर्णांक32_t page_buf[FLASH_PAGESIZE_32];
	uपूर्णांक8_t *p;

	dev_dbg(fsm->dev, "reading %d bytes from 0x%08x\n", size, offset);

	/* Enter 32-bit address mode, अगर required */
	अगर (fsm->configuration & CFG_READ_TOGGLE_32BIT_ADDR)
		stfsm_enter_32bit_addr(fsm, 1);

	/* Must पढ़ो in multiples of 32 cycles (or 32*pads/8 Bytes) */
	data_pads = ((seq->seq_cfg >> 16) & 0x3) + 1;
	पढ़ो_mask = (data_pads << 2) - 1;

	/* Handle non-aligned buf */
	p = ((uपूर्णांकptr_t)buf & 0x3) ? (uपूर्णांक8_t *)page_buf : buf;

	/* Handle non-aligned size */
	size_ub = (size + पढ़ो_mask) & ~पढ़ो_mask;
	size_lb = size & ~पढ़ो_mask;
	size_mop = size & पढ़ो_mask;

	seq->data_size = TRANSFER_SIZE(size_ub);
	seq->addr1 = (offset >> 16) & 0xffff;
	seq->addr2 = offset & 0xffff;

	stfsm_load_seq(fsm, seq);

	अगर (size_lb)
		stfsm_पढ़ो_fअगरo(fsm, (uपूर्णांक32_t *)p, size_lb);

	अगर (size_mop) अणु
		stfsm_पढ़ो_fअगरo(fsm, पंचांगp, पढ़ो_mask + 1);
		स_नकल(p + size_lb, &पंचांगp, size_mop);
	पूर्ण

	/* Handle non-aligned buf */
	अगर ((uपूर्णांकptr_t)buf & 0x3)
		स_नकल(buf, page_buf, size);

	/* Wait क्रम sequence to finish */
	stfsm_रुको_seq(fsm);

	stfsm_clear_fअगरo(fsm);

	/* Exit 32-bit address mode, अगर required */
	अगर (fsm->configuration & CFG_READ_TOGGLE_32BIT_ADDR)
		stfsm_enter_32bit_addr(fsm, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक stfsm_ग_लिखो(काष्ठा stfsm *fsm, स्थिर uपूर्णांक8_t *buf,
		       uपूर्णांक32_t size, uपूर्णांक32_t offset)
अणु
	काष्ठा stfsm_seq *seq = &fsm->stfsm_seq_ग_लिखो;
	uपूर्णांक32_t data_pads;
	uपूर्णांक32_t ग_लिखो_mask;
	uपूर्णांक32_t size_ub;
	uपूर्णांक32_t size_lb;
	uपूर्णांक32_t size_mop;
	uपूर्णांक32_t पंचांगp[4];
	uपूर्णांक32_t i;
	uपूर्णांक32_t page_buf[FLASH_PAGESIZE_32];
	uपूर्णांक8_t *t = (uपूर्णांक8_t *)&पंचांगp;
	स्थिर uपूर्णांक8_t *p;
	पूर्णांक ret;

	dev_dbg(fsm->dev, "writing %d bytes to 0x%08x\n", size, offset);

	/* Enter 32-bit address mode, अगर required */
	अगर (fsm->configuration & CFG_WRITE_TOGGLE_32BIT_ADDR)
		stfsm_enter_32bit_addr(fsm, 1);

	/* Must ग_लिखो in multiples of 32 cycles (or 32*pads/8 bytes) */
	data_pads = ((seq->seq_cfg >> 16) & 0x3) + 1;
	ग_लिखो_mask = (data_pads << 2) - 1;

	/* Handle non-aligned buf */
	अगर ((uपूर्णांकptr_t)buf & 0x3) अणु
		स_नकल(page_buf, buf, size);
		p = (uपूर्णांक8_t *)page_buf;
	पूर्ण अन्यथा अणु
		p = buf;
	पूर्ण

	/* Handle non-aligned size */
	size_ub = (size + ग_लिखो_mask) & ~ग_लिखो_mask;
	size_lb = size & ~ग_लिखो_mask;
	size_mop = size & ग_लिखो_mask;

	seq->data_size = TRANSFER_SIZE(size_ub);
	seq->addr1 = (offset >> 16) & 0xffff;
	seq->addr2 = offset & 0xffff;

	/* Need to set FIFO to ग_लिखो mode, beक्रमe writing data to FIFO (see
	 * GNBvb79594)
	 */
	ग_लिखोl(0x00040000, fsm->base + SPI_FAST_SEQ_CFG);

	/*
	 * Beक्रमe writing data to the FIFO, apply a small delay to allow a
	 * potential change of FIFO direction to complete.
	 */
	अगर (fsm->fअगरo_dir_delay == 0)
		पढ़ोl(fsm->base + SPI_FAST_SEQ_CFG);
	अन्यथा
		udelay(fsm->fअगरo_dir_delay);


	/* Write data to FIFO, beक्रमe starting sequence (see GNBvd79593) */
	अगर (size_lb) अणु
		stfsm_ग_लिखो_fअगरo(fsm, (uपूर्णांक32_t *)p, size_lb);
		p += size_lb;
	पूर्ण

	/* Handle non-aligned size */
	अगर (size_mop) अणु
		स_रखो(t, 0xff, ग_लिखो_mask + 1);	/* fill with 0xff's */
		क्रम (i = 0; i < size_mop; i++)
			t[i] = *p++;

		stfsm_ग_लिखो_fअगरo(fsm, पंचांगp, ग_लिखो_mask + 1);
	पूर्ण

	/* Start sequence */
	stfsm_load_seq(fsm, seq);

	/* Wait क्रम sequence to finish */
	stfsm_रुको_seq(fsm);

	/* Wait क्रम completion */
	ret = stfsm_रुको_busy(fsm);
	अगर (ret && fsm->configuration & CFG_S25FL_CHECK_ERROR_FLAGS)
		stfsm_s25fl_clear_status_reg(fsm);

	/* Exit 32-bit address mode, अगर required */
	अगर (fsm->configuration & CFG_WRITE_TOGGLE_32BIT_ADDR)
		stfsm_enter_32bit_addr(fsm, 0);

	वापस 0;
पूर्ण

/*
 * Read an address range from the flash chip. The address range
 * may be any size provided it is within the physical boundaries.
 */
अटल पूर्णांक stfsm_mtd_पढ़ो(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len,
			  माप_प्रकार *retlen, u_अक्षर *buf)
अणु
	काष्ठा stfsm *fsm = dev_get_drvdata(mtd->dev.parent);
	uपूर्णांक32_t bytes;

	dev_dbg(fsm->dev, "%s from 0x%08x, len %zd\n",
		__func__, (u32)from, len);

	mutex_lock(&fsm->lock);

	जबतक (len > 0) अणु
		bytes = min_t(माप_प्रकार, len, FLASH_PAGESIZE);

		stfsm_पढ़ो(fsm, buf, bytes, from);

		buf += bytes;
		from += bytes;
		len -= bytes;

		*retlen += bytes;
	पूर्ण

	mutex_unlock(&fsm->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक stfsm_erase_sector(काष्ठा stfsm *fsm, uपूर्णांक32_t offset)
अणु
	काष्ठा stfsm_seq *seq = &stfsm_seq_erase_sector;
	पूर्णांक ret;

	dev_dbg(fsm->dev, "erasing sector at 0x%08x\n", offset);

	/* Enter 32-bit address mode, अगर required */
	अगर (fsm->configuration & CFG_ERASESEC_TOGGLE_32BIT_ADDR)
		stfsm_enter_32bit_addr(fsm, 1);

	seq->addr1 = (offset >> 16) & 0xffff;
	seq->addr2 = offset & 0xffff;

	stfsm_load_seq(fsm, seq);

	stfsm_रुको_seq(fsm);

	/* Wait क्रम completion */
	ret = stfsm_रुको_busy(fsm);
	अगर (ret && fsm->configuration & CFG_S25FL_CHECK_ERROR_FLAGS)
		stfsm_s25fl_clear_status_reg(fsm);

	/* Exit 32-bit address mode, अगर required */
	अगर (fsm->configuration & CFG_ERASESEC_TOGGLE_32BIT_ADDR)
		stfsm_enter_32bit_addr(fsm, 0);

	वापस ret;
पूर्ण

अटल पूर्णांक stfsm_erase_chip(काष्ठा stfsm *fsm)
अणु
	स्थिर काष्ठा stfsm_seq *seq = &stfsm_seq_erase_chip;

	dev_dbg(fsm->dev, "erasing chip\n");

	stfsm_load_seq(fsm, seq);

	stfsm_रुको_seq(fsm);

	वापस stfsm_रुको_busy(fsm);
पूर्ण

/*
 * Write an address range to the flash chip.  Data must be written in
 * FLASH_PAGESIZE chunks.  The address range may be any size provided
 * it is within the physical boundaries.
 */
अटल पूर्णांक stfsm_mtd_ग_लिखो(काष्ठा mtd_info *mtd, loff_t to, माप_प्रकार len,
			   माप_प्रकार *retlen, स्थिर u_अक्षर *buf)
अणु
	काष्ठा stfsm *fsm = dev_get_drvdata(mtd->dev.parent);

	u32 page_offs;
	u32 bytes;
	uपूर्णांक8_t *b = (uपूर्णांक8_t *)buf;
	पूर्णांक ret = 0;

	dev_dbg(fsm->dev, "%s to 0x%08x, len %zd\n", __func__, (u32)to, len);

	/* Offset within page */
	page_offs = to % FLASH_PAGESIZE;

	mutex_lock(&fsm->lock);

	जबतक (len) अणु
		/* Write up to page boundary */
		bytes = min_t(माप_प्रकार, FLASH_PAGESIZE - page_offs, len);

		ret = stfsm_ग_लिखो(fsm, b, bytes, to);
		अगर (ret)
			जाओ out1;

		b += bytes;
		len -= bytes;
		to += bytes;

		/* We are now page-aligned */
		page_offs = 0;

		*retlen += bytes;

	पूर्ण

out1:
	mutex_unlock(&fsm->lock);

	वापस ret;
पूर्ण

/*
 * Erase an address range on the flash chip. The address range may extend
 * one or more erase sectors.  Return an error is there is a problem erasing.
 */
अटल पूर्णांक stfsm_mtd_erase(काष्ठा mtd_info *mtd, काष्ठा erase_info *instr)
अणु
	काष्ठा stfsm *fsm = dev_get_drvdata(mtd->dev.parent);
	u32 addr, len;
	पूर्णांक ret;

	dev_dbg(fsm->dev, "%s at 0x%llx, len %lld\n", __func__,
		(दीर्घ दीर्घ)instr->addr, (दीर्घ दीर्घ)instr->len);

	addr = instr->addr;
	len = instr->len;

	mutex_lock(&fsm->lock);

	/* Whole-chip erase? */
	अगर (len == mtd->size) अणु
		ret = stfsm_erase_chip(fsm);
		अगर (ret)
			जाओ out1;
	पूर्ण अन्यथा अणु
		जबतक (len) अणु
			ret = stfsm_erase_sector(fsm, addr);
			अगर (ret)
				जाओ out1;

			addr += mtd->erasesize;
			len -= mtd->erasesize;
		पूर्ण
	पूर्ण

	mutex_unlock(&fsm->lock);

	वापस 0;

out1:
	mutex_unlock(&fsm->lock);

	वापस ret;
पूर्ण

अटल व्योम stfsm_पढ़ो_jedec(काष्ठा stfsm *fsm, uपूर्णांक8_t *jedec)
अणु
	स्थिर काष्ठा stfsm_seq *seq = &stfsm_seq_पढ़ो_jedec;
	uपूर्णांक32_t पंचांगp[2];

	stfsm_load_seq(fsm, seq);

	stfsm_पढ़ो_fअगरo(fsm, पंचांगp, 8);

	स_नकल(jedec, पंचांगp, 5);

	stfsm_रुको_seq(fsm);
पूर्ण

अटल काष्ठा flash_info *stfsm_jedec_probe(काष्ठा stfsm *fsm)
अणु
	काष्ठा flash_info	*info;
	u16                     ext_jedec;
	u32			jedec;
	u8			id[5];

	stfsm_पढ़ो_jedec(fsm, id);

	jedec     = id[0] << 16 | id[1] << 8 | id[2];
	/*
	 * JEDEC also defines an optional "extended device information"
	 * string क्रम after venकरोr-specअगरic data, after the three bytes
	 * we use here. Supporting some chips might require using it.
	 */
	ext_jedec = id[3] << 8  | id[4];

	dev_dbg(fsm->dev, "JEDEC =  0x%08x [%5ph]\n", jedec, id);

	क्रम (info = flash_types; info->name; info++) अणु
		अगर (info->jedec_id == jedec) अणु
			अगर (info->ext_id && info->ext_id != ext_jedec)
				जारी;
			वापस info;
		पूर्ण
	पूर्ण
	dev_err(fsm->dev, "Unrecognized JEDEC id %06x\n", jedec);

	वापस शून्य;
पूर्ण

अटल पूर्णांक stfsm_set_mode(काष्ठा stfsm *fsm, uपूर्णांक32_t mode)
अणु
	पूर्णांक ret, समयout = 10;

	/* Wait क्रम controller to accept mode change */
	जबतक (--समयout) अणु
		ret = पढ़ोl(fsm->base + SPI_STA_MODE_CHANGE);
		अगर (ret & 0x1)
			अवरोध;
		udelay(1);
	पूर्ण

	अगर (!समयout)
		वापस -EBUSY;

	ग_लिखोl(mode, fsm->base + SPI_MODESELECT);

	वापस 0;
पूर्ण

अटल व्योम stfsm_set_freq(काष्ठा stfsm *fsm, uपूर्णांक32_t spi_freq)
अणु
	uपूर्णांक32_t emi_freq;
	uपूर्णांक32_t clk_भाग;

	emi_freq = clk_get_rate(fsm->clk);

	/*
	 * Calculate clk_भाग - values between 2 and 128
	 * Multiple of 2, rounded up
	 */
	clk_भाग = 2 * DIV_ROUND_UP(emi_freq, 2 * spi_freq);
	अगर (clk_भाग < 2)
		clk_भाग = 2;
	अन्यथा अगर (clk_भाग > 128)
		clk_भाग = 128;

	/*
	 * Determine a suitable delay क्रम the IP to complete a change of
	 * direction of the FIFO. The required delay is related to the घड़ी
	 * भागider used. The following heuristics are based on empirical tests,
	 * using a 100MHz EMI घड़ी.
	 */
	अगर (clk_भाग <= 4)
		fsm->fअगरo_dir_delay = 0;
	अन्यथा अगर (clk_भाग <= 10)
		fsm->fअगरo_dir_delay = 1;
	अन्यथा
		fsm->fअगरo_dir_delay = DIV_ROUND_UP(clk_भाग, 10);

	dev_dbg(fsm->dev, "emi_clk = %uHZ, spi_freq = %uHZ, clk_div = %u\n",
		emi_freq, spi_freq, clk_भाग);

	ग_लिखोl(clk_भाग, fsm->base + SPI_CLOCKDIV);
पूर्ण

अटल पूर्णांक stfsm_init(काष्ठा stfsm *fsm)
अणु
	पूर्णांक ret;

	/* Perक्रमm a soft reset of the FSM controller */
	ग_लिखोl(SEQ_CFG_SWRESET, fsm->base + SPI_FAST_SEQ_CFG);
	udelay(1);
	ग_लिखोl(0, fsm->base + SPI_FAST_SEQ_CFG);

	/* Set घड़ी to 'safe' frequency initially */
	stfsm_set_freq(fsm, STFSM_FLASH_SAFE_FREQ);

	/* Switch to FSM */
	ret = stfsm_set_mode(fsm, SPI_MODESELECT_FSM);
	अगर (ret)
		वापस ret;

	/* Set timing parameters */
	ग_लिखोl(SPI_CFG_DEVICE_ST            |
	       SPI_CFG_DEFAULT_MIN_CS_HIGH  |
	       SPI_CFG_DEFAULT_CS_SETUPHOLD |
	       SPI_CFG_DEFAULT_DATA_HOLD,
	       fsm->base + SPI_CONFIGDATA);
	ग_लिखोl(STFSM_DEFAULT_WR_TIME, fsm->base + SPI_STATUS_WR_TIME_REG);

	/*
	 * Set the FSM 'WAIT' delay to the minimum workable value.  Note, क्रम
	 * our purposes, the WAIT inकाष्ठाion is used purely to achieve
	 * "sequence validity" rather than actually implement a delay.
	 */
	ग_लिखोl(0x00000001, fsm->base + SPI_PROGRAM_ERASE_TIME);

	/* Clear FIFO, just in हाल */
	stfsm_clear_fअगरo(fsm);

	वापस 0;
पूर्ण

अटल व्योम stfsm_fetch_platक्रमm_configs(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा stfsm *fsm = platक्रमm_get_drvdata(pdev);
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा regmap *regmap;
	uपूर्णांक32_t boot_device_reg;
	uपूर्णांक32_t boot_device_spi;
	uपूर्णांक32_t boot_device;     /* Value we पढ़ो from *boot_device_reg */
	पूर्णांक ret;

	/* Booting from SPI NOR Flash is the शेष */
	fsm->booted_from_spi = true;

	regmap = syscon_regmap_lookup_by_phandle(np, "st,syscfg");
	अगर (IS_ERR(regmap))
		जाओ boot_device_fail;

	fsm->reset_संकेत = of_property_पढ़ो_bool(np, "st,reset-signal");

	fsm->reset_por = of_property_पढ़ो_bool(np, "st,reset-por");

	/* Where in the syscon the boot device inक्रमmation lives */
	ret = of_property_पढ़ो_u32(np, "st,boot-device-reg", &boot_device_reg);
	अगर (ret)
		जाओ boot_device_fail;

	/* Boot device value when booted from SPI NOR */
	ret = of_property_पढ़ो_u32(np, "st,boot-device-spi", &boot_device_spi);
	अगर (ret)
		जाओ boot_device_fail;

	ret = regmap_पढ़ो(regmap, boot_device_reg, &boot_device);
	अगर (ret)
		जाओ boot_device_fail;

	अगर (boot_device != boot_device_spi)
		fsm->booted_from_spi = false;

	वापस;

boot_device_fail:
	dev_warn(&pdev->dev,
		 "failed to fetch boot device, assuming boot from SPI\n");
पूर्ण

अटल पूर्णांक stfsm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा flash_info *info;
	काष्ठा resource *res;
	काष्ठा stfsm *fsm;
	पूर्णांक ret;

	अगर (!np) अणु
		dev_err(&pdev->dev, "No DT found\n");
		वापस -EINVAL;
	पूर्ण

	fsm = devm_kzalloc(&pdev->dev, माप(*fsm), GFP_KERNEL);
	अगर (!fsm)
		वापस -ENOMEM;

	fsm->dev = &pdev->dev;

	platक्रमm_set_drvdata(pdev, fsm);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "Resource not found\n");
		वापस -ENODEV;
	पूर्ण

	fsm->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(fsm->base)) अणु
		dev_err(&pdev->dev,
			"Failed to reserve memory region %pR\n", res);
		वापस PTR_ERR(fsm->base);
	पूर्ण

	fsm->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(fsm->clk)) अणु
		dev_err(fsm->dev, "Couldn't find EMI clock.\n");
		वापस PTR_ERR(fsm->clk);
	पूर्ण

	ret = clk_prepare_enable(fsm->clk);
	अगर (ret) अणु
		dev_err(fsm->dev, "Failed to enable EMI clock.\n");
		वापस ret;
	पूर्ण

	mutex_init(&fsm->lock);

	ret = stfsm_init(fsm);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to initialise FSM Controller\n");
		जाओ err_clk_unprepare;
	पूर्ण

	stfsm_fetch_platक्रमm_configs(pdev);

	/* Detect SPI FLASH device */
	info = stfsm_jedec_probe(fsm);
	अगर (!info) अणु
		ret = -ENODEV;
		जाओ err_clk_unprepare;
	पूर्ण
	fsm->info = info;

	/* Use device size to determine address width */
	अगर (info->sector_size * info->n_sectors > 0x1000000)
		info->flags |= FLASH_FLAG_32BIT_ADDR;

	/*
	 * Configure READ/WRITE/ERASE sequences according to platक्रमm and
	 * device flags.
	 */
	अगर (info->config) अणु
		ret = info->config(fsm);
		अगर (ret)
			जाओ err_clk_unprepare;
	पूर्ण अन्यथा अणु
		ret = stfsm_prepare_rwe_seqs_शेष(fsm);
		अगर (ret)
			जाओ err_clk_unprepare;
	पूर्ण

	fsm->mtd.name		= info->name;
	fsm->mtd.dev.parent	= &pdev->dev;
	mtd_set_of_node(&fsm->mtd, np);
	fsm->mtd.type		= MTD_NORFLASH;
	fsm->mtd.ग_लिखोsize	= 4;
	fsm->mtd.ग_लिखोbufsize	= fsm->mtd.ग_लिखोsize;
	fsm->mtd.flags		= MTD_CAP_NORFLASH;
	fsm->mtd.size		= info->sector_size * info->n_sectors;
	fsm->mtd.erasesize	= info->sector_size;

	fsm->mtd._पढ़ो  = stfsm_mtd_पढ़ो;
	fsm->mtd._ग_लिखो = stfsm_mtd_ग_लिखो;
	fsm->mtd._erase = stfsm_mtd_erase;

	dev_info(&pdev->dev,
		"Found serial flash device: %s\n"
		" size = %llx (%lldMiB) erasesize = 0x%08x (%uKiB)\n",
		info->name,
		(दीर्घ दीर्घ)fsm->mtd.size, (दीर्घ दीर्घ)(fsm->mtd.size >> 20),
		fsm->mtd.erasesize, (fsm->mtd.erasesize >> 10));

	वापस mtd_device_रेजिस्टर(&fsm->mtd, शून्य, 0);

err_clk_unprepare:
	clk_disable_unprepare(fsm->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक stfsm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा stfsm *fsm = platक्रमm_get_drvdata(pdev);

	वापस mtd_device_unरेजिस्टर(&fsm->mtd);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक stfsmfsm_suspend(काष्ठा device *dev)
अणु
	काष्ठा stfsm *fsm = dev_get_drvdata(dev);

	clk_disable_unprepare(fsm->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक stfsmfsm_resume(काष्ठा device *dev)
अणु
	काष्ठा stfsm *fsm = dev_get_drvdata(dev);

	वापस clk_prepare_enable(fsm->clk);
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(stfsm_pm_ops, stfsmfsm_suspend, stfsmfsm_resume);

अटल स्थिर काष्ठा of_device_id stfsm_match[] = अणु
	अणु .compatible = "st,spi-fsm", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, stfsm_match);

अटल काष्ठा platक्रमm_driver stfsm_driver = अणु
	.probe		= stfsm_probe,
	.हटाओ		= stfsm_हटाओ,
	.driver		= अणु
		.name	= "st-spi-fsm",
		.of_match_table = stfsm_match,
		.pm     = &stfsm_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(stfsm_driver);

MODULE_AUTHOR("Angus Clark <angus.clark@st.com>");
MODULE_DESCRIPTION("ST SPI FSM driver");
MODULE_LICENSE("GPL");
