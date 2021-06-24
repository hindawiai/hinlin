<शैली गुरु>
/*
 * Copyright 2012 Cisco Systems, Inc.  All rights reserved.
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

#समावेश <linux/module.h>
#समावेश <linux/mempool.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/समय.स>
#समावेश <linux/vदो_स्मृति.h>
#समावेश "fnic_io.h"
#समावेश "fnic.h"

अचिन्हित पूर्णांक trace_max_pages;
अटल पूर्णांक fnic_max_trace_entries;

अटल अचिन्हित दीर्घ fnic_trace_buf_p;
अटल DEFINE_SPINLOCK(fnic_trace_lock);

अटल fnic_trace_dbg_t fnic_trace_entries;
पूर्णांक fnic_tracing_enabled = 1;

/* अटल अक्षर *fnic_fc_ctlr_trace_buf_p; */

अटल पूर्णांक fc_trace_max_entries;
अटल अचिन्हित दीर्घ fnic_fc_ctlr_trace_buf_p;
अटल fnic_trace_dbg_t fc_trace_entries;
पूर्णांक fnic_fc_tracing_enabled = 1;
पूर्णांक fnic_fc_trace_cleared = 1;
अटल DEFINE_SPINLOCK(fnic_fc_trace_lock);


/*
 * fnic_trace_get_buf - Give buffer poपूर्णांकer to user to fill up trace inक्रमmation
 *
 * Description:
 * This routine माला_लो next available trace buffer entry location @wr_idx
 * from allocated trace buffer pages and give that memory location
 * to user to store the trace inक्रमmation.
 *
 * Return Value:
 * This routine वापसs poपूर्णांकer to next available trace entry
 * @fnic_buf_head क्रम user to fill trace inक्रमmation.
 */
fnic_trace_data_t *fnic_trace_get_buf(व्योम)
अणु
	अचिन्हित दीर्घ fnic_buf_head;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&fnic_trace_lock, flags);

	/*
	 * Get next available memory location क्रम writing trace inक्रमmation
	 * at @wr_idx and increment @wr_idx
	 */
	fnic_buf_head =
		fnic_trace_entries.page_offset[fnic_trace_entries.wr_idx];
	fnic_trace_entries.wr_idx++;

	/*
	 * Verअगरy अगर trace buffer is full then change wd_idx to
	 * start from zero
	 */
	अगर (fnic_trace_entries.wr_idx >= fnic_max_trace_entries)
		fnic_trace_entries.wr_idx = 0;

	/*
	 * Verअगरy अगर ग_लिखो index @wr_idx and पढ़ो index @rd_idx are same then
	 * increment @rd_idx to move to next entry in trace buffer
	 */
	अगर (fnic_trace_entries.wr_idx == fnic_trace_entries.rd_idx) अणु
		fnic_trace_entries.rd_idx++;
		अगर (fnic_trace_entries.rd_idx >= fnic_max_trace_entries)
			fnic_trace_entries.rd_idx = 0;
	पूर्ण
	spin_unlock_irqrestore(&fnic_trace_lock, flags);
	वापस (fnic_trace_data_t *)fnic_buf_head;
पूर्ण

/*
 * fnic_get_trace_data - Copy trace buffer to a memory file
 * @fnic_dbgfs_t: poपूर्णांकer to debugfs trace buffer
 *
 * Description:
 * This routine gathers the fnic trace debugfs data from the fnic_trace_data_t
 * buffer and dumps it to fnic_dbgfs_t. It will start at the rd_idx entry in
 * the log and process the log until the end of the buffer. Then it will gather
 * from the beginning of the log and process until the current entry @wr_idx.
 *
 * Return Value:
 * This routine वापसs the amount of bytes that were dumped पूर्णांकo fnic_dbgfs_t
 */
