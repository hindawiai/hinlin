<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2017 Marvell
 *
 * Antoine Tenart <antoine.tenart@मुक्त-electrons.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/firmware.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/workqueue.h>

#समावेश <crypto/पूर्णांकernal/aead.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>

#समावेश "safexcel.h"

अटल u32 max_rings = EIP197_MAX_RINGS;
module_param(max_rings, uपूर्णांक, 0644);
MODULE_PARM_DESC(max_rings, "Maximum number of rings to use.");

अटल व्योम eip197_trc_cache_setupvirt(काष्ठा safexcel_crypto_priv *priv)
अणु
	पूर्णांक i;

	/*
	 * Map all पूर्णांकerfaces/rings to रेजिस्टर index 0
	 * so they can share contexts. Without this, the EIP197 will
	 * assume each पूर्णांकerface/ring to be in its own memory करोमुख्य
	 * i.e. have its own subset of UNIQUE memory addresses.
	 * Which would cause records with the SAME memory address to
	 * use DIFFERENT cache buffers, causing both poor cache utilization
	 * AND serious coherence/invalidation issues.
	 */
	क्रम (i = 0; i < 4; i++)
		ग_लिखोl(0, priv->base + EIP197_FLUE_IFC_LUT(i));

	/*
	 * Initialize other भवization regs क्रम cache
	 * These may not be in their reset state ...
	 */
	क्रम (i = 0; i < priv->config.rings; i++) अणु
		ग_लिखोl(0, priv->base + EIP197_FLUE_CACHEBASE_LO(i));
		ग_लिखोl(0, priv->base + EIP197_FLUE_CACHEBASE_HI(i));
		ग_लिखोl(EIP197_FLUE_CONFIG_MAGIC,
		       priv->base + EIP197_FLUE_CONFIG(i));
	पूर्ण
	ग_लिखोl(0, priv->base + EIP197_FLUE_OFFSETS);
	ग_लिखोl(0, priv->base + EIP197_FLUE_ARC4_OFFSET);
पूर्ण

अटल व्योम eip197_trc_cache_banksel(काष्ठा safexcel_crypto_priv *priv,
				     u32 addrmid, पूर्णांक *actbank)
अणु
	u32 val;
	पूर्णांक curbank;

	curbank = addrmid >> 16;
	अगर (curbank != *actbank) अणु
		val = पढ़ोl(priv->base + EIP197_CS_RAM_CTRL);
		val = (val & ~EIP197_CS_BANKSEL_MASK) |
		      (curbank << EIP197_CS_BANKSEL_OFS);
		ग_लिखोl(val, priv->base + EIP197_CS_RAM_CTRL);
		*actbank = curbank;
	पूर्ण
पूर्ण

अटल u32 eip197_trc_cache_probe(काष्ठा safexcel_crypto_priv *priv,
				  पूर्णांक maxbanks, u32 probemask, u32 stride)
अणु
	u32 val, addrhi, addrlo, addrmid, addralias, delta, marker;
	पूर्णांक actbank;

	/*
	 * And probe the actual size of the physically attached cache data RAM
	 * Using a binary subभागision algorithm करोwnto 32 byte cache lines.
	 */
	addrhi = 1 << (16 + maxbanks);
	addrlo = 0;
	actbank = min(maxbanks - 1, 0);
	जबतक ((addrhi - addrlo) > stride) अणु
		/* ग_लिखो marker to lowest address in top half */
		addrmid = (addrhi + addrlo) >> 1;
		marker = (addrmid ^ 0xabadbabe) & probemask; /* Unique */
		eip197_trc_cache_banksel(priv, addrmid, &actbank);
		ग_लिखोl(marker,
			priv->base + EIP197_CLASSIFICATION_RAMS +
			(addrmid & 0xffff));

		/* ग_लिखो invalid markers to possible aliases */
		delta = 1 << __fls(addrmid);
		जबतक (delta >= stride) अणु
			addralias = addrmid - delta;
			eip197_trc_cache_banksel(priv, addralias, &actbank);
			ग_लिखोl(~marker,
			       priv->base + EIP197_CLASSIFICATION_RAMS +
			       (addralias & 0xffff));
			delta >>= 1;
		पूर्ण

		/* पढ़ो back marker from top half */
		eip197_trc_cache_banksel(priv, addrmid, &actbank);
		val = पढ़ोl(priv->base + EIP197_CLASSIFICATION_RAMS +
			    (addrmid & 0xffff));

		अगर ((val & probemask) == marker)
			/* पढ़ो back correct, जारी with top half */
			addrlo = addrmid;
		अन्यथा
			/* not पढ़ो back correct, जारी with bottom half */
			addrhi = addrmid;
	पूर्ण
	वापस addrhi;
पूर्ण

अटल व्योम eip197_trc_cache_clear(काष्ठा safexcel_crypto_priv *priv,
				   पूर्णांक cs_rc_max, पूर्णांक cs_ht_wc)
अणु
	पूर्णांक i;
	u32 htable_offset, val, offset;

	/* Clear all records in administration RAM */
	क्रम (i = 0; i < cs_rc_max; i++) अणु
		offset = EIP197_CLASSIFICATION_RAMS + i * EIP197_CS_RC_SIZE;

		ग_लिखोl(EIP197_CS_RC_NEXT(EIP197_RC_शून्य) |
		       EIP197_CS_RC_PREV(EIP197_RC_शून्य),
		       priv->base + offset);

		val = EIP197_CS_RC_NEXT(i + 1) | EIP197_CS_RC_PREV(i - 1);
		अगर (i == 0)
			val |= EIP197_CS_RC_PREV(EIP197_RC_शून्य);
		अन्यथा अगर (i == cs_rc_max - 1)
			val |= EIP197_CS_RC_NEXT(EIP197_RC_शून्य);
		ग_लिखोl(val, priv->base + offset + 4);
		/* must also initialize the address key due to ECC! */
		ग_लिखोl(0, priv->base + offset + 8);
		ग_लिखोl(0, priv->base + offset + 12);
	पूर्ण

	/* Clear the hash table entries */
	htable_offset = cs_rc_max * EIP197_CS_RC_SIZE;
	क्रम (i = 0; i < cs_ht_wc; i++)
		ग_लिखोl(GENMASK(29, 0),
		       priv->base + EIP197_CLASSIFICATION_RAMS +
		       htable_offset + i * माप(u32));
पूर्ण

अटल पूर्णांक eip197_trc_cache_init(काष्ठा safexcel_crypto_priv *priv)
अणु
	u32 val, dsize, asize;
	पूर्णांक cs_rc_max, cs_ht_wc, cs_trc_rec_wc, cs_trc_lg_rec_wc;
	पूर्णांक cs_rc_असल_max, cs_ht_sz;
	पूर्णांक maxbanks;

	/* Setup (dummy) भवization क्रम cache */
	eip197_trc_cache_setupvirt(priv);

	/*
	 * Enable the record cache memory access and
	 * probe the bank select width
	 */
	val = पढ़ोl(priv->base + EIP197_CS_RAM_CTRL);
	val &= ~EIP197_TRC_ENABLE_MASK;
	val |= EIP197_TRC_ENABLE_0 | EIP197_CS_BANKSEL_MASK;
	ग_लिखोl(val, priv->base + EIP197_CS_RAM_CTRL);
	val = पढ़ोl(priv->base + EIP197_CS_RAM_CTRL);
	maxbanks = ((val&EIP197_CS_BANKSEL_MASK)>>EIP197_CS_BANKSEL_OFS) + 1;

	/* Clear all ECC errors */
	ग_लिखोl(0, priv->base + EIP197_TRC_ECCCTRL);

	/*
	 * Make sure the cache memory is accessible by taking record cache पूर्णांकo
	 * reset. Need data memory access here, not admin access.
	 */
	val = पढ़ोl(priv->base + EIP197_TRC_PARAMS);
	val |= EIP197_TRC_PARAMS_SW_RESET | EIP197_TRC_PARAMS_DATA_ACCESS;
	ग_लिखोl(val, priv->base + EIP197_TRC_PARAMS);

	/* Probed data RAM size in bytes */
	dsize = eip197_trc_cache_probe(priv, maxbanks, 0xffffffff, 32);

	/*
	 * Now probe the administration RAM size pretty much the same way
	 * Except that only the lower 30 bits are writable and we करोn't need
	 * bank selects
	 */
	val = पढ़ोl(priv->base + EIP197_TRC_PARAMS);
	/* admin access now */
	val &= ~(EIP197_TRC_PARAMS_DATA_ACCESS | EIP197_CS_BANKSEL_MASK);
	ग_लिखोl(val, priv->base + EIP197_TRC_PARAMS);

	/* Probed admin RAM size in admin words */
	asize = eip197_trc_cache_probe(priv, 0, 0x3fffffff, 16) >> 4;

	/* Clear any ECC errors detected जबतक probing! */
	ग_लिखोl(0, priv->base + EIP197_TRC_ECCCTRL);

	/* Sanity check probing results */
	अगर (dsize < EIP197_MIN_DSIZE || asize < EIP197_MIN_ASIZE) अणु
		dev_err(priv->dev, "Record cache probing failed (%d,%d).",
			dsize, asize);
		वापस -ENODEV;
	पूर्ण

	/*
	 * Determine optimal configuration from RAM sizes
	 * Note that we assume that the physical RAM configuration is sane
	 * Thereक्रमe, we करोn't करो any parameter error checking here ...
	 */

	/* For now, just use a single record क्रमmat covering everything */
	cs_trc_rec_wc = EIP197_CS_TRC_REC_WC;
	cs_trc_lg_rec_wc = EIP197_CS_TRC_REC_WC;

	/*
	 * Step #1: How many records will physically fit?
	 * Hard upper limit is 1023!
	 */
	cs_rc_असल_max = min_t(uपूर्णांक, ((dsize >> 2) / cs_trc_lg_rec_wc), 1023);
	/* Step #2: Need at least 2 words in the admin RAM per record */
	cs_rc_max = min_t(uपूर्णांक, cs_rc_असल_max, (asize >> 1));
	/* Step #3: Determine log2 of hash table size */
	cs_ht_sz = __fls(asize - cs_rc_max) - 2;
	/* Step #4: determine current size of hash table in dwords */
	cs_ht_wc = 16 << cs_ht_sz; /* dwords, not admin words */
	/* Step #5: add back excess words and see अगर we can fit more records */
	cs_rc_max = min_t(uपूर्णांक, cs_rc_असल_max, asize - (cs_ht_wc >> 2));

	/* Clear the cache RAMs */
	eip197_trc_cache_clear(priv, cs_rc_max, cs_ht_wc);

	/* Disable the record cache memory access */
	val = पढ़ोl(priv->base + EIP197_CS_RAM_CTRL);
	val &= ~EIP197_TRC_ENABLE_MASK;
	ग_लिखोl(val, priv->base + EIP197_CS_RAM_CTRL);

	/* Write head and tail poपूर्णांकers of the record मुक्त chain */
	val = EIP197_TRC_FREECHAIN_HEAD_PTR(0) |
	      EIP197_TRC_FREECHAIN_TAIL_PTR(cs_rc_max - 1);
	ग_लिखोl(val, priv->base + EIP197_TRC_FREECHAIN);

	/* Configure the record cache #1 */
	val = EIP197_TRC_PARAMS2_RC_SZ_SMALL(cs_trc_rec_wc) |
	      EIP197_TRC_PARAMS2_HTABLE_PTR(cs_rc_max);
	ग_लिखोl(val, priv->base + EIP197_TRC_PARAMS2);

	/* Configure the record cache #2 */
	val = EIP197_TRC_PARAMS_RC_SZ_LARGE(cs_trc_lg_rec_wc) |
	      EIP197_TRC_PARAMS_BLK_TIMER_SPEED(1) |
	      EIP197_TRC_PARAMS_HTABLE_SZ(cs_ht_sz);
	ग_लिखोl(val, priv->base + EIP197_TRC_PARAMS);

	dev_info(priv->dev, "TRC init: %dd,%da (%dr,%dh)\n",
		 dsize, asize, cs_rc_max, cs_ht_wc + cs_ht_wc);
	वापस 0;
