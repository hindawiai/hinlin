<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Generic Error-Correcting Code (ECC) engine
 *
 * Copyright (C) 2019 Macronix
 * Author:
 *     Miquथउl RAYNAL <miquel.raynal@bootlin.com>
 *
 *
 * This file describes the असलtraction of any न_अंकD ECC engine. It has been
 * deचिन्हित to fit most हालs, including parallel न_अंकDs and SPI-न_अंकDs.
 *
 * There are three मुख्य situations where instantiating this ECC engine makes
 * sense:
 *   - बाह्यal: The ECC engine is outside the न_अंकD pipeline, typically this
 *               is a software ECC engine, or an hardware engine that is
 *               outside the न_अंकD controller pipeline.
 *   - pipelined: The ECC engine is inside the न_अंकD pipeline, ie. on the
 *                controller's side. This is the हाल of most of the raw न_अंकD
 *                controllers. In the pipeline हाल, the ECC bytes are
 *                generated/data corrected on the fly when a page is
 *                written/पढ़ो.
 *   - ondie: The ECC engine is inside the न_अंकD pipeline, on the chip's side.
 *            Some न_अंकD chips can correct themselves the data.
 *
 * Besides the initial setup and final cleanups, the पूर्णांकerfaces are rather
 * simple:
 *   - prepare: Prepare an I/O request. Enable/disable the ECC engine based on
 *              the I/O request type. In हाल of software correction or बाह्यal
 *              engine, this step may involve to derive the ECC bytes and place
 *              them in the OOB area beक्रमe a ग_लिखो.
 *   - finish: Finish an I/O request. Correct the data in हाल of a पढ़ो
 *             request and report the number of corrected bits/uncorrectable
 *             errors. Most likely empty क्रम ग_लिखो operations, unless you have
 *             hardware specअगरic stuff to करो, like shutting करोwn the engine to
 *             save घातer.
 *
 * The I/O request should be enबंदd in a prepare()/finish() pair of calls
 * and will behave dअगरferently depending on the requested I/O type:
 *   - raw: Correction disabled
 *   - ecc: Correction enabled
 *
 * The request direction is impacting the logic as well:
 *   - पढ़ो: Load data from the न_अंकD chip
 *   - ग_लिखो: Store data in the न_अंकD chip
 *
 * Mixing all this combinations together gives the following behavior.
 * Those are just examples, drivers are मुक्त to add custom steps in their
 * prepare/finish hook.
 *
 * [बाह्यal ECC engine]
 *   - बाह्यal + prepare + raw + पढ़ो: करो nothing
 *   - बाह्यal + finish  + raw + पढ़ो: करो nothing
 *   - बाह्यal + prepare + raw + ग_लिखो: करो nothing
 *   - बाह्यal + finish  + raw + ग_लिखो: करो nothing
 *   - बाह्यal + prepare + ecc + पढ़ो: करो nothing
 *   - बाह्यal + finish  + ecc + पढ़ो: calculate expected ECC bytes, extract
 *                                      ECC bytes from OOB buffer, correct
 *                                      and report any bitflip/error
 *   - बाह्यal + prepare + ecc + ग_लिखो: calculate ECC bytes and store them at
 *                                       the right place in the OOB buffer based
 *                                       on the OOB layout
 *   - बाह्यal + finish  + ecc + ग_लिखो: करो nothing
 *
 * [pipelined ECC engine]
 *   - pipelined + prepare + raw + पढ़ो: disable the controller's ECC engine अगर
 *                                       activated
 *   - pipelined + finish  + raw + पढ़ो: करो nothing
 *   - pipelined + prepare + raw + ग_लिखो: disable the controller's ECC engine अगर
 *                                        activated
 *   - pipelined + finish  + raw + ग_लिखो: करो nothing
 *   - pipelined + prepare + ecc + पढ़ो: enable the controller's ECC engine अगर
 *                                       deactivated
 *   - pipelined + finish  + ecc + पढ़ो: check the status, report any
 *                                       error/bitflip
 *   - pipelined + prepare + ecc + ग_लिखो: enable the controller's ECC engine अगर
 *                                        deactivated
 *   - pipelined + finish  + ecc + ग_लिखो: करो nothing
 *
 * [ondie ECC engine]
 *   - ondie + prepare + raw + पढ़ो: send commands to disable the on-chip ECC
 *                                   engine अगर activated
 *   - ondie + finish  + raw + पढ़ो: करो nothing
 *   - ondie + prepare + raw + ग_लिखो: send commands to disable the on-chip ECC
 *                                    engine अगर activated
 *   - ondie + finish  + raw + ग_लिखो: करो nothing
 *   - ondie + prepare + ecc + पढ़ो: send commands to enable the on-chip ECC
 *                                   engine अगर deactivated
 *   - ondie + finish  + ecc + पढ़ो: send commands to check the status, report
 *                                   any error/bitflip
 *   - ondie + prepare + ecc + ग_लिखो: send commands to enable the on-chip ECC
 *                                    engine अगर deactivated
 *   - ondie + finish  + ecc + ग_लिखो: करो nothing
 */

