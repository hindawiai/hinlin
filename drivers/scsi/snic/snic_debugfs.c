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

#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/debugfs.h>

#समावेश "snic.h"

/*
 * snic_debugfs_init - Initialize debugfs क्रम snic debug logging
 *
 * Description:
 * When Debugfs is configured this routine sets up fnic debugfs
 * fileप्रणाली. If not alपढ़ोy created. this routine will crate the
 * fnic directory and statistics directory क्रम trace buffer and
 * stats logging
 */
व्योम snic_debugfs_init(व्योम)
अणु
	snic_glob->trc_root = debugfs_create_dir("snic", शून्य);

	snic_glob->stats_root = debugfs_create_dir("statistics",
						   snic_glob->trc_root);
पूर्ण

/*
 * snic_debugfs_term - Tear करोwn debugfs पूर्णांकraकाष्ठाure
 *
 * Description:
 * When Debufs is configured this routine हटाओs debugfs file प्रणाली
 * elements that are specअगरic to snic
 */
व्योम
snic_debugfs_term(व्योम)
अणु
	debugfs_हटाओ(snic_glob->stats_root);
	snic_glob->stats_root = शून्य;

	debugfs_हटाओ(snic_glob->trc_root);
	snic_glob->trc_root = शून्य;
पूर्ण

/*
 * snic_reset_stats_खोलो - Open the reset_stats file
 */
अटल पूर्णांक
snic_reset_stats_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	SNIC_BUG_ON(!inode->i_निजी);
	filp->निजी_data = inode->i_निजी;

	वापस 0;
पूर्ण

/*
 * snic_reset_stats_पढ़ो - Read a reset_stats debugfs file
 * @filp: The file poपूर्णांकer to पढ़ो from.
 * @ubuf: The buffer tocopy the data to.
 * @cnt: The number of bytes to पढ़ो.
 * @ppos: The position in the file to start पढ़ोing frm.
 *
 * Description:
 * This routine पढ़ोs value of variable reset_stats
 * and stores पूर्णांकo local @buf. It will start पढ़ोing file @ppos and
 * copy up to @cnt of data to @ubuf from @buf.
 *
 * Returns:
 * This function वापसs the amount of data that was पढ़ो.
 */
अटल sमाप_प्रकार
snic_reset_stats_पढ़ो(काष्ठा file *filp,
		      अक्षर __user *ubuf,
		      माप_प्रकार cnt,
		      loff_t *ppos)
अणु
	काष्ठा snic *snic = (काष्ठा snic *) filp->निजी_data;
	अक्षर buf[64];
	पूर्णांक len;

	len = प्र_लिखो(buf, "%u\n", snic->reset_stats);

	वापस simple_पढ़ो_from_buffer(ubuf, cnt, ppos, buf, len);
पूर्ण

/*
 * snic_reset_stats_ग_लिखो - Write to reset_stats debugfs file
 * @filp: The file poपूर्णांकer to ग_लिखो from
 * @ubuf: The buffer to copy the data from.
 * @cnt: The number of bytes to ग_लिखो.
 * @ppos: The position in the file to start writing to.
 *
 * Description:
 * This routine ग_लिखोs data from user buffer @ubuf to buffer @buf and
 * resets cumulative stats of snic.
 *
 * Returns:
 * This function वापसs the amount of data that was written.
 */
अटल sमाप_प्रकार
snic_reset_stats_ग_लिखो(काष्ठा file *filp,
		       स्थिर अक्षर __user *ubuf,
		       माप_प्रकार cnt,
		       loff_t *ppos)
अणु
	काष्ठा snic *snic = (काष्ठा snic *) filp->निजी_data;
	काष्ठा snic_stats *stats = &snic->s_stats;
	u64 *io_stats_p = (u64 *) &stats->io;
	u64 *fw_stats_p = (u64 *) &stats->fw;
	अक्षर buf[64];
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	अगर (cnt >= माप(buf))
		वापस -EINVAL;

	अगर (copy_from_user(&buf, ubuf, cnt))
		वापस -EFAULT;

	buf[cnt] = '\0';

	ret = kम_से_अदीर्घ(buf, 10, &val);
	अगर (ret < 0)
		वापस ret;

	snic->reset_stats = val;

	अगर (snic->reset_stats) अणु
		/* Skip variable is used to aव्योम descrepancies to Num IOs
		 * and IO Completions stats. Skip incrementing No IO Compls
		 * क्रम pending active IOs after reset_stats
		 */
		atomic64_set(&snic->io_cmpl_skip,
			     atomic64_पढ़ो(&stats->io.active));
		स_रखो(&stats->abts, 0, माप(काष्ठा snic_पात_stats));
		स_रखो(&stats->reset, 0, माप(काष्ठा snic_reset_stats));
		स_रखो(&stats->misc, 0, माप(काष्ठा snic_misc_stats));
		स_रखो(io_stats_p+1,
			0,
			माप(काष्ठा snic_io_stats) - माप(u64));
		स_रखो(fw_stats_p+1,
			0,
			माप(काष्ठा snic_fw_stats) - माप(u64));
	पूर्ण

	(*ppos)++;

	SNIC_HOST_INFO(snic->shost, "Reset Op: Driver statistics.\n");

	वापस cnt;
