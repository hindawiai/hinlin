<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Perक्रमmance event support क्रम the System z CPU-measurement Sampling Facility
 *
 * Copyright IBM Corp. 2013, 2018
 * Author(s): Hendrik Brueckner <brueckner@linux.vnet.ibm.com>
 */
#घोषणा KMSG_COMPONENT	"cpum_sf"
#घोषणा pr_fmt(fmt)	KMSG_COMPONENT ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/perf_event.h>
#समावेश <linux/percpu.h>
#समावेश <linux/pid.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/moduleparam.h>
#समावेश <यंत्र/cpu_mf.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/debug.h>
#समावेश <यंत्र/समयx.h>

/* Minimum number of sample-data-block-tables:
 * At least one table is required क्रम the sampling buffer काष्ठाure.
 * A single table contains up to 511 poपूर्णांकers to sample-data-blocks.
 */
#घोषणा CPUM_SF_MIN_SDBT	1

/* Number of sample-data-blocks per sample-data-block-table (SDBT):
 * A table contains SDB poपूर्णांकers (8 bytes) and one table-link entry
 * that poपूर्णांकs to the origin of the next SDBT.
 */
#घोषणा CPUM_SF_SDB_PER_TABLE	((PAGE_SIZE - 8) / 8)

/* Maximum page offset क्रम an SDBT table-link entry:
 * If this page offset is reached, a table-link entry to the next SDBT
 * must be added.
 */
#घोषणा CPUM_SF_SDBT_TL_OFFSET	(CPUM_SF_SDB_PER_TABLE * 8)
अटल अंतरभूत पूर्णांक require_table_link(स्थिर व्योम *sdbt)
अणु
	वापस ((अचिन्हित दीर्घ) sdbt & ~PAGE_MASK) == CPUM_SF_SDBT_TL_OFFSET;
पूर्ण

/* Minimum and maximum sampling buffer sizes:
 *
 * This number represents the maximum size of the sampling buffer taking
 * the number of sample-data-block-tables पूर्णांकo account.  Note that these
 * numbers apply to the basic-sampling function only.
 * The maximum number of SDBs is increased by CPUM_SF_SDB_DIAG_FACTOR अगर
 * the diagnostic-sampling function is active.
 *
 * Sampling buffer size		Buffer अक्षरacteristics
 * ---------------------------------------------------
 *	 64KB		    ==	  16 pages (4KB per page)
 *				   1 page  क्रम SDB-tables
 *				  15 pages क्रम SDBs
 *
 *  32MB		    ==	8192 pages (4KB per page)
 *				  16 pages क्रम SDB-tables
 *				8176 pages क्रम SDBs
 */
अटल अचिन्हित दीर्घ __पढ़ो_mostly CPUM_SF_MIN_SDB = 15;
अटल अचिन्हित दीर्घ __पढ़ो_mostly CPUM_SF_MAX_SDB = 8176;
अटल अचिन्हित दीर्घ __पढ़ो_mostly CPUM_SF_SDB_DIAG_FACTOR = 1;

काष्ठा sf_buffer अणु
	अचिन्हित दीर्घ	 *sdbt;	    /* Sample-data-block-table origin */
	/* buffer अक्षरacteristics (required क्रम buffer increments) */
	अचिन्हित दीर्घ  num_sdb;	    /* Number of sample-data-blocks */
	अचिन्हित दीर्घ num_sdbt;	    /* Number of sample-data-block-tables */
	अचिन्हित दीर्घ	 *tail;	    /* last sample-data-block-table */
पूर्ण;

काष्ठा aux_buffer अणु
	काष्ठा sf_buffer sfb;
	अचिन्हित दीर्घ head;	   /* index of SDB of buffer head */
	अचिन्हित दीर्घ alert_mark;  /* index of SDB of alert request position */
	अचिन्हित दीर्घ empty_mark;  /* mark of SDB not marked full */
	अचिन्हित दीर्घ *sdb_index;  /* SDB address क्रम fast lookup */
	अचिन्हित दीर्घ *sdbt_index; /* SDBT address क्रम fast lookup */
पूर्ण;

काष्ठा cpu_hw_sf अणु
	/* CPU-measurement sampling inक्रमmation block */
	काष्ठा hws_qsi_info_block qsi;
	/* CPU-measurement sampling control block */
	काष्ठा hws_lsctl_request_block lsctl;
	काष्ठा sf_buffer sfb;	    /* Sampling buffer */
	अचिन्हित पूर्णांक flags;	    /* Status flags */
	काष्ठा perf_event *event;   /* Scheduled perf event */
	काष्ठा perf_output_handle handle; /* AUX buffer output handle */
पूर्ण;
अटल DEFINE_PER_CPU(काष्ठा cpu_hw_sf, cpu_hw_sf);

/* Debug feature */
अटल debug_info_t *sfdbg;

/*
 * sf_disable() - Switch off sampling facility
 */
अटल पूर्णांक sf_disable(व्योम)
अणु
	काष्ठा hws_lsctl_request_block sreq;

	स_रखो(&sreq, 0, माप(sreq));
	वापस lsctl(&sreq);
पूर्ण

/*
 * sf_buffer_available() - Check क्रम an allocated sampling buffer
 */
अटल पूर्णांक sf_buffer_available(काष्ठा cpu_hw_sf *cpuhw)
अणु
	वापस !!cpuhw->sfb.sdbt;
पूर्ण

/*
 * deallocate sampling facility buffer
 */
अटल व्योम मुक्त_sampling_buffer(काष्ठा sf_buffer *sfb)
अणु
	अचिन्हित दीर्घ *sdbt, *curr;

	अगर (!sfb->sdbt)
		वापस;

	sdbt = sfb->sdbt;
	curr = sdbt;

	/* Free the SDBT after all SDBs are processed... */
	जबतक (1) अणु
		अगर (!*curr || !sdbt)
			अवरोध;

		/* Process table-link entries */
		अगर (is_link_entry(curr)) अणु
			curr = get_next_sdbt(curr);
			अगर (sdbt)
				मुक्त_page((अचिन्हित दीर्घ) sdbt);

			/* If the origin is reached, sampling buffer is मुक्तd */
			अगर (curr == sfb->sdbt)
				अवरोध;
			अन्यथा
				sdbt = curr;
		पूर्ण अन्यथा अणु
			/* Process SDB poपूर्णांकer */
			अगर (*curr) अणु
				मुक्त_page(*curr);
				curr++;
			पूर्ण
		पूर्ण
	पूर्ण

	debug_प्र_लिखो_event(sfdbg, 5, "%s: freed sdbt %#lx\n", __func__,
			    (अचिन्हित दीर्घ)sfb->sdbt);
	स_रखो(sfb, 0, माप(*sfb));
पूर्ण

अटल पूर्णांक alloc_sample_data_block(अचिन्हित दीर्घ *sdbt, gfp_t gfp_flags)
अणु
	अचिन्हित दीर्घ sdb, *trailer;

	/* Allocate and initialize sample-data-block */
	sdb = get_zeroed_page(gfp_flags);
	अगर (!sdb)
		वापस -ENOMEM;
	trailer = trailer_entry_ptr(sdb);
	*trailer = SDB_TE_ALERT_REQ_MASK;

	/* Link SDB पूर्णांकo the sample-data-block-table */
	*sdbt = sdb;

	वापस 0;
पूर्ण

/*
 * पुनः_स्मृति_sampling_buffer() - extend sampler memory
 *
 * Allocates new sample-data-blocks and adds them to the specअगरied sampling
 * buffer memory.
 *
 * Important: This modअगरies the sampling buffer and must be called when the
 *	      sampling facility is disabled.
 *
 * Returns zero on success, non-zero otherwise.
 */
अटल पूर्णांक पुनः_स्मृति_sampling_buffer(काष्ठा sf_buffer *sfb,
				   अचिन्हित दीर्घ num_sdb, gfp_t gfp_flags)
अणु
	पूर्णांक i, rc;
	अचिन्हित दीर्घ *new, *tail, *tail_prev = शून्य;

	अगर (!sfb->sdbt || !sfb->tail)
		वापस -EINVAL;

	अगर (!is_link_entry(sfb->tail))
		वापस -EINVAL;

	/* Append to the existing sampling buffer, overwriting the table-link
	 * रेजिस्टर.
	 * The tail variables always poपूर्णांकs to the "tail" (last and table-link)
	 * entry in an SDB-table.
	 */
	tail = sfb->tail;

	/* Do a sanity check whether the table-link entry poपूर्णांकs to
	 * the sampling buffer origin.
	 */
	अगर (sfb->sdbt != get_next_sdbt(tail)) अणु
		debug_प्र_लिखो_event(sfdbg, 3, "%s: "
				    "sampling buffer is not linked: origin %#lx"
				    " tail %#lx\n", __func__,
				    (अचिन्हित दीर्घ)sfb->sdbt,
				    (अचिन्हित दीर्घ)tail);
		वापस -EINVAL;
	पूर्ण

	/* Allocate reमुख्यing SDBs */
	rc = 0;
	क्रम (i = 0; i < num_sdb; i++) अणु
		/* Allocate a new SDB-table अगर it is full. */
		अगर (require_table_link(tail)) अणु
			new = (अचिन्हित दीर्घ *) get_zeroed_page(gfp_flags);
			अगर (!new) अणु
				rc = -ENOMEM;
				अवरोध;
			पूर्ण
			sfb->num_sdbt++;
			/* Link current page to tail of chain */
			*tail = (अचिन्हित दीर्घ)(व्योम *) new + 1;
			tail_prev = tail;
			tail = new;
		पूर्ण

		/* Allocate a new sample-data-block.
		 * If there is not enough memory, stop the पुनः_स्मृति process
		 * and simply use what was allocated.  If this is a temporary
		 * issue, a new पुनः_स्मृति call (अगर required) might succeed.
		 */
		rc = alloc_sample_data_block(tail, gfp_flags);
		अगर (rc) अणु
			/* Unकरो last SDBT. An SDBT with no SDB at its first
			 * entry but with an SDBT entry instead can not be
			 * handled by the पूर्णांकerrupt handler code.
			 * Aव्योम this situation.
			 */
			अगर (tail_prev) अणु
				sfb->num_sdbt--;
				मुक्त_page((अचिन्हित दीर्घ) new);
				tail = tail_prev;
			पूर्ण
			अवरोध;
		पूर्ण
		sfb->num_sdb++;
		tail++;
		tail_prev = new = शून्य;	/* Allocated at least one SBD */
	पूर्ण

	/* Link sampling buffer to its origin */
	*tail = (अचिन्हित दीर्घ) sfb->sdbt + 1;
	sfb->tail = tail;

	debug_प्र_लिखो_event(sfdbg, 4, "%s: new buffer"
			    " settings: sdbt %lu sdb %lu\n", __func__,
			    sfb->num_sdbt, sfb->num_sdb);
	वापस rc;
पूर्ण

/*
 * allocate_sampling_buffer() - allocate sampler memory
 *
 * Allocates and initializes a sampling buffer काष्ठाure using the
 * specअगरied number of sample-data-blocks (SDB).  For each allocation,
 * a 4K page is used.  The number of sample-data-block-tables (SDBT)
 * are calculated from SDBs.
 * Also set the ALERT_REQ mask in each SDBs trailer.
 *
 * Returns zero on success, non-zero otherwise.
 */
