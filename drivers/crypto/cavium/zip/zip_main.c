<शैली गुरु>
/***********************license start************************************
 * Copyright (c) 2003-2017 Cavium, Inc.
 * All rights reserved.
 *
 * License: one of 'Cavium License' or 'GNU General Public License Version 2'
 *
 * This file is provided under the terms of the Cavium License (see below)
 * or under the terms of GNU General Public License, Version 2, as
 * published by the Free Software Foundation. When using or redistributing
 * this file, you may करो so under either license.
 *
 * Cavium License:  Redistribution and use in source and binary क्रमms, with
 * or without modअगरication, are permitted provided that the following
 * conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *  * Redistributions in binary क्रमm must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the करोcumentation and/or other materials provided
 *    with the distribution.
 *
 *  * Neither the name of Cavium Inc. nor the names of its contributors may be
 *    used to enकरोrse or promote products derived from this software without
 *    specअगरic prior written permission.
 *
 * This Software, including technical data, may be subject to U.S. export
 * control laws, including the U.S. Export Administration Act and its
 * associated regulations, and may be subject to export or import
 * regulations in other countries.
 *
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
 * AND WITH ALL FAULTS AND CAVIUM INC. MAKES NO PROMISES, REPRESENTATIONS
 * OR WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH
 * RESPECT TO THE SOFTWARE, INCLUDING ITS CONDITION, ITS CONFORMITY TO ANY
 * REPRESENTATION OR DESCRIPTION, OR THE EXISTENCE OF ANY LATENT OR PATENT
 * DEFECTS, AND CAVIUM SPECIFICALLY DISCLAIMS ALL IMPLIED (IF ANY)
 * WARRANTIES OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A
 * PARTICULAR PURPOSE, LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET
 * ENJOYMENT, QUIET POSSESSION OR CORRESPONDENCE TO DESCRIPTION. THE
 * ENTIRE  RISK ARISING OUT OF USE OR PERFORMANCE OF THE SOFTWARE LIES
 * WITH YOU.
 ***********************license end**************************************/

#समावेश "common.h"
#समावेश "zip_crypto.h"

#घोषणा DRV_NAME		"ThunderX-ZIP"

अटल काष्ठा zip_device *zip_dev[MAX_ZIP_DEVICES];

अटल स्थिर काष्ठा pci_device_id zip_id_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_CAVIUM, PCI_DEVICE_ID_THUNDERX_ZIP) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

व्योम zip_reg_ग_लिखो(u64 val, u64 __iomem *addr)
अणु
	ग_लिखोq(val, addr);
पूर्ण

u64 zip_reg_पढ़ो(u64 __iomem *addr)
अणु
	वापस पढ़ोq(addr);
पूर्ण

/*
 * Allocates new ZIP device काष्ठाure
 * Returns zip_device poपूर्णांकer or शून्य अगर cannot allocate memory क्रम zip_device
 */
अटल काष्ठा zip_device *zip_alloc_device(काष्ठा pci_dev *pdev)
अणु
	काष्ठा zip_device *zip = शून्य;
	पूर्णांक idx;

	क्रम (idx = 0; idx < MAX_ZIP_DEVICES; idx++) अणु
		अगर (!zip_dev[idx])
			अवरोध;
	पूर्ण

	/* To ensure that the index is within the limit */
	अगर (idx < MAX_ZIP_DEVICES)
		zip = devm_kzalloc(&pdev->dev, माप(*zip), GFP_KERNEL);

	अगर (!zip)
		वापस शून्य;

	zip_dev[idx] = zip;
	zip->index = idx;
	वापस zip;
पूर्ण

/**
 * zip_get_device - Get ZIP device based on node id of cpu
 *
 * @node: Node id of the current cpu
 * Return: Poपूर्णांकer to Zip device काष्ठाure
 */
