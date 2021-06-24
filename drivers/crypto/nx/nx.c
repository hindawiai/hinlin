<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Routines supporting the Power 7+ Nest Accelerators driver
 *
 * Copyright (C) 2011-2012 International Business Machines Inc.
 *
 * Author: Kent Yoder <yoder1@us.ibm.com>
 */

#समावेश <crypto/पूर्णांकernal/aead.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/aes.h>
#समावेश <crypto/sha2.h>
#समावेश <crypto/algapi.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/device.h>
#समावेश <linux/of.h>
#समावेश <यंत्र/hvcall.h>
#समावेश <यंत्र/vपन.स>

#समावेश "nx_csbcpb.h"
#समावेश "nx.h"


/**
 * nx_hcall_sync - make an H_COP_OP hcall क्रम the passed in op काष्ठाure
 *
 * @nx_ctx: the crypto context handle
 * @op: PFO operation काष्ठा to pass in
 * @may_sleep: flag indicating the request can sleep
 *
 * Make the hcall, retrying जबतक the hardware is busy. If we cannot yield
 * the thपढ़ो, limit the number of retries to 10 here.
 */
पूर्णांक nx_hcall_sync(काष्ठा nx_crypto_ctx *nx_ctx,
		  काष्ठा vio_pfo_op    *op,
		  u32                   may_sleep)
अणु
	पूर्णांक rc, retries = 10;
	काष्ठा vio_dev *viodev = nx_driver.viodev;

	atomic_inc(&(nx_ctx->stats->sync_ops));

	करो अणु
		rc = vio_h_cop_sync(viodev, op);
	पूर्ण जबतक (rc == -EBUSY && !may_sleep && retries--);

	अगर (rc) अणु
		dev_dbg(&viodev->dev, "vio_h_cop_sync failed: rc: %d "
			"hcall rc: %ld\n", rc, op->hcall_err);
		atomic_inc(&(nx_ctx->stats->errors));
		atomic_set(&(nx_ctx->stats->last_error), op->hcall_err);
		atomic_set(&(nx_ctx->stats->last_error_pid), current->pid);
	पूर्ण

	वापस rc;
पूर्ण

/**
 * nx_build_sg_list - build an NX scatter list describing a single  buffer
 *
 * @sg_head: poपूर्णांकer to the first scatter list element to build
 * @start_addr: poपूर्णांकer to the linear buffer
 * @len: length of the data at @start_addr
 * @sgmax: the largest number of scatter list elements we're allowed to create
 *
 * This function will start writing nx_sg elements at @sg_head and keep
 * writing them until all of the data from @start_addr is described or
 * until sgmax elements have been written. Scatter list elements will be
 * created such that none of the elements describes a buffer that crosses a 4K
 * boundary.
 */
काष्ठा nx_sg *nx_build_sg_list(काष्ठा nx_sg *sg_head,
			       u8           *start_addr,
			       अचिन्हित पूर्णांक *len,
			       u32           sgmax)
अणु
	अचिन्हित पूर्णांक sg_len = 0;
	काष्ठा nx_sg *sg;
	u64 sg_addr = (u64)start_addr;
	u64 end_addr;

	/* determine the start and end क्रम this address range - slightly
	 * dअगरferent अगर this is in VMALLOC_REGION */
	अगर (is_vदो_स्मृति_addr(start_addr))
		sg_addr = page_to_phys(vदो_स्मृति_to_page(start_addr))
			  + offset_in_page(sg_addr);
	अन्यथा
		sg_addr = __pa(sg_addr);

	end_addr = sg_addr + *len;

	/* each iteration will ग_लिखो one काष्ठा nx_sg element and add the
	 * length of data described by that element to sg_len. Once @len bytes
	 * have been described (or @sgmax elements have been written), the
	 * loop ends. min_t is used to ensure @end_addr falls on the same page
	 * as sg_addr, अगर not, we need to create another nx_sg element क्रम the
	 * data on the next page.
	 *
	 * Also when using vदो_स्मृति'ed data, every समय that a प्रणाली page
	 * boundary is crossed the physical address needs to be re-calculated.
	 */
	क्रम (sg = sg_head; sg_len < *len; sg++) अणु
		u64 next_page;

		sg->addr = sg_addr;
		sg_addr = min_t(u64, NX_PAGE_NUM(sg_addr + NX_PAGE_SIZE),
				end_addr);

		next_page = (sg->addr & PAGE_MASK) + PAGE_SIZE;
		sg->len = min_t(u64, sg_addr, next_page) - sg->addr;
		sg_len += sg->len;

		अगर (sg_addr >= next_page &&
				is_vदो_स्मृति_addr(start_addr + sg_len)) अणु
			sg_addr = page_to_phys(vदो_स्मृति_to_page(
						start_addr + sg_len));
			end_addr = sg_addr + *len - sg_len;
		पूर्ण

		अगर ((sg - sg_head) == sgmax) अणु
			pr_err("nx: scatter/gather list overflow, pid: %d\n",
			       current->pid);
			sg++;
			अवरोध;
		पूर्ण
	पूर्ण
	*len = sg_len;

	/* वापस the moved sg_head poपूर्णांकer */
	वापस sg;
