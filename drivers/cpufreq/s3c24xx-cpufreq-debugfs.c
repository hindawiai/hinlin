<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2009 Simtec Electronics
 *	http://armlinux.simtec.co.uk/
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * S3C24XX CPU Frequency scaling - debugfs status support
*/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/err.h>

#समावेश <linux/soc/samsung/s3c-cpufreq-core.h>

अटल काष्ठा dentry *dbgfs_root;
अटल काष्ठा dentry *dbgfs_file_io;
अटल काष्ठा dentry *dbgfs_file_info;
अटल काष्ठा dentry *dbgfs_file_board;

#घोषणा prपूर्णांक_ns(x) ((x) / 10), ((x) % 10)

अटल व्योम show_max(काष्ठा seq_file *seq, काष्ठा s3c_freq *f)
अणु
	seq_म_लिखो(seq, "MAX: F=%lu, H=%lu, P=%lu, A=%lu\n",
		   f->fclk, f->hclk, f->pclk, f->armclk);
पूर्ण

अटल पूर्णांक board_show(काष्ठा seq_file *seq, व्योम *p)
अणु
	काष्ठा s3c_cpufreq_config *cfg;
	काष्ठा s3c_cpufreq_board *brd;

	cfg = s3c_cpufreq_अ_लोonfig();
	अगर (!cfg) अणु
		seq_म_लिखो(seq, "no configuration registered\n");
		वापस 0;
	पूर्ण

	brd = cfg->board;
	अगर (!brd) अणु
		seq_म_लिखो(seq, "no board definition set?\n");
		वापस 0;
	पूर्ण

	seq_म_लिखो(seq, "SDRAM refresh %u ns\n", brd->refresh);
	seq_म_लिखो(seq, "auto_io=%u\n", brd->स्वतः_io);
	seq_म_लिखो(seq, "need_io=%u\n", brd->need_io);

	show_max(seq, &brd->max);


	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(board);

अटल पूर्णांक info_show(काष्ठा seq_file *seq, व्योम *p)
अणु
	काष्ठा s3c_cpufreq_config *cfg;

	cfg = s3c_cpufreq_अ_लोonfig();
	अगर (!cfg) अणु
		seq_म_लिखो(seq, "no configuration registered\n");
		वापस 0;
	पूर्ण

	seq_म_लिखो(seq, "  FCLK %ld Hz\n", cfg->freq.fclk);
	seq_म_लिखो(seq, "  HCLK %ld Hz (%lu.%lu ns)\n",
		   cfg->freq.hclk, prपूर्णांक_ns(cfg->freq.hclk_tns));
	seq_म_लिखो(seq, "  PCLK %ld Hz\n", cfg->freq.hclk);
	seq_म_लिखो(seq, "ARMCLK %ld Hz\n", cfg->freq.armclk);
	seq_म_लिखो(seq, "\n");

	show_max(seq, &cfg->max);

	seq_म_लिखो(seq, "Divisors: P=%d, H=%d, A=%d, dvs=%s\n",
		   cfg->भागs.h_भागisor, cfg->भागs.p_भागisor,
		   cfg->भागs.arm_भागisor, cfg->भागs.dvs ? "on" : "off");
	seq_म_लिखो(seq, "\n");

	seq_म_लिखो(seq, "lock_pll=%u\n", cfg->lock_pll);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(info);

अटल पूर्णांक io_show(काष्ठा seq_file *seq, व्योम *p)
अणु
	व्योम (*show_bank)(काष्ठा seq_file *, काष्ठा s3c_cpufreq_config *, जोड़ s3c_iobank *);
	काष्ठा s3c_cpufreq_config *cfg;
	काष्ठा s3c_iotimings *iot;
	जोड़ s3c_iobank *iob;
	पूर्णांक bank;

	cfg = s3c_cpufreq_अ_लोonfig();
	अगर (!cfg) अणु
		seq_म_लिखो(seq, "no configuration registered\n");
		वापस 0;
	पूर्ण

	show_bank = cfg->info->debug_io_show;
	अगर (!show_bank) अणु
		seq_म_लिखो(seq, "no code to show bank timing\n");
		वापस 0;
	पूर्ण

	iot = s3c_cpufreq_getiotimings();
	अगर (!iot) अणु
		seq_म_लिखो(seq, "no io timings registered\n");
		वापस 0;
	पूर्ण

	seq_म_लिखो(seq, "hclk period is %lu.%lu ns\n", prपूर्णांक_ns(cfg->freq.hclk_tns));

	क्रम (bank = 0; bank < MAX_BANKS; bank++) अणु
		iob = &iot->bank[bank];

		seq_म_लिखो(seq, "bank %d: ", bank);

		अगर (!iob->io_2410) अणु
			seq_म_लिखो(seq, "nothing set\n");
			जारी;
		पूर्ण

		show_bank(seq, cfg, iob);
	पूर्ण

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(io);

अटल पूर्णांक __init s3c_freq_debugfs_init(व्योम)
अणु
	dbgfs_root = debugfs_create_dir("s3c-cpufreq", शून्य);
	अगर (IS_ERR(dbgfs_root)) अणु
		pr_err("%s: error creating debugfs root\n", __func__);
		वापस PTR_ERR(dbgfs_root);
	पूर्ण

	dbgfs_file_io = debugfs_create_file("io-timing", S_IRUGO, dbgfs_root,
					    शून्य, &io_fops);

	dbgfs_file_info = debugfs_create_file("info", S_IRUGO, dbgfs_root,
					      शून्य, &info_fops);

	dbgfs_file_board = debugfs_create_file("board", S_IRUGO, dbgfs_root,
					       शून्य, &board_fops);

	वापस 0;
पूर्ण

late_initcall(s3c_freq_debugfs_init);

