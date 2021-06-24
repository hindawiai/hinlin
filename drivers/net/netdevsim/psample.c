<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2021 Mellanox Technologies. All rights reserved */

#समावेश <linux/debugfs.h>
#समावेश <linux/err.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/inet.h>
#समावेश <linux/kernel.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/slab.h>
#समावेश <net/devlink.h>
#समावेश <net/ip.h>
#समावेश <net/psample.h>
#समावेश <uapi/linux/ip.h>
#समावेश <uapi/linux/udp.h>

#समावेश "netdevsim.h"

#घोषणा NSIM_PSAMPLE_REPORT_INTERVAL_MS	100
#घोषणा NSIM_PSAMPLE_INVALID_TC		0xFFFF
#घोषणा NSIM_PSAMPLE_L4_DATA_LEN	100

काष्ठा nsim_dev_psample अणु
	काष्ठा delayed_work psample_dw;
	काष्ठा dentry *ddir;
	काष्ठा psample_group *group;
	u32 rate;
	u32 group_num;
	u32 trunc_size;
	पूर्णांक in_अगरindex;
	पूर्णांक out_अगरindex;
	u16 out_tc;
	u64 out_tc_occ_max;
	u64 latency_max;
	bool is_active;
पूर्ण;

अटल काष्ठा sk_buff *nsim_dev_psample_skb_build(व्योम)
अणु
	पूर्णांक tot_len, data_len = NSIM_PSAMPLE_L4_DATA_LEN;
	काष्ठा sk_buff *skb;
	काष्ठा udphdr *udph;
	काष्ठा ethhdr *eth;
	काष्ठा iphdr *iph;

	skb = alloc_skb(NLMSG_GOODSIZE, GFP_KERNEL);
	अगर (!skb)
		वापस शून्य;
	tot_len = माप(काष्ठा iphdr) + माप(काष्ठा udphdr) + data_len;

	skb_reset_mac_header(skb);
	eth = skb_put(skb, माप(काष्ठा ethhdr));
	eth_अक्रमom_addr(eth->h_dest);
	eth_अक्रमom_addr(eth->h_source);
	eth->h_proto = htons(ETH_P_IP);
	skb->protocol = htons(ETH_P_IP);

	skb_set_network_header(skb, skb->len);
	iph = skb_put(skb, माप(काष्ठा iphdr));
	iph->protocol = IPPROTO_UDP;
	iph->saddr = in_aton("192.0.2.1");
	iph->daddr = in_aton("198.51.100.1");
	iph->version = 0x4;
	iph->frag_off = 0;
	iph->ihl = 0x5;
	iph->tot_len = htons(tot_len);
	iph->id = 0;
	iph->ttl = 100;
	iph->check = 0;
	iph->check = ip_fast_csum((अचिन्हित अक्षर *)iph, iph->ihl);

	skb_set_transport_header(skb, skb->len);
	udph = skb_put_zero(skb, माप(काष्ठा udphdr) + data_len);
	get_अक्रमom_bytes(&udph->source, माप(u16));
	get_अक्रमom_bytes(&udph->dest, माप(u16));
	udph->len = htons(माप(काष्ठा udphdr) + data_len);

	वापस skb;
पूर्ण

अटल व्योम nsim_dev_psample_md_prepare(स्थिर काष्ठा nsim_dev_psample *psample,
					काष्ठा psample_metadata *md,
					अचिन्हित पूर्णांक len)
अणु
	md->trunc_size = psample->trunc_size ? psample->trunc_size : len;
	md->in_अगरindex = psample->in_अगरindex;
	md->out_अगरindex = psample->out_अगरindex;

	अगर (psample->out_tc != NSIM_PSAMPLE_INVALID_TC) अणु
		md->out_tc = psample->out_tc;
		md->out_tc_valid = 1;
	पूर्ण

	अगर (psample->out_tc_occ_max) अणु
		u64 out_tc_occ;

		get_अक्रमom_bytes(&out_tc_occ, माप(u64));
		md->out_tc_occ = out_tc_occ & (psample->out_tc_occ_max - 1);
		md->out_tc_occ_valid = 1;
	पूर्ण

	अगर (psample->latency_max) अणु
		u64 latency;

		get_अक्रमom_bytes(&latency, माप(u64));
		md->latency = latency & (psample->latency_max - 1);
		md->latency_valid = 1;
	पूर्ण
पूर्ण

अटल व्योम nsim_dev_psample_report_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nsim_dev_psample *psample;
	काष्ठा psample_metadata md = अणुपूर्ण;
	काष्ठा sk_buff *skb;
	अचिन्हित दीर्घ delay;

	psample = container_of(work, काष्ठा nsim_dev_psample, psample_dw.work);

	skb = nsim_dev_psample_skb_build();
	अगर (!skb)
		जाओ out;

	nsim_dev_psample_md_prepare(psample, &md, skb->len);
	psample_sample_packet(psample->group, skb, psample->rate, &md);
	consume_skb(skb);

