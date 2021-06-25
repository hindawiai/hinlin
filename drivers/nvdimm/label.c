<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright(c) 2013-2015 Intel Corporation. All rights reserved.
 */
#समावेश <linux/device.h>
#समावेश <linux/ndctl.h>
#समावेश <linux/uuid.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/nd.h>
#समावेश "nd-core.h"
#समावेश "label.h"
#समावेश "nd.h"

अटल guid_t nvdimm_btt_guid;
अटल guid_t nvdimm_btt2_guid;
अटल guid_t nvdimm_pfn_guid;
अटल guid_t nvdimm_dax_guid;

अटल स्थिर अक्षर NSINDEX_SIGNATURE[] = "NAMESPACE_INDEX\0";

अटल u32 best_seq(u32 a, u32 b)
अणु
	a &= NSINDEX_SEQ_MASK;
	b &= NSINDEX_SEQ_MASK;

	अगर (a == 0 || a == b)
		वापस b;
	अन्यथा अगर (b == 0)
		वापस a;
	अन्यथा अगर (nd_inc_seq(a) == b)
		वापस b;
	अन्यथा
		वापस a;
पूर्ण

अचिन्हित माप_namespace_label(काष्ठा nvdimm_drvdata *ndd)
अणु
	वापस ndd->nslabel_size;
पूर्ण

अटल माप_प्रकार __माप_namespace_index(u32 nslot)
अणु
	वापस ALIGN(माप(काष्ठा nd_namespace_index) + DIV_ROUND_UP(nslot, 8),
			NSINDEX_ALIGN);
पूर्ण

अटल पूर्णांक __nvdimm_num_label_slots(काष्ठा nvdimm_drvdata *ndd,
		माप_प्रकार index_size)
अणु
	वापस (ndd->nsarea.config_size - index_size * 2) /
			माप_namespace_label(ndd);
पूर्ण

पूर्णांक nvdimm_num_label_slots(काष्ठा nvdimm_drvdata *ndd)
अणु
	u32 पंचांगp_nslot, n;

	पंचांगp_nslot = ndd->nsarea.config_size / माप_namespace_label(ndd);
	n = __माप_namespace_index(पंचांगp_nslot) / NSINDEX_ALIGN;

	वापस __nvdimm_num_label_slots(ndd, NSINDEX_ALIGN * n);
पूर्ण

माप_प्रकार माप_namespace_index(काष्ठा nvdimm_drvdata *ndd)
अणु
	u32 nslot, space, size;

	/*
	 * Per UEFI 2.7, the minimum size of the Label Storage Area is large
	 * enough to hold 2 index blocks and 2 labels.  The minimum index
	 * block size is 256 bytes. The label size is 128 क्रम namespaces
	 * prior to version 1.2 and at minimum 256 क्रम version 1.2 and later.
	 */
	nslot = nvdimm_num_label_slots(ndd);
	space = ndd->nsarea.config_size - nslot * माप_namespace_label(ndd);
	size = __माप_namespace_index(nslot) * 2;
	अगर (size <= space && nslot >= 2)
		वापस size / 2;

	dev_err(ndd->dev, "label area (%d) too small to host (%d byte) labels\n",
			ndd->nsarea.config_size, माप_namespace_label(ndd));
	वापस 0;
पूर्ण

अटल पूर्णांक __nd_label_validate(काष्ठा nvdimm_drvdata *ndd)
अणु
	/*
	 * On media label क्रमmat consists of two index blocks followed
	 * by an array of labels.  None of these काष्ठाures are ever
	 * updated in place.  A sequence number tracks the current
	 * active index and the next one to ग_लिखो, जबतक labels are
	 * written to मुक्त slots.
	 *
	 *     +------------+
	 *     |            |
	 *     |  nsindex0  |
	 *     |            |
	 *     +------------+
	 *     |            |
	 *     |  nsindex1  |
	 *     |            |
	 *     +------------+
	 *     |   label0   |
	 *     +------------+
	 *     |   label1   |
	 *     +------------+
	 *     |            |
	 *      ....nslot...
	 *     |            |
	 *     +------------+
	 *     |   labelN   |
	 *     +------------+
	 */
	काष्ठा nd_namespace_index *nsindex[] = अणु
		to_namespace_index(ndd, 0),
		to_namespace_index(ndd, 1),
	पूर्ण;
	स्थिर पूर्णांक num_index = ARRAY_SIZE(nsindex);
	काष्ठा device *dev = ndd->dev;
	bool valid[2] = अणु 0 पूर्ण;
	पूर्णांक i, num_valid = 0;
	u32 seq;

	क्रम (i = 0; i < num_index; i++) अणु
		u32 nslot;
		u8 sig[NSINDEX_SIG_LEN];
		u64 sum_save, sum, size;
		अचिन्हित पूर्णांक version, labelsize;

		स_नकल(sig, nsindex[i]->sig, NSINDEX_SIG_LEN);
		अगर (स_भेद(sig, NSINDEX_SIGNATURE, NSINDEX_SIG_LEN) != 0) अणु
			dev_dbg(dev, "nsindex%d signature invalid\n", i);
			जारी;
		पूर्ण

		/* label sizes larger than 128 arrived with v1.2 */
		version = __le16_to_cpu(nsindex[i]->major) * 100
			+ __le16_to_cpu(nsindex[i]->minor);
		अगर (version >= 102)
			labelsize = 1 << (7 + nsindex[i]->labelsize);
		अन्यथा
			labelsize = 128;

		अगर (labelsize != माप_namespace_label(ndd)) अणु
			dev_dbg(dev, "nsindex%d labelsize %d invalid\n",
					i, nsindex[i]->labelsize);
			जारी;
		पूर्ण

		sum_save = __le64_to_cpu(nsindex[i]->checksum);
		nsindex[i]->checksum = __cpu_to_le64(0);
		sum = nd_fletcher64(nsindex[i], माप_namespace_index(ndd), 1);
		nsindex[i]->checksum = __cpu_to_le64(sum_save);
		अगर (sum != sum_save) अणु
			dev_dbg(dev, "nsindex%d checksum invalid\n", i);
			जारी;
		पूर्ण

		seq = __le32_to_cpu(nsindex[i]->seq);
		अगर ((seq & NSINDEX_SEQ_MASK) == 0) अणु
			dev_dbg(dev, "nsindex%d sequence: %#x invalid\n", i, seq);
			जारी;
		पूर्ण

		/* sanity check the index against expected values */
		अगर (__le64_to_cpu(nsindex[i]->myoff)
				!= i * माप_namespace_index(ndd)) अणु
			dev_dbg(dev, "nsindex%d myoff: %#llx invalid\n",
					i, (अचिन्हित दीर्घ दीर्घ)
					__le64_to_cpu(nsindex[i]->myoff));
			जारी;
		पूर्ण
		अगर (__le64_to_cpu(nsindex[i]->otheroff)
				!= (!i) * माप_namespace_index(ndd)) अणु
			dev_dbg(dev, "nsindex%d otheroff: %#llx invalid\n",
					i, (अचिन्हित दीर्घ दीर्घ)
					__le64_to_cpu(nsindex[i]->otheroff));
			जारी;
		पूर्ण
		अगर (__le64_to_cpu(nsindex[i]->labeloff)
				!= 2 * माप_namespace_index(ndd)) अणु
			dev_dbg(dev, "nsindex%d labeloff: %#llx invalid\n",
					i, (अचिन्हित दीर्घ दीर्घ)
					__le64_to_cpu(nsindex[i]->labeloff));
			जारी;
		पूर्ण

		size = __le64_to_cpu(nsindex[i]->mysize);
		अगर (size > माप_namespace_index(ndd)
				|| size < माप(काष्ठा nd_namespace_index)) अणु
			dev_dbg(dev, "nsindex%d mysize: %#llx invalid\n", i, size);
			जारी;
		पूर्ण

		nslot = __le32_to_cpu(nsindex[i]->nslot);
		अगर (nslot * माप_namespace_label(ndd)
				+ 2 * माप_namespace_index(ndd)
				> ndd->nsarea.config_size) अणु
			dev_dbg(dev, "nsindex%d nslot: %u invalid, config_size: %#x\n",
					i, nslot, ndd->nsarea.config_size);
			जारी;
		पूर्ण
		valid[i] = true;
		num_valid++;
	पूर्ण

	चयन (num_valid) अणु
	हाल 0:
		अवरोध;
	हाल 1:
		क्रम (i = 0; i < num_index; i++)
			अगर (valid[i])
				वापस i;
		/* can't have num_valid > 0 but valid[] = अणु false, false पूर्ण */
		WARN_ON(1);
		अवरोध;
	शेष:
		/* pick the best index... */
		seq = best_seq(__le32_to_cpu(nsindex[0]->seq),
				__le32_to_cpu(nsindex[1]->seq));
		अगर (seq == (__le32_to_cpu(nsindex[1]->seq) & NSINDEX_SEQ_MASK))
			वापस 1;
		अन्यथा
			वापस 0;
		अवरोध;
	पूर्ण

	वापस -1;
