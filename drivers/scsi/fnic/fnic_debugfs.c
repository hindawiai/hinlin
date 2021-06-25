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
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/debugfs.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश "fnic.h"

अटल काष्ठा dentry *fnic_trace_debugfs_root;
अटल काष्ठा dentry *fnic_trace_debugfs_file;
अटल काष्ठा dentry *fnic_trace_enable;
अटल काष्ठा dentry *fnic_stats_debugfs_root;

अटल काष्ठा dentry *fnic_fc_trace_debugfs_file;
अटल काष्ठा dentry *fnic_fc_rdata_trace_debugfs_file;
अटल काष्ठा dentry *fnic_fc_trace_enable;
अटल काष्ठा dentry *fnic_fc_trace_clear;

काष्ठा fc_trace_flag_type अणु
	u8 fc_row_file;
	u8 fc_normal_file;
	u8 fnic_trace;
	u8 fc_trace;
	u8 fc_clear;
पूर्ण;

अटल काष्ठा fc_trace_flag_type *fc_trc_flag;

/*
 * fnic_debugfs_init - Initialize debugfs क्रम fnic debug logging
 *
 * Description:
 * When Debugfs is configured this routine sets up the fnic debugfs
 * file प्रणाली. If not alपढ़ोy created, this routine will create the
 * fnic directory and statistics directory क्रम trace buffer and
 * stats logging.
 */
पूर्णांक fnic_debugfs_init(व्योम)
अणु
	fnic_trace_debugfs_root = debugfs_create_dir("fnic", शून्य);

	fnic_stats_debugfs_root = debugfs_create_dir("statistics",
						fnic_trace_debugfs_root);

	/* Allocate memory to काष्ठाure */
	fc_trc_flag = vदो_स्मृति(माप(काष्ठा fc_trace_flag_type));

	अगर (fc_trc_flag) अणु
		fc_trc_flag->fc_row_file = 0;
		fc_trc_flag->fc_normal_file = 1;
		fc_trc_flag->fnic_trace = 2;
		fc_trc_flag->fc_trace = 3;
		fc_trc_flag->fc_clear = 4;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * fnic_debugfs_terminate - Tear करोwn debugfs infraकाष्ठाure
 *
 * Description:
 * When Debugfs is configured this routine हटाओs debugfs file प्रणाली
 * elements that are specअगरic to fnic.
 */
व्योम fnic_debugfs_terminate(व्योम)
अणु
	debugfs_हटाओ(fnic_stats_debugfs_root);
	fnic_stats_debugfs_root = शून्य;

	debugfs_हटाओ(fnic_trace_debugfs_root);
	fnic_trace_debugfs_root = शून्य;

	अगर (fc_trc_flag)
		vमुक्त(fc_trc_flag);
पूर्ण

/*
 * fnic_trace_ctrl_पढ़ो -
 *          Read  trace_enable ,fc_trace_enable
 *              or fc_trace_clear debugfs file
 * @filp: The file poपूर्णांकer to पढ़ो from.
 * @ubuf: The buffer to copy the data to.
 * @cnt: The number of bytes to पढ़ो.
 * @ppos: The position in the file to start पढ़ोing from.
 *
 * Description:
 * This routine पढ़ोs value of variable fnic_tracing_enabled or
 * fnic_fc_tracing_enabled or fnic_fc_trace_cleared
 * and stores पूर्णांकo local @buf.
 * It will start पढ़ोing file at @ppos and
 * copy up to @cnt of data to @ubuf from @buf.
 *
 * Returns:
 * This function वापसs the amount of data that was पढ़ो.
 */
अटल sमाप_प्रकार fnic_trace_ctrl_पढ़ो(काष्ठा file *filp,
				  अक्षर __user *ubuf,
				  माप_प्रकार cnt, loff_t *ppos)