अटल पूर्णांक alloc_sampling_buffer(काष्ठा sf_buffer *sfb, अचिन्हित दीर्घ num_sdb)
अणु
	पूर्णांक rc;

	अगर (sfb->sdbt)
		वापस -EINVAL;

	/* Allocate the sample-data-block-table origin */
	sfb->sdbt = (अचिन्हित दीर्घ *) get_zeroed_page(GFP_KERNEL);
	अगर (!sfb->sdbt)
		वापस -ENOMEM;
	sfb->num_sdb = 0;
	sfb->num_sdbt = 1;

	/* Link the table origin to poपूर्णांक to itself to prepare क्रम
	 * पुनः_स्मृति_sampling_buffer() invocation.
	 */
	sfb->tail = sfb->sdbt;
	*sfb->tail = (अचिन्हित दीर्घ)(व्योम *) sfb->sdbt + 1;

	/* Allocate requested number of sample-data-blocks */
	rc = पुनः_स्मृति_sampling_buffer(sfb, num_sdb, GFP_KERNEL);
	अगर (rc) अणु
		मुक्त_sampling_buffer(sfb);
		debug_प्र_लिखो_event(sfdbg, 4, "%s: "
			"realloc_sampling_buffer failed with rc %i\n",
			__func__, rc);
	पूर्ण अन्यथा
		debug_प्र_लिखो_event(sfdbg, 4,
			"%s: tear %#lx dear %#lx\n", __func__,
			(अचिन्हित दीर्घ)sfb->sdbt, (अचिन्हित दीर्घ)*sfb->sdbt);
	वापस rc;
पूर्ण

अटल व्योम sfb_set_limits(अचिन्हित दीर्घ min, अचिन्हित दीर्घ max)
अणु
	काष्ठा hws_qsi_info_block si;

	CPUM_SF_MIN_SDB = min;
	CPUM_SF_MAX_SDB = max;

	स_रखो(&si, 0, माप(si));
	अगर (!qsi(&si))
		CPUM_SF_SDB_DIAG_FACTOR = DIV_ROUND_UP(si.dsdes, si.bsdes);
पूर्ण

अटल अचिन्हित दीर्घ sfb_max_limit(काष्ठा hw_perf_event *hwc)
अणु
	वापस SAMPL_DIAG_MODE(hwc) ? CPUM_SF_MAX_SDB * CPUM_SF_SDB_DIAG_FACTOR
				    : CPUM_SF_MAX_SDB;
पूर्ण

अटल अचिन्हित दीर्घ sfb_pending_allocs(काष्ठा sf_buffer *sfb,
					काष्ठा hw_perf_event *hwc)
अणु
	अगर (!sfb->sdbt)
		वापस SFB_ALLOC_REG(hwc);
	अगर (SFB_ALLOC_REG(hwc) > sfb->num_sdb)
		वापस SFB_ALLOC_REG(hwc) - sfb->num_sdb;
	वापस 0;
पूर्ण

अटल पूर्णांक sfb_has_pending_allocs(काष्ठा sf_buffer *sfb,
				   काष्ठा hw_perf_event *hwc)
अणु
	वापस sfb_pending_allocs(sfb, hwc) > 0;
पूर्ण

अटल व्योम sfb_account_allocs(अचिन्हित दीर्घ num, काष्ठा hw_perf_event *hwc)
अणु
	/* Limit the number of SDBs to not exceed the maximum */
	num = min_t(अचिन्हित दीर्घ, num, sfb_max_limit(hwc) - SFB_ALLOC_REG(hwc));
	अगर (num)
		SFB_ALLOC_REG(hwc) += num;
पूर्ण

अटल व्योम sfb_init_allocs(अचिन्हित दीर्घ num, काष्ठा hw_perf_event *hwc)
अणु
	SFB_ALLOC_REG(hwc) = 0;
	sfb_account_allocs(num, hwc);
पूर्ण

अटल व्योम deallocate_buffers(काष्ठा cpu_hw_sf *cpuhw)
अणु
	अगर (cpuhw->sfb.sdbt)
		मुक्त_sampling_buffer(&cpuhw->sfb);
पूर्ण

अटल पूर्णांक allocate_buffers(काष्ठा cpu_hw_sf *cpuhw, काष्ठा hw_perf_event *hwc)
अणु
	अचिन्हित दीर्घ n_sdb, freq;
	माप_प्रकार sample_size;

	/* Calculate sampling buffers using 4K pages
	 *
	 *    1. The sampling size is 32 bytes क्रम basic sampling. This size
	 *	 is the same क्रम all machine types. Diagnostic
	 *	 sampling uses auxlilary data buffer setup which provides the
	 *	 memory क्रम SDBs using linux common code auxiliary trace
	 *	 setup.
	 *
	 *    2. Function alloc_sampling_buffer() sets the Alert Request
	 *	 Control indicator to trigger a measurement-alert to harvest
	 *	 sample-data-blocks (SDB). This is करोne per SDB. This
	 *	 measurement alert पूर्णांकerrupt fires quick enough to handle
	 *	 one SDB, on very high frequency and work loads there might
	 *	 be 2 to 3 SBDs available क्रम sample processing.
	 *	 Currently there is no need क्रम setup alert request on every
	 *	 n-th page. This is counterproductive as one IRQ triggers
	 *	 a very high number of samples to be processed at one IRQ.
	 *
	 *    3. Use the sampling frequency as input.
	 *	 Compute the number of SDBs and ensure a minimum
	 *	 of CPUM_SF_MIN_SDB.  Depending on frequency add some more
	 *	 SDBs to handle a higher sampling rate.
	 *	 Use a minimum of CPUM_SF_MIN_SDB and allow क्रम 100 samples
	 *	 (one SDB) क्रम every 10000 HZ frequency increment.
	 *
	 *    4. Compute the number of sample-data-block-tables (SDBT) and
	 *	 ensure a minimum of CPUM_SF_MIN_SDBT (one table can manage up
	 *	 to 511 SDBs).
	 */
	sample_size = माप(काष्ठा hws_basic_entry);
	freq = sample_rate_to_freq(&cpuhw->qsi, SAMPL_RATE(hwc));
	n_sdb = CPUM_SF_MIN_SDB + DIV_ROUND_UP(freq, 10000);

	/* If there is alपढ़ोy a sampling buffer allocated, it is very likely
	 * that the sampling facility is enabled too.  If the event to be
	 * initialized requires a greater sampling buffer, the allocation must
	 * be postponed.  Changing the sampling buffer requires the sampling
	 * facility to be in the disabled state.  So, account the number of
	 * required SDBs and let cpumsf_pmu_enable() resize the buffer just
	 * beक्रमe the event is started.
	 */
	sfb_init_allocs(n_sdb, hwc);
	अगर (sf_buffer_available(cpuhw))
		वापस 0;

	debug_प्र_लिखो_event(sfdbg, 3,
			    "%s: rate %lu f %lu sdb %lu/%lu"
			    " sample_size %lu cpuhw %p\n", __func__,
			    SAMPL_RATE(hwc), freq, n_sdb, sfb_max_limit(hwc),
			    sample_size, cpuhw);

	वापस alloc_sampling_buffer(&cpuhw->sfb,
				     sfb_pending_allocs(&cpuhw->sfb, hwc));
पूर्ण

अटल अचिन्हित दीर्घ min_percent(अचिन्हित पूर्णांक percent, अचिन्हित दीर्घ base,
				 अचिन्हित दीर्घ min)
अणु
	वापस min_t(अचिन्हित दीर्घ, min, DIV_ROUND_UP(percent * base, 100));
पूर्ण

अटल अचिन्हित दीर्घ compute_sfb_extent(अचिन्हित दीर्घ ratio, अचिन्हित दीर्घ base)
अणु
	/* Use a percentage-based approach to extend the sampling facility
	 * buffer.  Accept up to 5% sample data loss.
	 * Vary the extents between 1% to 5% of the current number of
	 * sample-data-blocks.
	 */
	अगर (ratio <= 5)
		वापस 0;
	अगर (ratio <= 25)
		वापस min_percent(1, base, 1);
	अगर (ratio <= 50)
		वापस min_percent(1, base, 1);
	अगर (ratio <= 75)
		वापस min_percent(2, base, 2);
	अगर (ratio <= 100)
		वापस min_percent(3, base, 3);
	अगर (ratio <= 250)
		वापस min_percent(4, base, 4);

	वापस min_percent(5, base, 8);
पूर्ण

अटल व्योम sfb_account_overflows(काष्ठा cpu_hw_sf *cpuhw,
				  काष्ठा hw_perf_event *hwc)
अणु
	अचिन्हित दीर्घ ratio, num;

	अगर (!OVERFLOW_REG(hwc))
		वापस;

	/* The sample_overflow contains the average number of sample data
	 * that has been lost because sample-data-blocks were full.
	 *
	 * Calculate the total number of sample data entries that has been
	 * discarded.  Then calculate the ratio of lost samples to total samples
	 * per second in percent.
	 */
	ratio = DIV_ROUND_UP(100 * OVERFLOW_REG(hwc) * cpuhw->sfb.num_sdb,
			     sample_rate_to_freq(&cpuhw->qsi, SAMPL_RATE(hwc)));

	/* Compute number of sample-data-blocks */
	num = compute_sfb_extent(ratio, cpuhw->sfb.num_sdb);
	अगर (num)
		sfb_account_allocs(num, hwc);

	debug_प्र_लिखो_event(sfdbg, 5, "%s: overflow %llu ratio %lu num %lu\n",
			    __func__, OVERFLOW_REG(hwc), ratio, num);
	OVERFLOW_REG(hwc) = 0;
पूर्ण

/* extend_sampling_buffer() - Extend sampling buffer
 * @sfb:	Sampling buffer काष्ठाure (क्रम local CPU)
 * @hwc:	Perf event hardware काष्ठाure
 *
 * Use this function to extend the sampling buffer based on the overflow counter
 * and postponed allocation extents stored in the specअगरied Perf event hardware.
 *
 * Important: This function disables the sampling facility in order to safely
 *	      change the sampling buffer काष्ठाure.  Do not call this function
 *	      when the PMU is active.
 */
अटल व्योम extend_sampling_buffer(काष्ठा sf_buffer *sfb,
				   काष्ठा hw_perf_event *hwc)
अणु
	अचिन्हित दीर्घ num, num_old;
	पूर्णांक rc;

	num = sfb_pending_allocs(sfb, hwc);
	अगर (!num)
		वापस;
	num_old = sfb->num_sdb;

	/* Disable the sampling facility to reset any states and also
	 * clear pending measurement alerts.
	 */
	sf_disable();

	/* Extend the sampling buffer.
	 * This memory allocation typically happens in an atomic context when
	 * called by perf.  Because this is a पुनः_स्मृतिation, it is fine अगर the
	 * new SDB-request cannot be satisfied immediately.
	 */
	rc = पुनः_स्मृति_sampling_buffer(sfb, num, GFP_ATOMIC);
	अगर (rc)
		debug_प्र_लिखो_event(sfdbg, 5, "%s: realloc failed with rc %i\n",
				    __func__, rc);

	अगर (sfb_has_pending_allocs(sfb, hwc))
		debug_प्र_लिखो_event(sfdbg, 5, "%s: "
				    "req %lu alloc %lu remaining %lu\n",
				    __func__, num, sfb->num_sdb - num_old,
				    sfb_pending_allocs(sfb, hwc));
पूर्ण

/* Number of perf events counting hardware events */
अटल atomic_t num_events;
/* Used to aव्योम races in calling reserve/release_cpumf_hardware */
अटल DEFINE_MUTEX(pmc_reserve_mutex);