पूर्ण

अटल पूर्णांक nd_label_validate(काष्ठा nvdimm_drvdata *ndd)
अणु
	/*
	 * In order to probe क्रम and validate namespace index blocks we
	 * need to know the size of the labels, and we can't trust the
	 * size of the labels until we validate the index blocks.
	 * Resolve this dependency loop by probing क्रम known label
	 * sizes, but शेष to v1.2 256-byte namespace labels अगर
	 * discovery fails.
	 */
	पूर्णांक label_size[] = अणु 128, 256 पूर्ण;
	पूर्णांक i, rc;

	क्रम (i = 0; i < ARRAY_SIZE(label_size); i++) अणु
		ndd->nslabel_size = label_size[i];
		rc = __nd_label_validate(ndd);
		अगर (rc >= 0)
			वापस rc;
	पूर्ण

	वापस -1;
पूर्ण

अटल व्योम nd_label_copy(काष्ठा nvdimm_drvdata *ndd,
			  काष्ठा nd_namespace_index *dst,
			  काष्ठा nd_namespace_index *src)
अणु
	/* just निकास अगर either destination or source is शून्य */
	अगर (!dst || !src)
		वापस;

	स_नकल(dst, src, माप_namespace_index(ndd));
पूर्ण

अटल काष्ठा nd_namespace_label *nd_label_base(काष्ठा nvdimm_drvdata *ndd)
अणु
	व्योम *base = to_namespace_index(ndd, 0);

	वापस base + 2 * माप_namespace_index(ndd);
पूर्ण

अटल पूर्णांक to_slot(काष्ठा nvdimm_drvdata *ndd,
		काष्ठा nd_namespace_label *nd_label)
अणु
	अचिन्हित दीर्घ label, base;

	label = (अचिन्हित दीर्घ) nd_label;
	base = (अचिन्हित दीर्घ) nd_label_base(ndd);

	वापस (label - base) / माप_namespace_label(ndd);
पूर्ण

अटल काष्ठा nd_namespace_label *to_label(काष्ठा nvdimm_drvdata *ndd, पूर्णांक slot)
अणु
	अचिन्हित दीर्घ label, base;

	base = (अचिन्हित दीर्घ) nd_label_base(ndd);
	label = base + माप_namespace_label(ndd) * slot;

	वापस (काष्ठा nd_namespace_label *) label;
पूर्ण

#घोषणा क्रम_each_clear_bit_le(bit, addr, size) \
	क्रम ((bit) = find_next_zero_bit_le((addr), (size), 0);  \
	     (bit) < (size);                                    \
	     (bit) = find_next_zero_bit_le((addr), (size), (bit) + 1))

/**
 * preamble_index - common variable initialization क्रम nd_label_* routines
 * @ndd: dimm container क्रम the relevant label set
 * @idx: namespace_index index
 * @nsindex_out: on वापस set to the currently active namespace index
 * @मुक्त: on वापस set to the मुक्त label biपंचांगap in the index
 * @nslot: on वापस set to the number of slots in the label space
 */
अटल bool preamble_index(काष्ठा nvdimm_drvdata *ndd, पूर्णांक idx,
		काष्ठा nd_namespace_index **nsindex_out,
		अचिन्हित दीर्घ **मुक्त, u32 *nslot)
अणु
	काष्ठा nd_namespace_index *nsindex;

	nsindex = to_namespace_index(ndd, idx);
	अगर (nsindex == शून्य)
		वापस false;

	*मुक्त = (अचिन्हित दीर्घ *) nsindex->मुक्त;
	*nslot = __le32_to_cpu(nsindex->nslot);
	*nsindex_out = nsindex;

	वापस true;
पूर्ण

अक्षर *nd_label_gen_id(काष्ठा nd_label_id *label_id, u8 *uuid, u32 flags)
अणु
	अगर (!label_id || !uuid)
		वापस शून्य;
	snम_लिखो(label_id->id, ND_LABEL_ID_SIZE, "%s-%pUb",
			flags & NSLABEL_FLAG_LOCAL ? "blk" : "pmem", uuid);
	वापस label_id->id;
पूर्ण

अटल bool preamble_current(काष्ठा nvdimm_drvdata *ndd,
		काष्ठा nd_namespace_index **nsindex,
		अचिन्हित दीर्घ **मुक्त, u32 *nslot)
अणु
	वापस preamble_index(ndd, ndd->ns_current, nsindex,
			मुक्त, nslot);
पूर्ण

अटल bool preamble_next(काष्ठा nvdimm_drvdata *ndd,
		काष्ठा nd_namespace_index **nsindex,
		अचिन्हित दीर्घ **मुक्त, u32 *nslot)
