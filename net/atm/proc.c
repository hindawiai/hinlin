<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* net/aपंचांग/proc.c - ATM /proc पूर्णांकerface
 *
 * Written 1995-2000 by Werner Almesberger, EPFL LRC/ICA
 *
 * seq_file api usage by romieu@fr.zoreil.com
 *
 * Evaluating the efficiency of the whole thing अगर left as an exercise to
 * the पढ़ोer.
 */

#समावेश <linux/module.h> /* क्रम EXPORT_SYMBOL */
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/fs.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/aपंचांग.h>
#समावेश <linux/aपंचांगdev.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/aपंचांगclip.h>
#समावेश <linux/init.h> /* क्रम __init */
#समावेश <linux/slab.h>
#समावेश <net/net_namespace.h>
#समावेश <net/aपंचांगclip.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/param.h> /* क्रम HZ */
#समावेश <linux/atomic.h>
#समावेश "resources.h"
#समावेश "common.h" /* aपंचांग_proc_init prototype */
#समावेश "signaling.h" /* to get sigd - ugly too */

अटल sमाप_प्रकार proc_dev_aपंचांग_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				 माप_प्रकार count, loff_t *pos);

अटल स्थिर काष्ठा proc_ops aपंचांग_dev_proc_ops = अणु
	.proc_पढ़ो	= proc_dev_aपंचांग_पढ़ो,
	.proc_lseek	= noop_llseek,
पूर्ण;

अटल व्योम add_stats(काष्ठा seq_file *seq, स्थिर अक्षर *aal,
  स्थिर काष्ठा k_aपंचांग_aal_stats *stats)
अणु
	seq_म_लिखो(seq, "%s ( %d %d %d %d %d )", aal,
		   atomic_पढ़ो(&stats->tx), atomic_पढ़ो(&stats->tx_err),
		   atomic_पढ़ो(&stats->rx), atomic_पढ़ो(&stats->rx_err),
		   atomic_पढ़ो(&stats->rx_drop));
पूर्ण

अटल व्योम aपंचांग_dev_info(काष्ठा seq_file *seq, स्थिर काष्ठा aपंचांग_dev *dev)
अणु
	पूर्णांक i;

	seq_म_लिखो(seq, "%3d %-8s", dev->number, dev->type);
	क्रम (i = 0; i < ESI_LEN; i++)
		seq_म_लिखो(seq, "%02x", dev->esi[i]);
	seq_माला_दो(seq, "  ");
	add_stats(seq, "0", &dev->stats.aal0);
	seq_माला_दो(seq, "  ");
	add_stats(seq, "5", &dev->stats.aal5);
	seq_म_लिखो(seq, "\t[%d]", refcount_पढ़ो(&dev->refcnt));
	seq_अ_दो(seq, '\n');
पूर्ण

काष्ठा vcc_state अणु
	पूर्णांक bucket;
	काष्ठा sock *sk;
पूर्ण;

अटल अंतरभूत पूर्णांक compare_family(काष्ठा sock *sk, पूर्णांक family)
अणु
	वापस !family || (sk->sk_family == family);
पूर्ण

अटल पूर्णांक __vcc_walk(काष्ठा sock **sock, पूर्णांक family, पूर्णांक *bucket, loff_t l)
अणु
	काष्ठा sock *sk = *sock;

	अगर (sk == SEQ_START_TOKEN) अणु
		क्रम (*bucket = 0; *bucket < VCC_HTABLE_SIZE; ++*bucket) अणु
			काष्ठा hlist_head *head = &vcc_hash[*bucket];

			sk = hlist_empty(head) ? शून्य : __sk_head(head);
			अगर (sk)
				अवरोध;
		पूर्ण
		l--;
	पूर्ण
try_again:
	क्रम (; sk; sk = sk_next(sk)) अणु
		l -= compare_family(sk, family);
		अगर (l < 0)
			जाओ out;
	पूर्ण
	अगर (!sk && ++*bucket < VCC_HTABLE_SIZE) अणु
		sk = sk_head(&vcc_hash[*bucket]);
		जाओ try_again;
	पूर्ण
	sk = SEQ_START_TOKEN;
