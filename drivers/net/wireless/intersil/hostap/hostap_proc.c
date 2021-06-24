<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* /proc routines क्रम Host AP driver */

#समावेश <linux/types.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/export.h>
#समावेश <net/lib80211.h>

#समावेश "hostap_wlan.h"
#समावेश "hostap.h"

#घोषणा PROC_LIMIT (PAGE_SIZE - 80)

#अगर !defined(PRISM2_NO_PROCFS_DEBUG) && defined(CONFIG_PROC_FS)
अटल पूर्णांक prism2_debug_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	local_info_t *local = m->निजी;
	पूर्णांक i;

	seq_म_लिखो(m, "next_txfid=%d next_alloc=%d\n",
		   local->next_txfid, local->next_alloc);
	क्रम (i = 0; i < PRISM2_TXFID_COUNT; i++)
		seq_म_लिखो(m, "FID: tx=%04X intransmit=%04X\n",
			   local->txfid[i], local->पूर्णांकransmitfid[i]);
	seq_म_लिखो(m, "FW TX rate control: %d\n", local->fw_tx_rate_control);
	seq_म_लिखो(m, "beacon_int=%d\n", local->beacon_पूर्णांक);
	seq_म_लिखो(m, "dtim_period=%d\n", local->dtim_period);
	seq_म_लिखो(m, "wds_max_connections=%d\n", local->wds_max_connections);
	seq_म_लिखो(m, "dev_enabled=%d\n", local->dev_enabled);
	seq_म_लिखो(m, "sw_tick_stuck=%d\n", local->sw_tick_stuck);
	क्रम (i = 0; i < WEP_KEYS; i++) अणु
		अगर (local->crypt_info.crypt[i] &&
		    local->crypt_info.crypt[i]->ops) अणु
			seq_म_लिखो(m, "crypt[%d]=%s\n", i,
				   local->crypt_info.crypt[i]->ops->name);
		पूर्ण
	पूर्ण
	seq_म_लिखो(m, "pri_only=%d\n", local->pri_only);
	seq_म_लिखो(m, "pci=%d\n", local->func->hw_type == HOSTAP_HW_PCI);
	seq_म_लिखो(m, "sram_type=%d\n", local->sram_type);
	seq_म_लिखो(m, "no_pri=%d\n", local->no_pri);

	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PROC_FS
अटल पूर्णांक prism2_stats_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	local_info_t *local = m->निजी;
	काष्ठा comm_tallies_sums *sums = &local->comm_tallies;

	seq_म_लिखो(m, "TxUnicastFrames=%u\n", sums->tx_unicast_frames);
	seq_म_लिखो(m, "TxMulticastframes=%u\n", sums->tx_multicast_frames);
	seq_म_लिखो(m, "TxFragments=%u\n", sums->tx_fragments);
	seq_म_लिखो(m, "TxUnicastOctets=%u\n", sums->tx_unicast_octets);
	seq_म_लिखो(m, "TxMulticastOctets=%u\n", sums->tx_multicast_octets);
	seq_म_लिखो(m, "TxDeferredTransmissions=%u\n",
		   sums->tx_deferred_transmissions);
	seq_म_लिखो(m, "TxSingleRetryFrames=%u\n", sums->tx_single_retry_frames);
	seq_म_लिखो(m, "TxMultipleRetryFrames=%u\n",
		   sums->tx_multiple_retry_frames);
	seq_म_लिखो(m, "TxRetryLimitExceeded=%u\n",
		   sums->tx_retry_limit_exceeded);
	seq_म_लिखो(m, "TxDiscards=%u\n", sums->tx_discards);
	seq_म_लिखो(m, "RxUnicastFrames=%u\n", sums->rx_unicast_frames);
	seq_म_लिखो(m, "RxMulticastFrames=%u\n", sums->rx_multicast_frames);
	seq_म_लिखो(m, "RxFragments=%u\n", sums->rx_fragments);
	seq_म_लिखो(m, "RxUnicastOctets=%u\n", sums->rx_unicast_octets);
	seq_म_लिखो(m, "RxMulticastOctets=%u\n", sums->rx_multicast_octets);
	seq_म_लिखो(m, "RxFCSErrors=%u\n", sums->rx_fcs_errors);
	seq_म_लिखो(m, "RxDiscardsNoBuffer=%u\n", sums->rx_discards_no_buffer);
	seq_म_लिखो(m, "TxDiscardsWrongSA=%u\n", sums->tx_discards_wrong_sa);
	seq_म_लिखो(m, "RxDiscardsWEPUndecryptable=%u\n",
		   sums->rx_discards_wep_undecryptable);
	seq_म_लिखो(m, "RxMessageInMsgFragments=%u\n",
		   sums->rx_message_in_msg_fragments);
	seq_म_लिखो(m, "RxMessageInBadMsgFragments=%u\n",
		   sums->rx_message_in_bad_msg_fragments);
	/* FIX: this may grow too दीर्घ क्रम one page(?) */

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक prism2_wds_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा list_head *ptr = v;
	काष्ठा hostap_पूर्णांकerface *अगरace;

	अगरace = list_entry(ptr, काष्ठा hostap_पूर्णांकerface, list);
	अगर (अगरace->type == HOSTAP_INTERFACE_WDS)
		seq_म_लिखो(m, "%s\t%pM\n",
			   अगरace->dev->name, अगरace->u.wds.remote_addr);
	वापस 0;
