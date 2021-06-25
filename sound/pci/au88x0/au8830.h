<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
    Aureal Vortex Soundcard driver.

    IO addr collected from asp4core.vxd:
    function    address
    0005D5A0    13004
    00080674    14004
    00080AFF    12818

 */

#घोषणा CHIP_AU8830

#घोषणा CARD_NAME "Aureal Vortex 2"
#घोषणा CARD_NAME_SHORT "au8830"

#घोषणा NR_ADB 0x20
#घोषणा NR_SRC 0x10
#घोषणा NR_A3D 0x10
#घोषणा NR_MIXIN 0x20
#घोषणा NR_MIXOUT 0x10
#घोषणा NR_WT 0x40

/* ADBDMA */
#घोषणा VORTEX_ADBDMA_STAT 0x27e00	/* पढ़ो only, subbuffer, DMA pos */
#घोषणा		POS_MASK 0x00000fff
#घोषणा     POS_SHIFT 0x0
#घोषणा 	ADB_SUBBUF_MASK 0x00003000	/* ADB only. */
#घोषणा     ADB_SUBBUF_SHIFT 0xc	/* ADB only. */
#घोषणा VORTEX_ADBDMA_CTRL 0x27a00	/* ग_लिखो only; क्रमmat, flags, DMA pos */
#घोषणा		OFFSET_MASK 0x00000fff
#घोषणा     OFFSET_SHIFT 0x0
#घोषणा		IE_MASK 0x00001000	/* पूर्णांकerrupt enable. */
#घोषणा     IE_SHIFT 0xc
#घोषणा     सूची_MASK 0x00002000	/* Direction. */
#घोषणा     सूची_SHIFT 0xd
#घोषणा		FMT_MASK 0x0003c000
#घोषणा		FMT_SHIFT 0xe
#घोषणा		ADB_FIFO_EN_SHIFT	0x15
#घोषणा		ADB_FIFO_EN			(1 << 0x15)
// The ADB masks and shअगरt also are valid क्रम the wtdma, except अगर specअगरied otherwise.
#घोषणा VORTEX_ADBDMA_BUFCFG0 0x27800
#घोषणा VORTEX_ADBDMA_BUFCFG1 0x27804
#घोषणा VORTEX_ADBDMA_BUFBASE 0x27400
#घोषणा VORTEX_ADBDMA_START 0x27c00	/* Which subbuffer starts */

#घोषणा VORTEX_ADBDMA_STATUS 0x27A90	/* stored at AdbDma->this_10 / 2 DWORD in size. */
/* Starting at the MSB, each pair of bits seem to be the current DMA page. */
/* This current page bits are consistent (same value) with VORTEX_ADBDMA_STAT) */

/* DMA */
#घोषणा VORTEX_ENGINE_CTRL 0x27ae8
#घोषणा 	ENGINE_INIT 0x1380000

/* WTDMA */
#घोषणा VORTEX_WTDMA_CTRL 0x27900	/* क्रमmat, DMA pos */
#घोषणा VORTEX_WTDMA_STAT 0x27d00	/* DMA subbuf, DMA pos */
#घोषणा     WT_SUBBUF_MASK 0x3
#घोषणा     WT_SUBBUF_SHIFT 0xc
#घोषणा VORTEX_WTDMA_BUFBASE 0x27000
#घोषणा VORTEX_WTDMA_BUFCFG0 0x27600
#घोषणा VORTEX_WTDMA_BUFCFG1 0x27604
#घोषणा VORTEX_WTDMA_START 0x27b00	/* which subbuffer is first */