पूर्ण

अटल पूर्णांक
snic_reset_stats_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	filp->निजी_data = शून्य;

	वापस 0;
पूर्ण

/*
 * snic_stats_show - Formats and prपूर्णांकs per host specअगरic driver stats.
 */
अटल पूर्णांक
snic_stats_show(काष्ठा seq_file *sfp, व्योम *data)
अणु
	काष्ठा snic *snic = (काष्ठा snic *) sfp->निजी;
	काष्ठा snic_stats *stats = &snic->s_stats;
	काष्ठा बारpec64 last_isr_पंचांगs, last_ack_पंचांगs;
	u64 maxio_पंचांग;
	पूर्णांक i;

	/* Dump IO Stats */
	seq_म_लिखो(sfp,
		   "------------------------------------------\n"
		   "\t\t IO Statistics\n"
		   "------------------------------------------\n");

	maxio_पंचांग = (u64) atomic64_पढ़ो(&stats->io.max_समय);
	seq_म_लिखो(sfp,
		   "Active IOs                  : %lld\n"
		   "Max Active IOs              : %lld\n"
		   "Total IOs                   : %lld\n"
		   "IOs Completed               : %lld\n"
		   "IOs Failed                  : %lld\n"
		   "IOs Not Found               : %lld\n"
		   "Memory Alloc Failures       : %lld\n"
		   "REQs Null                   : %lld\n"
		   "SCSI Cmd Pointers Null      : %lld\n"
		   "Max SGL for any IO          : %lld\n"
		   "Max IO Size                 : %lld Sectors\n"
		   "Max Queuing Time            : %lld\n"
		   "Max Completion Time         : %lld\n"
		   "Max IO Process Time(FW)     : %lld (%u msec)\n",
		   (u64) atomic64_पढ़ो(&stats->io.active),
		   (u64) atomic64_पढ़ो(&stats->io.max_active),
		   (u64) atomic64_पढ़ो(&stats->io.num_ios),
		   (u64) atomic64_पढ़ो(&stats->io.compl),
		   (u64) atomic64_पढ़ो(&stats->io.fail),
		   (u64) atomic64_पढ़ो(&stats->io.io_not_found),
		   (u64) atomic64_पढ़ो(&stats->io.alloc_fail),
		   (u64) atomic64_पढ़ो(&stats->io.req_null),
		   (u64) atomic64_पढ़ो(&stats->io.sc_null),
		   (u64) atomic64_पढ़ो(&stats->io.max_sgl),
		   (u64) atomic64_पढ़ो(&stats->io.max_io_sz),
		   (u64) atomic64_पढ़ो(&stats->io.max_qसमय),
		   (u64) atomic64_पढ़ो(&stats->io.max_cmpl_समय),
		   maxio_पंचांग,
		   jअगरfies_to_msecs(maxio_पंचांग));

	seq_माला_दो(sfp, "\nSGL Counters\n");

	क्रम (i = 0; i < SNIC_MAX_SG_DESC_CNT; i++) अणु
		seq_म_लिखो(sfp,
			   "%10lld ",
			   (u64) atomic64_पढ़ो(&stats->io.sgl_cnt[i]));

		अगर ((i + 1) % 8 == 0)
			seq_माला_दो(sfp, "\n");
	पूर्ण

	/* Dump Abort Stats */
	seq_म_लिखो(sfp,
		   "\n-------------------------------------------\n"
		   "\t\t Abort Statistics\n"
		   "---------------------------------------------\n");

	seq_म_लिखो(sfp,
		   "Aborts                      : %lld\n"
		   "Aborts Fail                 : %lld\n"
		   "Aborts Driver Timeout       : %lld\n"
		   "Abort FW Timeout            : %lld\n"
		   "Abort IO NOT Found          : %lld\n"
		   "Abort Queuing Failed        : %lld\n",
		   (u64) atomic64_पढ़ो(&stats->abts.num),
		   (u64) atomic64_पढ़ो(&stats->abts.fail),
		   (u64) atomic64_पढ़ो(&stats->abts.drv_पंचांगo),
		   (u64) atomic64_पढ़ो(&stats->abts.fw_पंचांगo),
		   (u64) atomic64_पढ़ो(&stats->abts.io_not_found),
		   (u64) atomic64_पढ़ो(&stats->abts.q_fail));

	/* Dump Reset Stats */
	seq_म_लिखो(sfp,
		   "\n-------------------------------------------\n"
		   "\t\t Reset Statistics\n"
		   "---------------------------------------------\n");

	seq_म_लिखो(sfp,
		   "HBA Resets                  : %lld\n"
		   "HBA Reset Cmpls             : %lld\n"
		   "HBA Reset Fail              : %lld\n",
		   (u64) atomic64_पढ़ो(&stats->reset.hba_resets),
		   (u64) atomic64_पढ़ो(&stats->reset.hba_reset_cmpl),
		   (u64) atomic64_पढ़ो(&stats->reset.hba_reset_fail));

	/* Dump Firmware Stats */
	seq_म_लिखो(sfp,
		   "\n-------------------------------------------\n"
		   "\t\t Firmware Statistics\n"
		   "---------------------------------------------\n");

	seq_म_लिखो(sfp,
		"Active FW Requests             : %lld\n"
		"Max FW Requests                : %lld\n"
		"FW Out Of Resource Errs        : %lld\n"
		"FW IO Errors                   : %lld\n"
		"FW SCSI Errors                 : %lld\n",
		(u64) atomic64_पढ़ो(&stats->fw.actv_reqs),
		(u64) atomic64_पढ़ो(&stats->fw.max_actv_reqs),
		(u64) atomic64_पढ़ो(&stats->fw.out_of_res),
		(u64) atomic64_पढ़ो(&stats->fw.io_errs),
		(u64) atomic64_पढ़ो(&stats->fw.scsi_errs));


	/* Dump Miscellenous Stats */
	seq_म_लिखो(sfp,
		   "\n---------------------------------------------\n"
		   "\t\t Other Statistics\n"
		   "\n---------------------------------------------\n");

	jअगरfies_to_बारpec64(stats->misc.last_isr_समय, &last_isr_पंचांगs);
	jअगरfies_to_बारpec64(stats->misc.last_ack_समय, &last_ack_पंचांगs);

	seq_म_लिखो(sfp,
		   "Last ISR Time               : %llu (%8llu.%09lu)\n"
		   "Last Ack Time               : %llu (%8llu.%09lu)\n"
		   "Ack ISRs                    : %llu\n"
		   "IO Cmpl ISRs                : %llu\n"
		   "Err Notify ISRs             : %llu\n"
		   "Max CQ Entries              : %lld\n"
		   "Data Count Mismatch         : %lld\n"
		   "IOs w/ Timeout Status       : %lld\n"
		   "IOs w/ Aborted Status       : %lld\n"
		   "IOs w/ SGL Invalid Stat     : %lld\n"
		   "WQ Desc Alloc Fail          : %lld\n"
		   "Queue Full                  : %lld\n"
		   "Queue Ramp Up               : %lld\n"
		   "Queue Ramp Down             : %lld\n"
		   "Queue Last Queue Depth      : %lld\n"
		   "Target Not Ready            : %lld\n",
		   (u64) stats->misc.last_isr_समय,
		   last_isr_पंचांगs.tv_sec, last_isr_पंचांगs.tv_nsec,
		   (u64)stats->misc.last_ack_समय,
		   last_ack_पंचांगs.tv_sec, last_ack_पंचांगs.tv_nsec,
		   (u64) atomic64_पढ़ो(&stats->misc.ack_isr_cnt),
		   (u64) atomic64_पढ़ो(&stats->misc.cmpl_isr_cnt),
		   (u64) atomic64_पढ़ो(&stats->misc.त्रुटि_संtअगरy_isr_cnt),
		   (u64) atomic64_पढ़ो(&stats->misc.max_cq_ents),
		   (u64) atomic64_पढ़ो(&stats->misc.data_cnt_mismat),
		   (u64) atomic64_पढ़ो(&stats->misc.io_पंचांगo),
		   (u64) atomic64_पढ़ो(&stats->misc.io_पातed),
		   (u64) atomic64_पढ़ो(&stats->misc.sgl_inval),
		   (u64) atomic64_पढ़ो(&stats->misc.wq_alloc_fail),
		   (u64) atomic64_पढ़ो(&stats->misc.qfull),
		   (u64) atomic64_पढ़ो(&stats->misc.qsz_rampup),
		   (u64) atomic64_पढ़ो(&stats->misc.qsz_rampकरोwn),
		   (u64) atomic64_पढ़ो(&stats->misc.last_qsz),
		   (u64) atomic64_पढ़ो(&stats->misc.tgt_not_rdy));

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(snic_stats);