काष्ठा zip_device *zip_get_device(पूर्णांक node)
अणु
	अगर ((node < MAX_ZIP_DEVICES) && (node >= 0))
		वापस zip_dev[node];

	zip_err("ZIP device not found for node id %d\n", node);
	वापस शून्य;
पूर्ण

/**
 * zip_get_node_id - Get the node id of the current cpu
 *
 * Return: Node id of the current cpu
 */
पूर्णांक zip_get_node_id(व्योम)
अणु
	वापस cpu_to_node(raw_smp_processor_id());
पूर्ण

/* Initializes the ZIP h/w sub-प्रणाली */
अटल पूर्णांक zip_init_hw(काष्ठा zip_device *zip)
अणु
	जोड़ zip_cmd_ctl    cmd_ctl;
	जोड़ zip_स्थिरants  स्थिरants;
	जोड़ zip_que_ena    que_ena;
	जोड़ zip_quex_map   que_map;
	जोड़ zip_que_pri    que_pri;

	जोड़ zip_quex_sbuf_addr que_sbuf_addr;
	जोड़ zip_quex_sbuf_ctl  que_sbuf_ctl;

	पूर्णांक q = 0;

	/* Enable the ZIP Engine(Core) Clock */
	cmd_ctl.u_reg64 = zip_reg_पढ़ो(zip->reg_base + ZIP_CMD_CTL);
	cmd_ctl.s.क्रमceclk = 1;
	zip_reg_ग_लिखो(cmd_ctl.u_reg64 & 0xFF, (zip->reg_base + ZIP_CMD_CTL));

	zip_msg("ZIP_CMD_CTL  : 0x%016llx",
		zip_reg_पढ़ो(zip->reg_base + ZIP_CMD_CTL));

	स्थिरants.u_reg64 = zip_reg_पढ़ो(zip->reg_base + ZIP_CONSTANTS);
	zip->depth    = स्थिरants.s.depth;
	zip->onfsize  = स्थिरants.s.onfsize;
	zip->ctxsize  = स्थिरants.s.ctxsize;

	zip_msg("depth: 0x%016llx , onfsize : 0x%016llx , ctxsize : 0x%016llx",
		zip->depth, zip->onfsize, zip->ctxsize);

	/*
	 * Program ZIP_QUE(0..7)_SBUF_ADDR and ZIP_QUE(0..7)_SBUF_CTL to
	 * have the correct buffer poपूर्णांकer and size configured क्रम each
	 * inकाष्ठाion queue.
	 */
	क्रम (q = 0; q < ZIP_NUM_QUEUES; q++) अणु
		que_sbuf_ctl.u_reg64 = 0ull;
		que_sbuf_ctl.s.size = (ZIP_CMD_QBUF_SIZE / माप(u64));
		que_sbuf_ctl.s.inst_be   = 0;
		que_sbuf_ctl.s.stream_id = 0;
		zip_reg_ग_लिखो(que_sbuf_ctl.u_reg64,
			      (zip->reg_base + ZIP_QUEX_SBUF_CTL(q)));

		zip_msg("QUEX_SBUF_CTL[%d]: 0x%016llx", q,
			zip_reg_पढ़ो(zip->reg_base + ZIP_QUEX_SBUF_CTL(q)));
	पूर्ण

	क्रम (q = 0; q < ZIP_NUM_QUEUES; q++) अणु
		स_रखो(&zip->iq[q], 0x0, माप(काष्ठा zip_iq));

		spin_lock_init(&zip->iq[q].lock);

		अगर (zip_cmd_qbuf_alloc(zip, q)) अणु
			जबतक (q != 0) अणु
				q--;
				zip_cmd_qbuf_मुक्त(zip, q);
			पूर्ण
			वापस -ENOMEM;
		पूर्ण

		/* Initialize tail ptr to head */
		zip->iq[q].sw_tail = zip->iq[q].sw_head;
		zip->iq[q].hw_tail = zip->iq[q].sw_head;

		/* Write the physical addr to रेजिस्टर */
		que_sbuf_addr.u_reg64   = 0ull;
		que_sbuf_addr.s.ptr = (__pa(zip->iq[q].sw_head) >>
				       ZIP_128B_ALIGN);

		zip_msg("QUE[%d]_PTR(PHYS): 0x%016llx", q,
			(u64)que_sbuf_addr.s.ptr);

		zip_reg_ग_लिखो(que_sbuf_addr.u_reg64,
			      (zip->reg_base + ZIP_QUEX_SBUF_ADDR(q)));

		zip_msg("QUEX_SBUF_ADDR[%d]: 0x%016llx", q,
			zip_reg_पढ़ो(zip->reg_base + ZIP_QUEX_SBUF_ADDR(q)));

		zip_dbg("sw_head :0x%lx sw_tail :0x%lx hw_tail :0x%lx",
			zip->iq[q].sw_head, zip->iq[q].sw_tail,
			zip->iq[q].hw_tail);
		zip_dbg("sw_head phy addr : 0x%lx", que_sbuf_addr.s.ptr);
	पूर्ण

	/*
	 * Queue-to-ZIP core mapping
	 * If a queue is not mapped to a particular core, it is equivalent to
	 * the ZIP core being disabled.
	 */
	que_ena.u_reg64 = 0x0ull;
	/* Enabling queues based on ZIP_NUM_QUEUES */
	क्रम (q = 0; q < ZIP_NUM_QUEUES; q++)
		que_ena.s.ena |= (0x1 << q);
	zip_reg_ग_लिखो(que_ena.u_reg64, (zip->reg_base + ZIP_QUE_ENA));

	zip_msg("QUE_ENA      : 0x%016llx",
		zip_reg_पढ़ो(zip->reg_base + ZIP_QUE_ENA));

	क्रम (q = 0; q < ZIP_NUM_QUEUES; q++) अणु
		que_map.u_reg64 = 0ull;
		/* Mapping each queue to two ZIP cores */
		que_map.s.zce = 0x3;
		zip_reg_ग_लिखो(que_map.u_reg64,
			      (zip->reg_base + ZIP_QUEX_MAP(q)));

		zip_msg("QUE_MAP(%d)   : 0x%016llx", q,
			zip_reg_पढ़ो(zip->reg_base + ZIP_QUEX_MAP(q)));
	पूर्ण

	que_pri.u_reg64 = 0ull;
	क्रम (q = 0; q < ZIP_NUM_QUEUES; q++)
		que_pri.s.pri |= (0x1 << q); /* Higher Priority RR */
	zip_reg_ग_लिखो(que_pri.u_reg64, (zip->reg_base + ZIP_QUE_PRI));

	zip_msg("QUE_PRI %016llx", zip_reg_पढ़ो(zip->reg_base + ZIP_QUE_PRI));

	वापस 0;
