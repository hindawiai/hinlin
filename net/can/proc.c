<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause)
/*
 * proc.c - procfs support क्रम Protocol family CAN core module
 *
 * Copyright (c) 2002-2007 Volkswagen Group Electronic Research
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. Neither the name of Volkswagen nor the names of its contributors
 *    may be used to enकरोrse or promote products derived from this software
 *    without specअगरic prior written permission.
 *
 * Alternatively, provided that this notice is retained in full, this
 * software may be distributed under the terms of the GNU General
 * Public License ("GPL") version 2, in which हाल the provisions of the
 * GPL apply INSTEAD OF those given above.
 *
 * The provided data काष्ठाures and बाह्यal पूर्णांकerfaces from this code
 * are not restricted to be used by modules with a GPL compatible license.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/list.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/can/can-ml.h>
#समावेश <linux/can/core.h>

#समावेश "af_can.h"

/*
 * proc filenames क्रम the PF_CAN core
 */

#घोषणा CAN_PROC_STATS       "stats"
#घोषणा CAN_PROC_RESET_STATS "reset_stats"
#घोषणा CAN_PROC_RCVLIST_ALL "rcvlist_all"
#घोषणा CAN_PROC_RCVLIST_FIL "rcvlist_fil"
#घोषणा CAN_PROC_RCVLIST_INV "rcvlist_inv"
#घोषणा CAN_PROC_RCVLIST_SFF "rcvlist_sff"
#घोषणा CAN_PROC_RCVLIST_EFF "rcvlist_eff"
#घोषणा CAN_PROC_RCVLIST_ERR "rcvlist_err"

अटल पूर्णांक user_reset;

अटल स्थिर अक्षर rx_list_name[][8] = अणु
	[RX_ERR] = "rx_err",
	[RX_ALL] = "rx_all",
	[RX_FIL] = "rx_fil",
	[RX_INV] = "rx_inv",
पूर्ण;

/*
 * af_can statistics stuff
 */

अटल व्योम can_init_stats(काष्ठा net *net)
अणु
	काष्ठा can_pkg_stats *pkg_stats = net->can.pkg_stats;
	काष्ठा can_rcv_lists_stats *rcv_lists_stats = net->can.rcv_lists_stats;
	/*
	 * This स_रखो function is called from a समयr context (when
	 * can_statसमयr is active which is the शेष) OR in a process
	 * context (पढ़ोing the proc_fs when can_statसमयr is disabled).
	 */
	स_रखो(pkg_stats, 0, माप(काष्ठा can_pkg_stats));
	pkg_stats->jअगरfies_init = jअगरfies;

	rcv_lists_stats->stats_reset++;

	अगर (user_reset) अणु
		user_reset = 0;
		rcv_lists_stats->user_reset++;
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ calc_rate(अचिन्हित दीर्घ oldjअगर, अचिन्हित दीर्घ newjअगर,
			       अचिन्हित दीर्घ count)
अणु
	अचिन्हित दीर्घ rate;

	अगर (oldjअगर == newjअगर)
		वापस 0;

	/* see can_stat_update() - this should NEVER happen! */
	अगर (count > (अच_दीर्घ_उच्च / HZ)) अणु
		prपूर्णांकk(KERN_ERR "can: calc_rate: count exceeded! %ld\n",
		       count);
		वापस 99999999;
	पूर्ण

	rate = (count * HZ) / (newjअगर - oldjअगर);

	वापस rate;
पूर्ण

