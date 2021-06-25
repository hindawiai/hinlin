<शैली गुरु>
/*
 * Copyright (C) 2014-2015 Broadcom Corporation
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */
#समावेश <linux/debugfs.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/समयr.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dai.h>

#समावेश "cygnus-ssp.h"

/* Register offset needed क्रम ASoC PCM module */

#घोषणा INTH_R5F_STATUS_OFFSET     0x040
#घोषणा INTH_R5F_CLEAR_OFFSET      0x048
#घोषणा INTH_R5F_MASK_SET_OFFSET   0x050
#घोषणा INTH_R5F_MASK_CLEAR_OFFSET 0x054

#घोषणा BF_REARM_FREE_MARK_OFFSET 0x344
#घोषणा BF_REARM_FULL_MARK_OFFSET 0x348

/* Ring Buffer Ctrl Regs --- Start */
/* AUD_FMM_BF_CTRL_SOURCECH_RINGBUF_X_RDADDR_REG_BASE */
#घोषणा SRC_RBUF_0_RDADDR_OFFSET 0x500
#घोषणा SRC_RBUF_1_RDADDR_OFFSET 0x518
#घोषणा SRC_RBUF_2_RDADDR_OFFSET 0x530
#घोषणा SRC_RBUF_3_RDADDR_OFFSET 0x548
#घोषणा SRC_RBUF_4_RDADDR_OFFSET 0x560
#घोषणा SRC_RBUF_5_RDADDR_OFFSET 0x578
#घोषणा SRC_RBUF_6_RDADDR_OFFSET 0x590

/* AUD_FMM_BF_CTRL_SOURCECH_RINGBUF_X_WRADDR_REG_BASE */
#घोषणा SRC_RBUF_0_WRADDR_OFFSET 0x504
#घोषणा SRC_RBUF_1_WRADDR_OFFSET 0x51c
#घोषणा SRC_RBUF_2_WRADDR_OFFSET 0x534
#घोषणा SRC_RBUF_3_WRADDR_OFFSET 0x54c
#घोषणा SRC_RBUF_4_WRADDR_OFFSET 0x564
#घोषणा SRC_RBUF_5_WRADDR_OFFSET 0x57c
#घोषणा SRC_RBUF_6_WRADDR_OFFSET 0x594

/* AUD_FMM_BF_CTRL_SOURCECH_RINGBUF_X_BASEADDR_REG_BASE */
#घोषणा SRC_RBUF_0_BASEADDR_OFFSET 0x508
#घोषणा SRC_RBUF_1_BASEADDR_OFFSET 0x520
#घोषणा SRC_RBUF_2_BASEADDR_OFFSET 0x538
#घोषणा SRC_RBUF_3_BASEADDR_OFFSET 0x550
#घोषणा SRC_RBUF_4_BASEADDR_OFFSET 0x568
#घोषणा SRC_RBUF_5_BASEADDR_OFFSET 0x580
#घोषणा SRC_RBUF_6_BASEADDR_OFFSET 0x598

/* AUD_FMM_BF_CTRL_SOURCECH_RINGBUF_X_ENDADDR_REG_BASE */
#घोषणा SRC_RBUF_0_ENDADDR_OFFSET 0x50c
#घोषणा SRC_RBUF_1_ENDADDR_OFFSET 0x524
#घोषणा SRC_RBUF_2_ENDADDR_OFFSET 0x53c
#घोषणा SRC_RBUF_3_ENDADDR_OFFSET 0x554
#घोषणा SRC_RBUF_4_ENDADDR_OFFSET 0x56c
#घोषणा SRC_RBUF_5_ENDADDR_OFFSET 0x584
#घोषणा SRC_RBUF_6_ENDADDR_OFFSET 0x59c

/* AUD_FMM_BF_CTRL_SOURCECH_RINGBUF_X_FREE_MARK_REG_BASE */
#घोषणा SRC_RBUF_0_FREE_MARK_OFFSET 0x510
#घोषणा SRC_RBUF_1_FREE_MARK_OFFSET 0x528
#घोषणा SRC_RBUF_2_FREE_MARK_OFFSET 0x540
#घोषणा SRC_RBUF_3_FREE_MARK_OFFSET 0x558
#घोषणा SRC_RBUF_4_FREE_MARK_OFFSET 0x570
#घोषणा SRC_RBUF_5_FREE_MARK_OFFSET 0x588
#घोषणा SRC_RBUF_6_FREE_MARK_OFFSET 0x5a0