#घोषणा PMC_INIT      0
#घोषणा PMC_RELEASE   1
#घोषणा PMC_FAILURE   2
अटल व्योम setup_pmc_cpu(व्योम *flags)
अणु
	पूर्णांक err;
	काष्ठा cpu_hw_sf *cpusf = this_cpu_ptr(&cpu_hw_sf);

	err = 0;
	चयन (*((पूर्णांक *) flags)) अणु
	हाल PMC_INIT:
		स_रखो(cpusf, 0, माप(*cpusf));
		err = qsi(&cpusf->qsi);
		अगर (err)
			अवरोध;
		cpusf->flags |= PMU_F_RESERVED;
		err = sf_disable();
		अगर (err)
			pr_err("Switching off the sampling facility failed "
			       "with rc %i\n", err);
		debug_प्र_लिखो_event(sfdbg, 5,
				    "%s: initialized: cpuhw %p\n", __func__,
				    cpusf);
		अवरोध;
	हाल PMC_RELEASE:
		cpusf->flags &= ~PMU_F_RESERVED;
		err = sf_disable();
		अगर (err) अणु
			pr_err("Switching off the sampling facility failed "
			       "with rc %i\n", err);
		पूर्ण अन्यथा
			deallocate_buffers(cpusf);
		debug_प्र_लिखो_event(sfdbg, 5,
				    "%s: released: cpuhw %p\n", __func__,
				    cpusf);
		अवरोध;
	पूर्ण
	अगर (err)
		*((पूर्णांक *) flags) |= PMC_FAILURE;
पूर्ण

अटल व्योम release_pmc_hardware(व्योम)
अणु
	पूर्णांक flags = PMC_RELEASE;

	irq_subclass_unरेजिस्टर(IRQ_SUBCLASS_MEASUREMENT_ALERT);
	on_each_cpu(setup_pmc_cpu, &flags, 1);
पूर्ण

अटल पूर्णांक reserve_pmc_hardware(व्योम)
अणु
	पूर्णांक flags = PMC_INIT;

	on_each_cpu(setup_pmc_cpu, &flags, 1);
	अगर (flags & PMC_FAILURE) अणु
		release_pmc_hardware();
		वापस -ENODEV;
	पूर्ण
	irq_subclass_रेजिस्टर(IRQ_SUBCLASS_MEASUREMENT_ALERT);

	वापस 0;
पूर्ण

अटल व्योम hw_perf_event_destroy(काष्ठा perf_event *event)
अणु
	/* Release PMC अगर this is the last perf event */
	अगर (!atomic_add_unless(&num_events, -1, 1)) अणु
		mutex_lock(&pmc_reserve_mutex);
		अगर (atomic_dec_वापस(&num_events) == 0)
			release_pmc_hardware();
		mutex_unlock(&pmc_reserve_mutex);
	पूर्ण
पूर्ण

अटल व्योम hw_init_period(काष्ठा hw_perf_event *hwc, u64 period)
अणु
	hwc->sample_period = period;
	hwc->last_period = hwc->sample_period;
	local64_set(&hwc->period_left, hwc->sample_period);
पूर्ण

अटल अचिन्हित दीर्घ hw_limit_rate(स्थिर काष्ठा hws_qsi_info_block *si,
				   अचिन्हित दीर्घ rate)
अणु
	वापस clamp_t(अचिन्हित दीर्घ, rate,
		       si->min_sampl_rate, si->max_sampl_rate);
पूर्ण

अटल u32 cpumsf_pid_type(काष्ठा perf_event *event,
			   u32 pid, क्रमागत pid_type type)
अणु
	काष्ठा task_काष्ठा *tsk;

	/* Idle process */
	अगर (!pid)
		जाओ out;

	tsk = find_task_by_pid_ns(pid, &init_pid_ns);
	pid = -1;
	अगर (tsk) अणु
		/*
		 * Only top level events contain the pid namespace in which
		 * they are created.
		 */
		अगर (event->parent)
			event = event->parent;
		pid = __task_pid_nr_ns(tsk, type, event->ns);
		/*
		 * See also 1d953111b648
		 * "perf/core: Don't report zero PIDs for exiting tasks".
		 */
		अगर (!pid && !pid_alive(tsk))
			pid = -1;
	पूर्ण
out:
	वापस pid;
पूर्ण

अटल व्योम cpumsf_output_event_pid(काष्ठा perf_event *event,
				    काष्ठा perf_sample_data *data,
				    काष्ठा pt_regs *regs)
अणु
	u32 pid;
	काष्ठा perf_event_header header;
	काष्ठा perf_output_handle handle;

	/*
	 * Obtain the PID from the basic-sampling data entry and
	 * correct the data->tid_entry.pid value.
	 */
	pid = data->tid_entry.pid;

	/* Protect callchain buffers, tasks */
	rcu_पढ़ो_lock();

	perf_prepare_sample(&header, data, event, regs);
	अगर (perf_output_begin(&handle, data, event, header.size))
		जाओ out;

	/* Update the process ID (see also kernel/events/core.c) */
	data->tid_entry.pid = cpumsf_pid_type(event, pid, PIDTYPE_TGID);
	data->tid_entry.tid = cpumsf_pid_type(event, pid, PIDTYPE_PID);

	perf_output_sample(&handle, &header, data, event);
	perf_output_end(&handle);
out:
	rcu_पढ़ो_unlock();
पूर्ण

अटल अचिन्हित दीर्घ getrate(bool freq, अचिन्हित दीर्घ sample,
			     काष्ठा hws_qsi_info_block *si)
अणु
	अचिन्हित दीर्घ rate;

	अगर (freq) अणु
		rate = freq_to_sample_rate(si, sample);
		rate = hw_limit_rate(si, rate);
	पूर्ण अन्यथा अणु
		/* The min/max sampling rates specअगरies the valid range
		 * of sample periods.  If the specअगरied sample period is
		 * out of range, limit the period to the range boundary.
		 */
		rate = hw_limit_rate(si, sample);

		/* The perf core मुख्यtains a maximum sample rate that is
		 * configurable through the sysctl पूर्णांकerface.  Ensure the
		 * sampling rate करोes not exceed this value.  This also helps
		 * to aव्योम throttling when pushing samples with
		 * perf_event_overflow().
		 */
		अगर (sample_rate_to_freq(si, rate) >
		    sysctl_perf_event_sample_rate) अणु
			debug_प्र_लिखो_event(sfdbg, 1, "%s: "
					    "Sampling rate exceeds maximum "
					    "perf sample rate\n", __func__);
			rate = 0;
		पूर्ण
	पूर्ण
	वापस rate;
पूर्ण

/* The sampling inक्रमmation (si) contains inक्रमmation about the
 * min/max sampling पूर्णांकervals and the CPU speed.  So calculate the
 * correct sampling पूर्णांकerval and aव्योम the whole period adjust
 * feedback loop.
 *
 * Since the CPU Measurement sampling facility can not handle frequency
 * calculate the sampling पूर्णांकerval when frequency is specअगरied using
 * this क्रमmula:
 *	पूर्णांकerval := cpu_speed * 1000000 / sample_freq
 *
 * Returns त्रुटि_सं on bad input and zero on success with parameter पूर्णांकerval
 * set to the correct sampling rate.
 *
 * Note: This function turns off freq bit to aव्योम calling function
 * perf_adjust_period(). This causes frequency adjusपंचांगent in the common
 * code part which causes tremenकरोus variations in the counter values.
 */
अटल पूर्णांक __hw_perf_event_init_rate(काष्ठा perf_event *event,
				     काष्ठा hws_qsi_info_block *si)
अणु
	काष्ठा perf_event_attr *attr = &event->attr;
	काष्ठा hw_perf_event *hwc = &event->hw;
	अचिन्हित दीर्घ rate;

	अगर (attr->freq) अणु
		अगर (!attr->sample_freq)
			वापस -EINVAL;
		rate = getrate(attr->freq, attr->sample_freq, si);
		attr->freq = 0;		/* Don't call  perf_adjust_period() */
		SAMPL_FLAGS(hwc) |= PERF_CPUM_SF_FREQ_MODE;
	पूर्ण अन्यथा अणु
		rate = getrate(attr->freq, attr->sample_period, si);
		अगर (!rate)
			वापस -EINVAL;
	पूर्ण
	attr->sample_period = rate;
	SAMPL_RATE(hwc) = rate;
	hw_init_period(hwc, SAMPL_RATE(hwc));
	debug_प्र_लिखो_event(sfdbg, 4, "%s: cpu %d period %#llx freq %d,%#lx\n",
			    __func__, event->cpu, event->attr.sample_period,
			    event->attr.freq, SAMPLE_FREQ_MODE(hwc));
	वापस 0;
पूर्ण

अटल पूर्णांक __hw_perf_event_init(काष्ठा perf_event *event)
अणु
	काष्ठा cpu_hw_sf *cpuhw;
	काष्ठा hws_qsi_info_block si;
	काष्ठा perf_event_attr *attr = &event->attr;
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक cpu, err;

	/* Reserve CPU-measurement sampling facility */
	err = 0;
	अगर (!atomic_inc_not_zero(&num_events)) अणु
		mutex_lock(&pmc_reserve_mutex);
		अगर (atomic_पढ़ो(&num_events) == 0 && reserve_pmc_hardware())
			err = -EBUSY;
		अन्यथा
			atomic_inc(&num_events);
		mutex_unlock(&pmc_reserve_mutex);
	पूर्ण
	event->destroy = hw_perf_event_destroy;

	अगर (err)
		जाओ out;

	/* Access per-CPU sampling inक्रमmation (query sampling info) */
	/*
	 * The event->cpu value can be -1 to count on every CPU, क्रम example,
	 * when attaching to a task.  If this is specअगरied, use the query
	 * sampling info from the current CPU, otherwise use event->cpu to
	 * retrieve the per-CPU inक्रमmation.
	 * Later, cpuhw indicates whether to allocate sampling buffers क्रम a
	 * particular CPU (cpuhw!=शून्य) or each online CPU (cpuw==शून्य).
	 */
	स_रखो(&si, 0, माप(si));
	cpuhw = शून्य;
	अगर (event->cpu == -1)
		qsi(&si);
	अन्यथा अणु
		/* Event is pinned to a particular CPU, retrieve the per-CPU
		 * sampling काष्ठाure क्रम accessing the CPU-specअगरic QSI.
		 */
		cpuhw = &per_cpu(cpu_hw_sf, event->cpu);
		si = cpuhw->qsi;
	पूर्ण

	/* Check sampling facility authorization and, अगर not authorized,
	 * fall back to other PMUs.  It is safe to check any CPU because
	 * the authorization is identical क्रम all configured CPUs.
	 */
	अगर (!si.as) अणु
		err = -ENOENT;
		जाओ out;
	पूर्ण

	अगर (si.ribm & CPU_MF_SF_RIBM_NOTAV) अणु
		pr_warn("CPU Measurement Facility sampling is temporarily not available\n");
		err = -EBUSY;
		जाओ out;
	पूर्ण

	/* Always enable basic sampling */
	SAMPL_FLAGS(hwc) = PERF_CPUM_SF_BASIC_MODE;

	/* Check अगर diagnostic sampling is requested.  Deny अगर the required
	 * sampling authorization is missing.
	 */
	अगर (attr->config == PERF_EVENT_CPUM_SF_DIAG) अणु
		अगर (!si.ad) अणु
			err = -EPERM;
			जाओ out;
		पूर्ण
		SAMPL_FLAGS(hwc) |= PERF_CPUM_SF_DIAG_MODE;
	पूर्ण

	/* Check and set other sampling flags */
	अगर (attr->config1 & PERF_CPUM_SF_FULL_BLOCKS)
		SAMPL_FLAGS(hwc) |= PERF_CPUM_SF_FULL_BLOCKS;

	err =  __hw_perf_event_init_rate(event, &si);
	अगर (err)
		जाओ out;

	/* Initialize sample data overflow accounting */
	hwc->extra_reg.reg = REG_OVERFLOW;
	OVERFLOW_REG(hwc) = 0;

	/* Use AUX buffer. No need to allocate it by ourself */
	अगर (attr->config == PERF_EVENT_CPUM_SF_DIAG)
		वापस 0;

	/* Allocate the per-CPU sampling buffer using the CPU inक्रमmation
	 * from the event.  If the event is not pinned to a particular
	 * CPU (event->cpu == -1; or cpuhw == शून्य), allocate sampling
	 * buffers क्रम each online CPU.
	 */
	अगर (cpuhw)
		/* Event is pinned to a particular CPU */
		err = allocate_buffers(cpuhw, hwc);
	अन्यथा अणु
		/* Event is not pinned, allocate sampling buffer on
		 * each online CPU
		 */
		क्रम_each_online_cpu(cpu) अणु
			cpuhw = &per_cpu(cpu_hw_sf, cpu);
			err = allocate_buffers(cpuhw, hwc);
			अगर (err)
				अवरोध;
		पूर्ण
	पूर्ण

	/* If PID/TID sampling is active, replace the शेष overflow
	 * handler to extract and resolve the PIDs from the basic-sampling
	 * data entries.
	 */
	अगर (event->attr.sample_type & PERF_SAMPLE_TID)
		अगर (is_शेष_overflow_handler(event))
			event->overflow_handler = cpumsf_output_event_pid;