पूर्ण

/**
 * nx_walk_and_build - walk a linux scatterlist and build an nx scatterlist
 *
 * @nx_dst: poपूर्णांकer to the first nx_sg element to ग_लिखो
 * @sglen: max number of nx_sg entries we're allowed to ग_लिखो
 * @sg_src: poपूर्णांकer to the source linux scatterlist to walk
 * @start: number of bytes to fast-क्रमward past at the beginning of @sg_src
 * @src_len: number of bytes to walk in @sg_src
 */
काष्ठा nx_sg *nx_walk_and_build(काष्ठा nx_sg       *nx_dst,
				अचिन्हित पूर्णांक        sglen,
				काष्ठा scatterlist *sg_src,
				अचिन्हित पूर्णांक        start,
				अचिन्हित पूर्णांक       *src_len)
अणु
	काष्ठा scatter_walk walk;
	काष्ठा nx_sg *nx_sg = nx_dst;
	अचिन्हित पूर्णांक n, offset = 0, len = *src_len;
	अक्षर *dst;

	/* we need to fast क्रमward through @start bytes first */
	क्रम (;;) अणु
		scatterwalk_start(&walk, sg_src);

		अगर (start < offset + sg_src->length)
			अवरोध;

		offset += sg_src->length;
		sg_src = sg_next(sg_src);
	पूर्ण

	/* start - offset is the number of bytes to advance in the scatterlist
	 * element we're currently looking at */
	scatterwalk_advance(&walk, start - offset);

	जबतक (len && (nx_sg - nx_dst) < sglen) अणु
		n = scatterwalk_clamp(&walk, len);
		अगर (!n) अणु
			/* In हालs where we have scatterlist chain sg_next
			 * handles with it properly */
			scatterwalk_start(&walk, sg_next(walk.sg));
			n = scatterwalk_clamp(&walk, len);
		पूर्ण
		dst = scatterwalk_map(&walk);

		nx_sg = nx_build_sg_list(nx_sg, dst, &n, sglen - (nx_sg - nx_dst));
		len -= n;

		scatterwalk_unmap(dst);
		scatterwalk_advance(&walk, n);
		scatterwalk_करोne(&walk, SCATTERWALK_FROM_SG, len);
	पूर्ण
	/* update to_process */
	*src_len -= len;

	/* वापस the moved destination poपूर्णांकer */
	वापस nx_sg;
पूर्ण

/**
 * trim_sg_list - ensures the bound in sg list.
 * @sg: sg list head
 * @end: sg lisg end
 * @delta:  is the amount we need to crop in order to bound the list.
 * @nbytes: length of data in the scatterlists or data length - whichever
 *          is greater.
 */
अटल दीर्घ पूर्णांक trim_sg_list(काष्ठा nx_sg *sg,
			     काष्ठा nx_sg *end,
			     अचिन्हित पूर्णांक delta,
			     अचिन्हित पूर्णांक *nbytes)
अणु
	दीर्घ पूर्णांक oplen;
	दीर्घ पूर्णांक data_back;
	अचिन्हित पूर्णांक is_delta = delta;

	जबतक (delta && end > sg) अणु
		काष्ठा nx_sg *last = end - 1;

		अगर (last->len > delta) अणु
			last->len -= delta;
			delta = 0;
		पूर्ण अन्यथा अणु
			end--;
			delta -= last->len;
		पूर्ण
	पूर्ण

	/* There are हालs where we need to crop list in order to make it
	 * a block size multiple, but we also need to align data. In order to
	 * that we need to calculate how much we need to put back to be
	 * processed
	 */
	oplen = (sg - end) * माप(काष्ठा nx_sg);
	अगर (is_delta) अणु
		data_back = (असल(oplen) / AES_BLOCK_SIZE) *  sg->len;
		data_back = *nbytes - (data_back & ~(AES_BLOCK_SIZE - 1));
		*nbytes -= data_back;
	पूर्ण

	वापस oplen;
पूर्ण

