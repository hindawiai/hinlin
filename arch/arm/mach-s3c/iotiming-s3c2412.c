<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2006-2008 Simtec Electronics
//	http://armlinux.simtec.co.uk/
//	Ben Dooks <ben@simtec.co.uk>
//
// S3C2412/S3C2443 (PL093 based) IO timing support

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/device.h>
#समावेश <linux/delay.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>

#समावेश <linux/amba/pl093.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>

#समावेश "cpu.h"
#समावेश <linux/soc/samsung/s3c-cpufreq-core.h>

#समावेश "s3c2412.h"

#घोषणा prपूर्णांक_ns(x) ((x) / 10), ((x) % 10)

/**
 * s3c2412_prपूर्णांक_timing - prपूर्णांक timing inक्रमmation via prपूर्णांकk.
 * @pfx: The prefix to prपूर्णांक each line with.
 * @iot: The IO timing inक्रमmation
 */
अटल व्योम s3c2412_prपूर्णांक_timing(स्थिर अक्षर *pfx, काष्ठा s3c_iotimings *iot)
अणु
	काष्ठा s3c2412_iobank_timing *bt;
	अचिन्हित पूर्णांक bank;

	क्रम (bank = 0; bank < MAX_BANKS; bank++) अणु
		bt = iot->bank[bank].io_2412;
		अगर (!bt)
			जारी;

		prपूर्णांकk(KERN_DEBUG "%s: %d: idcy=%d.%d wstrd=%d.%d wstwr=%d,%d"
		       "wstoen=%d.%d wstwen=%d.%d wstbrd=%d.%d\n", pfx, bank,
		       prपूर्णांक_ns(bt->idcy),
		       prपूर्णांक_ns(bt->wstrd),
		       prपूर्णांक_ns(bt->wstwr),
		       prपूर्णांक_ns(bt->wstoen),
		       prपूर्णांक_ns(bt->wstwen),
		       prपूर्णांक_ns(bt->wstbrd));
	पूर्ण
पूर्ण

/**
 * to_भाग - turn a cycle length पूर्णांकo a भागisor setting.
 * @cyc_tns: The cycle समय in 10ths of nanoseconds.
 * @clk_tns: The घड़ी period in 10ths of nanoseconds.
 */
अटल अंतरभूत अचिन्हित पूर्णांक to_भाग(अचिन्हित पूर्णांक cyc_tns, अचिन्हित पूर्णांक clk_tns)
अणु
	वापस cyc_tns ? DIV_ROUND_UP(cyc_tns, clk_tns) : 0;
पूर्ण

/**
 * calc_timing - calculate timing भागisor value and check in range.
 * @hwपंचांग: The hardware timing in 10ths of nanoseconds.
 * @clk_tns: The घड़ी period in 10ths of nanoseconds.
 * @err: Poपूर्णांकer to err variable to update in event of failure.
 */
अटल अचिन्हित पूर्णांक calc_timing(अचिन्हित पूर्णांक hwपंचांग, अचिन्हित पूर्णांक clk_tns,
				अचिन्हित पूर्णांक *err)
अणु
	अचिन्हित पूर्णांक ret = to_भाग(hwपंचांग, clk_tns);

	अगर (ret > 0xf)
		*err = -EINVAL;

	वापस ret;
पूर्ण

/**
 * s3c2412_calc_bank - calculate the bank भागisor settings.
 * @cfg: The current frequency configuration.
 * @bt: The bank timing.
 */
अटल पूर्णांक s3c2412_calc_bank(काष्ठा s3c_cpufreq_config *cfg,
			     काष्ठा s3c2412_iobank_timing *bt)
