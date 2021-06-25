<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2006-2009 Simtec Electronics
//	http://armlinux.simtec.co.uk/
//	Ben Dooks <ben@simtec.co.uk>
//
// S3C24XX CPU Frequency scaling - IO timing क्रम S3C2410/S3C2440/S3C2442

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/cpufreq.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>

#समावेश "map.h"
#समावेश "regs-clock.h"

#समावेश <linux/soc/samsung/s3c-cpufreq-core.h>

#समावेश "regs-mem-s3c24xx.h"

#घोषणा prपूर्णांक_ns(x) ((x) / 10), ((x) % 10)

/**
 * s3c2410_prपूर्णांक_timing - prपूर्णांक bank timing data क्रम debug purposes
 * @pfx: The prefix to put on the output
 * @timings: The timing inक्रमamtion to prपूर्णांक.
*/
अटल व्योम s3c2410_prपूर्णांक_timing(स्थिर अक्षर *pfx,
				 काष्ठा s3c_iotimings *timings)
अणु
	काष्ठा s3c2410_iobank_timing *bt;
	पूर्णांक bank;

	क्रम (bank = 0; bank < MAX_BANKS; bank++) अणु
		bt = timings->bank[bank].io_2410;
		अगर (!bt)
			जारी;

		prपूर्णांकk(KERN_DEBUG "%s %d: Tacs=%d.%d, Tcos=%d.%d, Tacc=%d.%d, "
		       "Tcoh=%d.%d, Tcah=%d.%d\n", pfx, bank,
		       prपूर्णांक_ns(bt->tacs),
		       prपूर्णांक_ns(bt->tcos),
		       prपूर्णांक_ns(bt->tacc),
		       prपूर्णांक_ns(bt->tcoh),
		       prपूर्णांक_ns(bt->tcah));
	पूर्ण
पूर्ण

/**
 * bank_reg - convert bank number to poपूर्णांकer to the control रेजिस्टर.
 * @bank: The IO bank number.
 */
अटल अंतरभूत व्योम __iomem *bank_reg(अचिन्हित पूर्णांक bank)
अणु
	वापस S3C2410_BANKCON0 + (bank << 2);
पूर्ण

/**
 * bank_is_io - test whether bank is used क्रम IO
 * @bankcon: The bank control रेजिस्टर.
 *
 * This is a simplistic test to see अगर any BANKCON[x] is not an IO
 * bank. It currently करोes not take पूर्णांकo account whether BWSCON has
 * an illegal width-setting in it, or अगर the pin connected to nCS[x]
 * is actually being handled as a chip-select.
 */
अटल अंतरभूत पूर्णांक bank_is_io(अचिन्हित दीर्घ bankcon)
अणु
	वापस !(bankcon & S3C2410_BANKCON_SDRAM);
पूर्ण

/**
 * to_भाग - convert cycle समय to भागisor
 * @cyc: The cycle समय, in 10ths of nanoseconds.
 * @hclk_tns: The cycle समय क्रम HCLK, in 10ths of nanoseconds.
 *
 * Convert the given cycle समय पूर्णांकo the भागisor to use to obtain it from
 * HCLK.
*/
अटल अंतरभूत अचिन्हित पूर्णांक to_भाग(अचिन्हित पूर्णांक cyc, अचिन्हित पूर्णांक hclk_tns)
अणु
	अगर (cyc == 0)
		वापस 0;

	वापस DIV_ROUND_UP(cyc, hclk_tns);
पूर्ण

/**
 * calc_0124 - calculate भागisor control क्रम भागisors that करो /0, /1. /2 and /4
 * @cyc: The cycle समय, in 10ths of nanoseconds.
 * @hclk_tns: The cycle समय क्रम HCLK, in 10ths of nanoseconds.
 * @v: Poपूर्णांकer to रेजिस्टर to alter.
 * @shअगरt: The shअगरt to get to the control bits.
 *
 * Calculate the भागisor, and turn it पूर्णांकo the correct control bits to
 * set in the result, @v.
 */
अटल अचिन्हित पूर्णांक calc_0124(अचिन्हित पूर्णांक cyc, अचिन्हित दीर्घ hclk_tns,
			      अचिन्हित दीर्घ *v, पूर्णांक shअगरt)
अणु
	अचिन्हित पूर्णांक भाग = to_भाग(cyc, hclk_tns);
	अचिन्हित दीर्घ val;

	s3c_freq_iodbg("%s: cyc=%d, hclk=%lu, shift=%d => div %d\n",
		       __func__, cyc, hclk_tns, shअगरt, भाग);

	चयन (भाग) अणु
	हाल 0:
		val = 0;
		अवरोध;
	हाल 1:
		val = 1;
		अवरोध;
	हाल 2:
		val = 2;
		अवरोध;
	हाल 3:
	हाल 4:
		val = 3;
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण

	*v |= val << shअगरt;
	वापस 0;