व्योम can_stat_update(काष्ठा समयr_list *t)
अणु
	काष्ठा net *net = from_समयr(net, t, can.statसमयr);
	काष्ठा can_pkg_stats *pkg_stats = net->can.pkg_stats;
	अचिन्हित दीर्घ j = jअगरfies; /* snapshot */

	/* restart counting in समयr context on user request */
	अगर (user_reset)
		can_init_stats(net);

	/* restart counting on jअगरfies overflow */
	अगर (j < pkg_stats->jअगरfies_init)
		can_init_stats(net);

	/* prevent overflow in calc_rate() */
	अगर (pkg_stats->rx_frames > (अच_दीर्घ_उच्च / HZ))
		can_init_stats(net);

	/* prevent overflow in calc_rate() */
	अगर (pkg_stats->tx_frames > (अच_दीर्घ_उच्च / HZ))
		can_init_stats(net);

	/* matches overflow - very improbable */
	अगर (pkg_stats->matches > (अच_दीर्घ_उच्च / 100))
		can_init_stats(net);

	/* calc total values */
	अगर (pkg_stats->rx_frames)
		pkg_stats->total_rx_match_ratio = (pkg_stats->matches * 100) /
			pkg_stats->rx_frames;

	pkg_stats->total_tx_rate = calc_rate(pkg_stats->jअगरfies_init, j,
					    pkg_stats->tx_frames);
	pkg_stats->total_rx_rate = calc_rate(pkg_stats->jअगरfies_init, j,
					    pkg_stats->rx_frames);

	/* calc current values */
	अगर (pkg_stats->rx_frames_delta)
		pkg_stats->current_rx_match_ratio =
			(pkg_stats->matches_delta * 100) /
			pkg_stats->rx_frames_delta;

	pkg_stats->current_tx_rate = calc_rate(0, HZ, pkg_stats->tx_frames_delta);
	pkg_stats->current_rx_rate = calc_rate(0, HZ, pkg_stats->rx_frames_delta);

	/* check / update maximum values */
	अगर (pkg_stats->max_tx_rate < pkg_stats->current_tx_rate)
		pkg_stats->max_tx_rate = pkg_stats->current_tx_rate;

	अगर (pkg_stats->max_rx_rate < pkg_stats->current_rx_rate)
		pkg_stats->max_rx_rate = pkg_stats->current_rx_rate;

	अगर (pkg_stats->max_rx_match_ratio < pkg_stats->current_rx_match_ratio)
		pkg_stats->max_rx_match_ratio = pkg_stats->current_rx_match_ratio;

	/* clear values क्रम 'current rate' calculation */
	pkg_stats->tx_frames_delta = 0;
	pkg_stats->rx_frames_delta = 0;
	pkg_stats->matches_delta   = 0;

	/* restart समयr (one second) */
	mod_समयr(&net->can.statसमयr, round_jअगरfies(jअगरfies + HZ));
पूर्ण

/*
 * proc पढ़ो functions
 */

अटल व्योम can_prपूर्णांक_rcvlist(काष्ठा seq_file *m, काष्ठा hlist_head *rx_list,
			      काष्ठा net_device *dev)
अणु
	काष्ठा receiver *r;

	hlist_क्रम_each_entry_rcu(r, rx_list, list) अणु
		अक्षर *fmt = (r->can_id & CAN_EFF_FLAG)?
			"   %-5s  %08x  %08x  %pK  %pK  %8ld  %s\n" :
			"   %-5s     %03x    %08x  %pK  %pK  %8ld  %s\n";

		seq_म_लिखो(m, fmt, DNAME(dev), r->can_id, r->mask,
				r->func, r->data, r->matches, r->ident);
	पूर्ण
पूर्ण

अटल व्योम can_prपूर्णांक_recv_banner(काष्ठा seq_file *m)
अणु
	/*
	 *                  can1.  00000000  00000000  00000000
	 *                 .......          0  tp20
	 */
	अगर (IS_ENABLED(CONFIG_64BIT))
		seq_माला_दो(m, "  device   can_id   can_mask      function          userdata       matches  ident\n");
	अन्यथा
		seq_माला_दो(m, "  device   can_id   can_mask  function  userdata   matches  ident\n");
पूर्ण

