<शैली गुरु>
/*
 * edac_mc kernel module
 * (C) 2005, 2006 Linux Networx (http://lnxi.com)
 * This file may be distributed under the terms of the
 * GNU General Public License.
 *
 * Written by Thayne Harbaugh
 * Based on work by Dan Hollis <goemon at anime करोt net> and others.
 *	http://www.anime.net/~goemon/linux-ecc/
 *
 * Modअगरied by Dave Peterson and Doug Thompson
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/smp.h>
#समावेश <linux/init.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/समयr.h>
#समावेश <linux/slab.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/list.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/edac.h>
#समावेश <linux/bitops.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/page.h>
#समावेश "edac_mc.h"
#समावेश "edac_module.h"
#समावेश <ras/ras_event.h>

#अगर_घोषित CONFIG_EDAC_ATOMIC_SCRUB
#समावेश <यंत्र/edac.h>
#अन्यथा
#घोषणा edac_atomic_scrub(va, size) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

पूर्णांक edac_op_state = EDAC_OPSTATE_INVAL;
EXPORT_SYMBOL_GPL(edac_op_state);

/* lock to memory controller's control array */
अटल DEFINE_MUTEX(mem_ctls_mutex);
अटल LIST_HEAD(mc_devices);

/*
 * Used to lock EDAC MC to just one module, aव्योमing two drivers e. g.
 *	apei/ghes and i7core_edac to be used at the same समय.
 */
अटल स्थिर अक्षर *edac_mc_owner;

अटल काष्ठा mem_ctl_info *error_desc_to_mci(काष्ठा edac_raw_error_desc *e)
अणु
	वापस container_of(e, काष्ठा mem_ctl_info, error_desc);
पूर्ण

अचिन्हित पूर्णांक edac_dimm_info_location(काष्ठा dimm_info *dimm, अक्षर *buf,
				     अचिन्हित पूर्णांक len)
अणु
	काष्ठा mem_ctl_info *mci = dimm->mci;
	पूर्णांक i, n, count = 0;
	अक्षर *p = buf;

	क्रम (i = 0; i < mci->n_layers; i++) अणु
		n = snम_लिखो(p, len, "%s %d ",
			      edac_layer_name[mci->layers[i].type],
			      dimm->location[i]);
		p += n;
		len -= n;
		count += n;
		अगर (!len)
			अवरोध;
	पूर्ण

	वापस count;
पूर्ण

#अगर_घोषित CONFIG_EDAC_DEBUG

अटल व्योम edac_mc_dump_channel(काष्ठा rank_info *chan)
अणु
	edac_dbg(4, "  channel->chan_idx = %d\n", chan->chan_idx);
	edac_dbg(4, "    channel = %p\n", chan);
	edac_dbg(4, "    channel->csrow = %p\n", chan->csrow);
	edac_dbg(4, "    channel->dimm = %p\n", chan->dimm);
पूर्ण

अटल व्योम edac_mc_dump_dimm(काष्ठा dimm_info *dimm)
अणु
	अक्षर location[80];

	अगर (!dimm->nr_pages)
		वापस;

	edac_dimm_info_location(dimm, location, माप(location));

	edac_dbg(4, "%s%i: %smapped as virtual row %d, chan %d\n",
		 dimm->mci->csbased ? "rank" : "dimm",
		 dimm->idx, location, dimm->csrow, dimm->cschannel);
	edac_dbg(4, "  dimm = %p\n", dimm);
	edac_dbg(4, "  dimm->label = '%s'\n", dimm->label);
	edac_dbg(4, "  dimm->nr_pages = 0x%x\n", dimm->nr_pages);
	edac_dbg(4, "  dimm->grain = %d\n", dimm->grain);
	edac_dbg(4, "  dimm->nr_pages = 0x%x\n", dimm->nr_pages);
पूर्ण

अटल व्योम edac_mc_dump_csrow(काष्ठा csrow_info *csrow)
अणु
	edac_dbg(4, "csrow->csrow_idx = %d\n", csrow->csrow_idx);
	edac_dbg(4, "  csrow = %p\n", csrow);
	edac_dbg(4, "  csrow->first_page = 0x%lx\n", csrow->first_page);
	edac_dbg(4, "  csrow->last_page = 0x%lx\n", csrow->last_page);
	edac_dbg(4, "  csrow->page_mask = 0x%lx\n", csrow->page_mask);
	edac_dbg(4, "  csrow->nr_channels = %d\n", csrow->nr_channels);
	edac_dbg(4, "  csrow->channels = %p\n", csrow->channels);
	edac_dbg(4, "  csrow->mci = %p\n", csrow->mci);
पूर्ण

अटल व्योम edac_mc_dump_mci(काष्ठा mem_ctl_info *mci)
अणु
	edac_dbg(3, "\tmci = %p\n", mci);
	edac_dbg(3, "\tmci->mtype_cap = %lx\n", mci->mtype_cap);
	edac_dbg(3, "\tmci->edac_ctl_cap = %lx\n", mci->edac_ctl_cap);
	edac_dbg(3, "\tmci->edac_cap = %lx\n", mci->edac_cap);
	edac_dbg(4, "\tmci->edac_check = %p\n", mci->edac_check);
	edac_dbg(3, "\tmci->nr_csrows = %d, csrows = %p\n",
		 mci->nr_csrows, mci->csrows);
	edac_dbg(3, "\tmci->nr_dimms = %d, dimms = %p\n",
		 mci->tot_dimms, mci->dimms);
	edac_dbg(3, "\tdev = %p\n", mci->pdev);
	edac_dbg(3, "\tmod_name:ctl_name = %s:%s\n",
		 mci->mod_name, mci->ctl_name);
	edac_dbg(3, "\tpvt_info = %p\n\n", mci->pvt_info);