अणु
	अक्षर buf[64];
	पूर्णांक len;
	u8 *trace_type;
	len = 0;
	trace_type = (u8 *)filp->निजी_data;
	अगर (*trace_type == fc_trc_flag->fnic_trace)
		len = प्र_लिखो(buf, "%d\n", fnic_tracing_enabled);
	अन्यथा अगर (*trace_type == fc_trc_flag->fc_trace)
		len = प्र_लिखो(buf, "%d\n", fnic_fc_tracing_enabled);
	अन्यथा अगर (*trace_type == fc_trc_flag->fc_clear)
		len = प्र_लिखो(buf, "%d\n", fnic_fc_trace_cleared);
	अन्यथा
		pr_err("fnic: Cannot read to any debugfs file\n");

	वापस simple_पढ़ो_from_buffer(ubuf, cnt, ppos, buf, len);
पूर्ण

/*
 * fnic_trace_ctrl_ग_लिखो -
 * Write to trace_enable, fc_trace_enable or
 *         fc_trace_clear debugfs file
 * @filp: The file poपूर्णांकer to ग_लिखो from.
 * @ubuf: The buffer to copy the data from.
 * @cnt: The number of bytes to ग_लिखो.
 * @ppos: The position in the file to start writing to.
 *
 * Description:
 * This routine ग_लिखोs data from user buffer @ubuf to buffer @buf and
 * sets fc_trace_enable ,tracing_enable or fnic_fc_trace_cleared
 * value as per user input.
 *
 * Returns:
 * This function वापसs the amount of data that was written.
 */
अटल sमाप_प्रकार fnic_trace_ctrl_ग_लिखो(काष्ठा file *filp,
				  स्थिर अक्षर __user *ubuf,
				  माप_प्रकार cnt, loff_t *ppos)
अणु
	अक्षर buf[64];
	अचिन्हित दीर्घ val;
	पूर्णांक ret;
	u8 *trace_type;
	trace_type = (u8 *)filp->निजी_data;

	अगर (cnt >= माप(buf))
		वापस -EINVAL;

	अगर (copy_from_user(&buf, ubuf, cnt))
		वापस -EFAULT;

	buf[cnt] = 0;

	ret = kम_से_अदीर्घ(buf, 10, &val);
	अगर (ret < 0)
		वापस ret;

	अगर (*trace_type == fc_trc_flag->fnic_trace)
		fnic_tracing_enabled = val;
	अन्यथा अगर (*trace_type == fc_trc_flag->fc_trace)
		fnic_fc_tracing_enabled = val;
	अन्यथा अगर (*trace_type == fc_trc_flag->fc_clear)
		fnic_fc_trace_cleared = val;
	अन्यथा
		pr_err("fnic: cannot write to any debugfs file\n");

	(*ppos)++;

	वापस cnt;
पूर्ण

अटल स्थिर काष्ठा file_operations fnic_trace_ctrl_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = simple_खोलो,
	.पढ़ो = fnic_trace_ctrl_पढ़ो,
	.ग_लिखो = fnic_trace_ctrl_ग_लिखो,
पूर्ण;

/*
 * fnic_trace_debugfs_खोलो - Open the fnic trace log
 * @inode: The inode poपूर्णांकer
 * @file: The file poपूर्णांकer to attach the log output
 *
 * Description:
 * This routine is the entry poपूर्णांक क्रम the debugfs खोलो file operation.
 * It allocates the necessary buffer क्रम the log, fills the buffer from
 * the in-memory log and then वापसs a poपूर्णांकer to that log in
 * the निजी_data field in @file.
 *
 * Returns:
 * This function वापसs zero अगर successful. On error it will वापस
 * a negative error value.
 */
अटल पूर्णांक fnic_trace_debugfs_खोलो(काष्ठा inode *inode,
				  काष्ठा file *file)