out:
	*sock = sk;
	वापस (l < 0);
पूर्ण

अटल अंतरभूत व्योम *vcc_walk(काष्ठा seq_file *seq, loff_t l)
अणु
	काष्ठा vcc_state *state = seq->निजी;
	पूर्णांक family = (uपूर्णांकptr_t)(PDE_DATA(file_inode(seq->file)));

	वापस __vcc_walk(&state->sk, family, &state->bucket, l) ?
	       state : शून्य;
पूर्ण

अटल व्योम *vcc_seq_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(vcc_sklist_lock)
अणु
	काष्ठा vcc_state *state = seq->निजी;
	loff_t left = *pos;

	पढ़ो_lock(&vcc_sklist_lock);
	state->sk = SEQ_START_TOKEN;
	वापस left ? vcc_walk(seq, left) : SEQ_START_TOKEN;
पूर्ण

अटल व्योम vcc_seq_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(vcc_sklist_lock)
अणु
	पढ़ो_unlock(&vcc_sklist_lock);
पूर्ण

अटल व्योम *vcc_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	v = vcc_walk(seq, 1);
	(*pos)++;
	वापस v;
पूर्ण

अटल व्योम pvc_info(काष्ठा seq_file *seq, काष्ठा aपंचांग_vcc *vcc)
अणु
	अटल स्थिर अक्षर *स्थिर class_name[] = अणु
		"off", "UBR", "CBR", "VBR", "ABR"पूर्ण;
	अटल स्थिर अक्षर *स्थिर aal_name[] = अणु
		"---",	"1",	"2",	"3/4",	/*  0- 3 */
		"???",	"5",	"???",	"???",	/*  4- 7 */
		"???",	"???",	"???",	"???",	/*  8-11 */
		"???",	"0",	"???",	"???"पूर्ण;	/* 12-15 */

	seq_म_लिखो(seq, "%3d %3d %5d %-3s %7d %-5s %7d %-6s",
		   vcc->dev->number, vcc->vpi, vcc->vci,
		   vcc->qos.aal >= ARRAY_SIZE(aal_name) ? "err" :
		   aal_name[vcc->qos.aal], vcc->qos.rxtp.min_pcr,
		   class_name[vcc->qos.rxtp.traffic_class],
		   vcc->qos.txtp.min_pcr,
		   class_name[vcc->qos.txtp.traffic_class]);
	अगर (test_bit(ATM_VF_IS_CLIP, &vcc->flags)) अणु
		काष्ठा clip_vcc *clip_vcc = CLIP_VCC(vcc);
		काष्ठा net_device *dev;

		dev = clip_vcc->entry ? clip_vcc->entry->neigh->dev : शून्य;
		seq_म_लिखो(seq, "CLIP, Itf:%s, Encap:",
		    dev ? dev->name : "none?");
		seq_म_लिखो(seq, "%s", clip_vcc->encap ? "LLC/SNAP" : "None");
	पूर्ण
	seq_अ_दो(seq, '\n');
पूर्ण

अटल स्थिर अक्षर *vcc_state(काष्ठा aपंचांग_vcc *vcc)
अणु
	अटल स्थिर अक्षर *स्थिर map[] = अणु ATM_VS2TXT_MAP पूर्ण;

	वापस map[ATM_VF2VS(vcc->flags)];
पूर्ण

अटल व्योम vcc_info(काष्ठा seq_file *seq, काष्ठा aपंचांग_vcc *vcc)
अणु
	काष्ठा sock *sk = sk_aपंचांग(vcc);

	seq_म_लिखो(seq, "%pK ", vcc);
	अगर (!vcc->dev)
		seq_म_लिखो(seq, "Unassigned    ");
	अन्यथा
		seq_म_लिखो(seq, "%3d %3d %5d ", vcc->dev->number, vcc->vpi,
			vcc->vci);
	चयन (sk->sk_family) अणु
	हाल AF_ATMPVC:
		seq_म_लिखो(seq, "PVC");
		अवरोध;
	हाल AF_ATMSVC:
		seq_म_लिखो(seq, "SVC");
		अवरोध;
	शेष:
		seq_म_लिखो(seq, "%3d", sk->sk_family);
	पूर्ण
	seq_म_लिखो(seq, " %04lx  %5d %7d/%7d %7d/%7d [%d]\n",
		   vcc->flags, sk->sk_err,
		   sk_wmem_alloc_get(sk), sk->sk_sndbuf,
		   sk_rmem_alloc_get(sk), sk->sk_rcvbuf,
		   refcount_पढ़ो(&sk->sk_refcnt));
