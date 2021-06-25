<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * channel program पूर्णांकerfaces
 *
 * Copyright IBM Corp. 2017
 *
 * Author(s): Dong Jia Shi <bjsdjshi@linux.vnet.ibm.com>
 *            Xiao Feng Ren <renxiaof@linux.vnet.ibm.com>
 */

#समावेश <linux/ratelimit.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/iommu.h>
#समावेश <linux/vfपन.स>
#समावेश <यंत्र/idals.h>

#समावेश "vfio_ccw_cp.h"

काष्ठा pfn_array अणु
	/* Starting guest physical I/O address. */
	अचिन्हित दीर्घ		pa_iova;
	/* Array that stores PFNs of the pages need to pin. */
	अचिन्हित दीर्घ		*pa_iova_pfn;
	/* Array that receives PFNs of the pages pinned. */
	अचिन्हित दीर्घ		*pa_pfn;
	/* Number of pages pinned from @pa_iova. */
	पूर्णांक			pa_nr;
पूर्ण;

काष्ठा ccwchain अणु
	काष्ठा list_head	next;
	काष्ठा ccw1		*ch_ccw;
	/* Guest physical address of the current chain. */
	u64			ch_iova;
	/* Count of the valid ccws in chain. */
	पूर्णांक			ch_len;
	/* Pinned PAGEs क्रम the original data. */
	काष्ठा pfn_array	*ch_pa;
पूर्ण;

/*
 * pfn_array_alloc() - alloc memory क्रम PFNs
 * @pa: pfn_array on which to perक्रमm the operation
 * @iova: target guest physical address
 * @len: number of bytes that should be pinned from @iova
 *
 * Attempt to allocate memory क्रम PFNs.
 *
 * Usage of pfn_array:
 * We expect (pa_nr == 0) and (pa_iova_pfn == शून्य), any field in
 * this काष्ठाure will be filled in by this function.
 *
 * Returns:
 *         0 अगर PFNs are allocated
 *   -EINVAL अगर pa->pa_nr is not initially zero, or pa->pa_iova_pfn is not शून्य
 *   -ENOMEM अगर alloc failed
 */
अटल पूर्णांक pfn_array_alloc(काष्ठा pfn_array *pa, u64 iova, अचिन्हित पूर्णांक len)
अणु
	पूर्णांक i;

	अगर (pa->pa_nr || pa->pa_iova_pfn)
		वापस -EINVAL;

	pa->pa_iova = iova;

	pa->pa_nr = ((iova & ~PAGE_MASK) + len + (PAGE_SIZE - 1)) >> PAGE_SHIFT;
	अगर (!pa->pa_nr)
		वापस -EINVAL;

	pa->pa_iova_pfn = kसुस्मृति(pa->pa_nr,
				  माप(*pa->pa_iova_pfn) +
				  माप(*pa->pa_pfn),
				  GFP_KERNEL);
	अगर (unlikely(!pa->pa_iova_pfn)) अणु
		pa->pa_nr = 0;
		वापस -ENOMEM;
	पूर्ण
	pa->pa_pfn = pa->pa_iova_pfn + pa->pa_nr;

	pa->pa_iova_pfn[0] = pa->pa_iova >> PAGE_SHIFT;
	pa->pa_pfn[0] = -1ULL;
	क्रम (i = 1; i < pa->pa_nr; i++) अणु
		pa->pa_iova_pfn[i] = pa->pa_iova_pfn[i - 1] + 1;
		pa->pa_pfn[i] = -1ULL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * pfn_array_pin() - Pin user pages in memory
 * @pa: pfn_array on which to perक्रमm the operation
 * @mdev: the mediated device to perक्रमm pin operations
 *
 * Returns number of pages pinned upon success.
 * If the pin request partially succeeds, or fails completely,
 * all pages are left unpinned and a negative error value is वापसed.
 */
