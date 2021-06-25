<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#घोषणा pr_fmt(fmt)	"papr-scm: " fmt

#समावेश <linux/of.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>
#समावेश <linux/ndctl.h>
#समावेश <linux/sched.h>
#समावेश <linux/libnvdimm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/seq_buf.h>
#समावेश <linux/nd.h>

#समावेश <यंत्र/plpar_wrappers.h>
#समावेश <यंत्र/papr_pdsm.h>
#समावेश <यंत्र/mce.h>

#घोषणा BIND_ANY_ADDR (~0ul)

#घोषणा PAPR_SCM_DIMM_CMD_MASK \
	((1ul << ND_CMD_GET_CONFIG_SIZE) | \
	 (1ul << ND_CMD_GET_CONFIG_DATA) | \
	 (1ul << ND_CMD_SET_CONFIG_DATA) | \
	 (1ul << ND_CMD_CALL))

/* DIMM health biपंचांगap biपंचांगap indicators */
/* SCM device is unable to persist memory contents */
#घोषणा PAPR_PMEM_UNARMED                   (1ULL << (63 - 0))
/* SCM device failed to persist memory contents */
#घोषणा PAPR_PMEM_SHUTDOWN_सूचीTY            (1ULL << (63 - 1))
/* SCM device contents are persisted from previous IPL */
#घोषणा PAPR_PMEM_SHUTDOWN_CLEAN            (1ULL << (63 - 2))
/* SCM device contents are not persisted from previous IPL */
#घोषणा PAPR_PMEM_EMPTY                     (1ULL << (63 - 3))
/* SCM device memory lअगरe reमुख्यing is critically low */
#घोषणा PAPR_PMEM_HEALTH_CRITICAL           (1ULL << (63 - 4))
/* SCM device will be garded off next IPL due to failure */
#घोषणा PAPR_PMEM_HEALTH_FATAL              (1ULL << (63 - 5))
/* SCM contents cannot persist due to current platक्रमm health status */
#घोषणा PAPR_PMEM_HEALTH_UNHEALTHY          (1ULL << (63 - 6))
/* SCM device is unable to persist memory contents in certain conditions */
#घोषणा PAPR_PMEM_HEALTH_NON_CRITICAL       (1ULL << (63 - 7))
/* SCM device is encrypted */
#घोषणा PAPR_PMEM_ENCRYPTED                 (1ULL << (63 - 8))
/* SCM device has been scrubbed and locked */
#घोषणा PAPR_PMEM_SCRUBBED_AND_LOCKED       (1ULL << (63 - 9))

/* Bits status indicators क्रम health biपंचांगap indicating unarmed dimm */
#घोषणा PAPR_PMEM_UNARMED_MASK (PAPR_PMEM_UNARMED |		\
				PAPR_PMEM_HEALTH_UNHEALTHY)

/* Bits status indicators क्रम health biपंचांगap indicating unflushed dimm */
#घोषणा PAPR_PMEM_BAD_SHUTDOWN_MASK (PAPR_PMEM_SHUTDOWN_सूचीTY)

/* Bits status indicators क्रम health biपंचांगap indicating unrestored dimm */
#घोषणा PAPR_PMEM_BAD_RESTORE_MASK  (PAPR_PMEM_EMPTY)

/* Bit status indicators क्रम smart event notअगरication */
#घोषणा PAPR_PMEM_SMART_EVENT_MASK (PAPR_PMEM_HEALTH_CRITICAL | \
				    PAPR_PMEM_HEALTH_FATAL |	\
				    PAPR_PMEM_HEALTH_UNHEALTHY)

#घोषणा PAPR_SCM_PERF_STATS_EYECATCHER __stringअगरy(SCMSTATS)
#घोषणा PAPR_SCM_PERF_STATS_VERSION 0x1

/* Struct holding a single perक्रमmance metric */
काष्ठा papr_scm_perf_stat अणु
	u8 stat_id[8];
	__be64 stat_val;
पूर्ण __packed;

/* Struct exchanged between kernel and PHYP क्रम fetching drc perf stats */
काष्ठा papr_scm_perf_stats अणु
	u8 eye_catcher[8];
	/* Should be PAPR_SCM_PERF_STATS_VERSION */
	__be32 stats_version;
	/* Number of stats following */
	__be32 num_statistics;
	/* zero or more perक्रमmance matrics */
	काष्ठा papr_scm_perf_stat scm_statistic[];
पूर्ण __packed;

/* निजी काष्ठा associated with each region */
काष्ठा papr_scm_priv अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा device_node *dn;
	uपूर्णांक32_t drc_index;
	uपूर्णांक64_t blocks;
	uपूर्णांक64_t block_size;
	पूर्णांक metadata_size;
	bool is_अस्थिर;
	bool hcall_flush_required;

	uपूर्णांक64_t bound_addr;

	काष्ठा nvdimm_bus_descriptor bus_desc;
	काष्ठा nvdimm_bus *bus;
	काष्ठा nvdimm *nvdimm;
	काष्ठा resource res;
	काष्ठा nd_region *region;
	काष्ठा nd_पूर्णांकerleave_set nd_set;
	काष्ठा list_head region_list;

	/* Protect dimm health data from concurrent पढ़ो/ग_लिखोs */
	काष्ठा mutex health_mutex;

	/* Last समय the health inक्रमmation of the dimm was updated */
	अचिन्हित दीर्घ lasthealth_jअगरfies;

	/* Health inक्रमmation क्रम the dimm */
	u64 health_biपंचांगap;

	/* length of the stat buffer as expected by phyp */
	माप_प्रकार stat_buffer_len;
पूर्ण;

अटल पूर्णांक papr_scm_pmem_flush(काष्ठा nd_region *nd_region,
			       काष्ठा bio *bio __maybe_unused)
