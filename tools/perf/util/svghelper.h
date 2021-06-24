<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_SVGHELPER_H
#घोषणा __PERF_SVGHELPER_H

#समावेश <linux/types.h>

काष्ठा perf_env;

व्योम खोलो_svg(स्थिर अक्षर *filename, पूर्णांक cpus, पूर्णांक rows, u64 start, u64 end);
व्योम svg_ubox(पूर्णांक Yslot, u64 start, u64 end, द्विगुन height, स्थिर अक्षर *type, पूर्णांक fd, पूर्णांक err, पूर्णांक merges);
व्योम svg_lbox(पूर्णांक Yslot, u64 start, u64 end, द्विगुन height, स्थिर अक्षर *type, पूर्णांक fd, पूर्णांक err, पूर्णांक merges);
व्योम svg_fbox(पूर्णांक Yslot, u64 start, u64 end, द्विगुन height, स्थिर अक्षर *type, पूर्णांक fd, पूर्णांक err, पूर्णांक merges);
व्योम svg_box(पूर्णांक Yslot, u64 start, u64 end, स्थिर अक्षर *type);
व्योम svg_blocked(पूर्णांक Yslot, पूर्णांक cpu, u64 start, u64 end, स्थिर अक्षर *backtrace);
व्योम svg_running(पूर्णांक Yslot, पूर्णांक cpu, u64 start, u64 end, स्थिर अक्षर *backtrace);
व्योम svg_रुकोing(पूर्णांक Yslot, पूर्णांक cpu, u64 start, u64 end, स्थिर अक्षर *backtrace);
व्योम svg_cpu_box(पूर्णांक cpu, u64 max_frequency, u64 turbo_frequency);


व्योम svg_process(पूर्णांक cpu, u64 start, u64 end, पूर्णांक pid, स्थिर अक्षर *name, स्थिर अक्षर *backtrace);
व्योम svg_cstate(पूर्णांक cpu, u64 start, u64 end, पूर्णांक type);
व्योम svg_pstate(पूर्णांक cpu, u64 start, u64 end, u64 freq);


व्योम svg_समय_grid(द्विगुन min_thickness);
व्योम svg_io_legenda(व्योम);
व्योम svg_legenda(व्योम);
व्योम svg_wakeline(u64 start, पूर्णांक row1, पूर्णांक row2, स्थिर अक्षर *backtrace);
व्योम svg_partial_wakeline(u64 start, पूर्णांक row1, अक्षर *desc1, पूर्णांक row2, अक्षर *desc2, स्थिर अक्षर *backtrace);
व्योम svg_पूर्णांकerrupt(u64 start, पूर्णांक row, स्थिर अक्षर *backtrace);
व्योम svg_text(पूर्णांक Yslot, u64 start, स्थिर अक्षर *text);
व्योम svg_बंद(व्योम);
पूर्णांक svg_build_topology_map(काष्ठा perf_env *env);

बाह्य पूर्णांक svg_page_width;
बाह्य u64 svg_highlight;
बाह्य स्थिर अक्षर *svg_highlight_name;

#पूर्ण_अगर /* __PERF_SVGHELPER_H */