पूर्ण

अटल व्योम eip197_init_firmware(काष्ठा safexcel_crypto_priv *priv)
अणु
	पूर्णांक pe, i;
	u32 val;

	क्रम (pe = 0; pe < priv->config.pes; pe++) अणु
		/* Configure the token FIFO's */
		ग_लिखोl(3, EIP197_PE(priv) + EIP197_PE_ICE_PUTF_CTRL(pe));
		ग_लिखोl(0, EIP197_PE(priv) + EIP197_PE_ICE_PPTF_CTRL(pe));

		/* Clear the ICE scratchpad memory */
		val = पढ़ोl(EIP197_PE(priv) + EIP197_PE_ICE_SCRATCH_CTRL(pe));
		val |= EIP197_PE_ICE_SCRATCH_CTRL_CHANGE_TIMER |
		       EIP197_PE_ICE_SCRATCH_CTRL_TIMER_EN |
		       EIP197_PE_ICE_SCRATCH_CTRL_SCRATCH_ACCESS |
		       EIP197_PE_ICE_SCRATCH_CTRL_CHANGE_ACCESS;
		ग_लिखोl(val, EIP197_PE(priv) + EIP197_PE_ICE_SCRATCH_CTRL(pe));

		/* clear the scratchpad RAM using 32 bit ग_लिखोs only */
		क्रम (i = 0; i < EIP197_NUM_OF_SCRATCH_BLOCKS; i++)
			ग_लिखोl(0, EIP197_PE(priv) +
				  EIP197_PE_ICE_SCRATCH_RAM(pe) + (i << 2));

		/* Reset the IFPP engine to make its program mem accessible */
		ग_लिखोl(EIP197_PE_ICE_x_CTRL_SW_RESET |
		       EIP197_PE_ICE_x_CTRL_CLR_ECC_CORR |
		       EIP197_PE_ICE_x_CTRL_CLR_ECC_NON_CORR,
		       EIP197_PE(priv) + EIP197_PE_ICE_FPP_CTRL(pe));

		/* Reset the IPUE engine to make its program mem accessible */
		ग_लिखोl(EIP197_PE_ICE_x_CTRL_SW_RESET |
		       EIP197_PE_ICE_x_CTRL_CLR_ECC_CORR |
		       EIP197_PE_ICE_x_CTRL_CLR_ECC_NON_CORR,
		       EIP197_PE(priv) + EIP197_PE_ICE_PUE_CTRL(pe));

		/* Enable access to all IFPP program memories */
		ग_लिखोl(EIP197_PE_ICE_RAM_CTRL_FPP_PROG_EN,
		       EIP197_PE(priv) + EIP197_PE_ICE_RAM_CTRL(pe));

		/* bypass the OCE, अगर present */
		अगर (priv->flags & EIP197_OCE)
			ग_लिखोl(EIP197_DEBUG_OCE_BYPASS, EIP197_PE(priv) +
							EIP197_PE_DEBUG(pe));
	पूर्ण

पूर्ण

अटल पूर्णांक eip197_ग_लिखो_firmware(काष्ठा safexcel_crypto_priv *priv,
				  स्थिर काष्ठा firmware *fw)
अणु
	स्थिर __be32 *data = (स्थिर __be32 *)fw->data;
	पूर्णांक i;

	/* Write the firmware */
	क्रम (i = 0; i < fw->size / माप(u32); i++)
		ग_लिखोl(be32_to_cpu(data[i]),
		       priv->base + EIP197_CLASSIFICATION_RAMS +
		       i * माप(__be32));

	/* Exclude final 2 NOPs from size */
	वापस i - EIP197_FW_TERMINAL_NOPS;
पूर्ण

/*
 * If FW is actual production firmware, then poll क्रम its initialization
 * to complete and check अगर it is good क्रम the HW, otherwise just वापस OK.
 */
अटल bool poll_fw_पढ़ोy(काष्ठा safexcel_crypto_priv *priv, पूर्णांक fpp)
अणु
	पूर्णांक pe, pollcnt;
	u32 base, pollofs;

	अगर (fpp)
		pollofs  = EIP197_FW_FPP_READY;
	अन्यथा
		pollofs  = EIP197_FW_PUE_READY;

	क्रम (pe = 0; pe < priv->config.pes; pe++) अणु
		base = EIP197_PE_ICE_SCRATCH_RAM(pe);
		pollcnt = EIP197_FW_START_POLLCNT;
		जबतक (pollcnt &&
		       (पढ़ोl_relaxed(EIP197_PE(priv) + base +
			      pollofs) != 1)) अणु
			pollcnt--;
		पूर्ण
		अगर (!pollcnt) अणु
			dev_err(priv->dev, "FW(%d) for PE %d failed to start\n",
				fpp, pe);
			वापस false;
		पूर्ण
	पूर्ण
	वापस true;
पूर्ण

अटल bool eip197_start_firmware(काष्ठा safexcel_crypto_priv *priv,
				  पूर्णांक ipuesz, पूर्णांक अगरppsz, पूर्णांक minअगरw)
अणु
	पूर्णांक pe;
	u32 val;

	क्रम (pe = 0; pe < priv->config.pes; pe++) अणु
		/* Disable access to all program memory */
		ग_लिखोl(0, EIP197_PE(priv) + EIP197_PE_ICE_RAM_CTRL(pe));

		/* Start IFPP microengines */
		अगर (minअगरw)
			val = 0;
		अन्यथा
			val = EIP197_PE_ICE_UENG_START_OFFSET((अगरppsz - 1) &
					EIP197_PE_ICE_UENG_INIT_ALIGN_MASK) |
				EIP197_PE_ICE_UENG_DEBUG_RESET;
		ग_लिखोl(val, EIP197_PE(priv) + EIP197_PE_ICE_FPP_CTRL(pe));

		/* Start IPUE microengines */
		अगर (minअगरw)
			val = 0;
		अन्यथा
			val = EIP197_PE_ICE_UENG_START_OFFSET((ipuesz - 1) &
					EIP197_PE_ICE_UENG_INIT_ALIGN_MASK) |
				EIP197_PE_ICE_UENG_DEBUG_RESET;
		ग_लिखोl(val, EIP197_PE(priv) + EIP197_PE_ICE_PUE_CTRL(pe));
	पूर्ण

	/* For miniFW startup, there is no initialization, so always succeed */
	अगर (minअगरw)
		वापस true;

	/* Wait until all the firmwares have properly started up */
	अगर (!poll_fw_पढ़ोy(priv, 1))
		वापस false;
	अगर (!poll_fw_पढ़ोy(priv, 0))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक eip197_load_firmwares(काष्ठा safexcel_crypto_priv *priv)
अणु
	स्थिर अक्षर *fw_name[] = अणु"ifpp.bin", "ipue.bin"पूर्ण;
	स्थिर काष्ठा firmware *fw[FW_NB];
	अक्षर fw_path[37], *dir = शून्य;
	पूर्णांक i, j, ret = 0, pe;
	पूर्णांक ipuesz, अगरppsz, minअगरw = 0;

	अगर (priv->version == EIP197D_MRVL)
		dir = "eip197d";
	अन्यथा अगर (priv->version == EIP197B_MRVL ||
		 priv->version == EIP197_DEVBRD)
		dir = "eip197b";
	अन्यथा
		वापस -ENODEV;

retry_fw:
	क्रम (i = 0; i < FW_NB; i++) अणु
		snम_लिखो(fw_path, 37, "inside-secure/%s/%s", dir, fw_name[i]);
		ret = firmware_request_nowarn(&fw[i], fw_path, priv->dev);
		अगर (ret) अणु
			अगर (minअगरw || priv->version != EIP197B_MRVL)
				जाओ release_fw;

			/* Fallback to the old firmware location क्रम the
			 * EIP197b.
			 */
			ret = firmware_request_nowarn(&fw[i], fw_name[i],
						      priv->dev);
			अगर (ret)
				जाओ release_fw;
		पूर्ण
	पूर्ण

	eip197_init_firmware(priv);

	अगरppsz = eip197_ग_लिखो_firmware(priv, fw[FW_IFPP]);

	/* Enable access to IPUE program memories */
	क्रम (pe = 0; pe < priv->config.pes; pe++)
		ग_लिखोl(EIP197_PE_ICE_RAM_CTRL_PUE_PROG_EN,
		       EIP197_PE(priv) + EIP197_PE_ICE_RAM_CTRL(pe));

	ipuesz = eip197_ग_लिखो_firmware(priv, fw[FW_IPUE]);

	अगर (eip197_start_firmware(priv, ipuesz, अगरppsz, minअगरw)) अणु
		dev_dbg(priv->dev, "Firmware loaded successfully\n");
		वापस 0;
	पूर्ण

	ret = -ENODEV;

release_fw:
	क्रम (j = 0; j < i; j++)
		release_firmware(fw[j]);

	अगर (!minअगरw) अणु
		/* Retry with minअगरw path */
		dev_dbg(priv->dev, "Firmware set not (fully) present or init failed, falling back to BCLA mode\n");
		dir = "eip197_minifw";
		minअगरw = 1;
		जाओ retry_fw;
	पूर्ण

	dev_dbg(priv->dev, "Firmware load failed.\n");

	वापस ret;
पूर्ण