पूर्ण

अटल व्योम *prism2_wds_proc_start(काष्ठा seq_file *m, loff_t *_pos)
अणु
	local_info_t *local = PDE_DATA(file_inode(m->file));
	पढ़ो_lock_bh(&local->अगरace_lock);
	वापस seq_list_start(&local->hostap_पूर्णांकerfaces, *_pos);
पूर्ण

अटल व्योम *prism2_wds_proc_next(काष्ठा seq_file *m, व्योम *v, loff_t *_pos)
अणु
	local_info_t *local = PDE_DATA(file_inode(m->file));
	वापस seq_list_next(v, &local->hostap_पूर्णांकerfaces, _pos);
पूर्ण

अटल व्योम prism2_wds_proc_stop(काष्ठा seq_file *m, व्योम *v)
अणु
	local_info_t *local = PDE_DATA(file_inode(m->file));
	पढ़ो_unlock_bh(&local->अगरace_lock);
पूर्ण

अटल स्थिर काष्ठा seq_operations prism2_wds_proc_seqops = अणु
	.start	= prism2_wds_proc_start,
	.next	= prism2_wds_proc_next,
	.stop	= prism2_wds_proc_stop,
	.show	= prism2_wds_proc_show,
पूर्ण;

अटल पूर्णांक prism2_bss_list_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	local_info_t *local = PDE_DATA(file_inode(m->file));
	काष्ठा list_head *ptr = v;
	काष्ठा hostap_bss_info *bss;

	अगर (ptr == &local->bss_list) अणु
		seq_म_लिखो(m, "#BSSID\tlast_update\tcount\tcapab_info\tSSID(txt)\t"
			   "SSID(hex)\tWPA IE\n");
		वापस 0;
	पूर्ण

	bss = list_entry(ptr, काष्ठा hostap_bss_info, list);
	seq_म_लिखो(m, "%pM\t%lu\t%u\t0x%x\t",
		   bss->bssid, bss->last_update,
		   bss->count, bss->capab_info);

	seq_म_लिखो(m, "%*pE", (पूर्णांक)bss->ssid_len, bss->ssid);

	seq_अ_दो(m, '\t');
	seq_म_लिखो(m, "%*phN", (पूर्णांक)bss->ssid_len, bss->ssid);
	seq_अ_दो(m, '\t');
	seq_म_लिखो(m, "%*phN", (पूर्णांक)bss->wpa_ie_len, bss->wpa_ie);
	seq_अ_दो(m, '\n');
	वापस 0;
पूर्ण

अटल व्योम *prism2_bss_list_proc_start(काष्ठा seq_file *m, loff_t *_pos)
	__acquires(&local->lock)
अणु
	local_info_t *local = PDE_DATA(file_inode(m->file));
	spin_lock_bh(&local->lock);
	वापस seq_list_start_head(&local->bss_list, *_pos);
पूर्ण

अटल व्योम *prism2_bss_list_proc_next(काष्ठा seq_file *m, व्योम *v, loff_t *_pos)
अणु
	local_info_t *local = PDE_DATA(file_inode(m->file));
	वापस seq_list_next(v, &local->bss_list, _pos);
पूर्ण

अटल व्योम prism2_bss_list_proc_stop(काष्ठा seq_file *m, व्योम *v)
	__releases(&local->lock)
अणु
	local_info_t *local = PDE_DATA(file_inode(m->file));
	spin_unlock_bh(&local->lock);
पूर्ण

अटल स्थिर काष्ठा seq_operations prism2_bss_list_proc_seqops = अणु
	.start	= prism2_bss_list_proc_start,
	.next	= prism2_bss_list_proc_next,
	.stop	= prism2_bss_list_proc_stop,
	.show	= prism2_bss_list_proc_show,
पूर्ण;