अणु
	काष्ठा papr_scm_priv *p = nd_region_provider_data(nd_region);
	अचिन्हित दीर्घ ret_buf[PLPAR_HCALL_बफ_मानE], token = 0;
	दीर्घ rc;

	dev_dbg(&p->pdev->dev, "flush drc 0x%x", p->drc_index);

	करो अणु
		rc = plpar_hcall(H_SCM_FLUSH, ret_buf, p->drc_index, token);
		token = ret_buf[0];

		/* Check अगर we are stalled क्रम some समय */
		अगर (H_IS_LONG_BUSY(rc)) अणु
			msleep(get_दीर्घbusy_msecs(rc));
			rc = H_BUSY;
		पूर्ण अन्यथा अगर (rc == H_BUSY) अणु
			cond_resched();
		पूर्ण
	पूर्ण जबतक (rc == H_BUSY);

	अगर (rc) अणु
		dev_err(&p->pdev->dev, "flush error: %ld", rc);
		rc = -EIO;
	पूर्ण अन्यथा अणु
		dev_dbg(&p->pdev->dev, "flush drc 0x%x complete", p->drc_index);
	पूर्ण

	वापस rc;
पूर्ण

अटल LIST_HEAD(papr_nd_regions);
अटल DEFINE_MUTEX(papr_ndr_lock);

अटल पूर्णांक drc_pmem_bind(काष्ठा papr_scm_priv *p)
अणु
	अचिन्हित दीर्घ ret[PLPAR_HCALL_बफ_मानE];
	uपूर्णांक64_t saved = 0;
	uपूर्णांक64_t token;
	पूर्णांक64_t rc;

	/*
	 * When the hypervisor cannot map all the requested memory in a single
	 * hcall it वापसs H_BUSY and we call again with the token until
	 * we get H_SUCCESS. Aborting the retry loop beक्रमe getting H_SUCCESS
	 * leave the प्रणाली in an undefined state, so we रुको.
	 */
	token = 0;

	करो अणु
		rc = plpar_hcall(H_SCM_BIND_MEM, ret, p->drc_index, 0,
				p->blocks, BIND_ANY_ADDR, token);
		token = ret[0];
		अगर (!saved)
			saved = ret[1];
		cond_resched();
	पूर्ण जबतक (rc == H_BUSY);

	अगर (rc)
		वापस rc;

	p->bound_addr = saved;
	dev_dbg(&p->pdev->dev, "bound drc 0x%x to 0x%lx\n",
		p->drc_index, (अचिन्हित दीर्घ)saved);
	वापस rc;
पूर्ण

अटल व्योम drc_pmem_unbind(काष्ठा papr_scm_priv *p)
अणु
	अचिन्हित दीर्घ ret[PLPAR_HCALL_बफ_मानE];
	uपूर्णांक64_t token = 0;
	पूर्णांक64_t rc;

	dev_dbg(&p->pdev->dev, "unbind drc 0x%x\n", p->drc_index);

	/* NB: unbind has the same retry requirements as drc_pmem_bind() */
	करो अणु

		/* Unbind of all SCM resources associated with drcIndex */
		rc = plpar_hcall(H_SCM_UNBIND_ALL, ret, H_UNBIND_SCOPE_DRC,
				 p->drc_index, token);
		token = ret[0];

		/* Check अगर we are stalled क्रम some समय */
		अगर (H_IS_LONG_BUSY(rc)) अणु
			msleep(get_दीर्घbusy_msecs(rc));
			rc = H_BUSY;
		पूर्ण अन्यथा अगर (rc == H_BUSY) अणु
			cond_resched();
		पूर्ण

	पूर्ण जबतक (rc == H_BUSY);

	अगर (rc)
		dev_err(&p->pdev->dev, "unbind error: %lld\n", rc);
	अन्यथा
		dev_dbg(&p->pdev->dev, "unbind drc 0x%x complete\n",
			p->drc_index);

	वापस;
पूर्ण

अटल पूर्णांक drc_pmem_query_n_bind(काष्ठा papr_scm_priv *p)
अणु
	अचिन्हित दीर्घ start_addr;
	अचिन्हित दीर्घ end_addr;
	अचिन्हित दीर्घ ret[PLPAR_HCALL_बफ_मानE];
	पूर्णांक64_t rc;


	rc = plpar_hcall(H_SCM_QUERY_BLOCK_MEM_BINDING, ret,
			 p->drc_index, 0);
	अगर (rc)
		जाओ err_out;
	start_addr = ret[0];

	/* Make sure the full region is bound. */
	rc = plpar_hcall(H_SCM_QUERY_BLOCK_MEM_BINDING, ret,
			 p->drc_index, p->blocks - 1);
	अगर (rc)
		जाओ err_out;
	end_addr = ret[0];

	अगर ((end_addr - start_addr) != ((p->blocks - 1) * p->block_size))
		जाओ err_out;

	p->bound_addr = start_addr;
	dev_dbg(&p->pdev->dev, "bound drc 0x%x to 0x%lx\n", p->drc_index, start_addr);
	वापस rc;

err_out:
	dev_info(&p->pdev->dev,
		 "Failed to query, trying an unbind followed by bind");
	drc_pmem_unbind(p);
	वापस drc_pmem_bind(p);
पूर्ण

/*
 * Query the Dimm perक्रमmance stats from PHYP and copy them (अगर वापसed) to
 * provided काष्ठा papr_scm_perf_stats instance 'stats' that can hold atleast
 * (num_stats + header) bytes.
 * - If buff_stats == शून्य the वापस value is the size in byes of the buffer
 * needed to hold all supported perक्रमmance-statistics.
 * - If buff_stats != शून्य and num_stats == 0 then we copy all known
 * perक्रमmance-statistics to 'buff_stat' and expect to be large enough to
 * hold them.
 * - अगर buff_stats != शून्य and num_stats > 0 then copy the requested
 * perक्रमmance-statistics to buff_stats.
 */
अटल sमाप_प्रकार drc_pmem_query_stats(काष्ठा papr_scm_priv *p,
				    काष्ठा papr_scm_perf_stats *buff_stats,
				    अचिन्हित पूर्णांक num_stats)