/* ADB */
#घोषणा VORTEX_ADB_SR 0x28400	/* Samplerates enable/disable */
#घोषणा VORTEX_ADB_RTBASE 0x28000
#घोषणा VORTEX_ADB_RTBASE_COUNT 173
#घोषणा VORTEX_ADB_CHNBASE 0x282b4
#घोषणा VORTEX_ADB_CHNBASE_COUNT 24
#घोषणा 	ROUTE_MASK	0xffff
#घोषणा		SOURCE_MASK	0xff00
#घोषणा     ADB_MASK   0xff
#घोषणा		ADB_SHIFT 0x8
/* ADB address */
#घोषणा		OFFSET_ADBDMA	0x00
#घोषणा		OFFSET_ADBDMAB	0x20
#घोषणा		OFFSET_SRCIN	0x40
#घोषणा		OFFSET_SRCOUT	0x20	/* ch 0x11 */
#घोषणा		OFFSET_MIXIN	0x50	/* ch 0x11 */
#घोषणा		OFFSET_MIXOUT	0x30	/* ch 0x11 */
#घोषणा		OFFSET_CODECIN	0x70 /* ch 0x11 */	/* adb source */
#घोषणा		OFFSET_CODECOUT	0x88 /* ch 0x11 */	/* adb target */
#घोषणा		OFFSET_SPORTIN	0x78	/* ch 0x13 ADB source. 2 routes. */
#घोषणा		OFFSET_SPORTOUT	0x90	/* ch 0x13 ADB sink. 2 routes. */
#घोषणा		OFFSET_SPDIFIN	0x7A	/* ch 0x14 ADB source. */
#घोषणा		OFFSET_SPDIFOUT	0x92	/* ch 0x14 ADB sink. */
#घोषणा		OFFSET_AC98IN	0x7c	/* ch 0x14 ADB source. */
#घोषणा		OFFSET_AC98OUT	0x94	/* ch 0x14 ADB sink. */
#घोषणा		OFFSET_EQIN		0xa0	/* ch 0x11 */
#घोषणा		OFFSET_EQOUT	0x7e /* ch 0x11 */	/* 2 routes on ch 0x11 */
#घोषणा		OFFSET_A3DIN	0x70	/* ADB sink. */
#घोषणा		OFFSET_A3DOUT	0xA6	/* ADB source. 2 routes per slice = 8 */
#घोषणा		OFFSET_WT0		0x40	/* WT bank 0 output. 0x40 - 0x65 */
#घोषणा		OFFSET_WT1		0x80	/* WT bank 1 output. 0x80 - 0xA5 */
/* WT sources offset : 0x00-0x1f Direct stream. */
/* WT sources offset : 0x20-0x25 Mixed Output. */
#घोषणा		OFFSET_XTALKOUT	0x66	/* crosstalk canceller (source) 2 routes */
#घोषणा		OFFSET_XTALKIN	0x96	/* crosstalk canceller (sink). 10 routes */
#घोषणा		OFFSET_EFXOUT	0x68	/* ADB source. 8 routes. */
#घोषणा		OFFSET_EFXIN	0x80	/* ADB sink. 8 routes. */

/* ADB route translate helper */
#घोषणा ADB_DMA(x) (x)
#घोषणा ADB_SRCOUT(x) (x + OFFSET_SRCOUT)
#घोषणा ADB_SRCIN(x) (x + OFFSET_SRCIN)
#घोषणा ADB_MIXOUT(x) (x + OFFSET_MIXOUT)
#घोषणा ADB_MIXIN(x) (x + OFFSET_MIXIN)
#घोषणा ADB_CODECIN(x) (x + OFFSET_CODECIN)
#घोषणा ADB_CODECOUT(x) (x + OFFSET_CODECOUT)
#घोषणा ADB_SPORTIN(x) (x + OFFSET_SPORTIN)
#घोषणा ADB_SPORTOUT(x) (x + OFFSET_SPORTOUT)
#घोषणा ADB_SPDIFIN(x)	(x + OFFSET_SPDIFIN)
#घोषणा ADB_SPDIFOUT(x)	(x + OFFSET_SPDIFOUT)
#घोषणा ADB_EQIN(x) (x + OFFSET_EQIN)
#घोषणा ADB_EQOUT(x) (x + OFFSET_EQOUT)
#घोषणा ADB_A3DOUT(x) (x + OFFSET_A3DOUT)	/* 0x10 A3D blocks */
#घोषणा ADB_A3DIN(x) (x + OFFSET_A3DIN)
//#घोषणा ADB_WTOUT(x) ((x<x20)?(x + OFFSET_WT0):(x + OFFSET_WT1))
#घोषणा ADB_WTOUT(x,y) (((x)==0)?((y) + OFFSET_WT0):((y) + OFFSET_WT1))
#घोषणा ADB_XTALKIN(x) ((x) + OFFSET_XTALKIN)
#घोषणा ADB_XTALKOUT(x) ((x) + OFFSET_XTALKOUT)

