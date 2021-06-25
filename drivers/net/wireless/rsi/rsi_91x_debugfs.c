<शैली गुरु>
/*
 * Copyright (c) 2014 Redpine Signals Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#समावेश "rsi_debugfs.h"
#समावेश "rsi_sdio.h"

/**
 * rsi_sdio_stats_पढ़ो() - This function वापसs the sdio status of the driver.
 * @seq: Poपूर्णांकer to the sequence file काष्ठाure.
 * @data: Poपूर्णांकer to the data.
 *
 * Return: 0 on success, -1 on failure.
 */
अटल पूर्णांक rsi_sdio_stats_पढ़ो(काष्ठा seq_file *seq, व्योम *data)
अणु
	काष्ठा rsi_common *common = seq->निजी;
	काष्ठा rsi_hw *adapter = common->priv;
	काष्ठा rsi_91x_sdiodev *dev =
		(काष्ठा rsi_91x_sdiodev *)adapter->rsi_dev;

	seq_म_लिखो(seq, "total_sdio_interrupts: %d\n",
		   dev->rx_info.sdio_पूर्णांक_counter);
	seq_म_लिखो(seq, "sdio_msdu_pending_intr_count: %d\n",
		   dev->rx_info.total_sdio_msdu_pending_पूर्णांकr);
	seq_म_लिखो(seq, "sdio_buff_full_count : %d\n",
		   dev->rx_info.buf_full_counter);
	seq_म_लिखो(seq, "sdio_buf_semi_full_count %d\n",
		   dev->rx_info.buf_semi_full_counter);
	seq_म_लिखो(seq, "sdio_unknown_intr_count: %d\n",
		   dev->rx_info.total_sdio_unknown_पूर्णांकr);
	/* RX Path Stats */
	seq_म_लिखो(seq, "BUFFER FULL STATUS  : %d\n",
		   dev->rx_info.buffer_full);
	seq_म_लिखो(seq, "SEMI BUFFER FULL STATUS  : %d\n",
		   dev->rx_info.semi_buffer_full);
	seq_म_लिखो(seq, "MGMT BUFFER FULL STATUS  : %d\n",
		   dev->rx_info.mgmt_buffer_full);
	seq_म_लिखो(seq, "BUFFER FULL COUNTER  : %d\n",
		   dev->rx_info.buf_full_counter);
	seq_म_लिखो(seq, "BUFFER SEMI FULL COUNTER  : %d\n",
		   dev->rx_info.buf_semi_full_counter);
	seq_म_लिखो(seq, "MGMT BUFFER FULL COUNTER  : %d\n",
		   dev->rx_info.mgmt_buf_full_counter);

	वापस 0;
पूर्ण

/**
 * rsi_sdio_stats_खोलो() - This function calls single खोलो function of seq_file
 *			   to खोलो file and पढ़ो contents from it.
 * @inode: Poपूर्णांकer to the inode काष्ठाure.
 * @file: Poपूर्णांकer to the file काष्ठाure.
 *
 * Return: Poपूर्णांकer to the खोलोed file status: 0 on success, ENOMEM on failure.
 */
अटल पूर्णांक rsi_sdio_stats_खोलो(काष्ठा inode *inode,
			       काष्ठा file *file)
अणु
	वापस single_खोलो(file, rsi_sdio_stats_पढ़ो, inode->i_निजी);
पूर्ण

/**
 * rsi_version_पढ़ो() - This function gives driver and firmware version number.
 * @seq: Poपूर्णांकer to the sequence file काष्ठाure.
 * @data: Poपूर्णांकer to the data.
 *
 * Return: 0 on success, -1 on failure.
 */
अटल पूर्णांक rsi_version_पढ़ो(काष्ठा seq_file *seq, व्योम *data)
अणु
	काष्ठा rsi_common *common = seq->निजी;

	seq_म_लिखो(seq, "LMAC   : %d.%d.%d.%d\n",
		   common->lmac_ver.major,
		   common->lmac_ver.minor,
		   common->lmac_ver.release_num,
		   common->lmac_ver.patch_num);

	वापस 0;
पूर्ण

/**
 * rsi_version_खोलो() - This function calls single खोलो function of seq_file to
 *			खोलो file and पढ़ो contents from it.
 * @inode: Poपूर्णांकer to the inode काष्ठाure.
 * @file: Poपूर्णांकer to the file काष्ठाure.
 *
 * Return: Poपूर्णांकer to the खोलोed file status: 0 on success, ENOMEM on failure.
 */
अटल पूर्णांक rsi_version_खोलो(काष्ठा inode *inode,
				 काष्ठा file *file)
अणु
	वापस single_खोलो(file, rsi_version_पढ़ो, inode->i_निजी);
पूर्ण

/**
 * rsi_stats_पढ़ो() - This function वापस the status of the driver.
 * @seq: Poपूर्णांकer to the sequence file काष्ठाure.
 * @data: Poपूर्णांकer to the data.
 *
 * Return: 0 on success, -1 on failure.
 */
