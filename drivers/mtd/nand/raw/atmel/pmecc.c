<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2017 ATMEL
 * Copyright 2017 Free Electrons
 *
 * Author: Boris Brezillon <boris.brezillon@मुक्त-electrons.com>
 *
 * Derived from the aपंचांगel_nand.c driver which contained the following
 * copyrights:
 *
 *   Copyright 2003 Rick Bronson
 *
 *   Derived from drivers/mtd/nand/autcpu12.c (हटाओd in v3.8)
 *	Copyright 2001 Thomas Gleixner (gleixner@autronix.de)
 *
 *   Derived from drivers/mtd/spia.c (हटाओd in v3.8)
 *	Copyright 2000 Steven J. Hill (sjhill@cotw.com)
 *
 *   Add Hardware ECC support क्रम AT91SAM9260 / AT91SAM9263
 *	Riअक्षरd Genoud (riअक्षरd.genoud@gmail.com), Adeneo Copyright 2007
 *
 *   Derived from Das U-Boot source code
 *	(u-boot-1.1.5/board/aपंचांगel/at91sam9263ek/nand.c)
 *      Copyright 2006 ATMEL Rousset, Lacressonniere Nicolas
 *
 *   Add Programmable Multibit ECC support क्रम various AT91 SoC
 *	Copyright 2012 ATMEL, Hong Xu
 *
 *   Add Nand Flash Controller support क्रम SAMA5 SoC
 *	Copyright 2013 ATMEL, Josh Wu (josh.wu@aपंचांगel.com)
 *
 * The PMECC is an hardware assisted BCH engine, which means part of the
 * ECC algorithm is left to the software. The hardware/software repartition
 * is explained in the "PMECC Controller Functional Description" chapter in
 * Aपंचांगel datasheets, and some of the functions in this file are directly
 * implementing the algorithms described in the "Software Implementation"
 * sub-section.
 *
 * TODO: it seems that the software BCH implementation in lib/bch.c is alपढ़ोy
 * providing some of the logic we are implementing here. It would be smart
 * to expose the needed lib/bch.c helpers/functions and re-use them here.
 */

#समावेश <linux/genभाग.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश "pmecc.h"

/* Galois field dimension */
#घोषणा PMECC_GF_DIMENSION_13			13
#घोषणा PMECC_GF_DIMENSION_14			14

/* Primitive Polynomial used by PMECC */
#घोषणा PMECC_GF_13_PRIMITIVE_POLY		0x201b
#घोषणा PMECC_GF_14_PRIMITIVE_POLY		0x4443

#घोषणा PMECC_LOOKUP_TABLE_SIZE_512		0x2000
#घोषणा PMECC_LOOKUP_TABLE_SIZE_1024		0x4000

/* Time out value क्रम पढ़ोing PMECC status रेजिस्टर */
#घोषणा PMECC_MAX_TIMEOUT_MS			100

/* PMECC Register Definitions */
#घोषणा ATMEL_PMECC_CFG				0x0
#घोषणा PMECC_CFG_BCH_STRENGTH(x)		(x)
#घोषणा PMECC_CFG_BCH_STRENGTH_MASK		GENMASK(2, 0)
#घोषणा PMECC_CFG_SECTOR512			(0 << 4)
#घोषणा PMECC_CFG_SECTOR1024			(1 << 4)
#घोषणा PMECC_CFG_NSECTORS(x)			((fls(x) - 1) << 8)
#घोषणा PMECC_CFG_READ_OP			(0 << 12)
#घोषणा PMECC_CFG_WRITE_OP			(1 << 12)
#घोषणा PMECC_CFG_SPARE_ENABLE			BIT(16)
#घोषणा PMECC_CFG_AUTO_ENABLE			BIT(20)

#घोषणा ATMEL_PMECC_SAREA			0x4
#घोषणा ATMEL_PMECC_SADDR			0x8
#घोषणा ATMEL_PMECC_EADDR			0xc

#घोषणा ATMEL_PMECC_CLK				0x10
#घोषणा PMECC_CLK_133MHZ			(2 << 0)

#घोषणा ATMEL_PMECC_CTRL			0x14
#घोषणा PMECC_CTRL_RST				BIT(0)
#घोषणा PMECC_CTRL_DATA				BIT(1)
#घोषणा PMECC_CTRL_USER				BIT(2)
#घोषणा PMECC_CTRL_ENABLE			BIT(4)
#घोषणा PMECC_CTRL_DISABLE			BIT(5)

#घोषणा ATMEL_PMECC_SR				0x18
#घोषणा PMECC_SR_BUSY				BIT(0)
#घोषणा PMECC_SR_ENABLE				BIT(4)

#घोषणा ATMEL_PMECC_IER				0x1c
#घोषणा ATMEL_PMECC_IDR				0x20
#घोषणा ATMEL_PMECC_IMR				0x24
#घोषणा ATMEL_PMECC_ISR				0x28
#घोषणा PMECC_ERROR_INT				BIT(0)

#घोषणा ATMEL_PMECC_ECC(sector, n)		\
	((((sector) + 1) * 0x40) + (n))

#घोषणा ATMEL_PMECC_REM(sector, n)		\
	((((sector) + 1) * 0x40) + ((n) * 4) + 0x200)