अणु
	fnic_dbgfs_t *fnic_dbg_prt;
	u8 *rdata_ptr;
	rdata_ptr = (u8 *)inode->i_निजी;
	fnic_dbg_prt = kzalloc(माप(fnic_dbgfs_t), GFP_KERNEL);
	अगर (!fnic_dbg_prt)
		वापस -ENOMEM;

	अगर (*rdata_ptr == fc_trc_flag->fnic_trace) अणु
		fnic_dbg_prt->buffer = vदो_स्मृति(array3_size(3, trace_max_pages,
							   PAGE_SIZE));
		अगर (!fnic_dbg_prt->buffer) अणु
			kमुक्त(fnic_dbg_prt);
			वापस -ENOMEM;
		पूर्ण
		स_रखो((व्योम *)fnic_dbg_prt->buffer, 0,
		3 * (trace_max_pages * PAGE_SIZE));
		fnic_dbg_prt->buffer_len = fnic_get_trace_data(fnic_dbg_prt);
	पूर्ण अन्यथा अणु
		fnic_dbg_prt->buffer =
			vदो_स्मृति(array3_size(3, fnic_fc_trace_max_pages,
					    PAGE_SIZE));
		अगर (!fnic_dbg_prt->buffer) अणु
			kमुक्त(fnic_dbg_prt);
			वापस -ENOMEM;
		पूर्ण
		स_रखो((व्योम *)fnic_dbg_prt->buffer, 0,
			3 * (fnic_fc_trace_max_pages * PAGE_SIZE));
		fnic_dbg_prt->buffer_len =
			fnic_fc_trace_get_data(fnic_dbg_prt, *rdata_ptr);
	पूर्ण
	file->निजी_data = fnic_dbg_prt;

	वापस 0;
पूर्ण

/*
 * fnic_trace_debugfs_lseek - Seek through a debugfs file
 * @file: The file poपूर्णांकer to seek through.
 * @offset: The offset to seek to or the amount to seek by.
 * @howto: Indicates how to seek.
 *
 * Description:
 * This routine is the entry poपूर्णांक क्रम the debugfs lseek file operation.
 * The @howto parameter indicates whether @offset is the offset to directly
 * seek to, or अगर it is a value to seek क्रमward or reverse by. This function
 * figures out what the new offset of the debugfs file will be and assigns
 * that value to the f_pos field of @file.
 *
 * Returns:
 * This function वापसs the new offset अगर successful and वापसs a negative
 * error अगर unable to process the seek.
 */
अटल loff_t fnic_trace_debugfs_lseek(काष्ठा file *file,
					loff_t offset,
					पूर्णांक howto)
अणु
	fnic_dbgfs_t *fnic_dbg_prt = file->निजी_data;
	वापस fixed_size_llseek(file, offset, howto,
				fnic_dbg_prt->buffer_len);
पूर्ण

/*
 * fnic_trace_debugfs_पढ़ो - Read a debugfs file
 * @file: The file poपूर्णांकer to पढ़ो from.
 * @ubuf: The buffer to copy the data to.
 * @nbytes: The number of bytes to पढ़ो.
 * @pos: The position in the file to start पढ़ोing from.
 *
 * Description:
 * This routine पढ़ोs data from the buffer indicated in the निजी_data
 * field of @file. It will start पढ़ोing at @pos and copy up to @nbytes of
 * data to @ubuf.
 *
 * Returns:
 * This function वापसs the amount of data that was पढ़ो (this could be
 * less than @nbytes अगर the end of the file was reached).
 */
अटल sमाप_प्रकार fnic_trace_debugfs_पढ़ो(काष्ठा file *file,
					अक्षर __user *ubuf,
					माप_प्रकार nbytes,
					loff_t *pos)
अणु
	fnic_dbgfs_t *fnic_dbg_prt = file->निजी_data;
	पूर्णांक rc = 0;
	rc = simple_पढ़ो_from_buffer(ubuf, nbytes, pos,
				  fnic_dbg_prt->buffer,
				  fnic_dbg_prt->buffer_len);
	वापस rc;
पूर्ण

/*
 * fnic_trace_debugfs_release - Release the buffer used to store
 * debugfs file data
 * @inode: The inode poपूर्णांकer
 * @file: The file poपूर्णांकer that contains the buffer to release
 *
 * Description:
 * This routine मुक्तs the buffer that was allocated when the debugfs
 * file was खोलोed.
 *
 * Returns:
 * This function वापसs zero.
 */
अटल पूर्णांक fnic_trace_debugfs_release(काष्ठा inode *inode,
					  काष्ठा file *file)
