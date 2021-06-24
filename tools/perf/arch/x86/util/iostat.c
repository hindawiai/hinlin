<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * perf iostat
 *
 * Copyright (C) 2020, Intel Corporation
 *
 * Authors: Alexander Antonov <alexander.antonov@linux.पूर्णांकel.com>
 */

#समावेश <api/fs/fs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <सीमा.स>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <त्रुटिसं.स>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <dirent.h>
#समावेश <unistd.h>
#समावेश <मानककोष.स>
#समावेश <regex.h>
#समावेश "util/cpumap.h"
#समावेश "util/debug.h"
#समावेश "util/iostat.h"
#समावेश "util/counts.h"
#समावेश "path.h"

#अगर_अघोषित MAX_PATH
#घोषणा MAX_PATH 1024
#पूर्ण_अगर

#घोषणा UNCORE_IIO_PMU_PATH	"devices/uncore_iio_%d"
#घोषणा SYSFS_UNCORE_PMU_PATH	"%s/"UNCORE_IIO_PMU_PATH
#घोषणा PLATFORM_MAPPING_PATH	UNCORE_IIO_PMU_PATH"/die%d"

/*
 * Each metric requiries one IIO event which increments at every 4B transfer
 * in corresponding direction. The क्रमmulas to compute metrics are generic:
 *     #EventCount * 4B / (1024 * 1024)
 */
अटल स्थिर अक्षर * स्थिर iostat_metrics[] = अणु
	"Inbound Read(MB)",
	"Inbound Write(MB)",
	"Outbound Read(MB)",
	"Outbound Write(MB)",
पूर्ण;

अटल अंतरभूत पूर्णांक iostat_metrics_count(व्योम)
अणु
	वापस माप(iostat_metrics) / माप(अक्षर *);
पूर्ण

अटल स्थिर अक्षर *iostat_metric_by_idx(पूर्णांक idx)
अणु
	वापस *(iostat_metrics + idx % iostat_metrics_count());
पूर्ण

काष्ठा iio_root_port अणु
	u32 करोमुख्य;
	u8 bus;
	u8 die;
	u8 pmu_idx;
	पूर्णांक idx;
पूर्ण;

काष्ठा iio_root_ports_list अणु
	काष्ठा iio_root_port **rps;
	पूर्णांक nr_entries;
पूर्ण;

अटल काष्ठा iio_root_ports_list *root_ports;

अटल व्योम iio_root_port_show(खाता *output,
			       स्थिर काष्ठा iio_root_port * स्थिर rp)
अणु
	अगर (output && rp)
		ख_लिखो(output, "S%d-uncore_iio_%d<%04x:%02x>\n",
			rp->die, rp->pmu_idx, rp->करोमुख्य, rp->bus);
पूर्ण

अटल काष्ठा iio_root_port *iio_root_port_new(u32 करोमुख्य, u8 bus,
					       u8 die, u8 pmu_idx)
अणु
	काष्ठा iio_root_port *p = सुस्मृति(1, माप(*p));

	अगर (p) अणु
		p->करोमुख्य = करोमुख्य;
		p->bus = bus;
		p->die = die;
		p->pmu_idx = pmu_idx;
	पूर्ण
	वापस p;
पूर्ण

अटल व्योम iio_root_ports_list_मुक्त(काष्ठा iio_root_ports_list *list)
अणु
	पूर्णांक idx;

	अगर (list) अणु
		क्रम (idx = 0; idx < list->nr_entries; idx++)
			मुक्त(list->rps[idx]);
		मुक्त(list->rps);
		मुक्त(list);
	पूर्ण
पूर्ण

अटल काष्ठा iio_root_port *iio_root_port_find_by_notation(
	स्थिर काष्ठा iio_root_ports_list * स्थिर list, u32 करोमुख्य, u8 bus)
अणु
	पूर्णांक idx;
	काष्ठा iio_root_port *rp;

	अगर (list) अणु
		क्रम (idx = 0; idx < list->nr_entries; idx++) अणु
			rp = list->rps[idx];
			अगर (rp && rp->करोमुख्य == करोमुख्य && rp->bus == bus)
				वापस rp;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक iio_root_ports_list_insert(काष्ठा iio_root_ports_list *list,
				      काष्ठा iio_root_port * स्थिर rp)