अणु
	अचिन्हित पूर्णांक hclk = cfg->freq.hclk_tns;
	पूर्णांक err = 0;

	bt->smbidcyr = calc_timing(bt->idcy, hclk, &err);
	bt->smbwstrd = calc_timing(bt->wstrd, hclk, &err);
	bt->smbwstwr = calc_timing(bt->wstwr, hclk, &err);
	bt->smbwstoen = calc_timing(bt->wstoen, hclk, &err);
	bt->smbwstwen = calc_timing(bt->wstwen, hclk, &err);
	bt->smbwstbrd = calc_timing(bt->wstbrd, hclk, &err);

	वापस err;
पूर्ण

/**
 * s3c2412_iotiming_debugfs - debugfs show io bank timing inक्रमmation
 * @seq: The seq_file to ग_लिखो output to using seq_म_लिखो().
 * @cfg: The current configuration.
 * @iob: The IO bank inक्रमmation to decode.
*/
व्योम s3c2412_iotiming_debugfs(काष्ठा seq_file *seq,
			      काष्ठा s3c_cpufreq_config *cfg,
			      जोड़ s3c_iobank *iob)
अणु
	काष्ठा s3c2412_iobank_timing *bt = iob->io_2412;

	seq_म_लिखो(seq,
		   "\tRead: idcy=%d.%d wstrd=%d.%d wstwr=%d,%d"
		   "wstoen=%d.%d wstwen=%d.%d wstbrd=%d.%d\n",
		   prपूर्णांक_ns(bt->idcy),
		   prपूर्णांक_ns(bt->wstrd),
		   prपूर्णांक_ns(bt->wstwr),
		   prपूर्णांक_ns(bt->wstoen),
		   prपूर्णांक_ns(bt->wstwen),
		   prपूर्णांक_ns(bt->wstbrd));
पूर्ण

/**
 * s3c2412_iotiming_calc - calculate all the bank भागisor settings.
 * @cfg: The current frequency configuration.
 * @iot: The bank timing inक्रमmation.
 *
 * Calculate the timing inक्रमmation क्रम all the banks that are
 * configured as IO, using s3c2412_calc_bank().
 */
पूर्णांक s3c2412_iotiming_calc(काष्ठा s3c_cpufreq_config *cfg,
			  काष्ठा s3c_iotimings *iot)
अणु
	काष्ठा s3c2412_iobank_timing *bt;
	पूर्णांक bank;
	पूर्णांक ret;

	क्रम (bank = 0; bank < MAX_BANKS; bank++) अणु
		bt = iot->bank[bank].io_2412;
		अगर (!bt)
			जारी;

		ret = s3c2412_calc_bank(cfg, bt);
		अगर (ret) अणु
			prपूर्णांकk(KERN_ERR "%s: cannot calculate bank %d io\n",
			       __func__, bank);
			जाओ err;
		पूर्ण
	पूर्ण

	वापस 0;
 err:
	वापस ret;
पूर्ण

/**
 * s3c2412_iotiming_set - set the timing inक्रमmation
 * @cfg: The current frequency configuration.
 * @iot: The bank timing inक्रमmation.
 *
 * Set the IO bank inक्रमmation from the details calculated earlier from
 * calling s3c2412_iotiming_calc().
 */
व्योम s3c2412_iotiming_set(काष्ठा s3c_cpufreq_config *cfg,
			  काष्ठा s3c_iotimings *iot)
अणु
	काष्ठा s3c2412_iobank_timing *bt;
	व्योम __iomem *regs;
	पूर्णांक bank;

	/* set the io timings from the specअगरier */

	क्रम (bank = 0; bank < MAX_BANKS; bank++) अणु
		bt = iot->bank[bank].io_2412;
		अगर (!bt)
			जारी;

		regs = S3C2412_SSMC_BANK(bank);

		__raw_ग_लिखोl(bt->smbidcyr, regs + SMBIDCYR);
		__raw_ग_लिखोl(bt->smbwstrd, regs + SMBWSTRDR);
		__raw_ग_लिखोl(bt->smbwstwr, regs + SMBWSTWRR);
		__raw_ग_लिखोl(bt->smbwstoen, regs + SMBWSTOENR);
		__raw_ग_लिखोl(bt->smbwstwen, regs + SMBWSTWENR);
		__raw_ग_लिखोl(bt->smbwstbrd, regs + SMBWSTBRDR);
	पूर्ण
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक s3c2412_decode_timing(अचिन्हित पूर्णांक घड़ी, u32 reg)
अणु
	वापस (reg & 0xf) * घड़ी;
