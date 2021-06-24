<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This file is part of STM32 DFSDM driver
 *
 * Copyright (C) 2017, STMicroelectronics - All Rights Reserved
 * Author(s): Arnaud Pouliquen <arnaud.pouliquen@st.com>.
 */

#अगर_अघोषित MDF_STM32_DFSDM__H
#घोषणा MDF_STM32_DFSDM__H

#समावेश <linux/bitfield.h>

/*
 * STM32 DFSDM - global रेजिस्टर map
 * ________________________________________________________
 * | Offset |                 Registers block             |
 * --------------------------------------------------------
 * | 0x000  |      CHANNEL 0 + COMMON CHANNEL FIELDS      |
 * --------------------------------------------------------
 * | 0x020  |                CHANNEL 1                    |
 * --------------------------------------------------------
 * | ...    |                .....                        |
 * --------------------------------------------------------
 * | 0x0E0  |                CHANNEL 7                    |
 * --------------------------------------------------------
 * | 0x100  |      FILTER  0 + COMMON  FILTER FIELDs      |
 * --------------------------------------------------------
 * | 0x200  |                FILTER  1                    |
 * --------------------------------------------------------
 * | 0x300  |                FILTER  2                    |
 * --------------------------------------------------------
 * | 0x400  |                FILTER  3                    |
 * --------------------------------------------------------
 */

/*
 * Channels रेजिस्टर definitions
 */
#घोषणा DFSDM_CHCFGR1(y)  ((y) * 0x20 + 0x00)
#घोषणा DFSDM_CHCFGR2(y)  ((y) * 0x20 + 0x04)
#घोषणा DFSDM_AWSCDR(y)   ((y) * 0x20 + 0x08)
#घोषणा DFSDM_CHWDATR(y)  ((y) * 0x20 + 0x0C)
#घोषणा DFSDM_CHDATINR(y) ((y) * 0x20 + 0x10)

/* CHCFGR1: Channel configuration रेजिस्टर 1 */
#घोषणा DFSDM_CHCFGR1_SITP_MASK     GENMASK(1, 0)
#घोषणा DFSDM_CHCFGR1_SITP(v)       FIELD_PREP(DFSDM_CHCFGR1_SITP_MASK, v)
#घोषणा DFSDM_CHCFGR1_SPICKSEL_MASK GENMASK(3, 2)
#घोषणा DFSDM_CHCFGR1_SPICKSEL(v)   FIELD_PREP(DFSDM_CHCFGR1_SPICKSEL_MASK, v)
#घोषणा DFSDM_CHCFGR1_SCDEN_MASK    BIT(5)
#घोषणा DFSDM_CHCFGR1_SCDEN(v)      FIELD_PREP(DFSDM_CHCFGR1_SCDEN_MASK, v)
#घोषणा DFSDM_CHCFGR1_CKABEN_MASK   BIT(6)
#घोषणा DFSDM_CHCFGR1_CKABEN(v)     FIELD_PREP(DFSDM_CHCFGR1_CKABEN_MASK, v)
#घोषणा DFSDM_CHCFGR1_CHEN_MASK     BIT(7)
#घोषणा DFSDM_CHCFGR1_CHEN(v)       FIELD_PREP(DFSDM_CHCFGR1_CHEN_MASK, v)
#घोषणा DFSDM_CHCFGR1_CHINSEL_MASK  BIT(8)
#घोषणा DFSDM_CHCFGR1_CHINSEL(v)    FIELD_PREP(DFSDM_CHCFGR1_CHINSEL_MASK, v)
#घोषणा DFSDM_CHCFGR1_DATMPX_MASK   GENMASK(13, 12)
#घोषणा DFSDM_CHCFGR1_DATMPX(v)     FIELD_PREP(DFSDM_CHCFGR1_DATMPX_MASK, v)
#घोषणा DFSDM_CHCFGR1_DATPACK_MASK  GENMASK(15, 14)
#घोषणा DFSDM_CHCFGR1_DATPACK(v)    FIELD_PREP(DFSDM_CHCFGR1_DATPACK_MASK, v)
#घोषणा DFSDM_CHCFGR1_CKOUTDIV_MASK GENMASK(23, 16)
#घोषणा DFSDM_CHCFGR1_CKOUTDIV(v)   FIELD_PREP(DFSDM_CHCFGR1_CKOUTDIV_MASK, v)
#घोषणा DFSDM_CHCFGR1_CKOUTSRC_MASK BIT(30)
#घोषणा DFSDM_CHCFGR1_CKOUTSRC(v)   FIELD_PREP(DFSDM_CHCFGR1_CKOUTSRC_MASK, v)
#घोषणा DFSDM_CHCFGR1_DFSDMEN_MASK  BIT(31)
#घोषणा DFSDM_CHCFGR1_DFSDMEN(v)    FIELD_PREP(DFSDM_CHCFGR1_DFSDMEN_MASK, v)