पूर्ण

अटल पूर्णांक calc_tacp(अचिन्हित पूर्णांक cyc, अचिन्हित दीर्घ hclk, अचिन्हित दीर्घ *v)
अणु
	/* Currently no support क्रम Tacp calculations. */
	वापस 0;
पूर्ण

/**
 * calc_tacc - calculate भागisor control क्रम tacc.
 * @cyc: The cycle समय, in 10ths of nanoseconds.
 * @nरुको_en: IS nWAIT enabled क्रम this bank.
 * @hclk_tns: The cycle समय क्रम HCLK, in 10ths of nanoseconds.
 * @v: Poपूर्णांकer to रेजिस्टर to alter.
 *
 * Calculate the भागisor control क्रम tACC, taking पूर्णांकo account whether
 * the bank has nWAIT enabled. The result is used to modअगरy the value
 * poपूर्णांकed to by @v.
*/
अटल पूर्णांक calc_tacc(अचिन्हित पूर्णांक cyc, पूर्णांक nरुको_en,
		     अचिन्हित दीर्घ hclk_tns, अचिन्हित दीर्घ *v)
अणु
	अचिन्हित पूर्णांक भाग = to_भाग(cyc, hclk_tns);
	अचिन्हित दीर्घ val;

	s3c_freq_iodbg("%s: cyc=%u, nwait=%d, hclk=%lu => div=%u\n",
		       __func__, cyc, nरुको_en, hclk_tns, भाग);

	/* अगर nWait enabled on an bank, Tacc must be at-least 4 cycles. */
	अगर (nरुको_en && भाग < 4)
		भाग = 4;

	चयन (भाग) अणु
	हाल 0:
		val = 0;
		अवरोध;

	हाल 1:
	हाल 2:
	हाल 3:
	हाल 4:
		val = भाग - 1;
		अवरोध;

	हाल 5:
	हाल 6:
		val = 4;
		अवरोध;

	हाल 7:
	हाल 8:
		val = 5;
		अवरोध;

	हाल 9:
	हाल 10:
		val = 6;
		अवरोध;

	हाल 11:
	हाल 12:
	हाल 13:
	हाल 14:
		val = 7;
		अवरोध;

	शेष:
		वापस -1;
	पूर्ण

	*v |= val << 8;
	वापस 0;
पूर्ण

/**
 * s3c2410_calc_bank - calculate bank timing inक्रमmation
 * @cfg: The configuration we need to calculate क्रम.
 * @bt: The bank timing inक्रमmation.
 *
 * Given the cycle timine क्रम a bank @bt, calculate the new BANKCON
 * setting क्रम the @cfg timing. This updates the timing inक्रमmation
 * पढ़ोy क्रम the cpu frequency change.
 */
अटल पूर्णांक s3c2410_calc_bank(काष्ठा s3c_cpufreq_config *cfg,
			     काष्ठा s3c2410_iobank_timing *bt)
अणु
	अचिन्हित दीर्घ hclk = cfg->freq.hclk_tns;
	अचिन्हित दीर्घ res;
	पूर्णांक ret;

	res  = bt->bankcon;
	res &= (S3C2410_BANKCON_SDRAM | S3C2410_BANKCON_PMC16);

	/* tacp: 2,3,4,5 */
	/* tcah: 0,1,2,4 */
	/* tcoh: 0,1,2,4 */
	/* tacc: 1,2,3,4,6,7,10,14 (>4 क्रम nरुको) */
	/* tcos: 0,1,2,4 */
	/* tacs: 0,1,2,4 */

	ret  = calc_0124(bt->tacs, hclk, &res, S3C2410_BANKCON_Tacs_SHIFT);
	ret |= calc_0124(bt->tcos, hclk, &res, S3C2410_BANKCON_Tcos_SHIFT);
	ret |= calc_0124(bt->tcah, hclk, &res, S3C2410_BANKCON_Tcah_SHIFT);
	ret |= calc_0124(bt->tcoh, hclk, &res, S3C2410_BANKCON_Tcoh_SHIFT);

	अगर (ret)
		वापस -EINVAL;

	ret |= calc_tacp(bt->tacp, hclk, &res);
	ret |= calc_tacc(bt->tacc, bt->nरुको_en, hclk, &res);

	अगर (ret)
		वापस -EINVAL;

	bt->bankcon = res;
	वापस 0;
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक tacc_tab[] = अणु
	[0]	= 1,
	[1]	= 2,
	[2]	= 3,
	[3]	= 4,
	[4]	= 6,
	[5]	= 9,
	[6]	= 10,
	[7]	= 14,
पूर्ण;