अटल पूर्णांक pfn_array_pin(काष्ठा pfn_array *pa, काष्ठा device *mdev)
अणु
	पूर्णांक ret = 0;

	ret = vfio_pin_pages(mdev, pa->pa_iova_pfn, pa->pa_nr,
			     IOMMU_READ | IOMMU_WRITE, pa->pa_pfn);

	अगर (ret < 0) अणु
		जाओ err_out;
	पूर्ण अन्यथा अगर (ret > 0 && ret != pa->pa_nr) अणु
		vfio_unpin_pages(mdev, pa->pa_iova_pfn, ret);
		ret = -EINVAL;
		जाओ err_out;
	पूर्ण

	वापस ret;

err_out:
	pa->pa_nr = 0;

	वापस ret;
पूर्ण

/* Unpin the pages beक्रमe releasing the memory. */
अटल व्योम pfn_array_unpin_मुक्त(काष्ठा pfn_array *pa, काष्ठा device *mdev)
अणु
	/* Only unpin अगर any pages were pinned to begin with */
	अगर (pa->pa_nr)
		vfio_unpin_pages(mdev, pa->pa_iova_pfn, pa->pa_nr);
	pa->pa_nr = 0;
	kमुक्त(pa->pa_iova_pfn);
पूर्ण

अटल bool pfn_array_iova_pinned(काष्ठा pfn_array *pa, अचिन्हित दीर्घ iova)
अणु
	अचिन्हित दीर्घ iova_pfn = iova >> PAGE_SHIFT;
	पूर्णांक i;

	क्रम (i = 0; i < pa->pa_nr; i++)
		अगर (pa->pa_iova_pfn[i] == iova_pfn)
			वापस true;

	वापस false;
पूर्ण
/* Create the list of IDAL words क्रम a pfn_array. */
अटल अंतरभूत व्योम pfn_array_idal_create_words(
	काष्ठा pfn_array *pa,
	अचिन्हित दीर्घ *idaws)
अणु
	पूर्णांक i;

	/*
	 * Idal words (execept the first one) rely on the memory being 4k
	 * aligned. If a user भव address is 4K aligned, then it's
	 * corresponding kernel physical address will also be 4K aligned. Thus
	 * there will be no problem here to simply use the phys to create an
	 * idaw.
	 */

	क्रम (i = 0; i < pa->pa_nr; i++)
		idaws[i] = pa->pa_pfn[i] << PAGE_SHIFT;

	/* Adjust the first IDAW, since it may not start on a page boundary */
	idaws[0] += pa->pa_iova & (PAGE_SIZE - 1);
पूर्ण

अटल व्योम convert_ccw0_to_ccw1(काष्ठा ccw1 *source, अचिन्हित दीर्घ len)
अणु
	काष्ठा ccw0 ccw0;
	काष्ठा ccw1 *pccw1 = source;
	पूर्णांक i;

	क्रम (i = 0; i < len; i++) अणु
		ccw0 = *(काष्ठा ccw0 *)pccw1;
		अगर ((pccw1->cmd_code & 0x0f) == CCW_CMD_TIC) अणु
			pccw1->cmd_code = CCW_CMD_TIC;
			pccw1->flags = 0;
			pccw1->count = 0;
		पूर्ण अन्यथा अणु
			pccw1->cmd_code = ccw0.cmd_code;
			pccw1->flags = ccw0.flags;
			pccw1->count = ccw0.count;
		पूर्ण
		pccw1->cda = ccw0.cda;
		pccw1++;
	पूर्ण
पूर्ण

/*
 * Within the करोमुख्य (@mdev), copy @n bytes from a guest physical
 * address (@iova) to a host physical address (@to).
 */
अटल दीर्घ copy_from_iova(काष्ठा device *mdev,
			   व्योम *to, u64 iova,
			   अचिन्हित दीर्घ n)