पूर्णांक fnic_get_trace_data(fnic_dbgfs_t *fnic_dbgfs_prt)
अणु
	पूर्णांक rd_idx;
	पूर्णांक wr_idx;
	पूर्णांक len = 0;
	अचिन्हित दीर्घ flags;
	अक्षर str[KSYM_SYMBOL_LEN];
	काष्ठा बारpec64 val;
	fnic_trace_data_t *tbp;

	spin_lock_irqsave(&fnic_trace_lock, flags);
	rd_idx = fnic_trace_entries.rd_idx;
	wr_idx = fnic_trace_entries.wr_idx;
	अगर (wr_idx < rd_idx) अणु
		जबतक (1) अणु
			/* Start from पढ़ो index @rd_idx */
			tbp = (fnic_trace_data_t *)
				  fnic_trace_entries.page_offset[rd_idx];
			अगर (!tbp) अणु
				spin_unlock_irqrestore(&fnic_trace_lock, flags);
				वापस 0;
			पूर्ण
			/* Convert function poपूर्णांकer to function name */
			अगर (माप(अचिन्हित दीर्घ) < 8) अणु
				sprपूर्णांक_symbol(str, tbp->fnaddr.low);
				jअगरfies_to_बारpec64(tbp->बारtamp.low, &val);
			पूर्ण अन्यथा अणु
				sprपूर्णांक_symbol(str, tbp->fnaddr.val);
				jअगरfies_to_बारpec64(tbp->बारtamp.val, &val);
			पूर्ण
			/*
			 * Dump trace buffer entry to memory file
			 * and increment पढ़ो index @rd_idx
			 */
			len += scnम_लिखो(fnic_dbgfs_prt->buffer + len,
				  (trace_max_pages * PAGE_SIZE * 3) - len,
				  "%16llu.%09lu %-50s %8x %8x %16llx %16llx "
				  "%16llx %16llx %16llx\n", (u64)val.tv_sec,
				  val.tv_nsec, str, tbp->host_no, tbp->tag,
				  tbp->data[0], tbp->data[1], tbp->data[2],
				  tbp->data[3], tbp->data[4]);
			rd_idx++;
			/*
			 * If rd_idx is reached to maximum trace entries
			 * then move rd_idx to zero
			 */
			अगर (rd_idx > (fnic_max_trace_entries-1))
				rd_idx = 0;
			/*
			 * Continue dumping trace buffer entries पूर्णांकo
			 * memory file till rd_idx reaches ग_लिखो index
			 */
			अगर (rd_idx == wr_idx)
				अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (wr_idx > rd_idx) अणु
		जबतक (1) अणु
			/* Start from पढ़ो index @rd_idx */
			tbp = (fnic_trace_data_t *)
				  fnic_trace_entries.page_offset[rd_idx];
			अगर (!tbp) अणु
				spin_unlock_irqrestore(&fnic_trace_lock, flags);
				वापस 0;
			पूर्ण
			/* Convert function poपूर्णांकer to function name */
			अगर (माप(अचिन्हित दीर्घ) < 8) अणु
				sprपूर्णांक_symbol(str, tbp->fnaddr.low);
				jअगरfies_to_बारpec64(tbp->बारtamp.low, &val);
			पूर्ण अन्यथा अणु
				sprपूर्णांक_symbol(str, tbp->fnaddr.val);
				jअगरfies_to_बारpec64(tbp->बारtamp.val, &val);
			पूर्ण
			/*
			 * Dump trace buffer entry to memory file
			 * and increment पढ़ो index @rd_idx
			 */
			len += scnम_लिखो(fnic_dbgfs_prt->buffer + len,
				  (trace_max_pages * PAGE_SIZE * 3) - len,
				  "%16llu.%09lu %-50s %8x %8x %16llx %16llx "
				  "%16llx %16llx %16llx\n", (u64)val.tv_sec,
				  val.tv_nsec, str, tbp->host_no, tbp->tag,
				  tbp->data[0], tbp->data[1], tbp->data[2],
				  tbp->data[3], tbp->data[4]);
			rd_idx++;
			/*
			 * Continue dumping trace buffer entries पूर्णांकo
			 * memory file till rd_idx reaches ग_लिखो index
			 */
			अगर (rd_idx == wr_idx)
				अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&fnic_trace_lock, flags);
	वापस len;
पूर्ण

/*
 * fnic_get_stats_data - Copy fnic stats buffer to a memory file
 * @fnic_dbgfs_t: poपूर्णांकer to debugfs fnic stats buffer
 *
 * Description:
 * This routine gathers the fnic stats debugfs data from the fnic_stats काष्ठा
 * and dumps it to stats_debug_info.
 *
 * Return Value:
 * This routine वापसs the amount of bytes that were dumped पूर्णांकo
 * stats_debug_info
 */
पूर्णांक fnic_get_stats_data(काष्ठा stats_debug_info *debug,
			काष्ठा fnic_stats *stats)
