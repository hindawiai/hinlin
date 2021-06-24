<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2009 Simtec Electronics
//	http://armlinux.simtec.co.uk/
//	Ben Dooks <ben@simtec.co.uk>
//
// Simtec Osiris Dynamic Voltage Scaling support.

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/gpपन.स>

#समावेश <linux/mfd/tps65010.h>

#समावेश <linux/soc/samsung/s3c-cpu-freq.h>
#समावेश "gpio-samsung.h"

#घोषणा OSIRIS_GPIO_DVS	S3C2410_GPB(5)

अटल bool dvs_en;

अटल व्योम osiris_dvs_tps_setdvs(bool on)
अणु
	अचिन्हित vregs1 = 0, vdcdc2 = 0;

	अगर (!on) अणु
		vdcdc2 = TPS_VCORE_DISCH | TPS_LP_CORखातापूर्णF;
		vregs1 = TPS_LDO1_OFF;	/* turn off in low-घातer mode */
	पूर्ण

	dvs_en = on;
	vdcdc2 |= TPS_VCORE_1_3V | TPS_VCORE_LP_1_0V;
	vregs1 |= TPS_LDO2_ENABLE | TPS_LDO1_ENABLE;

	tps65010_config_vregs1(vregs1);
	tps65010_config_vdcdc2(vdcdc2);
पूर्ण

अटल bool is_dvs(काष्ठा s3c_freq *f)
अणु
	/* at the moment, we assume ARMCLK = HCLK => DVS */
	वापस f->armclk == f->hclk;
पूर्ण

/* keep track of current state */
अटल bool cur_dvs = false;

अटल पूर्णांक osiris_dvs_notअगरy(काष्ठा notअगरier_block *nb,
			      अचिन्हित दीर्घ val, व्योम *data)
अणु
	काष्ठा cpufreq_freqs *cf = data;
	काष्ठा s3c_cpufreq_freqs *freqs = to_s3c_cpufreq(cf);
	bool old_dvs = is_dvs(&freqs->old);
	bool new_dvs = is_dvs(&freqs->new);
	पूर्णांक ret = 0;

	अगर (!dvs_en)
		वापस 0;

	prपूर्णांकk(KERN_DEBUG "%s: old %ld,%ld new %ld,%ld\n", __func__,
	       freqs->old.armclk, freqs->old.hclk,
	       freqs->new.armclk, freqs->new.hclk);

	चयन (val) अणु
	हाल CPUFREQ_PRECHANGE:
		अगर ((old_dvs && !new_dvs) ||
		    (cur_dvs && !new_dvs)) अणु
			pr_debug("%s: exiting dvs\n", __func__);
			cur_dvs = false;
			gpio_set_value(OSIRIS_GPIO_DVS, 1);
		पूर्ण
		अवरोध;
	हाल CPUFREQ_POSTCHANGE:
		अगर ((!old_dvs && new_dvs) ||
		    (!cur_dvs && new_dvs)) अणु
			pr_debug("entering dvs\n");
			cur_dvs = true;
			gpio_set_value(OSIRIS_GPIO_DVS, 0);
		पूर्ण
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा notअगरier_block osiris_dvs_nb = अणु
	.notअगरier_call	= osiris_dvs_notअगरy,
पूर्ण;

अटल पूर्णांक osiris_dvs_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;

	dev_info(&pdev->dev, "initialising\n");

	ret = gpio_request(OSIRIS_GPIO_DVS, "osiris-dvs");
	अगर (ret) अणु
		dev_err(&pdev->dev, "cannot claim gpio\n");
		जाओ err_nogpio;
	पूर्ण

	/* start with dvs disabled */
	gpio_direction_output(OSIRIS_GPIO_DVS, 1);

	ret = cpufreq_रेजिस्टर_notअगरier(&osiris_dvs_nb,
					CPUFREQ_TRANSITION_NOTIFIER);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register with cpufreq\n");
		जाओ err_nofreq;
	पूर्ण

	osiris_dvs_tps_setdvs(true);

	वापस 0;

err_nofreq:
	gpio_मुक्त(OSIRIS_GPIO_DVS);

err_nogpio:
	वापस ret;
पूर्ण

अटल पूर्णांक osiris_dvs_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	dev_info(&pdev->dev, "exiting\n");

	/* disable any current dvs */
	gpio_set_value(OSIRIS_GPIO_DVS, 1);
	osiris_dvs_tps_setdvs(false);

	cpufreq_unरेजिस्टर_notअगरier(&osiris_dvs_nb,
				    CPUFREQ_TRANSITION_NOTIFIER);

	gpio_मुक्त(OSIRIS_GPIO_DVS);

	वापस 0;
पूर्ण

/* the CONFIG_PM block is so small, it isn't worth actually compiling it
 * out अगर the configuration isn't set. */

अटल पूर्णांक osiris_dvs_suspend(काष्ठा device *dev)
अणु
	gpio_set_value(OSIRIS_GPIO_DVS, 1);
	osiris_dvs_tps_setdvs(false);
	cur_dvs = false;

	वापस 0;
पूर्ण

अटल पूर्णांक osiris_dvs_resume(काष्ठा device *dev)
अणु
	osiris_dvs_tps_setdvs(true);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops osiris_dvs_pm = अणु
	.suspend	= osiris_dvs_suspend,
	.resume		= osiris_dvs_resume,
पूर्ण;

अटल काष्ठा platक्रमm_driver osiris_dvs_driver = अणु
	.probe		= osiris_dvs_probe,
	.हटाओ		= osiris_dvs_हटाओ,
	.driver		= अणु
		.name	= "osiris-dvs",
		.pm	= &osiris_dvs_pm,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(osiris_dvs_driver);

MODULE_DESCRIPTION("Simtec OSIRIS DVS support");
MODULE_AUTHOR("Ben Dooks <ben@simtec.co.uk>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:osiris-dvs");
