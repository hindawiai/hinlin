<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <elf.h>
#समावेश <पूर्णांकtypes.h>
#समावेश <sys/ttyशेषs.h>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <linux/bitops.h>
#समावेश "../../util/debug.h"
#समावेश "../../util/map.h"
#समावेश "../../util/dso.h"
#समावेश "../../util/symbol.h"
#समावेश "../browser.h"
#समावेश "../helpline.h"
#समावेश "../keysyms.h"
#समावेश "map.h"

#समावेश <linux/प्रकार.स>

काष्ठा map_browser अणु
	काष्ठा ui_browser b;
	काष्ठा map	  *map;
	u8		  addrlen;
पूर्ण;

अटल व्योम map_browser__ग_लिखो(काष्ठा ui_browser *browser, व्योम *nd, पूर्णांक row)
अणु
	काष्ठा symbol *sym = rb_entry(nd, काष्ठा symbol, rb_node);
	काष्ठा map_browser *mb = container_of(browser, काष्ठा map_browser, b);
	bool current_entry = ui_browser__is_current_entry(browser, row);
	पूर्णांक width;

	ui_browser__set_percent_color(browser, 0, current_entry);
	ui_browser__म_लिखो(browser, "%*" PRIx64 " %*" PRIx64 " %c ",
			   mb->addrlen, sym->start, mb->addrlen, sym->end,
			   sym->binding == STB_GLOBAL ? 'g' :
				sym->binding == STB_LOCAL  ? 'l' : 'w');
	width = browser->width - ((mb->addrlen * 2) + 4);
	अगर (width > 0)
		ui_browser__ग_लिखो_nstring(browser, sym->name, width);
पूर्ण

/* FIXME uber-kludgy, see comment on cmd_report... */
अटल u32 *symbol__browser_index(काष्ठा symbol *browser)
अणु
	वापस ((व्योम *)browser) - माप(काष्ठा rb_node) - माप(u32);
पूर्ण

अटल पूर्णांक map_browser__search(काष्ठा map_browser *browser)
अणु
	अक्षर target[512];
	काष्ठा symbol *sym;
	पूर्णांक err = ui_browser__input_winकरोw("Search by name/addr",
					   "Prefix with 0x to search by address",
					   target, "ENTER: OK, ESC: Cancel", 0);
	अगर (err != K_ENTER)
		वापस -1;

	अगर (target[0] == '0' && tolower(target[1]) == 'x') अणु
		u64 addr = म_से_अदीर्घl(target, शून्य, 16);
		sym = map__find_symbol(browser->map, addr);
	पूर्ण अन्यथा
		sym = map__find_symbol_by_name(browser->map, target);

	अगर (sym != शून्य) अणु
		u32 *idx = symbol__browser_index(sym);

		browser->b.top = &sym->rb_node;
		browser->b.index = browser->b.top_idx = *idx;
	पूर्ण अन्यथा
		ui_helpline__fpush("%s not found!", target);

	वापस 0;
पूर्ण

अटल पूर्णांक map_browser__run(काष्ठा map_browser *browser)
अणु
	पूर्णांक key;

	अगर (ui_browser__show(&browser->b, browser->map->dso->दीर्घ_name,
			     "Press ESC to exit, %s / to search",
			     verbose > 0 ? "" : "restart with -v to use") < 0)
		वापस -1;

	जबतक (1) अणु
		key = ui_browser__run(&browser->b, 0);

		चयन (key) अणु
		हाल '/':
			अगर (verbose > 0)
				map_browser__search(browser);
		शेष:
			अवरोध;
                हाल K_LEFT:
                हाल K_ESC:
                हाल 'q':
                हाल CTRL('c'):
                        जाओ out;
		पूर्ण
	पूर्ण
out:
	ui_browser__hide(&browser->b);
	वापस key;
पूर्ण

पूर्णांक map__browse(काष्ठा map *map)
अणु
	काष्ठा map_browser mb = अणु
		.b = अणु
			.entries = &map->dso->symbols,
			.refresh = ui_browser__rb_tree_refresh,
			.seek	 = ui_browser__rb_tree_seek,
			.ग_लिखो	 = map_browser__ग_लिखो,
		पूर्ण,
		.map = map,
	पूर्ण;
	काष्ठा rb_node *nd;
	अक्षर पंचांगp[BITS_PER_LONG / 4];
	u64 maxaddr = 0;

	क्रम (nd = rb_first(mb.b.entries); nd; nd = rb_next(nd)) अणु
		काष्ठा symbol *pos = rb_entry(nd, काष्ठा symbol, rb_node);

		अगर (maxaddr < pos->end)
			maxaddr = pos->end;
		अगर (verbose > 0) अणु
			u32 *idx = symbol__browser_index(pos);
			*idx = mb.b.nr_entries;
		पूर्ण
		++mb.b.nr_entries;
	पूर्ण

	mb.addrlen = snम_लिखो(पंचांगp, माप(पंचांगp), "%" PRIx64, maxaddr);
	वापस map_browser__run(&mb);
पूर्ण
