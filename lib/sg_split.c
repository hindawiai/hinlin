<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 Robert Jarzmik <robert.jarzmik@मुक्त.fr>
 *
 * Scatterlist splitting helpers.
 */

#समावेश <linux/scatterlist.h>
#समावेश <linux/slab.h>

काष्ठा sg_splitter अणु
	काष्ठा scatterlist *in_sg0;
	पूर्णांक nents;
	off_t skip_sg0;
	अचिन्हित पूर्णांक length_last_sg;

	काष्ठा scatterlist *out_sg;
पूर्ण;

अटल पूर्णांक sg_calculate_split(काष्ठा scatterlist *in, पूर्णांक nents, पूर्णांक nb_splits,
			      off_t skip, स्थिर माप_प्रकार *sizes,
			      काष्ठा sg_splitter *splitters, bool mapped)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक sglen;
	माप_प्रकार size = sizes[0], len;
	काष्ठा sg_splitter *curr = splitters;
	काष्ठा scatterlist *sg;

	क्रम (i = 0; i < nb_splits; i++) अणु
		splitters[i].in_sg0 = शून्य;
		splitters[i].nents = 0;
	पूर्ण

	क्रम_each_sg(in, sg, nents, i) अणु
		sglen = mapped ? sg_dma_len(sg) : sg->length;
		अगर (skip > sglen) अणु
			skip -= sglen;
			जारी;
		पूर्ण

		len = min_t(माप_प्रकार, size, sglen - skip);
		अगर (!curr->in_sg0) अणु
			curr->in_sg0 = sg;
			curr->skip_sg0 = skip;
		पूर्ण
		size -= len;
		curr->nents++;
		curr->length_last_sg = len;

		जबतक (!size && (skip + len < sglen) && (--nb_splits > 0)) अणु
			curr++;
			size = *(++sizes);
			skip += len;
			len = min_t(माप_प्रकार, size, sglen - skip);

			curr->in_sg0 = sg;
			curr->skip_sg0 = skip;
			curr->nents = 1;
			curr->length_last_sg = len;
			size -= len;
		पूर्ण
		skip = 0;

		अगर (!size && --nb_splits > 0) अणु
			curr++;
			size = *(++sizes);
		पूर्ण

		अगर (!nb_splits)
			अवरोध;
	पूर्ण

	वापस (size || !splitters[0].in_sg0) ? -EINVAL : 0;
पूर्ण

अटल व्योम sg_split_phys(काष्ठा sg_splitter *splitters, स्थिर पूर्णांक nb_splits)
अणु
	पूर्णांक i, j;
	काष्ठा scatterlist *in_sg, *out_sg;
	काष्ठा sg_splitter *split;

	क्रम (i = 0, split = splitters; i < nb_splits; i++, split++) अणु
		in_sg = split->in_sg0;
		out_sg = split->out_sg;
		क्रम (j = 0; j < split->nents; j++, out_sg++) अणु
			*out_sg = *in_sg;
			अगर (!j) अणु
				out_sg->offset += split->skip_sg0;
				out_sg->length -= split->skip_sg0;
			पूर्ण अन्यथा अणु
				out_sg->offset = 0;
			पूर्ण
			sg_dma_address(out_sg) = 0;
			sg_dma_len(out_sg) = 0;
			in_sg = sg_next(in_sg);
		पूर्ण
		out_sg[-1].length = split->length_last_sg;
		sg_mark_end(out_sg - 1);
	पूर्ण
पूर्ण

अटल व्योम sg_split_mapped(काष्ठा sg_splitter *splitters, स्थिर पूर्णांक nb_splits)
अणु
	पूर्णांक i, j;
	काष्ठा scatterlist *in_sg, *out_sg;
	काष्ठा sg_splitter *split;

	क्रम (i = 0, split = splitters; i < nb_splits; i++, split++) अणु
		in_sg = split->in_sg0;
		out_sg = split->out_sg;
		क्रम (j = 0; j < split->nents; j++, out_sg++) अणु
			sg_dma_address(out_sg) = sg_dma_address(in_sg);
			sg_dma_len(out_sg) = sg_dma_len(in_sg);
			अगर (!j) अणु
				sg_dma_address(out_sg) += split->skip_sg0;
				sg_dma_len(out_sg) -= split->skip_sg0;
			पूर्ण
			in_sg = sg_next(in_sg);
		पूर्ण
		sg_dma_len(--out_sg) = split->length_last_sg;
	पूर्ण
पूर्ण

/**
 * sg_split - split a scatterlist पूर्णांकo several scatterlists
 * @in: the input sg list
 * @in_mapped_nents: the result of a dma_map_sg(in, ...), or 0 अगर not mapped.
 * @skip: the number of bytes to skip in the input sg list
 * @nb_splits: the number of desired sg outमाला_दो
 * @split_sizes: the respective size of each output sg list in bytes
 * @out: an array where to store the allocated output sg lists
 * @out_mapped_nents: the resulting sg lists mapped number of sg entries. Might
 *                    be शून्य अगर sglist not alपढ़ोy mapped (in_mapped_nents = 0)
 * @gfp_mask: the allocation flag
 *
 * This function splits the input sg list पूर्णांकo nb_splits sg lists, which are
 * allocated and stored पूर्णांकo out.
 * The @in is split पूर्णांकo :
 *  - @out[0], which covers bytes [@skip .. @skip + @split_sizes[0] - 1] of @in
 *  - @out[1], which covers bytes [@skip + split_sizes[0] ..
 *                                 @skip + @split_sizes[0] + @split_sizes[1] -1]
 * etc ...
 * It will be the caller's duty to kमुक्त() out array members.
 *
 * Returns 0 upon success, or error code
 */
पूर्णांक sg_split(काष्ठा scatterlist *in, स्थिर पूर्णांक in_mapped_nents,
	     स्थिर off_t skip, स्थिर पूर्णांक nb_splits,
	     स्थिर माप_प्रकार *split_sizes,
	     काष्ठा scatterlist **out, पूर्णांक *out_mapped_nents,
	     gfp_t gfp_mask)
अणु
	पूर्णांक i, ret;
	काष्ठा sg_splitter *splitters;

	splitters = kसुस्मृति(nb_splits, माप(*splitters), gfp_mask);
	अगर (!splitters)
		वापस -ENOMEM;

	ret = sg_calculate_split(in, sg_nents(in), nb_splits, skip, split_sizes,
			   splitters, false);
	अगर (ret < 0)
		जाओ err;

	ret = -ENOMEM;
	क्रम (i = 0; i < nb_splits; i++) अणु
		splitters[i].out_sg = kदो_स्मृति_array(splitters[i].nents,
						    माप(काष्ठा scatterlist),
						    gfp_mask);
		अगर (!splitters[i].out_sg)
			जाओ err;
	पूर्ण

	/*
	 * The order of these 3 calls is important and should be kept.
	 */
	sg_split_phys(splitters, nb_splits);
	अगर (in_mapped_nents) अणु
		ret = sg_calculate_split(in, in_mapped_nents, nb_splits, skip,
					 split_sizes, splitters, true);
		अगर (ret < 0)
			जाओ err;
		sg_split_mapped(splitters, nb_splits);
	पूर्ण

	क्रम (i = 0; i < nb_splits; i++) अणु
		out[i] = splitters[i].out_sg;
		अगर (out_mapped_nents)
			out_mapped_nents[i] = splitters[i].nents;
	पूर्ण

	kमुक्त(splitters);
	वापस 0;

err:
	क्रम (i = 0; i < nb_splits; i++)
		kमुक्त(splitters[i].out_sg);
	kमुक्त(splitters);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(sg_split);