/**
 * nx_build_sg_lists - walk the input scatterlists and build arrays of NX
 *                     scatterlists based on them.
 *
 * @nx_ctx: NX crypto context क्रम the lists we're building
 * @iv: iv data, अगर the algorithm requires it
 * @dst: destination scatterlist
 * @src: source scatterlist
 * @nbytes: length of data described in the scatterlists
 * @offset: number of bytes to fast-क्रमward past at the beginning of
 *          scatterlists.
 * @oiv: destination क्रम the iv data, अगर the algorithm requires it
 *
 * This is common code shared by all the AES algorithms. It uses the crypto
 * scatterlist walk routines to traverse input and output scatterlists, building
 * corresponding NX scatterlists
 */
पूर्णांक nx_build_sg_lists(काष्ठा nx_crypto_ctx  *nx_ctx,
		      स्थिर u8              *iv,
		      काष्ठा scatterlist    *dst,
		      काष्ठा scatterlist    *src,
		      अचिन्हित पूर्णांक          *nbytes,
		      अचिन्हित पूर्णांक           offset,
		      u8                    *oiv)
अणु
	अचिन्हित पूर्णांक delta = 0;
	अचिन्हित पूर्णांक total = *nbytes;
	काष्ठा nx_sg *nx_insg = nx_ctx->in_sg;
	काष्ठा nx_sg *nx_outsg = nx_ctx->out_sg;
	अचिन्हित पूर्णांक max_sg_len;

	max_sg_len = min_t(u64, nx_ctx->ap->sglen,
			nx_driver.of.max_sg_len/माप(काष्ठा nx_sg));
	max_sg_len = min_t(u64, max_sg_len,
			nx_ctx->ap->databytelen/NX_PAGE_SIZE);

	अगर (oiv)
		स_नकल(oiv, iv, AES_BLOCK_SIZE);

	*nbytes = min_t(u64, *nbytes, nx_ctx->ap->databytelen);

	nx_outsg = nx_walk_and_build(nx_outsg, max_sg_len, dst,
					offset, nbytes);
	nx_insg = nx_walk_and_build(nx_insg, max_sg_len, src,
					offset, nbytes);

	अगर (*nbytes < total)
		delta = *nbytes - (*nbytes & ~(AES_BLOCK_SIZE - 1));

	/* these lengths should be negative, which will indicate to phyp that
	 * the input and output parameters are scatterlists, not linear
	 * buffers */
	nx_ctx->op.inlen = trim_sg_list(nx_ctx->in_sg, nx_insg, delta, nbytes);
	nx_ctx->op.outlen = trim_sg_list(nx_ctx->out_sg, nx_outsg, delta, nbytes);

	वापस 0;
पूर्ण

/**
 * nx_ctx_init - initialize an nx_ctx's vio_pfo_op काष्ठा
 *
 * @nx_ctx: the nx context to initialize
 * @function: the function code क्रम the op
 */
व्योम nx_ctx_init(काष्ठा nx_crypto_ctx *nx_ctx, अचिन्हित पूर्णांक function)
अणु
	spin_lock_init(&nx_ctx->lock);
	स_रखो(nx_ctx->kmem, 0, nx_ctx->kmem_len);
	nx_ctx->csbcpb->csb.valid |= NX_CSB_VALID_BIT;

	nx_ctx->op.flags = function;
	nx_ctx->op.csbcpb = __pa(nx_ctx->csbcpb);
	nx_ctx->op.in = __pa(nx_ctx->in_sg);
	nx_ctx->op.out = __pa(nx_ctx->out_sg);

	अगर (nx_ctx->csbcpb_aead) अणु
		nx_ctx->csbcpb_aead->csb.valid |= NX_CSB_VALID_BIT;

		nx_ctx->op_aead.flags = function;
		nx_ctx->op_aead.csbcpb = __pa(nx_ctx->csbcpb_aead);
		nx_ctx->op_aead.in = __pa(nx_ctx->in_sg);
		nx_ctx->op_aead.out = __pa(nx_ctx->out_sg);
	पूर्ण
पूर्ण

अटल व्योम nx_of_update_status(काष्ठा device   *dev,
			       काष्ठा property *p,
			       काष्ठा nx_of    *props)
अणु
	अगर (!म_भेदन(p->value, "okay", p->length)) अणु
		props->status = NX_WAITING;
		props->flags |= NX_OF_FLAG_STATUS_SET;
	पूर्ण अन्यथा अणु
		dev_info(dev, "%s: status '%s' is not 'okay'\n", __func__,
			 (अक्षर *)p->value);
	पूर्ण
पूर्ण