अणु
	वापस preamble_index(ndd, ndd->ns_next, nsindex,
			मुक्त, nslot);
पूर्ण

अटल bool slot_valid(काष्ठा nvdimm_drvdata *ndd,
		काष्ठा nd_namespace_label *nd_label, u32 slot)
अणु
	/* check that we are written where we expect to be written */
	अगर (slot != __le32_to_cpu(nd_label->slot))
		वापस false;

	/* check checksum */
	अगर (namespace_label_has(ndd, checksum)) अणु
		u64 sum, sum_save;

		sum_save = __le64_to_cpu(nd_label->checksum);
		nd_label->checksum = __cpu_to_le64(0);
		sum = nd_fletcher64(nd_label, माप_namespace_label(ndd), 1);
		nd_label->checksum = __cpu_to_le64(sum_save);
		अगर (sum != sum_save) अणु
			dev_dbg(ndd->dev, "fail checksum. slot: %d expect: %#llx\n",
				slot, sum);
			वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

पूर्णांक nd_label_reserve_dpa(काष्ठा nvdimm_drvdata *ndd)
अणु
	काष्ठा nd_namespace_index *nsindex;
	अचिन्हित दीर्घ *मुक्त;
	u32 nslot, slot;

	अगर (!preamble_current(ndd, &nsindex, &मुक्त, &nslot))
		वापस 0; /* no label, nothing to reserve */

	क्रम_each_clear_bit_le(slot, मुक्त, nslot) अणु
		काष्ठा nvdimm *nvdimm = to_nvdimm(ndd->dev);
		काष्ठा nd_namespace_label *nd_label;
		काष्ठा nd_region *nd_region = शून्य;
		u8 label_uuid[NSLABEL_UUID_LEN];
		काष्ठा nd_label_id label_id;
		काष्ठा resource *res;
		u32 flags;

		nd_label = to_label(ndd, slot);

		अगर (!slot_valid(ndd, nd_label, slot))
			जारी;

		स_नकल(label_uuid, nd_label->uuid, NSLABEL_UUID_LEN);
		flags = __le32_to_cpu(nd_label->flags);
		अगर (test_bit(NDD_NOBLK, &nvdimm->flags))
			flags &= ~NSLABEL_FLAG_LOCAL;
		nd_label_gen_id(&label_id, label_uuid, flags);
		res = nvdimm_allocate_dpa(ndd, &label_id,
				__le64_to_cpu(nd_label->dpa),
				__le64_to_cpu(nd_label->rawsize));
		nd_dbg_dpa(nd_region, ndd, res, "reserve\n");
		अगर (!res)
			वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक nd_label_data_init(काष्ठा nvdimm_drvdata *ndd)
अणु
	माप_प्रकार config_size, पढ़ो_size, max_xfer, offset;
	काष्ठा nd_namespace_index *nsindex;
	अचिन्हित पूर्णांक i;
	पूर्णांक rc = 0;
	u32 nslot;

	अगर (ndd->data)
		वापस 0;

	अगर (ndd->nsarea.status || ndd->nsarea.max_xfer == 0) अणु
		dev_dbg(ndd->dev, "failed to init config data area: (%u:%u)\n",
			ndd->nsarea.max_xfer, ndd->nsarea.config_size);
		वापस -ENXIO;
	पूर्ण

	/*
	 * We need to determine the maximum index area as this is the section
	 * we must पढ़ो and validate beक्रमe we can start processing labels.
	 *
	 * If the area is too small to contain the two indexes and 2 labels
	 * then we पात.
	 *
	 * Start at a label size of 128 as this should result in the largest
	 * possible namespace index size.
	 */
	ndd->nslabel_size = 128;
	पढ़ो_size = माप_namespace_index(ndd) * 2;
	अगर (!पढ़ो_size)
		वापस -ENXIO;

	/* Allocate config data */
	config_size = ndd->nsarea.config_size;
	ndd->data = kvzalloc(config_size, GFP_KERNEL);
	अगर (!ndd->data)
		वापस -ENOMEM;

	/*
	 * We want to guarantee as few पढ़ोs as possible जबतक conserving
	 * memory. To करो that we figure out how much unused space will be left
	 * in the last पढ़ो, भागide that by the total number of पढ़ोs it is
	 * going to take given our maximum transfer size, and then reduce our
	 * maximum transfer size based on that result.
	 */
	max_xfer = min_t(माप_प्रकार, ndd->nsarea.max_xfer, config_size);
	अगर (पढ़ो_size < max_xfer) अणु
		/* trim waste */
		max_xfer -= ((max_xfer - 1) - (config_size - 1) % max_xfer) /
			    DIV_ROUND_UP(config_size, max_xfer);
		/* make certain we पढ़ो indexes in exactly 1 पढ़ो */
		अगर (max_xfer < पढ़ो_size)
			max_xfer = पढ़ो_size;
	पूर्ण

	/* Make our initial पढ़ो size a multiple of max_xfer size */
	पढ़ो_size = min(DIV_ROUND_UP(पढ़ो_size, max_xfer) * max_xfer,
			config_size);

	/* Read the index data */
	rc = nvdimm_get_config_data(ndd, ndd->data, 0, पढ़ो_size);
	अगर (rc)
		जाओ out_err;

	/* Validate index data, अगर not valid assume all labels are invalid */
	ndd->ns_current = nd_label_validate(ndd);
	अगर (ndd->ns_current < 0)
		वापस 0;

	/* Record our index values */
	ndd->ns_next = nd_label_next_nsindex(ndd->ns_current);

	/* Copy "current" index on top of the "next" index */
	nsindex = to_current_namespace_index(ndd);
	nd_label_copy(ndd, to_next_namespace_index(ndd), nsindex);

	/* Determine starting offset क्रम label data */
	offset = __le64_to_cpu(nsindex->labeloff);
	nslot = __le32_to_cpu(nsindex->nslot);

	/* Loop through the मुक्त list pulling in any active labels */
	क्रम (i = 0; i < nslot; i++, offset += ndd->nslabel_size) अणु
		माप_प्रकार label_पढ़ो_size;

		/* zero out the unused labels */
		अगर (test_bit_le(i, nsindex->मुक्त)) अणु
			स_रखो(ndd->data + offset, 0, ndd->nslabel_size);
			जारी;
		पूर्ण

		/* अगर we alपढ़ोy पढ़ो past here then just जारी */
		अगर (offset + ndd->nslabel_size <= पढ़ो_size)
			जारी;

		/* अगर we haven't पढ़ो in a जबतक reset our पढ़ो_size offset */
		अगर (पढ़ो_size < offset)
			पढ़ो_size = offset;

		/* determine how much more will be पढ़ो after this next call. */
		label_पढ़ो_size = offset + ndd->nslabel_size - पढ़ो_size;
		label_पढ़ो_size = DIV_ROUND_UP(label_पढ़ो_size, max_xfer) *
				  max_xfer;

		/* truncate last पढ़ो अगर needed */
		अगर (पढ़ो_size + label_पढ़ो_size > config_size)
			label_पढ़ो_size = config_size - पढ़ो_size;

		/* Read the label data */
		rc = nvdimm_get_config_data(ndd, ndd->data + पढ़ो_size,
					    पढ़ो_size, label_पढ़ो_size);
		अगर (rc)
			जाओ out_err;

		/* push पढ़ो_size to next पढ़ो offset */
		पढ़ो_size += label_पढ़ो_size;
	पूर्ण

	dev_dbg(ndd->dev, "len: %zu rc: %d\n", offset, rc);