/* AUD_FMM_BF_CTRL_DESTCH_RINGBUF_X_RDADDR_REG_BASE */
#घोषणा DST_RBUF_0_RDADDR_OFFSET 0x5c0
#घोषणा DST_RBUF_1_RDADDR_OFFSET 0x5d8
#घोषणा DST_RBUF_2_RDADDR_OFFSET 0x5f0
#घोषणा DST_RBUF_3_RDADDR_OFFSET 0x608
#घोषणा DST_RBUF_4_RDADDR_OFFSET 0x620
#घोषणा DST_RBUF_5_RDADDR_OFFSET 0x638

/* AUD_FMM_BF_CTRL_DESTCH_RINGBUF_X_WRADDR_REG_BASE */
#घोषणा DST_RBUF_0_WRADDR_OFFSET 0x5c4
#घोषणा DST_RBUF_1_WRADDR_OFFSET 0x5dc
#घोषणा DST_RBUF_2_WRADDR_OFFSET 0x5f4
#घोषणा DST_RBUF_3_WRADDR_OFFSET 0x60c
#घोषणा DST_RBUF_4_WRADDR_OFFSET 0x624
#घोषणा DST_RBUF_5_WRADDR_OFFSET 0x63c

/* AUD_FMM_BF_CTRL_DESTCH_RINGBUF_X_BASEADDR_REG_BASE */
#घोषणा DST_RBUF_0_BASEADDR_OFFSET 0x5c8
#घोषणा DST_RBUF_1_BASEADDR_OFFSET 0x5e0
#घोषणा DST_RBUF_2_BASEADDR_OFFSET 0x5f8
#घोषणा DST_RBUF_3_BASEADDR_OFFSET 0x610
#घोषणा DST_RBUF_4_BASEADDR_OFFSET 0x628
#घोषणा DST_RBUF_5_BASEADDR_OFFSET 0x640

/* AUD_FMM_BF_CTRL_DESTCH_RINGBUF_X_ENDADDR_REG_BASE */
#घोषणा DST_RBUF_0_ENDADDR_OFFSET 0x5cc
#घोषणा DST_RBUF_1_ENDADDR_OFFSET 0x5e4
#घोषणा DST_RBUF_2_ENDADDR_OFFSET 0x5fc
#घोषणा DST_RBUF_3_ENDADDR_OFFSET 0x614
#घोषणा DST_RBUF_4_ENDADDR_OFFSET 0x62c
#घोषणा DST_RBUF_5_ENDADDR_OFFSET 0x644

/* AUD_FMM_BF_CTRL_DESTCH_RINGBUF_X_FULL_MARK_REG_BASE */
#घोषणा DST_RBUF_0_FULL_MARK_OFFSET 0x5d0
#घोषणा DST_RBUF_1_FULL_MARK_OFFSET 0x5e8
#घोषणा DST_RBUF_2_FULL_MARK_OFFSET 0x600
#घोषणा DST_RBUF_3_FULL_MARK_OFFSET 0x618
#घोषणा DST_RBUF_4_FULL_MARK_OFFSET 0x630
#घोषणा DST_RBUF_5_FULL_MARK_OFFSET 0x648
/* Ring Buffer Ctrl Regs --- End */

/* Error Status Regs --- Start */
/* AUD_FMM_BF_ESR_ESRX_STATUS_REG_BASE */
#घोषणा ESR0_STATUS_OFFSET 0x900
#घोषणा ESR1_STATUS_OFFSET 0x918
#घोषणा ESR2_STATUS_OFFSET 0x930
#घोषणा ESR3_STATUS_OFFSET 0x948
#घोषणा ESR4_STATUS_OFFSET 0x960

/* AUD_FMM_BF_ESR_ESRX_STATUS_CLEAR_REG_BASE */
#घोषणा ESR0_STATUS_CLR_OFFSET 0x908
#घोषणा ESR1_STATUS_CLR_OFFSET 0x920
#घोषणा ESR2_STATUS_CLR_OFFSET 0x938
#घोषणा ESR3_STATUS_CLR_OFFSET 0x950
#घोषणा ESR4_STATUS_CLR_OFFSET 0x968