out:
	वापस err;
पूर्ण

अटल bool is_callchain_event(काष्ठा perf_event *event)
अणु
	u64 sample_type = event->attr.sample_type;

	वापस sample_type & (PERF_SAMPLE_CALLCHAIN | PERF_SAMPLE_REGS_USER |
			      PERF_SAMPLE_STACK_USER);
पूर्ण

अटल पूर्णांक cpumsf_pmu_event_init(काष्ठा perf_event *event)
अणु
	पूर्णांक err;

	/* No support क्रम taken branch sampling */
	/* No support क्रम callchain, stacks and रेजिस्टरs */
	अगर (has_branch_stack(event) || is_callchain_event(event))
		वापस -EOPNOTSUPP;

	चयन (event->attr.type) अणु
	हाल PERF_TYPE_RAW:
		अगर ((event->attr.config != PERF_EVENT_CPUM_SF) &&
		    (event->attr.config != PERF_EVENT_CPUM_SF_DIAG))
			वापस -ENOENT;
		अवरोध;
	हाल PERF_TYPE_HARDWARE:
		/* Support sampling of CPU cycles in addition to the
		 * counter facility.  However, the counter facility
		 * is more precise and, hence, restrict this PMU to
		 * sampling events only.
		 */
		अगर (event->attr.config != PERF_COUNT_HW_CPU_CYCLES)
			वापस -ENOENT;
		अगर (!is_sampling_event(event))
			वापस -ENOENT;
		अवरोध;
	शेष:
		वापस -ENOENT;
	पूर्ण

	/* Check online status of the CPU to which the event is pinned */
	अगर (event->cpu >= 0 && !cpu_online(event->cpu))
		वापस -ENODEV;

	/* Force reset of idle/hv excludes regardless of what the
	 * user requested.
	 */
	अगर (event->attr.exclude_hv)
		event->attr.exclude_hv = 0;
	अगर (event->attr.exclude_idle)
		event->attr.exclude_idle = 0;

	err = __hw_perf_event_init(event);
	अगर (unlikely(err))
		अगर (event->destroy)
			event->destroy(event);
	वापस err;
पूर्ण

अटल व्योम cpumsf_pmu_enable(काष्ठा pmu *pmu)
अणु
	काष्ठा cpu_hw_sf *cpuhw = this_cpu_ptr(&cpu_hw_sf);
	काष्ठा hw_perf_event *hwc;
	पूर्णांक err;

	अगर (cpuhw->flags & PMU_F_ENABLED)
		वापस;

	अगर (cpuhw->flags & PMU_F_ERR_MASK)
		वापस;

	/* Check whether to extent the sampling buffer.
	 *
	 * Two conditions trigger an increase of the sampling buffer क्रम a
	 * perf event:
	 *    1. Postponed buffer allocations from the event initialization.
	 *    2. Sampling overflows that contribute to pending allocations.
	 *
	 * Note that the extend_sampling_buffer() function disables the sampling
	 * facility, but it can be fully re-enabled using sampling controls that
	 * have been saved in cpumsf_pmu_disable().
	 */
	अगर (cpuhw->event) अणु
		hwc = &cpuhw->event->hw;
		अगर (!(SAMPL_DIAG_MODE(hwc))) अणु
			/*
			 * Account number of overflow-designated
			 * buffer extents
			 */
			sfb_account_overflows(cpuhw, hwc);
			extend_sampling_buffer(&cpuhw->sfb, hwc);
		पूर्ण
		/* Rate may be adjusted with ioctl() */
		cpuhw->lsctl.पूर्णांकerval = SAMPL_RATE(&cpuhw->event->hw);
	पूर्ण

	/* (Re)enable the PMU and sampling facility */
	cpuhw->flags |= PMU_F_ENABLED;
	barrier();

	err = lsctl(&cpuhw->lsctl);
	अगर (err) अणु
		cpuhw->flags &= ~PMU_F_ENABLED;
		pr_err("Loading sampling controls failed: op %i err %i\n",
			1, err);
		वापस;
	पूर्ण

	/* Load current program parameter */
	lpp(&S390_lowcore.lpp);

	debug_प्र_लिखो_event(sfdbg, 6, "%s: es %i cs %i ed %i cd %i "
			    "interval %#lx tear %#lx dear %#lx\n", __func__,
			    cpuhw->lsctl.es, cpuhw->lsctl.cs, cpuhw->lsctl.ed,
			    cpuhw->lsctl.cd, cpuhw->lsctl.पूर्णांकerval,
			    cpuhw->lsctl.tear, cpuhw->lsctl.dear);
पूर्ण

अटल व्योम cpumsf_pmu_disable(काष्ठा pmu *pmu)
अणु
	काष्ठा cpu_hw_sf *cpuhw = this_cpu_ptr(&cpu_hw_sf);
	काष्ठा hws_lsctl_request_block inactive;
	काष्ठा hws_qsi_info_block si;
	पूर्णांक err;

	अगर (!(cpuhw->flags & PMU_F_ENABLED))
		वापस;

	अगर (cpuhw->flags & PMU_F_ERR_MASK)
		वापस;

	/* Switch off sampling activation control */
	inactive = cpuhw->lsctl;
	inactive.cs = 0;
	inactive.cd = 0;

	err = lsctl(&inactive);
	अगर (err) अणु
		pr_err("Loading sampling controls failed: op %i err %i\n",
			2, err);
		वापस;
	पूर्ण

	/* Save state of TEAR and DEAR रेजिस्टर contents */
	err = qsi(&si);
	अगर (!err) अणु
		/* TEAR/DEAR values are valid only अगर the sampling facility is
		 * enabled.  Note that cpumsf_pmu_disable() might be called even
		 * क्रम a disabled sampling facility because cpumsf_pmu_enable()
		 * controls the enable/disable state.
		 */
		अगर (si.es) अणु
			cpuhw->lsctl.tear = si.tear;
			cpuhw->lsctl.dear = si.dear;
		पूर्ण
	पूर्ण अन्यथा
		debug_प्र_लिखो_event(sfdbg, 3, "%s: qsi() failed with err %i\n",
				    __func__, err);

	cpuhw->flags &= ~PMU_F_ENABLED;
पूर्ण

/* perf_exclude_event() - Filter event
 * @event:	The perf event
 * @regs:	pt_regs काष्ठाure
 * @sde_regs:	Sample-data-entry (sde) regs काष्ठाure
 *
 * Filter perf events according to their exclude specअगरication.
 *
 * Return non-zero अगर the event shall be excluded.
 */
अटल पूर्णांक perf_exclude_event(काष्ठा perf_event *event, काष्ठा pt_regs *regs,
			      काष्ठा perf_sf_sde_regs *sde_regs)
अणु
	अगर (event->attr.exclude_user && user_mode(regs))
		वापस 1;
	अगर (event->attr.exclude_kernel && !user_mode(regs))
		वापस 1;
	अगर (event->attr.exclude_guest && sde_regs->in_guest)
		वापस 1;
	अगर (event->attr.exclude_host && !sde_regs->in_guest)
		वापस 1;
	वापस 0;
पूर्ण

/* perf_push_sample() - Push samples to perf
 * @event:	The perf event
 * @sample:	Hardware sample data
 *
 * Use the hardware sample data to create perf event sample.  The sample
 * is the pushed to the event subप्रणाली and the function checks क्रम
 * possible event overflows.  If an event overflow occurs, the PMU is
 * stopped.
 *
 * Return non-zero अगर an event overflow occurred.
 */
अटल पूर्णांक perf_push_sample(काष्ठा perf_event *event,
			    काष्ठा hws_basic_entry *basic)
अणु
	पूर्णांक overflow;
	काष्ठा pt_regs regs;
	काष्ठा perf_sf_sde_regs *sde_regs;
	काष्ठा perf_sample_data data;

	/* Setup perf sample */
	perf_sample_data_init(&data, 0, event->hw.last_period);

	/* Setup pt_regs to look like an CPU-measurement बाह्यal पूर्णांकerrupt
	 * using the Program Request Alert code.  The regs.पूर्णांक_parm_दीर्घ
	 * field which is unused contains additional sample-data-entry related
	 * indicators.
	 */
	स_रखो(&regs, 0, माप(regs));
	regs.पूर्णांक_code = 0x1407;
	regs.पूर्णांक_parm = CPU_MF_INT_SF_PRA;
	sde_regs = (काष्ठा perf_sf_sde_regs *) &regs.पूर्णांक_parm_दीर्घ;

	psw_bits(regs.psw).ia	= basic->ia;
	psw_bits(regs.psw).dat	= basic->T;
	psw_bits(regs.psw).रुको = basic->W;
	psw_bits(regs.psw).pstate = basic->P;
	psw_bits(regs.psw).as	= basic->AS;

	/*
	 * Use the hardware provided configuration level to decide अगर the
	 * sample beदीर्घs to a guest or host. If that is not available,
	 * fall back to the following heuristics:
	 * A non-zero guest program parameter always indicates a guest
	 * sample. Some early samples or samples from guests without
	 * lpp usage would be misaccounted to the host. We use the asn
	 * value as an adकरोn heuristic to detect most of these guest samples.
	 * If the value dअगरfers from 0xffff (the host value), we assume to
	 * be a KVM guest.
	 */
	चयन (basic->CL) अणु
	हाल 1: /* logical partition */
		sde_regs->in_guest = 0;
		अवरोध;
	हाल 2: /* भव machine */
		sde_regs->in_guest = 1;
		अवरोध;
	शेष: /* old machine, use heuristics */
		अगर (basic->gpp || basic->prim_asn != 0xffff)
			sde_regs->in_guest = 1;
		अवरोध;
	पूर्ण

	/*
	 * Store the PID value from the sample-data-entry to be
	 * processed and resolved by cpumsf_output_event_pid().
	 */
	data.tid_entry.pid = basic->hpp & LPP_PID_MASK;

	overflow = 0;
	अगर (perf_exclude_event(event, &regs, sde_regs))
		जाओ out;
	अगर (perf_event_overflow(event, &data, &regs)) अणु
		overflow = 1;
		event->pmu->stop(event, 0);
	पूर्ण
	perf_event_update_userpage(event);