out:
	delay = msecs_to_jअगरfies(NSIM_PSAMPLE_REPORT_INTERVAL_MS);
	schedule_delayed_work(&psample->psample_dw, delay);
पूर्ण

अटल पूर्णांक nsim_dev_psample_enable(काष्ठा nsim_dev *nsim_dev)
अणु
	काष्ठा nsim_dev_psample *psample = nsim_dev->psample;
	काष्ठा devlink *devlink;
	अचिन्हित दीर्घ delay;

	अगर (psample->is_active)
		वापस -EBUSY;

	devlink = priv_to_devlink(nsim_dev);
	psample->group = psample_group_get(devlink_net(devlink),
					   psample->group_num);
	अगर (!psample->group)
		वापस -EINVAL;

	delay = msecs_to_jअगरfies(NSIM_PSAMPLE_REPORT_INTERVAL_MS);
	schedule_delayed_work(&psample->psample_dw, delay);

	psample->is_active = true;

	वापस 0;
पूर्ण

अटल पूर्णांक nsim_dev_psample_disable(काष्ठा nsim_dev *nsim_dev)
अणु
	काष्ठा nsim_dev_psample *psample = nsim_dev->psample;

	अगर (!psample->is_active)
		वापस -EINVAL;

	psample->is_active = false;

	cancel_delayed_work_sync(&psample->psample_dw);
	psample_group_put(psample->group);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार nsim_dev_psample_enable_ग_लिखो(काष्ठा file *file,
					     स्थिर अक्षर __user *data,
					     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा nsim_dev *nsim_dev = file->निजी_data;
	bool enable;
	पूर्णांक err;

	err = kstrtobool_from_user(data, count, &enable);
	अगर (err)
		वापस err;

	अगर (enable)
		err = nsim_dev_psample_enable(nsim_dev);
	अन्यथा
		err = nsim_dev_psample_disable(nsim_dev);

	वापस err ? err : count;
पूर्ण

अटल स्थिर काष्ठा file_operations nsim_psample_enable_fops = अणु
	.खोलो = simple_खोलो,
	.ग_लिखो = nsim_dev_psample_enable_ग_लिखो,
	.llseek = generic_file_llseek,
	.owner = THIS_MODULE,
पूर्ण;

पूर्णांक nsim_dev_psample_init(काष्ठा nsim_dev *nsim_dev)
अणु
	काष्ठा nsim_dev_psample *psample;
	पूर्णांक err;

	psample = kzalloc(माप(*psample), GFP_KERNEL);
	अगर (!psample)
		वापस -ENOMEM;
	nsim_dev->psample = psample;

	INIT_DELAYED_WORK(&psample->psample_dw, nsim_dev_psample_report_work);

	psample->ddir = debugfs_create_dir("psample", nsim_dev->ddir);
	अगर (IS_ERR(psample->ddir)) अणु
		err = PTR_ERR(psample->ddir);
		जाओ err_psample_मुक्त;
	पूर्ण

	/* Populate sampling parameters with sane शेषs. */
	psample->rate = 100;
	debugfs_create_u32("rate", 0600, psample->ddir, &psample->rate);

	psample->group_num = 10;
	debugfs_create_u32("group_num", 0600, psample->ddir,
			   &psample->group_num);

	psample->trunc_size = 0;
	debugfs_create_u32("trunc_size", 0600, psample->ddir,
			   &psample->trunc_size);

	psample->in_अगरindex = 1;
	debugfs_create_u32("in_ifindex", 0600, psample->ddir,
			   &psample->in_अगरindex);

	psample->out_अगरindex = 2;
	debugfs_create_u32("out_ifindex", 0600, psample->ddir,
			   &psample->out_अगरindex);

	psample->out_tc = 0;
	debugfs_create_u16("out_tc", 0600, psample->ddir, &psample->out_tc);

	psample->out_tc_occ_max = 10000;
	debugfs_create_u64("out_tc_occ_max", 0600, psample->ddir,
			   &psample->out_tc_occ_max);

	psample->latency_max = 50;
	debugfs_create_u64("latency_max", 0600, psample->ddir,
			   &psample->latency_max);

	debugfs_create_file("enable", 0200, psample->ddir, nsim_dev,
			    &nsim_psample_enable_fops);

	वापस 0;

err_psample_मुक्त:
	kमुक्त(nsim_dev->psample);
	वापस err;
पूर्ण

व्योम nsim_dev_psample_निकास(काष्ठा nsim_dev *nsim_dev)
अणु
	debugfs_हटाओ_recursive(nsim_dev->psample->ddir);
	अगर (nsim_dev->psample->is_active) अणु
		cancel_delayed_work_sync(&nsim_dev->psample->psample_dw);
		psample_group_put(nsim_dev->psample->group);
	पूर्ण
	kमुक्त(nsim_dev->psample);
पूर्ण