अटल व्योम nx_of_update_sglen(काष्ठा device   *dev,
			       काष्ठा property *p,
			       काष्ठा nx_of    *props)
अणु
	अगर (p->length != माप(props->max_sg_len)) अणु
		dev_err(dev, "%s: unexpected format for "
			"ibm,max-sg-len property\n", __func__);
		dev_dbg(dev, "%s: ibm,max-sg-len is %d bytes "
			"long, expected %zd bytes\n", __func__,
			p->length, माप(props->max_sg_len));
		वापस;
	पूर्ण

	props->max_sg_len = *(u32 *)p->value;
	props->flags |= NX_OF_FLAG_MAXSGLEN_SET;
पूर्ण

अटल व्योम nx_of_update_msc(काष्ठा device   *dev,
			     काष्ठा property *p,
			     काष्ठा nx_of    *props)
अणु
	काष्ठा msc_triplet *trip;
	काष्ठा max_sync_cop *msc;
	अचिन्हित पूर्णांक bytes_so_far, i, lenp;

	msc = (काष्ठा max_sync_cop *)p->value;
	lenp = p->length;

	/* You can't tell अगर the data पढ़ो in क्रम this property is sane by its
	 * size alone. This is because there are sizes embedded in the data
	 * काष्ठाure. The best we can करो is check lengths as we parse and bail
	 * as soon as a length error is detected. */
	bytes_so_far = 0;

	जबतक ((bytes_so_far + माप(काष्ठा max_sync_cop)) <= lenp) अणु
		bytes_so_far += माप(काष्ठा max_sync_cop);

		trip = msc->trip;

		क्रम (i = 0;
		     ((bytes_so_far + माप(काष्ठा msc_triplet)) <= lenp) &&
		     i < msc->triplets;
		     i++) अणु
			अगर (msc->fc >= NX_MAX_FC || msc->mode >= NX_MAX_MODE) अणु
				dev_err(dev, "unknown function code/mode "
					"combo: %d/%d (ignored)\n", msc->fc,
					msc->mode);
				जाओ next_loop;
			पूर्ण

			अगर (!trip->sglen || trip->databytelen < NX_PAGE_SIZE) अणु
				dev_warn(dev, "bogus sglen/databytelen: "
					 "%u/%u (ignored)\n", trip->sglen,
					 trip->databytelen);
				जाओ next_loop;
			पूर्ण

			चयन (trip->keybitlen) अणु
			हाल 128:
			हाल 160:
				props->ap[msc->fc][msc->mode][0].databytelen =
					trip->databytelen;
				props->ap[msc->fc][msc->mode][0].sglen =
					trip->sglen;
				अवरोध;
			हाल 192:
				props->ap[msc->fc][msc->mode][1].databytelen =
					trip->databytelen;
				props->ap[msc->fc][msc->mode][1].sglen =
					trip->sglen;
				अवरोध;
			हाल 256:
				अगर (msc->fc == NX_FC_AES) अणु
					props->ap[msc->fc][msc->mode][2].
						databytelen = trip->databytelen;
					props->ap[msc->fc][msc->mode][2].sglen =
						trip->sglen;
				पूर्ण अन्यथा अगर (msc->fc == NX_FC_AES_HMAC ||
					   msc->fc == NX_FC_SHA) अणु
					props->ap[msc->fc][msc->mode][1].
						databytelen = trip->databytelen;
					props->ap[msc->fc][msc->mode][1].sglen =
						trip->sglen;
				पूर्ण अन्यथा अणु
					dev_warn(dev, "unknown function "
						"code/key bit len combo"
						": (%u/256)\n", msc->fc);
				पूर्ण
				अवरोध;
			हाल 512:
				props->ap[msc->fc][msc->mode][2].databytelen =
					trip->databytelen;
				props->ap[msc->fc][msc->mode][2].sglen =
					trip->sglen;
				अवरोध;
			शेष:
				dev_warn(dev, "unknown function code/key bit "
					 "len combo: (%u/%u)\n", msc->fc,
					 trip->keybitlen);
				अवरोध;
			पूर्ण
next_loop:
			bytes_so_far += माप(काष्ठा msc_triplet);
			trip++;
		पूर्ण

		msc = (काष्ठा max_sync_cop *)trip;
	पूर्ण

	props->flags |= NX_OF_FLAG_MAXSYNCCOP_SET;
पूर्ण

/**
 * nx_of_init - पढ़ो खोलोFirmware values from the device tree
 *
 * @dev: device handle
 * @props: poपूर्णांकer to काष्ठा to hold the properties values
 *
 * Called once at driver probe समय, this function will पढ़ो out the
 * खोलोFirmware properties we use at runसमय. If all the OF properties are
 * acceptable, when we निकास this function props->flags will indicate that
 * we're पढ़ोy to रेजिस्टर our crypto algorithms.
 */