पूर्ण

अटल व्योम svc_info(काष्ठा seq_file *seq, काष्ठा aपंचांग_vcc *vcc)
अणु
	अगर (!vcc->dev)
		seq_म_लिखो(seq, माप(व्योम *) == 4 ?
			   "N/A@%pK%10s" : "N/A@%pK%2s", vcc, "");
	अन्यथा
		seq_म_लिखो(seq, "%3d %3d %5d         ",
			   vcc->dev->number, vcc->vpi, vcc->vci);
	seq_म_लिखो(seq, "%-10s ", vcc_state(vcc));
	seq_म_लिखो(seq, "%s%s", vcc->remote.sas_addr.pub,
	    *vcc->remote.sas_addr.pub && *vcc->remote.sas_addr.prv ? "+" : "");
	अगर (*vcc->remote.sas_addr.prv) अणु
		पूर्णांक i;

		क्रम (i = 0; i < ATM_ESA_LEN; i++)
			seq_म_लिखो(seq, "%02x", vcc->remote.sas_addr.prv[i]);
	पूर्ण
	seq_अ_दो(seq, '\n');
पूर्ण

अटल पूर्णांक aपंचांग_dev_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	अटल अक्षर aपंचांग_dev_banner[] =
		"Itf Type    ESI/\"MAC\"addr "
		"AAL(TX,err,RX,err,drop) ...               [refcnt]\n";

	अगर (v == &aपंचांग_devs)
		seq_माला_दो(seq, aपंचांग_dev_banner);
	अन्यथा अणु
		काष्ठा aपंचांग_dev *dev = list_entry(v, काष्ठा aपंचांग_dev, dev_list);

		aपंचांग_dev_info(seq, dev);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations aपंचांग_dev_seq_ops = अणु
	.start	= aपंचांग_dev_seq_start,
	.next	= aपंचांग_dev_seq_next,
	.stop	= aपंचांग_dev_seq_stop,
	.show	= aपंचांग_dev_seq_show,
पूर्ण;

अटल पूर्णांक pvc_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	अटल अक्षर aपंचांग_pvc_banner[] =
		"Itf VPI VCI   AAL RX(PCR,Class) TX(PCR,Class)\n";

	अगर (v == SEQ_START_TOKEN)
		seq_माला_दो(seq, aपंचांग_pvc_banner);
	अन्यथा अणु
		काष्ठा vcc_state *state = seq->निजी;
		काष्ठा aपंचांग_vcc *vcc = aपंचांग_sk(state->sk);

		pvc_info(seq, vcc);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations pvc_seq_ops = अणु
	.start	= vcc_seq_start,
	.next	= vcc_seq_next,
	.stop	= vcc_seq_stop,
	.show	= pvc_seq_show,
पूर्ण;

अटल पूर्णांक vcc_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	अगर (v == SEQ_START_TOKEN) अणु
		seq_म_लिखो(seq, माप(व्योम *) == 4 ? "%-8s%s" : "%-16s%s",
			"Address ", "Itf VPI VCI   Fam Flags Reply "
			"Send buffer     Recv buffer      [refcnt]\n");
	पूर्ण अन्यथा अणु
		काष्ठा vcc_state *state = seq->निजी;
		काष्ठा aपंचांग_vcc *vcc = aपंचांग_sk(state->sk);

		vcc_info(seq, vcc);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations vcc_seq_ops = अणु
	.start	= vcc_seq_start,
	.next	= vcc_seq_next,
	.stop	= vcc_seq_stop,
	.show	= vcc_seq_show,
पूर्ण;