अणु
	काष्ठा pfn_array pa = अणु0पूर्ण;
	u64 from;
	पूर्णांक i, ret;
	अचिन्हित दीर्घ l, m;

	ret = pfn_array_alloc(&pa, iova, n);
	अगर (ret < 0)
		वापस ret;

	ret = pfn_array_pin(&pa, mdev);
	अगर (ret < 0) अणु
		pfn_array_unpin_मुक्त(&pa, mdev);
		वापस ret;
	पूर्ण

	l = n;
	क्रम (i = 0; i < pa.pa_nr; i++) अणु
		from = pa.pa_pfn[i] << PAGE_SHIFT;
		m = PAGE_SIZE;
		अगर (i == 0) अणु
			from += iova & (PAGE_SIZE - 1);
			m -= iova & (PAGE_SIZE - 1);
		पूर्ण

		m = min(l, m);
		स_नकल(to + (n - l), (व्योम *)from, m);

		l -= m;
		अगर (l == 0)
			अवरोध;
	पूर्ण

	pfn_array_unpin_मुक्त(&pa, mdev);

	वापस l;
पूर्ण

/*
 * Helpers to operate ccwchain.
 */
#घोषणा ccw_is_पढ़ो(_ccw) (((_ccw)->cmd_code & 0x03) == 0x02)
#घोषणा ccw_is_पढ़ो_backward(_ccw) (((_ccw)->cmd_code & 0x0F) == 0x0C)
#घोषणा ccw_is_sense(_ccw) (((_ccw)->cmd_code & 0x0F) == CCW_CMD_BASIC_SENSE)

#घोषणा ccw_is_noop(_ccw) ((_ccw)->cmd_code == CCW_CMD_NOOP)

#घोषणा ccw_is_tic(_ccw) ((_ccw)->cmd_code == CCW_CMD_TIC)

#घोषणा ccw_is_idal(_ccw) ((_ccw)->flags & CCW_FLAG_IDA)
#घोषणा ccw_is_skip(_ccw) ((_ccw)->flags & CCW_FLAG_SKIP)

#घोषणा ccw_is_chain(_ccw) ((_ccw)->flags & (CCW_FLAG_CC | CCW_FLAG_DC))

/*
 * ccw_करोes_data_transfer()
 *
 * Determine whether a CCW will move any data, such that the guest pages
 * would need to be pinned beक्रमe perक्रमming the I/O.
 *
 * Returns 1 अगर yes, 0 अगर no.
 */
अटल अंतरभूत पूर्णांक ccw_करोes_data_transfer(काष्ठा ccw1 *ccw)
अणु
	/* If the count field is zero, then no data will be transferred */
	अगर (ccw->count == 0)
		वापस 0;

	/* If the command is a NOP, then no data will be transferred */
	अगर (ccw_is_noop(ccw))
		वापस 0;

	/* If the skip flag is off, then data will be transferred */
	अगर (!ccw_is_skip(ccw))
		वापस 1;

	/*
	 * If the skip flag is on, it is only meaningful अगर the command
	 * code is a पढ़ो, पढ़ो backward, sense, or sense ID.  In those
	 * हालs, no data will be transferred.
	 */
	अगर (ccw_is_पढ़ो(ccw) || ccw_is_पढ़ो_backward(ccw))
		वापस 0;

	अगर (ccw_is_sense(ccw))
		वापस 0;

	/* The skip flag is on, but it is ignored क्रम this command code. */
	वापस 1;
पूर्ण

/*
 * is_cpa_within_range()
 *
 * @cpa: channel program address being questioned
 * @head: address of the beginning of a CCW chain
 * @len: number of CCWs within the chain
 *
 * Determine whether the address of a CCW (whether a new chain,
 * or the target of a TIC) falls within a range (including the end poपूर्णांकs).
 *
 * Returns 1 अगर yes, 0 अगर no.
 */
अटल अंतरभूत पूर्णांक is_cpa_within_range(u32 cpa, u32 head, पूर्णांक len)
अणु
	u32 tail = head + (len - 1) * माप(काष्ठा ccw1);

	वापस (head <= cpa && cpa <= tail);
पूर्ण

अटल अंतरभूत पूर्णांक is_tic_within_range(काष्ठा ccw1 *ccw, u32 head, पूर्णांक len)
अणु
	अगर (!ccw_is_tic(ccw))
		वापस 0;

	वापस is_cpa_within_range(ccw->cda, head, len);
पूर्ण

