<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Analog Devices 1889 audio driver
 * Copyright (C) 2004, Kyle McMartin <kyle@parisc-linux.org>
 */

#अगर_अघोषित __AD1889_H__
#घोषणा __AD1889_H__

#घोषणा AD_DS_WSMC	0x00 /* wave/synthesis channel mixer control */
#घोषणा  AD_DS_WSMC_SYEN 0x0004 /* synthesis channel enable */
#घोषणा  AD_DS_WSMC_SYRQ 0x0030 /* synth. fअगरo request poपूर्णांक */
#घोषणा  AD_DS_WSMC_WA16 0x0100 /* wave channel 16bit select */
#घोषणा  AD_DS_WSMC_WAST 0x0200 /* wave channel stereo select */
#घोषणा  AD_DS_WSMC_WAEN 0x0400 /* wave channel enable */
#घोषणा  AD_DS_WSMC_WARQ 0x3000 /* wave fअगरo request poपूर्णांक */

#घोषणा AD_DS_RAMC	0x02 /* resampler/ADC channel mixer control */
#घोषणा  AD_DS_RAMC_AD16 0x0001 /* ADC channel 16bit select */
#घोषणा  AD_DS_RAMC_ADST 0x0002 /* ADC channel stereo select */
#घोषणा  AD_DS_RAMC_ADEN 0x0004 /* ADC channel enable */
#घोषणा  AD_DS_RAMC_ACRQ 0x0030 /* ADC fअगरo request poपूर्णांक */
#घोषणा  AD_DS_RAMC_REEN 0x0400 /* resampler channel enable */
#घोषणा  AD_DS_RAMC_RERQ 0x3000 /* res. fअगरo request poपूर्णांक */

#घोषणा AD_DS_WADA	0x04 /* wave channel mix attenuation */
#घोषणा  AD_DS_WADA_RWAM 0x0080 /* right wave mute */
#घोषणा  AD_DS_WADA_RWAA 0x001f /* right wave attenuation */
#घोषणा  AD_DS_WADA_LWAM 0x8000 /* left wave mute */
#घोषणा  AD_DS_WADA_LWAA 0x3e00 /* left wave attenuation */

#घोषणा AD_DS_SYDA	0x06 /* synthesis channel mix attenuation */
#घोषणा  AD_DS_SYDA_RSYM 0x0080 /* right synthesis mute */
#घोषणा  AD_DS_SYDA_RSYA 0x001f /* right synthesis attenuation */
#घोषणा  AD_DS_SYDA_LSYM 0x8000 /* left synthesis mute */
#घोषणा  AD_DS_SYDA_LSYA 0x3e00 /* left synthesis attenuation */

#घोषणा AD_DS_WAS	0x08 /* wave channel sample rate */
#घोषणा  AD_DS_WAS_WAS   0xffff /* sample rate mask */

#घोषणा AD_DS_RES	0x0a /* resampler channel sample rate */
#घोषणा  AD_DS_RES_RES   0xffff /* sample rate mask */

#घोषणा AD_DS_CCS	0x0c /* chip control/status */
#घोषणा  AD_DS_CCS_ADO   0x0001 /* ADC channel overflow */
#घोषणा  AD_DS_CCS_REO   0x0002 /* resampler channel overflow */
#घोषणा  AD_DS_CCS_SYU   0x0004 /* synthesis channel underflow */
#घोषणा  AD_DS_CCS_WAU   0x0008 /* wave channel underflow */
/* bits 4 -> 7, 9, 11 -> 14 reserved */
#घोषणा  AD_DS_CCS_XTD   0x0100 /* xtd delay control (4096 घड़ी cycles) */
#घोषणा  AD_DS_CCS_PDALL 0x0400 /* घातer */
#घोषणा  AD_DS_CCS_CLKEN 0x8000 /* घड़ी */

#घोषणा AD_DMA_RESBA	0x40 /* RES base address */
#घोषणा AD_DMA_RESCA	0x44 /* RES current address */
#घोषणा AD_DMA_RESBC	0x48 /* RES base count */
#घोषणा AD_DMA_RESCC	0x4c /* RES current count */

#घोषणा AD_DMA_ADCBA	0x50 /* ADC base address */
#घोषणा AD_DMA_ADCCA	0x54 /* ADC current address */
#घोषणा AD_DMA_ADCBC	0x58 /* ADC base count */
#घोषणा AD_DMA_ADCCC	0x5c /* ADC current count */