अटल पूर्णांक svc_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	अटल स्थिर अक्षर aपंचांग_svc_banner[] =
		"Itf VPI VCI           State      Remote\n";

	अगर (v == SEQ_START_TOKEN)
		seq_माला_दो(seq, aपंचांग_svc_banner);
	अन्यथा अणु
		काष्ठा vcc_state *state = seq->निजी;
		काष्ठा aपंचांग_vcc *vcc = aपंचांग_sk(state->sk);

		svc_info(seq, vcc);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations svc_seq_ops = अणु
	.start	= vcc_seq_start,
	.next	= vcc_seq_next,
	.stop	= vcc_seq_stop,
	.show	= svc_seq_show,
पूर्ण;

अटल sमाप_प्रकार proc_dev_aपंचांग_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				 माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा aपंचांग_dev *dev;
	अचिन्हित दीर्घ page;
	पूर्णांक length;

	अगर (count == 0)
		वापस 0;
	page = get_zeroed_page(GFP_KERNEL);
	अगर (!page)
		वापस -ENOMEM;
	dev = PDE_DATA(file_inode(file));
	अगर (!dev->ops->proc_पढ़ो)
		length = -EINVAL;
	अन्यथा अणु
		length = dev->ops->proc_पढ़ो(dev, pos, (अक्षर *)page);
		अगर (length > count)
			length = -EINVAL;
	पूर्ण
	अगर (length >= 0) अणु
		अगर (copy_to_user(buf, (अक्षर *)page, length))
			length = -EFAULT;
		(*pos)++;
	पूर्ण
	मुक्त_page(page);
	वापस length;
पूर्ण

काष्ठा proc_dir_entry *aपंचांग_proc_root;
EXPORT_SYMBOL(aपंचांग_proc_root);


पूर्णांक aपंचांग_proc_dev_रेजिस्टर(काष्ठा aपंचांग_dev *dev)
अणु
	पूर्णांक error;

	/* No proc info */
	अगर (!dev->ops->proc_पढ़ो)
		वापस 0;

	error = -ENOMEM;
	dev->proc_name = kaप्र_लिखो(GFP_KERNEL, "%s:%d", dev->type, dev->number);
	अगर (!dev->proc_name)
		जाओ err_out;

	dev->proc_entry = proc_create_data(dev->proc_name, 0, aपंचांग_proc_root,
					   &aपंचांग_dev_proc_ops, dev);
	अगर (!dev->proc_entry)
		जाओ err_मुक्त_name;
	वापस 0;

err_मुक्त_name:
	kमुक्त(dev->proc_name);
err_out:
	वापस error;
पूर्ण

व्योम aपंचांग_proc_dev_deरेजिस्टर(काष्ठा aपंचांग_dev *dev)
अणु
	अगर (!dev->ops->proc_पढ़ो)
		वापस;

	हटाओ_proc_entry(dev->proc_name, aपंचांग_proc_root);
	kमुक्त(dev->proc_name);
पूर्ण

पूर्णांक __init aपंचांग_proc_init(व्योम)
अणु
	aपंचांग_proc_root = proc_net_सूची_गढ़ो(&init_net, "atm", init_net.proc_net);
	अगर (!aपंचांग_proc_root)
		वापस -ENOMEM;
	proc_create_seq("devices", 0444, aपंचांग_proc_root, &aपंचांग_dev_seq_ops);
	proc_create_seq_निजी("pvc", 0444, aपंचांग_proc_root, &pvc_seq_ops,
			माप(काष्ठा vcc_state), (व्योम *)(uपूर्णांकptr_t)PF_ATMPVC);
	proc_create_seq_निजी("svc", 0444, aपंचांग_proc_root, &svc_seq_ops,
			माप(काष्ठा vcc_state), (व्योम *)(uपूर्णांकptr_t)PF_ATMSVC);
	proc_create_seq_निजी("vc", 0444, aपंचांग_proc_root, &vcc_seq_ops,
			माप(काष्ठा vcc_state), शून्य);
	वापस 0;
पूर्ण

व्योम aपंचांग_proc_निकास(व्योम)
अणु
	हटाओ_proc_subtree("atm", init_net.proc_net);
पूर्ण