पूर्ण

अटल पूर्णांक zip_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा zip_device *zip = शून्य;
	पूर्णांक    err;

	zip = zip_alloc_device(pdev);
	अगर (!zip)
		वापस -ENOMEM;

	dev_info(dev, "Found ZIP device %d %x:%x on Node %d\n", zip->index,
		 pdev->venकरोr, pdev->device, dev_to_node(dev));

	pci_set_drvdata(pdev, zip);
	zip->pdev = pdev;

	err = pci_enable_device(pdev);
	अगर (err) अणु
		dev_err(dev, "Failed to enable PCI device");
		जाओ err_मुक्त_device;
	पूर्ण

	err = pci_request_regions(pdev, DRV_NAME);
	अगर (err) अणु
		dev_err(dev, "PCI request regions failed 0x%x", err);
		जाओ err_disable_device;
	पूर्ण

	err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(48));
	अगर (err) अणु
		dev_err(dev, "Unable to get usable 48-bit DMA configuration\n");
		जाओ err_release_regions;
	पूर्ण

	/* MAP configuration रेजिस्टरs */
	zip->reg_base = pci_ioremap_bar(pdev, PCI_CFG_ZIP_PF_BAR0);
	अगर (!zip->reg_base) अणु
		dev_err(dev, "ZIP: Cannot map BAR0 CSR memory space, aborting");
		err = -ENOMEM;
		जाओ err_release_regions;
	पूर्ण

	/* Initialize ZIP Hardware */
	err = zip_init_hw(zip);
	अगर (err)
		जाओ err_release_regions;

	वापस 0;

