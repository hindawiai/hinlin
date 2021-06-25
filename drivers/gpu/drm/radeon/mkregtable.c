<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/* utility to create the रेजिस्टर check tables
 * this includes अंतरभूतd list.h safe क्रम userspace.
 *
 * Copyright 2009 Jerome Glisse
 * Copyright 2009 Red Hat Inc.
 *
 * Authors:
 * 	Jerome Glisse
 * 	Dave Airlie
 */

#समावेश <sys/types.h>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <मानकपन.स>
#समावेश <regex.h>
#समावेश <libgen.h>

#घोषणा दुरत्व(TYPE, MEMBER) ((माप_प्रकार) &((TYPE *)0)->MEMBER)
/**
 * container_of - cast a member of a काष्ठाure out to the containing काष्ठाure
 * @ptr:    the poपूर्णांकer to the member.
 * @type:   the type of the container काष्ठा this is embedded in.
 * @member: the name of the member within the काष्ठा.
 *
 */
#घोषणा container_of(ptr, type, member) (अणु          \
	स्थिर typeof(((type *)0)->member)*__mptr = (ptr);    \
		     (type *)((अक्षर *)__mptr - दुरत्व(type, member)); पूर्ण)

/*
 * Simple करोubly linked list implementation.
 *
 * Some of the पूर्णांकernal functions ("__xxx") are useful when
 * manipulating whole lists rather than single entries, as
 * someबार we alपढ़ोy know the next/prev entries and we can
 * generate better code by using them directly rather than
 * using the generic single-entry routines.
 */

काष्ठा list_head अणु
	काष्ठा list_head *next, *prev;
पूर्ण;


अटल अंतरभूत व्योम INIT_LIST_HEAD(काष्ठा list_head *list)
अणु
	list->next = list;
	list->prev = list;
पूर्ण

/*
 * Insert a new entry between two known consecutive entries.
 *
 * This is only क्रम पूर्णांकernal list manipulation where we know
 * the prev/next entries alपढ़ोy!
 */
#अगर_अघोषित CONFIG_DEBUG_LIST
अटल अंतरभूत व्योम __list_add(काष्ठा list_head *new,
			      काष्ठा list_head *prev, काष्ठा list_head *next)
अणु
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
पूर्ण
#अन्यथा
बाह्य व्योम __list_add(काष्ठा list_head *new,
		       काष्ठा list_head *prev, काष्ठा list_head *next);
#पूर्ण_अगर

/**
 * list_add_tail - add a new entry
 * @new: new entry to be added
 * @head: list head to add it beक्रमe
 *
 * Insert a new entry beक्रमe the specअगरied head.
 * This is useful क्रम implementing queues.
 */
अटल अंतरभूत व्योम list_add_tail(काष्ठा list_head *new, काष्ठा list_head *head)
अणु
	__list_add(new, head->prev, head);
पूर्ण

/**
 * list_entry - get the काष्ठा क्रम this entry
 * @ptr:	the &काष्ठा list_head poपूर्णांकer.
 * @type:	the type of the काष्ठा this is embedded in.
 * @member:	the name of the list_head within the काष्ठा.
 */
#घोषणा list_entry(ptr, type, member) \
	container_of(ptr, type, member)

/**
 * list_क्रम_each_entry	-	iterate over list of given type
 * @pos:	the type * to use as a loop cursor.
 * @head:	the head क्रम your list.
 * @member:	the name of the list_head within the काष्ठा.
 */
#घोषणा list_क्रम_each_entry(pos, head, member)				\
	क्रम (pos = list_entry((head)->next, typeof(*pos), member);	\
	     &pos->member != (head); 	\
	     pos = list_entry(pos->member.next, typeof(*pos), member))

काष्ठा offset अणु
	काष्ठा list_head list;
	अचिन्हित offset;
पूर्ण;

काष्ठा table अणु
	काष्ठा list_head offsets;
	अचिन्हित offset_max;
	अचिन्हित nentry;
	अचिन्हित *table;
	अक्षर *gpu_prefix;
पूर्ण;

अटल काष्ठा offset *offset_new(अचिन्हित o)
अणु
	काष्ठा offset *offset;

	offset = (काष्ठा offset *)दो_स्मृति(माप(काष्ठा offset));
	अगर (offset) अणु
		INIT_LIST_HEAD(&offset->list);
		offset->offset = o;
	पूर्ण
	वापस offset;
पूर्ण

अटल व्योम table_offset_add(काष्ठा table *t, काष्ठा offset *offset)
अणु
	list_add_tail(&offset->list, &t->offsets);
पूर्ण

अटल व्योम table_init(काष्ठा table *t)
अणु
	INIT_LIST_HEAD(&t->offsets);
	t->offset_max = 0;
	t->nentry = 0;
	t->table = शून्य;
पूर्ण