अणु
	fnic_dbgfs_t *fnic_dbg_prt = file->निजी_data;

	vमुक्त(fnic_dbg_prt->buffer);
	kमुक्त(fnic_dbg_prt);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations fnic_trace_debugfs_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = fnic_trace_debugfs_खोलो,
	.llseek = fnic_trace_debugfs_lseek,
	.पढ़ो = fnic_trace_debugfs_पढ़ो,
	.release = fnic_trace_debugfs_release,
पूर्ण;

/*
 * fnic_trace_debugfs_init - Initialize debugfs क्रम fnic trace logging
 *
 * Description:
 * When Debugfs is configured this routine sets up the fnic debugfs
 * file प्रणाली. If not alपढ़ोy created, this routine will create the
 * create file trace to log fnic trace buffer output पूर्णांकo debugfs and
 * it will also create file trace_enable to control enable/disable of
 * trace logging पूर्णांकo trace buffer.
 */
व्योम fnic_trace_debugfs_init(व्योम)
अणु
	fnic_trace_enable = debugfs_create_file("tracing_enable",
					S_IFREG|S_IRUGO|S_IWUSR,
					fnic_trace_debugfs_root,
					&(fc_trc_flag->fnic_trace),
					&fnic_trace_ctrl_fops);

	fnic_trace_debugfs_file = debugfs_create_file("trace",
					S_IFREG|S_IRUGO|S_IWUSR,
					fnic_trace_debugfs_root,
					&(fc_trc_flag->fnic_trace),
					&fnic_trace_debugfs_fops);
पूर्ण

/*
 * fnic_trace_debugfs_terminate - Tear करोwn debugfs infraकाष्ठाure
 *
 * Description:
 * When Debugfs is configured this routine हटाओs debugfs file प्रणाली
 * elements that are specअगरic to fnic trace logging.
 */
व्योम fnic_trace_debugfs_terminate(व्योम)
अणु
	debugfs_हटाओ(fnic_trace_debugfs_file);
	fnic_trace_debugfs_file = शून्य;

	debugfs_हटाओ(fnic_trace_enable);
	fnic_trace_enable = शून्य;
पूर्ण

/*
 * fnic_fc_trace_debugfs_init -
 * Initialize debugfs क्रम fnic control frame trace logging
 *
 * Description:
 * When Debugfs is configured this routine sets up the fnic_fc debugfs
 * file प्रणाली. If not alपढ़ोy created, this routine will create the
 * create file trace to log fnic fc trace buffer output पूर्णांकo debugfs and
 * it will also create file fc_trace_enable to control enable/disable of
 * trace logging पूर्णांकo trace buffer.
 */

व्योम fnic_fc_trace_debugfs_init(व्योम)
अणु
	fnic_fc_trace_enable = debugfs_create_file("fc_trace_enable",
					S_IFREG|S_IRUGO|S_IWUSR,
					fnic_trace_debugfs_root,
					&(fc_trc_flag->fc_trace),
					&fnic_trace_ctrl_fops);

	fnic_fc_trace_clear = debugfs_create_file("fc_trace_clear",
					S_IFREG|S_IRUGO|S_IWUSR,
					fnic_trace_debugfs_root,
					&(fc_trc_flag->fc_clear),
					&fnic_trace_ctrl_fops);

	fnic_fc_rdata_trace_debugfs_file =
		debugfs_create_file("fc_trace_rdata",
				    S_IFREG|S_IRUGO|S_IWUSR,
				    fnic_trace_debugfs_root,
				    &(fc_trc_flag->fc_normal_file),
				    &fnic_trace_debugfs_fops);

	fnic_fc_trace_debugfs_file =
		debugfs_create_file("fc_trace",
				    S_IFREG|S_IRUGO|S_IWUSR,
				    fnic_trace_debugfs_root,
				    &(fc_trc_flag->fc_row_file),
				    &fnic_trace_debugfs_fops);
पूर्ण