अणु
	पूर्णांक len = 0;
	पूर्णांक buf_size = debug->buf_size;
	काष्ठा बारpec64 val1, val2;

	kसमय_get_real_ts64(&val1);
	len = scnम_लिखो(debug->debug_buffer + len, buf_size - len,
		"------------------------------------------\n"
		 "\t\tTime\n"
		"------------------------------------------\n");

	len += scnम_लिखो(debug->debug_buffer + len, buf_size - len,
		"Current time :          [%lld:%ld]\n"
		"Last stats reset time:  [%lld:%09ld]\n"
		"Last stats read time:   [%lld:%ld]\n"
		"delta since last reset: [%lld:%ld]\n"
		"delta since last read:  [%lld:%ld]\n",
	(s64)val1.tv_sec, val1.tv_nsec,
	(s64)stats->stats_बारtamps.last_reset_समय.tv_sec,
	stats->stats_बारtamps.last_reset_समय.tv_nsec,
	(s64)stats->stats_बारtamps.last_पढ़ो_समय.tv_sec,
	stats->stats_बारtamps.last_पढ़ो_समय.tv_nsec,
	(s64)बारpec64_sub(val1, stats->stats_बारtamps.last_reset_समय).tv_sec,
	बारpec64_sub(val1, stats->stats_बारtamps.last_reset_समय).tv_nsec,
	(s64)बारpec64_sub(val1, stats->stats_बारtamps.last_पढ़ो_समय).tv_sec,
	बारpec64_sub(val1, stats->stats_बारtamps.last_पढ़ो_समय).tv_nsec);

	stats->stats_बारtamps.last_पढ़ो_समय = val1;

	len += scnम_लिखो(debug->debug_buffer + len, buf_size - len,
		  "------------------------------------------\n"
		  "\t\tIO Statistics\n"
		  "------------------------------------------\n");
	len += scnम_लिखो(debug->debug_buffer + len, buf_size - len,
		  "Number of Active IOs: %lld\nMaximum Active IOs: %lld\n"
		  "Number of IOs: %lld\nNumber of IO Completions: %lld\n"
		  "Number of IO Failures: %lld\nNumber of IO NOT Found: %lld\n"
		  "Number of Memory alloc Failures: %lld\n"
		  "Number of IOREQ Null: %lld\n"
		  "Number of SCSI cmd pointer Null: %lld\n"

		  "\nIO completion times: \n"
		  "            < 10 ms : %lld\n"
		  "     10 ms - 100 ms : %lld\n"
		  "    100 ms - 500 ms : %lld\n"
		  "    500 ms -   5 sec: %lld\n"
		  "     5 sec -  10 sec: %lld\n"
		  "    10 sec -  30 sec: %lld\n"
		  "            > 30 sec: %lld\n",
		  (u64)atomic64_पढ़ो(&stats->io_stats.active_ios),
		  (u64)atomic64_पढ़ो(&stats->io_stats.max_active_ios),
		  (u64)atomic64_पढ़ो(&stats->io_stats.num_ios),
		  (u64)atomic64_पढ़ो(&stats->io_stats.io_completions),
		  (u64)atomic64_पढ़ो(&stats->io_stats.io_failures),
		  (u64)atomic64_पढ़ो(&stats->io_stats.io_not_found),
		  (u64)atomic64_पढ़ो(&stats->io_stats.alloc_failures),
		  (u64)atomic64_पढ़ो(&stats->io_stats.ioreq_null),
		  (u64)atomic64_पढ़ो(&stats->io_stats.sc_null),
		  (u64)atomic64_पढ़ो(&stats->io_stats.io_btw_0_to_10_msec),
		  (u64)atomic64_पढ़ो(&stats->io_stats.io_btw_10_to_100_msec),
		  (u64)atomic64_पढ़ो(&stats->io_stats.io_btw_100_to_500_msec),
		  (u64)atomic64_पढ़ो(&stats->io_stats.io_btw_500_to_5000_msec),
		  (u64)atomic64_पढ़ो(&stats->io_stats.io_btw_5000_to_10000_msec),
		  (u64)atomic64_पढ़ो(&stats->io_stats.io_btw_10000_to_30000_msec),
		  (u64)atomic64_पढ़ो(&stats->io_stats.io_greater_than_30000_msec));

	len += scnम_लिखो(debug->debug_buffer + len, buf_size - len,
		  "\nCurrent Max IO time : %lld\n",
		  (u64)atomic64_पढ़ो(&stats->io_stats.current_max_io_समय));

	len += scnम_लिखो(debug->debug_buffer + len, buf_size - len,
		  "\n------------------------------------------\n"
		  "\t\tAbort Statistics\n"
		  "------------------------------------------\n");

	len += scnम_लिखो(debug->debug_buffer + len, buf_size - len,
		  "Number of Aborts: %lld\n"
		  "Number of Abort Failures: %lld\n"
		  "Number of Abort Driver Timeouts: %lld\n"
		  "Number of Abort FW Timeouts: %lld\n"
		  "Number of Abort IO NOT Found: %lld\n"

		  "Abort issued times: \n"
		  "            < 6 sec : %lld\n"
		  "     6 sec - 20 sec : %lld\n"
		  "    20 sec - 30 sec : %lld\n"
		  "    30 sec - 40 sec : %lld\n"
		  "    40 sec - 50 sec : %lld\n"
		  "    50 sec - 60 sec : %lld\n"
		  "            > 60 sec: %lld\n",

		  (u64)atomic64_पढ़ो(&stats->abts_stats.पातs),
		  (u64)atomic64_पढ़ो(&stats->abts_stats.पात_failures),
		  (u64)atomic64_पढ़ो(&stats->abts_stats.पात_drv_समयouts),
		  (u64)atomic64_पढ़ो(&stats->abts_stats.पात_fw_समयouts),
		  (u64)atomic64_पढ़ो(&stats->abts_stats.पात_io_not_found),
		  (u64)atomic64_पढ़ो(&stats->abts_stats.पात_issued_btw_0_to_6_sec),
		  (u64)atomic64_पढ़ो(&stats->abts_stats.पात_issued_btw_6_to_20_sec),
		  (u64)atomic64_पढ़ो(&stats->abts_stats.पात_issued_btw_20_to_30_sec),
		  (u64)atomic64_पढ़ो(&stats->abts_stats.पात_issued_btw_30_to_40_sec),
		  (u64)atomic64_पढ़ो(&stats->abts_stats.पात_issued_btw_40_to_50_sec),
		  (u64)atomic64_पढ़ो(&stats->abts_stats.पात_issued_btw_50_to_60_sec),
		  (u64)atomic64_पढ़ो(&stats->abts_stats.पात_issued_greater_than_60_sec));

	len += scnम_लिखो(debug->debug_buffer + len, buf_size - len,
		  "\n------------------------------------------\n"
		  "\t\tTerminate Statistics\n"
		  "------------------------------------------\n");

	len += scnम_लिखो(debug->debug_buffer + len, buf_size - len,
		  "Number of Terminates: %lld\n"
		  "Maximum Terminates: %lld\n"
		  "Number of Terminate Driver Timeouts: %lld\n"
		  "Number of Terminate FW Timeouts: %lld\n"
		  "Number of Terminate IO NOT Found: %lld\n"
		  "Number of Terminate Failures: %lld\n",
		  (u64)atomic64_पढ़ो(&stats->term_stats.terminates),
		  (u64)atomic64_पढ़ो(&stats->term_stats.max_terminates),
		  (u64)atomic64_पढ़ो(&stats->term_stats.terminate_drv_समयouts),
		  (u64)atomic64_पढ़ो(&stats->term_stats.terminate_fw_समयouts),
		  (u64)atomic64_पढ़ो(&stats->term_stats.terminate_io_not_found),
		  (u64)atomic64_पढ़ो(&stats->term_stats.terminate_failures));

	len += scnम_लिखो(debug->debug_buffer + len, buf_size - len,
		  "\n------------------------------------------\n"
		  "\t\tReset Statistics\n"
		  "------------------------------------------\n");

	len += scnम_लिखो(debug->debug_buffer + len, buf_size - len,
		  "Number of Device Resets: %lld\n"
		  "Number of Device Reset Failures: %lld\n"
		  "Number of Device Reset Aborts: %lld\n"
		  "Number of Device Reset Timeouts: %lld\n"
		  "Number of Device Reset Terminates: %lld\n"
		  "Number of FW Resets: %lld\n"
		  "Number of FW Reset Completions: %lld\n"
		  "Number of FW Reset Failures: %lld\n"
		  "Number of Fnic Reset: %lld\n"
		  "Number of Fnic Reset Completions: %lld\n"
		  "Number of Fnic Reset Failures: %lld\n",
		  (u64)atomic64_पढ़ो(&stats->reset_stats.device_resets),
		  (u64)atomic64_पढ़ो(&stats->reset_stats.device_reset_failures),
		  (u64)atomic64_पढ़ो(&stats->reset_stats.device_reset_पातs),
		  (u64)atomic64_पढ़ो(&stats->reset_stats.device_reset_समयouts),
		  (u64)atomic64_पढ़ो(
			  &stats->reset_stats.device_reset_terminates),
		  (u64)atomic64_पढ़ो(&stats->reset_stats.fw_resets),
		  (u64)atomic64_पढ़ो(&stats->reset_stats.fw_reset_completions),
		  (u64)atomic64_पढ़ो(&stats->reset_stats.fw_reset_failures),
		  (u64)atomic64_पढ़ो(&stats->reset_stats.fnic_resets),
		  (u64)atomic64_पढ़ो(
			  &stats->reset_stats.fnic_reset_completions),
		  (u64)atomic64_पढ़ो(&stats->reset_stats.fnic_reset_failures));

	len += scnम_लिखो(debug->debug_buffer + len, buf_size - len,
		  "\n------------------------------------------\n"
		  "\t\tFirmware Statistics\n"
		  "------------------------------------------\n");

	len += scnम_लिखो(debug->debug_buffer + len, buf_size - len,
		  "Number of Active FW Requests %lld\n"
		  "Maximum FW Requests: %lld\n"
		  "Number of FW out of resources: %lld\n"
		  "Number of FW IO errors: %lld\n",
		  (u64)atomic64_पढ़ो(&stats->fw_stats.active_fw_reqs),
		  (u64)atomic64_पढ़ो(&stats->fw_stats.max_fw_reqs),
		  (u64)atomic64_पढ़ो(&stats->fw_stats.fw_out_of_resources),
		  (u64)atomic64_पढ़ो(&stats->fw_stats.io_fw_errs));

	len += scnम_लिखो(debug->debug_buffer + len, buf_size - len,
		  "\n------------------------------------------\n"
		  "\t\tVlan Discovery Statistics\n"
		  "------------------------------------------\n");

	len += scnम_लिखो(debug->debug_buffer + len, buf_size - len,
		  "Number of Vlan Discovery Requests Sent %lld\n"
		  "Vlan Response Received with no FCF VLAN ID: %lld\n"
		  "No solicitations recvd after vlan set, expiry count: %lld\n"
		  "Flogi rejects count: %lld\n",
		  (u64)atomic64_पढ़ो(&stats->vlan_stats.vlan_disc_reqs),
		  (u64)atomic64_पढ़ो(&stats->vlan_stats.resp_withno_vlanID),
		  (u64)atomic64_पढ़ो(&stats->vlan_stats.sol_expiry_count),
		  (u64)atomic64_पढ़ो(&stats->vlan_stats.flogi_rejects));

	len += scnम_लिखो(debug->debug_buffer + len, buf_size - len,
		  "\n------------------------------------------\n"
		  "\t\tOther Important Statistics\n"
		  "------------------------------------------\n");

	jअगरfies_to_बारpec64(stats->misc_stats.last_isr_समय, &val1);
	jअगरfies_to_बारpec64(stats->misc_stats.last_ack_समय, &val2);

	len += scnम_लिखो(debug->debug_buffer + len, buf_size - len,
		  "Last ISR time: %llu (%8llu.%09lu)\n"
		  "Last ACK time: %llu (%8llu.%09lu)\n"
		  "Max ISR jiffies: %llu\n"
		  "Max ISR time (ms) (0 denotes < 1 ms): %llu\n"
		  "Corr. work done: %llu\n"
		  "Number of ISRs: %lld\n"
		  "Maximum CQ Entries: %lld\n"
		  "Number of ACK index out of range: %lld\n"
		  "Number of data count mismatch: %lld\n"
		  "Number of FCPIO Timeouts: %lld\n"
		  "Number of FCPIO Aborted: %lld\n"
		  "Number of SGL Invalid: %lld\n"
		  "Number of Copy WQ Alloc Failures for ABTs: %lld\n"
		  "Number of Copy WQ Alloc Failures for Device Reset: %lld\n"
		  "Number of Copy WQ Alloc Failures for IOs: %lld\n"
		  "Number of no icmnd itmf Completions: %lld\n"
		  "Number of Check Conditions encountered: %lld\n"
		  "Number of QUEUE Fulls: %lld\n"
		  "Number of rport not ready: %lld\n"
		  "Number of receive frame errors: %lld\n",
		  (u64)stats->misc_stats.last_isr_समय,
		  (s64)val1.tv_sec, val1.tv_nsec,
		  (u64)stats->misc_stats.last_ack_समय,
		  (s64)val2.tv_sec, val2.tv_nsec,
		  (u64)atomic64_पढ़ो(&stats->misc_stats.max_isr_jअगरfies),
		  (u64)atomic64_पढ़ो(&stats->misc_stats.max_isr_समय_ms),
		  (u64)atomic64_पढ़ो(&stats->misc_stats.corr_work_करोne),
		  (u64)atomic64_पढ़ो(&stats->misc_stats.isr_count),
		  (u64)atomic64_पढ़ो(&stats->misc_stats.max_cq_entries),
		  (u64)atomic64_पढ़ो(&stats->misc_stats.ack_index_out_of_range),
		  (u64)atomic64_पढ़ो(&stats->misc_stats.data_count_mismatch),
		  (u64)atomic64_पढ़ो(&stats->misc_stats.fcpio_समयout),
		  (u64)atomic64_पढ़ो(&stats->misc_stats.fcpio_पातed),
		  (u64)atomic64_पढ़ो(&stats->misc_stats.sgl_invalid),
		  (u64)atomic64_पढ़ो(
			  &stats->misc_stats.abts_cpwq_alloc_failures),
		  (u64)atomic64_पढ़ो(
			  &stats->misc_stats.devrst_cpwq_alloc_failures),
		  (u64)atomic64_पढ़ो(&stats->misc_stats.io_cpwq_alloc_failures),
		  (u64)atomic64_पढ़ो(&stats->misc_stats.no_icmnd_iपंचांगf_cmpls),
		  (u64)atomic64_पढ़ो(&stats->misc_stats.check_condition),
		  (u64)atomic64_पढ़ो(&stats->misc_stats.queue_fulls),
		  (u64)atomic64_पढ़ो(&stats->misc_stats.rport_not_पढ़ोy),
		  (u64)atomic64_पढ़ो(&stats->misc_stats.frame_errors));

	len += scnम_लिखो(debug->debug_buffer + len, buf_size - len,
			"Firmware reported port speed: %llu\n",
			(u64)atomic64_पढ़ो(
				&stats->misc_stats.current_port_speed));

	वापस len;