पूर्ण

#पूर्ण_अगर				/* CONFIG_EDAC_DEBUG */

स्थिर अक्षर * स्थिर edac_mem_types[] = अणु
	[MEM_EMPTY]	= "Empty",
	[MEM_RESERVED]	= "Reserved",
	[MEM_UNKNOWN]	= "Unknown",
	[MEM_FPM]	= "FPM",
	[MEM_EDO]	= "EDO",
	[MEM_BEDO]	= "BEDO",
	[MEM_SDR]	= "Unbuffered-SDR",
	[MEM_RDR]	= "Registered-SDR",
	[MEM_DDR]	= "Unbuffered-DDR",
	[MEM_RDDR]	= "Registered-DDR",
	[MEM_RMBS]	= "RMBS",
	[MEM_DDR2]	= "Unbuffered-DDR2",
	[MEM_FB_DDR2]	= "FullyBuffered-DDR2",
	[MEM_RDDR2]	= "Registered-DDR2",
	[MEM_XDR]	= "XDR",
	[MEM_DDR3]	= "Unbuffered-DDR3",
	[MEM_RDDR3]	= "Registered-DDR3",
	[MEM_LRDDR3]	= "Load-Reduced-DDR3-RAM",
	[MEM_LPDDR3]	= "Low-Power-DDR3-RAM",
	[MEM_DDR4]	= "Unbuffered-DDR4",
	[MEM_RDDR4]	= "Registered-DDR4",
	[MEM_LPDDR4]	= "Low-Power-DDR4-RAM",
	[MEM_LRDDR4]	= "Load-Reduced-DDR4-RAM",
	[MEM_DDR5]	= "Unbuffered-DDR5",
	[MEM_NVDIMM]	= "Non-volatile-RAM",
	[MEM_WIO2]	= "Wide-IO-2",
पूर्ण;
EXPORT_SYMBOL_GPL(edac_mem_types);

/**
 * edac_align_ptr - Prepares the poपूर्णांकer offsets क्रम a single-shot allocation
 * @p:		poपूर्णांकer to a poपूर्णांकer with the memory offset to be used. At
 *		वापस, this will be incremented to poपूर्णांक to the next offset
 * @size:	Size of the data काष्ठाure to be reserved
 * @n_elems:	Number of elements that should be reserved
 *
 * If 'size' is a स्थिरant, the compiler will optimize this whole function
 * करोwn to either a no-op or the addition of a स्थिरant to the value of '*p'.
 *
 * The 'p' poपूर्णांकer is असलolutely needed to keep the proper advancing
 * further in memory to the proper offsets when allocating the काष्ठा aदीर्घ
 * with its embedded काष्ठाs, as edac_device_alloc_ctl_info() करोes it
 * above, क्रम example.
 *
 * At वापस, the poपूर्णांकer 'p' will be incremented to be used on a next call
 * to this function.
 */
व्योम *edac_align_ptr(व्योम **p, अचिन्हित पूर्णांक size, पूर्णांक n_elems)
अणु
	अचिन्हित पूर्णांक align, r;
	व्योम *ptr = *p;

	*p += size * n_elems;

	/*
	 * 'p' can possibly be an unaligned item X such that माप(X) is
	 * 'size'.  Adjust 'p' so that its alignment is at least as
	 * stringent as what the compiler would provide क्रम X and वापस
	 * the aligned result.
	 * Here we assume that the alignment of a "long long" is the most
	 * stringent alignment that the compiler will ever provide by शेष.
	 * As far as I know, this is a reasonable assumption.
	 */
	अगर (size > माप(दीर्घ))
		align = माप(दीर्घ दीर्घ);
	अन्यथा अगर (size > माप(पूर्णांक))
		align = माप(दीर्घ);
	अन्यथा अगर (size > माप(लघु))
		align = माप(पूर्णांक);
	अन्यथा अगर (size > माप(अक्षर))
		align = माप(लघु);
	अन्यथा
		वापस (अक्षर *)ptr;

	r = (अचिन्हित दीर्घ)p % align;

	अगर (r == 0)
		वापस (अक्षर *)ptr;

	*p += align - r;

	वापस (व्योम *)(((अचिन्हित दीर्घ)ptr) + align - r);
पूर्ण

अटल व्योम _edac_mc_मुक्त(काष्ठा mem_ctl_info *mci)
अणु
	put_device(&mci->dev);
पूर्ण

अटल व्योम mci_release(काष्ठा device *dev)
अणु
	काष्ठा mem_ctl_info *mci = container_of(dev, काष्ठा mem_ctl_info, dev);
	काष्ठा csrow_info *csr;
	पूर्णांक i, chn, row;

	अगर (mci->dimms) अणु
		क्रम (i = 0; i < mci->tot_dimms; i++)
			kमुक्त(mci->dimms[i]);
		kमुक्त(mci->dimms);
	पूर्ण

	अगर (mci->csrows) अणु
		क्रम (row = 0; row < mci->nr_csrows; row++) अणु
			csr = mci->csrows[row];
			अगर (!csr)
				जारी;

			अगर (csr->channels) अणु
				क्रम (chn = 0; chn < mci->num_cschannel; chn++)
					kमुक्त(csr->channels[chn]);
				kमुक्त(csr->channels);
			पूर्ण
			kमुक्त(csr);
		पूर्ण
		kमुक्त(mci->csrows);
	पूर्ण
	kमुक्त(mci);