out:
	वापस overflow;
पूर्ण

अटल व्योम perf_event_count_update(काष्ठा perf_event *event, u64 count)
अणु
	local64_add(count, &event->count);
पूर्ण

/* hw_collect_samples() - Walk through a sample-data-block and collect samples
 * @event:	The perf event
 * @sdbt:	Sample-data-block table
 * @overflow:	Event overflow counter
 *
 * Walks through a sample-data-block and collects sampling data entries that are
 * then pushed to the perf event subप्रणाली.  Depending on the sampling function,
 * there can be either basic-sampling or combined-sampling data entries.  A
 * combined-sampling data entry consists of a basic- and a diagnostic-sampling
 * data entry.	The sampling function is determined by the flags in the perf
 * event hardware काष्ठाure.  The function always works with a combined-sampling
 * data entry but ignores the the diagnostic portion अगर it is not available.
 *
 * Note that the implementation focuses on basic-sampling data entries and, अगर
 * such an entry is not valid, the entire combined-sampling data entry is
 * ignored.
 *
 * The overflow variables counts the number of samples that has been discarded
 * due to a perf event overflow.
 */
अटल व्योम hw_collect_samples(काष्ठा perf_event *event, अचिन्हित दीर्घ *sdbt,
			       अचिन्हित दीर्घ दीर्घ *overflow)
अणु
	काष्ठा hws_trailer_entry *te;
	काष्ठा hws_basic_entry *sample;

	te = (काष्ठा hws_trailer_entry *) trailer_entry_ptr(*sdbt);
	sample = (काष्ठा hws_basic_entry *) *sdbt;
	जबतक ((अचिन्हित दीर्घ *) sample < (अचिन्हित दीर्घ *) te) अणु
		/* Check क्रम an empty sample */
		अगर (!sample->def)
			अवरोध;

		/* Update perf event period */
		perf_event_count_update(event, SAMPL_RATE(&event->hw));

		/* Check whether sample is valid */
		अगर (sample->def == 0x0001) अणु
			/* If an event overflow occurred, the PMU is stopped to
			 * throttle event delivery.  Reमुख्यing sample data is
			 * discarded.
			 */
			अगर (!*overflow) अणु
				/* Check whether sample is consistent */
				अगर (sample->I == 0 && sample->W == 0) अणु
					/* Deliver sample data to perf */
					*overflow = perf_push_sample(event,
								     sample);
				पूर्ण
			पूर्ण अन्यथा
				/* Count discarded samples */
				*overflow += 1;
		पूर्ण अन्यथा अणु
			debug_प्र_लिखो_event(sfdbg, 4,
					    "%s: Found unknown"
					    " sampling data entry: te->f %i"
					    " basic.def %#4x (%p)\n", __func__,
					    te->f, sample->def, sample);
			/* Sample slot is not yet written or other record.
			 *
			 * This condition can occur अगर the buffer was reused
			 * from a combined basic- and diagnostic-sampling.
			 * If only basic-sampling is then active, entries are
			 * written पूर्णांकo the larger diagnostic entries.
			 * This is typically the हाल क्रम sample-data-blocks
			 * that are not full.  Stop processing अगर the first
			 * invalid क्रमmat was detected.
			 */
			अगर (!te->f)
				अवरोध;
		पूर्ण

		/* Reset sample slot and advance to next sample */
		sample->def = 0;
		sample++;
	पूर्ण
पूर्ण

/* hw_perf_event_update() - Process sampling buffer
 * @event:	The perf event
 * @flush_all:	Flag to also flush partially filled sample-data-blocks
 *
 * Processes the sampling buffer and create perf event samples.
 * The sampling buffer position are retrieved and saved in the TEAR_REG
 * रेजिस्टर of the specअगरied perf event.
 *
 * Only full sample-data-blocks are processed.	Specअगरy the flash_all flag
 * to also walk through partially filled sample-data-blocks.  It is ignored
 * अगर PERF_CPUM_SF_FULL_BLOCKS is set.	The PERF_CPUM_SF_FULL_BLOCKS flag
 * enक्रमces the processing of full sample-data-blocks only (trailer entries
 * with the block-full-indicator bit set).
 */
अटल व्योम hw_perf_event_update(काष्ठा perf_event *event, पूर्णांक flush_all)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा hws_trailer_entry *te;
	अचिन्हित दीर्घ *sdbt;
	अचिन्हित दीर्घ दीर्घ event_overflow, sampl_overflow, num_sdb, te_flags;
	पूर्णांक करोne;

	/*
	 * AUX buffer is used when in diagnostic sampling mode.
	 * No perf events/samples are created.
	 */
	अगर (SAMPL_DIAG_MODE(&event->hw))
		वापस;

	अगर (flush_all && SDB_FULL_BLOCKS(hwc))
		flush_all = 0;

	sdbt = (अचिन्हित दीर्घ *) TEAR_REG(hwc);
	करोne = event_overflow = sampl_overflow = num_sdb = 0;
	जबतक (!करोne) अणु
		/* Get the trailer entry of the sample-data-block */
		te = (काष्ठा hws_trailer_entry *) trailer_entry_ptr(*sdbt);

		/* Leave loop अगर no more work to करो (block full indicator) */
		अगर (!te->f) अणु
			करोne = 1;
			अगर (!flush_all)
				अवरोध;
		पूर्ण

		/* Check the sample overflow count */
		अगर (te->overflow)
			/* Account sample overflows and, अगर a particular limit
			 * is reached, extend the sampling buffer.
			 * For details, see sfb_account_overflows().
			 */
			sampl_overflow += te->overflow;

		/* Timestamps are valid क्रम full sample-data-blocks only */
		debug_प्र_लिखो_event(sfdbg, 6, "%s: sdbt %#lx "
				    "overflow %llu timestamp %#llx\n",
				    __func__, (अचिन्हित दीर्घ)sdbt, te->overflow,
				    (te->f) ? trailer_बारtamp(te) : 0ULL);

		/* Collect all samples from a single sample-data-block and
		 * flag अगर an (perf) event overflow happened.  If so, the PMU
		 * is stopped and reमुख्यing samples will be discarded.
		 */
		hw_collect_samples(event, sdbt, &event_overflow);
		num_sdb++;

		/* Reset trailer (using compare-द्विगुन-and-swap) */
		करो अणु
			te_flags = te->flags & ~SDB_TE_BUFFER_FULL_MASK;
			te_flags |= SDB_TE_ALERT_REQ_MASK;
		पूर्ण जबतक (!cmpxchg_द्विगुन(&te->flags, &te->overflow,
					 te->flags, te->overflow,
					 te_flags, 0ULL));

		/* Advance to next sample-data-block */
		sdbt++;
		अगर (is_link_entry(sdbt))
			sdbt = get_next_sdbt(sdbt);

		/* Update event hardware रेजिस्टरs */
		TEAR_REG(hwc) = (अचिन्हित दीर्घ) sdbt;

		/* Stop processing sample-data अगर all samples of the current
		 * sample-data-block were flushed even अगर it was not full.
		 */
		अगर (flush_all && करोne)
			अवरोध;
	पूर्ण

	/* Account sample overflows in the event hardware काष्ठाure */
	अगर (sampl_overflow)
		OVERFLOW_REG(hwc) = DIV_ROUND_UP(OVERFLOW_REG(hwc) +
						 sampl_overflow, 1 + num_sdb);

	/* Perf_event_overflow() and perf_event_account_पूर्णांकerrupt() limit
	 * the पूर्णांकerrupt rate to an upper limit. Roughly 1000 samples per
	 * task tick.
	 * Hitting this limit results in a large number
	 * of throttled REF_REPORT_THROTTLE entries and the samples
	 * are dropped.
	 * Slightly increase the पूर्णांकerval to aव्योम hitting this limit.
	 */
	अगर (event_overflow) अणु
		SAMPL_RATE(hwc) += DIV_ROUND_UP(SAMPL_RATE(hwc), 10);
		debug_प्र_लिखो_event(sfdbg, 1, "%s: rate adjustment %ld\n",
				    __func__,
				    DIV_ROUND_UP(SAMPL_RATE(hwc), 10));
	पूर्ण

	अगर (sampl_overflow || event_overflow)
		debug_प्र_लिखो_event(sfdbg, 4, "%s: "
				    "overflows: sample %llu event %llu"
				    " total %llu num_sdb %llu\n",
				    __func__, sampl_overflow, event_overflow,
				    OVERFLOW_REG(hwc), num_sdb);
पूर्ण

#घोषणा AUX_SDB_INDEX(aux, i) ((i) % aux->sfb.num_sdb)
#घोषणा AUX_SDB_NUM(aux, start, end) (end >= start ? end - start + 1 : 0)
#घोषणा AUX_SDB_NUM_ALERT(aux) AUX_SDB_NUM(aux, aux->head, aux->alert_mark)
#घोषणा AUX_SDB_NUM_EMPTY(aux) AUX_SDB_NUM(aux, aux->head, aux->empty_mark)

/*
 * Get trailer entry by index of SDB.
 */
अटल काष्ठा hws_trailer_entry *aux_sdb_trailer(काष्ठा aux_buffer *aux,
						 अचिन्हित दीर्घ index)
अणु
	अचिन्हित दीर्घ sdb;

	index = AUX_SDB_INDEX(aux, index);
	sdb = aux->sdb_index[index];
	वापस (काष्ठा hws_trailer_entry *)trailer_entry_ptr(sdb);
पूर्ण

/*
 * Finish sampling on the cpu. Called by cpumsf_pmu_del() with pmu
 * disabled. Collect the full SDBs in AUX buffer which have not reached
 * the poपूर्णांक of alert indicator. And ignore the SDBs which are not
 * full.
 *
 * 1. Scan SDBs to see how much data is there and consume them.
 * 2. Remove alert indicator in the buffer.
 */
अटल व्योम aux_output_end(काष्ठा perf_output_handle *handle)
अणु
	अचिन्हित दीर्घ i, range_scan, idx;
	काष्ठा aux_buffer *aux;
	काष्ठा hws_trailer_entry *te;

	aux = perf_get_aux(handle);
	अगर (!aux)
		वापस;

	range_scan = AUX_SDB_NUM_ALERT(aux);
	क्रम (i = 0, idx = aux->head; i < range_scan; i++, idx++) अणु
		te = aux_sdb_trailer(aux, idx);
		अगर (!(te->flags & SDB_TE_BUFFER_FULL_MASK))
			अवरोध;
	पूर्ण
	/* i is num of SDBs which are full */
	perf_aux_output_end(handle, i << PAGE_SHIFT);

	/* Remove alert indicators in the buffer */
	te = aux_sdb_trailer(aux, aux->alert_mark);
	te->flags &= ~SDB_TE_ALERT_REQ_MASK;

	debug_प्र_लिखो_event(sfdbg, 6, "%s: SDBs %ld range %ld head %ld\n",
			    __func__, i, range_scan, aux->head);
पूर्ण

/*
 * Start sampling on the CPU. Called by cpumsf_pmu_add() when an event
 * is first added to the CPU or rescheduled again to the CPU. It is called
 * with pmu disabled.
 *
 * 1. Reset the trailer of SDBs to get पढ़ोy क्रम new data.
 * 2. Tell the hardware where to put the data by reset the SDBs buffer
 *    head(tear/dear).
 */
अटल पूर्णांक aux_output_begin(काष्ठा perf_output_handle *handle,
			    काष्ठा aux_buffer *aux,
			    काष्ठा cpu_hw_sf *cpuhw)