out_err:
	वापस rc;
पूर्ण

पूर्णांक nd_label_active_count(काष्ठा nvdimm_drvdata *ndd)
अणु
	काष्ठा nd_namespace_index *nsindex;
	अचिन्हित दीर्घ *मुक्त;
	u32 nslot, slot;
	पूर्णांक count = 0;

	अगर (!preamble_current(ndd, &nsindex, &मुक्त, &nslot))
		वापस 0;

	क्रम_each_clear_bit_le(slot, मुक्त, nslot) अणु
		काष्ठा nd_namespace_label *nd_label;

		nd_label = to_label(ndd, slot);

		अगर (!slot_valid(ndd, nd_label, slot)) अणु
			u32 label_slot = __le32_to_cpu(nd_label->slot);
			u64 size = __le64_to_cpu(nd_label->rawsize);
			u64 dpa = __le64_to_cpu(nd_label->dpa);

			dev_dbg(ndd->dev,
				"slot%d invalid slot: %d dpa: %llx size: %llx\n",
					slot, label_slot, dpa, size);
			जारी;
		पूर्ण
		count++;
	पूर्ण
	वापस count;
पूर्ण

काष्ठा nd_namespace_label *nd_label_active(काष्ठा nvdimm_drvdata *ndd, पूर्णांक n)
अणु
	काष्ठा nd_namespace_index *nsindex;
	अचिन्हित दीर्घ *मुक्त;
	u32 nslot, slot;

	अगर (!preamble_current(ndd, &nsindex, &मुक्त, &nslot))
		वापस शून्य;

	क्रम_each_clear_bit_le(slot, मुक्त, nslot) अणु
		काष्ठा nd_namespace_label *nd_label;

		nd_label = to_label(ndd, slot);
		अगर (!slot_valid(ndd, nd_label, slot))
			जारी;

		अगर (n-- == 0)
			वापस to_label(ndd, slot);
	पूर्ण

	वापस शून्य;
पूर्ण

u32 nd_label_alloc_slot(काष्ठा nvdimm_drvdata *ndd)
अणु
	काष्ठा nd_namespace_index *nsindex;
	अचिन्हित दीर्घ *मुक्त;
	u32 nslot, slot;

	अगर (!preamble_next(ndd, &nsindex, &मुक्त, &nslot))
		वापस अच_पूर्णांक_उच्च;

	WARN_ON(!is_nvdimm_bus_locked(ndd->dev));

	slot = find_next_bit_le(मुक्त, nslot, 0);
	अगर (slot == nslot)
		वापस अच_पूर्णांक_उच्च;

	clear_bit_le(slot, मुक्त);

	वापस slot;
पूर्ण

bool nd_label_मुक्त_slot(काष्ठा nvdimm_drvdata *ndd, u32 slot)
अणु
	काष्ठा nd_namespace_index *nsindex;
	अचिन्हित दीर्घ *मुक्त;
	u32 nslot;

	अगर (!preamble_next(ndd, &nsindex, &मुक्त, &nslot))
		वापस false;

	WARN_ON(!is_nvdimm_bus_locked(ndd->dev));

	अगर (slot < nslot)
		वापस !test_and_set_bit_le(slot, मुक्त);
	वापस false;
पूर्ण

u32 nd_label_nमुक्त(काष्ठा nvdimm_drvdata *ndd)
अणु
	काष्ठा nd_namespace_index *nsindex;
	अचिन्हित दीर्घ *मुक्त;
	u32 nslot;

	WARN_ON(!is_nvdimm_bus_locked(ndd->dev));

	अगर (!preamble_next(ndd, &nsindex, &मुक्त, &nslot))
		वापस nvdimm_num_label_slots(ndd);

	वापस biपंचांगap_weight(मुक्त, nslot);
पूर्ण

अटल पूर्णांक nd_label_ग_लिखो_index(काष्ठा nvdimm_drvdata *ndd, पूर्णांक index, u32 seq,
		अचिन्हित दीर्घ flags)
अणु
	काष्ठा nd_namespace_index *nsindex;
	अचिन्हित दीर्घ offset;
	u64 checksum;
	u32 nslot;
	पूर्णांक rc;

	nsindex = to_namespace_index(ndd, index);
	अगर (flags & ND_NSINDEX_INIT)
		nslot = nvdimm_num_label_slots(ndd);
	अन्यथा
		nslot = __le32_to_cpu(nsindex->nslot);

	स_नकल(nsindex->sig, NSINDEX_SIGNATURE, NSINDEX_SIG_LEN);
	स_रखो(&nsindex->flags, 0, 3);
	nsindex->labelsize = माप_namespace_label(ndd) >> 8;
	nsindex->seq = __cpu_to_le32(seq);
	offset = (अचिन्हित दीर्घ) nsindex
		- (अचिन्हित दीर्घ) to_namespace_index(ndd, 0);
	nsindex->myoff = __cpu_to_le64(offset);
	nsindex->mysize = __cpu_to_le64(माप_namespace_index(ndd));
	offset = (अचिन्हित दीर्घ) to_namespace_index(ndd,
			nd_label_next_nsindex(index))
		- (अचिन्हित दीर्घ) to_namespace_index(ndd, 0);
	nsindex->otheroff = __cpu_to_le64(offset);
	offset = (अचिन्हित दीर्घ) nd_label_base(ndd)
		- (अचिन्हित दीर्घ) to_namespace_index(ndd, 0);
	nsindex->labeloff = __cpu_to_le64(offset);
	nsindex->nslot = __cpu_to_le32(nslot);
	nsindex->major = __cpu_to_le16(1);
	अगर (माप_namespace_label(ndd) < 256)
		nsindex->minor = __cpu_to_le16(1);
	अन्यथा
		nsindex->minor = __cpu_to_le16(2);
	nsindex->checksum = __cpu_to_le64(0);
	अगर (flags & ND_NSINDEX_INIT) अणु
		अचिन्हित दीर्घ *मुक्त = (अचिन्हित दीर्घ *) nsindex->मुक्त;
		u32 nमुक्त = ALIGN(nslot, BITS_PER_LONG);
		पूर्णांक last_bits, i;

		स_रखो(nsindex->मुक्त, 0xff, nमुक्त / 8);
		क्रम (i = 0, last_bits = nमुक्त - nslot; i < last_bits; i++)
			clear_bit_le(nslot + i, मुक्त);
	पूर्ण
	checksum = nd_fletcher64(nsindex, माप_namespace_index(ndd), 1);
	nsindex->checksum = __cpu_to_le64(checksum);
	rc = nvdimm_set_config_data(ndd, __le64_to_cpu(nsindex->myoff),
			nsindex, माप_namespace_index(ndd));
	अगर (rc < 0)
		वापस rc;

	अगर (flags & ND_NSINDEX_INIT)
		वापस 0;

	/* copy the index we just wrote to the new 'next' */
	WARN_ON(index != ndd->ns_next);
	nd_label_copy(ndd, to_current_namespace_index(ndd), nsindex);
	ndd->ns_current = nd_label_next_nsindex(ndd->ns_current);
	ndd->ns_next = nd_label_next_nsindex(ndd->ns_next);
	WARN_ON(ndd->ns_current == ndd->ns_next);

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ nd_label_offset(काष्ठा nvdimm_drvdata *ndd,
		काष्ठा nd_namespace_label *nd_label)