अटल पूर्णांक rsi_stats_पढ़ो(काष्ठा seq_file *seq, व्योम *data)
अणु
	काष्ठा rsi_common *common = seq->निजी;

	अचिन्हित अक्षर fsm_state[][32] = अणु
		"FSM_FW_NOT_LOADED",
		"FSM_CARD_NOT_READY",
		"FSM_COMMON_DEV_PARAMS_SENT",
		"FSM_BOOT_PARAMS_SENT",
		"FSM_EEPROM_READ_MAC_ADDR",
		"FSM_EEPROM_READ_RF_TYPE",
		"FSM_RESET_MAC_SENT",
		"FSM_RADIO_CAPS_SENT",
		"FSM_BB_RF_PROG_SENT",
		"FSM_MAC_INIT_DONE"
	पूर्ण;
	seq_माला_दो(seq, "==> RSI STA DRIVER STATUS <==\n");
	seq_माला_दो(seq, "DRIVER_FSM_STATE: ");

	BUILD_BUG_ON(ARRAY_SIZE(fsm_state) != NUM_FSM_STATES);

	अगर (common->fsm_state <= FSM_MAC_INIT_DONE)
		seq_म_लिखो(seq, "%s", fsm_state[common->fsm_state]);

	seq_म_लिखो(seq, "(%d)\n\n", common->fsm_state);

	/* Mgmt TX Path Stats */
	seq_म_लिखो(seq, "total_mgmt_pkt_send : %d\n",
		   common->tx_stats.total_tx_pkt_send[MGMT_SOFT_Q]);
	seq_म_लिखो(seq, "total_mgmt_pkt_queued : %d\n",
		   skb_queue_len(&common->tx_queue[MGMT_SOFT_Q]));
	seq_म_लिखो(seq, "total_mgmt_pkt_freed  : %d\n",
		   common->tx_stats.total_tx_pkt_मुक्तd[MGMT_SOFT_Q]);

	/* Data TX Path Stats */
	seq_म_लिखो(seq, "total_data_vo_pkt_send: %8d\t",
		   common->tx_stats.total_tx_pkt_send[VO_Q]);
	seq_म_लिखो(seq, "total_data_vo_pkt_queued:  %8d\t",
		   skb_queue_len(&common->tx_queue[VO_Q]));
	seq_म_लिखो(seq, "total_vo_pkt_freed: %8d\n",
		   common->tx_stats.total_tx_pkt_मुक्तd[VO_Q]);
	seq_म_लिखो(seq, "total_data_vi_pkt_send: %8d\t",
		   common->tx_stats.total_tx_pkt_send[VI_Q]);
	seq_म_लिखो(seq, "total_data_vi_pkt_queued:  %8d\t",
		   skb_queue_len(&common->tx_queue[VI_Q]));
	seq_म_लिखो(seq, "total_vi_pkt_freed: %8d\n",
		   common->tx_stats.total_tx_pkt_मुक्तd[VI_Q]);
	seq_म_लिखो(seq,  "total_data_be_pkt_send: %8d\t",
		   common->tx_stats.total_tx_pkt_send[BE_Q]);
	seq_म_लिखो(seq, "total_data_be_pkt_queued:  %8d\t",
		   skb_queue_len(&common->tx_queue[BE_Q]));
	seq_म_लिखो(seq, "total_be_pkt_freed: %8d\n",
		   common->tx_stats.total_tx_pkt_मुक्तd[BE_Q]);
	seq_म_लिखो(seq, "total_data_bk_pkt_send: %8d\t",
		   common->tx_stats.total_tx_pkt_send[BK_Q]);
	seq_म_लिखो(seq, "total_data_bk_pkt_queued:  %8d\t",
		   skb_queue_len(&common->tx_queue[BK_Q]));
	seq_म_लिखो(seq, "total_bk_pkt_freed: %8d\n",
		   common->tx_stats.total_tx_pkt_मुक्तd[BK_Q]);

	seq_माला_दो(seq, "\n");
	वापस 0;
पूर्ण

/**
 * rsi_stats_खोलो() - This function calls single खोलो function of seq_file to
 *		      खोलो file and पढ़ो contents from it.
 * @inode: Poपूर्णांकer to the inode काष्ठाure.
 * @file: Poपूर्णांकer to the file काष्ठाure.
 *
 * Return: Poपूर्णांकer to the खोलोed file status: 0 on success, ENOMEM on failure.
 */
अटल पूर्णांक rsi_stats_खोलो(काष्ठा inode *inode,
			  काष्ठा file *file)
अणु
	वापस single_खोलो(file, rsi_stats_पढ़ो, inode->i_निजी);
पूर्ण

/**
 * rsi_debug_zone_पढ़ो() - This function display the currently enabled debug zones.
 * @seq: Poपूर्णांकer to the sequence file काष्ठाure.
 * @data: Poपूर्णांकer to the data.
 *
 * Return: 0 on success, -1 on failure.
 */
अटल पूर्णांक rsi_debug_zone_पढ़ो(काष्ठा seq_file *seq, व्योम *data)
अणु
	rsi_dbg(FSM_ZONE, "%x: rsi_enabled zone", rsi_zone_enabled);
	seq_म_लिखो(seq, "The zones available are %#x\n",
		   rsi_zone_enabled);
	वापस 0;