/**
 * get_tacc - turn tACC value पूर्णांकo cycle समय
 * @hclk_tns: The cycle समय क्रम HCLK, in 10ths of nanoseconds.
 * @val: The bank timing रेजिस्टर value, shअगरed करोwn.
 */
अटल अचिन्हित पूर्णांक get_tacc(अचिन्हित दीर्घ hclk_tns,
			     अचिन्हित दीर्घ val)
अणु
	val &= 7;
	वापस hclk_tns * tacc_tab[val];
पूर्ण

/**
 * get_0124 - turn 0/1/2/4 भागider पूर्णांकo cycle समय
 * @hclk_tns: The cycle समय क्रम HCLK, in 10ths of nanoseconds.
 * @val: The bank timing रेजिस्टर value, shअगरed करोwn.
 */
अटल अचिन्हित पूर्णांक get_0124(अचिन्हित दीर्घ hclk_tns,
			     अचिन्हित दीर्घ val)
अणु
	val &= 3;
	वापस hclk_tns * ((val == 3) ? 4 : val);
पूर्ण

/**
 * s3c2410_iotiming_getbank - turn BANKCON पूर्णांकo cycle समय inक्रमmation
 * @cfg: The frequency configuration
 * @bt: The bank timing to fill in (uses cached BANKCON)
 *
 * Given the BANKCON setting in @bt and the current frequency settings
 * in @cfg, update the cycle timing inक्रमmation.
 */
अटल व्योम s3c2410_iotiming_getbank(काष्ठा s3c_cpufreq_config *cfg,
				     काष्ठा s3c2410_iobank_timing *bt)
अणु
	अचिन्हित दीर्घ bankcon = bt->bankcon;
	अचिन्हित दीर्घ hclk = cfg->freq.hclk_tns;

	bt->tcah = get_0124(hclk, bankcon >> S3C2410_BANKCON_Tcah_SHIFT);
	bt->tcoh = get_0124(hclk, bankcon >> S3C2410_BANKCON_Tcoh_SHIFT);
	bt->tcos = get_0124(hclk, bankcon >> S3C2410_BANKCON_Tcos_SHIFT);
	bt->tacs = get_0124(hclk, bankcon >> S3C2410_BANKCON_Tacs_SHIFT);
	bt->tacc = get_tacc(hclk, bankcon >> S3C2410_BANKCON_Tacc_SHIFT);
पूर्ण

/**
 * s3c2410_iotiming_debugfs - debugfs show io bank timing inक्रमmation
 * @seq: The seq_file to ग_लिखो output to using seq_म_लिखो().
 * @cfg: The current configuration.
 * @iob: The IO bank inक्रमmation to decode.
 */
व्योम s3c2410_iotiming_debugfs(काष्ठा seq_file *seq,
			      काष्ठा s3c_cpufreq_config *cfg,
			      जोड़ s3c_iobank *iob)
अणु
	काष्ठा s3c2410_iobank_timing *bt = iob->io_2410;
	अचिन्हित दीर्घ bankcon = bt->bankcon;
	अचिन्हित दीर्घ hclk = cfg->freq.hclk_tns;
	अचिन्हित पूर्णांक tacs;
	अचिन्हित पूर्णांक tcos;
	अचिन्हित पूर्णांक tacc;
	अचिन्हित पूर्णांक tcoh;
	अचिन्हित पूर्णांक tcah;

	seq_म_लिखो(seq, "BANKCON=0x%08lx\n", bankcon);

	tcah = get_0124(hclk, bankcon >> S3C2410_BANKCON_Tcah_SHIFT);
	tcoh = get_0124(hclk, bankcon >> S3C2410_BANKCON_Tcoh_SHIFT);
	tcos = get_0124(hclk, bankcon >> S3C2410_BANKCON_Tcos_SHIFT);
	tacs = get_0124(hclk, bankcon >> S3C2410_BANKCON_Tacs_SHIFT);
	tacc = get_tacc(hclk, bankcon >> S3C2410_BANKCON_Tacc_SHIFT);

	seq_म_लिखो(seq,
		   "\tRead: Tacs=%d.%d, Tcos=%d.%d, Tacc=%d.%d, Tcoh=%d.%d, Tcah=%d.%d\n",
		   prपूर्णांक_ns(bt->tacs),
		   prपूर्णांक_ns(bt->tcos),
		   prपूर्णांक_ns(bt->tacc),
		   prपूर्णांक_ns(bt->tcoh),
		   prपूर्णांक_ns(bt->tcah));

	seq_म_लिखो(seq,
		   "\t Set: Tacs=%d.%d, Tcos=%d.%d, Tacc=%d.%d, Tcoh=%d.%d, Tcah=%d.%d\n",
		   prपूर्णांक_ns(tacs),
		   prपूर्णांक_ns(tcos),
		   prपूर्णांक_ns(tacc),
		   prपूर्णांक_ns(tcoh),
		   prपूर्णांक_ns(tcah));
