<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// siu.h - ALSA SoC driver क्रम Renesas SH7343, SH7722 SIU peripheral.
//
// Copyright (C) 2009-2010 Guennadi Liakhovetski <g.liakhovetski@gmx.de>
// Copyright (C) 2006 Carlos Munoz <carlos@kenati.com>

#अगर_अघोषित SIU_H
#घोषणा SIU_H

/* Common kernel and user-space firmware-building defines and types */

#घोषणा YRAM0_SIZE		(0x0040 / 4)		/* 16 */
#घोषणा YRAM1_SIZE		(0x0080 / 4)		/* 32 */
#घोषणा YRAM2_SIZE		(0x0040 / 4)		/* 16 */
#घोषणा YRAM3_SIZE		(0x0080 / 4)		/* 32 */
#घोषणा YRAM4_SIZE		(0x0080 / 4)		/* 32 */
#घोषणा YRAM_DEF_SIZE		(YRAM0_SIZE + YRAM1_SIZE + YRAM2_SIZE + \
				 YRAM3_SIZE + YRAM4_SIZE)
#घोषणा YRAM_FIR_SIZE		(0x0400 / 4)		/* 256 */
#घोषणा YRAM_IIR_SIZE		(0x0200 / 4)		/* 128 */

#घोषणा XRAM0_SIZE		(0x0400 / 4)		/* 256 */
#घोषणा XRAM1_SIZE		(0x0200 / 4)		/* 128 */
#घोषणा XRAM2_SIZE		(0x0200 / 4)		/* 128 */

/* PRAM program array size */
#घोषणा PRAM0_SIZE		(0x0100 / 4)		/* 64 */
#घोषणा PRAM1_SIZE		((0x2000 - 0x0100) / 4)	/* 1984 */

#समावेश <linux/types.h>

काष्ठा siu_spb_param अणु
	__u32	ab1a;	/* input FIFO address */
	__u32	ab0a;	/* output FIFO address */
	__u32	dir;	/* 0=the ather except CPUOUTPUT, 1=CPUINPUT */
	__u32	event;	/* SPB program starting conditions */
	__u32	stfअगरo;	/* STFIFO रेजिस्टर setting value */
	__u32	trdat;	/* TRDAT रेजिस्टर setting value */
पूर्ण;

काष्ठा siu_firmware अणु
	__u32			yram_fir_coeff[YRAM_FIR_SIZE];
	__u32			pram0[PRAM0_SIZE];
	__u32			pram1[PRAM1_SIZE];
	__u32			yram0[YRAM0_SIZE];
	__u32			yram1[YRAM1_SIZE];
	__u32			yram2[YRAM2_SIZE];
	__u32			yram3[YRAM3_SIZE];
	__u32			yram4[YRAM4_SIZE];
	__u32			spbpar_num;
	काष्ठा siu_spb_param	spbpar[32];
पूर्ण;

#अगर_घोषित __KERNEL__

#समावेश <linux/dmaengine.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/sh_dma.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>

#घोषणा SIU_PERIOD_BYTES_MAX	8192		/* DMA transfer/period size */
#घोषणा SIU_PERIOD_BYTES_MIN	256		/* DMA transfer/period size */
#घोषणा SIU_PERIODS_MAX		64		/* Max periods in buffer */
#घोषणा SIU_PERIODS_MIN		4		/* Min periods in buffer */
#घोषणा SIU_BUFFER_BYTES_MAX	(SIU_PERIOD_BYTES_MAX * SIU_PERIODS_MAX)

/* SIU ports: only one can be used at a समय */
क्रमागत अणु
	SIU_PORT_A,
	SIU_PORT_B,
	SIU_PORT_NUM,
पूर्ण;

/* SIU घड़ी configuration */
क्रमागत अणु
	SIU_CLKA_PLL,
	SIU_CLKA_EXT,
	SIU_CLKB_PLL,
	SIU_CLKB_EXT
पूर्ण;

काष्ठा device;
काष्ठा siu_info अणु
	काष्ठा device		*dev;
	पूर्णांक			port_id;
	u32 __iomem		*pram;
	u32 __iomem		*xram;
	u32 __iomem		*yram;
	u32 __iomem		*reg;
	काष्ठा siu_firmware	fw;
पूर्ण;