अटल व्योम nx_of_init(काष्ठा device *dev, काष्ठा nx_of *props)
अणु
	काष्ठा device_node *base_node = dev->of_node;
	काष्ठा property *p;

	p = of_find_property(base_node, "status", शून्य);
	अगर (!p)
		dev_info(dev, "%s: property 'status' not found\n", __func__);
	अन्यथा
		nx_of_update_status(dev, p, props);

	p = of_find_property(base_node, "ibm,max-sg-len", शून्य);
	अगर (!p)
		dev_info(dev, "%s: property 'ibm,max-sg-len' not found\n",
			 __func__);
	अन्यथा
		nx_of_update_sglen(dev, p, props);

	p = of_find_property(base_node, "ibm,max-sync-cop", शून्य);
	अगर (!p)
		dev_info(dev, "%s: property 'ibm,max-sync-cop' not found\n",
			 __func__);
	अन्यथा
		nx_of_update_msc(dev, p, props);
पूर्ण

अटल bool nx_check_prop(काष्ठा device *dev, u32 fc, u32 mode, पूर्णांक slot)
अणु
	काष्ठा alg_props *props = &nx_driver.of.ap[fc][mode][slot];

	अगर (!props->sglen || props->databytelen < NX_PAGE_SIZE) अणु
		अगर (dev)
			dev_warn(dev, "bogus sglen/databytelen for %u/%u/%u: "
				 "%u/%u (ignored)\n", fc, mode, slot,
				 props->sglen, props->databytelen);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool nx_check_props(काष्ठा device *dev, u32 fc, u32 mode)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 3; i++)
		अगर (!nx_check_prop(dev, fc, mode, i))
			वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक nx_रेजिस्टर_skcipher(काष्ठा skcipher_alg *alg, u32 fc, u32 mode)
अणु
	वापस nx_check_props(&nx_driver.viodev->dev, fc, mode) ?
	       crypto_रेजिस्टर_skcipher(alg) : 0;
पूर्ण

अटल पूर्णांक nx_रेजिस्टर_aead(काष्ठा aead_alg *alg, u32 fc, u32 mode)
अणु
	वापस nx_check_props(&nx_driver.viodev->dev, fc, mode) ?
	       crypto_रेजिस्टर_aead(alg) : 0;
पूर्ण

अटल पूर्णांक nx_रेजिस्टर_shash(काष्ठा shash_alg *alg, u32 fc, u32 mode, पूर्णांक slot)
अणु
	वापस (slot >= 0 ? nx_check_prop(&nx_driver.viodev->dev,
					  fc, mode, slot) :
			    nx_check_props(&nx_driver.viodev->dev, fc, mode)) ?
	       crypto_रेजिस्टर_shash(alg) : 0;
पूर्ण

अटल व्योम nx_unरेजिस्टर_skcipher(काष्ठा skcipher_alg *alg, u32 fc, u32 mode)
अणु
	अगर (nx_check_props(शून्य, fc, mode))
		crypto_unरेजिस्टर_skcipher(alg);
पूर्ण

अटल व्योम nx_unरेजिस्टर_aead(काष्ठा aead_alg *alg, u32 fc, u32 mode)
अणु
	अगर (nx_check_props(शून्य, fc, mode))
		crypto_unरेजिस्टर_aead(alg);
पूर्ण

अटल व्योम nx_unरेजिस्टर_shash(काष्ठा shash_alg *alg, u32 fc, u32 mode,
				पूर्णांक slot)
अणु
	अगर (slot >= 0 ? nx_check_prop(शून्य, fc, mode, slot) :
			nx_check_props(शून्य, fc, mode))
		crypto_unरेजिस्टर_shash(alg);
पूर्ण

/**
 * nx_रेजिस्टर_algs - रेजिस्टर algorithms with the crypto API
 *
 * Called from nx_probe()
 *
 * If all OF properties are in an acceptable state, the driver flags will
 * indicate that we're ready and we'll create our debugfs files and रेजिस्टर
 * out crypto algorithms.
 */