अटल पूर्णांक safexcel_hw_setup_cdesc_rings(काष्ठा safexcel_crypto_priv *priv)
अणु
	u32 cd_size_rnd, val;
	पूर्णांक i, cd_fetch_cnt;

	cd_size_rnd  = (priv->config.cd_size +
			(BIT(priv->hwconfig.hwdataw) - 1)) >>
		       priv->hwconfig.hwdataw;
	/* determine number of CD's we can fetch पूर्णांकo the CD FIFO as 1 block */
	अगर (priv->flags & SAFEXCEL_HW_EIP197) अणु
		/* EIP197: try to fetch enough in 1 go to keep all pipes busy */
		cd_fetch_cnt = (1 << priv->hwconfig.hwcfsize) / cd_size_rnd;
		cd_fetch_cnt = min_t(uपूर्णांक, cd_fetch_cnt,
				     (priv->config.pes * EIP197_FETCH_DEPTH));
	पूर्ण अन्यथा अणु
		/* क्रम the EIP97, just fetch all that fits minus 1 */
		cd_fetch_cnt = ((1 << priv->hwconfig.hwcfsize) /
				cd_size_rnd) - 1;
	पूर्ण
	/*
	 * Since we're using command desc's way larger than क्रमmally specअगरied,
	 * we need to check whether we can fit even 1 क्रम low-end EIP196's!
	 */
	अगर (!cd_fetch_cnt) अणु
		dev_err(priv->dev, "Unable to fit even 1 command desc!\n");
		वापस -ENODEV;
	पूर्ण

	क्रम (i = 0; i < priv->config.rings; i++) अणु
		/* ring base address */
		ग_लिखोl(lower_32_bits(priv->ring[i].cdr.base_dma),
		       EIP197_HIA_CDR(priv, i) + EIP197_HIA_xDR_RING_BASE_ADDR_LO);
		ग_लिखोl(upper_32_bits(priv->ring[i].cdr.base_dma),
		       EIP197_HIA_CDR(priv, i) + EIP197_HIA_xDR_RING_BASE_ADDR_HI);

		ग_लिखोl(EIP197_xDR_DESC_MODE_64BIT | EIP197_CDR_DESC_MODE_ADCP |
		       (priv->config.cd_offset << 14) | priv->config.cd_size,
		       EIP197_HIA_CDR(priv, i) + EIP197_HIA_xDR_DESC_SIZE);
		ग_लिखोl(((cd_fetch_cnt *
			 (cd_size_rnd << priv->hwconfig.hwdataw)) << 16) |
		       (cd_fetch_cnt * (priv->config.cd_offset / माप(u32))),
		       EIP197_HIA_CDR(priv, i) + EIP197_HIA_xDR_CFG);

		/* Configure DMA tx control */
		val = EIP197_HIA_xDR_CFG_WR_CACHE(WR_CACHE_3BITS);
		val |= EIP197_HIA_xDR_CFG_RD_CACHE(RD_CACHE_3BITS);
		ग_लिखोl(val, EIP197_HIA_CDR(priv, i) + EIP197_HIA_xDR_DMA_CFG);

		/* clear any pending पूर्णांकerrupt */
		ग_लिखोl(GENMASK(5, 0),
		       EIP197_HIA_CDR(priv, i) + EIP197_HIA_xDR_STAT);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_hw_setup_rdesc_rings(काष्ठा safexcel_crypto_priv *priv)
अणु
	u32 rd_size_rnd, val;
	पूर्णांक i, rd_fetch_cnt;

	/* determine number of RD's we can fetch पूर्णांकo the FIFO as one block */
	rd_size_rnd = (EIP197_RD64_FETCH_SIZE +
		       (BIT(priv->hwconfig.hwdataw) - 1)) >>
		      priv->hwconfig.hwdataw;
	अगर (priv->flags & SAFEXCEL_HW_EIP197) अणु
		/* EIP197: try to fetch enough in 1 go to keep all pipes busy */
		rd_fetch_cnt = (1 << priv->hwconfig.hwrfsize) / rd_size_rnd;
		rd_fetch_cnt = min_t(uपूर्णांक, rd_fetch_cnt,
				     (priv->config.pes * EIP197_FETCH_DEPTH));
	पूर्ण अन्यथा अणु
		/* क्रम the EIP97, just fetch all that fits minus 1 */
		rd_fetch_cnt = ((1 << priv->hwconfig.hwrfsize) /
				rd_size_rnd) - 1;
	पूर्ण

	क्रम (i = 0; i < priv->config.rings; i++) अणु
		/* ring base address */
		ग_लिखोl(lower_32_bits(priv->ring[i].rdr.base_dma),
		       EIP197_HIA_RDR(priv, i) + EIP197_HIA_xDR_RING_BASE_ADDR_LO);
		ग_लिखोl(upper_32_bits(priv->ring[i].rdr.base_dma),
		       EIP197_HIA_RDR(priv, i) + EIP197_HIA_xDR_RING_BASE_ADDR_HI);

		ग_लिखोl(EIP197_xDR_DESC_MODE_64BIT | (priv->config.rd_offset << 14) |
		       priv->config.rd_size,
		       EIP197_HIA_RDR(priv, i) + EIP197_HIA_xDR_DESC_SIZE);

		ग_लिखोl(((rd_fetch_cnt *
			 (rd_size_rnd << priv->hwconfig.hwdataw)) << 16) |
		       (rd_fetch_cnt * (priv->config.rd_offset / माप(u32))),
		       EIP197_HIA_RDR(priv, i) + EIP197_HIA_xDR_CFG);

		/* Configure DMA tx control */
		val = EIP197_HIA_xDR_CFG_WR_CACHE(WR_CACHE_3BITS);
		val |= EIP197_HIA_xDR_CFG_RD_CACHE(RD_CACHE_3BITS);
		val |= EIP197_HIA_xDR_WR_RES_BUF | EIP197_HIA_xDR_WR_CTRL_BUF;
		ग_लिखोl(val,
		       EIP197_HIA_RDR(priv, i) + EIP197_HIA_xDR_DMA_CFG);

		/* clear any pending पूर्णांकerrupt */
		ग_लिखोl(GENMASK(7, 0),
		       EIP197_HIA_RDR(priv, i) + EIP197_HIA_xDR_STAT);

		/* enable ring पूर्णांकerrupt */
		val = पढ़ोl(EIP197_HIA_AIC_R(priv) + EIP197_HIA_AIC_R_ENABLE_CTRL(i));
		val |= EIP197_RDR_IRQ(i);
		ग_लिखोl(val, EIP197_HIA_AIC_R(priv) + EIP197_HIA_AIC_R_ENABLE_CTRL(i));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_hw_init(काष्ठा safexcel_crypto_priv *priv)
अणु
	u32 val;
	पूर्णांक i, ret, pe, opbuflo, opbufhi;

	dev_dbg(priv->dev, "HW init: using %d pipe(s) and %d ring(s)\n",
		priv->config.pes, priv->config.rings);

	/*
	 * For EIP197's only set maximum number of TX commands to 2^5 = 32
	 * Skip क्रम the EIP97 as it करोes not have this field.
	 */
	अगर (priv->flags & SAFEXCEL_HW_EIP197) अणु
		val = पढ़ोl(EIP197_HIA_AIC(priv) + EIP197_HIA_MST_CTRL);
		val |= EIP197_MST_CTRL_TX_MAX_CMD(5);
		ग_लिखोl(val, EIP197_HIA_AIC(priv) + EIP197_HIA_MST_CTRL);
	पूर्ण

	/* Configure wr/rd cache values */
	ग_लिखोl(EIP197_MST_CTRL_RD_CACHE(RD_CACHE_4BITS) |
	       EIP197_MST_CTRL_WD_CACHE(WR_CACHE_4BITS),
	       EIP197_HIA_GEN_CFG(priv) + EIP197_MST_CTRL);

	/* Interrupts reset */

	/* Disable all global पूर्णांकerrupts */
	ग_लिखोl(0, EIP197_HIA_AIC_G(priv) + EIP197_HIA_AIC_G_ENABLE_CTRL);

	/* Clear any pending पूर्णांकerrupt */
	ग_लिखोl(GENMASK(31, 0), EIP197_HIA_AIC_G(priv) + EIP197_HIA_AIC_G_ACK);

	/* Processing Engine configuration */
	क्रम (pe = 0; pe < priv->config.pes; pe++) अणु
		/* Data Fetch Engine configuration */

		/* Reset all DFE thपढ़ोs */
		ग_लिखोl(EIP197_DxE_THR_CTRL_RESET_PE,
		       EIP197_HIA_DFE_THR(priv) + EIP197_HIA_DFE_THR_CTRL(pe));

		अगर (priv->flags & EIP197_PE_ARB)
			/* Reset HIA input पूर्णांकerface arbiter (अगर present) */
			ग_लिखोl(EIP197_HIA_RA_PE_CTRL_RESET,
			       EIP197_HIA_AIC(priv) + EIP197_HIA_RA_PE_CTRL(pe));

		/* DMA transfer size to use */
		val = EIP197_HIA_DFE_CFG_DIS_DEBUG;
		val |= EIP197_HIA_DxE_CFG_MIN_DATA_SIZE(6) |
		       EIP197_HIA_DxE_CFG_MAX_DATA_SIZE(9);
		val |= EIP197_HIA_DxE_CFG_MIN_CTRL_SIZE(6) |
		       EIP197_HIA_DxE_CFG_MAX_CTRL_SIZE(7);
		val |= EIP197_HIA_DxE_CFG_DATA_CACHE_CTRL(RD_CACHE_3BITS);
		val |= EIP197_HIA_DxE_CFG_CTRL_CACHE_CTRL(RD_CACHE_3BITS);
		ग_लिखोl(val, EIP197_HIA_DFE(priv) + EIP197_HIA_DFE_CFG(pe));

		/* Leave the DFE thपढ़ोs reset state */
		ग_लिखोl(0, EIP197_HIA_DFE_THR(priv) + EIP197_HIA_DFE_THR_CTRL(pe));

		/* Configure the processing engine thresholds */
		ग_लिखोl(EIP197_PE_IN_xBUF_THRES_MIN(6) |
		       EIP197_PE_IN_xBUF_THRES_MAX(9),
		       EIP197_PE(priv) + EIP197_PE_IN_DBUF_THRES(pe));
		ग_लिखोl(EIP197_PE_IN_xBUF_THRES_MIN(6) |
		       EIP197_PE_IN_xBUF_THRES_MAX(7),
		       EIP197_PE(priv) + EIP197_PE_IN_TBUF_THRES(pe));

		अगर (priv->flags & SAFEXCEL_HW_EIP197)
			/* enable HIA input पूर्णांकerface arbiter and rings */
			ग_लिखोl(EIP197_HIA_RA_PE_CTRL_EN |
			       GENMASK(priv->config.rings - 1, 0),
			       EIP197_HIA_AIC(priv) + EIP197_HIA_RA_PE_CTRL(pe));

		/* Data Store Engine configuration */

		/* Reset all DSE thपढ़ोs */
		ग_लिखोl(EIP197_DxE_THR_CTRL_RESET_PE,
		       EIP197_HIA_DSE_THR(priv) + EIP197_HIA_DSE_THR_CTRL(pe));

		/* Wait क्रम all DSE thपढ़ोs to complete */
		जबतक ((पढ़ोl(EIP197_HIA_DSE_THR(priv) + EIP197_HIA_DSE_THR_STAT(pe)) &
			GENMASK(15, 12)) != GENMASK(15, 12))
			;

		/* DMA transfer size to use */
		अगर (priv->hwconfig.hwnumpes > 4) अणु
			opbuflo = 9;
			opbufhi = 10;
		पूर्ण अन्यथा अणु
			opbuflo = 7;
			opbufhi = 8;
		पूर्ण
		val = EIP197_HIA_DSE_CFG_DIS_DEBUG;
		val |= EIP197_HIA_DxE_CFG_MIN_DATA_SIZE(opbuflo) |
		       EIP197_HIA_DxE_CFG_MAX_DATA_SIZE(opbufhi);
		val |= EIP197_HIA_DxE_CFG_DATA_CACHE_CTRL(WR_CACHE_3BITS);
		val |= EIP197_HIA_DSE_CFG_ALWAYS_BUFFERABLE;
		/* FIXME: instability issues can occur क्रम EIP97 but disabling
		 * it impacts perक्रमmance.
		 */
		अगर (priv->flags & SAFEXCEL_HW_EIP197)
			val |= EIP197_HIA_DSE_CFG_EN_SINGLE_WR;
		ग_लिखोl(val, EIP197_HIA_DSE(priv) + EIP197_HIA_DSE_CFG(pe));

		/* Leave the DSE thपढ़ोs reset state */
		ग_लिखोl(0, EIP197_HIA_DSE_THR(priv) + EIP197_HIA_DSE_THR_CTRL(pe));

		/* Configure the processing engine thresholds */
		ग_लिखोl(EIP197_PE_OUT_DBUF_THRES_MIN(opbuflo) |
		       EIP197_PE_OUT_DBUF_THRES_MAX(opbufhi),
		       EIP197_PE(priv) + EIP197_PE_OUT_DBUF_THRES(pe));

		/* Processing Engine configuration */

		/* Token & context configuration */
		val = EIP197_PE_EIP96_TOKEN_CTRL_CTX_UPDATES |
		      EIP197_PE_EIP96_TOKEN_CTRL_NO_TOKEN_WAIT |
		      EIP197_PE_EIP96_TOKEN_CTRL_ENABLE_TIMEOUT;
		ग_लिखोl(val, EIP197_PE(priv) + EIP197_PE_EIP96_TOKEN_CTRL(pe));

		/* H/W capabilities selection: just enable everything */
		ग_लिखोl(EIP197_FUNCTION_ALL,
		       EIP197_PE(priv) + EIP197_PE_EIP96_FUNCTION_EN(pe));
		ग_लिखोl(EIP197_FUNCTION_ALL,
		       EIP197_PE(priv) + EIP197_PE_EIP96_FUNCTION2_EN(pe));
	पूर्ण

	/* Command Descriptor Rings prepare */
	क्रम (i = 0; i < priv->config.rings; i++) अणु
		/* Clear पूर्णांकerrupts क्रम this ring */
		ग_लिखोl(GENMASK(31, 0),
		       EIP197_HIA_AIC_R(priv) + EIP197_HIA_AIC_R_ENABLE_CLR(i));

		/* Disable बाह्यal triggering */
		ग_लिखोl(0, EIP197_HIA_CDR(priv, i) + EIP197_HIA_xDR_CFG);

		/* Clear the pending prepared counter */
		ग_लिखोl(EIP197_xDR_PREP_CLR_COUNT,
		       EIP197_HIA_CDR(priv, i) + EIP197_HIA_xDR_PREP_COUNT);

		/* Clear the pending processed counter */
		ग_लिखोl(EIP197_xDR_PROC_CLR_COUNT,
		       EIP197_HIA_CDR(priv, i) + EIP197_HIA_xDR_PROC_COUNT);

		ग_लिखोl(0,
		       EIP197_HIA_CDR(priv, i) + EIP197_HIA_xDR_PREP_PNTR);
		ग_लिखोl(0,
		       EIP197_HIA_CDR(priv, i) + EIP197_HIA_xDR_PROC_PNTR);

		ग_लिखोl((EIP197_DEFAULT_RING_SIZE * priv->config.cd_offset),
		       EIP197_HIA_CDR(priv, i) + EIP197_HIA_xDR_RING_SIZE);
	पूर्ण

	/* Result Descriptor Ring prepare */
	क्रम (i = 0; i < priv->config.rings; i++) अणु
		/* Disable बाह्यal triggering*/
		ग_लिखोl(0, EIP197_HIA_RDR(priv, i) + EIP197_HIA_xDR_CFG);

		/* Clear the pending prepared counter */
		ग_लिखोl(EIP197_xDR_PREP_CLR_COUNT,
		       EIP197_HIA_RDR(priv, i) + EIP197_HIA_xDR_PREP_COUNT);

		/* Clear the pending processed counter */
		ग_लिखोl(EIP197_xDR_PROC_CLR_COUNT,
		       EIP197_HIA_RDR(priv, i) + EIP197_HIA_xDR_PROC_COUNT);

		ग_लिखोl(0,
		       EIP197_HIA_RDR(priv, i) + EIP197_HIA_xDR_PREP_PNTR);
		ग_लिखोl(0,
		       EIP197_HIA_RDR(priv, i) + EIP197_HIA_xDR_PROC_PNTR);

		/* Ring size */
		ग_लिखोl((EIP197_DEFAULT_RING_SIZE * priv->config.rd_offset),
		       EIP197_HIA_RDR(priv, i) + EIP197_HIA_xDR_RING_SIZE);
	पूर्ण

	क्रम (pe = 0; pe < priv->config.pes; pe++) अणु
		/* Enable command descriptor rings */
		ग_लिखोl(EIP197_DxE_THR_CTRL_EN | GENMASK(priv->config.rings - 1, 0),
		       EIP197_HIA_DFE_THR(priv) + EIP197_HIA_DFE_THR_CTRL(pe));

		/* Enable result descriptor rings */
		ग_लिखोl(EIP197_DxE_THR_CTRL_EN | GENMASK(priv->config.rings - 1, 0),
		       EIP197_HIA_DSE_THR(priv) + EIP197_HIA_DSE_THR_CTRL(pe));
	पूर्ण

	/* Clear any HIA पूर्णांकerrupt */
	ग_लिखोl(GENMASK(30, 20), EIP197_HIA_AIC_G(priv) + EIP197_HIA_AIC_G_ACK);

	अगर (priv->flags & EIP197_SIMPLE_TRC) अणु
		ग_लिखोl(EIP197_STRC_CONFIG_INIT |
		       EIP197_STRC_CONFIG_LARGE_REC(EIP197_CS_TRC_REC_WC) |
		       EIP197_STRC_CONFIG_SMALL_REC(EIP197_CS_TRC_REC_WC),
		       priv->base + EIP197_STRC_CONFIG);
		ग_लिखोl(EIP197_PE_EIP96_TOKEN_CTRL2_CTX_DONE,
		       EIP197_PE(priv) + EIP197_PE_EIP96_TOKEN_CTRL2(0));
	पूर्ण अन्यथा अगर (priv->flags & SAFEXCEL_HW_EIP197) अणु
		ret = eip197_trc_cache_init(priv);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (priv->flags & EIP197_ICE) अणु
		ret = eip197_load_firmwares(priv);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस safexcel_hw_setup_cdesc_rings(priv) ?:
	       safexcel_hw_setup_rdesc_rings(priv) ?:
	       0;