अणु
	वापस (अचिन्हित दीर्घ) nd_label
		- (अचिन्हित दीर्घ) to_namespace_index(ndd, 0);
पूर्ण

क्रमागत nvdimm_claim_class to_nvdimm_cclass(guid_t *guid)
अणु
	अगर (guid_equal(guid, &nvdimm_btt_guid))
		वापस NVDIMM_CCLASS_BTT;
	अन्यथा अगर (guid_equal(guid, &nvdimm_btt2_guid))
		वापस NVDIMM_CCLASS_BTT2;
	अन्यथा अगर (guid_equal(guid, &nvdimm_pfn_guid))
		वापस NVDIMM_CCLASS_PFN;
	अन्यथा अगर (guid_equal(guid, &nvdimm_dax_guid))
		वापस NVDIMM_CCLASS_DAX;
	अन्यथा अगर (guid_equal(guid, &guid_null))
		वापस NVDIMM_CCLASS_NONE;

	वापस NVDIMM_CCLASS_UNKNOWN;
पूर्ण

अटल स्थिर guid_t *to_असलtraction_guid(क्रमागत nvdimm_claim_class claim_class,
	guid_t *target)
अणु
	अगर (claim_class == NVDIMM_CCLASS_BTT)
		वापस &nvdimm_btt_guid;
	अन्यथा अगर (claim_class == NVDIMM_CCLASS_BTT2)
		वापस &nvdimm_btt2_guid;
	अन्यथा अगर (claim_class == NVDIMM_CCLASS_PFN)
		वापस &nvdimm_pfn_guid;
	अन्यथा अगर (claim_class == NVDIMM_CCLASS_DAX)
		वापस &nvdimm_dax_guid;
	अन्यथा अगर (claim_class == NVDIMM_CCLASS_UNKNOWN) अणु
		/*
		 * If we're modifying a namespace for which we don't
		 * know the claim_class, करोn't touch the existing guid.
		 */
		वापस target;
	पूर्ण अन्यथा
		वापस &guid_null;
पूर्ण

अटल व्योम reap_victim(काष्ठा nd_mapping *nd_mapping,
		काष्ठा nd_label_ent *victim)
अणु
	काष्ठा nvdimm_drvdata *ndd = to_ndd(nd_mapping);
	u32 slot = to_slot(ndd, victim->label);

	dev_dbg(ndd->dev, "free: %d\n", slot);
	nd_label_मुक्त_slot(ndd, slot);
	victim->label = शून्य;
पूर्ण

अटल पूर्णांक __pmem_label_update(काष्ठा nd_region *nd_region,
		काष्ठा nd_mapping *nd_mapping, काष्ठा nd_namespace_pmem *nspm,
		पूर्णांक pos, अचिन्हित दीर्घ flags)
अणु
	काष्ठा nd_namespace_common *ndns = &nspm->nsio.common;
	काष्ठा nd_पूर्णांकerleave_set *nd_set = nd_region->nd_set;
	काष्ठा nvdimm_drvdata *ndd = to_ndd(nd_mapping);
	काष्ठा nd_namespace_label *nd_label;
	काष्ठा nd_namespace_index *nsindex;
	काष्ठा nd_label_ent *label_ent;
	काष्ठा nd_label_id label_id;
	काष्ठा resource *res;
	अचिन्हित दीर्घ *मुक्त;
	u32 nslot, slot;
	माप_प्रकार offset;
	u64 cookie;
	पूर्णांक rc;

	अगर (!preamble_next(ndd, &nsindex, &मुक्त, &nslot))
		वापस -ENXIO;

	cookie = nd_region_पूर्णांकerleave_set_cookie(nd_region, nsindex);
	nd_label_gen_id(&label_id, nspm->uuid, 0);
	क्रम_each_dpa_resource(ndd, res)
		अगर (म_भेद(res->name, label_id.id) == 0)
			अवरोध;

	अगर (!res) अणु
		WARN_ON_ONCE(1);
		वापस -ENXIO;
	पूर्ण

	/* allocate and ग_लिखो the label to the staging (next) index */
	slot = nd_label_alloc_slot(ndd);
	अगर (slot == अच_पूर्णांक_उच्च)
		वापस -ENXIO;
	dev_dbg(ndd->dev, "allocated: %d\n", slot);

	nd_label = to_label(ndd, slot);
	स_रखो(nd_label, 0, माप_namespace_label(ndd));
	स_नकल(nd_label->uuid, nspm->uuid, NSLABEL_UUID_LEN);
	अगर (nspm->alt_name)
		स_नकल(nd_label->name, nspm->alt_name, NSLABEL_NAME_LEN);
	nd_label->flags = __cpu_to_le32(flags);
	nd_label->nlabel = __cpu_to_le16(nd_region->ndr_mappings);
	nd_label->position = __cpu_to_le16(pos);
	nd_label->isetcookie = __cpu_to_le64(cookie);
	nd_label->rawsize = __cpu_to_le64(resource_size(res));
	nd_label->lbasize = __cpu_to_le64(nspm->lbasize);
	nd_label->dpa = __cpu_to_le64(res->start);
	nd_label->slot = __cpu_to_le32(slot);
	अगर (namespace_label_has(ndd, type_guid))
		guid_copy(&nd_label->type_guid, &nd_set->type_guid);
	अगर (namespace_label_has(ndd, असलtraction_guid))
		guid_copy(&nd_label->असलtraction_guid,
				to_असलtraction_guid(ndns->claim_class,
					&nd_label->असलtraction_guid));
	अगर (namespace_label_has(ndd, checksum)) अणु
		u64 sum;

		nd_label->checksum = __cpu_to_le64(0);
		sum = nd_fletcher64(nd_label, माप_namespace_label(ndd), 1);
		nd_label->checksum = __cpu_to_le64(sum);
	पूर्ण
	nd_dbg_dpa(nd_region, ndd, res, "\n");

	/* update label */
	offset = nd_label_offset(ndd, nd_label);
	rc = nvdimm_set_config_data(ndd, offset, nd_label,
			माप_namespace_label(ndd));
	अगर (rc < 0)
		वापस rc;

	/* Garbage collect the previous label */
	mutex_lock(&nd_mapping->lock);
	list_क्रम_each_entry(label_ent, &nd_mapping->labels, list) अणु
		अगर (!label_ent->label)
			जारी;
		अगर (test_and_clear_bit(ND_LABEL_REAP, &label_ent->flags)
				|| स_भेद(nspm->uuid, label_ent->label->uuid,
					NSLABEL_UUID_LEN) == 0)
			reap_victim(nd_mapping, label_ent);
	पूर्ण

	/* update index */
	rc = nd_label_ग_लिखो_index(ndd, ndd->ns_next,
			nd_inc_seq(__le32_to_cpu(nsindex->seq)), 0);
	अगर (rc == 0) अणु
		list_क्रम_each_entry(label_ent, &nd_mapping->labels, list)
			अगर (!label_ent->label) अणु
				label_ent->label = nd_label;
				nd_label = शून्य;
				अवरोध;
			पूर्ण
		dev_WARN_ONCE(&nspm->nsio.common.dev, nd_label,
				"failed to track label: %d\n",
				to_slot(ndd, nd_label));
		अगर (nd_label)
			rc = -ENXIO;
	पूर्ण
	mutex_unlock(&nd_mapping->lock);

	वापस rc;