अटल पूर्णांक nx_रेजिस्टर_algs(व्योम)
अणु
	पूर्णांक rc = -1;

	अगर (nx_driver.of.flags != NX_OF_FLAG_MASK_READY)
		जाओ out;

	स_रखो(&nx_driver.stats, 0, माप(काष्ठा nx_stats));

	NX_DEBUGFS_INIT(&nx_driver);

	nx_driver.of.status = NX_OKAY;

	rc = nx_रेजिस्टर_skcipher(&nx_ecb_aes_alg, NX_FC_AES, NX_MODE_AES_ECB);
	अगर (rc)
		जाओ out;

	rc = nx_रेजिस्टर_skcipher(&nx_cbc_aes_alg, NX_FC_AES, NX_MODE_AES_CBC);
	अगर (rc)
		जाओ out_unreg_ecb;

	rc = nx_रेजिस्टर_skcipher(&nx_ctr3686_aes_alg, NX_FC_AES,
				  NX_MODE_AES_CTR);
	अगर (rc)
		जाओ out_unreg_cbc;

	rc = nx_रेजिस्टर_aead(&nx_gcm_aes_alg, NX_FC_AES, NX_MODE_AES_GCM);
	अगर (rc)
		जाओ out_unreg_ctr3686;

	rc = nx_रेजिस्टर_aead(&nx_gcm4106_aes_alg, NX_FC_AES, NX_MODE_AES_GCM);
	अगर (rc)
		जाओ out_unreg_gcm;

	rc = nx_रेजिस्टर_aead(&nx_ccm_aes_alg, NX_FC_AES, NX_MODE_AES_CCM);
	अगर (rc)
		जाओ out_unreg_gcm4106;

	rc = nx_रेजिस्टर_aead(&nx_ccm4309_aes_alg, NX_FC_AES, NX_MODE_AES_CCM);
	अगर (rc)
		जाओ out_unreg_ccm;

	rc = nx_रेजिस्टर_shash(&nx_shash_sha256_alg, NX_FC_SHA, NX_MODE_SHA,
			       NX_PROPS_SHA256);
	अगर (rc)
		जाओ out_unreg_ccm4309;

	rc = nx_रेजिस्टर_shash(&nx_shash_sha512_alg, NX_FC_SHA, NX_MODE_SHA,
			       NX_PROPS_SHA512);
	अगर (rc)
		जाओ out_unreg_s256;

	rc = nx_रेजिस्टर_shash(&nx_shash_aes_xcbc_alg,
			       NX_FC_AES, NX_MODE_AES_XCBC_MAC, -1);
	अगर (rc)
		जाओ out_unreg_s512;

	जाओ out;

out_unreg_s512:
	nx_unरेजिस्टर_shash(&nx_shash_sha512_alg, NX_FC_SHA, NX_MODE_SHA,
			    NX_PROPS_SHA512);
out_unreg_s256:
	nx_unरेजिस्टर_shash(&nx_shash_sha256_alg, NX_FC_SHA, NX_MODE_SHA,
			    NX_PROPS_SHA256);
out_unreg_ccm4309:
	nx_unरेजिस्टर_aead(&nx_ccm4309_aes_alg, NX_FC_AES, NX_MODE_AES_CCM);
out_unreg_ccm:
	nx_unरेजिस्टर_aead(&nx_ccm_aes_alg, NX_FC_AES, NX_MODE_AES_CCM);
out_unreg_gcm4106:
	nx_unरेजिस्टर_aead(&nx_gcm4106_aes_alg, NX_FC_AES, NX_MODE_AES_GCM);
out_unreg_gcm:
	nx_unरेजिस्टर_aead(&nx_gcm_aes_alg, NX_FC_AES, NX_MODE_AES_GCM);
out_unreg_ctr3686:
	nx_unरेजिस्टर_skcipher(&nx_ctr3686_aes_alg, NX_FC_AES, NX_MODE_AES_CTR);
out_unreg_cbc:
	nx_unरेजिस्टर_skcipher(&nx_cbc_aes_alg, NX_FC_AES, NX_MODE_AES_CBC);
out_unreg_ecb:
	nx_unरेजिस्टर_skcipher(&nx_ecb_aes_alg, NX_FC_AES, NX_MODE_AES_ECB);
out:
	वापस rc;
पूर्ण

/**
 * nx_crypto_ctx_init - create and initialize a crypto api context
 *
 * @nx_ctx: the crypto api context
 * @fc: function code क्रम the context
 * @mode: the function code specअगरic mode क्रम this context
 */
