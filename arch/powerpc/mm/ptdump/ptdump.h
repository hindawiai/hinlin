<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/types.h>
#समावेश <linux/seq_file.h>

काष्ठा flag_info अणु
	u64		mask;
	u64		val;
	स्थिर अक्षर	*set;
	स्थिर अक्षर	*clear;
	bool		is_val;
	पूर्णांक		shअगरt;
पूर्ण;

काष्ठा pgtable_level अणु
	स्थिर काष्ठा flag_info *flag;
	माप_प्रकार num;
	u64 mask;
पूर्ण;

बाह्य काष्ठा pgtable_level pg_level[5];

व्योम pt_dump_size(काष्ठा seq_file *m, अचिन्हित दीर्घ delta);