अटल काष्ठा ccwchain *ccwchain_alloc(काष्ठा channel_program *cp, पूर्णांक len)
अणु
	काष्ठा ccwchain *chain;
	व्योम *data;
	माप_प्रकार size;

	/* Make ccw address aligned to 8. */
	size = ((माप(*chain) + 7L) & -8L) +
		माप(*chain->ch_ccw) * len +
		माप(*chain->ch_pa) * len;
	chain = kzalloc(size, GFP_DMA | GFP_KERNEL);
	अगर (!chain)
		वापस शून्य;

	data = (u8 *)chain + ((माप(*chain) + 7L) & -8L);
	chain->ch_ccw = (काष्ठा ccw1 *)data;

	data = (u8 *)(chain->ch_ccw) + माप(*chain->ch_ccw) * len;
	chain->ch_pa = (काष्ठा pfn_array *)data;

	chain->ch_len = len;

	list_add_tail(&chain->next, &cp->ccwchain_list);

	वापस chain;
पूर्ण

अटल व्योम ccwchain_मुक्त(काष्ठा ccwchain *chain)
अणु
	list_del(&chain->next);
	kमुक्त(chain);
पूर्ण

/* Free resource क्रम a ccw that allocated memory क्रम its cda. */
अटल व्योम ccwchain_cda_मुक्त(काष्ठा ccwchain *chain, पूर्णांक idx)
अणु
	काष्ठा ccw1 *ccw = chain->ch_ccw + idx;

	अगर (ccw_is_tic(ccw))
		वापस;

	kमुक्त((व्योम *)(u64)ccw->cda);
पूर्ण

/**
 * ccwchain_calc_length - calculate the length of the ccw chain.
 * @iova: guest physical address of the target ccw chain
 * @cp: channel_program on which to perक्रमm the operation
 *
 * This is the chain length not considering any TICs.
 * You need to करो a new round क्रम each TIC target.
 *
 * The program is also validated क्रम असलence of not yet supported
 * indirect data addressing scenarios.
 *
 * Returns: the length of the ccw chain or -त्रुटि_सं.
 */
अटल पूर्णांक ccwchain_calc_length(u64 iova, काष्ठा channel_program *cp)
अणु
	काष्ठा ccw1 *ccw = cp->guest_cp;
	पूर्णांक cnt = 0;

	करो अणु
		cnt++;

		/*
		 * As we करोn't want to fail direct addressing even अगर the
		 * orb specअगरied one of the unsupported क्रमmats, we defer
		 * checking क्रम IDAWs in unsupported क्रमmats to here.
		 */
		अगर ((!cp->orb.cmd.c64 || cp->orb.cmd.i2k) && ccw_is_idal(ccw))
			वापस -EOPNOTSUPP;

		/*
		 * We want to keep counting अगर the current CCW has the
		 * command-chaining flag enabled, or अगर it is a TIC CCW
		 * that loops back पूर्णांकo the current chain.  The latter
		 * is used क्रम device orientation, where the CCW PRIOR to
		 * the TIC can either jump to the TIC or a CCW immediately
		 * after the TIC, depending on the results of its operation.
		 */
		अगर (!ccw_is_chain(ccw) && !is_tic_within_range(ccw, iova, cnt))
			अवरोध;

		ccw++;
	पूर्ण जबतक (cnt < CCWCHAIN_LEN_MAX + 1);

	अगर (cnt == CCWCHAIN_LEN_MAX + 1)
		cnt = -EINVAL;

	वापस cnt;
पूर्ण

अटल पूर्णांक tic_target_chain_exists(काष्ठा ccw1 *tic, काष्ठा channel_program *cp)
अणु
	काष्ठा ccwchain *chain;
	u32 ccw_head;

	list_क्रम_each_entry(chain, &cp->ccwchain_list, next) अणु
		ccw_head = chain->ch_iova;
		अगर (is_cpa_within_range(tic->cda, ccw_head, chain->ch_len))
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ccwchain_loop_tic(काष्ठा ccwchain *chain,
			     काष्ठा channel_program *cp);

