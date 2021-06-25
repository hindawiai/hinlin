<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * User-space helper to sort the output of /sys/kernel/debug/page_owner
 *
 * Example use:
 * cat /sys/kernel/debug/page_owner > page_owner_full.txt
 * ./page_owner_sort page_owner_full.txt sorted_page_owner.txt
 *
 * See Documentation/vm/page_owner.rst
*/

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <unistd.h>
#समावेश <माला.स>

काष्ठा block_list अणु
	अक्षर *txt;
	पूर्णांक len;
	पूर्णांक num;
पूर्ण;


अटल काष्ठा block_list *list;
अटल पूर्णांक list_size;
अटल पूर्णांक max_size;

काष्ठा block_list *block_head;

पूर्णांक पढ़ो_block(अक्षर *buf, पूर्णांक buf_size, खाता *fin)
अणु
	अक्षर *curr = buf, *स्थिर buf_end = buf + buf_size;

	जबतक (buf_end - curr > 1 && ख_माला_लो(curr, buf_end - curr, fin)) अणु
		अगर (*curr == '\n') /* empty line */
			वापस curr - buf;
		अगर (!म_भेदन(curr, "PFN", 3))
			जारी;
		curr += म_माप(curr);
	पूर्ण

	वापस -1; /* खातापूर्ण or no space left in buf. */
पूर्ण

अटल पूर्णांक compare_txt(स्थिर व्योम *p1, स्थिर व्योम *p2)
अणु
	स्थिर काष्ठा block_list *l1 = p1, *l2 = p2;

	वापस म_भेद(l1->txt, l2->txt);
पूर्ण

अटल पूर्णांक compare_num(स्थिर व्योम *p1, स्थिर व्योम *p2)
अणु
	स्थिर काष्ठा block_list *l1 = p1, *l2 = p2;

	वापस l2->num - l1->num;
पूर्ण

अटल व्योम add_list(अक्षर *buf, पूर्णांक len)
अणु
	अगर (list_size != 0 &&
	    len == list[list_size-1].len &&
	    स_भेद(buf, list[list_size-1].txt, len) == 0) अणु
		list[list_size-1].num++;
		वापस;
	पूर्ण
	अगर (list_size == max_size) अणु
		म_लिखो("max_size too small??\n");
		निकास(1);
	पूर्ण
	list[list_size].txt = दो_स्मृति(len+1);
	list[list_size].len = len;
	list[list_size].num = 1;
	स_नकल(list[list_size].txt, buf, len);
	list[list_size].txt[len] = 0;
	list_size++;
	अगर (list_size % 1000 == 0) अणु
		म_लिखो("loaded %d\r", list_size);
		ख_साफ(मानक_निकास);
	पूर्ण
पूर्ण

#घोषणा BUF_SIZE	(128 * 1024)

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	खाता *fin, *fout;
	अक्षर *buf;
	पूर्णांक ret, i, count;
	काष्ठा block_list *list2;
	काष्ठा stat st;

	अगर (argc < 3) अणु
		म_लिखो("Usage: ./program <input> <output>\n");
		लिखो_त्रुटि("open: ");
		निकास(1);
	पूर्ण

	fin = ख_खोलो(argv[1], "r");
	fout = ख_खोलो(argv[2], "w");
	अगर (!fin || !fout) अणु
		म_लिखो("Usage: ./program <input> <output>\n");
		लिखो_त्रुटि("open: ");
		निकास(1);
	पूर्ण

	ख_स्थिति(fileno(fin), &st);
	max_size = st.st_size / 100; /* hack ... */

	list = दो_स्मृति(max_size * माप(*list));
	buf = दो_स्मृति(BUF_SIZE);
	अगर (!list || !buf) अणु
		म_लिखो("Out of memory\n");
		निकास(1);
	पूर्ण

	क्रम ( ; ; ) अणु
		ret = पढ़ो_block(buf, BUF_SIZE, fin);
		अगर (ret < 0)
			अवरोध;

		add_list(buf, ret);
	पूर्ण

	म_लिखो("loaded %d\n", list_size);

	म_लिखो("sorting ....\n");

	क्विक(list, list_size, माप(list[0]), compare_txt);

	list2 = दो_स्मृति(माप(*list) * list_size);

	म_लिखो("culling\n");

	क्रम (i = count = 0; i < list_size; i++) अणु
		अगर (count == 0 ||
		    म_भेद(list2[count-1].txt, list[i].txt) != 0) अणु
			list2[count++] = list[i];
		पूर्ण अन्यथा अणु
			list2[count-1].num += list[i].num;
		पूर्ण
	पूर्ण

	क्विक(list2, count, माप(list[0]), compare_num);

	क्रम (i = 0; i < count; i++)
		ख_लिखो(fout, "%d times:\n%s\n", list2[i].num, list2[i].txt);

	वापस 0;
पूर्ण