err_release_regions:
	अगर (zip->reg_base)
		iounmap(zip->reg_base);
	pci_release_regions(pdev);

err_disable_device:
	pci_disable_device(pdev);

err_मुक्त_device:
	pci_set_drvdata(pdev, शून्य);

	/* Remove zip_dev from zip_device list, मुक्त the zip_device memory */
	zip_dev[zip->index] = शून्य;
	devm_kमुक्त(dev, zip);

	वापस err;
पूर्ण

अटल व्योम zip_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा zip_device *zip = pci_get_drvdata(pdev);
	जोड़ zip_cmd_ctl cmd_ctl;
	पूर्णांक q = 0;

	अगर (!zip)
		वापस;

	अगर (zip->reg_base) अणु
		cmd_ctl.u_reg64 = 0x0ull;
		cmd_ctl.s.reset = 1;  /* Forces ZIP cores to करो reset */
		zip_reg_ग_लिखो(cmd_ctl.u_reg64, (zip->reg_base + ZIP_CMD_CTL));
		iounmap(zip->reg_base);
	पूर्ण

	pci_release_regions(pdev);
	pci_disable_device(pdev);

	/*
	 * Free Command Queue buffers. This मुक्त should be called क्रम all
	 * the enabled Queues.
	 */
	क्रम (q = 0; q < ZIP_NUM_QUEUES; q++)
		zip_cmd_qbuf_मुक्त(zip, q);

	pci_set_drvdata(pdev, शून्य);
	/* हटाओ zip device from zip device list */
	zip_dev[zip->index] = शून्य;
पूर्ण

/* PCI Sub-System Interface */
अटल काष्ठा pci_driver zip_driver = अणु
	.name	    =  DRV_NAME,
	.id_table   =  zip_id_table,
	.probe	    =  zip_probe,
	.हटाओ     =  zip_हटाओ,
पूर्ण;

/* Kernel Crypto Subप्रणाली Interface */

अटल काष्ठा crypto_alg zip_comp_deflate = अणु
	.cra_name		= "deflate",
	.cra_driver_name	= "deflate-cavium",
	.cra_flags		= CRYPTO_ALG_TYPE_COMPRESS,
	.cra_ctxsize		= माप(काष्ठा zip_kernel_ctx),
	.cra_priority           = 300,
	.cra_module		= THIS_MODULE,
	.cra_init		= zip_alloc_comp_ctx_deflate,
	.cra_निकास		= zip_मुक्त_comp_ctx,
	.cra_u			= अणु .compress = अणु
		.coa_compress	= zip_comp_compress,
		.coa_decompress	= zip_comp_decompress
		 पूर्ण पूर्ण
पूर्ण;

अटल काष्ठा crypto_alg zip_comp_lzs = अणु
	.cra_name		= "lzs",
	.cra_driver_name	= "lzs-cavium",
	.cra_flags		= CRYPTO_ALG_TYPE_COMPRESS,
	.cra_ctxsize		= माप(काष्ठा zip_kernel_ctx),
	.cra_priority           = 300,
	.cra_module		= THIS_MODULE,
	.cra_init		= zip_alloc_comp_ctx_lzs,
	.cra_निकास		= zip_मुक्त_comp_ctx,
	.cra_u			= अणु .compress = अणु
		.coa_compress	= zip_comp_compress,
		.coa_decompress	= zip_comp_decompress
		 पूर्ण पूर्ण
पूर्ण;

