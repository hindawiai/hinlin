<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/hpfs/name.c
 *
 *  Mikulas Patocka (mikulas@artax.karlin.mff.cuni.cz), 1998-1999
 *
 *  operations with filenames
 */

#समावेश "hpfs_fn.h"

अटल अंतरभूत पूर्णांक not_allowed_अक्षर(अचिन्हित अक्षर c)
अणु
	वापस c<' ' || c=='"' || c=='*' || c=='/' || c==':' || c=='<' ||
	      c=='>' || c=='?' || c=='\\' || c=='|';
पूर्ण

अटल अंतरभूत पूर्णांक no_करोs_अक्षर(अचिन्हित अक्षर c)
अणु	/* Characters that are allowed in HPFS but not in DOS */
	वापस c=='+' || c==',' || c==';' || c=='=' || c=='[' || c==']';
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर upहाल(अचिन्हित अक्षर *dir, अचिन्हित अक्षर a)
अणु
	अगर (a<128 || a==255) वापस a>='a' && a<='z' ? a - 0x20 : a;
	अगर (!dir) वापस a;
	वापस dir[a-128];
पूर्ण

अचिन्हित अक्षर hpfs_upहाल(अचिन्हित अक्षर *dir, अचिन्हित अक्षर a)
अणु
	वापस upहाल(dir, a);
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर loहाल(अचिन्हित अक्षर *dir, अचिन्हित अक्षर a)
अणु
	अगर (a<128 || a==255) वापस a>='A' && a<='Z' ? a + 0x20 : a;
	अगर (!dir) वापस a;
	वापस dir[a];
पूर्ण

पूर्णांक hpfs_chk_name(स्थिर अचिन्हित अक्षर *name, अचिन्हित *len)
अणु
	पूर्णांक i;
	अगर (*len > 254) वापस -ENAMETOOLONG;
	hpfs_adjust_length(name, len);
	अगर (!*len) वापस -EINVAL;
	क्रम (i = 0; i < *len; i++) अगर (not_allowed_अक्षर(name[i])) वापस -EINVAL;
	अगर (*len == 1) अगर (name[0] == '.') वापस -EINVAL;
	अगर (*len == 2) अगर (name[0] == '.' && name[1] == '.') वापस -EINVAL;
	वापस 0;
पूर्ण

अचिन्हित अक्षर *hpfs_translate_name(काष्ठा super_block *s, अचिन्हित अक्षर *from,
			  अचिन्हित len, पूर्णांक lc, पूर्णांक lng)
अणु
	अचिन्हित अक्षर *to;
	पूर्णांक i;
	अगर (hpfs_sb(s)->sb_chk >= 2) अगर (hpfs_is_name_दीर्घ(from, len) != lng) अणु
		pr_err("Long name flag mismatch - name ");
		क्रम (i = 0; i < len; i++)
			pr_cont("%c", from[i]);
		pr_cont(" misidentified as %s.\n", lng ? "short" : "long");
		pr_err("It's nothing serious. It could happen because of bug in OS/2.\nSet checks=normal to disable this message.\n");
	पूर्ण
	अगर (!lc) वापस from;
	अगर (!(to = kदो_स्मृति(len, GFP_KERNEL))) अणु
		pr_err("can't allocate memory for name conversion buffer\n");
		वापस from;
	पूर्ण
	क्रम (i = 0; i < len; i++) to[i] = loहाल(hpfs_sb(s)->sb_cp_table,from[i]);
	वापस to;
पूर्ण

पूर्णांक hpfs_compare_names(काष्ठा super_block *s,
		       स्थिर अचिन्हित अक्षर *n1, अचिन्हित l1,
		       स्थिर अचिन्हित अक्षर *n2, अचिन्हित l2, पूर्णांक last)
अणु
	अचिन्हित l = l1 < l2 ? l1 : l2;
	अचिन्हित i;
	अगर (last) वापस -1;
	क्रम (i = 0; i < l; i++) अणु
		अचिन्हित अक्षर c1 = upहाल(hpfs_sb(s)->sb_cp_table,n1[i]);
		अचिन्हित अक्षर c2 = upहाल(hpfs_sb(s)->sb_cp_table,n2[i]);
		अगर (c1 < c2) वापस -1;
		अगर (c1 > c2) वापस 1;
	पूर्ण
	अगर (l1 < l2) वापस -1;
	अगर (l1 > l2) वापस 1;
	वापस 0;
पूर्ण

पूर्णांक hpfs_is_name_दीर्घ(स्थिर अचिन्हित अक्षर *name, अचिन्हित len)
अणु
	पूर्णांक i,j;
	क्रम (i = 0; i < len && name[i] != '.'; i++)
		अगर (no_करोs_अक्षर(name[i])) वापस 1;
	अगर (!i || i > 8) वापस 1;
	अगर (i == len) वापस 0;
	क्रम (j = i + 1; j < len; j++)
		अगर (name[j] == '.' || no_करोs_अक्षर(name[i])) वापस 1;
	वापस j - i > 4;
पूर्ण

/* OS/2 clears करोts and spaces at the end of file name, so we have to */

व्योम hpfs_adjust_length(स्थिर अचिन्हित अक्षर *name, अचिन्हित *len)
अणु
	अगर (!*len) वापस;
	अगर (*len == 1 && name[0] == '.') वापस;
	अगर (*len == 2 && name[0] == '.' && name[1] == '.') वापस;
	जबतक (*len && (name[*len - 1] == '.' || name[*len - 1] == ' '))
		(*len)--;
पूर्ण
