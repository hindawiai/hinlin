<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * NXP AUDMIX ALSA SoC Digital Audio Interface (DAI) driver
 *
 * Copyright 2017 NXP
 */

#अगर_अघोषित __FSL_AUDMIX_H
#घोषणा __FSL_AUDMIX_H

#घोषणा FSL_AUDMIX_FORMATS (SNDRV_PCM_FMTBIT_S16_LE |\
			SNDRV_PCM_FMTBIT_S24_LE |\
			SNDRV_PCM_FMTBIT_S32_LE)
/* AUDMIX Registers */
#घोषणा FSL_AUDMIX_CTR		0x200 /* Control */
#घोषणा FSL_AUDMIX_STR		0x204 /* Status */

#घोषणा FSL_AUDMIX_ATCR0	0x208 /* Attenuation Control */
#घोषणा FSL_AUDMIX_ATIVAL0	0x20c /* Attenuation Initial Value */
#घोषणा FSL_AUDMIX_ATSTPUP0	0x210 /* Attenuation step up factor */
#घोषणा FSL_AUDMIX_ATSTPDN0	0x214 /* Attenuation step करोwn factor */
#घोषणा FSL_AUDMIX_ATSTPTGT0	0x218 /* Attenuation step target */
#घोषणा FSL_AUDMIX_ATTNVAL0	0x21c /* Attenuation Value */
#घोषणा FSL_AUDMIX_ATSTP0	0x220 /* Attenuation step number */

#घोषणा FSL_AUDMIX_ATCR1	0x228 /* Attenuation Control */
#घोषणा FSL_AUDMIX_ATIVAL1	0x22c /* Attenuation Initial Value */
#घोषणा FSL_AUDMIX_ATSTPUP1	0x230 /* Attenuation step up factor */
#घोषणा FSL_AUDMIX_ATSTPDN1	0x234 /* Attenuation step करोwn factor */
#घोषणा FSL_AUDMIX_ATSTPTGT1	0x238 /* Attenuation step target */
#घोषणा FSL_AUDMIX_ATTNVAL1	0x23c /* Attenuation Value */
#घोषणा FSL_AUDMIX_ATSTP1	0x240 /* Attenuation step number */

/* AUDMIX Control Register */
#घोषणा FSL_AUDMIX_CTR_MIXCLK_SHIFT	0
#घोषणा FSL_AUDMIX_CTR_MIXCLK_MASK	BIT(FSL_AUDMIX_CTR_MIXCLK_SHIFT)
#घोषणा FSL_AUDMIX_CTR_MIXCLK(i)	((i) << FSL_AUDMIX_CTR_MIXCLK_SHIFT)
#घोषणा FSL_AUDMIX_CTR_OUTSRC_SHIFT	1
#घोषणा FSL_AUDMIX_CTR_OUTSRC_MASK	(0x3 << FSL_AUDMIX_CTR_OUTSRC_SHIFT)
#घोषणा FSL_AUDMIX_CTR_OUTSRC(i)	(((i) << FSL_AUDMIX_CTR_OUTSRC_SHIFT)\
					      & FSL_AUDMIX_CTR_OUTSRC_MASK)
#घोषणा FSL_AUDMIX_CTR_OUTWIDTH_SHIFT	3
#घोषणा FSL_AUDMIX_CTR_OUTWIDTH_MASK	(0x7 << FSL_AUDMIX_CTR_OUTWIDTH_SHIFT)
#घोषणा FSL_AUDMIX_CTR_OUTWIDTH(i)	(((i) << FSL_AUDMIX_CTR_OUTWIDTH_SHIFT)\
					      & FSL_AUDMIX_CTR_OUTWIDTH_MASK)