पूर्ण

अटल पूर्णांक edac_mc_alloc_csrows(काष्ठा mem_ctl_info *mci)
अणु
	अचिन्हित पूर्णांक tot_channels = mci->num_cschannel;
	अचिन्हित पूर्णांक tot_csrows = mci->nr_csrows;
	अचिन्हित पूर्णांक row, chn;

	/*
	 * Alocate and fill the csrow/channels काष्ठाs
	 */
	mci->csrows = kसुस्मृति(tot_csrows, माप(*mci->csrows), GFP_KERNEL);
	अगर (!mci->csrows)
		वापस -ENOMEM;

	क्रम (row = 0; row < tot_csrows; row++) अणु
		काष्ठा csrow_info *csr;

		csr = kzalloc(माप(**mci->csrows), GFP_KERNEL);
		अगर (!csr)
			वापस -ENOMEM;

		mci->csrows[row] = csr;
		csr->csrow_idx = row;
		csr->mci = mci;
		csr->nr_channels = tot_channels;
		csr->channels = kसुस्मृति(tot_channels, माप(*csr->channels),
					GFP_KERNEL);
		अगर (!csr->channels)
			वापस -ENOMEM;

		क्रम (chn = 0; chn < tot_channels; chn++) अणु
			काष्ठा rank_info *chan;

			chan = kzalloc(माप(**csr->channels), GFP_KERNEL);
			अगर (!chan)
				वापस -ENOMEM;

			csr->channels[chn] = chan;
			chan->chan_idx = chn;
			chan->csrow = csr;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक edac_mc_alloc_dimms(काष्ठा mem_ctl_info *mci)
अणु
	अचिन्हित पूर्णांक pos[EDAC_MAX_LAYERS];
	अचिन्हित पूर्णांक row, chn, idx;
	पूर्णांक layer;
	व्योम *p;

	/*
	 * Allocate and fill the dimm काष्ठाs
	 */
	mci->dimms  = kसुस्मृति(mci->tot_dimms, माप(*mci->dimms), GFP_KERNEL);
	अगर (!mci->dimms)
		वापस -ENOMEM;

	स_रखो(&pos, 0, माप(pos));
	row = 0;
	chn = 0;
	क्रम (idx = 0; idx < mci->tot_dimms; idx++) अणु
		काष्ठा dimm_info *dimm;
		काष्ठा rank_info *chan;
		पूर्णांक n, len;

		chan = mci->csrows[row]->channels[chn];

		dimm = kzalloc(माप(**mci->dimms), GFP_KERNEL);
		अगर (!dimm)
			वापस -ENOMEM;
		mci->dimms[idx] = dimm;
		dimm->mci = mci;
		dimm->idx = idx;

		/*
		 * Copy DIMM location and initialize it.
		 */
		len = माप(dimm->label);
		p = dimm->label;
		n = snम_लिखो(p, len, "mc#%u", mci->mc_idx);
		p += n;
		len -= n;
		क्रम (layer = 0; layer < mci->n_layers; layer++) अणु
			n = snम_लिखो(p, len, "%s#%u",
				     edac_layer_name[mci->layers[layer].type],
				     pos[layer]);
			p += n;
			len -= n;
			dimm->location[layer] = pos[layer];

			अगर (len <= 0)
				अवरोध;
		पूर्ण

		/* Link it to the csrows old API data */
		chan->dimm = dimm;
		dimm->csrow = row;
		dimm->cschannel = chn;

		/* Increment csrow location */
		अगर (mci->layers[0].is_virt_csrow) अणु
			chn++;
			अगर (chn == mci->num_cschannel) अणु
				chn = 0;
				row++;
			पूर्ण
		पूर्ण अन्यथा अणु
			row++;
			अगर (row == mci->nr_csrows) अणु
				row = 0;
				chn++;
			पूर्ण
		पूर्ण

		/* Increment dimm location */
		क्रम (layer = mci->n_layers - 1; layer >= 0; layer--) अणु
			pos[layer]++;
			अगर (pos[layer] < mci->layers[layer].size)
				अवरोध;
			pos[layer] = 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा mem_ctl_info *edac_mc_alloc(अचिन्हित पूर्णांक mc_num,
				   अचिन्हित पूर्णांक n_layers,
				   काष्ठा edac_mc_layer *layers,
				   अचिन्हित पूर्णांक sz_pvt)