#घोषणा MIX_DEFIGAIN 0x08
#घोषणा MIX_DEFOGAIN 0x08	/* 0x8->6dB  (6dB = x4) 16 to 18 bit conversion? */

/* MIXER */
#घोषणा VORTEX_MIXER_SR 0x21f00
#घोषणा VORTEX_MIXER_CLIP 0x21f80
#घोषणा VORTEX_MIXER_CHNBASE 0x21e40
#घोषणा VORTEX_MIXER_RTBASE 0x21e00
#घोषणा 	MIXER_RTBASE_SIZE 0x38
#घोषणा VORTEX_MIX_ENIN 0x21a00	/* Input enable bits. 4 bits wide. */
#घोषणा VORTEX_MIX_SMP 0x21c00	/* wave data buffers. AU8820: 0x9c00 */

/* MIX */
#घोषणा VORTEX_MIX_INVOL_B 0x20000	/* Input volume current */
#घोषणा VORTEX_MIX_VOL_B 0x20800	/* Output Volume current */
#घोषणा VORTEX_MIX_INVOL_A 0x21000	/* Input Volume target */
#घोषणा VORTEX_MIX_VOL_A 0x21800	/* Output Volume target */

#घोषणा 	VOL_MIN 0x80	/* Input volume when muted. */
#घोषणा		VOL_MAX 0x7f	/* FIXME: Not confirmed! Just guessed. */

/* SRC */
#घोषणा VORTEX_SRC_CHNBASE		0x26c40
#घोषणा VORTEX_SRC_RTBASE		0x26c00
#घोषणा VORTEX_SRCBLOCK_SR		0x26cc0
#घोषणा VORTEX_SRC_SOURCE		0x26cc4
#घोषणा VORTEX_SRC_SOURCESIZE	0x26cc8
/* Params
	0x26e00	: 1 U0
	0x26e40	: 2 CR
	0x26e80	: 3 U3
	0x26ec0	: 4 DRIFT1
	0x26f00 : 5 U1
	0x26f40	: 6 DRIFT2
	0x26f80	: 7 U2 : Target rate, direction
*/

#घोषणा VORTEX_SRC_CONVRATIO	0x26e40
#घोषणा VORTEX_SRC_DRIFT0		0x26e80
#घोषणा VORTEX_SRC_DRIFT1		0x26ec0
#घोषणा VORTEX_SRC_DRIFT2		0x26f40
#घोषणा VORTEX_SRC_U0			0x26e00
#घोषणा		U0_SLOWLOCK		0x200
#घोषणा VORTEX_SRC_U1			0x26f00
#घोषणा VORTEX_SRC_U2			0x26f80
#घोषणा VORTEX_SRC_DATA			0x26800	/* 0xc800 */
#घोषणा VORTEX_SRC_DATA0		0x26000

/* FIFO */
#घोषणा VORTEX_FIFO_ADBCTRL 0x16100	/* Control bits. */
#घोषणा VORTEX_FIFO_WTCTRL 0x16000
#घोषणा		FIFO_RDONLY	0x00000001
#घोषणा		FIFO_CTRL	0x00000002	/* Allow ctrl. ? */
#घोषणा		FIFO_VALID	0x00000010
#घोषणा 	FIFO_EMPTY	0x00000020
#घोषणा		FIFO_U0		0x00002000	/* Unknown. */
#घोषणा		FIFO_U1		0x00040000
#घोषणा		FIFO_SIZE_BITS 6
#घोषणा		FIFO_SIZE	(1<<(FIFO_SIZE_BITS))	// 0x40
#घोषणा 	FIFO_MASK	(FIFO_SIZE-1)	//0x3f    /* at shअगरt left 0xc */
#घोषणा 	FIFO_BITS	0x1c400000
#घोषणा VORTEX_FIFO_ADBDATA 0x14000
#घोषणा VORTEX_FIFO_WTDATA 0x10000