#समावेश <linux/module.h>
#समावेश <linux/mtd/nand.h>
#समावेश <linux/slab.h>

/**
 * nand_ecc_init_ctx - Init the ECC engine context
 * @nand: the न_अंकD device
 *
 * On success, the caller is responsible of calling @nand_ecc_cleanup_ctx().
 */
पूर्णांक nand_ecc_init_ctx(काष्ठा nand_device *nand)
अणु
	अगर (!nand->ecc.engine || !nand->ecc.engine->ops->init_ctx)
		वापस 0;

	वापस nand->ecc.engine->ops->init_ctx(nand);
पूर्ण
EXPORT_SYMBOL(nand_ecc_init_ctx);

/**
 * nand_ecc_cleanup_ctx - Cleanup the ECC engine context
 * @nand: the न_अंकD device
 */
व्योम nand_ecc_cleanup_ctx(काष्ठा nand_device *nand)
अणु
	अगर (nand->ecc.engine && nand->ecc.engine->ops->cleanup_ctx)
		nand->ecc.engine->ops->cleanup_ctx(nand);
पूर्ण
EXPORT_SYMBOL(nand_ecc_cleanup_ctx);

/**
 * nand_ecc_prepare_io_req - Prepare an I/O request
 * @nand: the न_अंकD device
 * @req: the I/O request
 */
पूर्णांक nand_ecc_prepare_io_req(काष्ठा nand_device *nand,
			    काष्ठा nand_page_io_req *req)
अणु
	अगर (!nand->ecc.engine || !nand->ecc.engine->ops->prepare_io_req)
		वापस 0;

	वापस nand->ecc.engine->ops->prepare_io_req(nand, req);
पूर्ण
EXPORT_SYMBOL(nand_ecc_prepare_io_req);

/**
 * nand_ecc_finish_io_req - Finish an I/O request
 * @nand: the न_अंकD device
 * @req: the I/O request
 */
पूर्णांक nand_ecc_finish_io_req(काष्ठा nand_device *nand,
			   काष्ठा nand_page_io_req *req)
अणु
	अगर (!nand->ecc.engine || !nand->ecc.engine->ops->finish_io_req)
		वापस 0;

	वापस nand->ecc.engine->ops->finish_io_req(nand, req);
पूर्ण
EXPORT_SYMBOL(nand_ecc_finish_io_req);