अणु
	काष्ठा iio_root_port **पंचांगp_buf;

	अगर (list && rp) अणु
		rp->idx = list->nr_entries++;
		पंचांगp_buf = पुनः_स्मृति(list->rps,
				  list->nr_entries * माप(*list->rps));
		अगर (!पंचांगp_buf) अणु
			pr_err("Failed to realloc memory\n");
			वापस -ENOMEM;
		पूर्ण
		पंचांगp_buf[rp->idx] = rp;
		list->rps = पंचांगp_buf;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक iio_mapping(u8 pmu_idx, काष्ठा iio_root_ports_list * स्थिर list)
अणु
	अक्षर *buf;
	अक्षर path[MAX_PATH];
	u32 करोमुख्य;
	u8 bus;
	काष्ठा iio_root_port *rp;
	माप_प्रकार size;
	पूर्णांक ret;

	क्रम (पूर्णांक die = 0; die < cpu__max_node(); die++) अणु
		scnम_लिखो(path, MAX_PATH, PLATFORM_MAPPING_PATH, pmu_idx, die);
		अगर (sysfs__पढ़ो_str(path, &buf, &size) < 0) अणु
			अगर (pmu_idx)
				जाओ out;
			pr_err("Mode iostat is not supported\n");
			वापस -1;
		पूर्ण
		ret = माला_पूछो(buf, "%04x:%02hhx", &करोमुख्य, &bus);
		मुक्त(buf);
		अगर (ret != 2) अणु
			pr_err("Invalid mapping data: iio_%d; die%d\n",
			       pmu_idx, die);
			वापस -1;
		पूर्ण
		rp = iio_root_port_new(करोमुख्य, bus, die, pmu_idx);
		अगर (!rp || iio_root_ports_list_insert(list, rp)) अणु
			मुक्त(rp);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
out:
	वापस 0;
पूर्ण

अटल u8 iio_pmu_count(व्योम)
अणु
	u8 pmu_idx = 0;
	अक्षर path[MAX_PATH];
	स्थिर अक्षर *sysfs = sysfs__mountpoपूर्णांक();

	अगर (sysfs) अणु
		क्रम (;; pmu_idx++) अणु
			snम_लिखो(path, माप(path), SYSFS_UNCORE_PMU_PATH,
				 sysfs, pmu_idx);
			अगर (access(path, F_OK) != 0)
				अवरोध;
		पूर्ण
	पूर्ण
	वापस pmu_idx;
पूर्ण

अटल पूर्णांक iio_root_ports_scan(काष्ठा iio_root_ports_list **list)
अणु
	पूर्णांक ret = -ENOMEM;
	काष्ठा iio_root_ports_list *पंचांगp_list;
	u8 pmu_count = iio_pmu_count();

	अगर (!pmu_count) अणु
		pr_err("Unsupported uncore pmu configuration\n");
		वापस -1;
	पूर्ण

	पंचांगp_list = सुस्मृति(1, माप(*पंचांगp_list));
	अगर (!पंचांगp_list)
		जाओ err;

	क्रम (u8 pmu_idx = 0; pmu_idx < pmu_count; pmu_idx++) अणु
		ret = iio_mapping(pmu_idx, पंचांगp_list);
		अगर (ret)
			अवरोध;
	पूर्ण
err:
	अगर (!ret)
		*list = पंचांगp_list;
	अन्यथा
		iio_root_ports_list_मुक्त(पंचांगp_list);

	वापस ret;
पूर्ण

अटल पूर्णांक iio_root_port_parse_str(u32 *करोमुख्य, u8 *bus, अक्षर *str)
अणु
	पूर्णांक ret;
	regex_t regex;
	/*
	 * Expected क्रमmat करोमुख्य:bus:
	 * Valid करोमुख्य range [0:ffff]
	 * Valid bus range [0:ff]
	 * Example: 0000:af, 0:3d, 01:7
	 */
	regcomp(&regex, "^([a-f0-9A-F]अणु1,पूर्ण):([a-f0-9A-F]अणु1,2पूर्ण)", REG_EXTENDED);
	ret = regexec(&regex, str, 0, शून्य, 0);
	अगर (ret || माला_पूछो(str, "%08x:%02hhx", करोमुख्य, bus) != 2)
		pr_warning("Unrecognized root port format: %s\n"
			   "Please use the following format:\n"
			   "\t [domain]:[bus]\n"
			   "\t for example: 0000:3d\n", str);

	regमुक्त(&regex);
	वापस ret;
पूर्ण

अटल पूर्णांक iio_root_ports_list_filter(काष्ठा iio_root_ports_list **list,
				      स्थिर अक्षर *filter)
