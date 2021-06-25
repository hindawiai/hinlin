<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Manage prपूर्णांकing of source lines
 * Copyright (c) 2017, Intel Corporation.
 * Author: Andi Kleen
 */
#समावेश <linux/list.h>
#समावेश <linux/zभाग.स>
#समावेश <मानककोष.स>
#समावेश <sys/mman.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <unistd.h>
#समावेश <निश्चित.स>
#समावेश <माला.स>
#समावेश "srccode.h"
#समावेश "debug.h"
#समावेश <पूर्णांकernal/lib.h> // page_size
#समावेश "fncache.h"

#घोषणा MAXSRCCACHE (32*1024*1024)
#घोषणा MAXSRCखाताS     64
#घोषणा SRC_HTAB_SZ	64

काष्ठा srcfile अणु
	काष्ठा hlist_node hash_nd;
	काष्ठा list_head nd;
	अक्षर *fn;
	अक्षर **lines;
	अक्षर *map;
	अचिन्हित numlines;
	माप_प्रकार maplen;
पूर्ण;

अटल काष्ठा hlist_head srcfile_htab[SRC_HTAB_SZ];
अटल LIST_HEAD(srcfile_list);
अटल दीर्घ map_total_sz;
अटल पूर्णांक num_srcfiles;

अटल पूर्णांक countlines(अक्षर *map, पूर्णांक maplen)
अणु
	पूर्णांक numl;
	अक्षर *end = map + maplen;
	अक्षर *p = map;

	अगर (maplen == 0)
		वापस 0;
	numl = 0;
	जबतक (p < end && (p = स_प्रथम(p, '\n', end - p)) != शून्य) अणु
		numl++;
		p++;
	पूर्ण
	अगर (p < end)
		numl++;
	वापस numl;
पूर्ण

अटल व्योम fill_lines(अक्षर **lines, पूर्णांक maxline, अक्षर *map, पूर्णांक maplen)
अणु
	पूर्णांक l;
	अक्षर *end = map + maplen;
	अक्षर *p = map;

	अगर (maplen == 0 || maxline == 0)
		वापस;
	l = 0;
	lines[l++] = map;
	जबतक (p < end && (p = स_प्रथम(p, '\n', end - p)) != शून्य) अणु
		अगर (l >= maxline)
			वापस;
		lines[l++] = ++p;
	पूर्ण
	अगर (p < end)
		lines[l] = p;
पूर्ण

अटल व्योम मुक्त_srcfile(काष्ठा srcfile *sf)
अणु
	list_del_init(&sf->nd);
	hlist_del(&sf->hash_nd);
	map_total_sz -= sf->maplen;
	munmap(sf->map, sf->maplen);
	zमुक्त(&sf->lines);
	zमुक्त(&sf->fn);
	मुक्त(sf);
	num_srcfiles--;
पूर्ण

अटल काष्ठा srcfile *find_srcfile(अक्षर *fn)
अणु
	काष्ठा stat st;
	काष्ठा srcfile *h;
	पूर्णांक fd;
	अचिन्हित दीर्घ sz;
	अचिन्हित hval = shash((अचिन्हित अक्षर *)fn) % SRC_HTAB_SZ;

	hlist_क्रम_each_entry (h, &srcfile_htab[hval], hash_nd) अणु
		अगर (!म_भेद(fn, h->fn)) अणु
			/* Move to front */
			list_del(&h->nd);
			list_add(&h->nd, &srcfile_list);
			वापस h;
		पूर्ण
	पूर्ण

	/* Only prune अगर there is more than one entry */
	जबतक ((num_srcfiles > MAXSRCखाताS || map_total_sz > MAXSRCCACHE) &&
	       srcfile_list.next != &srcfile_list) अणु
		निश्चित(!list_empty(&srcfile_list));
		h = list_entry(srcfile_list.prev, काष्ठा srcfile, nd);
		मुक्त_srcfile(h);
	पूर्ण

	fd = खोलो(fn, O_RDONLY);
	अगर (fd < 0 || ख_स्थिति(fd, &st) < 0) अणु
		pr_debug("cannot open source file %s\n", fn);
		वापस शून्य;
	पूर्ण

	h = दो_स्मृति(माप(काष्ठा srcfile));
	अगर (!h)
		वापस शून्य;

	h->fn = strdup(fn);
	अगर (!h->fn)
		जाओ out_h;

	h->maplen = st.st_size;
	sz = (h->maplen + page_size - 1) & ~(page_size - 1);
	h->map = mmap(शून्य, sz, PROT_READ, MAP_SHARED, fd, 0);
	बंद(fd);
	अगर (h->map == (अक्षर *)-1) अणु
		pr_debug("cannot mmap source file %s\n", fn);
		जाओ out_fn;
	पूर्ण
	h->numlines = countlines(h->map, h->maplen);
	h->lines = सुस्मृति(h->numlines, माप(अक्षर *));
	अगर (!h->lines)
		जाओ out_map;
	fill_lines(h->lines, h->numlines, h->map, h->maplen);
	list_add(&h->nd, &srcfile_list);
	hlist_add_head(&h->hash_nd, &srcfile_htab[hval]);
	map_total_sz += h->maplen;
	num_srcfiles++;
	वापस h;

out_map:
	munmap(h->map, sz);
out_fn:
	zमुक्त(&h->fn);
out_h:
	मुक्त(h);
	वापस शून्य;
पूर्ण

/* Result is not 0 terminated */
अक्षर *find_sourceline(अक्षर *fn, अचिन्हित line, पूर्णांक *lenp)
अणु
	अक्षर *l, *p;
	काष्ठा srcfile *sf = find_srcfile(fn);
	अगर (!sf)
		वापस शून्य;
	line--;
	अगर (line >= sf->numlines)
		वापस शून्य;
	l = sf->lines[line];
	अगर (!l)
		वापस शून्य;
	p = स_प्रथम(l, '\n', sf->map + sf->maplen - l);
	*lenp = p - l;
	वापस l;
पूर्ण
