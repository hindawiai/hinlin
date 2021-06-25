<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
अटल पूर्णांक find_map(व्योम **start, व्योम **end, स्थिर अक्षर *name)
अणु
	खाता *maps;
	अक्षर line[128];
	पूर्णांक found = 0;

	maps = ख_खोलो("/proc/self/maps", "r");
	अगर (!maps) अणु
		ख_लिखो(मानक_त्रुटि, "cannot open maps\n");
		वापस -1;
	पूर्ण

	जबतक (!found && ख_माला_लो(line, माप(line), maps)) अणु
		पूर्णांक m = -1;

		/* We care only about निजी r-x mappings. */
		अगर (2 != माला_पूछो(line, "%p-%p r-xp %*x %*x:%*x %*u %n",
				start, end, &m))
			जारी;
		अगर (m < 0)
			जारी;

		अगर (!म_भेदन(&line[m], name, म_माप(name)))
			found = 1;
	पूर्ण

	ख_बंद(maps);
	वापस !found;
पूर्ण
