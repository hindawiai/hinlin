<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/fs.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <यंत्र/octeon/octeon.h>
#समावेश <यंत्र/octeon/cvmx-ciu-defs.h>
#समावेश <यंत्र/octeon/cvmx.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/seq_file.h>

#घोषणा TIMER_NUM 3

अटल bool reset_stats;

काष्ठा latency_info अणु
	u64 io_पूर्णांकerval;
	u64 cpu_पूर्णांकerval;
	u64 समयr_start1;
	u64 समयr_start2;
	u64 max_latency;
	u64 min_latency;
	u64 latency_sum;
	u64 average_latency;
	u64 पूर्णांकerrupt_cnt;
पूर्ण;

अटल काष्ठा latency_info li;
अटल काष्ठा dentry *dir;

अटल पूर्णांक show_latency(काष्ठा seq_file *m, व्योम *v)
अणु
	u64 cpuclk, avg, max, min;
	काष्ठा latency_info curr_li = li;

	cpuclk = octeon_get_घड़ी_rate();

	max = (curr_li.max_latency * 1000000000) / cpuclk;
	min = (curr_li.min_latency * 1000000000) / cpuclk;
	avg = (curr_li.latency_sum * 1000000000) / (cpuclk * curr_li.पूर्णांकerrupt_cnt);

	seq_म_लिखो(m, "cnt: %10lld, avg: %7lld ns, max: %7lld ns, min: %7lld ns\n",
		   curr_li.पूर्णांकerrupt_cnt, avg, max, min);
	वापस 0;
पूर्ण

अटल पूर्णांक oct_ilm_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, show_latency, शून्य);
पूर्ण

अटल स्थिर काष्ठा file_operations oct_ilm_ops = अणु
	.खोलो = oct_ilm_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = single_release,
पूर्ण;

अटल पूर्णांक reset_statistics(व्योम *data, u64 value)
अणु
	reset_stats = true;
	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(reset_statistics_ops, शून्य, reset_statistics, "%llu\n");

अटल व्योम init_debugfs(व्योम)
अणु
	dir = debugfs_create_dir("oct_ilm", 0);
	debugfs_create_file("statistics", 0222, dir, शून्य, &oct_ilm_ops);
	debugfs_create_file("reset", 0222, dir, शून्य, &reset_statistics_ops);
पूर्ण

अटल व्योम init_latency_info(काष्ठा latency_info *li, पूर्णांक startup)
अणु
	/* पूर्णांकerval in milli seconds after which the पूर्णांकerrupt will
	 * be triggered
	 */
	पूर्णांक पूर्णांकerval = 1;

	अगर (startup) अणु
		/* Calculating by the amounts io घड़ी and cpu घड़ी would
		 *  increment in पूर्णांकerval amount of ms
		 */
		li->io_पूर्णांकerval = (octeon_get_io_घड़ी_rate() * पूर्णांकerval) / 1000;
		li->cpu_पूर्णांकerval = (octeon_get_घड़ी_rate() * पूर्णांकerval) / 1000;
	पूर्ण
	li->समयr_start1 = 0;
	li->समयr_start2 = 0;
	li->max_latency = 0;
	li->min_latency = (u64)-1;
	li->latency_sum = 0;
	li->पूर्णांकerrupt_cnt = 0;
पूर्ण


अटल व्योम start_समयr(पूर्णांक समयr, u64 पूर्णांकerval)
अणु
	जोड़ cvmx_ciu_timx timx;
	अचिन्हित दीर्घ flags;

	timx.u64 = 0;
	timx.s.one_shot = 1;
	timx.s.len = पूर्णांकerval;
	raw_local_irq_save(flags);
	li.समयr_start1 = पढ़ो_c0_cvmcount();
	cvmx_ग_लिखो_csr(CVMX_CIU_TIMX(समयr), timx.u64);
	/* Read it back to क्रमce रुको until रेजिस्टर is written. */
	timx.u64 = cvmx_पढ़ो_csr(CVMX_CIU_TIMX(समयr));
	li.समयr_start2 = पढ़ो_c0_cvmcount();
	raw_local_irq_restore(flags);
पूर्ण


अटल irqवापस_t cvm_oct_ciu_समयr_पूर्णांकerrupt(पूर्णांक cpl, व्योम *dev_id)
अणु
	u64 last_latency;
	u64 last_पूर्णांक_cnt;

	अगर (reset_stats) अणु
		init_latency_info(&li, 0);
		reset_stats = false;
	पूर्ण अन्यथा अणु
		last_पूर्णांक_cnt = पढ़ो_c0_cvmcount();
		last_latency = last_पूर्णांक_cnt - (li.समयr_start1 + li.cpu_पूर्णांकerval);
		li.पूर्णांकerrupt_cnt++;
		li.latency_sum += last_latency;
		अगर (last_latency > li.max_latency)
			li.max_latency = last_latency;
		अगर (last_latency < li.min_latency)
			li.min_latency = last_latency;
	पूर्ण
	start_समयr(TIMER_NUM, li.io_पूर्णांकerval);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम disable_समयr(पूर्णांक समयr)
अणु
	जोड़ cvmx_ciu_timx timx;

	timx.s.one_shot = 0;
	timx.s.len = 0;
	cvmx_ग_लिखो_csr(CVMX_CIU_TIMX(समयr), timx.u64);
	/* Read it back to क्रमce immediate ग_लिखो of समयr रेजिस्टर*/
	timx.u64 = cvmx_पढ़ो_csr(CVMX_CIU_TIMX(समयr));
पूर्ण

अटल __init पूर्णांक oct_ilm_module_init(व्योम)
अणु
	पूर्णांक rc;
	पूर्णांक irq = OCTEON_IRQ_TIMER0 + TIMER_NUM;

	init_debugfs();

	rc = request_irq(irq, cvm_oct_ciu_समयr_पूर्णांकerrupt, IRQF_NO_THREAD,
			 "oct_ilm", 0);
	अगर (rc) अणु
		WARN(1, "Could not acquire IRQ %d", irq);
		जाओ err_irq;
	पूर्ण

	init_latency_info(&li, 1);
	start_समयr(TIMER_NUM, li.io_पूर्णांकerval);

	वापस 0;
err_irq:
	debugfs_हटाओ_recursive(dir);
	वापस rc;
पूर्ण

अटल __निकास व्योम oct_ilm_module_निकास(व्योम)
अणु
	disable_समयr(TIMER_NUM);
	debugfs_हटाओ_recursive(dir);
	मुक्त_irq(OCTEON_IRQ_TIMER0 + TIMER_NUM, 0);
पूर्ण

module_निकास(oct_ilm_module_निकास);
module_init(oct_ilm_module_init);
MODULE_AUTHOR("Venkat Subbiah, Cavium");
MODULE_DESCRIPTION("Measures interrupt latency on Octeon chips.");
MODULE_LICENSE("GPL");