पूर्ण

/*
 * fnic_trace_buf_init - Initialize fnic trace buffer logging facility
 *
 * Description:
 * Initialize trace buffer data काष्ठाure by allocating required memory and
 * setting page_offset inक्रमmation क्रम every trace entry by adding trace entry
 * length to previous page_offset value.
 */
पूर्णांक fnic_trace_buf_init(व्योम)
अणु
	अचिन्हित दीर्घ fnic_buf_head;
	पूर्णांक i;
	पूर्णांक err = 0;

	trace_max_pages = fnic_trace_max_pages;
	fnic_max_trace_entries = (trace_max_pages * PAGE_SIZE)/
					  FNIC_ENTRY_SIZE_BYTES;

	fnic_trace_buf_p = (अचिन्हित दीर्घ)vzalloc(trace_max_pages * PAGE_SIZE);
	अगर (!fnic_trace_buf_p) अणु
		prपूर्णांकk(KERN_ERR PFX "Failed to allocate memory "
				  "for fnic_trace_buf_p\n");
		err = -ENOMEM;
		जाओ err_fnic_trace_buf_init;
	पूर्ण

	fnic_trace_entries.page_offset =
		vदो_स्मृति(array_size(fnic_max_trace_entries,
				   माप(अचिन्हित दीर्घ)));
	अगर (!fnic_trace_entries.page_offset) अणु
		prपूर्णांकk(KERN_ERR PFX "Failed to allocate memory for"
				  " page_offset\n");
		अगर (fnic_trace_buf_p) अणु
			vमुक्त((व्योम *)fnic_trace_buf_p);
			fnic_trace_buf_p = 0;
		पूर्ण
		err = -ENOMEM;
		जाओ err_fnic_trace_buf_init;
	पूर्ण
	स_रखो((व्योम *)fnic_trace_entries.page_offset, 0,
		  (fnic_max_trace_entries * माप(अचिन्हित दीर्घ)));
	fnic_trace_entries.wr_idx = fnic_trace_entries.rd_idx = 0;
	fnic_buf_head = fnic_trace_buf_p;

	/*
	 * Set page_offset field of fnic_trace_entries काष्ठा by
	 * calculating memory location क्रम every trace entry using
	 * length of each trace entry
	 */
	क्रम (i = 0; i < fnic_max_trace_entries; i++) अणु
		fnic_trace_entries.page_offset[i] = fnic_buf_head;
		fnic_buf_head += FNIC_ENTRY_SIZE_BYTES;
	पूर्ण
	fnic_trace_debugfs_init();
	pr_info("fnic: Successfully Initialized Trace Buffer\n");
	वापस err;

