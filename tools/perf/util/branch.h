<शैली गुरु>
#अगर_अघोषित _PERF_BRANCH_H
#घोषणा _PERF_BRANCH_H 1
/*
 * The linux/मानकघोष.स isn't need here, but is needed क्रम __always_अंतरभूत used
 * in files included from uapi/linux/perf_event.h such as
 * /usr/include/linux/swab.h and /usr/include/linux/byteorder/little_endian.h,
 * detected in at least musl libc, used in Alpine Linux. -acme
 */
#समावेश <मानकपन.स>
#समावेश <मानक_निवेशt.h>
#समावेश <linux/compiler.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/perf_event.h>
#समावेश <linux/types.h>
#समावेश "event.h"

काष्ठा branch_flags अणु
	जोड़ अणु
		u64 value;
		काष्ठा अणु
			u64 mispred:1;
			u64 predicted:1;
			u64 in_tx:1;
			u64 पात:1;
			u64 cycles:16;
			u64 type:4;
			u64 reserved:40;
		पूर्ण;
	पूर्ण;
पूर्ण;

काष्ठा branch_info अणु
	काष्ठा addr_map_symbol from;
	काष्ठा addr_map_symbol to;
	काष्ठा branch_flags    flags;
	अक्षर		       *srcline_from;
	अक्षर		       *srcline_to;
पूर्ण;

काष्ठा branch_entry अणु
	u64			from;
	u64			to;
	काष्ठा branch_flags	flags;
पूर्ण;

काष्ठा branch_stack अणु
	u64			nr;
	u64			hw_idx;
	काष्ठा branch_entry	entries[];
पूर्ण;

/*
 * The hw_idx is only available when PERF_SAMPLE_BRANCH_HW_INDEX is applied.
 * Otherwise, the output क्रमmat of a sample with branch stack is
 * काष्ठा branch_stack अणु
 *	u64			nr;
 *	काष्ठा branch_entry	entries[0];
 * पूर्ण
 * Check whether the hw_idx is available,
 * and वापस the corresponding poपूर्णांकer of entries[0].
 */
अटल अंतरभूत काष्ठा branch_entry *perf_sample__branch_entries(काष्ठा perf_sample *sample)
अणु
	u64 *entry = (u64 *)sample->branch_stack;

	entry++;
	अगर (sample->no_hw_idx)
		वापस (काष्ठा branch_entry *)entry;
	वापस (काष्ठा branch_entry *)(++entry);
पूर्ण

काष्ठा branch_type_stat अणु
	bool	branch_to;
	u64	counts[PERF_BR_MAX];
	u64	cond_fwd;
	u64	cond_bwd;
	u64	cross_4k;
	u64	cross_2m;
पूर्ण;

व्योम branch_type_count(काष्ठा branch_type_stat *st, काष्ठा branch_flags *flags,
		       u64 from, u64 to);

स्थिर अक्षर *branch_type_name(पूर्णांक type);
व्योम branch_type_stat_display(खाता *fp, काष्ठा branch_type_stat *st);
पूर्णांक branch_type_str(काष्ठा branch_type_stat *st, अक्षर *bf, पूर्णांक bfsize);

#पूर्ण_अगर /* _PERF_BRANCH_H */