पूर्ण

अटल bool is_old_resource(काष्ठा resource *res, काष्ठा resource **list, पूर्णांक n)
अणु
	पूर्णांक i;

	अगर (res->flags & DPA_RESOURCE_ADJUSTED)
		वापस false;
	क्रम (i = 0; i < n; i++)
		अगर (res == list[i])
			वापस true;
	वापस false;
पूर्ण

अटल काष्ठा resource *to_resource(काष्ठा nvdimm_drvdata *ndd,
		काष्ठा nd_namespace_label *nd_label)
अणु
	काष्ठा resource *res;

	क्रम_each_dpa_resource(ndd, res) अणु
		अगर (res->start != __le64_to_cpu(nd_label->dpa))
			जारी;
		अगर (resource_size(res) != __le64_to_cpu(nd_label->rawsize))
			जारी;
		वापस res;
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * 1/ Account all the labels that can be मुक्तd after this update
 * 2/ Allocate and ग_लिखो the label to the staging (next) index
 * 3/ Record the resources in the namespace device
 */
अटल पूर्णांक __blk_label_update(काष्ठा nd_region *nd_region,
		काष्ठा nd_mapping *nd_mapping, काष्ठा nd_namespace_blk *nsblk,
		पूर्णांक num_labels)
अणु
	पूर्णांक i, alloc, victims, nमुक्त, old_num_resources, nlabel, rc = -ENXIO;
	काष्ठा nd_पूर्णांकerleave_set *nd_set = nd_region->nd_set;
	काष्ठा nd_namespace_common *ndns = &nsblk->common;
	काष्ठा nvdimm_drvdata *ndd = to_ndd(nd_mapping);
	काष्ठा nd_namespace_label *nd_label;
	काष्ठा nd_label_ent *label_ent, *e;
	काष्ठा nd_namespace_index *nsindex;
	अचिन्हित दीर्घ *मुक्त, *victim_map = शून्य;
	काष्ठा resource *res, **old_res_list;
	काष्ठा nd_label_id label_id;
	u8 uuid[NSLABEL_UUID_LEN];
	पूर्णांक min_dpa_idx = 0;
	LIST_HEAD(list);
	u32 nslot, slot;

	अगर (!preamble_next(ndd, &nsindex, &मुक्त, &nslot))
		वापस -ENXIO;

	old_res_list = nsblk->res;
	nमुक्त = nd_label_nमुक्त(ndd);
	old_num_resources = nsblk->num_resources;
	nd_label_gen_id(&label_id, nsblk->uuid, NSLABEL_FLAG_LOCAL);

	/*
	 * We need to loop over the old resources a few बार, which seems a
	 * bit inefficient, but we need to know that we have the label
	 * space beक्रमe we start mutating the tracking काष्ठाures.
	 * Otherwise the recovery method of last resort क्रम userspace is
	 * disable and re-enable the parent region.
	 */
	alloc = 0;
	क्रम_each_dpa_resource(ndd, res) अणु
		अगर (म_भेद(res->name, label_id.id) != 0)
			जारी;
		अगर (!is_old_resource(res, old_res_list, old_num_resources))
			alloc++;
	पूर्ण

	victims = 0;
	अगर (old_num_resources) अणु
		/* convert old local-label-map to dimm-slot victim-map */
		victim_map = biपंचांगap_zalloc(nslot, GFP_KERNEL);
		अगर (!victim_map)
			वापस -ENOMEM;

		/* mark unused labels क्रम garbage collection */
		क्रम_each_clear_bit_le(slot, मुक्त, nslot) अणु
			nd_label = to_label(ndd, slot);
			स_नकल(uuid, nd_label->uuid, NSLABEL_UUID_LEN);
			अगर (स_भेद(uuid, nsblk->uuid, NSLABEL_UUID_LEN) != 0)
				जारी;
			res = to_resource(ndd, nd_label);
			अगर (res && is_old_resource(res, old_res_list,
						old_num_resources))
				जारी;
			slot = to_slot(ndd, nd_label);
			set_bit(slot, victim_map);
			victims++;
		पूर्ण
	पूर्ण

	/* करोn't allow updates that consume the last label */
	अगर (nमुक्त - alloc < 0 || nमुक्त - alloc + victims < 1) अणु
		dev_info(&nsblk->common.dev, "insufficient label space\n");
		biपंचांगap_मुक्त(victim_map);
		वापस -ENOSPC;
	पूर्ण
	/* from here on we need to पात on error */


	/* assign all resources to the namespace beक्रमe writing the labels */
	nsblk->res = शून्य;
	nsblk->num_resources = 0;
	क्रम_each_dpa_resource(ndd, res) अणु
		अगर (म_भेद(res->name, label_id.id) != 0)
			जारी;
		अगर (!nsblk_add_resource(nd_region, ndd, nsblk, res->start)) अणु
			rc = -ENOMEM;
			जाओ पात;
		पूर्ण
	पूर्ण

	/* release slots associated with any invalidated UUIDs */
	mutex_lock(&nd_mapping->lock);
	list_क्रम_each_entry_safe(label_ent, e, &nd_mapping->labels, list)
		अगर (test_and_clear_bit(ND_LABEL_REAP, &label_ent->flags)) अणु
			reap_victim(nd_mapping, label_ent);
			list_move(&label_ent->list, &list);
		पूर्ण
	mutex_unlock(&nd_mapping->lock);

	/*
	 * Find the resource associated with the first label in the set
	 * per the v1.2 namespace specअगरication.
	 */
	क्रम (i = 0; i < nsblk->num_resources; i++) अणु
		काष्ठा resource *min = nsblk->res[min_dpa_idx];

		res = nsblk->res[i];
		अगर (res->start < min->start)
			min_dpa_idx = i;
	पूर्ण

	क्रम (i = 0; i < nsblk->num_resources; i++) अणु
		माप_प्रकार offset;

		res = nsblk->res[i];
		अगर (is_old_resource(res, old_res_list, old_num_resources))
			जारी; /* carry-over */
		slot = nd_label_alloc_slot(ndd);
		अगर (slot == अच_पूर्णांक_उच्च) अणु
			rc = -ENXIO;
			जाओ पात;
		पूर्ण
		dev_dbg(ndd->dev, "allocated: %d\n", slot);

		nd_label = to_label(ndd, slot);
		स_रखो(nd_label, 0, माप_namespace_label(ndd));
		स_नकल(nd_label->uuid, nsblk->uuid, NSLABEL_UUID_LEN);
		अगर (nsblk->alt_name)
			स_नकल(nd_label->name, nsblk->alt_name,
					NSLABEL_NAME_LEN);
		nd_label->flags = __cpu_to_le32(NSLABEL_FLAG_LOCAL);

		/*
		 * Use the presence of the type_guid as a flag to
		 * determine isetcookie usage and nlabel + position
		 * policy क्रम blk-aperture namespaces.
		 */
		अगर (namespace_label_has(ndd, type_guid)) अणु
			अगर (i == min_dpa_idx) अणु
				nd_label->nlabel = __cpu_to_le16(nsblk->num_resources);
				nd_label->position = __cpu_to_le16(0);
			पूर्ण अन्यथा अणु
				nd_label->nlabel = __cpu_to_le16(0xffff);
				nd_label->position = __cpu_to_le16(0xffff);
			पूर्ण
			nd_label->isetcookie = __cpu_to_le64(nd_set->cookie2);
		पूर्ण अन्यथा अणु
			nd_label->nlabel = __cpu_to_le16(0); /* N/A */
			nd_label->position = __cpu_to_le16(0); /* N/A */
			nd_label->isetcookie = __cpu_to_le64(0); /* N/A */
		पूर्ण

		nd_label->dpa = __cpu_to_le64(res->start);
		nd_label->rawsize = __cpu_to_le64(resource_size(res));
		nd_label->lbasize = __cpu_to_le64(nsblk->lbasize);
		nd_label->slot = __cpu_to_le32(slot);
		अगर (namespace_label_has(ndd, type_guid))
			guid_copy(&nd_label->type_guid, &nd_set->type_guid);
		अगर (namespace_label_has(ndd, असलtraction_guid))
			guid_copy(&nd_label->असलtraction_guid,
					to_असलtraction_guid(ndns->claim_class,
						&nd_label->असलtraction_guid));

		अगर (namespace_label_has(ndd, checksum)) अणु
			u64 sum;

			nd_label->checksum = __cpu_to_le64(0);
			sum = nd_fletcher64(nd_label,
					माप_namespace_label(ndd), 1);
			nd_label->checksum = __cpu_to_le64(sum);
		पूर्ण

		/* update label */
		offset = nd_label_offset(ndd, nd_label);
		rc = nvdimm_set_config_data(ndd, offset, nd_label,
				माप_namespace_label(ndd));
		अगर (rc < 0)
			जाओ पात;
	पूर्ण

	/* मुक्त up now unused slots in the new index */
	क्रम_each_set_bit(slot, victim_map, victim_map ? nslot : 0) अणु
		dev_dbg(ndd->dev, "free: %d\n", slot);
		nd_label_मुक्त_slot(ndd, slot);
	पूर्ण

	/* update index */
	rc = nd_label_ग_लिखो_index(ndd, ndd->ns_next,
			nd_inc_seq(__le32_to_cpu(nsindex->seq)), 0);
	अगर (rc)
		जाओ पात;

	/*
	 * Now that the on-dimm labels are up to date, fix up the tracking
	 * entries in nd_mapping->labels
	 */
	nlabel = 0;
	mutex_lock(&nd_mapping->lock);
	list_क्रम_each_entry_safe(label_ent, e, &nd_mapping->labels, list) अणु
		nd_label = label_ent->label;
		अगर (!nd_label)
			जारी;
		nlabel++;
		स_नकल(uuid, nd_label->uuid, NSLABEL_UUID_LEN);
		अगर (स_भेद(uuid, nsblk->uuid, NSLABEL_UUID_LEN) != 0)
			जारी;
		nlabel--;
		list_move(&label_ent->list, &list);
		label_ent->label = शून्य;
	पूर्ण
	list_splice_tail_init(&list, &nd_mapping->labels);
	mutex_unlock(&nd_mapping->lock);

	अगर (nlabel + nsblk->num_resources > num_labels) अणु
		/*
		 * Bug, we can't end up with more resources than
		 * available labels
		 */
		WARN_ON_ONCE(1);
		rc = -ENXIO;
		जाओ out;
	पूर्ण

	mutex_lock(&nd_mapping->lock);
	label_ent = list_first_entry_or_null(&nd_mapping->labels,
			typeof(*label_ent), list);
	अगर (!label_ent) अणु
		WARN_ON(1);
		mutex_unlock(&nd_mapping->lock);
		rc = -ENXIO;
		जाओ out;
	पूर्ण
	क्रम_each_clear_bit_le(slot, मुक्त, nslot) अणु
		nd_label = to_label(ndd, slot);
		स_नकल(uuid, nd_label->uuid, NSLABEL_UUID_LEN);
		अगर (स_भेद(uuid, nsblk->uuid, NSLABEL_UUID_LEN) != 0)
			जारी;
		res = to_resource(ndd, nd_label);
		res->flags &= ~DPA_RESOURCE_ADJUSTED;
		dev_vdbg(&nsblk->common.dev, "assign label slot: %d\n", slot);
		list_क्रम_each_entry_from(label_ent, &nd_mapping->labels, list) अणु
			अगर (label_ent->label)
				जारी;
			label_ent->label = nd_label;
			nd_label = शून्य;
			अवरोध;
		पूर्ण
		अगर (nd_label)
			dev_WARN(&nsblk->common.dev,
					"failed to track label slot%d\n", slot);
	पूर्ण
	mutex_unlock(&nd_mapping->lock);

 out:
	kमुक्त(old_res_list);
	biपंचांगap_मुक्त(victim_map);
	वापस rc;

 पात:
	/*
	 * 1/ repair the allocated label biपंचांगap in the index
	 * 2/ restore the resource list
	 */
	nd_label_copy(ndd, nsindex, to_current_namespace_index(ndd));
	kमुक्त(nsblk->res);
	nsblk->res = old_res_list;
	nsblk->num_resources = old_num_resources;
	old_res_list = शून्य;
	जाओ out;