/* PMERRLOC Register Definitions */
#घोषणा ATMEL_PMERRLOC_ELCFG			0x0
#घोषणा PMERRLOC_ELCFG_SECTOR_512		(0 << 0)
#घोषणा PMERRLOC_ELCFG_SECTOR_1024		(1 << 0)
#घोषणा PMERRLOC_ELCFG_NUM_ERRORS(n)		((n) << 16)

#घोषणा ATMEL_PMERRLOC_ELPRIM			0x4
#घोषणा ATMEL_PMERRLOC_ELEN			0x8
#घोषणा ATMEL_PMERRLOC_ELDIS			0xc
#घोषणा PMERRLOC_DISABLE			BIT(0)

#घोषणा ATMEL_PMERRLOC_ELSR			0x10
#घोषणा PMERRLOC_ELSR_BUSY			BIT(0)

#घोषणा ATMEL_PMERRLOC_ELIER			0x14
#घोषणा ATMEL_PMERRLOC_ELIDR			0x18
#घोषणा ATMEL_PMERRLOC_ELIMR			0x1c
#घोषणा ATMEL_PMERRLOC_ELISR			0x20
#घोषणा PMERRLOC_ERR_NUM_MASK			GENMASK(12, 8)
#घोषणा PMERRLOC_CALC_DONE			BIT(0)

#घोषणा ATMEL_PMERRLOC_SIGMA(x)			(((x) * 0x4) + 0x28)

#घोषणा ATMEL_PMERRLOC_EL(offs, x)		(((x) * 0x4) + (offs))

काष्ठा aपंचांगel_pmecc_gf_tables अणु
	u16 *alpha_to;
	u16 *index_of;
पूर्ण;

काष्ठा aपंचांगel_pmecc_caps अणु
	स्थिर पूर्णांक *strengths;
	पूर्णांक nstrengths;
	पूर्णांक el_offset;
	bool correct_erased_chunks;
पूर्ण;

काष्ठा aपंचांगel_pmecc अणु
	काष्ठा device *dev;
	स्थिर काष्ठा aपंचांगel_pmecc_caps *caps;

	काष्ठा अणु
		व्योम __iomem *base;
		व्योम __iomem *errloc;
	पूर्ण regs;

	काष्ठा mutex lock;
पूर्ण;

काष्ठा aपंचांगel_pmecc_user_conf_cache अणु
	u32 cfg;
	u32 sarea;
	u32 saddr;
	u32 eaddr;
पूर्ण;

काष्ठा aपंचांगel_pmecc_user अणु
	काष्ठा aपंचांगel_pmecc_user_conf_cache cache;
	काष्ठा aपंचांगel_pmecc *pmecc;
	स्थिर काष्ठा aपंचांगel_pmecc_gf_tables *gf_tables;
	पूर्णांक eccbytes;
	s16 *partial_syn;
	s16 *si;
	s16 *lmu;
	s16 *smu;
	s32 *mu;
	s32 *dmu;
	s32 *delta;
	u32 isr;
पूर्ण;

अटल DEFINE_MUTEX(pmecc_gf_tables_lock);
अटल स्थिर काष्ठा aपंचांगel_pmecc_gf_tables *pmecc_gf_tables_512;
अटल स्थिर काष्ठा aपंचांगel_pmecc_gf_tables *pmecc_gf_tables_1024;

अटल अंतरभूत पूर्णांक deg(अचिन्हित पूर्णांक poly)
अणु
	/* polynomial degree is the most-signअगरicant bit index */
	वापस fls(poly) - 1;
पूर्ण

अटल पूर्णांक aपंचांगel_pmecc_build_gf_tables(पूर्णांक mm, अचिन्हित पूर्णांक poly,
				       काष्ठा aपंचांगel_pmecc_gf_tables *gf_tables)
अणु
	अचिन्हित पूर्णांक i, x = 1;
	स्थिर अचिन्हित पूर्णांक k = BIT(deg(poly));
	अचिन्हित पूर्णांक nn = BIT(mm) - 1;

	/* primitive polynomial must be of degree m */
	अगर (k != (1u << mm))
		वापस -EINVAL;

	क्रम (i = 0; i < nn; i++) अणु
		gf_tables->alpha_to[i] = x;
		gf_tables->index_of[x] = i;
		अगर (i && (x == 1))
			/* polynomial is not primitive (a^i=1 with 0<i<2^m-1) */
			वापस -EINVAL;
		x <<= 1;
		अगर (x & k)
			x ^= poly;
	पूर्ण
	gf_tables->alpha_to[nn] = 1;
	gf_tables->index_of[0] = 0;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा aपंचांगel_pmecc_gf_tables *
