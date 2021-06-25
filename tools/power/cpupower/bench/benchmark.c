<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*  cpufreq-bench CPUFreq microbenchmark
 *
 *  Copyright (C) 2008 Christian Kornacker <ckornacker@suse.de>
 */

#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <गणित.स>

#समावेश "config.h"
#समावेश "system.h"
#समावेश "benchmark.h"

/* Prपूर्णांक out progress अगर we log पूर्णांकo a file */
#घोषणा show_progress(total_समय, progress_समय)	\
अगर (config->output != मानक_निकास) अणु				\
	ख_लिखो(मानक_निकास, "Progress: %02lu %%\r",		\
		(progress_समय * 100) / total_समय);	\
	ख_साफ(मानक_निकास);					\
पूर्ण

/**
 * compute how many rounds of calculation we should करो
 * to get the given load समय
 *
 * @param load aimed load समय in तगs
 *
 * @retval rounds of calculation
 **/

अचिन्हित पूर्णांक calculate_बारpace(दीर्घ load, काष्ठा config *config)
अणु
	पूर्णांक i;
	दीर्घ दीर्घ now, then;
	अचिन्हित पूर्णांक estimated = GAUGECOUNT;
	अचिन्हित पूर्णांक rounds = 0;
	अचिन्हित पूर्णांक समयd = 0;

	अगर (config->verbose)
		म_लिखो("calibrating load of %lius, please wait...\n", load);

	/* get the initial calculation समय क्रम a specअगरic number of rounds */
	now = get_समय();
	ROUNDS(estimated);
	then = get_समय();

	समयd = (अचिन्हित पूर्णांक)(then - now);

	/* approximation of the wanted load समय by comparing with the
	 * initial calculation समय */
	क्रम (i = 0; i < 4; i++) अणु
		rounds = (अचिन्हित पूर्णांक)(load * estimated / समयd);
		dम_लिखो("calibrating with %u rounds\n", rounds);
		now = get_समय();
		ROUNDS(rounds);
		then = get_समय();

		समयd = (अचिन्हित पूर्णांक)(then - now);
		estimated = rounds;
	पूर्ण
	अगर (config->verbose)
		म_लिखो("calibration done\n");

	वापस estimated;
पूर्ण

/**
 * benchmark
 * generates a specअगरic sleep an load समय with the perक्रमmance
 * governor and compares the used समय क्रम same calculations करोne
 * with the configured घातersave governor
 *
 * @param config config values क्रम the benchmark
 *
 **/

व्योम start_benchmark(काष्ठा config *config)
अणु
	अचिन्हित पूर्णांक _round, cycle;
	दीर्घ दीर्घ now, then;
	दीर्घ sleep_समय = 0, load_समय = 0;
	दीर्घ perक्रमmance_समय = 0, घातersave_समय = 0;
	अचिन्हित पूर्णांक calculations;
	अचिन्हित दीर्घ total_समय = 0, progress_समय = 0;

	sleep_समय = config->sleep;
	load_समय = config->load;

	/* For the progress bar */
	क्रम (_round = 1; _round <= config->rounds; _round++)
		total_समय += _round * (config->sleep + config->load);
	total_समय *= 2; /* घातersave and perक्रमmance cycles */

	क्रम (_round = 0; _round < config->rounds; _round++) अणु
		perक्रमmance_समय = 0LL;
		घातersave_समय = 0LL;

		show_progress(total_समय, progress_समय);

		/* set the cpufreq governor to "performance" which disables
		 * P-State चयनing. */
		अगर (set_cpufreq_governor("performance", config->cpu) != 0)
			वापस;

		/* calibrate the calculation समय. the resulting calculation
		 * _rounds should produce a load which matches the configured
		 * load समय */
		calculations = calculate_बारpace(load_समय, config);

		अगर (config->verbose)
			म_लिखो("_round %i: doing %u cycles with %u calculations"
			       " for %lius\n", _round + 1, config->cycles,
			       calculations, load_समय);

		ख_लिखो(config->output, "%u %li %li ",
			_round, load_समय, sleep_समय);

		अगर (config->verbose)
			म_लिखो("average: %lius, rps:%li\n",
				load_समय / calculations,
				1000000 * calculations / load_समय);

		/* करो some sleep/load cycles with the perक्रमmance governor */
		क्रम (cycle = 0; cycle < config->cycles; cycle++) अणु
			now = get_समय();
			usleep(sleep_समय);
			ROUNDS(calculations);
			then = get_समय();
			perक्रमmance_समय += then - now - sleep_समय;
			अगर (config->verbose)
				म_लिखो("performance cycle took %lius, "
					"sleep: %lius, "
					"load: %lius, rounds: %u\n",
					(दीर्घ)(then - now), sleep_समय,
					load_समय, calculations);
		पूर्ण
		ख_लिखो(config->output, "%li ",
			perक्रमmance_समय / config->cycles);

		progress_समय += sleep_समय + load_समय;
		show_progress(total_समय, progress_समय);

		/* set the घातersave governor which activates P-State चयनing
		 * again */
		अगर (set_cpufreq_governor(config->governor, config->cpu) != 0)
			वापस;

		/* again, करो some sleep/load cycles with the
		 * घातersave governor */
		क्रम (cycle = 0; cycle < config->cycles; cycle++) अणु
			now = get_समय();
			usleep(sleep_समय);
			ROUNDS(calculations);
			then = get_समय();
			घातersave_समय += then - now - sleep_समय;
			अगर (config->verbose)
				म_लिखो("powersave cycle took %lius, "
					"sleep: %lius, "
					"load: %lius, rounds: %u\n",
					(दीर्घ)(then - now), sleep_समय,
					load_समय, calculations);
		पूर्ण

		progress_समय += sleep_समय + load_समय;

		/* compare the average sleep/load cycles  */
		ख_लिखो(config->output, "%li ",
			घातersave_समय / config->cycles);
		ख_लिखो(config->output, "%.3f\n",
			perक्रमmance_समय * 100.0 / घातersave_समय);
		ख_साफ(config->output);

		अगर (config->verbose)
			म_लिखो("performance is at %.2f%%\n",
				perक्रमmance_समय * 100.0 / घातersave_समय);

		sleep_समय += config->sleep_step;
		load_समय += config->load_step;
	पूर्ण
पूर्ण
