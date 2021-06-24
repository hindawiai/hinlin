<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * This file provides ECC correction क्रम more than 1 bit per block of data,
 * using binary BCH codes. It relies on the generic BCH library lib/bch.c.
 *
 * Copyright तऊ 2011 Ivan Djelic <ivan.djelic@parrot.com>
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/bitops.h>
#समावेश <linux/mtd/nand.h>
#समावेश <linux/mtd/nand-ecc-sw-bch.h>

/**
 * nand_ecc_sw_bch_calculate - Calculate the ECC corresponding to a data block
 * @nand: न_अंकD device
 * @buf: Input buffer with raw data
 * @code: Output buffer with ECC
 */
पूर्णांक nand_ecc_sw_bch_calculate(काष्ठा nand_device *nand,
			      स्थिर अचिन्हित अक्षर *buf, अचिन्हित अक्षर *code)
अणु
	काष्ठा nand_ecc_sw_bch_conf *engine_conf = nand->ecc.ctx.priv;
	अचिन्हित पूर्णांक i;

	स_रखो(code, 0, engine_conf->code_size);
	bch_encode(engine_conf->bch, buf, nand->ecc.ctx.conf.step_size, code);

	/* apply mask so that an erased page is a valid codeword */
	क्रम (i = 0; i < engine_conf->code_size; i++)
		code[i] ^= engine_conf->eccmask[i];

	वापस 0;
पूर्ण
EXPORT_SYMBOL(nand_ecc_sw_bch_calculate);

/**
 * nand_ecc_sw_bch_correct - Detect, correct and report bit error(s)
 * @nand: न_अंकD device
 * @buf: Raw data पढ़ो from the chip
 * @पढ़ो_ecc: ECC bytes from the chip
 * @calc_ecc: ECC calculated from the raw data
 *
 * Detect and correct bit errors क्रम a data block.
 */
पूर्णांक nand_ecc_sw_bch_correct(काष्ठा nand_device *nand, अचिन्हित अक्षर *buf,
			    अचिन्हित अक्षर *पढ़ो_ecc, अचिन्हित अक्षर *calc_ecc)
अणु
	काष्ठा nand_ecc_sw_bch_conf *engine_conf = nand->ecc.ctx.priv;
	अचिन्हित पूर्णांक step_size = nand->ecc.ctx.conf.step_size;
	अचिन्हित पूर्णांक *errloc = engine_conf->errloc;
	पूर्णांक i, count;

	count = bch_decode(engine_conf->bch, शून्य, step_size, पढ़ो_ecc,
			   calc_ecc, शून्य, errloc);
	अगर (count > 0) अणु
		क्रम (i = 0; i < count; i++) अणु
			अगर (errloc[i] < (step_size * 8))
				/* The error is in the data area: correct it */
				buf[errloc[i] >> 3] ^= (1 << (errloc[i] & 7));

			/* Otherwise the error is in the ECC area: nothing to करो */
			pr_debug("%s: corrected bitflip %u\n", __func__,
				 errloc[i]);
		पूर्ण
	पूर्ण अन्यथा अगर (count < 0) अणु
		pr_err("ECC unrecoverable error\n");
		count = -EBADMSG;
	पूर्ण

	वापस count;
पूर्ण
EXPORT_SYMBOL(nand_ecc_sw_bch_correct);

/**
 * nand_ecc_sw_bch_cleanup - Cleanup software BCH ECC resources
 * @nand: न_अंकD device
 */
अटल व्योम nand_ecc_sw_bch_cleanup(काष्ठा nand_device *nand)
अणु
	काष्ठा nand_ecc_sw_bch_conf *engine_conf = nand->ecc.ctx.priv;

	bch_मुक्त(engine_conf->bch);
	kमुक्त(engine_conf->errloc);
	kमुक्त(engine_conf->eccmask);
पूर्ण

/**
 * nand_ecc_sw_bch_init - Initialize software BCH ECC engine
 * @nand: न_अंकD device
 *
 * Returns: a poपूर्णांकer to a new न_अंकD BCH control काष्ठाure, or शून्य upon failure
 *
 * Initialize न_अंकD BCH error correction. @nand.ecc parameters 'step_size' and
 * 'bytes' are used to compute the following BCH parameters:
 *     m, the Galois field order
 *     t, the error correction capability
 * 'bytes' should be equal to the number of bytes required to store m * t
 * bits, where m is such that 2^m - 1 > step_size * 8.
 *
 * Example: to configure 4 bit correction per 512 bytes, you should pass
 * step_size = 512 (thus, m = 13 is the smallest पूर्णांकeger such that 2^m - 1 > 512 * 8)
 * bytes = 7 (7 bytes are required to store m * t = 13 * 4 = 52 bits)
 */