पूर्ण

/* Called with ring's lock taken */
अटल व्योम safexcel_try_push_requests(काष्ठा safexcel_crypto_priv *priv,
				       पूर्णांक ring)
अणु
	पूर्णांक coal = min_t(पूर्णांक, priv->ring[ring].requests, EIP197_MAX_BATCH_SZ);

	अगर (!coal)
		वापस;

	/* Configure when we want an पूर्णांकerrupt */
	ग_लिखोl(EIP197_HIA_RDR_THRESH_PKT_MODE |
	       EIP197_HIA_RDR_THRESH_PROC_PKT(coal),
	       EIP197_HIA_RDR(priv, ring) + EIP197_HIA_xDR_THRESH);
पूर्ण

व्योम safexcel_dequeue(काष्ठा safexcel_crypto_priv *priv, पूर्णांक ring)
अणु
	काष्ठा crypto_async_request *req, *backlog;
	काष्ठा safexcel_context *ctx;
	पूर्णांक ret, nreq = 0, cdesc = 0, rdesc = 0, commands, results;

	/* If a request wasn't properly dequeued because of a lack of resources,
	 * proceeded it first,
	 */
	req = priv->ring[ring].req;
	backlog = priv->ring[ring].backlog;
	अगर (req)
		जाओ handle_req;

	जबतक (true) अणु
		spin_lock_bh(&priv->ring[ring].queue_lock);
		backlog = crypto_get_backlog(&priv->ring[ring].queue);
		req = crypto_dequeue_request(&priv->ring[ring].queue);
		spin_unlock_bh(&priv->ring[ring].queue_lock);

		अगर (!req) अणु
			priv->ring[ring].req = शून्य;
			priv->ring[ring].backlog = शून्य;
			जाओ finalize;
		पूर्ण

handle_req:
		ctx = crypto_tfm_ctx(req->tfm);
		ret = ctx->send(req, ring, &commands, &results);
		अगर (ret)
			जाओ request_failed;

		अगर (backlog)
			backlog->complete(backlog, -EINPROGRESS);

		/* In हाल the send() helper did not issue any command to push
		 * to the engine because the input data was cached, जारी to
		 * dequeue other requests as this is valid and not an error.
		 */
		अगर (!commands && !results)
			जारी;

		cdesc += commands;
		rdesc += results;
		nreq++;
	पूर्ण

request_failed:
	/* Not enough resources to handle all the requests. Bail out and save
	 * the request and the backlog क्रम the next dequeue call (per-ring).
	 */
	priv->ring[ring].req = req;
	priv->ring[ring].backlog = backlog;

finalize:
	अगर (!nreq)
		वापस;

	spin_lock_bh(&priv->ring[ring].lock);

	priv->ring[ring].requests += nreq;

	अगर (!priv->ring[ring].busy) अणु
		safexcel_try_push_requests(priv, ring);
		priv->ring[ring].busy = true;
	पूर्ण

	spin_unlock_bh(&priv->ring[ring].lock);

	/* let the RDR know we have pending descriptors */
	ग_लिखोl((rdesc * priv->config.rd_offset),
	       EIP197_HIA_RDR(priv, ring) + EIP197_HIA_xDR_PREP_COUNT);

	/* let the CDR know we have pending descriptors */
	ग_लिखोl((cdesc * priv->config.cd_offset),
	       EIP197_HIA_CDR(priv, ring) + EIP197_HIA_xDR_PREP_COUNT);
पूर्ण

अंतरभूत पूर्णांक safexcel_rdesc_check_errors(काष्ठा safexcel_crypto_priv *priv,
				       व्योम *rdp)
अणु
	काष्ठा safexcel_result_desc *rdesc = rdp;
	काष्ठा result_data_desc *result_data = rdp + priv->config.res_offset;

	अगर (likely((!rdesc->last_seg) || /* Rest only valid अगर last seg! */
		   ((!rdesc->descriptor_overflow) &&
		    (!rdesc->buffer_overflow) &&
		    (!result_data->error_code))))
		वापस 0;

	अगर (rdesc->descriptor_overflow)
		dev_err(priv->dev, "Descriptor overflow detected");

	अगर (rdesc->buffer_overflow)
		dev_err(priv->dev, "Buffer overflow detected");

	अगर (result_data->error_code & 0x4066) अणु
		/* Fatal error (bits 1,2,5,6 & 14) */
		dev_err(priv->dev,
			"result descriptor error (%x)",
			result_data->error_code);

		वापस -EIO;
	पूर्ण अन्यथा अगर (result_data->error_code &
		   (BIT(7) | BIT(4) | BIT(3) | BIT(0))) अणु
		/*
		 * Give priority over authentication fails:
		 * Blocksize, length & overflow errors,
		 * something wrong with the input!
		 */
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (result_data->error_code & BIT(9)) अणु
		/* Authentication failed */
		वापस -EBADMSG;
	पूर्ण

	/* All other non-fatal errors */
	वापस -EINVAL;
पूर्ण

अंतरभूत व्योम safexcel_rdr_req_set(काष्ठा safexcel_crypto_priv *priv,
				 पूर्णांक ring,
				 काष्ठा safexcel_result_desc *rdesc,
				 काष्ठा crypto_async_request *req)
अणु
	पूर्णांक i = safexcel_ring_rdr_rdesc_index(priv, ring, rdesc);

	priv->ring[ring].rdr_req[i] = req;
पूर्ण

