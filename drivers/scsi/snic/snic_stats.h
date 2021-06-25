<शैली गुरु>
/*
 * Copyright 2014 Cisco Systems, Inc.  All rights reserved.
 *
 * This program is मुक्त software; you may redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#अगर_अघोषित __SNIC_STATS_H
#घोषणा __SNIC_STATS_H

काष्ठा snic_io_stats अणु
	atomic64_t active;		/* Active IOs */
	atomic64_t max_active;		/* Max # active IOs */
	atomic64_t max_sgl;		/* Max # SGLs क्रम any IO */
	atomic64_t max_समय;		/* Max समय to process IO */
	atomic64_t max_qसमय;		/* Max समय to Queue the IO */
	atomic64_t max_cmpl_समय;	/* Max समय to complete the IO */
	atomic64_t sgl_cnt[SNIC_MAX_SG_DESC_CNT]; /* SGL Counters */
	atomic64_t max_io_sz;		/* Max IO Size */
	atomic64_t compl;		/* IO Completions */
	atomic64_t fail;		/* IO Failures */
	atomic64_t req_null;		/* req or req info is शून्य */
	atomic64_t alloc_fail;		/* Alloc Failures */
	atomic64_t sc_null;
	atomic64_t io_not_found;	/* IO Not Found */
	atomic64_t num_ios;		/* Number of IOs */
पूर्ण;

काष्ठा snic_पात_stats अणु
	atomic64_t num;		/* Abort counter */
	atomic64_t fail;	/* Abort Failure Counter */
	atomic64_t drv_पंचांगo;	/* Abort Driver Timeouts */
	atomic64_t fw_पंचांगo;	/* Abort Firmware Timeouts */
	atomic64_t io_not_found;/* Abort IO Not Found */
	atomic64_t q_fail;	/* Abort Queuing Failed */
पूर्ण;

काष्ठा snic_reset_stats अणु
	atomic64_t dev_resets;		/* Device Reset Counter */
	atomic64_t dev_reset_fail;	/* Device Reset Failures */
	atomic64_t dev_reset_पातs;	/* Device Reset Aborts */
	atomic64_t dev_reset_पंचांगo;	/* Device Reset Timeout */
	atomic64_t dev_reset_terms;	/* Device Reset terminate */
	atomic64_t hba_resets;		/* hba/firmware resets */
	atomic64_t hba_reset_cmpl;	/* hba/firmware reset completions */
	atomic64_t hba_reset_fail;	/* hba/firmware failures */
	atomic64_t snic_resets;		/* snic resets */
	atomic64_t snic_reset_compl;	/* snic reset completions */
	atomic64_t snic_reset_fail;	/* snic reset failures */
पूर्ण;

काष्ठा snic_fw_stats अणु
	atomic64_t actv_reqs;		/* Active Requests */
	atomic64_t max_actv_reqs;	/* Max Active Requests */
	atomic64_t out_of_res;		/* Firmware Out Of Resources */
	atomic64_t io_errs;		/* Firmware IO Firmware Errors */
	atomic64_t scsi_errs;		/* Target hits check condition */
पूर्ण;

काष्ठा snic_misc_stats अणु
	u64	last_isr_समय;
	u64	last_ack_समय;
	atomic64_t ack_isr_cnt;
	atomic64_t cmpl_isr_cnt;
	atomic64_t त्रुटि_संtअगरy_isr_cnt;
	atomic64_t max_cq_ents;		/* Max CQ Entries */
	atomic64_t data_cnt_mismat;	/* Data Count Mismatch */
	atomic64_t io_पंचांगo;
	atomic64_t io_पातed;
	atomic64_t sgl_inval;		/* SGL Invalid */
	atomic64_t abts_wq_alloc_fail;	/* Abort Path WQ desc alloc failure */
	atomic64_t devrst_wq_alloc_fail;/* Device Reset - WQ desc alloc fail */
	atomic64_t wq_alloc_fail;	/* IO WQ desc alloc failure */
	atomic64_t no_icmnd_iपंचांगf_cmpls;
	atomic64_t io_under_run;
	atomic64_t qfull;
	atomic64_t qsz_rampup;
	atomic64_t qsz_rampकरोwn;
	atomic64_t last_qsz;
	atomic64_t tgt_not_rdy;
पूर्ण;

काष्ठा snic_stats अणु
	काष्ठा snic_io_stats io;
	काष्ठा snic_पात_stats abts;
	काष्ठा snic_reset_stats reset;
	काष्ठा snic_fw_stats fw;
	काष्ठा snic_misc_stats misc;
	atomic64_t io_cmpl_skip;
पूर्ण;

व्योम snic_stats_debugfs_init(काष्ठा snic *);
व्योम snic_stats_debugfs_हटाओ(काष्ठा snic *);

/* Auxillary function to update active IO counter */
अटल अंतरभूत व्योम
snic_stats_update_active_ios(काष्ठा snic_stats *s_stats)
अणु
	काष्ठा snic_io_stats *io = &s_stats->io;
	पूर्णांक nr_active_ios;

	nr_active_ios = atomic64_पढ़ो(&io->active);
	अगर (atomic64_पढ़ो(&io->max_active) < nr_active_ios)
		atomic64_set(&io->max_active, nr_active_ios);

	atomic64_inc(&io->num_ios);
पूर्ण

/* Auxillary function to update IO completion counter */
अटल अंतरभूत व्योम
snic_stats_update_io_cmpl(काष्ठा snic_stats *s_stats)
अणु
	atomic64_dec(&s_stats->io.active);
	अगर (unlikely(atomic64_पढ़ो(&s_stats->io_cmpl_skip)))
		atomic64_dec(&s_stats->io_cmpl_skip);
	अन्यथा
		atomic64_inc(&s_stats->io.compl);
पूर्ण
#पूर्ण_अगर /* __SNIC_STATS_H */