अटल स्थिर काष्ठा file_operations snic_reset_stats_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = snic_reset_stats_खोलो,
	.पढ़ो = snic_reset_stats_पढ़ो,
	.ग_लिखो = snic_reset_stats_ग_लिखो,
	.release = snic_reset_stats_release,
पूर्ण;

/*
 * snic_stats_init - Initialize stats काष्ठा and create stats file
 * per snic
 *
 * Description:
 * When debugfs is cofigured this routine sets up the stats file per snic
 * It will create file stats and reset_stats under statistics/host# directory
 * to log per snic stats
 */
व्योम snic_stats_debugfs_init(काष्ठा snic *snic)
अणु
	अक्षर name[16];

	snम_लिखो(name, माप(name), "host%d", snic->shost->host_no);

	snic->stats_host = debugfs_create_dir(name, snic_glob->stats_root);

	snic->stats_file = debugfs_create_file("stats", S_IFREG|S_IRUGO,
					       snic->stats_host, snic,
					       &snic_stats_fops);

	snic->reset_stats_file = debugfs_create_file("reset_stats",
						     S_IFREG|S_IRUGO|S_IWUSR,
						     snic->stats_host, snic,
						     &snic_reset_stats_fops);
पूर्ण

/*
 * snic_stats_debugfs_हटाओ - Tear करोwn debugfs infraकाष्ठाure of stats
 *
 * Description:
 * When Debufs is configured this routine हटाओs debugfs file प्रणाली
 * elements that are specअगरic to to snic stats
 */