अटल पूर्णांक nand_ecc_sw_bch_init(काष्ठा nand_device *nand)
अणु
	काष्ठा nand_ecc_sw_bch_conf *engine_conf = nand->ecc.ctx.priv;
	अचिन्हित पूर्णांक eccsize = nand->ecc.ctx.conf.step_size;
	अचिन्हित पूर्णांक eccbytes = engine_conf->code_size;
	अचिन्हित पूर्णांक m, t, i;
	अचिन्हित अक्षर *erased_page;
	पूर्णांक ret;

	m = fls(1 + (8 * eccsize));
	t = (eccbytes * 8) / m;

	engine_conf->bch = bch_init(m, t, 0, false);
	अगर (!engine_conf->bch)
		वापस -EINVAL;

	engine_conf->eccmask = kzalloc(eccbytes, GFP_KERNEL);
	engine_conf->errloc = kदो_स्मृति_array(t, माप(*engine_conf->errloc),
					    GFP_KERNEL);
	अगर (!engine_conf->eccmask || !engine_conf->errloc) अणु
		ret = -ENOMEM;
		जाओ cleanup;
	पूर्ण

	/* Compute and store the inverted ECC of an erased step */
	erased_page = kदो_स्मृति(eccsize, GFP_KERNEL);
	अगर (!erased_page) अणु
		ret = -ENOMEM;
		जाओ cleanup;
	पूर्ण

	स_रखो(erased_page, 0xff, eccsize);
	bch_encode(engine_conf->bch, erased_page, eccsize,
		   engine_conf->eccmask);
	kमुक्त(erased_page);

	क्रम (i = 0; i < eccbytes; i++)
		engine_conf->eccmask[i] ^= 0xff;

	/* Verअगरy that the number of code bytes has the expected value */
	अगर (engine_conf->bch->ecc_bytes != eccbytes) अणु
		pr_err("Invalid number of ECC bytes: %u, expected: %u\n",
		       eccbytes, engine_conf->bch->ecc_bytes);
		ret = -EINVAL;
		जाओ cleanup;
	पूर्ण

	/* Sanity checks */
	अगर (8 * (eccsize + eccbytes) >= (1 << m)) अणु
		pr_err("ECC step size is too large (%u)\n", eccsize);
		ret = -EINVAL;
		जाओ cleanup;
	पूर्ण

	वापस 0;

cleanup:
	nand_ecc_sw_bch_cleanup(nand);

	वापस ret;
पूर्ण

