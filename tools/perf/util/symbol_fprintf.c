<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <elf.h>
#समावेश <पूर्णांकtypes.h>
#समावेश <मानकपन.स>

#समावेश "dso.h"
#समावेश "map.h"
#समावेश "symbol.h"

माप_प्रकार symbol__ख_लिखो(काष्ठा symbol *sym, खाता *fp)
अणु
	वापस ख_लिखो(fp, " %" PRIx64 "-%" PRIx64 " %c %s\n",
		       sym->start, sym->end,
		       sym->binding == STB_GLOBAL ? 'g' :
		       sym->binding == STB_LOCAL  ? 'l' : 'w',
		       sym->name);
पूर्ण

माप_प्रकार __symbol__ख_लिखो_symname_offs(स्थिर काष्ठा symbol *sym,
				      स्थिर काष्ठा addr_location *al,
				      bool unknown_as_addr,
				      bool prपूर्णांक_offsets, खाता *fp)
अणु
	अचिन्हित दीर्घ offset;
	माप_प्रकार length;

	अगर (sym) अणु
		length = ख_लिखो(fp, "%s", sym->name);
		अगर (al && prपूर्णांक_offsets) अणु
			अगर (al->addr < sym->end)
				offset = al->addr - sym->start;
			अन्यथा
				offset = al->addr - al->map->start - sym->start;
			length += ख_लिखो(fp, "+0x%lx", offset);
		पूर्ण
		वापस length;
	पूर्ण अन्यथा अगर (al && unknown_as_addr)
		वापस ख_लिखो(fp, "[%#" PRIx64 "]", al->addr);
	अन्यथा
		वापस ख_लिखो(fp, "[unknown]");
पूर्ण

माप_प्रकार symbol__ख_लिखो_symname_offs(स्थिर काष्ठा symbol *sym,
				    स्थिर काष्ठा addr_location *al,
				    खाता *fp)
अणु
	वापस __symbol__ख_लिखो_symname_offs(sym, al, false, true, fp);
पूर्ण

माप_प्रकार __symbol__ख_लिखो_symname(स्थिर काष्ठा symbol *sym,
				 स्थिर काष्ठा addr_location *al,
				 bool unknown_as_addr, खाता *fp)
अणु
	वापस __symbol__ख_लिखो_symname_offs(sym, al, unknown_as_addr, false, fp);
पूर्ण

माप_प्रकार symbol__ख_लिखो_symname(स्थिर काष्ठा symbol *sym, खाता *fp)
अणु
	वापस __symbol__ख_लिखो_symname_offs(sym, शून्य, false, false, fp);
पूर्ण

माप_प्रकार dso__ख_लिखो_symbols_by_name(काष्ठा dso *dso,
				    खाता *fp)
अणु
	माप_प्रकार ret = 0;
	काष्ठा rb_node *nd;
	काष्ठा symbol_name_rb_node *pos;

	क्रम (nd = rb_first_cached(&dso->symbol_names); nd; nd = rb_next(nd)) अणु
		pos = rb_entry(nd, काष्ठा symbol_name_rb_node, rb_node);
		ret += ख_लिखो(fp, "%s\n", pos->sym.name);
	पूर्ण

	वापस ret;
पूर्ण