/* CHCFGR2: Channel configuration रेजिस्टर 2 */
#घोषणा DFSDM_CHCFGR2_DTRBS_MASK    GENMASK(7, 3)
#घोषणा DFSDM_CHCFGR2_DTRBS(v)      FIELD_PREP(DFSDM_CHCFGR2_DTRBS_MASK, v)
#घोषणा DFSDM_CHCFGR2_OFFSET_MASK   GENMASK(31, 8)
#घोषणा DFSDM_CHCFGR2_OFFSET(v)     FIELD_PREP(DFSDM_CHCFGR2_OFFSET_MASK, v)

/* AWSCDR: Channel analog watchकरोg and लघु circuit detector */
#घोषणा DFSDM_AWSCDR_SCDT_MASK    GENMASK(7, 0)
#घोषणा DFSDM_AWSCDR_SCDT(v)      FIELD_PREP(DFSDM_AWSCDR_SCDT_MASK, v)
#घोषणा DFSDM_AWSCDR_BKSCD_MASK   GENMASK(15, 12)
#घोषणा DFSDM_AWSCDR_BKSCD(v)	  FIELD_PREP(DFSDM_AWSCDR_BKSCD_MASK, v)
#घोषणा DFSDM_AWSCDR_AWFOSR_MASK  GENMASK(20, 16)
#घोषणा DFSDM_AWSCDR_AWFOSR(v)    FIELD_PREP(DFSDM_AWSCDR_AWFOSR_MASK, v)
#घोषणा DFSDM_AWSCDR_AWFORD_MASK  GENMASK(23, 22)
#घोषणा DFSDM_AWSCDR_AWFORD(v)    FIELD_PREP(DFSDM_AWSCDR_AWFORD_MASK, v)

/*
 * Filters रेजिस्टर definitions
 */
#घोषणा DFSDM_FILTER_BASE_ADR		0x100
#घोषणा DFSDM_FILTER_REG_MASK		0x7F
#घोषणा DFSDM_FILTER_X_BASE_ADR(x)	((x) * 0x80 + DFSDM_FILTER_BASE_ADR)

#घोषणा DFSDM_CR1(x)     (DFSDM_FILTER_X_BASE_ADR(x)  + 0x00)
#घोषणा DFSDM_CR2(x)     (DFSDM_FILTER_X_BASE_ADR(x)  + 0x04)
#घोषणा DFSDM_ISR(x)     (DFSDM_FILTER_X_BASE_ADR(x)  + 0x08)
#घोषणा DFSDM_ICR(x)     (DFSDM_FILTER_X_BASE_ADR(x)  + 0x0C)
#घोषणा DFSDM_JCHGR(x)   (DFSDM_FILTER_X_BASE_ADR(x)  + 0x10)
#घोषणा DFSDM_FCR(x)     (DFSDM_FILTER_X_BASE_ADR(x)  + 0x14)
#घोषणा DFSDM_JDATAR(x)  (DFSDM_FILTER_X_BASE_ADR(x)  + 0x18)
#घोषणा DFSDM_RDATAR(x)  (DFSDM_FILTER_X_BASE_ADR(x)  + 0x1C)
#घोषणा DFSDM_AWHTR(x)   (DFSDM_FILTER_X_BASE_ADR(x)  + 0x20)
#घोषणा DFSDM_AWLTR(x)   (DFSDM_FILTER_X_BASE_ADR(x)  + 0x24)
#घोषणा DFSDM_AWSR(x)    (DFSDM_FILTER_X_BASE_ADR(x)  + 0x28)
#घोषणा DFSDM_AWCFR(x)   (DFSDM_FILTER_X_BASE_ADR(x)  + 0x2C)
#घोषणा DFSDM_EXMAX(x)   (DFSDM_FILTER_X_BASE_ADR(x)  + 0x30)
#घोषणा DFSDM_EXMIN(x)   (DFSDM_FILTER_X_BASE_ADR(x)  + 0x34)
#घोषणा DFSDM_CNVTIMR(x) (DFSDM_FILTER_X_BASE_ADR(x)  + 0x38)