#घोषणा AD_DMA_SYNBA	0x60 /* synth base address */
#घोषणा AD_DMA_SYNCA	0x64 /* synth current address */
#घोषणा AD_DMA_SYNBC	0x68 /* synth base count */
#घोषणा AD_DMA_SYNCC	0x6c /* synth current count */

#घोषणा AD_DMA_WAVBA	0x70 /* wave base address */
#घोषणा AD_DMA_WAVCA	0x74 /* wave current address */
#घोषणा AD_DMA_WAVBC	0x78 /* wave base count */
#घोषणा AD_DMA_WAVCC	0x7c /* wave current count */

#घोषणा AD_DMA_RESIC	0x80 /* RES dma पूर्णांकerrupt current byte count */
#घोषणा AD_DMA_RESIB	0x84 /* RES dma पूर्णांकerrupt base byte count */

#घोषणा AD_DMA_ADCIC	0x88 /* ADC dma पूर्णांकerrupt current byte count */
#घोषणा AD_DMA_ADCIB	0x8c /* ADC dma पूर्णांकerrupt base byte count */

#घोषणा AD_DMA_SYNIC	0x90 /* synth dma पूर्णांकerrupt current byte count */
#घोषणा AD_DMA_SYNIB	0x94 /* synth dma पूर्णांकerrupt base byte count */

#घोषणा AD_DMA_WAVIC	0x98 /* wave dma पूर्णांकerrupt current byte count */
#घोषणा AD_DMA_WAVIB	0x9c /* wave dma पूर्णांकerrupt base byte count */

#घोषणा  AD_DMA_ICC	0xffffff /* current byte count mask */
#घोषणा  AD_DMA_IBC	0xffffff /* base byte count mask */
/* bits 24 -> 31 reserved */

/* 4 bytes pad */
#घोषणा AD_DMA_ADC	0xa8	/* ADC      dma control and status */
#घोषणा AD_DMA_SYNTH	0xb0	/* Synth    dma control and status */
#घोषणा AD_DMA_WAV	0xb8	/* wave     dma control and status */
#घोषणा AD_DMA_RES	0xa0	/* Resample dma control and status */

#घोषणा  AD_DMA_SGDE	0x0001 /* SGD mode enable */
#घोषणा  AD_DMA_LOOP	0x0002 /* loop enable */
#घोषणा  AD_DMA_IM	0x000c /* पूर्णांकerrupt mode mask */
#घोषणा  AD_DMA_IM_DIS	(~AD_DMA_IM)	/* disable */
#घोषणा  AD_DMA_IM_CNT	0x0004 /* पूर्णांकerrupt on count */
#घोषणा  AD_DMA_IM_SGD	0x0008 /* पूर्णांकerrupt on SGD flag */
#घोषणा  AD_DMA_IM_EOL	0x000c /* पूर्णांकerrupt on End of Linked List */
#घोषणा  AD_DMA_SGDS	0x0030 /* SGD status */
#घोषणा  AD_DMA_SFLG	0x0040 /* SGD flag */
#घोषणा  AD_DMA_EOL	0x0080 /* SGD end of list */
/* bits 8 -> 15 reserved */

#घोषणा AD_DMA_DISR	0xc0 /* dma पूर्णांकerrupt status */
#घोषणा  AD_DMA_DISR_RESI 0x000001 /* resampler channel पूर्णांकerrupt */
#घोषणा  AD_DMA_DISR_ADCI 0x000002 /* ADC channel पूर्णांकerrupt */
#घोषणा  AD_DMA_DISR_SYNI 0x000004 /* synthesis channel पूर्णांकerrupt */
#घोषणा  AD_DMA_DISR_WAVI 0x000008 /* wave channel पूर्णांकerrupt */
/* bits 4, 5 reserved */
#घोषणा  AD_DMA_DISR_SEPS 0x000040 /* serial eeprom status */
/* bits 7 -> 13 reserved */
#घोषणा  AD_DMA_DISR_PMAI 0x004000 /* pci master पात पूर्णांकerrupt */
#घोषणा  AD_DMA_DISR_PTAI 0x008000 /* pci target पात पूर्णांकerrupt */
#घोषणा  AD_DMA_DISR_PTAE 0x010000 /* pci target पात पूर्णांकerrupt enable */
#घोषणा  AD_DMA_DISR_PMAE 0x020000 /* pci master पात पूर्णांकerrupt enable */
/* bits 19 -> 31 reserved */