अटल पूर्णांक can_stats_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा net *net = m->निजी;
	काष्ठा can_pkg_stats *pkg_stats = net->can.pkg_stats;
	काष्ठा can_rcv_lists_stats *rcv_lists_stats = net->can.rcv_lists_stats;

	seq_अ_दो(m, '\n');
	seq_म_लिखो(m, " %8ld transmitted frames (TXF)\n", pkg_stats->tx_frames);
	seq_म_लिखो(m, " %8ld received frames (RXF)\n", pkg_stats->rx_frames);
	seq_म_लिखो(m, " %8ld matched frames (RXMF)\n", pkg_stats->matches);

	seq_अ_दो(m, '\n');

	अगर (net->can.statसमयr.function == can_stat_update) अणु
		seq_म_लिखो(m, " %8ld %% total match ratio (RXMR)\n",
				pkg_stats->total_rx_match_ratio);

		seq_म_लिखो(m, " %8ld frames/s total tx rate (TXR)\n",
				pkg_stats->total_tx_rate);
		seq_म_लिखो(m, " %8ld frames/s total rx rate (RXR)\n",
				pkg_stats->total_rx_rate);

		seq_अ_दो(m, '\n');

		seq_म_लिखो(m, " %8ld %% current match ratio (CRXMR)\n",
				pkg_stats->current_rx_match_ratio);

		seq_म_लिखो(m, " %8ld frames/s current tx rate (CTXR)\n",
				pkg_stats->current_tx_rate);
		seq_म_लिखो(m, " %8ld frames/s current rx rate (CRXR)\n",
				pkg_stats->current_rx_rate);

		seq_अ_दो(m, '\n');

		seq_म_लिखो(m, " %8ld %% max match ratio (MRXMR)\n",
				pkg_stats->max_rx_match_ratio);

		seq_म_लिखो(m, " %8ld frames/s max tx rate (MTXR)\n",
				pkg_stats->max_tx_rate);
		seq_म_लिखो(m, " %8ld frames/s max rx rate (MRXR)\n",
				pkg_stats->max_rx_rate);

		seq_अ_दो(m, '\n');
	पूर्ण

	seq_म_लिखो(m, " %8ld current receive list entries (CRCV)\n",
			rcv_lists_stats->rcv_entries);
	seq_म_लिखो(m, " %8ld maximum receive list entries (MRCV)\n",
			rcv_lists_stats->rcv_entries_max);

	अगर (rcv_lists_stats->stats_reset)
		seq_म_लिखो(m, "\n %8ld statistic resets (STR)\n",
				rcv_lists_stats->stats_reset);

	अगर (rcv_lists_stats->user_reset)
		seq_म_लिखो(m, " %8ld user statistic resets (USTR)\n",
				rcv_lists_stats->user_reset);

	seq_अ_दो(m, '\n');
	वापस 0;
पूर्ण

अटल पूर्णांक can_reset_stats_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा net *net = m->निजी;
	काष्ठा can_rcv_lists_stats *rcv_lists_stats = net->can.rcv_lists_stats;
	काष्ठा can_pkg_stats *pkg_stats = net->can.pkg_stats;

	user_reset = 1;

	अगर (net->can.statसमयr.function == can_stat_update) अणु
		seq_म_लिखो(m, "Scheduled statistic reset #%ld.\n",
				rcv_lists_stats->stats_reset + 1);
	पूर्ण अन्यथा अणु
		अगर (pkg_stats->jअगरfies_init != jअगरfies)
			can_init_stats(net);

		seq_म_लिखो(m, "Performed statistic reset #%ld.\n",
				rcv_lists_stats->stats_reset);
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम can_rcvlist_proc_show_one(काष्ठा seq_file *m, पूर्णांक idx,
					     काष्ठा net_device *dev,
					     काष्ठा can_dev_rcv_lists *dev_rcv_lists)
अणु
	अगर (!hlist_empty(&dev_rcv_lists->rx[idx])) अणु
		can_prपूर्णांक_recv_banner(m);
		can_prपूर्णांक_rcvlist(m, &dev_rcv_lists->rx[idx], dev);
	पूर्ण अन्यथा
		seq_म_लिखो(m, "  (%s: no entry)\n", DNAME(dev));

पूर्ण