अणु
	अक्षर *tok, *पंचांगp, *filter_copy = शून्य;
	काष्ठा iio_root_port *rp;
	u32 करोमुख्य;
	u8 bus;
	पूर्णांक ret = -ENOMEM;
	काष्ठा iio_root_ports_list *पंचांगp_list = सुस्मृति(1, माप(*पंचांगp_list));

	अगर (!पंचांगp_list)
		जाओ err;

	filter_copy = strdup(filter);
	अगर (!filter_copy)
		जाओ err;

	क्रम (tok = म_मोहर_r(filter_copy, ",", &पंचांगp); tok;
	     tok = म_मोहर_r(शून्य, ",", &पंचांगp)) अणु
		अगर (!iio_root_port_parse_str(&करोमुख्य, &bus, tok)) अणु
			rp = iio_root_port_find_by_notation(*list, करोमुख्य, bus);
			अगर (rp) अणु
				(*list)->rps[rp->idx] = शून्य;
				ret = iio_root_ports_list_insert(पंचांगp_list, rp);
				अगर (ret) अणु
					मुक्त(rp);
					जाओ err;
				पूर्ण
			पूर्ण अन्यथा अगर (!iio_root_port_find_by_notation(पंचांगp_list,
								   करोमुख्य, bus))
				pr_warning("Root port %04x:%02x were not found\n",
					   करोमुख्य, bus);
		पूर्ण
	पूर्ण

	अगर (पंचांगp_list->nr_entries == 0) अणु
		pr_err("Requested root ports were not found\n");
		ret = -EINVAL;
	पूर्ण
err:
	iio_root_ports_list_मुक्त(*list);
	अगर (ret)
		iio_root_ports_list_मुक्त(पंचांगp_list);
	अन्यथा
		*list = पंचांगp_list;

	मुक्त(filter_copy);
	वापस ret;
पूर्ण

अटल पूर्णांक iostat_event_group(काष्ठा evlist *evl,
			      काष्ठा iio_root_ports_list *list)
अणु
	पूर्णांक ret;
	पूर्णांक idx;
	स्थिर अक्षर *iostat_cmd_ढाँचा =
	"अणुuncore_iio_%x/event=0x83,umask=0x04,ch_mask=0xF,fc_mask=0x07/,\
	  uncore_iio_%x/event=0x83,umask=0x01,ch_mask=0xF,fc_mask=0x07/,\
	  uncore_iio_%x/event=0xc0,umask=0x04,ch_mask=0xF,fc_mask=0x07/,\
	  uncore_iio_%x/event=0xc0,umask=0x01,ch_mask=0xF,fc_mask=0x07/पूर्ण";
	स्थिर पूर्णांक len_ढाँचा = म_माप(iostat_cmd_ढाँचा) + 1;
	काष्ठा evsel *evsel = शून्य;
	पूर्णांक metrics_count = iostat_metrics_count();
	अक्षर *iostat_cmd = सुस्मृति(len_ढाँचा, 1);

	अगर (!iostat_cmd)
		वापस -ENOMEM;

	क्रम (idx = 0; idx < list->nr_entries; idx++) अणु
		प्र_लिखो(iostat_cmd, iostat_cmd_ढाँचा,
			list->rps[idx]->pmu_idx, list->rps[idx]->pmu_idx,
			list->rps[idx]->pmu_idx, list->rps[idx]->pmu_idx);
		ret = parse_events(evl, iostat_cmd, शून्य);
		अगर (ret)
			जाओ err;
	पूर्ण

	evlist__क्रम_each_entry(evl, evsel) अणु
		evsel->priv = list->rps[evsel->idx / metrics_count];
	पूर्ण
	list->nr_entries = 0;
err:
	iio_root_ports_list_मुक्त(list);
	मुक्त(iostat_cmd);
	वापस ret;
पूर्ण

पूर्णांक iostat_prepare(काष्ठा evlist *evlist, काष्ठा perf_stat_config *config)
अणु
	अगर (evlist->core.nr_entries > 0) अणु
		pr_warning("The -e and -M options are not supported."
			   "All chosen events/metrics will be dropped\n");
		evlist__delete(evlist);
		evlist = evlist__new();
		अगर (!evlist)
			वापस -ENOMEM;
	पूर्ण

	config->metric_only = true;
	config->aggr_mode = AGGR_GLOBAL;

	वापस iostat_event_group(evlist, root_ports);
पूर्ण

पूर्णांक iostat_parse(स्थिर काष्ठा option *opt, स्थिर अक्षर *str,
		 पूर्णांक unset __maybe_unused)