अटल काष्ठा scomp_alg zip_scomp_deflate = अणु
	.alloc_ctx		= zip_alloc_scomp_ctx_deflate,
	.मुक्त_ctx		= zip_मुक्त_scomp_ctx,
	.compress		= zip_scomp_compress,
	.decompress		= zip_scomp_decompress,
	.base			= अणु
		.cra_name		= "deflate",
		.cra_driver_name	= "deflate-scomp-cavium",
		.cra_module		= THIS_MODULE,
		.cra_priority           = 300,
	पूर्ण
पूर्ण;

अटल काष्ठा scomp_alg zip_scomp_lzs = अणु
	.alloc_ctx		= zip_alloc_scomp_ctx_lzs,
	.मुक्त_ctx		= zip_मुक्त_scomp_ctx,
	.compress		= zip_scomp_compress,
	.decompress		= zip_scomp_decompress,
	.base			= अणु
		.cra_name		= "lzs",
		.cra_driver_name	= "lzs-scomp-cavium",
		.cra_module		= THIS_MODULE,
		.cra_priority           = 300,
	पूर्ण
पूर्ण;

अटल पूर्णांक zip_रेजिस्टर_compression_device(व्योम)
अणु
	पूर्णांक ret;

	ret = crypto_रेजिस्टर_alg(&zip_comp_deflate);
	अगर (ret < 0) अणु
		zip_err("Deflate algorithm registration failed\n");
		वापस ret;
	पूर्ण

	ret = crypto_रेजिस्टर_alg(&zip_comp_lzs);
	अगर (ret < 0) अणु
		zip_err("LZS algorithm registration failed\n");
		जाओ err_unरेजिस्टर_alg_deflate;
	पूर्ण

	ret = crypto_रेजिस्टर_scomp(&zip_scomp_deflate);
	अगर (ret < 0) अणु
		zip_err("Deflate scomp algorithm registration failed\n");
		जाओ err_unरेजिस्टर_alg_lzs;
	पूर्ण

	ret = crypto_रेजिस्टर_scomp(&zip_scomp_lzs);
	अगर (ret < 0) अणु
		zip_err("LZS scomp algorithm registration failed\n");
		जाओ err_unरेजिस्टर_scomp_deflate;
	पूर्ण

	वापस ret;

err_unरेजिस्टर_scomp_deflate:
	crypto_unरेजिस्टर_scomp(&zip_scomp_deflate);
err_unरेजिस्टर_alg_lzs:
	crypto_unरेजिस्टर_alg(&zip_comp_lzs);
err_unरेजिस्टर_alg_deflate:
	crypto_unरेजिस्टर_alg(&zip_comp_deflate);

	वापस ret;
पूर्ण

अटल व्योम zip_unरेजिस्टर_compression_device(व्योम)
अणु
	crypto_unरेजिस्टर_alg(&zip_comp_deflate);
	crypto_unरेजिस्टर_alg(&zip_comp_lzs);
	crypto_unरेजिस्टर_scomp(&zip_scomp_deflate);
	crypto_unरेजिस्टर_scomp(&zip_scomp_lzs);
पूर्ण

/*
 * debugfs functions
 */
#अगर_घोषित CONFIG_DEBUG_FS
#समावेश <linux/debugfs.h>