/* पूर्णांकerrupt mask */
#घोषणा  AD_INTR_MASK     (AD_DMA_DISR_RESI|AD_DMA_DISR_ADCI| \
                           AD_DMA_DISR_WAVI|AD_DMA_DISR_SYNI| \
                           AD_DMA_DISR_PMAI|AD_DMA_DISR_PTAI)

#घोषणा AD_DMA_CHSS	0xc4 /* dma channel stop status */
#घोषणा  AD_DMA_CHSS_RESS 0x000001 /* resampler channel stopped */
#घोषणा  AD_DMA_CHSS_ADCS 0x000002 /* ADC channel stopped */
#घोषणा  AD_DMA_CHSS_SYNS 0x000004 /* synthesis channel stopped */
#घोषणा  AD_DMA_CHSS_WAVS 0x000008 /* wave channel stopped */

#घोषणा AD_GPIO_IPC	0xc8	/* gpio port control */
#घोषणा AD_GPIO_OP	0xca	/* gpio output port status */
#घोषणा AD_GPIO_IP	0xcc	/* gpio  input port status */

#घोषणा AD_AC97_BASE	0x100	/* ac97 base रेजिस्टर */

#घोषणा AD_AC97_RESET   0x100   /* reset */

#घोषणा AD_AC97_PWR_CTL	0x126	/* == AC97_POWERDOWN */
#घोषणा  AD_AC97_PWR_ADC 0x0001 /* ADC पढ़ोy status */
#घोषणा  AD_AC97_PWR_DAC 0x0002 /* DAC पढ़ोy status */
#घोषणा  AD_AC97_PWR_PR0 0x0100 /* PR0 (ADC) घातerकरोwn */
#घोषणा  AD_AC97_PWR_PR1 0x0200 /* PR1 (DAC) घातerकरोwn */

#घोषणा AD_MISC_CTL     0x176 /* misc control */
#घोषणा  AD_MISC_CTL_DACZ   0x8000 /* set क्रम zero fill, unset क्रम repeat */
#घोषणा  AD_MISC_CTL_ARSR   0x0001 /* set क्रम SR1, unset क्रम SR0 */
#घोषणा  AD_MISC_CTL_ALSR   0x0100
#घोषणा  AD_MISC_CTL_DLSR   0x0400
#घोषणा  AD_MISC_CTL_DRSR   0x0004

#घोषणा AD_AC97_SR0     0x178 /* sample rate 0, 0xbb80 == 48K */
#घोषणा  AD_AC97_SR0_48K 0xbb80 /* 48KHz */
#घोषणा AD_AC97_SR1     0x17a /* sample rate 1 */

#घोषणा AD_AC97_ACIC	0x180 /* ac97 codec पूर्णांकerface control */
#घोषणा  AD_AC97_ACIC_ACIE  0x0001 /* analog codec पूर्णांकerface enable */
#घोषणा  AD_AC97_ACIC_ACRD  0x0002 /* analog codec reset disable */
#घोषणा  AD_AC97_ACIC_ASOE  0x0004 /* audio stream output enable */
#घोषणा  AD_AC97_ACIC_VSRM  0x0008 /* variable sample rate mode */
#घोषणा  AD_AC97_ACIC_FSDH  0x0100 /* क्रमce SDATA_OUT high */
#घोषणा  AD_AC97_ACIC_FSYH  0x0200 /* क्रमce sync high */
#घोषणा  AD_AC97_ACIC_ACRDY 0x8000 /* analog codec पढ़ोy status */
/* bits 10 -> 14 reserved */


#घोषणा AD_DS_MEMSIZE	512
#घोषणा AD_OPL_MEMSIZE	16
#घोषणा AD_MIDI_MEMSIZE	16

#घोषणा AD_WAV_STATE	0
#घोषणा AD_ADC_STATE	1
#घोषणा AD_MAX_STATES	2

#घोषणा AD_CHAN_WAV	0x0001
#घोषणा AD_CHAN_ADC	0x0002
#घोषणा AD_CHAN_RES	0x0004
#घोषणा AD_CHAN_SYN	0x0008


/* The chip would support 4 GB buffers and 16 MB periods,
 * but let's not overकरो it ... */
#घोषणा BUFFER_BYTES_MAX	(256 * 1024)
#घोषणा PERIOD_BYTES_MIN	32
#घोषणा PERIOD_BYTES_MAX	(BUFFER_BYTES_MAX / 2)
#घोषणा PERIODS_MIN		2
#घोषणा PERIODS_MAX		(BUFFER_BYTES_MAX / PERIOD_BYTES_MIN)

#पूर्ण_अगर /* __AD1889_H__ */