अणु
	अचिन्हित दीर्घ range;
	अचिन्हित दीर्घ i, range_scan, idx;
	अचिन्हित दीर्घ head, base, offset;
	काष्ठा hws_trailer_entry *te;

	अगर (WARN_ON_ONCE(handle->head & ~PAGE_MASK))
		वापस -EINVAL;

	aux->head = handle->head >> PAGE_SHIFT;
	range = (handle->size + 1) >> PAGE_SHIFT;
	अगर (range <= 1)
		वापस -ENOMEM;

	/*
	 * SDBs between aux->head and aux->empty_mark are alपढ़ोy पढ़ोy
	 * क्रम new data. range_scan is num of SDBs not within them.
	 */
	debug_प्र_लिखो_event(sfdbg, 6,
			    "%s: range %ld head %ld alert %ld empty %ld\n",
			    __func__, range, aux->head, aux->alert_mark,
			    aux->empty_mark);
	अगर (range > AUX_SDB_NUM_EMPTY(aux)) अणु
		range_scan = range - AUX_SDB_NUM_EMPTY(aux);
		idx = aux->empty_mark + 1;
		क्रम (i = 0; i < range_scan; i++, idx++) अणु
			te = aux_sdb_trailer(aux, idx);
			te->flags &= ~(SDB_TE_BUFFER_FULL_MASK |
				       SDB_TE_ALERT_REQ_MASK);
			te->overflow = 0;
		पूर्ण
		/* Save the position of empty SDBs */
		aux->empty_mark = aux->head + range - 1;
	पूर्ण

	/* Set alert indicator */
	aux->alert_mark = aux->head + range/2 - 1;
	te = aux_sdb_trailer(aux, aux->alert_mark);
	te->flags = te->flags | SDB_TE_ALERT_REQ_MASK;

	/* Reset hardware buffer head */
	head = AUX_SDB_INDEX(aux, aux->head);
	base = aux->sdbt_index[head / CPUM_SF_SDB_PER_TABLE];
	offset = head % CPUM_SF_SDB_PER_TABLE;
	cpuhw->lsctl.tear = base + offset * माप(अचिन्हित दीर्घ);
	cpuhw->lsctl.dear = aux->sdb_index[head];

	debug_प्र_लिखो_event(sfdbg, 6, "%s: head %ld alert %ld empty %ld "
			    "index %ld tear %#lx dear %#lx\n", __func__,
			    aux->head, aux->alert_mark, aux->empty_mark,
			    head / CPUM_SF_SDB_PER_TABLE,
			    cpuhw->lsctl.tear, cpuhw->lsctl.dear);

	वापस 0;
पूर्ण

/*
 * Set alert indicator on SDB at index @alert_index जबतक sampler is running.
 *
 * Return true अगर successfully.
 * Return false अगर full indicator is alपढ़ोy set by hardware sampler.
 */
अटल bool aux_set_alert(काष्ठा aux_buffer *aux, अचिन्हित दीर्घ alert_index,
			  अचिन्हित दीर्घ दीर्घ *overflow)
अणु
	अचिन्हित दीर्घ दीर्घ orig_overflow, orig_flags, new_flags;
	काष्ठा hws_trailer_entry *te;

	te = aux_sdb_trailer(aux, alert_index);
	करो अणु
		orig_flags = te->flags;
		*overflow = orig_overflow = te->overflow;
		अगर (orig_flags & SDB_TE_BUFFER_FULL_MASK) अणु
			/*
			 * SDB is alपढ़ोy set by hardware.
			 * Abort and try to set somewhere
			 * behind.
			 */
			वापस false;
		पूर्ण
		new_flags = orig_flags | SDB_TE_ALERT_REQ_MASK;
	पूर्ण जबतक (!cmpxchg_द्विगुन(&te->flags, &te->overflow,
				 orig_flags, orig_overflow,
				 new_flags, 0ULL));
	वापस true;
पूर्ण

/*
 * aux_reset_buffer() - Scan and setup SDBs क्रम new samples
 * @aux:	The AUX buffer to set
 * @range:	The range of SDBs to scan started from aux->head
 * @overflow:	Set to overflow count
 *
 * Set alert indicator on the SDB at index of aux->alert_mark. If this SDB is
 * marked as empty, check अगर it is alपढ़ोy set full by the hardware sampler.
 * If yes, that means new data is alपढ़ोy there beक्रमe we can set an alert
 * indicator. Caller should try to set alert indicator to some position behind.
 *
 * Scan the SDBs in AUX buffer from behind aux->empty_mark. They are used
 * previously and have alपढ़ोy been consumed by user space. Reset these SDBs
 * (clear full indicator and alert indicator) क्रम new data.
 * If aux->alert_mark fall in this area, just set it. Overflow count is
 * recorded जबतक scanning.
 *
 * SDBs between aux->head and aux->empty_mark are alपढ़ोy reset at last समय.
 * and पढ़ोy क्रम new samples. So scanning on this area could be skipped.
 *
 * Return true अगर alert indicator is set successfully and false अगर not.
 */
अटल bool aux_reset_buffer(काष्ठा aux_buffer *aux, अचिन्हित दीर्घ range,
			     अचिन्हित दीर्घ दीर्घ *overflow)
अणु
	अचिन्हित दीर्घ दीर्घ orig_overflow, orig_flags, new_flags;
	अचिन्हित दीर्घ i, range_scan, idx, idx_old;
	काष्ठा hws_trailer_entry *te;

	debug_प्र_लिखो_event(sfdbg, 6, "%s: range %ld head %ld alert %ld "
			    "empty %ld\n", __func__, range, aux->head,
			    aux->alert_mark, aux->empty_mark);
	अगर (range <= AUX_SDB_NUM_EMPTY(aux))
		/*
		 * No need to scan. All SDBs in range are marked as empty.
		 * Just set alert indicator. Should check race with hardware
		 * sampler.
		 */
		वापस aux_set_alert(aux, aux->alert_mark, overflow);

	अगर (aux->alert_mark <= aux->empty_mark)
		/*
		 * Set alert indicator on empty SDB. Should check race
		 * with hardware sampler.
		 */
		अगर (!aux_set_alert(aux, aux->alert_mark, overflow))
			वापस false;

	/*
	 * Scan the SDBs to clear full and alert indicator used previously.
	 * Start scanning from one SDB behind empty_mark. If the new alert
	 * indicator fall पूर्णांकo this range, set it.
	 */
	range_scan = range - AUX_SDB_NUM_EMPTY(aux);
	idx_old = idx = aux->empty_mark + 1;
	क्रम (i = 0; i < range_scan; i++, idx++) अणु
		te = aux_sdb_trailer(aux, idx);
		करो अणु
			orig_flags = te->flags;
			orig_overflow = te->overflow;
			new_flags = orig_flags & ~SDB_TE_BUFFER_FULL_MASK;
			अगर (idx == aux->alert_mark)
				new_flags |= SDB_TE_ALERT_REQ_MASK;
			अन्यथा
				new_flags &= ~SDB_TE_ALERT_REQ_MASK;
		पूर्ण जबतक (!cmpxchg_द्विगुन(&te->flags, &te->overflow,
					 orig_flags, orig_overflow,
					 new_flags, 0ULL));
		*overflow += orig_overflow;
	पूर्ण

	/* Update empty_mark to new position */
	aux->empty_mark = aux->head + range - 1;

	debug_प्र_लिखो_event(sfdbg, 6, "%s: range_scan %ld idx %ld..%ld "
			    "empty %ld\n", __func__, range_scan, idx_old,
			    idx - 1, aux->empty_mark);
	वापस true;
पूर्ण

/*
 * Measurement alert handler क्रम diagnostic mode sampling.
 */
अटल व्योम hw_collect_aux(काष्ठा cpu_hw_sf *cpuhw)
अणु
	काष्ठा aux_buffer *aux;
	पूर्णांक करोne = 0;
	अचिन्हित दीर्घ range = 0, size;
	अचिन्हित दीर्घ दीर्घ overflow = 0;
	काष्ठा perf_output_handle *handle = &cpuhw->handle;
	अचिन्हित दीर्घ num_sdb;

	aux = perf_get_aux(handle);
	अगर (WARN_ON_ONCE(!aux))
		वापस;

	/* Inक्रमm user space new data arrived */
	size = AUX_SDB_NUM_ALERT(aux) << PAGE_SHIFT;
	debug_प्र_लिखो_event(sfdbg, 6, "%s: #alert %ld\n", __func__,
			    size >> PAGE_SHIFT);
	perf_aux_output_end(handle, size);

	num_sdb = aux->sfb.num_sdb;
	जबतक (!करोne) अणु
		/* Get an output handle */
		aux = perf_aux_output_begin(handle, cpuhw->event);
		अगर (handle->size == 0) अणु
			pr_err("The AUX buffer with %lu pages for the "
			       "diagnostic-sampling mode is full\n",
				num_sdb);
			debug_प्र_लिखो_event(sfdbg, 1,
					    "%s: AUX buffer used up\n",
					    __func__);
			अवरोध;
		पूर्ण
		अगर (WARN_ON_ONCE(!aux))
			वापस;

		/* Update head and alert_mark to new position */
		aux->head = handle->head >> PAGE_SHIFT;
		range = (handle->size + 1) >> PAGE_SHIFT;
		अगर (range == 1)
			aux->alert_mark = aux->head;
		अन्यथा
			aux->alert_mark = aux->head + range/2 - 1;

		अगर (aux_reset_buffer(aux, range, &overflow)) अणु
			अगर (!overflow) अणु
				करोne = 1;
				अवरोध;
			पूर्ण
			size = range << PAGE_SHIFT;
			perf_aux_output_end(&cpuhw->handle, size);
			pr_err("Sample data caused the AUX buffer with %lu "
			       "pages to overflow\n", aux->sfb.num_sdb);
			debug_प्र_लिखो_event(sfdbg, 1, "%s: head %ld range %ld "
					    "overflow %lld\n", __func__,
					    aux->head, range, overflow);
		पूर्ण अन्यथा अणु
			size = AUX_SDB_NUM_ALERT(aux) << PAGE_SHIFT;
			perf_aux_output_end(&cpuhw->handle, size);
			debug_प्र_लिखो_event(sfdbg, 6, "%s: head %ld alert %ld "
					    "already full, try another\n",
					    __func__,
					    aux->head, aux->alert_mark);
		पूर्ण
	पूर्ण

	अगर (करोne)
		debug_प्र_लिखो_event(sfdbg, 6, "%s: head %ld alert %ld "
				    "empty %ld\n", __func__, aux->head,
				    aux->alert_mark, aux->empty_mark);
पूर्ण

/*
 * Callback when मुक्तing AUX buffers.
 */
अटल व्योम aux_buffer_मुक्त(व्योम *data)
अणु
	काष्ठा aux_buffer *aux = data;
	अचिन्हित दीर्घ i, num_sdbt;

	अगर (!aux)
		वापस;

	/* Free SDBT. SDB is मुक्तd by the caller */
	num_sdbt = aux->sfb.num_sdbt;
	क्रम (i = 0; i < num_sdbt; i++)
		मुक्त_page(aux->sdbt_index[i]);

	kमुक्त(aux->sdbt_index);
	kमुक्त(aux->sdb_index);
	kमुक्त(aux);

	debug_प्र_लिखो_event(sfdbg, 4, "%s: SDBTs %lu\n", __func__, num_sdbt);
पूर्ण