/* CR1 Control रेजिस्टर 1 */
#घोषणा DFSDM_CR1_DFEN_MASK	BIT(0)
#घोषणा DFSDM_CR1_DFEN(v)	FIELD_PREP(DFSDM_CR1_DFEN_MASK, v)
#घोषणा DFSDM_CR1_JSWSTART_MASK	BIT(1)
#घोषणा DFSDM_CR1_JSWSTART(v)	FIELD_PREP(DFSDM_CR1_JSWSTART_MASK, v)
#घोषणा DFSDM_CR1_JSYNC_MASK	BIT(3)
#घोषणा DFSDM_CR1_JSYNC(v)	FIELD_PREP(DFSDM_CR1_JSYNC_MASK, v)
#घोषणा DFSDM_CR1_JSCAN_MASK	BIT(4)
#घोषणा DFSDM_CR1_JSCAN(v)	FIELD_PREP(DFSDM_CR1_JSCAN_MASK, v)
#घोषणा DFSDM_CR1_JDMAEN_MASK	BIT(5)
#घोषणा DFSDM_CR1_JDMAEN(v)	FIELD_PREP(DFSDM_CR1_JDMAEN_MASK, v)
#घोषणा DFSDM_CR1_JEXTSEL_MASK	GENMASK(12, 8)
#घोषणा DFSDM_CR1_JEXTSEL(v)	FIELD_PREP(DFSDM_CR1_JEXTSEL_MASK, v)
#घोषणा DFSDM_CR1_JEXTEN_MASK	GENMASK(14, 13)
#घोषणा DFSDM_CR1_JEXTEN(v)	FIELD_PREP(DFSDM_CR1_JEXTEN_MASK, v)
#घोषणा DFSDM_CR1_RSWSTART_MASK	BIT(17)
#घोषणा DFSDM_CR1_RSWSTART(v)	FIELD_PREP(DFSDM_CR1_RSWSTART_MASK, v)
#घोषणा DFSDM_CR1_RCONT_MASK	BIT(18)
#घोषणा DFSDM_CR1_RCONT(v)	FIELD_PREP(DFSDM_CR1_RCONT_MASK, v)
#घोषणा DFSDM_CR1_RSYNC_MASK	BIT(19)
#घोषणा DFSDM_CR1_RSYNC(v)	FIELD_PREP(DFSDM_CR1_RSYNC_MASK, v)
#घोषणा DFSDM_CR1_RDMAEN_MASK	BIT(21)
#घोषणा DFSDM_CR1_RDMAEN(v)	FIELD_PREP(DFSDM_CR1_RDMAEN_MASK, v)
#घोषणा DFSDM_CR1_RCH_MASK	GENMASK(26, 24)
#घोषणा DFSDM_CR1_RCH(v)	FIELD_PREP(DFSDM_CR1_RCH_MASK, v)
#घोषणा DFSDM_CR1_FAST_MASK	BIT(29)
#घोषणा DFSDM_CR1_FAST(v)	FIELD_PREP(DFSDM_CR1_FAST_MASK, v)
#घोषणा DFSDM_CR1_AWFSEL_MASK	BIT(30)
#घोषणा DFSDM_CR1_AWFSEL(v)	FIELD_PREP(DFSDM_CR1_AWFSEL_MASK, v)