#घोषणा VORTEX_FIFO_GIRT	0x17000	/* wt0, wt1, adb */
#घोषणा		GIRT_COUNT	3

/* CODEC */

#घोषणा VORTEX_CODEC_CHN 0x29080	/* The name "CHN" is wrong. */

#घोषणा VORTEX_CODEC_CTRL 0x29184
#घोषणा VORTEX_CODEC_IO 0x29188

#घोषणा VORTEX_CODEC_SPORTCTRL 0x2918c

#घोषणा VORTEX_CODEC_EN 0x29190
#घोषणा		EN_AUDIO0		0x00000300
#घोषणा		EN_MODEM		0x00000c00
#घोषणा		EN_AUDIO1		0x00003000
#घोषणा		EN_SPORT		0x00030000
#घोषणा		EN_SPDIF		0x000c0000
#घोषणा		EN_CODEC		(EN_AUDIO1 | EN_AUDIO0)

#घोषणा VORTEX_SPDIF_SMPRATE	0x29194

#घोषणा VORTEX_SPDIF_FLAGS		0x2205c
#घोषणा VORTEX_SPDIF_CFG0		0x291D0	/* status data */
#घोषणा VORTEX_SPDIF_CFG1		0x291D4

#घोषणा VORTEX_SMP_TIME			0x29198	/* Sample counter/समयr */
#घोषणा VORTEX_SMP_TIMER		0x2919c
#घोषणा VORTEX_CODEC2_CTRL		0x291a0

#घोषणा VORTEX_MODEM_CTRL		0x291ac

/* IRQ */
#घोषणा VORTEX_IRQ_SOURCE 0x2a000	/* Interrupt source flags. */
#घोषणा VORTEX_IRQ_CTRL 0x2a004	/* Interrupt source mask. */

//#घोषणा VORTEX_IRQ_U0 0x2a008 /* ?? */
#घोषणा VORTEX_STAT		0x2a008	/* Some sort of status */
#घोषणा 	STAT_IRQ	0x00000001	/* This bitis set अगर the IRQ is valid. */

#घोषणा VORTEX_CTRL		0x2a00c
#घोषणा 	CTRL_MIDI_EN	0x00000001
#घोषणा 	CTRL_MIDI_PORT	0x00000060
#घोषणा 	CTRL_GAME_EN	0x00000008
#घोषणा 	CTRL_GAME_PORT	0x00000e00
#घोषणा 	CTRL_IRQ_ENABLE	0x00004000
#घोषणा		CTRL_SPDIF		0x00000000	/* unknown. Please find this value */
#घोषणा 	CTRL_SPORT		0x00200000
#घोषणा 	CTRL_RST		0x00800000
#घोषणा 	CTRL_UNKNOWN	0x01000000

/* ग_लिखो: Timer period config / पढ़ो: TIMER IRQ ack. */
#घोषणा VORTEX_IRQ_STAT 0x2919c

		     /* MIDI *//* GAME. */
#घोषणा VORTEX_MIDI_DATA 0x28800
#घोषणा VORTEX_MIDI_CMD 0x28804	/* Write command / Read status */

#घोषणा VORTEX_GAME_LEGACY 0x28808
#घोषणा VORTEX_CTRL2 0x2880c
#घोषणा		CTRL2_GAME_ADCMODE 0x40
#घोषणा VORTEX_GAME_AXIS 0x28810	/* Axis base रेजिस्टर. 4 axis's */
#घोषणा		AXIS_SIZE 4
#घोषणा		AXIS_RANGE 0x1fff