अटल व्योम aux_sdb_init(अचिन्हित दीर्घ sdb)
अणु
	काष्ठा hws_trailer_entry *te;

	te = (काष्ठा hws_trailer_entry *)trailer_entry_ptr(sdb);

	/* Save घड़ी base */
	te->घड़ी_base = 1;
	te->progusage2 = tod_घड़ी_base.tod;
पूर्ण

/*
 * aux_buffer_setup() - Setup AUX buffer क्रम diagnostic mode sampling
 * @event:	Event the buffer is setup क्रम, event->cpu == -1 means current
 * @pages:	Array of poपूर्णांकers to buffer pages passed from perf core
 * @nr_pages:	Total pages
 * @snapshot:	Flag क्रम snapshot mode
 *
 * This is the callback when setup an event using AUX buffer. Perf tool can
 * trigger this by an additional mmap() call on the event. Unlike the buffer
 * क्रम basic samples, AUX buffer beदीर्घs to the event. It is scheduled with
 * the task among online cpus when it is a per-thपढ़ो event.
 *
 * Return the निजी AUX buffer काष्ठाure अगर success or शून्य अगर fails.
 */
अटल व्योम *aux_buffer_setup(काष्ठा perf_event *event, व्योम **pages,
			      पूर्णांक nr_pages, bool snapshot)
अणु
	काष्ठा sf_buffer *sfb;
	काष्ठा aux_buffer *aux;
	अचिन्हित दीर्घ *new, *tail;
	पूर्णांक i, n_sdbt;

	अगर (!nr_pages || !pages)
		वापस शून्य;

	अगर (nr_pages > CPUM_SF_MAX_SDB * CPUM_SF_SDB_DIAG_FACTOR) अणु
		pr_err("AUX buffer size (%i pages) is larger than the "
		       "maximum sampling buffer limit\n",
		       nr_pages);
		वापस शून्य;
	पूर्ण अन्यथा अगर (nr_pages < CPUM_SF_MIN_SDB * CPUM_SF_SDB_DIAG_FACTOR) अणु
		pr_err("AUX buffer size (%i pages) is less than the "
		       "minimum sampling buffer limit\n",
		       nr_pages);
		वापस शून्य;
	पूर्ण

	/* Allocate aux_buffer काष्ठा क्रम the event */
	aux = kzalloc(माप(काष्ठा aux_buffer), GFP_KERNEL);
	अगर (!aux)
		जाओ no_aux;
	sfb = &aux->sfb;

	/* Allocate sdbt_index क्रम fast reference */
	n_sdbt = DIV_ROUND_UP(nr_pages, CPUM_SF_SDB_PER_TABLE);
	aux->sdbt_index = kदो_स्मृति_array(n_sdbt, माप(व्योम *), GFP_KERNEL);
	अगर (!aux->sdbt_index)
		जाओ no_sdbt_index;

	/* Allocate sdb_index क्रम fast reference */
	aux->sdb_index = kदो_स्मृति_array(nr_pages, माप(व्योम *), GFP_KERNEL);
	अगर (!aux->sdb_index)
		जाओ no_sdb_index;

	/* Allocate the first SDBT */
	sfb->num_sdbt = 0;
	sfb->sdbt = (अचिन्हित दीर्घ *) get_zeroed_page(GFP_KERNEL);
	अगर (!sfb->sdbt)
		जाओ no_sdbt;
	aux->sdbt_index[sfb->num_sdbt++] = (अचिन्हित दीर्घ)sfb->sdbt;
	tail = sfb->tail = sfb->sdbt;

	/*
	 * Link the provided pages of AUX buffer to SDBT.
	 * Allocate SDBT अगर needed.
	 */
	क्रम (i = 0; i < nr_pages; i++, tail++) अणु
		अगर (require_table_link(tail)) अणु
			new = (अचिन्हित दीर्घ *) get_zeroed_page(GFP_KERNEL);
			अगर (!new)
				जाओ no_sdbt;
			aux->sdbt_index[sfb->num_sdbt++] = (अचिन्हित दीर्घ)new;
			/* Link current page to tail of chain */
			*tail = (अचिन्हित दीर्घ)(व्योम *) new + 1;
			tail = new;
		पूर्ण
		/* Tail is the entry in a SDBT */
		*tail = (अचिन्हित दीर्घ)pages[i];
		aux->sdb_index[i] = (अचिन्हित दीर्घ)pages[i];
		aux_sdb_init((अचिन्हित दीर्घ)pages[i]);
	पूर्ण
	sfb->num_sdb = nr_pages;

	/* Link the last entry in the SDBT to the first SDBT */
	*tail = (अचिन्हित दीर्घ) sfb->sdbt + 1;
	sfb->tail = tail;

	/*
	 * Initial all SDBs are zeroed. Mark it as empty.
	 * So there is no need to clear the full indicator
	 * when this event is first added.
	 */
	aux->empty_mark = sfb->num_sdb - 1;

	debug_प्र_लिखो_event(sfdbg, 4, "%s: SDBTs %lu SDBs %lu\n", __func__,
			    sfb->num_sdbt, sfb->num_sdb);

	वापस aux;

no_sdbt:
	/* SDBs (AUX buffer pages) are मुक्तd by caller */
	क्रम (i = 0; i < sfb->num_sdbt; i++)
		मुक्त_page(aux->sdbt_index[i]);
	kमुक्त(aux->sdb_index);
no_sdb_index:
	kमुक्त(aux->sdbt_index);
no_sdbt_index:
	kमुक्त(aux);
no_aux:
	वापस शून्य;
पूर्ण

अटल व्योम cpumsf_pmu_पढ़ो(काष्ठा perf_event *event)
अणु
	/* Nothing to करो ... updates are पूर्णांकerrupt-driven */
पूर्ण

/* Check अगर the new sampling period/freqeuncy is appropriate.
 *
 * Return non-zero on error and zero on passed checks.
 */
अटल पूर्णांक cpumsf_pmu_check_period(काष्ठा perf_event *event, u64 value)
अणु
	काष्ठा hws_qsi_info_block si;
	अचिन्हित दीर्घ rate;
	bool करो_freq;

	स_रखो(&si, 0, माप(si));
	अगर (event->cpu == -1) अणु
		अगर (qsi(&si))
			वापस -ENODEV;
	पूर्ण अन्यथा अणु
		/* Event is pinned to a particular CPU, retrieve the per-CPU
		 * sampling काष्ठाure क्रम accessing the CPU-specअगरic QSI.
		 */
		काष्ठा cpu_hw_sf *cpuhw = &per_cpu(cpu_hw_sf, event->cpu);

		si = cpuhw->qsi;
	पूर्ण

	करो_freq = !!SAMPLE_FREQ_MODE(&event->hw);
	rate = getrate(करो_freq, value, &si);
	अगर (!rate)
		वापस -EINVAL;

	event->attr.sample_period = rate;
	SAMPL_RATE(&event->hw) = rate;
	hw_init_period(&event->hw, SAMPL_RATE(&event->hw));
	debug_प्र_लिखो_event(sfdbg, 4, "%s:"
			    " cpu %d value %#llx period %#llx freq %d\n",
			    __func__, event->cpu, value,
			    event->attr.sample_period, करो_freq);
	वापस 0;
पूर्ण

/* Activate sampling control.
 * Next call of pmu_enable() starts sampling.
 */