/* CR2: Control रेजिस्टर 2 */
#घोषणा DFSDM_CR2_IE_MASK	GENMASK(6, 0)
#घोषणा DFSDM_CR2_IE(v)		FIELD_PREP(DFSDM_CR2_IE_MASK, v)
#घोषणा DFSDM_CR2_JEOCIE_MASK	BIT(0)
#घोषणा DFSDM_CR2_JEOCIE(v)	FIELD_PREP(DFSDM_CR2_JEOCIE_MASK, v)
#घोषणा DFSDM_CR2_REOCIE_MASK	BIT(1)
#घोषणा DFSDM_CR2_REOCIE(v)	FIELD_PREP(DFSDM_CR2_REOCIE_MASK, v)
#घोषणा DFSDM_CR2_JOVRIE_MASK	BIT(2)
#घोषणा DFSDM_CR2_JOVRIE(v)	FIELD_PREP(DFSDM_CR2_JOVRIE_MASK, v)
#घोषणा DFSDM_CR2_ROVRIE_MASK	BIT(3)
#घोषणा DFSDM_CR2_ROVRIE(v)	FIELD_PREP(DFSDM_CR2_ROVRIE_MASK, v)
#घोषणा DFSDM_CR2_AWDIE_MASK	BIT(4)
#घोषणा DFSDM_CR2_AWDIE(v)	FIELD_PREP(DFSDM_CR2_AWDIE_MASK, v)
#घोषणा DFSDM_CR2_SCDIE_MASK	BIT(5)
#घोषणा DFSDM_CR2_SCDIE(v)	FIELD_PREP(DFSDM_CR2_SCDIE_MASK, v)
#घोषणा DFSDM_CR2_CKABIE_MASK	BIT(6)
#घोषणा DFSDM_CR2_CKABIE(v)	FIELD_PREP(DFSDM_CR2_CKABIE_MASK, v)
#घोषणा DFSDM_CR2_EXCH_MASK	GENMASK(15, 8)
#घोषणा DFSDM_CR2_EXCH(v)	FIELD_PREP(DFSDM_CR2_EXCH_MASK, v)
#घोषणा DFSDM_CR2_AWDCH_MASK	GENMASK(23, 16)
#घोषणा DFSDM_CR2_AWDCH(v)	FIELD_PREP(DFSDM_CR2_AWDCH_MASK, v)

/* ISR: Interrupt status रेजिस्टर */
#घोषणा DFSDM_ISR_JEOCF_MASK	BIT(0)
#घोषणा DFSDM_ISR_JEOCF(v)	FIELD_PREP(DFSDM_ISR_JEOCF_MASK, v)
#घोषणा DFSDM_ISR_REOCF_MASK	BIT(1)
#घोषणा DFSDM_ISR_REOCF(v)	FIELD_PREP(DFSDM_ISR_REOCF_MASK, v)
#घोषणा DFSDM_ISR_JOVRF_MASK	BIT(2)
#घोषणा DFSDM_ISR_JOVRF(v)	FIELD_PREP(DFSDM_ISR_JOVRF_MASK, v)
#घोषणा DFSDM_ISR_ROVRF_MASK	BIT(3)
#घोषणा DFSDM_ISR_ROVRF(v)	FIELD_PREP(DFSDM_ISR_ROVRF_MASK, v)
#घोषणा DFSDM_ISR_AWDF_MASK	BIT(4)
#घोषणा DFSDM_ISR_AWDF(v)	FIELD_PREP(DFSDM_ISR_AWDF_MASK, v)
#घोषणा DFSDM_ISR_JCIP_MASK	BIT(13)
#घोषणा DFSDM_ISR_JCIP(v)	FIELD_PREP(DFSDM_ISR_JCIP_MASK, v)
#घोषणा DFSDM_ISR_RCIP_MASK	BIT(14)
#घोषणा DFSDM_ISR_RCIP(v)	FIELD_PREP(DFSDM_ISR_RCIP, v)
#घोषणा DFSDM_ISR_CKABF_MASK	GENMASK(23, 16)
#घोषणा DFSDM_ISR_CKABF(v)	FIELD_PREP(DFSDM_ISR_CKABF_MASK, v)
#घोषणा DFSDM_ISR_SCDF_MASK	GENMASK(31, 24)
#घोषणा DFSDM_ISR_SCDF(v)	FIELD_PREP(DFSDM_ISR_SCDF_MASK, v)

/* ICR: Interrupt flag clear रेजिस्टर */
#घोषणा DFSDM_ICR_CLRJOVRF_MASK	      BIT(2)
#घोषणा DFSDM_ICR_CLRJOVRF(v)	      FIELD_PREP(DFSDM_ICR_CLRJOVRF_MASK, v)
#घोषणा DFSDM_ICR_CLRROVRF_MASK	      BIT(3)
#घोषणा DFSDM_ICR_CLRROVRF(v)	      FIELD_PREP(DFSDM_ICR_CLRROVRF_MASK, v)
#घोषणा DFSDM_ICR_CLRCKABF_MASK	      GENMASK(23, 16)
#घोषणा DFSDM_ICR_CLRCKABF(v)	      FIELD_PREP(DFSDM_ICR_CLRCKABF_MASK, v)
#घोषणा DFSDM_ICR_CLRCKABF_CH_MASK(y) BIT(16 + (y))
#घोषणा DFSDM_ICR_CLRCKABF_CH(v, y)   \
			   (((v) << (16 + (y))) & DFSDM_ICR_CLRCKABF_CH_MASK(y))