अंतरभूत काष्ठा crypto_async_request *
safexcel_rdr_req_get(काष्ठा safexcel_crypto_priv *priv, पूर्णांक ring)
अणु
	पूर्णांक i = safexcel_ring_first_rdr_index(priv, ring);

	वापस priv->ring[ring].rdr_req[i];
पूर्ण

व्योम safexcel_complete(काष्ठा safexcel_crypto_priv *priv, पूर्णांक ring)
अणु
	काष्ठा safexcel_command_desc *cdesc;

	/* Acknowledge the command descriptors */
	करो अणु
		cdesc = safexcel_ring_next_rptr(priv, &priv->ring[ring].cdr);
		अगर (IS_ERR(cdesc)) अणु
			dev_err(priv->dev,
				"Could not retrieve the command descriptor\n");
			वापस;
		पूर्ण
	पूर्ण जबतक (!cdesc->last_seg);
पूर्ण

व्योम safexcel_inv_complete(काष्ठा crypto_async_request *req, पूर्णांक error)
अणु
	काष्ठा safexcel_inv_result *result = req->data;

	अगर (error == -EINPROGRESS)
		वापस;

	result->error = error;
	complete(&result->completion);
पूर्ण

पूर्णांक safexcel_invalidate_cache(काष्ठा crypto_async_request *async,
			      काष्ठा safexcel_crypto_priv *priv,
			      dma_addr_t ctxr_dma, पूर्णांक ring)
अणु
	काष्ठा safexcel_command_desc *cdesc;
	काष्ठा safexcel_result_desc *rdesc;
	काष्ठा safexcel_token  *dmmy;
	पूर्णांक ret = 0;

	/* Prepare command descriptor */
	cdesc = safexcel_add_cdesc(priv, ring, true, true, 0, 0, 0, ctxr_dma,
				   &dmmy);
	अगर (IS_ERR(cdesc))
		वापस PTR_ERR(cdesc);

	cdesc->control_data.type = EIP197_TYPE_EXTENDED;
	cdesc->control_data.options = 0;
	cdesc->control_data.context_lo &= ~EIP197_CONTEXT_SIZE_MASK;
	cdesc->control_data.control0 = CONTEXT_CONTROL_INV_TR;

	/* Prepare result descriptor */
	rdesc = safexcel_add_rdesc(priv, ring, true, true, 0, 0);

	अगर (IS_ERR(rdesc)) अणु
		ret = PTR_ERR(rdesc);
		जाओ cdesc_rollback;
	पूर्ण

	safexcel_rdr_req_set(priv, ring, rdesc, async);

	वापस ret;

cdesc_rollback:
	safexcel_ring_rollback_wptr(priv, &priv->ring[ring].cdr);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम safexcel_handle_result_descriptor(काष्ठा safexcel_crypto_priv *priv,
						     पूर्णांक ring)
अणु
	काष्ठा crypto_async_request *req;
	काष्ठा safexcel_context *ctx;
	पूर्णांक ret, i, nreq, ndesc, tot_descs, handled = 0;
	bool should_complete;

handle_results:
	tot_descs = 0;

	nreq = पढ़ोl(EIP197_HIA_RDR(priv, ring) + EIP197_HIA_xDR_PROC_COUNT);
	nreq >>= EIP197_xDR_PROC_xD_PKT_OFFSET;
	nreq &= EIP197_xDR_PROC_xD_PKT_MASK;
	अगर (!nreq)
		जाओ requests_left;

	क्रम (i = 0; i < nreq; i++) अणु
		req = safexcel_rdr_req_get(priv, ring);

		ctx = crypto_tfm_ctx(req->tfm);
		ndesc = ctx->handle_result(priv, ring, req,
					   &should_complete, &ret);
		अगर (ndesc < 0) अणु
			dev_err(priv->dev, "failed to handle result (%d)\n",
				ndesc);
			जाओ acknowledge;
		पूर्ण

		अगर (should_complete) अणु
			local_bh_disable();
			req->complete(req, ret);
			local_bh_enable();
		पूर्ण

		tot_descs += ndesc;
		handled++;
	पूर्ण

acknowledge:
	अगर (i)
		ग_लिखोl(EIP197_xDR_PROC_xD_PKT(i) |
		       (tot_descs * priv->config.rd_offset),
		       EIP197_HIA_RDR(priv, ring) + EIP197_HIA_xDR_PROC_COUNT);

	/* If the number of requests overflowed the counter, try to proceed more
	 * requests.
	 */
	अगर (nreq == EIP197_xDR_PROC_xD_PKT_MASK)
		जाओ handle_results;

requests_left:
	spin_lock_bh(&priv->ring[ring].lock);

	priv->ring[ring].requests -= handled;
	safexcel_try_push_requests(priv, ring);

	अगर (!priv->ring[ring].requests)
		priv->ring[ring].busy = false;

	spin_unlock_bh(&priv->ring[ring].lock);
पूर्ण

अटल व्योम safexcel_dequeue_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा safexcel_work_data *data =
			container_of(work, काष्ठा safexcel_work_data, work);

	safexcel_dequeue(data->priv, data->ring);
पूर्ण

काष्ठा safexcel_ring_irq_data अणु
	काष्ठा safexcel_crypto_priv *priv;
	पूर्णांक ring;
पूर्ण;

