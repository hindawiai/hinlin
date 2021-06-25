<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_COLOR_H
#घोषणा __PERF_COLOR_H

#समावेश <मानकपन.स>
#समावेश <मानकतर्क.स>

/* "\033[1;38;5;2xx;48;5;2xxm\0" is 23 bytes */
#घोषणा COLOR_MAXLEN 24

#घोषणा PERF_COLOR_NORMAL	""
#घोषणा PERF_COLOR_RESET	"\033[m"
#घोषणा PERF_COLOR_BOLD		"\033[1m"
#घोषणा PERF_COLOR_RED		"\033[31m"
#घोषणा PERF_COLOR_GREEN	"\033[32m"
#घोषणा PERF_COLOR_YELLOW	"\033[33m"
#घोषणा PERF_COLOR_BLUE		"\033[34m"
#घोषणा PERF_COLOR_MAGENTA	"\033[35m"
#घोषणा PERF_COLOR_CYAN		"\033[36m"
#घोषणा PERF_COLOR_BG_RED	"\033[41m"

#घोषणा MIN_GREEN	0.5
#घोषणा MIN_RED		5.0

/*
 * This variable stores the value of color.ui
 */
बाह्य पूर्णांक perf_use_color_शेष;


/*
 * Use this instead of perf_शेष_config अगर you need the value of color.ui.
 */
पूर्णांक perf_color_शेष_config(स्थिर अक्षर *var, स्थिर अक्षर *value, व्योम *cb);

पूर्णांक perf_config_colorbool(स्थिर अक्षर *var, स्थिर अक्षर *value, पूर्णांक मानक_निकास_is_tty);
पूर्णांक color_vsnम_लिखो(अक्षर *bf, माप_प्रकार size, स्थिर अक्षर *color,
		    स्थिर अक्षर *fmt, बहु_सूची args);
पूर्णांक color_भख_लिखो(खाता *fp, स्थिर अक्षर *color, स्थिर अक्षर *fmt, बहु_सूची args);
पूर्णांक color_ख_लिखो(खाता *fp, स्थिर अक्षर *color, स्थिर अक्षर *fmt, ...);
पूर्णांक color_snम_लिखो(अक्षर *bf, माप_प्रकार size, स्थिर अक्षर *color, स्थिर अक्षर *fmt, ...);
पूर्णांक color_ख_डालो_lines(खाता *fp, स्थिर अक्षर *color, माप_प्रकार count, स्थिर अक्षर *buf);
पूर्णांक value_color_snम_लिखो(अक्षर *bf, माप_प्रकार size, स्थिर अक्षर *fmt, द्विगुन value);
पूर्णांक percent_color_snम_लिखो(अक्षर *bf, माप_प्रकार size, स्थिर अक्षर *fmt, ...);
पूर्णांक percent_color_len_snम_लिखो(अक्षर *bf, माप_प्रकार size, स्थिर अक्षर *fmt, ...);
पूर्णांक percent_color_ख_लिखो(खाता *fp, स्थिर अक्षर *fmt, द्विगुन percent);
स्थिर अक्षर *get_percent_color(द्विगुन percent);

#पूर्ण_अगर /* __PERF_COLOR_H */