अणु
	अचिन्हित दीर्घ ret[PLPAR_HCALL_बफ_मानE];
	माप_प्रकार size;
	s64 rc;

	/* Setup the out buffer */
	अगर (buff_stats) अणु
		स_नकल(buff_stats->eye_catcher,
		       PAPR_SCM_PERF_STATS_EYECATCHER, 8);
		buff_stats->stats_version =
			cpu_to_be32(PAPR_SCM_PERF_STATS_VERSION);
		buff_stats->num_statistics =
			cpu_to_be32(num_stats);

		/*
		 * Calculate the buffer size based on num-stats provided
		 * or use the prefetched max buffer length
		 */
		अगर (num_stats)
			/* Calculate size from the num_stats */
			size = माप(काष्ठा papr_scm_perf_stats) +
				num_stats * माप(काष्ठा papr_scm_perf_stat);
		अन्यथा
			size = p->stat_buffer_len;
	पूर्ण अन्यथा अणु
		/* In हाल of no out buffer ignore the size */
		size = 0;
	पूर्ण

	/* Do the HCALL asking PHYP क्रम info */
	rc = plpar_hcall(H_SCM_PERFORMANCE_STATS, ret, p->drc_index,
			 buff_stats ? virt_to_phys(buff_stats) : 0,
			 size);

	/* Check अगर the error was due to an unknown stat-id */
	अगर (rc == H_PARTIAL) अणु
		dev_err(&p->pdev->dev,
			"Unknown performance stats, Err:0x%016lX\n", ret[0]);
		वापस -ENOENT;
	पूर्ण अन्यथा अगर (rc != H_SUCCESS) अणु
		dev_err(&p->pdev->dev,
			"Failed to query performance stats, Err:%lld\n", rc);
		वापस -EIO;

	पूर्ण अन्यथा अगर (!size) अणु
		/* Handle हाल where stat buffer size was requested */
		dev_dbg(&p->pdev->dev,
			"Performance stats size %ld\n", ret[0]);
		वापस ret[0];
	पूर्ण

	/* Successfully fetched the requested stats from phyp */
	dev_dbg(&p->pdev->dev,
		"Performance stats returned %d stats\n",
		be32_to_cpu(buff_stats->num_statistics));
	वापस 0;
पूर्ण

/*
 * Issue hcall to retrieve dimm health info and populate papr_scm_priv with the
 * health inक्रमmation.
 */
अटल पूर्णांक __drc_pmem_query_health(काष्ठा papr_scm_priv *p)
अणु
	अचिन्हित दीर्घ ret[PLPAR_HCALL_बफ_मानE];
	दीर्घ rc;

	/* issue the hcall */
	rc = plpar_hcall(H_SCM_HEALTH, ret, p->drc_index);
	अगर (rc != H_SUCCESS) अणु
		dev_err(&p->pdev->dev,
			"Failed to query health information, Err:%ld\n", rc);
		वापस -ENXIO;
	पूर्ण

	p->lasthealth_jअगरfies = jअगरfies;
	p->health_biपंचांगap = ret[0] & ret[1];

	dev_dbg(&p->pdev->dev,
		"Queried dimm health info. Bitmap:0x%016lx Mask:0x%016lx\n",
		ret[0], ret[1]);

	वापस 0;
पूर्ण

/* Min पूर्णांकerval in seconds क्रम assuming stable dimm health */
#घोषणा MIN_HEALTH_QUERY_INTERVAL 60

/* Query cached health info and अगर needed call drc_pmem_query_health */
अटल पूर्णांक drc_pmem_query_health(काष्ठा papr_scm_priv *p)
अणु
	अचिन्हित दीर्घ cache_समयout;
	पूर्णांक rc;

	/* Protect concurrent modअगरications to papr_scm_priv */
	rc = mutex_lock_पूर्णांकerruptible(&p->health_mutex);
	अगर (rc)
		वापस rc;

	/* Jअगरfies offset क्रम which the health data is assumed to be same */
	cache_समयout = p->lasthealth_jअगरfies +
		msecs_to_jअगरfies(MIN_HEALTH_QUERY_INTERVAL * 1000);

	/* Fetch new health info is its older than MIN_HEALTH_QUERY_INTERVAL */
	अगर (समय_after(jअगरfies, cache_समयout))
		rc = __drc_pmem_query_health(p);
	अन्यथा
		/* Assume cached health data is valid */
		rc = 0;

	mutex_unlock(&p->health_mutex);
	वापस rc;
पूर्ण

अटल पूर्णांक papr_scm_meta_get(काष्ठा papr_scm_priv *p,
			     काष्ठा nd_cmd_get_config_data_hdr *hdr)
अणु
	अचिन्हित दीर्घ data[PLPAR_HCALL_बफ_मानE];
	अचिन्हित दीर्घ offset, data_offset;
	पूर्णांक len, पढ़ो;
	पूर्णांक64_t ret;

	अगर ((hdr->in_offset + hdr->in_length) > p->metadata_size)
		वापस -EINVAL;

	क्रम (len = hdr->in_length; len; len -= पढ़ो) अणु

		data_offset = hdr->in_length - len;
		offset = hdr->in_offset + data_offset;

		अगर (len >= 8)
			पढ़ो = 8;
		अन्यथा अगर (len >= 4)
			पढ़ो = 4;
		अन्यथा अगर (len >= 2)
			पढ़ो = 2;
		अन्यथा
			पढ़ो = 1;

		ret = plpar_hcall(H_SCM_READ_METADATA, data, p->drc_index,
				  offset, पढ़ो);

		अगर (ret == H_PARAMETER) /* bad DRC index */
			वापस -ENODEV;
		अगर (ret)
			वापस -EINVAL; /* other invalid parameter */

		चयन (पढ़ो) अणु
		हाल 8:
			*(uपूर्णांक64_t *)(hdr->out_buf + data_offset) = be64_to_cpu(data[0]);
			अवरोध;
		हाल 4:
			*(uपूर्णांक32_t *)(hdr->out_buf + data_offset) = be32_to_cpu(data[0] & 0xffffffff);
			अवरोध;

		हाल 2:
			*(uपूर्णांक16_t *)(hdr->out_buf + data_offset) = be16_to_cpu(data[0] & 0xffff);
			अवरोध;

		हाल 1:
			*(uपूर्णांक8_t *)(hdr->out_buf + data_offset) = (data[0] & 0xff);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक papr_scm_meta_set(काष्ठा papr_scm_priv *p,
			     काष्ठा nd_cmd_set_config_hdr *hdr)