/* Displays ZIP device statistics */
अटल पूर्णांक zip_stats_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	u64 val = 0ull;
	u64 avg_chunk = 0ull, avg_cr = 0ull;
	u32 q = 0;

	पूर्णांक index  = 0;
	काष्ठा zip_device *zip;
	काष्ठा zip_stats  *st;

	क्रम (index = 0; index < MAX_ZIP_DEVICES; index++) अणु
		u64 pending = 0;

		अगर (zip_dev[index]) अणु
			zip = zip_dev[index];
			st  = &zip->stats;

			/* Get all the pending requests */
			क्रम (q = 0; q < ZIP_NUM_QUEUES; q++) अणु
				val = zip_reg_पढ़ो((zip->reg_base +
						    ZIP_DBG_QUEX_STA(q)));
				pending += val >> 32 & 0xffffff;
			पूर्ण

			val = atomic64_पढ़ो(&st->comp_req_complete);
			avg_chunk = (val) ? atomic64_पढ़ो(&st->comp_in_bytes) / val : 0;

			val = atomic64_पढ़ो(&st->comp_out_bytes);
			avg_cr = (val) ? atomic64_पढ़ो(&st->comp_in_bytes) / val : 0;
			seq_म_लिखो(s, "        ZIP Device %d Stats\n"
				      "-----------------------------------\n"
				      "Comp Req Submitted        : \t%lld\n"
				      "Comp Req Completed        : \t%lld\n"
				      "Compress In Bytes         : \t%lld\n"
				      "Compressed Out Bytes      : \t%lld\n"
				      "Average Chunk size        : \t%llu\n"
				      "Average Compression ratio : \t%llu\n"
				      "Decomp Req Submitted      : \t%lld\n"
				      "Decomp Req Completed      : \t%lld\n"
				      "Decompress In Bytes       : \t%lld\n"
				      "Decompressed Out Bytes    : \t%lld\n"
				      "Decompress Bad requests   : \t%lld\n"
				      "Pending Req               : \t%lld\n"
					"---------------------------------\n",
				       index,
				       (u64)atomic64_पढ़ो(&st->comp_req_submit),
				       (u64)atomic64_पढ़ो(&st->comp_req_complete),
				       (u64)atomic64_पढ़ो(&st->comp_in_bytes),
				       (u64)atomic64_पढ़ो(&st->comp_out_bytes),
				       avg_chunk,
				       avg_cr,
				       (u64)atomic64_पढ़ो(&st->decomp_req_submit),
				       (u64)atomic64_पढ़ो(&st->decomp_req_complete),
				       (u64)atomic64_पढ़ो(&st->decomp_in_bytes),
				       (u64)atomic64_पढ़ो(&st->decomp_out_bytes),
				       (u64)atomic64_पढ़ो(&st->decomp_bad_reqs),
				       pending);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* Clears stats data */
अटल पूर्णांक zip_clear_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	पूर्णांक index = 0;

	क्रम (index = 0; index < MAX_ZIP_DEVICES; index++) अणु
		अगर (zip_dev[index]) अणु
			स_रखो(&zip_dev[index]->stats, 0,
			       माप(काष्ठा zip_stats));
			seq_म_लिखो(s, "Cleared stats for zip %d\n", index);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा zip_रेजिस्टरs zipregs[64] = अणु
	अणु"ZIP_CMD_CTL        ",  0x0000ullपूर्ण,
	अणु"ZIP_THROTTLE       ",  0x0010ullपूर्ण,
	अणु"ZIP_CONSTANTS      ",  0x00A0ullपूर्ण,
	अणु"ZIP_QUE0_MAP       ",  0x1400ullपूर्ण,
	अणु"ZIP_QUE1_MAP       ",  0x1408ullपूर्ण,
	अणु"ZIP_QUE_ENA        ",  0x0500ullपूर्ण,
	अणु"ZIP_QUE_PRI        ",  0x0508ullपूर्ण,
	अणु"ZIP_QUE0_DONE      ",  0x2000ullपूर्ण,
	अणु"ZIP_QUE1_DONE      ",  0x2008ullपूर्ण,
	अणु"ZIP_QUE0_DOORBELL  ",  0x4000ullपूर्ण,
	अणु"ZIP_QUE1_DOORBELL  ",  0x4008ullपूर्ण,
	अणु"ZIP_QUE0_SBUF_ADDR ",  0x1000ullपूर्ण,
	अणु"ZIP_QUE1_SBUF_ADDR ",  0x1008ullपूर्ण,
	अणु"ZIP_QUE0_SBUF_CTL  ",  0x1200ullपूर्ण,
	अणु"ZIP_QUE1_SBUF_CTL  ",  0x1208ullपूर्ण,
	अणु शून्य, 0पूर्ण
