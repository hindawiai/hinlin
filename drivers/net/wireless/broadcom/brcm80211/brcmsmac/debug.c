<शैली गुरु>
/*
 * Copyright (c) 2012 Broadcom Corporation
 * Copyright (c) 2012 Canonical Ltd.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#समावेश <linux/debugfs.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर.h>
#समावेश <linux/net.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/ieee80211.h>
#समावेश <linux/module.h>
#समावेश <net/mac80211.h>

#समावेश <defs.h>
#समावेश <brcmu_wअगरi.h>
#समावेश <brcmu_utils.h>
#समावेश "types.h"
#समावेश "main.h"
#समावेश "debug.h"
#समावेश "brcms_trace_events.h"
#समावेश "phy/phy_int.h"

अटल काष्ठा dentry *root_folder;

व्योम brcms_debugfs_init(व्योम)
अणु
	root_folder = debugfs_create_dir(KBUILD_MODNAME, शून्य);
पूर्ण

व्योम brcms_debugfs_निकास(व्योम)
अणु
	debugfs_हटाओ_recursive(root_folder);
	root_folder = शून्य;
पूर्ण

व्योम brcms_debugfs_attach(काष्ठा brcms_pub *drvr)
अणु
	drvr->dbgfs_dir = debugfs_create_dir(
		 dev_name(&drvr->wlc->hw->d11core->dev), root_folder);
पूर्ण

व्योम brcms_debugfs_detach(काष्ठा brcms_pub *drvr)
अणु
	debugfs_हटाओ_recursive(drvr->dbgfs_dir);
पूर्ण

काष्ठा dentry *brcms_debugfs_get_devdir(काष्ठा brcms_pub *drvr)
अणु
	वापस drvr->dbgfs_dir;
पूर्ण

अटल
पूर्णांक brcms_debugfs_hardware_पढ़ो(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा brcms_pub *drvr = s->निजी;
	काष्ठा brcms_hardware *hw = drvr->wlc->hw;
	काष्ठा bcma_device *core = hw->d11core;
	काष्ठा bcma_bus *bus = core->bus;
	अक्षर boardrev[BRCMU_BOARDREV_LEN];

	seq_म_लिखो(s, "chipnum 0x%x\n"
		   "chiprev 0x%x\n"
		   "chippackage 0x%x\n"
		   "corerev 0x%x\n"
		   "boardid 0x%x\n"
		   "boardvendor 0x%x\n"
		   "boardrev %s\n"
		   "boardflags 0x%x\n"
		   "boardflags2 0x%x\n"
		   "ucoderev 0x%x\n"
		   "radiorev 0x%x\n"
		   "phytype 0x%x\n"
		   "phyrev 0x%x\n"
		   "anarev 0x%x\n"
		   "nvramrev %d\n",
		   bus->chipinfo.id, bus->chipinfo.rev, bus->chipinfo.pkg,
		   core->id.rev, bus->boardinfo.type, bus->boardinfo.venकरोr,
		   brcmu_boardrev_str(hw->boardrev, boardrev),
		   drvr->wlc->hw->boardflags, drvr->wlc->hw->boardflags2,
		   drvr->wlc->ucode_rev, hw->band->radiorev,
		   hw->band->phytype, hw->band->phyrev, hw->band->pi->ana_rev,
		   hw->sromrev);
	वापस 0;
पूर्ण

अटल पूर्णांक brcms_debugfs_macstat_पढ़ो(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा brcms_pub *drvr = s->निजी;
	काष्ठा brcms_info *wl = drvr->ieee_hw->priv;
	काष्ठा macstat stats;
	पूर्णांक i;

	spin_lock_bh(&wl->lock);
	stats = *(drvr->wlc->core->macstat_snapshot);
	spin_unlock_bh(&wl->lock);

	seq_म_लिखो(s, "txallfrm: %d\n", stats.txallfrm);
	seq_म_लिखो(s, "txrtsfrm: %d\n", stats.txrtsfrm);
	seq_म_लिखो(s, "txctsfrm: %d\n", stats.txctsfrm);
	seq_म_लिखो(s, "txackfrm: %d\n", stats.txackfrm);
	seq_म_लिखो(s, "txdnlfrm: %d\n", stats.txdnlfrm);
	seq_म_लिखो(s, "txbcnfrm: %d\n", stats.txbcnfrm);
	seq_म_लिखो(s, "txfunfl[8]:");
	क्रम (i = 0; i < ARRAY_SIZE(stats.txfunfl); i++)
		seq_म_लिखो(s, " %d", stats.txfunfl[i]);
	seq_म_लिखो(s, "\ntxtplunfl: %d\n", stats.txtplunfl);
	seq_म_लिखो(s, "txphyerr: %d\n", stats.txphyerr);
	seq_म_लिखो(s, "pktengrxducast: %d\n", stats.pktengrxducast);
	seq_म_लिखो(s, "pktengrxdmcast: %d\n", stats.pktengrxdmcast);
	seq_म_लिखो(s, "rxfrmtoolong: %d\n", stats.rxfrmtooदीर्घ);
	seq_म_लिखो(s, "rxfrmtooshrt: %d\n", stats.rxfrmtooshrt);
	seq_म_लिखो(s, "rxinvmachdr: %d\n", stats.rxinvmachdr);
	seq_म_लिखो(s, "rxbadfcs: %d\n", stats.rxbadfcs);
	seq_म_लिखो(s, "rxbadplcp: %d\n", stats.rxbadplcp);
	seq_म_लिखो(s, "rxcrsglitch: %d\n", stats.rxcrsglitch);
	seq_म_लिखो(s, "rxstrt: %d\n", stats.rxstrt);
	seq_म_लिखो(s, "rxdfrmucastmbss: %d\n", stats.rxdfrmucasपंचांगbss);
	seq_म_लिखो(s, "rxmfrmucastmbss: %d\n", stats.rxmfrmucasपंचांगbss);
	seq_म_लिखो(s, "rxcfrmucast: %d\n", stats.rxcfrmucast);
	seq_म_लिखो(s, "rxrtsucast: %d\n", stats.rxrtsucast);
	seq_म_लिखो(s, "rxctsucast: %d\n", stats.rxctsucast);
	seq_म_लिखो(s, "rxackucast: %d\n", stats.rxackucast);
	seq_म_लिखो(s, "rxdfrmocast: %d\n", stats.rxdfrmocast);
	seq_म_लिखो(s, "rxmfrmocast: %d\n", stats.rxmfrmocast);
	seq_म_लिखो(s, "rxcfrmocast: %d\n", stats.rxcfrmocast);
	seq_म_लिखो(s, "rxrtsocast: %d\n", stats.rxrtsocast);
	seq_म_लिखो(s, "rxctsocast: %d\n", stats.rxctsocast);
	seq_म_लिखो(s, "rxdfrmmcast: %d\n", stats.rxdfrmmcast);
	seq_म_लिखो(s, "rxmfrmmcast: %d\n", stats.rxmfrmmcast);
	seq_म_लिखो(s, "rxcfrmmcast: %d\n", stats.rxcfrmmcast);
	seq_म_लिखो(s, "rxbeaconmbss: %d\n", stats.rxbeaconmbss);
	seq_म_लिखो(s, "rxdfrmucastobss: %d\n", stats.rxdfrmucastobss);
	seq_म_लिखो(s, "rxbeaconobss: %d\n", stats.rxbeaconobss);
	seq_म_लिखो(s, "rxrsptmout: %d\n", stats.rxrspपंचांगout);
	seq_म_लिखो(s, "bcntxcancl: %d\n", stats.bcntxcancl);
	seq_म_लिखो(s, "rxf0ovfl: %d\n", stats.rxf0ovfl);
	seq_म_लिखो(s, "rxf1ovfl: %d\n", stats.rxf1ovfl);
	seq_म_लिखो(s, "rxf2ovfl: %d\n", stats.rxf2ovfl);
	seq_म_लिखो(s, "txsfovfl: %d\n", stats.txsfovfl);
	seq_म_लिखो(s, "pmqovfl: %d\n", stats.pmqovfl);
	seq_म_लिखो(s, "rxcgprqfrm: %d\n", stats.rxcgprqfrm);
	seq_म_लिखो(s, "rxcgprsqovfl: %d\n", stats.rxcgprsqovfl);
	seq_म_लिखो(s, "txcgprsfail: %d\n", stats.txcgprsfail);
	seq_म_लिखो(s, "txcgprssuc: %d\n", stats.txcgprssuc);
	seq_म_लिखो(s, "prs_timeout: %d\n", stats.prs_समयout);
	seq_म_लिखो(s, "rxnack: %d\n", stats.rxnack);
	seq_म_लिखो(s, "frmscons: %d\n", stats.frmscons);
	seq_म_लिखो(s, "txnack: %d\n", stats.txnack);
	seq_म_लिखो(s, "txglitch_nack: %d\n", stats.txglitch_nack);
	seq_म_लिखो(s, "txburst: %d\n", stats.txburst);
	seq_म_लिखो(s, "bphy_rxcrsglitch: %d\n", stats.bphy_rxcrsglitch);
	seq_म_लिखो(s, "phywatchdog: %d\n", stats.phywatchकरोg);
	seq_म_लिखो(s, "bphy_badplcp: %d\n", stats.bphy_badplcp);
	वापस 0;
पूर्ण

काष्ठा brcms_debugfs_entry अणु
	पूर्णांक (*पढ़ो)(काष्ठा seq_file *seq, व्योम *data);
	काष्ठा brcms_pub *drvr;
पूर्ण;

अटल पूर्णांक brcms_debugfs_entry_खोलो(काष्ठा inode *inode, काष्ठा file *f)
अणु
	काष्ठा brcms_debugfs_entry *entry = inode->i_निजी;

	वापस single_खोलो(f, entry->पढ़ो, entry->drvr);
पूर्ण

अटल स्थिर काष्ठा file_operations brcms_debugfs_def_ops = अणु
	.owner = THIS_MODULE,
	.खोलो = brcms_debugfs_entry_खोलो,
	.release = single_release,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek
पूर्ण;

अटल व्योम
brcms_debugfs_add_entry(काष्ठा brcms_pub *drvr, स्थिर अक्षर *fn,
			पूर्णांक (*पढ़ो_fn)(काष्ठा seq_file *seq, व्योम *data))
अणु
	काष्ठा device *dev = &drvr->wlc->hw->d11core->dev;
	काष्ठा dentry *dentry =  drvr->dbgfs_dir;
	काष्ठा brcms_debugfs_entry *entry;

	entry = devm_kzalloc(dev, माप(*entry), GFP_KERNEL);
	अगर (!entry)
		वापस;

	entry->पढ़ो = पढ़ो_fn;
	entry->drvr = drvr;

	debugfs_create_file(fn, 0444, dentry, entry, &brcms_debugfs_def_ops);
पूर्ण

व्योम brcms_debugfs_create_files(काष्ठा brcms_pub *drvr)
अणु
	brcms_debugfs_add_entry(drvr, "hardware", brcms_debugfs_hardware_पढ़ो);
	brcms_debugfs_add_entry(drvr, "macstat", brcms_debugfs_macstat_पढ़ो);
पूर्ण

#घोषणा __brcms_fn(fn)						\
व्योम __brcms_ ##fn(काष्ठा device *dev, स्थिर अक्षर *fmt, ...)	\
अणु								\
	काष्ठा va_क्रमmat vaf = अणु				\
		.fmt = fmt,					\
	पूर्ण;							\
	बहु_सूची args;						\
								\
	बहु_शुरू(args, fmt);					\
	vaf.va = &args;						\
	dev_ ##fn(dev, "%pV", &vaf);				\
	trace_brcms_ ##fn(&vaf);				\
	बहु_पूर्ण(args);						\
पूर्ण

__brcms_fn(info)
__brcms_fn(warn)
__brcms_fn(err)
__brcms_fn(crit)

#अगर defined(CONFIG_BRCMDBG) || defined(CONFIG_BRCM_TRACING)
व्योम __brcms_dbg(काष्ठा device *dev, u32 level, स्थिर अक्षर *func,
		 स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf = अणु
		.fmt = fmt,
	पूर्ण;
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	vaf.va = &args;
#अगर_घोषित CONFIG_BRCMDBG
	अगर ((brcm_msg_level & level) && net_ratelimit())
		dev_err(dev, "%s %pV", func, &vaf);
#पूर्ण_अगर
	trace_brcms_dbg(level, func, &vaf);
	बहु_पूर्ण(args);
पूर्ण
#पूर्ण_अगर