/* AUD_FMM_BF_ESR_ESRX_MASK_REG_BASE */
#घोषणा ESR0_MASK_STATUS_OFFSET 0x90c
#घोषणा ESR1_MASK_STATUS_OFFSET 0x924
#घोषणा ESR2_MASK_STATUS_OFFSET 0x93c
#घोषणा ESR3_MASK_STATUS_OFFSET 0x954
#घोषणा ESR4_MASK_STATUS_OFFSET 0x96c

/* AUD_FMM_BF_ESR_ESRX_MASK_SET_REG_BASE */
#घोषणा ESR0_MASK_SET_OFFSET 0x910
#घोषणा ESR1_MASK_SET_OFFSET 0x928
#घोषणा ESR2_MASK_SET_OFFSET 0x940
#घोषणा ESR3_MASK_SET_OFFSET 0x958
#घोषणा ESR4_MASK_SET_OFFSET 0x970

/* AUD_FMM_BF_ESR_ESRX_MASK_CLEAR_REG_BASE */
#घोषणा ESR0_MASK_CLR_OFFSET 0x914
#घोषणा ESR1_MASK_CLR_OFFSET 0x92c
#घोषणा ESR2_MASK_CLR_OFFSET 0x944
#घोषणा ESR3_MASK_CLR_OFFSET 0x95c
#घोषणा ESR4_MASK_CLR_OFFSET 0x974
/* Error Status Regs --- End */

#घोषणा R5F_ESR0_SHIFT  0    /* esr0 = fअगरo underflow */
#घोषणा R5F_ESR1_SHIFT  1    /* esr1 = ringbuf underflow */
#घोषणा R5F_ESR2_SHIFT  2    /* esr2 = ringbuf overflow */
#घोषणा R5F_ESR3_SHIFT  3    /* esr3 = मुक्तmark */
#घोषणा R5F_ESR4_SHIFT  4    /* esr4 = fullmark */


/* Mask क्रम R5F रेजिस्टर.  Set all relevant पूर्णांकerrupt क्रम playback handler */
#घोषणा ANY_PLAYBACK_IRQ  (BIT(R5F_ESR0_SHIFT) | \
			   BIT(R5F_ESR1_SHIFT) | \
			   BIT(R5F_ESR3_SHIFT))

/* Mask क्रम R5F रेजिस्टर.  Set all relevant पूर्णांकerrupt क्रम capture handler */
#घोषणा ANY_CAPTURE_IRQ   (BIT(R5F_ESR2_SHIFT) | BIT(R5F_ESR4_SHIFT))

/*
 * PERIOD_BYTES_MIN is the number of bytes to at which the पूर्णांकerrupt will tick.
 * This number should be a multiple of 256. Minimum value is 256
 */
#घोषणा PERIOD_BYTES_MIN 0x100

अटल स्थिर काष्ठा snd_pcm_hardware cygnus_pcm_hw = अणु
	.info = SNDRV_PCM_INFO_MMAP |
			SNDRV_PCM_INFO_MMAP_VALID |
			SNDRV_PCM_INFO_INTERLEAVED,
	.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |
			SNDRV_PCM_FMTBIT_S32_LE,

	/* A period is basically an पूर्णांकerrupt */
	.period_bytes_min = PERIOD_BYTES_MIN,
	.period_bytes_max = 0x10000,

	/* period_min/max gives range of approx पूर्णांकerrupts per buffer */
	.periods_min = 2,
	.periods_max = 8,

	/*
	 * maximum buffer size in bytes = period_bytes_max * periods_max
	 * We allocate this amount of data क्रम each enabled channel
	 */
	.buffer_bytes_max = 4 * 0x8000,
पूर्ण;

अटल u64 cygnus_dma_dmamask = DMA_BIT_MASK(32);

