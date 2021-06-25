<शैली गुरु>
#समावेश "util/map_symbol.h"
#समावेश "util/branch.h"
#समावेश <linux/kernel.h>

अटल bool cross_area(u64 addr1, u64 addr2, पूर्णांक size)
अणु
	u64 align1, align2;

	align1 = addr1 & ~(size - 1);
	align2 = addr2 & ~(size - 1);

	वापस (align1 != align2) ? true : false;
पूर्ण

#घोषणा AREA_4K		4096
#घोषणा AREA_2M		(2 * 1024 * 1024)

व्योम branch_type_count(काष्ठा branch_type_stat *st, काष्ठा branch_flags *flags,
		       u64 from, u64 to)
अणु
	अगर (flags->type == PERF_BR_UNKNOWN || from == 0)
		वापस;

	st->counts[flags->type]++;

	अगर (flags->type == PERF_BR_COND) अणु
		अगर (to > from)
			st->cond_fwd++;
		अन्यथा
			st->cond_bwd++;
	पूर्ण

	अगर (cross_area(from, to, AREA_2M))
		st->cross_2m++;
	अन्यथा अगर (cross_area(from, to, AREA_4K))
		st->cross_4k++;
पूर्ण

स्थिर अक्षर *branch_type_name(पूर्णांक type)
अणु
	स्थिर अक्षर *branch_names[PERF_BR_MAX] = अणु
		"N/A",
		"COND",
		"UNCOND",
		"IND",
		"CALL",
		"IND_CALL",
		"RET",
		"SYSCALL",
		"SYSRET",
		"COND_CALL",
		"COND_RET"
	पूर्ण;

	अगर (type >= 0 && type < PERF_BR_MAX)
		वापस branch_names[type];

	वापस शून्य;
पूर्ण

व्योम branch_type_stat_display(खाता *fp, काष्ठा branch_type_stat *st)
अणु
	u64 total = 0;
	पूर्णांक i;

	क्रम (i = 0; i < PERF_BR_MAX; i++)
		total += st->counts[i];

	अगर (total == 0)
		वापस;

	ख_लिखो(fp, "\n#");
	ख_लिखो(fp, "\n# Branch Statistics:");
	ख_लिखो(fp, "\n#");

	अगर (st->cond_fwd > 0) अणु
		ख_लिखो(fp, "\n%8s: %5.1f%%",
			"COND_FWD",
			100.0 * (द्विगुन)st->cond_fwd / (द्विगुन)total);
	पूर्ण

	अगर (st->cond_bwd > 0) अणु
		ख_लिखो(fp, "\n%8s: %5.1f%%",
			"COND_BWD",
			100.0 * (द्विगुन)st->cond_bwd / (द्विगुन)total);
	पूर्ण

	अगर (st->cross_4k > 0) अणु
		ख_लिखो(fp, "\n%8s: %5.1f%%",
			"CROSS_4K",
			100.0 * (द्विगुन)st->cross_4k / (द्विगुन)total);
	पूर्ण

	अगर (st->cross_2m > 0) अणु
		ख_लिखो(fp, "\n%8s: %5.1f%%",
			"CROSS_2M",
			100.0 * (द्विगुन)st->cross_2m / (द्विगुन)total);
	पूर्ण

	क्रम (i = 0; i < PERF_BR_MAX; i++) अणु
		अगर (st->counts[i] > 0)
			ख_लिखो(fp, "\n%8s: %5.1f%%",
				branch_type_name(i),
				100.0 *
				(द्विगुन)st->counts[i] / (द्विगुन)total);
	पूर्ण
पूर्ण

अटल पूर्णांक count_str_scnम_लिखो(पूर्णांक idx, स्थिर अक्षर *str, अक्षर *bf, पूर्णांक size)
अणु
	वापस scnम_लिखो(bf, size, "%s%s", (idx) ? " " : " (", str);
पूर्ण

पूर्णांक branch_type_str(काष्ठा branch_type_stat *st, अक्षर *bf, पूर्णांक size)
अणु
	पूर्णांक i, j = 0, prपूर्णांकed = 0;
	u64 total = 0;

	क्रम (i = 0; i < PERF_BR_MAX; i++)
		total += st->counts[i];

	अगर (total == 0)
		वापस 0;

	अगर (st->cond_fwd > 0)
		prपूर्णांकed += count_str_scnम_लिखो(j++, "COND_FWD", bf + prपूर्णांकed, size - prपूर्णांकed);

	अगर (st->cond_bwd > 0)
		prपूर्णांकed += count_str_scnम_लिखो(j++, "COND_BWD", bf + prपूर्णांकed, size - prपूर्णांकed);

	क्रम (i = 0; i < PERF_BR_MAX; i++) अणु
		अगर (i == PERF_BR_COND)
			जारी;

		अगर (st->counts[i] > 0)
			prपूर्णांकed += count_str_scnम_लिखो(j++, branch_type_name(i), bf + prपूर्णांकed, size - prपूर्णांकed);
	पूर्ण

	अगर (st->cross_4k > 0)
		prपूर्णांकed += count_str_scnम_लिखो(j++, "CROSS_4K", bf + prपूर्णांकed, size - prपूर्णांकed);

	अगर (st->cross_2m > 0)
		prपूर्णांकed += count_str_scnम_लिखो(j++, "CROSS_2M", bf + prपूर्णांकed, size - prपूर्णांकed);

	वापस prपूर्णांकed;
पूर्ण