अटल पूर्णांक nx_crypto_ctx_init(काष्ठा nx_crypto_ctx *nx_ctx, u32 fc, u32 mode)
अणु
	अगर (nx_driver.of.status != NX_OKAY) अणु
		pr_err("Attempt to initialize NX crypto context while device "
		       "is not available!\n");
		वापस -ENODEV;
	पूर्ण

	/* we need an extra page क्रम csbcpb_aead क्रम these modes */
	अगर (mode == NX_MODE_AES_GCM || mode == NX_MODE_AES_CCM)
		nx_ctx->kmem_len = (5 * NX_PAGE_SIZE) +
				   माप(काष्ठा nx_csbcpb);
	अन्यथा
		nx_ctx->kmem_len = (4 * NX_PAGE_SIZE) +
				   माप(काष्ठा nx_csbcpb);

	nx_ctx->kmem = kदो_स्मृति(nx_ctx->kmem_len, GFP_KERNEL);
	अगर (!nx_ctx->kmem)
		वापस -ENOMEM;

	/* the csbcpb and scatterlists must be 4K aligned pages */
	nx_ctx->csbcpb = (काष्ठा nx_csbcpb *)(round_up((u64)nx_ctx->kmem,
						       (u64)NX_PAGE_SIZE));
	nx_ctx->in_sg = (काष्ठा nx_sg *)((u8 *)nx_ctx->csbcpb + NX_PAGE_SIZE);
	nx_ctx->out_sg = (काष्ठा nx_sg *)((u8 *)nx_ctx->in_sg + NX_PAGE_SIZE);

	अगर (mode == NX_MODE_AES_GCM || mode == NX_MODE_AES_CCM)
		nx_ctx->csbcpb_aead =
			(काष्ठा nx_csbcpb *)((u8 *)nx_ctx->out_sg +
					     NX_PAGE_SIZE);

	/* give each context a poपूर्णांकer to global stats and their OF
	 * properties */
	nx_ctx->stats = &nx_driver.stats;
	स_नकल(nx_ctx->props, nx_driver.of.ap[fc][mode],
	       माप(काष्ठा alg_props) * 3);

	वापस 0;
पूर्ण

/* entry poपूर्णांकs from the crypto tfm initializers */
पूर्णांक nx_crypto_ctx_aes_ccm_init(काष्ठा crypto_aead *tfm)
अणु
	crypto_aead_set_reqsize(tfm, माप(काष्ठा nx_ccm_rctx));
	वापस nx_crypto_ctx_init(crypto_aead_ctx(tfm), NX_FC_AES,
				  NX_MODE_AES_CCM);
पूर्ण

पूर्णांक nx_crypto_ctx_aes_gcm_init(काष्ठा crypto_aead *tfm)
अणु
	crypto_aead_set_reqsize(tfm, माप(काष्ठा nx_gcm_rctx));
	वापस nx_crypto_ctx_init(crypto_aead_ctx(tfm), NX_FC_AES,
				  NX_MODE_AES_GCM);
पूर्ण

पूर्णांक nx_crypto_ctx_aes_ctr_init(काष्ठा crypto_skcipher *tfm)
अणु
	वापस nx_crypto_ctx_init(crypto_skcipher_ctx(tfm), NX_FC_AES,
				  NX_MODE_AES_CTR);
पूर्ण

पूर्णांक nx_crypto_ctx_aes_cbc_init(काष्ठा crypto_skcipher *tfm)
अणु
	वापस nx_crypto_ctx_init(crypto_skcipher_ctx(tfm), NX_FC_AES,
				  NX_MODE_AES_CBC);
पूर्ण

पूर्णांक nx_crypto_ctx_aes_ecb_init(काष्ठा crypto_skcipher *tfm)
अणु
	वापस nx_crypto_ctx_init(crypto_skcipher_ctx(tfm), NX_FC_AES,
				  NX_MODE_AES_ECB);
पूर्ण

पूर्णांक nx_crypto_ctx_sha_init(काष्ठा crypto_tfm *tfm)
अणु
	वापस nx_crypto_ctx_init(crypto_tfm_ctx(tfm), NX_FC_SHA, NX_MODE_SHA);
पूर्ण

पूर्णांक nx_crypto_ctx_aes_xcbc_init(काष्ठा crypto_tfm *tfm)
अणु
	वापस nx_crypto_ctx_init(crypto_tfm_ctx(tfm), NX_FC_AES,
				  NX_MODE_AES_XCBC_MAC);
पूर्ण

/**
 * nx_crypto_ctx_निकास - destroy a crypto api context
 *
 * @tfm: the crypto transक्रमm poपूर्णांकer क्रम the context
 *
 * As crypto API contexts are destroyed, this निकास hook is called to मुक्त the
 * memory associated with it.
 */