अटल पूर्णांक ccwchain_handle_ccw(u32 cda, काष्ठा channel_program *cp)
अणु
	काष्ठा ccwchain *chain;
	पूर्णांक len, ret;

	/* Copy 2K (the most we support today) of possible CCWs */
	len = copy_from_iova(cp->mdev, cp->guest_cp, cda,
			     CCWCHAIN_LEN_MAX * माप(काष्ठा ccw1));
	अगर (len)
		वापस len;

	/* Convert any Format-0 CCWs to Format-1 */
	अगर (!cp->orb.cmd.fmt)
		convert_ccw0_to_ccw1(cp->guest_cp, CCWCHAIN_LEN_MAX);

	/* Count the CCWs in the current chain */
	len = ccwchain_calc_length(cda, cp);
	अगर (len < 0)
		वापस len;

	/* Need alloc a new chain क्रम this one. */
	chain = ccwchain_alloc(cp, len);
	अगर (!chain)
		वापस -ENOMEM;
	chain->ch_iova = cda;

	/* Copy the actual CCWs पूर्णांकo the new chain */
	स_नकल(chain->ch_ccw, cp->guest_cp, len * माप(काष्ठा ccw1));

	/* Loop क्रम tics on this new chain. */
	ret = ccwchain_loop_tic(chain, cp);

	अगर (ret)
		ccwchain_मुक्त(chain);

	वापस ret;
पूर्ण

/* Loop क्रम TICs. */
अटल पूर्णांक ccwchain_loop_tic(काष्ठा ccwchain *chain, काष्ठा channel_program *cp)
अणु
	काष्ठा ccw1 *tic;
	पूर्णांक i, ret;

	क्रम (i = 0; i < chain->ch_len; i++) अणु
		tic = chain->ch_ccw + i;

		अगर (!ccw_is_tic(tic))
			जारी;

		/* May transfer to an existing chain. */
		अगर (tic_target_chain_exists(tic, cp))
			जारी;

		/* Build a ccwchain क्रम the next segment */
		ret = ccwchain_handle_ccw(tic->cda, cp);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ccwchain_fetch_tic(काष्ठा ccwchain *chain,
			      पूर्णांक idx,
			      काष्ठा channel_program *cp)
अणु
	काष्ठा ccw1 *ccw = chain->ch_ccw + idx;
	काष्ठा ccwchain *iter;
	u32 ccw_head;

	list_क्रम_each_entry(iter, &cp->ccwchain_list, next) अणु
		ccw_head = iter->ch_iova;
		अगर (is_cpa_within_range(ccw->cda, ccw_head, iter->ch_len)) अणु
			ccw->cda = (__u32) (addr_t) (((अक्षर *)iter->ch_ccw) +
						     (ccw->cda - ccw_head));
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EFAULT;
पूर्ण

अटल पूर्णांक ccwchain_fetch_direct(काष्ठा ccwchain *chain,
				 पूर्णांक idx,
				 काष्ठा channel_program *cp)