err_fnic_trace_buf_init:
	वापस err;
पूर्ण

/*
 * fnic_trace_मुक्त - Free memory of fnic trace data काष्ठाures.
 */
व्योम fnic_trace_मुक्त(व्योम)
अणु
	fnic_tracing_enabled = 0;
	fnic_trace_debugfs_terminate();
	अगर (fnic_trace_entries.page_offset) अणु
		vमुक्त((व्योम *)fnic_trace_entries.page_offset);
		fnic_trace_entries.page_offset = शून्य;
	पूर्ण
	अगर (fnic_trace_buf_p) अणु
		vमुक्त((व्योम *)fnic_trace_buf_p);
		fnic_trace_buf_p = 0;
	पूर्ण
	prपूर्णांकk(KERN_INFO PFX "Successfully Freed Trace Buffer\n");
पूर्ण

/*
 * fnic_fc_ctlr_trace_buf_init -
 * Initialize trace buffer to log fnic control frames
 * Description:
 * Initialize trace buffer data काष्ठाure by allocating
 * required memory क्रम trace data as well as क्रम Indexes.
 * Frame size is 256 bytes and
 * memory is allocated क्रम 1024 entries of 256 bytes.
 * Page_offset(Index) is set to the address of trace entry
 * and page_offset is initialized by adding frame size
 * to the previous page_offset entry.
 */