aपंचांगel_pmecc_create_gf_tables(स्थिर काष्ठा aपंचांगel_pmecc_user_req *req)
अणु
	काष्ठा aपंचांगel_pmecc_gf_tables *gf_tables;
	अचिन्हित पूर्णांक poly, degree, table_size;
	पूर्णांक ret;

	अगर (req->ecc.sectorsize == 512) अणु
		degree = PMECC_GF_DIMENSION_13;
		poly = PMECC_GF_13_PRIMITIVE_POLY;
		table_size = PMECC_LOOKUP_TABLE_SIZE_512;
	पूर्ण अन्यथा अणु
		degree = PMECC_GF_DIMENSION_14;
		poly = PMECC_GF_14_PRIMITIVE_POLY;
		table_size = PMECC_LOOKUP_TABLE_SIZE_1024;
	पूर्ण

	gf_tables = kzalloc(माप(*gf_tables) +
			    (2 * table_size * माप(u16)),
			    GFP_KERNEL);
	अगर (!gf_tables)
		वापस ERR_PTR(-ENOMEM);

	gf_tables->alpha_to = (व्योम *)(gf_tables + 1);
	gf_tables->index_of = gf_tables->alpha_to + table_size;

	ret = aपंचांगel_pmecc_build_gf_tables(degree, poly, gf_tables);
	अगर (ret) अणु
		kमुक्त(gf_tables);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस gf_tables;
पूर्ण

