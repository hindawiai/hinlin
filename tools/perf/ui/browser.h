<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PERF_UI_BROWSER_H_
#घोषणा _PERF_UI_BROWSER_H_ 1

#समावेश <linux/types.h>
#समावेश <मानकतर्क.स>
#समावेश <sys/types.h>

#घोषणा HE_COLORSET_TOP		50
#घोषणा HE_COLORSET_MEDIUM	51
#घोषणा HE_COLORSET_NORMAL	52
#घोषणा HE_COLORSET_SELECTED	53
#घोषणा HE_COLORSET_JUMP_ARROWS	54
#घोषणा HE_COLORSET_ADDR	55
#घोषणा HE_COLORSET_ROOT	56

काष्ठा ui_browser अणु
	u64	      index, top_idx;
	व्योम	      *top, *entries;
	u16	      y, x, width, height, rows, columns, horiz_scroll;
	u8	      extra_title_lines;
	पूर्णांक	      current_color;
	व्योम	      *priv;
	स्थिर अक्षर    *title;
	अक्षर	      *helpline;
	स्थिर अक्षर    *no_samples_msg;
	व्योम 	      (*refresh_dimensions)(काष्ठा ui_browser *browser);
	अचिन्हित पूर्णांक  (*refresh)(काष्ठा ui_browser *browser);
	व्योम	      (*ग_लिखो)(काष्ठा ui_browser *browser, व्योम *entry, पूर्णांक row);
	व्योम	      (*seek)(काष्ठा ui_browser *browser, off_t offset, पूर्णांक whence);
	bool	      (*filter)(काष्ठा ui_browser *browser, व्योम *entry);
	u32	      nr_entries;
	bool	      navkeypressed;
	bool	      use_navkeypressed;
पूर्ण;

पूर्णांक  ui_browser__set_color(काष्ठा ui_browser *browser, पूर्णांक color);
व्योम ui_browser__set_percent_color(काष्ठा ui_browser *browser,
				   द्विगुन percent, bool current);
bool ui_browser__is_current_entry(काष्ठा ui_browser *browser, अचिन्हित row);
व्योम ui_browser__refresh_dimensions(काष्ठा ui_browser *browser);
व्योम ui_browser__reset_index(काष्ठा ui_browser *browser);

व्योम ui_browser__जाओrc_title(काष्ठा ui_browser *browser, पूर्णांक y, पूर्णांक x);
व्योम ui_browser__जाओrc(काष्ठा ui_browser *browser, पूर्णांक y, पूर्णांक x);
व्योम ui_browser__ग_लिखो_nstring(काष्ठा ui_browser *browser, स्थिर अक्षर *msg,
			       अचिन्हित पूर्णांक width);
व्योम ui_browser__भ_लिखो(काष्ठा ui_browser *browser, स्थिर अक्षर *fmt, बहु_सूची args);
व्योम ui_browser__म_लिखो(काष्ठा ui_browser *browser, स्थिर अक्षर *fmt, ...);
व्योम ui_browser__ग_लिखो_graph(काष्ठा ui_browser *browser, पूर्णांक graph);
व्योम __ui_browser__line_arrow(काष्ठा ui_browser *browser, अचिन्हित पूर्णांक column,
			      u64 start, u64 end);
व्योम ui_browser__mark_fused(काष्ठा ui_browser *browser, अचिन्हित पूर्णांक column,
			    अचिन्हित पूर्णांक row, bool arrow_करोwn);
व्योम __ui_browser__show_title(काष्ठा ui_browser *browser, स्थिर अक्षर *title);
व्योम ui_browser__show_title(काष्ठा ui_browser *browser, स्थिर अक्षर *title);
पूर्णांक ui_browser__show(काष्ठा ui_browser *browser, स्थिर अक्षर *title,
		     स्थिर अक्षर *helpline, ...);
व्योम ui_browser__hide(काष्ठा ui_browser *browser);
पूर्णांक ui_browser__refresh(काष्ठा ui_browser *browser);
पूर्णांक ui_browser__run(काष्ठा ui_browser *browser, पूर्णांक delay_secs);
व्योम ui_browser__update_nr_entries(काष्ठा ui_browser *browser, u32 nr_entries);
व्योम ui_browser__handle_resize(काष्ठा ui_browser *browser);
व्योम __ui_browser__vline(काष्ठा ui_browser *browser, अचिन्हित पूर्णांक column,
			 u16 start, u16 end);

पूर्णांक ui_browser__warning(काष्ठा ui_browser *browser, पूर्णांक समयout,
			स्थिर अक्षर *क्रमmat, ...);
पूर्णांक ui_browser__help_winकरोw(काष्ठा ui_browser *browser, स्थिर अक्षर *text);
bool ui_browser__dialog_yesno(काष्ठा ui_browser *browser, स्थिर अक्षर *text);
पूर्णांक ui_browser__input_winकरोw(स्थिर अक्षर *title, स्थिर अक्षर *text, अक्षर *input,
			     स्थिर अक्षर *निकास_msg, पूर्णांक delay_sec);
काष्ठा perf_env;
पूर्णांक tui__header_winकरोw(काष्ठा perf_env *env);

व्योम ui_browser__argv_seek(काष्ठा ui_browser *browser, off_t offset, पूर्णांक whence);
अचिन्हित पूर्णांक ui_browser__argv_refresh(काष्ठा ui_browser *browser);

व्योम ui_browser__rb_tree_seek(काष्ठा ui_browser *browser, off_t offset, पूर्णांक whence);
अचिन्हित पूर्णांक ui_browser__rb_tree_refresh(काष्ठा ui_browser *browser);

व्योम ui_browser__list_head_seek(काष्ठा ui_browser *browser, off_t offset, पूर्णांक whence);
अचिन्हित पूर्णांक ui_browser__list_head_refresh(काष्ठा ui_browser *browser);

व्योम ui_browser__init(व्योम);
#पूर्ण_अगर /* _PERF_UI_BROWSER_H_ */