/*
 * fnic_fc_trace_debugfs_terminate - Tear करोwn debugfs infraकाष्ठाure
 *
 * Description:
 * When Debugfs is configured this routine हटाओs debugfs file प्रणाली
 * elements that are specअगरic to fnic_fc trace logging.
 */

व्योम fnic_fc_trace_debugfs_terminate(व्योम)
अणु
	debugfs_हटाओ(fnic_fc_trace_debugfs_file);
	fnic_fc_trace_debugfs_file = शून्य;

	debugfs_हटाओ(fnic_fc_rdata_trace_debugfs_file);
	fnic_fc_rdata_trace_debugfs_file = शून्य;

	debugfs_हटाओ(fnic_fc_trace_enable);
	fnic_fc_trace_enable = शून्य;

	debugfs_हटाओ(fnic_fc_trace_clear);
	fnic_fc_trace_clear = शून्य;
पूर्ण

/*
 * fnic_reset_stats_खोलो - Open the reset_stats file
 * @inode: The inode poपूर्णांकer.
 * @file: The file poपूर्णांकer to attach the stats reset flag.
 *
 * Description:
 * This routine खोलोs a debugsfs file reset_stats and stores i_निजी data
 * to debug काष्ठाure to retrieve later क्रम जबतक perक्रमming other
 * file oprations.
 *
 * Returns:
 * This function वापसs zero अगर successful.
 */
अटल पूर्णांक fnic_reset_stats_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा stats_debug_info *debug;

	debug = kzalloc(माप(काष्ठा stats_debug_info), GFP_KERNEL);
	अगर (!debug)
		वापस -ENOMEM;

	debug->i_निजी = inode->i_निजी;

	file->निजी_data = debug;

	वापस 0;
पूर्ण

/*
 * fnic_reset_stats_पढ़ो - Read a reset_stats debugfs file
 * @filp: The file poपूर्णांकer to पढ़ो from.
 * @ubuf: The buffer to copy the data to.
 * @cnt: The number of bytes to पढ़ो.
 * @ppos: The position in the file to start पढ़ोing from.
 *
 * Description:
 * This routine पढ़ोs value of variable reset_stats
 * and stores पूर्णांकo local @buf. It will start पढ़ोing file at @ppos and
 * copy up to @cnt of data to @ubuf from @buf.
 *
 * Returns:
 * This function वापसs the amount of data that was पढ़ो.
 */
अटल sमाप_प्रकार fnic_reset_stats_पढ़ो(काष्ठा file *file,
					अक्षर __user *ubuf,
					माप_प्रकार cnt, loff_t *ppos)
अणु
	काष्ठा stats_debug_info *debug = file->निजी_data;
	काष्ठा fnic *fnic = (काष्ठा fnic *)debug->i_निजी;
	अक्षर buf[64];
	पूर्णांक len;

	len = प्र_लिखो(buf, "%u\n", fnic->reset_stats);

	वापस simple_पढ़ो_from_buffer(ubuf, cnt, ppos, buf, len);
पूर्ण

/*
 * fnic_reset_stats_ग_लिखो - Write to reset_stats debugfs file
 * @filp: The file poपूर्णांकer to ग_लिखो from.
 * @ubuf: The buffer to copy the data from.
 * @cnt: The number of bytes to ग_लिखो.
 * @ppos: The position in the file to start writing to.
 *
 * Description:
 * This routine ग_लिखोs data from user buffer @ubuf to buffer @buf and
 * resets cumulative stats of fnic.
 *
 * Returns:
 * This function वापसs the amount of data that was written.
 */
अटल sमाप_प्रकार fnic_reset_stats_ग_लिखो(काष्ठा file *file,
					स्थिर अक्षर __user *ubuf,
					माप_प्रकार cnt, loff_t *ppos)