अटल पूर्णांक can_rcvlist_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	/* द्विगुन cast to prevent GCC warning */
	पूर्णांक idx = (पूर्णांक)(दीर्घ)PDE_DATA(m->file->f_inode);
	काष्ठा net_device *dev;
	काष्ठा can_dev_rcv_lists *dev_rcv_lists;
	काष्ठा net *net = m->निजी;

	seq_म_लिखो(m, "\nreceive list '%s':\n", rx_list_name[idx]);

	rcu_पढ़ो_lock();

	/* receive list क्रम 'all' CAN devices (dev == शून्य) */
	dev_rcv_lists = net->can.rx_alldev_list;
	can_rcvlist_proc_show_one(m, idx, शून्य, dev_rcv_lists);

	/* receive list क्रम रेजिस्टरed CAN devices */
	क्रम_each_netdev_rcu(net, dev) अणु
		काष्ठा can_ml_priv *can_ml = can_get_ml_priv(dev);

		अगर (can_ml)
			can_rcvlist_proc_show_one(m, idx, dev,
						  &can_ml->dev_rcv_lists);
	पूर्ण

	rcu_पढ़ो_unlock();

	seq_अ_दो(m, '\n');
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम can_rcvlist_proc_show_array(काष्ठा seq_file *m,
					       काष्ठा net_device *dev,
					       काष्ठा hlist_head *rcv_array,
					       अचिन्हित पूर्णांक rcv_array_sz)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक all_empty = 1;

	/* check whether at least one list is non-empty */
	क्रम (i = 0; i < rcv_array_sz; i++)
		अगर (!hlist_empty(&rcv_array[i])) अणु
			all_empty = 0;
			अवरोध;
		पूर्ण

	अगर (!all_empty) अणु
		can_prपूर्णांक_recv_banner(m);
		क्रम (i = 0; i < rcv_array_sz; i++) अणु
			अगर (!hlist_empty(&rcv_array[i]))
				can_prपूर्णांक_rcvlist(m, &rcv_array[i], dev);
		पूर्ण
	पूर्ण अन्यथा
		seq_म_लिखो(m, "  (%s: no entry)\n", DNAME(dev));
पूर्ण

अटल पूर्णांक can_rcvlist_sff_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा net_device *dev;
	काष्ठा can_dev_rcv_lists *dev_rcv_lists;
	काष्ठा net *net = m->निजी;

	/* RX_SFF */
	seq_माला_दो(m, "\nreceive list 'rx_sff':\n");

	rcu_पढ़ो_lock();

	/* sff receive list क्रम 'all' CAN devices (dev == शून्य) */
	dev_rcv_lists = net->can.rx_alldev_list;
	can_rcvlist_proc_show_array(m, शून्य, dev_rcv_lists->rx_sff,
				    ARRAY_SIZE(dev_rcv_lists->rx_sff));

	/* sff receive list क्रम रेजिस्टरed CAN devices */
	क्रम_each_netdev_rcu(net, dev) अणु
		काष्ठा can_ml_priv *can_ml = can_get_ml_priv(dev);

		अगर (can_ml) अणु
			dev_rcv_lists = &can_ml->dev_rcv_lists;
			can_rcvlist_proc_show_array(m, dev, dev_rcv_lists->rx_sff,
						    ARRAY_SIZE(dev_rcv_lists->rx_sff));
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();

	seq_अ_दो(m, '\n');
	वापस 0;
पूर्ण

अटल पूर्णांक can_rcvlist_eff_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा net_device *dev;
	काष्ठा can_dev_rcv_lists *dev_rcv_lists;
	काष्ठा net *net = m->निजी;

	/* RX_EFF */
	seq_माला_दो(m, "\nreceive list 'rx_eff':\n");

	rcu_पढ़ो_lock();

	/* eff receive list क्रम 'all' CAN devices (dev == शून्य) */
	dev_rcv_lists = net->can.rx_alldev_list;
	can_rcvlist_proc_show_array(m, शून्य, dev_rcv_lists->rx_eff,
				    ARRAY_SIZE(dev_rcv_lists->rx_eff));

	/* eff receive list क्रम रेजिस्टरed CAN devices */
	क्रम_each_netdev_rcu(net, dev) अणु
		काष्ठा can_ml_priv *can_ml = can_get_ml_priv(dev);

		अगर (can_ml) अणु
			dev_rcv_lists = &can_ml->dev_rcv_lists;
			can_rcvlist_proc_show_array(m, dev, dev_rcv_lists->rx_eff,
						    ARRAY_SIZE(dev_rcv_lists->rx_eff));
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();

	seq_अ_दो(m, '\n');
	वापस 0;