अणु
	काष्ठा ccw1 *ccw;
	काष्ठा pfn_array *pa;
	u64 iova;
	अचिन्हित दीर्घ *idaws;
	पूर्णांक ret;
	पूर्णांक bytes = 1;
	पूर्णांक idaw_nr, idal_len;
	पूर्णांक i;

	ccw = chain->ch_ccw + idx;

	अगर (ccw->count)
		bytes = ccw->count;

	/* Calculate size of IDAL */
	अगर (ccw_is_idal(ccw)) अणु
		/* Read first IDAW to see अगर it's 4K-aligned or not. */
		/* All subsequent IDAws will be 4K-aligned. */
		ret = copy_from_iova(cp->mdev, &iova, ccw->cda, माप(iova));
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		iova = ccw->cda;
	पूर्ण
	idaw_nr = idal_nr_words((व्योम *)iova, bytes);
	idal_len = idaw_nr * माप(*idaws);

	/* Allocate an IDAL from host storage */
	idaws = kसुस्मृति(idaw_nr, माप(*idaws), GFP_DMA | GFP_KERNEL);
	अगर (!idaws) अणु
		ret = -ENOMEM;
		जाओ out_init;
	पूर्ण

	/*
	 * Allocate an array of pfn's क्रम pages to pin/translate.
	 * The number of pages is actually the count of the idaws
	 * required क्रम the data transfer, since we only only support
	 * 4K IDAWs today.
	 */
	pa = chain->ch_pa + idx;
	ret = pfn_array_alloc(pa, iova, bytes);
	अगर (ret < 0)
		जाओ out_मुक्त_idaws;

	अगर (ccw_is_idal(ccw)) अणु
		/* Copy guest IDAL पूर्णांकo host IDAL */
		ret = copy_from_iova(cp->mdev, idaws, ccw->cda, idal_len);
		अगर (ret)
			जाओ out_unpin;

		/*
		 * Copy guest IDAWs पूर्णांकo pfn_array, in हाल the memory they
		 * occupy is not contiguous.
		 */
		क्रम (i = 0; i < idaw_nr; i++)
			pa->pa_iova_pfn[i] = idaws[i] >> PAGE_SHIFT;
	पूर्ण अन्यथा अणु
		/*
		 * No action is required here; the iova addresses in pfn_array
		 * were initialized sequentially in pfn_array_alloc() beginning
		 * with the contents of ccw->cda.
		 */
	पूर्ण

	अगर (ccw_करोes_data_transfer(ccw)) अणु
		ret = pfn_array_pin(pa, cp->mdev);
		अगर (ret < 0)
			जाओ out_unpin;
	पूर्ण अन्यथा अणु
		pa->pa_nr = 0;
	पूर्ण

	ccw->cda = (__u32) virt_to_phys(idaws);
	ccw->flags |= CCW_FLAG_IDA;

	/* Populate the IDAL with pinned/translated addresses from pfn */
	pfn_array_idal_create_words(pa, idaws);

	वापस 0;

out_unpin:
	pfn_array_unpin_मुक्त(pa, cp->mdev);
out_मुक्त_idaws:
	kमुक्त(idaws);
out_init:
	ccw->cda = 0;
	वापस ret;
पूर्ण

/*
 * Fetch one ccw.
 * To reduce memory copy, we'll pin the cda page in memory,
 * and to get rid of the cda 2G limitiaion of ccw1, we'll translate
 * direct ccws to idal ccws.
 */
अटल पूर्णांक ccwchain_fetch_one(काष्ठा ccwchain *chain,
			      पूर्णांक idx,
			      काष्ठा channel_program *cp)
अणु
	काष्ठा ccw1 *ccw = chain->ch_ccw + idx;

	अगर (ccw_is_tic(ccw))
		वापस ccwchain_fetch_tic(chain, idx, cp);

	वापस ccwchain_fetch_direct(chain, idx, cp);
पूर्ण

/**
 * cp_init() - allocate ccwchains क्रम a channel program.
 * @cp: channel_program on which to perक्रमm the operation
 * @mdev: the mediated device to perक्रमm pin/unpin operations
 * @orb: control block क्रम the channel program from the guest
 *
 * This creates one or more ccwchain(s), and copies the raw data of
 * the target channel program from @orb->cmd.iova to the new ccwchain(s).
 *
 * Limitations:
 * 1. Supports idal(c64) ccw chaining.
 * 2. Supports 4k idaw.
 *
 * Returns:
 *   %0 on success and a negative error value on failure.
 */
पूर्णांक cp_init(काष्ठा channel_program *cp, काष्ठा device *mdev, जोड़ orb *orb)
अणु
	/* custom ratelimit used to aव्योम flood during guest IPL */
	अटल DEFINE_RATELIMIT_STATE(ratelimit_state, 5 * HZ, 1);
	पूर्णांक ret;

	/* this is an error in the caller */
	अगर (cp->initialized)
		वापस -EBUSY;

	/*
	 * We only support prefetching the channel program. We assume all channel
	 * programs executed by supported guests likewise support prefetching.
	 * Executing a channel program that करोes not specअगरy prefetching will
	 * typically not cause an error, but a warning is issued to help identअगरy
	 * the problem अगर something करोes अवरोध.
	 */
	अगर (!orb->cmd.pfch && __ratelimit(&ratelimit_state))
		dev_warn(mdev, "Prefetching channel program even though prefetch not specified in ORB");

	INIT_LIST_HEAD(&cp->ccwchain_list);
	स_नकल(&cp->orb, orb, माप(*orb));
	cp->mdev = mdev;

	/* Build a ccwchain क्रम the first CCW segment */
	ret = ccwchain_handle_ccw(orb->cmd.cpa, cp);

	अगर (!ret) अणु
		cp->initialized = true;

		/* It is safe to क्रमce: अगर it was not set but idals used
		 * ccwchain_calc_length would have वापसed an error.
		 */
		cp->orb.cmd.c64 = 1;
	पूर्ण

	वापस ret;
