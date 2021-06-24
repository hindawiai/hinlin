<शैली गुरु>
/*
 * Copyright (c) 2008-2011 Atheros Communications Inc.
 * Copyright (c) 2011 Neratec Solutions AG
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

#समावेश <linux/debugfs.h>
#समावेश <linux/export.h>

#समावेश "ath9k.h"
#समावेश "dfs_debug.h"
#समावेश "../dfs_pattern_detector.h"

अटल काष्ठा ath_dfs_pool_stats dfs_pool_stats = अणु 0 पूर्ण;

#घोषणा ATH9K_DFS_STAT(s, p) \
	len += scnम_लिखो(buf + len, size - len, "%28s : %10u\n", s, \
			 sc->debug.stats.dfs_stats.p)
#घोषणा ATH9K_DFS_POOL_STAT(s, p) \
	len += scnम_लिखो(buf + len, size - len, "%28s : %10u\n", s, \
			 dfs_pool_stats.p);

अटल sमाप_प्रकार पढ़ो_file_dfs(काष्ठा file *file, अक्षर __user *user_buf,
			     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath_softc *sc = file->निजी_data;
	काष्ठा ath9k_hw_version *hw_ver = &sc->sc_ah->hw_version;
	अक्षर *buf;
	अचिन्हित पूर्णांक len = 0, size = 8000;
	sमाप_प्रकार retval = 0;

	buf = kzalloc(size, GFP_KERNEL);
	अगर (buf == शून्य)
		वापस -ENOMEM;

	len += scnम_लिखो(buf + len, size - len, "DFS support for "
			 "macVersion = 0x%x, macRev = 0x%x: %s\n",
			 hw_ver->macVersion, hw_ver->macRev,
			 (sc->sc_ah->caps.hw_caps & ATH9K_HW_CAP_DFS) ?
					"enabled" : "disabled");

	अगर (!sc->dfs_detector) अणु
		len += scnम_लिखो(buf + len, size - len,
				 "DFS detector not enabled\n");
		जाओ निकास;
	पूर्ण

	dfs_pool_stats = sc->dfs_detector->get_stats(sc->dfs_detector);

	len += scnम_लिखो(buf + len, size - len, "Pulse detector statistics:\n");
	ATH9K_DFS_STAT("pulse events reported   ", pulses_total);
	ATH9K_DFS_STAT("invalid pulse events    ", pulses_no_dfs);
	ATH9K_DFS_STAT("DFS pulses detected     ", pulses_detected);
	ATH9K_DFS_STAT("Datalen discards        ", datalen_discards);
	ATH9K_DFS_STAT("RSSI discards           ", rssi_discards);
	ATH9K_DFS_STAT("BW info discards        ", bwinfo_discards);
	ATH9K_DFS_STAT("Primary channel pulses  ", pri_phy_errors);
	ATH9K_DFS_STAT("Secondary channel pulses", ext_phy_errors);
	ATH9K_DFS_STAT("Dual channel pulses     ", dc_phy_errors);
	len += scnम_लिखो(buf + len, size - len, "Radar detector statistics "
			 "(current DFS region: %d)\n",
			 sc->dfs_detector->region);
	ATH9K_DFS_STAT("Pulse events processed  ", pulses_processed);
	ATH9K_DFS_STAT("Radars detected         ", radar_detected);
	len += scnम_लिखो(buf + len, size - len, "Global Pool statistics:\n");
	ATH9K_DFS_POOL_STAT("Pool references         ", pool_reference);
	ATH9K_DFS_POOL_STAT("Pulses allocated        ", pulse_allocated);
	ATH9K_DFS_POOL_STAT("Pulses alloc error      ", pulse_alloc_error);
	ATH9K_DFS_POOL_STAT("Pulses in use           ", pulse_used);
	ATH9K_DFS_POOL_STAT("Seqs. allocated         ", pseq_allocated);
	ATH9K_DFS_POOL_STAT("Seqs. alloc error       ", pseq_alloc_error);
	ATH9K_DFS_POOL_STAT("Seqs. in use            ", pseq_used);

निकास:
	अगर (len > size)
		len = size;

	retval = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
	kमुक्त(buf);

	वापस retval;
पूर्ण

/* magic number to prevent accidental reset of DFS statistics */
#घोषणा DFS_STATS_RESET_MAGIC	0x80000000
अटल sमाप_प्रकार ग_लिखो_file_dfs(काष्ठा file *file, स्थिर अक्षर __user *user_buf,
			      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath_softc *sc = file->निजी_data;
	अचिन्हित दीर्घ val;
	अक्षर buf[32];
	sमाप_प्रकार len;

	len = min(count, माप(buf) - 1);
	अगर (copy_from_user(buf, user_buf, len))
		वापस -EFAULT;

	buf[len] = '\0';
	अगर (kम_से_अदीर्घ(buf, 0, &val))
		वापस -EINVAL;

	अगर (val == DFS_STATS_RESET_MAGIC)
		स_रखो(&sc->debug.stats.dfs_stats, 0,
		       माप(sc->debug.stats.dfs_stats));
	वापस count;
पूर्ण

अटल sमाप_प्रकार ग_लिखो_file_simulate_radar(काष्ठा file *file,
					 स्थिर अक्षर __user *user_buf,
					 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath_softc *sc = file->निजी_data;

	ieee80211_radar_detected(sc->hw);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_simulate_radar = अणु
	.ग_लिखो = ग_लिखो_file_simulate_radar,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल स्थिर काष्ठा file_operations fops_dfs_stats = अणु
	.पढ़ो = पढ़ो_file_dfs,
	.ग_लिखो = ग_लिखो_file_dfs,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

व्योम ath9k_dfs_init_debug(काष्ठा ath_softc *sc)
अणु
	debugfs_create_file("dfs_stats", 0400,
			    sc->debug.debugfs_phy, sc, &fops_dfs_stats);
	debugfs_create_file("dfs_simulate_radar", 0200,
			    sc->debug.debugfs_phy, sc, &fops_simulate_radar);
पूर्ण