काष्ठा siu_stream अणु
	काष्ठा work_काष्ठा		work;
	काष्ठा snd_pcm_substream	*substream;
	snd_pcm_क्रमmat_t		क्रमmat;
	माप_प्रकार				buf_bytes;
	माप_प्रकार				period_bytes;
	पूर्णांक				cur_period;	/* Period currently in dma */
	u32				volume;
	snd_pcm_sframes_t		xfer_cnt;	/* Number of frames */
	u8				rw_flg;		/* transfer status */
	/* DMA status */
	काष्ठा dma_chan			*chan;		/* DMA channel */
	काष्ठा dma_async_tx_descriptor	*tx_desc;
	dma_cookie_t			cookie;
	काष्ठा sh_dmae_slave		param;
पूर्ण;

काष्ठा siu_port अणु
	अचिन्हित दीर्घ		play_cap;	/* Used to track full duplex */
	काष्ठा snd_pcm		*pcm;
	काष्ठा siu_stream	playback;
	काष्ठा siu_stream	capture;
	u32			stfअगरo;		/* STFIFO value from firmware */
	u32			trdat;		/* TRDAT value from firmware */
पूर्ण;

बाह्य काष्ठा siu_port *siu_ports[SIU_PORT_NUM];

अटल अंतरभूत काष्ठा siu_port *siu_port_info(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा platक्रमm_device *pdev =
		to_platक्रमm_device(substream->pcm->card->dev);
	वापस siu_ports[pdev->id];
पूर्ण

/* Register access */
अटल अंतरभूत व्योम siu_ग_लिखो32(u32 __iomem *addr, u32 val)
अणु
	__raw_ग_लिखोl(val, addr);
पूर्ण

अटल अंतरभूत u32 siu_पढ़ो32(u32 __iomem *addr)
अणु
	वापस __raw_पढ़ोl(addr);
पूर्ण

/* SIU रेजिस्टरs */
#घोषणा SIU_IFCTL	(0x000 / माप(u32))
#घोषणा SIU_SRCTL	(0x004 / माप(u32))
#घोषणा SIU_SFORM	(0x008 / माप(u32))
#घोषणा SIU_CKCTL	(0x00c / माप(u32))
#घोषणा SIU_TRDAT	(0x010 / माप(u32))
#घोषणा SIU_STFIFO	(0x014 / माप(u32))
#घोषणा SIU_DPAK	(0x01c / माप(u32))
#घोषणा SIU_CKREV	(0x020 / माप(u32))
#घोषणा SIU_EVNTC	(0x028 / माप(u32))
#घोषणा SIU_SBCTL	(0x040 / माप(u32))
#घोषणा SIU_SBPSET	(0x044 / माप(u32))
#घोषणा SIU_SBFSTS	(0x068 / माप(u32))
#घोषणा SIU_SBDVCA	(0x06c / माप(u32))
#घोषणा SIU_SBDVCB	(0x070 / माप(u32))
#घोषणा SIU_SBACTIV	(0x074 / माप(u32))
#घोषणा SIU_DMAIA	(0x090 / माप(u32))
#घोषणा SIU_DMAIB	(0x094 / माप(u32))
#घोषणा SIU_DMAOA	(0x098 / माप(u32))
#घोषणा SIU_DMAOB	(0x09c / माप(u32))
#घोषणा SIU_DMAML	(0x0a0 / माप(u32))
#घोषणा SIU_SPSTS	(0x0cc / माप(u32))
#घोषणा SIU_SPCTL	(0x0d0 / माप(u32))
#घोषणा SIU_BRGASEL	(0x100 / माप(u32))
#घोषणा SIU_BRRA	(0x104 / माप(u32))
#घोषणा SIU_BRGBSEL	(0x108 / माप(u32))
#घोषणा SIU_BRRB	(0x10c / माप(u32))

बाह्य स्थिर काष्ठा snd_soc_component_driver siu_component;
बाह्य काष्ठा siu_info *siu_i2s_data;

पूर्णांक siu_init_port(पूर्णांक port, काष्ठा siu_port **port_info, काष्ठा snd_card *card);
व्योम siu_मुक्त_port(काष्ठा siu_port *port_info);

#पूर्ण_अगर

#पूर्ण_अगर /* SIU_H */