अणु
	अचिन्हित दीर्घ offset, data_offset;
	पूर्णांक len, wrote;
	अचिन्हित दीर्घ data;
	__be64 data_be;
	पूर्णांक64_t ret;

	अगर ((hdr->in_offset + hdr->in_length) > p->metadata_size)
		वापस -EINVAL;

	क्रम (len = hdr->in_length; len; len -= wrote) अणु

		data_offset = hdr->in_length - len;
		offset = hdr->in_offset + data_offset;

		अगर (len >= 8) अणु
			data = *(uपूर्णांक64_t *)(hdr->in_buf + data_offset);
			data_be = cpu_to_be64(data);
			wrote = 8;
		पूर्ण अन्यथा अगर (len >= 4) अणु
			data = *(uपूर्णांक32_t *)(hdr->in_buf + data_offset);
			data &= 0xffffffff;
			data_be = cpu_to_be32(data);
			wrote = 4;
		पूर्ण अन्यथा अगर (len >= 2) अणु
			data = *(uपूर्णांक16_t *)(hdr->in_buf + data_offset);
			data &= 0xffff;
			data_be = cpu_to_be16(data);
			wrote = 2;
		पूर्ण अन्यथा अणु
			data_be = *(uपूर्णांक8_t *)(hdr->in_buf + data_offset);
			data_be &= 0xff;
			wrote = 1;
		पूर्ण

		ret = plpar_hcall_norets(H_SCM_WRITE_METADATA, p->drc_index,
					 offset, data_be, wrote);
		अगर (ret == H_PARAMETER) /* bad DRC index */
			वापस -ENODEV;
		अगर (ret)
			वापस -EINVAL; /* other invalid parameter */
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Do a sanity checks on the inमाला_दो args to dimm-control function and वापस
 * '0' अगर valid. Validation of PDSM payloads happens later in
 * papr_scm_service_pdsm.
 */
अटल पूर्णांक is_cmd_valid(काष्ठा nvdimm *nvdimm, अचिन्हित पूर्णांक cmd, व्योम *buf,
			अचिन्हित पूर्णांक buf_len)
अणु
	अचिन्हित दीर्घ cmd_mask = PAPR_SCM_DIMM_CMD_MASK;
	काष्ठा nd_cmd_pkg *nd_cmd;
	काष्ठा papr_scm_priv *p;
	क्रमागत papr_pdsm pdsm;

	/* Only dimm-specअगरic calls are supported aपंचांग */
	अगर (!nvdimm)
		वापस -EINVAL;

	/* get the provider data from काष्ठा nvdimm */
	p = nvdimm_provider_data(nvdimm);

	अगर (!test_bit(cmd, &cmd_mask)) अणु
		dev_dbg(&p->pdev->dev, "Unsupported cmd=%u\n", cmd);
		वापस -EINVAL;
	पूर्ण

	/* For CMD_CALL verअगरy pdsm request */
	अगर (cmd == ND_CMD_CALL) अणु
		/* Verअगरy the envelope and envelop size */
		अगर (!buf ||
		    buf_len < (माप(काष्ठा nd_cmd_pkg) + ND_PDSM_HDR_SIZE)) अणु
			dev_dbg(&p->pdev->dev, "Invalid pkg size=%u\n",
				buf_len);
			वापस -EINVAL;
		पूर्ण

		/* Verअगरy that the nd_cmd_pkg.nd_family is correct */
		nd_cmd = (काष्ठा nd_cmd_pkg *)buf;

		अगर (nd_cmd->nd_family != NVDIMM_FAMILY_PAPR) अणु
			dev_dbg(&p->pdev->dev, "Invalid pkg family=0x%llx\n",
				nd_cmd->nd_family);
			वापस -EINVAL;
		पूर्ण

		pdsm = (क्रमागत papr_pdsm)nd_cmd->nd_command;

		/* Verअगरy अगर the pdsm command is valid */
		अगर (pdsm <= PAPR_PDSM_MIN || pdsm >= PAPR_PDSM_MAX) अणु
			dev_dbg(&p->pdev->dev, "PDSM[0x%x]: Invalid PDSM\n",
				pdsm);
			वापस -EINVAL;
		पूर्ण

		/* Have enough space to hold वापसed 'nd_pkg_pdsm' header */
		अगर (nd_cmd->nd_size_out < ND_PDSM_HDR_SIZE) अणु
			dev_dbg(&p->pdev->dev, "PDSM[0x%x]: Invalid payload\n",
				pdsm);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Let the command be further processed */
	वापस 0;
पूर्ण

अटल पूर्णांक papr_pdsm_fuel_gauge(काष्ठा papr_scm_priv *p,
				जोड़ nd_pdsm_payload *payload)
अणु
	पूर्णांक rc, size;
	u64 statval;
	काष्ठा papr_scm_perf_stat *stat;
	काष्ठा papr_scm_perf_stats *stats;

	/* Silently fail अगर fetching perक्रमmance metrics isn't  supported */
	अगर (!p->stat_buffer_len)
		वापस 0;

	/* Allocate request buffer enough to hold single perक्रमmance stat */
	size = माप(काष्ठा papr_scm_perf_stats) +
		माप(काष्ठा papr_scm_perf_stat);

	stats = kzalloc(size, GFP_KERNEL);
	अगर (!stats)
		वापस -ENOMEM;

	stat = &stats->scm_statistic[0];
	स_नकल(&stat->stat_id, "MemLife ", माप(stat->stat_id));
	stat->stat_val = 0;

	/* Fetch the fuel gauge and populate it in payload */
	rc = drc_pmem_query_stats(p, stats, 1);
	अगर (rc < 0) अणु
		dev_dbg(&p->pdev->dev, "Err(%d) fetching fuel gauge\n", rc);
		जाओ मुक्त_stats;
	पूर्ण

	statval = be64_to_cpu(stat->stat_val);
	dev_dbg(&p->pdev->dev,
		"Fetched fuel-gauge %llu", statval);
	payload->health.extension_flags |=
		PDSM_DIMM_HEALTH_RUN_GAUGE_VALID;
	payload->health.dimm_fuel_gauge = statval;

	rc = माप(काष्ठा nd_papr_pdsm_health);

मुक्त_stats:
	kमुक्त(stats);
	वापस rc;
पूर्ण

/* Fetch the DIMM health info and populate it in provided package. */
अटल पूर्णांक papr_pdsm_health(काष्ठा papr_scm_priv *p,
			    जोड़ nd_pdsm_payload *payload)