पूर्ण


/**
 * cp_मुक्त() - मुक्त resources क्रम channel program.
 * @cp: channel_program on which to perक्रमm the operation
 *
 * This unpins the memory pages and मुक्तs the memory space occupied by
 * @cp, which must have been वापसed by a previous call to cp_init().
 * Otherwise, undefined behavior occurs.
 */
व्योम cp_मुक्त(काष्ठा channel_program *cp)
अणु
	काष्ठा ccwchain *chain, *temp;
	पूर्णांक i;

	अगर (!cp->initialized)
		वापस;

	cp->initialized = false;
	list_क्रम_each_entry_safe(chain, temp, &cp->ccwchain_list, next) अणु
		क्रम (i = 0; i < chain->ch_len; i++) अणु
			pfn_array_unpin_मुक्त(chain->ch_pa + i, cp->mdev);
			ccwchain_cda_मुक्त(chain, i);
		पूर्ण
		ccwchain_मुक्त(chain);
	पूर्ण
पूर्ण

/**
 * cp_prefetch() - translate a guest physical address channel program to
 *                 a real-device runnable channel program.
 * @cp: channel_program on which to perक्रमm the operation
 *
 * This function translates the guest-physical-address channel program
 * and stores the result to ccwchain list. @cp must have been
 * initialized by a previous call with cp_init(). Otherwise, undefined
 * behavior occurs.
 * For each chain composing the channel program:
 * - On entry ch_len holds the count of CCWs to be translated.
 * - On निकास ch_len is adjusted to the count of successfully translated CCWs.
 * This allows cp_मुक्त to find in ch_len the count of CCWs to मुक्त in a chain.
 *
 * The S/390 CCW Translation APIS (prefixed by 'cp_') are पूर्णांकroduced
 * as helpers to करो ccw chain translation inside the kernel. Basically
 * they accept a channel program issued by a भव machine, and
 * translate the channel program to a real-device runnable channel
 * program.
 *
 * These APIs will copy the ccws पूर्णांकo kernel-space buffers, and update
 * the guest phsical addresses with their corresponding host physical
 * addresses.  Then channel I/O device drivers could issue the
 * translated channel program to real devices to perक्रमm an I/O
 * operation.
 *
 * These पूर्णांकerfaces are deचिन्हित to support translation only क्रम
 * channel programs, which are generated and क्रमmatted by a
 * guest. Thus this will make it possible क्रम things like VFIO to
 * leverage the पूर्णांकerfaces to passthrough a channel I/O mediated
 * device in QEMU.
 *
 * We support direct ccw chaining by translating them to idal ccws.
 *
 * Returns:
 *   %0 on success and a negative error value on failure.
 */
पूर्णांक cp_prefetch(काष्ठा channel_program *cp)
अणु
	काष्ठा ccwchain *chain;
	पूर्णांक len, idx, ret;

	/* this is an error in the caller */
	अगर (!cp->initialized)
		वापस -EINVAL;

	list_क्रम_each_entry(chain, &cp->ccwchain_list, next) अणु
		len = chain->ch_len;
		क्रम (idx = 0; idx < len; idx++) अणु
			ret = ccwchain_fetch_one(chain, idx, cp);
			अगर (ret)
				जाओ out_err;
		पूर्ण
	पूर्ण

	वापस 0;
out_err:
	/* Only cleanup the chain elements that were actually translated. */
	chain->ch_len = idx;
	list_क्रम_each_entry_जारी(chain, &cp->ccwchain_list, next) अणु
		chain->ch_len = 0;
	पूर्ण
	वापस ret;