अटल irqवापस_t safexcel_irq_ring(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा safexcel_ring_irq_data *irq_data = data;
	काष्ठा safexcel_crypto_priv *priv = irq_data->priv;
	पूर्णांक ring = irq_data->ring, rc = IRQ_NONE;
	u32 status, stat;

	status = पढ़ोl(EIP197_HIA_AIC_R(priv) + EIP197_HIA_AIC_R_ENABLED_STAT(ring));
	अगर (!status)
		वापस rc;

	/* RDR पूर्णांकerrupts */
	अगर (status & EIP197_RDR_IRQ(ring)) अणु
		stat = पढ़ोl(EIP197_HIA_RDR(priv, ring) + EIP197_HIA_xDR_STAT);

		अगर (unlikely(stat & EIP197_xDR_ERR)) अणु
			/*
			 * Fatal error, the RDR is unusable and must be
			 * reinitialized. This should not happen under
			 * normal circumstances.
			 */
			dev_err(priv->dev, "RDR: fatal error.\n");
		पूर्ण अन्यथा अगर (likely(stat & EIP197_xDR_THRESH)) अणु
			rc = IRQ_WAKE_THREAD;
		पूर्ण

		/* ACK the पूर्णांकerrupts */
		ग_लिखोl(stat & 0xff,
		       EIP197_HIA_RDR(priv, ring) + EIP197_HIA_xDR_STAT);
	पूर्ण

	/* ACK the पूर्णांकerrupts */
	ग_लिखोl(status, EIP197_HIA_AIC_R(priv) + EIP197_HIA_AIC_R_ACK(ring));

	वापस rc;
पूर्ण

अटल irqवापस_t safexcel_irq_ring_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा safexcel_ring_irq_data *irq_data = data;
	काष्ठा safexcel_crypto_priv *priv = irq_data->priv;
	पूर्णांक ring = irq_data->ring;

	safexcel_handle_result_descriptor(priv, ring);

	queue_work(priv->ring[ring].workqueue,
		   &priv->ring[ring].work_data.work);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक safexcel_request_ring_irq(व्योम *pdev, पूर्णांक irqid,
				     पूर्णांक is_pci_dev,
				     पूर्णांक ring_id,
				     irq_handler_t handler,
				     irq_handler_t thपढ़ोed_handler,
				     काष्ठा safexcel_ring_irq_data *ring_irq_priv)
अणु
	पूर्णांक ret, irq, cpu;
	काष्ठा device *dev;

	अगर (IS_ENABLED(CONFIG_PCI) && is_pci_dev) अणु
		काष्ठा pci_dev *pci_pdev = pdev;

		dev = &pci_pdev->dev;
		irq = pci_irq_vector(pci_pdev, irqid);
		अगर (irq < 0) अणु
			dev_err(dev, "unable to get device MSI IRQ %d (err %d)\n",
				irqid, irq);
			वापस irq;
		पूर्ण
	पूर्ण अन्यथा अगर (IS_ENABLED(CONFIG_OF)) अणु
		काष्ठा platक्रमm_device *plf_pdev = pdev;
		अक्षर irq_name[6] = अणु0पूर्ण; /* "ringX\0" */

		snम_लिखो(irq_name, 6, "ring%d", irqid);
		dev = &plf_pdev->dev;
		irq = platक्रमm_get_irq_byname(plf_pdev, irq_name);

		अगर (irq < 0)
			वापस irq;
	पूर्ण अन्यथा अणु
		वापस -ENXIO;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(dev, irq, handler,
					thपढ़ोed_handler, IRQF_ONESHOT,
					dev_name(dev), ring_irq_priv);
	अगर (ret) अणु
		dev_err(dev, "unable to request IRQ %d\n", irq);
		वापस ret;
	पूर्ण

	/* Set affinity */
	cpu = cpumask_local_spपढ़ो(ring_id, NUMA_NO_NODE);
	irq_set_affinity_hपूर्णांक(irq, get_cpu_mask(cpu));

	वापस irq;
पूर्ण

अटल काष्ठा safexcel_alg_ढाँचा *safexcel_algs[] = अणु
	&safexcel_alg_ecb_des,
	&safexcel_alg_cbc_des,
	&safexcel_alg_ecb_des3_ede,
	&safexcel_alg_cbc_des3_ede,
	&safexcel_alg_ecb_aes,
	&safexcel_alg_cbc_aes,
	&safexcel_alg_cfb_aes,
	&safexcel_alg_ofb_aes,
	&safexcel_alg_ctr_aes,
	&safexcel_alg_md5,
	&safexcel_alg_sha1,
	&safexcel_alg_sha224,
	&safexcel_alg_sha256,
	&safexcel_alg_sha384,
	&safexcel_alg_sha512,
	&safexcel_alg_hmac_md5,
	&safexcel_alg_hmac_sha1,
	&safexcel_alg_hmac_sha224,
	&safexcel_alg_hmac_sha256,
	&safexcel_alg_hmac_sha384,
	&safexcel_alg_hmac_sha512,
	&safexcel_alg_authenc_hmac_sha1_cbc_aes,
	&safexcel_alg_authenc_hmac_sha224_cbc_aes,
	&safexcel_alg_authenc_hmac_sha256_cbc_aes,
	&safexcel_alg_authenc_hmac_sha384_cbc_aes,
	&safexcel_alg_authenc_hmac_sha512_cbc_aes,
	&safexcel_alg_authenc_hmac_sha1_cbc_des3_ede,
	&safexcel_alg_authenc_hmac_sha1_ctr_aes,
	&safexcel_alg_authenc_hmac_sha224_ctr_aes,
	&safexcel_alg_authenc_hmac_sha256_ctr_aes,
	&safexcel_alg_authenc_hmac_sha384_ctr_aes,
	&safexcel_alg_authenc_hmac_sha512_ctr_aes,
	&safexcel_alg_xts_aes,
	&safexcel_alg_gcm,
	&safexcel_alg_ccm,
	&safexcel_alg_crc32,
	&safexcel_alg_cbcmac,
	&safexcel_alg_xcbcmac,
	&safexcel_alg_cmac,
	&safexcel_alg_chacha20,
	&safexcel_alg_chachapoly,
	&safexcel_alg_chachapoly_esp,
	&safexcel_alg_sm3,
	&safexcel_alg_hmac_sm3,
	&safexcel_alg_ecb_sm4,
	&safexcel_alg_cbc_sm4,
	&safexcel_alg_ofb_sm4,
	&safexcel_alg_cfb_sm4,
	&safexcel_alg_ctr_sm4,
	&safexcel_alg_authenc_hmac_sha1_cbc_sm4,
	&safexcel_alg_authenc_hmac_sm3_cbc_sm4,
	&safexcel_alg_authenc_hmac_sha1_ctr_sm4,
	&safexcel_alg_authenc_hmac_sm3_ctr_sm4,
	&safexcel_alg_sha3_224,
	&safexcel_alg_sha3_256,
	&safexcel_alg_sha3_384,
	&safexcel_alg_sha3_512,
	&safexcel_alg_hmac_sha3_224,
	&safexcel_alg_hmac_sha3_256,
	&safexcel_alg_hmac_sha3_384,
	&safexcel_alg_hmac_sha3_512,
	&safexcel_alg_authenc_hmac_sha1_cbc_des,
	&safexcel_alg_authenc_hmac_sha256_cbc_des3_ede,
	&safexcel_alg_authenc_hmac_sha224_cbc_des3_ede,
	&safexcel_alg_authenc_hmac_sha512_cbc_des3_ede,
	&safexcel_alg_authenc_hmac_sha384_cbc_des3_ede,
	&safexcel_alg_authenc_hmac_sha256_cbc_des,
	&safexcel_alg_authenc_hmac_sha224_cbc_des,
	&safexcel_alg_authenc_hmac_sha512_cbc_des,
	&safexcel_alg_authenc_hmac_sha384_cbc_des,
	&safexcel_alg_rfc4106_gcm,
	&safexcel_alg_rfc4543_gcm,
	&safexcel_alg_rfc4309_ccm,
पूर्ण;

अटल पूर्णांक safexcel_रेजिस्टर_algorithms(काष्ठा safexcel_crypto_priv *priv)
अणु
	पूर्णांक i, j, ret = 0;

	क्रम (i = 0; i < ARRAY_SIZE(safexcel_algs); i++) अणु
		safexcel_algs[i]->priv = priv;

		/* Do we have all required base algorithms available? */
		अगर ((safexcel_algs[i]->algo_mask & priv->hwconfig.algo_flags) !=
		    safexcel_algs[i]->algo_mask)
			/* No, so करोn't रेजिस्टर this ciphersuite */
			जारी;

		अगर (safexcel_algs[i]->type == SAFEXCEL_ALG_TYPE_SKCIPHER)
			ret = crypto_रेजिस्टर_skcipher(&safexcel_algs[i]->alg.skcipher);
		अन्यथा अगर (safexcel_algs[i]->type == SAFEXCEL_ALG_TYPE_AEAD)
			ret = crypto_रेजिस्टर_aead(&safexcel_algs[i]->alg.aead);
		अन्यथा
			ret = crypto_रेजिस्टर_ahash(&safexcel_algs[i]->alg.ahash);

		अगर (ret)
			जाओ fail;
	पूर्ण

	वापस 0;

fail:
	क्रम (j = 0; j < i; j++) अणु
		/* Do we have all required base algorithms available? */
		अगर ((safexcel_algs[j]->algo_mask & priv->hwconfig.algo_flags) !=
		    safexcel_algs[j]->algo_mask)
			/* No, so करोn't unरेजिस्टर this ciphersuite */
			जारी;

		अगर (safexcel_algs[j]->type == SAFEXCEL_ALG_TYPE_SKCIPHER)
			crypto_unरेजिस्टर_skcipher(&safexcel_algs[j]->alg.skcipher);
		अन्यथा अगर (safexcel_algs[j]->type == SAFEXCEL_ALG_TYPE_AEAD)
			crypto_unरेजिस्टर_aead(&safexcel_algs[j]->alg.aead);
		अन्यथा
			crypto_unरेजिस्टर_ahash(&safexcel_algs[j]->alg.ahash);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम safexcel_unरेजिस्टर_algorithms(काष्ठा safexcel_crypto_priv *priv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(safexcel_algs); i++) अणु
		/* Do we have all required base algorithms available? */
		अगर ((safexcel_algs[i]->algo_mask & priv->hwconfig.algo_flags) !=
		    safexcel_algs[i]->algo_mask)
			/* No, so करोn't unरेजिस्टर this ciphersuite */
			जारी;

		अगर (safexcel_algs[i]->type == SAFEXCEL_ALG_TYPE_SKCIPHER)
			crypto_unरेजिस्टर_skcipher(&safexcel_algs[i]->alg.skcipher);
		अन्यथा अगर (safexcel_algs[i]->type == SAFEXCEL_ALG_TYPE_AEAD)
			crypto_unरेजिस्टर_aead(&safexcel_algs[i]->alg.aead);
		अन्यथा
			crypto_unरेजिस्टर_ahash(&safexcel_algs[i]->alg.ahash);
	पूर्ण
पूर्ण

अटल व्योम safexcel_configure(काष्ठा safexcel_crypto_priv *priv)
अणु
	u32 mask = BIT(priv->hwconfig.hwdataw) - 1;

	priv->config.pes = priv->hwconfig.hwnumpes;
	priv->config.rings = min_t(u32, priv->hwconfig.hwnumrings, max_rings);
	/* Cannot currently support more rings than we have ring AICs! */
	priv->config.rings = min_t(u32, priv->config.rings,
					priv->hwconfig.hwnumraic);

	priv->config.cd_size = EIP197_CD64_FETCH_SIZE;
	priv->config.cd_offset = (priv->config.cd_size + mask) & ~mask;
	priv->config.cdsh_offset = (EIP197_MAX_TOKENS + mask) & ~mask;

	/* res token is behind the descr, but ofs must be rounded to buswdth */
	priv->config.res_offset = (EIP197_RD64_FETCH_SIZE + mask) & ~mask;
	/* now the size of the descr is this 1st part plus the result काष्ठा */
	priv->config.rd_size    = priv->config.res_offset +
				  EIP197_RD64_RESULT_SIZE;
	priv->config.rd_offset = (priv->config.rd_size + mask) & ~mask;

	/* convert dwords to bytes */
	priv->config.cd_offset *= माप(u32);
	priv->config.cdsh_offset *= माप(u32);
	priv->config.rd_offset *= माप(u32);
	priv->config.res_offset *= माप(u32);
पूर्ण

अटल व्योम safexcel_init_रेजिस्टर_offsets(काष्ठा safexcel_crypto_priv *priv)
अणु
	काष्ठा safexcel_रेजिस्टर_offsets *offsets = &priv->offsets;

	अगर (priv->flags & SAFEXCEL_HW_EIP197) अणु
		offsets->hia_aic	= EIP197_HIA_AIC_BASE;
		offsets->hia_aic_g	= EIP197_HIA_AIC_G_BASE;
		offsets->hia_aic_r	= EIP197_HIA_AIC_R_BASE;
		offsets->hia_aic_xdr	= EIP197_HIA_AIC_xDR_BASE;
		offsets->hia_dfe	= EIP197_HIA_DFE_BASE;
		offsets->hia_dfe_thr	= EIP197_HIA_DFE_THR_BASE;
		offsets->hia_dse	= EIP197_HIA_DSE_BASE;
		offsets->hia_dse_thr	= EIP197_HIA_DSE_THR_BASE;
		offsets->hia_gen_cfg	= EIP197_HIA_GEN_CFG_BASE;
		offsets->pe		= EIP197_PE_BASE;
		offsets->global		= EIP197_GLOBAL_BASE;
	पूर्ण अन्यथा अणु
		offsets->hia_aic	= EIP97_HIA_AIC_BASE;
		offsets->hia_aic_g	= EIP97_HIA_AIC_G_BASE;
		offsets->hia_aic_r	= EIP97_HIA_AIC_R_BASE;
		offsets->hia_aic_xdr	= EIP97_HIA_AIC_xDR_BASE;
		offsets->hia_dfe	= EIP97_HIA_DFE_BASE;
		offsets->hia_dfe_thr	= EIP97_HIA_DFE_THR_BASE;
		offsets->hia_dse	= EIP97_HIA_DSE_BASE;
		offsets->hia_dse_thr	= EIP97_HIA_DSE_THR_BASE;
		offsets->hia_gen_cfg	= EIP97_HIA_GEN_CFG_BASE;
		offsets->pe		= EIP97_PE_BASE;
		offsets->global		= EIP97_GLOBAL_BASE;
	पूर्ण
पूर्ण

/*
 * Generic part of probe routine, shared by platक्रमm and PCI driver
 *
 * Assumes IO resources have been mapped, निजी data mem has been allocated,
 * घड़ीs have been enabled, device poपूर्णांकer has been asचिन्हित etc.
 *
 */
अटल पूर्णांक safexcel_probe_generic(व्योम *pdev,
				  काष्ठा safexcel_crypto_priv *priv,
				  पूर्णांक is_pci_dev)
अणु
	काष्ठा device *dev = priv->dev;
	u32 peid, version, mask, val, hiaopt, hwopt, peopt;
	पूर्णांक i, ret, hwctg;

	priv->context_pool = dmam_pool_create("safexcel-context", dev,
					      माप(काष्ठा safexcel_context_record),
					      1, 0);
	अगर (!priv->context_pool)
		वापस -ENOMEM;

	/*
	 * First try the EIP97 HIA version regs
	 * For the EIP197, this is guaranteed to NOT वापस any of the test
	 * values
	 */
	version = पढ़ोl(priv->base + EIP97_HIA_AIC_BASE + EIP197_HIA_VERSION);

	mask = 0;  /* करो not swap */
	अगर (EIP197_REG_LO16(version) == EIP197_HIA_VERSION_LE) अणु
		priv->hwconfig.hiaver = EIP197_VERSION_MASK(version);
	पूर्ण अन्यथा अगर (EIP197_REG_HI16(version) == EIP197_HIA_VERSION_BE) अणु
		/* पढ़ो back byte-swapped, so complement byte swap bits */
		mask = EIP197_MST_CTRL_BYTE_SWAP_BITS;
		priv->hwconfig.hiaver = EIP197_VERSION_SWAP(version);
	पूर्ण अन्यथा अणु
		/* So it wasn't an EIP97 ... maybe it's an EIP197? */
		version = पढ़ोl(priv->base + EIP197_HIA_AIC_BASE +
				EIP197_HIA_VERSION);
		अगर (EIP197_REG_LO16(version) == EIP197_HIA_VERSION_LE) अणु
			priv->hwconfig.hiaver = EIP197_VERSION_MASK(version);
			priv->flags |= SAFEXCEL_HW_EIP197;
		पूर्ण अन्यथा अगर (EIP197_REG_HI16(version) ==
			   EIP197_HIA_VERSION_BE) अणु
			/* पढ़ो back byte-swapped, so complement swap bits */
			mask = EIP197_MST_CTRL_BYTE_SWAP_BITS;
			priv->hwconfig.hiaver = EIP197_VERSION_SWAP(version);
			priv->flags |= SAFEXCEL_HW_EIP197;
		पूर्ण अन्यथा अणु
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	/* Now initialize the reg offsets based on the probing info so far */
	safexcel_init_रेजिस्टर_offsets(priv);

	/*
	 * If the version was पढ़ो byte-swapped, we need to flip the device
	 * swapping Keep in mind here, though, that what we ग_लिखो will also be
	 * byte-swapped ...
	 */
	अगर (mask) अणु
		val = पढ़ोl(EIP197_HIA_AIC(priv) + EIP197_HIA_MST_CTRL);
		val = val ^ (mask >> 24); /* toggle byte swap bits */
		ग_लिखोl(val, EIP197_HIA_AIC(priv) + EIP197_HIA_MST_CTRL);
	पूर्ण

	/*
	 * We're not करोne probing yet! We may fall through to here अगर no HIA
	 * was found at all. So, with the endianness presumably correct now and
	 * the offsets setup, *really* probe क्रम the EIP97/EIP197.
	 */
	version = पढ़ोl(EIP197_GLOBAL(priv) + EIP197_VERSION);
	अगर (((priv->flags & SAFEXCEL_HW_EIP197) &&
	     (EIP197_REG_LO16(version) != EIP197_VERSION_LE) &&
	     (EIP197_REG_LO16(version) != EIP196_VERSION_LE)) ||
	    ((!(priv->flags & SAFEXCEL_HW_EIP197) &&
	     (EIP197_REG_LO16(version) != EIP97_VERSION_LE)))) अणु
		/*
		 * We did not find the device that matched our initial probing
		 * (or our initial probing failed) Report appropriate error.
		 */
		dev_err(priv->dev, "Probing for EIP97/EIP19x failed - no such device (read %08x)\n",
			version);
		वापस -ENODEV;
	पूर्ण

	priv->hwconfig.hwver = EIP197_VERSION_MASK(version);
	hwctg = version >> 28;
	peid = version & 255;

	/* Detect EIP206 processing pipe */
	version = पढ़ोl(EIP197_PE(priv) + + EIP197_PE_VERSION(0));
	अगर (EIP197_REG_LO16(version) != EIP206_VERSION_LE) अणु
		dev_err(priv->dev, "EIP%d: EIP206 not detected\n", peid);
		वापस -ENODEV;
	पूर्ण
	priv->hwconfig.ppver = EIP197_VERSION_MASK(version);

	/* Detect EIP96 packet engine and version */
	version = पढ़ोl(EIP197_PE(priv) + EIP197_PE_EIP96_VERSION(0));
	अगर (EIP197_REG_LO16(version) != EIP96_VERSION_LE) अणु
		dev_err(dev, "EIP%d: EIP96 not detected.\n", peid);
		वापस -ENODEV;
	पूर्ण
	priv->hwconfig.pever = EIP197_VERSION_MASK(version);

	hwopt = पढ़ोl(EIP197_GLOBAL(priv) + EIP197_OPTIONS);
	hiaopt = पढ़ोl(EIP197_HIA_AIC(priv) + EIP197_HIA_OPTIONS);

	priv->hwconfig.icever = 0;
	priv->hwconfig.ocever = 0;
	priv->hwconfig.psever = 0;
	अगर (priv->flags & SAFEXCEL_HW_EIP197) अणु
		/* EIP197 */
		peopt = पढ़ोl(EIP197_PE(priv) + EIP197_PE_OPTIONS(0));

		priv->hwconfig.hwdataw  = (hiaopt >> EIP197_HWDATAW_OFFSET) &
					  EIP197_HWDATAW_MASK;
		priv->hwconfig.hwcfsize = ((hiaopt >> EIP197_CFSIZE_OFFSET) &
					   EIP197_CFSIZE_MASK) +
					  EIP197_CFSIZE_ADJUST;
		priv->hwconfig.hwrfsize = ((hiaopt >> EIP197_RFSIZE_OFFSET) &
					   EIP197_RFSIZE_MASK) +
					  EIP197_RFSIZE_ADJUST;
		priv->hwconfig.hwnumpes	= (hiaopt >> EIP197_N_PES_OFFSET) &
					  EIP197_N_PES_MASK;
		priv->hwconfig.hwnumrings = (hiaopt >> EIP197_N_RINGS_OFFSET) &
					    EIP197_N_RINGS_MASK;
		अगर (hiaopt & EIP197_HIA_OPT_HAS_PE_ARB)
			priv->flags |= EIP197_PE_ARB;
		अगर (EIP206_OPT_ICE_TYPE(peopt) == 1) अणु
			priv->flags |= EIP197_ICE;
			/* Detect ICE EIP207 class. engine and version */
			version = पढ़ोl(EIP197_PE(priv) +
				  EIP197_PE_ICE_VERSION(0));
			अगर (EIP197_REG_LO16(version) != EIP207_VERSION_LE) अणु
				dev_err(dev, "EIP%d: ICE EIP207 not detected.\n",
					peid);
				वापस -ENODEV;
			पूर्ण
			priv->hwconfig.icever = EIP197_VERSION_MASK(version);
		पूर्ण
		अगर (EIP206_OPT_OCE_TYPE(peopt) == 1) अणु
			priv->flags |= EIP197_OCE;
			/* Detect EIP96PP packet stream editor and version */
			version = पढ़ोl(EIP197_PE(priv) + EIP197_PE_PSE_VERSION(0));
			अगर (EIP197_REG_LO16(version) != EIP96_VERSION_LE) अणु
				dev_err(dev, "EIP%d: EIP96PP not detected.\n", peid);
				वापस -ENODEV;
			पूर्ण
			priv->hwconfig.psever = EIP197_VERSION_MASK(version);
			/* Detect OCE EIP207 class. engine and version */
			version = पढ़ोl(EIP197_PE(priv) +
				  EIP197_PE_ICE_VERSION(0));
			अगर (EIP197_REG_LO16(version) != EIP207_VERSION_LE) अणु
				dev_err(dev, "EIP%d: OCE EIP207 not detected.\n",
					peid);
				वापस -ENODEV;
			पूर्ण
			priv->hwconfig.ocever = EIP197_VERSION_MASK(version);
		पूर्ण
		/* If not a full TRC, then assume simple TRC */
		अगर (!(hwopt & EIP197_OPT_HAS_TRC))
			priv->flags |= EIP197_SIMPLE_TRC;
		/* EIP197 always has SOME क्रमm of TRC */
		priv->flags |= EIP197_TRC_CACHE;
	पूर्ण अन्यथा अणु
		/* EIP97 */
		priv->hwconfig.hwdataw  = (hiaopt >> EIP197_HWDATAW_OFFSET) &
					  EIP97_HWDATAW_MASK;
		priv->hwconfig.hwcfsize = (hiaopt >> EIP97_CFSIZE_OFFSET) &
					  EIP97_CFSIZE_MASK;
		priv->hwconfig.hwrfsize = (hiaopt >> EIP97_RFSIZE_OFFSET) &
					  EIP97_RFSIZE_MASK;
		priv->hwconfig.hwnumpes	= 1; /* by definition */
		priv->hwconfig.hwnumrings = (hiaopt >> EIP197_N_RINGS_OFFSET) &
					    EIP197_N_RINGS_MASK;
	पूर्ण

	/* Scan क्रम ring AIC's */
	क्रम (i = 0; i < EIP197_MAX_RING_AIC; i++) अणु
		version = पढ़ोl(EIP197_HIA_AIC_R(priv) +
				EIP197_HIA_AIC_R_VERSION(i));
		अगर (EIP197_REG_LO16(version) != EIP201_VERSION_LE)
			अवरोध;
	पूर्ण
	priv->hwconfig.hwnumraic = i;
	/* Low-end EIP196 may not have any ring AIC's ... */
	अगर (!priv->hwconfig.hwnumraic) अणु
		dev_err(priv->dev, "No ring interrupt controller present!\n");
		वापस -ENODEV;
	पूर्ण

	/* Get supported algorithms from EIP96 transक्रमm engine */
	priv->hwconfig.algo_flags = पढ़ोl(EIP197_PE(priv) +
				    EIP197_PE_EIP96_OPTIONS(0));

	/* Prपूर्णांक single info line describing what we just detected */
	dev_info(priv->dev, "EIP%d:%x(%d,%d,%d,%d)-HIA:%x(%d,%d,%d),PE:%x/%x(alg:%08x)/%x/%x/%x\n",
		 peid, priv->hwconfig.hwver, hwctg, priv->hwconfig.hwnumpes,
		 priv->hwconfig.hwnumrings, priv->hwconfig.hwnumraic,
		 priv->hwconfig.hiaver, priv->hwconfig.hwdataw,
		 priv->hwconfig.hwcfsize, priv->hwconfig.hwrfsize,
		 priv->hwconfig.ppver, priv->hwconfig.pever,
		 priv->hwconfig.algo_flags, priv->hwconfig.icever,
		 priv->hwconfig.ocever, priv->hwconfig.psever);

	safexcel_configure(priv);

	अगर (IS_ENABLED(CONFIG_PCI) && priv->version == EIP197_DEVBRD) अणु
		/*
		 * Request MSI vectors क्रम global + 1 per ring -
		 * or just 1 क्रम older dev images
		 */
		काष्ठा pci_dev *pci_pdev = pdev;

		ret = pci_alloc_irq_vectors(pci_pdev,
					    priv->config.rings + 1,
					    priv->config.rings + 1,
					    PCI_IRQ_MSI | PCI_IRQ_MSIX);
		अगर (ret < 0) अणु
			dev_err(dev, "Failed to allocate PCI MSI interrupts\n");
			वापस ret;
		पूर्ण
	पूर्ण

	/* Register the ring IRQ handlers and configure the rings */
	priv->ring = devm_kसुस्मृति(dev, priv->config.rings,
				  माप(*priv->ring),
				  GFP_KERNEL);
	अगर (!priv->ring)
		वापस -ENOMEM;

	क्रम (i = 0; i < priv->config.rings; i++) अणु
		अक्षर wq_name[9] = अणु0पूर्ण;
		पूर्णांक irq;
		काष्ठा safexcel_ring_irq_data *ring_irq;

		ret = safexcel_init_ring_descriptors(priv,
						     &priv->ring[i].cdr,
						     &priv->ring[i].rdr);
		अगर (ret) अणु
			dev_err(dev, "Failed to initialize rings\n");
			वापस ret;
		पूर्ण

		priv->ring[i].rdr_req = devm_kसुस्मृति(dev,
			EIP197_DEFAULT_RING_SIZE,
			माप(*priv->ring[i].rdr_req),
			GFP_KERNEL);
		अगर (!priv->ring[i].rdr_req)
			वापस -ENOMEM;

		ring_irq = devm_kzalloc(dev, माप(*ring_irq), GFP_KERNEL);
		अगर (!ring_irq)
			वापस -ENOMEM;

		ring_irq->priv = priv;
		ring_irq->ring = i;

		irq = safexcel_request_ring_irq(pdev,
						EIP197_IRQ_NUMBER(i, is_pci_dev),
						is_pci_dev,
						i,
						safexcel_irq_ring,
						safexcel_irq_ring_thपढ़ो,
						ring_irq);
		अगर (irq < 0) अणु
			dev_err(dev, "Failed to get IRQ ID for ring %d\n", i);
			वापस irq;
		पूर्ण

		priv->ring[i].irq = irq;
		priv->ring[i].work_data.priv = priv;
		priv->ring[i].work_data.ring = i;
		INIT_WORK(&priv->ring[i].work_data.work,
			  safexcel_dequeue_work);

		snम_लिखो(wq_name, 9, "wq_ring%d", i);
		priv->ring[i].workqueue =
			create_singlethपढ़ो_workqueue(wq_name);
		अगर (!priv->ring[i].workqueue)
			वापस -ENOMEM;

		priv->ring[i].requests = 0;
		priv->ring[i].busy = false;

		crypto_init_queue(&priv->ring[i].queue,
				  EIP197_DEFAULT_RING_SIZE);

		spin_lock_init(&priv->ring[i].lock);
		spin_lock_init(&priv->ring[i].queue_lock);
	पूर्ण

	atomic_set(&priv->ring_used, 0);

	ret = safexcel_hw_init(priv);
	अगर (ret) अणु
		dev_err(dev, "HW init failed (%d)\n", ret);
		वापस ret;
	पूर्ण

	ret = safexcel_रेजिस्टर_algorithms(priv);
	अगर (ret) अणु
		dev_err(dev, "Failed to register algorithms (%d)\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम safexcel_hw_reset_rings(काष्ठा safexcel_crypto_priv *priv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < priv->config.rings; i++) अणु
		/* clear any pending पूर्णांकerrupt */
		ग_लिखोl(GENMASK(5, 0), EIP197_HIA_CDR(priv, i) + EIP197_HIA_xDR_STAT);
		ग_लिखोl(GENMASK(7, 0), EIP197_HIA_RDR(priv, i) + EIP197_HIA_xDR_STAT);

		/* Reset the CDR base address */
		ग_लिखोl(0, EIP197_HIA_CDR(priv, i) + EIP197_HIA_xDR_RING_BASE_ADDR_LO);
		ग_लिखोl(0, EIP197_HIA_CDR(priv, i) + EIP197_HIA_xDR_RING_BASE_ADDR_HI);

		/* Reset the RDR base address */
		ग_लिखोl(0, EIP197_HIA_RDR(priv, i) + EIP197_HIA_xDR_RING_BASE_ADDR_LO);
		ग_लिखोl(0, EIP197_HIA_RDR(priv, i) + EIP197_HIA_xDR_RING_BASE_ADDR_HI);
	पूर्ण
पूर्ण

/* क्रम Device Tree platक्रमm driver */

अटल पूर्णांक safexcel_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा safexcel_crypto_priv *priv;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->dev = dev;
	priv->version = (क्रमागत safexcel_eip_version)of_device_get_match_data(dev);

	platक्रमm_set_drvdata(pdev, priv);

	priv->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->base)) अणु
		dev_err(dev, "failed to get resource\n");
		वापस PTR_ERR(priv->base);
	पूर्ण

	priv->clk = devm_clk_get(&pdev->dev, शून्य);
	ret = PTR_ERR_OR_ZERO(priv->clk);
	/* The घड़ी isn't mandatory */
	अगर  (ret != -ENOENT) अणु
		अगर (ret)
			वापस ret;

		ret = clk_prepare_enable(priv->clk);
		अगर (ret) अणु
			dev_err(dev, "unable to enable clk (%d)\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	priv->reg_clk = devm_clk_get(&pdev->dev, "reg");
	ret = PTR_ERR_OR_ZERO(priv->reg_clk);
	/* The घड़ी isn't mandatory */
	अगर  (ret != -ENOENT) अणु
		अगर (ret)
			जाओ err_core_clk;

		ret = clk_prepare_enable(priv->reg_clk);
		अगर (ret) अणु
			dev_err(dev, "unable to enable reg clk (%d)\n", ret);
			जाओ err_core_clk;
		पूर्ण
	पूर्ण

	ret = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(64));
	अगर (ret)
		जाओ err_reg_clk;

	/* Generic EIP97/EIP197 device probing */
	ret = safexcel_probe_generic(pdev, priv, 0);
	अगर (ret)
		जाओ err_reg_clk;

	वापस 0;