अणु
	पूर्णांक rc;

	/* Ensure dimm health mutex is taken preventing concurrent access */
	rc = mutex_lock_पूर्णांकerruptible(&p->health_mutex);
	अगर (rc)
		जाओ out;

	/* Always fetch upto date dimm health data ignoring cached values */
	rc = __drc_pmem_query_health(p);
	अगर (rc) अणु
		mutex_unlock(&p->health_mutex);
		जाओ out;
	पूर्ण

	/* update health काष्ठा with various flags derived from health biपंचांगap */
	payload->health = (काष्ठा nd_papr_pdsm_health) अणु
		.extension_flags = 0,
		.dimm_unarmed = !!(p->health_biपंचांगap & PAPR_PMEM_UNARMED_MASK),
		.dimm_bad_shutकरोwn = !!(p->health_biपंचांगap & PAPR_PMEM_BAD_SHUTDOWN_MASK),
		.dimm_bad_restore = !!(p->health_biपंचांगap & PAPR_PMEM_BAD_RESTORE_MASK),
		.dimm_scrubbed = !!(p->health_biपंचांगap & PAPR_PMEM_SCRUBBED_AND_LOCKED),
		.dimm_locked = !!(p->health_biपंचांगap & PAPR_PMEM_SCRUBBED_AND_LOCKED),
		.dimm_encrypted = !!(p->health_biपंचांगap & PAPR_PMEM_ENCRYPTED),
		.dimm_health = PAPR_PDSM_DIMM_HEALTHY,
	पूर्ण;

	/* Update field dimm_health based on health_biपंचांगap flags */
	अगर (p->health_biपंचांगap & PAPR_PMEM_HEALTH_FATAL)
		payload->health.dimm_health = PAPR_PDSM_DIMM_FATAL;
	अन्यथा अगर (p->health_biपंचांगap & PAPR_PMEM_HEALTH_CRITICAL)
		payload->health.dimm_health = PAPR_PDSM_DIMM_CRITICAL;
	अन्यथा अगर (p->health_biपंचांगap & PAPR_PMEM_HEALTH_UNHEALTHY)
		payload->health.dimm_health = PAPR_PDSM_DIMM_UNHEALTHY;

	/* काष्ठा populated hence can release the mutex now */
	mutex_unlock(&p->health_mutex);

	/* Populate the fuel gauge meter in the payload */
	papr_pdsm_fuel_gauge(p, payload);

	rc = माप(काष्ठा nd_papr_pdsm_health);

out:
	वापस rc;
पूर्ण

/*
 * 'struct pdsm_cmd_desc'
 * Identअगरies supported PDSMs' expected length of in/out payloads
 * and pdsm service function.
 *
 * size_in	: Size of input payload अगर any in the PDSM request.
 * size_out	: Size of output payload अगर any in the PDSM request.
 * service	: Service function क्रम the PDSM request. Return semantics:
 *		  rc < 0 : Error servicing PDSM and rc indicates the error.
 *		  rc >=0 : Serviced successfully and 'rc' indicate number of
 *			bytes written to payload.
 */
काष्ठा pdsm_cmd_desc अणु
	u32 size_in;
	u32 size_out;
	पूर्णांक (*service)(काष्ठा papr_scm_priv *dimm,
		       जोड़ nd_pdsm_payload *payload);
पूर्ण;

/* Holds all supported PDSMs' command descriptors */
अटल स्थिर काष्ठा pdsm_cmd_desc __pdsm_cmd_descriptors[] = अणु
	[PAPR_PDSM_MIN] = अणु
		.size_in = 0,
		.size_out = 0,
		.service = शून्य,
	पूर्ण,
	/* New PDSM command descriptors to be added below */

	[PAPR_PDSM_HEALTH] = अणु
		.size_in = 0,
		.size_out = माप(काष्ठा nd_papr_pdsm_health),
		.service = papr_pdsm_health,
	पूर्ण,
	/* Empty */
	[PAPR_PDSM_MAX] = अणु
		.size_in = 0,
		.size_out = 0,
		.service = शून्य,
	पूर्ण,
पूर्ण;

/* Given a valid pdsm cmd वापस its command descriptor अन्यथा वापस शून्य */
अटल अंतरभूत स्थिर काष्ठा pdsm_cmd_desc *pdsm_cmd_desc(क्रमागत papr_pdsm cmd)
अणु
	अगर (cmd >= 0 || cmd < ARRAY_SIZE(__pdsm_cmd_descriptors))
		वापस &__pdsm_cmd_descriptors[cmd];

	वापस शून्य;
पूर्ण

/*
 * For a given pdsm request call an appropriate service function.
 * Returns errors अगर any जबतक handling the pdsm command package.
 */
अटल पूर्णांक papr_scm_service_pdsm(काष्ठा papr_scm_priv *p,
				 काष्ठा nd_cmd_pkg *pkg)
अणु
	/* Get the PDSM header and PDSM command */
	काष्ठा nd_pkg_pdsm *pdsm_pkg = (काष्ठा nd_pkg_pdsm *)pkg->nd_payload;
	क्रमागत papr_pdsm pdsm = (क्रमागत papr_pdsm)pkg->nd_command;
	स्थिर काष्ठा pdsm_cmd_desc *pdsc;
	पूर्णांक rc;

	/* Fetch corresponding pdsm descriptor क्रम validation and servicing */
	pdsc = pdsm_cmd_desc(pdsm);

	/* Validate pdsm descriptor */
	/* Ensure that reserved fields are 0 */
	अगर (pdsm_pkg->reserved[0] || pdsm_pkg->reserved[1]) अणु
		dev_dbg(&p->pdev->dev, "PDSM[0x%x]: Invalid reserved field\n",
			pdsm);
		वापस -EINVAL;
	पूर्ण

	/* If pdsm expects some input, then ensure that the size_in matches */
	अगर (pdsc->size_in &&
	    pkg->nd_size_in != (pdsc->size_in + ND_PDSM_HDR_SIZE)) अणु
		dev_dbg(&p->pdev->dev, "PDSM[0x%x]: Mismatched size_in=%d\n",
			pdsm, pkg->nd_size_in);
		वापस -EINVAL;
	पूर्ण

	/* If pdsm wants to वापस data, then ensure that  size_out matches */
	अगर (pdsc->size_out &&
	    pkg->nd_size_out != (pdsc->size_out + ND_PDSM_HDR_SIZE)) अणु
		dev_dbg(&p->pdev->dev, "PDSM[0x%x]: Mismatched size_out=%d\n",
			pdsm, pkg->nd_size_out);
		वापस -EINVAL;
	पूर्ण

	/* Service the pdsm */
	अगर (pdsc->service) अणु
		dev_dbg(&p->pdev->dev, "PDSM[0x%x]: Servicing..\n", pdsm);

		rc = pdsc->service(p, &pdsm_pkg->payload);

		अगर (rc < 0) अणु
			/* error encountered जबतक servicing pdsm */
			pdsm_pkg->cmd_status = rc;
			pkg->nd_fw_size = ND_PDSM_HDR_SIZE;
		पूर्ण अन्यथा अणु
			/* pdsm serviced and 'rc' bytes written to payload */
			pdsm_pkg->cmd_status = 0;
			pkg->nd_fw_size = ND_PDSM_HDR_SIZE + rc;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_dbg(&p->pdev->dev, "PDSM[0x%x]: Unsupported PDSM request\n",
			pdsm);
		pdsm_pkg->cmd_status = -ENOENT;
		pkg->nd_fw_size = ND_PDSM_HDR_SIZE;
	पूर्ण

	वापस pdsm_pkg->cmd_status;