व्योम
snic_stats_debugfs_हटाओ(काष्ठा snic *snic)
अणु
	debugfs_हटाओ(snic->stats_file);
	snic->stats_file = शून्य;

	debugfs_हटाओ(snic->reset_stats_file);
	snic->reset_stats_file = शून्य;

	debugfs_हटाओ(snic->stats_host);
	snic->stats_host = शून्य;
पूर्ण

/* Trace Facility related API */
अटल व्योम *
snic_trc_seq_start(काष्ठा seq_file *sfp, loff_t *pos)
अणु
	वापस &snic_glob->trc;
पूर्ण

अटल व्योम *
snic_trc_seq_next(काष्ठा seq_file *sfp, व्योम *data, loff_t *pos)
अणु
	वापस शून्य;
पूर्ण

अटल व्योम
snic_trc_seq_stop(काष्ठा seq_file *sfp, व्योम *data)
अणु
पूर्ण

#घोषणा SNIC_TRC_PBLEN	256
अटल पूर्णांक
snic_trc_seq_show(काष्ठा seq_file *sfp, व्योम *data)
अणु
	अक्षर buf[SNIC_TRC_PBLEN];

	अगर (snic_get_trc_data(buf, SNIC_TRC_PBLEN) > 0)
		seq_म_लिखो(sfp, "%s\n", buf);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations snic_trc_sops = अणु
	.start	= snic_trc_seq_start,
	.next	= snic_trc_seq_next,
	.stop	= snic_trc_seq_stop,
	.show	= snic_trc_seq_show,
पूर्ण;

DEFINE_SEQ_ATTRIBUTE(snic_trc);

/*
 * snic_trc_debugfs_init : creates trace/tracing_enable files क्रम trace
 * under debugfs
 */
व्योम snic_trc_debugfs_init(व्योम)
अणु
	snic_glob->trc.trc_enable = debugfs_create_bool("tracing_enable",
							S_IFREG | S_IRUGO | S_IWUSR,
							snic_glob->trc_root,
							&snic_glob->trc.enable);

	snic_glob->trc.trc_file = debugfs_create_file("trace",
						      S_IFREG | S_IRUGO | S_IWUSR,
						      snic_glob->trc_root, शून्य,
						      &snic_trc_fops);
पूर्ण

/*
 * snic_trc_debugfs_term : cleans up the files created क्रम trace under debugfs
 */
व्योम
snic_trc_debugfs_term(व्योम)
अणु
	debugfs_हटाओ(snic_glob->trc.trc_file);
	snic_glob->trc.trc_file = शून्य;

	debugfs_हटाओ(snic_glob->trc.trc_enable);
	snic_glob->trc.trc_enable = शून्य;
पूर्ण