पूर्ण

/**
 * rsi_debug_पढ़ो() - This function calls single खोलो function of seq_file to
 *		      खोलो file and पढ़ो contents from it.
 * @inode: Poपूर्णांकer to the inode काष्ठाure.
 * @file: Poपूर्णांकer to the file काष्ठाure.
 *
 * Return: Poपूर्णांकer to the खोलोed file status: 0 on success, ENOMEM on failure.
 */
अटल पूर्णांक rsi_debug_पढ़ो(काष्ठा inode *inode,
			  काष्ठा file *file)
अणु
	वापस single_खोलो(file, rsi_debug_zone_पढ़ो, inode->i_निजी);
पूर्ण

/**
 * rsi_debug_zone_ग_लिखो() - This function ग_लिखोs पूर्णांकo hal queues as per user
 *			    requirement.
 * @filp: Poपूर्णांकer to the file काष्ठाure.
 * @buff: Poपूर्णांकer to the अक्षरacter buffer.
 * @len: Length of the data to be written पूर्णांकo buffer.
 * @data: Poपूर्णांकer to the data.
 *
 * Return: len: Number of bytes पढ़ो.
 */
अटल sमाप_प्रकार rsi_debug_zone_ग_लिखो(काष्ठा file *filp,
				    स्थिर अक्षर __user *buff,
				    माप_प्रकार len,
				    loff_t *data)
अणु
	अचिन्हित दीर्घ dbg_zone;
	पूर्णांक ret;

	अगर (!len)
		वापस 0;

	ret = kम_से_अदीर्घ_from_user(buff, len, 16, &dbg_zone);

	अगर (ret)
		वापस ret;

	rsi_zone_enabled = dbg_zone;
	वापस len;
पूर्ण

#घोषणा FOPS(ख_खोलो) अणु \
	.owner = THIS_MODULE, \
	.खोलो = (ख_खोलो), \
	.पढ़ो = seq_पढ़ो, \
	.llseek = seq_lseek, \
पूर्ण

#घोषणा FOPS_RW(ख_खोलो, ख_डालो) अणु \
	.owner = THIS_MODULE, \
	.खोलो = (ख_खोलो), \
	.पढ़ो = seq_पढ़ो, \
	.llseek = seq_lseek, \
	.ग_लिखो = (ख_डालो), \
पूर्ण

अटल स्थिर काष्ठा rsi_dbg_files dev_debugfs_files[] = अणु
	अणु"version", 0644, FOPS(rsi_version_खोलो),पूर्ण,
	अणु"stats", 0644, FOPS(rsi_stats_खोलो),पूर्ण,
	अणु"debug_zone", 0666, FOPS_RW(rsi_debug_पढ़ो, rsi_debug_zone_ग_लिखो),पूर्ण,
	अणु"sdio_stats", 0644, FOPS(rsi_sdio_stats_खोलो),पूर्ण,
पूर्ण;

/**
 * rsi_init_dbgfs() - This function initializes the dbgfs entry.
 * @adapter: Poपूर्णांकer to the adapter काष्ठाure.
 *
 * Return: 0 on success, -1 on failure.
 */
पूर्णांक rsi_init_dbgfs(काष्ठा rsi_hw *adapter)
अणु
	काष्ठा rsi_common *common = adapter->priv;
	काष्ठा rsi_debugfs *dev_dbgfs;
	अक्षर devdir[6];
	पूर्णांक ii;
	स्थिर काष्ठा rsi_dbg_files *files;

	dev_dbgfs = kzalloc(माप(*dev_dbgfs), GFP_KERNEL);
	अगर (!dev_dbgfs)
		वापस -ENOMEM;

	adapter->dfsentry = dev_dbgfs;

	snम_लिखो(devdir, माप(devdir), "%s",
		 wiphy_name(adapter->hw->wiphy));

	dev_dbgfs->subdir = debugfs_create_dir(devdir, शून्य);

	क्रम (ii = 0; ii < adapter->num_debugfs_entries; ii++) अणु
		files = &dev_debugfs_files[ii];
		dev_dbgfs->rsi_files[ii] =
		debugfs_create_file(files->name,
				    files->perms,
				    dev_dbgfs->subdir,
				    common,
				    &files->fops);
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rsi_init_dbgfs);

/**
 * rsi_हटाओ_dbgfs() - Removes the previously created dbgfs file entries
 *			in the reverse order of creation.
 * @adapter: Poपूर्णांकer to the adapter काष्ठाure.
 *
 * Return: None.
 */
व्योम rsi_हटाओ_dbgfs(काष्ठा rsi_hw *adapter)
अणु
	काष्ठा rsi_debugfs *dev_dbgfs = adapter->dfsentry;

	अगर (!dev_dbgfs)
		वापस;

	debugfs_हटाओ_recursive(dev_dbgfs->subdir);
पूर्ण
EXPORT_SYMBOL_GPL(rsi_हटाओ_dbgfs);