पूर्ण

/*
 * can_init_proc - create मुख्य CAN proc directory and procfs entries
 */
व्योम can_init_proc(काष्ठा net *net)
अणु
	/* create /proc/net/can directory */
	net->can.proc_dir = proc_net_सूची_गढ़ो(net, "can", net->proc_net);

	अगर (!net->can.proc_dir) अणु
		prपूर्णांकk(KERN_INFO "can: failed to create /proc/net/can . "
			   "CONFIG_PROC_FS missing?\n");
		वापस;
	पूर्ण

	/* own procfs entries from the AF_CAN core */
	net->can.pde_stats = proc_create_net_single(CAN_PROC_STATS, 0644,
			net->can.proc_dir, can_stats_proc_show, शून्य);
	net->can.pde_reset_stats = proc_create_net_single(CAN_PROC_RESET_STATS,
			0644, net->can.proc_dir, can_reset_stats_proc_show,
			शून्य);
	net->can.pde_rcvlist_err = proc_create_net_single(CAN_PROC_RCVLIST_ERR,
			0644, net->can.proc_dir, can_rcvlist_proc_show,
			(व्योम *)RX_ERR);
	net->can.pde_rcvlist_all = proc_create_net_single(CAN_PROC_RCVLIST_ALL,
			0644, net->can.proc_dir, can_rcvlist_proc_show,
			(व्योम *)RX_ALL);
	net->can.pde_rcvlist_fil = proc_create_net_single(CAN_PROC_RCVLIST_FIL,
			0644, net->can.proc_dir, can_rcvlist_proc_show,
			(व्योम *)RX_FIL);
	net->can.pde_rcvlist_inv = proc_create_net_single(CAN_PROC_RCVLIST_INV,
			0644, net->can.proc_dir, can_rcvlist_proc_show,
			(व्योम *)RX_INV);
	net->can.pde_rcvlist_eff = proc_create_net_single(CAN_PROC_RCVLIST_EFF,
			0644, net->can.proc_dir, can_rcvlist_eff_proc_show, शून्य);
	net->can.pde_rcvlist_sff = proc_create_net_single(CAN_PROC_RCVLIST_SFF,
			0644, net->can.proc_dir, can_rcvlist_sff_proc_show, शून्य);
पूर्ण

/*
 * can_हटाओ_proc - हटाओ procfs entries and मुख्य CAN proc directory
 */
व्योम can_हटाओ_proc(काष्ठा net *net)
अणु
	अगर (!net->can.proc_dir)
		वापस;

	अगर (net->can.pde_stats)
		हटाओ_proc_entry(CAN_PROC_STATS, net->can.proc_dir);

	अगर (net->can.pde_reset_stats)
		हटाओ_proc_entry(CAN_PROC_RESET_STATS, net->can.proc_dir);

	अगर (net->can.pde_rcvlist_err)
		हटाओ_proc_entry(CAN_PROC_RCVLIST_ERR, net->can.proc_dir);

	अगर (net->can.pde_rcvlist_all)
		हटाओ_proc_entry(CAN_PROC_RCVLIST_ALL, net->can.proc_dir);

	अगर (net->can.pde_rcvlist_fil)
		हटाओ_proc_entry(CAN_PROC_RCVLIST_FIL, net->can.proc_dir);

	अगर (net->can.pde_rcvlist_inv)
		हटाओ_proc_entry(CAN_PROC_RCVLIST_INV, net->can.proc_dir);

	अगर (net->can.pde_rcvlist_eff)
		हटाओ_proc_entry(CAN_PROC_RCVLIST_EFF, net->can.proc_dir);

	अगर (net->can.pde_rcvlist_sff)
		हटाओ_proc_entry(CAN_PROC_RCVLIST_SFF, net->can.proc_dir);

	हटाओ_proc_entry("can", net->proc_net);
पूर्ण
