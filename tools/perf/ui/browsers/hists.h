<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PERF_UI_BROWSER_HISTS_H_
#घोषणा _PERF_UI_BROWSER_HISTS_H_ 1

#समावेश "ui/browser.h"

काष्ठा annotation_options;
काष्ठा evsel;

काष्ठा hist_browser अणु
	काष्ठा ui_browser   b;
	काष्ठा hists	    *hists;
	काष्ठा hist_entry   *he_selection;
	काष्ठा map_symbol   *selection;
	काष्ठा hist_browser_समयr *hbt;
	काष्ठा pstack	    *pstack;
	काष्ठा perf_env	    *env;
	काष्ठा annotation_options *annotation_opts;
	काष्ठा evsel	    *block_evsel;
	पूर्णांक		     prपूर्णांक_seq;
	bool		     show_dso;
	bool		     show_headers;
	भग्न		     min_pcnt;
	u64		     nr_non_filtered_entries;
	u64		     nr_hierarchy_entries;
	u64		     nr_callchain_rows;
	bool		     c2c_filter;

	/* Get title string. */
	पूर्णांक                  (*title)(काष्ठा hist_browser *browser,
			     अक्षर *bf, माप_प्रकार size);
पूर्ण;

काष्ठा hist_browser *hist_browser__new(काष्ठा hists *hists);
व्योम hist_browser__delete(काष्ठा hist_browser *browser);
पूर्णांक hist_browser__run(काष्ठा hist_browser *browser, स्थिर अक्षर *help,
		      bool warn_lost_event, पूर्णांक key);
व्योम hist_browser__init(काष्ठा hist_browser *browser,
			काष्ठा hists *hists);
#पूर्ण_अगर /* _PERF_UI_BROWSER_HISTS_H_ */