पूर्णांक fnic_fc_trace_init(व्योम)
अणु
	अचिन्हित दीर्घ fc_trace_buf_head;
	पूर्णांक err = 0;
	पूर्णांक i;

	fc_trace_max_entries = (fnic_fc_trace_max_pages * PAGE_SIZE)/
				FC_TRC_SIZE_BYTES;
	fnic_fc_ctlr_trace_buf_p =
		(अचिन्हित दीर्घ)vदो_स्मृति(array_size(PAGE_SIZE,
						  fnic_fc_trace_max_pages));
	अगर (!fnic_fc_ctlr_trace_buf_p) अणु
		pr_err("fnic: Failed to allocate memory for "
		       "FC Control Trace Buf\n");
		err = -ENOMEM;
		जाओ err_fnic_fc_ctlr_trace_buf_init;
	पूर्ण

	स_रखो((व्योम *)fnic_fc_ctlr_trace_buf_p, 0,
			fnic_fc_trace_max_pages * PAGE_SIZE);

	/* Allocate memory क्रम page offset */
	fc_trace_entries.page_offset =
		vदो_स्मृति(array_size(fc_trace_max_entries,
				   माप(अचिन्हित दीर्घ)));
	अगर (!fc_trace_entries.page_offset) अणु
		pr_err("fnic:Failed to allocate memory for page_offset\n");
		अगर (fnic_fc_ctlr_trace_buf_p) अणु
			pr_err("fnic: Freeing FC Control Trace Buf\n");
			vमुक्त((व्योम *)fnic_fc_ctlr_trace_buf_p);
			fnic_fc_ctlr_trace_buf_p = 0;
		पूर्ण
		err = -ENOMEM;
		जाओ err_fnic_fc_ctlr_trace_buf_init;
	पूर्ण
	स_रखो((व्योम *)fc_trace_entries.page_offset, 0,
	       (fc_trace_max_entries * माप(अचिन्हित दीर्घ)));

	fc_trace_entries.rd_idx = fc_trace_entries.wr_idx = 0;
	fc_trace_buf_head = fnic_fc_ctlr_trace_buf_p;

	/*
	* Set up fc_trace_entries.page_offset field with memory location
	* क्रम every trace entry
	*/
	क्रम (i = 0; i < fc_trace_max_entries; i++) अणु
		fc_trace_entries.page_offset[i] = fc_trace_buf_head;
		fc_trace_buf_head += FC_TRC_SIZE_BYTES;
	पूर्ण
	fnic_fc_trace_debugfs_init();
	pr_info("fnic: Successfully Initialized FC_CTLR Trace Buffer\n");
	वापस err;

err_fnic_fc_ctlr_trace_buf_init:
	वापस err;
पूर्ण

/*
 * Fnic_fc_ctlr_trace_मुक्त - Free memory of fnic_fc_ctlr trace data काष्ठाures.
 */
व्योम fnic_fc_trace_मुक्त(व्योम)
अणु
	fnic_fc_tracing_enabled = 0;
	fnic_fc_trace_debugfs_terminate();
	अगर (fc_trace_entries.page_offset) अणु
		vमुक्त((व्योम *)fc_trace_entries.page_offset);
		fc_trace_entries.page_offset = शून्य;
	पूर्ण
	अगर (fnic_fc_ctlr_trace_buf_p) अणु
		vमुक्त((व्योम *)fnic_fc_ctlr_trace_buf_p);
		fnic_fc_ctlr_trace_buf_p = 0;
	पूर्ण
	pr_info("fnic:Successfully FC_CTLR Freed Trace Buffer\n");
पूर्ण

