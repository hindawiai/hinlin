<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ":%s: " fmt, __func__

#अगर_घोषित CONFIG_PROC_FS
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/seq_file.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/aपंचांगmpc.h>
#समावेश <linux/aपंचांग.h>
#समावेश <linux/gfp.h>
#समावेश "mpc.h"
#समावेश "mpoa_caches.h"

/*
 * mpoa_proc.c: Implementation MPOA client's proc
 * file प्रणाली statistics
 */

#अगर 1
#घोषणा dprपूर्णांकk(क्रमmat, args...)					\
	prपूर्णांकk(KERN_DEBUG "mpoa:%s: " क्रमmat, __खाता__, ##args)  /* debug */
#अन्यथा
#घोषणा dprपूर्णांकk(क्रमmat, args...)					\
	करो अणु अगर (0)							\
		prपूर्णांकk(KERN_DEBUG "mpoa:%s: " क्रमmat, __खाता__, ##args);\
	पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर 0
#घोषणा ddprपूर्णांकk(क्रमmat, args...)					\
	prपूर्णांकk(KERN_DEBUG "mpoa:%s: " क्रमmat, __खाता__, ##args)  /* debug */
#अन्यथा
#घोषणा ddprपूर्णांकk(क्रमmat, args...)					\
	करो अणु अगर (0)							\
		prपूर्णांकk(KERN_DEBUG "mpoa:%s: " क्रमmat, __खाता__, ##args);\
	पूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा STAT_खाता_NAME "mpc"     /* Our statistic file's name */

बाह्य काष्ठा mpoa_client *mpcs;
बाह्य काष्ठा proc_dir_entry *aपंचांग_proc_root;  /* from proc.c. */

अटल पूर्णांक proc_mpc_खोलो(काष्ठा inode *inode, काष्ठा file *file);
अटल sमाप_प्रकार proc_mpc_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buff,
			      माप_प्रकार nbytes, loff_t *ppos);

अटल पूर्णांक parse_qos(स्थिर अक्षर *buff);

अटल स्थिर काष्ठा proc_ops mpc_proc_ops = अणु
	.proc_खोलो	= proc_mpc_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_ग_लिखो	= proc_mpc_ग_लिखो,
	.proc_release	= seq_release,
पूर्ण;

/*
 * Returns the state of an ingress cache entry as a string
 */
अटल स्थिर अक्षर *ingress_state_string(पूर्णांक state)
अणु
	चयन (state) अणु
	हाल INGRESS_RESOLVING:
		वापस "resolving  ";
	हाल INGRESS_RESOLVED:
		वापस "resolved   ";
	हाल INGRESS_INVALID:
		वापस "invalid    ";
	हाल INGRESS_REFRESHING:
		वापस "refreshing ";
	पूर्ण

	वापस "";
पूर्ण

/*
 * Returns the state of an egress cache entry as a string
 */
अटल स्थिर अक्षर *egress_state_string(पूर्णांक state)
अणु
	चयन (state) अणु
	हाल EGRESS_RESOLVED:
		वापस "resolved   ";
	हाल EGRESS_PURGE:
		वापस "purge      ";
	हाल EGRESS_INVALID:
		वापस "invalid    ";
	पूर्ण

	वापस "";
पूर्ण

/*
 * FIXME: mpcs (and per-mpc lists) have no locking whatsoever.
 */

अटल व्योम *mpc_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	loff_t l = *pos;
	काष्ठा mpoa_client *mpc;

	अगर (!l--)
		वापस SEQ_START_TOKEN;
	क्रम (mpc = mpcs; mpc; mpc = mpc->next)
		अगर (!l--)
			वापस mpc;
	वापस शून्य;
पूर्ण

अटल व्योम *mpc_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	काष्ठा mpoa_client *p = v;
	(*pos)++;
	वापस v == SEQ_START_TOKEN ? mpcs : p->next;
पूर्ण

अटल व्योम mpc_stop(काष्ठा seq_file *m, व्योम *v)
अणु
पूर्ण

/*
 * READING function - called when the /proc/aपंचांग/mpoa file is पढ़ो from.
 */
अटल पूर्णांक mpc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा mpoa_client *mpc = v;
	पूर्णांक i;
	in_cache_entry *in_entry;
	eg_cache_entry *eg_entry;
	समय64_t now;
	अचिन्हित अक्षर ip_string[16];

	अगर (v == SEQ_START_TOKEN) अणु
		aपंचांग_mpoa_disp_qos(m);
		वापस 0;
	पूर्ण

	seq_म_लिखो(m, "\nInterface %d:\n\n", mpc->dev_num);
	seq_म_लिखो(m, "Ingress Entries:\nIP address      State      Holding time  Packets fwded  VPI  VCI\n");
	now = kसमय_get_seconds();

	क्रम (in_entry = mpc->in_cache; in_entry; in_entry = in_entry->next) अणु
		अचिन्हित दीर्घ seconds_delta = now - in_entry->समय;

		प्र_लिखो(ip_string, "%pI4", &in_entry->ctrl_info.in_dst_ip);
		seq_म_लिखो(m, "%-16s%s%-14lu%-12u",
			   ip_string,
			   ingress_state_string(in_entry->entry_state),
			   in_entry->ctrl_info.holding_समय -
			   seconds_delta,
			   in_entry->packets_fwded);
		अगर (in_entry->लघुcut)
			seq_म_लिखो(m, "   %-3d  %-3d",
				   in_entry->लघुcut->vpi,
				   in_entry->लघुcut->vci);
		seq_म_लिखो(m, "\n");
	पूर्ण

	seq_म_लिखो(m, "\n");
	seq_म_लिखो(m, "Egress Entries:\nIngress MPC ATM addr\nCache-id        State      Holding time  Packets recvd  Latest IP addr   VPI VCI\n");
	क्रम (eg_entry = mpc->eg_cache; eg_entry; eg_entry = eg_entry->next) अणु
		अचिन्हित अक्षर *p = eg_entry->ctrl_info.in_MPC_data_ATM_addr;
		अचिन्हित दीर्घ seconds_delta = now - eg_entry->समय;

		क्रम (i = 0; i < ATM_ESA_LEN; i++)
			seq_म_लिखो(m, "%02x", p[i]);
		seq_म_लिखो(m, "\n%-16lu%s%-14lu%-15u",
			   (अचिन्हित दीर्घ)ntohl(eg_entry->ctrl_info.cache_id),
			   egress_state_string(eg_entry->entry_state),
			   (eg_entry->ctrl_info.holding_समय - seconds_delta),
			   eg_entry->packets_rcvd);

		/* latest IP address */
		प्र_लिखो(ip_string, "%pI4", &eg_entry->latest_ip_addr);
		seq_म_लिखो(m, "%-16s", ip_string);

		अगर (eg_entry->लघुcut)
			seq_म_लिखो(m, " %-3d %-3d",
				   eg_entry->लघुcut->vpi,
				   eg_entry->लघुcut->vci);
		seq_म_लिखो(m, "\n");
	पूर्ण
	seq_म_लिखो(m, "\n");
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations mpc_op = अणु
	.start =	mpc_start,
	.next =		mpc_next,
	.stop =		mpc_stop,
	.show =		mpc_show
पूर्ण;

अटल पूर्णांक proc_mpc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस seq_खोलो(file, &mpc_op);
पूर्ण

अटल sमाप_प्रकार proc_mpc_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buff,
			      माप_प्रकार nbytes, loff_t *ppos)
अणु
	अक्षर *page, *p;
	अचिन्हित पूर्णांक len;

	अगर (nbytes == 0)
		वापस 0;

	अगर (nbytes >= PAGE_SIZE)
		nbytes = PAGE_SIZE-1;

	page = (अक्षर *)__get_मुक्त_page(GFP_KERNEL);
	अगर (!page)
		वापस -ENOMEM;

	क्रम (p = page, len = 0; len < nbytes; p++, len++) अणु
		अगर (get_user(*p, buff++)) अणु
			मुक्त_page((अचिन्हित दीर्घ)page);
			वापस -EFAULT;
		पूर्ण
		अगर (*p == '\0' || *p == '\n')
			अवरोध;
	पूर्ण

	*p = '\0';

	अगर (!parse_qos(page))
		prपूर्णांकk("mpoa: proc_mpc_write: could not parse '%s'\n", page);

	मुक्त_page((अचिन्हित दीर्घ)page);

	वापस len;
पूर्ण

अटल पूर्णांक parse_qos(स्थिर अक्षर *buff)
अणु
	/* possible lines look like this
	 * add 130.230.54.142 tx=max_pcr,max_sdu rx=max_pcr,max_sdu
	 */
	अचिन्हित अक्षर ip[4];
	पूर्णांक tx_pcr, tx_sdu, rx_pcr, rx_sdu;
	__be32 ipaddr;
	काष्ठा aपंचांग_qos qos;

	स_रखो(&qos, 0, माप(काष्ठा aपंचांग_qos));

	अगर (माला_पूछो(buff, "del %hhu.%hhu.%hhu.%hhu",
			ip, ip+1, ip+2, ip+3) == 4) अणु
		ipaddr = *(__be32 *)ip;
		वापस aपंचांग_mpoa_delete_qos(aपंचांग_mpoa_search_qos(ipaddr));
	पूर्ण

	अगर (माला_पूछो(buff, "add %hhu.%hhu.%hhu.%hhu tx=%d,%d rx=tx",
			ip, ip+1, ip+2, ip+3, &tx_pcr, &tx_sdu) == 6) अणु
		rx_pcr = tx_pcr;
		rx_sdu = tx_sdu;
	पूर्ण अन्यथा अगर (माला_पूछो(buff, "add %hhu.%hhu.%hhu.%hhu tx=%d,%d rx=%d,%d",
		ip, ip+1, ip+2, ip+3, &tx_pcr, &tx_sdu, &rx_pcr, &rx_sdu) != 8)
		वापस 0;

	ipaddr = *(__be32 *)ip;
	qos.txtp.traffic_class = ATM_CBR;
	qos.txtp.max_pcr = tx_pcr;
	qos.txtp.max_sdu = tx_sdu;
	qos.rxtp.traffic_class = ATM_CBR;
	qos.rxtp.max_pcr = rx_pcr;
	qos.rxtp.max_sdu = rx_sdu;
	qos.aal = ATM_AAL5;
	dprपूर्णांकk("parse_qos(): setting qos parameters to tx=%d,%d rx=%d,%d\n",
		qos.txtp.max_pcr, qos.txtp.max_sdu,
		qos.rxtp.max_pcr, qos.rxtp.max_sdu);

	aपंचांग_mpoa_add_qos(ipaddr, &qos);
	वापस 1;
पूर्ण

/*
 * INITIALIZATION function - called when module is initialized/loaded.
 */
पूर्णांक mpc_proc_init(व्योम)
अणु
	काष्ठा proc_dir_entry *p;

	p = proc_create(STAT_खाता_NAME, 0, aपंचांग_proc_root, &mpc_proc_ops);
	अगर (!p) अणु
		pr_err("Unable to initialize /proc/atm/%s\n", STAT_खाता_NAME);
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * DELETING function - called when module is हटाओd.
 */
व्योम mpc_proc_clean(व्योम)
अणु
	हटाओ_proc_entry(STAT_खाता_NAME, aपंचांग_proc_root);
पूर्ण

#पूर्ण_अगर /* CONFIG_PROC_FS */