अटल स्थिर काष्ठा aपंचांगel_pmecc_gf_tables *
aपंचांगel_pmecc_get_gf_tables(स्थिर काष्ठा aपंचांगel_pmecc_user_req *req)
अणु
	स्थिर काष्ठा aपंचांगel_pmecc_gf_tables **gf_tables, *ret;

	mutex_lock(&pmecc_gf_tables_lock);
	अगर (req->ecc.sectorsize == 512)
		gf_tables = &pmecc_gf_tables_512;
	अन्यथा
		gf_tables = &pmecc_gf_tables_1024;

	ret = *gf_tables;

	अगर (!ret) अणु
		ret = aपंचांगel_pmecc_create_gf_tables(req);
		अगर (!IS_ERR(ret))
			*gf_tables = ret;
	पूर्ण
	mutex_unlock(&pmecc_gf_tables_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक aपंचांगel_pmecc_prepare_user_req(काष्ठा aपंचांगel_pmecc *pmecc,
					काष्ठा aपंचांगel_pmecc_user_req *req)
अणु
	पूर्णांक i, max_eccbytes, eccbytes = 0, eccstrength = 0;

	अगर (req->pagesize <= 0 || req->oobsize <= 0 || req->ecc.bytes <= 0)
		वापस -EINVAL;

	अगर (req->ecc.ooboffset >= 0 &&
	    req->ecc.ooboffset + req->ecc.bytes > req->oobsize)
		वापस -EINVAL;

	अगर (req->ecc.sectorsize == ATMEL_PMECC_SECTOR_SIZE_AUTO) अणु
		अगर (req->ecc.strength != ATMEL_PMECC_MAXIMIZE_ECC_STRENGTH)
			वापस -EINVAL;

		अगर (req->pagesize > 512)
			req->ecc.sectorsize = 1024;
		अन्यथा
			req->ecc.sectorsize = 512;
	पूर्ण

	अगर (req->ecc.sectorsize != 512 && req->ecc.sectorsize != 1024)
		वापस -EINVAL;

	अगर (req->pagesize % req->ecc.sectorsize)
		वापस -EINVAL;

	req->ecc.nsectors = req->pagesize / req->ecc.sectorsize;

	max_eccbytes = req->ecc.bytes;

	क्रम (i = 0; i < pmecc->caps->nstrengths; i++) अणु
		पूर्णांक nbytes, strength = pmecc->caps->strengths[i];

		अगर (req->ecc.strength != ATMEL_PMECC_MAXIMIZE_ECC_STRENGTH &&
		    strength < req->ecc.strength)
			जारी;

		nbytes = DIV_ROUND_UP(strength * fls(8 * req->ecc.sectorsize),
				      8);
		nbytes *= req->ecc.nsectors;

		अगर (nbytes > max_eccbytes)
			अवरोध;

		eccstrength = strength;
		eccbytes = nbytes;

		अगर (req->ecc.strength != ATMEL_PMECC_MAXIMIZE_ECC_STRENGTH)
			अवरोध;
	पूर्ण

	अगर (!eccstrength)
		वापस -EINVAL;

	req->ecc.bytes = eccbytes;
	req->ecc.strength = eccstrength;

	अगर (req->ecc.ooboffset < 0)
		req->ecc.ooboffset = req->oobsize - eccbytes;

	वापस 0;
पूर्ण

काष्ठा aपंचांगel_pmecc_user *
aपंचांगel_pmecc_create_user(काष्ठा aपंचांगel_pmecc *pmecc,
			काष्ठा aपंचांगel_pmecc_user_req *req)
अणु
	काष्ठा aपंचांगel_pmecc_user *user;
	स्थिर काष्ठा aपंचांगel_pmecc_gf_tables *gf_tables;
	पूर्णांक strength, size, ret;

	ret = aपंचांगel_pmecc_prepare_user_req(pmecc, req);
	अगर (ret)
		वापस ERR_PTR(ret);

	size = माप(*user);
	size = ALIGN(size, माप(u16));
	/* Reserve space क्रम partial_syn, si and smu */
	size += ((2 * req->ecc.strength) + 1) * माप(u16) *
		(2 + req->ecc.strength + 2);
	/* Reserve space क्रम lmu. */
	size += (req->ecc.strength + 1) * माप(u16);
	/* Reserve space क्रम mu, dmu and delta. */
	size = ALIGN(size, माप(s32));
	size += (req->ecc.strength + 1) * माप(s32) * 3;

	user = kzalloc(size, GFP_KERNEL);
	अगर (!user)
		वापस ERR_PTR(-ENOMEM);

	user->pmecc = pmecc;

	user->partial_syn = (s16 *)PTR_ALIGN(user + 1, माप(u16));
	user->si = user->partial_syn + ((2 * req->ecc.strength) + 1);
	user->lmu = user->si + ((2 * req->ecc.strength) + 1);
	user->smu = user->lmu + (req->ecc.strength + 1);
	user->mu = (s32 *)PTR_ALIGN(user->smu +
				    (((2 * req->ecc.strength) + 1) *
				     (req->ecc.strength + 2)),
				    माप(s32));
	user->dmu = user->mu + req->ecc.strength + 1;
	user->delta = user->dmu + req->ecc.strength + 1;

	gf_tables = aपंचांगel_pmecc_get_gf_tables(req);
	अगर (IS_ERR(gf_tables)) अणु
		kमुक्त(user);
		वापस ERR_CAST(gf_tables);
	पूर्ण

	user->gf_tables = gf_tables;

	user->eccbytes = req->ecc.bytes / req->ecc.nsectors;

	क्रम (strength = 0; strength < pmecc->caps->nstrengths; strength++) अणु
		अगर (pmecc->caps->strengths[strength] == req->ecc.strength)
			अवरोध;
	पूर्ण

	user->cache.cfg = PMECC_CFG_BCH_STRENGTH(strength) |
			  PMECC_CFG_NSECTORS(req->ecc.nsectors);

	अगर (req->ecc.sectorsize == 1024)
		user->cache.cfg |= PMECC_CFG_SECTOR1024;

	user->cache.sarea = req->oobsize - 1;
	user->cache.saddr = req->ecc.ooboffset;
	user->cache.eaddr = req->ecc.ooboffset + req->ecc.bytes - 1;

	वापस user;
पूर्ण
EXPORT_SYMBOL_GPL(aपंचांगel_pmecc_create_user);

व्योम aपंचांगel_pmecc_destroy_user(काष्ठा aपंचांगel_pmecc_user *user)
अणु
	kमुक्त(user);
पूर्ण
EXPORT_SYMBOL_GPL(aपंचांगel_pmecc_destroy_user);

अटल पूर्णांक get_strength(काष्ठा aपंचांगel_pmecc_user *user)
अणु
	स्थिर पूर्णांक *strengths = user->pmecc->caps->strengths;

	वापस strengths[user->cache.cfg & PMECC_CFG_BCH_STRENGTH_MASK];
पूर्ण

अटल पूर्णांक get_sectorsize(काष्ठा aपंचांगel_pmecc_user *user)
अणु
	वापस user->cache.cfg & PMECC_CFG_SECTOR1024 ? 1024 : 512;
पूर्ण

अटल व्योम aपंचांगel_pmecc_gen_syndrome(काष्ठा aपंचांगel_pmecc_user *user, पूर्णांक sector)
अणु
	पूर्णांक strength = get_strength(user);
	u32 value;
	पूर्णांक i;

	/* Fill odd syndromes */
	क्रम (i = 0; i < strength; i++) अणु
		value = पढ़ोl_relaxed(user->pmecc->regs.base +
				      ATMEL_PMECC_REM(sector, i / 2));
		अगर (i & 1)
			value >>= 16;

		user->partial_syn[(2 * i) + 1] = value;
	पूर्ण
पूर्ण

अटल व्योम aपंचांगel_pmecc_substitute(काष्ठा aपंचांगel_pmecc_user *user)
अणु
	पूर्णांक degree = get_sectorsize(user) == 512 ? 13 : 14;
	पूर्णांक cw_len = BIT(degree) - 1;
	पूर्णांक strength = get_strength(user);
	s16 *alpha_to = user->gf_tables->alpha_to;
	s16 *index_of = user->gf_tables->index_of;
	s16 *partial_syn = user->partial_syn;
	s16 *si;
	पूर्णांक i, j;

	/*
	 * si[] is a table that holds the current syndrome value,
	 * an element of that table beदीर्घs to the field
	 */
	si = user->si;

	स_रखो(&si[1], 0, माप(s16) * ((2 * strength) - 1));

	/* Computation 2t syndromes based on S(x) */
	/* Odd syndromes */
	क्रम (i = 1; i < 2 * strength; i += 2) अणु
		क्रम (j = 0; j < degree; j++) अणु
			अगर (partial_syn[i] & BIT(j))
				si[i] = alpha_to[i * j] ^ si[i];
		पूर्ण
	पूर्ण
	/* Even syndrome = (Odd syndrome) ** 2 */
	क्रम (i = 2, j = 1; j <= strength; i = ++j << 1) अणु
		अगर (si[j] == 0) अणु
			si[i] = 0;
		पूर्ण अन्यथा अणु
			s16 पंचांगp;

			पंचांगp = index_of[si[j]];
			पंचांगp = (पंचांगp * 2) % cw_len;
			si[i] = alpha_to[पंचांगp];
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम aपंचांगel_pmecc_get_sigma(काष्ठा aपंचांगel_pmecc_user *user)
अणु
	s16 *lmu = user->lmu;
	s16 *si = user->si;
	s32 *mu = user->mu;
	s32 *dmu = user->dmu;
	s32 *delta = user->delta;
	पूर्णांक degree = get_sectorsize(user) == 512 ? 13 : 14;
	पूर्णांक cw_len = BIT(degree) - 1;
	पूर्णांक strength = get_strength(user);
	पूर्णांक num = 2 * strength + 1;
	s16 *index_of = user->gf_tables->index_of;
	s16 *alpha_to = user->gf_tables->alpha_to;
	पूर्णांक i, j, k;
	u32 dmu_0_count, पंचांगp;
	s16 *smu = user->smu;

	/* index of largest delta */
	पूर्णांक ro;
	पूर्णांक largest;
	पूर्णांक dअगरf;

	dmu_0_count = 0;

	/* First Row */

	/* Mu */
	mu[0] = -1;

	स_रखो(smu, 0, माप(s16) * num);
	smu[0] = 1;

	/* discrepancy set to 1 */
	dmu[0] = 1;
	/* polynom order set to 0 */
	lmu[0] = 0;
	delta[0] = (mu[0] * 2 - lmu[0]) >> 1;

	/* Second Row */

	/* Mu */
	mu[1] = 0;
	/* Sigma(x) set to 1 */
	स_रखो(&smu[num], 0, माप(s16) * num);
	smu[num] = 1;

	/* discrepancy set to S1 */
	dmu[1] = si[1];

	/* polynom order set to 0 */
	lmu[1] = 0;

	delta[1] = (mu[1] * 2 - lmu[1]) >> 1;

	/* Init the Sigma(x) last row */
	स_रखो(&smu[(strength + 1) * num], 0, माप(s16) * num);

	क्रम (i = 1; i <= strength; i++) अणु
		mu[i + 1] = i << 1;
		/* Begin Computing Sigma (Mu+1) and L(mu) */
		/* check अगर discrepancy is set to 0 */
		अगर (dmu[i] == 0) अणु
			dmu_0_count++;

			पंचांगp = ((strength - (lmu[i] >> 1) - 1) / 2);
			अगर ((strength - (lmu[i] >> 1) - 1) & 0x1)
				पंचांगp += 2;
			अन्यथा
				पंचांगp += 1;

			अगर (dmu_0_count == पंचांगp) अणु
				क्रम (j = 0; j <= (lmu[i] >> 1) + 1; j++)
					smu[(strength + 1) * num + j] =
							smu[i * num + j];

				lmu[strength + 1] = lmu[i];
				वापस;
			पूर्ण

			/* copy polynom */
			क्रम (j = 0; j <= lmu[i] >> 1; j++)
				smu[(i + 1) * num + j] = smu[i * num + j];

			/* copy previous polynom order to the next */
			lmu[i + 1] = lmu[i];
		पूर्ण अन्यथा अणु
			ro = 0;
			largest = -1;
			/* find largest delta with dmu != 0 */
			क्रम (j = 0; j < i; j++) अणु
				अगर ((dmu[j]) && (delta[j] > largest)) अणु
					largest = delta[j];
					ro = j;
				पूर्ण
			पूर्ण

			/* compute dअगरference */
			dअगरf = (mu[i] - mu[ro]);

			/* Compute degree of the new smu polynomial */
			अगर ((lmu[i] >> 1) > ((lmu[ro] >> 1) + dअगरf))
				lmu[i + 1] = lmu[i];
			अन्यथा
				lmu[i + 1] = ((lmu[ro] >> 1) + dअगरf) * 2;

			/* Init smu[i+1] with 0 */
			क्रम (k = 0; k < num; k++)
				smu[(i + 1) * num + k] = 0;

			/* Compute smu[i+1] */
			क्रम (k = 0; k <= lmu[ro] >> 1; k++) अणु
				s16 a, b, c;

				अगर (!(smu[ro * num + k] && dmu[i]))
					जारी;

				a = index_of[dmu[i]];
				b = index_of[dmu[ro]];
				c = index_of[smu[ro * num + k]];
				पंचांगp = a + (cw_len - b) + c;
				a = alpha_to[पंचांगp % cw_len];
				smu[(i + 1) * num + (k + dअगरf)] = a;
			पूर्ण

			क्रम (k = 0; k <= lmu[i] >> 1; k++)
				smu[(i + 1) * num + k] ^= smu[i * num + k];
		पूर्ण

		/* End Computing Sigma (Mu+1) and L(mu) */
		/* In either हाल compute delta */
		delta[i + 1] = (mu[i + 1] * 2 - lmu[i + 1]) >> 1;

		/* Do not compute discrepancy क्रम the last iteration */
		अगर (i >= strength)
			जारी;

		क्रम (k = 0; k <= (lmu[i + 1] >> 1); k++) अणु
			पंचांगp = 2 * (i - 1);
			अगर (k == 0) अणु
				dmu[i + 1] = si[पंचांगp + 3];
			पूर्ण अन्यथा अगर (smu[(i + 1) * num + k] && si[पंचांगp + 3 - k]) अणु
				s16 a, b, c;

				a = index_of[smu[(i + 1) * num + k]];
				b = si[2 * (i - 1) + 3 - k];
				c = index_of[b];
				पंचांगp = a + c;
				पंचांगp %= cw_len;
				dmu[i + 1] = alpha_to[पंचांगp] ^ dmu[i + 1];
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक aपंचांगel_pmecc_err_location(काष्ठा aपंचांगel_pmecc_user *user)
अणु
	पूर्णांक sector_size = get_sectorsize(user);
	पूर्णांक degree = sector_size == 512 ? 13 : 14;
	काष्ठा aपंचांगel_pmecc *pmecc = user->pmecc;
	पूर्णांक strength = get_strength(user);
	पूर्णांक ret, roots_nbr, i, err_nbr = 0;
	पूर्णांक num = (2 * strength) + 1;
	s16 *smu = user->smu;
	u32 val;

	ग_लिखोl(PMERRLOC_DISABLE, pmecc->regs.errloc + ATMEL_PMERRLOC_ELDIS);

	क्रम (i = 0; i <= user->lmu[strength + 1] >> 1; i++) अणु
		ग_लिखोl_relaxed(smu[(strength + 1) * num + i],
			       pmecc->regs.errloc + ATMEL_PMERRLOC_SIGMA(i));
		err_nbr++;
	पूर्ण

	val = (err_nbr - 1) << 16;
	अगर (sector_size == 1024)
		val |= 1;

	ग_लिखोl(val, pmecc->regs.errloc + ATMEL_PMERRLOC_ELCFG);
	ग_लिखोl((sector_size * 8) + (degree * strength),
	       pmecc->regs.errloc + ATMEL_PMERRLOC_ELEN);

	ret = पढ़ोl_relaxed_poll_समयout(pmecc->regs.errloc +
					 ATMEL_PMERRLOC_ELISR,
					 val, val & PMERRLOC_CALC_DONE, 0,
					 PMECC_MAX_TIMEOUT_MS * 1000);
	अगर (ret) अणु
		dev_err(pmecc->dev,
			"PMECC: Timeout to calculate error location.\n");
		वापस ret;
	पूर्ण

	roots_nbr = (val & PMERRLOC_ERR_NUM_MASK) >> 8;
	/* Number of roots == degree of smu hence <= cap */
	अगर (roots_nbr == user->lmu[strength + 1] >> 1)
		वापस err_nbr - 1;

	/*
	 * Number of roots करोes not match the degree of smu
	 * unable to correct error.
	 */
	वापस -EBADMSG;
पूर्ण

पूर्णांक aपंचांगel_pmecc_correct_sector(काष्ठा aपंचांगel_pmecc_user *user, पूर्णांक sector,
			       व्योम *data, व्योम *ecc)
अणु
	काष्ठा aपंचांगel_pmecc *pmecc = user->pmecc;
	पूर्णांक sectorsize = get_sectorsize(user);
	पूर्णांक eccbytes = user->eccbytes;
	पूर्णांक i, nerrors;

	अगर (!(user->isr & BIT(sector)))
		वापस 0;

	aपंचांगel_pmecc_gen_syndrome(user, sector);
	aपंचांगel_pmecc_substitute(user);
	aपंचांगel_pmecc_get_sigma(user);

	nerrors = aपंचांगel_pmecc_err_location(user);
	अगर (nerrors < 0)
		वापस nerrors;

	क्रम (i = 0; i < nerrors; i++) अणु
		स्थिर अक्षर *area;
		पूर्णांक byte, bit;
		u32 errpos;
		u8 *ptr;

		errpos = पढ़ोl_relaxed(pmecc->regs.errloc +
				ATMEL_PMERRLOC_EL(pmecc->caps->el_offset, i));
		errpos--;

		byte = errpos / 8;
		bit = errpos % 8;

		अगर (byte < sectorsize) अणु
			ptr = data + byte;
			area = "data";
		पूर्ण अन्यथा अगर (byte < sectorsize + eccbytes) अणु
			ptr = ecc + byte - sectorsize;
			area = "ECC";
		पूर्ण अन्यथा अणु
			dev_dbg(pmecc->dev,
				"Invalid errpos value (%d, max is %d)\n",
				errpos, (sectorsize + eccbytes) * 8);
			वापस -EINVAL;
		पूर्ण

		dev_dbg(pmecc->dev,
			"Bit flip in %s area, byte %d: 0x%02x -> 0x%02x\n",
			area, byte, *ptr, (अचिन्हित पूर्णांक)(*ptr ^ BIT(bit)));

		*ptr ^= BIT(bit);
	पूर्ण

	वापस nerrors;
पूर्ण
EXPORT_SYMBOL_GPL(aपंचांगel_pmecc_correct_sector);

bool aपंचांगel_pmecc_correct_erased_chunks(काष्ठा aपंचांगel_pmecc_user *user)
अणु
	वापस user->pmecc->caps->correct_erased_chunks;
पूर्ण
EXPORT_SYMBOL_GPL(aपंचांगel_pmecc_correct_erased_chunks);

व्योम aपंचांगel_pmecc_get_generated_eccbytes(काष्ठा aपंचांगel_pmecc_user *user,
					पूर्णांक sector, व्योम *ecc)
अणु
	काष्ठा aपंचांगel_pmecc *pmecc = user->pmecc;
	u8 *ptr = ecc;
	पूर्णांक i;

	क्रम (i = 0; i < user->eccbytes; i++)
		ptr[i] = पढ़ोb_relaxed(pmecc->regs.base +
				       ATMEL_PMECC_ECC(sector, i));
पूर्ण
EXPORT_SYMBOL_GPL(aपंचांगel_pmecc_get_generated_eccbytes);

व्योम aपंचांगel_pmecc_reset(काष्ठा aपंचांगel_pmecc *pmecc)
अणु
	ग_लिखोl(PMECC_CTRL_RST, pmecc->regs.base + ATMEL_PMECC_CTRL);
	ग_लिखोl(PMECC_CTRL_DISABLE, pmecc->regs.base + ATMEL_PMECC_CTRL);
पूर्ण
EXPORT_SYMBOL_GPL(aपंचांगel_pmecc_reset);

पूर्णांक aपंचांगel_pmecc_enable(काष्ठा aपंचांगel_pmecc_user *user, पूर्णांक op)
अणु
	काष्ठा aपंचांगel_pmecc *pmecc = user->pmecc;
	u32 cfg;

	अगर (op != न_अंकD_ECC_READ && op != न_अंकD_ECC_WRITE) अणु
		dev_err(pmecc->dev, "Bad ECC operation!");
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&user->pmecc->lock);

	cfg = user->cache.cfg;
	अगर (op == न_अंकD_ECC_WRITE)
		cfg |= PMECC_CFG_WRITE_OP;
	अन्यथा
		cfg |= PMECC_CFG_AUTO_ENABLE;

	ग_लिखोl(cfg, pmecc->regs.base + ATMEL_PMECC_CFG);
	ग_लिखोl(user->cache.sarea, pmecc->regs.base + ATMEL_PMECC_SAREA);
	ग_लिखोl(user->cache.saddr, pmecc->regs.base + ATMEL_PMECC_SADDR);
	ग_लिखोl(user->cache.eaddr, pmecc->regs.base + ATMEL_PMECC_EADDR);

	ग_लिखोl(PMECC_CTRL_ENABLE, pmecc->regs.base + ATMEL_PMECC_CTRL);
	ग_लिखोl(PMECC_CTRL_DATA, pmecc->regs.base + ATMEL_PMECC_CTRL);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(aपंचांगel_pmecc_enable);