अणु
	पूर्णांक ret;
	काष्ठा perf_stat_config *config = (काष्ठा perf_stat_config *)opt->data;

	ret = iio_root_ports_scan(&root_ports);
	अगर (!ret) अणु
		config->iostat_run = true;
		अगर (!str)
			iostat_mode = IOSTAT_RUN;
		अन्यथा अगर (!म_भेद(str, "list"))
			iostat_mode = IOSTAT_LIST;
		अन्यथा अणु
			iostat_mode = IOSTAT_RUN;
			ret = iio_root_ports_list_filter(&root_ports, str);
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

व्योम iostat_list(काष्ठा evlist *evlist, काष्ठा perf_stat_config *config)
अणु
	काष्ठा evsel *evsel;
	काष्ठा iio_root_port *rp = शून्य;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर (rp != evsel->priv) अणु
			rp = evsel->priv;
			iio_root_port_show(config->output, rp);
		पूर्ण
	पूर्ण
पूर्ण

व्योम iostat_release(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel;
	काष्ठा iio_root_port *rp = शून्य;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर (rp != evsel->priv) अणु
			rp = evsel->priv;
			मुक्त(evsel->priv);
		पूर्ण
	पूर्ण
पूर्ण

व्योम iostat_prefix(काष्ठा evlist *evlist,
		   काष्ठा perf_stat_config *config,
		   अक्षर *prefix, काष्ठा बारpec *ts)
अणु
	काष्ठा iio_root_port *rp = evlist->selected->priv;

	अगर (rp) अणु
		अगर (ts)
			प्र_लिखो(prefix, "%6lu.%09lu%s%04x:%02x%s",
				ts->tv_sec, ts->tv_nsec,
				config->csv_sep, rp->करोमुख्य, rp->bus,
				config->csv_sep);
		अन्यथा
			प्र_लिखो(prefix, "%04x:%02x%s", rp->करोमुख्य, rp->bus,
				config->csv_sep);
	पूर्ण
पूर्ण

व्योम iostat_prपूर्णांक_header_prefix(काष्ठा perf_stat_config *config)
अणु
	अगर (config->csv_output)
		ख_माला_दो("port,", config->output);
	अन्यथा अगर (config->पूर्णांकerval)
		ख_लिखो(config->output, "#          time    port         ");
	अन्यथा
		ख_लिखो(config->output, "   port         ");
पूर्ण

व्योम iostat_prपूर्णांक_metric(काष्ठा perf_stat_config *config, काष्ठा evsel *evsel,
			 काष्ठा perf_stat_output_ctx *out)
अणु
	द्विगुन iostat_value = 0;
	u64 prev_count_val = 0;
	स्थिर अक्षर *iostat_metric = iostat_metric_by_idx(evsel->idx);
	u8 die = ((काष्ठा iio_root_port *)evsel->priv)->die;
	काष्ठा perf_counts_values *count = perf_counts(evsel->counts, die, 0);

	अगर (count->run && count->ena) अणु
		अगर (evsel->prev_raw_counts && !out->क्रमce_header) अणु
			काष्ठा perf_counts_values *prev_count =
				perf_counts(evsel->prev_raw_counts, die, 0);

			prev_count_val = prev_count->val;
			prev_count->val = count->val;
		पूर्ण
		iostat_value = (count->val - prev_count_val) /
			       ((द्विगुन) count->run / count->ena);
	पूर्ण
	out->prपूर्णांक_metric(config, out->ctx, शून्य, "%8.0f", iostat_metric,
			  iostat_value / (256 * 1024));
पूर्ण

व्योम iostat_prपूर्णांक_counters(काष्ठा evlist *evlist,
			   काष्ठा perf_stat_config *config, काष्ठा बारpec *ts,
			   अक्षर *prefix, iostat_prपूर्णांक_counter_t prपूर्णांक_cnt_cb)
अणु
	व्योम *perf_device = शून्य;
	काष्ठा evsel *counter = evlist__first(evlist);

	evlist__set_selected(evlist, counter);
	iostat_prefix(evlist, config, prefix, ts);
	ख_लिखो(config->output, "%s", prefix);
	evlist__क्रम_each_entry(evlist, counter) अणु
		perf_device = evlist->selected->priv;
		अगर (perf_device && perf_device != counter->priv) अणु
			evlist__set_selected(evlist, counter);
			iostat_prefix(evlist, config, prefix, ts);
			ख_लिखो(config->output, "\n%s", prefix);
		पूर्ण
		prपूर्णांक_cnt_cb(config, counter, prefix);
	पूर्ण
	ख_अक्षर_दो('\n', config->output);
पूर्ण