पूर्ण

/**
 * cp_get_orb() - get the orb of the channel program
 * @cp: channel_program on which to perक्रमm the operation
 * @पूर्णांकparm: new पूर्णांकparm क्रम the वापसed orb
 * @lpm: candidate value of the logical-path mask क्रम the वापसed orb
 *
 * This function वापसs the address of the updated orb of the channel
 * program. Channel I/O device drivers could use this orb to issue a
 * ssch.
 */
जोड़ orb *cp_get_orb(काष्ठा channel_program *cp, u32 पूर्णांकparm, u8 lpm)
अणु
	जोड़ orb *orb;
	काष्ठा ccwchain *chain;
	काष्ठा ccw1 *cpa;

	/* this is an error in the caller */
	अगर (!cp->initialized)
		वापस शून्य;

	orb = &cp->orb;

	orb->cmd.पूर्णांकparm = पूर्णांकparm;
	orb->cmd.fmt = 1;
	orb->cmd.key = PAGE_DEFAULT_KEY >> 4;

	अगर (orb->cmd.lpm == 0)
		orb->cmd.lpm = lpm;

	chain = list_first_entry(&cp->ccwchain_list, काष्ठा ccwchain, next);
	cpa = chain->ch_ccw;
	orb->cmd.cpa = (__u32) __pa(cpa);

	वापस orb;
पूर्ण

/**
 * cp_update_scsw() - update scsw क्रम a channel program.
 * @cp: channel_program on which to perक्रमm the operation
 * @scsw: I/O results of the channel program and also the target to be
 *        updated
 *
 * @scsw contains the I/O results of the channel program that poपूर्णांकed
 * to by @cp. However what @scsw->cpa stores is a host physical
 * address, which is meaningless क्रम the guest, which is रुकोing क्रम
 * the I/O results.
 *
 * This function updates @scsw->cpa to its coressponding guest physical
 * address.
 */
व्योम cp_update_scsw(काष्ठा channel_program *cp, जोड़ scsw *scsw)
अणु
	काष्ठा ccwchain *chain;
	u32 cpa = scsw->cmd.cpa;
	u32 ccw_head;

	अगर (!cp->initialized)
		वापस;

	/*
	 * LATER:
	 * For now, only update the cmd.cpa part. We may need to deal with
	 * other portions of the schib as well, even अगर we करोn't वापस them
	 * in the ioctl directly. Path status changes etc.
	 */
	list_क्रम_each_entry(chain, &cp->ccwchain_list, next) अणु
		ccw_head = (u32)(u64)chain->ch_ccw;
		/*
		 * On successful execution, cpa poपूर्णांकs just beyond the end
		 * of the chain.
		 */
		अगर (is_cpa_within_range(cpa, ccw_head, chain->ch_len + 1)) अणु
			/*
			 * (cpa - ccw_head) is the offset value of the host
			 * physical ccw to its chain head.
			 * Adding this value to the guest physical ccw chain
			 * head माला_लो us the guest cpa.
			 */
			cpa = chain->ch_iova + (cpa - ccw_head);
			अवरोध;
		पूर्ण
	पूर्ण

	scsw->cmd.cpa = cpa;
पूर्ण

/**
 * cp_iova_pinned() - check अगर an iova is pinned क्रम a ccw chain.
 * @cp: channel_program on which to perक्रमm the operation
 * @iova: the iova to check
 *
 * If the @iova is currently pinned क्रम the ccw chain, वापस true;
 * अन्यथा वापस false.
 */
bool cp_iova_pinned(काष्ठा channel_program *cp, u64 iova)
अणु
	काष्ठा ccwchain *chain;
	पूर्णांक i;

	अगर (!cp->initialized)
		वापस false;

	list_क्रम_each_entry(chain, &cp->ccwchain_list, next) अणु
		क्रम (i = 0; i < chain->ch_len; i++)
			अगर (pfn_array_iova_pinned(chain->ch_pa + i, iova))
				वापस true;
	पूर्ण

	वापस false;
पूर्ण