#घोषणा DFSDM_ICR_CLRSCDF_MASK	      GENMASK(31, 24)
#घोषणा DFSDM_ICR_CLRSCDF(v)	      FIELD_PREP(DFSDM_ICR_CLRSCDF_MASK, v)
#घोषणा DFSDM_ICR_CLRSCDF_CH_MASK(y)  BIT(24 + (y))
#घोषणा DFSDM_ICR_CLRSCDF_CH(v, y)    \
			       (((v) << (24 + (y))) & DFSDM_ICR_CLRSCDF_MASK(y))

/* FCR: Filter control रेजिस्टर */
#घोषणा DFSDM_FCR_IOSR_MASK	GENMASK(7, 0)
#घोषणा DFSDM_FCR_IOSR(v)	FIELD_PREP(DFSDM_FCR_IOSR_MASK, v)
#घोषणा DFSDM_FCR_FOSR_MASK	GENMASK(25, 16)
#घोषणा DFSDM_FCR_FOSR(v)	FIELD_PREP(DFSDM_FCR_FOSR_MASK, v)
#घोषणा DFSDM_FCR_FORD_MASK	GENMASK(31, 29)
#घोषणा DFSDM_FCR_FORD(v)	FIELD_PREP(DFSDM_FCR_FORD_MASK, v)

/* RDATAR: Filter data रेजिस्टर क्रम regular channel */
#घोषणा DFSDM_DATAR_CH_MASK	GENMASK(2, 0)
#घोषणा DFSDM_DATAR_DATA_OFFSET 8
#घोषणा DFSDM_DATAR_DATA_MASK	GENMASK(31, DFSDM_DATAR_DATA_OFFSET)

/* AWLTR: Filter analog watchकरोg low threshold रेजिस्टर */
#घोषणा DFSDM_AWLTR_BKAWL_MASK	GENMASK(3, 0)
#घोषणा DFSDM_AWLTR_BKAWL(v)	FIELD_PREP(DFSDM_AWLTR_BKAWL_MASK, v)
#घोषणा DFSDM_AWLTR_AWLT_MASK	GENMASK(31, 8)
#घोषणा DFSDM_AWLTR_AWLT(v)	FIELD_PREP(DFSDM_AWLTR_AWLT_MASK, v)

/* AWHTR: Filter analog watchकरोg low threshold रेजिस्टर */
#घोषणा DFSDM_AWHTR_BKAWH_MASK	GENMASK(3, 0)
#घोषणा DFSDM_AWHTR_BKAWH(v)	FIELD_PREP(DFSDM_AWHTR_BKAWH_MASK, v)
#घोषणा DFSDM_AWHTR_AWHT_MASK	GENMASK(31, 8)
#घोषणा DFSDM_AWHTR_AWHT(v)	FIELD_PREP(DFSDM_AWHTR_AWHT_MASK, v)

/* AWSR: Filter watchकरोg status रेजिस्टर */
#घोषणा DFSDM_AWSR_AWLTF_MASK	GENMASK(7, 0)
#घोषणा DFSDM_AWSR_AWLTF(v)	FIELD_PREP(DFSDM_AWSR_AWLTF_MASK, v)
#घोषणा DFSDM_AWSR_AWHTF_MASK	GENMASK(15, 8)
#घोषणा DFSDM_AWSR_AWHTF(v)	FIELD_PREP(DFSDM_AWSR_AWHTF_MASK, v)

/* AWCFR: Filter watchकरोg status रेजिस्टर */
#घोषणा DFSDM_AWCFR_AWLTF_MASK	GENMASK(7, 0)
#घोषणा DFSDM_AWCFR_AWLTF(v)	FIELD_PREP(DFSDM_AWCFR_AWLTF_MASK, v)
#घोषणा DFSDM_AWCFR_AWHTF_MASK	GENMASK(15, 8)
#घोषणा DFSDM_AWCFR_AWHTF(v)	FIELD_PREP(DFSDM_AWCFR_AWHTF_MASK, v)

/* DFSDM filter order  */
क्रमागत sपंचांग32_dfsdm_sinc_order अणु
	DFSDM_FASTSINC_ORDER, /* FastSinc filter type */
	DFSDM_SINC1_ORDER,    /* Sinc 1 filter type */
	DFSDM_SINC2_ORDER,    /* Sinc 2 filter type */
	DFSDM_SINC3_ORDER,    /* Sinc 3 filter type */
	DFSDM_SINC4_ORDER,    /* Sinc 4 filter type (N.A. क्रम watchकरोg) */
	DFSDM_SINC5_ORDER,    /* Sinc 5 filter type (N.A. क्रम watchकरोg) */
	DFSDM_NB_SINC_ORDER,
