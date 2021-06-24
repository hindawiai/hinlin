<शैली गुरु>
/*
 * Copyright (c) 2017 Oracle and/or its affiliates. All rights reserved.
 */

#अगर_अघोषित _ASM_SPARC_VVAR_DATA_H
#घोषणा _ASM_SPARC_VVAR_DATA_H

#समावेश <यंत्र/घड़ीsource.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/barrier.h>
#समावेश <linux/समय.स>
#समावेश <linux/types.h>

काष्ठा vvar_data अणु
	अचिन्हित पूर्णांक seq;

	पूर्णांक vघड़ी_mode;
	काष्ठा अणु /* extract of a घड़ीsource काष्ठा */
		u64	cycle_last;
		u64	mask;
		पूर्णांक	mult;
		पूर्णांक	shअगरt;
	पूर्ण घड़ी;
	/* खोलो coded 'struct timespec' */
	u64		wall_समय_sec;
	u64		wall_समय_snsec;
	u64		monotonic_समय_snsec;
	u64		monotonic_समय_sec;
	u64		monotonic_समय_coarse_sec;
	u64		monotonic_समय_coarse_nsec;
	u64		wall_समय_coarse_sec;
	u64		wall_समय_coarse_nsec;

	पूर्णांक		tz_minuteswest;
	पूर्णांक		tz_dstसमय;
पूर्ण;

बाह्य काष्ठा vvar_data *vvar_data;
बाह्य पूर्णांक vdso_fix_stick;

अटल अंतरभूत अचिन्हित पूर्णांक vvar_पढ़ो_begin(स्थिर काष्ठा vvar_data *s)
अणु
	अचिन्हित पूर्णांक ret;

repeat:
	ret = READ_ONCE(s->seq);
	अगर (unlikely(ret & 1)) अणु
		cpu_relax();
		जाओ repeat;
	पूर्ण
	smp_rmb(); /* Finish all पढ़ोs beक्रमe we वापस seq */
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक vvar_पढ़ो_retry(स्थिर काष्ठा vvar_data *s,
					अचिन्हित पूर्णांक start)
अणु
	smp_rmb(); /* Finish all पढ़ोs beक्रमe checking the value of seq */
	वापस unlikely(s->seq != start);
पूर्ण

अटल अंतरभूत व्योम vvar_ग_लिखो_begin(काष्ठा vvar_data *s)
अणु
	++s->seq;
	smp_wmb(); /* Makes sure that increment of seq is reflected */
पूर्ण

अटल अंतरभूत व्योम vvar_ग_लिखो_end(काष्ठा vvar_data *s)
अणु
	smp_wmb(); /* Makes the value of seq current beक्रमe we increment */
	++s->seq;
पूर्ण


#पूर्ण_अगर /* _ASM_SPARC_VVAR_DATA_H */