err_reg_clk:
	clk_disable_unprepare(priv->reg_clk);
err_core_clk:
	clk_disable_unprepare(priv->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक safexcel_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा safexcel_crypto_priv *priv = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	safexcel_unरेजिस्टर_algorithms(priv);
	safexcel_hw_reset_rings(priv);

	clk_disable_unprepare(priv->reg_clk);
	clk_disable_unprepare(priv->clk);

	क्रम (i = 0; i < priv->config.rings; i++) अणु
		irq_set_affinity_hपूर्णांक(priv->ring[i].irq, शून्य);
		destroy_workqueue(priv->ring[i].workqueue);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id safexcel_of_match_table[] = अणु
	अणु
		.compatible = "inside-secure,safexcel-eip97ies",
		.data = (व्योम *)EIP97IES_MRVL,
	पूर्ण,
	अणु
		.compatible = "inside-secure,safexcel-eip197b",
		.data = (व्योम *)EIP197B_MRVL,
	पूर्ण,
	अणु
		.compatible = "inside-secure,safexcel-eip197d",
		.data = (व्योम *)EIP197D_MRVL,
	पूर्ण,
	/* For backward compatibility and पूर्णांकended क्रम generic use */
	अणु
		.compatible = "inside-secure,safexcel-eip97",
		.data = (व्योम *)EIP97IES_MRVL,
	पूर्ण,
	अणु
		.compatible = "inside-secure,safexcel-eip197",
		.data = (व्योम *)EIP197B_MRVL,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver  crypto_safexcel = अणु
	.probe		= safexcel_probe,
	.हटाओ		= safexcel_हटाओ,
	.driver		= अणु
		.name	= "crypto-safexcel",
		.of_match_table = safexcel_of_match_table,
	पूर्ण,
पूर्ण;

/* PCIE devices - i.e. Inside Secure development boards */

अटल पूर्णांक safexcel_pci_probe(काष्ठा pci_dev *pdev,
			       स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा safexcel_crypto_priv *priv;
	व्योम __iomem *pciebase;
	पूर्णांक rc;
	u32 val;

	dev_dbg(dev, "Probing PCIE device: vendor %04x, device %04x, subv %04x, subdev %04x, ctxt %lx\n",
		ent->venकरोr, ent->device, ent->subvenकरोr,
		ent->subdevice, ent->driver_data);

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->dev = dev;
	priv->version = (क्रमागत safexcel_eip_version)ent->driver_data;

	pci_set_drvdata(pdev, priv);

	/* enable the device */
	rc = pcim_enable_device(pdev);
	अगर (rc) अणु
		dev_err(dev, "Failed to enable PCI device\n");
		वापस rc;
	पूर्ण

	/* take ownership of PCI BAR0 */
	rc = pcim_iomap_regions(pdev, 1, "crypto_safexcel");
	अगर (rc) अणु
		dev_err(dev, "Failed to map IO region for BAR0\n");
		वापस rc;
	पूर्ण
	priv->base = pcim_iomap_table(pdev)[0];

	अगर (priv->version == EIP197_DEVBRD) अणु
		dev_dbg(dev, "Device identified as FPGA based development board - applying HW reset\n");

		rc = pcim_iomap_regions(pdev, 4, "crypto_safexcel");
		अगर (rc) अणु
			dev_err(dev, "Failed to map IO region for BAR4\n");
			वापस rc;
		पूर्ण

		pciebase = pcim_iomap_table(pdev)[2];
		val = पढ़ोl(pciebase + EIP197_XLX_IRQ_BLOCK_ID_ADDR);
		अगर ((val >> 16) == EIP197_XLX_IRQ_BLOCK_ID_VALUE) अणु
			dev_dbg(dev, "Detected Xilinx PCIE IRQ block version %d, multiple MSI support enabled\n",
				(val & 0xff));

			/* Setup MSI identity map mapping */
			ग_लिखोl(EIP197_XLX_USER_VECT_LUT0_IDENT,
			       pciebase + EIP197_XLX_USER_VECT_LUT0_ADDR);
			ग_लिखोl(EIP197_XLX_USER_VECT_LUT1_IDENT,
			       pciebase + EIP197_XLX_USER_VECT_LUT1_ADDR);
			ग_लिखोl(EIP197_XLX_USER_VECT_LUT2_IDENT,
			       pciebase + EIP197_XLX_USER_VECT_LUT2_ADDR);
			ग_लिखोl(EIP197_XLX_USER_VECT_LUT3_IDENT,
			       pciebase + EIP197_XLX_USER_VECT_LUT3_ADDR);

			/* Enable all device पूर्णांकerrupts */
			ग_लिखोl(GENMASK(31, 0),
			       pciebase + EIP197_XLX_USER_INT_ENB_MSK);
		पूर्ण अन्यथा अणु
			dev_err(dev, "Unrecognised IRQ block identifier %x\n",
				val);
			वापस -ENODEV;
		पूर्ण

		/* HW reset FPGA dev board */
		/* निश्चित reset */
		ग_लिखोl(1, priv->base + EIP197_XLX_GPIO_BASE);
		wmb(); /* मुख्यtain strict ordering क्रम accesses here */
		/* deनिश्चित reset */
		ग_लिखोl(0, priv->base + EIP197_XLX_GPIO_BASE);
		wmb(); /* मुख्यtain strict ordering क्रम accesses here */
	पूर्ण

	/* enable bus mastering */
	pci_set_master(pdev);

	/* Generic EIP97/EIP197 device probing */
	rc = safexcel_probe_generic(pdev, priv, 1);
	वापस rc;
पूर्ण

अटल व्योम safexcel_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा safexcel_crypto_priv *priv = pci_get_drvdata(pdev);
	पूर्णांक i;

	safexcel_unरेजिस्टर_algorithms(priv);

	क्रम (i = 0; i < priv->config.rings; i++)
		destroy_workqueue(priv->ring[i].workqueue);

	safexcel_hw_reset_rings(priv);
पूर्ण

अटल स्थिर काष्ठा pci_device_id safexcel_pci_ids[] = अणु
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_XILINX, 0x9038,
			       0x16ae, 0xc522),
		.driver_data = EIP197_DEVBRD,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, safexcel_pci_ids);