अणु
	काष्ठा mem_ctl_info *mci;
	काष्ठा edac_mc_layer *layer;
	अचिन्हित पूर्णांक idx, size, tot_dimms = 1;
	अचिन्हित पूर्णांक tot_csrows = 1, tot_channels = 1;
	व्योम *pvt, *ptr = शून्य;
	bool per_rank = false;

	अगर (WARN_ON(n_layers > EDAC_MAX_LAYERS || n_layers == 0))
		वापस शून्य;

	/*
	 * Calculate the total amount of dimms and csrows/cschannels जबतक
	 * in the old API emulation mode
	 */
	क्रम (idx = 0; idx < n_layers; idx++) अणु
		tot_dimms *= layers[idx].size;

		अगर (layers[idx].is_virt_csrow)
			tot_csrows *= layers[idx].size;
		अन्यथा
			tot_channels *= layers[idx].size;

		अगर (layers[idx].type == EDAC_MC_LAYER_CHIP_SELECT)
			per_rank = true;
	पूर्ण

	/* Figure out the offsets of the various items from the start of an mc
	 * काष्ठाure.  We want the alignment of each item to be at least as
	 * stringent as what the compiler would provide अगर we could simply
	 * hardcode everything पूर्णांकo a single काष्ठा.
	 */
	mci	= edac_align_ptr(&ptr, माप(*mci), 1);
	layer	= edac_align_ptr(&ptr, माप(*layer), n_layers);
	pvt	= edac_align_ptr(&ptr, sz_pvt, 1);
	size	= ((अचिन्हित दीर्घ)pvt) + sz_pvt;

	edac_dbg(1, "allocating %u bytes for mci data (%d %s, %d csrows/channels)\n",
		 size,
		 tot_dimms,
		 per_rank ? "ranks" : "dimms",
		 tot_csrows * tot_channels);

	mci = kzalloc(size, GFP_KERNEL);
	अगर (mci == शून्य)
		वापस शून्य;

	mci->dev.release = mci_release;
	device_initialize(&mci->dev);

	/* Adjust poपूर्णांकers so they poपूर्णांक within the memory we just allocated
	 * rather than an imaginary chunk of memory located at address 0.
	 */
	layer = (काष्ठा edac_mc_layer *)(((अक्षर *)mci) + ((अचिन्हित दीर्घ)layer));
	pvt = sz_pvt ? (((अक्षर *)mci) + ((अचिन्हित दीर्घ)pvt)) : शून्य;

	/* setup index and various पूर्णांकernal poपूर्णांकers */
	mci->mc_idx = mc_num;
	mci->tot_dimms = tot_dimms;
	mci->pvt_info = pvt;
	mci->n_layers = n_layers;
	mci->layers = layer;
	स_नकल(mci->layers, layers, माप(*layer) * n_layers);
	mci->nr_csrows = tot_csrows;
	mci->num_cschannel = tot_channels;
	mci->csbased = per_rank;

	अगर (edac_mc_alloc_csrows(mci))
		जाओ error;

	अगर (edac_mc_alloc_dimms(mci))
		जाओ error;

	mci->op_state = OP_ALLOC;

	वापस mci;

error:
	_edac_mc_मुक्त(mci);

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(edac_mc_alloc);

व्योम edac_mc_मुक्त(काष्ठा mem_ctl_info *mci)
अणु
	edac_dbg(1, "\n");

	_edac_mc_मुक्त(mci);
पूर्ण
EXPORT_SYMBOL_GPL(edac_mc_मुक्त);

bool edac_has_mcs(व्योम)
अणु
	bool ret;

	mutex_lock(&mem_ctls_mutex);

	ret = list_empty(&mc_devices);

	mutex_unlock(&mem_ctls_mutex);

	वापस !ret;
पूर्ण
EXPORT_SYMBOL_GPL(edac_has_mcs);

/* Caller must hold mem_ctls_mutex */
अटल काष्ठा mem_ctl_info *__find_mci_by_dev(काष्ठा device *dev)
अणु
	काष्ठा mem_ctl_info *mci;
	काष्ठा list_head *item;

	edac_dbg(3, "\n");

	list_क्रम_each(item, &mc_devices) अणु
		mci = list_entry(item, काष्ठा mem_ctl_info, link);

		अगर (mci->pdev == dev)
			वापस mci;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * find_mci_by_dev
 *
 *	scan list of controllers looking क्रम the one that manages
 *	the 'dev' device
 * @dev: poपूर्णांकer to a काष्ठा device related with the MCI
 */