#अगर_घोषित CONFIG_PROC_FS
अटल पूर्णांक prism2_crypt_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	local_info_t *local = m->निजी;
	पूर्णांक i;

	seq_म_लिखो(m, "tx_keyidx=%d\n", local->crypt_info.tx_keyidx);
	क्रम (i = 0; i < WEP_KEYS; i++) अणु
		अगर (local->crypt_info.crypt[i] &&
		    local->crypt_info.crypt[i]->ops &&
		    local->crypt_info.crypt[i]->ops->prपूर्णांक_stats) अणु
			local->crypt_info.crypt[i]->ops->prपूर्णांक_stats(
				m, local->crypt_info.crypt[i]->priv);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल sमाप_प्रकार prism2_pda_proc_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				    माप_प्रकार count, loff_t *_pos)
अणु
	local_info_t *local = PDE_DATA(file_inode(file));
	माप_प्रकार off;

	अगर (local->pda == शून्य || *_pos >= PRISM2_PDA_SIZE)
		वापस 0;

	off = *_pos;
	अगर (count > PRISM2_PDA_SIZE - off)
		count = PRISM2_PDA_SIZE - off;
	अगर (copy_to_user(buf, local->pda + off, count) != 0)
		वापस -EFAULT;
	*_pos += count;
	वापस count;
पूर्ण

अटल स्थिर काष्ठा proc_ops prism2_pda_proc_ops = अणु
	.proc_पढ़ो	= prism2_pda_proc_पढ़ो,
	.proc_lseek	= generic_file_llseek,
पूर्ण;


अटल sमाप_प्रकार prism2_aux_dump_proc_no_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
					    माप_प्रकार bufsize, loff_t *_pos)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा proc_ops prism2_aux_dump_proc_ops = अणु
	.proc_पढ़ो	= prism2_aux_dump_proc_no_पढ़ो,
	.proc_lseek	= शेष_llseek,
पूर्ण;


#अगर_घोषित PRISM2_IO_DEBUG
अटल पूर्णांक prism2_io_debug_proc_पढ़ो(अक्षर *page, अक्षर **start, off_t off,
				     पूर्णांक count, पूर्णांक *eof, व्योम *data)
अणु
	local_info_t *local = (local_info_t *) data;
	पूर्णांक head = local->io_debug_head;
	पूर्णांक start_bytes, left, copy;

	अगर (off + count > PRISM2_IO_DEBUG_SIZE * 4) अणु
		*eof = 1;
		अगर (off >= PRISM2_IO_DEBUG_SIZE * 4)
			वापस 0;
		count = PRISM2_IO_DEBUG_SIZE * 4 - off;
	पूर्ण

	start_bytes = (PRISM2_IO_DEBUG_SIZE - head) * 4;
	left = count;

	अगर (off < start_bytes) अणु
		copy = start_bytes - off;
		अगर (copy > count)
			copy = count;
		स_नकल(page, ((u8 *) &local->io_debug[head]) + off, copy);
		left -= copy;
		अगर (left > 0)
			स_नकल(&page[copy], local->io_debug, left);
	पूर्ण अन्यथा अणु
		स_नकल(page, ((u8 *) local->io_debug) + (off - start_bytes),
		       left);
	पूर्ण

	*start = page;

	वापस count;
पूर्ण
#पूर्ण_अगर /* PRISM2_IO_DEBUG */


#अगर_अघोषित PRISM2_NO_STATION_MODES
अटल पूर्णांक prism2_scan_results_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	local_info_t *local = PDE_DATA(file_inode(m->file));
	अचिन्हित दीर्घ entry;
	पूर्णांक i, len;
	काष्ठा hfa384x_hostscan_result *scanres;
	u8 *p;

	अगर (v == SEQ_START_TOKEN) अणु
		seq_म_लिखो(m,
			   "CHID ANL SL BcnInt Capab Rate BSSID ATIM SupRates SSID\n");
		वापस 0;
	पूर्ण

	entry = (अचिन्हित दीर्घ)v - 2;
	scanres = &local->last_scan_results[entry];

	seq_म_लिखो(m, "%d %d %d %d 0x%02x %d %pM %d ",
		   le16_to_cpu(scanres->chid),
		   (s16) le16_to_cpu(scanres->anl),
		   (s16) le16_to_cpu(scanres->sl),
		   le16_to_cpu(scanres->beacon_पूर्णांकerval),
		   le16_to_cpu(scanres->capability),
		   le16_to_cpu(scanres->rate),
		   scanres->bssid,
		   le16_to_cpu(scanres->atim));

	p = scanres->sup_rates;
	क्रम (i = 0; i < माप(scanres->sup_rates); i++) अणु
		अगर (p[i] == 0)
			अवरोध;
		seq_म_लिखो(m, "<%02x>", p[i]);
	पूर्ण
	seq_अ_दो(m, ' ');

	p = scanres->ssid;
	len = le16_to_cpu(scanres->ssid_len);
	अगर (len > 32)
		len = 32;
	क्रम (i = 0; i < len; i++) अणु
		अचिन्हित अक्षर c = p[i];
		अगर (c >= 32 && c < 127)
			seq_अ_दो(m, c);
		अन्यथा
			seq_म_लिखो(m, "<%02x>", c);
	पूर्ण
	seq_अ_दो(m, '\n');
	वापस 0;