/*
 * fnic_fc_ctlr_set_trace_data:
 *       Maपूर्णांकain rd & wr idx accordingly and set data
 * Passed parameters:
 *       host_no: host number associated with fnic
 *       frame_type: send_frame, rece_frame or link event
 *       fc_frame: poपूर्णांकer to fc_frame
 *       frame_len: Length of the fc_frame
 * Description:
 *   This routine will get next available wr_idx and
 *   copy all passed trace data to the buffer poपूर्णांकed by wr_idx
 *   and increment wr_idx. It will also make sure that we करोnt
 *   overग_लिखो the entry which we are पढ़ोing and also
 *   wrap around अगर we reach the maximum entries.
 * Returned Value:
 *   It will वापस 0 क्रम success or -1 क्रम failure
 */
पूर्णांक fnic_fc_trace_set_data(u32 host_no, u8 frame_type,
				अक्षर *frame, u32 fc_trc_frame_len)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा fc_trace_hdr *fc_buf;
	अचिन्हित दीर्घ eth_fcoe_hdr_len;
	अक्षर *fc_trace;

	अगर (fnic_fc_tracing_enabled == 0)
		वापस 0;

	spin_lock_irqsave(&fnic_fc_trace_lock, flags);

	अगर (fnic_fc_trace_cleared == 1) अणु
		fc_trace_entries.rd_idx = fc_trace_entries.wr_idx = 0;
		pr_info("fnic: Resetting the read idx\n");
		स_रखो((व्योम *)fnic_fc_ctlr_trace_buf_p, 0,
				fnic_fc_trace_max_pages * PAGE_SIZE);
		fnic_fc_trace_cleared = 0;
	पूर्ण

	fc_buf = (काष्ठा fc_trace_hdr *)
		fc_trace_entries.page_offset[fc_trace_entries.wr_idx];

	fc_trace_entries.wr_idx++;

	अगर (fc_trace_entries.wr_idx >= fc_trace_max_entries)
		fc_trace_entries.wr_idx = 0;

	अगर (fc_trace_entries.wr_idx == fc_trace_entries.rd_idx) अणु
		fc_trace_entries.rd_idx++;
		अगर (fc_trace_entries.rd_idx >= fc_trace_max_entries)
			fc_trace_entries.rd_idx = 0;
	पूर्ण

	kसमय_get_real_ts64(&fc_buf->समय_stamp);
	fc_buf->host_no = host_no;
	fc_buf->frame_type = frame_type;

	fc_trace = (अक्षर *)FC_TRACE_ADDRESS(fc_buf);

	/* During the receive path, we करो not have eth hdr as well as fcoe hdr
	 * at trace entry poपूर्णांक so we will stuff 0xff just to make it generic.
	 */
	अगर (frame_type == FNIC_FC_RECV) अणु
		eth_fcoe_hdr_len = माप(काष्ठा ethhdr) +
					माप(काष्ठा fcoe_hdr);
		स_रखो((अक्षर *)fc_trace, 0xff, eth_fcoe_hdr_len);
		/* Copy the rest of data frame */
		स_नकल((अक्षर *)(fc_trace + eth_fcoe_hdr_len), (व्योम *)frame,
		min_t(u8, fc_trc_frame_len,
			(u8)(FC_TRC_SIZE_BYTES - FC_TRC_HEADER_SIZE
						- eth_fcoe_hdr_len)));
	पूर्ण अन्यथा अणु
		स_नकल((अक्षर *)fc_trace, (व्योम *)frame,
		min_t(u8, fc_trc_frame_len,
			(u8)(FC_TRC_SIZE_BYTES - FC_TRC_HEADER_SIZE)));
	पूर्ण

	/* Store the actual received length */
	fc_buf->frame_len = fc_trc_frame_len;

	spin_unlock_irqrestore(&fnic_fc_trace_lock, flags);
	वापस 0;
पूर्ण

/*
 * fnic_fc_ctlr_get_trace_data: Copy trace buffer to a memory file
 * Passed parameter:
 *       @fnic_dbgfs_t: poपूर्णांकer to debugfs trace buffer
 *       rdata_flag: 1 => Unक्रमmatted file
 *                   0 => क्रमmatted file
 * Description:
 *       This routine will copy the trace data to memory file with
 *       proper क्रमmatting and also copy to another memory
 *       file without क्रमmatting क्रम further processing.
 * Return Value:
 *       Number of bytes that were dumped पूर्णांकo fnic_dbgfs_t
 */