अटल काष्ठा cygnus_aio_port *cygnus_dai_get_dma_data(
				काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *soc_runसमय = asoc_substream_to_rtd(substream);

	वापस snd_soc_dai_get_dma_data(asoc_rtd_to_cpu(soc_runसमय, 0), substream);
पूर्ण

अटल व्योम ringbuf_set_initial(व्योम __iomem *audio_io,
		काष्ठा ringbuf_regs *p_rbuf,
		bool is_playback,
		u32 start,
		u32 periodsize,
		u32 bufsize)
अणु
	u32 initial_rd;
	u32 initial_wr;
	u32 end;
	u32 fmark_val; /* मुक्त or full mark */

	p_rbuf->period_bytes = periodsize;
	p_rbuf->buf_size = bufsize;

	अगर (is_playback) अणु
		/* Set the poपूर्णांकers to indicate full (flip uppermost bit) */
		initial_rd = start;
		initial_wr = initial_rd ^ BIT(31);
	पूर्ण अन्यथा अणु
		/* Set the poपूर्णांकers to indicate empty */
		initial_wr = start;
		initial_rd = initial_wr;
	पूर्ण

	end = start + bufsize - 1;

	/*
	 * The पूर्णांकerrupt will fire when मुक्त/full mark is *exceeded*
	 * The fmark value must be multiple of PERIOD_BYTES_MIN so set fmark
	 * to be PERIOD_BYTES_MIN less than the period size.
	 */
	fmark_val = periodsize - PERIOD_BYTES_MIN;

	ग_लिखोl(start, audio_io + p_rbuf->baseaddr);
	ग_लिखोl(end, audio_io + p_rbuf->endaddr);
	ग_लिखोl(fmark_val, audio_io + p_rbuf->fmark);
	ग_लिखोl(initial_rd, audio_io + p_rbuf->rdaddr);
	ग_लिखोl(initial_wr, audio_io + p_rbuf->wraddr);
पूर्ण

अटल पूर्णांक configure_ringbuf_regs(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा cygnus_aio_port *aio;
	काष्ठा ringbuf_regs *p_rbuf;
	पूर्णांक status = 0;

	aio = cygnus_dai_get_dma_data(substream);

	/* Map the ssp portnum to a set of ring buffers. */
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		p_rbuf = &aio->play_rb_regs;

		चयन (aio->portnum) अणु
		हाल 0:
			*p_rbuf = RINGBUF_REG_PLAYBACK(0);
			अवरोध;
		हाल 1:
			*p_rbuf = RINGBUF_REG_PLAYBACK(2);
			अवरोध;
		हाल 2:
			*p_rbuf = RINGBUF_REG_PLAYBACK(4);
			अवरोध;
		हाल 3: /* SPDIF */
			*p_rbuf = RINGBUF_REG_PLAYBACK(6);
			अवरोध;
		शेष:
			status = -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		p_rbuf = &aio->capture_rb_regs;

		चयन (aio->portnum) अणु
		हाल 0:
			*p_rbuf = RINGBUF_REG_CAPTURE(0);
			अवरोध;
		हाल 1:
			*p_rbuf = RINGBUF_REG_CAPTURE(2);
			अवरोध;
		हाल 2:
			*p_rbuf = RINGBUF_REG_CAPTURE(4);
			अवरोध;
		शेष:
			status = -EINVAL;
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण

अटल काष्ठा ringbuf_regs *get_ringbuf(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा cygnus_aio_port *aio;
	काष्ठा ringbuf_regs *p_rbuf = शून्य;

	aio = cygnus_dai_get_dma_data(substream);

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		p_rbuf = &aio->play_rb_regs;
	अन्यथा
		p_rbuf = &aio->capture_rb_regs;

	वापस p_rbuf;
पूर्ण

अटल व्योम enable_पूर्णांकr(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा cygnus_aio_port *aio;
	u32 clear_mask;

	aio = cygnus_dai_get_dma_data(substream);

	/* The port number maps to the bit position to be cleared */
	clear_mask = BIT(aio->portnum);

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		/* Clear पूर्णांकerrupt status beक्रमe enabling them */
		ग_लिखोl(clear_mask, aio->cygaud->audio + ESR0_STATUS_CLR_OFFSET);
		ग_लिखोl(clear_mask, aio->cygaud->audio + ESR1_STATUS_CLR_OFFSET);
		ग_लिखोl(clear_mask, aio->cygaud->audio + ESR3_STATUS_CLR_OFFSET);
		/* Unmask the पूर्णांकerrupts of the given port*/
		ग_लिखोl(clear_mask, aio->cygaud->audio + ESR0_MASK_CLR_OFFSET);
		ग_लिखोl(clear_mask, aio->cygaud->audio + ESR1_MASK_CLR_OFFSET);
		ग_लिखोl(clear_mask, aio->cygaud->audio + ESR3_MASK_CLR_OFFSET);

		ग_लिखोl(ANY_PLAYBACK_IRQ,
			aio->cygaud->audio + INTH_R5F_MASK_CLEAR_OFFSET);
	पूर्ण अन्यथा अणु
		ग_लिखोl(clear_mask, aio->cygaud->audio + ESR2_STATUS_CLR_OFFSET);
		ग_लिखोl(clear_mask, aio->cygaud->audio + ESR4_STATUS_CLR_OFFSET);
		ग_लिखोl(clear_mask, aio->cygaud->audio + ESR2_MASK_CLR_OFFSET);
		ग_लिखोl(clear_mask, aio->cygaud->audio + ESR4_MASK_CLR_OFFSET);

		ग_लिखोl(ANY_CAPTURE_IRQ,
			aio->cygaud->audio + INTH_R5F_MASK_CLEAR_OFFSET);
	पूर्ण

पूर्ण

अटल व्योम disable_पूर्णांकr(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा cygnus_aio_port *aio;
	u32 set_mask;

	aio = cygnus_dai_get_dma_data(substream);

	dev_dbg(asoc_rtd_to_cpu(rtd, 0)->dev, "%s on port %d\n", __func__, aio->portnum);

	/* The port number maps to the bit position to be set */
	set_mask = BIT(aio->portnum);

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		/* Mask the पूर्णांकerrupts of the given port*/
		ग_लिखोl(set_mask, aio->cygaud->audio + ESR0_MASK_SET_OFFSET);
		ग_लिखोl(set_mask, aio->cygaud->audio + ESR1_MASK_SET_OFFSET);
		ग_लिखोl(set_mask, aio->cygaud->audio + ESR3_MASK_SET_OFFSET);
	पूर्ण अन्यथा अणु
		ग_लिखोl(set_mask, aio->cygaud->audio + ESR2_MASK_SET_OFFSET);
		ग_लिखोl(set_mask, aio->cygaud->audio + ESR4_MASK_SET_OFFSET);
	पूर्ण

पूर्ण

अटल पूर्णांक cygnus_pcm_trigger(काष्ठा snd_soc_component *component,
			      काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	पूर्णांक ret = 0;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		enable_पूर्णांकr(substream);
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		disable_पूर्णांकr(substream);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम cygnus_pcm_period_elapsed(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा cygnus_aio_port *aio;
	काष्ठा ringbuf_regs *p_rbuf = शून्य;
	u32 regval;

	aio = cygnus_dai_get_dma_data(substream);

	p_rbuf = get_ringbuf(substream);

	/*
	 * If मुक्त/full mark पूर्णांकerrupt occurs, provide बारtamp
	 * to ALSA and update appropriate idx by period_bytes
	 */
	snd_pcm_period_elapsed(substream);

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		/* Set the ring buffer to full */
		regval = पढ़ोl(aio->cygaud->audio + p_rbuf->rdaddr);
		regval = regval ^ BIT(31);
		ग_लिखोl(regval, aio->cygaud->audio + p_rbuf->wraddr);
	पूर्ण अन्यथा अणु
		/* Set the ring buffer to empty */
		regval = पढ़ोl(aio->cygaud->audio + p_rbuf->wraddr);
		ग_लिखोl(regval, aio->cygaud->audio + p_rbuf->rdaddr);
	पूर्ण
पूर्ण

/*
 * ESR0/1/3 status  Description
 *  0x1	I2S0_out port caused पूर्णांकerrupt
 *  0x2	I2S1_out port caused पूर्णांकerrupt
 *  0x4	I2S2_out port caused पूर्णांकerrupt
 *  0x8	SPDIF_out port caused पूर्णांकerrupt
 */
अटल व्योम handle_playback_irq(काष्ठा cygnus_audio *cygaud)
अणु
	व्योम __iomem *audio_io;
	u32 port;
	u32 esr_status0, esr_status1, esr_status3;

	audio_io = cygaud->audio;

	/*
	 * ESR status माला_लो updates with/without पूर्णांकerrupts enabled.
	 * So, check the ESR mask, which provides पूर्णांकerrupt enable/
	 * disable status and use it to determine which ESR status
	 * should be serviced.
	 */
	esr_status0 = पढ़ोl(audio_io + ESR0_STATUS_OFFSET);
	esr_status0 &= ~पढ़ोl(audio_io + ESR0_MASK_STATUS_OFFSET);
	esr_status1 = पढ़ोl(audio_io + ESR1_STATUS_OFFSET);
	esr_status1 &= ~पढ़ोl(audio_io + ESR1_MASK_STATUS_OFFSET);
	esr_status3 = पढ़ोl(audio_io + ESR3_STATUS_OFFSET);
	esr_status3 &= ~पढ़ोl(audio_io + ESR3_MASK_STATUS_OFFSET);

	क्रम (port = 0; port < CYGNUS_MAX_PLAYBACK_PORTS; port++) अणु
		u32 esrmask = BIT(port);

		/*
		 * Ringbuffer or FIFO underflow
		 * If we get this पूर्णांकerrupt then, it is also true that we have
		 * not yet responded to the मुक्तmark पूर्णांकerrupt.
		 * Log a debug message.  The मुक्तmark handler below will
		 * handle getting everything going again.
		 */
		अगर ((esrmask & esr_status1) || (esrmask & esr_status0)) अणु
			dev_dbg(cygaud->dev,
				"Underrun: esr0=0x%x, esr1=0x%x esr3=0x%x\n",
				esr_status0, esr_status1, esr_status3);
		पूर्ण

		/*
		 * Freemark is hit. This is the normal पूर्णांकerrupt.
		 * In typical operation the पढ़ो and ग_लिखो regs will be equal
		 */
		अगर (esrmask & esr_status3) अणु
			काष्ठा snd_pcm_substream *playstr;

			playstr = cygaud->portinfo[port].play_stream;
			cygnus_pcm_period_elapsed(playstr);
		पूर्ण
	पूर्ण

	/* Clear ESR पूर्णांकerrupt */
	ग_लिखोl(esr_status0, audio_io + ESR0_STATUS_CLR_OFFSET);
	ग_लिखोl(esr_status1, audio_io + ESR1_STATUS_CLR_OFFSET);
	ग_लिखोl(esr_status3, audio_io + ESR3_STATUS_CLR_OFFSET);
	/* Rearm मुक्तmark logic by writing 1 to the correct bit */
	ग_लिखोl(esr_status3, audio_io + BF_REARM_FREE_MARK_OFFSET);
पूर्ण

/*
 * ESR2/4 status  Description
 *  0x1	I2S0_in port caused पूर्णांकerrupt
 *  0x2	I2S1_in port caused पूर्णांकerrupt
 *  0x4	I2S2_in port caused पूर्णांकerrupt
 */
अटल व्योम handle_capture_irq(काष्ठा cygnus_audio *cygaud)
अणु
	व्योम __iomem *audio_io;
	u32 port;
	u32 esr_status2, esr_status4;

	audio_io = cygaud->audio;

	/*
	 * ESR status माला_लो updates with/without पूर्णांकerrupts enabled.
	 * So, check the ESR mask, which provides पूर्णांकerrupt enable/
	 * disable status and use it to determine which ESR status
	 * should be serviced.
	 */
	esr_status2 = पढ़ोl(audio_io + ESR2_STATUS_OFFSET);
	esr_status2 &= ~पढ़ोl(audio_io + ESR2_MASK_STATUS_OFFSET);
	esr_status4 = पढ़ोl(audio_io + ESR4_STATUS_OFFSET);
	esr_status4 &= ~पढ़ोl(audio_io + ESR4_MASK_STATUS_OFFSET);

	क्रम (port = 0; port < CYGNUS_MAX_CAPTURE_PORTS; port++) अणु
		u32 esrmask = BIT(port);

		/*
		 * Ringbuffer or FIFO overflow
		 * If we get this पूर्णांकerrupt then, it is also true that we have
		 * not yet responded to the fullmark पूर्णांकerrupt.
		 * Log a debug message.  The fullmark handler below will
		 * handle getting everything going again.
		 */
		अगर (esrmask & esr_status2)
			dev_dbg(cygaud->dev,
				"Overflow: esr2=0x%x\n", esr_status2);

		अगर (esrmask & esr_status4) अणु
			काष्ठा snd_pcm_substream *capstr;

			capstr = cygaud->portinfo[port].capture_stream;
			cygnus_pcm_period_elapsed(capstr);
		पूर्ण
	पूर्ण

	ग_लिखोl(esr_status2, audio_io + ESR2_STATUS_CLR_OFFSET);
	ग_लिखोl(esr_status4, audio_io + ESR4_STATUS_CLR_OFFSET);
	/* Rearm fullmark logic by writing 1 to the correct bit */
	ग_लिखोl(esr_status4, audio_io + BF_REARM_FULL_MARK_OFFSET);
पूर्ण

अटल irqवापस_t cygnus_dma_irq(पूर्णांक irq, व्योम *data)
अणु
	u32 r5_status;
	काष्ठा cygnus_audio *cygaud = data;

	/*
	 * R5 status bits	Description
	 *  0		ESR0 (playback FIFO पूर्णांकerrupt)
	 *  1		ESR1 (playback rbuf पूर्णांकerrupt)
	 *  2		ESR2 (capture rbuf पूर्णांकerrupt)
	 *  3		ESR3 (Freemark play. पूर्णांकerrupt)
	 *  4		ESR4 (Fullmark capt. पूर्णांकerrupt)
	 */
	r5_status = पढ़ोl(cygaud->audio + INTH_R5F_STATUS_OFFSET);

	अगर (!(r5_status & (ANY_PLAYBACK_IRQ | ANY_CAPTURE_IRQ)))
		वापस IRQ_NONE;

	/* If playback पूर्णांकerrupt happened */
	अगर (ANY_PLAYBACK_IRQ & r5_status) अणु
		handle_playback_irq(cygaud);
		ग_लिखोl(ANY_PLAYBACK_IRQ & r5_status,
			cygaud->audio + INTH_R5F_CLEAR_OFFSET);
	पूर्ण

	/* If  capture पूर्णांकerrupt happened */
	अगर (ANY_CAPTURE_IRQ & r5_status) अणु
		handle_capture_irq(cygaud);
		ग_लिखोl(ANY_CAPTURE_IRQ & r5_status,
			cygaud->audio + INTH_R5F_CLEAR_OFFSET);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक cygnus_pcm_खोलो(काष्ठा snd_soc_component *component,
			   काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा cygnus_aio_port *aio;
	पूर्णांक ret;

	aio = cygnus_dai_get_dma_data(substream);
	अगर (!aio)
		वापस -ENODEV;

	dev_dbg(asoc_rtd_to_cpu(rtd, 0)->dev, "%s port %d\n", __func__, aio->portnum);

	snd_soc_set_runसमय_hwparams(substream, &cygnus_pcm_hw);

	ret = snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0,
		SNDRV_PCM_HW_PARAM_PERIOD_BYTES, PERIOD_BYTES_MIN);
	अगर (ret < 0)
		वापस ret;

	ret = snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0,
		SNDRV_PCM_HW_PARAM_BUFFER_BYTES, PERIOD_BYTES_MIN);
	अगर (ret < 0)
		वापस ret;
	/*
	 * Keep track of which substream beदीर्घs to which port.
	 * This info is needed by snd_pcm_period_elapsed() in irq_handler
	 */
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		aio->play_stream = substream;
	अन्यथा
		aio->capture_stream = substream;

	वापस 0;
पूर्ण

अटल पूर्णांक cygnus_pcm_बंद(काष्ठा snd_soc_component *component,
			    काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा cygnus_aio_port *aio;

	aio = cygnus_dai_get_dma_data(substream);

	dev_dbg(asoc_rtd_to_cpu(rtd, 0)->dev, "%s  port %d\n", __func__, aio->portnum);

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		aio->play_stream = शून्य;
	अन्यथा
		aio->capture_stream = शून्य;

	अगर (!aio->play_stream && !aio->capture_stream)
		dev_dbg(asoc_rtd_to_cpu(rtd, 0)->dev, "freed  port %d\n", aio->portnum);

	वापस 0;
पूर्ण

अटल पूर्णांक cygnus_pcm_prepare(काष्ठा snd_soc_component *component,
			      काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा cygnus_aio_port *aio;
	अचिन्हित दीर्घ bufsize, periodsize;
	bool is_play;
	u32 start;
	काष्ठा ringbuf_regs *p_rbuf = शून्य;

	aio = cygnus_dai_get_dma_data(substream);
	dev_dbg(asoc_rtd_to_cpu(rtd, 0)->dev, "%s port %d\n", __func__, aio->portnum);

	bufsize = snd_pcm_lib_buffer_bytes(substream);
	periodsize = snd_pcm_lib_period_bytes(substream);

	dev_dbg(asoc_rtd_to_cpu(rtd, 0)->dev, "%s (buf_size %lu) (period_size %lu)\n",
			__func__, bufsize, periodsize);

	configure_ringbuf_regs(substream);

	p_rbuf = get_ringbuf(substream);

	start = runसमय->dma_addr;

	is_play = (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) ? 1 : 0;

	ringbuf_set_initial(aio->cygaud->audio, p_rbuf, is_play, start,
				periodsize, bufsize);

	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t cygnus_pcm_poपूर्णांकer(काष्ठा snd_soc_component *component,
					    काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा cygnus_aio_port *aio;
	अचिन्हित पूर्णांक res = 0, cur = 0, base = 0;
	काष्ठा ringbuf_regs *p_rbuf = शून्य;

	aio = cygnus_dai_get_dma_data(substream);

	/*
	 * Get the offset of the current पढ़ो (क्रम playack) or ग_लिखो
	 * index (क्रम capture).  Report this value back to the asoc framework.
	 */
	p_rbuf = get_ringbuf(substream);
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		cur = पढ़ोl(aio->cygaud->audio + p_rbuf->rdaddr);
	अन्यथा
		cur = पढ़ोl(aio->cygaud->audio + p_rbuf->wraddr);

	base = पढ़ोl(aio->cygaud->audio + p_rbuf->baseaddr);

	/*
	 * Mask off the MSB of the rdaddr,wraddr and baseaddr
	 * since MSB is not part of the address
	 */
	res = (cur & 0x7fffffff) - (base & 0x7fffffff);

	वापस bytes_to_frames(substream->runसमय, res);
पूर्ण

अटल पूर्णांक cygnus_dma_new(काष्ठा snd_soc_component *component,
			  काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	माप_प्रकार size = cygnus_pcm_hw.buffer_bytes_max;
	काष्ठा snd_card *card = rtd->card->snd_card;

	अगर (!card->dev->dma_mask)
		card->dev->dma_mask = &cygnus_dma_dmamask;
	अगर (!card->dev->coherent_dma_mask)
		card->dev->coherent_dma_mask = DMA_BIT_MASK(32);

	snd_pcm_set_managed_buffer_all(rtd->pcm, SNDRV_DMA_TYPE_DEV,
				       card->dev, size, size);

	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_component_driver cygnus_soc_platक्रमm = अणु
	.खोलो		= cygnus_pcm_खोलो,
	.बंद		= cygnus_pcm_बंद,
	.prepare	= cygnus_pcm_prepare,
	.trigger	= cygnus_pcm_trigger,
	.poपूर्णांकer	= cygnus_pcm_poपूर्णांकer,
	.pcm_स्थिरruct	= cygnus_dma_new,
पूर्ण;

पूर्णांक cygnus_soc_platक्रमm_रेजिस्टर(काष्ठा device *dev,
				 काष्ठा cygnus_audio *cygaud)
अणु
	पूर्णांक rc = 0;

	dev_dbg(dev, "%s Enter\n", __func__);

	rc = devm_request_irq(dev, cygaud->irq_num, cygnus_dma_irq,
				IRQF_SHARED, "cygnus-audio", cygaud);
	अगर (rc) अणु
		dev_err(dev, "%s request_irq error %d\n", __func__, rc);
		वापस rc;
	पूर्ण

	rc = devm_snd_soc_रेजिस्टर_component(dev, &cygnus_soc_platक्रमm,
					     शून्य, 0);
	अगर (rc) अणु
		dev_err(dev, "%s failed\n", __func__);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक cygnus_soc_platक्रमm_unरेजिस्टर(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Broadcom");
MODULE_DESCRIPTION("Cygnus ASoC PCM module");