पूर्ण

अटल व्योम *prism2_scan_results_proc_start(काष्ठा seq_file *m, loff_t *_pos)
अणु
	local_info_t *local = PDE_DATA(file_inode(m->file));
	spin_lock_bh(&local->lock);

	/* We have a header (pos 0) + N results to show (pos 1...N) */
	अगर (*_pos > local->last_scan_results_count)
		वापस शून्य;
	वापस (व्योम *)(अचिन्हित दीर्घ)(*_pos + 1); /* 0 would be खातापूर्ण */
पूर्ण

अटल व्योम *prism2_scan_results_proc_next(काष्ठा seq_file *m, व्योम *v, loff_t *_pos)
अणु
	local_info_t *local = PDE_DATA(file_inode(m->file));

	++*_pos;
	अगर (*_pos > local->last_scan_results_count)
		वापस शून्य;
	वापस (व्योम *)(अचिन्हित दीर्घ)(*_pos + 1); /* 0 would be खातापूर्ण */
पूर्ण

अटल व्योम prism2_scan_results_proc_stop(काष्ठा seq_file *m, व्योम *v)
अणु
	local_info_t *local = PDE_DATA(file_inode(m->file));
	spin_unlock_bh(&local->lock);
पूर्ण

अटल स्थिर काष्ठा seq_operations prism2_scan_results_proc_seqops = अणु
	.start	= prism2_scan_results_proc_start,
	.next	= prism2_scan_results_proc_next,
	.stop	= prism2_scan_results_proc_stop,
	.show	= prism2_scan_results_proc_show,
पूर्ण;
#पूर्ण_अगर /* PRISM2_NO_STATION_MODES */


व्योम hostap_init_proc(local_info_t *local)
अणु
	local->proc = शून्य;

	अगर (hostap_proc == शून्य) अणु
		prपूर्णांकk(KERN_WARNING "%s: hostap proc directory not created\n",
		       local->dev->name);
		वापस;
	पूर्ण

	local->proc = proc_सूची_गढ़ो(local->ddev->name, hostap_proc);
	अगर (local->proc == शून्य) अणु
		prपूर्णांकk(KERN_INFO "/proc/net/hostap/%s creation failed\n",
		       local->ddev->name);
		वापस;
	पूर्ण

#अगर_अघोषित PRISM2_NO_PROCFS_DEBUG
	proc_create_single_data("debug", 0, local->proc,
			prism2_debug_proc_show, local);
#पूर्ण_अगर /* PRISM2_NO_PROCFS_DEBUG */
	proc_create_single_data("stats", 0, local->proc, prism2_stats_proc_show,
			local);
	proc_create_seq_data("wds", 0, local->proc,
			&prism2_wds_proc_seqops, local);
	proc_create_data("pda", 0, local->proc,
			 &prism2_pda_proc_ops, local);
	proc_create_data("aux_dump", 0, local->proc,
			 local->func->पढ़ो_aux_proc_ops ?: &prism2_aux_dump_proc_ops,
			 local);
	proc_create_seq_data("bss_list", 0, local->proc,
			&prism2_bss_list_proc_seqops, local);
	proc_create_single_data("crypt", 0, local->proc, prism2_crypt_proc_show,
		local);
#अगर_घोषित PRISM2_IO_DEBUG
	proc_create_single_data("io_debug", 0, local->proc,
			prism2_debug_proc_show, local);
#पूर्ण_अगर /* PRISM2_IO_DEBUG */
#अगर_अघोषित PRISM2_NO_STATION_MODES
	proc_create_seq_data("scan_results", 0, local->proc,
			&prism2_scan_results_proc_seqops, local);
#पूर्ण_अगर /* PRISM2_NO_STATION_MODES */
पूर्ण


व्योम hostap_हटाओ_proc(local_info_t *local)
अणु
	proc_हटाओ(local->proc);
पूर्ण


EXPORT_SYMBOL(hostap_init_proc);
EXPORT_SYMBOL(hostap_हटाओ_proc);
