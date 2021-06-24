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

#घोषणा CHIP_AU8820

#घोषणा CARD_NAME "Aureal Vortex"
#घोषणा CARD_NAME_SHORT "au8820"

/* Number of ADB and WT channels */
#घोषणा NR_ADB		0x10
#घोषणा NR_WT		0x20
#घोषणा NR_SRC		0x10
#घोषणा NR_A3D		0x00
#घोषणा NR_MIXIN	0x10
#घोषणा NR_MIXOUT 	0x10


/* ADBDMA */
#घोषणा VORTEX_ADBDMA_STAT 0x105c0	/* पढ़ो only, subbuffer, DMA pos */
#घोषणा		POS_MASK 0x00000fff
#घोषणा     POS_SHIFT 0x0
#घोषणा 	ADB_SUBBUF_MASK 0x00003000	/* ADB only. */
#घोषणा     ADB_SUBBUF_SHIFT 0xc	/* ADB only. */
#घोषणा VORTEX_ADBDMA_CTRL 0x10580	/* ग_लिखो only, क्रमmat, flags, DMA pos */
#घोषणा		OFFSET_MASK 0x00000fff
#घोषणा     OFFSET_SHIFT 0x0
#घोषणा		IE_MASK 0x00001000	/* पूर्णांकerrupt enable. */
#घोषणा     IE_SHIFT 0xc
#घोषणा     सूची_MASK 0x00002000	/* Direction. */
#घोषणा     सूची_SHIFT 0xd
#घोषणा		FMT_MASK 0x0003c000
#घोषणा		FMT_SHIFT 0xe
// The masks and shअगरt also work क्रम the wtdma, अगर not specअगरied otherwise.
#घोषणा VORTEX_ADBDMA_BUFCFG0 0x10400
#घोषणा VORTEX_ADBDMA_BUFCFG1 0x10404
#घोषणा VORTEX_ADBDMA_BUFBASE 0x10200
#घोषणा VORTEX_ADBDMA_START 0x106c0	/* Which subbuffer starts */
#घोषणा VORTEX_ADBDMA_STATUS 0x10600	/* stored at AdbDma->this_10 / 2 DWORD in size. */

/* ADB */
#घोषणा VORTEX_ADB_SR 0x10a00	/* Samplerates enable/disable */
#घोषणा VORTEX_ADB_RTBASE 0x10800
#घोषणा VORTEX_ADB_RTBASE_COUNT 103
#घोषणा VORTEX_ADB_CHNBASE 0x1099c
#घोषणा VORTEX_ADB_CHNBASE_COUNT 22
#घोषणा 	ROUTE_MASK	0x3fff
#घोषणा     ADB_MASK   0x7f
#घोषणा		ADB_SHIFT 0x7
//#घोषणा     ADB_MIX_MASK 0xf
/* ADB address */
#घोषणा		OFFSET_ADBDMA	0x00
#घोषणा		OFFSET_SRCOUT	0x10	/* on channel 0x11 */
#घोषणा		OFFSET_SRCIN	0x10	/* on channel < 0x11 */
#घोषणा		OFFSET_MIXOUT	0x20	/* source */
#घोषणा		OFFSET_MIXIN	0x30	/* sink */
#घोषणा		OFFSET_CODECIN	0x48	/* ADB source */
#घोषणा		OFFSET_CODECOUT	0x58	/* ADB sink/target */
#घोषणा		OFFSET_SPORTOUT	0x60	/* sink */
#घोषणा		OFFSET_SPORTIN	0x50	/* source */
#घोषणा		OFFSET_EFXOUT	0x50	/* sink */
#घोषणा		OFFSET_EFXIN	0x40	/* source */
#घोषणा		OFFSET_A3DOUT	0x00	/* This card has no HRTF :( */
#घोषणा		OFFSET_A3DIN	0x00
#घोषणा		OFFSET_WTOUT	0x58	/*  */