पूर्ण

अटल पूर्णांक papr_scm_ndctl(काष्ठा nvdimm_bus_descriptor *nd_desc,
			  काष्ठा nvdimm *nvdimm, अचिन्हित पूर्णांक cmd, व्योम *buf,
			  अचिन्हित पूर्णांक buf_len, पूर्णांक *cmd_rc)
अणु
	काष्ठा nd_cmd_get_config_size *get_size_hdr;
	काष्ठा nd_cmd_pkg *call_pkg = शून्य;
	काष्ठा papr_scm_priv *p;
	पूर्णांक rc;

	rc = is_cmd_valid(nvdimm, cmd, buf, buf_len);
	अगर (rc) अणु
		pr_debug("Invalid cmd=0x%x. Err=%d\n", cmd, rc);
		वापस rc;
	पूर्ण

	/* Use a local variable in हाल cmd_rc poपूर्णांकer is शून्य */
	अगर (!cmd_rc)
		cmd_rc = &rc;

	p = nvdimm_provider_data(nvdimm);

	चयन (cmd) अणु
	हाल ND_CMD_GET_CONFIG_SIZE:
		get_size_hdr = buf;

		get_size_hdr->status = 0;
		get_size_hdr->max_xfer = 8;
		get_size_hdr->config_size = p->metadata_size;
		*cmd_rc = 0;
		अवरोध;

	हाल ND_CMD_GET_CONFIG_DATA:
		*cmd_rc = papr_scm_meta_get(p, buf);
		अवरोध;

	हाल ND_CMD_SET_CONFIG_DATA:
		*cmd_rc = papr_scm_meta_set(p, buf);
		अवरोध;

	हाल ND_CMD_CALL:
		call_pkg = (काष्ठा nd_cmd_pkg *)buf;
		*cmd_rc = papr_scm_service_pdsm(p, call_pkg);
		अवरोध;

	शेष:
		dev_dbg(&p->pdev->dev, "Unknown command = %d\n", cmd);
		वापस -EINVAL;
	पूर्ण

	dev_dbg(&p->pdev->dev, "returned with cmd_rc = %d\n", *cmd_rc);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार perf_stats_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक index;
	sमाप_प्रकार rc;
	काष्ठा seq_buf s;
	काष्ठा papr_scm_perf_stat *stat;
	काष्ठा papr_scm_perf_stats *stats;
	काष्ठा nvdimm *dimm = to_nvdimm(dev);
	काष्ठा papr_scm_priv *p = nvdimm_provider_data(dimm);

	अगर (!p->stat_buffer_len)
		वापस -ENOENT;

	/* Allocate the buffer क्रम phyp where stats are written */
	stats = kzalloc(p->stat_buffer_len, GFP_KERNEL);
	अगर (!stats)
		वापस -ENOMEM;

	/* Ask phyp to वापस all dimm perf stats */
	rc = drc_pmem_query_stats(p, stats, 0);
	अगर (rc)
		जाओ मुक्त_stats;
	/*
	 * Go through the वापसed output buffer and prपूर्णांक stats and
	 * values. Since stat_id is essentially a अक्षर string of
	 * 8 bytes, simply use the string क्रमmat specअगरier to prपूर्णांक it.
	 */
	seq_buf_init(&s, buf, PAGE_SIZE);
	क्रम (index = 0, stat = stats->scm_statistic;
	     index < be32_to_cpu(stats->num_statistics);
	     ++index, ++stat) अणु
		seq_buf_म_लिखो(&s, "%.8s = 0x%016llX\n",
			       stat->stat_id,
			       be64_to_cpu(stat->stat_val));
	पूर्ण

मुक्त_stats:
	kमुक्त(stats);
	वापस rc ? rc : (sमाप_प्रकार)seq_buf_used(&s);
पूर्ण
अटल DEVICE_ATTR_ADMIN_RO(perf_stats);

