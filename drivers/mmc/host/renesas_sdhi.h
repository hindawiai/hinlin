<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Renesas Mobile SDHI
 *
 * Copyright (C) 2017 Horms Solutions Ltd., Simon Horman
 * Copyright (C) 2017-19 Renesas Electronics Corporation
 */

#अगर_अघोषित RENESAS_SDHI_H
#घोषणा RENESAS_SDHI_H

#समावेश <linux/platक्रमm_device.h>
#समावेश "tmio_mmc.h"

काष्ठा renesas_sdhi_scc अणु
	अचिन्हित दीर्घ clk_rate;	/* घड़ी rate क्रम SDR104 */
	u32 tap;		/* sampling घड़ी position क्रम SDR104/HS400 (8 TAP) */
	u32 tap_hs400_4tap;	/* sampling घड़ी position क्रम HS400 (4 TAP) */
पूर्ण;

काष्ठा renesas_sdhi_of_data अणु
	अचिन्हित दीर्घ पंचांगio_flags;
	u32	      पंचांगio_ocr_mask;
	अचिन्हित दीर्घ capabilities;
	अचिन्हित दीर्घ capabilities2;
	क्रमागत dma_slave_buswidth dma_buswidth;
	dma_addr_t dma_rx_offset;
	अचिन्हित पूर्णांक bus_shअगरt;
	पूर्णांक scc_offset;
	काष्ठा renesas_sdhi_scc *taps;
	पूर्णांक taps_num;
	अचिन्हित पूर्णांक max_blk_count;
	अचिन्हित लघु max_segs;
पूर्ण;

#घोषणा SDHI_CALIB_TABLE_MAX 32

काष्ठा renesas_sdhi_quirks अणु
	bool hs400_disabled;
	bool hs400_4taps;
	u32 hs400_bad_taps;
	स्थिर u8 (*hs400_calib_table)[SDHI_CALIB_TABLE_MAX];
पूर्ण;

काष्ठा पंचांगio_mmc_dma अणु
	क्रमागत dma_slave_buswidth dma_buswidth;
	bool (*filter)(काष्ठा dma_chan *chan, व्योम *arg);
	व्योम (*enable)(काष्ठा पंचांगio_mmc_host *host, bool enable);
	काष्ठा completion	dma_dataend;
	काष्ठा tasklet_काष्ठा	dma_complete;
पूर्ण;

काष्ठा renesas_sdhi अणु
	काष्ठा clk *clk;
	काष्ठा clk *clk_cd;
	काष्ठा पंचांगio_mmc_data mmc_data;
	काष्ठा पंचांगio_mmc_dma dma_priv;
	स्थिर काष्ठा renesas_sdhi_quirks *quirks;
	काष्ठा pinctrl *pinctrl;
	काष्ठा pinctrl_state *pins_शेष, *pins_uhs;
	व्योम __iomem *scc_ctl;
	u32 scc_tappos;
	u32 scc_tappos_hs400;
	स्थिर u8 *adjust_hs400_calib_table;
	bool needs_adjust_hs400;

	/* Tuning values: 1 क्रम success, 0 क्रम failure */
	DECLARE_BITMAP(taps, BITS_PER_LONG);
	/* Sampling data comparison: 1 क्रम match, 0 क्रम mismatch */
	DECLARE_BITMAP(smpcmp, BITS_PER_LONG);
	अचिन्हित पूर्णांक tap_num;
	अचिन्हित पूर्णांक tap_set;

	काष्ठा reset_control *rstc;
पूर्ण;

#घोषणा host_to_priv(host) \
	container_of((host)->pdata, काष्ठा renesas_sdhi, mmc_data)

पूर्णांक renesas_sdhi_probe(काष्ठा platक्रमm_device *pdev,
		       स्थिर काष्ठा पंचांगio_mmc_dma_ops *dma_ops);
पूर्णांक renesas_sdhi_हटाओ(काष्ठा platक्रमm_device *pdev);
#पूर्ण_अगर