अटल व्योम cpumsf_pmu_start(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा cpu_hw_sf *cpuhw = this_cpu_ptr(&cpu_hw_sf);

	अगर (WARN_ON_ONCE(!(event->hw.state & PERF_HES_STOPPED)))
		वापस;

	अगर (flags & PERF_EF_RELOAD)
		WARN_ON_ONCE(!(event->hw.state & PERF_HES_UPTODATE));

	perf_pmu_disable(event->pmu);
	event->hw.state = 0;
	cpuhw->lsctl.cs = 1;
	अगर (SAMPL_DIAG_MODE(&event->hw))
		cpuhw->lsctl.cd = 1;
	perf_pmu_enable(event->pmu);
पूर्ण

/* Deactivate sampling control.
 * Next call of pmu_enable() stops sampling.
 */
अटल व्योम cpumsf_pmu_stop(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा cpu_hw_sf *cpuhw = this_cpu_ptr(&cpu_hw_sf);

	अगर (event->hw.state & PERF_HES_STOPPED)
		वापस;

	perf_pmu_disable(event->pmu);
	cpuhw->lsctl.cs = 0;
	cpuhw->lsctl.cd = 0;
	event->hw.state |= PERF_HES_STOPPED;

	अगर ((flags & PERF_EF_UPDATE) && !(event->hw.state & PERF_HES_UPTODATE)) अणु
		hw_perf_event_update(event, 1);
		event->hw.state |= PERF_HES_UPTODATE;
	पूर्ण
	perf_pmu_enable(event->pmu);
पूर्ण

अटल पूर्णांक cpumsf_pmu_add(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा cpu_hw_sf *cpuhw = this_cpu_ptr(&cpu_hw_sf);
	काष्ठा aux_buffer *aux;
	पूर्णांक err;

	अगर (cpuhw->flags & PMU_F_IN_USE)
		वापस -EAGAIN;

	अगर (!SAMPL_DIAG_MODE(&event->hw) && !cpuhw->sfb.sdbt)
		वापस -EINVAL;

	err = 0;
	perf_pmu_disable(event->pmu);

	event->hw.state = PERF_HES_UPTODATE | PERF_HES_STOPPED;

	/* Set up sampling controls.  Always program the sampling रेजिस्टर
	 * using the SDB-table start.  Reset TEAR_REG event hardware रेजिस्टर
	 * that is used by hw_perf_event_update() to store the sampling buffer
	 * position after samples have been flushed.
	 */
	cpuhw->lsctl.s = 0;
	cpuhw->lsctl.h = 1;
	cpuhw->lsctl.पूर्णांकerval = SAMPL_RATE(&event->hw);
	अगर (!SAMPL_DIAG_MODE(&event->hw)) अणु
		cpuhw->lsctl.tear = (अचिन्हित दीर्घ) cpuhw->sfb.sdbt;
		cpuhw->lsctl.dear = *(अचिन्हित दीर्घ *) cpuhw->sfb.sdbt;
		TEAR_REG(&event->hw) = (अचिन्हित दीर्घ) cpuhw->sfb.sdbt;
	पूर्ण

	/* Ensure sampling functions are in the disabled state.  If disabled,
	 * चयन on sampling enable control. */
	अगर (WARN_ON_ONCE(cpuhw->lsctl.es == 1 || cpuhw->lsctl.ed == 1)) अणु
		err = -EAGAIN;
		जाओ out;
	पूर्ण
	अगर (SAMPL_DIAG_MODE(&event->hw)) अणु
		aux = perf_aux_output_begin(&cpuhw->handle, event);
		अगर (!aux) अणु
			err = -EINVAL;
			जाओ out;
		पूर्ण
		err = aux_output_begin(&cpuhw->handle, aux, cpuhw);
		अगर (err)
			जाओ out;
		cpuhw->lsctl.ed = 1;
	पूर्ण
	cpuhw->lsctl.es = 1;

	/* Set in_use flag and store event */
	cpuhw->event = event;
	cpuhw->flags |= PMU_F_IN_USE;

	अगर (flags & PERF_EF_START)
		cpumsf_pmu_start(event, PERF_EF_RELOAD);
out:
	perf_event_update_userpage(event);
	perf_pmu_enable(event->pmu);
	वापस err;
पूर्ण

अटल व्योम cpumsf_pmu_del(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा cpu_hw_sf *cpuhw = this_cpu_ptr(&cpu_hw_sf);

	perf_pmu_disable(event->pmu);
	cpumsf_pmu_stop(event, PERF_EF_UPDATE);

	cpuhw->lsctl.es = 0;
	cpuhw->lsctl.ed = 0;
	cpuhw->flags &= ~PMU_F_IN_USE;
	cpuhw->event = शून्य;

	अगर (SAMPL_DIAG_MODE(&event->hw))
		aux_output_end(&cpuhw->handle);
	perf_event_update_userpage(event);
	perf_pmu_enable(event->pmu);
पूर्ण

CPUMF_EVENT_ATTR(SF, SF_CYCLES_BASIC, PERF_EVENT_CPUM_SF);
CPUMF_EVENT_ATTR(SF, SF_CYCLES_BASIC_DIAG, PERF_EVENT_CPUM_SF_DIAG);

/* Attribute list क्रम CPU_SF.
 *
 * The availablitiy depends on the CPU_MF sampling facility authorization
 * क्रम basic + diagnositic samples. This is determined at initialization
 * समय by the sampling facility device driver.
 * If the authorization क्रम basic samples is turned off, it should be
 * also turned off क्रम diagnostic sampling.
 *
 * During initialization of the device driver, check the authorization
 * level क्रम diagnostic sampling and installs the attribute
 * file क्रम diagnostic sampling अगर necessary.
 *
 * For now install a placeholder to reference all possible attributes:
 * SF_CYCLES_BASIC and SF_CYCLES_BASIC_DIAG.
 * Add another entry क्रम the final शून्य poपूर्णांकer.
 */
क्रमागत अणु
	SF_CYCLES_BASIC_ATTR_IDX = 0,
	SF_CYCLES_BASIC_DIAG_ATTR_IDX,
	SF_CYCLES_ATTR_MAX
पूर्ण;

अटल काष्ठा attribute *cpumsf_pmu_events_attr[SF_CYCLES_ATTR_MAX + 1] = अणु
	[SF_CYCLES_BASIC_ATTR_IDX] = CPUMF_EVENT_PTR(SF, SF_CYCLES_BASIC)
पूर्ण;

PMU_FORMAT_ATTR(event, "config:0-63");

अटल काष्ठा attribute *cpumsf_pmu_क्रमmat_attr[] = अणु
	&क्रमmat_attr_event.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group cpumsf_pmu_events_group = अणु
	.name = "events",
	.attrs = cpumsf_pmu_events_attr,
पूर्ण;

अटल काष्ठा attribute_group cpumsf_pmu_क्रमmat_group = अणु
	.name = "format",
	.attrs = cpumsf_pmu_क्रमmat_attr,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *cpumsf_pmu_attr_groups[] = अणु
	&cpumsf_pmu_events_group,
	&cpumsf_pmu_क्रमmat_group,
	शून्य,
पूर्ण;

अटल काष्ठा pmu cpumf_sampling = अणु
	.pmu_enable   = cpumsf_pmu_enable,
	.pmu_disable  = cpumsf_pmu_disable,

	.event_init   = cpumsf_pmu_event_init,
	.add	      = cpumsf_pmu_add,
	.del	      = cpumsf_pmu_del,

	.start	      = cpumsf_pmu_start,
	.stop	      = cpumsf_pmu_stop,
	.पढ़ो	      = cpumsf_pmu_पढ़ो,

	.attr_groups  = cpumsf_pmu_attr_groups,

	.setup_aux    = aux_buffer_setup,
	.मुक्त_aux     = aux_buffer_मुक्त,

	.check_period = cpumsf_pmu_check_period,
पूर्ण;

अटल व्योम cpumf_measurement_alert(काष्ठा ext_code ext_code,
				    अचिन्हित पूर्णांक alert, अचिन्हित दीर्घ unused)
अणु
	काष्ठा cpu_hw_sf *cpuhw;

	अगर (!(alert & CPU_MF_INT_SF_MASK))
		वापस;
	inc_irq_stat(IRQEXT_CMS);
	cpuhw = this_cpu_ptr(&cpu_hw_sf);

	/* Measurement alerts are shared and might happen when the PMU
	 * is not reserved.  Ignore these alerts in this हाल. */
	अगर (!(cpuhw->flags & PMU_F_RESERVED))
		वापस;

	/* The processing below must take care of multiple alert events that
	 * might be indicated concurrently. */

	/* Program alert request */
	अगर (alert & CPU_MF_INT_SF_PRA) अणु
		अगर (cpuhw->flags & PMU_F_IN_USE)
			अगर (SAMPL_DIAG_MODE(&cpuhw->event->hw))
				hw_collect_aux(cpuhw);
			अन्यथा
				hw_perf_event_update(cpuhw->event, 0);
		अन्यथा
			WARN_ON_ONCE(!(cpuhw->flags & PMU_F_IN_USE));
	पूर्ण

	/* Report measurement alerts only क्रम non-PRA codes */
	अगर (alert != CPU_MF_INT_SF_PRA)
		debug_प्र_लिखो_event(sfdbg, 6, "%s: alert %#x\n", __func__,
				    alert);

	/* Sampling authorization change request */
	अगर (alert & CPU_MF_INT_SF_SACA)
		qsi(&cpuhw->qsi);

	/* Loss of sample data due to high-priority machine activities */
	अगर (alert & CPU_MF_INT_SF_LSDA) अणु
		pr_err("Sample data was lost\n");
		cpuhw->flags |= PMU_F_ERR_LSDA;
		sf_disable();
	पूर्ण

	/* Invalid sampling buffer entry */
	अगर (alert & (CPU_MF_INT_SF_IAE|CPU_MF_INT_SF_ISE)) अणु
		pr_err("A sampling buffer entry is incorrect (alert=0x%x)\n",
		       alert);
		cpuhw->flags |= PMU_F_ERR_IBE;
		sf_disable();
	पूर्ण
पूर्ण

अटल पूर्णांक cpusf_pmu_setup(अचिन्हित पूर्णांक cpu, पूर्णांक flags)
अणु
	/* Ignore the notअगरication अगर no events are scheduled on the PMU.
	 * This might be racy...
	 */
	अगर (!atomic_पढ़ो(&num_events))
		वापस 0;

	local_irq_disable();
	setup_pmc_cpu(&flags);
	local_irq_enable();
	वापस 0;
पूर्ण

अटल पूर्णांक s390_pmu_sf_online_cpu(अचिन्हित पूर्णांक cpu)
अणु
	वापस cpusf_pmu_setup(cpu, PMC_INIT);
पूर्ण

अटल पूर्णांक s390_pmu_sf_offline_cpu(अचिन्हित पूर्णांक cpu)
अणु
	वापस cpusf_pmu_setup(cpu, PMC_RELEASE);
पूर्ण

अटल पूर्णांक param_get_sfb_size(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp)
अणु
	अगर (!cpum_sf_avail())
		वापस -ENODEV;
	वापस प्र_लिखो(buffer, "%lu,%lu", CPUM_SF_MIN_SDB, CPUM_SF_MAX_SDB);
पूर्ण

अटल पूर्णांक param_set_sfb_size(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक rc;
	अचिन्हित दीर्घ min, max;

	अगर (!cpum_sf_avail())
		वापस -ENODEV;
	अगर (!val || !म_माप(val))
		वापस -EINVAL;

	/* Valid parameter values: "min,max" or "max" */
	min = CPUM_SF_MIN_SDB;
	max = CPUM_SF_MAX_SDB;
	अगर (म_अक्षर(val, ','))
		rc = (माला_पूछो(val, "%lu,%lu", &min, &max) == 2) ? 0 : -EINVAL;
	अन्यथा
		rc = kम_से_अदीर्घ(val, 10, &max);

	अगर (min < 2 || min >= max || max > get_num_physpages())
		rc = -EINVAL;
	अगर (rc)
		वापस rc;

	sfb_set_limits(min, max);
	pr_info("The sampling buffer limits have changed to: "
		"min %lu max %lu (diag %lu)\n",
		CPUM_SF_MIN_SDB, CPUM_SF_MAX_SDB, CPUM_SF_SDB_DIAG_FACTOR);
	वापस 0;
पूर्ण

#घोषणा param_check_sfb_size(name, p) __param_check(name, p, व्योम)
अटल स्थिर काष्ठा kernel_param_ops param_ops_sfb_size = अणु
	.set = param_set_sfb_size,
	.get = param_get_sfb_size,
पूर्ण;

#घोषणा RS_INIT_FAILURE_QSI	  0x0001
#घोषणा RS_INIT_FAILURE_BSDES	  0x0002
#घोषणा RS_INIT_FAILURE_ALRT	  0x0003
#घोषणा RS_INIT_FAILURE_PERF	  0x0004
अटल व्योम __init pr_cpumsf_err(अचिन्हित पूर्णांक reason)
अणु
	pr_err("Sampling facility support for perf is not available: "
	       "reason %#x\n", reason);
पूर्ण

अटल पूर्णांक __init init_cpum_sampling_pmu(व्योम)
अणु
	काष्ठा hws_qsi_info_block si;
	पूर्णांक err;

	अगर (!cpum_sf_avail())
		वापस -ENODEV;

	स_रखो(&si, 0, माप(si));
	अगर (qsi(&si)) अणु
		pr_cpumsf_err(RS_INIT_FAILURE_QSI);
		वापस -ENODEV;
	पूर्ण

	अगर (!si.as && !si.ad)
		वापस -ENODEV;

	अगर (si.bsdes != माप(काष्ठा hws_basic_entry)) अणु
		pr_cpumsf_err(RS_INIT_FAILURE_BSDES);
		वापस -EINVAL;
	पूर्ण

	अगर (si.ad) अणु
		sfb_set_limits(CPUM_SF_MIN_SDB, CPUM_SF_MAX_SDB);
		/* Sampling of diagnostic data authorized,
		 * install event पूर्णांकo attribute list of PMU device.
		 */
		cpumsf_pmu_events_attr[SF_CYCLES_BASIC_DIAG_ATTR_IDX] =
			CPUMF_EVENT_PTR(SF, SF_CYCLES_BASIC_DIAG);
	पूर्ण

	sfdbg = debug_रेजिस्टर(KMSG_COMPONENT, 2, 1, 80);
	अगर (!sfdbg) अणु
		pr_err("Registering for s390dbf failed\n");
		वापस -ENOMEM;
	पूर्ण
	debug_रेजिस्टर_view(sfdbg, &debug_प्र_लिखो_view);

	err = रेजिस्टर_बाह्यal_irq(EXT_IRQ_MEASURE_ALERT,
				    cpumf_measurement_alert);
	अगर (err) अणु
		pr_cpumsf_err(RS_INIT_FAILURE_ALRT);
		debug_unरेजिस्टर(sfdbg);
		जाओ out;
	पूर्ण

	err = perf_pmu_रेजिस्टर(&cpumf_sampling, "cpum_sf", PERF_TYPE_RAW);
	अगर (err) अणु
		pr_cpumsf_err(RS_INIT_FAILURE_PERF);
		unरेजिस्टर_बाह्यal_irq(EXT_IRQ_MEASURE_ALERT,
					cpumf_measurement_alert);
		debug_unरेजिस्टर(sfdbg);
		जाओ out;
	पूर्ण

	cpuhp_setup_state(CPUHP_AP_PERF_S390_SF_ONLINE, "perf/s390/sf:online",
			  s390_pmu_sf_online_cpu, s390_pmu_sf_offline_cpu);
out:
	वापस err;
पूर्ण

arch_initcall(init_cpum_sampling_pmu);
core_param(cpum_sfb_size, CPUM_SF_MAX_SDB, sfb_size, 0644);