अटल sमाप_प्रकार flags_show(काष्ठा device *dev,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nvdimm *dimm = to_nvdimm(dev);
	काष्ठा papr_scm_priv *p = nvdimm_provider_data(dimm);
	काष्ठा seq_buf s;
	u64 health;
	पूर्णांक rc;

	rc = drc_pmem_query_health(p);
	अगर (rc)
		वापस rc;

	/* Copy health_biपंचांगap locally, check masks & update out buffer */
	health = READ_ONCE(p->health_biपंचांगap);

	seq_buf_init(&s, buf, PAGE_SIZE);
	अगर (health & PAPR_PMEM_UNARMED_MASK)
		seq_buf_म_लिखो(&s, "not_armed ");

	अगर (health & PAPR_PMEM_BAD_SHUTDOWN_MASK)
		seq_buf_म_लिखो(&s, "flush_fail ");

	अगर (health & PAPR_PMEM_BAD_RESTORE_MASK)
		seq_buf_म_लिखो(&s, "restore_fail ");

	अगर (health & PAPR_PMEM_ENCRYPTED)
		seq_buf_म_लिखो(&s, "encrypted ");

	अगर (health & PAPR_PMEM_SMART_EVENT_MASK)
		seq_buf_म_लिखो(&s, "smart_notify ");

	अगर (health & PAPR_PMEM_SCRUBBED_AND_LOCKED)
		seq_buf_म_लिखो(&s, "scrubbed locked ");

	अगर (seq_buf_used(&s))
		seq_buf_म_लिखो(&s, "\n");

	वापस seq_buf_used(&s);
पूर्ण
DEVICE_ATTR_RO(flags);

/* papr_scm specअगरic dimm attributes */
अटल काष्ठा attribute *papr_nd_attributes[] = अणु
	&dev_attr_flags.attr,
	&dev_attr_perf_stats.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group papr_nd_attribute_group = अणु
	.name = "papr",
	.attrs = papr_nd_attributes,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *papr_nd_attr_groups[] = अणु
	&papr_nd_attribute_group,
	शून्य,
पूर्ण;

अटल पूर्णांक papr_scm_nvdimm_init(काष्ठा papr_scm_priv *p)
अणु
	काष्ठा device *dev = &p->pdev->dev;
	काष्ठा nd_mapping_desc mapping;
	काष्ठा nd_region_desc ndr_desc;
	अचिन्हित दीर्घ dimm_flags;
	पूर्णांक target_nid, online_nid;
	sमाप_प्रकार stat_size;

	p->bus_desc.ndctl = papr_scm_ndctl;
	p->bus_desc.module = THIS_MODULE;
	p->bus_desc.of_node = p->pdev->dev.of_node;
	p->bus_desc.provider_name = kstrdup(p->pdev->name, GFP_KERNEL);

	/* Set the dimm command family mask to accept PDSMs */
	set_bit(NVDIMM_FAMILY_PAPR, &p->bus_desc.dimm_family_mask);

	अगर (!p->bus_desc.provider_name)
		वापस -ENOMEM;

	p->bus = nvdimm_bus_रेजिस्टर(शून्य, &p->bus_desc);
	अगर (!p->bus) अणु
		dev_err(dev, "Error creating nvdimm bus %pOF\n", p->dn);
		kमुक्त(p->bus_desc.provider_name);
		वापस -ENXIO;
	पूर्ण

	dimm_flags = 0;
	set_bit(NDD_LABELING, &dimm_flags);

	/*
	 * Check अगर the nvdimm is unarmed. No locking needed as we are still
	 * initializing. Ignore error encountered अगर any.
	 */
	__drc_pmem_query_health(p);

	अगर (p->health_biपंचांगap & PAPR_PMEM_UNARMED_MASK)
		set_bit(NDD_UNARMED, &dimm_flags);

	p->nvdimm = nvdimm_create(p->bus, p, papr_nd_attr_groups,
				  dimm_flags, PAPR_SCM_DIMM_CMD_MASK, 0, शून्य);
	अगर (!p->nvdimm) अणु
		dev_err(dev, "Error creating DIMM object for %pOF\n", p->dn);
		जाओ err;
	पूर्ण

	अगर (nvdimm_bus_check_dimm_count(p->bus, 1))
		जाओ err;

	/* now add the region */

	स_रखो(&mapping, 0, माप(mapping));
	mapping.nvdimm = p->nvdimm;
	mapping.start = 0;
	mapping.size = p->blocks * p->block_size; // XXX: potential overflow?

	स_रखो(&ndr_desc, 0, माप(ndr_desc));
	target_nid = dev_to_node(&p->pdev->dev);
	online_nid = numa_map_to_online_node(target_nid);
	ndr_desc.numa_node = online_nid;
	ndr_desc.target_node = target_nid;
	ndr_desc.res = &p->res;
	ndr_desc.of_node = p->dn;
	ndr_desc.provider_data = p;
	ndr_desc.mapping = &mapping;
	ndr_desc.num_mappings = 1;
	ndr_desc.nd_set = &p->nd_set;

	अगर (p->hcall_flush_required) अणु
		set_bit(ND_REGION_ASYNC, &ndr_desc.flags);
		ndr_desc.flush = papr_scm_pmem_flush;
	पूर्ण

	अगर (p->is_अस्थिर)
		p->region = nvdimm_अस्थिर_region_create(p->bus, &ndr_desc);
	अन्यथा अणु
		set_bit(ND_REGION_PERSIST_MEMCTRL, &ndr_desc.flags);
		p->region = nvdimm_pmem_region_create(p->bus, &ndr_desc);
	पूर्ण
	अगर (!p->region) अणु
		dev_err(dev, "Error registering region %pR from %pOF\n",
				ndr_desc.res, p->dn);
		जाओ err;
	पूर्ण
	अगर (target_nid != online_nid)
		dev_info(dev, "Region registered with target node %d and online node %d",
			 target_nid, online_nid);

	mutex_lock(&papr_ndr_lock);
	list_add_tail(&p->region_list, &papr_nd_regions);
	mutex_unlock(&papr_ndr_lock);

	/* Try retriving the stat buffer and see अगर its supported */
	stat_size = drc_pmem_query_stats(p, शून्य, 0);
	अगर (stat_size > 0) अणु
		p->stat_buffer_len = stat_size;
		dev_dbg(&p->pdev->dev, "Max perf-stat size %lu-bytes\n",
			p->stat_buffer_len);
	पूर्ण अन्यथा अणु
		dev_info(&p->pdev->dev, "Dimm performance stats unavailable\n");
	पूर्ण

	वापस 0;

err:	nvdimm_bus_unरेजिस्टर(p->bus);
	kमुक्त(p->bus_desc.provider_name);
	वापस -ENXIO;
पूर्ण

अटल व्योम papr_scm_add_badblock(काष्ठा nd_region *region,
				  काष्ठा nvdimm_bus *bus, u64 phys_addr)
अणु
	u64 aligned_addr = ALIGN_DOWN(phys_addr, L1_CACHE_BYTES);

	अगर (nvdimm_bus_add_badrange(bus, aligned_addr, L1_CACHE_BYTES)) अणु
		pr_err("Bad block registration for 0x%llx failed\n", phys_addr);
		वापस;
	पूर्ण

	pr_debug("Add memory range (0x%llx - 0x%llx) as bad range\n",
		 aligned_addr, aligned_addr + L1_CACHE_BYTES);

	nvdimm_region_notअगरy(region, NVDIMM_REVALIDATE_POISON);
पूर्ण

अटल पूर्णांक handle_mce_ue(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ val,
			 व्योम *data)
अणु
	काष्ठा machine_check_event *evt = data;
	काष्ठा papr_scm_priv *p;
	u64 phys_addr;
	bool found = false;

	अगर (evt->error_type != MCE_ERROR_TYPE_UE)
		वापस NOTIFY_DONE;

	अगर (list_empty(&papr_nd_regions))
		वापस NOTIFY_DONE;

	/*
	 * The physical address obtained here is PAGE_SIZE aligned, so get the
	 * exact address from the effective address
	 */
	phys_addr = evt->u.ue_error.physical_address +
			(evt->u.ue_error.effective_address & ~PAGE_MASK);

	अगर (!evt->u.ue_error.physical_address_provided ||
	    !is_zone_device_page(pfn_to_page(phys_addr >> PAGE_SHIFT)))
		वापस NOTIFY_DONE;

	/* mce notअगरier is called from a process context, so mutex is safe */
	mutex_lock(&papr_ndr_lock);
	list_क्रम_each_entry(p, &papr_nd_regions, region_list) अणु
		अगर (phys_addr >= p->res.start && phys_addr <= p->res.end) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (found)
		papr_scm_add_badblock(p->region, p->bus, phys_addr);

	mutex_unlock(&papr_ndr_lock);

	वापस found ? NOTIFY_OK : NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block mce_ue_nb = अणु
	.notअगरier_call = handle_mce_ue
पूर्ण;

अटल पूर्णांक papr_scm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *dn = pdev->dev.of_node;
	u32 drc_index, metadata_size;
	u64 blocks, block_size;
	काष्ठा papr_scm_priv *p;
	स्थिर अक्षर *uuid_str;
	u64 uuid[2];
	पूर्णांक rc;

	/* check we have all the required DT properties */
	अगर (of_property_पढ़ो_u32(dn, "ibm,my-drc-index", &drc_index)) अणु
		dev_err(&pdev->dev, "%pOF: missing drc-index!\n", dn);
		वापस -ENODEV;
	पूर्ण

	अगर (of_property_पढ़ो_u64(dn, "ibm,block-size", &block_size)) अणु
		dev_err(&pdev->dev, "%pOF: missing block-size!\n", dn);
		वापस -ENODEV;
	पूर्ण

	अगर (of_property_पढ़ो_u64(dn, "ibm,number-of-blocks", &blocks)) अणु
		dev_err(&pdev->dev, "%pOF: missing number-of-blocks!\n", dn);
		वापस -ENODEV;
	पूर्ण

	अगर (of_property_पढ़ो_string(dn, "ibm,unit-guid", &uuid_str)) अणु
		dev_err(&pdev->dev, "%pOF: missing unit-guid!\n", dn);
		वापस -ENODEV;
	पूर्ण


	p = kzalloc(माप(*p), GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	/* Initialize the dimm mutex */
	mutex_init(&p->health_mutex);

	/* optional DT properties */
	of_property_पढ़ो_u32(dn, "ibm,metadata-size", &metadata_size);

	p->dn = dn;
	p->drc_index = drc_index;
	p->block_size = block_size;
	p->blocks = blocks;
	p->is_अस्थिर = !of_property_पढ़ो_bool(dn, "ibm,cache-flush-required");
	p->hcall_flush_required = of_property_पढ़ो_bool(dn, "ibm,hcall-flush-required");

	/* We just need to ensure that set cookies are unique across */
	uuid_parse(uuid_str, (uuid_t *) uuid);
	/*
	 * cookie1 and cookie2 are not really little endian
	 * we store a little endian representation of the
	 * uuid str so that we can compare this with the label
	 * area cookie irrespective of the endian config with which
	 * the kernel is built.
	 */
	p->nd_set.cookie1 = cpu_to_le64(uuid[0]);
	p->nd_set.cookie2 = cpu_to_le64(uuid[1]);

	/* might be zero */
	p->metadata_size = metadata_size;
	p->pdev = pdev;

	/* request the hypervisor to bind this region to somewhere in memory */
	rc = drc_pmem_bind(p);

	/* If phyp says drc memory still bound then क्रमce unbound and retry */
	अगर (rc == H_OVERLAP)
		rc = drc_pmem_query_n_bind(p);

	अगर (rc != H_SUCCESS) अणु
		dev_err(&p->pdev->dev, "bind err: %d\n", rc);
		rc = -ENXIO;
		जाओ err;
	पूर्ण

	/* setup the resource क्रम the newly bound range */
	p->res.start = p->bound_addr;
	p->res.end   = p->bound_addr + p->blocks * p->block_size - 1;
	p->res.name  = pdev->name;
	p->res.flags = IORESOURCE_MEM;

	rc = papr_scm_nvdimm_init(p);
	अगर (rc)
		जाओ err2;

	platक्रमm_set_drvdata(pdev, p);

	वापस 0;

err2:	drc_pmem_unbind(p);
err:	kमुक्त(p);
	वापस rc;
पूर्ण

अटल पूर्णांक papr_scm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा papr_scm_priv *p = platक्रमm_get_drvdata(pdev);

	mutex_lock(&papr_ndr_lock);
	list_del(&p->region_list);
	mutex_unlock(&papr_ndr_lock);

	nvdimm_bus_unरेजिस्टर(p->bus);
	drc_pmem_unbind(p);
	kमुक्त(p->bus_desc.provider_name);
	kमुक्त(p);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id papr_scm_match[] = अणु
	अणु .compatible = "ibm,pmemory" पूर्ण,
	अणु .compatible = "ibm,pmemory-v2" पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver papr_scm_driver = अणु
	.probe = papr_scm_probe,
	.हटाओ = papr_scm_हटाओ,
	.driver = अणु
		.name = "papr_scm",
		.of_match_table = papr_scm_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init papr_scm_init(व्योम)
अणु
	पूर्णांक ret;

	ret = platक्रमm_driver_रेजिस्टर(&papr_scm_driver);
	अगर (!ret)
		mce_रेजिस्टर_notअगरier(&mce_ue_nb);

	वापस ret;
पूर्ण
module_init(papr_scm_init);

अटल व्योम __निकास papr_scm_निकास(व्योम)
अणु
	mce_unरेजिस्टर_notअगरier(&mce_ue_nb);
	platक्रमm_driver_unरेजिस्टर(&papr_scm_driver);
पूर्ण
module_निकास(papr_scm_निकास);

MODULE_DEVICE_TABLE(of, papr_scm_match);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("IBM Corporation");