व्योम aपंचांगel_pmecc_disable(काष्ठा aपंचांगel_pmecc_user *user)
अणु
	aपंचांगel_pmecc_reset(user->pmecc);
	mutex_unlock(&user->pmecc->lock);
पूर्ण
EXPORT_SYMBOL_GPL(aपंचांगel_pmecc_disable);

पूर्णांक aपंचांगel_pmecc_रुको_rdy(काष्ठा aपंचांगel_pmecc_user *user)
अणु
	काष्ठा aपंचांगel_pmecc *pmecc = user->pmecc;
	u32 status;
	पूर्णांक ret;

	ret = पढ़ोl_relaxed_poll_समयout(pmecc->regs.base +
					 ATMEL_PMECC_SR,
					 status, !(status & PMECC_SR_BUSY), 0,
					 PMECC_MAX_TIMEOUT_MS * 1000);
	अगर (ret) अणु
		dev_err(pmecc->dev,
			"Timeout while waiting for PMECC ready.\n");
		वापस ret;
	पूर्ण

	user->isr = पढ़ोl_relaxed(pmecc->regs.base + ATMEL_PMECC_ISR);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(aपंचांगel_pmecc_रुको_rdy);

अटल काष्ठा aपंचांगel_pmecc *aपंचांगel_pmecc_create(काष्ठा platक्रमm_device *pdev,
					स्थिर काष्ठा aपंचांगel_pmecc_caps *caps,
					पूर्णांक pmecc_res_idx, पूर्णांक errloc_res_idx)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा aपंचांगel_pmecc *pmecc;
	काष्ठा resource *res;

	pmecc = devm_kzalloc(dev, माप(*pmecc), GFP_KERNEL);
	अगर (!pmecc)
		वापस ERR_PTR(-ENOMEM);

	pmecc->caps = caps;
	pmecc->dev = dev;
	mutex_init(&pmecc->lock);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, pmecc_res_idx);
	pmecc->regs.base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(pmecc->regs.base))
		वापस ERR_CAST(pmecc->regs.base);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, errloc_res_idx);
	pmecc->regs.errloc = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(pmecc->regs.errloc))
		वापस ERR_CAST(pmecc->regs.errloc);

	/* Disable all पूर्णांकerrupts beक्रमe रेजिस्टरing the PMECC handler. */
	ग_लिखोl(0xffffffff, pmecc->regs.base + ATMEL_PMECC_IDR);
	aपंचांगel_pmecc_reset(pmecc);

	वापस pmecc;