अणु
	काष्ठा stats_debug_info *debug = file->निजी_data;
	काष्ठा fnic *fnic = (काष्ठा fnic *)debug->i_निजी;
	काष्ठा fnic_stats *stats = &fnic->fnic_stats;
	u64 *io_stats_p = (u64 *)&stats->io_stats;
	u64 *fw_stats_p = (u64 *)&stats->fw_stats;
	अक्षर buf[64];
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	अगर (cnt >= माप(buf))
		वापस -EINVAL;

	अगर (copy_from_user(&buf, ubuf, cnt))
		वापस -EFAULT;

	buf[cnt] = 0;

	ret = kम_से_अदीर्घ(buf, 10, &val);
	अगर (ret < 0)
		वापस ret;

	fnic->reset_stats = val;

	अगर (fnic->reset_stats) अणु
		/* Skip variable is used to aव्योम descrepancies to Num IOs
		 * and IO Completions stats. Skip incrementing No IO Compls
		 * क्रम pending active IOs after reset stats
		 */
		atomic64_set(&fnic->io_cmpl_skip,
			atomic64_पढ़ो(&stats->io_stats.active_ios));
		स_रखो(&stats->abts_stats, 0, माप(काष्ठा पात_stats));
		स_रखो(&stats->term_stats, 0,
			माप(काष्ठा terminate_stats));
		स_रखो(&stats->reset_stats, 0, माप(काष्ठा reset_stats));
		स_रखो(&stats->misc_stats, 0, माप(काष्ठा misc_stats));
		स_रखो(&stats->vlan_stats, 0, माप(काष्ठा vlan_stats));
		स_रखो(io_stats_p+1, 0,
			माप(काष्ठा io_path_stats) - माप(u64));
		स_रखो(fw_stats_p+1, 0,
			माप(काष्ठा fw_stats) - माप(u64));
		kसमय_get_real_ts64(&stats->stats_बारtamps.last_reset_समय);
	पूर्ण

	(*ppos)++;
	वापस cnt;
पूर्ण

/*
 * fnic_reset_stats_release - Release the buffer used to store
 * debugfs file data
 * @inode: The inode poपूर्णांकer
 * @file: The file poपूर्णांकer that contains the buffer to release
 *
 * Description:
 * This routine मुक्तs the buffer that was allocated when the debugfs
 * file was खोलोed.
 *
 * Returns:
 * This function वापसs zero.
 */
अटल पूर्णांक fnic_reset_stats_release(काष्ठा inode *inode,
					काष्ठा file *file)
अणु
	काष्ठा stats_debug_info *debug = file->निजी_data;
	kमुक्त(debug);
	वापस 0;
पूर्ण

/*
 * fnic_stats_debugfs_खोलो - Open the stats file क्रम specअगरic host
 * and get fnic stats.
 * @inode: The inode poपूर्णांकer.
 * @file: The file poपूर्णांकer to attach the specअगरic host statistics.
 *
 * Description:
 * This routine खोलोs a debugsfs file stats of specअगरic host and prपूर्णांक
 * fnic stats.
 *
 * Returns:
 * This function वापसs zero अगर successful.
 */
अटल पूर्णांक fnic_stats_debugfs_खोलो(काष्ठा inode *inode,
					काष्ठा file *file)
अणु
	काष्ठा fnic *fnic = inode->i_निजी;
	काष्ठा fnic_stats *fnic_stats = &fnic->fnic_stats;
	काष्ठा stats_debug_info *debug;
	पूर्णांक buf_size = 2 * PAGE_SIZE;

	debug = kzalloc(माप(काष्ठा stats_debug_info), GFP_KERNEL);
	अगर (!debug)
		वापस -ENOMEM;

	debug->debug_buffer = vदो_स्मृति(buf_size);
	अगर (!debug->debug_buffer) अणु
		kमुक्त(debug);
		वापस -ENOMEM;
	पूर्ण

	debug->buf_size = buf_size;
	स_रखो((व्योम *)debug->debug_buffer, 0, buf_size);
	debug->buffer_len = fnic_get_stats_data(debug, fnic_stats);

	file->निजी_data = debug;

	वापस 0;
पूर्ण