पूर्ण

अटल पूर्णांक init_labels(काष्ठा nd_mapping *nd_mapping, पूर्णांक num_labels)
अणु
	पूर्णांक i, old_num_labels = 0;
	काष्ठा nd_label_ent *label_ent;
	काष्ठा nd_namespace_index *nsindex;
	काष्ठा nvdimm_drvdata *ndd = to_ndd(nd_mapping);

	mutex_lock(&nd_mapping->lock);
	list_क्रम_each_entry(label_ent, &nd_mapping->labels, list)
		old_num_labels++;
	mutex_unlock(&nd_mapping->lock);

	/*
	 * We need to preserve all the old labels क्रम the mapping so
	 * they can be garbage collected after writing the new labels.
	 */
	क्रम (i = old_num_labels; i < num_labels; i++) अणु
		label_ent = kzalloc(माप(*label_ent), GFP_KERNEL);
		अगर (!label_ent)
			वापस -ENOMEM;
		mutex_lock(&nd_mapping->lock);
		list_add_tail(&label_ent->list, &nd_mapping->labels);
		mutex_unlock(&nd_mapping->lock);
	पूर्ण

	अगर (ndd->ns_current == -1 || ndd->ns_next == -1)
		/* pass */;
	अन्यथा
		वापस max(num_labels, old_num_labels);

	nsindex = to_namespace_index(ndd, 0);
	स_रखो(nsindex, 0, ndd->nsarea.config_size);
	क्रम (i = 0; i < 2; i++) अणु
		पूर्णांक rc = nd_label_ग_लिखो_index(ndd, i, 3 - i, ND_NSINDEX_INIT);

		अगर (rc)
			वापस rc;
	पूर्ण
	ndd->ns_next = 1;
	ndd->ns_current = 0;

	वापस max(num_labels, old_num_labels);