पूर्ण

/**
 * s3c2410_iotiming_calc - Calculate bank timing क्रम frequency change.
 * @cfg: The frequency configuration
 * @iot: The IO timing inक्रमmation to fill out.
 *
 * Calculate the new values क्रम the banks in @iot based on the new
 * frequency inक्रमmation in @cfg. This is then used by s3c2410_iotiming_set()
 * to update the timing when necessary.
 */
पूर्णांक s3c2410_iotiming_calc(काष्ठा s3c_cpufreq_config *cfg,
			  काष्ठा s3c_iotimings *iot)
अणु
	काष्ठा s3c2410_iobank_timing *bt;
	अचिन्हित दीर्घ bankcon;
	पूर्णांक bank;
	पूर्णांक ret;

	क्रम (bank = 0; bank < MAX_BANKS; bank++) अणु
		bankcon = __raw_पढ़ोl(bank_reg(bank));
		bt = iot->bank[bank].io_2410;

		अगर (!bt)
			जारी;

		bt->bankcon = bankcon;

		ret = s3c2410_calc_bank(cfg, bt);
		अगर (ret) अणु
			prपूर्णांकk(KERN_ERR "%s: cannot calculate bank %d io\n",
			       __func__, bank);
			जाओ err;
		पूर्ण

		s3c_freq_iodbg("%s: bank %d: con=%08lx\n",
			       __func__, bank, bt->bankcon);
	पूर्ण

	वापस 0;
 err:
	वापस ret;
पूर्ण

/**
 * s3c2410_iotiming_set - set the IO timings from the given setup.
 * @cfg: The frequency configuration
 * @iot: The IO timing inक्रमmation to use.
 *
 * Set all the currently used IO bank timing inक्रमmation generated
 * by s3c2410_iotiming_calc() once the core has validated that all
 * the new values are within permitted bounds.
 */
व्योम s3c2410_iotiming_set(काष्ठा s3c_cpufreq_config *cfg,
			  काष्ठा s3c_iotimings *iot)
अणु
	काष्ठा s3c2410_iobank_timing *bt;
	पूर्णांक bank;

	/* set the io timings from the specअगरier */

	क्रम (bank = 0; bank < MAX_BANKS; bank++) अणु
		bt = iot->bank[bank].io_2410;
		अगर (!bt)
			जारी;

		__raw_ग_लिखोl(bt->bankcon, bank_reg(bank));
	पूर्ण
पूर्ण

/**
 * s3c2410_iotiming_get - Get the timing inक्रमmation from current रेजिस्टरs.
 * @cfg: The frequency configuration
 * @timings: The IO timing inक्रमmation to fill out.
 *
 * Calculate the @timings timing inक्रमmation from the current frequency
 * inक्रमmation in @cfg, and the new frequency configuration
 * through all the IO banks, पढ़ोing the state and then updating @iot
 * as necessary.
 *
 * This is used at the moment on initialisation to get the current
 * configuration so that boards करो not have to carry their own setup
 * अगर the timings are correct on initialisation.
 */

पूर्णांक s3c2410_iotiming_get(काष्ठा s3c_cpufreq_config *cfg,
			 काष्ठा s3c_iotimings *timings)
अणु
	काष्ठा s3c2410_iobank_timing *bt;
	अचिन्हित दीर्घ bankcon;
	अचिन्हित दीर्घ bwscon;
	पूर्णांक bank;

	bwscon = __raw_पढ़ोl(S3C2410_BWSCON);

	/* look through all banks to see what is currently set. */

	क्रम (bank = 0; bank < MAX_BANKS; bank++) अणु
		bankcon = __raw_पढ़ोl(bank_reg(bank));

		अगर (!bank_is_io(bankcon))
			जारी;

		s3c_freq_iodbg("%s: bank %d: con %08lx\n",
			       __func__, bank, bankcon);

		bt = kzalloc(माप(*bt), GFP_KERNEL);
		अगर (!bt)
			वापस -ENOMEM;

		/* find out in nWait is enabled क्रम bank. */

		अगर (bank != 0) अणु
			अचिन्हित दीर्घ पंचांगp  = S3C2410_BWSCON_GET(bwscon, bank);
			अगर (पंचांगp & S3C2410_BWSCON_WS)
				bt->nरुको_en = 1;
		पूर्ण

		timings->bank[bank].io_2410 = bt;
		bt->bankcon = bankcon;

		s3c2410_iotiming_getbank(cfg, bt);
	पूर्ण

	s3c2410_prपूर्णांक_timing("get", timings);
	वापस 0;
पूर्ण