पूर्ण

अटल व्योम devm_aपंचांगel_pmecc_put(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा aपंचांगel_pmecc **pmecc = res;

	put_device((*pmecc)->dev);
पूर्ण

अटल काष्ठा aपंचांगel_pmecc *aपंचांगel_pmecc_get_by_node(काष्ठा device *userdev,
						   काष्ठा device_node *np)
अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा aपंचांगel_pmecc *pmecc, **ptr;
	पूर्णांक ret;

	pdev = of_find_device_by_node(np);
	अगर (!pdev)
		वापस ERR_PTR(-EPROBE_DEFER);
	pmecc = platक्रमm_get_drvdata(pdev);
	अगर (!pmecc) अणु
		ret = -EPROBE_DEFER;
		जाओ err_put_device;
	पूर्ण

	ptr = devres_alloc(devm_aपंचांगel_pmecc_put, माप(*ptr), GFP_KERNEL);
	अगर (!ptr) अणु
		ret = -ENOMEM;
		जाओ err_put_device;
	पूर्ण

	*ptr = pmecc;

	devres_add(userdev, ptr);

	वापस pmecc;

err_put_device:
	put_device(&pdev->dev);
	वापस ERR_PTR(ret);
पूर्ण

अटल स्थिर पूर्णांक aपंचांगel_pmecc_strengths[] = अणु 2, 4, 8, 12, 24, 32 पूर्ण;

अटल काष्ठा aपंचांगel_pmecc_caps at91sam9g45_caps = अणु
	.strengths = aपंचांगel_pmecc_strengths,
	.nstrengths = 5,
	.el_offset = 0x8c,
पूर्ण;

अटल काष्ठा aपंचांगel_pmecc_caps sama5d4_caps = अणु
	.strengths = aपंचांगel_pmecc_strengths,
	.nstrengths = 5,
	.el_offset = 0x8c,
	.correct_erased_chunks = true,
पूर्ण;

अटल काष्ठा aपंचांगel_pmecc_caps sama5d2_caps = अणु
	.strengths = aपंचांगel_pmecc_strengths,
	.nstrengths = 6,
	.el_offset = 0xac,
	.correct_erased_chunks = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id aपंचांगel_pmecc_legacy_match[] = अणु
	अणु .compatible = "atmel,sama5d4-nand", &sama5d4_caps पूर्ण,
	अणु .compatible = "atmel,sama5d2-nand", &sama5d2_caps पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

काष्ठा aपंचांगel_pmecc *devm_aपंचांगel_pmecc_get(काष्ठा device *userdev)
अणु
	काष्ठा aपंचांगel_pmecc *pmecc;
	काष्ठा device_node *np;

	अगर (!userdev)
		वापस ERR_PTR(-EINVAL);

	अगर (!userdev->of_node)
		वापस शून्य;

	np = of_parse_phandle(userdev->of_node, "ecc-engine", 0);
	अगर (np) अणु
		pmecc = aपंचांगel_pmecc_get_by_node(userdev, np);
		of_node_put(np);
	पूर्ण अन्यथा अणु
		/*
		 * Support old DT bindings: in this हाल the PMECC iomem
		 * resources are directly defined in the user pdev at position
		 * 1 and 2. Extract all relevant inक्रमmation from there.
		 */
		काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(userdev);
		स्थिर काष्ठा aपंचांगel_pmecc_caps *caps;
		स्थिर काष्ठा of_device_id *match;

		/* No PMECC engine available. */
		अगर (!of_property_पढ़ो_bool(userdev->of_node,
					   "atmel,has-pmecc"))
			वापस शून्य;

		caps = &at91sam9g45_caps;

		/* Find the caps associated to the न_अंकD dev node. */
		match = of_match_node(aपंचांगel_pmecc_legacy_match,
				      userdev->of_node);
		अगर (match && match->data)
			caps = match->data;

		pmecc = aपंचांगel_pmecc_create(pdev, caps, 1, 2);
	पूर्ण

	वापस pmecc;
पूर्ण
EXPORT_SYMBOL(devm_aपंचांगel_pmecc_get);

अटल स्थिर काष्ठा of_device_id aपंचांगel_pmecc_match[] = अणु
	अणु .compatible = "atmel,at91sam9g45-pmecc", &at91sam9g45_caps पूर्ण,
	अणु .compatible = "atmel,sama5d4-pmecc", &sama5d4_caps पूर्ण,
	अणु .compatible = "atmel,sama5d2-pmecc", &sama5d2_caps पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, aपंचांगel_pmecc_match);

अटल पूर्णांक aपंचांगel_pmecc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा aपंचांगel_pmecc_caps *caps;
	काष्ठा aपंचांगel_pmecc *pmecc;

	caps = of_device_get_match_data(&pdev->dev);
	अगर (!caps) अणु
		dev_err(dev, "Invalid caps\n");
		वापस -EINVAL;
	पूर्ण

	pmecc = aपंचांगel_pmecc_create(pdev, caps, 0, 1);
	अगर (IS_ERR(pmecc))
		वापस PTR_ERR(pmecc);

	platक्रमm_set_drvdata(pdev, pmecc);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver aपंचांगel_pmecc_driver = अणु
	.driver = अणु
		.name = "atmel-pmecc",
		.of_match_table = of_match_ptr(aपंचांगel_pmecc_match),
	पूर्ण,
	.probe = aपंचांगel_pmecc_probe,
पूर्ण;
module_platक्रमm_driver(aपंचांगel_pmecc_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Boris Brezillon <boris.brezillon@free-electrons.com>");
MODULE_DESCRIPTION("PMECC engine driver");
MODULE_ALIAS("platform:atmel_pmecc");