पूर्ण

अटल पूर्णांक del_labels(काष्ठा nd_mapping *nd_mapping, u8 *uuid)
अणु
	काष्ठा nvdimm_drvdata *ndd = to_ndd(nd_mapping);
	काष्ठा nd_label_ent *label_ent, *e;
	काष्ठा nd_namespace_index *nsindex;
	u8 label_uuid[NSLABEL_UUID_LEN];
	अचिन्हित दीर्घ *मुक्त;
	LIST_HEAD(list);
	u32 nslot, slot;
	पूर्णांक active = 0;

	अगर (!uuid)
		वापस 0;

	/* no index || no labels == nothing to delete */
	अगर (!preamble_next(ndd, &nsindex, &मुक्त, &nslot))
		वापस 0;

	mutex_lock(&nd_mapping->lock);
	list_क्रम_each_entry_safe(label_ent, e, &nd_mapping->labels, list) अणु
		काष्ठा nd_namespace_label *nd_label = label_ent->label;

		अगर (!nd_label)
			जारी;
		active++;
		स_नकल(label_uuid, nd_label->uuid, NSLABEL_UUID_LEN);
		अगर (स_भेद(label_uuid, uuid, NSLABEL_UUID_LEN) != 0)
			जारी;
		active--;
		slot = to_slot(ndd, nd_label);
		nd_label_मुक्त_slot(ndd, slot);
		dev_dbg(ndd->dev, "free: %d\n", slot);
		list_move_tail(&label_ent->list, &list);
		label_ent->label = शून्य;
	पूर्ण
	list_splice_tail_init(&list, &nd_mapping->labels);

	अगर (active == 0) अणु
		nd_mapping_मुक्त_labels(nd_mapping);
		dev_dbg(ndd->dev, "no more active labels\n");
	पूर्ण
	mutex_unlock(&nd_mapping->lock);

	वापस nd_label_ग_लिखो_index(ndd, ndd->ns_next,
			nd_inc_seq(__le32_to_cpu(nsindex->seq)), 0);
पूर्ण

पूर्णांक nd_pmem_namespace_label_update(काष्ठा nd_region *nd_region,
		काष्ठा nd_namespace_pmem *nspm, resource_माप_प्रकार size)
अणु
	पूर्णांक i, rc;

	क्रम (i = 0; i < nd_region->ndr_mappings; i++) अणु
		काष्ठा nd_mapping *nd_mapping = &nd_region->mapping[i];
		काष्ठा nvdimm_drvdata *ndd = to_ndd(nd_mapping);
		काष्ठा resource *res;
		पूर्णांक count = 0;

		अगर (size == 0) अणु
			rc = del_labels(nd_mapping, nspm->uuid);
			अगर (rc)
				वापस rc;
			जारी;
		पूर्ण

		क्रम_each_dpa_resource(ndd, res)
			अगर (म_भेदन(res->name, "pmem", 4) == 0)
				count++;
		WARN_ON_ONCE(!count);

		rc = init_labels(nd_mapping, count);
		अगर (rc < 0)
			वापस rc;

		rc = __pmem_label_update(nd_region, nd_mapping, nspm, i,
				NSLABEL_FLAG_UPDATING);
		अगर (rc)
			वापस rc;
	पूर्ण

	अगर (size == 0)
		वापस 0;

	/* Clear the UPDATING flag per UEFI 2.7 expectations */
	क्रम (i = 0; i < nd_region->ndr_mappings; i++) अणु
		काष्ठा nd_mapping *nd_mapping = &nd_region->mapping[i];

		rc = __pmem_label_update(nd_region, nd_mapping, nspm, i, 0);
		अगर (rc)
			वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक nd_blk_namespace_label_update(काष्ठा nd_region *nd_region,
		काष्ठा nd_namespace_blk *nsblk, resource_माप_प्रकार size)
अणु
	काष्ठा nd_mapping *nd_mapping = &nd_region->mapping[0];
	काष्ठा resource *res;
	पूर्णांक count = 0;

	अगर (size == 0)
		वापस del_labels(nd_mapping, nsblk->uuid);

	क्रम_each_dpa_resource(to_ndd(nd_mapping), res)
		count++;

	count = init_labels(nd_mapping, count);
	अगर (count < 0)
		वापस count;

	वापस __blk_label_update(nd_region, nd_mapping, nsblk, count);
पूर्ण

पूर्णांक __init nd_label_init(व्योम)
अणु
	WARN_ON(guid_parse(NVDIMM_BTT_GUID, &nvdimm_btt_guid));
	WARN_ON(guid_parse(NVDIMM_BTT2_GUID, &nvdimm_btt2_guid));
	WARN_ON(guid_parse(NVDIMM_PFN_GUID, &nvdimm_pfn_guid));
	WARN_ON(guid_parse(NVDIMM_DAX_GUID, &nvdimm_dax_guid));

	वापस 0;
पूर्ण