पूर्ण

अटल व्योम s3c2412_iotiming_getbank(काष्ठा s3c_cpufreq_config *cfg,
				     काष्ठा s3c2412_iobank_timing *bt,
				     अचिन्हित पूर्णांक bank)
अणु
	अचिन्हित दीर्घ clk = cfg->freq.hclk_tns;  /* ssmc घड़ी??? */
	व्योम __iomem *regs = S3C2412_SSMC_BANK(bank);

	bt->idcy = s3c2412_decode_timing(clk, __raw_पढ़ोl(regs + SMBIDCYR));
	bt->wstrd = s3c2412_decode_timing(clk, __raw_पढ़ोl(regs + SMBWSTRDR));
	bt->wstoen = s3c2412_decode_timing(clk, __raw_पढ़ोl(regs + SMBWSTOENR));
	bt->wstwen = s3c2412_decode_timing(clk, __raw_पढ़ोl(regs + SMBWSTWENR));
	bt->wstbrd = s3c2412_decode_timing(clk, __raw_पढ़ोl(regs + SMBWSTBRDR));
पूर्ण

/**
 * bank_is_io - वापस true अगर bank is (possibly) IO.
 * @bank: The bank number.
 * @bankcfg: The value of S3C2412_EBI_BANKCFG.
 */
अटल अंतरभूत bool bank_is_io(अचिन्हित पूर्णांक bank, u32 bankcfg)
अणु
	अगर (bank < 2)
		वापस true;

	वापस !(bankcfg & (1 << bank));
पूर्ण

पूर्णांक s3c2412_iotiming_get(काष्ठा s3c_cpufreq_config *cfg,
			 काष्ठा s3c_iotimings *timings)
अणु
	काष्ठा s3c2412_iobank_timing *bt;
	u32 bankcfg = __raw_पढ़ोl(S3C2412_EBI_BANKCFG);
	अचिन्हित पूर्णांक bank;

	/* look through all banks to see what is currently set. */

	क्रम (bank = 0; bank < MAX_BANKS; bank++) अणु
		अगर (!bank_is_io(bank, bankcfg))
			जारी;

		bt = kzalloc(माप(*bt), GFP_KERNEL);
		अगर (!bt)
			वापस -ENOMEM;

		timings->bank[bank].io_2412 = bt;
		s3c2412_iotiming_getbank(cfg, bt, bank);
	पूर्ण

	s3c2412_prपूर्णांक_timing("get", timings);
	वापस 0;
पूर्ण

/* this is in here as it is so small, it करोesn't currently warrant a file
 * to itself. We expect that any s3c24xx needing this is going to also
 * need the iotiming support.
 */
व्योम s3c2412_cpufreq_setrefresh(काष्ठा s3c_cpufreq_config *cfg)
अणु
	काष्ठा s3c_cpufreq_board *board = cfg->board;
	u32 refresh;

	WARN_ON(board == शून्य);

	/* Reduce both the refresh समय (in ns) and the frequency (in MHz)
	 * करोwn to ensure that we करो not overflow 32 bit numbers.
	 *
	 * This should work क्रम HCLK up to 133MHz and refresh period up
	 * to 30usec.
	 */

	refresh = (cfg->freq.hclk / 100) * (board->refresh / 10);
	refresh = DIV_ROUND_UP(refresh, (1000 * 1000)); /* apply scale  */
	refresh &= ((1 << 16) - 1);

	s3c_freq_dbg("%s: refresh value %u\n", __func__, (अचिन्हित पूर्णांक)refresh);

	__raw_ग_लिखोl(refresh, S3C2412_REFRESH);
पूर्ण