/* ADB route translate helper */
#घोषणा ADB_DMA(x) (x + OFFSET_ADBDMA)
#घोषणा ADB_SRCOUT(x) (x + OFFSET_SRCOUT)
#घोषणा ADB_SRCIN(x) (x + OFFSET_SRCIN)
#घोषणा ADB_MIXOUT(x) (x + OFFSET_MIXOUT)
#घोषणा ADB_MIXIN(x) (x + OFFSET_MIXIN)
#घोषणा ADB_CODECIN(x) (x + OFFSET_CODECIN)
#घोषणा ADB_CODECOUT(x) (x + OFFSET_CODECOUT)
#घोषणा ADB_SPORTOUT(x) (x + OFFSET_SPORTOUT)
#घोषणा ADB_SPORTIN(x) (x + OFFSET_SPORTIN)	/*  */
#घोषणा ADB_A3DOUT(x) (x + OFFSET_A3DOUT)	/* 8 A3D blocks */
#घोषणा ADB_A3DIN(x) (x + OFFSET_A3DIN)
#घोषणा ADB_WTOUT(x,y) (y + OFFSET_WTOUT)

/* WTDMA */
#घोषणा VORTEX_WTDMA_CTRL 0x10500	/* क्रमmat, DMA pos */
#घोषणा VORTEX_WTDMA_STAT 0x10500	/* DMA subbuf, DMA pos */
#घोषणा     WT_SUBBUF_MASK (0x3 << WT_SUBBUF_SHIFT)
#घोषणा     WT_SUBBUF_SHIFT 0x15
#घोषणा VORTEX_WTDMA_BUFBASE 0x10000
#घोषणा VORTEX_WTDMA_BUFCFG0 0x10300
#घोषणा VORTEX_WTDMA_BUFCFG1 0x10304
#घोषणा VORTEX_WTDMA_START 0x10640	/* which subbuffer is first */

#घोषणा VORTEX_WT_BASE 0x9000

/* MIXER */
#घोषणा VORTEX_MIXER_SR 0x9f00
#घोषणा VORTEX_MIXER_CLIP 0x9f80
#घोषणा VORTEX_MIXER_CHNBASE 0x9e40
#घोषणा VORTEX_MIXER_RTBASE 0x9e00
#घोषणा 	MIXER_RTBASE_SIZE 0x26
#घोषणा VORTEX_MIX_ENIN 0x9a00	/* Input enable bits. 4 bits wide. */
#घोषणा VORTEX_MIX_SMP 0x9c00

/* MIX */
#घोषणा VORTEX_MIX_INVOL_A 0x9000	/* in? */
#घोषणा VORTEX_MIX_INVOL_B 0x8000	/* out? */
#घोषणा VORTEX_MIX_VOL_A 0x9800
#घोषणा VORTEX_MIX_VOL_B 0x8800

#घोषणा 	VOL_MIN 0x80	/* Input volume when muted. */
#घोषणा		VOL_MAX 0x7f	/* FIXME: Not confirmed! Just guessed. */

//#घोषणा MIX_OUTL    0xe
//#घोषणा MIX_OUTR    0xf
//#घोषणा MIX_INL     0xe
//#घोषणा MIX_INR     0xf
#घोषणा MIX_DEFIGAIN 0x08	/* 0x8 => 6dB */
#घोषणा MIX_DEFOGAIN 0x08

/* SRC */
#घोषणा VORTEX_SRCBLOCK_SR	0xccc0
#घोषणा VORTEX_SRC_CHNBASE	0xcc40
#घोषणा VORTEX_SRC_RTBASE	0xcc00
#घोषणा VORTEX_SRC_SOURCE	0xccc4
#घोषणा VORTEX_SRC_SOURCESIZE 0xccc8
#घोषणा VORTEX_SRC_U0		0xce00
#घोषणा VORTEX_SRC_DRIFT0	0xce80
#घोषणा VORTEX_SRC_DRIFT1	0xcec0
#घोषणा VORTEX_SRC_U1		0xcf00
#घोषणा VORTEX_SRC_DRIFT2	0xcf40
#घोषणा VORTEX_SRC_U2		0xcf80
#घोषणा VORTEX_SRC_DATA		0xc800
#घोषणा VORTEX_SRC_DATA0	0xc000
#घोषणा VORTEX_SRC_CONVRATIO 0xce40
//#घोषणा     SRC_RATIO(x) ((((x<<15)/48000) + 1)/2) /* Playback */
//#घोषणा     SRC_RATIO2(x) ((((48000<<15)/x) + 1)/2) /* Recording */