काष्ठा mem_ctl_info *find_mci_by_dev(काष्ठा device *dev)
अणु
	काष्ठा mem_ctl_info *ret;

	mutex_lock(&mem_ctls_mutex);
	ret = __find_mci_by_dev(dev);
	mutex_unlock(&mem_ctls_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(find_mci_by_dev);

/*
 * edac_mc_workq_function
 *	perक्रमms the operation scheduled by a workq request
 */
अटल व्योम edac_mc_workq_function(काष्ठा work_काष्ठा *work_req)
अणु
	काष्ठा delayed_work *d_work = to_delayed_work(work_req);
	काष्ठा mem_ctl_info *mci = to_edac_mem_ctl_work(d_work);

	mutex_lock(&mem_ctls_mutex);

	अगर (mci->op_state != OP_RUNNING_POLL) अणु
		mutex_unlock(&mem_ctls_mutex);
		वापस;
	पूर्ण

	अगर (edac_op_state == EDAC_OPSTATE_POLL)
		mci->edac_check(mci);

	mutex_unlock(&mem_ctls_mutex);

	/* Queue ourselves again. */
	edac_queue_work(&mci->work, msecs_to_jअगरfies(edac_mc_get_poll_msec()));
पूर्ण

/*
 * edac_mc_reset_delay_period(अचिन्हित दीर्घ value)
 *
 *	user space has updated our poll period value, need to
 *	reset our workq delays
 */
व्योम edac_mc_reset_delay_period(अचिन्हित दीर्घ value)
अणु
	काष्ठा mem_ctl_info *mci;
	काष्ठा list_head *item;

	mutex_lock(&mem_ctls_mutex);

	list_क्रम_each(item, &mc_devices) अणु
		mci = list_entry(item, काष्ठा mem_ctl_info, link);

		अगर (mci->op_state == OP_RUNNING_POLL)
			edac_mod_work(&mci->work, value);
	पूर्ण
	mutex_unlock(&mem_ctls_mutex);
पूर्ण



/* Return 0 on success, 1 on failure.
 * Beक्रमe calling this function, caller must
 * assign a unique value to mci->mc_idx.
 *
 *	locking model:
 *
 *		called with the mem_ctls_mutex lock held
 */
अटल पूर्णांक add_mc_to_global_list(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा list_head *item, *insert_beक्रमe;
	काष्ठा mem_ctl_info *p;

	insert_beक्रमe = &mc_devices;

	p = __find_mci_by_dev(mci->pdev);
	अगर (unlikely(p != शून्य))
		जाओ fail0;

	list_क्रम_each(item, &mc_devices) अणु
		p = list_entry(item, काष्ठा mem_ctl_info, link);

		अगर (p->mc_idx >= mci->mc_idx) अणु
			अगर (unlikely(p->mc_idx == mci->mc_idx))
				जाओ fail1;

			insert_beक्रमe = item;
			अवरोध;
		पूर्ण
	पूर्ण

	list_add_tail_rcu(&mci->link, insert_beक्रमe);
	वापस 0;

fail0:
	edac_prपूर्णांकk(KERN_WARNING, EDAC_MC,
		"%s (%s) %s %s already assigned %d\n", dev_name(p->pdev),
		edac_dev_name(mci), p->mod_name, p->ctl_name, p->mc_idx);
	वापस 1;

fail1:
	edac_prपूर्णांकk(KERN_WARNING, EDAC_MC,
		"bug in low-level driver: attempt to assign\n"
		"    duplicate mc_idx %d in %s()\n", p->mc_idx, __func__);
	वापस 1;
पूर्ण

अटल पूर्णांक del_mc_from_global_list(काष्ठा mem_ctl_info *mci)
अणु
	list_del_rcu(&mci->link);

	/* these are क्रम safe removal of devices from global list जबतक
	 * NMI handlers may be traversing list
	 */
	synchronize_rcu();
	INIT_LIST_HEAD(&mci->link);

	वापस list_empty(&mc_devices);
पूर्ण

काष्ठा mem_ctl_info *edac_mc_find(पूर्णांक idx)
अणु
	काष्ठा mem_ctl_info *mci;
	काष्ठा list_head *item;

	mutex_lock(&mem_ctls_mutex);

	list_क्रम_each(item, &mc_devices) अणु
		mci = list_entry(item, काष्ठा mem_ctl_info, link);
		अगर (mci->mc_idx == idx)
			जाओ unlock;
	पूर्ण

	mci = शून्य;
unlock:
	mutex_unlock(&mem_ctls_mutex);
	वापस mci;
पूर्ण
EXPORT_SYMBOL(edac_mc_find);

स्थिर अक्षर *edac_get_owner(व्योम)
अणु
	वापस edac_mc_owner;
पूर्ण
EXPORT_SYMBOL_GPL(edac_get_owner);

/* FIXME - should a warning be prपूर्णांकed अगर no error detection? correction? */
पूर्णांक edac_mc_add_mc_with_groups(काष्ठा mem_ctl_info *mci,
			       स्थिर काष्ठा attribute_group **groups)
अणु
	पूर्णांक ret = -EINVAL;
	edac_dbg(0, "\n");

#अगर_घोषित CONFIG_EDAC_DEBUG
	अगर (edac_debug_level >= 3)
		edac_mc_dump_mci(mci);

	अगर (edac_debug_level >= 4) अणु
		काष्ठा dimm_info *dimm;
		पूर्णांक i;

		क्रम (i = 0; i < mci->nr_csrows; i++) अणु
			काष्ठा csrow_info *csrow = mci->csrows[i];
			u32 nr_pages = 0;
			पूर्णांक j;

			क्रम (j = 0; j < csrow->nr_channels; j++)
				nr_pages += csrow->channels[j]->dimm->nr_pages;
			अगर (!nr_pages)
				जारी;
			edac_mc_dump_csrow(csrow);
			क्रम (j = 0; j < csrow->nr_channels; j++)
				अगर (csrow->channels[j]->dimm->nr_pages)
					edac_mc_dump_channel(csrow->channels[j]);
		पूर्ण

		mci_क्रम_each_dimm(mci, dimm)
			edac_mc_dump_dimm(dimm);
	पूर्ण
#पूर्ण_अगर
	mutex_lock(&mem_ctls_mutex);

	अगर (edac_mc_owner && edac_mc_owner != mci->mod_name) अणु
		ret = -EPERM;
		जाओ fail0;
	पूर्ण

	अगर (add_mc_to_global_list(mci))
		जाओ fail0;

	/* set load समय so that error rate can be tracked */
	mci->start_समय = jअगरfies;

	mci->bus = edac_get_sysfs_subsys();

	अगर (edac_create_sysfs_mci_device(mci, groups)) अणु
		edac_mc_prपूर्णांकk(mci, KERN_WARNING,
			"failed to create sysfs device\n");
		जाओ fail1;
	पूर्ण

	अगर (mci->edac_check) अणु
		mci->op_state = OP_RUNNING_POLL;

		INIT_DELAYED_WORK(&mci->work, edac_mc_workq_function);
		edac_queue_work(&mci->work, msecs_to_jअगरfies(edac_mc_get_poll_msec()));

	पूर्ण अन्यथा अणु
		mci->op_state = OP_RUNNING_INTERRUPT;
	पूर्ण

	/* Report action taken */
	edac_mc_prपूर्णांकk(mci, KERN_INFO,
		"Giving out device to module %s controller %s: DEV %s (%s)\n",
		mci->mod_name, mci->ctl_name, mci->dev_name,
		edac_op_state_to_string(mci->op_state));

	edac_mc_owner = mci->mod_name;

	mutex_unlock(&mem_ctls_mutex);
	वापस 0;

fail1:
	del_mc_from_global_list(mci);

fail0:
	mutex_unlock(&mem_ctls_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(edac_mc_add_mc_with_groups);

काष्ठा mem_ctl_info *edac_mc_del_mc(काष्ठा device *dev)
अणु
	काष्ठा mem_ctl_info *mci;

	edac_dbg(0, "\n");

	mutex_lock(&mem_ctls_mutex);

	/* find the requested mci काष्ठा in the global list */
	mci = __find_mci_by_dev(dev);
	अगर (mci == शून्य) अणु
		mutex_unlock(&mem_ctls_mutex);
		वापस शून्य;
	पूर्ण

	/* mark MCI offline: */
	mci->op_state = OP_OFFLINE;

	अगर (del_mc_from_global_list(mci))
		edac_mc_owner = शून्य;

	mutex_unlock(&mem_ctls_mutex);

	अगर (mci->edac_check)
		edac_stop_work(&mci->work);

	/* हटाओ from sysfs */
	edac_हटाओ_sysfs_mci_device(mci);

	edac_prपूर्णांकk(KERN_INFO, EDAC_MC,
		"Removed device %d for %s %s: DEV %s\n", mci->mc_idx,
		mci->mod_name, mci->ctl_name, edac_dev_name(mci));

	वापस mci;
पूर्ण
EXPORT_SYMBOL_GPL(edac_mc_del_mc);

अटल व्योम edac_mc_scrub_block(अचिन्हित दीर्घ page, अचिन्हित दीर्घ offset,
				u32 size)
अणु
	काष्ठा page *pg;
	व्योम *virt_addr;
	अचिन्हित दीर्घ flags = 0;

	edac_dbg(3, "\n");

	/* ECC error page was not in our memory. Ignore it. */
	अगर (!pfn_valid(page))
		वापस;

	/* Find the actual page काष्ठाure then map it and fix */
	pg = pfn_to_page(page);

	अगर (PageHighMem(pg))
		local_irq_save(flags);

	virt_addr = kmap_atomic(pg);

	/* Perक्रमm architecture specअगरic atomic scrub operation */
	edac_atomic_scrub(virt_addr + offset, size);

	/* Unmap and complete */
	kunmap_atomic(virt_addr);

	अगर (PageHighMem(pg))
		local_irq_restore(flags);
पूर्ण

/* FIXME - should वापस -1 */
पूर्णांक edac_mc_find_csrow_by_page(काष्ठा mem_ctl_info *mci, अचिन्हित दीर्घ page)
अणु
	काष्ठा csrow_info **csrows = mci->csrows;
	पूर्णांक row, i, j, n;

	edac_dbg(1, "MC%d: 0x%lx\n", mci->mc_idx, page);
	row = -1;

	क्रम (i = 0; i < mci->nr_csrows; i++) अणु
		काष्ठा csrow_info *csrow = csrows[i];
		n = 0;
		क्रम (j = 0; j < csrow->nr_channels; j++) अणु
			काष्ठा dimm_info *dimm = csrow->channels[j]->dimm;
			n += dimm->nr_pages;
		पूर्ण
		अगर (n == 0)
			जारी;

		edac_dbg(3, "MC%d: first(0x%lx) page(0x%lx) last(0x%lx) mask(0x%lx)\n",
			 mci->mc_idx,
			 csrow->first_page, page, csrow->last_page,
			 csrow->page_mask);

		अगर ((page >= csrow->first_page) &&
		    (page <= csrow->last_page) &&
		    ((page & csrow->page_mask) ==
		     (csrow->first_page & csrow->page_mask))) अणु
			row = i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (row == -1)
		edac_mc_prपूर्णांकk(mci, KERN_ERR,
			"could not look up page error address %lx\n",
			(अचिन्हित दीर्घ)page);

	वापस row;
पूर्ण
EXPORT_SYMBOL_GPL(edac_mc_find_csrow_by_page);

स्थिर अक्षर *edac_layer_name[] = अणु
	[EDAC_MC_LAYER_BRANCH] = "branch",
	[EDAC_MC_LAYER_CHANNEL] = "channel",
	[EDAC_MC_LAYER_SLOT] = "slot",
	[EDAC_MC_LAYER_CHIP_SELECT] = "csrow",
	[EDAC_MC_LAYER_ALL_MEM] = "memory",
पूर्ण;
EXPORT_SYMBOL_GPL(edac_layer_name);

अटल व्योम edac_inc_ce_error(काष्ठा edac_raw_error_desc *e)
अणु
	पूर्णांक pos[EDAC_MAX_LAYERS] = अणु e->top_layer, e->mid_layer, e->low_layer पूर्ण;
	काष्ठा mem_ctl_info *mci = error_desc_to_mci(e);
	काष्ठा dimm_info *dimm = edac_get_dimm(mci, pos[0], pos[1], pos[2]);

	mci->ce_mc += e->error_count;

	अगर (dimm)
		dimm->ce_count += e->error_count;
	अन्यथा
		mci->ce_noinfo_count += e->error_count;
पूर्ण

अटल व्योम edac_inc_ue_error(काष्ठा edac_raw_error_desc *e)
अणु
	पूर्णांक pos[EDAC_MAX_LAYERS] = अणु e->top_layer, e->mid_layer, e->low_layer पूर्ण;
	काष्ठा mem_ctl_info *mci = error_desc_to_mci(e);
	काष्ठा dimm_info *dimm = edac_get_dimm(mci, pos[0], pos[1], pos[2]);

	mci->ue_mc += e->error_count;

	अगर (dimm)
		dimm->ue_count += e->error_count;
	अन्यथा
		mci->ue_noinfo_count += e->error_count;
पूर्ण

अटल व्योम edac_ce_error(काष्ठा edac_raw_error_desc *e)
अणु
	काष्ठा mem_ctl_info *mci = error_desc_to_mci(e);
	अचिन्हित दीर्घ remapped_page;

	अगर (edac_mc_get_log_ce()) अणु
		edac_mc_prपूर्णांकk(mci, KERN_WARNING,
			"%d CE %s%son %s (%s page:0x%lx offset:0x%lx grain:%ld syndrome:0x%lx%s%s)\n",
			e->error_count, e->msg,
			*e->msg ? " " : "",
			e->label, e->location, e->page_frame_number, e->offset_in_page,
			e->grain, e->syndrome,
			*e->other_detail ? " - " : "",
			e->other_detail);
	पूर्ण

	edac_inc_ce_error(e);

	अगर (mci->scrub_mode == SCRUB_SW_SRC) अणु
		/*
			* Some memory controllers (called MCs below) can remap
			* memory so that it is still available at a dअगरferent
			* address when PCI devices map पूर्णांकo memory.
			* MC's that can't करो this, lose the memory where PCI
			* devices are mapped. This mapping is MC-dependent
			* and so we call back पूर्णांकo the MC driver क्रम it to
			* map the MC page to a physical (CPU) page which can
			* then be mapped to a भव page - which can then
			* be scrubbed.
			*/
		remapped_page = mci->ctl_page_to_phys ?
			mci->ctl_page_to_phys(mci, e->page_frame_number) :
			e->page_frame_number;

		edac_mc_scrub_block(remapped_page, e->offset_in_page, e->grain);
	पूर्ण
पूर्ण

अटल व्योम edac_ue_error(काष्ठा edac_raw_error_desc *e)
अणु
	काष्ठा mem_ctl_info *mci = error_desc_to_mci(e);

	अगर (edac_mc_get_log_ue()) अणु
		edac_mc_prपूर्णांकk(mci, KERN_WARNING,
			"%d UE %s%son %s (%s page:0x%lx offset:0x%lx grain:%ld%s%s)\n",
			e->error_count, e->msg,
			*e->msg ? " " : "",
			e->label, e->location, e->page_frame_number, e->offset_in_page,
			e->grain,
			*e->other_detail ? " - " : "",
			e->other_detail);
	पूर्ण

	edac_inc_ue_error(e);

	अगर (edac_mc_get_panic_on_ue()) अणु
		panic("UE %s%son %s (%s page:0x%lx offset:0x%lx grain:%ld%s%s)\n",
			e->msg,
			*e->msg ? " " : "",
			e->label, e->location, e->page_frame_number, e->offset_in_page,
			e->grain,
			*e->other_detail ? " - " : "",
			e->other_detail);
	पूर्ण
पूर्ण

अटल व्योम edac_inc_csrow(काष्ठा edac_raw_error_desc *e, पूर्णांक row, पूर्णांक chan)
अणु
	काष्ठा mem_ctl_info *mci = error_desc_to_mci(e);
	क्रमागत hw_event_mc_err_type type = e->type;
	u16 count = e->error_count;

	अगर (row < 0)
		वापस;

	edac_dbg(4, "csrow/channel to increment: (%d,%d)\n", row, chan);

	अगर (type == HW_EVENT_ERR_CORRECTED) अणु
		mci->csrows[row]->ce_count += count;
		अगर (chan >= 0)
			mci->csrows[row]->channels[chan]->ce_count += count;
	पूर्ण अन्यथा अणु
		mci->csrows[row]->ue_count += count;
	पूर्ण
पूर्ण

व्योम edac_raw_mc_handle_error(काष्ठा edac_raw_error_desc *e)
अणु
	काष्ठा mem_ctl_info *mci = error_desc_to_mci(e);
	u8 grain_bits;

	/* Sanity-check driver-supplied grain value. */
	अगर (WARN_ON_ONCE(!e->grain))
		e->grain = 1;

	grain_bits = fls_दीर्घ(e->grain - 1);

	/* Report the error via the trace पूर्णांकerface */
	अगर (IS_ENABLED(CONFIG_RAS))
		trace_mc_event(e->type, e->msg, e->label, e->error_count,
			       mci->mc_idx, e->top_layer, e->mid_layer,
			       e->low_layer,
			       (e->page_frame_number << PAGE_SHIFT) | e->offset_in_page,
			       grain_bits, e->syndrome, e->other_detail);

	अगर (e->type == HW_EVENT_ERR_CORRECTED)
		edac_ce_error(e);
	अन्यथा
		edac_ue_error(e);
पूर्ण
EXPORT_SYMBOL_GPL(edac_raw_mc_handle_error);

व्योम edac_mc_handle_error(स्थिर क्रमागत hw_event_mc_err_type type,
			  काष्ठा mem_ctl_info *mci,
			  स्थिर u16 error_count,
			  स्थिर अचिन्हित दीर्घ page_frame_number,
			  स्थिर अचिन्हित दीर्घ offset_in_page,
			  स्थिर अचिन्हित दीर्घ syndrome,
			  स्थिर पूर्णांक top_layer,
			  स्थिर पूर्णांक mid_layer,
			  स्थिर पूर्णांक low_layer,
			  स्थिर अक्षर *msg,
			  स्थिर अक्षर *other_detail)
अणु
	काष्ठा dimm_info *dimm;
	अक्षर *p;
	पूर्णांक row = -1, chan = -1;
	पूर्णांक pos[EDAC_MAX_LAYERS] = अणु top_layer, mid_layer, low_layer पूर्ण;
	पूर्णांक i, n_labels = 0;
	काष्ठा edac_raw_error_desc *e = &mci->error_desc;
	bool any_memory = true;

	edac_dbg(3, "MC%d\n", mci->mc_idx);

	/* Fills the error report buffer */
	स_रखो(e, 0, माप (*e));
	e->error_count = error_count;
	e->type = type;
	e->top_layer = top_layer;
	e->mid_layer = mid_layer;
	e->low_layer = low_layer;
	e->page_frame_number = page_frame_number;
	e->offset_in_page = offset_in_page;
	e->syndrome = syndrome;
	/* need valid strings here क्रम both: */
	e->msg = msg ?: "";
	e->other_detail = other_detail ?: "";

	/*
	 * Check अगर the event report is consistent and अगर the memory location is
	 * known. If it is, the DIMM(s) label info will be filled and the DIMM's
	 * error counters will be incremented.
	 */
	क्रम (i = 0; i < mci->n_layers; i++) अणु
		अगर (pos[i] >= (पूर्णांक)mci->layers[i].size) अणु

			edac_mc_prपूर्णांकk(mci, KERN_ERR,
				       "INTERNAL ERROR: %s value is out of range (%d >= %d)\n",
				       edac_layer_name[mci->layers[i].type],
				       pos[i], mci->layers[i].size);
			/*
			 * Instead of just वापसing it, let's use what's
			 * known about the error. The increment routines and
			 * the DIMM filter logic will करो the right thing by
			 * poपूर्णांकing the likely damaged DIMMs.
			 */
			pos[i] = -1;
		पूर्ण
		अगर (pos[i] >= 0)
			any_memory = false;
	पूर्ण

	/*
	 * Get the dimm label/grain that applies to the match criteria.
	 * As the error algorithm may not be able to poपूर्णांक to just one memory
	 * stick, the logic here will get all possible labels that could
	 * pottentially be affected by the error.
	 * On FB-DIMM memory controllers, क्रम uncorrected errors, it is common
	 * to have only the MC channel and the MC dimm (also called "branch")
	 * but the channel is not known, as the memory is arranged in pairs,
	 * where each memory beदीर्घs to a separate channel within the same
	 * branch.
	 */
	p = e->label;
	*p = '\0';

	mci_क्रम_each_dimm(mci, dimm) अणु
		अगर (top_layer >= 0 && top_layer != dimm->location[0])
			जारी;
		अगर (mid_layer >= 0 && mid_layer != dimm->location[1])
			जारी;
		अगर (low_layer >= 0 && low_layer != dimm->location[2])
			जारी;

		/* get the max grain, over the error match range */
		अगर (dimm->grain > e->grain)
			e->grain = dimm->grain;

		/*
		 * If the error is memory-controller wide, there's no need to
		 * seek क्रम the affected DIMMs because the whole channel/memory
		 * controller/... may be affected. Also, करोn't show errors क्रम
		 * empty DIMM slots.
		 */
		अगर (!dimm->nr_pages)
			जारी;

		n_labels++;
		अगर (n_labels > EDAC_MAX_LABELS) अणु
			p = e->label;
			*p = '\0';
		पूर्ण अन्यथा अणु
			अगर (p != e->label) अणु
				म_नकल(p, OTHER_LABEL);
				p += म_माप(OTHER_LABEL);
			पूर्ण
			म_नकल(p, dimm->label);
			p += म_माप(p);
		पूर्ण

		/*
		 * get csrow/channel of the DIMM, in order to allow
		 * incrementing the compat API counters
		 */
		edac_dbg(4, "%s csrows map: (%d,%d)\n",
			mci->csbased ? "rank" : "dimm",
			dimm->csrow, dimm->cschannel);
		अगर (row == -1)
			row = dimm->csrow;
		अन्यथा अगर (row >= 0 && row != dimm->csrow)
			row = -2;

		अगर (chan == -1)
			chan = dimm->cschannel;
		अन्यथा अगर (chan >= 0 && chan != dimm->cschannel)
			chan = -2;
	पूर्ण

	अगर (any_memory)
		म_नकल(e->label, "any memory");
	अन्यथा अगर (!*e->label)
		म_नकल(e->label, "unknown memory");

	edac_inc_csrow(e, row, chan);

	/* Fill the RAM location data */
	p = e->location;

	क्रम (i = 0; i < mci->n_layers; i++) अणु
		अगर (pos[i] < 0)
			जारी;

		p += प्र_लिखो(p, "%s:%d ",
			     edac_layer_name[mci->layers[i].type],
			     pos[i]);
	पूर्ण
	अगर (p > e->location)
		*(p - 1) = '\0';

	edac_raw_mc_handle_error(e);
पूर्ण
EXPORT_SYMBOL_GPL(edac_mc_handle_error);
