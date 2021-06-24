<शैली गुरु>
/*
 * Copyright (C) 2006 - 2008 Lemote Inc. & Institute of Computing Technology
 * Author: Yanhua, yanh@lemote.com
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#समावेश <linux/cpufreq.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/export.h>

#समावेश <यंत्र/mach-loongson2ef/loongson.h>

क्रमागत अणु
	DC_ZERO, DC_25PT = 2, DC_37PT, DC_50PT, DC_62PT, DC_75PT,
	DC_87PT, DC_DISABLE, DC_RESV
पूर्ण;

काष्ठा cpufreq_frequency_table loongson2_घड़ीmod_table[] = अणु
	अणु0, DC_RESV, CPUFREQ_ENTRY_INVALIDपूर्ण,
	अणु0, DC_ZERO, CPUFREQ_ENTRY_INVALIDपूर्ण,
	अणु0, DC_25PT, 0पूर्ण,
	अणु0, DC_37PT, 0पूर्ण,
	अणु0, DC_50PT, 0पूर्ण,
	अणु0, DC_62PT, 0पूर्ण,
	अणु0, DC_75PT, 0पूर्ण,
	अणु0, DC_87PT, 0पूर्ण,
	अणु0, DC_DISABLE, 0पूर्ण,
	अणु0, DC_RESV, CPUFREQ_TABLE_ENDपूर्ण,
पूर्ण;
EXPORT_SYMBOL_GPL(loongson2_घड़ीmod_table);

पूर्णांक loongson2_cpu_set_rate(अचिन्हित दीर्घ rate_khz)
अणु
	काष्ठा cpufreq_frequency_table *pos;
	पूर्णांक regval;

	cpufreq_क्रम_each_valid_entry(pos, loongson2_घड़ीmod_table)
		अगर (rate_khz == pos->frequency)
			अवरोध;
	अगर (rate_khz != pos->frequency)
		वापस -ENOTSUPP;

	regval = पढ़ोl(LOONGSON_CHIPCFG);
	regval = (regval & ~0x7) | (pos->driver_data - 1);
	ग_लिखोl(regval, LOONGSON_CHIPCFG);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(loongson2_cpu_set_rate);