/* FIFO */
#घोषणा VORTEX_FIFO_ADBCTRL 0xf800	/* Control bits. */
#घोषणा VORTEX_FIFO_WTCTRL 0xf840
#घोषणा		FIFO_RDONLY	0x00000001
#घोषणा		FIFO_CTRL	0x00000002	/* Allow ctrl. ? */
#घोषणा		FIFO_VALID	0x00000010
#घोषणा 	FIFO_EMPTY	0x00000020
#घोषणा		FIFO_U0		0x00001000	/* Unknown. */
#घोषणा		FIFO_U1		0x00010000
#घोषणा		FIFO_SIZE_BITS 5
#घोषणा		FIFO_SIZE	(1<<FIFO_SIZE_BITS)	// 0x20
#घोषणा 	FIFO_MASK	(FIFO_SIZE-1)	//0x1f    /* at shअगरt left 0xc */
#घोषणा VORTEX_FIFO_ADBDATA 0xe000
#घोषणा VORTEX_FIFO_WTDATA 0xe800

/* CODEC */
#घोषणा VORTEX_CODEC_CTRL 0x11984
#घोषणा VORTEX_CODEC_EN 0x11990
#घोषणा		EN_CODEC	0x00000300
#घोषणा		EN_SPORT	0x00030000
#घोषणा		EN_SPDIF	0x000c0000
#घोषणा VORTEX_CODEC_CHN 0x11880
#घोषणा VORTEX_CODEC_IO 0x11988

#घोषणा VORTEX_SPDIF_FLAGS		0x1005c	/* FIXME */
#घोषणा VORTEX_SPDIF_CFG0		0x119D0
#घोषणा VORTEX_SPDIF_CFG1		0x119D4
#घोषणा VORTEX_SPDIF_SMPRATE	0x11994

/* Sample समयr */
#घोषणा VORTEX_SMP_TIME 0x11998

/* IRQ */
#घोषणा VORTEX_IRQ_SOURCE 0x12800	/* Interrupt source flags. */
#घोषणा VORTEX_IRQ_CTRL 0x12804	/* Interrupt source mask. */

#घोषणा VORTEX_STAT		0x12808	/* ?? */

#घोषणा VORTEX_CTRL 0x1280c
#घोषणा 	CTRL_MIDI_EN 0x00000001
#घोषणा 	CTRL_MIDI_PORT 0x00000060
#घोषणा 	CTRL_GAME_EN 0x00000008
#घोषणा 	CTRL_GAME_PORT 0x00000e00
#घोषणा 	CTRL_IRQ_ENABLE 0x4000

/* ग_लिखो: Timer period config / पढ़ो: TIMER IRQ ack. */
#घोषणा VORTEX_IRQ_STAT 0x1199c

/* DMA */
#घोषणा VORTEX_DMA_BUFFER 0x10200
#घोषणा VORTEX_ENGINE_CTRL 0x1060c
#घोषणा 	ENGINE_INIT 0x0L

		     /* MIDI *//* GAME. */
#घोषणा VORTEX_MIDI_DATA 0x11000
#घोषणा VORTEX_MIDI_CMD 0x11004	/* Write command / Read status */
#घोषणा VORTEX_GAME_LEGACY 0x11008
#घोषणा VORTEX_CTRL2 0x1100c
#घोषणा 	CTRL2_GAME_ADCMODE 0x40
#घोषणा VORTEX_GAME_AXIS 0x11010
#घोषणा 	AXIS_SIZE 4
#घोषणा		AXIS_RANGE 0x1fff