पूर्णांक nand_ecc_sw_bch_init_ctx(काष्ठा nand_device *nand)
अणु
	काष्ठा nand_ecc_props *conf = &nand->ecc.ctx.conf;
	काष्ठा mtd_info *mtd = nanddev_to_mtd(nand);
	काष्ठा nand_ecc_sw_bch_conf *engine_conf;
	अचिन्हित पूर्णांक code_size = 0, nsteps;
	पूर्णांक ret;

	/* Only large page न_अंकD chips may use BCH */
	अगर (mtd->oobsize < 64) अणु
		pr_err("BCH cannot be used with small page NAND chips\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!mtd->ooblayout)
		mtd_set_ooblayout(mtd, nand_get_large_page_ooblayout());

	conf->engine_type = न_अंकD_ECC_ENGINE_TYPE_SOFT;
	conf->algo = न_अंकD_ECC_ALGO_BCH;
	conf->step_size = nand->ecc.user_conf.step_size;
	conf->strength = nand->ecc.user_conf.strength;

	/*
	 * Board driver should supply ECC size and ECC strength
	 * values to select how many bits are correctable.
	 * Otherwise, शेष to 512 bytes क्रम large page devices and 256 क्रम
	 * small page devices.
	 */
	अगर (!conf->step_size) अणु
		अगर (mtd->oobsize >= 64)
			conf->step_size = 512;
		अन्यथा
			conf->step_size = 256;

		conf->strength = 4;
	पूर्ण

	nsteps = mtd->ग_लिखोsize / conf->step_size;

	/* Maximize */
	अगर (nand->ecc.user_conf.flags & न_अंकD_ECC_MAXIMIZE_STRENGTH) अणु
		conf->step_size = 1024;
		nsteps = mtd->ग_लिखोsize / conf->step_size;
		/* Reserve 2 bytes क्रम the BBM */
		code_size = (mtd->oobsize - 2) / nsteps;
		conf->strength = code_size * 8 / fls(8 * conf->step_size);
	पूर्ण

	अगर (!code_size)
		code_size = DIV_ROUND_UP(conf->strength *
					 fls(8 * conf->step_size), 8);

	अगर (!conf->strength)
		conf->strength = (code_size * 8) / fls(8 * conf->step_size);

	अगर (!code_size && !conf->strength) अणु
		pr_err("Missing ECC parameters\n");
		वापस -EINVAL;
	पूर्ण

	engine_conf = kzalloc(माप(*engine_conf), GFP_KERNEL);
	अगर (!engine_conf)
		वापस -ENOMEM;

	ret = nand_ecc_init_req_tweaking(&engine_conf->req_ctx, nand);
	अगर (ret)
		जाओ मुक्त_engine_conf;

	engine_conf->code_size = code_size;
	engine_conf->calc_buf = kzalloc(mtd->oobsize, GFP_KERNEL);
	engine_conf->code_buf = kzalloc(mtd->oobsize, GFP_KERNEL);
	अगर (!engine_conf->calc_buf || !engine_conf->code_buf) अणु
		ret = -ENOMEM;
		जाओ मुक्त_bufs;
	पूर्ण

	nand->ecc.ctx.priv = engine_conf;
	nand->ecc.ctx.nsteps = nsteps;
	nand->ecc.ctx.total = nsteps * code_size;

	ret = nand_ecc_sw_bch_init(nand);
	अगर (ret)
		जाओ मुक्त_bufs;

	/* Verअगरy the layout validity */
	अगर (mtd_ooblayout_count_eccbytes(mtd) !=
	    nand->ecc.ctx.nsteps * engine_conf->code_size) अणु
		pr_err("Invalid ECC layout\n");
		ret = -EINVAL;
		जाओ cleanup_bch_ctx;
	पूर्ण

	वापस 0;

cleanup_bch_ctx:
	nand_ecc_sw_bch_cleanup(nand);
मुक्त_bufs:
	nand_ecc_cleanup_req_tweaking(&engine_conf->req_ctx);
	kमुक्त(engine_conf->calc_buf);
	kमुक्त(engine_conf->code_buf);
मुक्त_engine_conf:
	kमुक्त(engine_conf);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(nand_ecc_sw_bch_init_ctx);

व्योम nand_ecc_sw_bch_cleanup_ctx(काष्ठा nand_device *nand)
अणु
	काष्ठा nand_ecc_sw_bch_conf *engine_conf = nand->ecc.ctx.priv;

	अगर (engine_conf) अणु
		nand_ecc_sw_bch_cleanup(nand);
		nand_ecc_cleanup_req_tweaking(&engine_conf->req_ctx);
		kमुक्त(engine_conf->calc_buf);
		kमुक्त(engine_conf->code_buf);
		kमुक्त(engine_conf);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(nand_ecc_sw_bch_cleanup_ctx);

अटल पूर्णांक nand_ecc_sw_bch_prepare_io_req(काष्ठा nand_device *nand,
					  काष्ठा nand_page_io_req *req)
अणु
	काष्ठा nand_ecc_sw_bch_conf *engine_conf = nand->ecc.ctx.priv;
	काष्ठा mtd_info *mtd = nanddev_to_mtd(nand);
	पूर्णांक eccsize = nand->ecc.ctx.conf.step_size;
	पूर्णांक eccbytes = engine_conf->code_size;
	पूर्णांक eccsteps = nand->ecc.ctx.nsteps;
	पूर्णांक total = nand->ecc.ctx.total;
	u8 *ecccalc = engine_conf->calc_buf;
	स्थिर u8 *data;
	पूर्णांक i;

	/* Nothing to करो क्रम a raw operation */
	अगर (req->mode == MTD_OPS_RAW)
		वापस 0;

	/* This engine करोes not provide BBM/मुक्त OOB bytes protection */
	अगर (!req->datalen)
		वापस 0;

	nand_ecc_tweak_req(&engine_conf->req_ctx, req);

	/* No more preparation क्रम page पढ़ो */
	अगर (req->type == न_अंकD_PAGE_READ)
		वापस 0;

	/* Preparation क्रम page ग_लिखो: derive the ECC bytes and place them */
	क्रम (i = 0, data = req->databuf.out;
	     eccsteps;
	     eccsteps--, i += eccbytes, data += eccsize)
		nand_ecc_sw_bch_calculate(nand, data, &ecccalc[i]);

	वापस mtd_ooblayout_set_eccbytes(mtd, ecccalc, (व्योम *)req->oobbuf.out,
					  0, total);
पूर्ण

अटल पूर्णांक nand_ecc_sw_bch_finish_io_req(काष्ठा nand_device *nand,
					 काष्ठा nand_page_io_req *req)
अणु
	काष्ठा nand_ecc_sw_bch_conf *engine_conf = nand->ecc.ctx.priv;
	काष्ठा mtd_info *mtd = nanddev_to_mtd(nand);
	पूर्णांक eccsize = nand->ecc.ctx.conf.step_size;
	पूर्णांक total = nand->ecc.ctx.total;
	पूर्णांक eccbytes = engine_conf->code_size;
	पूर्णांक eccsteps = nand->ecc.ctx.nsteps;
	u8 *ecccalc = engine_conf->calc_buf;
	u8 *ecccode = engine_conf->code_buf;
	अचिन्हित पूर्णांक max_bitflips = 0;
	u8 *data = req->databuf.in;
	पूर्णांक i, ret;

	/* Nothing to करो क्रम a raw operation */
	अगर (req->mode == MTD_OPS_RAW)
		वापस 0;

	/* This engine करोes not provide BBM/मुक्त OOB bytes protection */
	अगर (!req->datalen)
		वापस 0;

	/* No more preparation क्रम page ग_लिखो */
	अगर (req->type == न_अंकD_PAGE_WRITE) अणु
		nand_ecc_restore_req(&engine_conf->req_ctx, req);
		वापस 0;
	पूर्ण

	/* Finish a page पढ़ो: retrieve the (raw) ECC bytes*/
	ret = mtd_ooblayout_get_eccbytes(mtd, ecccode, req->oobbuf.in, 0,
					 total);
	अगर (ret)
		वापस ret;

	/* Calculate the ECC bytes */
	क्रम (i = 0; eccsteps; eccsteps--, i += eccbytes, data += eccsize)
		nand_ecc_sw_bch_calculate(nand, data, &ecccalc[i]);

	/* Finish a page पढ़ो: compare and correct */
	क्रम (eccsteps = nand->ecc.ctx.nsteps, i = 0, data = req->databuf.in;
	     eccsteps;
	     eccsteps--, i += eccbytes, data += eccsize) अणु
		पूर्णांक stat =  nand_ecc_sw_bch_correct(nand, data,
						    &ecccode[i],
						    &ecccalc[i]);
		अगर (stat < 0) अणु
			mtd->ecc_stats.failed++;
		पूर्ण अन्यथा अणु
			mtd->ecc_stats.corrected += stat;
			max_bitflips = max_t(अचिन्हित पूर्णांक, max_bitflips, stat);
		पूर्ण
	पूर्ण

	nand_ecc_restore_req(&engine_conf->req_ctx, req);

	वापस max_bitflips;
पूर्ण

अटल काष्ठा nand_ecc_engine_ops nand_ecc_sw_bch_engine_ops = अणु
	.init_ctx = nand_ecc_sw_bch_init_ctx,
	.cleanup_ctx = nand_ecc_sw_bch_cleanup_ctx,
	.prepare_io_req = nand_ecc_sw_bch_prepare_io_req,
	.finish_io_req = nand_ecc_sw_bch_finish_io_req,
पूर्ण;

अटल काष्ठा nand_ecc_engine nand_ecc_sw_bch_engine = अणु
	.ops = &nand_ecc_sw_bch_engine_ops,
पूर्ण;

काष्ठा nand_ecc_engine *nand_ecc_sw_bch_get_engine(व्योम)
अणु
	वापस &nand_ecc_sw_bch_engine;
पूर्ण
EXPORT_SYMBOL(nand_ecc_sw_bch_get_engine);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ivan Djelic <ivan.djelic@parrot.com>");
MODULE_DESCRIPTION("NAND software BCH ECC support");