पूर्ण;

/* Prपूर्णांकs रेजिस्टरs' contents */
अटल पूर्णांक zip_regs_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	u64 val = 0;
	पूर्णांक i = 0, index = 0;

	क्रम (index = 0; index < MAX_ZIP_DEVICES; index++) अणु
		अगर (zip_dev[index]) अणु
			seq_म_लिखो(s, "--------------------------------\n"
				      "     ZIP Device %d Registers\n"
				      "--------------------------------\n",
				      index);

			i = 0;

			जबतक (zipregs[i].reg_name) अणु
				val = zip_reg_पढ़ो((zip_dev[index]->reg_base +
						    zipregs[i].reg_offset));
				seq_म_लिखो(s, "%s: 0x%016llx\n",
					   zipregs[i].reg_name, val);
				i++;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(zip_stats);
DEFINE_SHOW_ATTRIBUTE(zip_clear);
DEFINE_SHOW_ATTRIBUTE(zip_regs);

/* Root directory क्रम thunderx_zip debugfs entry */
अटल काष्ठा dentry *zip_debugfs_root;

अटल व्योम __init zip_debugfs_init(व्योम)
अणु
	अगर (!debugfs_initialized())
		वापस;

	zip_debugfs_root = debugfs_create_dir("thunderx_zip", शून्य);

	/* Creating files क्रम entries inside thunderx_zip directory */
	debugfs_create_file("zip_stats", 0444, zip_debugfs_root, शून्य,
			    &zip_stats_fops);

	debugfs_create_file("zip_clear", 0444, zip_debugfs_root, शून्य,
			    &zip_clear_fops);

	debugfs_create_file("zip_regs", 0444, zip_debugfs_root, शून्य,
			    &zip_regs_fops);

पूर्ण

अटल व्योम __निकास zip_debugfs_निकास(व्योम)
अणु
	debugfs_हटाओ_recursive(zip_debugfs_root);
पूर्ण

#अन्यथा
अटल व्योम __init zip_debugfs_init(व्योम) अणु पूर्ण
अटल व्योम __निकास zip_debugfs_निकास(व्योम) अणु पूर्ण
#पूर्ण_अगर
/* debugfs - end */

अटल पूर्णांक __init zip_init_module(व्योम)
अणु
	पूर्णांक ret;

	zip_msg("%s\n", DRV_NAME);

	ret = pci_रेजिस्टर_driver(&zip_driver);
	अगर (ret < 0) अणु
		zip_err("ZIP: pci_register_driver() failed\n");
		वापस ret;
	पूर्ण

	/* Register with the Kernel Crypto Interface */
	ret = zip_रेजिस्टर_compression_device();
	अगर (ret < 0) अणु
		zip_err("ZIP: Kernel Crypto Registration failed\n");
		जाओ err_pci_unरेजिस्टर;
	पूर्ण

	/* comp-decomp statistics are handled with debugfs पूर्णांकerface */
	zip_debugfs_init();

	वापस ret;

err_pci_unरेजिस्टर:
	pci_unरेजिस्टर_driver(&zip_driver);
	वापस ret;
पूर्ण

अटल व्योम __निकास zip_cleanup_module(व्योम)
अणु
	zip_debugfs_निकास();

	/* Unरेजिस्टर from the kernel crypto पूर्णांकerface */
	zip_unरेजिस्टर_compression_device();

	/* Unरेजिस्टर this driver क्रम pci zip devices */
	pci_unरेजिस्टर_driver(&zip_driver);
पूर्ण

module_init(zip_init_module);
module_निकास(zip_cleanup_module);

MODULE_AUTHOR("Cavium Inc");
MODULE_DESCRIPTION("Cavium Inc ThunderX ZIP Driver");
MODULE_LICENSE("GPL v2");
MODULE_DEVICE_TABLE(pci, zip_id_table);