#घोषणा FSL_AUDMIX_CTR_OUTCKPOL_SHIFT	6
#घोषणा FSL_AUDMIX_CTR_OUTCKPOL_MASK	BIT(FSL_AUDMIX_CTR_OUTCKPOL_SHIFT)
#घोषणा FSL_AUDMIX_CTR_OUTCKPOL(i)	((i) << FSL_AUDMIX_CTR_OUTCKPOL_SHIFT)
#घोषणा FSL_AUDMIX_CTR_MASKRTDF_SHIFT	7
#घोषणा FSL_AUDMIX_CTR_MASKRTDF_MASK	BIT(FSL_AUDMIX_CTR_MASKRTDF_SHIFT)
#घोषणा FSL_AUDMIX_CTR_MASKRTDF(i)	((i) << FSL_AUDMIX_CTR_MASKRTDF_SHIFT)
#घोषणा FSL_AUDMIX_CTR_MASKCKDF_SHIFT	8
#घोषणा FSL_AUDMIX_CTR_MASKCKDF_MASK	BIT(FSL_AUDMIX_CTR_MASKCKDF_SHIFT)
#घोषणा FSL_AUDMIX_CTR_MASKCKDF(i)	((i) << FSL_AUDMIX_CTR_MASKCKDF_SHIFT)
#घोषणा FSL_AUDMIX_CTR_SYNCMODE_SHIFT	9
#घोषणा FSL_AUDMIX_CTR_SYNCMODE_MASK	BIT(FSL_AUDMIX_CTR_SYNCMODE_SHIFT)
#घोषणा FSL_AUDMIX_CTR_SYNCMODE(i)	((i) << FSL_AUDMIX_CTR_SYNCMODE_SHIFT)
#घोषणा FSL_AUDMIX_CTR_SYNCSRC_SHIFT	10
#घोषणा FSL_AUDMIX_CTR_SYNCSRC_MASK	BIT(FSL_AUDMIX_CTR_SYNCSRC_SHIFT)
#घोषणा FSL_AUDMIX_CTR_SYNCSRC(i)	((i) << FSL_AUDMIX_CTR_SYNCSRC_SHIFT)

/* AUDMIX Status Register */
#घोषणा FSL_AUDMIX_STR_RATEDIFF		BIT(0)
#घोषणा FSL_AUDMIX_STR_CLKDIFF		BIT(1)
#घोषणा FSL_AUDMIX_STR_MIXSTAT_SHIFT	2
#घोषणा FSL_AUDMIX_STR_MIXSTAT_MASK	(0x3 << FSL_AUDMIX_STR_MIXSTAT_SHIFT)
#घोषणा FSL_AUDMIX_STR_MIXSTAT(i)	(((i) & FSL_AUDMIX_STR_MIXSTAT_MASK) \
					   >> FSL_AUDMIX_STR_MIXSTAT_SHIFT)
/* AUDMIX Attenuation Control Register */
#घोषणा FSL_AUDMIX_ATCR_AT_EN		BIT(0)
#घोषणा FSL_AUDMIX_ATCR_AT_UPDN		BIT(1)
#घोषणा FSL_AUDMIX_ATCR_ATSTPDIF_SHIFT	2
#घोषणा FSL_AUDMIX_ATCR_ATSTPDFI_MASK	\
				(0xfff << FSL_AUDMIX_ATCR_ATSTPDIF_SHIFT)

/* AUDMIX Attenuation Initial Value Register */
#घोषणा FSL_AUDMIX_ATIVAL_ATINVAL_MASK	0x3FFFF

/* AUDMIX Attenuation Step Up Factor Register */
#घोषणा FSL_AUDMIX_ATSTPUP_ATSTEPUP_MASK	0x3FFFF

/* AUDMIX Attenuation Step Down Factor Register */
#घोषणा FSL_AUDMIX_ATSTPDN_ATSTEPDN_MASK	0x3FFFF

/* AUDMIX Attenuation Step Target Register */
#घोषणा FSL_AUDMIX_ATSTPTGT_ATSTPTG_MASK	0x3FFFF

/* AUDMIX Attenuation Value Register */
#घोषणा FSL_AUDMIX_ATTNVAL_ATCURVAL_MASK	0x3FFFF

/* AUDMIX Attenuation Step Number Register */
#घोषणा FSL_AUDMIX_ATSTP_STPCTR_MASK	0x3FFFF

#घोषणा FSL_AUDMIX_MAX_DAIS		2
काष्ठा fsl_audmix अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा regmap *regmap;
	काष्ठा clk *ipg_clk;
	spinlock_t lock; /* Protect tdms */
	u8 tdms;
पूर्ण;

#पूर्ण_अगर /* __FSL_AUDMIX_H */
