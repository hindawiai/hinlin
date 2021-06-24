<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Debugfs support क्रम hosts and cards
 *
 * Copyright (C) 2008 Aपंचांगel Corporation
 */
#समावेश <linux/moduleparam.h>
#समावेश <linux/export.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/fault-inject.h>

#समावेश <linux/mmc/card.h>
#समावेश <linux/mmc/host.h>

#समावेश "core.h"
#समावेश "card.h"
#समावेश "host.h"
#समावेश "mmc_ops.h"

#अगर_घोषित CONFIG_FAIL_MMC_REQUEST

अटल DECLARE_FAULT_ATTR(fail_शेष_attr);
अटल अक्षर *fail_request;
module_param(fail_request, अक्षरp, 0);

#पूर्ण_अगर /* CONFIG_FAIL_MMC_REQUEST */

/* The debugfs functions are optimized away when CONFIG_DEBUG_FS isn't set. */
अटल पूर्णांक mmc_ios_show(काष्ठा seq_file *s, व्योम *data)
अणु
	अटल स्थिर अक्षर *vdd_str[] = अणु
		[8]	= "2.0",
		[9]	= "2.1",
		[10]	= "2.2",
		[11]	= "2.3",
		[12]	= "2.4",
		[13]	= "2.5",
		[14]	= "2.6",
		[15]	= "2.7",
		[16]	= "2.8",
		[17]	= "2.9",
		[18]	= "3.0",
		[19]	= "3.1",
		[20]	= "3.2",
		[21]	= "3.3",
		[22]	= "3.4",
		[23]	= "3.5",
		[24]	= "3.6",
	पूर्ण;
	काष्ठा mmc_host	*host = s->निजी;
	काष्ठा mmc_ios	*ios = &host->ios;
	स्थिर अक्षर *str;

	seq_म_लिखो(s, "clock:\t\t%u Hz\n", ios->घड़ी);
	अगर (host->actual_घड़ी)
		seq_म_लिखो(s, "actual clock:\t%u Hz\n", host->actual_घड़ी);
	seq_म_लिखो(s, "vdd:\t\t%u ", ios->vdd);
	अगर ((1 << ios->vdd) & MMC_VDD_165_195)
		seq_म_लिखो(s, "(1.65 - 1.95 V)\n");
	अन्यथा अगर (ios->vdd < (ARRAY_SIZE(vdd_str) - 1)
			&& vdd_str[ios->vdd] && vdd_str[ios->vdd + 1])
		seq_म_लिखो(s, "(%s ~ %s V)\n", vdd_str[ios->vdd],
				vdd_str[ios->vdd + 1]);
	अन्यथा
		seq_म_लिखो(s, "(invalid)\n");

	चयन (ios->bus_mode) अणु
	हाल MMC_BUSMODE_OPENDRAIN:
		str = "open drain";
		अवरोध;
	हाल MMC_BUSMODE_PUSHPULL:
		str = "push-pull";
		अवरोध;
	शेष:
		str = "invalid";
		अवरोध;
	पूर्ण
	seq_म_लिखो(s, "bus mode:\t%u (%s)\n", ios->bus_mode, str);

	चयन (ios->chip_select) अणु
	हाल MMC_CS_DONTCARE:
		str = "don't care";
		अवरोध;
	हाल MMC_CS_HIGH:
		str = "active high";
		अवरोध;
	हाल MMC_CS_LOW:
		str = "active low";
		अवरोध;
	शेष:
		str = "invalid";
		अवरोध;
	पूर्ण
	seq_म_लिखो(s, "chip select:\t%u (%s)\n", ios->chip_select, str);

	चयन (ios->घातer_mode) अणु
	हाल MMC_POWER_OFF:
		str = "off";
		अवरोध;
	हाल MMC_POWER_UP:
		str = "up";
		अवरोध;
	हाल MMC_POWER_ON:
		str = "on";
		अवरोध;
	शेष:
		str = "invalid";
		अवरोध;
	पूर्ण
	seq_म_लिखो(s, "power mode:\t%u (%s)\n", ios->घातer_mode, str);
	seq_म_लिखो(s, "bus width:\t%u (%u bits)\n",
			ios->bus_width, 1 << ios->bus_width);

	चयन (ios->timing) अणु
	हाल MMC_TIMING_LEGACY:
		str = "legacy";
		अवरोध;
	हाल MMC_TIMING_MMC_HS:
		str = "mmc high-speed";
		अवरोध;
	हाल MMC_TIMING_SD_HS:
		str = "sd high-speed";
		अवरोध;
	हाल MMC_TIMING_UHS_SDR12:
		str = "sd uhs SDR12";
		अवरोध;
	हाल MMC_TIMING_UHS_SDR25:
		str = "sd uhs SDR25";
		अवरोध;
	हाल MMC_TIMING_UHS_SDR50:
		str = "sd uhs SDR50";
		अवरोध;
	हाल MMC_TIMING_UHS_SDR104:
		str = "sd uhs SDR104";
		अवरोध;
	हाल MMC_TIMING_UHS_DDR50:
		str = "sd uhs DDR50";
		अवरोध;
	हाल MMC_TIMING_MMC_DDR52:
		str = "mmc DDR52";
		अवरोध;
	हाल MMC_TIMING_MMC_HS200:
		str = "mmc HS200";
		अवरोध;
	हाल MMC_TIMING_MMC_HS400:
		str = mmc_card_hs400es(host->card) ?
			"mmc HS400 enhanced strobe" : "mmc HS400";
		अवरोध;
	शेष:
		str = "invalid";
		अवरोध;
	पूर्ण
	seq_म_लिखो(s, "timing spec:\t%u (%s)\n", ios->timing, str);

	चयन (ios->संकेत_voltage) अणु
	हाल MMC_SIGNAL_VOLTAGE_330:
		str = "3.30 V";
		अवरोध;
	हाल MMC_SIGNAL_VOLTAGE_180:
		str = "1.80 V";
		अवरोध;
	हाल MMC_SIGNAL_VOLTAGE_120:
		str = "1.20 V";
		अवरोध;
	शेष:
		str = "invalid";
		अवरोध;
	पूर्ण
	seq_म_लिखो(s, "signal voltage:\t%u (%s)\n", ios->संकेत_voltage, str);

	चयन (ios->drv_type) अणु
	हाल MMC_SET_DRIVER_TYPE_A:
		str = "driver type A";
		अवरोध;
	हाल MMC_SET_DRIVER_TYPE_B:
		str = "driver type B";
		अवरोध;
	हाल MMC_SET_DRIVER_TYPE_C:
		str = "driver type C";
		अवरोध;
	हाल MMC_SET_DRIVER_TYPE_D:
		str = "driver type D";
		अवरोध;
	शेष:
		str = "invalid";
		अवरोध;
	पूर्ण
	seq_म_लिखो(s, "driver type:\t%u (%s)\n", ios->drv_type, str);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(mmc_ios);