अटल व्योम table_prपूर्णांक(काष्ठा table *t)
अणु
	अचिन्हित nlloop, i, j, n, c, id;

	nlloop = (t->nentry + 3) / 4;
	c = t->nentry;
	म_लिखो("static const unsigned %s_reg_safe_bm[%d] = {\n", t->gpu_prefix,
	       t->nentry);
	क्रम (i = 0, id = 0; i < nlloop; i++) अणु
		n = 4;
		अगर (n > c)
			n = c;
		c -= n;
		क्रम (j = 0; j < n; j++) अणु
			अगर (j == 0)
				म_लिखो("\t");
			अन्यथा
				म_लिखो(" ");
			म_लिखो("0x%08X,", t->table[id++]);
		पूर्ण
		म_लिखो("\n");
	पूर्ण
	म_लिखो("};\n");
पूर्ण

अटल पूर्णांक table_build(काष्ठा table *t)
अणु
	काष्ठा offset *offset;
	अचिन्हित i, m;

	t->nentry = ((t->offset_max >> 2) + 31) / 32;
	t->table = (अचिन्हित *)दो_स्मृति(माप(अचिन्हित) * t->nentry);
	अगर (t->table == शून्य)
		वापस -1;
	स_रखो(t->table, 0xff, माप(अचिन्हित) * t->nentry);
	list_क्रम_each_entry(offset, &t->offsets, list) अणु
		i = (offset->offset >> 2) / 32;
		m = (offset->offset >> 2) & 31;
		m = 1 << m;
		t->table[i] ^= m;
	पूर्ण
	वापस 0;
पूर्ण

अटल अक्षर gpu_name[10];
अटल पूर्णांक parser_auth(काष्ठा table *t, स्थिर अक्षर *filename)
अणु
	खाता *file;
	regex_t mask_rex;
	regmatch_t match[4];
	अक्षर buf[1024];
	माप_प्रकार end;
	पूर्णांक len;
	पूर्णांक करोne = 0;
	पूर्णांक r;
	अचिन्हित o;
	काष्ठा offset *offset;
	अक्षर last_reg_s[10];
	पूर्णांक last_reg;

	अगर (regcomp
	    (&mask_rex, "(0x[0-9a-fA-F]*) *([_a-zA-Z0-9]*)", REG_EXTENDED)) अणु
		ख_लिखो(मानक_त्रुटि, "Failed to compile regular expression\n");
		वापस -1;
	पूर्ण
	file = ख_खोलो(filename, "r");
	अगर (file == शून्य) अणु
		ख_लिखो(मानक_त्रुटि, "Failed to open: %s\n", filename);
		वापस -1;
	पूर्ण
	ख_जाओ(file, 0, अंत_से);
	end = ख_बताओ(file);
	ख_जाओ(file, 0, शुरू_से);

	/* get header */
	अगर (ख_माला_लो(buf, 1024, file) == शून्य) अणु
		ख_बंद(file);
		वापस -1;
	पूर्ण

	/* first line will contain the last रेजिस्टर
	 * and gpu name */
	माला_पूछो(buf, "%9s %9s", gpu_name, last_reg_s);
	t->gpu_prefix = gpu_name;
	last_reg = म_से_दीर्घ(last_reg_s, शून्य, 16);

	करो अणु
		अगर (ख_माला_लो(buf, 1024, file) == शून्य) अणु
			ख_बंद(file);
			वापस -1;
		पूर्ण
		len = म_माप(buf);
		अगर (ख_बताओ(file) == end)
			करोne = 1;
		अगर (len) अणु
			r = regexec(&mask_rex, buf, 4, match, 0);
			अगर (r == REG_NOMATCH) अणु
			पूर्ण अन्यथा अगर (r) अणु
				ख_लिखो(मानक_त्रुटि,
					"Error matching regular expression %d in %s\n",
					r, filename);
				ख_बंद(file);
				वापस -1;
			पूर्ण अन्यथा अणु
				buf[match[0].rm_eo] = 0;
				buf[match[1].rm_eo] = 0;
				buf[match[2].rm_eo] = 0;
				o = म_से_दीर्घ(&buf[match[1].rm_so], शून्य, 16);
				offset = offset_new(o);
				table_offset_add(t, offset);
				अगर (o > t->offset_max)
					t->offset_max = o;
			पूर्ण
		पूर्ण
	पूर्ण जबतक (!करोne);
	ख_बंद(file);
	अगर (t->offset_max < last_reg)
		t->offset_max = last_reg;
	वापस table_build(t);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	काष्ठा table t;

	अगर (argc != 2) अणु
		ख_लिखो(मानक_त्रुटि, "Usage: %s <authfile>\n", argv[0]);
		निकास(1);
	पूर्ण
	table_init(&t);
	अगर (parser_auth(&t, argv[1])) अणु
		ख_लिखो(मानक_त्रुटि, "Failed to parse file %s\n", argv[1]);
		वापस -1;
	पूर्ण
	table_prपूर्णांक(&t);
	वापस 0;
पूर्ण
