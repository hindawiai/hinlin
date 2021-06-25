<शैली गुरु>
/*
 * This file implement the Wireless Extensions proc API.
 *
 * Authors :	Jean Tourrilhes - HPL - <jt@hpl.hp.com>
 * Copyright (c) 1997-2007 Jean Tourrilhes, All Rights Reserved.
 *
 * (As all part of the Linux kernel, this file is GPL)
 */

/*
 * The /proc/net/wireless file is a human पढ़ोable user-space पूर्णांकerface
 * exporting various wireless specअगरic statistics from the wireless devices.
 * This is the most popular part of the Wireless Extensions ;-)
 *
 * This पूर्णांकerface is a pure clone of /proc/net/dev (in net/core/dev.c).
 * The content of the file is basically the content of "struct iw_statistics".
 */

#समावेश <linux/module.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/wireless.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/rtnetlink.h>
#समावेश <net/iw_handler.h>
#समावेश <net/wext.h>


अटल व्योम wireless_seq_म_लिखो_stats(काष्ठा seq_file *seq,
				      काष्ठा net_device *dev)
अणु
	/* Get stats from the driver */
	काष्ठा iw_statistics *stats = get_wireless_stats(dev);
	अटल काष्ठा iw_statistics nullstats = अणुपूर्ण;

	/* show device अगर it's wireless regardless of current stats */
	अगर (!stats) अणु
#अगर_घोषित CONFIG_WIRELESS_EXT
		अगर (dev->wireless_handlers)
			stats = &nullstats;
#पूर्ण_अगर
#अगर_घोषित CONFIG_CFG80211
		अगर (dev->ieee80211_ptr)
			stats = &nullstats;
#पूर्ण_अगर
	पूर्ण

	अगर (stats) अणु
		seq_म_लिखो(seq, "%6s: %04x  %3d%c  %3d%c  %3d%c  %6d %6d %6d "
				"%6d %6d   %6d\n",
			   dev->name, stats->status, stats->qual.qual,
			   stats->qual.updated & IW_QUAL_QUAL_UPDATED
			   ? '.' : ' ',
			   ((__s32) stats->qual.level) -
			   ((stats->qual.updated & IW_QUAL_DBM) ? 0x100 : 0),
			   stats->qual.updated & IW_QUAL_LEVEL_UPDATED
			   ? '.' : ' ',
			   ((__s32) stats->qual.noise) -
			   ((stats->qual.updated & IW_QUAL_DBM) ? 0x100 : 0),
			   stats->qual.updated & IW_QUAL_NOISE_UPDATED
			   ? '.' : ' ',
			   stats->discard.nwid, stats->discard.code,
			   stats->discard.fragment, stats->discard.retries,
			   stats->discard.misc, stats->miss.beacon);

		अगर (stats != &nullstats)
			stats->qual.updated &= ~IW_QUAL_ALL_UPDATED;
	पूर्ण
पूर्ण

/* ---------------------------------------------------------------- */
/*
 * Prपूर्णांक info क्रम /proc/net/wireless (prपूर्णांक all entries)
 */
अटल पूर्णांक wireless_dev_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	might_sleep();

	अगर (v == SEQ_START_TOKEN)
		seq_म_लिखो(seq, "Inter-| sta-|   Quality        |   Discarded "
				"packets               | Missed | WE\n"
				" face | tus | link level noise |  nwid  "
				"crypt   frag  retry   misc | beacon | %d\n",
			   WIRELESS_EXT);
	अन्यथा
		wireless_seq_म_लिखो_stats(seq, v);
	वापस 0;
पूर्ण

अटल व्योम *wireless_dev_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	काष्ठा net *net = seq_file_net(seq);
	loff_t off;
	काष्ठा net_device *dev;

	rtnl_lock();
	अगर (!*pos)
		वापस SEQ_START_TOKEN;

	off = 1;
	क्रम_each_netdev(net, dev)
		अगर (off++ == *pos)
			वापस dev;
	वापस शून्य;
पूर्ण

अटल व्योम *wireless_dev_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा net *net = seq_file_net(seq);

	++*pos;

	वापस v == SEQ_START_TOKEN ?
		first_net_device(net) : next_net_device(v);
पूर्ण

अटल व्योम wireless_dev_seq_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
	rtnl_unlock();
पूर्ण

अटल स्थिर काष्ठा seq_operations wireless_seq_ops = अणु
	.start = wireless_dev_seq_start,
	.next  = wireless_dev_seq_next,
	.stop  = wireless_dev_seq_stop,
	.show  = wireless_dev_seq_show,
पूर्ण;

पूर्णांक __net_init wext_proc_init(काष्ठा net *net)
अणु
	/* Create /proc/net/wireless entry */
	अगर (!proc_create_net("wireless", 0444, net->proc_net,
			&wireless_seq_ops, माप(काष्ठा seq_net_निजी)))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

व्योम __net_निकास wext_proc_निकास(काष्ठा net *net)
अणु
	हटाओ_proc_entry("wireless", net->proc_net);
पूर्ण