पूर्ण;

/**
 * काष्ठा sपंचांग32_dfsdm_filter_osr - DFSDM filter settings linked to oversampling
 * @iosr: पूर्णांकegrator oversampling
 * @fosr: filter oversampling
 * @rshअगरt: output sample right shअगरt (hardware shअगरt)
 * @lshअगरt: output sample left shअगरt (software shअगरt)
 * @res: output sample resolution
 * @bits: output sample resolution in bits
 * @max: output sample maximum positive value
 */
काष्ठा sपंचांग32_dfsdm_filter_osr अणु
	अचिन्हित पूर्णांक iosr;
	अचिन्हित पूर्णांक fosr;
	अचिन्हित पूर्णांक rshअगरt;
	अचिन्हित पूर्णांक lshअगरt;
	u64 res;
	u32 bits;
	s32 max;
पूर्ण;

/**
 * काष्ठा sपंचांग32_dfsdm_filter - काष्ठाure relative to sपंचांग32 FDSDM filter
 * @क्रमd: filter order
 * @flo: filter oversampling data table indexed by fast mode flag
 * @sync_mode: filter synchronized with filter 0
 * @fast: filter fast mode
 */
काष्ठा sपंचांग32_dfsdm_filter अणु
	क्रमागत sपंचांग32_dfsdm_sinc_order क्रमd;
	काष्ठा sपंचांग32_dfsdm_filter_osr flo[2];
	अचिन्हित पूर्णांक sync_mode;
	अचिन्हित पूर्णांक fast;
पूर्ण;

/**
 * काष्ठा sपंचांग32_dfsdm_channel - काष्ठाure relative to sपंचांग32 FDSDM channel
 * @id: id of the channel
 * @type: पूर्णांकerface type linked to sपंचांग32_dfsdm_chan_type
 * @src: पूर्णांकerface type linked to sपंचांग32_dfsdm_chan_src
 * @alt_si: alternative serial input पूर्णांकerface
 */
काष्ठा sपंचांग32_dfsdm_channel अणु
	अचिन्हित पूर्णांक id;
	अचिन्हित पूर्णांक type;
	अचिन्हित पूर्णांक src;
	अचिन्हित पूर्णांक alt_si;
पूर्ण;

/**
 * काष्ठा sपंचांग32_dfsdm - sपंचांग32 FDSDM driver common data (क्रम all instances)
 * @base:	control रेजिस्टरs base cpu addr
 * @phys_base:	DFSDM IP रेजिस्टर physical address
 * @regmap:	regmap क्रम रेजिस्टर पढ़ो/ग_लिखो
 * @fl_list:	filter resources list
 * @num_fls:	number of filter resources available
 * @ch_list:	channel resources list
 * @num_chs:	number of channel resources available
 * @spi_master_freq: SPI घड़ी out frequency
 */
काष्ठा sपंचांग32_dfsdm अणु
	व्योम __iomem	*base;
	phys_addr_t	phys_base;
	काष्ठा regmap *regmap;
	काष्ठा sपंचांग32_dfsdm_filter *fl_list;
	अचिन्हित पूर्णांक num_fls;
	काष्ठा sपंचांग32_dfsdm_channel *ch_list;
	अचिन्हित पूर्णांक num_chs;
	अचिन्हित पूर्णांक spi_master_freq;
पूर्ण;

/* DFSDM channel serial spi घड़ी source */
क्रमागत sपंचांग32_dfsdm_spi_clk_src अणु
	DFSDM_CHANNEL_SPI_CLOCK_EXTERNAL,
	DFSDM_CHANNEL_SPI_CLOCK_INTERNAL,
	DFSDM_CHANNEL_SPI_CLOCK_INTERNAL_DIV2_FALLING,
	DFSDM_CHANNEL_SPI_CLOCK_INTERNAL_DIV2_RISING
पूर्ण;

पूर्णांक sपंचांग32_dfsdm_start_dfsdm(काष्ठा sपंचांग32_dfsdm *dfsdm);
पूर्णांक sपंचांग32_dfsdm_stop_dfsdm(काष्ठा sपंचांग32_dfsdm *dfsdm);

#पूर्ण_अगर