अटल काष्ठा pci_driver safexcel_pci_driver = अणु
	.name          = "crypto-safexcel",
	.id_table      = safexcel_pci_ids,
	.probe         = safexcel_pci_probe,
	.हटाओ        = safexcel_pci_हटाओ,
पूर्ण;

अटल पूर्णांक __init safexcel_init(व्योम)
अणु
	पूर्णांक ret;

	/* Register PCI driver */
	ret = pci_रेजिस्टर_driver(&safexcel_pci_driver);

	/* Register platक्रमm driver */
	अगर (IS_ENABLED(CONFIG_OF) && !ret) अणु
		ret = platक्रमm_driver_रेजिस्टर(&crypto_safexcel);
		अगर (ret)
			pci_unरेजिस्टर_driver(&safexcel_pci_driver);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम __निकास safexcel_निकास(व्योम)
अणु
	/* Unरेजिस्टर platक्रमm driver */
	अगर (IS_ENABLED(CONFIG_OF))
		platक्रमm_driver_unरेजिस्टर(&crypto_safexcel);

	/* Unरेजिस्टर PCI driver अगर successfully रेजिस्टरed beक्रमe */
	pci_unरेजिस्टर_driver(&safexcel_pci_driver);
पूर्ण

module_init(safexcel_init);
module_निकास(safexcel_निकास);

MODULE_AUTHOR("Antoine Tenart <antoine.tenart@free-electrons.com>");
MODULE_AUTHOR("Ofer Heifetz <oferh@marvell.com>");
MODULE_AUTHOR("Igal Liberman <igall@marvell.com>");
MODULE_DESCRIPTION("Support for SafeXcel cryptographic engines: EIP97 & EIP197");
MODULE_LICENSE("GPL v2");
MODULE_IMPORT_NS(CRYPTO_INTERNAL);
