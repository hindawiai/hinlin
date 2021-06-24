<शैली गुरु>
/*
 * Copyright 2013 Cisco Systems, Inc.  All rights reserved.
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
#अगर_अघोषित _FNIC_STATS_H_
#घोषणा _FNIC_STATS_H_

काष्ठा stats_बारtamps अणु
	काष्ठा बारpec64 last_reset_समय;
	काष्ठा बारpec64 last_पढ़ो_समय;
पूर्ण;

काष्ठा io_path_stats अणु
	atomic64_t active_ios;
	atomic64_t max_active_ios;
	atomic64_t io_completions;
	atomic64_t io_failures;
	atomic64_t ioreq_null;
	atomic64_t alloc_failures;
	atomic64_t sc_null;
	atomic64_t io_not_found;
	atomic64_t num_ios;
	atomic64_t io_btw_0_to_10_msec;
	atomic64_t io_btw_10_to_100_msec;
	atomic64_t io_btw_100_to_500_msec;
	atomic64_t io_btw_500_to_5000_msec;
	atomic64_t io_btw_5000_to_10000_msec;
	atomic64_t io_btw_10000_to_30000_msec;
	atomic64_t io_greater_than_30000_msec;
	atomic64_t current_max_io_समय;
पूर्ण;

काष्ठा पात_stats अणु
	atomic64_t पातs;
	atomic64_t पात_failures;
	atomic64_t पात_drv_समयouts;
	atomic64_t पात_fw_समयouts;
	atomic64_t पात_io_not_found;
	atomic64_t पात_issued_btw_0_to_6_sec;
	atomic64_t पात_issued_btw_6_to_20_sec;
	atomic64_t पात_issued_btw_20_to_30_sec;
	atomic64_t पात_issued_btw_30_to_40_sec;
	atomic64_t पात_issued_btw_40_to_50_sec;
	atomic64_t पात_issued_btw_50_to_60_sec;
	atomic64_t पात_issued_greater_than_60_sec;
पूर्ण;

काष्ठा terminate_stats अणु
	atomic64_t terminates;
	atomic64_t max_terminates;
	atomic64_t terminate_drv_समयouts;
	atomic64_t terminate_fw_समयouts;
	atomic64_t terminate_io_not_found;
	atomic64_t terminate_failures;
पूर्ण;

काष्ठा reset_stats अणु
	atomic64_t device_resets;
	atomic64_t device_reset_failures;
	atomic64_t device_reset_पातs;
	atomic64_t device_reset_समयouts;
	atomic64_t device_reset_terminates;
	atomic64_t fw_resets;
	atomic64_t fw_reset_completions;
	atomic64_t fw_reset_failures;
	atomic64_t fnic_resets;
	atomic64_t fnic_reset_completions;
	atomic64_t fnic_reset_failures;
पूर्ण;

काष्ठा fw_stats अणु
	atomic64_t active_fw_reqs;
	atomic64_t max_fw_reqs;
	atomic64_t fw_out_of_resources;
	atomic64_t io_fw_errs;
पूर्ण;

काष्ठा vlan_stats अणु
	atomic64_t vlan_disc_reqs;
	atomic64_t resp_withno_vlanID;
	atomic64_t sol_expiry_count;
	atomic64_t flogi_rejects;
पूर्ण;

काष्ठा misc_stats अणु
	u64 last_isr_समय;
	u64 last_ack_समय;
	atomic64_t max_isr_jअगरfies;
	atomic64_t max_isr_समय_ms;
	atomic64_t corr_work_करोne;
	atomic64_t isr_count;
	atomic64_t max_cq_entries;
	atomic64_t ack_index_out_of_range;
	atomic64_t data_count_mismatch;
	atomic64_t fcpio_समयout;
	atomic64_t fcpio_पातed;
	atomic64_t sgl_invalid;
	atomic64_t mss_invalid;
	atomic64_t abts_cpwq_alloc_failures;
	atomic64_t devrst_cpwq_alloc_failures;
	atomic64_t io_cpwq_alloc_failures;
	atomic64_t no_icmnd_iपंचांगf_cmpls;
	atomic64_t check_condition;
	atomic64_t queue_fulls;
	atomic64_t rport_not_पढ़ोy;
	atomic64_t frame_errors;
	atomic64_t current_port_speed;
पूर्ण;

काष्ठा fnic_stats अणु
	काष्ठा stats_बारtamps stats_बारtamps;
	काष्ठा io_path_stats io_stats;
	काष्ठा पात_stats abts_stats;
	काष्ठा terminate_stats term_stats;
	काष्ठा reset_stats reset_stats;
	काष्ठा fw_stats fw_stats;
	काष्ठा vlan_stats vlan_stats;
	काष्ठा misc_stats misc_stats;
पूर्ण;

काष्ठा stats_debug_info अणु
	अक्षर *debug_buffer;
	व्योम *i_निजी;
	पूर्णांक buf_size;
	पूर्णांक buffer_len;
पूर्ण;

पूर्णांक fnic_get_stats_data(काष्ठा stats_debug_info *, काष्ठा fnic_stats *);
व्योम fnic_stats_debugfs_init(काष्ठा fnic *);
व्योम fnic_stats_debugfs_हटाओ(काष्ठा fnic *);
#पूर्ण_अगर /* _FNIC_STATS_H_ */