/* Define शेष OOB placement schemes क्रम large and small page devices */
अटल पूर्णांक nand_ooblayout_ecc_sp(काष्ठा mtd_info *mtd, पूर्णांक section,
				 काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_device *nand = mtd_to_nanddev(mtd);
	अचिन्हित पूर्णांक total_ecc_bytes = nand->ecc.ctx.total;

	अगर (section > 1)
		वापस -दुस्फल;

	अगर (!section) अणु
		oobregion->offset = 0;
		अगर (mtd->oobsize == 16)
			oobregion->length = 4;
		अन्यथा
			oobregion->length = 3;
	पूर्ण अन्यथा अणु
		अगर (mtd->oobsize == 8)
			वापस -दुस्फल;

		oobregion->offset = 6;
		oobregion->length = total_ecc_bytes - 4;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nand_ooblayout_मुक्त_sp(काष्ठा mtd_info *mtd, पूर्णांक section,
				  काष्ठा mtd_oob_region *oobregion)
अणु
	अगर (section > 1)
		वापस -दुस्फल;

	अगर (mtd->oobsize == 16) अणु
		अगर (section)
			वापस -दुस्फल;

		oobregion->length = 8;
		oobregion->offset = 8;
	पूर्ण अन्यथा अणु
		oobregion->length = 2;
		अगर (!section)
			oobregion->offset = 3;
		अन्यथा
			oobregion->offset = 6;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops nand_ooblayout_sp_ops = अणु
	.ecc = nand_ooblayout_ecc_sp,
	.मुक्त = nand_ooblayout_मुक्त_sp,
पूर्ण;

स्थिर काष्ठा mtd_ooblayout_ops *nand_get_small_page_ooblayout(व्योम)
अणु
	वापस &nand_ooblayout_sp_ops;
पूर्ण
EXPORT_SYMBOL_GPL(nand_get_small_page_ooblayout);

अटल पूर्णांक nand_ooblayout_ecc_lp(काष्ठा mtd_info *mtd, पूर्णांक section,
				 काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_device *nand = mtd_to_nanddev(mtd);
	अचिन्हित पूर्णांक total_ecc_bytes = nand->ecc.ctx.total;

	अगर (section || !total_ecc_bytes)
		वापस -दुस्फल;

	oobregion->length = total_ecc_bytes;
	oobregion->offset = mtd->oobsize - oobregion->length;

	वापस 0;
पूर्ण

अटल पूर्णांक nand_ooblayout_मुक्त_lp(काष्ठा mtd_info *mtd, पूर्णांक section,
				  काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_device *nand = mtd_to_nanddev(mtd);
	अचिन्हित पूर्णांक total_ecc_bytes = nand->ecc.ctx.total;

	अगर (section)
		वापस -दुस्फल;

	oobregion->length = mtd->oobsize - total_ecc_bytes - 2;
	oobregion->offset = 2;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops nand_ooblayout_lp_ops = अणु
	.ecc = nand_ooblayout_ecc_lp,
	.मुक्त = nand_ooblayout_मुक्त_lp,
पूर्ण;

स्थिर काष्ठा mtd_ooblayout_ops *nand_get_large_page_ooblayout(व्योम)
अणु
	वापस &nand_ooblayout_lp_ops;
पूर्ण
EXPORT_SYMBOL_GPL(nand_get_large_page_ooblayout);

/*
 * Support the old "large page" layout used क्रम 1-bit Hamming ECC where ECC
 * are placed at a fixed offset.
 */
अटल पूर्णांक nand_ooblayout_ecc_lp_hamming(काष्ठा mtd_info *mtd, पूर्णांक section,
					 काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_device *nand = mtd_to_nanddev(mtd);
	अचिन्हित पूर्णांक total_ecc_bytes = nand->ecc.ctx.total;

	अगर (section)
		वापस -दुस्फल;

	चयन (mtd->oobsize) अणु
	हाल 64:
		oobregion->offset = 40;
		अवरोध;
	हाल 128:
		oobregion->offset = 80;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	oobregion->length = total_ecc_bytes;
	अगर (oobregion->offset + oobregion->length > mtd->oobsize)
		वापस -दुस्फल;

	वापस 0;
पूर्ण

अटल पूर्णांक nand_ooblayout_मुक्त_lp_hamming(काष्ठा mtd_info *mtd, पूर्णांक section,
					  काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_device *nand = mtd_to_nanddev(mtd);
	अचिन्हित पूर्णांक total_ecc_bytes = nand->ecc.ctx.total;
	पूर्णांक ecc_offset = 0;

	अगर (section < 0 || section > 1)
		वापस -दुस्फल;

	चयन (mtd->oobsize) अणु
	हाल 64:
		ecc_offset = 40;
		अवरोध;
	हाल 128:
		ecc_offset = 80;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (section == 0) अणु
		oobregion->offset = 2;
		oobregion->length = ecc_offset - 2;
	पूर्ण अन्यथा अणु
		oobregion->offset = ecc_offset + total_ecc_bytes;
		oobregion->length = mtd->oobsize - oobregion->offset;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops nand_ooblayout_lp_hamming_ops = अणु
	.ecc = nand_ooblayout_ecc_lp_hamming,
	.मुक्त = nand_ooblayout_मुक्त_lp_hamming,
पूर्ण;

स्थिर काष्ठा mtd_ooblayout_ops *nand_get_large_page_hamming_ooblayout(व्योम)
अणु
	वापस &nand_ooblayout_lp_hamming_ops;
पूर्ण
EXPORT_SYMBOL_GPL(nand_get_large_page_hamming_ooblayout);

अटल क्रमागत nand_ecc_engine_type
of_get_nand_ecc_engine_type(काष्ठा device_node *np)
अणु
	काष्ठा device_node *eng_np;

	अगर (of_property_पढ़ो_bool(np, "nand-no-ecc-engine"))
		वापस न_अंकD_ECC_ENGINE_TYPE_NONE;

	अगर (of_property_पढ़ो_bool(np, "nand-use-soft-ecc-engine"))
		वापस न_अंकD_ECC_ENGINE_TYPE_SOFT;

	eng_np = of_parse_phandle(np, "nand-ecc-engine", 0);
	of_node_put(eng_np);

	अगर (eng_np) अणु
		अगर (eng_np == np)
			वापस न_अंकD_ECC_ENGINE_TYPE_ON_DIE;
		अन्यथा
			वापस न_अंकD_ECC_ENGINE_TYPE_ON_HOST;
	पूर्ण

	वापस न_अंकD_ECC_ENGINE_TYPE_INVALID;
पूर्ण

अटल स्थिर अक्षर * स्थिर nand_ecc_placement[] = अणु
	[न_अंकD_ECC_PLACEMENT_OOB] = "oob",
	[न_अंकD_ECC_PLACEMENT_INTERLEAVED] = "interleaved",
पूर्ण;

अटल क्रमागत nand_ecc_placement of_get_nand_ecc_placement(काष्ठा device_node *np)
अणु
	क्रमागत nand_ecc_placement placement;
	स्थिर अक्षर *pm;
	पूर्णांक err;

	err = of_property_पढ़ो_string(np, "nand-ecc-placement", &pm);
	अगर (!err) अणु
		क्रम (placement = न_अंकD_ECC_PLACEMENT_OOB;
		     placement < ARRAY_SIZE(nand_ecc_placement); placement++) अणु
			अगर (!strहालcmp(pm, nand_ecc_placement[placement]))
				वापस placement;
		पूर्ण
	पूर्ण

	वापस न_अंकD_ECC_PLACEMENT_UNKNOWN;
पूर्ण

अटल स्थिर अक्षर * स्थिर nand_ecc_algos[] = अणु
	[न_अंकD_ECC_ALGO_HAMMING] = "hamming",
	[न_अंकD_ECC_ALGO_BCH] = "bch",
	[न_अंकD_ECC_ALGO_RS] = "rs",
पूर्ण;

अटल क्रमागत nand_ecc_algo of_get_nand_ecc_algo(काष्ठा device_node *np)
अणु
	क्रमागत nand_ecc_algo ecc_algo;
	स्थिर अक्षर *pm;
	पूर्णांक err;

	err = of_property_पढ़ो_string(np, "nand-ecc-algo", &pm);
	अगर (!err) अणु
		क्रम (ecc_algo = न_अंकD_ECC_ALGO_HAMMING;
		     ecc_algo < ARRAY_SIZE(nand_ecc_algos);
		     ecc_algo++) अणु
			अगर (!strहालcmp(pm, nand_ecc_algos[ecc_algo]))
				वापस ecc_algo;
		पूर्ण
	पूर्ण

	वापस न_अंकD_ECC_ALGO_UNKNOWN;
पूर्ण

अटल पूर्णांक of_get_nand_ecc_step_size(काष्ठा device_node *np)
अणु
	पूर्णांक ret;
	u32 val;

	ret = of_property_पढ़ो_u32(np, "nand-ecc-step-size", &val);
	वापस ret ? ret : val;
पूर्ण

अटल पूर्णांक of_get_nand_ecc_strength(काष्ठा device_node *np)
अणु
	पूर्णांक ret;
	u32 val;

	ret = of_property_पढ़ो_u32(np, "nand-ecc-strength", &val);
	वापस ret ? ret : val;
पूर्ण

व्योम of_get_nand_ecc_user_config(काष्ठा nand_device *nand)
अणु
	काष्ठा device_node *dn = nanddev_get_of_node(nand);
	पूर्णांक strength, size;

	nand->ecc.user_conf.engine_type = of_get_nand_ecc_engine_type(dn);
	nand->ecc.user_conf.algo = of_get_nand_ecc_algo(dn);
	nand->ecc.user_conf.placement = of_get_nand_ecc_placement(dn);

	strength = of_get_nand_ecc_strength(dn);
	अगर (strength >= 0)
		nand->ecc.user_conf.strength = strength;

	size = of_get_nand_ecc_step_size(dn);
	अगर (size >= 0)
		nand->ecc.user_conf.step_size = size;

	अगर (of_property_पढ़ो_bool(dn, "nand-ecc-maximize"))
		nand->ecc.user_conf.flags |= न_अंकD_ECC_MAXIMIZE_STRENGTH;
पूर्ण
EXPORT_SYMBOL(of_get_nand_ecc_user_config);

/**
 * nand_ecc_is_strong_enough - Check अगर the chip configuration meets the
 *                             datasheet requirements.
 *
 * @nand: Device to check
 *
 * If our configuration corrects A bits per B bytes and the minimum
 * required correction level is X bits per Y bytes, then we must ensure
 * both of the following are true:
 *
 * (1) A / B >= X / Y
 * (2) A >= X
 *
 * Requirement (1) ensures we can correct क्रम the required bitflip density.
 * Requirement (2) ensures we can correct even when all bitflips are clumped
 * in the same sector.
 */
bool nand_ecc_is_strong_enough(काष्ठा nand_device *nand)
अणु
	स्थिर काष्ठा nand_ecc_props *reqs = nanddev_get_ecc_requirements(nand);
	स्थिर काष्ठा nand_ecc_props *conf = nanddev_get_ecc_conf(nand);
	काष्ठा mtd_info *mtd = nanddev_to_mtd(nand);
	पूर्णांक corr, ds_corr;

	अगर (conf->step_size == 0 || reqs->step_size == 0)
		/* Not enough inक्रमmation */
		वापस true;

	/*
	 * We get the number of corrected bits per page to compare
	 * the correction density.
	 */
	corr = (mtd->ग_लिखोsize * conf->strength) / conf->step_size;
	ds_corr = (mtd->ग_लिखोsize * reqs->strength) / reqs->step_size;

	वापस corr >= ds_corr && conf->strength >= reqs->strength;
पूर्ण
EXPORT_SYMBOL(nand_ecc_is_strong_enough);

/* ECC engine driver पूर्णांकernal helpers */
पूर्णांक nand_ecc_init_req_tweaking(काष्ठा nand_ecc_req_tweak_ctx *ctx,
			       काष्ठा nand_device *nand)
अणु
	अचिन्हित पूर्णांक total_buffer_size;

	ctx->nand = nand;

	/* Let the user decide the exact length of each buffer */
	अगर (!ctx->page_buffer_size)
		ctx->page_buffer_size = nanddev_page_size(nand);
	अगर (!ctx->oob_buffer_size)
		ctx->oob_buffer_size = nanddev_per_page_oobsize(nand);

	total_buffer_size = ctx->page_buffer_size + ctx->oob_buffer_size;

	ctx->spare_databuf = kzalloc(total_buffer_size, GFP_KERNEL);
	अगर (!ctx->spare_databuf)
		वापस -ENOMEM;

	ctx->spare_oobbuf = ctx->spare_databuf + ctx->page_buffer_size;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nand_ecc_init_req_tweaking);

व्योम nand_ecc_cleanup_req_tweaking(काष्ठा nand_ecc_req_tweak_ctx *ctx)
अणु
	kमुक्त(ctx->spare_databuf);
पूर्ण
EXPORT_SYMBOL_GPL(nand_ecc_cleanup_req_tweaking);

/*
 * Ensure data and OOB area is fully पढ़ो/written otherwise the correction might
 * not work as expected.
 */
व्योम nand_ecc_tweak_req(काष्ठा nand_ecc_req_tweak_ctx *ctx,
			काष्ठा nand_page_io_req *req)
अणु
	काष्ठा nand_device *nand = ctx->nand;
	काष्ठा nand_page_io_req *orig, *tweak;

	/* Save the original request */
	ctx->orig_req = *req;
	ctx->bounce_data = false;
	ctx->bounce_oob = false;
	orig = &ctx->orig_req;
	tweak = req;

	/* Ensure the request covers the entire page */
	अगर (orig->datalen < nanddev_page_size(nand)) अणु
		ctx->bounce_data = true;
		tweak->dataoffs = 0;
		tweak->datalen = nanddev_page_size(nand);
		tweak->databuf.in = ctx->spare_databuf;
		स_रखो(tweak->databuf.in, 0xFF, ctx->page_buffer_size);
	पूर्ण

	अगर (orig->ooblen < nanddev_per_page_oobsize(nand)) अणु
		ctx->bounce_oob = true;
		tweak->ooboffs = 0;
		tweak->ooblen = nanddev_per_page_oobsize(nand);
		tweak->oobbuf.in = ctx->spare_oobbuf;
		स_रखो(tweak->oobbuf.in, 0xFF, ctx->oob_buffer_size);
	पूर्ण

	/* Copy the data that must be ग_लिखोn in the bounce buffers, अगर needed */
	अगर (orig->type == न_अंकD_PAGE_WRITE) अणु
		अगर (ctx->bounce_data)
			स_नकल((व्योम *)tweak->databuf.out + orig->dataoffs,
			       orig->databuf.out, orig->datalen);

		अगर (ctx->bounce_oob)
			स_नकल((व्योम *)tweak->oobbuf.out + orig->ooboffs,
			       orig->oobbuf.out, orig->ooblen);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(nand_ecc_tweak_req);

व्योम nand_ecc_restore_req(काष्ठा nand_ecc_req_tweak_ctx *ctx,
			  काष्ठा nand_page_io_req *req)
अणु
	काष्ठा nand_page_io_req *orig, *tweak;

	orig = &ctx->orig_req;
	tweak = req;

	/* Restore the data पढ़ो from the bounce buffers, अगर needed */
	अगर (orig->type == न_अंकD_PAGE_READ) अणु
		अगर (ctx->bounce_data)
			स_नकल(orig->databuf.in,
			       tweak->databuf.in + orig->dataoffs,
			       orig->datalen);

		अगर (ctx->bounce_oob)
			स_नकल(orig->oobbuf.in,
			       tweak->oobbuf.in + orig->ooboffs,
			       orig->ooblen);
	पूर्ण

	/* Ensure the original request is restored */
	*req = *orig;
पूर्ण
EXPORT_SYMBOL_GPL(nand_ecc_restore_req);

काष्ठा nand_ecc_engine *nand_ecc_get_sw_engine(काष्ठा nand_device *nand)
अणु
	अचिन्हित पूर्णांक algo = nand->ecc.user_conf.algo;

	अगर (algo == न_अंकD_ECC_ALGO_UNKNOWN)
		algo = nand->ecc.शेषs.algo;

	चयन (algo) अणु
	हाल न_अंकD_ECC_ALGO_HAMMING:
		वापस nand_ecc_sw_hamming_get_engine();
	हाल न_अंकD_ECC_ALGO_BCH:
		वापस nand_ecc_sw_bch_get_engine();
	शेष:
		अवरोध;
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(nand_ecc_get_sw_engine);

काष्ठा nand_ecc_engine *nand_ecc_get_on_die_hw_engine(काष्ठा nand_device *nand)
अणु
	वापस nand->ecc.ondie_engine;
पूर्ण
EXPORT_SYMBOL(nand_ecc_get_on_die_hw_engine);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Miquel Raynal <miquel.raynal@bootlin.com>");
MODULE_DESCRIPTION("Generic ECC engine");