व्योम nx_crypto_ctx_निकास(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा nx_crypto_ctx *nx_ctx = crypto_tfm_ctx(tfm);

	kमुक्त_sensitive(nx_ctx->kmem);
	nx_ctx->csbcpb = शून्य;
	nx_ctx->csbcpb_aead = शून्य;
	nx_ctx->in_sg = शून्य;
	nx_ctx->out_sg = शून्य;
पूर्ण

व्योम nx_crypto_ctx_skcipher_निकास(काष्ठा crypto_skcipher *tfm)
अणु
	nx_crypto_ctx_निकास(crypto_skcipher_ctx(tfm));
पूर्ण

व्योम nx_crypto_ctx_aead_निकास(काष्ठा crypto_aead *tfm)
अणु
	काष्ठा nx_crypto_ctx *nx_ctx = crypto_aead_ctx(tfm);

	kमुक्त_sensitive(nx_ctx->kmem);
पूर्ण

अटल पूर्णांक nx_probe(काष्ठा vio_dev *viodev, स्थिर काष्ठा vio_device_id *id)
अणु
	dev_dbg(&viodev->dev, "driver probed: %s resource id: 0x%x\n",
		viodev->name, viodev->resource_id);

	अगर (nx_driver.viodev) अणु
		dev_err(&viodev->dev, "%s: Attempt to register more than one "
			"instance of the hardware\n", __func__);
		वापस -EINVAL;
	पूर्ण

	nx_driver.viodev = viodev;

	nx_of_init(&viodev->dev, &nx_driver.of);

	वापस nx_रेजिस्टर_algs();
पूर्ण

अटल व्योम nx_हटाओ(काष्ठा vio_dev *viodev)
अणु
	dev_dbg(&viodev->dev, "entering nx_remove for UA 0x%x\n",
		viodev->unit_address);

	अगर (nx_driver.of.status == NX_OKAY) अणु
		NX_DEBUGFS_FINI(&nx_driver);

		nx_unरेजिस्टर_shash(&nx_shash_aes_xcbc_alg,
				    NX_FC_AES, NX_MODE_AES_XCBC_MAC, -1);
		nx_unरेजिस्टर_shash(&nx_shash_sha512_alg,
				    NX_FC_SHA, NX_MODE_SHA, NX_PROPS_SHA256);
		nx_unरेजिस्टर_shash(&nx_shash_sha256_alg,
				    NX_FC_SHA, NX_MODE_SHA, NX_PROPS_SHA512);
		nx_unरेजिस्टर_aead(&nx_ccm4309_aes_alg,
				   NX_FC_AES, NX_MODE_AES_CCM);
		nx_unरेजिस्टर_aead(&nx_ccm_aes_alg, NX_FC_AES, NX_MODE_AES_CCM);
		nx_unरेजिस्टर_aead(&nx_gcm4106_aes_alg,
				   NX_FC_AES, NX_MODE_AES_GCM);
		nx_unरेजिस्टर_aead(&nx_gcm_aes_alg,
				   NX_FC_AES, NX_MODE_AES_GCM);
		nx_unरेजिस्टर_skcipher(&nx_ctr3686_aes_alg,
				       NX_FC_AES, NX_MODE_AES_CTR);
		nx_unरेजिस्टर_skcipher(&nx_cbc_aes_alg, NX_FC_AES,
				       NX_MODE_AES_CBC);
		nx_unरेजिस्टर_skcipher(&nx_ecb_aes_alg, NX_FC_AES,
				       NX_MODE_AES_ECB);
	पूर्ण
पूर्ण


/* module wide initialization/cleanup */
अटल पूर्णांक __init nx_init(व्योम)
अणु
	वापस vio_रेजिस्टर_driver(&nx_driver.viodriver);
पूर्ण

अटल व्योम __निकास nx_fini(व्योम)
अणु
	vio_unरेजिस्टर_driver(&nx_driver.viodriver);
पूर्ण

अटल स्थिर काष्ठा vio_device_id nx_crypto_driver_ids[] = अणु
	अणु "ibm,sym-encryption-v1", "ibm,sym-encryption" पूर्ण,
	अणु "", "" पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(vio, nx_crypto_driver_ids);

/* driver state काष्ठाure */
काष्ठा nx_crypto_driver nx_driver = अणु
	.viodriver = अणु
		.id_table = nx_crypto_driver_ids,
		.probe = nx_probe,
		.हटाओ = nx_हटाओ,
		.name  = NX_NAME,
	पूर्ण,
पूर्ण;

module_init(nx_init);
module_निकास(nx_fini);

MODULE_AUTHOR("Kent Yoder <yoder1@us.ibm.com>");
MODULE_DESCRIPTION(NX_STRING);
MODULE_LICENSE("GPL");
MODULE_VERSION(NX_VERSION);