/*
 * fnic_stats_debugfs_पढ़ो - Read a debugfs file
 * @file: The file poपूर्णांकer to पढ़ो from.
 * @ubuf: The buffer to copy the data to.
 * @nbytes: The number of bytes to पढ़ो.
 * @pos: The position in the file to start पढ़ोing from.
 *
 * Description:
 * This routine पढ़ोs data from the buffer indicated in the निजी_data
 * field of @file. It will start पढ़ोing at @pos and copy up to @nbytes of
 * data to @ubuf.
 *
 * Returns:
 * This function वापसs the amount of data that was पढ़ो (this could be
 * less than @nbytes अगर the end of the file was reached).
 */
अटल sमाप_प्रकार fnic_stats_debugfs_पढ़ो(काष्ठा file *file,
					अक्षर __user *ubuf,
					माप_प्रकार nbytes,
					loff_t *pos)
अणु
	काष्ठा stats_debug_info *debug = file->निजी_data;
	पूर्णांक rc = 0;
	rc = simple_पढ़ो_from_buffer(ubuf, nbytes, pos,
					debug->debug_buffer,
					debug->buffer_len);
	वापस rc;
पूर्ण

/*
 * fnic_stats_stats_release - Release the buffer used to store
 * debugfs file data
 * @inode: The inode poपूर्णांकer
 * @file: The file poपूर्णांकer that contains the buffer to release
 *
 * Description:
 * This routine मुक्तs the buffer that was allocated when the debugfs
 * file was खोलोed.
 *
 * Returns:
 * This function वापसs zero.
 */
अटल पूर्णांक fnic_stats_debugfs_release(काष्ठा inode *inode,
					काष्ठा file *file)
अणु
	काष्ठा stats_debug_info *debug = file->निजी_data;
	vमुक्त(debug->debug_buffer);
	kमुक्त(debug);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations fnic_stats_debugfs_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = fnic_stats_debugfs_खोलो,
	.पढ़ो = fnic_stats_debugfs_पढ़ो,
	.release = fnic_stats_debugfs_release,
पूर्ण;

अटल स्थिर काष्ठा file_operations fnic_reset_debugfs_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = fnic_reset_stats_खोलो,
	.पढ़ो = fnic_reset_stats_पढ़ो,
	.ग_लिखो = fnic_reset_stats_ग_लिखो,
	.release = fnic_reset_stats_release,
पूर्ण;

/*
 * fnic_stats_init - Initialize stats काष्ठा and create stats file per fnic
 *
 * Description:
 * When Debugfs is configured this routine sets up the stats file per fnic
 * It will create file stats and reset_stats under statistics/host# directory
 * to log per fnic stats.
 */
व्योम fnic_stats_debugfs_init(काष्ठा fnic *fnic)
अणु
	अक्षर name[16];

	snम_लिखो(name, माप(name), "host%d", fnic->lport->host->host_no);

	fnic->fnic_stats_debugfs_host = debugfs_create_dir(name,
						fnic_stats_debugfs_root);

	fnic->fnic_stats_debugfs_file = debugfs_create_file("stats",
						S_IFREG|S_IRUGO|S_IWUSR,
						fnic->fnic_stats_debugfs_host,
						fnic,
						&fnic_stats_debugfs_fops);

	fnic->fnic_reset_debugfs_file = debugfs_create_file("reset_stats",
						S_IFREG|S_IRUGO|S_IWUSR,
						fnic->fnic_stats_debugfs_host,
						fnic,
						&fnic_reset_debugfs_fops);
पूर्ण

/*
 * fnic_stats_debugfs_हटाओ - Tear करोwn debugfs infraकाष्ठाure of stats
 *
 * Description:
 * When Debugfs is configured this routine हटाओs debugfs file प्रणाली
 * elements that are specअगरic to fnic stats.
 */
व्योम fnic_stats_debugfs_हटाओ(काष्ठा fnic *fnic)
अणु
	अगर (!fnic)
		वापस;

	debugfs_हटाओ(fnic->fnic_stats_debugfs_file);
	fnic->fnic_stats_debugfs_file = शून्य;

	debugfs_हटाओ(fnic->fnic_reset_debugfs_file);
	fnic->fnic_reset_debugfs_file = शून्य;

	debugfs_हटाओ(fnic->fnic_stats_debugfs_host);
	fnic->fnic_stats_debugfs_host = शून्य;
पूर्ण