पूर्णांक fnic_fc_trace_get_data(fnic_dbgfs_t *fnic_dbgfs_prt, u8 rdata_flag)
अणु
	पूर्णांक rd_idx, wr_idx;
	अचिन्हित दीर्घ flags;
	पूर्णांक len = 0, j;
	काष्ठा fc_trace_hdr *tdata;
	अक्षर *fc_trace;

	spin_lock_irqsave(&fnic_fc_trace_lock, flags);
	अगर (fc_trace_entries.wr_idx == fc_trace_entries.rd_idx) अणु
		spin_unlock_irqrestore(&fnic_fc_trace_lock, flags);
		pr_info("fnic: Buffer is empty\n");
		वापस 0;
	पूर्ण
	rd_idx = fc_trace_entries.rd_idx;
	wr_idx = fc_trace_entries.wr_idx;
	अगर (rdata_flag == 0) अणु
		len += scnम_लिखो(fnic_dbgfs_prt->buffer + len,
			(fnic_fc_trace_max_pages * PAGE_SIZE * 3) - len,
			"Time Stamp (UTC)\t\t"
			"Host No:   F Type:  len:     FCoE_FRAME:\n");
	पूर्ण

	जबतक (rd_idx != wr_idx) अणु
		tdata = (काष्ठा fc_trace_hdr *)
			fc_trace_entries.page_offset[rd_idx];
		अगर (!tdata) अणु
			pr_info("fnic: Rd data is NULL\n");
			spin_unlock_irqrestore(&fnic_fc_trace_lock, flags);
			वापस 0;
		पूर्ण
		अगर (rdata_flag == 0) अणु
			copy_and_क्रमmat_trace_data(tdata,
				fnic_dbgfs_prt, &len, rdata_flag);
		पूर्ण अन्यथा अणु
			fc_trace = (अक्षर *)tdata;
			क्रम (j = 0; j < FC_TRC_SIZE_BYTES; j++) अणु
				len += scnम_लिखो(fnic_dbgfs_prt->buffer + len,
				(fnic_fc_trace_max_pages * PAGE_SIZE * 3)
				- len, "%02x", fc_trace[j] & 0xff);
			पूर्ण /* क्रम loop */
			len += scnम_लिखो(fnic_dbgfs_prt->buffer + len,
				(fnic_fc_trace_max_pages * PAGE_SIZE * 3) - len,
				"\n");
		पूर्ण
		rd_idx++;
		अगर (rd_idx > (fc_trace_max_entries - 1))
			rd_idx = 0;
	पूर्ण

	spin_unlock_irqrestore(&fnic_fc_trace_lock, flags);
	वापस len;
पूर्ण

/*
 * copy_and_क्रमmat_trace_data: Copy क्रमmatted data to अक्षर * buffer
 * Passed Parameter:
 *      @fc_trace_hdr_t: poपूर्णांकer to trace data
 *      @fnic_dbgfs_t: poपूर्णांकer to debugfs trace buffer
 *      @orig_len: poपूर्णांकer to len
 *      rdata_flag: 0 => Formatted file, 1 => Unक्रमmatted file
 * Description:
 *      This routine will क्रमmat and copy the passed trace data
 *      क्रम क्रमmatted file or unक्रमmatted file accordingly.
 */

व्योम copy_and_क्रमmat_trace_data(काष्ठा fc_trace_hdr *tdata,
				fnic_dbgfs_t *fnic_dbgfs_prt, पूर्णांक *orig_len,
				u8 rdata_flag)
अणु
	काष्ठा पंचांग पंचांग;
	पूर्णांक j, i = 1, len;
	अक्षर *fc_trace, *fmt;
	पूर्णांक ethhdr_len = माप(काष्ठा ethhdr) - 1;
	पूर्णांक fcoehdr_len = माप(काष्ठा fcoe_hdr);
	पूर्णांक fchdr_len = माप(काष्ठा fc_frame_header);
	पूर्णांक max_size = fnic_fc_trace_max_pages * PAGE_SIZE * 3;

	tdata->frame_type = tdata->frame_type & 0x7F;

	len = *orig_len;

	समय64_to_पंचांग(tdata->समय_stamp.tv_sec, 0, &पंचांग);

	fmt = "%02d:%02d:%04ld %02d:%02d:%02d.%09lu ns%8x       %c%8x\t";
	len += scnम_लिखो(fnic_dbgfs_prt->buffer + len,
		max_size - len,
		fmt,
		पंचांग.पंचांग_mon + 1, पंचांग.पंचांग_mday, पंचांग.पंचांग_year + 1900,
		पंचांग.पंचांग_hour, पंचांग.पंचांग_min, पंचांग.पंचांग_sec,
		tdata->समय_stamp.tv_nsec, tdata->host_no,
		tdata->frame_type, tdata->frame_len);

	fc_trace = (अक्षर *)FC_TRACE_ADDRESS(tdata);

	क्रम (j = 0; j < min_t(u8, tdata->frame_len,
		(u8)(FC_TRC_SIZE_BYTES - FC_TRC_HEADER_SIZE)); j++) अणु
		अगर (tdata->frame_type == FNIC_FC_LE) अणु
			len += scnम_लिखो(fnic_dbgfs_prt->buffer + len,
				max_size - len, "%c", fc_trace[j]);
		पूर्ण अन्यथा अणु
			len += scnम_लिखो(fnic_dbgfs_prt->buffer + len,
				max_size - len, "%02x", fc_trace[j] & 0xff);
			len += scnम_लिखो(fnic_dbgfs_prt->buffer + len,
				max_size - len, " ");
			अगर (j == ethhdr_len ||
				j == ethhdr_len + fcoehdr_len ||
				j == ethhdr_len + fcoehdr_len + fchdr_len ||
				(i > 3 && j%fchdr_len == 0)) अणु
				len += scnम_लिखो(fnic_dbgfs_prt->buffer
					+ len, max_size - len,
					"\n\t\t\t\t\t\t\t\t");
				i++;
			पूर्ण
		पूर्ण /* end of अन्यथा*/
	पूर्ण /* End of क्रम loop*/
	len += scnम_लिखो(fnic_dbgfs_prt->buffer + len,
		max_size - len, "\n");
	*orig_len = len;
पूर्ण