अटल पूर्णांक mmc_घड़ी_opt_get(व्योम *data, u64 *val)
अणु
	काष्ठा mmc_host *host = data;

	*val = host->ios.घड़ी;

	वापस 0;
पूर्ण

अटल पूर्णांक mmc_घड़ी_opt_set(व्योम *data, u64 val)
अणु
	काष्ठा mmc_host *host = data;

	/* We need this check due to input value is u64 */
	अगर (val != 0 && (val > host->f_max || val < host->f_min))
		वापस -EINVAL;

	mmc_claim_host(host);
	mmc_set_घड़ी(host, (अचिन्हित पूर्णांक) val);
	mmc_release_host(host);

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(mmc_घड़ी_fops, mmc_घड़ी_opt_get, mmc_घड़ी_opt_set,
	"%llu\n");

व्योम mmc_add_host_debugfs(काष्ठा mmc_host *host)
अणु
	काष्ठा dentry *root;

	root = debugfs_create_dir(mmc_hostname(host), शून्य);
	host->debugfs_root = root;

	debugfs_create_file("ios", S_IRUSR, root, host, &mmc_ios_fops);
	debugfs_create_x32("caps", S_IRUSR, root, &host->caps);
	debugfs_create_x32("caps2", S_IRUSR, root, &host->caps2);
	debugfs_create_file_unsafe("clock", S_IRUSR | S_IWUSR, root, host,
				   &mmc_घड़ी_fops);

#अगर_घोषित CONFIG_FAIL_MMC_REQUEST
	अगर (fail_request)
		setup_fault_attr(&fail_शेष_attr, fail_request);
	host->fail_mmc_request = fail_शेष_attr;
	fault_create_debugfs_attr("fail_mmc_request", root,
				  &host->fail_mmc_request);
#पूर्ण_अगर
पूर्ण

व्योम mmc_हटाओ_host_debugfs(काष्ठा mmc_host *host)
अणु
	debugfs_हटाओ_recursive(host->debugfs_root);
पूर्ण

व्योम mmc_add_card_debugfs(काष्ठा mmc_card *card)
अणु
	काष्ठा mmc_host	*host = card->host;
	काष्ठा dentry	*root;

	अगर (!host->debugfs_root)
		वापस;

	root = debugfs_create_dir(mmc_card_id(card), host->debugfs_root);
	card->debugfs_root = root;

	debugfs_create_x32("state", S_IRUSR, root, &card->state);
पूर्ण

व्योम mmc_हटाओ_card_debugfs(काष्ठा mmc_card *card)
अणु
	debugfs_हटाओ_recursive(card->debugfs_root);
	card->debugfs_root = शून्य;
पूर्ण
