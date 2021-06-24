<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * sun8i-ce-trng.c - hardware cryptographic offloader क्रम
 * Allwinner H3/A64/H5/H2+/H6/R40 SoC
 *
 * Copyright (C) 2015-2020 Corentin Labbe <clabbe@baylibre.com>
 *
 * This file handle the TRNG
 *
 * You could find a link क्रम the datasheet in Documentation/arm/sunxi.rst
 */
#समावेश "sun8i-ce.h"
#समावेश <linux/dma-mapping.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/hw_अक्रमom.h>
/*
 * Note that according to the algorithm ID, 2 versions of the TRNG exists,
 * The first present in H3/H5/R40/A64 and the second present in H6.
 * This file adds support क्रम both, but only the second is working
 * reliabily according to rngtest.
 **/

अटल पूर्णांक sun8i_ce_trng_पढ़ो(काष्ठा hwrng *rng, व्योम *data, माप_प्रकार max, bool रुको)
अणु
	काष्ठा sun8i_ce_dev *ce;
	dma_addr_t dma_dst;
	पूर्णांक err = 0;
	पूर्णांक flow = 3;
	अचिन्हित पूर्णांक toकरो;
	काष्ठा sun8i_ce_flow *chan;
	काष्ठा ce_task *cet;
	u32 common;
	व्योम *d;

	ce = container_of(rng, काष्ठा sun8i_ce_dev, trng);

	/* round the data length to a multiple of 32*/
	toकरो = max + 32;
	toकरो -= toकरो % 32;

	d = kzalloc(toकरो, GFP_KERNEL | GFP_DMA);
	अगर (!d)
		वापस -ENOMEM;

#अगर_घोषित CONFIG_CRYPTO_DEV_SUN8I_CE_DEBUG
	ce->hwrng_stat_req++;
	ce->hwrng_stat_bytes += toकरो;
#पूर्ण_अगर

	dma_dst = dma_map_single(ce->dev, d, toकरो, DMA_FROM_DEVICE);
	अगर (dma_mapping_error(ce->dev, dma_dst)) अणु
		dev_err(ce->dev, "Cannot DMA MAP DST\n");
		err = -EFAULT;
		जाओ err_dst;
	पूर्ण

	err = pm_runसमय_get_sync(ce->dev);
	अगर (err < 0) अणु
		pm_runसमय_put_noidle(ce->dev);
		जाओ err_pm;
	पूर्ण

	mutex_lock(&ce->rnglock);
	chan = &ce->chanlist[flow];

	cet = &chan->tl[0];
	स_रखो(cet, 0, माप(काष्ठा ce_task));

	cet->t_id = cpu_to_le32(flow);
	common = ce->variant->trng | CE_COMM_INT;
	cet->t_common_ctl = cpu_to_le32(common);

	/* recent CE (H6) need length in bytes, in word otherwise */
	अगर (ce->variant->trng_t_dlen_in_bytes)
		cet->t_dlen = cpu_to_le32(toकरो);
	अन्यथा
		cet->t_dlen = cpu_to_le32(toकरो / 4);

	cet->t_sym_ctl = 0;
	cet->t_asym_ctl = 0;

	cet->t_dst[0].addr = cpu_to_le32(dma_dst);
	cet->t_dst[0].len = cpu_to_le32(toकरो / 4);
	ce->chanlist[flow].समयout = toकरो;

	err = sun8i_ce_run_task(ce, 3, "TRNG");
	mutex_unlock(&ce->rnglock);

	pm_runसमय_put(ce->dev);

err_pm:
	dma_unmap_single(ce->dev, dma_dst, toकरो, DMA_FROM_DEVICE);

	अगर (!err) अणु
		स_नकल(data, d, max);
		err = max;
	पूर्ण
	memzero_explicit(d, toकरो);
err_dst:
	kमुक्त(d);
	वापस err;
पूर्ण

पूर्णांक sun8i_ce_hwrng_रेजिस्टर(काष्ठा sun8i_ce_dev *ce)
अणु
	पूर्णांक ret;

	अगर (ce->variant->trng == CE_ID_NOTSUPP) अणु
		dev_info(ce->dev, "TRNG not supported\n");
		वापस 0;
	पूर्ण
	ce->trng.name = "sun8i Crypto Engine TRNG";
	ce->trng.पढ़ो = sun8i_ce_trng_पढ़ो;
	ce->trng.quality = 1000;

	ret = hwrng_रेजिस्टर(&ce->trng);
	अगर (ret)
		dev_err(ce->dev, "Fail to register the TRNG\n");
	वापस ret;
पूर्ण

व्योम sun8i_ce_hwrng_unरेजिस्टर(काष्ठा sun8i_ce_dev *ce)
अणु
	अगर (ce->variant->trng == CE_ID_NOTSUPP)
		वापस;
	hwrng_unरेजिस्टर(&ce->trng);
पूर्ण
